#ifndef DIALOG_H
#define DIALOG_H

#include <vector>
#include <QDialog>
#include <QPushButton>
#include <QMessageBox>
#include <QCheckBox>
#include <QCloseEvent>
#include <QTime>
#include <QString>
#include <QObject>
#include <QLabel>
#include <QPainter>
#include "suspenddia.h"
#include "datetime.h"
#include "note.h"
#include <QSystemTrayIcon>
#include <QtWidgets>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

extern QString name;
extern QString thing;
extern QString importance;
extern int line;

class Dialog : public QDialog
{
Q_OBJECT

public:
    std::vector<Note*> note_vector;
    std::vector<Note*> note_vector_time;
    static bool isSmaller(Note* a,Note* b);
    Dialog(QWidget *parent = nullptr);
    ~Dialog();
    void onRefresh();
    void onRefresh1();
    void onRefresh_for_time();
    void closeEvent(QCloseEvent *); // 点击“x”按钮
    bool isLogsTimed();
    void composeRefresh();
    void settingsToFile();
    void getSettingsFromFile();
    void paintEvent(QPaintEvent *ev);
    QSystemTrayIcon *trayIcon;
    QSystemTrayIcon *ten_trayIcon;
    QSystemTrayIcon *five_trayIcon;
    QSystemTrayIcon *three_trayIcon;
    QMenu *menu;
    QMenu *ten_menu;
    QMenu *five_menu;
    QMenu *three_menu;
    QSystemTrayIcon* m_systray;         //xsr 20230402

public slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_4_clicked();
    void on_toSusbendBtn_clicked();
    void on_pushButton_5_toggled(bool checked);
    void timeUpdate(void);
    void suspendDiaBack();

public:
    Ui::Dialog *ui;
    Ui::dateTime  *warning;
    Ui::Dialog *warningit;
    QDateTime datetime,three_later_datetime,five_later_datetime,ten_later_datetime;
    QTimer *timer;
    QString systime,three_later_systime,five_later_systime,ten_later_systime;
    //QString str_time[10][7];
    int sign[100] = {0};
    int ten_sign[10] = {0};          //
    int three_sign[10] = {0};       //
    int five_sign[10] = {0};        //
    int m = 0;

private:
    int nextTime = 0;   // 说明有下一次
    SuspendDia *s = nullptr;
    bool logsTimed = true;

private slots:
    int OnSystemTrayClicked(QSystemTrayIcon::ActivationReason reason);
    int OnExit();
};
#endif // DIALOG_H
