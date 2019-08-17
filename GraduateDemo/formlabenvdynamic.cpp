#include "formlabenvdynamic.h"
#include "ui_formlabenvdynamic.h"

#include "databases.h"
#include "common.h"
#include "mymessagebox.h"

FormlabEnvdynamic::FormlabEnvdynamic(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormlabEnvdynamic)
{
    ui->setupUi(this);

    this->initForm();

    //table表的槽函数，当有刷新时，会响应槽函数
    connect(table,SIGNAL(LABDYNAMIC_SIG()),this,SLOT(flushData()));

    //刷新数据库
    this->flushData();

}

FormlabEnvdynamic::~FormlabEnvdynamic()
{
    delete ui;
}

//刷新表格数据
void FormlabEnvdynamic::flushData()
{
    qDebug() << "刷新表格数据";
    bool ok = m_DB.open();
    if(ok){
        QStringList data;
        QString empid,time,fingerid,nuno,name,profsionclas;
        QSqlQuery query(m_DB);
        QString sql = "select * from curinfotable";
        query.exec(sql);
        while (query.next()) {
            empid = QString::number(query.value(0).toInt());
            time = query.value(1).toString();
            fingerid = QString::number(query.value(2).toInt());
            nuno = query.value(3).toString();
            name = query.value(4).toString();
            profsionclas = query.value(5).toString();
            data<<empid<<time<<fingerid<<nuno<<name<<profsionclas;
            table->addRowValue(30, data);
            data.clear();
        }
        m_DB.close(); //关闭数据库
    }else{
        qDebug() << "打开数据库失败";
    }
}

void FormlabEnvdynamic::initForm()
{
    table = new Table(this);

    QStringList header;
    header<<tr("ID")<<tr("TIME")<<tr("指纹ID")<<tr("学号")<<tr("姓名")<<tr("专业班级");
    table->setColumnValue(6, header); //设置几列和头内容

    //设置表头的高度
    table->setHeaderHeight(30);

    //设置表头的宽度
    table->setHeaderWidth(0, 50);
    table->setHeaderWidth(1, 150);
    table->setHeaderWidth(2, 50);
    table->setHeaderWidth(3, 100);
    table->setHeaderWidth(4, 100);
    table->setHeaderWidth(5, 100);
    table->setHeaderWidth(6, 100);

    //设置表的宽度和高度
    table->setTableWidthAndHeight(650, 410);
}
