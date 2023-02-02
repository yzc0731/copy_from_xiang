#include "suspenddia.h"
#include "ui_suspenddia.h"
#include <QPushButton>
SuspendDia::SuspendDia(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SuspendDia)
{
    ui->setupUi(this);
    ui->title->setText(tr("软件名称"));
    ui->backBtn->setText(tr("回到主界面"));
    ui->exitBtn->setText(tr("退出悬浮球"));

    //监测信号，当按下back信号的时候，会发出一个back信号
    connect(ui->backBtn,&QPushButton::clicked,[=](){
        emit this->back();
    });
}

SuspendDia::~SuspendDia()
{
    delete ui;
}

void SuspendDia::on_exitBtn_clicked()
{
    this->close();
}
