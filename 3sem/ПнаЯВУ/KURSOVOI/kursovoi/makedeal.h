#ifndef MAKEDEAL_H
#define MAKEDEAL_H

#include <QWidget>

namespace Ui {
class MakeDeal;
}

class MakeDeal : public QWidget
{
    Q_OBJECT

public:
    explicit MakeDeal(QWidget *parent = nullptr);
    ~MakeDeal();

private:
    Ui::MakeDeal *ui;
};

#endif // MAKEDEAL_H
