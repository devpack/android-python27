/*
 * Interface wrapper code.
 *
 * Generated by SIP 4.11.2 on Thu Jul 12 20:04:00 2012
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

#include "sipAPIQtXmlPatterns.h"

#line 91 "/home/tsheasha/GUC/Bachelors/android-python27/python-build/PyQt-x11-gpl-4.8/sip/QtXmlPatterns/qabstractxmlnodemodel.sip"
#include <qabstractxmlnodemodel.h>
#line 39 "sipQtXmlPatternsQAbstractXmlNodeModel.cpp"

#line 38 "/home/tsheasha/GUC/Bachelors/android-python27/python-build/PyQt-x11-gpl-4.8/sip/QtXmlPatterns/qabstractxmlnodemodel.sip"
#include <qabstractxmlnodemodel.h>
#line 43 "sipQtXmlPatternsQAbstractXmlNodeModel.cpp"
#line 38 "/home/tsheasha/GUC/Bachelors/android-python27/python-build/PyQt-x11-gpl-4.8/sip/QtCore/qvector.sip"
#include <qvector.h>
#line 46 "sipQtXmlPatternsQAbstractXmlNodeModel.cpp"
#line 38 "/home/tsheasha/GUC/Bachelors/android-python27/python-build/PyQt-x11-gpl-4.8/sip/QtXmlPatterns/qsourcelocation.sip"
#include <qsourcelocation.h>
#line 49 "sipQtXmlPatternsQAbstractXmlNodeModel.cpp"
#line 38 "/home/tsheasha/GUC/Bachelors/android-python27/python-build/PyQt-x11-gpl-4.8/sip/QtXmlPatterns/qxmlname.sip"
#include <qxmlname.h>
#line 52 "sipQtXmlPatternsQAbstractXmlNodeModel.cpp"
#line 38 "/home/tsheasha/GUC/Bachelors/android-python27/python-build/PyQt-x11-gpl-4.8/sip/QtCore/qvector.sip"
#include <qvector.h>
#line 55 "sipQtXmlPatternsQAbstractXmlNodeModel.cpp"
#line 41 "/home/tsheasha/GUC/Bachelors/android-python27/python-build/PyQt-x11-gpl-4.8/sip/QtCore/qvariant.sip"
#include <qvariant.h>
#line 58 "sipQtXmlPatternsQAbstractXmlNodeModel.cpp"
#line 41 "/home/tsheasha/GUC/Bachelors/android-python27/python-build/PyQt-x11-gpl-4.8/sip/QtCore/qstring.sip"
#include <qstring.h>
#line 61 "sipQtXmlPatternsQAbstractXmlNodeModel.cpp"
#line 40 "/home/tsheasha/GUC/Bachelors/android-python27/python-build/PyQt-x11-gpl-4.8/sip/QtCore/qurl.sip"
#include <qurl.h>
#line 64 "sipQtXmlPatternsQAbstractXmlNodeModel.cpp"


class sipQAbstractXmlNodeModel : public QAbstractXmlNodeModel
{
public:
    sipQAbstractXmlNodeModel();
    virtual ~sipQAbstractXmlNodeModel();

    /*
     * There is a public method for every protected method visible from
     * this class.
     */
    QXmlNodeModelIndex sipProtect_nextFromSimpleAxis(QAbstractXmlNodeModel::SimpleAxis,const QXmlNodeModelIndex&) const;
    QVector<QXmlNodeModelIndex> sipProtect_attributes(const QXmlNodeModelIndex&) const;
    QXmlNodeModelIndex sipProtect_createIndex(qint64) const;
    QXmlNodeModelIndex sipProtect_createIndex(qint64,qint64) const;
    QXmlNodeModelIndex sipProtect_createIndex(void *,qint64) const;

    /*
     * There is a protected method for every virtual method visible from
     * this class.
     */
protected:
    QUrl baseUri(const QXmlNodeModelIndex&) const;
    QUrl documentUri(const QXmlNodeModelIndex&) const;
    QXmlNodeModelIndex::NodeKind kind(const QXmlNodeModelIndex&) const;
    QXmlNodeModelIndex::DocumentOrder compareOrder(const QXmlNodeModelIndex&,const QXmlNodeModelIndex&) const;
    QXmlNodeModelIndex root(const QXmlNodeModelIndex&) const;
    QXmlName name(const QXmlNodeModelIndex&) const;
    QString stringValue(const QXmlNodeModelIndex&) const;
    QVariant typedValue(const QXmlNodeModelIndex&) const;
    QVector<QXmlName> namespaceBindings(const QXmlNodeModelIndex&) const;
    QXmlNodeModelIndex elementById(const QXmlName&) const;
    QVector<QXmlNodeModelIndex> nodesByIdref(const QXmlName&) const;
    QXmlNodeModelIndex nextFromSimpleAxis(QAbstractXmlNodeModel::SimpleAxis,const QXmlNodeModelIndex&) const;
    QVector<QXmlNodeModelIndex> attributes(const QXmlNodeModelIndex&) const;

public:
    sipSimpleWrapper *sipPySelf;

private:
    sipQAbstractXmlNodeModel(const sipQAbstractXmlNodeModel &);
    sipQAbstractXmlNodeModel &operator = (const sipQAbstractXmlNodeModel &);

    char sipPyMethods[13];
};

sipQAbstractXmlNodeModel::sipQAbstractXmlNodeModel(): QAbstractXmlNodeModel(), sipPySelf(0)
{
    memset(sipPyMethods, 0, sizeof (sipPyMethods));
}

