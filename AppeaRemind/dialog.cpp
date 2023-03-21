#include "dialog.h"
#include "ui_dialog.h"

#include <vector>
#include <algorithm>
#include <QGridLayout>
#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QTextCodec>
#include <QDateTime>
#include <QMessageBox>
#include <QCheckBox>
#include <QPushButton>
#include <QDateTime>
#include <QTime>
#include <QTimer>
#include <QMessageBox>
#include <QString>

#include "datetime.h"
#include "vector_.h"
#include "addnew.h"
#include "about.h"
#include "history.h"
#include "windows.h"
#include "ball.h"
#include "suspenddia.h"
#include "note.h"
#include <QStandardPaths>
QString name;
QString thing;
QString importance;
int line = 0;

//主界面窗口设置
Dialog::Dialog(QWidget *parent)
        : QDialog(parent), ui(new Ui::Dialog) {
    ui->setupUi(this);

    this->setWindowTitle("AppeaRemind");
    this->setWindowOpacity(0.8);
    Qt::WindowFlags windowFlag  = Qt::Widget;
    this->setWindowFlags(windowFlag);     // 添加最小化、最大化按键，并且这些按钮自动有对应功能

    getSettingsFromFile();
    if(logsTimed){
        ui->pushButton_5->setText(tr("改为创建顺序"));
    } else {
        ui->pushButton_5->setText(tr("改为时间顺序"));
    }
    datetime = QDateTime::currentDateTime();
    systime = datetime.toString("hhh:mm yyyy/MM/dd");
    //创建定时器定时更新时间和日期
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Dialog::timeUpdate);
    timer->start(1000);
    //显示日期时间
    //extern QString str_read[20][7];
    QFile::link("AppeaRemind.exe", QStandardPaths::writableLocation(QStandardPaths::DesktopLocation).append("/").append("AppeaRemind.lnk"));
}

Dialog::~Dialog() {
    delete ui;
}  //析构函数


void Dialog::on_pushButton_clicked() {
    Addnew *add = new Addnew(&note_vector);
    add->exec();
    onRefresh() ; //刷新
}   //打开新增面板

void Dialog::on_pushButton_2_clicked() {
    About *about = new About;
    about->show();
}  //打开关于面板

void Dialog::on_pushButton_4_clicked() {
    history *a = new history(this, &note_vector);
    a->show();
}   //历史事项对应窗口

void Dialog::timeUpdate(void)
{
    datetime = QDateTime::currentDateTime();
    systime = datetime.toString("hh:mm yyyy/MM/dd");
    QFile file, file1;
    // int line = 0;
    // 得出事项的数目
    file1.setFileName("log.txt");                                      //保存到本地地址
    QString strline;
    if (file1.open(QIODevice::ReadOnly))                               //只读
    {
        QTextCodec *codec = QTextCodec::codecForName("GBK");         //指定读码方式为GBK
        //note_vector1.clear();
        while (!file1.atEnd())                                        //当没有读到文件末尾时
        {
            strline = codec->toUnicode(file1.readLine());             //以GBK的编码方式读取一行
            QChar c = strline[0];                                    //判断第一个字符是否是回车符（空文件只有一个回车符）
            char c0 = c.toLatin1();
            if (c0 > 57 || c0 < 48) { return; }
            //QStringList list = strline.split(" ");                   //以一个空格为分隔符
            line ++;
        }
    }
    //识别事项
    file.setFileName("log.txt");                                      //保存到本地地址
    //QString str_read[10][7];
    //QString strline;
    QString str_time[line][7];
    int mark[line];
    int j = 0;
    if (file.open(QIODevice::ReadOnly))                               //只读
    {
        QTextCodec *codec = QTextCodec::codecForName("GBK");         //指定读码方式为GBK
        //note_vector1.clear();

        while (!file.atEnd())                                        //当没有读到文件末尾时
        {
            strline = codec->toUnicode(file.readLine());             //以GBK的编码方式读取一行
            QChar c = strline[0];                                    //判断第一个字符是否是回车符（空文件只有一个回车符）
            char c0 = c.toLatin1();
            if (c0 > 57 || c0 < 48) { return; }
            QStringList list = strline.split(" ");                   //以一个空格为分隔符
            for (int i = 0; i < 7; i++) {
                str_time[j][i] = list[i];
            }
            mark[j] = str_time[j][0].toInt();   //将第一个数据转化为int类
            j ++;
        }
    }
    QString settime[line];
    for(int z = 0; z < line; z++)                                             //读取所有设定时间并转化为字符串
    settime[z] = str_time[z][2] + " " + str_time[z][3];

    for(m = 0;m < line; m++)
    if((settime[m] == systime)&&(mark[m] == 0)&&(sign[m] == 0))           //判定时间是否到达
    {
        name = str_time[m][1];
        thing = str_time[m][5];
        importance = str_time[m][4];
        dateTime *alarm = new dateTime;
        alarm -> show();
        sign[m] = 1;                                                     //防止不会一直弹出
   }
}

