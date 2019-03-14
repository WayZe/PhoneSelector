#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMenuBar>
#include "question.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    InitGui();

    _handler = new Handler();
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

    _le = new QTextEdit(this);
    ui->layout->addWidget(_le);

    _btn = new QPushButton(this);
    ui->layout->addWidget(_btn);
    _btn->setMaximumWidth(100);
    _btn->setText("Ok");
    _btn->setStyleSheet("color: black; alignment: left");
    connect(_btn, SIGNAL(clicked(bool)), this, SLOT(onClickBtn(bool)));

    this->setBaseSize(200, 100);
}

void MainWindow::onClickBtn(bool click)
{
    QList<Question *> *questions = nullptr;

    if (_handler->ReadQuestions(questions))
    {
        foreach (Question *question, *questions)
        {
            _le->setText(QString::number(question->_currId) +
                         QString::number(question->_prevId) +
                         question->_text);
        }
    }
}
