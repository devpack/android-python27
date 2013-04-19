// This contains the implementation of the pyqtBoundSignal type.
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

#include <QtGlobal>
#include <QByteArray>
#include <QMetaObject>

#include "qpycore_chimera.h"
#include "qpycore_misc.h"
#include "qpycore_pyqtboundsignal.h"
#include "qpycore_pyqtproxy.h"
#include "qpycore_pyqtpyobject.h"
#include "qpycore_pyqtsignal.h"
#include "qpycore_sip.h"
#include "qpycore_sip_helpers.h"


// Forward declarations.
extern "C" {
static PyObject *pyqtBoundSignal_call(PyObject *self, PyObject *args,
        PyObject *kw);
static void pyqtBoundSignal_dealloc(PyObject *self);
static PyObject *pyqtBoundSignal_repr(PyObject *self);
static PyObject *pyqtBoundSignal_get_doc(PyObject *self, void *);
static PyObject *pyqtBoundSignal_connect(PyObject *self, PyObject *args,
        PyObject *kwd_args);
static PyObject *pyqtBoundSignal_disconnect(PyObject *self, PyObject *args);
static PyObject *pyqtBoundSignal_emit(PyObject *self, PyObject *args);
static PyObject *pyqtBoundSignal_mp_subscript(PyObject *self,
        PyObject *subscript);
}

static PyObject *connect(qpycore_pyqtBoundSignal *bs, QObject *qrx,
        const char *slot, Qt::ConnectionType type);
static PyObject *disconnect(qpycore_pyqtBoundSignal *bs, QObject *qrx,
        const char *slot);
static QObject *get_receiver(Chimera::Signature *overload, PyObject *slot_obj,
        QByteArray &name);
static QByteArray slot_signature_from_decorations(Chimera::Signature *signal,
        PyObject *decorations, int nr_args);
static QByteArray slot_signature_from_metaobject(Chimera::Signature *signal,
        const QMetaObject *slot_mo, const QByteArray &slot_name, int nr_args);
static QByteArray slot_signature(Chimera::Signature *signal,
        const QByteArray &slot_name, int nr_args);


// Doc-strings.
PyDoc_STRVAR(pyqtBoundSignal_connect_doc,
"connect(slot[, type=Qt.AutoConnection])\n"
"\n"
"slot is either a Python callable or another signal.\n"
"type is a Qt.ConnectionType");

PyDoc_STRVAR(pyqtBoundSignal_disconnect_doc,
"disconnect([slot])\n"
"\n"
"slot is an optional Python callable or another signal.  If it is omitted\n"
"then the signal is disconnected from everything it is connected to.");

PyDoc_STRVAR(pyqtBoundSignal_emit_doc,
"emit(*args)\n"
"\n"
"*args are the values that will be passed as arguments to all connected\n"
"slots.");


// Define the methods.
static PyMethodDef pyqtBoundSignal_methods[] = {
    {SIP_MLNAME_CAST("connect"), (PyCFunction)pyqtBoundSignal_connect,
            METH_VARARGS|METH_KEYWORDS,
            SIP_MLDOC_CAST(pyqtBoundSignal_connect_doc)},
    {SIP_MLNAME_CAST("disconnect"), pyqtBoundSignal_disconnect,
            METH_VARARGS, SIP_MLDOC_CAST(pyqtBoundSignal_disconnect_doc)},
    {SIP_MLNAME_CAST("emit"), pyqtBoundSignal_emit,
            METH_VARARGS, SIP_MLDOC_CAST(pyqtBoundSignal_emit_doc)},
    {0, 0, 0, 0}
};


// Define the mapping methods.
static PyMappingMethods pyqtBoundSignal_as_mapping = {
    0,                      /* mp_length */
    pyqtBoundSignal_mp_subscript,   /* mp_subscript */
    0,                      /* mp_ass_subscript */
};


