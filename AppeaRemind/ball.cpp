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
    _globalBallPos = this->pos();

    // 无边框
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint
                         | Qt::WindowMinMaxButtonsHint|Qt::WindowStaysOnTopHint);

    // 窗口整体透明，但窗口控件不透明
    this->setAttribute(Qt::WA_TranslucentBackground,true);
}

Ball::Ball(QWidget *parent, QString text, QPoint posBegin, int radius, QString importance):
    QDialog(parent),ui(new Ui::Ball),_text(text),
    _globalBallPos(posBegin), _radius(radius), _importance(importance)
{
    ui->setupUi(this);
    QPoint windowPos = QPoint (_globalBallPos.x()-150,_globalBallPos.y()-150);
    this->move(windowPos);
    // 无边框
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint|Qt::WindowStaysOnTopHint);
    // 窗口整体透明，但窗口控件不透明
    this->setAttribute(Qt::WA_TranslucentBackground,true);
}

void Ball::paintEvent(QPaintEvent *)
{
    QPainter p(this);//将当前窗体作为画布
    if(_importance == "非常重要")
    {
        p.setBrush(QColor(255,100,70,150));
        qDebug() << "little red";
    }
    if(_importance == "无")
    {
        p.setBrush(QColor(255,255,255,150));
        qDebug() << "white";
    }
    if(_importance == "比较重要")
    {
        p.setBrush(QColor(65,105,225,150));
        qDebug() << "blue";
    }
    if(_importance == "重要")
    {
        p.setBrush(QColor(255,255,0,150));
        qDebug() << "yellow";
    }
    if(_importance == "紧迫")
    {
        p.setBrush(QColor(255,0,0,150));      //纯红色
        qDebug() <<"red";
    }
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
        _relateWindowPos = e->pos();    //鼠标相对窗体的位置
        update();                //触发窗体重绘
    }
}

void Ball::mouseMoveEvent(QMouseEvent *e){
    if (_pressed)
    {
         //e->pos鼠标移动过程中，鼠标相对窗体的位置-刚按下鼠标时鼠标相对窗体的位置=鼠标移动的大小
         //鼠标移动的大小+窗体原来的位置=窗体移动后的位置
         this->move(e->pos() - _relateWindowPos + this->pos());
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
}//将其看做方形的？

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

void Ball::ShowDockWidget()
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
            windowPos2 = QPoint (-_center.x(),windowPos.y());
            break;
        }
        case 2:{
            windowPos2 = QPoint (screenWidth-_center.x(),windowPos.y());
            break;
        }
        case 3:{
            windowPos2 = QPoint (windowPos.x(),-_center.y());
            break;
        }
    }
    MoveWindow(windowPos, windowPos2);
    _globalBallPos = QPoint (this->pos().x()+_center.x(), this->pos().y()+_center.y());
    qDebug() << _globalBallPos.x() << "," <<_globalBallPos.y();
    hideStatus = 0;
}

void Ball::HideDockWidget()
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
        qDebug() << _globalBallPos.x() << "," <<_globalBallPos.y();
        qDebug() << this->pos().x();
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
    qDebug() << _globalBallPos.x() << "," <<_globalBallPos.y();
    qDebug() << this->pos().x();
    if (hideStatus != 0){          //如果隐藏成功，那么就停止计时器
        if (m_timer && m_timer->isActive()){
            m_timer->stop();
        }
    }
}

QPoint Ball::getBeginPos()
{
    return _globalBallPos;
}
