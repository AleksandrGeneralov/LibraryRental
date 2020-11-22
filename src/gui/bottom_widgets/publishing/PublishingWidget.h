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
};

#endif // PUBLISHINGWIDGET_H
