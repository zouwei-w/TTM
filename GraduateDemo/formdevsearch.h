#ifndef FORMDEVSEARCH_H
#define FORMDEVSEARCH_H

#include <QWidget>
#include "table.h"

class MyMessageBox;

namespace Ui {
class FormdevSearch;
}

class FormdevSearch : public QWidget
{
    Q_OBJECT

public:
    explicit FormdevSearch(QWidget *parent = 0);
    ~FormdevSearch();

private slots:
    void flushData();

private:
    void initForm();

private:
    Ui::FormdevSearch *ui;
    Table *table;
};

#endif // FORMDEVSEARCH_H
