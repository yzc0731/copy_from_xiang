#ifndef DIALOG_H
#define DIALOG_H
#include <vector>
#include <QDialog>
#include "note.h"
#include <QPushButton>

// 为了更改主界面的“x”按钮之后的事件而添加
#include <QCloseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
Q_OBJECT

public:
    std::vector<Note*> note_vector;
    Dialog(QWidget *parent = nullptr);
    ~Dialog();
    void onCreate();
    void Shownote();
    void closeEvent(QCloseEvent *event);  // 点击“x”按钮

public slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_toggled(bool checked);

    void on_pushButton_4_clicked();

    void on_toSusbendBtn_clicked();

public:
    Ui::Dialog *ui;
};
#endif // DIALOG_H