// The getters/setters.
static PyGetSetDef pyqtBoundSignal_getsets[] = {
    {(char *)"__doc__", pyqtBoundSignal_get_doc, NULL, NULL, NULL},
    {NULL, NULL, NULL, NULL, NULL}
};


// The pyqtBoundSignal type object.
PyTypeObject qpycore_pyqtBoundSignal_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    SIP_TPNAME_CAST("PyQt4.QtCore.pyqtBoundSignal"),    /* tp_name */
    sizeof (qpycore_pyqtBoundSignal),   /* tp_basicsize */
    0,                      /* tp_itemsize */
    pyqtBoundSignal_dealloc,    /* tp_dealloc */
    0,                      /* tp_print */
    0,                      /* tp_getattr */
    0,                      /* tp_setattr */
    0,                      /* tp_compare */
    pyqtBoundSignal_repr,   /* tp_repr */
    0,                      /* tp_as_number */
    0,                      /* tp_as_sequence */
    &pyqtBoundSignal_as_mapping,    /* tp_as_mapping */
    0,                      /* tp_hash */
    pyqtBoundSignal_call,   /* tp_call */
    0,                      /* tp_str */
    0,                      /* tp_getattro */
    0,                      /* tp_setattro */
    0,                      /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT,     /* tp_flags */
    0,                      /* tp_doc */
    0,                      /* tp_traverse */
    0,                      /* tp_clear */
    0,                      /* tp_richcompare */
    0,                      /* tp_weaklistoffset */
    0,                      /* tp_iter */
    0,                      /* tp_iternext */
    pyqtBoundSignal_methods,    /* tp_methods */
    0,                      /* tp_members */
    pyqtBoundSignal_getsets,    /* tp_getset */
    0,                      /* tp_base */
    0,                      /* tp_dict */
    0,                      /* tp_descr_get */
    0,                      /* tp_descr_set */
    0,                      /* tp_dictoffset */
    0,                      /* tp_init */
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


// The __doc__ getter.
static PyObject *pyqtBoundSignal_get_doc(PyObject *self, void *)
{
    qpycore_pyqtBoundSignal *bs = (qpycore_pyqtBoundSignal *)self;

    return qpycore_get_signal_doc(bs->unbound_signal);
}


// The type repr slot.
static PyObject *pyqtBoundSignal_repr(PyObject *self)
{
    qpycore_pyqtBoundSignal *bs = (qpycore_pyqtBoundSignal *)self;

    QByteArray name = Chimera::Signature::name(bs->bound_overload->signature);

    return
#if PY_MAJOR_VERSION >= 3
        PyUnicode_FromFormat
#else
        PyString_FromFormat
#endif
            ("<bound signal %s of %s object at %p>", name.constData() + 1,
                    bs->bound_pyobject->ob_type->tp_name, bs->bound_pyobject);
}


// The type call slot.
static PyObject *pyqtBoundSignal_call(PyObject *self, PyObject *args,
        PyObject *kw)
{
    qpycore_pyqtBoundSignal *bs = (qpycore_pyqtBoundSignal *)self;

    return qpycore_call_signal_overload(bs->unbound_signal, bs->bound_pyobject,
            args, kw);
}


// The type dealloc slot.
static void pyqtBoundSignal_dealloc(PyObject *self)
{
    qpycore_pyqtBoundSignal *bs = (qpycore_pyqtBoundSignal *)self;

    Py_XDECREF(bs->unbound_signal);

    Py_TYPE(self)->tp_free(self);
}


// Create a bound signal.
PyObject *qpycore_pyqtBoundSignal_New(PyObject *unbound_signal,
        PyObject *bound_pyobject, QObject *bound_qobject, int signal_index)
{
    qpycore_pyqtBoundSignal *bs = (qpycore_pyqtBoundSignal *)PyType_GenericAlloc(&qpycore_pyqtBoundSignal_Type, 0);

    if (bs)
    {
        Py_INCREF(unbound_signal);
        bs->unbound_signal = unbound_signal;

        bs->bound_pyobject = bound_pyobject;
        bs->bound_qobject = bound_qobject;
        bs->bound_overload = ((qpycore_pyqtSignal *)unbound_signal)->overloads->at(signal_index);
    }

    return (PyObject *)bs;
}


