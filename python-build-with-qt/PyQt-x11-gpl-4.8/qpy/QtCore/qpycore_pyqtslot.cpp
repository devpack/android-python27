// This is the implementation of the pySlot (and deprecated pyqtSignature)
// decorator.
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
#include "qpycore_sip.h"


// Forward declarations.
static PyObject *decorate(Chimera::Signature *parsed_sig, PyObject *res_obj,
        const char *context);
extern "C" {static PyObject *decorator(PyObject *self, PyObject *f);}


// This implements the pyqtSlot decorator.
PyObject *qpycore_pyqtslot(PyObject *args, PyObject *kwds)
{
    const char *name_str = 0;
    PyObject *res_obj = 0;
    static const char *kwlist[] = {"name", "result", 0};

    static PyObject *no_args = 0;

    if (!no_args)
    {
        no_args = PyTuple_New(0);

        if (!no_args)
            return 0;
    }

    if (!PyArg_ParseTupleAndKeywords(no_args, kwds,
#if PY_VERSION_HEX >= 0x02050000
            "|sO:pyqtSlot",
#else
            const_cast<char *>("|sO:pyqtSlot"),
#endif
            const_cast<char **>(kwlist), &name_str, &res_obj))
        return 0;

    Chimera::Signature *parsed_sig = Chimera::parse(args, name_str,
            "a pyqtSlot type argument");

    if (!parsed_sig)
        return 0;

    return decorate(parsed_sig, res_obj, "a pyqtSlot result");
}


// This implements the pyqtSignature decorator.
PyObject *qpycore_pyqtsignature(PyObject *args, PyObject *kwds)
{
    const char *sig_str;
    PyObject *res_obj = 0;
    static const char *kwlist[] = {"signature", "result", 0};

    if (!PyArg_ParseTupleAndKeywords(args, kwds,
#if PY_VERSION_HEX >= 0x02050000
            "s|O:pyqtSignature",
#else
            const_cast<char *>("s|O:pyqtSignature"),
#endif
            const_cast<char **>(kwlist), &sig_str, &res_obj))
        return 0;

    // Parse the signature.
    QByteArray sig(sig_str);

    // Make sure the signature has parentheses before normalising it.
    if (!sig.contains('('))
    {
        sig.prepend('(');
        sig.append(')');
    }

    sig = QMetaObject::normalizedSignature(sig);

    Chimera::Signature *parsed_sig = Chimera::parse(sig,
            "a pyqtSlot signature argument");

    if (!parsed_sig)
        return 0;

    return decorate(parsed_sig, res_obj, "a pyqtSignature result");
}


// Decorate the method now the arguments have been parsed.
static PyObject *decorate(Chimera::Signature *parsed_sig, PyObject *res_obj,
        const char *context)
{
    // Parse any result type.
    if (res_obj)
    {
        parsed_sig->result = Chimera::parse(res_obj);

        if (!parsed_sig->result)
        {
            Chimera::raiseParseException(res_obj, context);
            delete parsed_sig;
            return 0;
        }
    }

    // Wrap the parsed signature in a Python object.
    PyObject *sig_obj = Chimera::Signature::toPyObject(parsed_sig);

    if (!sig_obj)
        return 0;

    // Create the decorator function itself.  We stash the arguments in "self".
    // This may be an abuse, but it seems to be Ok.
    static PyMethodDef deco_method = {
        SIP_MLNAME_CAST("_deco"), decorator, METH_O, 0
    };

    PyObject *obj = PyCFunction_New(&deco_method, sig_obj);
    Py_DECREF(sig_obj);

    return obj;
}


// This is the decorator function that saves the C++ signature as a function
// attribute.
static PyObject *decorator(PyObject *self, PyObject *f)
{
    Chimera::Signature *parsed_sig = Chimera::Signature::fromPyObject(self);
    const QByteArray &sig = parsed_sig->signature;

    // Use the function name if there isn't already one.
    if (sig.startsWith('('))
    {
        // Get the function's name.
        PyObject *nobj = PyObject_GetAttr(f, qpycore_name_attr_name);

        if (!nobj)
            return 0;

        PyObject *ascii_obj = nobj;
        const char *ascii = sipString_AsASCIIString(&ascii_obj);
        Py_DECREF(nobj);

        if (!ascii)
            return 0;

        parsed_sig->signature.prepend(ascii);
        parsed_sig->py_signature.prepend(ascii);
        Py_DECREF(ascii_obj);
    }

    // See if the function has already been decorated.
    PyObject *decorations = PyObject_GetAttr(f, qpycore_signature_attr_name);
    int rc;

    if (decorations)
    {
        // Insert the new decoration at the head of the existing ones so that
        // the list order matches the order they appear in the script.
        rc = PyList_Insert(decorations, 0, self);
    }
    else
    {
        PyErr_Clear();

        decorations = PyList_New(1);

        if (!decorations)
            return 0;

        Py_INCREF(self);
        PyList_SET_ITEM(decorations, 0, self);

        // Save the new decoration.
        rc = PyObject_SetAttr(f, qpycore_signature_attr_name, decorations);
    }

    Py_DECREF(decorations);

    if (rc < 0)
        return 0;

    // Return the function.
    Py_INCREF(f);
    return f;
}
