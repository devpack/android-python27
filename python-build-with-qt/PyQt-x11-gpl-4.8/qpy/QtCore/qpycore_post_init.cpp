// This is the post-initialisation support code for the QtCore module.
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

#include <QMetaType>
#include <QMutex>

#include "qpycore_pyqtboundsignal.h"
#include "qpycore_pyqtproperty.h"
#include "qpycore_pyqtproxy.h"
#include "qpycore_pyqtpyobject.h"
#include "qpycore_pyqtsignal.h"
#include "qpycore_sip.h"


// The name attribute name as an object.
PyObject *qpycore_name_attr_name;

// The signature attribute name as an object.
PyObject *qpycore_signature_attr_name;


// Perform any required post-initialisation.
void qpycore_post_init(PyObject *module_dict)
{
    // Add the meta-type to the module dictionary.
    if (PyDict_SetItemString(module_dict, "pyqtWrapperType",
                (PyObject *)&qpycore_pyqtWrapperType_Type) < 0)
        Py_FatalError("PyQt4.QtCore: Failed to set pyqtWrapperType type");

    // Initialise the pyqtProperty type and add it to the module dictionary.
    if (PyType_Ready(&qpycore_pyqtProperty_Type) < 0)
        Py_FatalError("PyQt4.QtCore: Failed to initialise pyqtProperty type");

    if (PyDict_SetItemString(module_dict, "pyqtProperty",
                (PyObject *)&qpycore_pyqtProperty_Type) < 0)
        Py_FatalError("PyQt4.QtCore: Failed to set pyqtProperty type");

    // Initialise the pyqtSignal type and add it to the module dictionary.
    if (PyType_Ready(&qpycore_pyqtSignal_Type) < 0)
        Py_FatalError("PyQt4.QtCore: Failed to initialise pyqtSignal type");

    if (PyDict_SetItemString(module_dict, "pyqtSignal",
                (PyObject *)&qpycore_pyqtSignal_Type) < 0)
        Py_FatalError("PyQt4.QtCore: Failed to set pyqtSignal type");

    // Initialise the pyqtBoundSignal type.  Don't add it to the module
    // dictionary as we don't want it to be explicitly invoked.
    qpycore_pyqtBoundSignal_Type.tp_new = PyType_GenericNew;

    if (PyType_Ready(&qpycore_pyqtBoundSignal_Type) < 0)
        Py_FatalError("PyQt4.QtCore: Failed to initialise pyqtBoundSignal type");

    // Register the C++ type that wraps Python objects.
    PyQt_PyObject::metatype = qRegisterMetaType<PyQt_PyObject>("PyQt_PyObject");
    qRegisterMetaTypeStreamOperators<PyQt_PyObject>("PyQt_PyObject");

    // Register the lazy attribute getter.
    if (sipRegisterAttributeGetter(sipType_QObject, qpycore_get_lazy_attr) < 0)
        Py_FatalError("PyQt4.QtCore: Failed to register attribute getter");

    // Objectify some strings.
#if PY_MAJOR_VERSION >= 3
    qpycore_signature_attr_name = PyUnicode_FromString("__pyqtSignature__");
#else
    qpycore_signature_attr_name = PyString_FromString("__pyqtSignature__");
#endif

    if (!qpycore_signature_attr_name)
        Py_FatalError("PyQt4.QtCore: Failed to objectify '__pyqtSignature__'");

#if PY_MAJOR_VERSION >= 3
    qpycore_name_attr_name = PyUnicode_FromString("__name__");
#else
    qpycore_name_attr_name = PyString_FromString("__name__");
#endif

    if (!qpycore_name_attr_name)
        Py_FatalError("PyQt4.QtCore: Failed to objectify '__name__'");

    // Create the mutex that serialises access to the signal/slot proxies.  We
    // don't use a statically initialised one because Qt needs some things to
    // be initialised first (at least for Windows) and this is the only way to
    // guarantee things are done in the right order.
    PyQtProxy::mutex = new QMutex(QMutex::Recursive);
}
