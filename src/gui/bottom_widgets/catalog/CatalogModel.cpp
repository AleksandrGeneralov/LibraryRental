#include "CatalogModel.h"

#include "data_base/SqlManager.h"
#include "../../MessageDialog.h"

CatalogModel::CatalogModel(QObject *parent)
    : BottomModel(parent)
{

}

void CatalogModel::setItems()
{
    std::shared_ptr<QSqlDatabase> db = SqlManager::getInstance().openDB();

    QString query = QString("SELECT * FROM books LEFT JOIN genres ON books.genres_id=genres.id");
    query += QString(" LEFT JOIN publishing ON books.publishing_id=publishing.id");
//    query += QString(" LEFT JOIN authors ON authors.id IN (books.authors_id)");

    QList<QSqlRecord> records;
    if (SqlUtils::getInstance()->sqlTable(db.get(), query, records))
    {
        qDebug() << records.count();
        if (records.count() > 0)
        {
            QSqlRecord rec = records.first();
            qDebug() << rec.count();
            beginResetModel();
            books.clear();
            foreach (QSqlRecord record, records)
            {
                QList<QSqlRecord> authorRecords;
                if (SqlUtils::getInstance()->sqlTable(db.get(), QString("SELECT * FROM authors WHERE id IN (%1)")
                                                                .arg(record.value("authors_id").toString()), authorRecords))
                {
                    if (authorRecords.isEmpty())
                    {
                        continue;
                    }

                    std::shared_ptr<Book> author = std::make_shared<Book>(record, authorRecords);
                    books.append(author);
                }
            }
            endResetModel();
        }
    }
    SqlManager::getInstance().closeDB();
}

void CatalogModel::addItem(std::shared_ptr<Book> book)
{
    beginInsertRows(QModelIndex(), books.count(), books.count());
    books.append(book);
    endInsertRows();
}

void CatalogModel::removeSelectedItem(const QModelIndex &indexRemove)
{
    if (!indexRemove.isValid())
    {
        return;
    }

    int row = indexRemove.row();
    qDebug() << row;

    if (row < books.count())
    {
        QString removeId = QString::number(books.at(row)->id);

        beginResetModel();
        books.removeAt(row);
        endResetModel();

        removeItemsFromBase(QStringList() << removeId);
    }
    else
    {
        MessageDialog::critical(nullptr, QString("Ошибка удаления."));
    }
}

void CatalogModel::removeItemsFromBase(QStringList ids)
{
    std::shared_ptr<QSqlDatabase> db = SqlManager::getInstance().openDB();

    SqlUtils::getInstance()->sqlExec(db.get(), QString("DELETE FROM books WHERE id=%1").arg(ids.join(",")));

    SqlManager::getInstance().closeDB();
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

    if (!index.isValid() || index.row() > books.count() - 1)
    {
        return QVariant();
    }

    std::shared_ptr<Book> book = std::static_pointer_cast<Book>(books.at(index.row()));

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
            return book->genre;
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
    else if (role == Qt::TextAlignmentRole)
    {
        return Qt::AlignCenter;
    }

    return QVariant();
}
