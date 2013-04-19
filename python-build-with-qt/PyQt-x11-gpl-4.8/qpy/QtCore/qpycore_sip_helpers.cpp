// This is the signal/slot helper code for SIP.
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


#include <string.h>

#include <Python.h>

#include <QByteArray>
#include <QMetaObject>
#include <QMutex>
#include <QObject>

#include "qpycore_chimera.h"
#include "qpycore_pyqtboundsignal.h"
#include "qpycore_pyqtproxy.h"
#include "qpycore_pyqtpyobject.h"
#include "qpycore_sip.h"
#include "qpycore_sip_helpers.h"


// Forward declarations.
static PyQtShortcircuitSignalProxy *find_shortcircuit_signal(QObject *qtx,
        const char **sig);
static PyQtProxy *find_signal(QObject *qtx, const QByteArray &sig);
static void emit_shortcircuit_signal(QObject *tx, const char *sig,
        PyObject *sigargs);
static bool is_shortcircuit_signal(const char *sig);


// Find an existing Python short-circuited signal proxy.  Returns a pointer to
// the instance or 0 there wasn't one.
static PyQtShortcircuitSignalProxy *find_shortcircuit_signal(QObject *qtx,
        const char **sig)
{
    PyQtShortcircuitSignalProxy *proxy = PyQtShortcircuitSignalProxy::find(qtx, *sig);

    if (proxy)
        *sig = SIGNAL(pysignal(const PyQt_PyObject &));

    return proxy;
}


// Find an existing Python signal proxy.  Returns a pointer to the instance or
// 0 there wasn't one.
static PyQtProxy *find_signal(QObject *qtx, const QByteArray &sig)
{
    PyQtProxy::ProxyHash::const_iterator it(PyQtProxy::proxy_signals.find(qtx));

    while (it != PyQtProxy::proxy_signals.end() && it.key() == qtx)
    {
        PyQtProxy *proxy = it.value();

        if (proxy->signature == sig)
            return proxy;

        ++it;
    }

    return 0;
}


// Find an existing signal emitter for the given object and signature.  Returns
// a pointer to the emitter or 0 if there wasn't one, and updates the signature
// if necessary.
QObject *qpycore_find_signal(QObject *qtx, const char **sig)
{
    // See if it a short-circuit signal.
    if (is_shortcircuit_signal(*sig))
        return find_shortcircuit_signal(qtx, sig);

    // See if the object can be used itself.
    QByteArray norm_sig = QMetaObject::normalizedSignature(&(*sig)[1]);

    if (qtx->metaObject()->indexOfSignal(norm_sig.constData()) >= 0)
        return qtx;

    // Look for an existing proxy.
    return find_signal(qtx, norm_sig);
}


// Find an existing signal emitter for the given object and signature.  Returns
// a pointer to the emitter or 0 if there wasn't one, and updates the signature
// if necessary.
extern "C" void *sipQtFindUniversalSignal(void *tx, const char **sig)
{
    return qpycore_find_signal(reinterpret_cast<QObject *>(tx), sig);
}


// Factory function to create a signal emitter for the given object and
// signature.  Returns a pointer to the emitter or 0 if there was an error, and
// updates the signature if necessary.
extern "C" void *sipQtCreateUniversalSignal(void *tx, const char **sigp)
{
    QObject *proxy;
    QObject *qtx = reinterpret_cast<QObject *>(tx);
    const char *sig = *sigp;

    // See if it a short-circuit signal.
    if (is_shortcircuit_signal(sig))
    {
        Py_BEGIN_ALLOW_THREADS
        proxy = new PyQtShortcircuitSignalProxy(qtx);
        proxy->setObjectName(sig);
        Py_END_ALLOW_THREADS

        *sigp = SIGNAL(pysignal(const PyQt_PyObject &));
    }
    else
    {
        Py_BEGIN_ALLOW_THREADS
        proxy = new PyQtProxy(qtx, &sig[1]);
        Py_END_ALLOW_THREADS
    }

    return proxy;
}


