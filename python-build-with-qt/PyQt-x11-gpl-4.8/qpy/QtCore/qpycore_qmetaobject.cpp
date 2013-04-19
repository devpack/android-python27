// This is the support code for QMetaObject.
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

#include <QGenericArgument>
#include <QGenericReturnArgument>

#include "qpycore_chimera.h"
#include "qpycore_misc.h"
#include "qpycore_sip.h"


// Forward declarations.
static PyObject *ArgumentStorage_New(PyObject *type, PyObject *data);
#if defined(SIP_USE_PYCAPSULE)
//extern "C" {static void ArgumentStorage_delete(PyObject *cap);}
//#else
extern "C" {static void ArgumentStorage_delete(void *stv);}
#endif


// Register a number of named types and integer types for Q_FLAGS and Q_ENUMS.
// Note that this support is half-baked but provided for backwards
// compatibility until something better is done.
PyObject *qpycore_register_int_types(PyObject *type_names)
{
    for (SIP_SSIZE_T i = 0; i < PyTuple_GET_SIZE(type_names); ++i)
    {
        PyObject *name = PyTuple_GET_ITEM(type_names, i);
        const char *ascii = sipString_AsASCIIString(&name);

        if (!ascii)
            return 0;

        Chimera::registerIntType(ascii);

        Py_DECREF(name);
    }

    Py_INCREF(Py_None);
    return Py_None;
}


// Return a wrapped QGenericArgument for the given type and Python object.
PyObject *qpycore_ArgumentFactory(PyObject *type, PyObject *data)
{
    PyObject *as_obj = ArgumentStorage_New(type, data);

    if (!as_obj)
    {
        Chimera::raiseParseException(type, "a Q_ARG()");
        return 0;
    }

#if defined(SIP_USE_PYCAPSULE)
//    Chimera::Storage *st = reinterpret_cast<Chimera::Storage *>(
//            PyCapsule_GetPointer(as_obj, NULL));
//#else
    Chimera::Storage *st = reinterpret_cast<Chimera::Storage *>(
            PyCObject_AsVoidPtr(as_obj));
#endif

    QGenericArgument *arg = new QGenericArgument(
            st->type()->name().constData(), st->address());

    PyObject *ga_obj = sipConvertFromNewType(arg, sipType_QGenericArgument, 0);

    if (ga_obj)
    {
        // Stash the storage in the user field so that everything will be
        // properly garbage collected.
        ((sipSimpleWrapper *)ga_obj)->user = as_obj;
    }
    else
    {
        delete arg;
        Py_DECREF(as_obj);
    }

    return ga_obj;
}


// Return a wrapped QGenericReturnArgument for the given type.
PyObject *qpycore_ReturnFactory(PyObject *type)
{
    PyObject *as_obj = ArgumentStorage_New(type, 0);

    if (!as_obj)
    {
        Chimera::raiseParseException(type, "a Q_RETURN_ARG()");
        return 0;
    }

#if defined(SIP_USE_PYCAPSULE)
//    Chimera::Storage *st = reinterpret_cast<Chimera::Storage *>(
//            PyCapsule_GetPointer(as_obj, NULL));
//#else
    Chimera::Storage *st = reinterpret_cast<Chimera::Storage *>(
            PyCObject_AsVoidPtr(as_obj));
#endif

    QGenericReturnArgument *arg = new QGenericReturnArgument(
            st->type()->name().constData(), st->address());

    PyObject *gra_obj = sipConvertFromNewType(arg,
            sipType_QGenericReturnArgument, 0);

    if (gra_obj)
    {
        // Stash the storage in the user field so that everything will be
        // properly garbage collected.
        ((sipSimpleWrapper *)gra_obj)->user = as_obj;
    }
    else
    {
        delete arg;
        Py_DECREF(as_obj);
    }

    return gra_obj;
}


// Return the Python result from a QGenericReturnArgument.
PyObject *qpycore_ReturnValue(PyObject *gra_obj)
{
    PyObject *as_obj = ((sipSimpleWrapper *)gra_obj)->user;

#if defined(SIP_USE_PYCAPSULE)
//    Chimera::Storage *st = reinterpret_cast<Chimera::Storage *>(
//            PyCapsule_GetPointer(as_obj, NULL));
//#else
    Chimera::Storage *st = reinterpret_cast<Chimera::Storage *>(
            PyCObject_AsVoidPtr(as_obj));
#endif

    return st->toPyObject();
}


#if defined(SIP_USE_PYCAPSULE)
// The PyCapsule destructor for the ArgumentStorage type.
//static void ArgumentStorage_delete(PyObject *cap)
//{
//    Chimera::Storage *st = reinterpret_cast<Chimera::Storage *>(
//            PyCapsule_GetPointer(cap, NULL));
//    const Chimera *ct = st->type();

//    delete st;
//    delete ct;
//}
//#else
// The PyCObject destructor for the ArgumentStorage type.
static void ArgumentStorage_delete(void *stv)
{
    Chimera::Storage *st = reinterpret_cast<Chimera::Storage *>(stv);
    const Chimera *ct = st->type();

    delete st;
    delete ct;
}
#endif


// Returns a Python object wrapping an ArgumentStorage instance.
static PyObject *ArgumentStorage_New(PyObject *type, PyObject *data)
{
    const Chimera *ct = Chimera::parse(type);

    if (!ct)
        return 0;

    Chimera::Storage *st;

    if (data)
        st = ct->fromPyObjectToStorage(data);
    else
        st = ct->storageFactory();

    if (!st)
    {
        delete ct;
        return 0;
    }

    // Convert to a Python object.
#if defined(SIP_USE_PYCAPSULE)
//    PyObject *as_obj = PyCapsule_New(st, NULL, ArgumentStorage_delete);
//#else
    PyObject *as_obj = PyCObject_FromVoidPtr(st, ArgumentStorage_delete);
#endif

    if (!as_obj)
    {
        delete st;
        delete ct;
    }

    return as_obj;
}
