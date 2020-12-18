#ifndef CATALOGWIDGET_H
#define CATALOGWIDGET_H

#include "../BottomWidget.h"

class CatalogWidget : public BottomWidget
{
    Q_OBJECT

public:
    CatalogWidget(QWidget *parent = nullptr);

private:
    void initUi();
    void setData();

private slots:
    void slotAddButtonClicked();
    void slotRemoveButtonClicked();
};

#endif // CATALOGWIDGET_H
