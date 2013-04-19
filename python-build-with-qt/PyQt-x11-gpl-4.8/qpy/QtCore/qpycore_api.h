// This defines the API provided by this library.  It must not be explicitly
// included by the library itself.
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


#ifndef _QPYCORE_API_H
#define _QPYCORE_API_H


#include <QCoreApplication>
#include <QString>
#include <QVariant>

#include "qpycore_shared.h"


class QObject;


// Support for pyqtSlot() and pyqtSignature().
PyObject *qpycore_pyqtslot(PyObject *args, PyObject *kwds);
PyObject *qpycore_pyqtsignature(PyObject *args, PyObject *kwds);


// Support for pyqtConfigure().
int qpycore_pyqtconfigure(PyObject *self, QObject *qobj, PyObject *kwds);


// Support for converting between PyObject and QString.
PyObject *qpycore_PyObject_FromQString(const QString &qstr);
QString qpycore_PyObject_AsQString(PyObject *obj);
const char *qpycore_encode(PyObject **s, QCoreApplication::Encoding encoding);


// Support for converting between PyObject and QStringList.
PyObject *qpycore_PyObject_FromQStringList(const QStringList &qstrlst);
QStringList qpycore_PySequence_AsQStringList(PyObject *obj);
int qpycore_PySequence_Check_QStringList(PyObject *obj);


// Support for converting between PyObject and QVariant.
PyObject *qpycore_PyObject_FromQVariant(const QVariant &qvar);
QVariant qpycore_PyObject_AsQVariant(PyObject *obj, int *is_err);


// Support for Q_FLAGS and Q_ENUMS.
PyObject *qpycore_register_int_types(PyObject *type_names);


// Support for creating QGenericArgument and QGenericReturnArgument instances.
PyObject *qpycore_ArgumentFactory(PyObject *type, PyObject *data);
PyObject *qpycore_ReturnFactory(PyObject *type);
PyObject *qpycore_ReturnValue(PyObject *gra);


// Support for QObject.staticMetaObject %GetCode.
PyObject *qpycore_qobject_staticmetaobject(PyObject *type_obj);


// Support for emitting signals.
bool qpycore_qobject_emit(QObject *qtx, const char *sig, PyObject *sigargs);


// Support for QMetaObject::connectSlotsByName.
void qpycore_qmetaobject_connectslotsbyname(QObject *qobj,
        PyObject *qobj_wrapper);

// Support for signals.
bool qpycore_pyqtsignal_get_parts(PyObject *sig_obj, QObject **qtx,
        const char **sig);


// Utilities.
#if PY_MAJOR_VERSION >= 3
void qpycore_Unicode_ConcatAndDel(PyObject **string, PyObject *newpart);
#endif


// Initialisation.
void qpycore_init();
void qpycore_post_init(PyObject *module_dict);


#endif
