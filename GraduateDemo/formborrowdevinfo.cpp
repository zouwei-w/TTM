#include "formborrowdevinfo.h"
#include "ui_formborrowdevinfo.h"

#include "databases.h"
#include "common.h"
#include "mymessagebox.h"


FormborrowDevInfo::FormborrowDevInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormborrowDevInfo)
{
    ui->setupUi(this);

    this->initForm();

    //table表的槽函数，当有刷新时，会响应槽函数
    connect(table,SIGNAL(BORROW_SIG()),this,SLOT(flushData()));

    //刷新数据库
    this->flushData();
}

FormborrowDevInfo::~FormborrowDevInfo()
{
    delete ui;
}

//刷新表格数据
void FormborrowDevInfo::flushData()
{
    qDebug() << "刷新表格数据";
    bool ok = m_DB.open();
    if(ok){
        QStringList data;
        QString time,devid,devname,nuno,name,profsionclas,borrowdesc;
        QSqlQuery query(m_DB);
        QString sql = "select * from borrowdevtable";
        query.exec(sql);
        while (query.next()) {
            time = query.value(1).toString();
            devid = query.value(2).toString();
            devname = query.value(3).toString();
            nuno = query.value(4).toString();
            name = query.value(5).toString();
            profsionclas = query.value(6).toString();
            borrowdesc = query.value(7).toString();
            data<<time<<devid<<devname<<nuno<<name<<profsionclas<<borrowdesc;
            table->addRowValue(30, data);
            data.clear();
        }
        m_DB.close(); //关闭数据库
    }else{
        qDebug() << "打开数据库失败";
    }
}

void FormborrowDevInfo::initForm()
{
    table = new Table(this);

    QStringList header;
    header<<tr("借用时间")<<tr("设备ID")<<tr("设备名称")<<tr("学号")<<tr("姓名")<<tr("专业班级")<<tr("借用说明");
    table->setColumnValue(7, header); //设置几列和头内容

    //设置每一列的宽度
    table->setHeaderWidth(0, 150);
    table->setHeaderWidth(1, 150);
    table->setHeaderWidth(2, 100);
    table->setHeaderWidth(3, 100);
    table->setHeaderWidth(4, 100);
    table->setHeaderWidth(5, 100);
    table->setHeaderWidth(6, 221);
    //设置表头的高度
    table->setHeaderHeight(30);
    //设置表的宽度和高度
    table->setTableWidthAndHeight(920, 410);
}
