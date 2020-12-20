#ifndef CATALOGWIDGET_H
#define CATALOGWIDGET_H

#include "../BottomWidget.h"

class CatalogWidget : public BottomWidget
{
    Q_OBJECT

    qlonglong userId;

public:
    CatalogWidget(qlonglong userId, QWidget *parent = nullptr);

private:
    void initUi();
    void setData();

private slots:
    void slotAddButtonClicked();
    void slotRemoveButtonClicked();
    void slotTakeButtonClicked();
};

#endif // CATALOGWIDGET_H
