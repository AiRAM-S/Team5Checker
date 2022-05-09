#include "clientwindow.h"
#include "ui_clientwindow.h"
#include <QMessageBox>
#include<QPainter>
#include<QPointF>
#include<QDebug>
#include<QLabel>
#include<QFont>
#include"networkdata.h"
#include"chooseclient.h"


#define I 40 //横向间距
#define JX 20
#define JY sqrt(3)*20 //行距
#define R 20
#define RR 34 //棋子半径
#define RRR 24

#define red 3
#define blue 2
#define green 1
#define pink 0
#define purple 5
#define orange 4

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

    //passit1(dd.port);
    passit2(cc.room,cc.id);


    //初始化socket
    socket = new NetworkSocket(new QTcpSocket(),this);
    connect(socket, &NetworkSocket::receive, this, &ClientWindow::receive);
    connect(socket->base(), &QAbstractSocket::disconnected, [=]() {
        QMessageBox::critical(this, tr("Connection lost"), tr("Connection to server has closed"));
    });

    //页面2：输入roomid和用户名 发送加入房间信号
    connect(this->cc.getYES(),&QPushButton::clicked,this,[=](){
       this->RoomID = cc.getRoomID();
       this->PlName = cc.getName();
        socket->send(NetworkData(OPCODE::JOIN_ROOM_OP,RoomID,PlName));
        //test
        qDebug() << PlName << " send JOIN_ROOM_OP of " << RoomID;
        //test end
    });

    //页面3：等待界面，ready按钮功能实现
    connect(ww.rea,&QPushButton::clicked,this,[=](){
        NetworkData sure(OPCODE::PLAYER_READY_OP,PlName,"");
        socket->send(sure);
        qDebug() << PlName << " says he is ready";
    });

    //开始界面 设置玩家人数
   /* myDialog *d = new myDialog;
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
        exit(0);*/

    playernum=2;

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
        if(overnum==playernum)
        rank->show();
        rank->hide();


        initializeChecker(QString("data2"));//这一处最后应该是需要删掉的

        //建立连接：按下棋子后记录被选中者
        for(int t=0;t<10;t++){
            for(int j=0;j<2;j++){
                qDebug() << "debug:j = " << j;
                qDebug() << "debug: t = " << t;
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
                     //  qDebug()<<but.x<<' '<<but.y;
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
//                shouldSwitch=true;
//                shouldSwitcht2f();
//                shouldSwitch=false;
//                ischange=true;
//                qDebug() << "player changed";
                NetworkData mv(OPCODE::MOVE_OP,QString(myPos),path);
                socket->send(mv);//发送move信号
                //test
                qDebug() << "client send MOVE_OP ";
                qDebug() << "path is " << path;
                //test end
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
//    Su:我觉得flag的修改可以不用客户端自己来，当客户端接收到服务端的行棋信号时，根据信号内容修改即可
    flag = (flag+1)%playernum;
    while(isover[flag]){
        flag = (flag+1)%playernum;
    }
    if(place2num(myPos)==flag)
    for(int j=0;j<10;j++){
        btn[flag][j]->setCheckable(true);
    }
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
    path = "";
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
                    //shouldSwitcht2f();
                    NetworkData mv(OPCODE::MOVE_OP,QString(myPos),path);
                    socket->send(mv);//发送move信号
                    //test
                    qDebug() << "client send MOVE_OP";
                    qDebug() << "path is " << path;
                    //test end
                }
                else if(mv==2){
                    jumped=checked;
                    chosenloc[0]=objloc[0];
                    chosenloc[1]=objloc[1];
                }
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
        qDebug() << "flat move made";
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
    if(iswin)
        return;//赢了就不让动 su
    QPropertyAnimation *anim = new QPropertyAnimation(btn, "pos", this);
    anim->setDuration(300);
    anim->setStartValue(loc[btn->x][btn->y]);
    anim->setEndValue(QPointF(p.rx()-R/2+1,p.ry()-R/2+0.5));
    anim->start(QPropertyAnimation::KeepWhenStopped);
    btn->x=objloc[0];
    btn->y=objloc[1];
    isfill[objloc[0]][objloc[1]]=btn->player+1;
    isfill[chosenloc[0]][chosenloc[1]]=0;
    ischange=false;
    step++;

    //test
        qDebug() << "chosen is" << chosenloc[0]-8 << "," << chosenloc[1]-8;
        qDebug() << "test:obj is " << objloc[0]-8 << "," << objloc[1]-8;
    //test end
    if(step==1){
        path = "";
        path = QString(QString::number(chosenloc[0]-8).append(" ").append(QString::number(chosenloc[1]-8)));
    }
    path.append(" ").append(QString::number(objloc[0]-8).append(" ").append(QString::number(objloc[1]-8)));
    //test
    qDebug() << "path now is " << path;
    //test end
    totalstep++;
    if(totalstep>60*playernum){
        //isfinish();
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
        case OPCODE::JOIN_ROOM_OP://有新玩家加入
        {
        //test
        qDebug() << "client receive JOIN_ROOM_OP";
        //test end
        players.append(data.data1);
        playerState.append(0);
        ww.ids[players.length()-1]->setText(players.at(players.length()-1));
        }
        break;
        case OPCODE::JOIN_ROOM_REPLY_OP://加入房间成功
            //test
            qDebug() << "client receive JOIN_ROOM_REPLY_OP";
            //test end
            //设置已有玩家状态
            if(data.data2==""){
                players.clear();
                players.append(PlName);
                playerState.clear();
                playerState.append(0);
            }
            else{
                players = data.data1.split(" ");//载入已有玩家姓名
                players.removeLast();
                for(int i=0;i<data.data2.length();i++){
                    playerState.append(QString(data.data2.at(i)).toInt());
                }
                players.append(PlName);
                playerState.append(0);
            }
//            qDebug() << "previous player name is " << players;
//            qDebug() << "now player number is " << players.length();
            for(int i=0;i<players.length();i++)
            {
                 ww.ids[i]->setText(players.at(i));
                 if(playerState.at(i))
                     ww.sis[i]->setText("ready");
            }
            cc.hide();
            ww.show();
        break;
        case OPCODE::LEAVE_ROOM_OP://有其他玩家离开了房间
        {
            //test
            qDebug() << "client receive LEAVE_ROOM_OP";
            //test end
            int Index = players.indexOf(data.data1);
            players.removeAt(Index);
            playerState.removeAt(Index);
        }
        break;
        case OPCODE::CLOSE_ROOM_OP://关闭房间 待实现 我理解是断开连接（Su）
            this->socket->bye();
        break;
        case OPCODE::PLAYER_READY_OP://有玩家准备就绪
            //test
            qDebug() << "client receive PLAYER_READY_OP";
            //test end
            playerState[players.indexOf(data.data1)] = 1;
            ww.sis[players.indexOf(data.data1)]->setText("Ready");

        break;
        case OPCODE::START_GAME_OP://开始游戏 实现了一半
           {
            //test
            qDebug() << "client receive START_GAME_OP";
            //test end
            QStringList pls = data.data1.split(" ");
            QStringList seq = data.data2.split(" ");
            playernum=data.data2.length();            
            for(int i=0;i<playernum;i++){
                players.replace(place2num(seq[i].toUtf8().at(0)),pls[i]);
            }
            myPos = seq.at(pls.indexOf(PlName)).toLatin1()[0];
            //接下来需要设定 只有己方棋子可动,以及根据data2画棋盘
            initializeChecker(data.data2);//画棋子
        }
        break;
        case OPCODE::START_TURN_OP://我的回合开始
        //test
        qDebug() << "client receive START_TURN_OP";
        //test end
            timeLeft=30;
            id=startTimer(1000);
            clock1->show();
            clock2->show();
            flag = myPos-65;
            nowplayer->setText(QString("Player:%1").arg(PlName));
        break;
        case OPCODE::MOVE_OP://其他玩家移动棋子
            {
                //test
                qDebug() << "client receive JOIN_ROOM_OP";
                qDebug() << "player is " << data.data1;
                qDebug() << "path is " << data.data2;
                //test end
                nowplayer->setText(QString("Player:%1").arg(players.at(data.data1.toLatin1()[0]-65)));
                if(data.data1.toLatin1()[0]==myPos&&path==data.data2){//自己的移动合法 服务端发来反馈
                    changeplayer();
                    break;
                }
                int nowPlpos;//该玩家的ABCDEF对应在btn里的序号
                nowPlpos = place2num(data.data1.toUtf8().at(0));
                if(data.data2=="-1"){
                    //移除该玩家所有棋子
                    for(int i=0;i<10;i++){
                        btn[nowPlpos][i]->hide();
                    }
                }
                else{
                    flag = data.data1.toInt()-65;
                    nowplayer->setText(QString("Player:%1").arg(players[nowPlpos]));
                    QStringList checkerpath = data.data2.split(" ");
                    int stepnum = checkerpath.length()/2-1;
                    int origin[2];
                    origin[0]= checkerpath.at(0).toInt();
                    origin[1]= checkerpath.at(1).toInt();
                    for(int i=0;i<10;i++){
                        if(btn[nowPlpos][i]->x==origin[0]
                           &&btn[nowPlpos][i]->y==origin[1]){
                            for(int j=1;j<=stepnum;j++){
                                int aimloc[2];
                                aimloc[0]= checkerpath.at(2*j).toInt();
                                aimloc[1]=checkerpath.at(2*j+1).toInt();
                                QPointF aim;
                                aim.setX(loc[aimloc[0]][aimloc[1]].rx()-RR/4);
                                aim.setY(loc[aimloc[0]][aimloc[1]].ry()-RR/4);
                                CheckerMove(btn[nowPlpos][i],aim);
                            }
                        }
                    }
                }
            }
        break;
    case OPCODE::END_TURN_OP://胜利反馈
    {
        iswin=true;
    }
    break;
    case OPCODE::END_GAME_OP://游戏结束
    {
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
            if(i%2==0){
                char plnow=data.data1.toLatin1()[i];
                rank->ranktable->setItem(i/2,0,new QTableWidgetItem(players[plnow-65]));
            }
        }
        //断开连接
        socket->bye(); 
    }
    break;
    case OPCODE::ERROR_OP://错误
    {
        if(data.data1=="INVALID_JOIN")
            QMessageBox::information(this,QString("error"),QString("用户名已存在"),"OK");
        else if(data.data1=="INVALID_MOVE"){
            //把棋子移回去
            CheckerMove(checked,loc[btnx][btny]);
            isfill[btnx][btny] = 1;
            isfill[objloc[0]][objloc[1]]=0;
            QMessageBox::information(this,QString("error"),QString("移动不合法"),"OK");}
        else if(data.data1=="INVALID_REQ")
            QMessageBox::information(this,QString("error"),QString("无法解析该请求"),"OK");
        else if(data.data1=="NOT_IN_ROOM")
            QMessageBox::information(this,QString("error"),QString("您不在该房间内"),"OK");
        else if(data.data1=="OUTTURN_MOVE"){
            //把棋子移回去
            CheckerMove(checked,loc[btnx][btny]);
            isfill[btnx][btny] = 1;
            isfill[objloc[0]][objloc[1]]=0;
            QMessageBox::information(this,QString("error"),QString("现在不是您的回合"),"OK");
            }
        else if(data.data1=="ROOM_IS_RUNNING")
            QMessageBox::information(this,QString("error"),QString("该房间正在游戏中"),"OK");
        else if(data.data1=="ROOM_NOT_RUNNING"){
            //把棋子移回去
            CheckerMove(checked,loc[btnx][btny]);
            isfill[btnx][btny] = 1;
            isfill[objloc[0]][objloc[1]]=0;
            QMessageBox::information(this,QString("error"),QString("房间内无游戏进行"),"OK");}
        else{
            if(data.data2.isEmpty()){
                QMessageBox::information(this,QString("error"),QString("未知错误"),"OK");
            }
            else{
                QMessageBox::information(this,QString("error"),data.data2,"OK");
            }
        }
    }
    }
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
int ClientWindow::place2num(char pln){
    int k=0;
    if(playernum==2){
        if(pln=='A') k=0;
        else if(pln=='D') k=1;
    }
    else if(playernum==3){
        if(pln=='A') k=0;
        else if(pln=='C') k=1;
        else if(pln=='E') k=2;
    }
    else if(playernum==6){
        k=pln-'A';
    }
    return k;
}

