// This contains the meta-type used by PyQt.
//
// Copyright (c) 2010 Riverbank Computing Limited <info@riverbankcomputing.com>
// 
// This file is part of PyQt.
// 
// This file may be used under the terms of the GNU General Public
// License versions 2.0 or 3.0 as published by the Free Software
// Foundation and appearing in the files LICENSE.GPL2 and LICENSE.GPL3
// included in the packaging of this file.  Alternatively you may (at
// your option) use any later version of the GNU General Public
// License if such license has been publicly approved by Riverbank
// Computing Limited (or its successors, if any) and the KDE Free Qt
// Foundation. In addition, as a special exception, Riverbank gives you
// certain additional rights. These rights are described in the Riverbank
// GPL Exception version 1.1, which can be found in the file
// GPL_EXCEPTION.txt in this package.
// 
// Please review the following information to ensure GNU General
// Public Licensing requirements will be met:
// http://trolltech.com/products/qt/licenses/licensing/opensource/. If
// you are unsure which license is appropriate for your use, please
// review the following information:
// http://trolltech.com/products/qt/licenses/licensing/licensingoverview
// or contact the sales department at sales@riverbankcomputing.com.
// 
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.


#include <Python.h>

#include <QByteArray>
#include <QList>
#include <QMap>
#include <QMetaObject>
#include <QMetaType>
#include <QPair>
#include <QPointer>

#include "qpycore_chimera.h"
#include "qpycore_misc.h"
#include "qpycore_pyqtproperty.h"
#include "qpycore_pyqtsignal.h"
#include "qpycore_sip.h"
#include "qpycore_types.h"


// The type of the static meta-call function.
typedef int (*static_metacall_func)(sipTypeDef *, QMetaObject::Call, int,
        void **);


// Forward declarations.
extern "C" {
static PyObject *pyqtWrapperType_call(PyObject *type, PyObject *args,
        PyObject *kwds);
static int pyqtWrapperType_init(pyqtWrapperType *self, PyObject *args,
        PyObject *kwds);
static void *qpointer_access_func(sipSimpleWrapper *w, AccessFuncOp op);
}

static int create_dynamic_metaobject(pyqtWrapperType *pyqt_wt);
static int add_arg_names(qpycore_metaobject *qo, const QByteArray &sig,
        int empty);
static const QMetaObject *get_scope_qmetaobject(const Chimera *ct);
static const QMetaObject *get_qmetaobject(pyqtWrapperType *pyqt_wt);


// The meta-type for PyQt classes.
PyTypeObject qpycore_pyqtWrapperType_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    SIP_TPNAME_CAST("PyQt4.QtCore.pyqtWrapperType"),    /* tp_name */
    sizeof (pyqtWrapperType),   /* tp_basicsize */
    0,                      /* tp_itemsize */
    0,                      /* tp_dealloc */
    0,                      /* tp_print */
    0,                      /* tp_getattr */
    0,                      /* tp_setattr */
    0,                      /* tp_compare */
    0,                      /* tp_repr */
    0,                      /* tp_as_number */
    0,                      /* tp_as_sequence */
    0,                      /* tp_as_mapping */
    0,                      /* tp_hash */
    pyqtWrapperType_call,   /* tp_call */
    0,                      /* tp_str */
    0,                      /* tp_getattro */
    0,                      /* tp_setattro */
    0,                      /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,   /* tp_flags */
    0,                      /* tp_doc */
    0,                      /* tp_traverse */
    0,                      /* tp_clear */
    0,                      /* tp_richcompare */
    0,                      /* tp_weaklistoffset */
    0,                      /* tp_iter */
    0,                      /* tp_iternext */
    0,                      /* tp_methods */
    0,                      /* tp_members */
    0,                      /* tp_getset */
    0,                      /* tp_base */
    0,                      /* tp_dict */
    0,                      /* tp_descr_get */
    0,                      /* tp_descr_set */
    0,                      /* tp_dictoffset */
    (initproc)pyqtWrapperType_init, /* tp_init */
    0,                      /* tp_alloc */
    0,                      /* tp_new */
    0,                      /* tp_free */
    0,                      /* tp_is_gc */
    0,                      /* tp_bases */
    0,                      /* tp_mro */
    0,                      /* tp_cache */
    0,                      /* tp_subclasses */
    0,                      /* tp_weaklist */
    0,                      /* tp_del */
