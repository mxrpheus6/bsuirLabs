#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDateTime>
#include <QMessageBox>

#include "packet.h"

void MainWindow::writeDebug(const QString &message) {
    QDateTime currentDateTime = QDateTime::currentDateTime();
    QString formattedDateTime = currentDateTime.toString("dd.MM.yyyy - hh:mm:ss");
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
    this->setWindowTitle("Token Ring");
    ui->plainTextEditOutput_2->setReadOnly(true);
    ui->plainTextEditOutput_1->setReadOnly(true);
    ui->plainTextEditDebug->setReadOnly(true);

    for (int i = 1; i <= 255; i++) {
        ui->comboBoxPort1Num->addItem(QString::number(i));
        ui->comboBoxPort2Num->addItem(QString::number(i));
        ui->comboBoxPort3Num->addItem(QString::number(i));
    }

    for (int i = 1200; i <= 115200; i *= 2) {
        ui->comboBoxPort1Rate->addItem(QString::number(i));
        ui->comboBoxtPort2Rate->addItem(QString::number(i));
        ui->comboBoxtPort3Rate->addItem(QString::number(i));
        if (i == 38400) {
            i = 28800;
        }
    }
    ui->comboBoxPort1Num->setCurrentIndex(-1);
    ui->comboBoxPort2Num->setCurrentIndex(-1);
    ui->comboBoxPort3Num->setCurrentIndex(-1);
    ui->comboBoxPort1Rate->setCurrentIndex(-1);
    ui->comboBoxtPort2Rate->setCurrentIndex(-1);
    ui->comboBoxtPort3Rate->setCurrentIndex(-1);

    writeDebug("Приложение запущено...");
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString vectorToQString(const std::vector<int>& vec) {
    QString result;

    for (int bit : vec) {
        result += QString::number(bit);
    }

    return result;
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
    if (ui->comboBoxPort3Num->currentIndex() == -1) {
        showError("Вы должны выбрать номер COM-порта 2!");
        return;
    }
    if (ui->comboBoxtPort3Rate->currentIndex() == -1) {
        showError("Вы должны выбрать скорость COM-порта 2!");
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
        writeDebug("Не удалось открыть COM" + ui->comboBoxPort3Num->currentText());
        port1->close();
        port2->close();
        port3->close();
        delete port1;
        delete port2;
        delete port3;
        port1 = nullptr;
        port2 = nullptr;
        port3 = nullptr;
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
        writeDebug("Не удалось открыть COM" + ui->comboBoxPort3Num->currentText());
        port1->close();
        port2->close();
        port3->close();
        delete port1;
        delete port2;
        delete port3;
        port1 = nullptr;
        port2 = nullptr;
        port3 = nullptr;
        return;
    }

    port3 = new QSerialPort(this);
    port3->setPortName("COM" + ui->comboBoxPort3Num->currentText());
    if (port3->open(QIODevice::ReadWrite)) {
        switch (ui->comboBoxtPort3Rate->currentText().toInt()) {
        case 1200:
            port3->setBaudRate(QSerialPort::Baud1200);
            break;
        case 2400:
            port3->setBaudRate(QSerialPort::Baud2400);
            break;
        case 4800:
            port3->setBaudRate(QSerialPort::Baud4800);
            break;
        case 9600:
            port3->setBaudRate(QSerialPort::Baud9600);
            break;
        case 19200:
            port3->setBaudRate(QSerialPort::Baud19200);
            break;
        case 38400:
            port3->setBaudRate(QSerialPort::Baud38400);
            break;
        case 57600:
            port3->setBaudRate(QSerialPort::Baud57600);
            break;
        case 115200:
            port3->setBaudRate(QSerialPort::Baud115200);
            break;
        default:
            port3->setBaudRate(QSerialPort::Baud9600);
            break;
        }
        port3->setDataBits(QSerialPort::Data8);
        port3->setParity(QSerialPort::NoParity);
        port3->setStopBits(QSerialPort::OneStop);
        port3->setFlowControl(QSerialPort::NoFlowControl);
    } else {
        writeDebug("Не удалось открыть COM" + ui->comboBoxPort3Num->currentText());
        port1->close();
        port2->close();
        port3->close();
        delete port1;
        delete port2;
        delete port3;
        port1 = nullptr;
        port2 = nullptr;
        port3 = nullptr;
        return;
    }

    QString message = "Сохранение параметров успешно! COM-" + ui->comboBoxPort1Num->currentText() + "->COM" +
                        ui->comboBoxPort2Num->currentText() + "->COM-" + ui->comboBoxPort3Num->currentText();
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

    QList<Packet> transmittedPackets = Packet::generatePacketListByData(ui->plainTextEditInput_1->toPlainText());
    for (auto& p : transmittedPackets) {
        p.setSourceAddress(ui->comboBoxPort1Num->currentText().toInt());
    }

    std::vector<uint16_t> collisions = Packet::transmitPacketsWithCollision(port1, transmittedPackets);

    QList<Packet> receivedPackets = Packet::receivePackets(port2);
    QList<Packet::FixedDataInfo> fixedPackets = Packet::checkPacketsDataIntegrity(receivedPackets);

    QByteArray mergedData;
    QString mergedInfo;
    for (const auto& p : receivedPackets) {
        mergedData.append(p.getData());

        QString packetInfo = "Flag = " + QString::number(p.getFlag()) + " | " +
                             "Dest = " + QString::number(p.getDestinationAddress()) + " | " +
                             "Src = " + QString::number(p.getSourceAddress()) + " | " +
                             "Data = " + QString::fromUtf8(p.getData()) + " | " +
                             "FCS = " + vectorToQString(Packet::convertBitsToVector(p.getFcs()));


        mergedInfo += packetInfo + "\n";
    }

    writeDebug("Вывод информации о пакетах:\n");
    ui->plainTextEditDebug->appendPlainText(mergedInfo);
    QString result = Packet::Unstuffing(mergedData);

    for (int i = 0; i < fixedPackets.size(); i++) {
        ui->plainTextEditOutput_2->appendPlainText(fixedPackets[i].data);
        ui->plainTextEditOutput_2->appendPlainText("Before  : " + vectorToQString(fixedPackets[i].controlBitsBefore));
        ui->plainTextEditOutput_2->appendPlainText("After     : " + vectorToQString(fixedPackets[i].controlBitsAfter));
        ui->plainTextEditOutput_2->appendPlainText("Position: " + QString::number(fixedPackets[i].errorPosition));
        ui->plainTextEditOutput_2->appendPlainText("Collisions: " + (collisions[i] == 16 ? "N/A" : QString::number(collisions[i])));
        ui->plainTextEditOutput_2->appendPlainText("");
    }

    QByteArray byteArray = result.toUtf8();
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

    QList<Packet> transmittedPackets = Packet::generatePacketListByData(ui->plainTextEditInput_2->toPlainText());
    for (auto& p : transmittedPackets) {
        p.setSourceAddress(ui->comboBoxPort2Num->currentText().toInt());
    }

    std::vector<uint16_t> collisions = Packet::transmitPacketsWithCollision(port2, transmittedPackets);

    QList<Packet> receivedPackets = Packet::receivePackets(port1);
    QList<Packet::FixedDataInfo> fixedPackets = Packet::checkPacketsDataIntegrity(receivedPackets);

    QByteArray mergedData;
    QString mergedInfo;
    for (const auto& p : receivedPackets) {
        mergedData.append(p.getData());

        QString packetInfo = "Flag = " + QString::number(p.getFlag()) + " | " +
                             "Dest = " + QString::number(p.getDestinationAddress()) + " | " +
                             "Src = " + QString::number(p.getSourceAddress()) + " | " +
                             "Data = " + QString::fromUtf8(p.getData()) + " | " +
                             "FCS = " + vectorToQString(Packet::convertBitsToVector(p.getFcs()));


        mergedInfo += packetInfo + "\n";
    }

    writeDebug("Вывод информации о пакетах:\n");
    ui->plainTextEditDebug->appendPlainText(mergedInfo);
    QString result = Packet::Unstuffing(mergedData);

    for (int i = 0; i < fixedPackets.size(); i++) {
        ui->plainTextEditOutput_1->appendPlainText(fixedPackets[i].data);
        ui->plainTextEditOutput_1->appendPlainText("Before  : " + vectorToQString(fixedPackets[i].controlBitsBefore));
        ui->plainTextEditOutput_1->appendPlainText("After     : " + vectorToQString(fixedPackets[i].controlBitsAfter));
        ui->plainTextEditOutput_1->appendPlainText("Position: " + QString::number(fixedPackets[i].errorPosition));
        ui->plainTextEditOutput_1->appendPlainText("Collisions: " + (collisions[i] == 16 ? "Error" : QString::number(collisions[i])));
        ui->plainTextEditOutput_1->appendPlainText("");
    }

    QByteArray byteArray = result.toUtf8();
    int byteCount = byteArray.size();
    writeDebug("Сообщение успешно отправлено c порта 2 и получено на порту 1! Количество байт - " + QString::number(byteCount));
}


void MainWindow::on_pushButtonSend_4_clicked()
{
    writeDebug("Отправка данных...");

    int senderPort = ui->lineEdit->text().toInt();
    int reciverPort = ui->lineEdit_2->text().toInt();

    bool isPacketSend = false;
    static int currentPort = ComPortManager::PORT_X;
    QString text;
    QSerialPort* port = nullptr;
    while (!isPacketSend) {
        if (currentPort == senderPort) {
            if (currentPort == ComPortManager::PORT_X) {
                port = comPortManager->getXPort();
                text = ui->inputXPortTextEdit->toPlainText();
            }
            else if (currentPort == ComPortManager::PORT_Y) {
                port = comPortManager->getYPort();
                text = ui->inputYPortTextEdit->toPlainText();
            }
            else if (currentPort == ComPortManager::PORT_Z) {
                port = comPortManager->getZPort();
                text = ui->inputZPortTextEdit->toPlainText();
            }

            QList<ComPortManager::TokenRingDataFrame> transmittedPackets = comPortManager->generatePacketListByData(text);
            for (auto& p : transmittedPackets) {
                p.data.sourceAddress = currentPort;
            }

            if (!comPortManager->transmitPackets(port, transmittedPackets)) {
                Logger::Error(ui->logsTextBrowser, "data send error");
                return;
            }

            isPacketSend = true;
        }

        currentPort = (currentPort + 1) > ComPortManager::PORT_Z ? ComPortManager::PORT_X : ++currentPort;
    }

    QList<ComPortManager::TokenRingDataFrame> receivedPackets;
    QList<ComPortManager::FixedDataInfo> fixedPackets;
    QTextBrowser* textBrowser = nullptr;
    bool isPacketReceived = false;
    while (!isPacketReceived) {
        if (currentPort == reciverPort) {
            if (currentPort == ComPortManager::PORT_X) {
                receivedPackets = comPortManager->receivePackets(comPortManager->getXPort());
                textBrowser = ui->outputXPortTextBrowser;
            }
            else if (currentPort == ComPortManager::PORT_Y) {
                receivedPackets = comPortManager->receivePackets(comPortManager->getYPort());
                textBrowser = ui->outputYPortTextBrowser;
            }
            else if (currentPort == ComPortManager::PORT_Z) {
                receivedPackets = comPortManager->receivePackets(comPortManager->getZPort());
                textBrowser = ui->outputZPortTextBrowser;
            }

            fixedPackets = comPortManager->checkPacketsDataIntegrity(receivedPackets);

            isPacketReceived = true;
        }

        currentPort = (currentPort + 1) > ComPortManager::PORT_Z ? ComPortManager::PORT_X : ++currentPort;
    }

    QByteArray mergedData;
    ui->stateTextBrowser->clear();
    ui->stateTextBrowser->append("----------------------------------");
    for (const auto& p : receivedPackets) {
        mergedData.append(p.data.data);
        ui->stateTextBrowser->append("flag: " + QString::number(p.data.flag));
        ui->stateTextBrowser->append("dest. address: " + QString::number(p.data.destinationAddress));
        ui->stateTextBrowser->append("source address: " + QString::number(p.data.sourceAddress));
        ui->stateTextBrowser->append("data: " + comPortManager->byteArrayToString(p.data.data));
        ui->stateTextBrowser->append("fcs: " + vectorToQString(comPortManager->convertBitsToVector(p.data.fcs)));
        ui->stateTextBrowser->append("----------------------------------");
    }

    textBrowser->clear();
    textBrowser->append("----------------------------------");
    for (const auto& p : fixedPackets) {
        textBrowser->append("Fixed Data: " + p.data);
        textBrowser->append("Control bits before: " + vectorToQString(p.controlBitsBefore));
        textBrowser->append("Control bits after: " + vectorToQString(p.controlBitsAfter));
        textBrowser->append("Error pos: " + QString::number(p.errorPosition));
        textBrowser->append("----------------------------------");
    }

    Logger::Info(ui->logsTextBrowser, QString::number(receivedPackets.size()) + " packets received");
}

