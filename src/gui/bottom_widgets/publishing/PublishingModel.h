#ifndef PUBLISHINGMODEL_H
#define PUBLISHINGMODEL_H

#include "../BottomModel.h"

class PublishingModel : public BottomModel
{
    enum CatalogColumns
    {
        colName = 0,
        colCount = 1
    };

    Q_OBJECT

    QList<std::shared_ptr<BaseDataInfo>> publishings;

public:
    PublishingModel(QObject *parent = nullptr);

    void setData(BaseDataInfos &publishings);

private:
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
};

#endif // PUBLISHINGMODEL_H
