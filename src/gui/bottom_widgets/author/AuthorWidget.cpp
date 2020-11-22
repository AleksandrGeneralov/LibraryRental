#include "AuthorWidget.h"

#include "AuthorModel.h"
#include "AuthorTable.h"

AuthorWidget::AuthorWidget(QWidget *parent)
    : BottomWidget(parent)
{
    initUi();
}

void AuthorWidget::initUi()
{
    table = new AuthorTable(this);
    model = new AuthorModel(table);

    table->setModel(model);

    mainLay->addWidget(table);
}
