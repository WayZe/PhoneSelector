#ifndef HANDLER_H
#define HANDLER_H

#include <QStringList>
#include "question.h"

class Handler
{
public:
    ~Handler();
    bool ReadQuestions(QList<Question *> *questions = nullptr);

private:
    QList<Question *> *_questions = nullptr;
    int _questionAmount = 0;
    void RemoveQuestions();
};

#endif // HANDLER_H
