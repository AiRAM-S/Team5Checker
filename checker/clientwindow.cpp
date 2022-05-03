#include "clientwindow.h"
#include "ui_clientwindow.h"
#include <QMessageBox>
#include<QPainter>
#include<QPointF>
#include<QDebug>
#include<QLabel>
#include<QFont>
#include"networkdata.h"

#define I 40 //横向间距
#define JX 20
#define JY sqrt(3)*20 //行距
#define R 20
#define RR 34 //棋子半径
#define RRR 24

#define red 0
#define blue 1
#define green 2
#define pink 3
#define purple 4
#define orange 5

void ClientWindow::cbuttonpress()
{
    z = new mydialog1(this) ;//将类指针实例化
    z->show();
}

ClientWindow::ClientWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ClientWindow)
{
    ui->setupUi(this);

    //初始化socket
    socket = new NetworkSocket(new QTcpSocket(),this);

    connect(socket, &NetworkSocket::receive, this, &ClientWindow::receive);
    connect(socket->base(), &QAbstractSocket::disconnected, [=]() {
        QMessageBox::critical(this, tr("Connection lost"), tr("Connection to server has closed"));
    });

    //建立连接
    const QString ip("10.46.156.60");//RUC-WEB
    quint16 port = 9999;//这个port我没搞太懂，，随便写了一个9999
    socket->hello(ip,port);

    //开始界面 设置玩家人数
    myDialog *d = new myDialog;
    d->exec();
    int ifstart=d->Join();
    QString str=d->setplayer->currentText();
        if(str=="2")
            playernum=2;
        else if(str=="3")
            playernum=3;
        else
            playernum=6;
    if(!ifstart)
        exit(0);

    //这行会报错 说没有QUIT成员 有点奇怪 不知道怎么改
    connect(ui->QUIT, SIGNAL(clicked(bool)), this, SLOT(cbuttonpress()));  //弹出退出窗口
    this->setWindowTitle("Client");

    //设置禁止摆烂弹窗
    nobai = new QDialog(this);
    QLabel *lb = new QLabel("禁止摆烂",nobai);
    nobai->setFixedSize(200,100);
    lb->setFont(QFont("Microsoft YaHei",20,75));
    lb->setGeometry(45,25,200,50);
    nobai->hide();

    this->setFixedSize(700,700);
    DrawCheckerboard();
    //初始化部分
        //初始化秒表
        clock1 = new QLabel("剩余时间",this);
        clock1->setFont(QFont("Microsoft YaHei",20));
        clock1->setGeometry(70,500,300,50);
        clock1->setStyleSheet("color:brown;");
        clock1->hide();
        clock2 = new QLabel("30 s",this);
        clock2->setFont(QFont("Agency FB",20));
        clock2->setStyleSheet("color:brown;");
        clock2->setGeometry(70,530,300,50);
        clock2->hide();

        //初始化isfill
        for(int i1=0;i1<17;i1++){
            for(int i2=0;i2<17;i2++){
                isfill[i1][i2]=0;
            }
        }
        for(int i=0;i<playernum;i++){
            isover[i]=false;
        }
        //初始化是否需要更换棋手
        shouldSwitch=false;
        //初始化是否胜利
        iswin=false;
        //记录上一步是否为跳子
        haveJumped=false;
        //初始化游戏结束排名表
        rank = new Rank(this);
        rank->show();


        //初始化棋子 2player
        int k=0;
        if(playernum==2){
            flag = blue;//12点的蓝方先手
            //记录棋手
            nowplayer = new QLabel(this);
            nowplayer->setFont(QFont("Agency FB",24));
            nowplayer->setGeometry(275,0,300,50);
            nowplayer->setText("Player: BLUE");
            nowplayer->setStyleSheet("color:blue;");
        for(int j=5;j<=8;j++){
            for(int i=j-4;i<=4;i++){
                btn[0][k]=new CheckerButton(this);
                btn[0][k]->setGeometry(loc[i+8][-j+8].rx()-RR/2,loc[i+8][-j+8].ry()-RR/2,RR,RR);
                btn[0][k]->setIcon(QPixmap(":/image/red.png"));
                btn[0][k]->setIconSize(QSize(RR,RR));
                btn[0][k]->setFlat(true);
                btn[0][k]->player=red; //set player
                btn[0][k]->x=i+8;
                btn[0][k]->y=-j+8;
                isfill[i+8][-j+8]=red+1;
                btn[1][k]=new CheckerButton(this);
                btn[1][k]->setGeometry(loc[-i+8][j+8].rx()-RR/2,loc[-i+8][j+8].ry()-RR/2,RR,RR);
                btn[1][k]->setIcon(QPixmap(":/image/blue.png"));
                btn[1][k]->setIconSize(QSize(RR,RR));
                btn[1][k]->setFlat(true);
                btn[1][k]->player=blue;//set player
                btn[1][k]->x=-i+8;
                btn[1][k]->y=j+8;
                isfill[-i+8][j+8]=blue+1;
                k++;
            }
        }
        }
        if(playernum==3){
            flag = blue;
            //记录棋手
            nowplayer = new QLabel(this);
            nowplayer->setFont(QFont("Agency FB",24));
            nowplayer->setGeometry(275,0,300,50);
            nowplayer->setText("Player: BLUE");
            nowplayer->setStyleSheet("color:blue;");
            k=0;
            for(int j=5;j<=8;j++){
                for(int i=j-4;i<=4;i++){
                    btn[0][k]=new CheckerButton(this);
                    btn[0][k]->setGeometry(loc[i+8][-j+8].rx()-RR/2,loc[i+8][-j+8].ry()-RR/2,RR,RR);
                    btn[0][k]->setIcon(QPixmap(":/image/red.png"));
                    btn[0][k]->setIconSize(QSize(RR,RR));
                    btn[0][k]->setFlat(true);
                    btn[0][k]->player=red; //set player
                    btn[0][k]->x=i+8;
                    btn[0][k]->y=-j+8;
                    isfill[i+8][-j+8]=red+1;
                    k++;
                }
            }
            k=0;
            for(int i=1; i<5; i++){
                for(int j=-4; j<i-4; j++){
                    btn[1][k]=new CheckerButton(this);
                    btn[1][k]->setGeometry(loc[i+8][-j+8].rx()-RR/2,loc[i+8][-j+8].ry()-RR/2,RR,RR);
                    btn[1][k]->setIcon(QPixmap(":/image/blue.png"));
                    btn[1][k]->setIconSize(QSize(RR,RR));
                    btn[1][k]->setFlat(true);
                    btn[1][k]->player=blue; //set player
                    btn[1][k]->x=i+8;
                    btn[1][k]->y=-j+8;
                    isfill[i+8][-j+8]=blue+1;
                    k++;
                }
            }

            k=0;
            for(int i=5;i<=8;i++){
                for(int j=i-4;j<=4;j++){
                    btn[2][k]=new CheckerButton(this);
                    btn[2][k]->setGeometry(loc[-i+8][j+8].rx()-RR/2,loc[-i+8][j+8].ry()-RR/2,RR,RR);
                    btn[2][k]->setIcon(QPixmap(":/image/green.png"));
                    btn[2][k]->setIconSize(QSize(RRR,RRR));
                    btn[2][k]->setFlat(true);
                    btn[2][k]->player=green; //set player
                    btn[2][k]->x=-i+8;
                    btn[2][k]->y=j+8;
                    isfill[-i+8][j+8]=green+1;
                    k++;
                }
            }
        }
        if(playernum==6){
            flag = pink;
            //记录棋手
            nowplayer = new QLabel(this);
            nowplayer->setFont(QFont("Agency FB",24));
            nowplayer->setGeometry(275,0,300,50);
            nowplayer->setText("Player:PINK");
            nowplayer->setStyleSheet("color:#DB7093;");
            k=0;
            for(int j=5;j<=8;j++){
                for(int i=j-4;i<=4;i++){
                    btn[0][k]=new CheckerButton(this);
                    btn[0][k]->setGeometry(loc[i+8][-j+8].rx()-RR/2,loc[i+8][-j+8].ry()-RR/2,RR,RR);
                    btn[0][k]->setIcon(QPixmap(":/image/red.png"));
                    btn[0][k]->setIconSize(QSize(RR,RR));
                    btn[0][k]->setFlat(true);
                    btn[0][k]->player=red; //set player
                    btn[0][k]->x=i+8;
                    btn[0][k]->y=-j+8;
                    isfill[i+8][-j+8]=red+1;
                    btn[3][k]=new CheckerButton(this);
                    btn[3][k]->setGeometry(loc[-i+8][j+8].rx()-RR/2,loc[-i+8][j+8].ry()-RR/2,RR,RR);
                    btn[3][k]->setIcon(QPixmap(":/image/pink.png"));
                    btn[3][k]->setIconSize(QSize(RRR,RRR));
                    btn[3][k]->setFlat(true);
                    btn[3][k]->player=pink;//set player
                    btn[3][k]->x=-i+8;
                    btn[3][k]->y=j+8;
                    isfill[-i+8][j+8]=pink+1;
                    k++;
                }
            }
            k=0;
            for(int i=1; i<5; i++){
                for(int j=-4; j<i-4; j++){
                    btn[2][k]=new CheckerButton(this);
                    btn[2][k]->setGeometry(loc[i+8][-j+8].rx()-RR/2,loc[i+8][-j+8].ry()-RR/2,RR,RR);
                    btn[2][k]->setIcon(QPixmap(":/image/green.png"));
                    btn[2][k]->setIconSize(QSize(RRR,RRR));
                    btn[2][k]->setFlat(true);
                    btn[2][k]->player=green; //set player
                    btn[2][k]->x=i+8;
                    btn[2][k]->y=-j+8;
                    isfill[i+8][-j+8]=green+1;
                    btn[5][k]=new CheckerButton(this);
                    btn[5][k]->setGeometry(loc[-i+8][j+8].rx()-RR/2,loc[-i+8][j+8].ry()-RR/2,RR,RR);
                    btn[5][k]->setIcon(QPixmap(":/image/orange.png"));
                    btn[5][k]->setIconSize(QSize(RRR,RRR));
                    btn[5][k]->setFlat(true);
                    btn[5][k]->player=orange; //set player
                    btn[5][k]->x=-i+8;
                    btn[5][k]->y=j+8;
                    isfill[-i+8][j+8]=orange+1;
                    k++;
                }
            }
            k=0;
            for(int i=5;i<=8;i++){
                for(int j=i-4;j<=4;j++){
                    btn[4][k]=new CheckerButton(this);
                    btn[4][k]->setGeometry(loc[-i+8][j+8].rx()-RR/2,loc[-i+8][j+8].ry()-RR/2,RR,RR);
                    btn[4][k]->setIcon(QPixmap(":/image/purple.png"));
                    btn[4][k]->setIconSize(QSize(RRR,RRR));
                    btn[4][k]->setFlat(true);
                    btn[4][k]->player=purple; //set player
                    btn[4][k]->x=-i+8;
                    btn[4][k]->y=j+8;
                    isfill[-i+8][j+8]=purple+1;
                    btn[1][k]=new CheckerButton(this);
                    btn[1][k]->setGeometry(loc[i+8][-j+8].rx()-RR/2,loc[i+8][-j+8].ry()-RR/2,RR,RR);
                    btn[1][k]->setIcon(QPixmap(":/image/blue.png"));
                    btn[1][k]->setIconSize(QSize(RR,RR));
                    btn[1][k]->setFlat(true);
                    btn[1][k]->player=blue; //set player
                    btn[1][k]->x=i+8;
                    btn[1][k]->y=-j+8;
                    isfill[i+8][-j+8]=blue+1;
                    k++;
                }
            }
        }

        //建立连接：按下棋子后记录被选中者
        for(int t=0;t<10;t++){
            for(int j=0;j<playernum;j++){
                connect(btn[j][t],&CheckerButton::is_chosen,this,[=](CheckerButton& but){
                    if(flag==but.player&&step==0){
                       chosen.setX(but.pos().rx());
                       chosen.setY(but.pos().ry());
                       chosenloc[0]=but.x;
                       chosenloc[1]=but.y;
                       btnx=but.x;
                       btny=but.y;
                       ischosen=true;
                       checked=&but;
                       qDebug()<<but.x<<' '<<but.y;
                     //  qDebug() << "choose a check";
                   }
                   else{
                       //返回警告
                   }
                });
            }
        }

        //调错用 做完删
        test = new QLabel(this);
        test->setGeometry(0,0,1000,20);
        test->setText("here");
        //初始化回合结束按钮
        end = new QPushButton(this);
        end->setText("回合结束");
        end->setGeometry(293,640,100,50);
        //实现更换执棋方功能
        connect(end,&QPushButton::clicked,this,[=](){
            if(ischange==false&&!(chosenloc[0]==btnx&&chosenloc[1]==btny)){//当没有换过且棋子不在初始位置时换player
                shouldSwitch=true;
                shouldSwitcht2f();
                shouldSwitch=false;
                ischange=true;
                qDebug() << "player changed";
            }
            else if(chosenloc[0]==btnx&&chosenloc[1]==btny){
                nobai->show();
            }
        });

        connect(this,SIGNAL(shouldSwitchChanged()),this,SLOT(changeplayer()));

}
void ClientWindow::shouldSwitcht2f(){
    if(shouldSwitch==true){
        shouldSwitch=false;
        emit shouldSwitchChanged();
    }
}

