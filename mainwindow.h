#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>
#include <QLabel>
#include "handler.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QPushButton *_btn = nullptr;
    QTextEdit *_le = nullptr;
    QLabel *_lbl = nullptr;
    Handler *_handler = nullptr;

    void InitGui();

private slots:
    void onClickBtn(bool click);

};

#endif // MAINWINDOW_H
