/****************************************************************************
** Meta object code from reading C++ file 'networksocket.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../checker/networksocket.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'networksocket.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_NetworkSocket_t {
    const uint offsetsAndSize[16];
    char stringdata0[77];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_NetworkSocket_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_NetworkSocket_t qt_meta_stringdata_NetworkSocket = {
    {
QT_MOC_LITERAL(0, 13), // "NetworkSocket"
QT_MOC_LITERAL(14, 7), // "receive"
QT_MOC_LITERAL(22, 0), // ""
QT_MOC_LITERAL(23, 11), // "NetworkData"
QT_MOC_LITERAL(35, 10), // "parseError"
QT_MOC_LITERAL(46, 14), // "InvalidMessage"
QT_MOC_LITERAL(61, 3), // "bye"
QT_MOC_LITERAL(65, 11) // "receiveData"

    },
    "NetworkSocket\0receive\0\0NetworkData\0"
    "parseError\0InvalidMessage\0bye\0receiveData"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NetworkSocket[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   38,    2, 0x06,    1 /* Public */,
       4,    1,   41,    2, 0x06,    3 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       6,    0,   44,    2, 0x0a,    5 /* Public */,
       7,    0,   45,    2, 0x08,    6 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 5,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void NetworkSocket::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<NetworkSocket *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->receive((*reinterpret_cast< NetworkData(*)>(_a[1]))); break;
        case 1: _t->parseError((*reinterpret_cast< const InvalidMessage(*)>(_a[1]))); break;
        case 2: _t->bye(); break;
        case 3: _t->receiveData(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (NetworkSocket::*)(NetworkData );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NetworkSocket::receive)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (NetworkSocket::*)(const InvalidMessage & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NetworkSocket::parseError)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject NetworkSocket::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_NetworkSocket.offsetsAndSize,
    qt_meta_data_NetworkSocket,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_NetworkSocket_t
, QtPrivate::TypeAndForceComplete<NetworkSocket, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<NetworkData, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const InvalidMessage &, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *NetworkSocket::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NetworkSocket::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_NetworkSocket.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int NetworkSocket::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void NetworkSocket::receive(NetworkData _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void NetworkSocket::parseError(const InvalidMessage & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
