#ifndef FORMREGISTER_H
#define FORMREGISTER_H

#include <QWidget>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>

class MyMessageBox;
class QTimer;

namespace Ui {
class FormRegister;
}

class FormRegister : public QWidget
{
    Q_OBJECT

public:
    explicit FormRegister(QWidget *parent = 0);
    ~FormRegister();

private slots:
    void updateBtnvalue();
    void on_cancleBtn_clicked();

    void on_regBtn_clicked();

    void on_sendSmsBtn_clicked();

private:
    void initForm();
    void flushData();
    QString randVrcode();
    void initWidget();

private:
    Ui::FormRegister *ui;
    QString m_vrcode;
    QTimer *m_timer;
    bool E_PRESSSTA;
    int  timeCount;
};

#endif // FORMREGISTER_H
