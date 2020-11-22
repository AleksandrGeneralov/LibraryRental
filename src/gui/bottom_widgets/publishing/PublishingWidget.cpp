#include "PublishingWidget.h"

#include "PublishingModel.h"
#include "PublishingTable.h"

PublishingWidget::PublishingWidget(QWidget *parent)
    : BottomWidget(parent)
{
    initUi();
}

void PublishingWidget::initUi()
{
    table = new PublishingTable(this);
    model = new PublishingModel(table);

    table->setModel(model);

    mainLay->addWidget(table);
}
