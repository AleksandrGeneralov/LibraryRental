#include "CatalogModel.h"

CatalogModel::CatalogModel(QObject *parent)
    : QStandardItemModel(parent)
{

}

void CatalogModel::setData(Books &books)
{
    this->books.clear();

    beginResetModel();
    foreach (auto &book, books)
    {
        this->books.append(book);
    }
    endResetModel();
}

int CatalogModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return books.count();
}

int CatalogModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    return colCount;
}

QVariant CatalogModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        if (section == colName)
        {
            return QString("Название");
        }
        else if (section == colAuthor)
        {
            return QString("Автор");
        }
        else if (section == colGenres)
        {
            return QString("Жанр");
        }
        else if (section == colPublishing)
        {
            return QString("Издательство");
        }
        else if (section == colCurrCount)
        {
            return QString("Количество в библиотеке");
        }
        else if (section == colAllCount)
        {
            return QString("Всего в библиотеке");
        }
    }

    return QVariant();
}

QVariant CatalogModel::data(const QModelIndex &index, int role) const
{
    int column = index.column();

    if (!index.isValid() || (column < 0 && column > books.count() - 1))
    {
        return QVariant();
    }

    std::shared_ptr<Book> book = books.at(index.row());

    if (role == Qt::DisplayRole)
    {
        if (column == colName)
        {
            return book->name;
        }
        else if (column == colAuthor)
        {
            return book->authors.join("\n");
        }
        else if (column == colGenres)
        {
            return book->genres.join("\n");
        }
        else if (column == colPublishing)
        {
            return book->publishing;
        }
        else if (column == colCurrCount)
        {
            return book->currentCount;
        }
        else if (column == colAllCount)
        {
            return book->allCount;
        }
    }

    return QVariant();
}
