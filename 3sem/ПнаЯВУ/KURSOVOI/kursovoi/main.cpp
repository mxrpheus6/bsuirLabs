#include "mainwindow.h"
#include "authorization.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Authorization au;
    au.show();

    QObject::connect(&au, &Authorization::authorizationSuccess, &w, [&]() {
        au.hide();
        w.show();
    });

    return a.exec();
}
