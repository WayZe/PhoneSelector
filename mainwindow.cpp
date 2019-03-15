#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMenuBar>
#include "question.h"
#include <QDebug>
#include <QSettings>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _handler = new Handler();
    connect(_handler, SIGNAL(signPrintQuestion(QString)),
            this, SLOT(onPrintQuestion(QString)),
            Qt::ConnectionType::QueuedConnection);
    connect(_handler, SIGNAL(signCreateButton(QString)),
            this, SLOT(onCreateButton(QString)),
            Qt::ConnectionType::QueuedConnection);

    this->ReadSettings();

    _handler->ReadQuestions(false);

    InitGui();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitGui()
{
    _lbl = new QLabel(this);
    _lbl->setText("Введите текст:");
    _lbl->setMaximumHeight(20);
    _lbl->setMinimumWidth(200);
    ui->layout->addWidget(_lbl);

//    _le = new QTextEdit(this);
//    _le->setText(_handler->GetPath());
//    ui->layout->addWidget(_le);

//    _btn = new QPushButton(this);
//    ui->layout->addWidget(_btn);
//    _btn->setMaximumWidth(100);
//    _btn->setText("Ok");
//    _btn->setStyleSheet("color: black; alignment: left");
//    connect(_btn, SIGNAL(clicked(bool)), this, SLOT(onClickBtn(bool)));

    _currentButtons = new QList<QPushButton *>();

    this->setBaseSize(200, 100);

    _handler->StartProccess();
}

void MainWindow::onClickBtn(bool click)
{
}

void MainWindow::on_action_triggered()
{
    QList<Question *> *questions = nullptr;

    if (_handler->ReadQuestions(true))
    {
        this->WriteSettings();
//        foreach (Question *question, *questions)
//        {
//            outQuestion+=QString::number(question->_currId) + " " +
//                    QString::number(question->_prevId) + " " +
//                    question->_question + " " +
//                    question->_answer + "\n";
//        }
//         _le->setText(outQuestion);
    }
    else
    {
        qDebug() << "Dont read";
    }
}

void MainWindow::WriteSettings()
{
    QSettings settings(QSettings::UserScope, "MAI", "Selector");

    settings.beginGroup("Settings");

    qDebug() <<  _handler->GetPath();
    settings.setValue("path", _handler->GetPath());

    settings.endGroup();

    settings.sync();
}

void MainWindow::ReadSettings()
{
    QSettings settings(QSettings::UserScope, "MAI", "Selector");

    settings.beginGroup("Settings");

    QString configFilePathFromSave = settings.value("path").toString();

    settings.endGroup();

    _handler->SetPath(configFilePathFromSave);
}

void MainWindow::onPrintQuestion(QString questionText)
{
    _lbl->setText(questionText);
}

void MainWindow::onCreateButton(QString answerText)
{
    QPushButton *btn = new QPushButton();
    btn->setText(answerText);
    btn->setMaximumWidth(100);
    btn->setMaximumHeight(50);
    btn->setStyleSheet("color: black; alignment: center");

    connect(btn, SIGNAL(clicked()),
            _handler, SLOT(onHandlerCurrentButtonsClick()),
            Qt::ConnectionType::QueuedConnection);
    connect(_handler, SIGNAL(onClicked()),
            this, SLOT(onCurrentButtonsClick()),
            Qt::ConnectionType::QueuedConnection);

    ui->layout->addWidget(btn);
    _currentButtons->append(btn);
}

void MainWindow::onCurrentButtonsClick()
{
    qDebug() << "onCurrentButtonsClick() -->" << _currentButtons->count();
    if (_currentButtons)
    {
        foreach (QPushButton *btn, *_currentButtons)
        {
            delete btn;
            btn = nullptr;
        }
        _currentButtons->clear();
    }
}
