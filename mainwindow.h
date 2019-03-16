#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>
#include <QLabel>
#include <QVBoxLayout>
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

    QTextEdit *_lbl = nullptr;
    Handler *_handler = nullptr;
    QList<QPushButton *> *_currentButtons = nullptr;
    QVBoxLayout *_buttonsLayout = nullptr;

    void InitGui();
    void WriteSettings();
    void ReadSettings();

private slots:
    void on_action_triggered();

    void onPrintQuestion(QString questionText);

    void onCreateButton(QString answerText);

    void onCurrentButtonsClick();

    void on_action_4_triggered();
    void on_action_3_triggered();
};

#endif // MAINWINDOW_H
