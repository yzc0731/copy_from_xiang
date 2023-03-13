#ifndef EDITDIALOG_H
#define EDITDIALOG_H

#include <QDialog>

#include "note.h"

namespace Ui {
class EditDialog;
}

class EditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditDialog(Note *parent = nullptr,QString str1 = "",QString str2="",QString str3="",QString str4="",QString str5="",QString str6="",QString str7="");
    ~EditDialog();
    QString s1,s2,s3,s4,s5,s6,s7;
    Note *note;
private slots:
    void on_pushButton_clicked();

    void on_checkBox_stateChanged(int arg1);

private:
    Ui::EditDialog *ui;
};

#endif // EDITDIALOG_H
