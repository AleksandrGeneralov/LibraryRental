#ifndef BOTTOMMODEL_H
#define BOTTOMMODEL_H

#include <QAbstractTableModel>
#include "DataStructures.h"

class BottomModel : public QAbstractTableModel
{
    Q_OBJECT

protected:
    BottomModel(QObject *parent = nullptr) : QAbstractTableModel(parent) {}
};

#endif // BOTTOMMODEL_H
