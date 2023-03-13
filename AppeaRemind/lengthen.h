#ifndef LENGTHEN_H
#define LENGTHEN_H

#include "ui_lengthen.h"

#include <QDialog>
#include <QTimer>

#include "datetime.h"

namespace Ui {
class lengthen;
}

class lengthen : public QDialog
{
    Q_OBJECT

public:
    explicit lengthen(QWidget *parent = nullptr);
    ~lengthen();

private slots:
    void on_pushButton_clicked();

    void myslot();


private:
    Ui::lengthen *ui;
    QTimer *timer;
};

#endif // LENGTHEN_H
