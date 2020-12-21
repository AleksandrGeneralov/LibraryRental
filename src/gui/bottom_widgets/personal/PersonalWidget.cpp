#include "PersonalWidget.h"
#include <QGroupBox>

#include "data_base/SqlManager.h"

PersonalWidget::PersonalWidget(FullUserInfo *user, QWidget *parent)
    : QWidget(parent)
{
    this->user = user;
    initUi();
}

void PersonalWidget::initUi()
{
    QVBoxLayout *mainLay = new QVBoxLayout();
    this->setLayout(mainLay);

    QGroupBox *groupBox = new QGroupBox(QString("Данные пользователя"), this);

    QLabel *nameLabel = new QLabel(QString("Пользователь: %1").arg(user->getName()));
    QLabel *cardLabel = new QLabel(QString("Номер карты: %1").arg(user->cardNumber));

    QVBoxLayout *groupBoxLay = new QVBoxLayout();
    groupBoxLay->addWidget(nameLabel);
    groupBoxLay->addWidget(cardLabel);
    groupBox->setLayout(groupBoxLay);
    mainLay->addWidget(groupBox);

    QPushButton *returnButton = new QPushButton(QString("Вернуть книгу"), this);
    connect(returnButton, SIGNAL(clicked()), this, SLOT(slotReturnButtonClicked()));

    QHBoxLayout *buttonLay = new QHBoxLayout();
    buttonLay->addWidget(returnButton);
    buttonLay->addStretch();
    mainLay->addLayout(buttonLay);

    tableBooks = new CatalogTable(this);
    modelBooks = new CatalogModel(typePersonal, tableBooks);
    tableBooks->setModel(modelBooks);
    tableBooks->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    mainLay->addWidget(tableBooks);

    setData();
}

void PersonalWidget::setData()
{
    std::shared_ptr<QSqlDatabase> db = SqlManager::getInstance().openDB();

    QString query = QString("SELECT * FROM books_history LEFT JOIN books ON books_history.book_id=books.id"
                            " LEFT JOIN genres ON books.genres_id=genres.id"
                            " LEFT JOIN publishing ON books.publishing_id=publishing.id"
                            " WHERE books_history.client_id='%1'").arg(user->userId);
    QList<QSqlRecord> records;
    if (SqlUtils::getInstance()->sqlTable(db.get(), query, records))
    {
        foreach (QSqlRecord rec, records)
        {
            QList<QSqlRecord> authorRecords;
            if (SqlUtils::getInstance()->sqlTable(db.get(), QString("SELECT * FROM authors WHERE id IN (%1)")
                                                            .arg(rec.value("authors_id").toString()), authorRecords))
            {
                if (authorRecords.isEmpty())
                {
                    continue;
                }

                std::shared_ptr<Book> dataInfo = std::make_shared<Book>(rec, authorRecords);
                modelBooks->addItem(dataInfo);
            }
        }
    }
    SqlManager::getInstance().closeDB();
}

void PersonalWidget::slotReturnButtonClicked()
{
    QModelIndex indexTake = tableBooks->currentIndex();
    modelBooks->returnSelectedItem(indexTake, user->userId);
}
