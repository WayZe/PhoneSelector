#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "question.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _handler = new Handler(_settings);
    connect(_handler, SIGNAL(signPrintQuestion(QString)),
            this, SLOT(onPrintQuestion(QString)),
            Qt::ConnectionType::QueuedConnection);
    connect(_handler, SIGNAL(signCreateButton(QString)),
            this, SLOT(onCreateButton(QString)),
            Qt::ConnectionType::QueuedConnection);

    _settings->ReadSettings();

    _handler->ReadQuestions(false);

    InitGui();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitGui()
{
    _lbl = new QTextEdit(this);
    _lbl->setText("Введите текст:");
    _lbl->setMaximumHeight(100);
    _lbl->setMinimumWidth(200);
    ui->horizontalLayout->addWidget(_lbl);

    _buttonsLayout = new QVBoxLayout(this);
    ui->horizontalLayout->addLayout(_buttonsLayout);

    _currentButtons = new QList<QPushButton *>();

    this->setBaseSize(200, 100);

    _handler->StartProccess();
}

void MainWindow::on_action_triggered()
{
    if (_handler->ReadQuestions(true))
    {
        _settings->WriteSettings();
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

    _buttonsLayout->addWidget(btn);
    _currentButtons->append(btn);
}

void MainWindow::onCurrentButtonsClick()
{
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

void MainWindow::on_action_4_triggered()
{
    if (_currentButtons)
    {
        foreach (QPushButton *btn, *_currentButtons)
        {
            delete btn;
            btn = nullptr;
        }
        _currentButtons->clear();
    }
    _handler->StartProccess();
}
