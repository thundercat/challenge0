#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAbstractSocket>

class Client;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    enum class ConnectionState {
        Disconnected,
        Connected
    };

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_connectButton_clicked();

    void onEventsReady();

    void on_addEventButton_clicked();

    void onStateChanged(QAbstractSocket::SocketState);
private:
    Ui::MainWindow *ui;
    Client *client;

    ConnectionState connectionState;
};
#endif // MAINWINDOW_H
