#ifndef FORMMEMBERINFOSEARCH_H
#define FORMMEMBERINFOSEARCH_H

#include <QWidget>
#include "table.h"

class MyMessageBox;

namespace Ui {
class FormMemberInfoSearch;
}

class FormMemberInfoSearch : public QWidget
{
    Q_OBJECT

public:
    explicit FormMemberInfoSearch(QWidget *parent = 0);
    ~FormMemberInfoSearch();

private slots:
    void flushData();

    void on_searchToolButton_clicked();

private:
    void initForm();

private:
    Ui::FormMemberInfoSearch *ui;
    Table *table;
};

#endif // FORMMEMBERINFOSEARCH_H
