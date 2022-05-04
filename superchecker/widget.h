#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QPushButton>
#include "checkerbutton.h"
#include "mydialog.h"
#include"mydialog1.h"
#include <QMouseEvent>
#include <QLabel>
#include <QDialog>
#include<QPropertyAnimation>
#include"networkserver.h"
#include"networksocket.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public Q_SLOTS:
    void cbuttonpress();

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void mousePressEvent(QMouseEvent* ev);
    int islegal();//判断移动是否合法

    int pixel2int(QPointF pixel);
    void CheckerMove(CheckerButton*btn,QPointF p);

    bool canJump(int x,int y);//排查是否可以进行下一次跳跃
    void shouldSwitcht2f();
    void isfinish();
protected:
    void paintEvent(QPaintEvent *);

private:
    Ui::Widget *ui;
    void DrawCheckerboard();
    void InitCheckerboard();
    QPointF loc[17][17];//棋盘每个位置的坐标
    int isfill[17][17];//棋盘每个位置是否有棋子
    CheckerButton* btn[6][10]; //六方棋子
    int playernum; //棋手个数
    int flag;  //判断下棋方
    bool isover[6];
    int overnum=0;

    QPointF chosen;//选中的棋子
    CheckerButton* checked;//被选中的棋子
    bool haveJumped;
    CheckerButton* jumped;

    QDialog *nobai;
   // QDialog *win;
   // QLabel *w;
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
    mydialog1 *z;
    int totalstep=0;

    NetworkServer* server;//监听
    NetworkSocket* conn;//通信
signals:
    void shouldSwitchChanged();
    //终局判断，信号和槽函数未实现连接
    void finish(int);//一方结束游戏信号
    void gameover();//游戏结束信号
public slots:
    void changeplayer();
  //  void someoneover(int i);


};
#endif // WIDGET_H