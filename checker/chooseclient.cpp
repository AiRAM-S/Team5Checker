#include "chooseclient.h"

#include<QApplication>
#include<QPushButton>
#include<QLabel>
#include<QMessageBox>
#include<QLineEdit>
#include"wait.h"

chooseclient::chooseclient(QWidget *parent) :
    QWidget(parent)
{
    //初始化
    /*client = new QTcpSocket(this);
    ui->IPS->setText("127.0.0.1");
    ui->PORTS->setText("9999");
    //连接服务器
    client->connectToHost(QHostAddress(ui->IPS->text()),ui->PORTS->text().toInt());*/

    this->resize( QSize( 400, 252 ));
    //setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    //quit=new QPushButton(this);
    QPalette palette ;
    palette.setColor(QPalette::Window,QColor("#f8f8ff"));
    this->setAutoFillBackground(true);
    this->setPalette(palette);

    IP=new QLabel(this);
    IP->move(50,70);
    IP->setText("IP");
    IP->setStyleSheet("QLabel {color:black;font:bold 11px;}");

    PORT=new QLabel(this);
    PORT->move(50,120);
    PORT->setText("Port");
    PORT->setStyleSheet("color:black;font:bold 11px;}");

    IPS=new QLineEdit(this);
    IPS->move(110,70);
    IPS->setText("");
    IPS->setStyleSheet("QLineEdit{color:black;font:11px}");

    PORTS=new QLineEdit(this);
    PORTS->move(110,120);
    PORTS->setText("");
    PORTS->setStyleSheet("QLineEdit{color:black;font:11px}");

    YES=new QPushButton(this);
    YES->move(160,180);
    YES->setText(tr("确 认"));
    YES->setStyleSheet("QPushButton {background-color: rgb(255,255,255);color:blue;font:bold 12px;}");

    connect(YES,&QPushButton::clicked,[&]()
            {
        Wait *d=new Wait;
        d->setWindowTitle("waiting");
        d->show();
        int ifs=d->Join();
        if(ifs)
            exit(0);
                    hide();
            });

}
chooseclient::~chooseclient()
{

}
