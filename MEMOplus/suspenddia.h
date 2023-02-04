#ifndef SUSPENDDIA_H
#define SUSPENDDIA_H

#include <QDialog>

namespace Ui {
class SuspendDia;
}

class SuspendDia : public QDialog
{
    Q_OBJECT

public:
    explicit SuspendDia(QWidget *parent = nullptr);
    ~SuspendDia();

signals:
    //创建一个信号
    void back();

private slots:
    void on_pacityBox_valueChanged(int arg1);

private:
    Ui::SuspendDia *ui;
    double pacity = 1;
};

#endif // SUSPENDDIA_H
