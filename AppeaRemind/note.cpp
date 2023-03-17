#include "note.h"
#include "ui_note.h"

#include <windows.h>
#include <iostream>
#include <QFile>
#include <QTextStream>
#include <QDate>
#include <QDebug>

#include "appremind.h"
#include "vector_.h"
#include "editdialog.h"
#include "dialog.h"

Note::Note(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::Note)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
}

Note::Note(std::vector<Note*> *note_vector,int num,QString str1,QString str2,QString str3,QString str4,QString str5,QString str6,QString str7) :
        finish(num),Thing(str1),Time(str2),Date(str3),ddl(str4),note(str5),repeat_times(str6),repeat_gap(str7),ui(new Ui::Note)
{
    this->am = new AppRemind(this->Thing, this->Date, this->Time);
    index=note_vector->size();
    ui->setupUi(this);
    this->note_vector = note_vector;
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    ui->label->setText(Thing);
    ui->label_2->setText(Time);
    ui->label_3->setText(Date);
    ui->label_4->setText(ddl);
    ui->label_5->setText(note);
    ui->label_7->setText(repeat_times);
    ui->label68->setText(repeat_gap);
    QPalette pa;
    if(ddl == "非常重要")
    {
        pa.setColor(QPalette::Background,QColor(255,0,0));
    }
    if(ddl == "无")
    {
        pa.setColor(QPalette::Background,QColor(255,255,255));
    }
    if(ddl == "比较重要")
    {
        pa.setColor(QPalette::Background,QColor(0,255,255));    //蓝色....
    }
    ui->label_4->setAutoFillBackground(true);
    ui->label_4->setPalette(pa);
}

Note::~Note()
{
    delete ui;
}

