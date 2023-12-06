#ifndef REALESTATEBASE_H
#define REALESTATEBASE_H

#include "defines.h"

#include <cfloat>


#include <QWidget>
#include <QtSql>
#include <QDataWidgetMapper>
#include <QStringList>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QMessageBox>
#include <QMenuBar>

#include "objectoverview.h"
#include "objectadding.h"

namespace Ui {
class RealEstateBase;
}

class RealEstateBase : public QWidget
{
    Q_OBJECT

public:
    explicit RealEstateBase(QWidget *parent, QString mode, QString access = "rieltor", int ID = -1);
    ~RealEstateBase();
    static bool numericCompare(const QString &str1, const QString &str2);
    QStandardItemModel* applyFilterCombobox(QAbstractItemModel *originalModel, int colIndex, QComboBox *cb);
    QStandardItemModel* applyFilterLineEdit(QAbstractItemModel *originalModel, int colIndex, QLineEdit *from, QLineEdit *to);
    void setFilters();
    void createEmptyTable(QSqlTableModel *model);
    int findID(QAbstractItemModel* model, int ID);
    int findIDTwoFields(QAbstractItemModel* model, int ID1, int ID2);
    QStandardItemModel* baseFilter(QAbstractItemModel *originalModel);
    QStandardItemModel* requestsFilter(QAbstractItemModel *originalModel);
    QStandardItemModel* purchasesFilter(QAbstractItemModel *originalModel);

public slots:
    void onObjectOverviewSaveClicked();

private slots:
    void on_checkBox_type_stateChanged(int arg1);

    void on_checkBox_district_stateChanged(int arg1);

    void on_checkBox_floor_amount_stateChanged(int arg1);

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

    void on_pushButton_add_clicked();

    void on_comboBox_type_currentTextChanged(const QString &arg1);

    void on_comboBox_district_currentTextChanged(const QString &arg1);

    void on_comboBox_floor_amount_currentTextChanged(const QString &arg1);

    void on_comboBox_deal_currentTextChanged(const QString &arg1);

    void on_pushButton_reject_clicked();

private:
    Ui::RealEstateBase *ui;
    QSqlTableModel *model;
    QAbstractItemModel *resModel;

    QDoubleValidator *doubleValidator;
    QIntValidator *intValidator;

    QString mode;
    QString access;
    int userID;
    int currentRow = -1;
};

#endif // REALESTATEBASE_H
