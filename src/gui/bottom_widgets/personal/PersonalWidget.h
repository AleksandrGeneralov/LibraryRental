#ifndef PERSONALWIDGET_H
#define PERSONALWIDGET_H

#include "../BottomWidget.h"

class PersonalWidget : public BottomWidget
{
    Q_OBJECT
public:
    PersonalWidget(QWidget *parent = nullptr);

private:
    void initUi();
};

#endif // PERSONALWIDGET_H