void ClientWindow::changeplayer(){
    for(int i=0;i<10;i++){
        btn[flag][i]->setCheckable(false);
    }

    flag = (flag+1)%playernum;
    while(isover[flag]){
        flag = (flag+1)%playernum;
    }
    for(int j=0;j<10;j++){
        btn[flag][j]->setCheckable(true);
    }
  
    NetworkData mv(OPCODE::MOVE_OP,QString(myPos),path);
    socket->send(mv);//发送move信号

    switch(flag){
    case red:
        nowplayer->setText("Player:  RED");
        nowplayer->setStyleSheet("color:red;");
        break;
    case blue:
        nowplayer->setText("Player: BLUE");
        nowplayer->setStyleSheet("color:blue;");
        break;
    case green:
        nowplayer->setText("Player:GREEN");
        nowplayer->setStyleSheet("color:green;");
        break;
    case pink:
        nowplayer->setText("Player:PINK");
        nowplayer->setStyleSheet("color:#DB7093;");
        break;
    case purple:
        nowplayer->setText("Player:PURPLE");
        nowplayer->setStyleSheet("color:#800080;");
        break;
      case orange:
        nowplayer->setText("Player:ORANGE");
        nowplayer->setStyleSheet("color:#FF4500;");
        break;
    }
    haveJumped=false;
    ischosen=false;
    isobjset=false;
    checked=NULL;
    jumped=NULL;
    step=0;
    path = QString("");
}

