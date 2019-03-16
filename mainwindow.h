#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>
#include <QLabel>
#include "handler.h"
#include <QVBoxLayout>
//#include "currentbutton.h"

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

    //QPushButton *_btn = nullptr;
    //QTextEdit *_le = nullptr;
    QTextEdit *_lbl = nullptr;
    Handler *_handler = nullptr;
    QList<QPushButton *> *_currentButtons = nullptr;
    QVBoxLayout *_buttonsLayout = nullptr;

    void InitGui();
    void WriteSettings();
    void ReadSettings();

private slots:
    void onClickBtn(bool click);

    void on_action_triggered();

    void onPrintQuestion(QString questionText);

    void onCreateButton(QString answerText);

    void onCurrentButtonsClick();

    void on_action_4_triggered();

signals:
    //void signButtons
};

#endif // MAINWINDOW_H
