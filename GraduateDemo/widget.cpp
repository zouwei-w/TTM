#include "widget.h"
#include "ui_widget.h"

#include <QTime>

#include "databases.h"
#include "formborrowdevinfo.h"
#include "formdevsearch.h"
#include "formlabenvdynamic.h"
#include "formlabenviroment.h"
#include "formmemberinfosearch.h"
#include "formmusic.h"
#include "formremoteoperation.h"
#include "formlogin.h"
#include "mymessagebox.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    initDatabases(); //初始化数据库

    this->initTimer();
    this->initFormStyle();
    this->initWidget();
}

Widget::~Widget()
{
    delete ui;
}

//初始化定时器
void Widget::initTimer()
{
    m_timer = new QTimer(this);
    connect(m_timer,SIGNAL(timeout()),
            this,SLOT(showCunrrentTime()));
    m_timer->start(1000);
}

//初始化界面风格
void Widget::initFormStyle()
{
    //设置窗体标题栏隐藏
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint);
    this->setWindowTitle(tr("开放实验室无人值守远程监控系统"));

    /*********************** 顶部设置和首页的样式 ******************************/
    myToolButtonStyle(ui->settingBtn,"设置",12,":/images/setting_normal.png");
    myToolButtonStyle(ui->homeBtn,"首页",12,":/images/home_normal.png");
    setStyleSheet(QLatin1String("QToolButton{border:0px;}"));

    /*********************** 底部控件样式 ******************************/
    myToolButtonStyle(ui->musicBtn,"音乐", 10, ":/images/music.png");
    myToolButtonStyle(ui->labEnvBtn,"实验室环境", 10, ":/images/video.png");
    myToolButtonStyle(ui->labEnvInfoBtn,"实验室动态", 10, ":/images/reset.png");
    myToolButtonStyle(ui->devSearchBtn,"设备查询", 10, ":/images/statistics.png");
    myToolButtonStyle(ui->memberInfoSearchBtn,"人员查询", 10, ":/images/night.png");
    myToolButtonStyle(ui->borrowDevInfoBtn,"设备借用", 10, ":/images/add.png");
    myToolButtonStyle(ui->remoteOperationBtn,"远程操作", 10, ":/images/control.png");

    /*********************** 中间控件样式 ******************************/
    ui->widget_data->setStyleSheet("QWidget{border-image: url(:/images/deepblue.png); border-radius:15px}");
    //将标签背景设置为透明
    ui->label_data->setAttribute(Qt::WA_TranslucentBackground);
    ui->label_hour->setAttribute(Qt::WA_TranslucentBackground);
    ui->label_min->setAttribute(Qt::WA_TranslucentBackground);
    ui->label_sec->setAttribute(Qt::WA_TranslucentBackground);
    ui->label_week->setAttribute(Qt::WA_TranslucentBackground);
    ui->ladoublebpoint->setAttribute(Qt::WA_TranslucentBackground);

}

//toolbutton的风格
void Widget::myToolButtonStyle(QToolButton *tbn, const QString &text, int textSize, const QString iconName)
{
    //设置显示的文本
    tbn->setText(text);

    //设置文字格式
    tbn->setFont(QFont("文泉驿雅黑",textSize,QFont::Bold));

    tbn->setAutoRaise(true);
    //设置按钮图标
    tbn->setIcon(QPixmap(QString("%1").arg(iconName)));
    tbn->setIconSize(QPixmap(QString("%1").arg(iconName)).size());
    //设置文本在图标下边
    tbn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    setStyleSheet("border-radius:5px}");
}

//初始化界面
void Widget::initWidget()
{
    qDebug() << "初始化界面";

    m_formLogin = new FormLogin; //登录界面
    m_formborrowDevInfo = new FormborrowDevInfo;
    m_formdevSearch = new FormdevSearch;
    m_formlabEnvdynamic = new FormlabEnvdynamic;
    m_formlabEnviroment = new FormlabEnviroment;
    m_formMemberInfoSearch = new FormMemberInfoSearch;
    m_formmusic = new Formmusic;
    m_formRemoteOperation = new FormRemoteOperation;

    ui->stackedWidget->addWidget(m_formborrowDevInfo);
    ui->stackedWidget->addWidget(m_formdevSearch);
    ui->stackedWidget->addWidget(m_formlabEnvdynamic);
    ui->stackedWidget->addWidget(m_formlabEnviroment);
    ui->stackedWidget->addWidget(m_formMemberInfoSearch);
    ui->stackedWidget->addWidget(m_formmusic);
    ui->stackedWidget->addWidget(m_formRemoteOperation);

    connect(m_formLogin,SIGNAL(LOGINSTA_SIG()), this, SLOT(showMainWidget()));
    m_formLogin->show();
}

//设置当前的widget
void Widget::setCurrentWidget(enum_widget enum_widget_name)
{
    ui->stackedWidget->setCurrentIndex(enum_widget_name);
}

//显示当前时间
void Widget::showCunrrentTime()
{
    ui->label_hour->setText(QTime::currentTime().toString("hh"));
    ui->label_min->setText(QTime::currentTime().toString("mm"));
    ui->label_sec->setText(QTime::currentTime().toString("ss"));
    ui->label_data->setText(QDate::currentDate().toString("yyyy年MM月dd日"));
    ui->label_week->setText(QDate::currentDate().toString("dddd"));
}

