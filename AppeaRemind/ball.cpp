#include "ball.h"
#include "ui_ball.h"

#include <QPainter>
#include <QTimer>
#include <QDateTime>
#include <QMouseEvent>
#include <QDesktopWidget>
#include <QDebug>
#include <QApplication>
#include <QScreen>

Ball::Ball(QWidget *parent) :
    QDialog(parent),ui(new Ui::Ball)
{
    ui->setupUi(this);
    _beginPos = this->pos();

    // 无边框
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint
                         | Qt::WindowMinMaxButtonsHint|Qt::WindowStaysOnTopHint);

    // 窗口整体透明，但窗口控件不透明
    this->setAttribute(Qt::WA_TranslucentBackground,true);
}

Ball::Ball(QWidget *parent, QString text, QPoint posBegin, int radius, QString importance):
    QDialog(parent),ui(new Ui::Ball),_text(text),
    _beginPos(posBegin), _radius(radius), _importance(importance)
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
    p.setBrush(Qt::white);//粉刷为白色
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

void Ball::enterEvent(QEvent *e)
{   //鼠标进入悬浮球，停止计时器，回到原位置,新建一个计时器，然后再等0.5秒之后才可能触发hide操作
    if (m_timer != nullptr )
    {
        if(m_timer->isActive()){
            m_timer->stop();
        }
    }
    ShowDockWidget();
    QWidget::enterEvent(e);
}

void Ball::leaveEvent(QEvent *e)
{
    QPoint mousePos = mapFromGlobal(QCursor::pos());
    if ( rect().contains(mousePos) == false && mousePos.x() != rect().width()){
        HideDockWidget();
    } else {
        if (m_timer == nullptr)
        {
            m_timer = new QTimer(this);
            connect(m_timer, &QTimer::timeout, this, [this]{
                QPoint mousePos = mapFromGlobal(QCursor::pos());
                if (this->rect().contains(mousePos) == false && mousePos.x() != rect().width())
                {
                    HideDockWidget();
                }
            });
        }
        m_timer->start(500);    //鼠标离开悬浮球0.5秒之后，就触发hide操作
    }

    QWidget::leaveEvent(e);
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
    _beginPos = this->pos();
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
}//将其看做方形的？

void Ball::mouseDoubleClickEvent(QMouseEvent *)
{
    _beginPos = QPoint (QCursor().pos().x(),QCursor().pos().y());
    emit this->backFromBall();
}

void Ball::MoveWindow(const QPoint &start, const QPoint &end, unsigned int step)
{
    QPoint distance = end - start;
    QPoint stepPos;
    QPoint unitStep;
    if (end.x() == start.x()){
        if (end.y() > start.y()){
            unitStep.setY(step);
        } else {
            unitStep.setY(-1*step);
        }
    } else {
        if (end.x() > start.x()){
            unitStep.setX(step);
        } else {
            unitStep.setX(-1*step);
        }
    }

    stepPos = unitStep;
    int distanceLength = distance.manhattanLength();
    while(stepPos.manhattanLength() < distanceLength){
        move(start+stepPos);
        stepPos += unitStep;
    }
    move(end);
}

void Ball::ShowDockWidget()
{
    if (ishideable)
    {
      return;
    }
    ishideable = true;

    QScreen *screen = qApp->primaryScreen();
    int screenWidth = screen->size().width();            //屏幕宽

    if (_beginPos.x() < detectLength_2){                               //左边
        MoveWindow(_beginPos, QPoint(0,_beginPos.y()));
        _beginPos = this->pos();
    }
    else if (_beginPos.x() > screenWidth - detectLength_2){            //右边
        MoveWindow(_beginPos, QPoint(screenWidth - 90,_beginPos.y()));
        _beginPos = this->pos();
    }
    else if (_beginPos.y() < detectLength_2){                          //上面
        MoveWindow(_beginPos, QPoint(_beginPos.x(),0));
        _beginPos = this->pos();
    }
    else{
        ishideable = false;
    }
}

void Ball::HideDockWidget()
{
    if (!ishideable){   //如果这个东西不可被隐藏，就不能被隐藏
        return;
    }
    //如果这个东西可被隐藏，就按照下面的步骤触发隐藏操作
    ishideable = false;

    QScreen *screen = qApp->primaryScreen();
    int screenWidth = screen->size().width();            //屏幕宽
    int screenHeight = screen->size().height();         //屏幕高
    double screenScale = double(screenHeight)/double(screenWidth);

    if (_beginPos.x() < detectLength ){                 //左边
        MoveWindow(_beginPos, QPoint(exposeLength, _beginPos.y()));
        _beginPos = this->pos();
    } else if (_beginPos.x() > screenWidth-detectLength){   //右边
        MoveWindow(_beginPos, QPoint(screenWidth - 30, _beginPos.y()));   //单独定义右边的缩进量
        _beginPos = this->pos();
    } else if (_beginPos.y() < detectLength){               //上面
        MoveWindow(_beginPos, QPoint(_beginPos.x(), exposeLength*screenScale)); //beginPos*要乘以电脑的长宽比
        _beginPos = this->pos();
    } else {
        ishideable = true;
    }

    if (!ishideable ){          //如果隐藏成功，那么就停止计时器
        if (m_timer && m_timer->isActive()){
            m_timer->stop();
        }
    }

}

QPoint Ball::getBeginPos()
{
    return _beginPos;
}
