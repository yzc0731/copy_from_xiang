#ifndef BALL_H
#define BALL_H

#include <QDialog>
#include <QTimer>
#include <QScreen>
#include <QApplication>

namespace Ui {
class Ball;
}

class Ball : public QDialog
{
    Q_OBJECT

public:
    //Ball(QWidget *parent = nullptr);
    explicit Ball(QWidget *parent = nullptr, QString text = "Nothing!",
         QPoint posBegin = QPoint(100,100), int radius = 50, QString importance = "无");
    void paintEvent(QPaintEvent *);
    ~Ball();
    void enterEvent(QEvent *);                  //进入窗口区域
    void leaveEvent(QEvent *);                  //离开窗口区域
    void mousePressEvent(QMouseEvent *e);       //鼠标按下事件
    void mouseReleaseEvent(QMouseEvent *e);     //鼠标释放事件
    void mouseMoveEvent(QMouseEvent *e);        //鼠标移动事件
    bool isContains(QPoint p);                  //判断鼠标是否在圆形范围之内
    void mouseDoubleClickEvent(QMouseEvent *); //鼠标双击事件
    void MoveWindow(const QPoint &start, const QPoint &end, unsigned int step = 10);
    void showBall();
    void hideBall();
    QPoint getBeginPos();

public slots:
    void hideTimertimeOut();

signals:
    void backFromBall();
    void clicked();

private:
    Ui::Ball *ui;
    QString _text = "Nothing!";  //控件显示文本
    QPoint _center = QPoint(100,100);     //相对窗体的圆心位置坐标
    QPoint _globalBallPos = QPoint(100,100);        //窗体相对屏幕的起始坐标
    QPoint _mouseRelateWidgetPos = QPoint(100,100);        //鼠标相对窗体的坐标
    int _radius = 50;                   //圆形半径
    int hideStatus = 0; //0表示没有隐藏，1表示左隐藏，2表示右隐藏，3表示上隐藏
    const int wideDetectRange = qApp->primaryScreen()->size().width()/25;
    const int highDetectRange = qApp->primaryScreen()->size().height()/25;
    const int hideLength = _radius/3;
    const int returnLength = _radius;
    QString _importance = "无";
    bool _pressed = false;
};

#endif // BALL_H
