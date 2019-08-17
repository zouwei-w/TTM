#include "formdevsearch.h"
#include "ui_formdevsearch.h"

#include "databases.h"
#include "common.h"
#include "mymessagebox.h"

FormdevSearch::FormdevSearch(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormdevSearch)
{
    ui->setupUi(this);

    this->initForm();

    //table表的槽函数，当有刷新时，会响应槽函数
    connect(table,SIGNAL(DEVSEARCH_SIG()),this,SLOT(flushData()));

    //刷新数据库
    this->flushData();
}

FormdevSearch::~FormdevSearch()
{
    delete ui;
}

void FormdevSearch::flushData()
{
    qDebug() << "刷新表格数据";
    bool ok = m_DB.open();
    if(ok){
        QStringList data;
        QString id,time,devnum,devid,devname,devdesc;
        QSqlQuery query(m_DB);
        QString sql = "select * from devtable";
        query.exec(sql);
        while (query.next()) {
            id = QString::number(query.value(0).toInt());
            time = query.value(1).toString();
            devnum = QString::number(query.value(2).toInt());
            devid = query.value(3).toString();
            devname = query.value(4).toString();
            devdesc = query.value(5).toString();
            data<<id<<time<<devnum<<devid<<devname<<devdesc;
            table->addRowValue(30, data);
            data.clear();
        }
        m_DB.close(); //关闭数据库
    }else{
        qDebug() << "打开数据库失败";
    }
}

void FormdevSearch::initForm()
{
    table = new Table(this);

    QStringList header;
    header<<tr("ID")<<tr("TIME")<<tr("设备数量")<<tr("设备ID")<<tr("设备名称")<<tr("描述信息");
    table->setColumnValue(6, header); //设置几列和头内容

    //设置每一列的宽度
    table->setHeaderWidth(0, 50);
    table->setHeaderWidth(1, 150);
    table->setHeaderWidth(2, 100);
    table->setHeaderWidth(3, 171);
    table->setHeaderWidth(4, 100);
    table->setHeaderWidth(5, 350);
    //设置表头的高度
    table->setHeaderHeight(30);
    //设置表的宽度和高度
    table->setTableWidthAndHeight(920, 410);

    resize(800, 800);
}
