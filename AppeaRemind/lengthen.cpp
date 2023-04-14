#include "lengthen.h"
#include "ui_lengthen.h"
#include <QDebug>
#include "datetime.h"

lengthen::lengthen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::lengthen)
{
    ui->setupUi(this);
    //创建定时器定时更新时间和日期
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(myslot()));
    ui->spinBox->setValue(10);
}

lengthen::~lengthen()
{
    delete ui;
}

void lengthen::myslot()
{
    //show();
    dateTime* alarm = new dateTime;                                  //计时到，再次显示
    alarm->show();
    timer->stop();
}

void lengthen::on_pushButton_clicked()
{
    int num = ui->spinBox->value();                      //计时秒数（600秒）
    num = num*60;
    num *= 1000;
    timer->start(num);
    hide();
}
