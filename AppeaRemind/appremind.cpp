#include "appremind.h"
#include "ui_appremind.h"
#include "QPainter"
#include <QPoint>
#include <QMouseEvent>
#include <QDebug>

AppRemind::AppRemind(QString Thing, QString Date, QString Time):
    ui(new Ui::AppRemind)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    this->setAttribute(Qt::WA_TranslucentBackground,true);
    QFont font ("Microsoft YaHei", 10, 75);
    ui->label_2->setText(Thing);
    ui->label_2->setFont(font);
    ui->label->setText(Date+" "+Time);
    ui->label->setFont(font);
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
        p.setPen(QPen(QColor(0,120,255,3*i),7));
        p.drawLine(QPointF(i,i),QPointF(i,i));
    }
    p.drawLine(QPoint(60,60),QPoint(60,90));
    p.drawLine(QPoint(60,60),QPoint(90,60));
    p.setBrush(QColor(255,255,255,150));
    p.setPen(Qt::NoPen);//没有线条
    p.drawRect(60,0,145,58);
    QPainterPath path;
    path.moveTo (0, 0);
    path.lineTo (60, 0);
    path.lineTo (60, 60);
    path.lineTo (0, 0);
    p.fillPath (path, QColor(255,255,255,150));
    //p.drawRect(60,60,120,120);    //TODO: capacity change to 0
}
