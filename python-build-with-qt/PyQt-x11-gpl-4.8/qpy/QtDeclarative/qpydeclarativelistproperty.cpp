// This is the implementation of the QPyDeclarativeListProperty class.
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


#include <QObject>
#include <QtDeclarative>

#include "sipAPIQtDeclarative.h"

#include "qpydeclarativelistproperty.h"
#include "qpydeclarative_listwrapper.h"


// Forward declarations.
extern "C" {
static PyObject *QPyDeclarativeListProperty_call(PyObject *, PyObject *args,
        PyObject *);
}

static void list_append(QDeclarativeListProperty<QObject> *p, QObject *el);
static QObject *list_at(QDeclarativeListProperty<QObject> *p, int idx);
static void list_clear(QDeclarativeListProperty<QObject> *p);
static int list_count(QDeclarativeListProperty<QObject> *p);


// The type's doc-string.
PyDoc_STRVAR(QPyDeclarativeListProperty_doc,
"QPyDeclarativeListProperty(QObject, list-of-QObject)");


// This implements the QPyDeclarativeListProperty Python type.  It is a
// sub-type of the standard string type that is callable.
PyTypeObject qpydeclarative_QPyDeclarativeListProperty_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    SIP_TPNAME_CAST("PyQt4.QtDeclarative.QPyDeclarativeListProperty"),
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    QPyDeclarativeListProperty_call,
    0,
    0,
    0,
    0,
    Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE|
#if PY_VERSION_HEX >= 0x03000000
        Py_TPFLAGS_UNICODE_SUBCLASS,
#elif PY_VERSION_HEX >= 0x02060000
        Py_TPFLAGS_STRING_SUBCLASS,
#else
        0,
#endif
    QPyDeclarativeListProperty_doc,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
#if PY_VERSION_HEX >= 0x02060000
    0,
#endif
};


// This is a factory for the wrapped QDeclarativeListProperty<PyDelegate>.
static PyObject *QPyDeclarativeListProperty_call(PyObject *, PyObject *args,
        PyObject *)
{
    PyTypeObject *qobject_type = sipTypeAsPyTypeObject(sipType_QObject);
    PyObject *qobj_obj, *list_obj;

    if (!PyArg_ParseTuple(args,
#if PY_VERSION_HEX >= 0x02050000
            "O!O!:QPyDeclarativeListProperty",
#else
            const_cast<char *>("O!O!:QPyDeclarativeListProperty"),
#endif
            qobject_type, &qobj_obj, &PyList_Type, &list_obj, &PyType_Type))
        return 0;

    // Get the C++ QObject.
    int iserr = 0;
    QObject *qobj = reinterpret_cast<QObject *>(sipConvertToType(qobj_obj, sipType_QObject, 0, SIP_NOT_NONE|SIP_NO_CONVERTORS, 0, &iserr));

    if (iserr)
        return 0;

    // Get a list wrapper with the C++ QObject as its parent.
    ListWrapper *list_wrapper = ListWrapper::wrapper(list_obj, qobj);

    if (!list_wrapper)
        return 0;

    // Create the C++ QDeclarativeListProperty<QObject> with the list as the
    // data.
    QDeclarativeListProperty<QObject> *prop = new QDeclarativeListProperty<QObject>(qobj, &list_wrapper->qobject_list, list_append, list_count, list_at, list_clear);

    // Convert it to a Python object.
    static const sipTypeDef *mapped_type = 0;

    if (!mapped_type)
        mapped_type = sipFindType("QDeclarativeListProperty<QObject>");

    Q_ASSERT(mapped_type);

    // Make sure ownership is with Python.
    PyObject *prop_obj = sipConvertFromNewType(prop, mapped_type, qobj_obj);

    if (!prop_obj)
    {
        delete prop;
        return 0;
    }

    return prop_obj;
}


// Append to the list.
static void list_append(QDeclarativeListProperty<QObject> *p, QObject *el)
{
    ListWrapper::append(p->object,
            reinterpret_cast<QList<QObject *> *>(p->data), el);
}


// Get the length of the list.
static int list_count(QDeclarativeListProperty<QObject> *p)
{
    return reinterpret_cast<QList<QObject *> *>(p->data)->count();
}


// Get an item from the list.
static QObject *list_at(QDeclarativeListProperty<QObject> *p, int idx)
{
    return reinterpret_cast<QList<QObject *> *>(p->data)->at(idx);
}


// Clear the list.
static void list_clear(QDeclarativeListProperty<QObject> *p)
{
    ListWrapper::clear(p->object,
            reinterpret_cast<QList<QObject *> *>(p->data));
}
