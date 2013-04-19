// This is the implementation of the Chimera::Storage class.
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

#include <QVariant>

#include "qpycore_chimera.h"
#include "qpycore_pyqtpyobject.h"
#include "qpycore_sip.h"


// Create a new storage instance containing a converted Python object.
Chimera::Storage::Storage(const Chimera *ct, PyObject *py)
    : _parsed_type(ct), _ptr_storage(0), _tmp_state(0)
{
    // We convert to a QVariant even for pointer types because this has the
    // side-effect of ensuring the object doesn't get garbage collected.
    _valid = _parsed_type->fromPyObject(py, &_value_storage);

    if (isPointerType())
    {
        int is_err = 0;

        _ptr_storage = sipForceConvertToType(py, _parsed_type->typeDef(), 0, 0,
                &_tmp_state, &is_err);

        if (is_err)
        {
            _value_storage = QVariant();
            _valid = false;
        }
    }
}


// Create a new storage instance.
Chimera::Storage::Storage(const Chimera *ct)
    : _parsed_type(ct), _ptr_storage(0), _tmp_state(0), _valid(true)
{
    if (!isPointerType())
    {
        // Create a default fundamental or value type.
        _value_storage = QVariant(_parsed_type->metatype(), (const void *)0);
    }
}


// Destroy the storage and any temporary value.
Chimera::Storage::~Storage()
{
    if (_tmp_state)
        sipReleaseType(_ptr_storage, _parsed_type->typeDef(), _tmp_state);
}


// Return the address of the storage.
void *Chimera::Storage::address()
{
    if (!isPointerType())
        return _value_storage.data();

    if (_parsed_type->name().endsWith('*'))
        return &_ptr_storage;

    return _ptr_storage;
}


// Return true if the value is a pointer type.
bool Chimera::Storage::isPointerType() const
{
    return (_parsed_type->metatype() == PyQt_PyObject::metatype &&
            _parsed_type->typeDef());
}


// Convert the stored value to a Python object.
PyObject *Chimera::Storage::toPyObject() const
{
    // Pointer-class and mapped types are not stored in the QVariant.
    if (isPointerType())
    {
        if (!_ptr_storage)
        {
            Py_INCREF(Py_None);
            return Py_None;
        }

        return sipConvertFromType(_ptr_storage, _parsed_type->typeDef(), 0);
    }

    return _parsed_type->toPyObject(_value_storage);
}