void ClientWindow::paintEvent(QPaintEvent *)
{
    DrawCheckerboard();       //棋盘
    update();          //强制更新界面
}


void ClientWindow::DrawCheckerboard(void)
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
            loc[i+8][-j+8].setX(bp.x()+i*I-j*JX+R/2);
            loc[i+8][-j+8].setY(bp.y()+j*JY+R/2);
        }
    }//左下到右上的菱形
    for(int j=5;j<=8;j++){
        for(int i=j-4;i<=4;i++){
            plot.drawEllipse(bp.x()+i*I-j*JX,bp.y()+j*JY, R, R);
            loc[i+8][-j+8].setX(bp.x()+i*I-j*JX+R/2);
            loc[i+8][-j+8].setY(bp.y()+j*JY+R/2);
            plot.drawEllipse(bp.x()-i*I+j*JX,bp.y()-j*JY, R, R);
            loc[-i+8][j+8].setX(bp.x()-i*I+j*JX+R/2);
            loc[-i+8][j+8].setY(bp.y()-j*JY+R/2);
        }
    }//上下三角形
    for(int i=5;i<=8;i++){
        for(int j=i-4;j<=4;j++){
            plot.drawEllipse(bp.x()+i*I-j*JX,bp.y()+j*JY, R, R);
            loc[i+8][-j+8].setX(bp.x()+i*I-j*JX+R/2);
            loc[i+8][-j+8].setY(bp.y()+j*JY+R/2);
            plot.drawEllipse(bp.x()-i*I+j*JX,bp.y()-j*JY, R, R);
            loc[-i+8][j+8].setX(bp.x()-i*I+j*JX+R/2);
            loc[-i+8][j+8].setY(bp.y()-j*JY+R/2);
        }
    }//左上右下三角形


}

