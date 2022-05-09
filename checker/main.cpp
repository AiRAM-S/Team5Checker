#include "widget.h"
#include "clientwindow.h"
#include "mydialog.h"
#include <QApplication>
#include"chooseclient.h"
#include"chooseservice.h"
#include<QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    myDialog h;
    h.exec();
    int ifsta=h.Join();
    if(!ifsta)
        return a.exec();
    QString str=h.settype->currentText();
    QString port = h.port;
    qDebug() << "debug: port is";
    qDebug() << port.toInt();
        //if(str=="Server")
        //{
            Widget* w = new Widget;
            w->hide();
            w->setPort(port);
            //开始监听
            w->server->listen(QHostAddress::Any,port.toInt());
            //test
            qDebug() << "start to listen:" << port.toInt();
            //test end
            //过渡界面显示
            w->ChooseServer->show();
            w->ServerWait->hide();
        //}
        //else if(str=="Client")
        //{

            ClientWindow *e = new ClientWindow;
            qDebug() << "point 1";
            e->hide();
            e->setPort(port);
            //建立连接
            e->getSocket()->hello("127.0.0.1",port.toInt());
            //test
            qDebug() << "client send hello:" << port;
            //test end
            e->cc.show();

        //}
    return a.exec();
}
