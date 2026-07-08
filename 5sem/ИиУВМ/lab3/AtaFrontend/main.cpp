#include <QApplication>
#include <QStyleFactory>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    deserializeAtaInfo();

    MainWindow mainWindow;
    mainWindow.setWindowTitle("Сканер ATA");
    mainWindow.resize(300, 550);
    mainWindow.show();

    return app.exec();
}