// The mapping subscript slot.
static PyObject *pyqtBoundSignal_mp_subscript(PyObject *self,
        PyObject *subscript)
{
    qpycore_pyqtBoundSignal *bs = (qpycore_pyqtBoundSignal *)self;

    int idx = qpycore_signal_index((qpycore_pyqtSignal *)bs->unbound_signal,
            subscript, "a bound signal type argument");

    if (idx < 0)
        return 0;

    // Create a new bound signal.
    return qpycore_pyqtBoundSignal_New(bs->unbound_signal, bs->bound_pyobject,
            bs->bound_qobject, idx);
}


// Connect a signal.
static PyObject *pyqtBoundSignal_connect(PyObject *self, PyObject *args,
        PyObject *kwd_args)
{
    qpycore_pyqtBoundSignal *bs = (qpycore_pyqtBoundSignal *)self;

    static const char *kwds[] = {
        "slot",
        "type",
        0
    };

    PyObject *slot_obj, *type_obj = 0;

    if (!PyArg_ParseTupleAndKeywords(args, kwd_args,
#if PY_VERSION_HEX >= 0x02050000
                "O|O:connect",
#else
                const_cast<char *>("O|O:connect"),
#endif
                const_cast<char **>(kwds), &slot_obj, &type_obj))
        return 0;

    Qt::ConnectionType type = Qt::AutoConnection;

    if (type_obj)
    {
        if (!sipCanConvertToEnum(type_obj, sipType_Qt_ConnectionType))
        {
            PyErr_Format(PyExc_TypeError,
                    "connect() type argument should be Qt.ConnectionType, not '%s'",
                    Py_TYPE(slot_obj)->tp_name);

            return 0;
        }

        type = (Qt::ConnectionType)SIPLong_AsLong(type_obj);
    }

    // See if the slot is a signal.
    if (Py_TYPE(slot_obj) == &qpycore_pyqtBoundSignal_Type)
    {
        qpycore_pyqtBoundSignal *slot_bs = (qpycore_pyqtBoundSignal *)slot_obj;

        // Check we are not connecting to ourself.  We do this because Qt
        // doesn't do a similar check and will recurse its way to a crash.
        if (slot_bs->unbound_signal == bs->unbound_signal && slot_bs->bound_qobject == bs->bound_qobject)
        {
            PyErr_SetString(PyExc_ValueError,
                    "cannot connect a signal to itself");
            return 0;
        }

        return connect(bs, slot_bs->bound_qobject,
                slot_bs->bound_overload->signature.constData(), type);
    }

    // Make sure the slot is callable.
    if (!PyCallable_Check(slot_obj))
    {
        PyErr_Format(PyExc_TypeError,
                "connect() slot argument should be a callable or a signal, not '%s'",
                Py_TYPE(slot_obj)->tp_name);

        return 0;
    }

    // See if the slot can be used directly (ie. it wraps a Qt slot) or if it
    // needs a proxy.
    QByteArray rx_name;
    QObject *rx_qobj = get_receiver(bs->bound_overload, slot_obj, rx_name);

    if (PyErr_Occurred())
        return 0;

    if (!rx_name.isEmpty())
        return connect(bs, rx_qobj, rx_name.constData(), type);

    // Create a proxy for the slot.
    PyQtProxy *proxy;
    const char *member;

    Py_BEGIN_ALLOW_THREADS

    proxy = new PyQtProxy(bs, slot_obj, &member);

    if (proxy->real_slot.signature)
    {
        if (rx_qobj)
            proxy->moveToThread(rx_qobj->thread());
    }
    else
    {
        delete proxy;
        proxy = 0;
    }

    Py_END_ALLOW_THREADS

    if (!proxy)
        return 0;

    return connect(bs, proxy, member, type);
}


