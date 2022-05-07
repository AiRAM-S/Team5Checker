/********************************************************************************
** Form generated from reading UI file 'wait.ui'
**
** Created by: Qt User Interface Compiler version 6.2.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WAIT_H
#define UI_WAIT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Wait
{
public:
    QLineEdit *ID;
    QPushButton *YES;
    QPushButton *EXIT;
    QLabel *A;
    QLabel *B;
    QLabel *C;
    QLabel *D;
    QLabel *E;
    QLabel *F;
    QRadioButton *btn1;
    QRadioButton *btn2;
    QRadioButton *btn3;
    QRadioButton *btn4;
    QRadioButton *btn5;
    QRadioButton *btn6;

    void setupUi(QWidget *Wait)
    {
        if (Wait->objectName().isEmpty())
            Wait->setObjectName(QString::fromUtf8("Wait"));
        Wait->resize(581, 345);
        QFont font;
        font.setPointSize(9);
        font.setBold(false);
        Wait->setFont(font);
        Wait->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 255, 255);"));
        ID = new QLineEdit(Wait);
        ID->setObjectName(QString::fromUtf8("ID"));
        ID->setGeometry(QRect(40, 50, 281, 31));
        QFont font1;
        font1.setPointSize(11);
        font1.setBold(false);
        ID->setFont(font1);
        ID->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        YES = new QPushButton(Wait);
        YES->setObjectName(QString::fromUtf8("YES"));
        YES->setGeometry(QRect(340, 50, 80, 31));
        QFont font2;
        font2.setPointSize(11);
        font2.setBold(true);
        YES->setFont(font2);
        YES->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 255);\n"
"background-color: rgb(255, 255, 255);"));
        EXIT = new QPushButton(Wait);
        EXIT->setObjectName(QString::fromUtf8("EXIT"));
        EXIT->setGeometry(QRect(450, 50, 80, 31));
        EXIT->setFont(font2);
        EXIT->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        A = new QLabel(Wait);
        A->setObjectName(QString::fromUtf8("A"));
        A->setGeometry(QRect(90, 105, 54, 31));
        QFont font3;
        font3.setPointSize(26);
        font3.setBold(true);
        A->setFont(font3);
        A->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 255);"));
        B = new QLabel(Wait);
        B->setObjectName(QString::fromUtf8("B"));
        B->setGeometry(QRect(90, 160, 54, 31));
        B->setFont(font3);
        B->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 255);"));
        C = new QLabel(Wait);
        C->setObjectName(QString::fromUtf8("C"));
        C->setGeometry(QRect(90, 210, 54, 31));
        C->setFont(font3);
        C->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 255);"));
        D = new QLabel(Wait);
        D->setObjectName(QString::fromUtf8("D"));
        D->setGeometry(QRect(320, 100, 54, 31));
        D->setFont(font3);
        D->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 255);"));
        E = new QLabel(Wait);
        E->setObjectName(QString::fromUtf8("E"));
        E->setGeometry(QRect(320, 160, 54, 31));
        E->setFont(font3);
        E->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 255);"));
        F = new QLabel(Wait);
        F->setObjectName(QString::fromUtf8("F"));
        F->setGeometry(QRect(320, 210, 54, 31));
        F->setFont(font3);
        F->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 255);"));
        btn1 = new QRadioButton(Wait);
        btn1->setObjectName(QString::fromUtf8("btn1"));
        btn1->setGeometry(QRect(140, 110, 121, 22));
        QFont font4;
        font4.setPointSize(12);
        font4.setBold(true);
        btn1->setFont(font4);
        btn1->setStyleSheet(QString::fromUtf8(""));
        btn2 = new QRadioButton(Wait);
        btn2->setObjectName(QString::fromUtf8("btn2"));
        btn2->setGeometry(QRect(140, 160, 121, 22));
        btn2->setFont(font4);
        btn3 = new QRadioButton(Wait);
        btn3->setObjectName(QString::fromUtf8("btn3"));
        btn3->setGeometry(QRect(140, 210, 121, 22));
        btn3->setFont(font4);
        btn4 = new QRadioButton(Wait);
        btn4->setObjectName(QString::fromUtf8("btn4"));
        btn4->setGeometry(QRect(370, 110, 121, 22));
        btn4->setFont(font4);
        btn5 = new QRadioButton(Wait);
        btn5->setObjectName(QString::fromUtf8("btn5"));
        btn5->setGeometry(QRect(370, 160, 121, 22));
        btn5->setFont(font4);
        btn6 = new QRadioButton(Wait);
        btn6->setObjectName(QString::fromUtf8("btn6"));
        btn6->setGeometry(QRect(370, 210, 121, 22));
        btn6->setFont(font4);

        retranslateUi(Wait);

        QMetaObject::connectSlotsByName(Wait);
    } // setupUi

    void retranslateUi(QWidget *Wait)
    {
        Wait->setWindowTitle(QCoreApplication::translate("wait", "Form", nullptr));
        ID->setText(QCoreApplication::translate("wait", "\350\257\267\350\276\223\345\205\245\344\275\240\347\232\204\347\224\250\346\210\267\345\220\215...", nullptr));
        YES->setText(QCoreApplication::translate("wait", "\347\241\256 \350\256\244", nullptr));
        EXIT->setText(QCoreApplication::translate("wait", "\351\200\200 \345\207\272", nullptr));
        A->setText(QCoreApplication::translate("wait", "A", nullptr));
        B->setText(QCoreApplication::translate("wait", "B", nullptr));
        C->setText(QCoreApplication::translate("wait", "C", nullptr));
        D->setText(QCoreApplication::translate("wait", "D", nullptr));
        E->setText(QCoreApplication::translate("wait", "E", nullptr));
        F->setText(QCoreApplication::translate("wait", "F", nullptr));
        btn1->setText(QCoreApplication::translate("wait", "GET READY", nullptr));
        btn2->setText(QCoreApplication::translate("wait", "GET READY", nullptr));
        btn3->setText(QCoreApplication::translate("wait", "GET READY", nullptr));
        btn4->setText(QCoreApplication::translate("wait", "GET READY", nullptr));
        btn5->setText(QCoreApplication::translate("wait", "GET READY", nullptr));
        btn6->setText(QCoreApplication::translate("wait", "GET READY", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Wait: public Ui_Wait {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WAIT_H
