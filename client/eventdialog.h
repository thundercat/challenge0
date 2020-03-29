#ifndef EVENTDIALOG_H
#define EVENTDIALOG_H

#include <QDialog>
#include "event.h"
namespace Ui {
class EventDialog;
}

class EventDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EventDialog(QWidget *parent = nullptr);
    ~EventDialog();

    std::shared_ptr<Event> getEvent();
protected:
    void changeEvent(QEvent *e);

private:
    Ui::EventDialog *ui;
};

#endif // EVENTDIALOG_H
