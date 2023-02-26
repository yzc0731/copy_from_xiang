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

void Ball::enterEvent(QEvent *e){
    // emit this->backFromBall();
//    QTimer *timer = new QTimer(this);
//    timer->start(10000);
    //    connect(timer,&QTimer::timeout,this,&Ball::timeout);

    if (m_timer && m_timer->isActive())
    {
        m_timer->stop();
    }
    ShowDockWidget();
    QWidget::enterEvent(e);
}

void Ball::leaveEvent(QEvent *e)
{
    QPoint mousePos = mapFromGlobal(QCursor::pos());
    if (rect().contains(mousePos) == false
      && mousePos.x() != rect().width())
    {
        HideDockWidget();
    }
    else
    {
        if (m_timer == nullptr)
        {
            m_timer = new QTimer(this);
            connect(m_timer, &QTimer::timeout, this, [this]{
                QPoint mousePos = mapFromGlobal(QCursor::pos());
                if (this->rect().contains(mousePos) == false
                 && mousePos.x() != rect().width())
                {
                 HideDockWidget();
                }
            });
        }
        m_timer->start(500);
    }

    QWidget::leaveEvent(e);
}

// QCursor::pos() 的结果是鼠标相对于桌面的绝对位置
// mousePressEvent的参数event的位置，event->pos() 是鼠标相对于应用程序的位置，
// event->globalPos() 相对于桌面原点的位置，绝对位置

void Ball::timeOut(){
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

    _beginPos = QPoint (QCursor().pos().x(),QCursor().pos().y());

//    if(_beginPos.x() < 100){
//        qDebug()<<"hello";
//        MoveWindow(_beginPos, QPoint(-50,_beginPos.y()));
//    }
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

void Ball::mouseDoubleClickEvent(QMouseEvent *)
{
    _beginPos = QPoint (QCursor().pos().x()-100,QCursor().pos().y()-100);
    // theFirstTimer = false;
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
    recoverposition = start;
}

void Ball::ShowDockWidget()
{
    if (isinvisible)
    {
      return;
    }

    isinvisible = true;

    QScreen *screen = qApp->primaryScreen();
    int screenWidth = screen->size().width();            //屏幕宽

    if (_beginPos.x() < 150)
    {
        MoveWindow(_beginPos, recoverposition);
        _beginPos = this->pos();
        qDebug()<<QString("(%1,%2)").arg(_beginPos.x()).arg(_beginPos.y());
    }
    else if (_beginPos.x() > screenWidth - 150)
    {
        MoveWindow(_beginPos, recoverposition);
        _beginPos = this->pos();
        qDebug()<<QString("(%1,%2)").arg(_beginPos.x()).arg(_beginPos.y());
    }
    else if (_beginPos.y() < 150)
    {
        MoveWindow(_beginPos, recoverposition);
        _beginPos = this->pos();
    }
    else
    {
        isinvisible = false;
    }
}

void Ball::HideDockWidget()
{
    if (!isinvisible){
        return;
    } else {
        isinvisible = false;

        QScreen *screen = qApp->primaryScreen();
        int screenWidth = screen->size().width();            //屏幕宽

        if (_beginPos.x() < detectLength ){
            qDebug()<<"Hide";
            MoveWindow(_beginPos, QPoint(exposeLength, _beginPos.y()));
            _beginPos = this->pos();
            qDebug()<<QString("(%1,%2)").arg(_beginPos.x()).arg(_beginPos.y());

        } else if (_beginPos.x() > screenWidth-detectLength){
            qDebug()<<"Hide";
            MoveWindow(_beginPos, QPoint(screenWidth-30, _beginPos.y()));
            _beginPos = this->pos();
            qDebug()<<QString("(%1,%2)").arg(_beginPos.x()).arg(_beginPos.y());

        } else if (_beginPos.y() < detectLength){
            MoveWindow(_beginPos, QPoint(_beginPos.x(), exposeLength));
            _beginPos = this->pos();

        } else {
            isinvisible = true;
        }
        if (!isinvisible){
            if (m_timer && m_timer->isActive()){
                m_timer->stop();
            }
        }
    }
}

QPoint Ball::getBeginPos(){
    return _beginPos;
}


