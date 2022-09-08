/****************************************************************************
** Meta object code from reading C++ file 'map3dwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "map3dwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'map3dwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Map3dWidget_t {
    QByteArrayData data[5];
    char stringdata0[38];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Map3dWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Map3dWidget_t qt_meta_stringdata_Map3dWidget = {
    {
QT_MOC_LITERAL(0, 0, 11), // "Map3dWidget"
QT_MOC_LITERAL(1, 12, 7), // "setZoom"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 4), // "home"
QT_MOC_LITERAL(4, 26, 11) // "typeChanged"

    },
    "Map3dWidget\0setZoom\0\0home\0typeChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Map3dWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x0a /* Public */,
       3,    0,   32,    2, 0x0a /* Public */,
       4,    1,   33,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,

       0        // eod
};

void Map3dWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Map3dWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setZoom((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: _t->home(); break;
        case 2: _t->typeChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Map3dWidget::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_Map3dWidget.data,
    qt_meta_data_Map3dWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Map3dWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Map3dWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Map3dWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Map3dWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
