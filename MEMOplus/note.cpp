#include "note.h"
#include "ui_note.h"
#include <windows.h>
#include <QFile>
Note::Note(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Note)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
}

Note::Note(QWidget *parent,QString thing,QString time,QString Date,QString ddl,QString note) :
    QDialog(parent),
    ui(new Ui::Note)
{

    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    ui->label->setText(thing);
    ui->label_2->setText(time);
    ui->label_3->setText(Date);
    ui->label_4->setText(ddl);
    ui->label_5->setText(note);
}
Note::~Note()
{
    delete ui;
}
void Note::on_checkBox_clicked()
{
    Sleep(1000);
    close();
}
