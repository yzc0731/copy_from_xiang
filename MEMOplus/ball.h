#ifndef BALL_H
#define BALL_H

#include <QDialog>

namespace Ui {
class Ball;
}

class Ball : public QDialog
{
    Q_OBJECT

public:
    explicit Ball(QWidget *parent = nullptr);
    Ball(QWidget *parent = nullptr, QString text = "Nothing on list", QPoint posBegin = QPoint(100,100));

    void paintEvent(QPaintEvent *);
    ~Ball();
    void enterEvent(QEvent *);  //进入窗口区域
    void timeout();

    void mousePressEvent(QMouseEvent *e);       //鼠标按下事件
    void mouseReleaseEvent(QMouseEvent *e);     //鼠标释放事件
    void mouseMoveEvent(QMouseEvent *e);        //鼠标移动事件
    bool isContains(QPoint p);                  //判断鼠标是否在圆形范围之内
    void mouseDoubleClickEvent(QMouseEvent *); //鼠标双击事件

    QPoint getBeginPos();


signals:
    void backFromBall();
    void clicked();

private:
    Ui::Ball *ui;
    QString _text = "Nothing on list";    //控件显示文本
    QPoint _center = QPoint(50,50);       //相对窗体的圆心位置坐标
    QPoint _beginPos;      //窗体相对屏幕的起始坐标
    int _radius = 50;      //圆形半径
    bool theFirstTimer = true;

public:
    bool _pressed;
};

#endif // BALL_H
