#include "wait.h"
#include "ui_wait.h"
#include"clientwindow.h"

void Wait::qqq()
{
    QApplication::exit();
}

Wait::Wait(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Wait)
{
    ui->setupUi(this);

    connect(ui->EXIT,SIGNAL(clicked(bool)), this, SLOT(qqq()));
    connect(ui->YES, &QPushButton::clicked, [&]()  //加入游戏并关闭开始窗口
    {
                    ClientWindow *c=new ClientWindow;
                    c->setWindowTitle("client");
                    c->show();
                    ifsuccessed = true;
                    hide();
    });
}

Wait::~Wait()
{
    delete ui;
}
