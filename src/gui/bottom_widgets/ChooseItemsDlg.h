#ifndef CHOOSEITEMSDLG_H
#define CHOOSEITEMSDLG_H

#include <QDialog>
#include <QListWidget>
#include "../DialogIncludes.h"

class ChooseItemsDlg : public QDialog
{
    Q_OBJECT

    enum Roles
    {
        id = 0
    };

    QMap<qlonglong, QString> checkedMap;
    QListWidget *items;

public:
    explicit ChooseItemsDlg(QMap<qlonglong, QString> dataMap, QWidget *parent = nullptr);

    QMap<qlonglong, QString> getCheckedMap();

private:
    void initUi(QMap<qlonglong, QString> dataMap);

    void setItemsValue(QMap<qlonglong, QString> dataMap);


private slots:
    void slotItemChange(QListWidgetItem *item);
};

#endif // CHOOSEITEMSDLG_H
