#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cstdint>
#include <QTcpSocket>
#include <QHostAddress>
#include <QMessageBox>
#include "client.h"
#include "databasemanagerclient.h"
#include "eventdialog.h"
#include "eventmodel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , connectionState(ConnectionState::Disconnected)
{
    ui->setupUi(this);
    ui->portLinieEdit->setValidator(new QIntValidator(1, UINT16_MAX));
    client = new Client(this);
    connect(client, &Client::eventsReady, this, &MainWindow::onEventsReady);

    //TODO temporary
    ui->hostLinieEdit->setText("192.168.1.100");
    ui->portLinieEdit->setText(QString::number(56556));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_connectButton_clicked()
{
    QHostAddress host(ui->hostLinieEdit->text());
    uint16_t port = static_cast<uint16_t>(ui->portLinieEdit->text().toUInt());

    qDebug() << "connecting" << host.toString() << port;
    client->connectToHost(host, port);
}

void MainWindow::onEventsReady()
{    
//    QMessageBox msgBox;
//    msgBox.setText("New events on server");
//    msgBox.setInformativeText("Do you want update events list?");
//    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
//    msgBox.setDefaultButton(QMessageBox::Yes);

//    if(msgBox.exec() == QMessageBox::Yes)
    {
        QAbstractTableModel *model = client->getModel();
        ui->tableView->setModel(model);
        ui->tableView->update();
    }

}

void MainWindow::on_addEventButton_clicked()
{
    EventDialog eventDialog;

    if(eventDialog.exec() == QDialog::Accepted)
    {
        auto event = eventDialog.getEvent();
        client->addEvent(event);
        client->getEvents();
    }
}

void MainWindow::onStateChanged(QAbstractSocket::SocketState)
{

}
