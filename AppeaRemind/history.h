#ifndef HISTORY_H
#define HISTORY_H

#include <QDialog>
#include "note.h"
#include <QIcon>
namespace Ui {
    class history;
}

class history : public QDialog
{
Q_OBJECT

public:
    explicit history(QWidget *parent = nullptr,std::vector<Note *> *note_vector1= nullptr);
    ~history();
    void refresh_history();
    std::vector<Note*> *note_vector_history;
private:
    Ui::history *ui;
};

#endif // HISTORY_H