void ClientWindow::mousePressEvent(QMouseEvent *ev){
    //录入obj 并进行棋子移动
    if(ischosen){
          //反映鼠标点击点坐标
//        QString posi = QString("%1,%2").arg(ev->pos().rx()).arg(ev->pos().ry());
//        test->setText(posi);

        //在这里判断所点位置是否在圆圈内，若在圆圈内，则为合法，直接设置目标位置obj
        QPointF td=ev->pos();
        int l=pixel2int(td);
        if((td.rx()-loc[l/17][l%17].rx())*(td.rx()-loc[l/17][l%17].rx())+(td.ry()-loc[l/17][l%17].ry())*(td.ry()-loc[l/17][l%17].ry())>RR*RR/4){
            test->setText("out range");//不合法
        }
        else{
            isobjset=true;//is obj set
            obj.setX(loc[l/17][l%17].rx()-RR/4);
            obj.setY(loc[l/17][l%17].ry()-RR/4);
            objloc[0] = l/17;
            objloc[1] = l%17;
            int mv=islegal();
            if(mv&&isobjset){
                CheckerMove(checked,obj);
                isobjset=false;
                if(mv==1){
                    shouldSwitcht2f();
                }
                else if(mv==2){
                    jumped=checked;
                    chosenloc[0]=objloc[0];
                    chosenloc[1]=objloc[1];
                }
//                if(shouldSwitch){
//                   shouldSwitcht2f();
//                }
//                else{
//                   chosenloc[0]=objloc[0];
//                   chosenloc[1]=objloc[1];
//                }
            }
        }
    }
}

