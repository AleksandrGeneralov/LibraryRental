#ifndef CATALOGWIDGET_H
#define CATALOGWIDGET_H

#include <QWidget>
#include "../../DialogIncludes.h"

class CatalogTable;
class CatalogModel;

class CatalogWidget : public QWidget
{
    Q_OBJECT

    CatalogTable *table;
    CatalogModel *model;

public:
    CatalogWidget(QWidget *parent);

private:
    void initUi();
};

#endif // CATALOGWIDGET_H
