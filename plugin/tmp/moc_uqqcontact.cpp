/****************************************************************************
** Meta object code from reading C++ file 'uqqcontact.h'
**
** Created: Fri Mar 22 20:14:42 2013
**      by: The Qt Meta Object Compiler version 67 (Qt 5.0.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../uqqcontact.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'uqqcontact.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.0.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_UQQContact_t {
    QByteArrayData data[4];
    char stringdata[32];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_UQQContact_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_UQQContact_t qt_meta_stringdata_UQQContact = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 13),
QT_MOC_LITERAL(2, 25, 0),
QT_MOC_LITERAL(3, 26, 4)
    },
    "UQQContact\0categoryReady\0\0json\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UQQContact[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x05,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,

       0        // eod
};

void UQQContact::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        UQQContact *_t = static_cast<UQQContact *>(_o);
        switch (_id) {
        case 0: _t->categoryReady((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (UQQContact::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&UQQContact::categoryReady)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject UQQContact::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_UQQContact.data,
      qt_meta_data_UQQContact,  qt_static_metacall, 0, 0}
};


const QMetaObject *UQQContact::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UQQContact::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_UQQContact.stringdata))
        return static_cast<void*>(const_cast< UQQContact*>(this));
    return QObject::qt_metacast(_clname);
}

int UQQContact::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void UQQContact::categoryReady(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
