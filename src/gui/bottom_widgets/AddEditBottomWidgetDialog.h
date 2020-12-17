#ifndef ADDEDITBOTTOMWIDGETDIALOG_H
#define ADDEDITBOTTOMWIDGETDIALOG_H

#include <QWidget>
#include "../DialogIncludes.h"
#include "DataStructures.h"

class AddEditBottomWidgetDialog : public QDialog
{
    Q_OBJECT

protected:
    QVBoxLayout *mainLay;
    QGridLayout *fieldsLay;
    QHBoxLayout *buttonLay;

    QLabel *nameLabel;
    QLineEdit *nameEdit;

    QPushButton *buttonAccept;
    QPushButton *buttonReject;

public:
    explicit AddEditBottomWidgetDialog(QWidget *parent = nullptr);

    virtual void fillData(std::shared_ptr<BaseDataInfo> dataInfo);

protected:
    void initUi();
};

class AddEditAuthorDialog : public AddEditBottomWidgetDialog
{
    Q_OBJECT

    QLabel *middleNameLabel;
    QLineEdit *middleNameEdit;

    QLabel *lastNameLabel;
    QLineEdit *lastNameEdit;

public:
    explicit AddEditAuthorDialog(QWidget *parent = nullptr);

    void fillData(std::shared_ptr<BaseDataInfo> dataInfo);

protected:
    void initUi();
};

class AddEditBooksDialog : public AddEditBottomWidgetDialog
{
    Q_OBJECT

    QLabel *middleNameLabel;
    QLineEdit *middleNameEdit;

    QLabel *lastNameLabel;
    QLineEdit *lastNameEdit;

public:
    explicit AddEditBooksDialog(QWidget *parent = nullptr);

    void fillData(std::shared_ptr<BaseDataInfo> dataInfo);

protected:
    void initUi();
};

#endif // ADDEDITBOTTOMWIDGETDIALOG_H
