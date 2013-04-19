// This contains definitions related to the support for Python objects and Qt's
// meta-type system.
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


#ifndef _QPYCORE_PYQTPYOBJECT_H
#define _QPYCORE_PYQTPYOBJECT_H


#include <Python.h>

#include <QMetaType>
#include <QDataStream>


// This class is used to wrap a PyObject so it can be passed around Qt's
// meta-type system while maintaining its reference count.
class PyQt_PyObject
{
public:
    PyQt_PyObject(PyObject *py);
    PyQt_PyObject();
    PyQt_PyObject(const PyQt_PyObject &other);
    ~PyQt_PyObject();

    PyQt_PyObject &operator=(const PyQt_PyObject &other);

    // The Python object being wrapped.
    PyObject *pyobject;
    
    // The Qt meta-type id.
    static int metatype;
};

QDataStream &operator<<(QDataStream &out, const PyQt_PyObject &obj);
QDataStream &operator>>(QDataStream &in, PyQt_PyObject &obj);

Q_DECLARE_METATYPE(PyQt_PyObject)


#endif
