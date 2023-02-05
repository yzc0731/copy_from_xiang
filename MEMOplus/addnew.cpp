#include "addnew.h"
#include "ui_addnew.h"
#include <QDebug>
#include <QFile>
#include "dialog.h"
#include "vector_.h"
//Addnew::Addnew(QWidget *parent) :
//    QDialog(parent),
//    ui(new Ui::Addnew)
//{
//    ui->setupUi(this);
//}
Addnew::Addnew(std::vector<Note*> *note_vector) :
        ui(new Ui::Addnew)

{
    ui->setupUi(this);
    this->note_vector=note_vector;
}

Addnew::~Addnew()
{
    delete ui;
}
//以下为按钮的函数
void Addnew::on_pushButton_clicked()
{
    //void vector_for_file(std::vector<Note*> note_vector);
    //提取提醒事项的各项内容
    QString str[5];
    str[0]=ui->nameLineEdit->text();      //内容
    str[1]=ui->timeTimeEdit->text();      //时间
    str[2]=ui->dateDateEdit->text();      //日期
    str[3]=ui->LineEdit->text();          //备注
    str[4]=ui->comboBox->currentText();   //ddl情况
    for(int i=0;i<5;i++)
        qDebug()<<str[i]<<endl;               //在Qt界面输出以上五点（类似调试输出
    //以下用于写入note_vector
    Note *n1 = new Note(note_vector,0,str[0], str[1], str[2], str[4], str[3]);
    note_vector->push_back(n1);   //放到vector最后一个位置
    Vector_ vector;
    vector.vector_for_file(*note_vector);
    close();
}
