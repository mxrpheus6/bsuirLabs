#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTextStream>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void showError(const QString &message);
    void writeDebug(const QString &message);

    std::vector<uint8_t> receiveAndProcessFrames(int chunkCount);
    QString bitStuffingOutput(const std::vector<uint8_t> &stuffedData);
    void sendChunks(const std::vector<std::vector<uint8_t> > &chunks, uint8_t flag, uint8_t sourceAddress);
    std::vector<std::vector<uint8_t> > convertToChunks(const std::vector<uint8_t> &data, size_t chunkSize);

    ~MainWindow();

private slots:
    void on_pushButtonSave_clicked();

    void on_pushButtonSend_1_clicked();

    void on_pushButtonClear_2_clicked();

    void on_pushButtonClear_1_clicked();

    void on_pushButtonSend_2_clicked();

private:
    Ui::MainWindow *ui;
    int inputPortNumber;
    int outputPortNumber;
    int inputPortRate;
    int outputPortRate;

    QSerialPort *port1 = nullptr;
    QSerialPort *port2 = nullptr;
};
#endif // MAINWINDOW_H
