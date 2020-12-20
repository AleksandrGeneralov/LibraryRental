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

    setData();

    connect(addButton, SIGNAL(clicked()), this, SLOT(slotAddButtonClicked()));
    connect(removeButton, SIGNAL(clicked()), this, SLOT(slotRemoveButtonClicked()));
}

void CatalogWidget::setData()
{
    CatalogModel *curModel = static_cast<CatalogModel *>(model);
    curModel->setItems();
}

void CatalogWidget::slotAddButtonClicked()
{
    AddEditBooksDialog addDlg(this);

    if (addDlg.exec() == QDialog::Accepted)
    {
        CatalogModel *curModel = static_cast<CatalogModel *>(model);
        std::shared_ptr<Book> dataInfo = std::make_shared<Book>();
        addDlg.fillData(dataInfo);
        if (addDlg.addToBase())
        {
            curModel->addItem(dataInfo);
        }
    }
}

void CatalogWidget::slotRemoveButtonClicked()
{
    QModelIndex indexRemove = table->currentIndex();
    CatalogModel *curModel = static_cast<CatalogModel *>(model);
    curModel->removeSelectedItem(indexRemove);
}
