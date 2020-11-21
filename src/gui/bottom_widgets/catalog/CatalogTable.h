#ifndef CATALOGTABLE_H
#define CATALOGTABLE_H

#include <QTableView>

class CatalogTable : public QTableView
{
    Q_OBJECT
public:
    explicit CatalogTable(QWidget *parent = nullptr);

};

#endif // CATALOGTABLE_H
