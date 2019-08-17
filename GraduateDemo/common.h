#ifndef COMMON_H
#define COMMON_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <qDebug>
#include <QMessageBox>
#include <QRect>
#include <QDesktopWidget>
#include <QStringList>


void myMessageBox(QString path, QString tile, QString text);

//场景名称枚举
enum enum_widget{
    E_NULL_WIDGET = 0,
    E_HOME_WIDGET = 1,          //首页
    E_BOOROW_WIDGET = 2,        //借用查询
    E_DEVSEARCH_WIDGET,         //设备查询
    E_LABENVDYNAMIC_WIDGET,     //实验动态
    E_LABENV_WIDGET,            //实验环境
    E_MEMBERINFO_WIDGET,        //人员查询
    E_MUSIC_WIDGET,             //音乐
    E_REMOTEOPERA_WIDGET        //远程操作
};

extern enum_widget CURRENT_WIDGET;


#endif // COMMON_H

