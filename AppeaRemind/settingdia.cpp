#include "settingdia.h"
#include "ui_settingdia.h"
#include <QDebug>
#include <QScrollArea>
#include <QApplication>
#include <QSettings>
#include <QDir>
#include <QMessageBox>

const QString regedit = "HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
const QString name = "AppeaRemind";

SettingDia::SettingDia(QWidget *parent, double pacity, int radius, int autoOpen):
    QDialog(parent),ui(new Ui::SettingDia),_pacity(pacity), _radius(radius),_autoOpen(autoOpen)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint
                         | Qt::WindowMinMaxButtonsHint|Qt::WindowStaysOnTopHint);
    this->setWindowOpacity(pacity);
    int value = _pacity*100 - 1;
    ui->horizontalSlider->setValue(value);
    ui->horizontalSlider_2->setValue(_radius);
    if(_autoOpen == 1){
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

int SettingDia::getAutoOpen()
{
    return _autoOpen;
}

void SettingDia::autoOpen(int flag)
{
    QSettings autoRunSetting(regedit, QSettings::NativeFormat);
    QString appPath = QCoreApplication::applicationFilePath();
    QString oldPath = autoRunSetting.value(name).toString();//从注册表中获取这个软件名字对应的绝对路径
    QString newPath = QDir::toNativeSeparators(appPath);//toNativeSeparators函数将"/"替换为"\"
    newPath.replace(".exe",".lnk"); //把路径中的exe换成lnk
    if(flag){
        if (!QFile::exists(newPath)) {
            //如果文件夹里不存在这个快捷方式，那就新建一个快捷方式
            QFile::link(QCoreApplication::applicationFilePath(), name + ".lnk");
        }
        if (oldPath != newPath){
            //如果注册表中的路径和当前程序路径不一样，则表示没有设置自启动或者已经更换了路径,那就得重新设置
            autoRunSetting.remove(name);
            autoRunSetting.setValue(name, newPath);
        }
    }
    else{
        autoRunSetting.remove(name);//取消开机自启
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
    QSettings autoRunSetting(regedit, QSettings::NativeFormat);
    QString newSetPath = autoRunSetting.value(name).toString();
    emit this->pacityChanged();
}

void SettingDia::on_horizontalSlider_2_valueChanged(int value)
{
    _radius = value;
}

bool SettingDia::checkIfSet(){
    QSettings autoRunSetting(regedit, QSettings::NativeFormat);
    QString newSetPath = autoRunSetting.value(name).toString();//从注册表中获取这个软件名字对应的绝对路径
    QString appPath = QCoreApplication::applicationFilePath();
    QString shallSetPath = QDir::toNativeSeparators(appPath);//toNativeSeparators函数将"/"替换为"\"
    shallSetPath.replace(".exe",".lnk");
    if(newSetPath == shallSetPath){
        return 1;
    }else{
        return 0;
    }
}

void SettingDia::on_checkBox_clicked()
{
    switch (_autoOpen) {
        case 2:{
            ui->checkBox->setChecked(false);
            QMessageBox *warningBox = new QMessageBox(this);
            warningBox->setIcon(QMessageBox::Warning);
            warningBox->setText(tr("这项操作已被系统禁止"));
            warningBox->exec();
            break;
        }
        case 1:{
            bool flag = checkIfSet();
            if (!flag){
                _autoOpen = 2;
                QMessageBox *warningBox = new QMessageBox(this);
                warningBox->setIcon(QMessageBox::Warning);
                warningBox->setText(tr("这项操作已被系统禁止"));
                warningBox->exec();
            } else {
                _autoOpen = 0;
                autoOpen(_autoOpen);
                ui->checkBox->setChecked(false);
            }
            break;
        }
        case 0:{
            _autoOpen = 1;
            autoOpen(_autoOpen);
            ui->checkBox->setChecked(true);
            break;
        }
    }
}

