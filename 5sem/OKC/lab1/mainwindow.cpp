#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDateTime>
#include <QMessageBox>

void MainWindow::writeDebug(const QString &message) {
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString formattedDateTime = currentDateTime.toString("dd:MM:yyyy - hh:mm:ss");
    ui->plainTextEditDebug->appendPlainText(formattedDateTime + " | " + message);
}

void MainWindow::showError(const QString &message) {
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setWindowTitle("Ошибка!");
    msgBox.setText(message);
    writeDebug(message);
    msgBox.exec();
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->plainTextEditOutput_2->setReadOnly(true);
    ui->plainTextEditOutput_1->setReadOnly(true);
    ui->plainTextEditDebug->setReadOnly(true);

    for (int i = 1; i <= 255; i++) {
        ui->comboBoxPort1Num->addItem(QString::number(i));
        ui->comboBoxPort2Num->addItem(QString::number(i));
    }

    for (int i = 1200; i <= 115200; i *= 2) {
        ui->comboBoxPort1Rate->addItem(QString::number(i));
        ui->comboBoxtPort2Rate->addItem(QString::number(i));
        if (i == 38400) {
            i = 28800;
        }
    }
    ui->comboBoxPort1Num->setCurrentIndex(-1);
    ui->comboBoxPort2Num->setCurrentIndex(-1);
    ui->comboBoxPort1Rate->setCurrentIndex(-1);
    ui->comboBoxtPort2Rate->setCurrentIndex(-1);

    writeDebug("Приложение запущено...");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonSave_clicked()
{
    if (ui->comboBoxPort1Num->currentIndex() == -1) {
        showError("Вы должны выбрать номер COM-порта 1!");
        return;
    }
    if (ui->comboBoxPort1Rate->currentIndex() == -1) {
        showError("Вы должны выбрать скорость COM-порта 1!");
        return;
    }
    if (ui->comboBoxPort2Num->currentIndex() == -1) {
        showError("Вы должны выбрать номер COM-порта 2!");
        return;
    }
    if (ui->comboBoxtPort2Rate->currentIndex() == -1) {
        showError("Вы должны выбрать скорость COM-порта 2!");
        return;
    }

    if (ui->comboBoxPort1Num->currentText() == ui->comboBoxPort2Num->currentText()) {
        showError("Номера COM-портов 1 и 2 не могут быть одинаковыми!");
        return;
    }

    port1 = new QSerialPort(this);
    port1->setPortName("COM" + ui->comboBoxPort1Num->currentText());
    if (port1->open(QIODevice::ReadWrite)) {
        switch (ui->comboBoxPort1Rate->currentText().toInt()) {
        case 1200:
            port1->setBaudRate(QSerialPort::Baud1200);
            break;
        case 2400:
            port1->setBaudRate(QSerialPort::Baud2400);
            break;
        case 4800:
            port1->setBaudRate(QSerialPort::Baud4800);
            break;
        case 9600:
            port1->setBaudRate(QSerialPort::Baud9600);
            break;
        case 19200:
            port1->setBaudRate(QSerialPort::Baud19200);
            break;
        case 38400:
            port1->setBaudRate(QSerialPort::Baud38400);
            break;
        case 57600:
            port1->setBaudRate(QSerialPort::Baud57600);
            break;
        case 115200:
            port1->setBaudRate(QSerialPort::Baud115200);
            break;
        default:
            port1->setBaudRate(QSerialPort::Baud9600);
            break;
        }
        port1->setDataBits(QSerialPort::Data8);
        port1->setParity(QSerialPort::NoParity);
        port1->setStopBits(QSerialPort::OneStop);
        port1->setFlowControl(QSerialPort::NoFlowControl);
    } else {
        writeDebug("Не удалось открыть COM" + ui->comboBoxPort1Num->currentText());
        port1->close();
        delete port1;
        port1 = nullptr;
        return;
    }

    port2 = new QSerialPort(this);
    port2->setPortName("COM" + ui->comboBoxPort2Num->currentText());
    if (port2->open(QIODevice::ReadWrite)) {
        switch (ui->comboBoxtPort2Rate->currentText().toInt()) {
        case 1200:
            port2->setBaudRate(QSerialPort::Baud1200);
            break;
        case 2400:
            port2->setBaudRate(QSerialPort::Baud2400);
            break;
        case 4800:
            port2->setBaudRate(QSerialPort::Baud4800);
            break;
        case 9600:
            port2->setBaudRate(QSerialPort::Baud9600);
            break;
        case 19200:
            port2->setBaudRate(QSerialPort::Baud19200);
            break;
        case 38400:
            port2->setBaudRate(QSerialPort::Baud38400);
            break;
        case 57600:
            port2->setBaudRate(QSerialPort::Baud57600);
            break;
        case 115200:
            port2->setBaudRate(QSerialPort::Baud115200);
            break;
        default:
            port2->setBaudRate(QSerialPort::Baud9600);
            break;
        }
        port2->setDataBits(QSerialPort::Data8);
        port2->setParity(QSerialPort::NoParity);
        port2->setStopBits(QSerialPort::OneStop);
        port2->setFlowControl(QSerialPort::NoFlowControl);
    } else {
        writeDebug("Не удалось открыть COM" + ui->comboBoxPort2Num->currentText());
        port1->close();
        port2->close();
        delete port1;
        delete port2;
        port1 = nullptr;
        port2 = nullptr;
        return;
    }

    QString message = "Сохранение параметров успешно! Порт ввода - COM" + ui->comboBoxPort1Num->currentText()
                      + ", порт вывода - COM"
                      + ui->comboBoxPort2Num->currentText();
    writeDebug(message);
}


void sendData(QSerialPort &port, const QString &data) {
    if (port.isOpen()) {
        port.write(data.toUtf8());
        port.waitForBytesWritten(1000);
    } else {
        QTextStream(stdout) << "Ошибка: Порт " << port.portName() << " не открыт для отправки данных.\n";
    }
}

QString receiveData(QSerialPort &port) {
    if (port.isOpen() && port.waitForReadyRead(1000)) {
        QByteArray receivedData = port.readAll();
        while (port.waitForReadyRead(10))
            receivedData += port.readAll();

        return QString::fromUtf8(receivedData);
    }
    return QString();
}

void MainWindow::on_pushButtonSend_1_clicked()
{
    if (port1 == nullptr || port2 == nullptr) {
        showError("Порты не определены!");
        return;
    }

    if (ui->plainTextEditInput_1->toPlainText().isEmpty()) {
        showError("Поле ввода пустое!");
        return;
    }

    sendData(*port1, ui->plainTextEditInput_1->toPlainText());
    QString receivedData = receiveData(*port2);

    ui->plainTextEditOutput_2->appendPlainText(receivedData);

    QByteArray byteArray = receivedData.toUtf8();
    int byteCount = byteArray.size();
    writeDebug("Сообщение успешно отправлено c порта 1 и получено на порту 2! Количество байт - " + QString::number(byteCount));
}


void MainWindow::on_pushButtonClear_2_clicked()
{
    ui->plainTextEditOutput_2->clear();
    writeDebug("Окно вывода 2 было успешно очищено!");
}

void MainWindow::on_pushButtonClear_1_clicked()
{
    ui->plainTextEditOutput_1->clear();
    writeDebug("Окно вывода 1 было успешно очищено!");
}


void MainWindow::on_pushButtonSend_2_clicked()
{
    if (port1 == nullptr || port2 == nullptr) {
        showError("Порты не определены!");
        return;
    }

    if (ui->plainTextEditInput_2->toPlainText().isEmpty()) {
        showError("Поле ввода пустое!");
        return;
    }

    sendData(*port2, ui->plainTextEditInput_2->toPlainText());
    QString receivedData = receiveData(*port1);

    ui->plainTextEditOutput_1->appendPlainText(receivedData);

    QByteArray byteArray = receivedData.toUtf8();
    int byteCount = byteArray.size();
    writeDebug("Сообщение успешно отправлено c порта 2 и получено на порту 1! Количество байт - " + QString::number(byteCount));
}
