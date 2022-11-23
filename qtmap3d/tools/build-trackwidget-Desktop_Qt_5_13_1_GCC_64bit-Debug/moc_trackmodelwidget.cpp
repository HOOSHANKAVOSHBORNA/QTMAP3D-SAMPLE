/****************************************************************************
** Meta object code from reading C++ file 'trackmodelwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../trackwidget/trackmodelwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'trackmodelwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TrackModelWidget_t {
    QByteArrayData data[20];
    char stringdata0[164];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TrackModelWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TrackModelWidget_t qt_meta_stringdata_TrackModelWidget = {
    {
QT_MOC_LITERAL(0, 0, 16), // "TrackModelWidget"
QT_MOC_LITERAL(1, 17, 14), // "onModelClicked"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 4), // "type"
QT_MOC_LITERAL(4, 38, 4), // "name"
QT_MOC_LITERAL(5, 43, 10), // "modelAdded"
QT_MOC_LITERAL(6, 54, 11), // "modelRemove"
QT_MOC_LITERAL(7, 66, 5), // "onPin"
QT_MOC_LITERAL(8, 72, 1), // "t"
QT_MOC_LITERAL(9, 74, 9), // "modelInfo"
QT_MOC_LITERAL(10, 84, 1), // "n"
QT_MOC_LITERAL(11, 86, 3), // "str"
QT_MOC_LITERAL(12, 90, 5), // "close"
QT_MOC_LITERAL(13, 96, 8), // "minimize"
QT_MOC_LITERAL(14, 105, 5), // "isMax"
QT_MOC_LITERAL(15, 111, 13), // "modelPosition"
QT_MOC_LITERAL(16, 125, 8), // "latitude"
QT_MOC_LITERAL(17, 134, 9), // "longitude"
QT_MOC_LITERAL(18, 144, 8), // "altitude"
QT_MOC_LITERAL(19, 153, 10) // "changeSize"

    },
    "TrackModelWidget\0onModelClicked\0\0type\0"
    "name\0modelAdded\0modelRemove\0onPin\0t\0"
    "modelInfo\0n\0str\0close\0minimize\0isMax\0"
    "modelPosition\0latitude\0longitude\0"
    "altitude\0changeSize"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TrackModelWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   59,    2, 0x06 /* Public */,
       5,    2,   64,    2, 0x06 /* Public */,
       6,    2,   69,    2, 0x06 /* Public */,
       7,    1,   74,    2, 0x06 /* Public */,
       9,    3,   77,    2, 0x06 /* Public */,
      12,    0,   84,    2, 0x06 /* Public */,
      13,    1,   85,    2, 0x06 /* Public */,
      15,    5,   88,    2, 0x06 /* Public */,
      19,    1,   99,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    4,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    4,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    4,
    QMetaType::Void, QMetaType::Bool,    8,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,    8,   10,   11,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   14,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Double, QMetaType::Double, QMetaType::Double,    8,   10,   16,   17,   18,
    QMetaType::Void, QMetaType::Bool,    8,

       0        // eod
};

void TrackModelWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TrackModelWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onModelClicked((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->modelAdded((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 2: _t->modelRemove((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 3: _t->onPin((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->modelInfo((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 5: _t->close(); break;
        case 6: _t->minimize((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->modelPosition((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4])),(*reinterpret_cast< double(*)>(_a[5]))); break;
        case 8: _t->changeSize((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TrackModelWidget::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TrackModelWidget::onModelClicked)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (TrackModelWidget::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TrackModelWidget::modelAdded)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (TrackModelWidget::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TrackModelWidget::modelRemove)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (TrackModelWidget::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TrackModelWidget::onPin)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (TrackModelWidget::*)(QString , QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TrackModelWidget::modelInfo)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (TrackModelWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TrackModelWidget::close)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (TrackModelWidget::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TrackModelWidget::minimize)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (TrackModelWidget::*)(QString , QString , double , double , double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TrackModelWidget::modelPosition)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (TrackModelWidget::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TrackModelWidget::changeSize)) {
                *result = 8;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject TrackModelWidget::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_TrackModelWidget.data,
    qt_meta_data_TrackModelWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TrackModelWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TrackModelWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TrackModelWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int TrackModelWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void TrackModelWidget::onModelClicked(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TrackModelWidget::modelAdded(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void TrackModelWidget::modelRemove(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void TrackModelWidget::onPin(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void TrackModelWidget::modelInfo(QString _t1, QString _t2, QString _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void TrackModelWidget::close()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void TrackModelWidget::minimize(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void TrackModelWidget::modelPosition(QString _t1, QString _t2, double _t3, double _t4, double _t5)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t5))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void TrackModelWidget::changeSize(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
