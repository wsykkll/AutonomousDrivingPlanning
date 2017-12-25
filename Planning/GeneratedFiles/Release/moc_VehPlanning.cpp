/****************************************************************************
** Meta object code from reading C++ file 'VehPlanning.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../VehPlanning.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'VehPlanning.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CVehPlanning_t {
    QByteArrayData data[11];
    char stringdata0[164];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CVehPlanning_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CVehPlanning_t qt_meta_stringdata_CVehPlanning = {
    {
QT_MOC_LITERAL(0, 0, 12), // "CVehPlanning"
QT_MOC_LITERAL(1, 13, 14), // "DisplayVehData"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 11), // "DisplayData"
QT_MOC_LITERAL(4, 41, 15), // "DisplayNaviPath"
QT_MOC_LITERAL(5, 57, 15), // "vector<PointXY>"
QT_MOC_LITERAL(6, 73, 16), // "DisplayLocalPath"
QT_MOC_LITERAL(7, 90, 22), // "DisplayGlobalLocalPath"
QT_MOC_LITERAL(8, 113, 17), // "DisplayGlobalPath"
QT_MOC_LITERAL(9, 131, 24), // "DisplayGlobalCurrentPath"
QT_MOC_LITERAL(10, 156, 7) // "PointXY"

    },
    "CVehPlanning\0DisplayVehData\0\0DisplayData\0"
    "DisplayNaviPath\0vector<PointXY>\0"
    "DisplayLocalPath\0DisplayGlobalLocalPath\0"
    "DisplayGlobalPath\0DisplayGlobalCurrentPath\0"
    "PointXY"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CVehPlanning[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       4,    1,   47,    2, 0x06 /* Public */,
       6,    1,   50,    2, 0x06 /* Public */,
       7,    1,   53,    2, 0x06 /* Public */,
       8,    1,   56,    2, 0x06 /* Public */,
       9,    1,   59,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void, 0x80000000 | 10,    2,

       0        // eod
};

void CVehPlanning::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CVehPlanning *_t = static_cast<CVehPlanning *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->DisplayVehData((*reinterpret_cast< DisplayData(*)>(_a[1]))); break;
        case 1: _t->DisplayNaviPath((*reinterpret_cast< vector<PointXY>(*)>(_a[1]))); break;
        case 2: _t->DisplayLocalPath((*reinterpret_cast< vector<PointXY>(*)>(_a[1]))); break;
        case 3: _t->DisplayGlobalLocalPath((*reinterpret_cast< vector<PointXY>(*)>(_a[1]))); break;
        case 4: _t->DisplayGlobalPath((*reinterpret_cast< vector<PointXY>(*)>(_a[1]))); break;
        case 5: _t->DisplayGlobalCurrentPath((*reinterpret_cast< PointXY(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CVehPlanning::*_t)(DisplayData );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CVehPlanning::DisplayVehData)) {
                *result = 0;
            }
        }
        {
            typedef void (CVehPlanning::*_t)(vector<PointXY> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CVehPlanning::DisplayNaviPath)) {
                *result = 1;
            }
        }
        {
            typedef void (CVehPlanning::*_t)(vector<PointXY> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CVehPlanning::DisplayLocalPath)) {
                *result = 2;
            }
        }
        {
            typedef void (CVehPlanning::*_t)(vector<PointXY> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CVehPlanning::DisplayGlobalLocalPath)) {
                *result = 3;
            }
        }
        {
            typedef void (CVehPlanning::*_t)(vector<PointXY> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CVehPlanning::DisplayGlobalPath)) {
                *result = 4;
            }
        }
        {
            typedef void (CVehPlanning::*_t)(PointXY );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CVehPlanning::DisplayGlobalCurrentPath)) {
                *result = 5;
            }
        }
    }
}

const QMetaObject CVehPlanning::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CVehPlanning.data,
      qt_meta_data_CVehPlanning,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CVehPlanning::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CVehPlanning::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CVehPlanning.stringdata0))
        return static_cast<void*>(const_cast< CVehPlanning*>(this));
    return QObject::qt_metacast(_clname);
}

int CVehPlanning::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void CVehPlanning::DisplayVehData(DisplayData _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CVehPlanning::DisplayNaviPath(vector<PointXY> _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CVehPlanning::DisplayLocalPath(vector<PointXY> _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void CVehPlanning::DisplayGlobalLocalPath(vector<PointXY> _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void CVehPlanning::DisplayGlobalPath(vector<PointXY> _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void CVehPlanning::DisplayGlobalCurrentPath(PointXY _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_END_MOC_NAMESPACE
