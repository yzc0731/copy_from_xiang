#include "ball.h"
#include "ui_ball.h"
#include <QDebug>
#include <QPainter>
#include <QTimer>
#include <QDateTime>
#include <QMouseEvent>
#include <QDesktopWidget>
#include <QApplication>
#include <QScreen>

Ball::Ball(QWidget *parent, QString text, QPoint posBegin, int radius, QString importance, double pacity):
    QDialog(parent),ui(new Ui::Ball),_text(text),
    _globalBallPos(posBegin), _radius(radius), _importance(importance)
{
    ui->setupUi(this);
    QPoint windowPos = QPoint (_globalBallPos.x()-150,_globalBallPos.y()-150);
    this->move(windowPos);
    if(_text == ""){
        _text = "Nothing!";
    }
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint |
                         Qt::WindowMinMaxButtonsHint|Qt::WindowStaysOnTopHint);// 无边框
    this->setAttribute(Qt::WA_TranslucentBackground,true);// 窗口整体透明，但窗口控件不透明
    this->setWindowOpacity(pacity);
}

void Ball::paintEvent(QPaintEvent *)
{
    QPainter p(this);//将当前窗体作为画布
    p.setBrush(QColor(255,255,255,150));
    if(_importance == "非常重要")
    {
        p.setBrush(QColor(255,100,70,150));
    }
    if(_importance == "比较重要")
    {
        p.setBrush(QColor(65,105,225,150));
    }
    if(_importance == "重要")
    {
        p.setBrush(QColor(255,255,0,150));
    }
    //if(_importance == "紧迫")
    //{
    //    p.setBrush(QColor(255,0,0,150));      //纯红色
    //}
    p.setPen(Qt::NoPen);//没有线条
    p.drawEllipse(_center,_radius,_radius);//画圆形
    QPen pen = QPen(Qt::black);
    p.setPen(pen);
    p.drawText(QRect(_center.x()-_radius,_center.x()-_radius,2*_radius,2*_radius),
               _text, QTextOption(Qt::AlignCenter));//添加文本
}

Ball::~Ball()
{
    delete ui;
}

void Ball::enterEvent(QEvent *)
{   //鼠标进入悬浮球，停止计时器，回到原位置,新建一个计时器，然后再等0.5秒之后才可能触发hide操作
    showBall();
}

void Ball::leaveEvent(QEvent *)
{
    QTimer::singleShot(1000, this,&Ball::hideTimertimeOut);
}

void Ball::hideTimertimeOut()
{
    QPoint mouseRelativePos = mapFromGlobal(QCursor::pos());
    if (isContains(mouseRelativePos)){
        return;
    } else {
        hideBall();
    }
}

void Ball::mousePressEvent(QMouseEvent *e){
   if(isContains(e->pos()))
    {
        _pressed = true;
        _mouseRelateWidgetPos = e->pos();    //鼠标相对窗体的位置
        update();                //触发窗体重绘
    }
}

void Ball::mouseMoveEvent(QMouseEvent *e){
    if (_pressed)
    {
         //e->pos鼠标移动过程中，鼠标相对窗体的位置-刚按下鼠标时鼠标相对窗体的位置=鼠标移动的大小
         //鼠标移动的大小+窗体原来的位置=窗体移动后的位置
         this->move(e->pos() - _mouseRelateWidgetPos + this->pos());
    }
}

void Ball::mouseReleaseEvent(QMouseEvent *e){
    _pressed = false;
    update();//触发窗体重绘
    if(isContains(e->pos()))    //当鼠标点击按钮
        emit clicked();         //发送点击信号
    _globalBallPos = QPoint (this->pos().x()+_center.x(), this->pos().y()+_center.y());
    //this->pos()获取的是当前窗口的坐标，我要长宽分别加上100，100
}

bool Ball::isContains(QPoint p){
    return (_center.x()-_radius < p.x()
            && _center.x()+_radius > p.x()
            && _center.y()-_radius < p.y()
            && _center.y()+_radius > p.y());
}

void Ball::mouseDoubleClickEvent(QMouseEvent *)
{
    _globalBallPos = QPoint (QCursor().pos().x(),QCursor().pos().y());
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
        this->move(start+stepPos);
        stepPos += unitStep;
    }
    this->move(end);
}

void Ball::showBall()
{
    QPoint windowPos = QPoint (_globalBallPos.x()-_center.x(), _globalBallPos.y()-_center.y());
    QPoint windowPos2;
    if (hideStatus == 0)//那就说明没有被隐藏过，直接跳过
    {
      return;
    }
    //如果现在是隐藏状态，那就触发恢复操作
    QScreen *screen = qApp->primaryScreen();
    int screenWidth = screen->size().width();            //屏幕宽
    switch (hideStatus) {
        case 1:{
            windowPos2 = QPoint (returnLength -_center.x(),windowPos.y());
            break;
        }
        case 2:{
            windowPos2 = QPoint (screenWidth - returnLength -_center.x(),windowPos.y());
            break;
        }
        case 3:{
            windowPos2 = QPoint (windowPos.x(),returnLength -_center.y());
            break;
        }
    }
    MoveWindow(windowPos, windowPos2);
    _globalBallPos = QPoint (this->pos().x()+_center.x(), this->pos().y()+_center.y());
    hideStatus = 0;
}

void Ball::hideBall()
{
    QPoint windowPos = QPoint (_globalBallPos.x()-_center.x(),_globalBallPos.y()-_center.y());
    QPoint windowPos2;
    if (hideStatus != 0){   //如果这个东西现在是隐藏状态，就不能被隐藏
        return;
    }
    //如果hideStatus == 0，那么这个东西可被隐藏，就按照下面的步骤触发隐藏操作    
    QScreen *screen = qApp->primaryScreen();
    int screenWidth = screen->size().width();            //屏幕宽

    if (_globalBallPos.x() < wideDetectRange ){                 //左边
        windowPos2 = QPoint(- hideLength - _center.x(), windowPos.y());
        //MoveWindow(windowPos, windowPos2);
        //这一步让this->pos()变成了windowPos2
        hideStatus = 1;//左
    } else if (_globalBallPos.x() > screenWidth - wideDetectRange){   //右边
        windowPos2 = QPoint(screenWidth + hideLength -_center.x(), windowPos.y());
        //MoveWindow(windowPos, windowPos2);
        hideStatus = 2;//右
    } else if (_globalBallPos.y() < highDetectRange){               //上面
        windowPos2 = QPoint(windowPos.x(), -hideLength -_center.y());
        //MoveWindow(windowPos, windowPos2);
        hideStatus = 3;//上
    } else {
        hideStatus = 0;
        return;
    }
    MoveWindow(windowPos, windowPos2);
    _globalBallPos = QPoint (this->pos().x()+_center.x(), this->pos().y()+_center.y());
}

QPoint Ball::getBeginPos()
{
    return _globalBallPos;
}
