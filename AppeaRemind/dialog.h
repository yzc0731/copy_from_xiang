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
    QDateTime datetime;
    QTimer *timer;
    QString systime;
    int sign[100] = {0};
    int m = 0;

private:
    int nextTime = 0;   // 说明有下一次
    SuspendDia *s = nullptr;
    bool logsTimed = 1;   // 默认为按照ddl时间排序
};
#endif // DIALOG_H
