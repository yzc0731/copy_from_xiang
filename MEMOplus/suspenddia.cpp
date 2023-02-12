#include "suspenddia.h"
#include "ui_suspenddia.h"
#include <QPushButton>
#include <QTextCodec>
#include <QFile>
#include "ball.h"
#include "settingdia.h"

SuspendDia::SuspendDia(QWidget *parent):
    QDialog(parent),ui(new Ui::SuspendDia)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("悬浮窗"));
    this->setWindowFlags(Qt::Widget);
    // setWindowOpacity(pacity);   // 可以设置透明度

    onRefresh();     //  创造显示一条记录
    this->move(_beginPos);

    //监测信号，当按下backBtn的时候，会发出一个back信号
    connect(ui->backBtn,&QPushButton::clicked,[=](){
        emit this->back();
        hasBall = true;
    });
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
    QString str_read[7];
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
            for (int i = 0; i < 7; i++) {
                str_read[i] = list[i];
            }
            num = str_read[0].toInt();   //将第一个数据转化为int类
            Note *n1 = new Note(&note_vector, num, str_read[1], str_read[2], str_read[3], str_read[4], str_read[5]);

            note_vector.push_back(n1);   //将读到的每行数据放到vector中，这个vector中的所有数据最后又会重新写入log.txt文件

            if (n1->finish == 0 && nothing) {
                gridLayout->addWidget(n1);
                // 把第一条没有被完成的记录，增添到界面上
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
    this->close();
}

// 创建一个栏目用来存放log.txt文件中的第一条记录


////离开窗口区域
//void SuspendDia::leaveEvent(QEvent *){
//    if (!hasBall){
//        Ball *ball = new Ball(nullptr,"Nothing on list",_beginPos);    // 创建一个悬浮球
//        hasBall = true;
//        ball->show();

//        this->hide();   // 隐藏悬浮窗窗口

//        //监测窗口s的回退信号
//        connect(ball,&Ball::backFromBall,[=](){
//            _beginPos = ball->getBeginPos();

//            ball->hide();
//            this->move(_beginPos);
//            this->show();
//        });
//    }
//}

void SuspendDia::mouseDoubleClickEvent(QMouseEvent *)
{
    if (!hasBall){
        Ball *ball = new Ball(nullptr,text,_beginPos);    // 创建一个悬浮球
        ball->show();

        this->hide();   // 隐藏悬浮窗窗口

        //监测窗口s的回退信号
        connect(ball,&Ball::backFromBall,[=](){
            _beginPos = ball->getBeginPos();

            ball->hide();
            this->move(_beginPos);
            this->show();
        });
    }
}

void SuspendDia::mousePressEvent(QMouseEvent *){
    pressed = true;
    _beginPos = QCursor::pos();
}

void SuspendDia::mouseReleaseEvent(QMouseEvent *){
    pressed = false;
}

void SuspendDia::mouseMoveEvent(QMouseEvent *){
    if (pressed)
    {
        QPoint newPoint = QCursor::pos();                       //记录鼠标移动最新的鼠标坐标
        float xDis = newPoint.x() - _beginPos.x();				//计算移动后和按下时的坐标差x
        float yDis = newPoint.y() - _beginPos.y();				//计算移动后和按下时的坐标差y
        this->move(this->pos().x() + xDis, this->pos().y()+yDis);	//让自定义按钮的位置加上坐标差，并移动至加上移动距离之后的位置
        _beginPos = QCursor::pos();                                 //更新按下时的坐标为当前坐标位置
    }
}

void SuspendDia::on_settingBtn_clicked()
{
    SettingDia *set = new SettingDia(nullptr,_pacity);    // 创建一个设置窗口
    QPoint setPos = QPoint(_beginPos.x()+this->width(),_beginPos.y());
    set->move(setPos);
    set->show();

    connect(set,&SettingDia::pacityChanged,[=](){
        _pacity = set->getPacity();
        this->setWindowOpacity(_pacity);
    });
}
