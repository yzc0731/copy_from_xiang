#include "dialog.h"

#include <QDebug>
#include <QApplication>

#include "dialog.h"
#include "about.h"
#include "history.h"
#include "addnew.h"
#include "note.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog *w = new Dialog;
    w->show();
    w->composeRefresh();   //显示提醒事项的函数
    return a.exec();
}
