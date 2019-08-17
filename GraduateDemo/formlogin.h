#ifndef FORMLOGIN_H
#define FORMLOGIN_H

#include <QWidget>
#include "mymessagebox.h"

class FormRegister;

namespace Ui {
class FormLogin;
}

class FormLogin : public QWidget
{
    Q_OBJECT

public:
    explicit FormLogin(QWidget *parent = 0);
    ~FormLogin();

    bool E_LOGIN_STA;

private slots:
    void on_loginButton_clicked();

    void on_registToolButton_clicked();

    void on_remberPassCheckBox_clicked();

    void on_autoLoginCheckBox_clicked();

signals:
    void LOGINSTA_SIG();

private:
    void initForm();
    bool remberCheckBox;
    bool autoLoginCheckBox;
    QString m_username;
    QString m_password;

private:
    Ui::FormLogin *ui;
    FormRegister *pm_formRegister;
};

#endif // FORMLOGIN_H
