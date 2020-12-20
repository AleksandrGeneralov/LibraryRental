#ifndef CATALOGMODEL_H
#define CATALOGMODEL_H

#include "../BottomModel.h"

enum CatalogType
{
    typeCatalog = 0,
    typePersonal = 1
};

class CatalogModel : public BottomModel
{

    enum CatalogColumns
    {
        colName = 0,
        colAuthor = 1,
        colGenres = 2,
        colPublishing = 3,
        colCurrCount = 4,
        colAllCount = 5,
        colCount = 6
    };

    Q_OBJECT

    QList<std::shared_ptr<Book>> books;

    int type;

public:
    explicit CatalogModel(int type, QObject *parent = nullptr);

    void setItems();
    void addItem(std::shared_ptr<Book> book);
    void removeSelectedItem(const QModelIndex &indexRemove);
    void takeSelectedItem(const QModelIndex &indexRemove, const qlonglong &userId);
    void returnSelectedItem(const QModelIndex &indexRemove, const qlonglong &userId);

private:
    void removeItemsFromBase(QStringList ids);

private:
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
};

#endif // CATALOGMODEL_H
