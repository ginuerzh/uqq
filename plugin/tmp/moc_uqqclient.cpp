/****************************************************************************
** Meta object code from reading C++ file 'uqqclient.h'
**
** Created: Tue Mar 19 17:02:16 2013
**      by: The Qt Meta Object Compiler version 67 (Qt 5.0.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../uqqclient.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'uqqclient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.0.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_UQQClient_t {
    QByteArrayData data[20];
    char stringdata[194];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_UQQClient_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_UQQClient_t qt_meta_stringdata_UQQClient = {
    {
QT_MOC_LITERAL(0, 0, 9),
QT_MOC_LITERAL(1, 10, 14),
QT_MOC_LITERAL(2, 25, 0),
QT_MOC_LITERAL(3, 26, 14),
QT_MOC_LITERAL(4, 41, 18),
QT_MOC_LITERAL(5, 60, 14),
QT_MOC_LITERAL(6, 75, 5),
QT_MOC_LITERAL(7, 81, 17),
QT_MOC_LITERAL(8, 99, 13),
QT_MOC_LITERAL(9, 113, 19),
QT_MOC_LITERAL(10, 133, 7),
QT_MOC_LITERAL(11, 141, 3),
QT_MOC_LITERAL(12, 145, 9),
QT_MOC_LITERAL(13, 155, 3),
QT_MOC_LITERAL(14, 159, 5),
QT_MOC_LITERAL(15, 165, 3),
QT_MOC_LITERAL(16, 169, 2),
QT_MOC_LITERAL(17, 172, 4),
QT_MOC_LITERAL(18, 177, 7),
QT_MOC_LITERAL(19, 185, 7)
    },
    "UQQClient\0errCodeChanged\0\0captchaChanged\0"
    "getCaptchaFinished\0QNetworkReply*\0"
    "reply\0checkCodeFinished\0loginFinished\0"
    "secondloginFinished\0getInfo\0key\0"
    "checkCode\0uin\0login\0pwd\0vc\0info\0errCode\0"
    "captcha\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UQQClient[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       3,   86, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x05,
       3,    0,   60,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
       4,    1,   61,    2, 0x0a,
       7,    1,   64,    2, 0x0a,
       8,    1,   67,    2, 0x0a,
       9,    1,   70,    2, 0x0a,

 // methods: name, argc, parameters, tag, flags
      10,    1,   73,    2, 0x02,
      12,    1,   76,    2, 0x02,
      14,    3,   79,    2, 0x02,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, 0x80000000 | 5,    6,

 // methods: parameters
    QMetaType::QVariant, QMetaType::QString,   11,
    QMetaType::Void, QMetaType::QString,   13,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,   13,   15,   16,

 // properties: name, type, flags
      17, QMetaType::QVariantMap, 0x00095001,
      18, QMetaType::Int, 0x00495001,
      19, QMetaType::Bool, 0x00495001,

 // properties: notify_signal_id
       0,
       0,
       1,

       0        // eod
};

void UQQClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        UQQClient *_t = static_cast<UQQClient *>(_o);
        switch (_id) {
        case 0: _t->errCodeChanged(); break;
        case 1: _t->captchaChanged(); break;
        case 2: _t->getCaptchaFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 3: _t->checkCodeFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 4: _t->loginFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 5: _t->secondloginFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 6: { QVariant _r = _t->getInfo((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 7: _t->checkCode((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->login((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (UQQClient::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UQQClient::errCodeChanged)) {
                *result = 0;
            }
        }
        {
            typedef void (UQQClient::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UQQClient::captchaChanged)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject UQQClient::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_UQQClient.data,
      qt_meta_data_UQQClient,  qt_static_metacall, 0, 0}
};


const QMetaObject *UQQClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UQQClient::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_UQQClient.stringdata))
        return static_cast<void*>(const_cast< UQQClient*>(this));
    return QObject::qt_metacast(_clname);
}

int UQQClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QVariantMap*>(_v) = info(); break;
        case 1: *reinterpret_cast< int*>(_v) = errCode(); break;
        case 2: *reinterpret_cast< bool*>(_v) = captcha(); break;
        }
        _id -= 3;
    } else if (_c == QMetaObject::WriteProperty) {
        _id -= 3;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 3;
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void UQQClient::errCodeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void UQQClient::captchaChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
