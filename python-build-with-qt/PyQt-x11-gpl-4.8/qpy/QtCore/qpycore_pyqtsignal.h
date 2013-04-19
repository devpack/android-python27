// This defines the interfaces for the pyqtSignal type.
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


#ifndef _QPYCORE_PYQTSIGNAL_H
#define _QPYCORE_PYQTSIGNAL_H


#include <Python.h>

#include <QList>

#include "qpycore_chimera.h"


extern "C" {

// This defines the structure of a PyQt signal.
typedef struct _qpycore_pyqtSignal {
    PyObject_HEAD

    // The signal master.
    struct _qpycore_pyqtSignal *master;

    // The index in the signal master.
    int master_index;

    // The non-signal overloads (if any).
    PyMethodDef *non_signals;

    // The list of overloaded signals.  (A pointer because C is creating the
    // instance.)  These are owned by the signal master.
    QList<Chimera::Signature *> *overloads;
} qpycore_pyqtSignal;


extern PyTypeObject qpycore_pyqtSignal_Type;

PyObject *qpycore_get_signal_doc(PyObject *self);
int qpycore_get_lazy_attr(const sipTypeDef *td, PyObject *dict);

}


int qpycore_signal_index(qpycore_pyqtSignal *ps, PyObject *subscript,
        const char *context);
void qpycore_set_signal_name(qpycore_pyqtSignal *ps, const char *type_name,
        const char *name);
PyObject *qpycore_call_signal_overload(PyObject *ps_obj, PyObject *bound,
        PyObject *args, PyObject *kw);


#endif
