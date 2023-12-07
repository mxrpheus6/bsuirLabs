/****************************************************************************
** Meta object code from reading C++ file 'objectoverview.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../kursovoi/objectoverview.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'objectoverview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_objectOverview_t {
    const uint offsetsAndSize[34];
    char stringdata0[430];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_objectOverview_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_objectOverview_t qt_meta_stringdata_objectOverview = {
    {
QT_MOC_LITERAL(0, 14), // "objectOverview"
QT_MOC_LITERAL(15, 29), // "on_checkBox_deal_stateChanged"
QT_MOC_LITERAL(45, 0), // ""
QT_MOC_LITERAL(46, 4), // "arg1"
QT_MOC_LITERAL(51, 26), // "on_pushButton_save_clicked"
QT_MOC_LITERAL(78, 40), // "on_plainTextEdit_description_..."
QT_MOC_LITERAL(119, 31), // "on_lineEdit_address_textChanged"
QT_MOC_LITERAL(151, 29), // "on_lineEdit_price_textChanged"
QT_MOC_LITERAL(181, 30), // "on_lineEdit_square_textChanged"
QT_MOC_LITERAL(212, 28), // "on_lineEdit_year_textChanged"
QT_MOC_LITERAL(241, 36), // "on_lineEdit_floor_amount_text..."
QT_MOC_LITERAL(278, 26), // "on_pushButton_deal_clicked"
QT_MOC_LITERAL(305, 29), // "on_comboBox_rieltor_activated"
QT_MOC_LITERAL(335, 5), // "index"
QT_MOC_LITERAL(341, 28), // "on_comboBox_client_activated"
QT_MOC_LITERAL(370, 29), // "on_checkBox_auth_stateChanged"
QT_MOC_LITERAL(400, 29) // "on_pushButton_request_clicked"

    },
    "objectOverview\0on_checkBox_deal_stateChanged\0"
    "\0arg1\0on_pushButton_save_clicked\0"
    "on_plainTextEdit_description_textChanged\0"
    "on_lineEdit_address_textChanged\0"
    "on_lineEdit_price_textChanged\0"
    "on_lineEdit_square_textChanged\0"
    "on_lineEdit_year_textChanged\0"
    "on_lineEdit_floor_amount_textChanged\0"
    "on_pushButton_deal_clicked\0"
    "on_comboBox_rieltor_activated\0index\0"
    "on_comboBox_client_activated\0"
    "on_checkBox_auth_stateChanged\0"
    "on_pushButton_request_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_objectOverview[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   92,    2, 0x08,    1 /* Private */,
       4,    0,   95,    2, 0x08,    3 /* Private */,
       5,    0,   96,    2, 0x08,    4 /* Private */,
       6,    1,   97,    2, 0x08,    5 /* Private */,
       7,    1,  100,    2, 0x08,    7 /* Private */,
       8,    1,  103,    2, 0x08,    9 /* Private */,
       9,    1,  106,    2, 0x08,   11 /* Private */,
      10,    1,  109,    2, 0x08,   13 /* Private */,
      11,    0,  112,    2, 0x08,   15 /* Private */,
      12,    1,  113,    2, 0x08,   16 /* Private */,
      14,    1,  116,    2, 0x08,   18 /* Private */,
      15,    1,  119,    2, 0x08,   20 /* Private */,
      16,    0,  122,    2, 0x08,   22 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,

       0        // eod
};

void objectOverview::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<objectOverview *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_checkBox_deal_stateChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 1: _t->on_pushButton_save_clicked(); break;
        case 2: _t->on_plainTextEdit_description_textChanged(); break;
        case 3: _t->on_lineEdit_address_textChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 4: _t->on_lineEdit_price_textChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 5: _t->on_lineEdit_square_textChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 6: _t->on_lineEdit_year_textChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 7: _t->on_lineEdit_floor_amount_textChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 8: _t->on_pushButton_deal_clicked(); break;
        case 9: _t->on_comboBox_rieltor_activated((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 10: _t->on_comboBox_client_activated((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 11: _t->on_checkBox_auth_stateChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 12: _t->on_pushButton_request_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject objectOverview::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_objectOverview.offsetsAndSize,
    qt_meta_data_objectOverview,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_objectOverview_t
, QtPrivate::TypeAndForceComplete<objectOverview, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *objectOverview::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *objectOverview::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_objectOverview.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int objectOverview::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 13;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
