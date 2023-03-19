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
    SettingDia(QWidget *parent = nullptr, double pacity = 1.0, int radius = 50, bool autoOpen = 0);
    ~SettingDia();
    double getPacity();
    int getRadius();
    bool isAutoOpen();
    void autoOpen(bool flag);

private slots:
    void on_backBtn_clicked();
    void on_horizontalSlider_valueChanged(int value);
    void on_horizontalSlider_2_valueChanged(int value);
    void on_checkBox_clicked();

signals:
    void pacityChanged();
    void backFromSet();

private:
    Ui::SettingDia *ui;
    double _pacity;
    int _radius;
    bool _autoOpen;
};

#endif // SETTINGDIA_H
