#ifndef WAIT_H
#define WAIT_H

#include <QWidget>
#include<QLineEdit>
#include<QLabel>

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
    //bool isready[6];
    QLineEdit *ids[6];
    QLabel *sis[6];

private slots:
   void qqq();

public:
    Ui::Wait *ui;
    bool ifsuccessed;
};

#endif // WAIT_H
