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

    QList<std::shared_ptr<BaseDataInfo>> genres;

public:
    GenreModel(QObject *parent = nullptr);

    void setData(BaseDataInfos &genres);

private:
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
};

#endif // GENREMODEL_H
