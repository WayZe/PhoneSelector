#include "question.h"

Question::Question(int currId, int prevId, QString question, QString answer, QString questionDescription)
{
    _currId = currId;
    _prevId = prevId;
    _answer = answer;
    _question = question;
    _questionDescription = questionDescription;
}
