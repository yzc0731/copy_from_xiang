#include "settingdia.h"
#include "ui_settingdia.h"

#include <QScrollArea>
#include <QDebug>
SettingDia::SettingDia(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingDia)
{
    ui->setupUi(this);
    // this->setWindowTitle(tr("设置"));
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint
                         | Qt::WindowMinMaxButtonsHint|Qt::WindowStaysOnTopHint);
    QScrollArea *scroll=new QScrollArea(this);
    scroll->setWidget(this);
}

SettingDia::SettingDia(QWidget *parent, double pacity, int radius, bool autoOpen):
    QDialog(parent),ui(new Ui::SettingDia),_pacity(pacity), _radius(radius),_autoOpen(autoOpen)
{
    ui->setupUi(this);
    // this->setWindowTitle(tr("设置"));
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint
                         | Qt::WindowMinMaxButtonsHint|Qt::WindowStaysOnTopHint);
    this->setWindowOpacity(pacity);
    int value = _pacity*100 - 1;
    ui->horizontalSlider->setValue(value);
    ui->horizontalSlider_2->setValue(_radius);
    if(_autoOpen){
        ui->checkBox->setChecked(true);
    } else {
        ui->checkBox->setChecked(false);
    }
}

SettingDia::~SettingDia()
{
    delete ui;
}

double SettingDia::getPacity()
{
    return _pacity;
}

int SettingDia::getRadius()
{
    return _radius;
}

bool SettingDia::isAutoOpen()
{
    return _autoOpen;
}

void SettingDia::on_backBtn_clicked()
{
    emit this->backFromSet();
    this->close();
}

void SettingDia::on_horizontalSlider_valueChanged(int value)
{
    _pacity = double(value+1)/100.0;
    setWindowOpacity(_pacity);
    emit this->pacityChanged();
}

void SettingDia::on_horizontalSlider_2_valueChanged(int value)
{
    _radius = value;
}

void SettingDia::on_checkBox_stateChanged(int arg1)
{
    if(_autoOpen){
        _autoOpen = 0;
        qDebug() <<QString("%1").arg(_autoOpen);
    } else {
        _autoOpen = 1;
        qDebug() <<QString("%1").arg(_autoOpen);
    }
}
