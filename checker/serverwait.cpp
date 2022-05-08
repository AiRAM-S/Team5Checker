#include "serverwait.h"
#include "ui_serverwait.h"
#include"widget.h"

serverwait::serverwait(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::serverwait)
{
    ui->setupUi(this);

    b=new QPushButton(this);
    b->move(450,50);
    b->setText("ok");

    connect(b, &QPushButton::clicked, [&]()  //加入游戏并关闭开始窗口
    {

                    Widget *c=new Widget;
                    c->setWindowTitle("server");
                    c->show();
                    hide();
    });
}

serverwait::~serverwait()
{
    delete ui;
}
