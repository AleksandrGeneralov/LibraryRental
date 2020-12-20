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

private slots:
    void slotAccept();
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

private slots:
    void slotAccept();
};

class AddEditBooksDialog : public AddEditBottomWidgetDialog
{
    Q_OBJECT

    enum HashTypes
    {
        typeAuthors = 0,
        typePublishing = 1,
        typeGenres = 2
    };

    QLabel *countLabel;
    QLineEdit *countEdit;

    QLabel *authorsLabelName;
    QLabel *authorsLabelValue;
    QPushButton *selectAuthorButton;

    QLabel *publishingLabelName;
    QLabel *publishingLabelValue;
    QPushButton *selectPublishButton;

    QLabel *genresLabelName;
    QLabel *genresLabelValue;
    QPushButton *selectGenresButton;

    QHash<int, QMap<qlonglong, QString>> selectedParams;

public:
    explicit AddEditBooksDialog(QWidget *parent = nullptr);

    void fillData(std::shared_ptr<BaseDataInfo> dataInfo);
    bool addToBase();

protected:
    void initUi();

private:
    QPushButton *createButton(const char *slot);
    QLabel *createLabelValue();

    QStringList getChooseAuthorsId();

private slots:
    void slotAuthorButtonClick();
    void slotPublishButtonClick();
    void slotGenresButtonClick();
    void slotAccept();
};

#endif // ADDEDITBOTTOMWIDGETDIALOG_H
