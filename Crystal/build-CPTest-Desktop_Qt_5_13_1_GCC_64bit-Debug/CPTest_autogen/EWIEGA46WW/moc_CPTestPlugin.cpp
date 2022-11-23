/****************************************************************************
** Meta object code from reading C++ file 'CPTestPlugin.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../CPTest/CPTestPlugin.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/qplugin.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CPTestPlugin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CPTestPlugin_t {
    QByteArrayData data[1];
    char stringdata0[13];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CPTestPlugin_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CPTestPlugin_t qt_meta_stringdata_CPTestPlugin = {
    {
QT_MOC_LITERAL(0, 0, 12) // "CPTestPlugin"

    },
    "CPTestPlugin"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CPTestPlugin[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void CPTestPlugin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject CPTestPlugin::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_CPTestPlugin.data,
    qt_meta_data_CPTestPlugin,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CPTestPlugin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CPTestPlugin::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CPTestPlugin.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "CrystalPluginInterface"))
        return static_cast< CrystalPluginInterface*>(this);
    if (!strcmp(_clname, "ali.askari.crystal"))
        return static_cast< CrystalPluginInterface*>(this);
    return QObject::qt_metacast(_clname);
}

int CPTestPlugin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    return _id;
}

QT_PLUGIN_METADATA_SECTION
static constexpr unsigned char qt_pluginMetaData[] = {
    'Q', 'T', 'M', 'E', 'T', 'A', 'D', 'A', 'T', 'A', ' ', '!',
    // metadata version, Qt version, architectural requirements
    0, QT_VERSION_MAJOR, QT_VERSION_MINOR, qPluginArchRequirements(),
    0xbf, 
    // "IID"
    0x02,  0x72,  'a',  'l',  'i',  '.',  'a',  's', 
    'k',  'a',  'r',  'i',  '.',  'c',  'r',  'y', 
    's',  't',  'a',  'l', 
    // "className"
    0x03,  0x6c,  'C',  'P',  'T',  'e',  's',  't', 
    'P',  'l',  'u',  'g',  'i',  'n', 
    // "MetaData"
    0x04,  0xa1,  0x64,  'K',  'e',  'y',  's',  0x80, 
    0xff, 
};
QT_MOC_EXPORT_PLUGIN(CPTestPlugin, CPTestPlugin)

QT_WARNING_POP
QT_END_MOC_NAMESPACE
