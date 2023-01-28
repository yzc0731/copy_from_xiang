#include "addnew.h"
#include "ui_addnew.h"
#include <QDebug>
#include <QFile>
Addnew::Addnew(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Addnew)
{
    ui->setupUi(this);
}

Addnew::~Addnew()
{
    delete ui;
}
//以下为按钮的函数
int count = 1;
void Addnew::on_pushButton_clicked()
{

    QString str[5];   //提取m提醒事项名
    str[0]=ui->nameLineEdit->text();
    str[1]=ui->timeTimeEdit->text();
    str[2]=ui->dateDateEdit->text();
    str[3]=ui->LineEdit->text();
    str[4]=ui->comboBox->currentText();
    for(int i=0;i<5;i++)
    qDebug()<<str[i]<<endl;
    QFile file;
    file.setFileName("D:/log.txt");
    if(file.open(QIODevice::Append| QIODevice::Text))
    {
        QTextStream stream(&file);
        stream<<count<<" "<<"note"<<count<<" ";
        for(int i=0;i<5;i++)
        {
             stream<<str[i]<<" ";
        }
        stream<<"#\n";
        count++;
        file.close();
    }
    close();
}
