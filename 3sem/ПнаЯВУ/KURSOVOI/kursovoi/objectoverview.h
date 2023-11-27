#ifndef OBJECTOVERVIEW_H
#define OBJECTOVERVIEW_H

/*#define ID_COL 0
#define PROPERTY_TYPE_COL 1
#define DEAL_TYPE_COL 2
#define DISTRICT_COL 3
#define ADDRESS_COL 4
#define DESCRIPTION_COL 5
#define SQUARE_COL 6
#define FLOOR_AMOUNT_COL 7
#define YEAR_COL 8
#define PRICE_COL 9

#define APARTMENT_RUS "Квартира"
#define HOUSE_RUS "Дом"
#define OFFICE_RUS "Офис"

#define DEALS_ARR {"Продажа", "Аренда"}*/

#include "defines.h"


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
    explicit objectOverview(QWidget *parent, QSqlTableModel* originalModel, QAbstractItemModel* resModel, QString tableName, int objectRow);

    int findID(QAbstractItemModel* model);
    void fillTableHeaders(QStandardItemModel* model, QString tableName);
    void updateExtended(const std::vector<QString> vector, int rowToUpdate);

    ~objectOverview();

signals:
    void saveButtonClicked();

private slots:
    void on_checkBox_deal_stateChanged(int arg1);

    void on_pushButton_save_clicked();

private:
    Ui::objectOverview *ui;
    QSqlTableModel* model;
    QSqlTableModel* extendedModel;
    QStandardItemModel *itemModel;

    const std::vector<QString> fields_apartment = {"Пл-дь кухни, м2", "Этажность", "Тип дома", "Балкон", "Лифт", "Потолок, м", "Паркинг", "Консьерж"};
    const std::vector<QString> fields_house = {"Пл-дь участка, м2", "Пл-дь кухни, м2", "Материал стен", "Материал крыши", "Камин", "Гараж", "Отопление", "Канализация", "Водоснабжение"};
    const std::vector<QString> fields_office = {"Класс", "Этажность", "Кол-во раб. мест", "Материал стен", "Ремонт", "Конференц залы", "Охрана", "Туалет"};
};

#endif // OBJECTOVERVIEW_H
