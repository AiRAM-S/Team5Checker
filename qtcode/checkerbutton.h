#ifndef CHECKERBUTTON_H
#define CHECKERBUTTON_H

#include <QWidget>
#include <QPushButton>



class CheckerButton : public QPushButton
{
    Q_OBJECT
public:
    explicit CheckerButton(QWidget *parent = nullptr);
    ~CheckerButton();

    int player;
    int x,y;//这里的x，y对应i，j

signals:
    void is_chosen(CheckerButton&);
};

#endif // CHECKERBUTTON_H
