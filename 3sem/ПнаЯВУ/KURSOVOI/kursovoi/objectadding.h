#ifndef OBJECTADDING_H
#define OBJECTADDING_H

#include <QWidget>
#include <QSqlTableModel>

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

private:
    Ui::objectAdding *ui;
    QSqlTableModel* model;

    const std::vector<QString> fields_apartment = {"Пл-дь кухни, м2", "Этажность", "Тип дома", "Балкон", "Лифт", "Потолок, м", "Паркинг", "Консьерж"};
    const std::vector<QString> fields_house = {"Пл-дь участка, м2", "Пл-дь кухни, м2", "Материал стен", "Материал крыши", "Камин", "Гараж", "Отопление", "Канализация", "Водоснабжение"};
    const std::vector<QString> fields_office = {"Класс", "Этажность", "Кол-во раб. мест", "Материал стен", "Ремонт", "Конференц залы", "Охрана", "Туалет"};
};

#endif // OBJECTADDING_H
