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

private slots:
    void on_backBtn_clicked();
    void on_horizontalSlider_valueChanged(int value);

signals:
    void pacityChanged();

private:
    Ui::SettingDia *ui;
    double _pacity = 1.0;
};

#endif // SETTINGDIA_H
