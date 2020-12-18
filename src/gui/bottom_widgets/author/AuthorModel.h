#ifndef AUTHORMODEL_H
#define AUTHORMODEL_H

#include "../BottomModel.h"

class AuthorModel : public BottomModel
{
    enum AuthorColumns
    {
        colFirstName = 0,
        colMiddleName = 1,
        colLastName = 2,
        colCount = 3
    };

    Q_OBJECT

    QList<std::shared_ptr<Author>> authors;

public:
    AuthorModel(QObject *parent = nullptr);

    void setItems();
    void addItem(std::shared_ptr<Author> author);
    void removeSelectedItem(const QModelIndex &indexRemove);

private:
    void removeItemsFromBase(QStringList ids);

private:
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
};

#endif // AUTHORMODEL_H
