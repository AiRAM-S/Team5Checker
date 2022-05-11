#include "checkerbutton.h"
#include <QPushButton>
#include <QDebug>

CheckerButton::CheckerButton(QWidget *parent)
    : QPushButton{parent}
{

    setCheckable(true);
    setAutoExclusive(true);

    connect(this,&CheckerButton::clicked,this,[=](){
        emit is_chosen(*this);
    });

}
CheckerButton::~CheckerButton(){
}

