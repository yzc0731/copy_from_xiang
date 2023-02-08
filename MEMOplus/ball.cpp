#include "ball.h"
#include "ui_ball.h"
#include <QPainter>
#include <QTimer>
#include <QDateTime>
#include <QMouseEvent>

Ball::Ball(QWidget *parent) :
    QDialog(parent),ui(new Ui::Ball)
{
    ui->setupUi(this);
    _beginPos = this->pos();
    // 无边框
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint|Qt::WindowStaysOnTopHint);
    // 窗口整体透明，但窗口控件不透明
    this->setAttribute(Qt::WA_TranslucentBackground,true);
    //在构造函数中
}

Ball::Ball(QWidget *parent, QString text, QPoint posBegin):
    QDialog(parent),ui(new Ui::Ball),_text(text),_beginPos(posBegin)
{
    ui->setupUi(this);
    this->move(_beginPos);
    // _beginPos = this->pos();
    // 无边框
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint|Qt::WindowStaysOnTopHint);
    // 窗口整体透明，但窗口控件不透明
    this->setAttribute(Qt::WA_TranslucentBackground,true);
}

void Ball::paintEvent(QPaintEvent *)
{
    QPainter p(this);//将当前窗体作为画布
    // if(_pressed)
        p.setBrush(Qt::white);//粉刷为白色
    // else
        // p.setBrush(QColor(255,255,255,10));
    p.setPen(Qt::NoPen);//没有线条
    //画圆形
    p.drawEllipse(_center,_radius,_radius);

    //添加文本，QTextOption(Qt::AlignCenter)可以让文本居中
    QPen pen = QPen(Qt::black);
    p.setPen(pen);
    p.drawText(QRect(_center.x()-_radius,_center.x()-_radius,2*_radius,2*_radius),
               _text, QTextOption(Qt::AlignCenter));
}

Ball::~Ball()
{
    delete ui;
}

void Ball::enterEvent(QEvent *){
    // emit this->backFromBall();
    QTimer *timer = new QTimer(this);
    timer->start(3000);
    connect(timer,&QTimer::timeout,this,&Ball::timeout);
}

// QCursor::pos() 的结果是鼠标相对于桌面的绝对位置
// mousePressEvent的参数event的位置，event->pos() 是鼠标相对于应用程序的位置，
// event->globalPos() 相对于桌面原点的位置，绝对位置

void Ball::timeout(){
    // QPoint coursepoint = QCursor::pos();

    int x=this->mapFromGlobal(QCursor().pos()).x();
    int y=this->mapFromGlobal(QCursor().pos()).y();

    int distance = (x-_center.x())*(x-_center.x())
            +(y-_center.y())*(y-_center.y());
    if ((distance<(_radius*_radius))
            && theFirstTimer){
        _beginPos = QPoint (QCursor().pos().x()-100,QCursor().pos().y()-100);
        theFirstTimer = false;
        emit this->backFromBall();
    }
}

void Ball::mousePressEvent(QMouseEvent *e){
   if(isContains(e->pos()))
    {
        _pressed = true;
        _beginPos = e->pos();    //鼠标相对窗体的位置
        update();                //触发窗体重绘
    }
}

void Ball::mouseReleaseEvent(QMouseEvent *e){
    _pressed = false;
    update();//触发窗体重绘
    if(isContains(e->pos()))    //当鼠标点击按钮
        emit clicked();         //发送点击信号
}

void Ball::mouseMoveEvent(QMouseEvent *e){
    if (_pressed)
    {
         //e->pos鼠标移动过程中，鼠标相对窗体的位置-刚按下鼠标时鼠标相对窗体的位置=鼠标移动的大小
         //鼠标移动的大小+窗体原来的位置=窗体移动后的位置

         this->move(e->pos() - _beginPos + this->pos());
    }
}

bool Ball::isContains(QPoint p){
    return (_center.x()-_radius < p.x()
            && _center.x()+_radius > p.x()
            && _center.y()-_radius < p.y()
            && _center.y()+_radius > p.y());
}// 将其看做方形的？

QPoint Ball::getBeginPos(){
    return _beginPos;
}