sipQAbstractXmlNodeModel::~sipQAbstractXmlNodeModel()
{
    sipCommonDtor(sipPySelf);
}

QUrl sipQAbstractXmlNodeModel::baseUri(const QXmlNodeModelIndex& a0) const
{
    sip_gilstate_t sipGILState;
    PyObject *meth;

    meth = sipIsPyMethod(&sipGILState,const_cast<char *>(&sipPyMethods[0]),sipPySelf,sipName_QAbstractXmlNodeModel,sipName_baseUri);

    if (!meth)
        return QUrl();

    extern QUrl sipVH_QtXmlPatterns_8(sip_gilstate_t,PyObject *,const QXmlNodeModelIndex&);

    return sipVH_QtXmlPatterns_8(sipGILState,meth,a0);
}

QUrl sipQAbstractXmlNodeModel::documentUri(const QXmlNodeModelIndex& a0) const
{
    sip_gilstate_t sipGILState;
    PyObject *meth;

    meth = sipIsPyMethod(&sipGILState,const_cast<char *>(&sipPyMethods[1]),sipPySelf,sipName_QAbstractXmlNodeModel,sipName_documentUri);

    if (!meth)
        return QUrl();

    extern QUrl sipVH_QtXmlPatterns_8(sip_gilstate_t,PyObject *,const QXmlNodeModelIndex&);

    return sipVH_QtXmlPatterns_8(sipGILState,meth,a0);
}

QXmlNodeModelIndex::NodeKind sipQAbstractXmlNodeModel::kind(const QXmlNodeModelIndex& a0) const
{
    sip_gilstate_t sipGILState;
    PyObject *meth;

    meth = sipIsPyMethod(&sipGILState,const_cast<char *>(&sipPyMethods[2]),sipPySelf,sipName_QAbstractXmlNodeModel,sipName_kind);

    if (!meth)
        return (QXmlNodeModelIndex::NodeKind)0;

    extern QXmlNodeModelIndex::NodeKind sipVH_QtXmlPatterns_15(sip_gilstate_t,PyObject *,const QXmlNodeModelIndex&);

    return sipVH_QtXmlPatterns_15(sipGILState,meth,a0);
}

QXmlNodeModelIndex::DocumentOrder sipQAbstractXmlNodeModel::compareOrder(const QXmlNodeModelIndex& a0,const QXmlNodeModelIndex& a1) const
{
    sip_gilstate_t sipGILState;
    PyObject *meth;

    meth = sipIsPyMethod(&sipGILState,const_cast<char *>(&sipPyMethods[3]),sipPySelf,sipName_QAbstractXmlNodeModel,sipName_compareOrder);

    if (!meth)
        return (QXmlNodeModelIndex::DocumentOrder)0;

    extern QXmlNodeModelIndex::DocumentOrder sipVH_QtXmlPatterns_14(sip_gilstate_t,PyObject *,const QXmlNodeModelIndex&,const QXmlNodeModelIndex&);

    return sipVH_QtXmlPatterns_14(sipGILState,meth,a0,a1);
}

QXmlNodeModelIndex sipQAbstractXmlNodeModel::root(const QXmlNodeModelIndex& a0) const
{
    sip_gilstate_t sipGILState;
    PyObject *meth;

    meth = sipIsPyMethod(&sipGILState,const_cast<char *>(&sipPyMethods[4]),sipPySelf,sipName_QAbstractXmlNodeModel,sipName_root);

    if (!meth)
        return QXmlNodeModelIndex();

    extern QXmlNodeModelIndex sipVH_QtXmlPatterns_13(sip_gilstate_t,PyObject *,const QXmlNodeModelIndex&);

    return sipVH_QtXmlPatterns_13(sipGILState,meth,a0);
}

QXmlName sipQAbstractXmlNodeModel::name(const QXmlNodeModelIndex& a0) const
{
    sip_gilstate_t sipGILState;
    PyObject *meth;

    meth = sipIsPyMethod(&sipGILState,const_cast<char *>(&sipPyMethods[5]),sipPySelf,sipName_QAbstractXmlNodeModel,sipName_name);

    if (!meth)
        return QXmlName();

    extern QXmlName sipVH_QtXmlPatterns_12(sip_gilstate_t,PyObject *,const QXmlNodeModelIndex&);

    return sipVH_QtXmlPatterns_12(sipGILState,meth,a0);
}

QString sipQAbstractXmlNodeModel::stringValue(const QXmlNodeModelIndex& a0) const
{
    sip_gilstate_t sipGILState;
    PyObject *meth;

    meth = sipIsPyMethod(&sipGILState,const_cast<char *>(&sipPyMethods[6]),sipPySelf,sipName_QAbstractXmlNodeModel,sipName_stringValue);

    if (!meth)
        return QString();

    extern QString sipVH_QtXmlPatterns_6(sip_gilstate_t,PyObject *,const QXmlNodeModelIndex&);

    return sipVH_QtXmlPatterns_6(sipGILState,meth,a0);
}

QVariant sipQAbstractXmlNodeModel::typedValue(const QXmlNodeModelIndex& a0) const
{
    sip_gilstate_t sipGILState;
    PyObject *meth;

    meth = sipIsPyMethod(&sipGILState,const_cast<char *>(&sipPyMethods[7]),sipPySelf,sipName_QAbstractXmlNodeModel,sipName_typedValue);

    if (!meth)
        return QVariant();

    extern QVariant sipVH_QtXmlPatterns_11(sip_gilstate_t,PyObject *,const QXmlNodeModelIndex&);

    return sipVH_QtXmlPatterns_11(sipGILState,meth,a0);
}

