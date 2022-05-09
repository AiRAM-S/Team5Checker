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
    QString port = h.getPort();
        if(str=="Client")
        {
            ClientWindow *e = new ClientWindow;
            e->hide();
            e->setPort(port);
            //建立连接
            e->getSocket()->hello("127.0.0.1",port.toInt());
            //test
            qDebug() << "client send hello";
            //test end
            e->cc.show();
        }
        else if(str=="Server")
        {
            Widget* w = new Widget;
            w->hide();
            w->setPort(port);
            //开始监听
            w->getServer()->listen(QHostAddress::Any,port.toInt());
            //test
            qDebug() << "start to listen";
            //test end
            //过渡界面显示
            w->ChooseServer->show();
            w->ServerWait->hide();
        }
    return a.exec();
}
