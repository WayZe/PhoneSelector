#include "handler.h"
#include <QFile>
#include <QFileDialog>
#include <QDir>
#include <QDebug>
#include <QPushButton>

Handler::Handler()
{
    _questionHistory = new QStringList();
    _currIds = new QList<Question *>();
}

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
        _defaultPath = QFileDialog::getOpenFileName(nullptr, "123", _defaultPath);
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
                if (questionsElems.count() != 5)
                {
                    isRightFormat = false;
                    RemoveQuestions();
                    qDebug() << "Bad format";
                    signPrintQuestion("Вы выбрали файл с неверным форматом.");
                    break;
                }
                else
                {

                    foreach (QByteArray part, questionsElems)
                    {
                        part = part.split('\n')[0];
                        qDebug() << part;
                    }

                    _questions->append(new Question(questionsElems.at(0).toInt(),
                                                    questionsElems.at(1).toInt(),
                                                    questionsElems.at(2),
                                                    questionsElems.at(3),
                                                    questionsElems.at(4)));
                }
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
    if (_currIds)
    {
        foreach (Question *question, *_currIds)
        {
            delete question;
            question = nullptr;
        }
        _currIds->clear();
    }

    if (_questions)
    {
        int minQuestionNumber = 0;

        for (int i = 1; i < _questions->count(); i++)
        {
            if (i < minQuestionNumber)
            {
                minQuestionNumber = i;
            }
        }

        foreach (Question *question, *_questions)
        {
            if (question->_currId == _questions->at(minQuestionNumber)->_currId)
            {
                emit signPrintQuestion(question->_question);
                _questionHistory->append(question->_questionDescription);
                break;
            }
        }

        foreach (Question *question, *_questions)
        {
            if (question->_prevId == _questions->at(minQuestionNumber)->_currId)
            {
                emit signCreateButton(question->_answer);
                _currIds->append(question);
            }
        }
    }
    else
    {
        qDebug() << "_questions is nullptr";
    }
}

void Handler::onHandlerCurrentButtonsClick()
{
    QPushButton* btn = qobject_cast<QPushButton *>(sender());
    QString answer = btn->text();
    int prevCurrId = -1;
    if (_currIds)
    {
        foreach (Question *question, *_currIds)
        {
            if(question->_answer == answer)
            {
                prevCurrId = question->_currId;
            }
        }
        _currIds->clear();
    }

    emit signClicked();

    int currId = -1;

    if (_questions)
    {
        foreach (Question *question, *_questions)
        {
            if(question->_currId == prevCurrId)
            {
                emit signPrintQuestion(question->_question);
                currId = question->_currId;
                _questionHistory->append(question->_questionDescription);
            }
        }

        foreach (Question *question, *_questions)
        {
            if (question->_prevId == currId)
            {
                if (question->_question != "")
                {
                    emit signCreateButton(question->_answer);
                    _currIds->append(question);

                }
                else
                {
                    emit signPrintQuestion(question->_answer);
                }
            }
        }
    }
}

QStringList * Handler::GetQuestionHistory()
{
    return _questionHistory;
}

void Handler::ClearQuestionHistory()
{
    if (_questionHistory)
    {
        _questionHistory->clear();
    }
}
