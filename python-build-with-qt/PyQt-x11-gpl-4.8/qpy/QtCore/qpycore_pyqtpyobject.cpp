// This contains the support for Python objects and Qt's metatype system.
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

#include "qpycore_pyqtpyobject.h"
#include "qpycore_sip.h"


// The Qt metatype id.
int PyQt_PyObject::metatype;


// Wrap a Python object.
PyQt_PyObject::PyQt_PyObject(PyObject *py)
{
    pyobject = py;

    SIP_BLOCK_THREADS
    Py_XINCREF(pyobject);
    SIP_UNBLOCK_THREADS
}


// Create a new wrapper, with no Python object.  This is called by Qt's
// metatype system.
PyQt_PyObject::PyQt_PyObject()
{
    pyobject = 0;
}


// Create a copy of an existing wrapper.  This is called by Qt's metatype
// system.
PyQt_PyObject::PyQt_PyObject(const PyQt_PyObject &other)
{
    pyobject = other.pyobject;

    SIP_BLOCK_THREADS
    Py_XINCREF(pyobject);
    SIP_UNBLOCK_THREADS
}


// Destroy a wrapper.
PyQt_PyObject::~PyQt_PyObject()
{
    // Qt can still be tidying up after Python has gone so make sure that it
    // hasn't.
    if (Py_IsInitialized())
    {
        SIP_BLOCK_THREADS
        Py_XDECREF(pyobject);
        SIP_UNBLOCK_THREADS
    }

    pyobject = 0;
}


// Assignment operator.
PyQt_PyObject &PyQt_PyObject::operator=(const PyQt_PyObject &other)
{
    pyobject = other.pyobject;

    SIP_BLOCK_THREADS
    Py_XINCREF(pyobject);
    SIP_UNBLOCK_THREADS

    return *this;
}


// Serialise operator.
QDataStream &operator<<(QDataStream &out, const PyQt_PyObject &obj)
{
    PyObject *ser_obj = 0;
    const char *ser = 0;
    uint len = 0;

    if (obj.pyobject)
    {
        static PyObject *dumps = 0;

        SIP_BLOCK_THREADS

        if (!dumps)
        {
            PyObject *pickle = PyImport_ImportModule("pickle");

            if (pickle)
            {
                dumps = PyObject_GetAttrString(pickle, "dumps");
                Py_DECREF(pickle);
            }
        }

        if (dumps)
        {
            ser_obj = PyObject_CallFunctionObjArgs(dumps, obj.pyobject, 0);

            if (ser_obj)
            {
                if (SIPBytes_Check(ser_obj))
                {
                    ser = SIPBytes_AS_STRING(ser_obj);
                    len = SIPBytes_GET_SIZE(ser_obj);
                }
                else
                {
                    Py_DECREF(ser_obj);
                    ser_obj = 0;
                }
            }
        }

        SIP_UNBLOCK_THREADS
    }

    out.writeBytes(ser, len);

    if (ser_obj)
    {
        SIP_BLOCK_THREADS
        Py_DECREF(ser_obj);
        SIP_UNBLOCK_THREADS
    }

    return out;
}


// De-serialise operator.
QDataStream &operator>>(QDataStream &in, PyQt_PyObject &obj)
{
    char *ser;
    uint len;

    in.readBytes(ser, len);

    if (len)
    {
        static PyObject *loads = 0;

        SIP_BLOCK_THREADS

        if (!loads)
        {
            PyObject *pickle = PyImport_ImportModule("pickle");

            if (pickle)
            {
                loads = PyObject_GetAttrString(pickle, "loads");
                Py_DECREF(pickle);
            }
        }

        if (loads)
        {
            PyObject *ser_obj = SIPBytes_FromStringAndSize(ser, len);

            if (ser_obj)
            {
                obj.pyobject = PyObject_CallFunctionObjArgs(loads, ser_obj, 0);
                Py_DECREF(ser_obj);
            }
        }

        SIP_UNBLOCK_THREADS
    }

    delete[] ser;

    return in;
}
