#include "CatalogWidget.h"

#include "CatalogTable.h"
#include "CatalogModel.h"

CatalogWidget::CatalogWidget(QWidget *parent)
    : QWidget(parent)
{
    initUi();
}

void CatalogWidget::initUi()
{
    QVBoxLayout *mainLay = new QVBoxLayout();
    this->setLayout(mainLay);

    table = new CatalogTable(this);
    model = new CatalogModel(table);

    table->setModel(model);

    mainLay->addWidget(table);
}
