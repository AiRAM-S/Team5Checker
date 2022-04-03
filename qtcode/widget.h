#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QPushButton>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
protected:
    void paintEvent(QPaintEvent *);

private:
    Ui::Widget *ui;
    void DrawCheckerboard();
    void InitCheckerboard();
    QPointF loc[17][17];//标记是否有棋子
    QPushButton *rbtn[10],*bbtn[10];//红蓝双方棋子

    int flag;  //判断下棋方

    QPushButton chosen;
    bool ischosen=false;
    QPoint obj;

};
#endif // WIDGET_H
