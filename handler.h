#ifndef HANDLER_H
#define HANDLER_H

#include <QStringList>
#include "question.h"
#include <QObject>

class Handler: public QObject
{
    Q_OBJECT
public:
    ~Handler();
    bool ReadQuestions(bool isDialog);
    void SetPath(QString path);
    QString GetPath();
    Question * GetQuestion(int questionNumber);
    void StartProccess();

private:
    QList<Question *> *_questions = nullptr;
    int _questionAmount = 0;
    void RemoveQuestions();
    QString _defaultPath = "";
    char _separators[2] = {'|','\n'};

signals:
     void signPrintQuestion(QString questionText);
     void signCreateButton(QString answerText);
     void onClicked();

public slots:
     void onHandlerCurrentButtonsClick();
};

#endif // HANDLER_H
