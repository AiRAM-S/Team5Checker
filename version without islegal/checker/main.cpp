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
       if(str=="Server")
        {
            Widget* w = new Widget;
            w->hide();
            w->setPort(port);
            //w->initializeChecker(h.setplayer->currentText().toInt());
            //开始监听
            w->server->listen(QHostAddress::Any,18888);
            //test
            qDebug() << "start to listen:" << port.toInt();
            //test end
            //过渡界面显示
            w->ChooseServer->show();
            w->ServerWait->hide();
        }
        else if(str=="Client")
        {

            ClientWindow *e = new ClientWindow;
            qDebug() << "point 1";
            e->hide();
            e->setPort(port);
            //建立连接
            QString ip_address;
            QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
            for (int i = 0; i < ipAddressesList.size(); ++i)
            {
                if (ipAddressesList.at(i) != QHostAddress::LocalHost &&  ipAddressesList.at(i).toIPv4Address())
                {
                    ip_address = ipAddressesList.at(i).toString();
                    qDebug()<<ip_address;  //debug
                    //break;
                }
            }
            if (ip_address.isEmpty())
                ip_address = QHostAddress(QHostAddress::LocalHost).toString();

            e->getSocket()->hello("127.0.0.1",18888);
            //test
            qDebug() << "client send hello:" << port;
            //test end
            e->cc.show();

            ClientWindow *e2 = new ClientWindow;
            qDebug() << "point 1";
            e2->hide();
            e2->setPort(port);
            //建立连接
            e2->getSocket()->hello("127.0.0.1",18888);
            //test
            qDebug() << "client send hello:" << port;
            //test end
            e2->cc.show();
        }
    return a.exec();
}
