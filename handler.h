#ifndef HANDLER_H
#define HANDLER_H

#include <QStringList>
#include "question.h"
#include <QObject>
#include <QList>

class Handler: public QObject
{
    Q_OBJECT
public:
    Handler();
    ~Handler();
    bool ReadQuestions(bool isDialog);
    void SetPath(QString path);
    QString GetPath();
    Question * GetQuestion(int questionNumber);
    void StartProccess();
    QStringList * GetQuestionHistory();
    void ClearQuestionHistory();

private:
    QList<Question *> *_questions = nullptr;
    int _questionAmount = 0;
    void RemoveQuestions();
    QString _defaultPath = "";
    char _separators[2] = {'|','\n'};
    QStringList *_questionHistory = nullptr;
    QList<Question *> *_currIds = nullptr;

signals:
     void signPrintQuestion(QString questionText);
     void signCreateButton(QString answerText);
     void signClicked();
     void signAddSpacer();

public slots:
     void onHandlerCurrentButtonsClick();
};

#endif // HANDLER_H
