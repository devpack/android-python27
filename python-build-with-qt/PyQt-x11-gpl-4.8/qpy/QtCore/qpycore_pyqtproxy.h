// This contains the definition of the PyQtProxy class.
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


#ifndef _QPYCORE_PYQTPROXY_H
#define _QPYCORE_PYQTPROXY_H


#include <Python.h>

#include <QByteArray>
#include <QMultiHash>
#include <QList>
#include <QMetaObject>
#include <QObject>

#include "qpycore_chimera.h"
#include "qpycore_pyqtboundsignal.h"
#include "qpycore_sip.h"
#include "qpycore_types.h"


class QMutex;
class PyQt_PyObject;


// This class is used as a signal on behalf of Python signals and as a slot on
// behalf of Python callables.  It is derived from QObject but is not run
// through moc.  Instead the normal moc-generated methods are handwritten in
// order to implement a universal signal or slot.  This requires some knowledge
// of the internal implementation of signals and slots but it is likely that
// they will only change between major Qt versions.
class PyQtProxy : public QObject
{
public:
    // The different roles a proxy can fulfill.  It might have been better to
    // implement each as a sub-class.
    enum ProxyType {
        ProxySlot,
        ProxySignal,
    };

    PyQtProxy(QObject *tx, const char *sig);
    PyQtProxy(sipWrapper *txObj, const char *sig, PyObject *rxObj,
            const char *slot, const char **member, int flags);
    PyQtProxy(qpycore_pyqtBoundSignal *bs, PyObject *rxObj,
            const char **member);
    ~PyQtProxy();

    static const QMetaObject staticMetaObject;
    virtual const QMetaObject *metaObject() const;
    virtual void *qt_metacast(const char *);
    virtual int qt_metacall(QMetaObject::Call, int, void **);

    void unislot(void **qargs);
    static PyObject *invokeSlot(const qpycore_slot &slot, void **qargs);
    void disable();

    int getReceivers(const char *signal) const {return receivers(signal);}

    static void deleteSlotProxies(void *tx, const char *sig);

    static PyQtProxy *findSlotProxy(void *tx, const char *sig, PyObject *rxObj,
            const char *slot, const char **member);

    // The type of a proxy hash.
    typedef QMultiHash<void *, PyQtProxy *> ProxyHash;

    // Each proxy type is held in a different hash.
    static ProxyHash proxy_slots;
    static ProxyHash proxy_signals;

    // The mutex around the proxies hashes.
    static QMutex *mutex;

    // The proxy type.
    ProxyType type;

    // The proxy flags.
    int proxy_flags;

    // The normalised signature.
    QByteArray signature;

    // Set if the proxy is in a hash.
    bool hashed;

    // The QObject transmitter we are proxying for (if any).
    QObject *transmitter;

    // The slot we are proxying for.  (Only used when type is ProxySlot.)
    qpycore_slot real_slot;

    // The last QObject sender.
    static QObject *last_sender;

private:
    void init(QObject *qtx, ProxyHash *hash, void *key);
    void remove();

    // This object's key in the relevant hash.
    void *saved_key;

    // Only used when type is ProxySignal.
    QMetaObject *sigmo;

    PyQtProxy(const PyQtProxy &);
    PyQtProxy &operator=(const PyQtProxy &);
};


// This acts as a proxy for short-circuit signals.  The parent is the object we
// are proxying for.  The object name is the name of the signal.
class PyQtShortcircuitSignalProxy : public QObject
{
    Q_OBJECT

public:
    PyQtShortcircuitSignalProxy(QObject *parent);

    int getReceivers(const char *signal) const {return receivers(signal);}

    void emit_signal(const PyQt_PyObject &args) {emit pysignal(args);}

    static PyQtShortcircuitSignalProxy *find(QObject *tx, const char *sig);

signals:
    void pysignal(const PyQt_PyObject &);
};


#endif
