//move成功以后记得把ischosen改成false 虽然我不记得为什么要写这个了 提醒自己一下
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


    //初始化部分
    //初始化isfill


    for(int i1=0;i1<17;i1++){
        for(int i2=0;i2<17;i2++){
            isfill[i1][i2]=false;
        }
    }
    //初始化是否需要更换棋手
    shouldSwitch=false;

    //初始化棋子 2player
    int k=0;
    for(int j=5;j<=8;j++){
        for(int i=j-4;i<=4;i++){
            btn[0][k]=new CheckerButton(this);
            btn[0][k]->setGeometry(loc[i+8][j+8].x()-R/4,loc[i+8][j+8].y()-R/4,RR,RR);
            btn[0][k]->setIcon(QPixmap(":/image/red.png"));
            btn[0][k]->setIconSize(QSize(RR,RR));
            btn[0][k]->setFlat(true);
            btn[0][k]->player=red; //set player
            btn[0][k]->x=i+8;
            btn[0][k]->y=j+8;
            isfill[i+8][j+8]=true;
            btn[1][k]=new CheckerButton(this);
            btn[1][k]->setGeometry(loc[-i+8][-j+8].x()-R/4,loc[-i+8][-j+8].y()-R/4,RR,RR);
            btn[1][k]->setIcon(QPixmap(":/image/blue.png"));
            btn[1][k]->setIconSize(QSize(RR,RR));
            btn[1][k]->setFlat(true);
            btn[1][k]->player=blue;//set player
            btn[1][k]->x=-i+8;
            btn[1][k]->y=-j+8;
            isfill[-i+8][-j+8]=true;
            k++;
        }
    }

    //先实现1v1
    playernum=2;
    //红方先手
    flag=red;

    //建立连接：按下棋子后记录被选中者
    for(int t=0;t<10;t++){
        for(int j=0;j<playernum;j++){
            connect(btn[j][t],&CheckerButton::is_chosen,this,[=](CheckerButton& but){
               if(flag==but.player){
                   chosen.setX(but.pos().rx());
                   chosen.setY(but.pos().ry());
                   chosenbtn=btn[j][t];
                   chosenloc[0]=but.x;
                   chosenloc[1]=but.y;
                   ischosen=true;
                   checked=&but;
               }
               else{
                   //返回警告
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
    //实现更换执棋方功能
    connect(end,&QPushButton::clicked,this,[=](){
        flag = (flag+1)%playernum;
        shouldSwitch=false;
    });


}
Widget::~Widget()
{
    delete ui;
}
void Widget::paintEvent(QPaintEvent *)
{
    DrawCheckerboard();       //棋盘
   // update();          //强制更新界面
}


void Widget::DrawCheckerboard(void)
{
    QPainter plot(this);
    plot.setRenderHint(QPainter::Antialiasing, true);    //防止棋盘变形
    plot.setPen(QPen(QColor(Qt::gray), 3));                        //给边框绘制颜色，灰色，线宽3
    plot.setBrush(Qt::transparent);
    QPointF bp(330,330);                                    //set base point原点
    //绘制棋盘所有的格子
    for(int i=-4; i<5; i++)
    {
        for(int j=-4; j<5; j++)
        {
            plot.drawEllipse(bp.x()+i*I-j*JX,bp.y()+j*JY, R, R);
            loc[i+8][j+8].setX(bp.x()+i*I-j*JX);
            loc[i+8][j+8].setY(bp.y()+j*JY);
        }
    }//左下到右上的菱形
    for(int j=5;j<=8;j++){
        for(int i=j-4;i<=4;i++){
            plot.drawEllipse(bp.x()+i*I-j*JX,bp.y()+j*JY, R, R);
            loc[i+8][j+8].setX(bp.x()+i*I-j*JX);
            loc[i+8][j+8].setY(bp.y()+j*JY);
            plot.drawEllipse(bp.x()-i*I+j*JX,bp.y()-j*JY, R, R);
            loc[-i+8][-j+8].setX(bp.x()-i*I+j*JX);
            loc[-i+8][-j+8].setY(bp.y()-j*JY);
        }
    }//上下三角形
    for(int i=5;i<=8;i++){
        for(int j=i-4;j<=4;j++){
            plot.drawEllipse(bp.x()+i*I-j*JX,bp.y()+j*JY, R, R);
            loc[i+8][j+8].setX(bp.x()+i*I-j*JX);
            loc[i+8][j+8].setY(bp.y()+j*JY);
            plot.drawEllipse(bp.x()-i*I+j*JX,bp.y()-j*JY, R, R);
            loc[-i+8][-j+8].setX(bp.x()-i*I+j*JX);
            loc[-i+8][-j+8].setY(bp.y()-j*JY);
        }
    }//左上右下三角形


}

void Widget::mousePressEvent(QMouseEvent *ev){

//    QString posi = QString("%1,%2").arg(ev->pos().rx()).arg(ev->pos().ry());
//    test->setText(posi);
    //录入obj 并进行棋子移动
    if(ischosen){

        QString posi = QString("%1,%2").arg(ev->pos().rx()).arg(ev->pos().ry());
        test->setText(posi);

        QPointF td=ev->pos();
        int l=pixel2int(td);
        if((td.rx()-loc[l/17][l%17].rx())*(td.rx()-loc[l/17][l%17].rx())+(td.ry()-loc[l/17][l%17].ry())*(td.ry()-loc[l/17][l%17].ry())>R){
            test->setText("here1");//不合法
        }
        else{
            obj=loc[l/17][l%17];
        }
        //在这里判断所点位置是否在圆圈内，若在圆圈内，则为合法，直接设置目标位置obj
        objloc[0] = pixel2int(ev->position())/17;
        objloc[1] = pixel2int(ev->position())%17;
            if(islegal()){
                CheckerMove(checked,obj);
                isfill[objloc[0]][objloc[1]]=true;
                isfill[chosenloc[0]][chosenloc[1]]=false;
                if(shouldSwitch){
                    flag = (flag+1)%playernum;
                    shouldSwitch=false;
                    for(int t=0;t<10;t++)
                        btn[flag][t]->setCheckable(true);
                }
                else{
                    chosenloc[0]=objloc[0];
                    chosenloc[1]=objloc[1];
                    //禁止选中刚才没跳的棋子
                    for(int t=0;t<10;t++){
                        if(&btn[flag][t]!=&checked){
                            btn[flag][t]->setCheckable(false);
                        }
                    }
                }
            }
        }
    
}



bool Widget::islegal(){
    //判断是否已经有选中棋子
    if(!ischosen){
        return false;
    }
    //判断目标点是否为空位
    if(isfill[objloc[0]][objloc[1]]==true){
        return false;
    }
    //判断是否平动
    bool flatmove;
    flatmove=(objloc[0]==chosenloc[0]+1&&objloc[1]==chosenloc[1])
            ||(objloc[0]==chosenloc[0]-1&&objloc[1]==chosenloc[1])
            ||(objloc[0]==chosenloc[0]+1&&objloc[1]==chosenloc[1]+1)
            ||(objloc[0]==chosenloc[0]-1&&objloc[1]==chosenloc[1]-1)
            ||(objloc[0]==chosenloc[0]&&objloc[1]==chosenloc[1]+1)
            ||(objloc[0]==chosenloc[0]&&objloc[1]==chosenloc[1]-1);
    if(flatmove){
        ischosen=false;
        shouldSwitch=true;//阻止下一步
        return true;
    }

    //判断是否为跳跃
    bool jumpmove=false;
    int midloc[2];
    midloc[0]=(objloc[0]+chosenloc[0])/2;
    midloc[1]=(objloc[1]+chosenloc[1])/2;
    if((objloc[0]==chosenloc[0]+2&&objloc[1]==chosenloc[1])
     ||(objloc[0]==chosenloc[0]-2&&objloc[1]==chosenloc[1])
     ||(objloc[0]==chosenloc[0]+2&&objloc[1]==chosenloc[1]+2)
     ||(objloc[0]==chosenloc[0]-2&&objloc[1]==chosenloc[1]-2)
     ||(objloc[0]==chosenloc[0]&&objloc[1]==chosenloc[1]+2)
     ||(objloc[0]==chosenloc[0]&&objloc[1]==chosenloc[1]-2)){
        if(isfill[midloc[0]][midloc[1]])


            jumpmove=true;
    }
    //排查是否可以进行下一次跳跃
    if(!canJump()){
       shouldSwitch=true;
    }
    else{
        shouldSwitch=false;
    }
   // if()
    return jumpmove;
}


int Widget::pixel2int(QPointF pixel){
    int x=0,y=0;
    double d=(loc[0][0].rx()-pixel.rx())*(loc[0][0].rx()-pixel.rx())+(loc[0][0].ry()-pixel.ry())*(loc[0][0].ry()-pixel.ry());
    for(int i=0;i<17;i++){
        for(int j=0;j<17;j++){
            if(loc[i][j].isNull()==false){
                if(d>(loc[i][j].rx()-pixel.rx())*(loc[i][j].rx()-pixel.rx())+(loc[i][j].ry()-pixel.ry())*(loc[i][j].ry()-pixel.ry())){
                    x=i;
                    y=j;
                    d=(loc[i][j].rx()-pixel.rx())*(loc[i][j].rx()-pixel.rx())+(loc[i][j].ry()-pixel.ry())*(loc[i][j].ry()-pixel.ry());
                }
            }
        }
    }
    return x*17+y;//进行一个下标的转换
}

void Widget::CheckerMove(CheckerButton*btn,QPointF p){
    QPropertyAnimation *anim = new QPropertyAnimation(btn, "pos", this);

    anim->setDuration(1000);
    anim->setStartValue(btn->pos());
    anim->setEndValue(QPointF(p.rx(),p.ry()));
    anim->start(QPropertyAnimation::KeepWhenStopped);

}

bool Widget::canJump(){
    int direction[6][2]={{2,2},{0,2},{-2,0},{-2,-2},{0,-2},{2,0}};
    for(int s=0;s<10;s++){
        for(int t=0;t<6;t++){
            int x1 = objloc[0]+direction[t][0];
            int y1 = objloc[1]+direction[t][1];
            if((x1==objloc[0]+2&&y1==objloc[1])
             ||(x1==objloc[0]+2&&y1==objloc[1]+2)
             ||(x1==objloc[0]&&y1==objloc[1]+2)
             ||(x1==objloc[0]-2&&y1==objloc[1])
             ||(x1==objloc[0]-2&&y1==objloc[1]-2)
             ||(x1==objloc[0]&&y1==objloc[1]-2)){
                if(isfill[(x1+objloc[0])/2][(y1+objloc[1])/2])
                    return true;
            }
        }
    }
    return false;
}
