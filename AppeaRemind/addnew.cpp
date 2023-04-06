#include "addnew.h"
#include "ui_addnew.h"
#include <QDebug>
#include <QFile>
#include <QDate>
#include <QTime>
#include "dialog.h"
#include "vector_.h"

Addnew::Addnew(std::vector<Note*> *note_vector) :
        ui(new Ui::Addnew)

{
    QPalette pa;
    pa.setColor(QPalette::Background,QColor(255,255,200,180));
    this->setAutoFillBackground(true);      //背景
    this->setPalette(pa);
    //

    ui->setupUi(this);
    this->note_vector1 = note_vector;

    ui->label_4->hide();
    ui->spinBox->hide();
    ui->comboBox_2->hide();

    // belows writen by shuc22 on 2023/2/7 for achieving adding 10min for a note
    QDate date;
    date = QDate::currentDate();
    QString datestr = date.toString("yyyy/MM/dd");
    QStringList list0 = datestr.split("/");
    //
    QTime time;
    time = QTime::currentTime();
    QString timestr = time.toString("hh:mm");
    QStringList list1 = timestr.split(":");
    int min = list1[1].toInt();

    if(min < 50)   //记得改回50
    {
        min = min + 10;
        QString min_ = QString::number(min,10);
        QString timestr_new = list1[0] +":"+ min_;
        time = QTime::fromString(timestr_new,"hh:mm");
        //qDebug()<<time;
        ui->dateDateEdit->setDate(date);
        ui->timeTimeEdit->setTime(time);
    }
    else   //要进一小时
    {
        int hou = list1[0].toInt();
        if(hou <= 22)
        {
            min = min - 50;
            hou = hou + 1;
            QString min_ = QString::number(min,10);
            QString hou_ = QString::number(hou,10);
            min_=min_.asprintf("%02d",min);
            hou_=hou_.asprintf("%02d",hou);              //为了补0 的无奈之举
            QString timestr_new = hou_+":"+min_;
            //qDebug()<<timestr_new;
            time = QTime::fromString(timestr_new,"hh:mm");
            //qDebug()<<time;
            ui->dateDateEdit->setDate(date);
            ui->timeTimeEdit->setTime(time);
        }
        else  //要进一天
        {
            int yea = list0[0].toInt();
            int mon = list0[1].toInt();
            int day = list0[2].toInt();
            if(day <= 27)                         //不满月
            {
                day = day + 1 ;
                min = min +10 -60 ;
                hou = hou+ 1 -24;
                //
                QString min_ = QString::number(min,10);
                QString hou_ = QString::number(hou,10);
                min_=min_.asprintf("%02d",min);
                hou_=hou_.asprintf("%02d",hou);              //为了补0 的无奈之举
                QString timestr_new = hou_+":"+min_;
                time = QTime::fromString(timestr_new,"hh:mm");
                //
                QString day_ = QString::number(day,10);
                QString datestr_new = list0[0] +"/"+ list0[1] +"/"+ day_;
                date = QDate::fromString(datestr_new,"yyyy/MM/dd");
                ui->dateDateEdit->setDate(date);
                ui->timeTimeEdit->setTime(time);
            }
            else if(mon == 1 || mon ==3 || mon == 5|| mon == 7 || mon == 8 || mon ==10 || mon == 12 )   //大月
            {
                if(day<=30)   //大月不满月
                {
                    day = day + 1 ;
                    min = min - 50 ;
                    hou = hou+ 1 -24;
                    //
                    QString min_ = QString::number(min,10);
                    QString hou_ = QString::number(hou,10);
                    min_=min_.asprintf("%02d",min);
                    hou_=hou_.asprintf("%02d",hou);              //为了补0 的无奈之举
                    QString timestr_new = hou_+":"+min_;
                    time = QTime::fromString(timestr_new,"hh:mm");
                    //
                    QString day_ = QString::number(day,10);
                    day_ =day_.asprintf("%02d",day);
                    QString datestr_new = list0[0] +"/"+ list0[1] +"/"+ day_;
                    date = QDate::fromString(datestr_new,"yyyy/MM/dd");
                    ui->dateDateEdit->setDate(date);
                    ui->timeTimeEdit->setTime(time);
                 }
                 else    //day == 31，满月
                 {
                    if(mon!= 12)   //不满年
                    {
                    mon = mon+1;
                    day = day + 1 -31;
                    min = min +10 -60 ;
                    hou = hou+ 1 -24;
                    //
                    QString min_ = QString::number(min,10);
                    QString hou_ = QString::number(hou,10);
                    min_=min_.asprintf("%02d",min);
                    hou_=hou_.asprintf("%02d",hou);              //为了补0 的无奈之举
                    QString timestr_new = hou_+":"+min_;
                    time = QTime::fromString(timestr_new,"hh:mm");
                    //
                    QString mon_ = QString::number(mon,10);
                    QString day_ = QString::number(day,10);
                    mon_ =mon_.asprintf("%02d",mon);
                    day_ =day_.asprintf("%02d",day);
                    QString datestr_new = list0[0] +"/"+ mon_ +"/"+ day_;
                    date = QDate::fromString(datestr_new,"yyyy/MM/dd");
                    ui->dateDateEdit->setDate(date);
                    ui->timeTimeEdit->setTime(time);
                    }
                    else //mon==12
                    {
                        yea = yea + 1;
                        mon = mon+1 -12;
                        day = day + 1 -31;
                        min = min +10 -60 ;
                        hou = hou+ 1 -24;
                        //
                        QString min_ = QString::number(min,10);
                        QString hou_ = QString::number(hou,10);
                        min_=min_.asprintf("%02d",min);
                        hou_=hou_.asprintf("%02d",hou);
                        QString timestr_new = hou_+":"+min_;
                        time = QTime::fromString(timestr_new,"hh:mm");
                        //
                        QString yea_ = QString::number(yea,10);
                        QString mon_ = QString::number(mon,10);
                        QString day_ = QString::number(day,10);
                        mon_ =mon_.asprintf("%02d",mon);
                        day_ =day_.asprintf("%02d",day);   //这里没有讨论年的补0问题，因为我觉得用不到9999年
                        QString datestr_new = yea_ +"/"+ mon_ +"/"+ day_;
                        date = QDate::fromString(datestr_new,"yyyy/MM/dd");
                        ui->dateDateEdit->setDate(date);
                        ui->timeTimeEdit->setTime(time);
                    }
                 }
            }
            else if(mon == 4 || mon ==6 || mon == 9|| mon == 11)
            {
                if(day<=29)    //不满月
                {
                    day = day + 1 ;
                    min = min +10 -60 ;
                    hou = hou+ 1 -24;
                    //
                    QString min_ = QString::number(min,10);
                    QString hou_ = QString::number(hou,10);
                    min_=min_.asprintf("%02d",min);
                    hou_=hou_.asprintf("%02d",hou);
                    QString timestr_new = hou_+":"+min_;
                    time = QTime::fromString(timestr_new,"hh:mm");
                    //
                    QString day_ = QString::number(day,10);
                    day_ =day_.asprintf("%02d",day);
                    QString datestr_new = list0[0] +"/"+ list0[1] +"/"+ day_;
                    date = QDate::fromString(datestr_new,"yyyy/MM/dd");
                    ui->dateDateEdit->setDate(date);
                    ui->timeTimeEdit->setTime(time);
                 }
                 else    //day == 30
                 {
                    mon = mon+1;
                    day = day + 1 -30;
                    min = min +10 -60 ;
                    hou = hou+ 1 -24;
                    //
                    QString min_ = QString::number(min,10);
                    QString hou_ = QString::number(hou,10);
                    min_=min_.asprintf("%02d",min);
                    hou_=hou_.asprintf("%02d",hou);
                    QString timestr_new = hou_+":"+min_;
                    time = QTime::fromString(timestr_new,"hh:mm");
                    //
                    QString mon_ = QString::number(mon,10);
                    QString day_ = QString::number(day,10);
                    mon_=mon_.asprintf("%02d",mon);
                    day_=day_.asprintf("%02d",day);
                    QString datestr_new = list0[0] +"/"+ mon_ +"/"+ day_;
                    date = QDate::fromString(datestr_new,"yyyy/MM/dd");
                    ui->dateDateEdit->setDate(date);
                    ui->timeTimeEdit->setTime(time);
                 }
            }
            else if (((yea%4 ==0)&&((yea%100)!=0))||((yea%16==0)&&(yea%100==0)))   //mon == 2 ,day ==29
            {
                if(day<=28)
                {
                    day = day + 1 ;
                    min = min +10 -60 ;
                    hou = hou+ 1 -24;
                    //
                    QString min_ = QString::number(min,10);
                    QString hou_ = QString::number(hou,10);
                    min_=min_.asprintf("%02d",min);
                    hou_=hou_.asprintf("%02d",hou);
                    QString timestr_new = hou_+":"+min_;
                    time = QTime::fromString(timestr_new,"hh:mm");
                    //
                    QString day_ = QString::number(day,10);
                    QString datestr_new = list0[0] +"/"+ list0[1] +"/"+ day_;
                    date = QDate::fromString(datestr_new,"yyyy/MM/dd");
                    day_=day_.asprintf("%02d",day);
                    ui->dateDateEdit->setDate(date);
                    ui->timeTimeEdit->setTime(time);
                 }
                 else    //day == 29
                 {
                    mon = mon+1;
                    day = day + 1 -29;
                    min = min +10 -60 ;
                    hou = hou+ 1 -24;
                    //
                    QString min_ = QString::number(min,10);
                    QString hou_ = QString::number(hou,10);
                    QString timestr_new = hou_+":"+min_;
                    min_=min_.asprintf("%02d",min);
                    hou_=hou_.asprintf("%02d",hou);
                    time = QTime::fromString(timestr_new,"hh:mm");
                    //
                    QString mon_ = QString::number(mon,10);
                    QString day_ = QString::number(day,10);
                    QString datestr_new = list0[0] +"/"+ mon_ +"/"+ day_;
                    mon_=mon_.asprintf("%02d",mon);
                    day_=day_.asprintf("%02d",day);
                    date = QDate::fromString(datestr_new,"yyyy/MM/dd");
                    ui->dateDateEdit->setDate(date);
                    ui->timeTimeEdit->setTime(time);
                 }
            }
            else //(mon == 2 && day == 28)
            {
                mon = mon+1;
                day = day + 1 -28;
                min = min +10 -60 ;
                hou = hou+ 1 -24;
                //
                QString min_ = QString::number(min,10);
                QString hou_ = QString::number(hou,10);
                min_=min_.asprintf("%02d",min);
                hou_=hou_.asprintf("%02d",hou);
                QString timestr_new = hou_+":"+min_;
                time = QTime::fromString(timestr_new,"hh:mm");
                //
                QString mon_ = QString::number(mon,10);
                QString day_ = QString::number(day,10);
                mon_=mon_.asprintf("%02d",mon);
                day_=day_.asprintf("%02d",day);
                QString datestr_new = list0[0] +"/"+ mon_ +"/"+ day_;
                date = QDate::fromString(datestr_new,"yyyy/MM/dd");
                ui->dateDateEdit->setDate(date);
                ui->timeTimeEdit->setTime(time);
            }
        }
    }
}

