#ifndef SERVERWAIT_H
#define SERVERWAIT_H

#include <QWidget>
#include"room.h"
#include<QPushButton>

namespace Ui {
class serverwait;
}

class serverwait : public QWidget
{
    Q_OBJECT

public:
    explicit serverwait(QWidget *parent = nullptr);
    ~serverwait();

private:
    Ui::serverwait *ui;
    QPushButton *b;
};

#endif // SERVERWAIT_H
