#ifndef PUBLISHINGWIDGET_H
#define PUBLISHINGWIDGET_H

#include "../BottomWidget.h"

class PublishingWidget : public BottomWidget
{
    Q_OBJECT

public:
    PublishingWidget(QWidget *parent = nullptr);

private:
    void initUi();
    void setData();

private slots:
    void slotAddButtonClicked();
    void slotRemoveButtonClicked();
};

#endif // PUBLISHINGWIDGET_H
