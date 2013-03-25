/****************************************************************************
** Meta object code from reading C++ file 'uqqcategory.h'
**
** Created: Sun Mar 24 16:27:07 2013
**      by: The Qt Meta Object Compiler version 67 (Qt 5.0.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../uqqcategory.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'uqqcategory.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.0.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_UQQCategory_t {
    QByteArrayData data[10];
    char stringdata[90];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_UQQCategory_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_UQQCategory_t qt_meta_stringdata_UQQCategory = {
    {
QT_MOC_LITERAL(0, 0, 11),
QT_MOC_LITERAL(1, 12, 11),
QT_MOC_LITERAL(2, 24, 0),
QT_MOC_LITERAL(3, 25, 13),
QT_MOC_LITERAL(4, 39, 12),
QT_MOC_LITERAL(5, 52, 12),
QT_MOC_LITERAL(6, 65, 4),
QT_MOC_LITERAL(7, 70, 6),
QT_MOC_LITERAL(8, 77, 5),
QT_MOC_LITERAL(9, 83, 5)
    },
    "UQQCategory\0nameChanged\0\0onlineChanged\0"
    "totalChanged\0indexChanged\0name\0online\0"
    "total\0index\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UQQCategory[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       4,   38, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x05,
       3,    0,   35,    2, 0x05,
       4,    0,   36,    2, 0x05,
       5,    0,   37,    2, 0x05,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
       6, QMetaType::QString, 0x00495103,
       7, QMetaType::Int, 0x00495103,
       8, QMetaType::Int, 0x00495103,
       9, QMetaType::Int, 0x00495001,

 // properties: notify_signal_id
       0,
       1,
       2,
       3,

       0        // eod
};

void UQQCategory::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        UQQCategory *_t = static_cast<UQQCategory *>(_o);
        switch (_id) {
        case 0: _t->nameChanged(); break;
        case 1: _t->onlineChanged(); break;
        case 2: _t->totalChanged(); break;
        case 3: _t->indexChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (UQQCategory::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UQQCategory::nameChanged)) {
                *result = 0;
            }
        }
        {
            typedef void (UQQCategory::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UQQCategory::onlineChanged)) {
                *result = 1;
            }
        }
        {
            typedef void (UQQCategory::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UQQCategory::totalChanged)) {
                *result = 2;
            }
        }
        {
            typedef void (UQQCategory::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UQQCategory::indexChanged)) {
                *result = 3;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject UQQCategory::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_UQQCategory.data,
      qt_meta_data_UQQCategory,  qt_static_metacall, 0, 0}
};


const QMetaObject *UQQCategory::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UQQCategory::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_UQQCategory.stringdata))
        return static_cast<void*>(const_cast< UQQCategory*>(this));
    return QObject::qt_metacast(_clname);
}

int UQQCategory::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = name(); break;
        case 1: *reinterpret_cast< int*>(_v) = online(); break;
        case 2: *reinterpret_cast< int*>(_v) = total(); break;
        case 3: *reinterpret_cast< int*>(_v) = index(); break;
        }
        _id -= 4;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setName(*reinterpret_cast< QString*>(_v)); break;
        case 1: setOnline(*reinterpret_cast< int*>(_v)); break;
        case 2: setTotal(*reinterpret_cast< int*>(_v)); break;
        }
        _id -= 4;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 4;
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void UQQCategory::nameChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void UQQCategory::onlineChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void UQQCategory::totalChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void UQQCategory::indexChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}
QT_END_MOC_NAMESPACE
