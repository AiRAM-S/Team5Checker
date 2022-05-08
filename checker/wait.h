#ifndef WAIT_H
#define WAIT_H

#include <QWidget>

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
    bool isready[6];

private slots:
   void qqq();

private:
    Ui::Wait *ui;
    int peo;
    int ple;
    //QRadioButton *btn[6];
    bool ifsuccessed;
};

#endif // WAIT_H
