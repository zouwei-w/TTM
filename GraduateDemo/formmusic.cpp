#include "formmusic.h"
#include "ui_formmusic.h"

#include "databases.h"
#include "common.h"
#include "mymessagebox.h"

Formmusic::Formmusic(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Formmusic)
{
    ui->setupUi(this);
    this->initForm();
}

Formmusic::~Formmusic()
{
    delete ui;
}

void Formmusic::initForm()
{
    ui->label_2->setAttribute(Qt::WA_TranslucentBackground);
    ui->label_3->setAttribute(Qt::WA_TranslucentBackground);

    QPalette p;
    p.setBrush(this->backgroundRole(),QBrush(QColor(0,0,127,255)));
    this->setPalette(p);
    this->setAutoFillBackground(true);
}













