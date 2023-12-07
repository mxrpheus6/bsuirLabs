#ifndef OBJECTOVERVIEW_H
#define OBJECTOVERVIEW_H

#include "defines.h"
#include "makedeal.h"
#include "realestate.h"
#include "apartment.h"
#include "house.h"
#include "office.h"


#include <QWidget>
#include <QtSql>
#include <QStandardItemModel>
#include <QTableWidgetItem>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QDebug>

namespace Ui {
class objectOverview;
}

class objectOverview : public QWidget
{
    Q_OBJECT

public:
    explicit objectOverview(QWidget *parent, QSqlTableModel* model, QAbstractItemModel* resModel, QString tableName, int objectRow, QString access, int ID);
    bool setRequests();
    void setPurhcases();
    int findID(QAbstractItemModel* model, int ID);
    void fillTableHeaders(QStandardItemModel* model, QString tableName);
    void updateExtended(const std::vector<QString> vector, int rowToUpdate);
    bool checkEmptySave();
    bool checkEmptyDeal();
    bool checkEmptyAuth();
    bool fillInherited(QString properyType);
    QVariant getDataFromItemModel(int row);

    ~objectOverview();

//signals:
    //void saveButtonClickedOverview();

private slots:
    void on_checkBox_deal_stateChanged(int arg1);

    void on_pushButton_save_clicked();

    void on_plainTextEdit_description_textChanged();

    void on_lineEdit_address_textChanged(const QString &arg1);

    void on_lineEdit_price_textChanged(const QString &arg1);

    void on_lineEdit_square_textChanged(const QString &arg1);

    void on_lineEdit_year_textChanged(const QString &arg1);

    void on_lineEdit_floor_amount_textChanged(const QString &arg1);

    void on_pushButton_deal_clicked();

    void on_comboBox_rieltor_activated(int index);

    void on_comboBox_client_activated(int index);

    void on_checkBox_auth_stateChanged(int arg1);

    void on_pushButton_request_clicked();

private:
    Ui::objectOverview *ui;
    QWidget *parent;
    QSqlTableModel* model;
    QSqlTableModel* extendedModel;
    QStandardItemModel *itemModel;

    QDoubleValidator *doubleValidator;
    QIntValidator *intValidator;

    RealEstate* realEstate = nullptr;
    Apartment* apartment = nullptr;
    House* house = nullptr;
    Office* office = nullptr;
    MakeDeal* makeDeal = nullptr;

    bool isRequested;
    int userID;

    const std::vector<QString> fields_apartment = {"Пл-дь кухни, м2", "Этажность", "Тип дома", "Балкон", "Лифт", "Потолок, м", "Паркинг", "Консьерж"};
    const std::vector<QString> fields_house = {"Пл-дь участка, м2", "Пл-дь кухни, м2", "Материал стен", "Материал крыши", "Камин", "Гараж", "Отопление", "Канализация", "Водоснабжение"};
    const std::vector<QString> fields_office = {"Класс", "Этажность", "Кол-во раб. мест", "Материал стен", "Ремонт", "Конференц залы", "Охрана", "Туалет"};
};

#endif // OBJECTOVERVIEW_H
