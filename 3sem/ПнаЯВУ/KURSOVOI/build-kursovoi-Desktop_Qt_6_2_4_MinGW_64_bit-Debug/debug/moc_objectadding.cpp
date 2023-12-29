/****************************************************************************
** Meta object code from reading C++ file 'objectadding.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../kursovoi/objectadding.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'objectadding.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_objectAdding_t {
    const uint offsetsAndSize[28];
    char stringdata0[347];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_objectAdding_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_objectAdding_t qt_meta_stringdata_objectAdding = {
    {
QT_MOC_LITERAL(0, 12), // "objectAdding"
QT_MOC_LITERAL(13, 26), // "on_pushButton_save_clicked"
QT_MOC_LITERAL(40, 0), // ""
QT_MOC_LITERAL(41, 40), // "on_plainTextEdit_description_..."
QT_MOC_LITERAL(82, 31), // "on_lineEdit_address_textChanged"
QT_MOC_LITERAL(114, 4), // "arg1"
QT_MOC_LITERAL(119, 30), // "on_lineEdit_square_textChanged"
QT_MOC_LITERAL(150, 28), // "on_lineEdit_year_textChanged"
QT_MOC_LITERAL(179, 36), // "on_lineEdit_floor_amount_text..."
QT_MOC_LITERAL(216, 29), // "on_lineEdit_price_textChanged"
QT_MOC_LITERAL(246, 26), // "on_comboBox_deal_activated"
QT_MOC_LITERAL(273, 5), // "index"
QT_MOC_LITERAL(279, 30), // "on_comboBox_district_activated"
QT_MOC_LITERAL(310, 36) // "on_comboBox_type_currentIndex..."

    },
    "objectAdding\0on_pushButton_save_clicked\0"
    "\0on_plainTextEdit_description_textChanged\0"
    "on_lineEdit_address_textChanged\0arg1\0"
    "on_lineEdit_square_textChanged\0"
    "on_lineEdit_year_textChanged\0"
    "on_lineEdit_floor_amount_textChanged\0"
    "on_lineEdit_price_textChanged\0"
    "on_comboBox_deal_activated\0index\0"
    "on_comboBox_district_activated\0"
    "on_comboBox_type_currentIndexChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_objectAdding[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   74,    2, 0x08,    1 /* Private */,
       3,    0,   75,    2, 0x08,    2 /* Private */,
       4,    1,   76,    2, 0x08,    3 /* Private */,
       6,    1,   79,    2, 0x08,    5 /* Private */,
       7,    1,   82,    2, 0x08,    7 /* Private */,
       8,    1,   85,    2, 0x08,    9 /* Private */,
       9,    1,   88,    2, 0x08,   11 /* Private */,
      10,    1,   91,    2, 0x08,   13 /* Private */,
      12,    1,   94,    2, 0x08,   15 /* Private */,
      13,    1,   97,    2, 0x08,   17 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::Int,   11,

       0        // eod
};

void objectAdding::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<objectAdding *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_pushButton_save_clicked(); break;
        case 1: _t->on_plainTextEdit_description_textChanged(); break;
        case 2: _t->on_lineEdit_address_textChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->on_lineEdit_square_textChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 4: _t->on_lineEdit_year_textChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 5: _t->on_lineEdit_floor_amount_textChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 6: _t->on_lineEdit_price_textChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 7: _t->on_comboBox_deal_activated((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 8: _t->on_comboBox_district_activated((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 9: _t->on_comboBox_type_currentIndexChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject objectAdding::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_objectAdding.offsetsAndSize,
    qt_meta_data_objectAdding,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_objectAdding_t
, QtPrivate::TypeAndForceComplete<objectAdding, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>


>,
    nullptr
} };


const QMetaObject *objectAdding::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *objectAdding::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_objectAdding.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int objectAdding::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
