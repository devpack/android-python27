// This implements the helpers for QObject.
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


#include <ctype.h>

#include <Python.h>

#include <QMetaObject>
#include <QMetaType>
#include <QObject>
#include <QVariant>

#include "qpycore_chimera.h"
#include "qpycore_pyqtboundsignal.h"
#include "qpycore_pyqtproxy.h"
#include "qpycore_pyqtproperty.h"
#include "qpycore_pyqtpyobject.h"
#include "qpycore_qobject_helpers.h"
#include "qpycore_sip.h"
#include "qpycore_sip_helpers.h"
#include "qpycore_types.h"


// Forward declarations.
static int qt_metacall_worker(sipSimpleWrapper *pySelf, PyTypeObject *pytype,
        sipTypeDef *base, QMetaObject::Call _c, int _id, void **_a);


// This is the helper for all implementations of QObject::metaObject().
const QMetaObject *qpycore_qobject_metaobject(sipSimpleWrapper *pySelf,
        sipTypeDef *base)
{
    // Return the dynamic meta-object if there is one.
    if (pySelf && ((pyqtWrapperType *)Py_TYPE(pySelf))->metaobject)
        return &((pyqtWrapperType *)Py_TYPE(pySelf))->metaobject->mo;

    // Fall back to the static Qt meta-object.
    return reinterpret_cast<const QMetaObject *>(((pyqt4ClassTypeDef *)base)->qt4_static_metaobject);
}


// This is the helper for all implementations of QObject::qt_metacall().
int qpycore_qobject_qt_metacall(sipSimpleWrapper *pySelf, sipTypeDef *base,
        QMetaObject::Call _c, int _id, void **_a)
{
    // Check if the Python object has gone.
    if (!pySelf)
        return -1;

    SIP_BLOCK_THREADS
    _id = qt_metacall_worker(pySelf, Py_TYPE(pySelf), base, _c, _id, _a);
    SIP_UNBLOCK_THREADS

    return _id;
}


// This does the real work for all implementations of QObject::qt_metacall().
static int qt_metacall_worker(sipSimpleWrapper *pySelf, PyTypeObject *pytype,
        sipTypeDef *base, QMetaObject::Call _c, int _id, void **_a)
{
    // See if this is a wrapped C++ type rather than a Python sub-type.
    if (pytype == sipTypeAsPyTypeObject(base))
        return _id;

    _id = qt_metacall_worker(pySelf, pytype->tp_base, base, _c, _id, _a);

    if (_id < 0)
        return _id;

    pyqtWrapperType *pyqt_wt = (pyqtWrapperType *)pytype;
    qpycore_metaobject *qo = pyqt_wt->metaobject;

    bool ok = true;

    if (_c == QMetaObject::InvokeMetaMethod)
    {
        if (_id < qo->nr_signals + qo->pslots.count())
        {
            if (_id < qo->nr_signals)
            {
                QObject *qthis = reinterpret_cast<QObject *>(sipGetCppPtr(pySelf, sipType_QObject));

                Py_BEGIN_ALLOW_THREADS
                QMetaObject::activate(qthis, &qo->mo, _id, _a);
                Py_END_ALLOW_THREADS
            }
            else
            {
                // We take a copy just to be safe.
                qpycore_slot slot = qo->pslots.at(_id - qo->nr_signals);

                // Set up the instance specific parts.
                slot.sip_slot.meth.mself = (PyObject *)pySelf;

                PyObject *py = PyQtProxy::invokeSlot(slot, _a);

                if (!py)
                    ok = false;
                else
                {
                    if (_a[0] && slot.signature->result)
                    {
                        ok = slot.signature->result->fromPyObject(py, _a[0]);
                    }

                    Py_DECREF(py);
                }
            }
        }

        _id -= qo->nr_signals + qo->pslots.count();
    }
    else if (_c == QMetaObject::ReadProperty)
    {
        if (_id < qo->pprops.count())
        {
            qpycore_pyqtProperty *prop = qo->pprops.at(_id);

            if (prop->pyqtprop_get)
            {
                PyObject *py = PyObject_CallFunction(prop->pyqtprop_get,
                        const_cast<char *>("O"), pySelf);

                if (py)
                {
                    // Get the underlying QVariant.  As of Qt v4.7.0,
                    // QtDeclarative doesn't pass a QVariant and this value is
                    // 0.
                    QVariant *var = reinterpret_cast<QVariant *>(_a[1]);

                    if (var)
                    {
                        // This tells QMetaProperty::read() to use the new
                        // contents of the QVariant it provided.
                        _a[1] = 0;

                        ok = prop->pyqtprop_parsed_type->fromPyObject(py, var);
                    }
                    else
                    {
                        ok = prop->pyqtprop_parsed_type->fromPyObject(py, _a[0]);
                    }

                    Py_DECREF(py);
                }
                else
                {
                    ok = false;
                }
            }
        }

        _id -= qo->pprops.count();
    }
    else if (_c == QMetaObject::WriteProperty)
    {
        if (_id < qo->pprops.count())
        {
            qpycore_pyqtProperty *prop = qo->pprops.at(_id);

            if (prop->pyqtprop_set)
            {
                // _a is an array whose length and contents vary according to
                // the version of Qt.  Prior to v4.6 _a[1] was the address of
                // the QVariant containing the property value and _a[0] was the
                // address of the actual data in the QVariant.  We used to
                // convert the QVariant at _a[1], rather than the data at
                // _a[0], which gave us a little bit more type checking.  In Qt
                // v4.6 the QPropertyAnimation class contains an optimised path
                // that bypasses QMetaProperty and only sets _a[0], so now
                // that is all we can rely on.  

                PyObject *py = prop->pyqtprop_parsed_type->toPyObject(_a[0]);

                if (py)
                {
                    PyObject *res = PyObject_CallFunction(prop->pyqtprop_set,
                            const_cast<char *>("OO"), pySelf, py);

                    if (res)
                        Py_DECREF(res);
                    else
                        ok = false;

                    Py_DECREF(py);
                }
                else
                    ok = false;
            }
        }

        _id -= qo->pprops.count();
    }
    else if (_c == QMetaObject::ResetProperty)
    {
        if (_id < qo->pprops.count())
        {
            qpycore_pyqtProperty *prop = qo->pprops.at(_id);

            if (prop->pyqtprop_reset)
            {
                PyObject *py = PyObject_CallFunction(prop->pyqtprop_reset,
                        const_cast<char *>("O"), pySelf);

                if (py)
                    Py_DECREF(py);
                else
                    ok = false;
            }
        }

        _id -= qo->pprops.count();
    }
    else if (_c == QMetaObject::QueryPropertyDesignable)
        _id -= qo->pprops.count();
    else if (_c == QMetaObject::QueryPropertyScriptable)
        _id -= qo->pprops.count();
    else if (_c == QMetaObject::QueryPropertyStored)
        _id -= qo->pprops.count();
    else if (_c == QMetaObject::QueryPropertyEditable)
        _id -= qo->pprops.count();
    else if (_c == QMetaObject::QueryPropertyUser)
        _id -= qo->pprops.count();

    // Handle any Python errors.
    if (!ok)
    {
        PyErr_Print();
        return -1;
    }

    return _id;
}


