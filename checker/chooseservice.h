#ifndef CHOOSESERVICE_H
#define CHOOSESERVICE_H

#include <QWidget>
#include<QTcpServer>
#include<QTcpSocket>
#include"widget.h"
class QPushButton;
class QLabel;
class QLineEdit;

class chooseservice:public QWidget
{
public:
    chooseservice(QWidget *parent = nullptr);
    ~chooseservice();

private:
    QTcpServer* service; //监听
    QTcpSocket* commun;   //通信
    QLabel *IP;
    QLabel *PORT;
    QPushButton *YES;
    QLineEdit *IPS;
    QLineEdit *PORTS;
    Widget* w;
};

#endif // CHOOSESERVICE_H
