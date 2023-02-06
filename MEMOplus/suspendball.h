#ifndef SUSPENDBALL_H
#define SUSPENDBALL_H

#include <QDialog>

namespace Ui {
class suspendBall;
}

class suspendBall : public QDialog
{
    Q_OBJECT

public:
    // explicit suspendBall(const QString text, QPoint center,int radius);

    explicit suspendBall(QWidget *parent = nullptr);    //explicit 避免歧义
    // 只定义寄生在哪里，具体数据使用默认值

    suspendBall(const QString text, QPoint center,
                 int radius,QWidget *parent = nullptr);
    ~suspendBall();
    void paintEvent(QPaintEvent *);                //--绘图事件，调用update()时触发
    void initForm();//初始化窗体

    void mousePressEvent(QMouseEvent *e);       //--鼠标按下事件
    void mouseReleaseEvent(QMouseEvent *e);     //--鼠标释放事件
    void mouseMoveEvent(QMouseEvent *e);        //--鼠标移动事件
    bool isContains(QPoint p);                  //判断鼠标是否在圆形范围之内

signals:
    void clicked();     //点击信号

private:
    Ui::suspendBall *ui;
    QString _text;    //控件显示文本
    QPoint _center;   //圆心位置坐标
    QPoint beginPos;  //圆形起始坐标
    int _radius;      //圆形半径

public:
    bool _pressed;//左键单击变色控制
};

#endif // SUSPENDBALL_H
