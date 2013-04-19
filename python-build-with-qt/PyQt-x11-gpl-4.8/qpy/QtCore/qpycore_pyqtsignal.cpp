// This contains the implementation of the pyqtSignal type.
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
#include "qpycore_pyqtsignal.h"


// Forward declarations.
extern "C" {
static PyObject *pyqtSignal_call(PyObject *self, PyObject *args, PyObject *kw);
static void pyqtSignal_dealloc(PyObject *self);
static PyObject *pyqtSignal_descr_get(PyObject *self, PyObject *obj,
        PyObject *type);
static int pyqtSignal_init(PyObject *self, PyObject *args, PyObject *kwd_args);
static PyObject *pyqtSignal_repr(PyObject *self);
static PyObject *pyqtSignal_mp_subscript(PyObject *self, PyObject *subscript);
static PyObject *pyqtSignal_get_doc(PyObject *self, void *);
}

static int add_overload(qpycore_pyqtSignal *ps, const char *name,
        PyObject *types);
static int add_overload(qpycore_pyqtSignal *ps, const char *sig,
        const char *docstring);
static bool is_signal_name(const char *sig, const char *name, uint name_len);


// Define the mapping methods.
static PyMappingMethods pyqtSignal_as_mapping = {
    0,                      /* mp_length */
    pyqtSignal_mp_subscript,    /* mp_subscript */
    0,                      /* mp_ass_subscript */
};


// The getters/setters.
static PyGetSetDef pyqtSignal_getsets[] = {
    {(char *)"__doc__", pyqtSignal_get_doc, NULL, NULL, NULL},
    {NULL, NULL, NULL, NULL, NULL}
};


PyDoc_STRVAR(pyqtSignal_doc,
"pyqtSignal(*types, name=str) -> signal\n"
"\n"
"types is normally a sequence of individual types.  Each type is either a\n"
"type object or a string that is the name of a C++ type.  Alternatively\n"
"each type could itself be a sequence of types each describing a different\n"
"overloaded signal.\n"
"name is the optional C++ name of the signal.  If it is not specified then\n"
"the name of the class attribute that is bound to the signal is used.");


// The pyqtSignal type object.
PyTypeObject qpycore_pyqtSignal_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    SIP_TPNAME_CAST("PyQt4.QtCore.pyqtSignal"), /* tp_name */
    sizeof (qpycore_pyqtSignal),    /* tp_basicsize */
    0,                      /* tp_itemsize */
    pyqtSignal_dealloc,     /* tp_dealloc */
    0,                      /* tp_print */
    0,                      /* tp_getattr */
    0,                      /* tp_setattr */
    0,                      /* tp_compare */
    pyqtSignal_repr,        /* tp_repr */
    0,                      /* tp_as_number */
    0,                      /* tp_as_sequence */
    &pyqtSignal_as_mapping, /* tp_as_mapping */
    0,                      /* tp_hash */
    pyqtSignal_call,        /* tp_call */
    0,                      /* tp_str */
    0,                      /* tp_getattro */
    0,                      /* tp_setattro */
    0,                      /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT,     /* tp_flags */
    pyqtSignal_doc,         /* tp_doc */
    0,                      /* tp_traverse */
    0,                      /* tp_clear */
    0,                      /* tp_richcompare */
    0,                      /* tp_weaklistoffset */
    0,                      /* tp_iter */
    0,                      /* tp_iternext */
    0,                      /* tp_methods */
    0,                      /* tp_members */
    pyqtSignal_getsets,     /* tp_getset */
    0,                      /* tp_base */
    0,                      /* tp_dict */
    pyqtSignal_descr_get,   /* tp_descr_get */
    0,                      /* tp_descr_set */
    0,                      /* tp_dictoffset */
    pyqtSignal_init,        /* tp_init */
    0,                      /* tp_alloc */
    PyType_GenericNew,      /* tp_new */
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


