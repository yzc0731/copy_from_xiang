#include "dialog.h"
#include <QDebug>
#include <QApplication>
#include "about.h"
#include "history.h"
#include "addnew.h"
#include "note.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog *w = new Dialog;
    w->show();
    w->AddNew("name1",1);
    w->AddNew("name2",2);
    //Note *n2=new Note;
    //n2->show();
    return a.exec();
}
