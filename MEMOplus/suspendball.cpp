#include "suspendball.h"
#include "ui_suspendball.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDialog>
/*
suspendBall::suspendBall(const QString text, QPoint center,int radius):
    QDialog(nullptr),_text(text), _center(center),_radius(radius)
{
    initForm();
}
*/
suspendBall::suspendBall(QWidget *parent):
    QDialog(parent),_text("CircleButton"),_center(50,50),_radius(50)
{
    initForm();
}

suspendBall::suspendBall(const QString text, QPoint center,int radius,QWidget *parent):
    QDialog(parent),_text(text), _center(center),_radius(radius)
{
    initForm();
}

suspendBall::~suspendBall()
{
    delete ui;
}

void suspendBall::initForm()
{
    _pressed = false;
    beginPos = this->pos();
    //无边框
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint|Qt::WindowStaysOnTopHint);
    /*  窗口整体透明，但窗口控件不透明*/
   this->setAttribute(Qt::WA_TranslucentBackground,true);
}

void suspendBall::paintEvent(QPaintEvent *)
{
    QPainter p(this);//将当前窗体作为画布
    // if(_pressed)
        p.setBrush(Qt::white);//粉刷为白色
    // else
        // p.setBrush(QColor(255,255,255,10));
    p.setPen(Qt::NoPen);//没有线条
    //画圆形
    p.drawEllipse(_center,_radius,_radius);
    //添加文本
    QPen pen = QPen(Qt::black);
    p.setPen(pen);
    p.drawText(QRect(_center.x()-_radius,_center.x()-_radius,2*_radius,2*_radius),
               _text, QTextOption(Qt::AlignCenter));
    //文本居中：QTextOption(Qt::AlignCenter)
}
void suspendBall::mousePressEvent(QMouseEvent *e)
{
   if(isContains(e->pos()))
    {
        _pressed = true;
        beginPos = e->pos();//鼠标相对窗体的位置
        update();//触发窗体重绘
    }
}
void suspendBall::mouseReleaseEvent(QMouseEvent *e)
{
    _pressed = false;
    update();//触发窗体重绘
    if(isContains(e->pos()))//当鼠标点击按钮
        emit clicked();//发送点击信号
}
void suspendBall::mouseMoveEvent(QMouseEvent *e)       //--鼠标移动事件
{
    if (_pressed)
    {
        this->move(e->pos() - beginPos + this->pos());
        //当前鼠标相对窗体的位置-刚按下左键时的相对位置=鼠标移动的大小
        //鼠标移动的大小+窗体原来的位置=窗体移动后的位置
    }
}
bool suspendBall::isContains(QPoint p)
{
    return (_center.x()-_radius < p.x()
            && _center.x()+_radius > p.x()
            && _center.y()-_radius < p.y()
            && _center.y()+_radius > p.y());
}


