#include "editdialog.h"
#include "ui_editdialog.h"

#include <QDebug>
#include "vector_.h"

EditDialog::EditDialog(Note *n1,QString str1,QString str2,QString str3,QString str4,QString str5,QString str6,QString str7) :
    s1(str1),s2(str2),s3(str3),s4(str4),s5(str5),s6(str6),s7(str7),note(n1),ui(new Ui::EditDialog)
{
    ui->setupUi(this);
//
    ui->nameLineEdit->setText(s1);
//
    QTime tm = QTime::fromString(s2,"hh:mm");
    ui->timeTimeEdit->setTime(tm);
//
    QDate da = QDate::fromString(s3,"yyyy/MM/dd");
    ui->dateDateEdit->setDate(da);
//
    ui->noteLineEdit->setText(s4);
//
    ui->impoComboBox->setCurrentText(s5);
//
    if(note->repeat_times == "#")
        {
        ui->label_2->hide();
        ui->spinBox->hide();
        ui->comboBox->hide();
        }
    else
    {
        ui->checkBox->setCheckState(Qt::Checked);
        int repeat_times = s6.toInt();
        //qDebug()<<s6<<s7;
        ui->spinBox->setValue(repeat_times);
        ui->comboBox->setCurrentText(s7);
    }
}
EditDialog::~EditDialog()
{
    delete ui;
}

void EditDialog::on_pushButton_clicked()
{
    //提取提醒事项的各项内容
    QString str[7] = {};
    str[0]=ui->nameLineEdit->text();      //内容
    str[1]=ui->timeTimeEdit->text();      //时间
    str[2]=ui->dateDateEdit->text();      //日期
    str[3]=ui->noteLineEdit->text();          //备注
    str[4]=ui->impoComboBox->currentText();   //ddl情况
    if(ui->checkBox->checkState()==Qt::Unchecked)
    {
        str[5] = "#";
        str[6] = "#";
    }
    else
    {
        str[5]=ui->spinBox->text();           //重复情况
        str[6]=ui->comboBox->currentText();   //
    }
//----------------------------------------------------------------//
    for(int i=0;i<5;i++)
        qDebug()<<str[i]<<endl;               //在Qt界面输出以上五点（类似调试输出）

    note->Thing = str[0];
    note->Time = str[1];
    note->Date = str[2];
    note->note = str[3];
    note->ddl = str[4];
    note->repeat_times = str[5];
    note->repeat_gap = str[6];
    Vector_ vector;
    vector.vector_for_file(*note->note_vector);   //?
    close();
}

void EditDialog::on_checkBox_stateChanged(int arg1)
{
    arg1 = 0;
    if(ui->checkBox->checkState()==Qt::Unchecked)
    {
        ui->label_2->hide();
        ui->spinBox->hide();
        ui->comboBox->hide();
    }
    else if(ui->checkBox->checkState()==Qt::Checked)
    {
        ui->label_2->show();
        ui->spinBox->show();
        ui->comboBox->show();
    }   //此函数用于控制是否重复
}

void EditDialog::on_pushButton_2_clicked()
{
    std::vector<Note*>::iterator itor;
    for (itor = note->note_vector->begin();itor != note->note_vector->end();itor++) {
        if(*itor == note)
        {itor = note->note_vector->erase(itor);break;}
    }
    this->on_pushButton_clicked();
}      //删除函数