// Connect a signal to a slot and handle any errors.
static PyObject *connect(qpycore_pyqtBoundSignal *bs, QObject *qrx,
        const char *slot, Qt::ConnectionType type)
{
    bool ok;

    Py_BEGIN_ALLOW_THREADS
    ok = QObject::connect(bs->bound_qobject,
            bs->bound_overload->signature.constData(), qrx, slot, type);
    Py_END_ALLOW_THREADS

    if (!ok)
    {
        QByteArray rx_name = Chimera::Signature::name(slot);

        PyErr_Format(PyExc_TypeError, "connect() failed between %s and %s()",
                bs->bound_overload->py_signature.constData(),
                rx_name.constData() + 1);

        return 0;
    }

    Py_INCREF(Py_None);
    return Py_None;
}


// Disconnect a signal.
static PyObject *pyqtBoundSignal_disconnect(PyObject *self, PyObject *args)
{
    qpycore_pyqtBoundSignal *bs = (qpycore_pyqtBoundSignal *)self;

    PyObject *slot_obj = 0, *res_obj;

#if PY_VERSION_HEX >= 0x02050000
    if (!PyArg_ParseTuple(args, "|O:disconnect", &slot_obj))
#else
    if (!PyArg_ParseTuple(args, const_cast<char *>("|O:disconnect"), &slot_obj))
#endif
        return 0;

    // See if we are disconnecting everything from the overload.
    if (!slot_obj)
    {
        res_obj = disconnect(bs, 0, 0);

        PyQtProxy::deleteSlotProxies(bs->bound_qobject,
                bs->bound_overload->signature.constData());

        return res_obj;
    }

    // See if the slot is a signal.
    if (Py_TYPE(slot_obj) == &qpycore_pyqtBoundSignal_Type)
    {
        qpycore_pyqtBoundSignal *slot_bs = (qpycore_pyqtBoundSignal *)slot_obj;

        return disconnect(bs, slot_bs->bound_qobject,
                slot_bs->bound_overload->signature.constData());
    }

    if (!PyCallable_Check(slot_obj))
    {
        PyErr_Format(PyExc_TypeError,
                "disconnect() argument should be callable, not '%s'",
                Py_TYPE(slot_obj)->tp_name);

        return 0;
    }

    // See if the slot has been used directly (ie. it wraps a Qt slot) or if it
    // has a proxy.
    QByteArray rx_name;
    QObject *rx_qobj = get_receiver(bs->bound_overload, slot_obj, rx_name);

    if (PyErr_Occurred())
        return 0;

    if (!rx_name.isEmpty())
        return disconnect(bs, rx_qobj, rx_name.constData());

    const char *member;
    PyQtProxy *proxy = PyQtProxy::findSlotProxy(bs->bound_qobject,
            bs->bound_overload->signature.constData(), slot_obj, 0, &member);

    if (!proxy)
    {
        PyErr_Format(PyExc_TypeError, "'%s' object is not connected",
                Py_TYPE(slot_obj)->tp_name);

        return 0;
    }

    res_obj = disconnect(bs, proxy, member);

    proxy->disable();

    return res_obj;
}


// Disonnect a signal from a slot and handle any errors.
static PyObject *disconnect(qpycore_pyqtBoundSignal *bs, QObject *qrx,
        const char *slot)
{
    bool ok;

    Py_BEGIN_ALLOW_THREADS
    ok = QObject::disconnect(bs->bound_qobject,
            bs->bound_overload->signature.constData(), qrx, slot);
    Py_END_ALLOW_THREADS

    if (!ok)
    {
        QByteArray tx_name = bs->bound_overload->name();

        if (slot)
        {
            QByteArray rx_name = Chimera::Signature::name(slot);

            PyErr_Format(PyExc_TypeError,
                    "disconnect() failed between '%s' and '%s'",
                    tx_name.constData() + 1, rx_name.constData() + 1);
        }
        else
        {
            PyErr_Format(PyExc_TypeError,
                    "disconnect() failed between '%s' and all its connections",
                    tx_name.constData() + 1);
        }

        return 0;
    }

    Py_INCREF(Py_None);
    return Py_None;
}


