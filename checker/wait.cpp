#include "wait.h"
#include "ui_wait.h"
#include<QLabel>
#include<QRadioButton>
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

    /*peo=0;
    this->resize( QSize( 600, 500 ));
    //初始化准备状态，默认为未开始
    for(int i=0;i<6;i++)
        isready[i]=0;
    NAME=new QLineEdit(this);
    NAME->move(130,100);
    NAME->setText("请输入用户名");
    NAME->setStyleSheet("QLineEdit{color:black;font:11px}");

    YES=new QPushButton(this);
    YES->move(450,100);
    YES ->setText(tr("确 认"));
    YES->setStyleSheet("QPushButton {background-color: rgb(255,255,255);color:blue;font:bold 20px;}");

    //设置label的内容
    for(int i=0;i<6;i++)
        num[i]=new QLabel(this);
    num[0]->setText("A");
    num[1]->setText("B");
    num[2]->setText("C");
    num[3]->setText("D");
    num[4]->setText("E");
    num[5]->setText("F");
    int nu=150;
    for(int i=0;i<6;i++)
    {
        num[i]->setStyleSheet("QLabel {color:blue;font:bold 25px;}");
        num[i]->move(200,nu);
        nu+=50;
    }
    //初始化，进入房间时默认未准备
    nu=150;
    for(int i=0;i<6;i++)
    {
        ready[i]=new QRadioButton(tr("GET READY"));
        ready[i]->setStyleSheet("QRadioButton{color:blue;font:bold 20px;}");
        ready[i]->setChecked(0);
        ready[i]->move(240,nu);
        nu+=50;
    }
    connect(YES, &QPushButton::clicked, [&]()  //加入游戏并关闭开始窗口
    {
            hide();
    });*/
    ui->ID->setText("请输入你的用户名...");
    ui->btn1->setChecked(0);
    ui->btn2->setChecked(0);
    ui->btn3->setChecked(0);
    ui->btn4->setChecked(0);
    ui->btn5->setChecked(0);
    ui->btn6->setChecked(0);
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
