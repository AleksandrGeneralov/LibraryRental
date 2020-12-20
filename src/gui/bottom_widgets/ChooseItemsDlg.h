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
        id = 0x0010
    };

    QMap<qlonglong, QString> checkedMap;
    QListWidget *items;
    bool isChecked;

public:
    explicit ChooseItemsDlg(QMap<qlonglong, QString> dataMap, bool isChecked = false, QWidget *parent = nullptr);

    QMap<qlonglong, QString> getCheckedMap();
    void setChecked(QMap<qlonglong, QString> checkedItems);
    QMap<qlonglong, QString> getSelected();

private:
    void initUi(QMap<qlonglong, QString> dataMap);

    void setItemsValue(QMap<qlonglong, QString> dataMap);

private slots:
    void slotItemChange(QListWidgetItem *item);
};

#endif // CHOOSEITEMSDLG_H
