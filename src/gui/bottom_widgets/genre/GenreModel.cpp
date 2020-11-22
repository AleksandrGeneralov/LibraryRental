#include "GenreModel.h"

GenreModel::GenreModel(QObject *parent)
    : BottomModel(parent)
{

}

void GenreModel::setData(BaseDataInfos &genres)
{
    this->genres.clear();

    beginResetModel();
    foreach (auto &genre, genres)
    {
        this->genres.append(genre);
    }
    endResetModel();
}

int GenreModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return genres.count();
}

int GenreModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return colCount;
}

QVariant GenreModel::headerData(int section, Qt::Orientation orientation, int role) const
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

QVariant GenreModel::data(const QModelIndex &index, int role) const
{
    int column = index.column();

    if (!index.isValid() || (column < 0 && column > genres.count() - 1))
    {
        return QVariant();
    }

    std::shared_ptr<Genre> genre = std::static_pointer_cast<Genre>(genres.at(index.row()));

    if (role == Qt::DisplayRole)
    {
        if (column == colName)
        {
            return genre->name;
        }
    }

    return QVariant();
}
