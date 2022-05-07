#ifndef CHOOSECLIENT_H
#define CHOOSECLIENT_H

#include <QWidget>
#include<QTcpSocket>
#include<QString>
#include<QHostAddress>
#include<QNetworkInterface>
class QPushButton;
class QLabel;
class QLineEdit;

class chooseclient:public QWidget
{
public:
    chooseclient(QWidget *parent = nullptr);
    ~chooseclient();
    QHostAddress ips;
    QString ip;
    QString port;
    QString id;
    QString read_ip_address();
private:
    //QTcpSocket* client;
    QLabel *IP;
    QLabel *PORT;
    QLabel *ID;
    QPushButton *YES;
    QLineEdit *IPS;
    QLineEdit *PORTS;
    QLineEdit *IDS;
};

#endif // CHOOSECLIENT_H
