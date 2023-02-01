#ifndef ADDNEW_H
#define ADDNEW_H
#include "note.h"
#include <QDialog>
#include "dialog.h"
//static QString *str_name;
namespace Ui
{
    class Addnew;
}

class Addnew : public QDialog
{
Q_OBJECT

public:
    std::vector<Note*> *note_vector;
    explicit Addnew(std::vector<Note*> *note_vector);
    //Addnew(QWidget *parent = nullptr);
    QString a[6];
    ~Addnew();

public slots:
    void on_pushButton_clicked();

private:
    Ui::Addnew *ui;
};

#endif // ADDNEW_H