#if PY_VERSION_HEX >= 0x02060000
    0,                      /* tp_version_tag */
#endif
};


// The type init slot.
static int pyqtWrapperType_init(pyqtWrapperType *self, PyObject *args,
        PyObject *kwds)
{
    // Let the super-type complete the basic initialisation.
    if (sipWrapperType_Type->tp_init((PyObject *)self, args, kwds) < 0)
        return -1;

    pyqt4ClassTypeDef *pyqt_td = (pyqt4ClassTypeDef *)((sipWrapperType *)self)->type;

    if (pyqt_td && !sipIsExactWrappedType((sipWrapperType *)self))
    {
        // Create a dynamic meta-object as its base wrapped type has a static
        // Qt meta-object.
        if (pyqt_td->qt4_static_metaobject && create_dynamic_metaobject(self) < 0)
            return -1;
    }

    return 0;
}


// Create a dynamic meta-object for a Python type by introspecting its
// attributes.  Note that it leaks if the type is deleted.
static int create_dynamic_metaobject(pyqtWrapperType *pyqt_wt)
{
    PyTypeObject *pytype = (PyTypeObject *)pyqt_wt;
    qpycore_metaobject *qo = new qpycore_metaobject;

    // Get the super-type's meta-object.
    qo->mo.d.superdata = get_qmetaobject((pyqtWrapperType *)pytype->tp_base);

    // Get the name of the type.  Dynamic types have simple names.
    qo->str_data = pytype->tp_name;
    qo->str_data.append('\0');

    // Go through the class dictionary getting all PyQt properties, slots,
    // signals or a (deprecated) sequence of signals.

    typedef QPair<PyObject *, PyObject *> prop_data;
    QMap<uint, prop_data> pprops;
    QList<QByteArray> psigs;
    QList<const QMetaObject *> enum_scopes;
    SIP_SSIZE_T pos = 0;
    PyObject *key, *value;
    bool has_notify_signal = false;

    while (PyDict_Next(pytype->tp_dict, &pos, &key, &value))
    {
        // See if it is a slot, ie. it has been decorated with pyqtSlot().
        PyObject *sig_obj = PyObject_GetAttr(value,
                qpycore_signature_attr_name);

        if (sig_obj)
        {
            // Make sure it is a list and not some legitimate attribute that
            // happens to use our special name.
            if (PyList_Check(sig_obj))
            {
                for (SIP_SSIZE_T i = 0; i < PyList_GET_SIZE(sig_obj); ++i)
                {
                    qpycore_slot slot;

                    // Set up the skeleton slot.
                    PyObject *decoration = PyList_GET_ITEM(sig_obj, i);
                    slot.signature = Chimera::Signature::fromPyObject(decoration);

                    slot.sip_slot.pyobj = 0;
                    slot.sip_slot.name = 0;
                    slot.sip_slot.meth.mfunc = value;
                    slot.sip_slot.meth.mself = 0;
#if PY_MAJOR_VERSION < 3
                    slot.sip_slot.meth.mclass = (PyObject *)pyqt_wt;
#endif
                    slot.sip_slot.weakSlot = 0;

                    qo->pslots.append(slot);
                }
            }

            Py_DECREF(sig_obj);
        }
        else
        {
            PyErr_Clear();

            // Make sure the key is an ASCII string.  Delay the error checking
            // until we know we actually need it.
            const char *ascii_key = sipString_AsASCIIString(&key);

            // See if the value is of interest.
            if (PyType_IsSubtype(Py_TYPE(value), &qpycore_pyqtProperty_Type))
            {
                // It is a property.

                if (!ascii_key)
                    return -1;

                Py_INCREF(value);

                qpycore_pyqtProperty *pp = (qpycore_pyqtProperty *)value;

                pprops.insert(pp->pyqtprop_sequence, prop_data(key, value));

                // See if the property has a scope.  If so, collect all
                // QMetaObject pointers that are not in the super-class
                // hierarchy.
                const QMetaObject *mo = get_scope_qmetaobject(pp->pyqtprop_parsed_type);

                if (mo && !enum_scopes.contains(mo))
                    enum_scopes.append(mo);

                // See if the property has a notify signal so that we can
                // allocate space for it in the meta-object.  We will check if
                // it is valid later on.  If there is one property with a
                // notify signal then a signal index is stored for all
                // properties.
                if (pp->pyqtprop_notify)
                    has_notify_signal = true;
            }
            else if (PyType_IsSubtype(Py_TYPE(value), &qpycore_pyqtSignal_Type))
            {
                // It is a signal.

                if (!ascii_key)
                    return -1;

                qpycore_pyqtSignal *ps = (qpycore_pyqtSignal *)value;

                // Make sure the signal has a name.
                qpycore_set_signal_name(ps, pytype->tp_name, ascii_key);

                // Add all the overloads.
                for (int ol = 0; ol < ps->overloads->size(); ++ol)
                    psigs.append(ps->overloads->at(ol)->signature);

                Py_DECREF(key);
            }
            else if (ascii_key && qstrcmp(ascii_key, "__pyqtSignals__") == 0)
            {
                // It is a sequence of signal signatures.  This is deprecated
                // in favour of pyqtSignal().

                if (PySequence_Check(value))
                {
                    SIP_SSIZE_T seq_sz = PySequence_Size(value);

                    for (SIP_SSIZE_T i = 0; i < seq_sz; ++i)
                    {
                        PyObject *itm = PySequence_ITEM(value, i);

                        if (!itm)
                        {
                            Py_DECREF(key);
                            return -1;
                        }

                        PyObject *ascii_itm = itm;
                        const char *ascii = sipString_AsASCIIString(&ascii_itm);
                        Py_DECREF(itm);

                        if (!ascii)
                        {
                            Py_DECREF(key);
                            return -1;
                        }

                        QByteArray old_sig = QMetaObject::normalizedSignature(ascii);
                        old_sig.prepend('2');
                        psigs.append(old_sig);

                        Py_DECREF(ascii_itm);
                    }
                }

                Py_DECREF(key);
            }
        }
    }

    qo->nr_signals = psigs.count();

    // Create and fill the extradata array.
    if (enum_scopes.isEmpty())
    {
        qo->mo.d.extradata = 0;
    }
    else
    {
        const QMetaObject **objects = new const QMetaObject *[enum_scopes.size() + 1];

        for (int i = 0; i < enum_scopes.size(); ++i)
            objects[i] = enum_scopes.at(i);

        objects[enum_scopes.size()] = 0;

#if QT_VERSION >= 0x040600
        qo->ed.objects = objects;
        qo->ed.static_metacall = 0;

        qo->mo.d.extradata = &qo->ed;
#else
        qo->mo.d.extradata = objects;
#endif
    }

    // Initialise the header section of the data table.  Note that Qt v4.5
    // introduced revision 2 which added constructors.  However the design is
    // broken in that the static meta-call function doesn't provide enough
    // information to determine which Python sub-class of a Qt class is to be
    // created.  So we stick with revision 1 (and don't allow pyqtSlot() to
    // decorate __init__).

#if QT_VERSION >= 0x040600
    const int revision = 4;
    const int header_size = 14;
#else
    const int revision = 1;
    const int header_size = 10;
#endif

    int data_len = header_size + qo->nr_signals * 5 + qo->pslots.count() * 5 + 
            pprops.count() * (has_notify_signal ? 4 : 3) + 1;
    uint *data = new uint[data_len];
    int g_offset = header_size;
    int s_offset = g_offset + qo->nr_signals * 5;
    int p_offset = s_offset + qo->pslots.count() * 5;
    int n_offset = p_offset + pprops.count() * 3;
    int empty = 0;

    for (int i = 0; i < data_len; ++i)
        data[i] = 0;

    // The revision number.
    data[0] = revision;

    // Set up the methods count and offset.
    if (qo->nr_signals || qo->pslots.count())
    {
        data[4] = qo->nr_signals + qo->pslots.count();
        data[5] = g_offset;

        // We might need an empty string.
        empty = qo->str_data.size();
        qo->str_data.append('\0');
    }

    // Set up the properties count and offset.
    if (pprops.count())
    {
        data[6] = pprops.count();
        data[7] = p_offset;
    }

#if QT_VERSION >= 0x040600
    data[13] = qo->nr_signals;
#endif

    // Add the signals to the meta-object.
    for (int g = 0; g < qo->nr_signals; ++g)
    {
        const QByteArray &norm = psigs.at(g);

        // Add the (non-existent) argument names.
        data[g_offset + (g * 5) + 1] = add_arg_names(qo, norm, empty);

        // Add the full signature.
        data[g_offset + (g * 5) + 0] = qo->str_data.size();
        qo->str_data.append(norm.constData() + 1);
        qo->str_data.append('\0');

        // Add the type, tag and flags.
        data[g_offset + (g * 5) + 2] = empty;
        data[g_offset + (g * 5) + 3] = empty;
        data[g_offset + (g * 5) + 4] = 0x05;
    }

    // Add the slots to the meta-object.
    for (int s = 0; s < qo->pslots.count(); ++s)
    {
        const qpycore_slot &slot = qo->pslots.at(s);
        const QByteArray &sig = slot.signature->signature;

        // Add the (non-existent) argument names.
        data[s_offset + (s * 5) + 1] = add_arg_names(qo, sig, empty);

        // Add the full signature.
        data[s_offset + (s * 5) + 0] = qo->str_data.size();
        qo->str_data.append(sig);
        qo->str_data.append('\0');

        // Add any type.
        if (slot.signature->result)
        {
            data[s_offset + (s * 5) + 2] = qo->str_data.size();
            qo->str_data.append(slot.signature->result->name());
            qo->str_data.append('\0');
        }
        else
        {
            data[s_offset + (s * 5) + 2] = empty;
        }

        // Add the tag and flags.
        data[s_offset + (s * 5) + 3] = empty;
        data[s_offset + (s * 5) + 4] = 0x0a;
    }

    // Add the properties to the meta-object.
    QList<uint> notify_signals;
    QMapIterator<uint, prop_data> it(pprops);

    for (int p = 0; it.hasNext(); ++p)
    {
        it.next();

        const prop_data &pprop = it.value();
        const char *prop_name = SIPBytes_AS_STRING(pprop.first);
        qpycore_pyqtProperty *pp = (qpycore_pyqtProperty *)pprop.second;

        // Add the property name.
        data[p_offset + (p * 3) + 0] = qo->str_data.size();
        qo->str_data.append(prop_name);
        qo->str_data.append('\0');

        // Add the name of the property type.
        data[p_offset + (p * 3) + 1] = qo->str_data.size();
        qo->str_data.append(pp->pyqtprop_parsed_type->name());
        qo->str_data.append('\0');

        // There are only 8 bits available for the type so use the special
        // value if more are required.
        uint metatype = pp->pyqtprop_parsed_type->metatype();
        uint flags = 0;

        if (metatype > 0xff)
        {
#if QT_VERSION >= 0x040600
            metatype = 0;
            flags |= 0x00000008;
#else
            // This is the old PyQt behaviour.  It may not be correct, but
            // nobody has complained, and if it ain't broke...
            metatype = 0xff;
#endif
        }

        // Enum or flag.
        if (pp->pyqtprop_parsed_type->isEnum() || pp->pyqtprop_parsed_type->isFlag())
        {
#if QT_VERSION >= 0x040600
            metatype = 0;
#endif
            flags |= 0x00000008;
        }

        flags |= metatype << 24;

        if (pp->pyqtprop_get && PyCallable_Check(pp->pyqtprop_get))
            // Readable.
            flags |= 0x00000001;

        if (pp->pyqtprop_set && PyCallable_Check(pp->pyqtprop_set))
        {
            // Writable.
            flags |= 0x00000002;

            // See if the name of the setter follows the Designer convention.
            // If so tell the UI compilers not to use setProperty().
            PyObject *setter_name_obj = PyObject_GetAttr(pp->pyqtprop_set,
                    qpycore_name_attr_name);

            if (setter_name_obj)
            {
                PyObject *ascii_obj = setter_name_obj;
                const char *ascii = sipString_AsASCIIString(&ascii_obj);
                Py_DECREF(setter_name_obj);

                if (ascii)
                {
                    if (qstrlen(ascii) > 3 && ascii[0] == 's' &&
                            ascii[1] == 'e' && ascii[2] == 't' &&
                            ascii[3] == toupper(prop_name[0]) &&
                            qstrcmp(&ascii[4], &prop_name[1]) == 0)
                        flags |= 0x00000100;
                }

                Py_DECREF(ascii_obj);
            }

            PyErr_Clear();
        }

        if (pp->pyqtprop_reset && PyCallable_Check(pp->pyqtprop_reset))
            // Resetable.
            flags |= 0x00000004;

        if (pp->pyqtprop_notify)
        {
            qpycore_pyqtSignal *ps = (qpycore_pyqtSignal *)pp->pyqtprop_notify;
            const QByteArray &sig = ps->master->overloads->at(ps->master_index)->signature;
            int idx = psigs.indexOf(sig);

            if (idx < 0)
            {
                PyErr_Format(PyExc_TypeError,
                        "the notify signal '%s' was not defined in this class",
                        sig.constData() + 1);

                // Note that we leak the property name and definition.
                return -1;
            }

            notify_signals.append(idx);
            flags |= 0x00400000;
        }
        else
        {
            notify_signals.append(0);
        }

        // Add the property flags.
        flags |= pp->pyqtprop_flags;

        data[p_offset + (p * 3) + 2] = flags;

        // Save the property data for qt_metacall().  (We already have a
        // reference.)
        qo->pprops.append(pp);

        // We've finished with the property name.
        Py_DECREF(pprop.first);
    }

    // Add the indices of the notify signals.
    if (has_notify_signal)
    {
        QListIterator<uint> notify_it(notify_signals);

        while (notify_it.hasNext())
            data[n_offset++] = notify_it.next();
    }

    // Initialise the rest of the meta-object.
    qo->mo.d.stringdata = qo->str_data.constData();
    qo->mo.d.data = data;

    // Save the meta-object.
    pyqt_wt->metaobject = qo;

    return 0;
}


