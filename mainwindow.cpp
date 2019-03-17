#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QSettings>
#include "question.h"
#include <QMessageBox>

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
    connect(_handler, SIGNAL(signAddSpacer()),
            this, SLOT(onAddSpacer()),
            Qt::ConnectionType::QueuedConnection);

    //_spacer = new QSpacerItem(100,100);
    _history = new History(_handler, this);
    connect(this, SIGNAL(signShowTable()),
            _history, SLOT(onShowTable()),
            Qt::ConnectionType::QueuedConnection);

    InitGui();

    this->ReadSettings();

     if (_handler->ReadQuestions(false))
     {
         _handler->StartProccess();
     }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitGui()
{
    _lbl = new QTextEdit(this);
    _lbl->setMinimumHeight(100);
    _lbl->setMinimumWidth(200);
    _lbl->setStyleSheet("color: black; alignment: center");
    _lbl->setReadOnly(true);
    ui->horizontalLayout->addWidget(_lbl);

    _buttonsLayout = new QVBoxLayout(this);
    ui->horizontalLayout->addLayout(_buttonsLayout);

    _currentButtons = new QList<QPushButton *>();

    this->setBaseSize(200, 100);
}

void MainWindow::on_Open_triggered()
{
    if (_handler->ReadQuestions(true))
    {
        this->WriteSettings();

        if (_currentButtons)
        {
            foreach (QPushButton *btn, *_currentButtons)
            {
                delete btn;
                btn = nullptr;
            }
            _currentButtons->clear();
        }

        _handler->ClearQuestionHistory();

        _handler->StartProccess();

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
    btn->setMaximumWidth(10000);
    btn->setMaximumHeight(50);
    btn->setStyleSheet("color: black; alignment: center");

    connect(btn, SIGNAL(clicked()),
            _handler, SLOT(onHandlerCurrentButtonsClick()),
            Qt::ConnectionType::QueuedConnection);
    connect(_handler, SIGNAL(signClicked()),
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

void MainWindow::on_Restart_triggered()
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

    _handler->ClearQuestionHistory();

    _handler->StartProccess();
}

void MainWindow::on_ShowPath_triggered()
{
    //QMessageBox::information(this, "История", _handler->GetQuestionHistory());
    emit signShowTable();
    _history->show();
}

void MainWindow::on_Exit_triggered()
{
    qApp->exit();
}

void MainWindow::onAddSpacer()
{
    //_buttonsLayout->addSpacerItem(_spacer);
}
