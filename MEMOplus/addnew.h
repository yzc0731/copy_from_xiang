#ifndef ADDNEW_H
#define ADDNEW_H

#include <QDialog>
//static QString *str_name;
namespace Ui
{
class Addnew;
}

class Addnew : public QDialog
{
    Q_OBJECT

public:
    explicit Addnew(QWidget *parent = nullptr);
    QString a[6];
    ~Addnew();

public slots:
    void on_pushButton_clicked();

private:
    Ui::Addnew *ui;
};

#endif // ADDNEW_H
