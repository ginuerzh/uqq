/****************************************************************************
** Meta object code from reading C++ file 'uqqmember.h'
**
** Created: Sun Mar 24 16:27:06 2013
**      by: The Qt Meta Object Compiler version 67 (Qt 5.0.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../uqqmember.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'uqqmember.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.0.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_UQQMember_t {
    QByteArrayData data[22];
    char stringdata[230];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_UQQMember_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_UQQMember_t qt_meta_stringdata_UQQMember = {
    {
QT_MOC_LITERAL(0, 0, 9),
QT_MOC_LITERAL(1, 10, 10),
QT_MOC_LITERAL(2, 21, 0),
QT_MOC_LITERAL(3, 22, 14),
QT_MOC_LITERAL(4, 37, 15),
QT_MOC_LITERAL(5, 53, 15),
QT_MOC_LITERAL(6, 69, 15),
QT_MOC_LITERAL(7, 85, 15),
QT_MOC_LITERAL(8, 101, 13),
QT_MOC_LITERAL(9, 115, 11),
QT_MOC_LITERAL(10, 127, 10),
QT_MOC_LITERAL(11, 138, 15),
QT_MOC_LITERAL(12, 154, 3),
QT_MOC_LITERAL(13, 158, 7),
QT_MOC_LITERAL(14, 166, 8),
QT_MOC_LITERAL(15, 175, 8),
QT_MOC_LITERAL(16, 184, 8),
QT_MOC_LITERAL(17, 193, 8),
QT_MOC_LITERAL(18, 202, 6),
QT_MOC_LITERAL(19, 209, 4),
QT_MOC_LITERAL(20, 214, 5),
QT_MOC_LITERAL(21, 220, 8)
    },
    "UQQMember\0uinChanged\0\0accountChanged\0"
    "categoryChanged\0marknameChanged\0"
    "nicknameChanged\0longnickChanged\0"
    "statusChanged\0faceChanged\0vipChanged\0"
    "vipLevelChanged\0uin\0account\0category\0"
    "markname\0nickname\0longnick\0status\0"
    "face\0isVip\0vipLevel\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UQQMember[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
      10,   74, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      10,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x05,
       3,    0,   65,    2, 0x05,
       4,    0,   66,    2, 0x05,
       5,    0,   67,    2, 0x05,
       6,    0,   68,    2, 0x05,
       7,    0,   69,    2, 0x05,
       8,    0,   70,    2, 0x05,
       9,    0,   71,    2, 0x05,
      10,    0,   72,    2, 0x05,
      11,    0,   73,    2, 0x05,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
      12, QMetaType::QString, 0x00495001,
      13, QMetaType::Int, 0x00495001,
      14, QMetaType::Int, 0x00495001,
      15, QMetaType::QString, 0x00495001,
      16, QMetaType::QString, 0x00495001,
      17, QMetaType::QString, 0x00495001,
      18, QMetaType::QString, 0x00495103,
      19, QMetaType::QUrl, 0x00495001,
      20, QMetaType::Bool, 0x00495001,
      21, QMetaType::Int, 0x00495001,

 // properties: notify_signal_id
       0,
       1,
       2,
       3,
       4,
       5,
       6,
       7,
       8,
       9,

       0        // eod
};

void UQQMember::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        UQQMember *_t = static_cast<UQQMember *>(_o);
        switch (_id) {
        case 0: _t->uinChanged(); break;
        case 1: _t->accountChanged(); break;
        case 2: _t->categoryChanged(); break;
        case 3: _t->marknameChanged(); break;
        case 4: _t->nicknameChanged(); break;
        case 5: _t->longnickChanged(); break;
        case 6: _t->statusChanged(); break;
        case 7: _t->faceChanged(); break;
        case 8: _t->vipChanged(); break;
        case 9: _t->vipLevelChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (UQQMember::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UQQMember::uinChanged)) {
                *result = 0;
            }
        }
        {
            typedef void (UQQMember::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UQQMember::accountChanged)) {
                *result = 1;
            }
        }
        {
            typedef void (UQQMember::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UQQMember::categoryChanged)) {
                *result = 2;
            }
        }
        {
            typedef void (UQQMember::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UQQMember::marknameChanged)) {
                *result = 3;
            }
        }
        {
            typedef void (UQQMember::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UQQMember::nicknameChanged)) {
                *result = 4;
            }
        }
        {
            typedef void (UQQMember::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UQQMember::longnickChanged)) {
                *result = 5;
            }
        }
        {
            typedef void (UQQMember::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UQQMember::statusChanged)) {
                *result = 6;
            }
        }
        {
            typedef void (UQQMember::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UQQMember::faceChanged)) {
                *result = 7;
            }
        }
        {
            typedef void (UQQMember::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UQQMember::vipChanged)) {
                *result = 8;
            }
        }
        {
            typedef void (UQQMember::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UQQMember::vipLevelChanged)) {
                *result = 9;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject UQQMember::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_UQQMember.data,
      qt_meta_data_UQQMember,  qt_static_metacall, 0, 0}
};


const QMetaObject *UQQMember::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UQQMember::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_UQQMember.stringdata))
        return static_cast<void*>(const_cast< UQQMember*>(this));
    return QObject::qt_metacast(_clname);
}

int UQQMember::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = uin(); break;
        case 1: *reinterpret_cast< int*>(_v) = account(); break;
        case 2: *reinterpret_cast< int*>(_v) = category(); break;
        case 3: *reinterpret_cast< QString*>(_v) = markname(); break;
        case 4: *reinterpret_cast< QString*>(_v) = nickname(); break;
        case 5: *reinterpret_cast< QString*>(_v) = longnick(); break;
        case 6: *reinterpret_cast< QString*>(_v) = status(); break;
        case 7: *reinterpret_cast< QUrl*>(_v) = face(); break;
        case 8: *reinterpret_cast< bool*>(_v) = isVip(); break;
        case 9: *reinterpret_cast< int*>(_v) = vipLevel(); break;
        }
        _id -= 10;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 6: setStatus(*reinterpret_cast< QString*>(_v)); break;
        }
        _id -= 10;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 10;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 10;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 10;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 10;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 10;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 10;
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void UQQMember::uinChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void UQQMember::accountChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void UQQMember::categoryChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void UQQMember::marknameChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void UQQMember::nicknameChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void UQQMember::longnickChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}

// SIGNAL 6
void UQQMember::statusChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 6, 0);
}

// SIGNAL 7
void UQQMember::faceChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 7, 0);
}

// SIGNAL 8
void UQQMember::vipChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 8, 0);
}

// SIGNAL 9
void UQQMember::vipLevelChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 9, 0);
}
QT_END_MOC_NAMESPACE
