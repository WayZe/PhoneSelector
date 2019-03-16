#ifndef QUESTION_H
#define QUESTION_H

#include <QString>

class Question
{
public:
    Question(int currId, int prevId, QString question, QString answer, QString questionDescription, QString answerDescription);

    int _currId = 0;
    int _prevId = 0;
    QString _question = "";
    QString _answer = "";
    QString _questionDescription = "";
    QString _answerDescription = "";
};

#endif // QUESTION_H
