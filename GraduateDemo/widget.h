#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include <qDebug>
#include <QToolButton>
#include <QPropertyAnimation>
#include "common.h"

class QTimer;

class FormLogin;
class FormborrowDevInfo;
class FormdevSearch;
class FormlabEnvdynamic;
class FormlabEnviroment;
class FormMemberInfoSearch;
class Formmusic;
class FormRemoteOperation;
class MyMessageBox;

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    //设置按钮样式
    void myToolButtonStyle(QToolButton *tbn,const QString &text,int textSize,
                            const QString iconName);

private:
    void initTimer();  //初始化定时器
    void initFormStyle();                            //样式初始化

    void initWidget(); //初始化界面
    void deletWidget();
    void setCurrentWidget(enum_widget enum_widget_name);

private slots:
    void showCunrrentTime();

    void showMainWidget();

    void on_settingBtn_clicked();

    void on_homeBtn_clicked();

    void on_musicBtn_clicked();

    void on_labEnvBtn_clicked();

    void on_labEnvInfoBtn_clicked();

    void on_devSearchBtn_clicked();

    void on_memberInfoSearchBtn_clicked();

    void on_borrowDevInfoBtn_clicked();

    void on_remoteOperationBtn_clicked();


private:
    Ui::Widget *ui;
    QTimer *m_timer;

    FormLogin *m_formLogin;
    FormborrowDevInfo  *m_formborrowDevInfo;
    FormdevSearch *m_formdevSearch;
    FormlabEnvdynamic *m_formlabEnvdynamic;
    FormlabEnviroment *m_formlabEnviroment;
    FormMemberInfoSearch *m_formMemberInfoSearch;
    Formmusic *m_formmusic;
    FormRemoteOperation *m_formRemoteOperation;
};

#endif // WIDGET_H
