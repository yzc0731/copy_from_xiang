#include "suspenddia.h"
#include "ui_suspenddia.h"

#include <QPushButton>
#include <QTextCodec>
#include <QFile>
#include <QDebug>

#include "ball.h"
#include "settingdia.h"

SuspendDia::SuspendDia(QWidget *parent, bool logsTimed):
    QDialog(parent),ui(new Ui::SuspendDia)
{
    ui->setupUi(this);
    //this->setWindowTitle(tr("悬浮窗"));
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint
                         | Qt::WindowMinMaxButtonsHint|Qt::WindowStaysOnTopHint);
    // setWindowOpacity(pacity);   // 可以设置透明度

    if(logsTimed){
        onRefreshForTime();
    } else{
        onRefresh();     // 创造显示一条记录
    }

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

            note_vector.push_back(notesus);   //将读到的每行数据放到vector中，这个vector中的所有数据最后又会重新写入log.txt文件

            if (notesus->finish == 0 && nothing) {
                gridLayout->addWidget(notesus); // 把第一条没有被完成的记录，增添到界面上
                text += str_read[1];
                text += "\n";
                text += str_read[3];
                text += "\n";
                text += str_read[2];

                nothing = false;
            }
        }
        ui->frame->setLayout(gridLayout);
        repaint();     //顺序输出vector所有的东西
    }
}

void SuspendDia::onRefreshForTime()
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
    file.setFileName("logTimed.txt");
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

            note_vector.push_back(notesus);   //将读到的每行数据放到vector中，这个vector中的所有数据最后又会重新写入log.txt文件

            if (notesus->finish == 0 && nothing) {
                gridLayout->addWidget(notesus); // 把第一条没有被完成的记录，增添到界面上
                text += str_read[1];
                text += "\n";
                text += str_read[3];
                text += "\n";
                text += str_read[2];

                nothing = false;
            }
        }
        ui->frame->setLayout(gridLayout);
        repaint();     //顺序输出vector所有的东西
    }
}

void SuspendDia::on_exitBtn_clicked()
{
    if(set){
        set->close();
    }
    this->close();
}

void SuspendDia::mouseDoubleClickEvent(QMouseEvent *)
{
    if(set){
        set->close();
    }
    if (!hasBall){
        Ball *ball = new Ball(nullptr,text,_beginPos);    // 创建一个悬浮球
        ball->show();
        this->hide();   // 隐藏悬浮窗窗口
        connect(ball,&Ball::backFromBall,[=](){
            _beginPos = ball->getBeginPos();

            ball->hide();
            this->move(_beginPos);
            this->show();
        });//监测窗口s的回退信号
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
//        if(set){
//            qDebug() << QString("%1,%2").arg(this->set->pos().x() + xDis).arg(this->set->pos().y()+yDis);
//            this->set->move(this->set->pos().x() + xDis, this->set->pos().y()+yDis);
//        }
        _beginPos = QCursor::pos();
        if(set){
            QPoint setPos = QPoint(this->pos().x()+this->width(),this->pos().y());
            set->move(setPos);      //更新按下时的坐标为当前坐标位置
        }
    }
}

void SuspendDia::closeEvent(QCloseEvent *)
{
    if(set){
        set->close();
    }
}

void SuspendDia::setPacityToFile()
{

}

void SuspendDia::getPacityFromFile()
{

}

void SuspendDia::on_settingBtn_clicked()
{
    set = new SettingDia(nullptr,_pacity);    // 创建一个设置窗口
    QPoint setPos = QPoint(_beginPos.x()+this->width(),_beginPos.y());
    set->move(setPos);
    set->show();

    connect(set,&SettingDia::pacityChanged,[=](){
        _pacity = set->getPacity();
        this->setWindowOpacity(_pacity);
    });
}

void SuspendDia::on_backBtn_clicked()
{
    hasBall = true;
    if(set != nullptr){
        set->close();
    }
    emit this->back();
}