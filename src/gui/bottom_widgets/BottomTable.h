#ifndef BOTTOMTABLE_H
#define BOTTOMTABLE_H

#include <QTableView>
#include <QHeaderView>

class BottomTable : public QTableView
{
    Q_OBJECT

protected:
    BottomTable(QWidget *parent = nullptr) : QTableView(parent)
    {
        horizontalHeader()->setStretchLastSection(true);
    }

};

#endif // BOTTOMTABLE_H
