#include "history.h"
#include "ui_history.h"
#include <iostream>
history::history(QWidget *parent,std::vector<Note*> *note_vector1) :
        QDialog(parent),note_vector_history(note_vector1),
        ui(new Ui::history)
{
    //std::cout<<note_vector1<<std::endl;                   //输出vector地址
    this->setWindowOpacity(0.8);
    ui->setupUi(this);
    if(ui->scrollArea->widget()->layout()!= nullptr){       //删除原有布局
        QLayoutItem *item;
        while((item=ui->scrollArea->widget()->layout()->takeAt(0))!= nullptr){
            delete item->widget();
            delete item;
        }
        delete ui->scrollArea->widget()->layout();
    }
    QGridLayout *gridlayout=new QGridLayout();
    for(unsigned i=0; i < note_vector_history->size();i++)
    {
        Note *n=note_vector_history->at(i);
        if(n->finish == 1)
        {
            gridlayout->addWidget(note_vector_history->at(i));
            n->show();
        }
    }
    ui->scrollArea->widget()->setLayout(gridlayout);
    repaint();
}

history::~history()
{
    delete ui;
}
void history::refresh_history()
{
    this->setWindowOpacity(0.8);
    ui->setupUi(this);
    if(ui->scrollArea->widget()->layout()!= nullptr){//删除原有布局
        QLayoutItem *item;
        while((item=ui->scrollArea->widget()->layout()->takeAt(0))!= nullptr){
            delete item->widget();
            delete item;
        }
        delete ui->scrollArea->widget()->layout();
    }
    QGridLayout *gridlayout=new QGridLayout();
    for(unsigned i=0; i < note_vector_history->size();i++)
    {
        Note *n=note_vector_history->at(i);
        if(n->finish == 1)
        {
            gridlayout->addWidget(note_vector_history->at(i));
            n->show();
        }
    }
    ui->scrollArea->widget()->setLayout(gridlayout);
    repaint();
}
