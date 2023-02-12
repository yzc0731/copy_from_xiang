#include "dialog.h"
#include "ui_dialog.h"
#include "addnew.h"
#include "about.h"
#include "history.h"
#include "windows.h"
#include <QGridLayout>
#include <QDebug>
#include "note.h"
#include <QFile>
#include <QTextCodec>
#include <QMessageBox>
#include <QCheckBox>
#include "suspenddia.h"
#include <QPushButton>
#include "ball.h"

//主界面窗口设置
Dialog::Dialog(QWidget *parent)
        : QDialog(parent), ui(new Ui::Dialog) {
    ui->setupUi(this);

    Qt::WindowFlags windowFlag  = Qt::Widget;
    this->setWindowFlags(windowFlag);     // 添加最小化、最大化按键，并且这些按钮自动有对应功能

}

Dialog::~Dialog() {
    delete ui;
}  //析构函数


void Dialog::on_pushButton_clicked() {
    Addnew *add = new Addnew(&note_vector);
    add->exec();    //打开新增面板
    onRefresh();     //刷新
}

void Dialog::on_pushButton_2_clicked() {
    About *about = new About;
    about->show();

}  //打开关于面板

void Dialog::on_pushButton_4_clicked() {
    history *a = new history(this, &note_vector);
    a->show();
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
}

// 按下悬浮窗按钮，跳到悬浮窗界面
void Dialog::on_toSusbendBtn_clicked()
{
    // 创建一个子窗口
    SuspendDia *s = new SuspendDia();
    s->show();

    // 隐藏主窗口
    this->hide();

    //监测窗口s的回退信号
    connect(s,&SuspendDia::back,[=](){
        s->hide();
        this->show();
        onRefresh(); // 刷新
    });
}

void Dialog::onRefresh() {//创建时调用
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

    //

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

            //

            QStringList list = strline.split(" ");                   //以一个空格为分隔符
            for (int i = 0; i < 7; i++) {
                str_read[i] = list[i];
            }
            num = str_read[0].toInt();   //将第一个数据转化为int类
            Note *n1 = new Note(&note_vector, num, str_read[1], str_read[2], str_read[3], str_read[4], str_read[5]);
            note_vector.push_back(n1);   //放到vector最后一个位置
            if (n1->finish == 0) {
                gridLayout->addWidget(n1);
            }
        }
        ui->frame_2->widget()->setLayout(gridLayout);
        repaint();     //顺序输出vector所有的东西
    }
}