// Get the docstring for a signal.
PyObject *qpycore_get_signal_doc(PyObject *self)
{
    qpycore_pyqtSignal *ps = (qpycore_pyqtSignal *)self;

    QByteArray doc;

    // Get any docstrings from any non-signal overloads.
    if (ps->non_signals && ps->non_signals->ml_doc)
    {
        doc.append('\n');
        doc.append(ps->non_signals->ml_doc);
    }

    // Get any docstrings from the signals.
    for (int i = 0; i < ps->overloads->size(); ++i)
    {
        const char *docstring = ps->overloads->at(i)->docstring;

        if (docstring)
        {
            if (*docstring == '\1')
                ++docstring;

            doc.append('\n');
            doc.append(docstring);
            doc.append(" [signal]");
        }
    }

    if (doc.isEmpty())
    {
        Py_INCREF(Py_None);
        return Py_None;
    }

    return
#if PY_MAJOR_VERSION >= 3
        PyUnicode_FromString
#else
        PyString_FromString
#endif
            (doc.constData() + 1);
}


// The __doc__ getter.
static PyObject *pyqtSignal_get_doc(PyObject *self, void *)
{
    return qpycore_get_signal_doc(self);
}


// The type repr slot.
static PyObject *pyqtSignal_repr(PyObject *self)
{
    qpycore_pyqtSignal *ps = (qpycore_pyqtSignal *)self;

    QByteArray name = Chimera::Signature::name(
            ps->overloads->at(ps->master_index)->signature);

    return
#if PY_MAJOR_VERSION >= 3
        PyUnicode_FromFormat
#else
        PyString_FromFormat
#endif
            ("<unbound signal %s>", name.constData() + 1);
}


// The type call slot.
static PyObject *pyqtSignal_call(PyObject *self, PyObject *args, PyObject *kw)
{
    return qpycore_call_signal_overload(self, 0, args, kw);
}


// The type dealloc slot.
static void pyqtSignal_dealloc(PyObject *self)
{
    qpycore_pyqtSignal *ps = (qpycore_pyqtSignal *)self;

    if (ps->overloads)
    {
        // If we are the master then we own any signatures.
        if (ps->master == ps)
        {
            qDeleteAll(*ps->overloads);
            delete ps->overloads;
        }

        ps->overloads = 0;
    }

    Py_TYPE(self)->tp_free(self);
}


// The type descriptor get slot.
static PyObject *pyqtSignal_descr_get(PyObject *self, PyObject *obj,
        PyObject *)
{
    qpycore_pyqtSignal *ps = (qpycore_pyqtSignal *)self;

    // Return the unbound signal if there is nothing to bind it to.
    if (obj == NULL || obj == Py_None)
    {
        Py_INCREF(self);
        return self;
    }

    // Get the QObject.
    int is_err = 0;
    void *qobject = sipForceConvertToType(obj, sipType_QObject, 0,
            SIP_NO_CONVERTORS, 0, &is_err);

    if (is_err)
    {
        PyErr_Format(PyExc_TypeError,
                "pyqtSignal must be bound to a QObject, not '%s'",
                Py_TYPE(obj)->tp_name);
        return 0;
    }

    // Return the bound signal.
    return qpycore_pyqtBoundSignal_New(self, obj,
            reinterpret_cast<QObject *>(qobject), ps->master_index);
}