void Note::on_checkBox_clicked()
{
    Sleep(1000);
    if(note_vector->at(index)->repeat_times == "#"){
        finish=1;
        note_vector->at(index)->finish=1;
        note_vector->at(index)->ui->checkBox->setChecked(true);//保持选中
        Vector_ vector;
        vector.vector_for_file(*note_vector);
        this->close();
    }
    if(note_vector->at(index)->repeat_times != "#"){
        QString str_date = note_vector->at(index)->Date;
        QStringList list = str_date.split("/");
        int year,month,day;
        year = list[0].toInt();
        month = list[1].toInt();
        day = list[2].toInt();
        //定义完毕
        int times = note_vector->at(index)->repeat_times.toInt() - 1;//减少一次重复
        int day_add;

        qDebug()<<note_vector->at(index)->repeat_gap;
        if(note_vector->at(index)->repeat_gap =="每周")  day_add = 7;
        else if(note_vector->at(index)->repeat_gap == "每两周") day_add = 14;
        else if(note_vector->at(index)->repeat_gap == "每天") day_add = 1;
        else day_add = 2;
//---------------------------------------------
        if(day <= 28-day_add)                         //不满月
            {
                day=day+day_add;
                QString day_ = QString::number(day,10);
                QString datestr_new = list[0] +"/"+ list[1] +"/"+ day_;
                note_vector->at(index)->Date = datestr_new;
            }
         else if(month == 1 || month ==3 || month == 5|| month == 7 || month == 8 || month ==10 || month == 12 )
            {
                if(day<=31-day_add)
                {
                    day=day+day_add;
                    QString day_ = QString::number(day,10);
                    QString datestr_new = list[0] +"/"+ list[1] +"/"+ day_;
                    note_vector->at(index)->Date = datestr_new;
                    qDebug()<<"2";
                }
          else
                {
                if(month != 12)   //不满年
                    {
                        month = month +1;
                        day = day + day_add -31;
                        QString mon_ = QString::number(month,10);
                        QString day_ = QString::number(day,10);
                        mon_ =mon_.asprintf("%02d",month);
                        day_ =day_.asprintf("%02d",day);
                        QString datestr_new = list[0] +"/"+ mon_ +"/"+ day_;
                        note_vector->at(index)->Date = datestr_new;
                        qDebug()<<"3";
                    }
                else    //mon==12，满一年。
                    {
                        year = year + 1;
                        month = month +7 -12;
                        day = day + day_add -31;
                        QString yea_ = QString::number(year,10);
                        QString mon_ = QString::number(month,10);
                        QString day_ = QString::number(day,10);
                        mon_ =mon_.asprintf("%02d",month);
                        day_ =day_.asprintf("%02d",day);   //这里没有讨论年的补0问题，因为我觉得用不到9999年
                        QString datestr_new = yea_ +"/"+ mon_ +"/"+ day_;
                        note_vector->at(index)->Date = datestr_new;
                    }
                }
            }
            else if(month == 4 || month ==6 || month == 9|| month == 11)
            {
                if(day<=30 - day_add)    //不满月
                {
                    day = day + day_add ;
                    QString day_ = QString::number(day,10);
                    day_ =day_.asprintf("%02d",day);
                    QString datestr_new = list[0] +"/"+ list[1] +"/"+ day_;
                    note_vector->at(index)->Date = datestr_new;
                 }
                 else    //满月
                 {
                    month = month+1;
                    day = day + day_add -30;
                    QString mon_ = QString::number(month,10);
                    QString day_ = QString::number(day,10);
                    mon_=mon_.asprintf("%02d",month);
                    day_=day_.asprintf("%02d",day);
                    QString datestr_new = list[0] +"/"+ mon_ +"/"+ day_;
                    note_vector->at(index)->Date = datestr_new;
                 }
            }
            else if (((year%4 ==0)&&((year%100)!=0))||((year%16==0)&&(year%100==0)))   //mon == 2 ,day ==29
            {
                if(day<=29 - day_add)
                {
                    day = day + day_add ;
                    QString day_ = QString::number(day,10);
                    QString datestr_new = list[0] +"/"+ list[1] +"/"+ day_;
                    note_vector->at(index)->Date = datestr_new;
                 }
                 else       //满月
                 {
                    month = month+1;
                    day = day + day_add -29;
                    QString mon_ = QString::number(month,10);
                    QString day_ = QString::number(day,10);
                    mon_=mon_.asprintf("%02d",month);
                    day_=day_.asprintf("%02d",day);
                    QString datestr_new = list[0] +"/"+ mon_ +"/"+ day_;
                    note_vector->at(index)->Date = datestr_new;
                 }
            }
            else //(mon == 2 && day == 28)
            {
                if(day<=28 - day_add)
                {
                    day = day + day_add ;
                    QString day_ = QString::number(day,10);
                    QString datestr_new = list[0] +"/"+ list[1] +"/"+ day_;
                    note_vector->at(index)->Date = datestr_new;
                 }
                 else       //满月
                 {
                    month = month+1;
                    day = day + day_add -28;
                    QString mon_ = QString::number(month,10);
                    QString day_ = QString::number(day,10);
                    mon_=mon_.asprintf("%02d",month);
                    day_=day_.asprintf("%02d",day);
                    QString datestr_new = list[0] +"/"+ mon_ +"/"+ day_;
                    note_vector->at(index)->Date = datestr_new;
                 }
            }
            if(times > 0)
            {
                QString times_ = QString::number(times,10);
                note_vector->at(index)->repeat_times = times_;
            }
            else if(times <= 0)
            {
                note_vector->at(index)->repeat_times = "#";
                note_vector->at(index)->repeat_gap = "#";
            }
        }
        if(isAm){
            this->am->close();
            ui->pushButton_2->setText("+");
        }
        Vector_ vector;
        vector.vector_for_file(*note_vector);
        //先覆写后台log.txt文件，再刷新输出到主界面上
        emit refresh();
}
//
void Note::on_pushButton_clicked()
{
    EditDialog *edi = new EditDialog(this,this->Thing,this->Time,this->Date,this->note,this->ddl,this->repeat_times,this->repeat_gap);  //通过新窗口的构造函数实现对this的内容的更改
    edi->exec();
    emit refresh();
    //Vector_ vector;
    //vector.vector_for_file(*note_vector);
    //目前需要重启才能生效
}


void Note::on_pushButton_2_clicked()
{
    if (!finish){
        if (!isAm){
            this->am->show();
            isAm = true;
            ui->pushButton_2->setText("-");
        } else {
            this->am->close();
            isAm = false;
            ui->pushButton_2->setText("+");
        }
    }
}
