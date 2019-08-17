#include "formregister.h"
#include "ui_formregister.h"

#include "mymessagebox.h"
#include "common.h"
#include "databases.h"

#include <QJsonObject>
#include <QJsonDocument>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QEventLoop>
#include <QTextCodec>
#include <QTimer>

FormRegister::FormRegister(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormRegister)
{
    ui->setupUi(this);

    this->initForm();

    this->initWidget();
}

FormRegister::~FormRegister()
{
    delete ui;
}

// 更新发送按钮状态
void FormRegister::updateBtnvalue()
{
    ui->sendSmsBtn->setText(QString::number(timeCount--));
    if(timeCount <= 0)
    {
       m_timer->stop();
       ui->sendSmsBtn->setText("发送验证码");
       timeCount = 60; //还原
       E_PRESSSTA = false;
    }
}

void FormRegister::initForm()
{
    //设置窗体标题栏隐藏
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint
                         | Qt::WindowMinMaxButtonsHint);

    this->setStyleSheet("border-radius: 2px;");

    QRect deskRect = QApplication::desktop()->availableGeometry();
    int x = deskRect.width();
    int y = deskRect.height();
    this->setGeometry((x-this->width())/2,(y-this->height())/2,this->width(),this->height());

    ui->regPass->setEchoMode(QLineEdit::Password); //密码格式
    ui->regPassTwo->setEchoMode(QLineEdit::Password); //密码格式
}


void FormRegister::initWidget()
{
    timeCount = 60;

    E_PRESSSTA = false;
}

void FormRegister::flushData()
{
    ui->regName->setText("");
    ui->regPass->setText("");
    ui->regPassTwo->setText("");
    ui->regPhone->setText("");
    m_timer->stop();
    ui->sendSmsBtn->setText("发送验证码");
    timeCount = 60; //还原
    E_PRESSSTA = false;
}


void FormRegister::on_cancleBtn_clicked()
{
    this->close();
}

void FormRegister::on_regBtn_clicked()
{
    MyMessageBox *pm_myMessageBox = new MyMessageBox;
    QString name = ui->regName->text();
    QString pass = ui->regPass->text();
    QString repass = ui->regPassTwo->text();
    QString phone = ui->regPhone->text();
    QString vrcode = ui->vrLineEdit->text();
    if(name.isEmpty() || pass.isEmpty() || repass.isEmpty() || phone.isEmpty())
    {
        pm_myMessageBox->myMessageBox(":/images/13.jpg", "ERROR", "请将信息填写完整");
        return;
    }
    if(pass != repass){
        pm_myMessageBox->myMessageBox(":/images/13.jpg", "ERROR", "两次输入的密码不同");
        return ;
    }
    if(vrcode == m_vrcode) //如果输入验证码正确
    {
        bool ok = m_DB.open();
        if(ok){
            QSqlQuery query(m_DB);

            // 验证用户名存在
            QString sql = "select * from usertable where username='" + name +"'";
            query.exec(sql);
            if(query.next()){
                pm_myMessageBox->myMessageBox(":/images/13.jpg", "ERROR", "用户名已存在!");
                m_DB.close();
                flushData(); //刷新
                return ;
            }
            // 验证手机号
            sql = "select * from usertable where phonenumber='" + phone +"'";
            query.exec(sql);
            if(query.next()){
                pm_myMessageBox->myMessageBox(":/images/13.jpg", "ERROR", "该手机号已被使用!");
                m_DB.close();
                flushData(); //刷新
                return ;
            }

            query.prepare("INSERT INTO usertable(username, password, phonenumber)"
                          "VALUES(:username, :password, :phonenumber)");
            query.bindValue(":username", name);
            query.bindValue(":password", pass);
            query.bindValue(":phonenumber", phone);
            query.exec();
            m_DB.close();
            pm_myMessageBox->myMessageBox(":/images/12.jpg", "SUCCESS", "注册成功");
            this->close(); //关闭界面
        }else{
            pm_myMessageBox->myMessageBox(":/images/13.jpg", "ERROR", "注册失败,请联系客服");
        }
        flushData(); //刷新
    }else{
        ui->vrLineEdit->setText("");
        pm_myMessageBox->myMessageBox(":/images/12.jpg", "SUCCESS", "输入验证码错误");
    }
}

//发送验证码
void FormRegister::on_sendSmsBtn_clicked()
{
    qDebug() << "发送";

    MyMessageBox *pm_myMessageBox = new MyMessageBox;

    if(E_PRESSSTA) //已经点击,等待60s
        return ;

    ui->sendSmsBtn->setText("已发送");
    E_PRESSSTA = true;

    if(ui->regPhone->text().isEmpty()){
        pm_myMessageBox->myMessageBox(":/images/13.jpg", "ERROR", "请填写电话号码");
        return ;
    }
    QString telnumber = ui->regPhone->text();
    m_vrcode = randVrcode(); //随机生成验证码

    QString data = "{\"vrcode\":\"" + m_vrcode + "\",\"telnumber\":\"" + telnumber + "\"}";

    QNetworkAccessManager naManager;
    QNetworkRequest request;
    request.setUrl(QUrl("http://112.74.45.81:8081/smsAction/sendSmsInfo"));
    request.setRawHeader("Content-Type","application/json;charset=GBK");
    QNetworkReply *reply = naManager.post( request, data.toLocal8Bit() );

    //更新发送按钮状态
    m_timer = new QTimer(this);
    connect(m_timer,SIGNAL(timeout()),this,SLOT(updateBtnvalue()));
    m_timer->start(1000);

    QEventLoop eventloop;
    connect( reply,SIGNAL(finished()),&eventloop,SLOT(quit()));
    eventloop.exec( QEventLoop::ExcludeUserInputEvents);

    QTextCodec *codec = QTextCodec::codecForName("utf8");
    QString replyData = codec->toUnicode( reply->readAll() );

    reply->deleteLater();
    reply = 0;

    qDebug() << replyData;
}

QString FormRegister::randVrcode()
{
    int code[6];
    QTime time;
    time= QTime::currentTime();
    qsrand(time.msec()+time.second()*1000);
    for(int i = 0; i < 6; i ++)
        code[i] = qrand() % 9;    //产生5以内的随机数

    QString strcode = "";
    for(int i = 0; i < 6; i ++)
        strcode += code[i] + '0';

    if(strcode.isEmpty()){
        return "698247";
    }else{
        return strcode;
    }
}