QVector<QXmlName> sipQAbstractXmlNodeModel::namespaceBindings(const QXmlNodeModelIndex& a0) const
{
    sip_gilstate_t sipGILState;
    PyObject *meth;

    meth = sipIsPyMethod(&sipGILState,const_cast<char *>(&sipPyMethods[8]),sipPySelf,sipName_QAbstractXmlNodeModel,sipName_namespaceBindings);

    if (!meth)
        return QVector<QXmlName>();

    extern QVector<QXmlName> sipVH_QtXmlPatterns_7(sip_gilstate_t,PyObject *,const QXmlNodeModelIndex&);

    return sipVH_QtXmlPatterns_7(sipGILState,meth,a0);
}

QXmlNodeModelIndex sipQAbstractXmlNodeModel::elementById(const QXmlName& a0) const
{
    sip_gilstate_t sipGILState;
    PyObject *meth;

    meth = sipIsPyMethod(&sipGILState,const_cast<char *>(&sipPyMethods[9]),sipPySelf,sipName_QAbstractXmlNodeModel,sipName_elementById);

    if (!meth)
        return QXmlNodeModelIndex();

    extern QXmlNodeModelIndex sipVH_QtXmlPatterns_5(sip_gilstate_t,PyObject *,const QXmlName&);

    return sipVH_QtXmlPatterns_5(sipGILState,meth,a0);
}

QVector<QXmlNodeModelIndex> sipQAbstractXmlNodeModel::nodesByIdref(const QXmlName& a0) const
{
    sip_gilstate_t sipGILState;
    PyObject *meth;

    meth = sipIsPyMethod(&sipGILState,const_cast<char *>(&sipPyMethods[10]),sipPySelf,sipName_QAbstractXmlNodeModel,sipName_nodesByIdref);

    if (!meth)
        return QVector<QXmlNodeModelIndex>();

    extern QVector<QXmlNodeModelIndex> sipVH_QtXmlPatterns_4(sip_gilstate_t,PyObject *,const QXmlName&);

    return sipVH_QtXmlPatterns_4(sipGILState,meth,a0);
}

QXmlNodeModelIndex sipQAbstractXmlNodeModel::nextFromSimpleAxis(QAbstractXmlNodeModel::SimpleAxis a0,const QXmlNodeModelIndex& a1) const
{
    sip_gilstate_t sipGILState;
    PyObject *meth;

    meth = sipIsPyMethod(&sipGILState,const_cast<char *>(&sipPyMethods[11]),sipPySelf,sipName_QAbstractXmlNodeModel,sipName_nextFromSimpleAxis);

    if (!meth)
        return QXmlNodeModelIndex();

    extern QXmlNodeModelIndex sipVH_QtXmlPatterns_10(sip_gilstate_t,PyObject *,QAbstractXmlNodeModel::SimpleAxis,const QXmlNodeModelIndex&);

    return sipVH_QtXmlPatterns_10(sipGILState,meth,a0,a1);
}

QVector<QXmlNodeModelIndex> sipQAbstractXmlNodeModel::attributes(const QXmlNodeModelIndex& a0) const
{
    sip_gilstate_t sipGILState;
    PyObject *meth;

    meth = sipIsPyMethod(&sipGILState,const_cast<char *>(&sipPyMethods[12]),sipPySelf,sipName_QAbstractXmlNodeModel,sipName_attributes);

    if (!meth)
        return QVector<QXmlNodeModelIndex>();

    extern QVector<QXmlNodeModelIndex> sipVH_QtXmlPatterns_9(sip_gilstate_t,PyObject *,const QXmlNodeModelIndex&);

    return sipVH_QtXmlPatterns_9(sipGILState,meth,a0);
}

QXmlNodeModelIndex sipQAbstractXmlNodeModel::sipProtect_nextFromSimpleAxis(QAbstractXmlNodeModel::SimpleAxis a0,const QXmlNodeModelIndex& a1) const
{
    return nextFromSimpleAxis(a0,a1);
}

QVector<QXmlNodeModelIndex> sipQAbstractXmlNodeModel::sipProtect_attributes(const QXmlNodeModelIndex& a0) const
{
    return attributes(a0);
}

QXmlNodeModelIndex sipQAbstractXmlNodeModel::sipProtect_createIndex(qint64 a0) const
{
    return QAbstractXmlNodeModel::createIndex(a0);
}

QXmlNodeModelIndex sipQAbstractXmlNodeModel::sipProtect_createIndex(qint64 a0,qint64 a1) const
{
    return QAbstractXmlNodeModel::createIndex(a0,a1);
}

QXmlNodeModelIndex sipQAbstractXmlNodeModel::sipProtect_createIndex(void *a0,qint64 a1) const
{
    return QAbstractXmlNodeModel::createIndex(a0,a1);
}


extern "C" {static PyObject *meth_QAbstractXmlNodeModel_baseUri(PyObject *, PyObject *);}
static PyObject *meth_QAbstractXmlNodeModel_baseUri(PyObject *sipSelf, PyObject *sipArgs)
{
    PyObject *sipParseErr = NULL;
    PyObject *sipOrigSelf = sipSelf;

    {
        const QXmlNodeModelIndex * a0;
        QAbstractXmlNodeModel *sipCpp;

        if (sipParseArgs(&sipParseErr, sipArgs, "BJ9", &sipSelf, sipType_QAbstractXmlNodeModel, &sipCpp, sipType_QXmlNodeModelIndex, &a0))
        {
            QUrl *sipRes;

            if (!sipOrigSelf)
            {
                sipAbstractMethod(sipName_QAbstractXmlNodeModel, sipName_baseUri);
                return NULL;
            }

            Py_BEGIN_ALLOW_THREADS
            sipRes = new QUrl(sipCpp->baseUri(*a0));
            Py_END_ALLOW_THREADS

            return sipConvertFromNewType(sipRes,sipType_QUrl,NULL);
        }
    }

    /* Raise an exception if the arguments couldn't be parsed. */
    sipNoMethod(sipParseErr, sipName_QAbstractXmlNodeModel, sipName_baseUri, NULL);

    return NULL;
}


