// This implements the helpers for QMetaObject.
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
#include <QMetaMethod>
#include <QMetaObject>
#include <QObject>

#include "qpycore_chimera.h"
#include "qpycore_misc.h"
#include "qpycore_sip.h"


// Forward declarations.
static void connect(QObject *qobj, PyObject *slot_obj,
        const QByteArray &slot_nm, const QByteArray &args);


void qpycore_qmetaobject_connectslotsbyname(QObject *qobj,
        PyObject *qobj_wrapper)
{
    // Get the class attributes.
    PyObject *dir = PyObject_Dir((PyObject *)Py_TYPE(qobj_wrapper));

    if (!dir)
        return;

    PyObject *slot_obj = 0;

    for (SIP_SSIZE_T li = 0; li < PyList_GET_SIZE(dir); ++li)
    {
        PyObject *name_obj = PyList_GET_ITEM(dir, li);

        // Get the slot object.
        Py_XDECREF(slot_obj);
        slot_obj = PyObject_GetAttr(qobj_wrapper, name_obj);

        if (!slot_obj)
            continue;

        // Ignore it if it is not a callable.
        if (!PyCallable_Check(slot_obj))
            continue;

        // Use the signature attribute instead of the name if there is one.
        PyObject *sigattr = PyObject_GetAttr(slot_obj,
                qpycore_signature_attr_name);

        if (sigattr)
        {
            for (SIP_SSIZE_T i = 0; i < PyList_GET_SIZE(sigattr); ++i)
            {
                PyObject *decoration = PyList_GET_ITEM(sigattr, i);
                Chimera::Signature *sig = Chimera::Signature::fromPyObject(decoration);
                QByteArray args = sig->arguments();

                if (!args.isEmpty())
                    connect(qobj, slot_obj, sig->name(), args);
            }

            Py_DECREF(sigattr);
        }
        else
        {
            const char *ascii_name = sipString_AsASCIIString(&name_obj);

            if (!ascii_name)
                continue;

            PyErr_Clear();

            connect(qobj, slot_obj, QByteArray(ascii_name), QByteArray());

            Py_DECREF(name_obj);
        }
    }

    Py_XDECREF(slot_obj);
    Py_DECREF(dir);
}


// Connect up a particular slot name, with optional arguments.
static void connect(QObject *qobj, PyObject *slot_obj,
        const QByteArray &slot_nm, const QByteArray &args)
{
    // Ignore if it's not an autoconnect slot.
    if (!slot_nm.startsWith("on_"))
        return;

    // Extract the names of the emitting object and the signal.
    int i;

    i = slot_nm.lastIndexOf('_');

    if (i - 3 < 1 || i + 1 >= slot_nm.size())
        return;

    QByteArray ename = slot_nm.mid(3, i - 3);
    QByteArray sname = slot_nm.mid(i + 1);

    // Find the emitting object and get its meta-object.
#if defined(QT_NO_MEMBER_TEMPLATES)
    QObject *eobj = qFindChild<QObject *>(qobj, ename);
#else
    QObject *eobj = qobj->findChild<QObject *>(ename);
#endif

    if (!eobj)
        return;

    const QMetaObject *mo = eobj->metaObject();

    // Got through the methods looking for a matching signal.
    PyObject *epyobj = 0;

    for (int m = 0; m < mo->methodCount(); ++m)
    {
        QMetaMethod mm = mo->method(m);

        if (mm.methodType() != QMetaMethod::Signal)
            continue;

        QByteArray sig(mm.signature());

        if (Chimera::Signature::name(sig) != sname)
            continue;

        // If we have slot arguments then they must match as well.
        if (!args.isEmpty() && Chimera::Signature::arguments(sig) != args)
            continue;

        // Add the type character.
        sig.prepend('2');

        // Get the wrapper now we know it is needed.
        if (!epyobj)
        {
            epyobj = sipConvertFromType(eobj, sipType_QObject, 0);

            if (!epyobj)
                break;
        }

        // Connect the signal.
        PyObject *res = sipConnectRx(epyobj, sig.constData(), slot_obj, 0, 0);
        Py_XDECREF(res);
    }

    Py_XDECREF(epyobj);
}
