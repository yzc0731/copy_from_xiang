#include "about.h"
#include "ui_about.h"
#include <QIcon>
#include <QDebug>
About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    this->setWindowIcon(QIcon("about_ima.png"));
    ui->setupUi(this);
}

About::~About()
{
    delete ui;
}
