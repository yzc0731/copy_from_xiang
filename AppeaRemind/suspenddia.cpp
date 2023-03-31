#include "suspenddia.h"
#include "ui_suspenddia.h"

#include <QPushButton>
#include <QTextCodec>
#include <QFile>
#include <QFileInfo>
#include <QDebug>
#include <QDateTime>
#include <QApplication>
#include <QScreen>

#include "ball.h"
#include "settingdia.h"

SuspendDia::SuspendDia(QWidget *parent, bool logsTimed):
    QDialog(parent),ui(new Ui::SuspendDia)
{
    ui->setupUi(this);

    QPalette pa;
    pa.setColor(QPalette::Background,QColor(255,255,200,255));
    this->setAutoFillBackground(true);
    this->setPalette(pa);

    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint
                         | Qt::WindowMinMaxButtonsHint|Qt::WindowStaysOnTopHint);
    getSettingsFromFile();//每次打开悬浮窗的时候，都要从设置文件中获得参数
    this->setWindowOpacity(_pacity);

    if(logsTimed){
        onRefreshForTime();
    } else{
        onRefresh();     // 创造显示一条记录
    }

    QScreen *screen = qApp->primaryScreen();
    int screenWidth = screen->size().width();
    int screenHeight = screen->size().height();

    int uiWidth = this->width();
    _beginPos = QPoint (screenWidth - uiWidth, screenHeight/3);
    this->move(_beginPos);
}

SuspendDia::~SuspendDia()
{
    delete ui;
}

void SuspendDia::onRefresh()
{
    if (ui->frame->layout() != nullptr) {//删除原有布局
        QLayoutItem *item;
        while ((item = ui->frame->layout()->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
        delete ui->frame->layout();
    }
    QGridLayout *gridLayout = new QGridLayout();                   //网格布局

    QFile file;
    //QString nametxt = QString("log.txt").toLatin1();               //读取文件的时候转化为拉丁文编码
    //file.setFileName(nametxt);                                    //保存到本地地址
    file.setFileName("log.txt");
    QString str_read[9];
    QString strline;
    int num;

    bool nothing = true;

    if (file.open(QIODevice::ReadOnly))                               //只读
    {
        QTextCodec *codec = QTextCodec::codecForName("GBK");         //指定读码方式为GBK

        note_vector.clear();

        while (!file.atEnd())                                        //当没有读到文件末尾时
        {
            strline = codec->toUnicode(file.readLine());             //以GBK的编码方式读取一行
            QChar c = strline[0];                       //判断第一个字符是否是回车符（空文件只有一个回车符）
            char c0 = c.toLatin1();
            if (c0 > 57 || c0 < 48) { return; }
            QStringList list = strline.split(" ");                   //以一个空格为分隔符
            for (int i = 0; i < 9; i++) {
                str_read[i] = list[i];
            }
            num = str_read[0].toInt();   //将第一个数据转化为int类
            notesus = new Note(&note_vector,num,str_read[1],str_read[2],str_read[3],
                    str_read[4],str_read[5],str_read[6],str_read[7]);
            QObject::connect(notesus,&Note::refresh,this,&SuspendDia::onRefresh);  //关联信号和槽
            //每次点击都能实现
            note_vector.push_back(notesus);   //将读到的每行数据放到vector中，这个vector中的所有数据最后又会重新写入log.txt文件
            if (notesus->finish == 0 && nothing) {
                gridLayout->addWidget(notesus); // 把第一条没有被完成的记录，增添到界面上
                addStringToBall(notesus);
                nothing = false;
            }
        }
        ui->frame->setLayout(gridLayout);
        repaint();     //顺序输出vector所有的东西
    }
}

void SuspendDia::onRefreshForTime()
{
    //如果是第一次按照时间顺序排序，先从log.txt里面读取，按照时间排序之后输出
    if (ui->frame->layout() != nullptr) {   //删除原有布局
        QLayoutItem *item;
        while ((item = ui->frame->layout()->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
        delete ui->frame->layout();
    }
    QGridLayout *gridLayout = new QGridLayout();                     //网格布局
    gridLayout->setVerticalSpacing(20);

    QFile file;
    //QString nametxt = QString("log.txt").toLatin1();               //读取文件的时候转化为拉丁文编码
    //file.setFileName(nametxt);                                    //保存到本地地址
    file.setFileName("log.txt");
    QString str_read[9];
    QString strline;
    int num;

    bool nothing = true;

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
                        str_read[2], str_read[3],str_read[4],
                        str_read[5],str_read[6], str_read[7]);
            QObject::connect(n1, &Note::refresh, this, &SuspendDia::onRefreshForTime);
            //因为在这个界面上没有办法修改顺序，所以就不需要composeRefresh
            note_vector.push_back(n1);                //放到vector最后一个位置
        }
    }

    // 以上这段代码是：删除布局之后再从log.txt文件中读一遍
    // 然后下面要开始按照时间排序，把notevector中的东西，按照时间顺序，放到notevectortime中，然后输出

    note_vector_time.clear();

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
    }
    //以上步骤提取了note_vector内的时间和日期并且合成了QDateTime类，转换为时间截time

    for(unsigned i=0; i < note_vector.size(); i++){
        note_vector_time.push_back(note_vector.at(i));
    } //放到notevectortime中
    std::sort(note_vector_time.begin(),note_vector_time.end(),isSmaller);
    for(unsigned i=0; i < note_vector_time.size(); i++){
        if(note_vector_time.at(i)->finish == 0 && nothing){
            gridLayout->addWidget(note_vector_time.at(i));
            addStringToBall(note_vector_time.at(i));
            nothing = false;
        }
    }

    ui->frame->setLayout(gridLayout);
    repaint();
}

