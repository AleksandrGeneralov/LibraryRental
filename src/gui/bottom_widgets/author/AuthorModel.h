#ifndef AUTHORMODEL_H
#define AUTHORMODEL_H

#include "../BottomModel.h"

class AuthorModel : public BottomModel
{
    enum AuthorColumns
    {
        colName = 0,
        colCount = 1
    };

    Q_OBJECT

    QList<std::shared_ptr<BaseDataInfo>> authors;

public:
    AuthorModel(QObject *parent = nullptr);

    void setItems(BaseDataInfos &authors);

private:
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
};

#endif // AUTHORMODEL_H
