#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "checkerbutton.h"
#include "mydialog.h"
#include"mydialog1.h"
#include <QMouseEvent>
#include <QLabel>
#include <QDialog>
#include<QPropertyAnimation>
#include<QTimerEvent>
#include "rank.h"
#include "networksocket.h"
#include"mydialog.h"
#include"chooseclient.h"
#include"wait.h"

namespace Ui {
class ClientWindow;
}

class ClientWindow : public QMainWindow
{
    Q_OBJECT

public Q_SLOTS:
    void cbuttonpress();

public:
    explicit ClientWindow(QWidget *parent = nullptr);
    ~ClientWindow();

    void mousePressEvent(QMouseEvent* ev);
    int islegal();//判断移动是否合法

    int pixel2int(QPointF pixel);
    void CheckerMove(CheckerButton*btn,QPointF p);

    bool canJump(int x,int y);//排查是否可以进行下一次跳跃
    void shouldSwitcht2f();
    void isfinish();//棋子是否走完
    int place2num(char);
    void setPort(QString p){
        Port = p;
        return;
    }
    NetworkSocket* getSocket(){
        return socket;
    }

protected:
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *event);

private:
    Ui::ClientWindow *ui;

    void DrawCheckerboard();
    void InitCheckerboard();
    QPointF loc[17][17];//棋盘每个位置的坐标
    int isfill[17][17];//棋盘每个位置是否有棋子
    CheckerButton* btn[6][10]; //六方棋子
    int playernum; //棋手个数
    int flag;  //判断下棋方


    QPointF chosen;//选中的棋子
    CheckerButton* checked;//被选中的棋子
    bool haveJumped;
    CheckerButton* jumped;

    QDialog *nobai;
    int chosenloc[2];//选中棋子所在位置
    bool ischosen=false;//是否有棋子被选中
    bool isobjset=false;
    QPointF obj;//目标位置
    int objloc[2];//目标位置坐标
    bool ischange=false;
    int btnx,btny;//记录选中棋子初始位置
    int step=0;
    QLabel* test;
    QLabel* nowplayer;
    QPushButton* end;
    bool shouldSwitch;
    bool isover[6];
    int overnum=0;
    mydialog1 *z;
    int totalstep=0;

    //stage2用到的
    char myPos;//记录该玩家所处位置（ABCDEF)
    NetworkSocket* socket;
    QString path;
    int id;//计时器id,负责倒计时
    QLabel* clock1;//显示倒计时提示
    QLabel* clock2;//显示时间
    bool iswin=false;//是否胜利，不知道有没有用先写着
    Rank* rank;
    void initializeChecker(QString);//根据服务端发来的信号，画棋子
    void setPlayerTable();//列玩家列表
    QList<QLabel*> PlayerTable;
    QStringList players;
    QList<int> playerState;
    QString RoomID;//该客户端所处房间号
    QString PlName;//玩家姓名
    QString Port;//端口号
public:
    //myDialog dd;
    chooseclient cc;
private:
    void passit1(QString a)
    {
        Port=a;
    }
    void passit2(QString b,QString c)
    {
        RoomID=b;
        PlName=c;
    }
    Wait ww;


signals:
    void shouldSwitchChanged();
    void finish(int);
    void gameover();
public slots:
    void changeplayer();
    void receive(NetworkData);
};

#endif // CLIENTWINDOW_H
