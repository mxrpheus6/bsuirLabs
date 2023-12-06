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
    const uint offsetsAndSize[36];
    char stringdata0[456];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_objectOverview_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_objectOverview_t qt_meta_stringdata_objectOverview = {
    {
QT_MOC_LITERAL(0, 14), // "objectOverview"
QT_MOC_LITERAL(15, 25), // "saveButtonClickedOverview"
QT_MOC_LITERAL(41, 0), // ""
QT_MOC_LITERAL(42, 29), // "on_checkBox_deal_stateChanged"
QT_MOC_LITERAL(72, 4), // "arg1"
QT_MOC_LITERAL(77, 26), // "on_pushButton_save_clicked"
QT_MOC_LITERAL(104, 40), // "on_plainTextEdit_description_..."
QT_MOC_LITERAL(145, 31), // "on_lineEdit_address_textChanged"
QT_MOC_LITERAL(177, 29), // "on_lineEdit_price_textChanged"
QT_MOC_LITERAL(207, 30), // "on_lineEdit_square_textChanged"
QT_MOC_LITERAL(238, 28), // "on_lineEdit_year_textChanged"
QT_MOC_LITERAL(267, 36), // "on_lineEdit_floor_amount_text..."
QT_MOC_LITERAL(304, 26), // "on_pushButton_deal_clicked"
QT_MOC_LITERAL(331, 29), // "on_comboBox_rieltor_activated"
QT_MOC_LITERAL(361, 5), // "index"
QT_MOC_LITERAL(367, 28), // "on_comboBox_client_activated"
QT_MOC_LITERAL(396, 29), // "on_checkBox_auth_stateChanged"
QT_MOC_LITERAL(426, 29) // "on_pushButton_request_clicked"

    },
    "objectOverview\0saveButtonClickedOverview\0"
    "\0on_checkBox_deal_stateChanged\0arg1\0"
    "on_pushButton_save_clicked\0"
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
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   98,    2, 0x06,    1 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       3,    1,   99,    2, 0x08,    2 /* Private */,
       5,    0,  102,    2, 0x08,    4 /* Private */,
       6,    0,  103,    2, 0x08,    5 /* Private */,
       7,    1,  104,    2, 0x08,    6 /* Private */,
       8,    1,  107,    2, 0x08,    8 /* Private */,
       9,    1,  110,    2, 0x08,   10 /* Private */,
      10,    1,  113,    2, 0x08,   12 /* Private */,
      11,    1,  116,    2, 0x08,   14 /* Private */,
      12,    0,  119,    2, 0x08,   16 /* Private */,
      13,    1,  120,    2, 0x08,   17 /* Private */,
      15,    1,  123,    2, 0x08,   19 /* Private */,
      16,    1,  126,    2, 0x08,   21 /* Private */,
      17,    0,  129,    2, 0x08,   23 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void,

       0        // eod
};

void objectOverview::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<objectOverview *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->saveButtonClickedOverview(); break;
        case 1: _t->on_checkBox_deal_stateChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 2: _t->on_pushButton_save_clicked(); break;
        case 3: _t->on_plainTextEdit_description_textChanged(); break;
        case 4: _t->on_lineEdit_address_textChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 5: _t->on_lineEdit_price_textChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 6: _t->on_lineEdit_square_textChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 7: _t->on_lineEdit_year_textChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 8: _t->on_lineEdit_floor_amount_textChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 9: _t->on_pushButton_deal_clicked(); break;
        case 10: _t->on_comboBox_rieltor_activated((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 11: _t->on_comboBox_client_activated((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 12: _t->on_checkBox_auth_stateChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 13: _t->on_pushButton_request_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (objectOverview::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&objectOverview::saveButtonClickedOverview)) {
                *result = 0;
                return;
            }
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
, QtPrivate::TypeAndForceComplete<objectOverview, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>
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
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void objectOverview::saveButtonClickedOverview()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
