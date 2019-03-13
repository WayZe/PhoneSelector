#ifndef HANDLER_H
#define HANDLER_H

#include <QStringList>

class Handler
{
public:
    Handler();

private:
    QStringList *_questions = nullptr;
    int _questionAmount;
};

#endif // HANDLER_H
