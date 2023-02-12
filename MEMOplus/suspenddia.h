#ifndef SUSPENDDIA_H
#define SUSPENDDIA_H

#include <QDialog>
#include "note.h"
#include <QLabel>

namespace Ui {
class SuspendDia;
}

class SuspendDia : public QDialog
{
    Q_OBJECT

public:
    std::vector<Note*> note_vector;
    explicit SuspendDia(QWidget *parent = nullptr);
    ~SuspendDia();
    void onRefresh();
    // void leaveEvent(QEvent *);  //离开窗口区域
    void mouseDoubleClickEvent(QMouseEvent *); //鼠标双击事件

    void mousePressEvent(QMouseEvent *);       //鼠标按下事件
    void mouseReleaseEvent(QMouseEvent *);     //鼠标释放事件
    void mouseMoveEvent(QMouseEvent *);        //鼠标移动事件

signals:
    void back();

private slots:
    void on_exitBtn_clicked();

    // void on_horizontalSlider_sliderMoved(int position);

    void on_settingBtn_clicked();

private:
    Ui::SuspendDia *ui;
    double _pacity = 1.0;
    bool hasBall = false;
    bool pressed = false;
    QString text;

public:
    QPoint _beginPos = QPoint(100,100);
};

#endif // SUSPENDDIA_H
