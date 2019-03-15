#include "question.h"

Question::Question(int currId, int prevId, QString question, QString answer)
{
    _currId = currId;
    _prevId = prevId;
    _answer = answer;
    _question = question;
}