extern "C" {static PyObject *meth_QAbstractXmlNodeModel_documentUri(PyObject *, PyObject *);}
static PyObject *meth_QAbstractXmlNodeModel_documentUri(PyObject *sipSelf, PyObject *sipArgs)
{
    PyObject *sipParseErr = NULL;
    PyObject *sipOrigSelf = sipSelf;

    {
        const QXmlNodeModelIndex * a0;
        QAbstractXmlNodeModel *sipCpp;

        if (sipParseArgs(&sipParseErr, sipArgs, "BJ9", &sipSelf, sipType_QAbstractXmlNodeModel, &sipCpp, sipType_QXmlNodeModelIndex, &a0))
        {
            QUrl *sipRes;

            if (!sipOrigSelf)
            {
                sipAbstractMethod(sipName_QAbstractXmlNodeModel, sipName_documentUri);
                return NULL;
            }

            Py_BEGIN_ALLOW_THREADS
            sipRes = new QUrl(sipCpp->documentUri(*a0));
            Py_END_ALLOW_THREADS

            return sipConvertFromNewType(sipRes,sipType_QUrl,NULL);
        }
    }

    /* Raise an exception if the arguments couldn't be parsed. */
    sipNoMethod(sipParseErr, sipName_QAbstractXmlNodeModel, sipName_documentUri, NULL);

    return NULL;
}


extern "C" {static PyObject *meth_QAbstractXmlNodeModel_kind(PyObject *, PyObject *);}
static PyObject *meth_QAbstractXmlNodeModel_kind(PyObject *sipSelf, PyObject *sipArgs)
{
    PyObject *sipParseErr = NULL;
    PyObject *sipOrigSelf = sipSelf;

    {
        const QXmlNodeModelIndex * a0;
        QAbstractXmlNodeModel *sipCpp;

        if (sipParseArgs(&sipParseErr, sipArgs, "BJ9", &sipSelf, sipType_QAbstractXmlNodeModel, &sipCpp, sipType_QXmlNodeModelIndex, &a0))
        {
            QXmlNodeModelIndex::NodeKind sipRes;

            if (!sipOrigSelf)
            {
                sipAbstractMethod(sipName_QAbstractXmlNodeModel, sipName_kind);
                return NULL;
            }

            Py_BEGIN_ALLOW_THREADS
            sipRes = sipCpp->kind(*a0);
            Py_END_ALLOW_THREADS

            return sipConvertFromEnum(sipRes,sipType_QXmlNodeModelIndex_NodeKind);
        }
    }

    /* Raise an exception if the arguments couldn't be parsed. */
    sipNoMethod(sipParseErr, sipName_QAbstractXmlNodeModel, sipName_kind, NULL);

    return NULL;
}


extern "C" {static PyObject *meth_QAbstractXmlNodeModel_compareOrder(PyObject *, PyObject *);}
static PyObject *meth_QAbstractXmlNodeModel_compareOrder(PyObject *sipSelf, PyObject *sipArgs)
{
    PyObject *sipParseErr = NULL;
    PyObject *sipOrigSelf = sipSelf;

    {
        const QXmlNodeModelIndex * a0;
        const QXmlNodeModelIndex * a1;
        QAbstractXmlNodeModel *sipCpp;

        if (sipParseArgs(&sipParseErr, sipArgs, "BJ9J9", &sipSelf, sipType_QAbstractXmlNodeModel, &sipCpp, sipType_QXmlNodeModelIndex, &a0, sipType_QXmlNodeModelIndex, &a1))
        {
            QXmlNodeModelIndex::DocumentOrder sipRes;

            if (!sipOrigSelf)
            {
                sipAbstractMethod(sipName_QAbstractXmlNodeModel, sipName_compareOrder);
                return NULL;
            }

            Py_BEGIN_ALLOW_THREADS
            sipRes = sipCpp->compareOrder(*a0,*a1);
            Py_END_ALLOW_THREADS

            return sipConvertFromEnum(sipRes,sipType_QXmlNodeModelIndex_DocumentOrder);
        }
    }

    /* Raise an exception if the arguments couldn't be parsed. */
    sipNoMethod(sipParseErr, sipName_QAbstractXmlNodeModel, sipName_compareOrder, NULL);

    return NULL;
}


extern "C" {static PyObject *meth_QAbstractXmlNodeModel_root(PyObject *, PyObject *);}
static PyObject *meth_QAbstractXmlNodeModel_root(PyObject *sipSelf, PyObject *sipArgs)
{
    PyObject *sipParseErr = NULL;
    PyObject *sipOrigSelf = sipSelf;

    {
        const QXmlNodeModelIndex * a0;
        QAbstractXmlNodeModel *sipCpp;

        if (sipParseArgs(&sipParseErr, sipArgs, "BJ9", &sipSelf, sipType_QAbstractXmlNodeModel, &sipCpp, sipType_QXmlNodeModelIndex, &a0))
        {
            QXmlNodeModelIndex *sipRes;

            if (!sipOrigSelf)
            {
                sipAbstractMethod(sipName_QAbstractXmlNodeModel, sipName_root);
                return NULL;
            }

            Py_BEGIN_ALLOW_THREADS
            sipRes = new QXmlNodeModelIndex(sipCpp->root(*a0));
            Py_END_ALLOW_THREADS

            return sipConvertFromNewType(sipRes,sipType_QXmlNodeModelIndex,NULL);
        }
    }

    /* Raise an exception if the arguments couldn't be parsed. */
    sipNoMethod(sipParseErr, sipName_QAbstractXmlNodeModel, sipName_root, NULL);

    return NULL;
}


