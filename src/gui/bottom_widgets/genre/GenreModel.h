#ifndef GENREMODEL_H
#define GENREMODEL_H

#include "../BottomModel.h"

class GenreModel : public BottomModel
{
    enum GenreColumns
    {
        colName = 0,
        colCount = 1
    };

    Q_OBJECT

    QList<std::shared_ptr<Genre>> genres;

public:
    GenreModel(QObject *parent = nullptr);

    void setItems();
    void addItem(std::shared_ptr<Genre> genre);
    void removeSelectedItem(const QModelIndex &indexRemove);

private:
    void removeItemsFromBase(QStringList ids);

private:
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QVariant data(const QModelIndex &index, int role) const;
};

#endif // GENREMODEL_H