void ClientWindow::initializeChecker(QString data){
    //初始化棋子 2player
    //wzr：我觉得不用根据data改棋子位置，把玩家和区域对应起来应该就行
    qDebug() << "enter initialize";
    int k=0;
    flag=pink;
    nowplayer = new QLabel(this);
    nowplayer->setFont(QFont("Agency FB",24));
    nowplayer->setGeometry(275,0,300,50);
    nowplayer->setText("Player: PINK");
    nowplayer->setStyleSheet("color:#DB7093;");
    if(playernum==2){
    for(int j=5;j<=8;j++){
        for(int i=j-4;i<=4;i++){
            btn[pink][k]=new CheckerButton(this);
            qDebug() << "debug: btn[" << pink << "][" << k << "] is constructed";
            btn[pink][k]->setGeometry(loc[-i+8][j+8].rx()-RR/2,loc[-i+8][j+8].ry()-RR/2,RR,RR);
            btn[pink][k]->setIcon(QPixmap(":/image/pink.png"));
            btn[pink][k]->setIconSize(QSize(RRR,RRR));
            btn[pink][k]->setFlat(true);
            btn[pink][k]->player=pink;//set player
            btn[pink][k]->x=-i+8;
            btn[pink][k]->y=j+8;
            isfill[-i+8][j+8]=pink+1;
            btn[green][k]=new CheckerButton(this);
            qDebug() << "debug: btn[" << green << "][" << k << "] is constructed";
            btn[green][k]->setGeometry(loc[i+8][-j+8].rx()-RR/2,loc[i+8][-j+8].ry()-RR/2,RR,RR);
            btn[green][k]->setIcon(QPixmap(":/image/green.png"));
            btn[green][k]->setIconSize(QSize(RRR,RRR));
            btn[green][k]->setFlat(true);
            btn[green][k]->player=green; //set player
            btn[green][k]->x=i+8;
            btn[green][k]->y=-j+8;
            isfill[i+8][-j+8]=green+1;
            k++;
        }
    }
}
}

