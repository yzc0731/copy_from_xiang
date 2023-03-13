#ifndef APPREMIND_H
#define APPREMIND_H

#include <QDialog>

namespace Ui {
class AppRemind;
}

class AppRemind : public QDialog
{
    Q_OBJECT

public:
    explicit AppRemind(QString Thing = "", QString Date = "", QString Time = "");
    ~AppRemind();
    void mousePressEvent(QMouseEvent *e);       //鼠标按下事件
    void mouseMoveEvent(QMouseEvent *e);        //鼠标移动事件
    void mouseReleaseEvent(QMouseEvent *e);     //鼠标释放事件

private:
    Ui::AppRemind *ui;
    QPoint beginPos_;
    bool pressed_ = false;

protected:
    void paintEvent(QPaintEvent *);

};

#endif // APPREMIND_H
