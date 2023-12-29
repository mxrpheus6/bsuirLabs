#ifndef OBJECTADDING_H
#define OBJECTADDING_H

#include <QWidget>
#include <QSqlTableModel>
#include <QStandardItem>
#include <QMessageBox>
#include <QDebug>


#include "realestate.h"
#include "apartment.h"
#include "house.h"
#include "office.h"
#include "defines.h"

namespace Ui {
class objectAdding;
}

class objectAdding : public QWidget
{
    Q_OBJECT

public:
    explicit objectAdding(QWidget *parent, QSqlTableModel* originalModel);
    ~objectAdding();
    int generateID();
    bool checkEmpty();
    void fillTableHeaders(QStandardItemModel* model);
    //void updateExtended(const std::vector<QString> vector, int rowToUpdate);
    bool fillInherited(QString properyType);
    QVariant getDataFromItemModel(int row);
    bool setСommonFields(RealEstate* estate);

private slots:
    void on_pushButton_save_clicked();

    void on_plainTextEdit_description_textChanged();

    void on_lineEdit_address_textChanged(const QString &arg1);

    void on_lineEdit_square_textChanged(const QString &arg1);

    void on_lineEdit_year_textChanged(const QString &arg1);

    void on_lineEdit_floor_amount_textChanged(const QString &arg1);

    void on_lineEdit_price_textChanged(const QString &arg1);

    void on_comboBox_deal_activated(int index);

    void on_comboBox_district_activated(int index);

    void on_comboBox_type_currentIndexChanged(int index);

private:
    Ui::objectAdding *ui;
    QWidget* parent;
    QSqlTableModel* model;
    QSqlTableModel* extendedModel;
    QStandardItemModel* itemModel;

    //RealEstate* realEstate = nullptr;
    Apartment* apartment = nullptr;
    House* house = nullptr;
    Office* office = nullptr;


    const std::vector<QString> fields_apartment = {"Пл-дь кухни, м2", "Этажность", "Тип дома", "Балкон", "Лифт", "Потолок, м", "Паркинг", "Консьерж"};
    const std::vector<QString> fields_house = {"Пл-дь участка, м2", "Пл-дь кухни, м2", "Материал стен", "Материал крыши", "Камин", "Гараж", "Отопление", "Канализация", "Водоснабжение"};
    const std::vector<QString> fields_office = {"Класс", "Этажность", "Кол-во раб. мест", "Материал стен", "Ремонт", "Конференц залы", "Охрана", "Туалет"};
};

#endif // OBJECTADDING_H
