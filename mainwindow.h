#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>
#include <QLabel>
#include <QVBoxLayout>
#include "handler.h"
#include <QSpacerItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QTextEdit *_lbl = nullptr;
    Handler *_handler = nullptr;
    QList<QPushButton *> *_currentButtons = nullptr;
    QVBoxLayout *_buttonsLayout = nullptr;
    QSpacerItem *_spacer = nullptr;

    void InitGui();
    void WriteSettings();
    void ReadSettings();

private slots:
    void on_Open_triggered();

    void onPrintQuestion(QString questionText);

    void onCreateButton(QString answerText);

    void onCurrentButtonsClick();

    void on_Restart_triggered();
    void on_ShowPath_triggered();
    void on_Exit_triggered();

    void onAddSpacer();
};

#endif // MAINWINDOW_H