extern "C" {static PyObject *meth_QAbstractXmlNodeModel_name(PyObject *, PyObject *);}
static PyObject *meth_QAbstractXmlNodeModel_name(PyObject *sipSelf, PyObject *sipArgs)
{
    PyObject *sipParseErr = NULL;
    PyObject *sipOrigSelf = sipSelf;

    {
        const QXmlNodeModelIndex * a0;
        QAbstractXmlNodeModel *sipCpp;

        if (sipParseArgs(&sipParseErr, sipArgs, "BJ9", &sipSelf, sipType_QAbstractXmlNodeModel, &sipCpp, sipType_QXmlNodeModelIndex, &a0))
        {
            QXmlName *sipRes;

            if (!sipOrigSelf)
            {
                sipAbstractMethod(sipName_QAbstractXmlNodeModel, sipName_name);
                return NULL;
            }

            Py_BEGIN_ALLOW_THREADS
            sipRes = new QXmlName(sipCpp->name(*a0));
            Py_END_ALLOW_THREADS

            return sipConvertFromNewType(sipRes,sipType_QXmlName,NULL);
        }
    }

    /* Raise an exception if the arguments couldn't be parsed. */
    sipNoMethod(sipParseErr, sipName_QAbstractXmlNodeModel, sipName_name, NULL);

    return NULL;
}


extern "C" {static PyObject *meth_QAbstractXmlNodeModel_stringValue(PyObject *, PyObject *);}
static PyObject *meth_QAbstractXmlNodeModel_stringValue(PyObject *sipSelf, PyObject *sipArgs)
{
    PyObject *sipParseErr = NULL;
    PyObject *sipOrigSelf = sipSelf;

    {
        const QXmlNodeModelIndex * a0;
        QAbstractXmlNodeModel *sipCpp;

        if (sipParseArgs(&sipParseErr, sipArgs, "BJ9", &sipSelf, sipType_QAbstractXmlNodeModel, &sipCpp, sipType_QXmlNodeModelIndex, &a0))
        {
            QString *sipRes;

            if (!sipOrigSelf)
            {
                sipAbstractMethod(sipName_QAbstractXmlNodeModel, sipName_stringValue);
                return NULL;
            }

            Py_BEGIN_ALLOW_THREADS
            sipRes = new QString(sipCpp->stringValue(*a0));
            Py_END_ALLOW_THREADS

            return sipConvertFromNewType(sipRes,sipType_QString,NULL);
        }
    }

    /* Raise an exception if the arguments couldn't be parsed. */
    sipNoMethod(sipParseErr, sipName_QAbstractXmlNodeModel, sipName_stringValue, NULL);

    return NULL;
}


extern "C" {static PyObject *meth_QAbstractXmlNodeModel_typedValue(PyObject *, PyObject *);}
static PyObject *meth_QAbstractXmlNodeModel_typedValue(PyObject *sipSelf, PyObject *sipArgs)
{
    PyObject *sipParseErr = NULL;
    PyObject *sipOrigSelf = sipSelf;

    {
        const QXmlNodeModelIndex * a0;
        QAbstractXmlNodeModel *sipCpp;

        if (sipParseArgs(&sipParseErr, sipArgs, "BJ9", &sipSelf, sipType_QAbstractXmlNodeModel, &sipCpp, sipType_QXmlNodeModelIndex, &a0))
        {
            QVariant *sipRes;

            if (!sipOrigSelf)
            {
                sipAbstractMethod(sipName_QAbstractXmlNodeModel, sipName_typedValue);
                return NULL;
            }

            Py_BEGIN_ALLOW_THREADS
            sipRes = new QVariant(sipCpp->typedValue(*a0));
            Py_END_ALLOW_THREADS

            return sipConvertFromNewType(sipRes,sipType_QVariant,NULL);
        }
    }

    /* Raise an exception if the arguments couldn't be parsed. */
    sipNoMethod(sipParseErr, sipName_QAbstractXmlNodeModel, sipName_typedValue, NULL);

    return NULL;
}


extern "C" {static PyObject *meth_QAbstractXmlNodeModel_namespaceBindings(PyObject *, PyObject *);}
static PyObject *meth_QAbstractXmlNodeModel_namespaceBindings(PyObject *sipSelf, PyObject *sipArgs)
{
    PyObject *sipParseErr = NULL;
    PyObject *sipOrigSelf = sipSelf;

    {
        const QXmlNodeModelIndex * a0;
        QAbstractXmlNodeModel *sipCpp;

        if (sipParseArgs(&sipParseErr, sipArgs, "BJ9", &sipSelf, sipType_QAbstractXmlNodeModel, &sipCpp, sipType_QXmlNodeModelIndex, &a0))
        {
            QVector<QXmlName> *sipRes;

            if (!sipOrigSelf)
            {
                sipAbstractMethod(sipName_QAbstractXmlNodeModel, sipName_namespaceBindings);
                return NULL;
            }

            Py_BEGIN_ALLOW_THREADS
            sipRes = new QVector<QXmlName>(sipCpp->namespaceBindings(*a0));
            Py_END_ALLOW_THREADS

            return sipConvertFromNewType(sipRes,sipType_QVector_0100QXmlName,NULL);
        }
    }

    /* Raise an exception if the arguments couldn't be parsed. */
    sipNoMethod(sipParseErr, sipName_QAbstractXmlNodeModel, sipName_namespaceBindings, NULL);

    return NULL;
}