void Dialog::closeEvent(QCloseEvent *){
    // 点击关闭之后，跳出下面这个对话框。
    // 如果选择no或者右上角的“x”，啥都不做，直接退出
    // 如果选择yes，就跳出悬浮界面
    // 这个函数结束之后主界面直接关闭
    QMessageBox *questionBox = new QMessageBox(this);
    questionBox->setIcon(QMessageBox::Question);
    questionBox->setText("是否进入桌面悬浮状态");
    questionBox->setWindowTitle("Question");

    QPushButton *yesBtn = new QPushButton(tr("是(&Y)"),this);
    questionBox->addButton(yesBtn,QMessageBox::YesRole);
    QPushButton *noBtn = new QPushButton(tr("直接退出(&N)"),this);
    questionBox->addButton(noBtn,QMessageBox::NoRole);

    QCheckBox *checkbox = new QCheckBox("下次不再提示");
    questionBox->setCheckBox(checkbox);

    switch (nextTime)
    {
        case 0:
        {
            questionBox->exec();
            if (checkbox->isChecked()){
                if (questionBox->clickedButton() == yesBtn){
                    nextTime = 1;
                    on_toSusbendBtn_clicked();
                } else {
                    nextTime = 2;
                }
            } else {
                // 没勾选的话,nextTime不会变
                if (questionBox->clickedButton() == yesBtn){
                    on_toSusbendBtn_clicked();
                }
            }
            break;
        }
        case 1:
        {
            on_toSusbendBtn_clicked();
            break;
            // 如果勾选"下次不再提示"+yes就会到这里
        }
        default:
        {
            break;
            // 如果勾选"下次不再提示"+no就会到直接结束
        }
    }
    settingsToFile();
}

bool Dialog::isLogsTimed()
{
    return logsTimed;
}

