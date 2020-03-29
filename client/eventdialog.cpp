#include "eventdialog.h"
#include "ui_eventdialog.h"
#include <QDebug>

EventDialog::EventDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EventDialog)
{
    ui->setupUi(this);

    QStringList priority;
    priority << "low" << "mormal" << "high";
    ui->comboBox->addItems(priority);
}

EventDialog::~EventDialog()
{
    delete ui;
}

std::shared_ptr<Event> EventDialog::getEvent()
{
    auto event = std::make_shared<Event>();
    event->setText(ui->lineEdit->text());
    event->setEventPriority(ui->comboBox->currentIndex());

    qDebug() << "event" << event->getText() << event->getPriority();
    return event;
}

void EventDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
