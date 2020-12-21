#include "GenreWidget.h"

#include "GenreModel.h"
#include "GenreTable.h"
#include "data_base/SqlManager.h"

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

    setData();

    connect(addButton, SIGNAL(clicked()), this, SLOT(slotAddButtonClicked()));
    connect(removeButton, SIGNAL(clicked()), this, SLOT(slotRemoveButtonClicked()));
}

void GenreWidget::setData()
{
    GenreModel *curModel = static_cast<GenreModel *>(model);
    curModel->setItems();
}

void GenreWidget::slotAddButtonClicked()
{
    AddEditBottomWidgetDialog addDlg(this);

    if (addDlg.exec() == QDialog::Accepted)
    {
        GenreModel *curModel = static_cast<GenreModel *>(model);
        std::shared_ptr<Genre> dataInfo = std::make_shared<Genre>();
        addDlg.fillData(dataInfo);
        curModel->addItem(dataInfo);
    }
}

void GenreWidget::slotRemoveButtonClicked()
{
    QModelIndex indexRemove = table->currentIndex();
    GenreModel *curModel = static_cast<GenreModel *>(model);
    curModel->removeSelectedItem(indexRemove);
}
