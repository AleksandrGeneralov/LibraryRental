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

    setData();

    connect(addButton, SIGNAL(clicked()), this, SLOT(slotAddButtonClicked()));
    connect(removeButton, SIGNAL(clicked()), this, SLOT(slotRemoveButtonClicked()));
}

void AuthorWidget::setData()
{
    AuthorModel *curModel = static_cast<AuthorModel *>(model);
    curModel->setItems();
}

void AuthorWidget::slotAddButtonClicked()
{
    AddEditAuthorDialog addDlg(this);

    if (addDlg.exec() == QDialog::Accepted)
    {
        AuthorModel *curModel = static_cast<AuthorModel *>(model);
        std::shared_ptr<Author> dataInfo = std::make_shared<Author>();
        addDlg.fillData(dataInfo);
        curModel->addItem(dataInfo);
    }
}

void AuthorWidget::slotRemoveButtonClicked()
{
    QModelIndex indexRemove = table->currentIndex();
    AuthorModel *curModel = static_cast<AuthorModel *>(model);
    curModel->removeSelectedItem(indexRemove);
}
