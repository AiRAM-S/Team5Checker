#ifndef CHOOSECLIENT_H
#define CHOOSECLIENT_H

#include <QWidget>
#include<QTcpSocket>
class QPushButton;
class QLabel;
class QLineEdit;

class chooseclient:public QWidget
{
public:
    chooseclient(QWidget *parent = nullptr);
    ~chooseclient();

private:
    QTcpSocket* client;
    QLabel *IP;
    QLabel *PORT;
    QPushButton *YES;
    QLineEdit *IPS;
    QLineEdit *PORTS;
};

#endif // CHOOSECLIENT_H