int ClientWindow::islegal(){
    //判断是否已经有选中棋子
    if(!ischosen){
        test->setText("no chosen checker");
        return 0;
    }
    //判断目标点是否为空位
    if(isfill[objloc[0]][objloc[1]]){
        test->setText("object is filled");
        return 0;
    }
    //判断是否平动
    bool flatmove;
    flatmove=(objloc[0]==chosenloc[0]+1&&objloc[1]==chosenloc[1])
            ||(objloc[0]==chosenloc[0]-1&&objloc[1]==chosenloc[1])
            ||(objloc[0]==chosenloc[0]-1&&objloc[1]==chosenloc[1]+1)
            ||(objloc[0]==chosenloc[0]+1&&objloc[1]==chosenloc[1]-1)
            ||(objloc[0]==chosenloc[0]&&objloc[1]==chosenloc[1]+1)
            ||(objloc[0]==chosenloc[0]&&objloc[1]==chosenloc[1]-1);
    if(flatmove&&haveJumped==false){
        ischosen=false;
        shouldSwitch=true;//阻止下一步
        test->setText("flatmove made");
        return 1;
    }

    //判断连跳
    if(haveJumped&&jumped!=checked){
        test->setText("jump checker changed");
        return 0;
    }
    //判断是否为跳跃
    int midloc[2];
    midloc[0]=(objloc[0]+chosenloc[0])/2;
    midloc[1]=(objloc[1]+chosenloc[1])/2;
    if((objloc[0]==chosenloc[0]+2&&objloc[1]==chosenloc[1])
     ||(objloc[0]==chosenloc[0]-2&&objloc[1]==chosenloc[1])
     ||(objloc[0]==chosenloc[0]-2&&objloc[1]==chosenloc[1]+2)
     ||(objloc[0]==chosenloc[0]+2&&objloc[1]==chosenloc[1]-2)
     ||(objloc[0]==chosenloc[0]&&objloc[1]==chosenloc[1]+2)
     ||(objloc[0]==chosenloc[0]&&objloc[1]==chosenloc[1]-2)){
        if(isfill[midloc[0]][midloc[1]]){
            if(!canJump(chosenloc[0],chosenloc[1])){
               shouldSwitch=true;
            }
            else{
                shouldSwitch=false;
            }
            test->setText("jump made");
            haveJumped=true;
            return 2;
        }
    }
    //排查是否可以进行下一次跳跃
    test->setText("undefined move");
    return 0;
}


int ClientWindow::pixel2int(QPointF pixel){
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
    qDebug()<<x<<' '<<y;
    return x*17+y;//进行一个下标的转换
}

