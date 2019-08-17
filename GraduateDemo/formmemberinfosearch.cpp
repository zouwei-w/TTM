#include "formmemberinfosearch.h"
#include "ui_formmemberinfosearch.h"

#include "databases.h"
#include "mymessagebox.h"

FormMemberInfoSearch::FormMemberInfoSearch(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormMemberInfoSearch)
{
    ui->setupUi(this);

    this->initForm();

    //table表的槽函数，当有刷新时，会响应槽函数
    connect(table,SIGNAL(MEMBERSEARCH_SIG()),this,SLOT(flushData()));

    //刷新数据库
    this->flushData();
}

FormMemberInfoSearch::~FormMemberInfoSearch()
{
    delete ui;
}

void FormMemberInfoSearch::flushData()
{
    qDebug() << "刷新表格数据";
    bool ok = m_DB.open();
    if(ok){
        QStringList data;
        QString empid,time,fingerid,nuno,name,profsionclas;
        QSqlQuery query(m_DB);
        QString sql = "select * from stuinfo";
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

void FormMemberInfoSearch::initForm()
{
    table = new Table(this);

    QStringList header;
    header<<tr("ID")<<tr("TIME")<<tr("指纹ID")<<tr("学号")<<tr("姓名")<<tr("专业班级");
    table->setColumnValue(6, header); //设置几列和头内容

    //设置每一列的宽度
    table->setHeaderWidth(0, 50);
    table->setHeaderWidth(1, 150);
    table->setHeaderWidth(2, 50);
    table->setHeaderWidth(3, 100);
    table->setHeaderWidth(4, 100);
    table->setHeaderWidth(5, 100);
    table->setHeaderWidth(6, 100);
    //设置表头的高度
    table->setHeaderHeight(30);
    //设置表的宽度和高度
    table->setTableWidthAndHeight(650, 410);

}

//根据学号查询
void FormMemberInfoSearch::on_searchToolButton_clicked()
{
    MyMessageBox *pm_myMessageBox = new MyMessageBox;
    if(ui->nunoLineEdit->text().isEmpty()){
        pm_myMessageBox->myMessageBox(":/images/13.jpg", "ERROR", "请输入所查询的学号");
        return ;
    }
    bool ok = m_DB.open();
    if(ok){
        QSqlQuery query(m_DB);
        QString sql = "select * from stuinfo where nuno='"+ui->nunoLineEdit->text()+"'";
        query.exec(sql);
        if(query.next()) {
            //myMessageBox(":/images/12.jpg", "SUCCESS", "已查询到该学生");
            QString str = query.value(4).toString();
            ui->textBrowser->setText("已查询到学号为: "+ui->nunoLineEdit->text()+
                                     "  姓名为: " + str + " 的同学信息");
            QList<QTableWidgetItem*> itemVec=table->findItems(ui->nunoLineEdit->text(),Qt::MatchExactly);
            int rw = itemVec.at(0)->row();
            //自动选择行，并且高亮该行
            table->setSelectionBehavior(QAbstractItemView::SelectRows);
            table->setStyleSheet("selection-background-color:rgb(255,209,128)");
            table->selectRow(rw);

            qDebug() << "行: " + QString::number(rw);

        }else{
            ui->textBrowser->setText("未查询到该同学信息");
        }
        m_DB.close(); //关闭数据库
    }else{
        qDebug() << "打开数据库失败";
    }
}





