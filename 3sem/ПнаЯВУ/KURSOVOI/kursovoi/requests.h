#ifndef REQUESTS_H
#define REQUESTS_H

#include <QWidget>
#include <QSqlTableModel>

#include "requests.h"
#include "defines.h"

namespace Ui {
class Requests;
}

class Requests : public QWidget
{
    Q_OBJECT

public:
    explicit Requests(QWidget *parent = nullptr);
    ~Requests();
    void createEmptyTable(QSqlTableModel* model);

private:
    Ui::Requests *ui;
    QSqlTableModel* model;
};

#endif // REQUESTS_H
