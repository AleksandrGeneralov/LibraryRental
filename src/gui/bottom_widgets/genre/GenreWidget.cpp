#include "GenreWidget.h"

#include "GenreModel.h"
#include "GenreTable.h"

GenreWidget::GenreWidget(QWidget *parent)
    : BottomWidget(parent)
{
    initUi();
}

void GenreWidget::initUi()
{
    table = new GenreTable(this);
    model = new GenreModel(table);

    table->setModel(model);

    mainLay->addWidget(table);
}
