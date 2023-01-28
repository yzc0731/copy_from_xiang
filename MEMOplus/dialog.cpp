#include "dialog.h"
#include "ui_dialog.h"
#include "addnew.h"
#include "about.h"
#include "history.h"
#include "windows.h"
#include <QDebug>
#include "note.h"
#include <QFile>
//主界面窗口设置
Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}  //析构函数


void Dialog::on_pushButton_clicked()
{
    Addnew *add= new Addnew();
    add->show();
    //qDebug()<<str_name[0];
}   //打开新增面板

void Dialog::on_pushButton_2_clicked()
{
    About *about= new About;
    about->show();

}  //打开关于面板

void Dialog::on_pushButton_3_toggled(bool checked)
{

    if(checked)
    {
         ui->pushButton_3->setText(tr("显示"));
         ui->frame->hide();
    }
    else
    {
        ui->pushButton_3->setText(tr("最小化"));
        ui->frame->show();
    }
}
void Dialog::on_pushButton_4_clicked()
{
    history *a =new history;
    a->show();
}
void Dialog::AddNew(QString name,int num)
{

    QFile file;
    QString str_read[7];
    QString strline;
    file.setFileName("D:/log.txt");
    if(file.open(QIODevice::ReadOnly))
    {
    while(! file.atEnd())
    {
            strline = file.readLine();
        QStringList list = strline.split(" ");
        for(int i=0;i<7;i++)
        {
            str_read[i]= list[i];
        }
    }
    name=str_read[1];//num=str_read[0];
    Note n1(ui->frame_2,str_read[2],str_read[3],str_read[4],str_read[5],str_read[6]);
    n1.move(2,2+60*(num-1));  //提醒事项的移动
    n1.exec();
    }     //仍然存在问题
}
