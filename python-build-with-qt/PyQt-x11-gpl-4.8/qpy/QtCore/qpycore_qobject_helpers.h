// This defines the interfaces of the helpers for QObject.
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


#ifndef _QPYCORE_QOBJECT_HELPERS_H
#define _QPYCORE_QOBJECT_HELPERS_H


#include <Python.h>

#include <QMetaObject>

#include "qpycore_sip.h"


class QObject;


const QMetaObject *qpycore_qobject_metaobject(sipSimpleWrapper *pySelf,
        sipTypeDef *base);
int qpycore_qobject_qt_metacall(sipSimpleWrapper *pySelf, sipTypeDef *base,
        QMetaObject::Call _c, int _id, void **_a);
int qpycore_qobject_qt_metacast(sipSimpleWrapper *pySelf, sipTypeDef *base,
        const char *_clname);
QObject *qpycore_qobject_sender(QObject *obj);
int qpycore_qobject_receivers(QObject *obj, const char *signal, int nr);
int qpycore_qobject_kw_handler(PyObject *obj, QObject *qobj, PyObject *kwds);


#endif