// Factory function to create a universal slot instance.  Returns a pointer to
// the instance or 0 if there was an error.  Note that we may also return a
// Qt signal (from a bound signal).
extern "C" void *sipQtCreateUniversalSlot(sipWrapper *tx, const char *sig,
        PyObject *rxObj, const char *slot, const char **member, int flags)
{
    // Get the receiver C++ QObject if there is one.
    PyObject *qrxObj;

    if (slot)
    {
        qrxObj = rxObj;
    }
    else if (Py_TYPE(rxObj) == &qpycore_pyqtBoundSignal_Type)
    {
        qpycore_pyqtBoundSignal *bs = (qpycore_pyqtBoundSignal *)rxObj;

        *member = bs->bound_overload->signature.constData();

        return bs->bound_qobject;
    }
    else if (PyMethod_Check(rxObj))
    {
        qrxObj = PyMethod_GET_SELF(rxObj);
    }
    else
    {
        qrxObj = 0;
    }

    QObject *qrx = 0;

    if (qrxObj)
    {
        int iserr = 0;
        void *rx = sipForceConvertToType(qrxObj, sipType_QObject, 0,
                SIP_NOT_NONE|SIP_NO_CONVERTORS, 0, &iserr);

        if (iserr)
            PyErr_Clear();
        else
            qrx = reinterpret_cast<QObject *>(rx);
    }

    PyQtProxy *res;

    Py_BEGIN_ALLOW_THREADS

    res = new PyQtProxy(tx, sig, rxObj, slot, member, flags);

    if (res->real_slot.signature)
    {
        // If the receiver is a QObject then move the proxy to the same thread.
        if (qrx)
            res->moveToThread(qrx->thread());
    }
    else
    {
        delete res;
        res = 0;
    }

    Py_END_ALLOW_THREADS

    return res;
}


// Dispose of a receiver that might be a universal slot.
extern "C" void sipQtDestroyUniversalSlot(void *rx)
{
    Py_BEGIN_ALLOW_THREADS
    PyQtProxy::mutex->lock();

    PyQtProxy::ProxyHash::const_iterator it(PyQtProxy::proxy_slots.begin());

    while (it != PyQtProxy::proxy_slots.end())
    {
        PyQtProxy *up = it.value();

        if (up == reinterpret_cast<QObject *>(rx))
        {
            // If we are disconnecting within the slot that is connected then
            // disable() will make sure the proxy isn't deleted until the slot
            // returns.
            up->disable();
            break;
        }

        ++it;
    }

    PyQtProxy::mutex->unlock();
    Py_END_ALLOW_THREADS
}


// Search for the universal slot connected to a particular Qt signal.
extern "C" void *sipQtFindSlot(void *tx, const char *sig, PyObject *rxObj,
        const char *slot, const char **member)
{
    return PyQtProxy::findSlotProxy(tx, sig, rxObj, slot, member);
}


// Connect a Qt signal to a Qt slot.
extern "C" int sipQtConnect(void *tx, const char *sig, void *rx, const char *slot, int type)
{
    // Unlike Qt3, Qt4 does not check that the signal and slot arguments are
    // compatible in a release build.  I think this is a bug, so we do the
    // missing check here.
#if defined(QT_NO_DEBUG)
    if (!QMetaObject::checkConnectArgs(sig, slot))
        return 0;
#endif

    int res;

    Py_BEGIN_ALLOW_THREADS
    res = QObject::connect(reinterpret_cast<QObject *>(tx), sig,
                           reinterpret_cast<QObject *>(rx), slot,
                           (Qt::ConnectionType)type);
    Py_END_ALLOW_THREADS

    return res;
}


// Disconnect a Qt signal from a Qt slot.
extern "C" int sipQtDisconnect(void *tx, const char *sig, void *rx, const char *slot)
{
    int res;

    Py_BEGIN_ALLOW_THREADS
    res = QObject::disconnect(reinterpret_cast<QObject *>(tx), sig,
                              reinterpret_cast<QObject *>(rx), slot);
    Py_END_ALLOW_THREADS

    return res;
}


// See if two signal or slot names are the same.
extern "C" int sipQtSameSignalSlotName(const char *s1, const char *s2)
{
    // Signal and slot names are always normalised so a simple string
    // comparison will do.
    return (qstrcmp(s1, s2) == 0);
}


// Return the next slot for a particular transmitter.  This will be called with
// the GIL locked.
extern "C" sipSlot *sipQtFindSipslot(void *tx, void **context)
{
    PyQtProxy::ProxyHash::const_iterator it;
    PyQtProxy::ProxyHash::const_iterator *itp = *reinterpret_cast<PyQtProxy::ProxyHash::const_iterator **>(context);

    // Use the existing context if there is one, otherwise initialise a new
    // one.
    if (itp)
        it = *itp;
    else
    {
        it = PyQtProxy::proxy_slots.find(tx);
        itp = new PyQtProxy::ProxyHash::const_iterator(it);
        *context = itp;
    }

    if (it != PyQtProxy::proxy_slots.end() && it.key() == tx)
    {
        PyQtProxy *up = it++.value();

        // Save the current context.
        *itp = it;

        return &up->real_slot.sip_slot;
    }

    // Discard the context as it is no longer needed.
    delete itp;
    *context = 0;

    return 0;
}


