#ifndef FORMBORROWDEVINFO_H
#define FORMBORROWDEVINFO_H

#include <QWidget>
#include "table.h"

class MyMessageBox;

namespace Ui {
class FormborrowDevInfo;
}

class FormborrowDevInfo : public QWidget
{
    Q_OBJECT

public:
    explicit FormborrowDevInfo(QWidget *parent = 0);
    ~FormborrowDevInfo();

private slots:
    void flushData();

private:
    void initForm();

private:
    Ui::FormborrowDevInfo *ui;
    Table *table;
};

#endif // FORMBORROWDEVINFO_H
