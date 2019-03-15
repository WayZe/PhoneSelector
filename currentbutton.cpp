#include "currentbutton.h"

CurrentButton::CurrentButton(QWidget *parent) :
    QPushButton(parent)
{
    connect(this, SIGNAL(clicked()), this, SLOT(buttonClicked()));
}

void CurrentButton::buttonClicked()
{
    //emit onClick(answerText);
}