// This is the helper for all implementations of QObject::qt_metacast().
int qpycore_qobject_qt_metacast(sipSimpleWrapper *pySelf, sipTypeDef *base,
        const char *_clname)
{
    if (!_clname)
        return 0;

    // Check if the Python object has gone.
    if (!pySelf)
        return 0;

    int is_py_class = 0;

    SIP_BLOCK_THREADS

    PyObject *mro = Py_TYPE(pySelf)->tp_mro;

    for (int i = 0; i < PyTuple_GET_SIZE(mro); ++i)
    {
        PyTypeObject *pytype = (PyTypeObject *)PyTuple_GET_ITEM(mro, i);

        if (pytype == sipTypeAsPyTypeObject(base))
            break;

        if (qstrcmp(pytype->tp_name, _clname) == 0)
        {
            is_py_class = 1;
            break;
        }
    }

    SIP_UNBLOCK_THREADS

    return is_py_class;
}


// This is a helper for QObject.staticMetaObject %GetCode.
PyObject *qpycore_qobject_staticmetaobject(PyObject *type_obj)
{
    pyqtWrapperType *pyqt_wt = (pyqtWrapperType *)type_obj;
    const QMetaObject *mo;

    if (pyqt_wt->metaobject)
        // It's a sub-type of a wrapped type.
        mo = &pyqt_wt->metaobject->mo;
    else
        // It's a wrapped type.
        mo = reinterpret_cast<const QMetaObject *>(((pyqt4ClassTypeDef *)((sipWrapperType *)pyqt_wt)->type)->qt4_static_metaobject);

    return sipConvertFromType(const_cast<QMetaObject *>(mo), sipType_QMetaObject, 0);
}


// This is a helper for QObject.sender().
QObject *qpycore_qobject_sender(QObject *obj)
{
    if (obj || !PyQtProxy::last_sender)
        return obj;

    // See if it is a short-circuit signal proxy.
    PyQtShortcircuitSignalProxy *ssp = qobject_cast<PyQtShortcircuitSignalProxy *>(PyQtProxy::last_sender);

    if (ssp)
        return ssp->parent();

    // See if it is an ordinary signal proxy.
    if (qstrcmp(PyQtProxy::last_sender->metaObject()->className(), "PyQtProxy") == 0)
        return static_cast<PyQtProxy *>(PyQtProxy::last_sender)->transmitter;

    return PyQtProxy::last_sender;
}


// This is a helper for QObject.receivers() that returns the number of
// receivers for an object if it is a signal proxy.  It is exported because
// QObject::receivers() is protected.
int qpycore_qobject_receivers(QObject *obj, const char *signal, int nr)
{
    // Find the object that is really emitting the signal.
    QObject *qtx = qpycore_find_signal(obj, &signal);

    if (!qtx)
        return 0;

    // If the emitter is the same then it is a Qt signal and the supplied
    // value is the correct one.
    if (qtx == obj)
        return nr;

    // See if it is a short-circuit signal proxy.
    PyQtShortcircuitSignalProxy *ssp = qobject_cast<PyQtShortcircuitSignalProxy *>(qtx);

    if (ssp)
        return ssp->getReceivers(signal);

    if (qstrcmp(qtx->metaObject()->className(), "PyQtProxy") == 0)
        return static_cast<const PyQtProxy *>(qtx)->getReceivers(signal);

    // We should never get here.
    return 0;
}
