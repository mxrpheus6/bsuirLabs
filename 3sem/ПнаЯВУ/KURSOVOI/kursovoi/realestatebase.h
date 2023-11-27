#ifndef REALESTATEBASE_H
#define REALESTATEBASE_H

/*#define TABLE_NAME "Estate"
#define ID_COL 0
#define PROPERTY_TYPE_COL 1
#define DEAL_TYPE_COL 2
#define DISTRICT_COL 3
#define ADDRESS_COL 4
#define DESCRIPTION_COL 5
#define SQUARE_COL 6
#define FLOOR_AMOUNT_COL 7
#define YEAR_COL 8
#define PRICE_COL 9*/

#include "defines.h"

#include <cfloat>

#include <QWidget>
#include <QtSql>
#include <QDataWidgetMapper>
#include <QStringList>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QMessageBox>

#include "objectoverview.h"
#include "objectadding.h"

namespace Ui {
class RealEstateBase;
}

class RealEstateBase : public QWidget
{
    Q_OBJECT

public:
    explicit RealEstateBase(QWidget *parent, QString tableName);
    ~RealEstateBase();
    static bool numericCompare(const QString &str1, const QString &str2);
    QStandardItemModel* applyFilterCombobox(QAbstractItemModel *originalModel, int colIndex, QComboBox *cb);
    QStandardItemModel* applyFilterLineEdit(QAbstractItemModel *originalModel, int colIndex, QLineEdit *from, QLineEdit *to);
    void setFilters();
    void createEmptyTable(QSqlTableModel *model);
    int findID(QAbstractItemModel* model, int ID);

public slots:
    void onObjectOverviewSaveClicked();

private slots:
    void on_checkBox_type_stateChanged(int arg1);

    void on_checkBox_district_stateChanged(int arg1);

    void on_checkBox_floor_amount_stateChanged(int arg1);

    void on_comboBox_type_activated(int index);

    void on_comboBox_district_activated(int index);

    void on_comboBox_floor_amount_activated(int index);

    void on_checkBox_square_stateChanged(int arg1);

    void on_checkBox_year_stateChanged(int arg1);

    void on_checkBox_price_stateChanged(int arg1);

    void on_lineEdit_square_from_textChanged(const QString &arg1);

    void on_lineEdit_square_to_textChanged(const QString &arg1);

    void on_lineEdit_year_from_textChanged(const QString &arg1);

    void on_lineEdit_year_to_textChanged(const QString &arg1);

    void on_lineEdit_price_from_textChanged(const QString &arg1);

    void on_lineEdit_price_to_textChanged(const QString &arg1);

    void on_tableView_estate_clicked(const QModelIndex &index);

    void on_pushButton_delete_clicked();

    void on_pushButton_estate_clicked();

    void on_checkBox_deal_stateChanged(int arg1);

    void on_comboBox_deal_activated(int index);

    void on_pushButton_add_clicked();

private:
    Ui::RealEstateBase *ui;
    QSqlTableModel *model;
    QAbstractItemModel *resModel;

    QDoubleValidator *doubleValidator;
    QIntValidator *intValidator;

    int currentRow = -1;
};

#endif // REALESTATEBASE_H
