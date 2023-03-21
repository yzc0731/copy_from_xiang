#ifndef ADDNEW_H
#define ADDNEW_H

#include <QDialog>

#include "dialog.h"
#include "note.h"

namespace Ui
{
    class Addnew;
}

class Addnew : public QDialog
{
Q_OBJECT
public:
    std::vector<Note*> *note_vector1;
    explicit Addnew(std::vector<Note*> *note_vector);
    ~Addnew();
public slots:
    void on_pushButton_clicked();
private slots:
    void on_checkBox_stateChanged(int arg1);
private:
    Ui::Addnew *ui;
};

#endif // ADDNEW_H
