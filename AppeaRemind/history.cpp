#include "history.h"
#include "ui_history.h"

#include <iostream>

history::history(QWidget *parent,std::vector<Note*> *note_vector1) :
        QDialog(parent),
        ui(new Ui::history)
{
    std::cout<<note_vector1<<std::endl;
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
    for(unsigned i=0; i < note_vector1->size();i++)
    {
        Note *n=note_vector1->at(i);
        if(n->finish == 1)
        {
            gridlayout->addWidget(note_vector1->at(i));
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