void Dialog::onRefresh() {        //用于初始化和添加的刷新函数
    if (ui->frame_2->widget()->layout() != nullptr) {   //删除原有布局
        QLayoutItem *item;
        while ((item = ui->frame_2->widget()->layout()->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
        delete ui->frame_2->widget()->layout();
    }
    QGridLayout *gridLayout = new QGridLayout();                     //网格布局
    gridLayout->setVerticalSpacing(20);
    QFile file;
    file.setFileName("log.txt");                                     //保存到本地地址
    QString str_read[9];
    QString strline;
    int num;
    if (file.open(QIODevice::ReadOnly))                              //只读
    {
        QTextCodec *codec = QTextCodec::codecForName("GBK");         //指定读码方式为GBK
        note_vector.clear();                                         //清空vector
        while (!file.atEnd())                                        //当没有读到文件末尾时
        {
            strline = codec->toUnicode(file.readLine());             //以GBK的编码方式读取一行
            QChar c = strline[0];                                    //判断第一个字符是否是回车符（空文件只有一个回车符）
            char c0 = c.toLatin1();
            if (c0 > 57 || c0 < 48)
            { return; }
            QStringList list = strline.split(" ");                   //以一个空格为分隔符
            for (int i = 0; i < 9; i++){str_read[i] = list[i];}
            num = str_read[0].toInt();                 //将第一个数据转化为int类
            Note *n1 = new Note(&note_vector,num, str_read[1],
                    str_read[2], str_read[3], str_read[4],
                    str_read[5], str_read[6], str_read[7]);
            QObject::connect(n1,&Note::refresh,this,&Dialog::composeRefresh);  //关联信号和槽
            note_vector.push_back(n1);                //放到vector最后一个位置
            if (n1->finish == 0) {
                gridLayout->addWidget(n1);
            }
        }
        ui->frame_2->widget()->setLayout(gridLayout);
        repaint();                                //顺序输出vector所有的东西
    }
}

void Dialog::onRefresh1() {     //专门用于编辑的刷新函数
   //
    if (ui->frame_2->widget()->layout() != nullptr) {//删除原有布局
        QLayoutItem *item;
        while ((item = ui->frame_2->widget()->layout()->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
        delete ui->frame_2->widget()->layout();
    }
    QGridLayout *gridLayout = new QGridLayout();                   //网格布局
    QFile file;
    file.setFileName("log.txt");                                    //保存到本地地址
    QString str_read[9];
    QString strline;
    int num;
    if (file.open(QIODevice::ReadOnly))                              //只读
    {
        QTextCodec *codec = QTextCodec::codecForName("GBK");         //指定读码方式为GBK
        note_vector.clear();                                         //清空当前vector，避免重复
        while (!file.atEnd())                                        //当没有读到文件末尾时
        {
            strline = codec->toUnicode(file.readLine());             //以GBK的编码方式读取一行
            QChar c = strline[0];                                    //判断第一个字符是否是回车符（空文件只有一个回车符）
            char c0 = c.toLatin1();
            if (c0 > 57 || c0 < 48)
            { return; }
            QStringList list = strline.split(" ");                   //以一个空格为分隔符
            for (int i = 0; i < 9; i++) {
                str_read[i] = list[i];
            }
            num = str_read[0].toInt();         //将第一个数据转化为int类
            Note *n1 = new Note(&note_vector, num, str_read[1], str_read[2], str_read[3], str_read[4], str_read[5],str_read[6],str_read[7]);
            QObject::connect(n1,&Note::refresh,this,&Dialog::composeRefresh);   //关联信号和槽
            note_vector.push_back(n1);         //放到vector最后一个位置
            if (n1->finish == 0) {gridLayout->addWidget(n1);}
        }
        ui->frame_2->widget()->setLayout(gridLayout);
        repaint();                             //顺序输出vector所有的东西
    }
}

void Dialog::onRefresh_for_time(){        //用于时间顺序的刷新函数

    if (ui->frame_2->widget()->layout() != nullptr) {   //删除原有布局
        QLayoutItem *item;
        while ((item = ui->frame_2->widget()->layout()->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
        delete ui->frame_2->widget()->layout();
    }
    QGridLayout *gridLayout = new QGridLayout();                     //网格布局
    gridLayout->setVerticalSpacing(20);
    QFile file;
    file.setFileName("log.txt");                                     //保存到本地地址
    QString str_read[9];
    QString strline;
    int num;
    if (file.open(QIODevice::ReadOnly))                              //只读
    {
        QTextCodec *codec = QTextCodec::codecForName("GBK");         //指定读码方式为GBK
        note_vector.clear();                                         //清空vector
        while (!file.atEnd())                                        //当没有读到文件末尾时
        {
            strline = codec->toUnicode(file.readLine());             //以GBK的编码方式读取一行
            QChar c = strline[0];                                    //判断第一个字符是否是回车符（空文件只有一个回车符）
            char c0 = c.toLatin1();
            if (c0 > 57 || c0 < 48) { return; }
            QStringList list = strline.split(" ");                   //以一个空格为分隔符
            for (int i = 0; i < 9; i++) { str_read[i] = list[i]; }
            num = str_read[0].toInt();                 //将第一个数据转化为int类
            Note *n1 = new Note(&note_vector, num, str_read[1],
                    str_read[2],str_read[3], str_read[4],
                    str_read[5],str_read[6], str_read[7]);
            QObject::connect(n1, &Note::refresh, this, &Dialog::composeRefresh);  //关联信号和槽
            note_vector.push_back(n1);                //放到vector最后一个位置

        }
    }//删除布局之后再从文件中读一遍

    note_vector_time.clear();
    //
    QString date_time_str[note_vector.size()][2];   //储存时间和日期
    QDateTime date_time[note_vector.size()];        //日时
    uint time[note_vector.size()];
    for(unsigned i = 0; i < note_vector.size(); i++)
    {
        date_time_str[i][0] = note_vector.at(i)->Date;
        date_time_str[i][1] = note_vector.at(i)->Time;
        QString s=date_time_str[i][0];
        QDate d = QDate::fromString(s,"yyyy/MM/dd");
        QTime t = QTime::fromString(date_time_str[i][1],"hh:mm");
        date_time[i] = QDateTime(d,t);
        time[i] = date_time[i].toTime_t();
        note_vector.at(i)->time_int=time[i];
    }//以上步骤提取了note_vector内的时间和日期并且合成了QDateTime类，转换为时间截time
    for(unsigned i=0; i < note_vector.size(); i++){
        note_vector_time.push_back(note_vector.at(i));
    }
    std::sort(note_vector_time.begin(),note_vector_time.end(),isSmaller);
    for(unsigned i=0; i < note_vector_time.size(); i++){
        if(note_vector_time.at(i)->finish == 0){
            gridLayout->addWidget(note_vector_time.at(i));
        }
    }
    ui->frame_2->widget()->setLayout(gridLayout);
    repaint();
}

void Dialog::composeRefresh(){
    if(logsTimed){
        onRefresh_for_time();
    } else {
        onRefresh();
    }
}

void Dialog::on_pushButton_5_toggled(bool)
{
    if (!logsTimed) {
        ui->pushButton_5->setText(tr("改为创建顺序"));
        this->onRefresh_for_time();
        //输出为按照时间排序的文件
        logsTimed = true;
    } else {
        ui->pushButton_5->setText(tr("改为时间顺序"));
        this->onRefresh();
        logsTimed = false;
    }
}

bool Dialog::isSmaller(Note *a, Note *b){
    return a->time_int < b->time_int;
}

void Dialog::suspendDiaBack(){
    s->hide();
    this->show();
    composeRefresh();
    getSettingsFromFile();//从悬浮窗中回来的时候，也要获取文件中的数据
}

void Dialog::on_toSusbendBtn_clicked()
{
    s = new SuspendDia(nullptr,logsTimed);  // 创建一个子窗口
    s->show();
    this->hide();   // 隐藏主窗口
    settingsToFile();
    connect(s,&SuspendDia::back,this,&Dialog::suspendDiaBack); //监测窗口s的回退信号
}

void Dialog::settingsToFile()
{
    std::vector<QString> strAll;
    QFile readFile;
    readFile.setFileName("logset.txt");
    QTextStream stream(&readFile);
    if(readFile.open(QIODevice::ReadOnly)){
        QString strLine;
        for(int i = 0; i < 5; i++){
            strLine = stream.readLine();
            strAll.push_back(strLine);
        }
    }
    readFile.close();
    QFile fileModify;
    fileModify.setFileName("logset.txt");
    if(fileModify.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        QTextStream stream(&fileModify);
        int size = strAll.size();   //size = 5。
        strAll[0] = "logsTimed#"+QString("%1").arg(logsTimed);     //取第一行,实现对logsTimed的替换
        strAll[1] = "nextTime#"+QString("%1").arg(nextTime);     //取第二行,实现对nextTime的替换
        for(int i = 0; i < size - 1; i++){
            QString strLine = strAll[i];
            stream << strLine + "\n";
        }//读取修改过后的每一行并输出
        QString strLine = strAll.at(size - 1);     //读取第五行
        stream << strLine;
    }
    fileModify.close();
}

void Dialog::getSettingsFromFile()
{
    if(QFileInfo::exists("logset.txt")){
        QFile file;
        file.setFileName("logset.txt");         //保存到本地地址
        QString strline;
        if (file.open(QIODevice::ReadOnly))
        {
            strline = file.readLine();             //读取第一行logsTimed
            QStringList list = strline.split("#");  //按照#划分成{logsTimed,0}
            logsTimed = list[1].toInt();
            strline = file.readLine();             //读取第二行nextTime
            QStringList list2 = strline.split("#");  //按照#划分成{nextTime,0}
            nextTime = list2[1].toInt();
        }
    } else {
        QFile initFile;
        initFile.setFileName("logset.txt");
        if(initFile.open(QIODevice::WriteOnly|QIODevice::Text))
        {
            QTextStream stream(&initFile);
            stream << "logsTimed#1\n";
            stream << "nextTime#0\n";
            stream << "pacity#1.0\n";
            stream << "radius#50\n";
            stream << "autoOpen#0";
        }
        initFile.close();
    }
}

void Dialog::paintEvent(QPaintEvent *)    //20230315主界面背景
{
    QPainter painter(this);
    painter.drawPixmap(rect(),QPixmap("Dialog_main_pic.jpg"),QRect());
}
