/*
 * This is the Qt Designer plugin that collects all the Python plugins it can
 * find as a widget collection to Designer.
 *
 * Copyright (c) 2010 Riverbank Computing Limited <info@riverbankcomputing.com>
 * 
 * This file is part of PyQt.
 * 
 * This file may be used under the terms of the GNU General Public
 * License versions 2.0 or 3.0 as published by the Free Software
 * Foundation and appearing in the files LICENSE.GPL2 and LICENSE.GPL3
 * included in the packaging of this file.  Alternatively you may (at
 * your option) use any later version of the GNU General Public
 * License if such license has been publicly approved by Riverbank
 * Computing Limited (or its successors, if any) and the KDE Free Qt
 * Foundation. In addition, as a special exception, Riverbank gives you
 * certain additional rights. These rights are described in the Riverbank
 * GPL Exception version 1.1, which can be found in the file
 * GPL_EXCEPTION.txt in this package.
 * 
 * Please review the following information to ensure GNU General
 * Public Licensing requirements will be met:
 * http://trolltech.com/products/qt/licenses/licensing/opensource/. If
 * you are unsure which license is appropriate for your use, please
 * review the following information:
 * http://trolltech.com/products/qt/licenses/licensing/licensingoverview
 * or contact the sales department at sales@riverbankcomputing.com.
 * 
 * This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 * WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */


#include "pluginloader.h"

#include <stdlib.h>

#include <QtGlobal>
#include <QtPlugin>
#include <QCoreApplication>
#include <QDesignerCustomWidgetInterface>
#include <QDir>
#include <QLibrary>
#include <QLibraryInfo>
#include <QStringList>
#include <QVector>

#include "../qpy/QtDesigner/qpydesignercustomwidgetplugin.h"