// Emit a signal.
static PyObject *pyqtBoundSignal_emit(PyObject *self, PyObject *args)
{
    qpycore_pyqtBoundSignal *bs = (qpycore_pyqtBoundSignal *)self;

    if (!bs->bound_qobject->signalsBlocked())
    {
        int signal_index = bs->bound_qobject->metaObject()->indexOfSignal(bs->bound_overload->signature.constData() + 1);

        Q_ASSERT(signal_index >= 0);

        if (!qpycore_emit(bs->bound_qobject, signal_index, bs->bound_overload, args))
            return 0;
    }

    Py_INCREF(Py_None);
    return Py_None;
}


// Get the receiver QObject from the slot (if there is one) and its signature
// (if it wraps a Qt slot).  A Python exception will be raised if there was an
// error.
static QObject *get_receiver(Chimera::Signature *overload, PyObject *slot_obj,
        QByteArray &name)
{
    PyObject *rx_self, *decorations;
    QByteArray rx_name;
    bool try_qt_slot;

    decorations = 0;

    if (PyMethod_Check(slot_obj))
    {
        rx_self = PyMethod_GET_SELF(slot_obj);

        PyObject *f = PyMethod_GET_FUNCTION(slot_obj);
        Q_ASSERT(PyFunction_Check(f));

        PyObject *f_name_obj = ((PyFunctionObject *)f)->func_name;
        const char *f_name = sipString_AsASCIIString(&f_name_obj);
        Q_ASSERT(f_name);

        rx_name = f_name;
        Py_DECREF(f_name_obj);

        // See if this has been decorated.
        decorations = PyObject_GetAttr(f, qpycore_signature_attr_name);

        if (decorations)
        {
            try_qt_slot = true;

            // It's convenient to do this here as it's not going to disappear.
            Py_DECREF(decorations);
        }
        else
        {
            try_qt_slot = false;
        }
    }
    else if (PyCFunction_Check(slot_obj))
    {
        rx_self = PyCFunction_GET_SELF(slot_obj);
        rx_name = ((PyCFunctionObject *)slot_obj)->m_ml->ml_name;

        // We actually want the C++ name which may (in theory) be completely
        // different.  However this will cope with the exec_ case which is
        // probably good enough.
        if (rx_name.endsWith('_'))
            rx_name.chop(1);

        try_qt_slot = true;
    }
    else
    {
        rx_self = 0;
    }
 
    if (!rx_self)
        return 0;

    int iserr = 0;
    void *rx = sipForceConvertToType(rx_self, sipType_QObject, 0,
            SIP_NO_CONVERTORS, 0, &iserr);

    PyErr_Clear();

    if (iserr)
        return 0;

    QObject *rx_qobj = reinterpret_cast<QObject *>(rx);

    // If there might be a Qt slot that can handle the arguments (or a subset
    // of them) then use it.  Otherwise we will fallback to using a proxy.
    if (try_qt_slot)
    {
        for (int ol = overload->parsed_arguments.count(); ol >= 0; --ol)
        {
            // If there are decorations then we compare the signal's signature
            // against them so that we distinguish between Python types that
            // are passed to Qt as PyQt_PyObject objects.  Qt will not make the
            // distinction.  If there are no decorations then let Qt determine
            // if a slot is available.
            if (decorations)
                name = slot_signature_from_decorations(overload, decorations,
                        ol);
            else
                name = slot_signature_from_metaobject(overload,
                        rx_qobj->metaObject(), rx_name, ol);

            if (!name.isEmpty())
            {
                // Prepend the magic slot marker.
                name.prepend('1');
                break;
            }
        }
    }

    return rx_qobj;
}


