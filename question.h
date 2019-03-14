#ifndef QUESTION_H
#define QUESTION_H

#include <QString>

class Question
{
public:
    Question(int currId, int prevId, QString text);

    int _currId = 0;
    int _prevId = 0;
    QString _text = "";
};

#endif // QUESTION_H
