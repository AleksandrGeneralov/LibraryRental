#ifndef BOTTOMMODEL_H
#define BOTTOMMODEL_H

#include <QStandardItemModel>
#include "DataStructures.h"

class BottomModel : public QStandardItemModel
{
    Q_OBJECT

protected:
    BottomModel(QObject *parent = nullptr) : QStandardItemModel(parent) {}

public:
    virtual void setData(BaseDataInfos &books) = 0;

protected:
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const = 0;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const = 0;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const = 0;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const = 0;
};

#endif // BOTTOMMODEL_H
