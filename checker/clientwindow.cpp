#include "clientwindow.h"
#include "ui_clientwindow.h"
#include <QMessageBox>

ClientWindow::ClientWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ClientWindow)
{
    ui->setupUi(this);

    //初始化socket
    socket = new NetworkSocket(new QTcpSocket(),this);

    connect(socket, &NetworkSocket::receive, this, &ClientWindow::receive);
    connect(socket->base(), &QAbstractSocket::disconnected, [=]() {
        QMessageBox::critical(this, tr("Connection lost"), tr("Connection to server has closed"));
    });

    //建立连接
    const QString ip("10.46.156.60");//RUC-WEB
    quint16 port = 9999;//这个port我没搞太懂，，随便写了一个9999
    socket->hello(ip,port);
}

ClientWindow::~ClientWindow()
{
    delete ui;
}

void ClientWindow::receive(){
    //实现receive槽函数
}