// Emit the given signal from the given object.
bool qpycore_qobject_emit(QObject *qtx, const char *sig, PyObject *sigargs)
{
    // We need to explicitly check for anything that uses a proxy, so we might
    // as well check for everything.
    if (qtx->signalsBlocked())
        return true;

    // See if it is a short-circuit signal.
    if (is_shortcircuit_signal(sig))
    {
        emit_shortcircuit_signal(qtx, sig, sigargs);
        return true;
    }

    QByteArray norm_sig = QMetaObject::normalizedSignature(&sig[1]);
    int signal_index = qtx->metaObject()->indexOfSignal(norm_sig.constData());

    // If the signal doesn't exist then see if there is a proxy for it.
    if (signal_index < 0)
    {
        PyQtProxy *proxy = find_signal(qtx, norm_sig);

        // Unfortunately we can't distinguish between a Qt name with a typo and
        // an unconnected Python signal - so we just ignore the emit.
        if (!proxy)
            return true;

        // Use the proxy instead.
        qtx = proxy;
        signal_index = proxy->metaObject()->indexOfSignal(norm_sig.constData());
    }

    // Parse the signature.
    const Chimera::Signature *parsed_signature = Chimera::parse(norm_sig,
            "a signal argument");

    if (!parsed_signature)
        return false;

    bool ok = qpycore_emit(qtx, signal_index, parsed_signature, sigargs);
    delete parsed_signature;

    return ok;
}


// Emit a signal based on a parsed signature.
bool qpycore_emit(QObject *qtx, int signal_index,
        const Chimera::Signature *parsed_signature, PyObject *sigargs)
{
    const QList<const Chimera *> &args = parsed_signature->parsed_arguments;

    if (args.size() != PyTuple_GET_SIZE(sigargs))
    {
        PyErr_Format(PyExc_TypeError,
                "signal %s has %d argument(s) but %d provided",
                parsed_signature->py_signature.constData(), args.size(),
                (int)PyTuple_GET_SIZE(sigargs));

        return false;
    }

    // Convert the arguments.
    QList<Chimera::Storage *> values;
    void **argv = new void *[1 + args.size()];

    argv[0] = 0;

    QList<const Chimera *>::const_iterator it = args.constBegin();

    for (int a = 0; it != args.constEnd(); ++a)
    {
        PyObject *arg_obj = PyTuple_GET_ITEM(sigargs, a);
        Chimera::Storage *val = (*it)->fromPyObjectToStorage(arg_obj);

        if (!val)
        {
            const char *sig;

            // Use the docstring if there is one and it is auto-generated.
            sig = parsed_signature->docstring;

            if (!sig || *sig != '\1')
            {
                sig = parsed_signature->py_signature.constData();
            }
            else
            {
                // Skip the auto-generated marker.
                ++sig;
            }

            // Mimic SIP's exception text.
            PyErr_Format(PyExc_TypeError,
                    "%s.emit(): argument %d has unexpected type '%s'", sig,
                    a + 1, Py_TYPE(arg_obj)->tp_name);

            delete[] argv;
            qDeleteAll(values.constBegin(), values.constEnd());

            return false;
        }

        argv[1 + a] = val->address();
        values << val;

        ++it;
    }

    Py_BEGIN_ALLOW_THREADS
    QMetaObject::activate(qtx, signal_index, signal_index, argv);
    Py_END_ALLOW_THREADS

    delete[] argv;
    qDeleteAll(values.constBegin(), values.constEnd());

    return true;
}


// Emit a shortcircuit signal.
static void emit_shortcircuit_signal(QObject *tx, const char *sig,
        PyObject *sigargs)
{
    // Find the proxy emitter.  Unfortunately we can't distinguish between a Qt
    // name with a typo and an unconnected Python signal - so we just ignore
    // the emit.
    PyQtShortcircuitSignalProxy *proxy = PyQtShortcircuitSignalProxy::find(tx, sig);

    if (proxy)
    {
        PyQt_PyObject wrapped_args(sigargs);

        Py_BEGIN_ALLOW_THREADS
        proxy->emit_signal(wrapped_args);
        Py_END_ALLOW_THREADS
    }
}


// Return true if the signature is of a short-circuit signal.
static bool is_shortcircuit_signal(const char *sig)
{
    return !strchr(sig, '(');
}
