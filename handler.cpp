#include "handler.h"
#include <QFile>
#include <QFileDialog>
#include <QDir>
#include <QDebug>
#include <QPushButton>

Handler::~Handler()
{
    RemoveQuestions();
}

bool Handler::ReadQuestions(bool isDialog)
{
    bool isRightFormat = true;

    RemoveQuestions();

    _questions = new QList<Question *>();

    if (isDialog)
    {
        _defaultPath = QFileDialog::getOpenFileName(NULL, "123", _defaultPath);
    }

    qDebug() << _defaultPath;

    if (_defaultPath != "" || !isDialog)
    {
        QFile file(_defaultPath);

        if (file.exists() && (file.open(QIODevice::ReadOnly)))
        {
            while(!file.atEnd())
            {
                QList<QByteArray> questionsElems = file.readLine().split(_separators[0]);
                if (questionsElems.count() > 4)
                {
                    isRightFormat = false;
                    RemoveQuestions();
                    break;
                }

                foreach (QByteArray part, questionsElems)
                {
                    part = part.split('\n')[0];
                    qDebug() << part;
                }

                _questions->append(new Question(questionsElems.at(0).toInt(),
                                                questionsElems.at(1).toInt(),
                                                questionsElems.at(2),
                                                questionsElems.at(3)));
            }
            file.close();
        }
        else
        {
            qDebug() << "File does not exist" << _defaultPath;
            emit signPrintQuestion("Выберите файл с вопросами!");
        }
    }
    else
    {
        emit signPrintQuestion("Выберите файл");
    }

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

void Handler::SetPath(QString path)
{
    _defaultPath = path;
}

QString Handler::GetPath()
{
    return _defaultPath;
}

Question * Handler::GetQuestion(int questionNumber)
{
    return _questions->at(questionNumber);
}

void Handler::StartProccess()
{
    foreach (Question *question, *_questions)
    {
        if (question->_currId == 1)
        {
            emit signPrintQuestion(question->_question);
            break;
        }
    }

    foreach (Question *question, *_questions)
    {
        if (question->_prevId == 1)
        {
            emit signCreateButton(question->_answer);
        }
    }
}

void Handler::onHandlerCurrentButtonsClick()
{
    QPushButton* btn = qobject_cast<QPushButton *>(sender());
    QString answer = btn->text();

    emit onClicked();

    int currId = -1;

    foreach (Question *question, *_questions)
    {
        if(question->_answer == answer)
        {
            emit signPrintQuestion(question->_question);
            currId = question->_currId;
        }
    }

    foreach (Question *question, *_questions)
    {
        if (question->_prevId == currId)
        {
            if (question->_question != '-')
            {
                emit signCreateButton(question->_answer);
            }
            else
            {
                emit signPrintQuestion(question->_answer);
            }
        }
    }
}
