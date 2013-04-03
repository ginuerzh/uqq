/****************************************************************************
** Meta object code from reading C++ file 'uqqclient.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.0.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../uqqclient.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'uqqclient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.0.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_UQQClient_t {
    QByteArrayData data[30];
    char stringdata[331];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_UQQClient_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_UQQClient_t qt_meta_stringdata_UQQClient = {
    {
QT_MOC_LITERAL(0, 0, 9),
QT_MOC_LITERAL(1, 10, 12),
QT_MOC_LITERAL(2, 23, 0),
QT_MOC_LITERAL(3, 24, 7),
QT_MOC_LITERAL(4, 32, 14),
QT_MOC_LITERAL(5, 47, 6),
QT_MOC_LITERAL(6, 54, 12),
QT_MOC_LITERAL(7, 67, 13),
QT_MOC_LITERAL(8, 81, 19),
QT_MOC_LITERAL(9, 101, 10),
QT_MOC_LITERAL(10, 112, 14),
QT_MOC_LITERAL(11, 127, 5),
QT_MOC_LITERAL(12, 133, 12),
QT_MOC_LITERAL(13, 146, 3),
QT_MOC_LITERAL(14, 150, 11),
QT_MOC_LITERAL(15, 162, 9),
QT_MOC_LITERAL(16, 172, 3),
QT_MOC_LITERAL(17, 176, 5),
QT_MOC_LITERAL(18, 182, 3),
QT_MOC_LITERAL(19, 186, 2),
QT_MOC_LITERAL(20, 189, 15),
QT_MOC_LITERAL(21, 205, 11),
QT_MOC_LITERAL(22, 217, 13),
QT_MOC_LITERAL(23, 231, 15),
QT_MOC_LITERAL(24, 247, 18),
QT_MOC_LITERAL(25, 266, 8),
QT_MOC_LITERAL(26, 275, 18),
QT_MOC_LITERAL(27, 294, 13),
QT_MOC_LITERAL(28, 308, 16),
QT_MOC_LITERAL(29, 325, 4)
    },
    "UQQClient\0errorChanged\0\0errCode\0"
    "captchaChanged\0needed\0loginSuccess\0"
    "categoryReady\0onlineStatusChanged\0"
    "onFinished\0QNetworkReply*\0reply\0"
    "getLoginInfo\0key\0getUserInfo\0checkCode\0"
    "uin\0login\0pwd\0vc\0getMemberDetail\0"
    "loadContact\0getCategories\0QList<QObject*>\0"
    "getCategoryMembers\0category\0"
    "loadInfoInCategory\0getMemberFace\0"
    "getOnlineBuddies\0poll\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UQQClient[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  104,    2, 0x05,
       4,    1,  107,    2, 0x05,
       6,    0,  110,    2, 0x05,
       7,    0,  111,    2, 0x05,
       8,    0,  112,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
       9,    1,  113,    2, 0x0a,

 // methods: name, argc, parameters, tag, flags
      12,    1,  116,    2, 0x02,
      14,    1,  119,    2, 0x02,
      15,    1,  122,    2, 0x02,
      17,    3,  125,    2, 0x02,
      20,    1,  132,    2, 0x02,
      21,    0,  135,    2, 0x02,
      22,    0,  136,    2, 0x02,
      24,    1,  137,    2, 0x02,
      26,    1,  140,    2, 0x02,
      27,    1,  143,    2, 0x02,
      28,    0,  146,    2, 0x02,
      29,    0,  147,    2, 0x02,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 10,   11,

 // methods: parameters
    QMetaType::QVariant, QMetaType::QString,   13,
    QMetaType::QVariant, QMetaType::QString,   13,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,   16,   18,   19,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void,
    0x80000000 | 23,
    0x80000000 | 23, QMetaType::Int,   25,
    QMetaType::Void, QMetaType::Int,   25,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void UQQClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        UQQClient *_t = static_cast<UQQClient *>(_o);
        switch (_id) {
        case 0: _t->errorChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->captchaChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->loginSuccess(); break;
        case 3: _t->categoryReady(); break;
        case 4: _t->onlineStatusChanged(); break;
        case 5: _t->onFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 6: { QVariant _r = _t->getLoginInfo((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 7: { QVariant _r = _t->getUserInfo((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = _r; }  break;
        case 8: _t->checkCode((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->login((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 10: _t->getMemberDetail((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 11: _t->loadContact(); break;
        case 12: { QList<QObject*> _r = _t->getCategories();
            if (_a[0]) *reinterpret_cast< QList<QObject*>*>(_a[0]) = _r; }  break;
        case 13: { QList<QObject*> _r = _t->getCategoryMembers((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QList<QObject*>*>(_a[0]) = _r; }  break;
        case 14: _t->loadInfoInCategory((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->getMemberFace((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 16: _t->getOnlineBuddies(); break;
        case 17: _t->poll(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
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
            typedef void (UQQClient::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UQQClient::errorChanged)) {
                *result = 0;
            }
        }
        {
            typedef void (UQQClient::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UQQClient::captchaChanged)) {
                *result = 1;
            }
        }
        {
            typedef void (UQQClient::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UQQClient::loginSuccess)) {
                *result = 2;
            }
        }
        {
            typedef void (UQQClient::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UQQClient::categoryReady)) {
                *result = 3;
            }
        }
        {
            typedef void (UQQClient::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UQQClient::onlineStatusChanged)) {
                *result = 4;
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
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    }
    return _id;
}

// SIGNAL 0
void UQQClient::errorChanged(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void UQQClient::captchaChanged(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void UQQClient::loginSuccess()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void UQQClient::categoryReady()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void UQQClient::onlineStatusChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}
QT_END_MOC_NAMESPACE