void SuspendDia::addStringToBall(Note *note)
{
    _text = note->Thing;
    _text += "\n";
    _text += note->Date;
    _text += "\n";
    _text += note->Time;
    _importance = note->ddl;
}

void SuspendDia::on_exitBtn_clicked()
{
    if(set){
        set->close();
    }
    settingsToFile();
    this->close();
}

void SuspendDia::backFromBall()
{
    int width = this->width();
    int height = this->height();
    _beginPos = ball->getBeginPos();
    _beginPos = QPoint (_beginPos.x()-width/2, _beginPos.y()-height/2);
    ball->hide();
    this->move(_beginPos);
    this->show();
    getSettingsFromFile();
    this->setWindowOpacity(_pacity);
}

void SuspendDia::backFromSet()
{
    _radiusOfBall = set->getRadius();
    _autoOpen = set->isAutoOpen();
    hasSet = false;
}

void SuspendDia::mouseDoubleClickEvent(QMouseEvent *)
{
    if(hasSet){
        set->close();
        backFromSet();
    }
    if (!hasBall){
        int width = this->width();
        int height = this->height();
        _beginPos = QPoint (_beginPos.x()+width/2, _beginPos.y()+height/2);
        ball = new Ball(nullptr, _text, _beginPos, _radiusOfBall, _importance);    // 创建一个悬浮球
        ball->show();
        settingsToFile();
        this->hide();   // 隐藏悬浮窗窗口

        connect(ball,&Ball::backFromBall,this,&SuspendDia::backFromBall);//监测窗口s的回退信号
    }
}

void SuspendDia::mousePressEvent(QMouseEvent *){
    pressed = true;
    _beginPos = QCursor::pos();
}

void SuspendDia::mouseReleaseEvent(QMouseEvent *){
    pressed = false;
    _beginPos = QPoint (this->pos().x(),this->pos().y());
}

void SuspendDia::mouseMoveEvent(QMouseEvent *){
    if (pressed)
    {
        QPoint newPoint = QCursor::pos();                       //记录鼠标移动最新的鼠标坐标
        float xDis = newPoint.x() - _beginPos.x();				//计算移动后和按下时的坐标差x
        float yDis = newPoint.y() - _beginPos.y();				//计算移动后和按下时的坐标差y
        this->move(this->pos().x() + xDis, this->pos().y()+yDis);
        //让自定义按钮的位置加上坐标差，并移动至加上移动距离之后的位置
        _beginPos = QCursor::pos();
        if(set){
            QPoint setPos = QPoint(this->pos().x()-set->width(),this->pos().y());
            set->move(setPos);      //更新设置窗口的位置
        }
    }
}

void SuspendDia::settingsToFile()
{
    std::vector<QString> strAll;
    QFile readFile;
    //QString nametxt = QString("logset.txt").toLatin1();               //读取文件的时候转化为拉丁文编码
    //readFile.setFileName(nametxt);
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
        //strAllList = strAll.split("\n");    //按照行来划分成list
        int size = strAll.size();   //size = 5。
        strAll[2] = "pacity#"+QString("%1").arg(_pacity);     //取第三行,实现对pacity的替换
        strAll[3] = "radius#"+QString("%1").arg(_radiusOfBall);     //取第四行,实现对nextTime的替换
        strAll[4] = "autoOpen#"+QString("%1").arg(_autoOpen);    //取第五行,实现对nextTime的替换
        for(int i = 0; i < size - 1; i++){
            QString strLine = strAll[i];
            stream << strLine + "\n";
        }//读取修改过后的每一行并输出
        QString strLine = strAll.at(size - 1);     //读取第五行
        stream << strLine;
    }
    fileModify.close();
}

void SuspendDia::getSettingsFromFile()
{
    //QString nametxt = QString("logset.txt").toLatin1();               //读取文件的时候转化为拉丁文编码
    if(QFileInfo::exists("logset.txt")){
        QFile file;
        file.setFileName("logset.txt");         //保存到本地地址
        QString strline;
        if (file.open(QIODevice::ReadOnly))
        {
            strline = file.readLine();             //读取第一行logsTimed
            strline = file.readLine();             //读取第二行nextTime
            strline = file.readLine();             //读取第三行pacity
            QStringList list = strline.split("#");  //按照#划分成{pacity,1.0}
            _pacity = list[1].toDouble();
            strline = file.readLine();             //读取第四行radius
            QStringList list2 = strline.split("#");  //按照#划分成{radius,50}
            _radiusOfBall = list2[1].toInt();
            strline = file.readLine();             //读取第五行autoOpen
            QStringList list3 = strline.split("#");  //按照#划分成{autoOpen,0}
            _autoOpen = list3[1].toInt();
        }
    } else {
        qDebug()<<"File not exists";
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

void SuspendDia::on_settingBtn_clicked()
{
    if (hasSet){
        return;
    } else {
        set = new SettingDia(nullptr,_pacity,_radiusOfBall,_autoOpen);    // 创建一个设置窗口
        QPoint setPos = QPoint(_beginPos.x()-set->width(),_beginPos.y());
        set->move(setPos);
        set->show();
        connect(set,&SettingDia::backFromSet,this,&SuspendDia::backFromSet);
        connect(set,&SettingDia::pacityChanged,this,&SuspendDia::pacityChange);
        hasSet = true;
    }
}

void SuspendDia::pacityChange(){
    _pacity = set->getPacity();
    this->setWindowOpacity(_pacity);
}

void SuspendDia::on_backBtn_clicked()
{
    hasBall = true;
    if(set != nullptr){
        set->close();
    }
    settingsToFile();
    emit this->back();
}

bool SuspendDia::isSmaller(Note *a, Note *b){
    return a->time_int < b->time_int;
}