extern "C" {static PyObject *meth_QAbstractXmlNodeModel_elementById(PyObject *, PyObject *);}
static PyObject *meth_QAbstractXmlNodeModel_elementById(PyObject *sipSelf, PyObject *sipArgs)
{
    PyObject *sipParseErr = NULL;
    PyObject *sipOrigSelf = sipSelf;

    {
        const QXmlName * a0;
        QAbstractXmlNodeModel *sipCpp;

        if (sipParseArgs(&sipParseErr, sipArgs, "BJ9", &sipSelf, sipType_QAbstractXmlNodeModel, &sipCpp, sipType_QXmlName, &a0))
        {
            QXmlNodeModelIndex *sipRes;

            if (!sipOrigSelf)
            {
                sipAbstractMethod(sipName_QAbstractXmlNodeModel, sipName_elementById);
                return NULL;
            }

            Py_BEGIN_ALLOW_THREADS
            sipRes = new QXmlNodeModelIndex(sipCpp->elementById(*a0));
            Py_END_ALLOW_THREADS

            return sipConvertFromNewType(sipRes,sipType_QXmlNodeModelIndex,NULL);
        }
    }

    /* Raise an exception if the arguments couldn't be parsed. */
    sipNoMethod(sipParseErr, sipName_QAbstractXmlNodeModel, sipName_elementById, NULL);

    return NULL;
}


extern "C" {static PyObject *meth_QAbstractXmlNodeModel_nodesByIdref(PyObject *, PyObject *);}
static PyObject *meth_QAbstractXmlNodeModel_nodesByIdref(PyObject *sipSelf, PyObject *sipArgs)
{
    PyObject *sipParseErr = NULL;
    PyObject *sipOrigSelf = sipSelf;

    {
        const QXmlName * a0;
        QAbstractXmlNodeModel *sipCpp;

        if (sipParseArgs(&sipParseErr, sipArgs, "BJ9", &sipSelf, sipType_QAbstractXmlNodeModel, &sipCpp, sipType_QXmlName, &a0))
        {
            QVector<QXmlNodeModelIndex> *sipRes;

            if (!sipOrigSelf)
            {
                sipAbstractMethod(sipName_QAbstractXmlNodeModel, sipName_nodesByIdref);
                return NULL;
            }

            Py_BEGIN_ALLOW_THREADS
            sipRes = new QVector<QXmlNodeModelIndex>(sipCpp->nodesByIdref(*a0));
            Py_END_ALLOW_THREADS

            return sipConvertFromNewType(sipRes,sipType_QVector_0100QXmlNodeModelIndex,NULL);
        }
    }

    /* Raise an exception if the arguments couldn't be parsed. */
    sipNoMethod(sipParseErr, sipName_QAbstractXmlNodeModel, sipName_nodesByIdref, NULL);

    return NULL;
}


extern "C" {static PyObject *meth_QAbstractXmlNodeModel_sourceLocation(PyObject *, PyObject *);}
static PyObject *meth_QAbstractXmlNodeModel_sourceLocation(PyObject *sipSelf, PyObject *sipArgs)
{
    PyObject *sipParseErr = NULL;

    {
        const QXmlNodeModelIndex * a0;
        QAbstractXmlNodeModel *sipCpp;

        if (sipParseArgs(&sipParseErr, sipArgs, "BJ9", &sipSelf, sipType_QAbstractXmlNodeModel, &sipCpp, sipType_QXmlNodeModelIndex, &a0))
        {
            QSourceLocation *sipRes;

            Py_BEGIN_ALLOW_THREADS
            sipRes = new QSourceLocation(sipCpp->sourceLocation(*a0));
            Py_END_ALLOW_THREADS

            return sipConvertFromNewType(sipRes,sipType_QSourceLocation,NULL);
        }
    }

    /* Raise an exception if the arguments couldn't be parsed. */
    sipNoMethod(sipParseErr, sipName_QAbstractXmlNodeModel, sipName_sourceLocation, NULL);

    return NULL;
}


extern "C" {static PyObject *meth_QAbstractXmlNodeModel_nextFromSimpleAxis(PyObject *, PyObject *);}
static PyObject *meth_QAbstractXmlNodeModel_nextFromSimpleAxis(PyObject *sipSelf, PyObject *sipArgs)
{
    PyObject *sipParseErr = NULL;
    PyObject *sipOrigSelf = sipSelf;

    {
        QAbstractXmlNodeModel::SimpleAxis a0;
        const QXmlNodeModelIndex * a1;
        sipQAbstractXmlNodeModel *sipCpp;

        if (sipParseArgs(&sipParseErr, sipArgs, "BEJ9", &sipSelf, sipType_QAbstractXmlNodeModel, &sipCpp, sipType_QAbstractXmlNodeModel_SimpleAxis, &a0, sipType_QXmlNodeModelIndex, &a1))
        {
            QXmlNodeModelIndex *sipRes;

            if (!sipOrigSelf)
            {
                sipAbstractMethod(sipName_QAbstractXmlNodeModel, sipName_nextFromSimpleAxis);
                return NULL;
            }

            Py_BEGIN_ALLOW_THREADS
            sipRes = new QXmlNodeModelIndex(sipCpp->sipProtect_nextFromSimpleAxis(a0,*a1));
            Py_END_ALLOW_THREADS

            return sipConvertFromNewType(sipRes,sipType_QXmlNodeModelIndex,NULL);
        }
    }

    /* Raise an exception if the arguments couldn't be parsed. */
    sipNoMethod(sipParseErr, sipName_QAbstractXmlNodeModel, sipName_nextFromSimpleAxis, NULL);

    return NULL;
}