// The type init slot.
static int pyqtSignal_init(PyObject *self, PyObject *args, PyObject *kwd_args)
{
    qpycore_pyqtSignal *ps = (qpycore_pyqtSignal *)self;

    // We are the signal master.
    ps->master = ps;
    ps->overloads = new QList<Chimera::Signature *>;

    // Get the keyword arguments.
    PyObject *name_obj = 0;
    const char *name = 0;

    if (kwd_args)
    {
        SIP_SSIZE_T pos = 0;
        PyObject *key, *value;

        while (PyDict_Next(kwd_args, &pos, &key, &value))
        {
#if PY_MAJOR_VERSION >= 3
            if (PyUnicode_CompareWithASCIIString(key, "name") != 0)
            {
                PyErr_Format(PyExc_TypeError,
                        "pyqtSignal() got an unexpected keyword argument '%U'",
                        key);

                Py_XDECREF(name_obj);
                return -1;
            }
#else
            Q_ASSERT(PyString_Check(key));

            if (qstrcmp(PyString_AS_STRING(key), "name") != 0)
            {
                PyErr_Format(PyExc_TypeError,
                        "pyqtSignal() got an unexpected keyword argument '%s'",
                        PyString_AS_STRING(key));

                Py_XDECREF(name_obj);
                return -1;
            }
#endif

            name_obj = value;
            name = sipString_AsASCIIString(&name_obj);

            if (!name)
                return -1;
        }
    }

    // If there is at least one argument and it is a sequence then assume all
    // arguments are sequences.  Unfortunately a string is also a sequence so
    // check for tuples and lists explicitly.
    if (PyTuple_GET_SIZE(args) > 0 && (PyTuple_Check(PyTuple_GET_ITEM(args, 0)) || PyList_Check(PyTuple_GET_ITEM(args, 0))))
    {
        for (SIP_SSIZE_T i = 0; i < PyTuple_GET_SIZE(args); ++i)
        {
            PyObject *types = PySequence_Tuple(PyTuple_GET_ITEM(args, i));

            if (!types)
            {
                PyErr_SetString(PyExc_TypeError,
                        "pyqtSignal() argument expected to be sequence of types");

                if (name)
                {
                    Py_DECREF(name_obj);
                }

                return -1;
            }

            int rc = add_overload(ps, name, types);

            Py_DECREF(types);

            if (rc < 0)
            {
                if (name)
                {
                    Py_DECREF(name_obj);
                }

                return -1;
            }
        }
    }
    else if (add_overload(ps, name, args) < 0)
    {
        if (name)
        {
            Py_DECREF(name_obj);
        }

        return -1;
    }

    if (name)
    {
        Py_DECREF(name_obj);
    }

    return 0;
}


// The mapping subscript slot.
static PyObject *pyqtSignal_mp_subscript(PyObject *self, PyObject *subscript)
{
    qpycore_pyqtSignal *ps = (qpycore_pyqtSignal *)self;

    int idx = qpycore_signal_index(ps->master, subscript,
            "an unbound signal type argument");

    if (idx < 0)
        return 0;

    // Create a copy of the signal with only the overload requested.
    PyObject *copy = PyType_GenericNew(Py_TYPE(ps), 0, 0);

    if (copy)
    {
        qpycore_pyqtSignal *ps_copy = (qpycore_pyqtSignal *)copy;
        ps_copy->master = ps->master;
        ps_copy->master_index = idx;
        ps_copy->overloads = ps->overloads;
    }

    return copy;
}


// Find an overload that matches a subscript.
int qpycore_signal_index(qpycore_pyqtSignal *ps, PyObject *subscript, const char *context)
{
    // Make sure the subscript is a tuple.
    PyObject *args;

    if (PyTuple_Check(subscript))
    {
        args = subscript;
    }
    else
    {
        args = PyTuple_New(1);

        if (!args)
            return -1;

        PyTuple_SET_ITEM(args, 0, subscript);
    }

    Py_INCREF(subscript);

    // Parse the subscript as a tuple of types.
    Chimera::Signature *ss_signature = Chimera::parse(args, 0, context);

    Py_DECREF(args);

    if (!ss_signature)
        return -1;

    // Search for an overload with this signature.
    int idx = -1;

    for (int i = 0; i < ps->overloads->size(); ++i)
    {
        Chimera::Signature *oload = ps->overloads->at(i);

        if (oload->arguments() == ss_signature->signature)
        {
            idx = i;
            break;
        }
    }

    delete ss_signature;

    if (idx < 0)
    {
        PyErr_SetString(PyExc_KeyError,
                "there is no matching overloaded signal");

        return -1;
    }

    return idx;
}


