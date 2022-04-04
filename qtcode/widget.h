#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QPushButton>
#include "checkerbutton.h"
#include <QMouseEvent>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void mousePressEvent(QMouseEvent* ev);
    bool islegal();
    void int2pixel();   //将loc坐标转换为像素坐标

protected:
    void paintEvent(QPaintEvent *);

private:
    Ui::Widget *ui;
    void DrawCheckerboard();
    void InitCheckerboard();
    QPointF loc[17][17];//标记是否有棋子
//    CheckerButton *rbtn[10],*bbtn[10];//红蓝双方棋子
    CheckerButton* btn[6][10]; //六方棋子

    int playernum; //棋手个数
    int flag;  //判断下棋方

    QPointF chosen;
    int chosenloc[2];
    bool ischosen=false;
    QPointF obj;
    int objloc[2];

    QLabel* test;
    QPushButton* end;

public slots:

};
#endif // WIDGET_H