void Widget::showMainWidget()
{
    this->show();
}

//设置button
void Widget::on_settingBtn_clicked()
{
    qDebug() << "设置button";
    m_formLogin = new FormLogin;
    m_formLogin->show();
}

//首页button
void Widget::on_homeBtn_clicked()
{
    qDebug() << "首页button";
    setCurrentWidget(E_HOME_WIDGET);
    CURRENT_WIDGET = E_HOME_WIDGET;
}

//音乐button
void Widget::on_musicBtn_clicked()
{
    qDebug() << "音乐button";   
    if(!m_formLogin->E_LOGIN_STA)
    {
        MyMessageBox *pm_myMessageBox = new MyMessageBox;
        pm_myMessageBox->myMessageBox(":/images/13.jpg", "ERROR", "未登录");
        return ;
    }

    setCurrentWidget(E_MUSIC_WIDGET);
    CURRENT_WIDGET = E_MUSIC_WIDGET;
}

//实验环境button
void Widget::on_labEnvBtn_clicked()
{
    qDebug() << "实验环境button";
    if(!m_formLogin->E_LOGIN_STA)
    {
        MyMessageBox *pm_myMessageBox = new MyMessageBox;
        pm_myMessageBox->myMessageBox(":/images/13.jpg", "ERROR", "未登录");
        return ;
    }

    setCurrentWidget(E_LABENV_WIDGET);
    CURRENT_WIDGET = E_LABENV_WIDGET;
}

//实验动态button
void Widget::on_labEnvInfoBtn_clicked()
{
    qDebug() << "实验动态button";
    if(!m_formLogin->E_LOGIN_STA)
    {
         MyMessageBox *pm_myMessageBox = new MyMessageBox;
         pm_myMessageBox->myMessageBox(":/images/13.jpg", "ERROR", "未登录");
         return ;
    }

    setCurrentWidget(E_LABENVDYNAMIC_WIDGET);
    CURRENT_WIDGET = E_LABENVDYNAMIC_WIDGET;
}

//设备查询button
void Widget::on_devSearchBtn_clicked()
{
    qDebug() << "设备查询button";
    if(!m_formLogin->E_LOGIN_STA)
    {
         MyMessageBox *pm_myMessageBox = new MyMessageBox;
         pm_myMessageBox->myMessageBox(":/images/13.jpg", "ERROR", "未登录");
         return ;
    }

    setCurrentWidget(E_DEVSEARCH_WIDGET);
    CURRENT_WIDGET = E_DEVSEARCH_WIDGET;
}

//人员查询button
void Widget::on_memberInfoSearchBtn_clicked()
{
    qDebug() << "人员查询button";
    if(!m_formLogin->E_LOGIN_STA)
    {
         MyMessageBox *pm_myMessageBox = new MyMessageBox;
         pm_myMessageBox->myMessageBox(":/images/13.jpg", "ERROR", "未登录");
         return ;
    }

    setCurrentWidget(E_MEMBERINFO_WIDGET);
    CURRENT_WIDGET = E_MEMBERINFO_WIDGET;
}

//借用查询button
void Widget::on_borrowDevInfoBtn_clicked()
{
    qDebug() << "借用查询button";
    if(!m_formLogin->E_LOGIN_STA)
    {
        MyMessageBox *pm_myMessageBox = new MyMessageBox;
        pm_myMessageBox->myMessageBox(":/images/13.jpg", "ERROR", "未登录");
        return ;
    }

    setCurrentWidget(E_BOOROW_WIDGET);
    CURRENT_WIDGET = E_BOOROW_WIDGET;
}

//远程操作button
void Widget::on_remoteOperationBtn_clicked()
{
    qDebug() << "远程操作button";
    if(!m_formLogin->E_LOGIN_STA)
    {
        MyMessageBox *pm_myMessageBox = new MyMessageBox;
        pm_myMessageBox->myMessageBox(":/images/13.jpg", "ERROR", "未登录");
        return ;
    }

    setCurrentWidget(E_REMOTEOPERA_WIDGET);
    CURRENT_WIDGET = E_REMOTEOPERA_WIDGET;
}

void Widget::deletWidget()
{
    if (m_formborrowDevInfo != NULL){
        delete m_formborrowDevInfo;
        m_formborrowDevInfo = NULL;
    }
    if (m_formdevSearch != NULL){
        delete m_formdevSearch;
        m_formdevSearch = NULL;
    }
    if (m_formlabEnvdynamic != NULL){
        delete m_formlabEnvdynamic;
        m_formlabEnvdynamic = NULL;
    }
    if (m_formlabEnviroment != NULL){
        delete m_formlabEnviroment;
        m_formlabEnviroment = NULL;
    }
    if (m_formMemberInfoSearch != NULL){
        delete m_formMemberInfoSearch;
        m_formMemberInfoSearch = NULL;
    }
    if (m_formmusic != NULL){
        delete m_formmusic;
        m_formmusic = NULL;
    }
    if (m_formRemoteOperation != NULL){
        delete m_formRemoteOperation;
        m_formRemoteOperation = NULL;
    }
}
