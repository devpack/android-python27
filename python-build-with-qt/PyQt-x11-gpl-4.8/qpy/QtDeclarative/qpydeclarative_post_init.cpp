// This is the initialisation support code for the QtDeclarative module.
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

#include "qpydeclarativelistproperty.h"


// Perform any required initialisation.
void qpydeclarative_post_init(PyObject *module_dict)
{
    // Initialise the QPyDeclarativeListProperty type.
#if PY_MAJOR_VERSION >= 3
    qpydeclarative_QPyDeclarativeListProperty_Type.tp_base = &PyUnicode_Type;
#else
    qpydeclarative_QPyDeclarativeListProperty_Type.tp_base = &PyString_Type;
#endif

    if (PyType_Ready(&qpydeclarative_QPyDeclarativeListProperty_Type) < 0)
        Py_FatalError("PyQt4.QtDeclarative: Failed to initialise QPyDeclarativeListProperty type");

    // Create the only instance and add it to the module dictionary.
    PyObject *inst = PyObject_CallFunction(
            (PyObject *)&qpydeclarative_QPyDeclarativeListProperty_Type,
            const_cast<char *>("s"), "QDeclarativeListProperty<QObject>");

    if (!inst)
        Py_FatalError("PyQt4.QtDeclarative: Failed to create QPyDeclarativeListProperty instance");

    if (PyDict_SetItemString(module_dict, "QPyDeclarativeListProperty", inst) < 0)
        Py_FatalError("PyQt4.QtDeclarative: Failed to set QPyDeclarativeListProperty instance");
}