// Add an overload when given a tuple of types.
static int add_overload(qpycore_pyqtSignal *ps, const char *name,
        PyObject *types)
{
    Chimera::Signature *parsed = Chimera::parse(types, name,
            "a pyqtSignal() type argument");

    if (!parsed)
        return -1;

    if (name)
        parsed->signature.prepend('2');

    ps->overloads->append(parsed);

    return 0;
}


// Give a signal a name if it hasn't already got one.
void qpycore_set_signal_name(qpycore_pyqtSignal *ps, const char *type_name, const char *name)
{
    QList<Chimera::Signature *> *overloads = ps->overloads;

    for (int i = 0; i < overloads->size(); ++i)
    {
        Chimera::Signature *overload = overloads->at(i);
        QByteArray &sig = overload->signature;
        QByteArray &py_sig = overload->py_signature;

        // If the signature already has a name then they all do and there is
        // nothing more to do.
        if (!sig.startsWith('('))
            return;

        sig.prepend(name);
        sig.prepend('2');

        py_sig.prepend(name);
        py_sig.prepend('.');
        py_sig.prepend(type_name);
    }
}


// Handle the getting of a lazy attribute, ie. a native Qt signal.
int qpycore_get_lazy_attr(const sipTypeDef *td, PyObject *dict)
{
    pyqt4ClassTypeDef *ctd = (pyqt4ClassTypeDef *)td;
    const pyqt4QtSignal *sigs = ctd->qt4_signals;

    // Handle the trvial case.
    if (!sigs)
        return 0;

    QByteArray curr_name;
    qpycore_pyqtSignal *curr = 0;

    do
    {
        // See if we have come to the end of the current signal.
        if (curr && !is_signal_name(sigs->signature, curr_name.constData(), curr_name.size()))
        {
            if (PyDict_SetItemString(dict, curr_name.constData(), (PyObject *)curr) < 0)
                return -1;

            curr = 0;
        }

        // See if we need to create a new signal.
        if (!curr)
        {
            // Get the name.
            curr_name = sigs->signature;
            curr_name.truncate(curr_name.indexOf('('));

            curr = (qpycore_pyqtSignal *)PyType_GenericAlloc(&qpycore_pyqtSignal_Type, 0);

            if (!curr)
                return -1;

            curr->master = curr;
            curr->non_signals = sigs->non_signals;
            curr->overloads = new QList<Chimera::Signature *>;
        }

        // Add the new overload.
        if (add_overload(curr, sigs->signature, sigs->docstring) < 0)
        {
            Py_DECREF((PyObject *)curr);
            return -1;
        }
    }
    while ((++sigs)->signature);

    // Save the last one.
    return PyDict_SetItemString(dict, curr_name.constData(), (PyObject *)curr);
}


// Add an overload when given a native Qt signature.
static int add_overload(qpycore_pyqtSignal *ps, const char *sig,
        const char *docstring)
{
    QByteArray norm = QMetaObject::normalizedSignature(sig);
    Chimera::Signature *parsed = Chimera::parse(norm, "a native Qt signal");

    // This should never fail.
    if (!parsed)
        return -1;

    parsed->signature.prepend('2');
    parsed->docstring = docstring;

    ps->overloads->append(parsed);

    return 0;
}


// Return true if the signal has the given name.
static bool is_signal_name(const char *sig, const char *name, uint name_len)
{
    return (qstrncmp(sig, name, name_len) == 0 && sig[name_len] == '(');
}


// Call a signal's overloaded method (if there is one).
PyObject *qpycore_call_signal_overload(PyObject *ps_obj, PyObject *bound,
        PyObject *args, PyObject *kw)
{
    qpycore_pyqtSignal *ps = (qpycore_pyqtSignal *)ps_obj;

    if (!ps->non_signals)
    {
        PyErr_SetString(PyExc_TypeError, "native Qt signal is not callable");
        return 0;
    }

    PyObject *func = PyCFunction_New(ps->non_signals, bound);

    if (!func)
        return 0;

    PyObject *result = PyCFunction_Call(func, args, kw);

    Py_DECREF(func);

    return result;
}
