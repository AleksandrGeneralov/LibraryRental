#include "AddEditBottomWidgetDialog.h"

AddEditBottomWidgetDialog::AddEditBottomWidgetDialog(QWidget *parent)
    : QWidget(parent)
{
    initUi();
}

void AddEditBottomWidgetDialog::fillData(std::shared_ptr<BaseDataInfo> dataInfo)
{
    dataInfo->name = nameEdit->text().trimmed();
}

void AddEditBottomWidgetDialog::initUi()
{
    mainLay = new QVBoxLayout();
    this->setLayout(mainLay);

    fieldsLay = new QGridLayout();
    mainLay->addLayout(fieldsLay);

    nameLabel = new QLabel(QString("Название"), this);
    nameEdit = new QLineEdit(this);
    fieldsLay->addWidget(nameLabel, fieldsLay->rowCount(), 0, 1, 1);
    fieldsLay->addWidget(nameEdit, fieldsLay->rowCount() - 1, 1, 1, 1);

    buttonAccept = new QPushButton(QString("Применить"), this);
    buttonReject = new QPushButton(QString("Отмена"), this);

    buttonLay = new QHBoxLayout();
    buttonLay->addWidget(buttonAccept);
    buttonLay->addStretch();
    buttonLay->addWidget(buttonReject);
    mainLay->addLayout(buttonLay);
}

AddEditAuthorDialog::AddEditAuthorDialog(QWidget *parent)
    : AddEditBottomWidgetDialog(parent)
{
    initUi();
}

void AddEditAuthorDialog::fillData(std::shared_ptr<BaseDataInfo> dataInfo)
{
    std::shared_ptr<Author> author = std::static_pointer_cast<Author>(dataInfo);

    author->firstName = nameEdit->text().trimmed();
    author->middleName = middleNameEdit->text().trimmed();
    author->lastName = lastNameEdit->text().trimmed();
}

void AddEditAuthorDialog::initUi()
{
    nameLabel->setText("Имя");

    middleNameLabel = new QLabel(QString("Отчество"), this);
    middleNameEdit = new QLineEdit(this);
    fieldsLay->addWidget(middleNameLabel, fieldsLay->rowCount(), 0, 1, 1);
    fieldsLay->addWidget(middleNameEdit, fieldsLay->rowCount() - 1, 1, 1, 1);

    lastNameLabel = new QLabel(QString("Фамилия"), this);
    lastNameEdit = new QLineEdit(this);
    fieldsLay->addWidget(lastNameLabel, fieldsLay->rowCount(), 0, 1, 1);
    fieldsLay->addWidget(lastNameEdit, fieldsLay->rowCount() - 1, 1, 1, 1);
}

AddEditBooksDialog::AddEditBooksDialog(QWidget *parent)
    : AddEditBottomWidgetDialog(parent)
{

}

void AddEditBooksDialog::fillData(std::shared_ptr<BaseDataInfo> dataInfo)
{

}
