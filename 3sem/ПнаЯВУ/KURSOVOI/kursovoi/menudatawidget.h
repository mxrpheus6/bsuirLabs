#ifndef MENUDATAWIDGET_H
#define MENUDATAWIDGET_H

#include <QWidget>
#include <QtSql>

namespace Ui {
class MenuDataWidget;
}

class MenuDataWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MenuDataWidget(QWidget *parent, QString tableName);
    ~MenuDataWidget();

private slots:
    void on_pushButton_add_clicked();

    void on_pushButton_del_clicked();

    void on_tableView_db_clicked(const QModelIndex &index);

private:
    Ui::MenuDataWidget *ui;
    QSqlTableModel *model;
    int currentRow;
};

#endif // MENUDATAWIDGET_H