// Return the full name and signature of a Qt slot that a signal can be
// connected to, taking the slot decorators into account.
static QByteArray slot_signature_from_decorations(Chimera::Signature *signal,
        PyObject *decorations, int nr_args)
{
    for (SIP_SSIZE_T i = 0; i < PyList_GET_SIZE(decorations); ++i)
    {
        Chimera::Signature *slot = Chimera::Signature::fromPyObject(
                PyList_GET_ITEM(decorations, i));

        if (slot->parsed_arguments.count() != nr_args)
            continue;

        int a;

        for (a = 0; a < nr_args; ++a)
        {
            const Chimera *sig_arg = signal->parsed_arguments.at(a);
            const Chimera *slot_arg = slot->parsed_arguments.at(a);

            // The same type names must be compatible.
            if (sig_arg->name() == slot_arg->name())
                continue;

            enum Match {
                // The type is PyQt_PyObject because it was explicitly
                // specified as such as a string.
                MatchesAll,

                // The type is PyQt_PyObject because it was specified as a type
                // object that needed wrapping.
                MatchesPyType,

                // The type is something other than PyQt_PyObject.
                MatchesName
            };

            Match sig_match, slot_match;

            if (sig_arg->name() != "PyQt_PyObject")
                sig_match = MatchesName;
            else
                sig_match = sig_arg->py_type() ? MatchesPyType : MatchesAll;

            if (slot_arg->name() != "PyQt_PyObject")
                slot_match = MatchesName;
            else
                slot_match = slot_arg->py_type() ? MatchesPyType : MatchesAll;

            // They are incompatible unless one is called PyQt_PyObject.
            if (sig_match == MatchesName || slot_match == MatchesName)
                break;

            // They are compatible if neither was a Python type.
            if (sig_match == MatchesAll || slot_match == MatchesAll)
                continue;

            // The signal type can be a sub-type of the slot type.
            if (!PyType_IsSubtype((PyTypeObject *)sig_arg->py_type(), (PyTypeObject *)slot_arg->py_type()))
                break;
        }

        if (a == nr_args)
            return slot_signature(signal, slot->name(), nr_args);
    }

    return QByteArray();
}


// Return the full name and signature of a Qt slot that a signal can be
// connected to, taking the Qt meta-object into account.
static QByteArray slot_signature_from_metaobject(Chimera::Signature *signal,
        const QMetaObject *slot_mo, const QByteArray &slot_name, int nr_args)
{
    QByteArray slot_sig = slot_signature(signal, slot_name, nr_args);

    if (slot_mo->indexOfSlot(slot_sig.constData()) < 0)
        slot_sig.clear();

    return slot_sig;
}


// Return the full name and signature of the Qt slot that a signal would be
// connected to.
static QByteArray slot_signature(Chimera::Signature *signal,
        const QByteArray &slot_name, int nr_args)
{
    QByteArray slot_sig = slot_name;

    slot_sig.append('(');

    for (int a = 0; a < nr_args; ++a)
    {
        if (a != 0)
            slot_sig.append(',');

        slot_sig.append(signal->parsed_arguments.at(a)->name());
    }

    slot_sig.append(')');

    return slot_sig;
}


// Check that an object is a bound signal and return the bound QObject and the
// signal signature.
bool qpycore_pyqtsignal_get_parts(PyObject *sig_obj, QObject **qtx,
        const char **sig)
{
    qpycore_pyqtBoundSignal *bs;

    if (!PyObject_TypeCheck(sig_obj, &qpycore_pyqtBoundSignal_Type))
        return false;

    bs = (qpycore_pyqtBoundSignal *)sig_obj;

    *qtx = bs->bound_qobject;
    *sig = bs->bound_overload->signature.constData();

    return true;
}
