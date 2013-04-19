/****************************************************************************
** Meta object code from reading C++ file 'qpydeclarativepropertyvaluesource.h'
**
** Created: Thu Jul 12 20:17:37 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "qpydeclarativepropertyvaluesource.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qpydeclarativepropertyvaluesource.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QPyDeclarativePropertyValueSource[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_QPyDeclarativePropertyValueSource[] = {
    "QPyDeclarativePropertyValueSource\0"
};

void QPyDeclarativePropertyValueSource::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData QPyDeclarativePropertyValueSource::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QPyDeclarativePropertyValueSource::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QPyDeclarativePropertyValueSource,
      qt_meta_data_QPyDeclarativePropertyValueSource, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QPyDeclarativePropertyValueSource::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QPyDeclarativePropertyValueSource::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QPyDeclarativePropertyValueSource::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QPyDeclarativePropertyValueSource))
        return static_cast<void*>(const_cast< QPyDeclarativePropertyValueSource*>(this));
    if (!strcmp(_clname, "QDeclarativePropertyValueSource"))
        return static_cast< QDeclarativePropertyValueSource*>(const_cast< QPyDeclarativePropertyValueSource*>(this));
    if (!strcmp(_clname, "com.trolltech.qml.QDeclarativePropertyValueSource"))
        return static_cast< QDeclarativePropertyValueSource*>(const_cast< QPyDeclarativePropertyValueSource*>(this));
    return QObject::qt_metacast(_clname);
}

int QPyDeclarativePropertyValueSource::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
