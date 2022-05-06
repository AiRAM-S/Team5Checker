#include "widget.h"
#include "clientwindow.h"
#include "mydialog.h"
#include <QApplication>
#include"chooseclient.h"
#include"chooseservice.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    myDialog h;
    h.exec();
    int ifsta=h.Join();
    if(!ifsta)
        return a.exec();
    QString str=h.settype->currentText();
       // if(str=="Client")
        {
            chooseclient *e=new chooseclient;
            e->show();
        }
       // else if(str=="Server")
        {
            chooseservice *v=new chooseservice;
            v->show();
        }
    return a.exec();
}
