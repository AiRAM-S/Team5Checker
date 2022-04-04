#include "widget.h"
#include "ui_widget.h"
#include<QPainter>
#include<QPointF>
#include<QDebug>
#define I 40 //横向间距
#define JX 20
#define JY sqrt(3)*20 //行距
#define R 20
#define RR 34 //棋子半径

#define red 0
#define blue 1
#define green 2
#define yellow 3
#define purple 4
#define orange 5

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setFixedSize(700,700);
    DrawCheckerboard();

    //初始化loc，如果是没有棋子的点就先赋为（0，0）吧，或者我们可以重新写一个数组来存是否有棋子
    for(int i1=0;i1<17;i1++){
        for(int i2=0;i2<17;i2++){
            loc[i1][i2].setX(0);
            loc[i1][i2].setY(0);
        }
    }

    playernum=2;//先实现1v1
    //红方先手
    flag=red;


    //建立连接：按下棋子后记录被选中者
    for(int t=0;t<10;t++){
        for(int j=0;j<playernum;j++){
            connect(btn[j][t],&CheckerButton::is_chosen,this,[=](CheckerButton& but){
               if(flag==but.player){
                   chosen.setX(but.x+17);
                   chosen.setY(but.y+17);
                   ischosen=true;
               }
            });
        }
    }

    //在左上角反映坐标 全部做完以后删
    test = new QLabel(this);
    test->setGeometry(0,0,100,20);
    test->setText("here");

    //初始化回合结束按钮
    end = new QPushButton(this);
    end->setText("回合结束");
    end->setGeometry(293,640,100,50);
    //更换执棋方
    connect(end,&QPushButton::clicked,this,[=](){
        flag = (flag+1)%playernum;
    });

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
    plot.setPen(QPen(QColor(Qt::gray), 3));                        //给边框绘制颜色，灰色，线宽3
    plot.setBrush(Qt::transparent);
    QPointF bp(330,330);                                    //set beginning point
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

            btn[0][k]=new CheckerButton(this);
            btn[0][k]->setGeometry(loc[i+8][j+8].x()-R/4,loc[i+8][j+8].y()-R/4,RR,RR);
            btn[0][k]->setIcon(QPixmap(":/image/red.png"));
            btn[0][k]->setIconSize(QSize(RR,RR));
            btn[0][k]->setFlat(true);
            btn[0][k]->player=red; //set player
            btn[1][k]=new CheckerButton(this);
            btn[1][k]->setGeometry(loc[-i+8][-j+8].x()-R/4,loc[-i+8][-j+8].y()-R/4,RR,RR);
            btn[1][k]->setIcon(QPixmap(":/image/blue.png"));
            btn[1][k]->setIconSize(QSize(RR,RR));
            btn[1][k]->setFlat(true);
            btn[1][k]->player=blue;//set player
            k++;
        }
    }

}

void Widget::mousePressEvent(QMouseEvent *ev){
    QString posi = QString("%1,%2").arg(ev->pos().rx()).arg(ev->pos().ry());
    test->setText(posi);
}

bool Widget::islegal(){
    //判断是否已经有选中棋子
    if(!ischosen)
        return false;
    //判断目标点是否为空位
    if(loc[chosenloc[0]][chosenloc[1]]=QPoint(0,0))
        return false;
    //判断是否平动
    bool flatmove;
    flagmove=((obj.rx()==chosen.rx()+40)&&obj.ry()==chosen.ry())||((obj.rx()==chosen.rx()-40)&&obj.ry()==chosen.ry())||((obj.rx()==chosen.rx()+20)&&(obj.ry()==chosen.ry+JY))||((obj.rx()==chosen.rx()+20)&&(obj.ry()==chosen.ry()-JY))||((obj.rx()==chosen.rx()-20)&&(obj.ry()==chosen.ry()+JY))||((obj.rx()==chosen.rx()-20)&&(obj.ry==chosen.ry()-JY));
    if(flatmove){
        chosen=false;//阻止下一步
        return true;
    }
    //判断是否为跳跃(这一块就比较乱了，等把下面两个转换函数实现了应该就比较清楚了，如果写到这里相关的内容可以踹我一起讨论）
    //（这里主要是记一下大概框架和思路）
    bool jumpmove=false;
    if(fabs(obj.rx()-chosen.rx())==20&&fabs(obj.ry()-chosen.ry())==JY){
        if(loc[pixel2int((chosen+obj)/2).rx()][loc[pixel2int((chosen+obj)/2).ry()]]!=QPoint(0,0))
            jumpmove=true;
    }
    else if(fabs(obj.rx()-chosen.rx())==40){
        if(obj.ry()==chosen.ry()){
            if(loc[pixel2int((chosen+obj)/2).rx()][loc[pixel2int((chosen+obj)/2).ry()]]!=QPoint(0,0))
                jumpmove=true;
        }
    }
}

void int2pixel(){

}

QPoint pixel2int(QPointF& pixel){

}