// Add the (non-existent) argument names for a signature and return their index
// in the meta-object string data.
static int add_arg_names(qpycore_metaobject *qo, const QByteArray &sig,
        int empty)
{
    int anames = -1;

    for (const char *com = sig.constData(); *com != '\0'; ++com)
        if (*com == ',')
        {
            if (anames < 0)
                anames = qo->str_data.size();

            qo->str_data.append(',');
        }

    if (anames < 0)
        anames = empty;
    else
        qo->str_data.append('\0');

    return anames;
}


// Return the QMetaObject for an enum type's scope.
static const QMetaObject *get_scope_qmetaobject(const Chimera *ct)
{
    // Check it is an enum.
    if (!ct->isEnum())
        return 0;

    // Check it has a scope.
    const sipTypeDef *td = sipTypeScope(ct->typeDef());

    if (!td)
        return 0;

    // Check the scope is wrapped by PyQt.
    if (!qpycore_is_pyqt4_class(td))
        return 0;

    return get_qmetaobject((pyqtWrapperType *)sipTypeAsPyTypeObject(td));
}


// Return the QMetaObject for a type.
static const QMetaObject *get_qmetaobject(pyqtWrapperType *pyqt_wt)
{
    // See if it's a sub-type of a wrapped type.
    if (pyqt_wt->metaobject)
        return &pyqt_wt->metaobject->mo;

    // It's a wrapped type.
    return reinterpret_cast<const QMetaObject *>(((pyqt4ClassTypeDef *)((sipWrapperType *)pyqt_wt)->type)->qt4_static_metaobject);
}


