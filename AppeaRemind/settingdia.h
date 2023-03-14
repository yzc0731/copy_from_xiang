#ifndef SETTINGDIA_H
#define SETTINGDIA_H

#include <QDialog>

namespace Ui {
class SettingDia;
}

class SettingDia : public QDialog
{
    Q_OBJECT

public:
    explicit SettingDia(QWidget *parent = nullptr);
    SettingDia(QWidget *parent = nullptr, double pacity = 1.0);
    ~SettingDia();
    double getPacity();
    int getRadius();

private slots:
    void on_backBtn_clicked();
    void on_horizontalSlider_valueChanged(int value);

    void on_horizontalSlider_2_valueChanged(int value);

signals:
    void pacityChanged();

private:
    Ui::SettingDia *ui;
    double _pacity = 1.0;
    int _radius = 50;
};

#endif // SETTINGDIA_H
