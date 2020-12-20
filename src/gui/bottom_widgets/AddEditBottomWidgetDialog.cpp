#include "AddEditBottomWidgetDialog.h"

#include <QRegExpValidator>

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
    connect(buttonAccept, SIGNAL(clicked()), this, SLOT(slotAccept()));
    connect(buttonReject, SIGNAL(clicked()), this, SLOT(reject()));

    buttonLay = new QHBoxLayout();
    buttonLay->addWidget(buttonAccept);
    buttonLay->addStretch();
    buttonLay->addWidget(buttonReject);
    mainLay->addLayout(buttonLay);
}

void AddEditBottomWidgetDialog::slotAccept()
{
    if (!nameEdit->text().trimmed().isEmpty())
    {
        accept();
    }
    else
    {
        MessageDialog::critical(nullptr, QString("Заполните все поля."));
    }
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

void AddEditAuthorDialog::slotAccept()
{
    if (!nameEdit->text().trimmed().isEmpty()
        && !middleNameEdit->text().trimmed().isEmpty()
        && !lastNameEdit->text().trimmed().isEmpty())
    {
        accept();
    }
    else
    {
        MessageDialog::critical(nullptr, QString("Заполните все поля."));
    }
}

AddEditBooksDialog::AddEditBooksDialog(QWidget *parent)
    : AddEditBottomWidgetDialog(parent)
{
    countLabel = new QLabel(QString("Количество"), this);
    countEdit = new QLineEdit(this);
    countEdit->setValidator(new QRegExpValidator(QRegExp("[0-9]*"), countEdit));
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
    std::shared_ptr<Book> book = std::static_pointer_cast<Book>(dataInfo);

    book->name = nameEdit->text().trimmed();
    book->allCount = countEdit->text().trimmed().toInt();
    book->currentCount = countEdit->text().trimmed().toInt();
    book->genre = selectedParams[typeGenres].values().first();
    book->publishing = selectedParams[typePublishing].values().first();
    book->authors = selectedParams[typeAuthors].values();
}

bool AddEditBooksDialog::addToBase()
{
    QStringList fields;
    QVariantList values;

    qDebug() << selectedParams[typeGenres].keys();
    qDebug() << selectedParams[typePublishing].keys();

    fields << "name"; values << nameEdit->text().trimmed();
    fields << "all_count"; values << countEdit->text().trimmed().toInt();
    fields << "current_count"; values << countEdit->text().trimmed().toInt();
    fields << "genres_id"; values << QString::number(selectedParams[typeGenres].keys().first());
    fields << "publishing_id"; values << QString::number(selectedParams[typePublishing].keys().first());
    fields << "authors_id"; values << getChooseAuthorsId().join(",");

    std::shared_ptr<QSqlDatabase> db = SqlManager::getInstance().openDB();
    if (!SqlUtils::getInstance()->sqlInsert(db.get(), "books", fields, values))
    {
        MessageDialog::critical(nullptr, QString("Ошибка добавления в базу."));
        return false;
    }
    SqlManager::getInstance().closeDB();

    return true;
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

QStringList AddEditBooksDialog::getChooseAuthorsId()
{
    QStringList res;

    QList<qlonglong> chooseIds = selectedParams[typeAuthors].keys();
    if (!chooseIds.isEmpty())
    {
        foreach (qlonglong id, chooseIds)
        {
            res << QString::number(id);
        }
    }

    return res;
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

    QMap<qlonglong, QString> selectedAuthors;
    if (selectedParams.contains(typeAuthors))
    {
        selectedAuthors = selectedParams[typeAuthors];
    }

    ChooseItemsDlg dlg(dataMap, true, this);
    dlg.setChecked(selectedAuthors);

    if (dlg.exec() == QDialog::Accepted)
    {
        selectedAuthors.clear();
        selectedAuthors = dlg.getCheckedMap();
        selectedParams[typeAuthors] = selectedAuthors;

        QStringList authors;
        foreach (QString itemName, selectedAuthors.values())
        {
            authors << itemName;
        }

        authorsLabelValue->setText(authors.join("\n"));
    }
}

void AddEditBooksDialog::slotPublishButtonClick()
{
    QMap<qlonglong, QString> dataMap;

    std::shared_ptr<QSqlDatabase> db = SqlManager::getInstance().openDB();
    QList<QSqlRecord> records;
    if (SqlUtils::getInstance()->sqlTable(db.get(), "SELECT * FROM publishing", records))
    {
        foreach (QSqlRecord record, records)
        {
            std::unique_ptr<Publishing> publish = std::make_unique<Publishing>(record);
            dataMap.insert(publish->id, publish->name);
        }
    }
    SqlManager::getInstance().closeDB();

    if (dataMap.isEmpty())
    {
        MessageDialog::information(nullptr, QString("Издательства отсутствуют в базе."));
        return;
    }

    ChooseItemsDlg dlg(dataMap, false, this);
    if (dlg.exec() == QDialog::Accepted)
    {
        QMap<qlonglong, QString> selected;
        selected = dlg.getSelected();
        qDebug() << selected;
        selectedParams[typePublishing] = selected;
        qDebug() << selectedParams[typePublishing].keys();

        QStringList publish;
        foreach (QString itemName, selected.values())
        {
            publish << itemName;
        }

        publishingLabelValue->setText(publish.join("\n"));
    }
}

void AddEditBooksDialog::slotGenresButtonClick()
{
    QMap<qlonglong, QString> dataMap;

    std::shared_ptr<QSqlDatabase> db = SqlManager::getInstance().openDB();
    QList<QSqlRecord> records;
    if (SqlUtils::getInstance()->sqlTable(db.get(), "SELECT * FROM genres", records))
    {
        foreach (QSqlRecord record, records)
        {
            std::unique_ptr<Genre> genre = std::make_unique<Genre>(record);
            dataMap.insert(genre->id, genre->name);
        }
    }
    SqlManager::getInstance().closeDB();

    if (dataMap.isEmpty())
    {
        MessageDialog::information(nullptr, QString("Жанры отсутствуют в базе."));
        return;
    }

    ChooseItemsDlg dlg(dataMap, false, this);
    if (dlg.exec() == QDialog::Accepted)
    {
        QMap<qlonglong, QString> selected;
        selected = dlg.getSelected();
        selectedParams[typeGenres] = selected;
        qDebug() << selectedParams[typeGenres].keys();

        QStringList genres;
        foreach (QString itemName, selected.values())
        {
            genres << itemName;
        }

        genresLabelValue->setText(genres.join("\n"));
    }
}

void AddEditBooksDialog::slotAccept()
{
    if (!nameEdit->text().trimmed().isEmpty()
        && !countEdit->text().trimmed().isEmpty()
        && !authorsLabelValue->text().trimmed().isEmpty()
        && !publishingLabelValue->text().trimmed().isEmpty()
        && !genresLabelValue->text().trimmed().isEmpty())
    {
        accept();
    }
    else
    {
        MessageDialog::critical(nullptr, QString("Заполните все поля."));
    }
}
