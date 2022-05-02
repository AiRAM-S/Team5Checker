//.h
#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QApplication>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QPushButton>
#include <QMouseEvent>
#include <QPoint>
#include <QComboBox>

class myDialog:public QDialog
{
    Q_OBJECT
public:
    myDialog(QWidget *parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());

    bool Join() const
    {
        return joinSuccessed;
    }
    QLabel *pix;
    QPoint& operator=(QPointF& f){
       p.setX((int)f.x());
       p.setY((int)f.y());
       return p;
    };
    QComboBox *setplayer;
protected:
    void mpe(QMouseEvent *mo);

private:
    QLabel *ch_logo;
    QLabel *checker;
    QPushButton *join;  //加入游戏
    QPushButton *an;
    QPushButton *quit;  //退出游戏

    QLabel *setp;

    bool joinSuccessed;

    QPoint p;

//signals:
//    void plnum(QString);
};

#endif // MYDIALOG_H
