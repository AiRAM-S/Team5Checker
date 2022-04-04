#include "widget.h"
#include "ui_widget.h"
#include<QPainter>
#include<QPointF>
#include<QDebug>
#define I 40 //横向间距
#define JX 20
#define JY sqrt(3)*20 //行距
#define R 20
#define RR 35 //棋子半径

#define red 0
#define blue 1
#define green 2
#define yellow 3

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setFixedSize(700,700);
    DrawCheckerboard();
    flag=red;

    for(int t=0;t<10;t++){
        connect(rbtn[t],&CheckerButton::is_chosen,this,[=](CheckerButton& but){
           chosen.setX(but.x);
           chosen.setY(but.y);
           ischosen=true;
        });
        connect(bbtn[t],&CheckerButton::is_chosen,this,[=](CheckerButton& but){
           chosen.setX(but.x);
           chosen.setY(but.y);
           ischosen=true;
        });
    }

    test = new QLabel(this);
    test->setGeometry(0,0,100,20);
    test->setText("here");
}

Widget::~Widget()
{
    delete ui;
}
void Widget::paintEvent(QPaintEvent *)
{
    DrawCheckerboard();       //棋盘
   // InitCheckerboard();
   // update();          //强制更新界面
}


void Widget::DrawCheckerboard(void)
{
    QPainter plot(this);
    plot.setRenderHint(QPainter::Antialiasing, true);    //防止棋盘变形
    plot.setPen(QPen(QColor(Qt::black), 3));                        //给边框绘制颜色，黑色，线宽3
    plot.setBrush(Qt::transparent);
    QPointF bp(330,330);                                    //set beginning point, I guess
    //绘制棋盘所有的格子
    for(int i=-4; i<5; i++)
    {
        for(int j=-4; j<5; j++)
        {
            plot.drawEllipse(bp.x()+i*I-j*JX,bp.y()+j*JY, R, R);
            loc[i+8][j+8].setX(bp.x()+i*I-j*JX);
            loc[i+8][j+8].setY(bp.y()+j*JY);
        }
    }//左上到右下的菱形
    for(int j=5;j<=8;j++){
        for(int i=j-4;i<=4;i++){
            plot.drawEllipse(bp.x()+i*I-j*JX,bp.y()+j*JY, R, R);
            loc[i+8][j+8].setX(bp.x()+i*I-j*JX);
            loc[i+8][j+8].setY(bp.y()+j*JY);
            plot.drawEllipse(bp.x()-i*I+j*JX,bp.y()-j*JY, R, R);
            loc[-i+8][-j+8].setX(bp.x()-i*I+j*JX);
            loc[-i+8][-j+8].setY(bp.y()-j*JY);
        }
    }
    for(int i=5;i<=8;i++){
        for(int j=i-4;j<=4;j++){
            plot.drawEllipse(bp.x()+i*I-j*JX,bp.y()+j*JY, R, R);
            loc[i+8][j+8].setX(bp.x()+i*I-j*JX);
            loc[i+8][j+8].setY(bp.y()+j*JY);
            plot.drawEllipse(bp.x()-i*I+j*JX,bp.y()-j*JY, R, R);
            loc[-i+8][-j+8].setX(bp.x()-i*I+j*JX);
            loc[-i+8][-j+8].setY(bp.y()-j*JY);
        }
    }
    int k=0;
    for(int j=5;j<=8;j++){
        for(int i=j-4;i<=4;i++){

            rbtn[k]=new CheckerButton(this);
            rbtn[k]->setGeometry(loc[i+8][j+8].x()-R/4,loc[i+8][j+8].y()-R/4,RR,RR);
            rbtn[k]->setIcon(QPixmap(":/image/red.png"));
            rbtn[k]->setIconSize(QSize(RR,RR));
            rbtn[k]->setFlat(true);
            rbtn[k]->player=red; //set player
            bbtn[k]=new CheckerButton(this);
            bbtn[k]->setGeometry(loc[-i+8][-j+8].x()-R/4,loc[-i+8][-j+8].y()-R/4,RR,RR);
            bbtn[k]->setIcon(QPixmap(":/image/blue.png"));
            bbtn[k]->setIconSize(QSize(RR,RR));
            bbtn[k]->setFlat(true);
            bbtn[k]->player=blue;//set player
            k++;
        }
    }

}

void Widget::mousePressEvent(QMouseEvent *ev){
    QString posi = QString("%1,%2").arg(ev->pos().rx()).arg(ev->pos().ry());
    test->setText(posi);
}