// The guard for Qt generated QObjects.
struct QObjectGuard
{
    QObjectGuard(void *addr) : guarded(reinterpret_cast<QObject *>(addr)), unguarded(addr) {}

    QPointer<QObject> guarded;
    void *unguarded;
};


// Reimplemented to wrap any QObjects created internally by Qt in a QPointer so
// that we can detect if they get destroyed.
static PyObject *pyqtWrapperType_call(PyObject *type, PyObject *args, PyObject *kwds)
{
    PyObject *self = sipWrapperType_Type->tp_call(type, args, kwds);

    // See if the object was created and it is a QObject sub-class.
    if (self && PyObject_TypeCheck(self, sipTypeAsPyTypeObject(sipType_QObject)))
    {
        sipSimpleWrapper *w = (sipSimpleWrapper *)self;

        // See if it is created internally by Qt and doesn't already have an
        // access function (e.g. qApp).
        if (!sipIsDerived(w) && !w->access_func)
        {
            QObjectGuard *guard = new QObjectGuard(w->data);

            w->data = guard;
            w->access_func = qpointer_access_func;
        }
    }

    return self;
}


// The access function for QPointers.
static void *qpointer_access_func(sipSimpleWrapper *w, AccessFuncOp op)
{
    QObjectGuard *guard = reinterpret_cast<QObjectGuard *>(w->data);
    void *addr;

    switch (op)
    {
    case UnguardedPointer:
        addr = guard->unguarded;
        break;

    case GuardedPointer:
        addr = (QObject *)guard->guarded;
        break;

    case ReleaseGuard:
        delete guard;
        addr = 0;
        break;
    }

    return addr;
}
