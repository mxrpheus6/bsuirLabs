/****************************************************************************
** Meta object code from reading C++ file 'menudatawidget.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../kursovoi/menudatawidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'menudatawidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MenuDataWidget_t {
    const uint offsetsAndSize[16];
    char stringdata0[135];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_MenuDataWidget_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_MenuDataWidget_t qt_meta_stringdata_MenuDataWidget = {
    {
QT_MOC_LITERAL(0, 14), // "MenuDataWidget"
QT_MOC_LITERAL(15, 25), // "on_pushButton_add_clicked"
QT_MOC_LITERAL(41, 0), // ""
QT_MOC_LITERAL(42, 25), // "on_pushButton_del_clicked"
QT_MOC_LITERAL(68, 23), // "on_tableView_db_clicked"
QT_MOC_LITERAL(92, 11), // "QModelIndex"
QT_MOC_LITERAL(104, 5), // "index"
QT_MOC_LITERAL(110, 24) // "on_pushButtonAdd_clicked"

    },
    "MenuDataWidget\0on_pushButton_add_clicked\0"
    "\0on_pushButton_del_clicked\0"
    "on_tableView_db_clicked\0QModelIndex\0"
    "index\0on_pushButtonAdd_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MenuDataWidget[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   38,    2, 0x08,    1 /* Private */,
       3,    0,   39,    2, 0x08,    2 /* Private */,
       4,    1,   40,    2, 0x08,    3 /* Private */,
       7,    0,   43,    2, 0x08,    5 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,

       0        // eod
};

void MenuDataWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MenuDataWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_pushButton_add_clicked(); break;
        case 1: _t->on_pushButton_del_clicked(); break;
        case 2: _t->on_tableView_db_clicked((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1]))); break;
        case 3: _t->on_pushButtonAdd_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject MenuDataWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_MenuDataWidget.offsetsAndSize,
    qt_meta_data_MenuDataWidget,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_MenuDataWidget_t
, QtPrivate::TypeAndForceComplete<MenuDataWidget, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QModelIndex &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *MenuDataWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MenuDataWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MenuDataWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int MenuDataWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
