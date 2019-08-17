#ifndef FORMREMOTEOPERATION_H
#define FORMREMOTEOPERATION_H

#include <QWidget>
#include "common.h"
#include <QToolButton>
#include <QLabel>
#include <QString>

class MyMessageBox;

class Widget;

namespace Ui {
class FormRemoteOperation;
}

class FormRemoteOperation : public QWidget
{
    Q_OBJECT

public:
    explicit FormRemoteOperation(QWidget *parent = 0);
    ~FormRemoteOperation();

private slots:
    void on_ledButton_clicked();
    void on_ledButton_2_clicked();

private:
    void initForm();
    void setLedStatus(QToolButton *btn, QLabel *lb, QString strbtn, QString strlab);

private:
    Ui::FormRemoteOperation *ui;
    bool led1_sta;
    bool led2_sta;

};

#endif // FORMREMOTEOPERATION_H
