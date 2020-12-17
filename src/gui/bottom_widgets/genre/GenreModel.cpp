#include "GenreModel.h"
#include "data_base/SqlManager.h"
#include "../../MessageDialog.h"

GenreModel::GenreModel(QObject *parent)
    : BottomModel(parent)
{

}

void GenreModel::setItems()
{
    qDebug("GenreModel::setData");
    std::shared_ptr<QSqlDatabase> db = SqlManager::getInstance().openDB();

    QList<QSqlRecord> records;
    if (SqlUtils::getInstance()->sqlTable(db.get(), "SELECT * FROM genres", records))
    {
        beginResetModel();
        genres.clear();
        foreach (QSqlRecord record, records)
        {
            std::shared_ptr<Genre> genre = std::make_shared<Genre>(record);
            genres.append(genre);
        }
        endResetModel();
    }
    SqlManager::getInstance().closeDB();
}

void GenreModel::addItem(std::shared_ptr<Genre> genre)
{
    std::shared_ptr<QSqlDatabase> db = SqlManager::getInstance().openDB();

    QStringList fields;
    QVariantList values;
    genre->fillSqlData(fields, values);

    if (SqlUtils::getInstance()->sqlInsert(db.get(), "genres", fields, values))
    {
        beginInsertRows(QModelIndex(), genres.count(), genres.count());
        genres.append(genre);
        endInsertRows();
    }
    else
    {
        MessageDialog::critical(nullptr, QString("Ошибка добавления в базу."));
    }
    SqlManager::getInstance().closeDB();
}

void GenreModel::removeSelectedItem(const QModelIndex &indexRemove)
{
    int row = indexRemove.row();

    if (row < genres.count())
    {
        QString removeId = QString::number(genres.at(row)->id);

        beginResetModel();
        genres.removeAt(row);
        endResetModel();

        removeItemsFromBase(QStringList() << removeId);
    }
    else
    {
        MessageDialog::critical(nullptr, QString("Ошибка удаления."));
    }
}

void GenreModel::removeItemsFromBase(QStringList ids)
{
    std::shared_ptr<QSqlDatabase> db = SqlManager::getInstance().openDB();

    SqlUtils::getInstance()->sqlExec(db.get(), QString("DELETE FROM genres WHERE id=%1").arg(ids.join(",")));

    SqlManager::getInstance().closeDB();
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

    if (!index.isValid() || index.row() > genres.count() - 1)
    {
        return QVariant();
    }

    std::shared_ptr<Genre> genre = genres.at(index.row());

    if (role == Qt::DisplayRole)
    {
        if (column == colName)
        {
            return genre->name;
        }
    }

    return QVariant();
}
