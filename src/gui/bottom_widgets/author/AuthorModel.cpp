#include "AuthorModel.h"

AuthorModel::AuthorModel(QObject *parent)
    : BottomModel(parent)
{

}

void AuthorModel::setItems(BaseDataInfos &authors)
{
    this->authors.clear();

    beginResetModel();
    foreach (auto &author, authors)
    {
        this->authors.append(author);
    }
    endResetModel();
}

int AuthorModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return authors.count();
}

int AuthorModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return colCount;
}

QVariant AuthorModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        if (section == colName)
        {
            return QString("Имя");
        }
    }

    return QVariant();
}

QVariant AuthorModel::data(const QModelIndex &index, int role) const
{
    int column = index.column();

    if (!index.isValid() || (column < 0 && column > authors.count() - 1))
    {
        return QVariant();
    }

    std::shared_ptr<Author> author = std::static_pointer_cast<Author>(authors.at(index.row()));

    if (role == Qt::DisplayRole)
    {
        if (column == colName)
        {
            return author->name;
        }
    }

    return QVariant();
}
