#include "handler.h"
#include <QFile>
#include <QFileDialog>
#include <QDir>
#include <QDebug>
#include <QPushButton>

Handler::Handler()
{
    _questionHistory = new QStringList();
}

Handler::~Handler()
{
//    if (_questionHistory)
//    {
//        foreach (Question *question, *_questionHistory)
//        {
//            delete question;
//            question = nullptr;
//        }
//        delete _questionHistory;
//        _questionHistory = nullptr;
//    }

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
                if (questionsElems.count() > 6)
                {
                    isRightFormat = false;
                    RemoveQuestions();
                    qDebug() << "Bad format";
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
                                                questionsElems.at(3),
                                                questionsElems.at(4),
                                                questionsElems.at(5)));
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

    if (isRightFormat)
    {

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
    if (_questions)
    {
        foreach (Question *question, *_questions)
        {
            if (question->_currId == 1)
            {
                emit signPrintQuestion(question->_question);
                _questionHistory->append(question->_question);
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
        emit signAddSpacer();
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

    //_questionHistory->append(answer);

    emit signClicked();

    int currId = -1;

    if (_questions)
    {
        foreach (Question *question, *_questions)
        {
            if(question->_answer == answer)
            {
                emit signPrintQuestion(question->_question);
                currId = question->_currId;
                _questionHistory->append(question->_answerDescription);
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
                }
                else
                {
                    emit signPrintQuestion(question->_answer);
                    _questionHistory->append(question->_answerDescription);
                }
            }
        }
        emit signAddSpacer();
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
