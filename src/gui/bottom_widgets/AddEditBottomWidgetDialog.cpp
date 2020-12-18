#include "AddEditBottomWidgetDialog.h"

#include "data_base/SqlManager.h"
#include "../MessageDialog.h"
#include "ChooseItemsDlg.h"

AddEditBottomWidgetDialog::AddEditBottomWidgetDialog(QWidget *parent)
    : QDialog(parent)
{
    initUi();
}

void AddEditBottomWidgetDialog::fillData(std::shared_ptr<BaseDataInfo> dataInfo)
{
    dataInfo->name = nameEdit->text().trimmed();
}

void AddEditBottomWidgetDialog::initUi()
{
    setMinimumWidth(300);
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
    connect(buttonAccept, SIGNAL(clicked()), this, SLOT(accept()));
    connect(buttonReject, SIGNAL(clicked()), this, SLOT(reject()));

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
    countLabel = new QLabel(QString("Количество"), this);
    countEdit = new QLineEdit(this);
    fieldsLay->addWidget(countLabel, fieldsLay->rowCount(), 0, 1, 1);
    fieldsLay->addWidget(countEdit, fieldsLay->rowCount() - 1, 1, 1, 1);

    authorsLabelName = new QLabel(QString("Авторы"), this);
    authorsLabelValue = createLabelValue();
    selectAuthorButton = createButton(SLOT(slotAuthorButtonClick()));
    QHBoxLayout *authorLay = new QHBoxLayout();
    authorLay->addWidget(authorsLabelValue);
    authorLay->addWidget(selectAuthorButton);
    fieldsLay->addWidget(authorsLabelName, fieldsLay->rowCount(), 0, 1, 1);
    fieldsLay->addLayout(authorLay, fieldsLay->rowCount() - 1, 1, 1, 1);

    publishingLabelName = new QLabel(QString("Издательство"), this);
    publishingLabelValue = createLabelValue();
    selectPublishButton = createButton(SLOT(slotPublishButtonClick()));
    QHBoxLayout *publishLay = new QHBoxLayout();
    publishLay->addWidget(publishingLabelValue);
    publishLay->addWidget(selectPublishButton);
    fieldsLay->addWidget(publishingLabelName, fieldsLay->rowCount(), 0, 1, 1);
    fieldsLay->addLayout(publishLay, fieldsLay->rowCount() - 1, 1, 1, 1);

    genresLabelName = new QLabel(QString("Жанр"), this);
    genresLabelValue = createLabelValue();
    selectGenresButton = createButton(SLOT(slotGenresButtonClick()));
    QHBoxLayout *genresLay = new QHBoxLayout();
    genresLay->addWidget(genresLabelValue);
    genresLay->addWidget(selectGenresButton);
    fieldsLay->addWidget(genresLabelName, fieldsLay->rowCount(), 0, 1, 1);
    fieldsLay->addLayout(genresLay, fieldsLay->rowCount() - 1, 1, 1, 1);
}

void AddEditBooksDialog::fillData(std::shared_ptr<BaseDataInfo> dataInfo)
{

}

QPushButton *AddEditBooksDialog::createButton(const char *slot)
{
    QPushButton *button = new QPushButton(QString("..."), this);
    connect(button, SIGNAL(clicked()), this, slot);
    button->setMaximumWidth(30);

    return button;
}

QLabel *AddEditBooksDialog::createLabelValue()
{
    QLabel *labelValue = new QLabel(this);
    labelValue->setStyleSheet(QString("QLabel"
                                      "{"
                                          "background: white;"
                                          "border: 1px solid gray;"
                                      "}"));

    labelValue->setWordWrap(true);

    return labelValue;
}

void AddEditBooksDialog::slotAuthorButtonClick()
{
    QMap<qlonglong, QString> dataMap;

    std::shared_ptr<QSqlDatabase> db = SqlManager::getInstance().openDB();
    QList<QSqlRecord> records;
    if (SqlUtils::getInstance()->sqlTable(db.get(), "SELECT * FROM authors", records))
    {
        foreach (QSqlRecord record, records)
        {
            std::unique_ptr<Author> author = std::make_unique<Author>(record);
            dataMap.insert(author->id, author->name);
        }
    }
    SqlManager::getInstance().closeDB();

    if (dataMap.isEmpty())
    {
        MessageDialog::information(nullptr, QString("Авторы отсутствуют в базе."));
        return;
    }

    ChooseItemsDlg dlg(dataMap, this);
    if (dlg.exec() == QDialog::Accepted)
    {
        QMap<qlonglong, QString> checked = dlg.getCheckedMap();

        QStringList authors;
        foreach (QString itemName, checked.values())
        {
            authors << itemName;
        }

        authorsLabelValue->setText(authors.join("\n"));
    }
}

void AddEditBooksDialog::slotPublishButtonClick()
{

}

void AddEditBooksDialog::slotGenresButtonClick()
{

}
