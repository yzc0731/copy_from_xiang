#ifndef SUSPENDDIA_H
#define SUSPENDDIA_H

#include <QDialog>
#include <QLabel>

#include "settingdia.h"
#include "note.h"
#include "ball.h"

namespace Ui {
class SuspendDia;
}

class SuspendDia : public QDialog
{
    Q_OBJECT

public:
    std::vector<Note*> note_vector;
    std::vector<Note*> note_vector_time;
    static bool isSmaller(Note* a,Note* b);
    explicit SuspendDia(QWidget *parent = nullptr, bool logsTimed = false);
    ~SuspendDia();
    void onRefresh();
    void onRefreshForTime();
    void addStringToBall(Note* note);
    void mouseDoubleClickEvent(QMouseEvent *); //鼠标双击事件
    void mousePressEvent(QMouseEvent *);       //鼠标按下事件
    void mouseReleaseEvent(QMouseEvent *);     //鼠标释放事件
    void mouseMoveEvent(QMouseEvent *);        //鼠标移动事件
    void settingsToFile();
    void getSettingsFromFile();

public slots:
    void pacityChange();

signals:
    void back();

private slots:
    void on_exitBtn_clicked();
    void on_settingBtn_clicked();
    void on_backBtn_clicked();
    void backFromBall();
    void backFromSet();
private:
    Ui::SuspendDia *ui;
    double _pacity = 1.0;
    bool hasBall = false;
    bool hasSet = false;
    QString _text = "Nothing!";
    int _radiusOfBall = 50;
    bool pressed = false;
    bool _autoOpen = false;
    QString _importance = "无";
public:
    QPoint _beginPos = QPoint(100,100);
    SettingDia *set = nullptr;
    //Note *notesus = nullptr;
    Ball *ball = nullptr;
};

#endif // SUSPENDDIA_H
