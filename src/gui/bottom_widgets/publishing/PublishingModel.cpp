#include "PublishingModel.h"

#include "data_base/SqlManager.h"
#include "../../MessageDialog.h"

PublishingModel::PublishingModel(QObject *parent)
    : BottomModel(parent)
{

}

void PublishingModel::setItems()
{
    qDebug("PublishingModel::setData");
    std::shared_ptr<QSqlDatabase> db = SqlManager::getInstance().openDB();

    QList<QSqlRecord> records;
    if (SqlUtils::getInstance()->sqlTable(db.get(), "SELECT * FROM publishing", records))
    {
        beginResetModel();
        publishings.clear();
        foreach (QSqlRecord record, records)
        {
            std::shared_ptr<Publishing> publishing = std::make_shared<Publishing>(record);
            publishings.append(publishing);
        }
        endResetModel();
    }
    SqlManager::getInstance().closeDB();
}

void PublishingModel::addItem(std::shared_ptr<Publishing> publishing)
{
    std::shared_ptr<QSqlDatabase> db = SqlManager::getInstance().openDB();

    QStringList fields;
    QVariantList values;
    publishing->fillSqlData(fields, values);

    if (SqlUtils::getInstance()->sqlInsert(db.get(), "publishing", fields, values))
    {
        beginInsertRows(QModelIndex(), publishings.count(), publishings.count());
        publishings.append(publishing);
        endInsertRows();
    }
    else
    {
        MessageDialog::critical(nullptr, QString("Ошибка добавления в базу."));
    }
    SqlManager::getInstance().closeDB();
}

void PublishingModel::removeSelectedItem(const QModelIndex &indexRemove)
{
    int row = indexRemove.row();

    if (row < publishings.count())
    {
        QString removeId = QString::number(publishings.at(row)->id);

        beginResetModel();
        publishings.removeAt(row);
        endResetModel();

        removeItemsFromBase(QStringList() << removeId);
    }
    else
    {
        MessageDialog::critical(nullptr, QString("Ошибка удаления."));
    }
}

void PublishingModel::removeItemsFromBase(QStringList ids)
{
    std::shared_ptr<QSqlDatabase> db = SqlManager::getInstance().openDB();

    SqlUtils::getInstance()->sqlExec(db.get(), QString("DELETE FROM publishing WHERE id=%1").arg(ids.join(",")));

    SqlManager::getInstance().closeDB();
}

int PublishingModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return publishings.count();
}

int PublishingModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return colCount;
}

QVariant PublishingModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        if (section == colName)
        {
            return QString("Название");
        }
    }

    return QVariant();
}

QVariant PublishingModel::data(const QModelIndex &index, int role) const
{
    int column = index.column();

    if (!index.isValid() || (column < 0 && column > publishings.count() - 1))
    {
        return QVariant();
    }

    std::shared_ptr<Publishing> publishing = std::static_pointer_cast<Publishing>(publishings.at(index.row()));

    if (role == Qt::DisplayRole)
    {
        if (column == colName)
        {
            return publishing->name;
        }
    }

    return QVariant();
}
