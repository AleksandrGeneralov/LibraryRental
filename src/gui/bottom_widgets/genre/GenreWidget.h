#ifndef GENREWIDGET_H
#define GENREWIDGET_H

#include "../BottomWidget.h"

class GenreWidget : public BottomWidget
{
    Q_OBJECT

public:
    GenreWidget(QWidget *parent = nullptr);

private:
    void initUi();
};

#endif // GENREWIDGET_H
