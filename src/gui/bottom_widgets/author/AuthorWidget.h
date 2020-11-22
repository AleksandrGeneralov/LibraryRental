#ifndef AUTHORWIDGET_H
#define AUTHORWIDGET_H

#include "../BottomWidget.h"

class AuthorWidget : public BottomWidget
{
    Q_OBJECT
public:
    AuthorWidget(QWidget *parent);

private:
    void initUi();
};

#endif // AUTHORWIDGET_H
