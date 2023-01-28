/********************************************************************************
** Form generated from reading UI file 'about.ui'
**
** Created by: Qt User Interface Compiler version 5.14.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUT_H
#define UI_ABOUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_About
{
public:
    QGridLayout *gridLayout;
    QLabel *label;

    void setupUi(QDialog *About)
    {
        if (About->objectName().isEmpty())
            About->setObjectName(QString::fromUtf8("About"));
        About->resize(326, 187);
        gridLayout = new QGridLayout(About);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(About);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label, 0, 0, 1, 1);


        retranslateUi(About);

        QMetaObject::connectSlotsByName(About);
    } // setupUi

    void retranslateUi(QDialog *About)
    {
        About->setWindowTitle(QCoreApplication::translate("About", "\345\205\263\344\272\216", nullptr));
        label->setText(QCoreApplication::translate("About", "\350\277\231\346\230\257\347\211\210\346\234\254\350\257\264\346\230\216\357\274\232\n"
"\347\211\210\346\234\254\357\274\2320.3 \n"
"\351\207\207\347\224\250\344\272\206\344\270\200\344\270\252\347\252\227\345\217\243\346\235\245\346\224\266\347\272\263\345\216\206\345\217\262\350\256\260\345\275\225\n"
"\345\256\236\347\216\260\344\272\206\346\267\273\345\212\240\347\225\214\351\235\242\345\206\231\345\205\245\346\226\207\346\241\243\347\232\204\346\223\215\344\275\234\n"
"\345\256\236\347\216\260\344\272\206\350\257\273\346\226\207\344\273\266\347\232\204\346\223\215\344\275\234\357\274\210\350\231\275\347\204\266\345\217\252\350\203\275\350\257\273\346\234\200\345\220\216\344\270\200\350\241\214\357\274\211\n"
"", nullptr));
    } // retranslateUi

};

namespace Ui {
    class About: public Ui_About {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUT_H
