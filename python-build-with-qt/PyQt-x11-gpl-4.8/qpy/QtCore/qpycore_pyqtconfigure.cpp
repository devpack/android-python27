// This implements the helper for QObject.pyqtConfigure().
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
#include <QMetaObject>
#include <QObject>
#include <QVariant>

#include "qpycore_chimera.h"
#include "qpycore_pyqtboundsignal.h"


// This is the helper for QObject.pyqtConfigure().
int qpycore_pyqtconfigure(PyObject *self, QObject *qobj, PyObject *kwds)
{
    PyObject *name_obj, *value_obj;
    SIP_SSIZE_T pos = 0;
    const QMetaObject *mo = qobj->metaObject();
    int rc = 0;

    while (PyDict_Next(kwds, &pos, &name_obj, &value_obj))
    {
        // Get the name encoded name.
        PyObject *enc_name_obj = name_obj;
        const char *name = sipString_AsASCIIString(&enc_name_obj);

        if (!name)
            return -1;

        QByteArray enc_name(name);
        Py_DECREF(enc_name_obj);

        // See if it is a property.
        int idx = mo->indexOfProperty(enc_name.constData());

        if (idx >= 0)
        {
            const Chimera *ct = Chimera::parse(mo->property(idx));

            if (!ct)
            {
                PyErr_Format(PyExc_TypeError,
                        "'%s' keyword argument has an invalid type",
                        enc_name.constData());

                return -1;
            }

            QVariant value;
            bool valid = ct->fromPyObject(value_obj, &value);

            delete ct;

            if (!valid)
                return -1;

            qobj->setProperty(enc_name.constData(), value);
        }
        else
        {
            bool unknown = true;

            // See if it is a signal.
            PyObject *sig = PyObject_GetAttr(self, name_obj);

            if (sig)
            {
                if (PyObject_IsInstance(sig, (PyObject *)&qpycore_pyqtBoundSignal_Type))
                {
                    static PyObject *connect_obj = NULL;

                    if (!connect_obj)
                    {
#if PY_MAJOR_VERSION >= 3
                        connect_obj = PyUnicode_FromString("connect");
#else
                        connect_obj = PyString_FromString("connect");
#endif

                        if (!connect_obj)
                        {
                            Py_DECREF(sig);
                            return -1;
                        }
                    }

                    // Connect the slot.
                    PyObject *res = PyObject_CallMethodObjArgs(sig,
                            connect_obj, value_obj, 0);

                    if (!res)
                    {
                        Py_DECREF(sig);
                        return -1;
                    }

                    Py_DECREF(res);

                    unknown = false;
                }

                Py_DECREF(sig);
            }

            if (unknown)
            {
                PyErr_Format(PyExc_AttributeError,
                        "'%s' is not a Qt property or a signal",
                        enc_name.constData());

                // Remember there is an exception but carry on with the
                // remaining names.  This supports the use case where a name
                // might not be valid in a particular context, but isn't a
                // problem.
                rc = -1;
            }
        }
    }

    return rc;
}
