#include "ChooseItemsDlg.h"

ChooseItemsDlg::ChooseItemsDlg(QMap<qlonglong, QString> dataMap, QWidget *parent)
    : QDialog(parent)
{
    initUi(dataMap);
}

void ChooseItemsDlg::initUi(QMap<qlonglong, QString> dataMap)
{
    setWindowTitle(QString("Выбрать элементы"));
    setMinimumSize(450, 350);

    QVBoxLayout *mainLay = new QVBoxLayout();
    this->setLayout(mainLay);

    items = new QListWidget(this);
    setItemsValue(dataMap);
    connect(items, SIGNAL(itemChanged(QListWidgetItem *)), this, SLOT(slotItemChange(QListWidgetItem *)));

    QPushButton *acceptButton = new QPushButton(QString("Сохранить"), this);
    QPushButton *rejectButton = new QPushButton(QString("Отмена"), this);
    connect(acceptButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(rejectButton, SIGNAL(clicked()), this, SLOT(reject()));

    QHBoxLayout *buttonLay = new QHBoxLayout();
    buttonLay->addWidget(acceptButton);
    buttonLay->addStretch();
    buttonLay->addWidget(rejectButton);

    mainLay->addWidget(items);
    mainLay->addLayout(buttonLay);
}

void ChooseItemsDlg::setItemsValue(QMap<qlonglong, QString> dataMap)
{
    foreach (QString data, dataMap)
    {
        QListWidgetItem *item = new QListWidgetItem(data);
        item->setData(id, dataMap.key(data));
        item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
        item->setCheckState(Qt::Unchecked);
        items->addItem(item);
    }
}

QMap<qlonglong, QString> ChooseItemsDlg::getCheckedMap()
{
    return checkedMap;
}

void ChooseItemsDlg::slotItemChange(QListWidgetItem *item)
{
    qDebug("ChooseItemsDlg::slotItemChange");

    qlonglong itemId = item->data(id).toLongLong();

    if (checkedMap.contains(itemId)
        && item->checkState() == Qt::Unchecked)
    {
        checkedMap.remove(itemId);
    }
    else if (!checkedMap.contains(itemId)
             && item->checkState() == Qt::Checked)
    {
        checkedMap.insert(itemId, item->text().trimmed());
    }
}
