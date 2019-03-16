#ifndef HANDLER_H
#define HANDLER_H

#include <QStringList>
#include "question.h"
#include <QObject>
#include "settings.h"

class Handler: public QObject
{
    Q_OBJECT
public:
    Handler(Settings *settings);
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
    char _separators[2] = {'|','\n'};
    Settings *_settings = nullptr;

signals:
     void signPrintQuestion(QString questionText);
     void signCreateButton(QString answerText);
     void onClicked();

public slots:
     void onHandlerCurrentButtonsClick();
};

#endif // HANDLER_H