extern "C" {static PyObject *meth_QAbstractXmlNodeModel_attributes(PyObject *, PyObject *);}
static PyObject *meth_QAbstractXmlNodeModel_attributes(PyObject *sipSelf, PyObject *sipArgs)
{
    PyObject *sipParseErr = NULL;
    PyObject *sipOrigSelf = sipSelf;

    {
        const QXmlNodeModelIndex * a0;
        sipQAbstractXmlNodeModel *sipCpp;

        if (sipParseArgs(&sipParseErr, sipArgs, "BJ9", &sipSelf, sipType_QAbstractXmlNodeModel, &sipCpp, sipType_QXmlNodeModelIndex, &a0))
        {
            QVector<QXmlNodeModelIndex> *sipRes;

            if (!sipOrigSelf)
            {
                sipAbstractMethod(sipName_QAbstractXmlNodeModel, sipName_attributes);
                return NULL;
            }

            Py_BEGIN_ALLOW_THREADS
            sipRes = new QVector<QXmlNodeModelIndex>(sipCpp->sipProtect_attributes(*a0));
            Py_END_ALLOW_THREADS

            return sipConvertFromNewType(sipRes,sipType_QVector_0100QXmlNodeModelIndex,NULL);
        }
    }

    /* Raise an exception if the arguments couldn't be parsed. */
    sipNoMethod(sipParseErr, sipName_QAbstractXmlNodeModel, sipName_attributes, NULL);

    return NULL;
}


extern "C" {static PyObject *meth_QAbstractXmlNodeModel_createIndex(PyObject *, PyObject *, PyObject *);}
static PyObject *meth_QAbstractXmlNodeModel_createIndex(PyObject *sipSelf, PyObject *sipArgs, PyObject *sipKwds)
{
    PyObject *sipParseErr = NULL;

    {
        qint64 a0;
        sipQAbstractXmlNodeModel *sipCpp;

        if (sipParseKwdArgs(&sipParseErr, sipArgs, sipKwds, NULL, NULL, "Bn", &sipSelf, sipType_QAbstractXmlNodeModel, &sipCpp, &a0))
        {
            QXmlNodeModelIndex *sipRes;

            Py_BEGIN_ALLOW_THREADS
            sipRes = new QXmlNodeModelIndex(sipCpp->sipProtect_createIndex(a0));
            Py_END_ALLOW_THREADS

            return sipConvertFromNewType(sipRes,sipType_QXmlNodeModelIndex,NULL);
        }
    }

    {
        qint64 a0;
        qint64 a1;
        sipQAbstractXmlNodeModel *sipCpp;

        if (sipParseKwdArgs(&sipParseErr, sipArgs, sipKwds, NULL, NULL, "Bnn", &sipSelf, sipType_QAbstractXmlNodeModel, &sipCpp, &a0, &a1))
        {
            QXmlNodeModelIndex *sipRes;

            Py_BEGIN_ALLOW_THREADS
            sipRes = new QXmlNodeModelIndex(sipCpp->sipProtect_createIndex(a0,a1));
            Py_END_ALLOW_THREADS

            return sipConvertFromNewType(sipRes,sipType_QXmlNodeModelIndex,NULL);
        }
    }

    {
        PyObject * a0;
        qint64 a1 = 0;
        sipQAbstractXmlNodeModel *sipCpp;

        static const char *sipKwdList[] = {
            NULL,
            sipName_additionalData,
        };

        if (sipParseKwdArgs(&sipParseErr, sipArgs, sipKwds, sipKwdList, NULL, "BP0|n", &sipSelf, sipType_QAbstractXmlNodeModel, &sipCpp, &a0, &a1))
        {
            QXmlNodeModelIndex *sipRes;

            Py_BEGIN_ALLOW_THREADS
            sipRes = new QXmlNodeModelIndex(sipCpp->sipProtect_createIndex(a0,a1));
            Py_END_ALLOW_THREADS

            return sipConvertFromNewType(sipRes,sipType_QXmlNodeModelIndex,NULL);
        }
    }

    /* Raise an exception if the arguments couldn't be parsed. */
    sipNoMethod(sipParseErr, sipName_QAbstractXmlNodeModel, sipName_createIndex, NULL);

    return NULL;
}


/* Cast a pointer to a type somewhere in its superclass hierarchy. */
extern "C" {static void *cast_QAbstractXmlNodeModel(void *, const sipTypeDef *);}
static void *cast_QAbstractXmlNodeModel(void *ptr, const sipTypeDef *targetType)
{
    if (targetType == sipType_QAbstractXmlNodeModel)
        return ptr;

    return NULL;
}


/* Call the instance's destructor. */
extern "C" {static void release_QAbstractXmlNodeModel(void *, int);}
static void release_QAbstractXmlNodeModel(void *sipCppV,int sipState)
{
    Py_BEGIN_ALLOW_THREADS

    if (sipState & SIP_DERIVED_CLASS)
        delete reinterpret_cast<sipQAbstractXmlNodeModel *>(sipCppV);
    else
        delete reinterpret_cast<QAbstractXmlNodeModel *>(sipCppV);

    Py_END_ALLOW_THREADS
}


