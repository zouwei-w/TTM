#include "mymessagebox.h"
#include "ui_mymessagebox.h"

MyMessageBox::MyMessageBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyMessageBox)
{
    ui->setupUi(this);
    this->initForm();
}

MyMessageBox::~MyMessageBox()
{
    delete ui;
}

void MyMessageBox::myMessageBox(QString path, QString tile, QString text)
{
    ui->label->setFont(QFont("文泉驿雅黑",16,QFont::Bold));
    ui->label_3->setFont(QFont("文泉驿雅黑",12,QFont::Bold));
    ui->label_2->setStyleSheet("image: url(" + path + ")");
    ui->okPushButton->setFont(QFont("文泉驿雅黑",12,QFont::Bold));

    ui->label->setText(tile);
    ui->label_3->setText(text);

    this->show();   
}

void MyMessageBox::initForm()
{
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint
                         | Qt::WindowMinMaxButtonsHint|Qt::WindowStaysOnTopHint);
    this->setStyleSheet("border-radius: 5px;");
    ui->label->setAttribute(Qt::WA_TranslucentBackground);
    ui->label_3->setAttribute(Qt::WA_TranslucentBackground);

    this->setAttribute(Qt::WA_DeleteOnClose); //close时 自动销毁
}

void MyMessageBox::on_okPushButton_clicked()
{
    this->close();
}
