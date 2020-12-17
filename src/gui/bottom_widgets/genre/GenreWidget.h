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
    void setData();

private slots:
    void slotAddButtonClicked();
    void slotRemoveButtonClicked();
};

#endif // GENREWIDGET_H
