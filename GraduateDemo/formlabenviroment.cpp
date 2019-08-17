#include "formlabenviroment.h"
#include "ui_formlabenviroment.h"

#include "databases.h"
#include <QDebug>
#include "mymessagebox.h"

FormlabEnviroment::FormlabEnviroment(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormlabEnviroment)
{
    ui->setupUi(this);

    this->initForm();
    this->initTimer();
}

FormlabEnviroment::~FormlabEnviroment()
{
    delete ui;
}

//初始化界面
void FormlabEnviroment::initForm()
{

}

//初始化定时器
void FormlabEnviroment::initTimer()
{
    pm_timer = new QTimer(this);
    connect(pm_timer,SIGNAL(timeout()),
            this,SLOT(showEnverimentInfo()));
    pm_timer->start(5000);
}

void FormlabEnviroment::showEnverimentInfo()
{
    bool ok = m_DB.open();
    if(ok){
        QSqlQuery query(m_DB);
        QString sql = "select * from envdata order by id DESC limit 1";
        query.exec(sql);
        if (query.next()) {
            ui->tempLabel->setText(QString::number(query.value(2).toInt()));
            ui->humiLabel->setText(QString::number(query.value(3).toInt()));
            ui->lightLabel->setText(QString::number(query.value(4).toInt()));
            ui->ppmLabel->setText(QString::number(query.value(5).toInt()));
        }else{
            qDebug() << "sql语法错误";
        }

        sql = "SELECT COUNT(*) FROM envdata";
        query.exec(sql);
        if(query.next()){
            int count = query.value(0).toInt();
            if(count > 100){ //数据库中只存储100环境记录
                sql = "DELETE from envdata";
                query.exec(sql);
                qDebug() << "已清空";
            }
        }else{
            qDebug() << "没有记录";
        }
        m_DB.close(); //关闭数据库
    }else{
        ;; //打开数据库失败
    }
}









