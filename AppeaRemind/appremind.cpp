#include "appremind.h"
#include "ui_appremind.h"

#include "QPainter"
#include <QPoint>
#include <QMouseEvent>

AppRemind::AppRemind(QString Thing, QString Date, QString Time):
    ui(new Ui::AppRemind)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    this->setAttribute(Qt::WA_TranslucentBackground,true);
    ui->label_2->setText(Thing);
    ui->label->setText(Date+" "+Time);
}

AppRemind::~AppRemind()
{
    delete ui;
}

void AppRemind::mousePressEvent(QMouseEvent *e)
{
    pressed_ = true;
    beginPos_ = e->pos();
}

void AppRemind::mouseMoveEvent(QMouseEvent *e)
{
    if (pressed_){
        this->move(e->pos() - beginPos_ + this->pos());
    }
}

void AppRemind::mouseReleaseEvent(QMouseEvent *)
{
    pressed_ = false;
}

void AppRemind::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    for(int i=0;i<=60;i++)
    {
        p.setPen(QPen(QColor(0,120,255,4*i),5));
        p.drawLine(QPointF(i,i),QPointF(i,i));
    }
    p.drawLine(QPoint(60,60),QPoint(60,90));
    p.drawLine(QPoint(60,60),QPoint(90,60));
    p.drawLine(QPoint(30,30),QPoint(90,30));
    p.setPen(QPen(QColor(0,120,255,4*60),6));//粉刷为白色
    p.drawRect(60,60,120,120);
}