void ClientWindow::CheckerMove(CheckerButton*btn,QPointF p){
    QPropertyAnimation *anim = new QPropertyAnimation(btn, "pos", this);
    anim->setDuration(300);
    anim->setStartValue(btn->pos());
    anim->setEndValue(QPointF(p.rx()-R/2+1,p.ry()-R/2+0.5));
    anim->start(QPropertyAnimation::KeepWhenStopped);
    btn->x=objloc[0];
    btn->y=objloc[1];
    isfill[objloc[0]][objloc[1]]=btn->player+1;
    isfill[chosenloc[0]][chosenloc[1]]=0;
    ischange=false;
    step++;

    if(step==1){
        path = QString(QString::number(chosenloc[0]).append(" ").append(QString::number(chosenloc[1])));
    }
    path.append(" ").append(QString::number(objloc[0]).append(" ").append(QString::number(objloc[1])));

    totalstep++;
    if(totalstep>60*playernum){
        isfinish();
    }

}

bool ClientWindow::canJump(int x,int y){//不能跳回原位
    int direction[6][2]={{2,2},{0,2},{-2,0},{-2,-2},{0,-2},{2,0}};
        for(int t=0;t<6;t++){
            int x1 = objloc[0]+direction[t][0];
            int y1 = objloc[1]+direction[t][1];
            if((x1==objloc[0]+2&&y1==objloc[1])
             ||(x1==objloc[0]-2&&y1==objloc[1]+2)
             ||(x1==objloc[0]&&y1==objloc[1]+2)
             ||(x1==objloc[0]-2&&y1==objloc[1])
             ||(x1==objloc[0]+2&&y1==objloc[1]-2)
             ||(x1==objloc[0]&&y1==objloc[1]-2))
                if(isfill[(x1+objloc[0])/2][(y1+objloc[1])/2]&&x1!=x&&y1!=y)
                    return true;

    }
    return false;
}
ClientWindow::~ClientWindow()
{
    delete ui;
}

static int timeLeft=30;

void ClientWindow::receive(NetworkData data){
    switch(data.op){
        case OPCODE::JOIN_ROOM_REPLY_OP://加入房间成功
            players = data.data1.split(" ");//载入已有玩家姓名
            for(int i=0;i<data.data2.length();i++){
                playerState[i]=QString(data.data2.at(i)).toInt();
            }//设置已有玩家状态
            players.append(myName);
            playerState[data.data2.length()] = 0;
        break;
        case OPCODE::LEAVE_ROOM_OP://有其他玩家离开了房间
            players.removeOne(data.data1);
            //这里没有改playerState，我觉得应该影响不大
        break;
        case OPCODE::CLOSE_ROOM_OP://关闭房间 待实现
        break;
        case OPCODE::PLAYER_READY_OP://有玩家准备就绪
            playerState[players.indexOf(data.data1)] = 1;
        break;
        case OPCODE::START_GAME_OP://开始游戏 实现了一半
           {
            QStringList pls = data.data1.split(" ");
            QStringList seq = data.data2.split(" ");
            playernum=data.data2.length();
            for(int i=0;i<playernum;i++){
                players.replace(seq.at(i).toInt()-65,pls.at(i));
            }
            myPos = *(seq.at(pls.indexOf(myName)).toLatin1().data());
            //接下来需要设定 只有己方棋子可动,以及根据data2画棋盘
        }
        break;
        case OPCODE::START_TURN_OP://我的回合开始
            timeLeft=30;
            id=startTimer(1000);
            clock1->show();
            clock2->show();
        break;
        case OPCODE::MOVE_OP://其他玩家移动棋子
            {
                if(data.data2=="-1"){
                    //移除该玩家所有棋子
                    char outpl = data.data1.toLatin1()[0];
                    for(int i=0;i<10;i++){
                        btn[outpl-65][i]->hide();
                    }
                }
                else{
                    QStringList checkerpath = data.data2.split(" ");
                    int stepnum = checkerpath.length()/2-1;
                    int origin[2];
                    origin[0]= checkerpath.at(0).toInt();
                    origin[1]= checkerpath.at(1).toInt();
                    char plnow = data.data1.toLatin1()[0];
                    for(int i=0;i<10;i++){
                        if(btn[plnow-65][i]->x==origin[0]
                           &&btn[plnow-65][i]->y==origin[1]){
                            for(int j=1;j<=stepnum;j++){
                                int aimloc[2];
                                aimloc[0]= checkerpath.at(2*j).toInt();
                                aimloc[1]=checkerpath.at(2*j+1).toInt();
                                QPointF aim;
                                aim.setX(loc[aimloc[0]][aimloc[1]].rx()-RR/4);
                                aim.setY(loc[aimloc[0]][aimloc[1]].ry()-RR/4);
                                CheckerMove(btn[plnow-65][i],aim);
                            }
                        }
                    }
                }
            }
        break;
    case OPCODE::END_TURN_OP://胜利反馈
        iswin=true;
    break;
    case OPCODE::END_GAME_OP://游戏结束
        //弹排名界面
        rank->ranktable->setRowCount(data.data1.length());
        rank->ranktable->setHorizontalHeaderLabels(QStringList("玩家ID"));
        QStringList header;
        for(int i=0;i<data.data1.length();i++){
            if(i==0)
                header << "1st";
            else if(i==1)
                header << "2nd";
            else{
                header << QString("%1th").arg(i);
            }
        }
        rank->ranktable->setVerticalHeaderLabels(header);
        for(int i=0;i<data.data1.length();i++){
            char plnow=data.data1.toLatin1()[i];
            rank->ranktable->setItem(i,0,new QTableWidgetItem(players[plnow-65]));
        }
        //断开连接
        socket->bye();
    }
    break;
    case OPCODE::ERROR_OP://错误
        //迷惑。

}

