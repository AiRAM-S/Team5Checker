#include "widget.h"
#include "clientwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.setWindowTitle("server");
    w.show();

    ClientWindow c;
    c.setWindowTitle("client");
    c.show();
    return a.exec();
}
