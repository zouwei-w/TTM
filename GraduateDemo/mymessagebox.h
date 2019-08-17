#ifndef MYMESSAGEBOX_H
#define MYMESSAGEBOX_H

#include <QWidget>

namespace Ui {
class MyMessageBox;
}

class MyMessageBox : public QWidget
{
    Q_OBJECT

public:
    explicit MyMessageBox(QWidget *parent = 0);
    ~MyMessageBox();

    void myMessageBox(QString path, QString tile, QString text);

private slots:
    void on_okPushButton_clicked();

private:
    void initForm();

private:
    Ui::MyMessageBox *ui;
};

#endif // MYMESSAGEBOX_H
