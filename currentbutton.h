#ifndef CURRENTBUTTON_H
#define CURRENTBUTTON_H

#include <QPushButton>

class CurrentButton: public QPushButton
{
    Q_OBJECT
private:
    QString _text = "";

public:
    explicit CurrentButton(QWidget *parent = 0);

signals:
    void onClick(QString answerText);

public slots:
    void buttonClicked();
};

#endif // CURRENTBUTTON_H
