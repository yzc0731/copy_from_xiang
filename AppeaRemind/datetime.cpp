#include "datetime.h"
#include "ui_datetime.h"

#include <QAction>
#include <QMenu>
#include <QStyle>
#include <QDesktopWidget>

#include "addnew.h"
#include "about.h"
#include "history.h"
#include "windows.h"
#include "note.h"
#include "dialog.h"
#include "lengthen.h"

dateTime::dateTime(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dateTime)
{
    ui->setupUi(this);
    //初始化时间和日期显示
    //隐藏标题栏
    setWindowFlags(Qt::FramelessWindowHint);//无边框

    //打开的窗口在屏幕右下角
    QDesktopWidget *widget= QApplication::desktop();
    move(widget->width()-this->width(),widget->height()-this->height()+10);

    ui->things->setText("名称："+ name + "\n" +"备注：" + thing+ "\n" +"重要程度：" + importance) ;

    datetime = QDateTime::currentDateTime();
    systime = datetime.toString("hh:mm yyyy/MM/dd");

    //创建定时器定时更新时间和日期
    timer = new QTimer(this);
   // connect(timer, SIGNAL(timeout()), this, SLOT(myslot()));
    connect(timer, &QTimer::timeout, this, &dateTime::timeUpdate);
    timer->start(1000);
}

dateTime::~dateTime()
{
    delete ui;
}

void dateTime::timeUpdate(void)
{
    datetime = QDateTime::currentDateTime();
    systime = datetime.toString("hhh:mm yyyy/MM/dd");
    QFile file;
    file.setFileName("log.txt");   //保存到本地地址
    QString str_read[line][7];
    QString strline;
    int mark[line];
    int j = 0;
    if (file.open(QIODevice::ReadOnly))                               //只读
    {
        QTextCodec *codec = QTextCodec::codecForName("GBK");         //指定读码方式为GBK
        //note_vector1.clear();

        while (!file.atEnd())                                        //当没有读到文件末尾时
        {
            strline = codec->toUnicode(file.readLine());             //以GBK的编码方式读取一行
            QChar c = strline[0];                       //判断第一个字符是否是回车符（空文件只有一个回车符）
            char c0 = c.toLatin1();
            if (c0 > 57 || c0 < 48) { return; }

            //

            QStringList list = strline.split(" ");                   //以一个空格为分隔符
            for (int i = 0; i < 7; i++) {
                str_read[j][i] = list[i];
            }
            mark[j] = str_read[j][0].toInt();   //将第一个数据转化为int类
            //Note *n1 = new Note(&note_vector, mark, str_read[1], str_read[2], str_read[3], str_read[4], str_read[5]);
            //QString settime = str_read[2] + " " + str_read[3];
            j ++;
        }
    }
   // QTime timeNow=QTime::currentTime();//获取实时时间
    //QString systime = timeNow.toString("hhh:mm") + " " + QDate::currentDate().toString("yyyy/MM/dd");

    QString settime[line];
    for(int z = 0; z < j; z++)//读取所有设定时间并转化为字符串
    settime[z] = str_read[z][2] + " " + str_read[z][3];

    for(int m = 0;m < j; m++)
    if((settime[m] == systime)&&(mark[m] == 0))
    {
        QMessageBox::information(this,"alarm","时间到了！");
        //QTime t(0,0,0);
        //ui->timeEdit_alarm->setReadOnly(false);
        //setTime = t;
        //ui->timeEdit_alarm->setTime(t);
        //delete alarm_timer;
        //alarm_timer = nullptr;
    }

}

//void dateTime::myslot()
//{
 //   show();                                            //计时到，再次显示
 //   timer->stop();
//}

void dateTime::on_pushButton_clicked()
{
    close();
}

void dateTime::on_pushButton_2_clicked()
{
    //hide();                                             //计时开始，界面隐藏
    //int num = 600;                                      //计时秒数（600秒）
    //num *= 1000;
    //timer->start(num);
    lengthen *timing = new lengthen;
    timing->show();
    hide();
}

