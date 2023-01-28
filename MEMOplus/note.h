#ifndef NOTE_H
#define NOTE_H

#include <QDialog>

namespace Ui {
class Note;
}

class Note : public QDialog
{
    Q_OBJECT

public:
    explicit Note(QWidget *parent = nullptr);
    explicit Note(QWidget *parent = nullptr,QString thing = "空",QString time = "00:00",QString Date = "2023/01/01",QString ddl = "无",QString note = "");
    ~Note();
private slots:
    void on_checkBox_clicked();
private:
    Ui::Note *ui;
};

#endif // NOTE_H
