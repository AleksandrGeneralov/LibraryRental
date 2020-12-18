#include "AuthorModel.h"

#include "data_base/SqlManager.h"
#include "../../MessageDialog.h"

AuthorModel::AuthorModel(QObject *parent)
    : BottomModel(parent)
{

}

void AuthorModel::setItems()
{
    std::shared_ptr<QSqlDatabase> db = SqlManager::getInstance().openDB();

    QList<QSqlRecord> records;
    if (SqlUtils::getInstance()->sqlTable(db.get(), "SELECT * FROM authors", records))
    {
        beginResetModel();
        authors.clear();
        foreach (QSqlRecord record, records)
        {
            std::shared_ptr<Author> author = std::make_shared<Author>(record);
            authors.append(author);
        }
        endResetModel();
    }
    SqlManager::getInstance().closeDB();
}

void AuthorModel::addItem(std::shared_ptr<Author> author)
{
    std::shared_ptr<QSqlDatabase> db = SqlManager::getInstance().openDB();

    QStringList fields;
    QVariantList values;
    author->fillSqlData(fields, values);

    if (SqlUtils::getInstance()->sqlInsert(db.get(), "authors", fields, values))
    {
        beginInsertRows(QModelIndex(), authors.count(), authors.count());
        authors.append(author);
        endInsertRows();
    }
    else
    {
        MessageDialog::critical(nullptr, QString("Ошибка добавления в базу."));
    }
    SqlManager::getInstance().closeDB();
}

void AuthorModel::removeSelectedItem(const QModelIndex &indexRemove)
{
    if (!indexRemove.isValid())
    {
        return;
    }

    int row = indexRemove.row();
    qDebug() << row;

    if (row < authors.count())
    {
        QString removeId = QString::number(authors.at(row)->id);

        beginResetModel();
        authors.removeAt(row);
        endResetModel();

        removeItemsFromBase(QStringList() << removeId);
    }
    else
    {
        MessageDialog::critical(nullptr, QString("Ошибка удаления."));
    }
}

void AuthorModel::removeItemsFromBase(QStringList ids)
{
    std::shared_ptr<QSqlDatabase> db = SqlManager::getInstance().openDB();

    SqlUtils::getInstance()->sqlExec(db.get(), QString("DELETE FROM genres WHERE id=%1").arg(ids.join(",")));

    SqlManager::getInstance().closeDB();
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
        if (section == colFirstName)
        {
            return QString("Фамилия");
        }
        else if (section == colMiddleName)
        {
            return QString("Имя");
        }
        else if (section == colLastName)
        {
            return QString("Отчество");
        }
    }

    return QVariant();
}

QVariant AuthorModel::data(const QModelIndex &index, int role) const
{
    int column = index.column();

    if (!index.isValid() || index.row() > authors.count() - 1)
    {
        return QVariant();
    }

    std::shared_ptr<Author> author = authors.at(index.row());

    if (role == Qt::DisplayRole)
    {
        if (column == colFirstName)
        {
            return author->firstName;
        }
        else if (column == colMiddleName)
        {
            return author->middleName;
        }
        else if (column == colLastName)
        {
            return author->lastName;
        }
    }
    else if (role == Qt::TextAlignmentRole)
    {
        return Qt::AlignCenter;
    }

    return QVariant();
}