void ClientWindow::timerEvent(QTimerEvent *event){
    timeLeft--;
    if(timeLeft<0){
        this->killTimer(id);//停止计时
    }
    else{
       clock2->setText(QString("%1 s").arg(timeLeft));
    }
}

void ClientWindow::isfinish(){
    bool flg[6];
    for(int i=0;i<6;i++){
        flg[i]=true;
    }
    if(playernum==2){
        for(int j=5;j<=8;j++){
            for(int i=j-4;i<=4;i++){
                if(!flg[0]&&!flg[1]){
                    break;
                }
                if(isfill[i+8][-j+8]!=blue+1) flg[1]=false;
                if(isfill[-i+8][j+8]!=red+1) flg[0]=false;
            }
            if(!flg[0]&&!flg[1]){
                break;
            }
        }
    }
    if(playernum==3){
        for(int j=5;j<=8;j++){
            for(int i=j-4;i<=4;i++){
                if(!flg[0]){
                    break;
                }
                if(isfill[-i+8][j+8]!=red+1) flg[0]=false;
            }
            if(!flg[0]){
                break;
            }
        }
        for(int i=1; i<5; i++){
            for(int j=-4; j<i-4; j++){
                if(!flg[1]){
                    break;
                }
                if(isfill[-i+8][j+8]!=blue+1) flg[1]=false;
            }
            if(!flg[1]){
                break;
            }
        }
        for(int i=5;i<=8;i++){
            for(int j=i-4;j<=4;j++){
                if(!flg[2]){
                    break;
                }
                if(isfill[i+8][-j+8]!=3) flg[2]=false;
            }
            if(!flg[2]){
                break;
            }
        }
    }
    if(playernum==6){
        for(int j=5;j<=8;j++){
            for(int i=j-4;i<=4;i++){
                if(!flg[0]&&!flg[3]){
                    break;
                }
                if(isfill[i+8][-j+8]!=4) flg[3]=false;
                if(isfill[-i+8][j+8]!=1) flg[0]=false;
            }
            if(!flg[0]&&!flg[3]){
                break;
            }
        }
        for(int i=1; i<5; i++){
            for(int j=-4; j<i-4; j++){
                if(!flg[2]&&!flg[5]){
                    break;
                }
                if(isfill[-i+8][j+8]!=3) flg[2]=false;
                if(isfill[i+8][-j+8]!=6) flg[5]=false;
            }
            if(!flg[2]&&!flg[5]){
                break;
            }
        }
        for(int i=5;i<=8;i++){
            for(int j=i-4;j<=4;j++){
                if(!flg[1]&&!flg[4]){
                    break;
                }
                if(isfill[i+8][-j+8]!=5) flg[4]=false;
                if(isfill[-i+8][j+8]!=2) flg[1]=false;
            }
            if(!flg[1]&&!flg[4]){
                break;
            }
        }
    }
    for(int i=0;i<playernum;i++){
        if(flg[i]){
            emit finish(i);//发出某一方结束信号
            isover[i]=true;
            overnum++;
        }
    }
    if(overnum==playernum){
        emit gameover();//游戏结束信号
    }
}

