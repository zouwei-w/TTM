#ifndef FORMLABENVIROMENT_H
#define FORMLABENVIROMENT_H

#include <QWidget>
#include <QTimer>
#include "common.h"

class QTimer;
class MyMessageBox;

namespace Ui {
class FormlabEnviroment;
}

class FormlabEnviroment : public QWidget
{
    Q_OBJECT

public:
    explicit FormlabEnviroment(QWidget *parent = 0);
    ~FormlabEnviroment();

private slots:
    void showEnverimentInfo();

private:
    void initForm();
    void initTimer();  //初始化定时器

private:
    Ui::FormlabEnviroment *ui;
    QTimer *pm_timer;
};

#endif // FORMLABENVIROMENT_H
