#ifndef NOTE_H
#define NOTE_H

#include <QDialog>

namespace Ui {
    class Note;
}

class Note : public QWidget
{
Q_OBJECT
public:
    explicit Note(QWidget *parent = nullptr);
    explicit Note(std::vector<Note*> *note_vector, int num = 0,QString str1 = "空",QString str2 = "00:00",QString str3 = "2023/01/01",QString str4 = "无",QString str5 = "");
    ~Note();
    int index;
    int finish;
    std::vector<Note*> *note_vector;
    QString Thing;
    QString Time;
    QString Date;
    QString ddl;
    QString note;
private slots:
    void on_checkBox_clicked();
private:
    Ui::Note *ui;
};

#endif // NOTE_H