extern "C" {static void dealloc_QAbstractXmlNodeModel(sipSimpleWrapper *);}
static void dealloc_QAbstractXmlNodeModel(sipSimpleWrapper *sipSelf)
{
    if (sipIsDerived(sipSelf))
        reinterpret_cast<sipQAbstractXmlNodeModel *>(sipGetAddress(sipSelf))->sipPySelf = NULL;

    if (sipIsPyOwned(sipSelf))
    {
        release_QAbstractXmlNodeModel(sipGetAddress(sipSelf),sipSelf->flags);
    }
}


extern "C" {static void *init_QAbstractXmlNodeModel(sipSimpleWrapper *, PyObject *, PyObject *, PyObject **, PyObject **, PyObject **);}
static void *init_QAbstractXmlNodeModel(sipSimpleWrapper *sipSelf, PyObject *sipArgs, PyObject *sipKwds, PyObject **sipUnused, PyObject **, PyObject **sipParseErr)
{
    sipQAbstractXmlNodeModel *sipCpp = 0;

    {
        if (sipParseKwdArgs(sipParseErr, sipArgs, sipKwds, NULL, sipUnused, ""))
        {
            Py_BEGIN_ALLOW_THREADS
            sipCpp = new sipQAbstractXmlNodeModel();
            Py_END_ALLOW_THREADS

            sipCpp->sipPySelf = sipSelf;

            return sipCpp;
        }
    }

    return NULL;
}


static PyMethodDef methods_QAbstractXmlNodeModel[] = {
    {SIP_MLNAME_CAST(sipName_attributes), meth_QAbstractXmlNodeModel_attributes, METH_VARARGS, NULL},
    {SIP_MLNAME_CAST(sipName_baseUri), meth_QAbstractXmlNodeModel_baseUri, METH_VARARGS, NULL},
    {SIP_MLNAME_CAST(sipName_compareOrder), meth_QAbstractXmlNodeModel_compareOrder, METH_VARARGS, NULL},
    {SIP_MLNAME_CAST(sipName_createIndex), (PyCFunction)meth_QAbstractXmlNodeModel_createIndex, METH_VARARGS|METH_KEYWORDS, NULL},
    {SIP_MLNAME_CAST(sipName_documentUri), meth_QAbstractXmlNodeModel_documentUri, METH_VARARGS, NULL},
    {SIP_MLNAME_CAST(sipName_elementById), meth_QAbstractXmlNodeModel_elementById, METH_VARARGS, NULL},
    {SIP_MLNAME_CAST(sipName_kind), meth_QAbstractXmlNodeModel_kind, METH_VARARGS, NULL},
    {SIP_MLNAME_CAST(sipName_name), meth_QAbstractXmlNodeModel_name, METH_VARARGS, NULL},
    {SIP_MLNAME_CAST(sipName_namespaceBindings), meth_QAbstractXmlNodeModel_namespaceBindings, METH_VARARGS, NULL},
    {SIP_MLNAME_CAST(sipName_nextFromSimpleAxis), meth_QAbstractXmlNodeModel_nextFromSimpleAxis, METH_VARARGS, NULL},
    {SIP_MLNAME_CAST(sipName_nodesByIdref), meth_QAbstractXmlNodeModel_nodesByIdref, METH_VARARGS, NULL},
    {SIP_MLNAME_CAST(sipName_root), meth_QAbstractXmlNodeModel_root, METH_VARARGS, NULL},
    {SIP_MLNAME_CAST(sipName_sourceLocation), meth_QAbstractXmlNodeModel_sourceLocation, METH_VARARGS, NULL},
    {SIP_MLNAME_CAST(sipName_stringValue), meth_QAbstractXmlNodeModel_stringValue, METH_VARARGS, NULL},
    {SIP_MLNAME_CAST(sipName_typedValue), meth_QAbstractXmlNodeModel_typedValue, METH_VARARGS, NULL}
};

static sipEnumMemberDef enummembers_QAbstractXmlNodeModel[] = {
    {sipName_FirstChild, QAbstractXmlNodeModel::FirstChild, 3},
    {sipName_NextSibling, QAbstractXmlNodeModel::NextSibling, 3},
    {sipName_Parent, QAbstractXmlNodeModel::Parent, 3},
    {sipName_PreviousSibling, QAbstractXmlNodeModel::PreviousSibling, 3},
};


pyqt4ClassTypeDef sipTypeDef_QtXmlPatterns_QAbstractXmlNodeModel = {
{
    {
        -1,
        0,
        0,
        SIP_TYPE_ABSTRACT|SIP_TYPE_CLASS,
        sipNameNr_QAbstractXmlNodeModel,
        {0}
    },
    {
        sipNameNr_QAbstractXmlNodeModel,
        {0, 0, 1},
        15, methods_QAbstractXmlNodeModel,
        4, enummembers_QAbstractXmlNodeModel,
        0, 0,
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    },
    0,
    sipNameNr_PyQt4_QtCore_pyqtWrapperType,
    sipNameNr_sip_simplewrapper,
    0,
    0,
    init_QAbstractXmlNodeModel,
    0,
    0,
#if PY_MAJOR_VERSION >= 3
    0,
    0,
#else
    0,
    0,
    0,
    0,
#endif
    dealloc_QAbstractXmlNodeModel,
    0,
    0,
    0,
    release_QAbstractXmlNodeModel,
    cast_QAbstractXmlNodeModel,
    0,
    0,
    0
},
    0,
    0,
    0
};
