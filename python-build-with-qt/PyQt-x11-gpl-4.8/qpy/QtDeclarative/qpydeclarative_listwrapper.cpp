// This is the implementation of the ListWrapper class.
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


#include "sipAPIQtDeclarative.h"

#include "qpydeclarative_listwrapper.h"


// Create a wrapper from validated objects.
ListWrapper::ListWrapper(PyObject *py_list, QObject *parent)
        : QObject(parent), _py_list(py_list)
{
    Py_INCREF(_py_list);
}


// Destroy the wrapper.
ListWrapper::~ListWrapper()
{
    Py_DECREF(_py_list);
}


// Get a wrapper after validating any list elements.
ListWrapper *ListWrapper::wrapper(PyObject *py_list, QObject *parent)
{
    ListWrapper *lw;

    // A wrapper might be created every time the property getter is called, so
    // try and reuse an existing one.

    const QObjectList &children = parent->children();

    for (int i = 0; i < children.count(); ++i)
    {
        lw = qobject_cast<ListWrapper *>(children.at(i));

        if (lw && lw->_py_list == py_list)
            return lw;
    }

    // Create a new one.
    lw = new ListWrapper(py_list, parent);

    for (SIP_SSIZE_T i = 0; i < PyList_GET_SIZE(py_list); ++i)
    {
        int iserr = 0;

        void *cpp = sipForceConvertToType(PyList_GET_ITEM(py_list, i),
                sipType_QObject, 0, SIP_NO_CONVERTORS, 0, &iserr);

        if (iserr)
        {
            delete lw;
            return 0;
        }

        lw->qobject_list.append(reinterpret_cast<QObject *>(cpp));
    }

    return lw;
}


// Append to the list.
void ListWrapper::append(QObject *qobj, QList<QObject *> *qlist, QObject *el)
{
    qlist->append(el);

    ListWrapper *lw = findWrapper(qobj, qlist);

    if (lw)
    {
        PyObject *el_obj = sipConvertFromType(el, sipType_QObject, 0);

        if (!el_obj || PyList_Append(lw->_py_list, el_obj) < 0)
        {
            PyErr_Print();
        }

        Py_XDECREF(el_obj);
    }
    else
    {
        PyErr_Print();
    }
}


// Clear the list.
void ListWrapper::clear(QObject *qobj, QList<QObject *> *qlist)
{
    qlist->clear();

    ListWrapper *lw = findWrapper(qobj, qlist);

    if (!lw || PyList_SetSlice(lw->_py_list, 0, PyList_GET_SIZE(lw->_py_list), NULL) < 0)
        PyErr_Print();
}


// Find the wrapper that handles a given C++ list.
ListWrapper *ListWrapper::findWrapper(QObject *qobj, QList<QObject *> *qlist)
{
    const QObjectList &children = qobj->children();

    for (int i = 0; i < children.count(); ++i)
    {
        ListWrapper *lw = qobject_cast<ListWrapper *>(children.at(i));

        if (lw && &lw->qobject_list == qlist)
            return lw;
    }

    PyErr_SetString(PyExc_AttributeError, "unable to find list wrapper");

    return 0;
}
