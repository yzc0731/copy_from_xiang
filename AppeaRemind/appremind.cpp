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
        QFont font ("Microsoft YaHei", 8);
        ui->label_2->setFont(font);
        ui->label_2->setWordWrap(true);
        ui->label_2->setAlignment(Qt::AlignTop);
        ui->label_2->setText(Thing.split("", QString::SkipEmptyParts).join("\n"));
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

void AppRemind::mouseDoubleClickEvent(QMouseEvent *)
{
   this->close();
}

void AppRemind::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    for(int i=0;i<=30;i++){
        p.setPen(QPen(QColor(0,120,255,3*i),7));
        p.drawLine(QPointF(i,i),QPointF(i,i));
    }//画出那条斜线

    p.drawLine(QPoint(30,30),QPoint(90,30));
    p.drawLine(QPoint(30,30),QPoint(30,90));
    //画出那个框

    p.setBrush(QColor(255,255,255,150));//白色
    p.setPen(Qt::NoPen);//没有线条

    QPainterPath path;
    path.moveTo (0, 0);
    path.lineTo (180, 0);
    path.lineTo (180, 30);
    path.lineTo (30, 30);
    path.lineTo (0, 0);
    p.fillPath (path, QColor(255,255,255,150));
    //画出白色的直角梯形

    p.setBrush(QColor(199,237,207,150));
    QPainterPath path2;
    path2.moveTo (0, 0);
    path2.lineTo (0, 180);
    path2.lineTo (30, 180);
    path2.lineTo (30, 30);
    path2.lineTo (0, 0);
    p.fillPath (path2, QColor(199,237,207,150));
    //画出绿色的直角梯形
}
