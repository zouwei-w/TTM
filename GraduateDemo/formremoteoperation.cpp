#include "formremoteoperation.h"
#include "ui_formremoteoperation.h"

#include "databases.h"
#include "common.h"
#include <QTextCodec>
#include "widget.h"
#include <QImage>
#include "mymessagebox.h"

FormRemoteOperation::FormRemoteOperation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormRemoteOperation)
{
    ui->setupUi(this);

    this->initForm();

}

FormRemoteOperation::~FormRemoteOperation()
{
    delete ui;
}

void FormRemoteOperation::initForm()
{
    ui->ledButton->setText("LED1");
    ui->ledButton->setFont(QFont("文泉驿雅黑",12,QFont::Bold));
    ui->ledButton->setAutoRaise(true);
    ui->ledButton->setIcon(QPixmap(QString("%1").arg(":/images/btncheckoff.png")));
    ui->ledButton->setIconSize(QPixmap(QString("%1").arg(":/images/btncheckoff.png")).size());
    ui->ledButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    ui->ledButton_2->setText("LED2");
    ui->ledButton_2->setFont(QFont("文泉驿雅黑",12,QFont::Bold));
    ui->ledButton_2->setAutoRaise(true);
    ui->ledButton_2->setIcon(QPixmap(QString("%1").arg(":/images/btncheckoff.png")));
    ui->ledButton_2->setIconSize(QPixmap(QString("%1").arg(":/images/btncheckoff.png")).size());
    ui->ledButton_2->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    led1_sta = false;
    led2_sta = false;

}

void FormRemoteOperation::setLedStatus(QToolButton *btn, QLabel *lb, QString strbtn, QString strlab)
{
    btn->setIcon(QPixmap(QString("%1").arg(strbtn)));
    btn->setIconSize(QPixmap(QString("%1").arg(strbtn)).size());
    lb->setStyleSheet(strlab);
}

void FormRemoteOperation::on_ledButton_clicked()
{  
    MyMessageBox *pm_myMessageBox = new MyMessageBox;
    int ledsta = 0;
    if(led1_sta){
        ledsta = 0;
        setLedStatus(ui->ledButton,ui->ledLabel_1,":/images/btncheckoff.png","image: url(:/images/light_off1.png);");
    }else{
        ledsta = 1;
        setLedStatus(ui->ledButton,ui->ledLabel_1,":/images/btncheckon.png", "image: url(:/images/light_on1.png);");
    }
    led1_sta = !led1_sta;

    bool ok = m_DB.open();
    if(ok){
        QSqlQuery query(m_DB);
        query.prepare("update cmddata set devselect=:devselect,"
                      "devstatus=:ledsta");
        query.bindValue(":devselect", 1);
        query.bindValue(":ledsta", ledsta);
        query.exec();
        m_DB.close();
    }else{
        pm_myMessageBox->myMessageBox(":/images/13.jpg", "ERROR", "操作灯失败!");
    }
}

void FormRemoteOperation::on_ledButton_2_clicked()
{
    MyMessageBox *pm_myMessageBox = new MyMessageBox;
    int ledsta = 0;
    if(led2_sta){
        ledsta = 0;
        setLedStatus(ui->ledButton_2,ui->ledLabel_2,":/images/btncheckoff.png","image: url(:/images/light_off.png);");
    }else{
        ledsta = 1;
        setLedStatus(ui->ledButton_2,ui->ledLabel_2,":/images/btncheckon.png","image: url(:/images/light_on.png);");
    }
    led2_sta = !led2_sta;

    bool ok = m_DB.open();
    if(ok){
        QSqlQuery query(m_DB);
        query.prepare("update cmddata set devselect=:devselect,"
                      "devstatus=:ledsta");
        query.bindValue(":devselect", 2);
        query.bindValue(":ledsta", ledsta);
        query.exec();
        m_DB.close();
    }else{
        pm_myMessageBox->myMessageBox(":/images/13.jpg", "ERROR", "操作灯失败!");
    }
}


