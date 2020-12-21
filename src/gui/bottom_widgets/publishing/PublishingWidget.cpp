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

    setData();

    connect(addButton, SIGNAL(clicked()), this, SLOT(slotAddButtonClicked()));
    connect(removeButton, SIGNAL(clicked()), this, SLOT(slotRemoveButtonClicked()));
}

void PublishingWidget::setData()
{
    PublishingModel *curModel = static_cast<PublishingModel *>(model);
    curModel->setItems();
}

void PublishingWidget::slotAddButtonClicked()
{
    AddEditBottomWidgetDialog addDlg(this);

    if (addDlg.exec() == QDialog::Accepted)
    {
        PublishingModel *curModel = static_cast<PublishingModel *>(model);
        std::shared_ptr<Publishing> dataInfo = std::make_shared<Publishing>();
        addDlg.fillData(dataInfo);
        curModel->addItem(dataInfo);
    }
}

void PublishingWidget::slotRemoveButtonClicked()
{
    QModelIndex indexRemove = table->currentIndex();
    PublishingModel *curModel = static_cast<PublishingModel *>(model);
    curModel->removeSelectedItem(indexRemove);
}
