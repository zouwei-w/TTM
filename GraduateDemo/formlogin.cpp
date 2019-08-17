#include "formlogin.h"
#include "ui_formlogin.h"
#include "common.h"
#include "databases.h"
#include "mymessagebox.h"
#include "formregister.h"

FormLogin::FormLogin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormLogin)
{
    ui->setupUi(this);
    this->initForm();

    E_LOGIN_STA = false;
    remberCheckBox = false;
    autoLoginCheckBox = false;
    pm_formRegister = new FormRegister;
}

FormLogin::~FormLogin()
{
    delete ui;
}

void FormLogin::initForm()
{
    //登录界面
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint
                         | Qt::WindowMinMaxButtonsHint );
    this->setWindowTitle(tr("开放实验室无人值守远程监控系统"));

    this->setStyleSheet("border-radius: 3px;");

    QRect deskRect = QApplication::desktop()->availableGeometry();
    int x = deskRect.width();
    int y = deskRect.height();
    this->setGeometry((x-this->width())/2,(y-this->height())/2,this->width(),this->height());

    ui->widgetTop->setStyleSheet("QWidget{border-image: url(:/images/deepblue.png);}");
    ui->widget->setStyleSheet("QWidget{border-image: rgb(255, 255, 255);}");
    ui->loginButton->setStyleSheet("border-image: url(:/images/deepblue.png);border-radius: 6px; color: rgb(255, 255, 255);");
    ui->loginButton->setFont(QFont("文泉驿雅黑",12,QFont::Bold));

    ui->label->setAttribute(Qt::WA_TranslucentBackground);
    ui->registToolButton->setAttribute(Qt::WA_TranslucentBackground);
    ui->autoLoginCheckBox->setAttribute(Qt::WA_TranslucentBackground);
    ui->remberPassCheckBox->setAttribute(Qt::WA_TranslucentBackground);
    ui->userEdit->setFont(QFont("文泉驿雅黑",12,QFont::Bold));
    ui->passwordEdit->setEchoMode(QLineEdit::Password); //密码格式
}

void FormLogin::on_loginButton_clicked()
{
    this->close();
    MyMessageBox *pm_myMessageBox = new MyMessageBox;
#if 1
    if(ui->userEdit->text().isEmpty() || ui->passwordEdit->text().isEmpty())
    {
        pm_myMessageBox->myMessageBox(":/images/13.jpg", "ERROR", "请将信息填写完整");
        return ;
    }

    QString user =  ui->userEdit->text();
    QString password = ui->passwordEdit->text();

    /*************************** 数据库操作 *******************************/
    bool ok = m_DB.open();
    if(ok){
        QString sql = "select * from usertable where username="
                      "'"+user+"' and password='" + password + "'";
        QSqlQuery query(m_DB);
        query.exec(sql);
        if(query.next()){
            pm_myMessageBox->myMessageBox(":/images/12.jpg", "SUCCESS", "登录成功!");
            emit LOGINSTA_SIG();
            E_LOGIN_STA = true; //登录状态:成功
            this->close();
        }else{
            pm_myMessageBox->myMessageBox(":/images/13.jpg", "ERROR", "用户名或密码错误");
        }
    }else{
        pm_myMessageBox->myMessageBox(":/images/13.jpg", "ERROR", "登录失败!");
    }
#endif
}

// 注册
void FormLogin::on_registToolButton_clicked()
{
    pm_formRegister->show();
}

//记住密码
void FormLogin::on_remberPassCheckBox_clicked()
{
   if(remberCheckBox){//去选上
       ui->remberPassCheckBox->setChecked(true);
       if(ui->userEdit->text().isEmpty() || ui->passwordEdit->text().isEmpty()){
           MyMessageBox *pm_myMessageBox = new MyMessageBox;
           pm_myMessageBox->myMessageBox(":/images/13.jpg", "ERROR", "请将信息填写完整");
       }
       m_username = ui->userEdit->text();
       m_password = ui->passwordEdit->text();

   }else{
       ui->remberPassCheckBox->setChecked(false);
   }
   remberCheckBox = !remberCheckBox;
}

//自动登录
void FormLogin::on_autoLoginCheckBox_clicked()
{
    if(autoLoginCheckBox){//去选上
       ui->autoLoginCheckBox->setChecked(true);
    }else{
       ui->autoLoginCheckBox->setChecked(false);
    }
    autoLoginCheckBox = !autoLoginCheckBox;
}
