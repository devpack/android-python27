// This is the initialisation support code for the QtCore module.
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

#include "qpycore_qobject_helpers.h"
#include "qpycore_shared.h"
#include "qpycore_sip.h"
#include "qpycore_types.h"


// Perform any required initialisation.
void qpycore_init()
{
    // Initialise the meta-type.
    qpycore_pyqtWrapperType_Type.tp_base = sipWrapperType_Type;

    if (PyType_Ready(&qpycore_pyqtWrapperType_Type) < 0)
        Py_FatalError("PyQt4.QtCore: Failed to initialise pyqtWrapperType type");

    // Register the meta-type.
    if (sipRegisterPyType((PyTypeObject *)&qpycore_pyqtWrapperType_Type) < 0)
        Py_FatalError("PyQt4.QtCore: Failed to register pyqtWrapperType type");

    // Export the helpers.
    sipExportSymbol("qtcore_qt_metaobject",
            (void *)qpycore_qobject_metaobject);
    sipExportSymbol("qtcore_qt_metacall", (void *)qpycore_qobject_qt_metacall);
    sipExportSymbol("qtcore_qt_metacast", (void *)qpycore_qobject_qt_metacast);
    sipExportSymbol("qpycore_qobject_sender", (void *)qpycore_qobject_sender);
    sipExportSymbol("qpycore_qobject_receivers",
            (void *)qpycore_qobject_receivers);

    sipExportSymbol("pyqt_kw_handler", (void *)qpycore_pyqtconfigure);

    sipExportSymbol("qpycore_ArgvToC", (void *)qpycore_ArgvToC);
    sipExportSymbol("qpycore_UpdatePyArgv", (void *)qpycore_UpdatePyArgv);
}