// Construct the collection of Python widgets.
PyCustomWidgets::PyCustomWidgets(QObject *parent) : QObject(parent)
{
    // Get the default list of directories to search.  These correspond to a
    // standard "python" subdirectory of all the places that Designer looks for
    // its own plugins.
    QStringList default_dirs;

    QStringList path_list = QCoreApplication::libraryPaths();
    foreach (const QString &path, path_list)
        default_dirs.append(path + QDir::separator() +
                QLatin1String("designer") + QDir::separator() +
                QLatin1String("python"));

    default_dirs.append(QDir::homePath() + QDir::separator() +
            QLatin1String(".designer") + QDir::separator() +
            QLatin1String("plugins") + QDir::separator() +
            QLatin1String("python"));

    // Get the list of directories to search.
    QStringList dirs;
    char *pyqt_path = getenv("PYQTDESIGNERPATH");

    if (pyqt_path)
    {
#if defined(Q_OS_WIN)
        QLatin1Char sep(';');
#else
        QLatin1Char sep(':');
#endif

        QStringList pyqt_dirs = QString::fromLatin1(pyqt_path).split(sep);

        for (QStringList::const_iterator it = pyqt_dirs.constBegin(); it != pyqt_dirs.constEnd(); ++it)
            if ((*it).isEmpty())
                dirs << default_dirs;
            else
                dirs.append(QDir(*it).canonicalPath());
    }
    else
        dirs = default_dirs;

    // The sys.path object if we need it.
    PyObject *sys_path = 0;

    // The sip.unwrapinstance object if we need it.
    PyObject *sip_unwrapinstance = 0;

    // The PyQt4.QtDesigner.QPyDesignerCustomWidgetPlugin object if we need it.
    PyObject *qtdesigner_custom = 0;

    // Go through each directory.
    for (int i = 0; i < dirs.size(); ++i)
    {
        QString dir = dirs.at(i);

        // Get a list of all candidate plugin modules.
        QStringList candidates = QDir(dir).entryList(QDir::Files);
        QStringList plugins;

        for (int p = 0; p < candidates.size(); ++p)
        {
            QStringList parts = candidates.at(p).split('.');

            if (parts.size() != 2)
                continue;

            if (!parts.at(1).startsWith("py"))
                continue;

            const QString &plugin = parts.at(0);

            if (!plugin.endsWith("plugin"))
                continue;

            if (plugins.contains(plugin))
                continue;

            plugins.append(plugin);
        }

        // Skip if there is nothing of interest in this directory.
        if (!plugins.size())
            continue;

        // Make sure the interpreter is loaded and initialised.  Leave this as
        // late as possible.
        if (!Py_IsInitialized())
        {
            QLibrary library(PYTHON_LIB);

            library.setLoadHints(QLibrary::ExportExternalSymbolsHint);

            if (!library.load())
                return;

            Py_Initialize();
        }

        // Make sure we have sys.path.
        if (!sys_path)
        {
            sys_path = getModuleAttr("sys", "path");

            if (!sys_path)
                return;
        }

        // Make sure we have sip.unwrapinstance.
        if (!sip_unwrapinstance)
        {
            sip_unwrapinstance = getModuleAttr("sip", "unwrapinstance");

            if (!sip_unwrapinstance)
                return;
        }

        // Make sure we have sip.unwrapinstance.
        if (!qtdesigner_custom)
        {
            qtdesigner_custom = getModuleAttr("PyQt4.QtDesigner", "QPyDesignerCustomWidgetPlugin");

            if (!qtdesigner_custom)
                return;
        }

        // Convert the directory to a Python object with native separators.
#if QT_VERSION >= 0x040200
        dir = QDir::toNativeSeparators(dir);
#else
        dir = QDir::convertSeparators(dir);
#endif

#if PY_MAJOR_VERSION >= 3
        // This is a copy of qpycore_PyObject_FromQString().

#if defined(Py_UNICODE_WIDE)
#if QT_VERSION >= 0x040200
        QVector<uint> ucs4 = dir.toUcs4();

        PyObject *dobj = PyUnicode_FromUnicode(NULL, ucs4.size());

        if (!dobj)
        {
            PyErr_Print();
            continue;
        }

        memcpy(PyUnicode_AS_UNICODE(dobj), ucs4.constData(),
                ucs4.size() * sizeof (Py_UNICODE));
#else
        PyObject *dobj = PyUnicode_FromUnicode(0, dir.length());

        if (!dobj)
        {
            PyErr_Print();
            continue;
        }

        Py_UNICODE *pyu = PyUnicode_AS_UNICODE(dobj);

        for (int i = 0; i < dir.length(); ++i)
            *pyu++ = (dir.at(i)).unicode();
#endif
#else
        PyObject *dobj = PyUnicode_FromUnicode(0, dir.length());

        if (!dobj)
        {
            PyErr_Print();
            continue;
        }

        memcpy(PyUnicode_AS_UNICODE(dobj), dir.utf16(),
                dir.length() * sizeof (Py_UNICODE));
#endif
#else
        PyObject *dobj = PyString_FromString(dir.toAscii().constData());

        if (!dobj)
        {
            PyErr_Print();
            continue;
        }
#endif

        // Add the directory to sys.path.
        int rc = PyList_Append(sys_path, dobj);
        Py_DECREF(dobj);

        if (rc < 0)
        {
            PyErr_Print();
            continue;
        }

        // Import each plugin.
        for (int plug = 0; plug < plugins.size(); ++plug)
        {
            PyObject *plug_mod = PyImport_ImportModule(plugins.at(plug).toAscii().data());

            if (!plug_mod)
            {
                PyErr_Print();
                continue;
            }

            // Go through the module looking for types that implement
            // QDesignerCustomWidgetInterface (ie. by deriving from
            // QPyDesignerCustomWidgetPlugin).
            PyObject *mod_dict = PyModule_GetDict(plug_mod);
            PyObject *key, *value;
#if PY_VERSION_HEX >= 0x02050000
            Py_ssize_t pos = 0;
#else
            int pos = 0;
#endif

            while (PyDict_Next(mod_dict, &pos, &key, &value))
            {
                if (!PyType_Check(value))
                    continue;

                if (value == qtdesigner_custom)
                    continue;

                if (!PyType_IsSubtype((PyTypeObject *)value, (PyTypeObject *)qtdesigner_custom))
                    continue;

                // Create the plugin instance.  Note that we don't give it a
                // parent, which make things easier.  It also means that Python
                // owns the instance so we don't decrement the reference count
                // so that it doesn't get garbage collected.
                PyObject *plugobj = PyObject_CallObject(value, NULL);

                if (!plugobj)
                {
                    PyErr_Print();
                    continue;
                }

                // Get the address of the C++ instance.
                PyObject *plugaddr = PyObject_CallFunctionObjArgs(sip_unwrapinstance, plugobj, NULL);

                if (!plugaddr)
                {
                    Py_DECREF(plugobj);
                    PyErr_Print();
                    continue;
                }

                void *addr = PyLong_AsVoidPtr(plugaddr);
                Py_DECREF(plugaddr);

                widgets.append(reinterpret_cast<QPyDesignerCustomWidgetPlugin *>(addr));
            }

            Py_DECREF(plug_mod);
        }
    }
}


// Return the list of custom widgets.
QList<QDesignerCustomWidgetInterface *> PyCustomWidgets::customWidgets() const
{
    return widgets;
}


// Return the named attribute object from the named module.
PyObject *PyCustomWidgets::getModuleAttr(const char *module, const char *attr)
{
#if PY_VERSION_HEX >= 0x02050000
    PyObject *mod = PyImport_ImportModule(module);
#else
    PyObject *mod = PyImport_ImportModule(const_cast<char *>(module));
#endif

    if (!mod)
    {
        PyErr_Print();
        return 0;
    }

#if PY_VERSION_HEX >= 0x02050000
    PyObject *obj = PyObject_GetAttrString(mod, attr);
#else
    PyObject *obj = PyObject_GetAttrString(mod, const_cast<char *>(attr));
#endif

    Py_DECREF(mod);

    if (!obj)
    {
        PyErr_Print();
        return 0;
    }

    return obj;
}


// Register the plugin.
Q_EXPORT_PLUGIN2(MODULE_NAME, PyCustomWidgets)
