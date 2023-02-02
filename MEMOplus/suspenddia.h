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

private slots:
    void on_exitBtn_clicked();

signals:
    //创建一个信号
    void back();

private:
    Ui::SuspendDia *ui;
};

#endif // SUSPENDDIA_H
