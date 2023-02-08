#include "suspenddia.h"
#include "ui_suspenddia.h"
#include <QPushButton>
#include <QTextCodec>
#include <QFile>
#include "ball.h"

SuspendDia::SuspendDia(QWidget *parent):
    QDialog(parent),ui(new Ui::SuspendDia)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("MEMOplus悬浮窗"));
    this->setWindowFlags(Qt::Widget);   // 最大化最小化和关闭按钮
    setWindowOpacity(pacity);   // 可以设置透明度

    Oncreate();     //  创造显示一条记录
    this->move(_beginPos);

    //监测信号，当按下backBtn的时候，会发出一个back信号
    connect(ui->backBtn,&QPushButton::clicked,[=](){
        emit this->back();
        hasBall = false;
    });
}

SuspendDia::~SuspendDia()
{
    delete ui;
}

void SuspendDia::on_exitBtn_clicked()
{
    this->close();
}

// 透明度滑动条变化，就能调整透明度
void SuspendDia::on_horizontalSlider_sliderMoved(int position)
{
    pacity = double(position+1)/100;
    setWindowOpacity(pacity);
}

// 创建一个栏目用来存放log.txt文件中的第一条记录
void SuspendDia::Oncreate(){
    if (ui->frame->layout() != nullptr) {
        // 如果本来有布局，就要删除原有布局
        QLayoutItem *item;
        while ((item = ui->frame->layout()->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
        delete ui->frame->layout();
    }
    QGridLayout *gridLayout = new QGridLayout();
    QFile file;
    file.setFileName("log.txt");   //保存到本地地址
    QString str_read[7];
    QString strline;
    int num;
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
            QStringList list = strline.split(" ");                   //以一个空格为分隔符读取
            for (int i = 0; i < 7; i++) {
                str_read[i] = list[i];
            }
            num = str_read[0].toInt();   //将第一个数据转化为int类
            Note *n1 = new Note(&note_vector, num, str_read[1], str_read[2], str_read[3], str_read[4], str_read[5]);
            note_vector.push_back(n1);   //放到vector最后一个位置

            if (n1->finish == 0) {
                gridLayout->addWidget(n1);
                break;
            }// 判断是否未完成，若未完成，输出，结束
        }
        ui->frame->setLayout(gridLayout);
        repaint();
    }
}

//离开窗口区域
void SuspendDia::leaveEvent(QEvent *){
    if (hasBall){
        Ball *ball = new Ball(nullptr,"Nothing on list");    // 创建一个悬浮球
        ball->show();

        this->hide();   // 隐藏悬浮窗窗口

        //监测窗口s的回退信号
        connect(ball,&Ball::backFromBall,[=](){
            _beginPos = ball->getBeginPos();

            ball->hide();
            this->move(_beginPos);
            this->show();
            this->ui->title->setText(tr("%1+%2").arg(_beginPos.x()).arg(_beginPos.y()));
        });
    }
}
