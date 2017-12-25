/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[25];
    char stringdata0[394];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 16), // "OnDisplayVehData"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 11), // "DisplayData"
QT_MOC_LITERAL(4, 41, 17), // "OnDisplayNaviPath"
QT_MOC_LITERAL(5, 59, 15), // "vector<PointXY>"
QT_MOC_LITERAL(6, 75, 18), // "OnDisplayLocalPath"
QT_MOC_LITERAL(7, 94, 24), // "OnDisplayGlobalLocalPath"
QT_MOC_LITERAL(8, 119, 19), // "OnDisplayGlobalPath"
QT_MOC_LITERAL(9, 139, 26), // "OnDisplayGlobalCurrentPath"
QT_MOC_LITERAL(10, 166, 7), // "PointXY"
QT_MOC_LITERAL(11, 174, 16), // "OnDriveOperation"
QT_MOC_LITERAL(12, 191, 19), // "OnSpeedSetOperation"
QT_MOC_LITERAL(13, 211, 21), // "OnChangeLeftOperation"
QT_MOC_LITERAL(14, 233, 22), // "OnChangeRightOperation"
QT_MOC_LITERAL(15, 256, 23), // "OnResetBehaviorSemiAuto"
QT_MOC_LITERAL(16, 280, 19), // "OnOpenControlButton"
QT_MOC_LITERAL(17, 300, 14), // "MouseMoveEvent"
QT_MOC_LITERAL(18, 315, 12), // "QMouseEvent*"
QT_MOC_LITERAL(19, 328, 5), // "event"
QT_MOC_LITERAL(20, 334, 10), // "WheelEvent"
QT_MOC_LITERAL(21, 345, 12), // "QWheelEvent*"
QT_MOC_LITERAL(22, 358, 22), // "SetPosInLocalSceneList"
QT_MOC_LITERAL(23, 381, 8), // "Obstacle"
QT_MOC_LITERAL(24, 390, 3) // "obs"

    },
    "MainWindow\0OnDisplayVehData\0\0DisplayData\0"
    "OnDisplayNaviPath\0vector<PointXY>\0"
    "OnDisplayLocalPath\0OnDisplayGlobalLocalPath\0"
    "OnDisplayGlobalPath\0OnDisplayGlobalCurrentPath\0"
    "PointXY\0OnDriveOperation\0OnSpeedSetOperation\0"
    "OnChangeLeftOperation\0OnChangeRightOperation\0"
    "OnResetBehaviorSemiAuto\0OnOpenControlButton\0"
    "MouseMoveEvent\0QMouseEvent*\0event\0"
    "WheelEvent\0QWheelEvent*\0SetPosInLocalSceneList\0"
    "Obstacle\0obs"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   89,    2, 0x0a /* Public */,
       4,    1,   92,    2, 0x0a /* Public */,
       6,    1,   95,    2, 0x0a /* Public */,
       7,    1,   98,    2, 0x0a /* Public */,
       8,    1,  101,    2, 0x0a /* Public */,
       9,    1,  104,    2, 0x0a /* Public */,
      11,    0,  107,    2, 0x0a /* Public */,
      12,    1,  108,    2, 0x0a /* Public */,
      13,    0,  111,    2, 0x0a /* Public */,
      14,    0,  112,    2, 0x0a /* Public */,
      15,    0,  113,    2, 0x0a /* Public */,
      16,    0,  114,    2, 0x0a /* Public */,
      17,    1,  115,    2, 0x0a /* Public */,
      20,    1,  118,    2, 0x0a /* Public */,
      22,    1,  121,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void, 0x80000000 | 10,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 18,   19,
    QMetaType::Void, 0x80000000 | 21,   19,
    0x80000000 | 10, 0x80000000 | 23,   24,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->OnDisplayVehData((*reinterpret_cast< DisplayData(*)>(_a[1]))); break;
        case 1: _t->OnDisplayNaviPath((*reinterpret_cast< vector<PointXY>(*)>(_a[1]))); break;
        case 2: _t->OnDisplayLocalPath((*reinterpret_cast< vector<PointXY>(*)>(_a[1]))); break;
        case 3: _t->OnDisplayGlobalLocalPath((*reinterpret_cast< vector<PointXY>(*)>(_a[1]))); break;
        case 4: _t->OnDisplayGlobalPath((*reinterpret_cast< vector<PointXY>(*)>(_a[1]))); break;
        case 5: _t->OnDisplayGlobalCurrentPath((*reinterpret_cast< PointXY(*)>(_a[1]))); break;
        case 6: _t->OnDriveOperation(); break;
        case 7: _t->OnSpeedSetOperation((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->OnChangeLeftOperation(); break;
        case 9: _t->OnChangeRightOperation(); break;
        case 10: _t->OnResetBehaviorSemiAuto(); break;
        case 11: _t->OnOpenControlButton(); break;
        case 12: _t->MouseMoveEvent((*reinterpret_cast< QMouseEvent*(*)>(_a[1]))); break;
        case 13: _t->WheelEvent((*reinterpret_cast< QWheelEvent*(*)>(_a[1]))); break;
        case 14: { PointXY _r = _t->SetPosInLocalSceneList((*reinterpret_cast< Obstacle(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< PointXY*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
