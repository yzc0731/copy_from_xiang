/********************************************************************************
** Form generated from reading UI file 'addnew.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDNEW_H
#define UI_ADDNEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTimeEdit>

QT_BEGIN_NAMESPACE

class Ui_Addnew
{
public:
    QGridLayout *gridLayout;
    QLineEdit *LineEdit;
    QLineEdit *nameLineEdit;
    QLabel *timeLabel;
    QLabel *label_2;
    QLabel *label;
    QLabel *dateLabel;
    QTimeEdit *timeTimeEdit;
    QComboBox *comboBox;
    QLabel *nameLabel;
    QLabel *Label;
    QDateEdit *dateDateEdit;
    QPushButton *pushButton;

    void setupUi(QDialog *Addnew)
    {
        if (Addnew->objectName().isEmpty())
            Addnew->setObjectName(QString::fromUtf8("Addnew"));
        Addnew->resize(511, 249);
        gridLayout = new QGridLayout(Addnew);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        LineEdit = new QLineEdit(Addnew);
        LineEdit->setObjectName(QString::fromUtf8("LineEdit"));
        LineEdit->setMinimumSize(QSize(0, 50));

        gridLayout->addWidget(LineEdit, 4, 2, 1, 1);

        nameLineEdit = new QLineEdit(Addnew);
        nameLineEdit->setObjectName(QString::fromUtf8("nameLineEdit"));

        gridLayout->addWidget(nameLineEdit, 1, 2, 1, 1);

        timeLabel = new QLabel(Addnew);
        timeLabel->setObjectName(QString::fromUtf8("timeLabel"));
        timeLabel->setMinimumSize(QSize(0, 23));

        gridLayout->addWidget(timeLabel, 2, 0, 1, 1);

        label_2 = new QLabel(Addnew);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 5, 0, 1, 1);

        label = new QLabel(Addnew);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        dateLabel = new QLabel(Addnew);
        dateLabel->setObjectName(QString::fromUtf8("dateLabel"));
        dateLabel->setMinimumSize(QSize(0, 25));
        dateLabel->setMaximumSize(QSize(16777215, 25));

        gridLayout->addWidget(dateLabel, 3, 0, 1, 1);

        timeTimeEdit = new QTimeEdit(Addnew);
        timeTimeEdit->setObjectName(QString::fromUtf8("timeTimeEdit"));
        timeTimeEdit->setDateTime(QDateTime(QDate(2023, 1, 1), QTime(0, 0, 0)));
        timeTimeEdit->setCurrentSection(QDateTimeEdit::NoSection);
        timeTimeEdit->setCalendarPopup(true);

        gridLayout->addWidget(timeTimeEdit, 2, 2, 1, 1);

        comboBox = new QComboBox(Addnew);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setEditable(true);

        gridLayout->addWidget(comboBox, 5, 2, 1, 1);

        nameLabel = new QLabel(Addnew);
        nameLabel->setObjectName(QString::fromUtf8("nameLabel"));

        gridLayout->addWidget(nameLabel, 1, 0, 1, 1);

        Label = new QLabel(Addnew);
        Label->setObjectName(QString::fromUtf8("Label"));
        Label->setMinimumSize(QSize(0, 50));

        gridLayout->addWidget(Label, 4, 0, 1, 1);

        dateDateEdit = new QDateEdit(Addnew);
        dateDateEdit->setObjectName(QString::fromUtf8("dateDateEdit"));
        dateDateEdit->setMinimumSize(QSize(0, 25));
        dateDateEdit->setMaximumSize(QSize(16777215, 25));
        dateDateEdit->setDateTime(QDateTime(QDate(2023, 1, 1), QTime(0, 0, 0)));
        dateDateEdit->setCalendarPopup(true);

        gridLayout->addWidget(dateDateEdit, 3, 2, 1, 1);

        pushButton = new QPushButton(Addnew);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout->addWidget(pushButton, 0, 2, 1, 1);


        retranslateUi(Addnew);

        QMetaObject::connectSlotsByName(Addnew);
    } // setupUi

    void retranslateUi(QDialog *Addnew)
    {
        Addnew->setWindowTitle(QCoreApplication::translate("Addnew", "\346\267\273\345\212\240", nullptr));
        timeLabel->setText(QCoreApplication::translate("Addnew", "\346\227\266\351\227\264(Time)", nullptr));
        label_2->setText(QCoreApplication::translate("Addnew", "\347\264\247\346\200\245\347\250\213\345\272\246(ddl)", nullptr));
        label->setText(QCoreApplication::translate("Addnew", "\346\267\273\345\212\240\347\225\214\351\235\242", nullptr));
        dateLabel->setText(QCoreApplication::translate("Addnew", "\346\227\245\346\234\237(Date)", nullptr));
        timeTimeEdit->setDisplayFormat(QCoreApplication::translate("Addnew", "0H:mm", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("Addnew", "\346\227\240", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("Addnew", "\344\270\215\347\264\247\346\200\245", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("Addnew", "\351\234\200\350\246\201\346\263\250\346\204\217", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("Addnew", "\346\257\224\350\276\203\347\264\247\346\200\245", nullptr));
        comboBox->setItemText(4, QCoreApplication::translate("Addnew", "\347\253\213\345\215\263\345\212\250\350\272\253", nullptr));
        comboBox->setItemText(5, QCoreApplication::translate("Addnew", "\345\215\263\345\260\206\345\217\221\347\224\237", nullptr));
        comboBox->setItemText(6, QCoreApplication::translate("Addnew", "\350\277\207\346\234\237", nullptr));

        nameLabel->setText(QCoreApplication::translate("Addnew", "\345\220\215\347\247\260(Name)", nullptr));
        Label->setText(QCoreApplication::translate("Addnew", "\345\244\207\346\263\250(Note)", nullptr));
        dateDateEdit->setDisplayFormat(QCoreApplication::translate("Addnew", "yyyy/0M/0d", nullptr));
        pushButton->setText(QCoreApplication::translate("Addnew", "\345\256\214\346\210\220", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Addnew: public Ui_Addnew {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDNEW_H
