#ifndef SUSPENDDIA_H
#define SUSPENDDIA_H

#include <QDialog>
#include "note.h"

namespace Ui {
class SuspendDia;
}

class SuspendDia : public QDialog
{
    Q_OBJECT

public:
    std::vector<Note*> note_vector;
    explicit SuspendDia(QWidget *parent = nullptr);
    ~SuspendDia();
    void Oncreate();

signals:
    void back();

private slots:
    void on_exitBtn_clicked();

    void on_horizontalSlider_sliderMoved(int position);

private:
    Ui::SuspendDia *ui;
    double pacity = 1.0;
};

#endif // SUSPENDDIA_H
