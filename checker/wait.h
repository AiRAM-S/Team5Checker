#ifndef WAIT_H
#define WAIT_H

#include <QWidget>
#include<QLabel>
#include<QRadioButton>
#include<QPushButton>
#include<QLineEdit>

namespace Ui {
class wait;
}

class wait : public QWidget
{
    Q_OBJECT

public:
    explicit wait(QWidget *parent = nullptr);
    ~wait();
    bool Join()const
    {
        return ifsuccessed;
    }

private slots:
   void qqq();

private:
    Ui::wait *ui;
    QLabel *num[6];
    QRadioButton *ready[6];
    int isready[6];
    int peo;
    bool ifsuccessed;

};

#endif // WAIT_H
