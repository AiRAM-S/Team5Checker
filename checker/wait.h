#ifndef WAIT_H
#define WAIT_H

#include <QWidget>
#include<QLabel>
#include<QRadioButton>
#include<QPushButton>
#include<QLineEdit>

namespace Ui {
class Wait;
}

class Wait : public QWidget
{
    Q_OBJECT

public:
    explicit Wait(QWidget *parent = nullptr);
    ~Wait();
    bool Join()const
    {
        return ifsuccessed;
    }

private slots:
   void qqq();

private:
    Ui::Wait *ui;
    QLabel *num[6];
    QRadioButton *ready[6];
    int isready[6];
    int peo;
    bool ifsuccessed=false;

};

#endif // WAIT_H
