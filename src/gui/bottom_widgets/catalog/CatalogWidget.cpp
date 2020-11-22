#include "CatalogWidget.h"

#include "CatalogTable.h"
#include "CatalogModel.h"

CatalogWidget::CatalogWidget(QWidget *parent)
    : BottomWidget(parent)
{
    initUi();
}

void CatalogWidget::initUi()
{
    table = new CatalogTable(this);
    model = new CatalogModel(table);

    table->setModel(model);

    mainLay->addWidget(table);
}
