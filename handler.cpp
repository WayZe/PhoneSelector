#include "handler.h"
#include <QFile>
#include <QFileDialog>
#include <QDir>
#include <QDebug>

Handler::~Handler()
{
    RemoveQuestions();
}

bool Handler::ReadQuestions(QList<Question *> *questions)
{
    bool isRightFormat = true;

    RemoveQuestions();

    _questions = new QList<Question *>();

    QFile file(QFileDialog::getOpenFileName());

    if (file.exists() && (file.open(QIODevice::ReadOnly)))
    {
        while(!file.atEnd())
        {
            QList<QByteArray> questionsElems = file.readLine().split('|');
            if (questionsElems.count() != 3)
            {
                isRightFormat = false;
                RemoveQuestions();
                break;
            }

            _questions->append(new Question(questionsElems.at(0).toInt(),
                                            questionsElems.at(1).toInt(),
                                            questionsElems.at(2)));
        }
        file.close();
    }
    else
    {
        qDebug() << "File does not exist";
    }

    questions = _questions;

    return isRightFormat;
}

void Handler::RemoveQuestions()
{
    if (_questions)
    {
        foreach (Question *question, *_questions)
        {
            delete question;
            question = nullptr;
        }
        delete _questions;
        _questions = nullptr;
    }
}
