/****************************************************************************
** Meta object code from reading C++ file 'networkserver.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../checker/networkserver.h"
#include <QtNetwork/QSslPreSharedKeyAuthenticator>
#include <QtNetwork/QSslError>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'networkserver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_NetworkServer_t {
    const uint offsetsAndSize[26];
    char stringdata0[128];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_NetworkServer_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_NetworkServer_t qt_meta_stringdata_NetworkServer = {
    {
QT_MOC_LITERAL(0, 13), // "NetworkServer"
QT_MOC_LITERAL(14, 7), // "receive"
QT_MOC_LITERAL(22, 0), // ""
QT_MOC_LITERAL(23, 11), // "QTcpSocket*"
QT_MOC_LITERAL(35, 6), // "client"
QT_MOC_LITERAL(42, 11), // "NetworkData"
QT_MOC_LITERAL(54, 4), // "data"
QT_MOC_LITERAL(59, 10), // "parseError"
QT_MOC_LITERAL(70, 14), // "InvalidMessage"
QT_MOC_LITERAL(85, 5), // "leave"
QT_MOC_LITERAL(91, 11), // "receiveData"
QT_MOC_LITERAL(103, 10), // "disconnect"
QT_MOC_LITERAL(114, 13) // "newconnection"

    },
    "NetworkServer\0receive\0\0QTcpSocket*\0"
    "client\0NetworkData\0data\0parseError\0"
    "InvalidMessage\0leave\0receiveData\0"
    "disconnect\0newconnection"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NetworkServer[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,   50,    2, 0x06,    1 /* Public */,
       7,    1,   55,    2, 0x06,    4 /* Public */,
       9,    1,   58,    2, 0x06,    6 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      10,    1,   61,    2, 0x08,    8 /* Private */,
      11,    1,   64,    2, 0x08,   10 /* Private */,
      12,    0,   67,    2, 0x08,   12 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,    6,
    QMetaType::Void, 0x80000000 | 8,    2,
    QMetaType::Void, 0x80000000 | 3,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::QObjectStar,    2,
    QMetaType::Void, QMetaType::QObjectStar,    2,
    QMetaType::Void,

       0        // eod
};

void NetworkServer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<NetworkServer *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->receive((*reinterpret_cast< QTcpSocket*(*)>(_a[1])),(*reinterpret_cast< NetworkData(*)>(_a[2]))); break;
        case 1: _t->parseError((*reinterpret_cast< const InvalidMessage(*)>(_a[1]))); break;
        case 2: _t->leave((*reinterpret_cast< QTcpSocket*(*)>(_a[1]))); break;
        case 3: _t->receiveData((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        case 4: _t->disconnect((*reinterpret_cast< QObject*(*)>(_a[1]))); break;
        case 5: _t->newconnection(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QTcpSocket* >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QTcpSocket* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (NetworkServer::*)(QTcpSocket * , NetworkData );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NetworkServer::receive)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (NetworkServer::*)(const InvalidMessage & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NetworkServer::parseError)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (NetworkServer::*)(QTcpSocket * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NetworkServer::leave)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject NetworkServer::staticMetaObject = { {
    QMetaObject::SuperData::link<QTcpServer::staticMetaObject>(),
    qt_meta_stringdata_NetworkServer.offsetsAndSize,
    qt_meta_data_NetworkServer,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_NetworkServer_t
, QtPrivate::TypeAndForceComplete<NetworkServer, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QTcpSocket *, std::false_type>, QtPrivate::TypeAndForceComplete<NetworkData, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const InvalidMessage &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QTcpSocket *, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QObject *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QObject *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *NetworkServer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NetworkServer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_NetworkServer.stringdata0))
        return static_cast<void*>(this);
    return QTcpServer::qt_metacast(_clname);
}

int NetworkServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTcpServer::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void NetworkServer::receive(QTcpSocket * _t1, NetworkData _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void NetworkServer::parseError(const InvalidMessage & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void NetworkServer::leave(QTcpSocket * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
