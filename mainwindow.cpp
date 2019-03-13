#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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

    _le = new QLineEdit(this);
    ui->layout->addWidget(_le);

    _btn = new QPushButton(this);
    ui->layout->addWidget(_btn);

    this->setBaseSize(200, 100);
}
