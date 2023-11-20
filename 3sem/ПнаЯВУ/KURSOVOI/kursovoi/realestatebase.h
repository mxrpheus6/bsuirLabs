#ifndef REALESTATEBASE_H
#define REALESTATEBASE_H

#define TABLE_NAME "Estate"

#include <cfloat>

#include <QWidget>
#include <QtSql>
#include <QDataWidgetMapper>
#include <QStringList>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QMessageBox>

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
    QStandardItemModel* apply_filter_combobox(QAbstractItemModel *originalModel, int colIndex, QComboBox *cb);
    QStandardItemModel* apply_filter_line_edit(QAbstractItemModel *originalModel, int colIndex, QLineEdit *from, QLineEdit *to);
    void set_filters();
    void createEmptyTable(QSqlTableModel *model);

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

private:
    Ui::RealEstateBase *ui;
    QSqlTableModel *model;
    QAbstractItemModel *resModel;

    QDoubleValidator *doubleValidator;
    QIntValidator *intValidator;

    int currentRow = -1;
};

#endif // REALESTATEBASE_H
