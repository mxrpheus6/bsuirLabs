#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton> // Include QPushButton
#include "ataManager.h" // Include the ATA management header

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onDeviceSelected(); // Slot for handling device selection
    void onLoadFileButtonClicked(); // New slot for button click

private:
    Ui::MainWindow *ui;
    QListWidget *deviceList;      // List of devices
    QLabel *deviceInfoLabel;      // Device info display
    void loadDeviceList();        // Load devices into the list
    QString getDeviceDetails(const DeviceInfo &device); // Get device info string
    QPushButton *loadFileButton; // Button to load file
};
#endif // MAINWINDOW_H
