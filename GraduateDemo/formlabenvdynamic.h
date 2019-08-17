#ifndef FORMLABENVDYNAMIC_H
#define FORMLABENVDYNAMIC_H

#include <QWidget>
#include "table.h"

class MyMessageBox;

namespace Ui {
class FormlabEnvdynamic;
}

class FormlabEnvdynamic : public QWidget
{
    Q_OBJECT

public:
    explicit FormlabEnvdynamic(QWidget *parent = 0);
    ~FormlabEnvdynamic();

private slots:
    void flushData();

private:
    void initForm();

private:
    Ui::FormlabEnvdynamic *ui;
    Table *table;
};

#endif // FORMLABENVDYNAMIC_H
