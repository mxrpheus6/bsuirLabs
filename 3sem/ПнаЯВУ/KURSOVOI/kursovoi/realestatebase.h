#ifndef REALESTATEBASE_H
#define REALESTATEBASE_H

#include <QWidget>

namespace Ui {
class RealEstateBase;
}

class RealEstateBase : public QWidget
{
    Q_OBJECT

public:
    explicit RealEstateBase(QWidget *parent = nullptr);
    ~RealEstateBase();

private:
    Ui::RealEstateBase *ui;
};

#endif // REALESTATEBASE_H
