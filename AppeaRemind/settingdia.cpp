#include "settingdia.h"
#include "ui_settingdia.h"

#include <QScrollArea>
#include <QDebug>
#include <QApplication>
#include <QSettings>
#include <QDir>

const QString regedit = "HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";

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
        //因为autoOpen是1所以就触发勾选，然后就相当于statechanged，然后就调用函数，把autoOpen给改为0
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

void SettingDia::autoOpen(bool flag)
{
    QSettings autoRunSetting(regedit, QSettings::NativeFormat);
    QString name = "AppeaRemind";
    QString appPath = qApp->applicationFilePath();
    QString oldPath = autoRunSetting.value(name).toString();//从注册表中获取这个软件名字对应的绝对路径
    QString newPath = QDir::toNativeSeparators(appPath);//toNativeSeparators函数将"/"替换为"\"
    if(flag){
        if (oldPath != newPath){
            //如果注册表中的路径和当前程序路径不一样，则表示没有设置自启动或者已经更换了路径,那就得重新设置
            autoRunSetting.remove(name);
            autoRunSetting.setValue(name, newPath);
        } else {
        }
    }
    else{
        autoRunSetting.remove(name);
        qDebug() << "delete auto open";
    }
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

void SettingDia::on_checkBox_clicked()
{
    if(_autoOpen){
        _autoOpen = 0;
        autoOpen(_autoOpen);
    } else {
        _autoOpen = 1;
        autoOpen(_autoOpen);
    }
}
