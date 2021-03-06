#include "history.h"
#include "ui_history.h"
#include <QHeaderView>
#include <QDebug>

History::History(Handler *handler, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::History)
{
    ui->setupUi(this);

    _handler = handler;
    _table = new QTableWidget(this);
    _table->setEditTriggers(QTableWidget::NoEditTriggers);
    //_table->setItem(1, 1, new QTableWidgetItem("2123"));
    _table->setColumnCount(2);
    _table->setShowGrid(true);
    _table->setStyleSheet("color: black");
    _table->horizontalHeader()->hide();
    _table->verticalHeader()->hide();
    _table->horizontalHeader()->setStretchLastSection(true);
    ui->verticalLayout->addWidget(_table);
    _table->resizeColumnsToContents();

    _tableItems = new QList<QTableWidgetItem *>();
}

History::~History()
{
    if (_tableItems)
    {
        foreach (QTableWidgetItem *tableItem, *_tableItems)
        {
            delete tableItem;
            tableItem = nullptr;
        }
        _tableItems->clear();
        delete _tableItems;
        _tableItems = nullptr;
    }
    delete ui;
}

void History::onShowTable()
{
    QStringList *descriptions = _handler->GetQuestionHistory();
    if (_tableItems)
    {
        foreach (QTableWidgetItem *tableItem, *_tableItems)
        {
            delete tableItem;
            tableItem = nullptr;
        }
        _tableItems->clear();
    }
    _table->setRowCount(descriptions->count() + 1);
    _table->resizeColumnsToContents();
    int i = 0;
    qDebug() << "descriptions count" << descriptions->count();
    for (i; i < descriptions->count() - 1; i++)
    {
        _table->setRowHeight(i, 40);
        _tableItems->append(new QTableWidgetItem(QString::number(i+1)));
        _table->setItem(i, 0, _tableItems->last());
        _tableItems->append(new QTableWidgetItem(descriptions->at(i)));
        _table->setItem(i, 1, _tableItems->last());
    }

    i++;

    _table->setRowHeight(i, 40);
    _tableItems->append(new QTableWidgetItem(QString::number(i)));
    _table->setItem(i, 0, _tableItems->last());
    _tableItems->append(new QTableWidgetItem(descriptions->last()));
    _table->setItem(i, 1, _tableItems->last());
}
