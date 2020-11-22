#include "PublishingModel.h"

PublishingModel::PublishingModel(QObject *parent)
    : BottomModel(parent)
{

}

void PublishingModel::setData(BaseDataInfos &publishings)
{
    this->publishings.clear();

    beginResetModel();
    foreach (auto &publishing, publishings)
    {
        this->publishings.append(publishing);
    }
    endResetModel();
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
