// This is the support for QString.
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
#include <string.h>

#include <QString>
#include <QTextCodec>
#include <QVector>

#include "qpycore_sip.h"


// Convert a QString to a Python Unicode object.
PyObject *qpycore_PyObject_FromQString(const QString &qstr)
{
    PyObject *obj;

#if defined(Py_UNICODE_WIDE)
#if QT_VERSION >= 0x040200
    QVector<uint> ucs4 = qstr.toUcs4();

    if ((obj = PyUnicode_FromUnicode(NULL, ucs4.size())) == NULL)
        return NULL;

    memcpy(PyUnicode_AS_UNICODE(obj), ucs4.constData(),
            ucs4.size() * sizeof (Py_UNICODE));
#else
    // Note that this code doesn't handle code points greater than 0xffff very
    // well.

    if ((obj = PyUnicode_FromUnicode(NULL, qstr.length())) == NULL)
        return NULL;

    Py_UNICODE *pyu = PyUnicode_AS_UNICODE(obj);

    for (int i = 0; i < qstr.length(); ++i)
        *pyu++ = (qstr.at(i)).unicode();
#endif
#else
    if ((obj = PyUnicode_FromUnicode(NULL, qstr.length())) == NULL)
        return NULL;

    memcpy(PyUnicode_AS_UNICODE(obj), qstr.utf16(),
            qstr.length() * sizeof (Py_UNICODE));
#endif

    return obj;
}


// Convert a Python Unicode object to a QString.
QString qpycore_PyObject_AsQString(PyObject *obj)
{
#if defined(Py_UNICODE_WIDE)
#if QT_VERSION >= 0x040200
    return QString::fromUcs4((const uint *)PyUnicode_AS_UNICODE(obj),
            PyUnicode_GET_SIZE(obj));
#else
    // Note that this code doesn't handle code points greater than 0xffff very
    // well.

    QString qstr;

    Py_UNICODE *ucode = PyUnicode_AS_UNICODE(obj);
    SIP_SSIZE_T len = PyUnicode_GET_SIZE(obj);

    for (SIP_SSIZE_T i = 0; i < len; ++i)
        qstr.append((uint)ucode[i]);

    return qstr;
#endif
#else
    return QString::fromUtf16((const ushort *)PyUnicode_AS_UNICODE(obj),
            PyUnicode_GET_SIZE(obj));
#endif
}


// Convert a Python unicode/string/bytes object to a character string encoded
// according to the given encoding.  Update the object with a new reference to
// the object that owns the data.
const char *qpycore_encode(PyObject **s, QCoreApplication::Encoding encoding)
{
    PyObject *obj = *s;
    const char *es = 0;
    SIP_SSIZE_T sz;

    if (PyUnicode_Check(obj))
    {
        if (encoding == QCoreApplication::UnicodeUTF8)
        {
            obj = PyUnicode_AsUTF8String(obj);
        }
        else
        {
            QTextCodec *codec = QTextCodec::codecForTr();

            if (codec)
            {
                // Use the Qt codec to get to a byte string, and then to a
                // Python object.
                QString qs = qpycore_PyObject_AsQString(obj);
                QByteArray ba = codec->fromUnicode(qs);

#if PY_MAJOR_VERSION >= 3
                obj = PyBytes_FromStringAndSize(ba.constData(), ba.size());
#else
                obj = PyString_FromStringAndSize(ba.constData(), ba.size());
#endif
            }
            else
            {
                obj = PyUnicode_AsLatin1String(obj);
            }
        }

        if (obj)
        {
#if PY_MAJOR_VERSION >= 3
            es = PyBytes_AS_STRING(obj);
#else
            es = PyString_AS_STRING(obj);
#endif
        }
    }
#if PY_MAJOR_VERSION >= 3
    else if (PyBytes_Check(obj))
    {
        es = PyBytes_AS_STRING(obj);
        Py_INCREF(obj);
    }
#else
    else if (PyString_Check(obj))
    {
        es = PyString_AS_STRING(obj);
        Py_INCREF(obj);
    }
#endif
    else if (PyObject_AsCharBuffer(obj, &es, &sz) >= 0)
    {
        Py_INCREF(obj);
    }

    if (es)
    {
        *s = obj;
    }
    else
    {
        PyErr_Format(PyExc_UnicodeEncodeError,
                "unable to convert '%s' to requested encoding",
                Py_TYPE(*s)->tp_name);
    }

    return es;
}
