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
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

private:
    Ui::AppRemind *ui;
    QPoint beginPos_;
    bool pressed_ = false;

protected:
    void paintEvent(QPaintEvent *);

};

#endif // APPREMIND_H
