#ifndef PERSONALWIDGET_H
#define PERSONALWIDGET_H

#include <QWidget>

#include "../../DialogIncludes.h"
#include "../catalog/CatalogTable.h"
#include "../catalog/CatalogModel.h"
#include "DataStructures.h"

class PersonalWidget : public QWidget
{
    Q_OBJECT

    FullUserInfo *user;

    CatalogModel *modelBooks;
    CatalogTable *tableBooks;

public:
    PersonalWidget(FullUserInfo* user, QWidget *parent = nullptr);

private:
    void initUi();
    void setData();

private slots:
    void slotReturnButtonClicked();
};

#endif // PERSONALWIDGET_H
