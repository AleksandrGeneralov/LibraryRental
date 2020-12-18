#ifndef BOTTOMWIDGET_H
#define BOTTOMWIDGET_H

#include <QWidget>
#include "../DialogIncludes.h"

#include "BottomModel.h"
#include "BottomTable.h"
#include "AddEditBottomWidgetDialog.h"

class BottomWidget : public QWidget
{
    Q_OBJECT

protected:
    QVBoxLayout *mainLay;
    QHBoxLayout *buttonLay;

    QPushButton *addButton;
    QPushButton *removeButton;

    BottomTable *table;
    BottomModel *model;

protected:
    BottomWidget(QWidget *parent = nullptr) : QWidget(parent)
    {
        mainLay = new QVBoxLayout();
        this->setLayout(mainLay);

        addButton = new QPushButton(QString("Добавить"), this);
        removeButton = new QPushButton(QString("Удалить"), this);

        buttonLay = new QHBoxLayout();
        buttonLay->addWidget(addButton);
        buttonLay->addWidget(removeButton);
        buttonLay->addStretch();
        mainLay->addLayout(buttonLay);
    }
};

#endif // BOTTOMWIDGET_H
