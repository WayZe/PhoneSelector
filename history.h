#ifndef HISTORY_H
#define HISTORY_H

#include <QDialog>
#include <QTableWidget>
#include "handler.h"
#include <QList>

namespace Ui {
class History;
}

class History : public QDialog
{
    Q_OBJECT

public:
    explicit History(Handler *handler, QWidget *parent = nullptr);
    ~History();

private:
    Ui::History *ui;
    QTableWidget *_table = nullptr;
    Handler *_handler = nullptr;
    QList<QTableWidgetItem *> *_tableItems = nullptr;

public slots:
    void onShowTable();
};

#endif // HISTORY_H
