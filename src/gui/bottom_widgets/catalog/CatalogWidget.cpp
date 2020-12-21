#include "CatalogWidget.h"

#include "CatalogTable.h"
#include "CatalogModel.h"

CatalogWidget::CatalogWidget(qlonglong userId, QWidget *parent)
    : BottomWidget(parent), userId(userId)
{
    initUi();
}

void CatalogWidget::initUi()
{
    table = new CatalogTable(this);
    model = new CatalogModel(typeCatalog, table);

    table->setModel(model);

    QFontMetrics metrics(table->horizontalHeader()->font());
    int shift = 15;

    table->setColumnWidth(0, 1.5 * metrics.boundingRect("Название").width() + shift);
    table->setColumnWidth(1, 3 * metrics.boundingRect("Автор").width() + shift);
    table->setColumnWidth(2, 3 * metrics.boundingRect("Жанр").width() + shift);
    table->setColumnWidth(3, 1.5 * metrics.boundingRect("Издательство").width() + shift);
    table->setColumnWidth(4, metrics.boundingRect("Доступно в библиотеке").width() + shift);
    table->setColumnWidth(5, metrics.boundingRect("Всего в библиотеке").width() + shift);

    table->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    mainLay->addWidget(table);

    QPushButton *takeButton = new QPushButton(QString("Взять в прокат"), this);
    connect(takeButton, SIGNAL(clicked()), this, SLOT(slotTakeButtonClicked()));
    buttonLay->addWidget(takeButton);

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

void CatalogWidget::slotTakeButtonClicked()
{
    QModelIndex indexTake = table->currentIndex();
    CatalogModel *curModel = static_cast<CatalogModel *>(model);
    curModel->takeSelectedItem(indexTake, userId);
}
