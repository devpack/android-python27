// This contains the implementation of various odds and ends.
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

#include "qpycore_misc.h"
#include "qpycore_types.h"


// Return true if the given type (which must be a class) was wrapped for PyQt4.
bool qpycore_is_pyqt4_class(const sipTypeDef *td)
{
    return PyType_IsSubtype(Py_TYPE(sipTypeAsPyTypeObject(td)),
            &qpycore_pyqtWrapperType_Type);
}


#if PY_MAJOR_VERSION >= 3
// Python v3 doesn't have the Unicode equivalent of Python v2's
// PyString_ConcatAndDel().
void qpycore_Unicode_ConcatAndDel(PyObject **string, PyObject *newpart)
{
    PyObject *old = *string;

    if (old)
    {
        if (newpart)
            *string = PyUnicode_Concat(old, newpart);
        else
            *string = 0;

        Py_DECREF(old);
    }

    Py_XDECREF(newpart);
}
#endif


// Convert a Python argv list to a conventional C argc count and argv array.
char **qpycore_ArgvToC(PyObject *argvlist, int &argc)
{
    argc = PyList_GET_SIZE(argvlist);

    // Allocate space for two copies of the argument pointers, plus the
    // terminating NULL.
    char **argv = new char *[2 * (argc + 1)];

    // Convert the list.
    for (int a = 0; a < argc; ++a)
    {
        PyObject *arg_obj = PyList_GET_ITEM(argvlist, a);
        const char *arg = sipString_AsLatin1String(&arg_obj);

        if (arg)
        {
            arg = qstrdup(arg);
            Py_DECREF(arg_obj);
        }
        else
        {
            // Try not to mess up Qt's argument parsing by simply missing out
            // the argument.
            arg = "unknown";
        }

        argv[a] = argv[a + argc + 1] = const_cast<char *>(arg);
    }

    argv[argc + argc + 1] = argv[argc] = NULL;

    return argv;
}


// Remove arguments from the Python argv list that have been removed from the
// C argv array.
void qpycore_UpdatePyArgv(PyObject *argvlist, int argc, char **argv)
{
    for (int a = 0, na = 0; a < argc; ++a)
    {
        // See if it was removed.
        if (argv[na] == argv[a + argc + 1])
            ++na;
        else
            PyList_SetSlice(argvlist, na, na + 1, 0);
    }
}
