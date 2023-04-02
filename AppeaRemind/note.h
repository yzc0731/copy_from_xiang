#ifndef NOTE_H
#define NOTE_H

#include <QDialog>

#include "appremind.h"

namespace Ui {
    class Note;
}

class Note : public QWidget
{
Q_OBJECT
public:
    explicit Note(QWidget *parent = nullptr);
    explicit Note(std::vector<Note*> *note_vector, int num = 0,QString str1 = "空",QString str2 = "00:00",QString str3 = "2023/01/01",QString str4 = "无",QString str5 = "",QString str6 = "#",QString str7 = "#");
    ~Note();
    int index;
    int finish;
    std::vector<Note*> *note_vector;
    QString Thing;
    QString Time;
    QString Date;
    QString ddl;
    QString note;
    QString repeat_times;
    QString repeat_gap;
    int time_int;
    void paintEvent(QPaintEvent * ev);   //20230315设置Note面背景
    void emit_exchange();   //20230327
    //void opacityChange();

signals:
    void refresh();
    void delete_();  //20230327
private slots:
    void on_checkBox_clicked();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::Note *ui;
    AppRemind *am;
    bool isAm = false;
    //QTimer *timer;
    //double noteExitPacity = 1.00;
};

#endif // NOTE_H