Addnew::~Addnew()
{
    delete ui;
}
//以下为按钮的函数
void Addnew::on_pushButton_clicked()
{

    //提取提醒事项的各项内容
    QString str[7] = {};
    str[0]=ui->nameLineEdit->text();      //内容
    str[1]=ui->timeTimeEdit->text();      //时间
    str[2]=ui->dateDateEdit->text();      //日期
    str[3]=ui->LineEdit->text();          //备注
    str[4]=ui->comboBox->currentText();   //ddl情况
    //重复情况
    if(ui->checkBox->checkState()==Qt::Unchecked)
    {str[5] = str[6] = "#";}

    else if(ui->checkBox->checkState() == Qt::Checked)
    {str[5] = ui->spinBox->text();
    str[6] = ui->comboBox_2->currentText();}

//    for(int i=0;i<7;i++)
//        qDebug()<<str[i]<<endl;           //在Qt界面输出以上五点（类似调试输出）
    //以下用于写入note_vector
    Note *n1 = nullptr;
    n1 = new Note(note_vector1,0,str[0], str[1], str[2], str[4], str[3],str[5],str[6]);
    note_vector1->push_back(n1);          //放到vector最后一个位置
    Vector_ vector;
    vector.vector_for_file(*note_vector1);
    //
    close();
}

void Addnew::on_checkBox_stateChanged(int)
{
    if(ui->checkBox->checkState()==Qt::Unchecked)
    {
        ui->label_4->hide();
        ui->spinBox->hide();
        ui->comboBox_2->hide();
    }
    else if(ui->checkBox->checkState()==Qt::Checked)
    {
        ui->label_4->show();
        ui->spinBox->show();
        ui->comboBox_2->show();
    }   //此函数用于控制是否重复
}
