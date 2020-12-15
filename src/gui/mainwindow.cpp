#include "mainwindow.h"

#include "bottom_widgets/catalog/CatalogWidget.h"
#include "bottom_widgets/author/AuthorWidget.h"
#include "bottom_widgets/genre/GenreWidget.h"
#include "bottom_widgets/publishing/PublishingWidget.h"
#include "bottom_widgets/personal/PersonalWidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    initUi();
}

MainWindow::~MainWindow()
{
}

void MainWindow::initUi()
{
    setMinimumSize(600, 600);
    mainWidget = new QWidget();
    mainLay = new QVBoxLayout();
    mainWidget->setLayout(mainLay);

    createButtonLayout(mainWidget);

    bottomWidget = std::make_unique<CatalogWidget>(mainWidget);
    mainLay->addWidget(bottomWidget.get());

    this->setCentralWidget(mainWidget);
}

void MainWindow::createFrames()
{
    topFrame = new QFrame();
    topFrame->setFrameShape(QFrame::NoFrame);
    topFrame->setFixedHeight(100);

    bottomFrame = new QFrame();
    bottomFrame->setFrameShape(QFrame::Box);
    bottomFrame->setStyleSheet(setFrameStyleSheet());
}

void MainWindow::createButtonLayout(QWidget *parent)
{
    buttonLay = new QGridLayout();

    catalogButton = new QPushButton(QString("Каталог"), parent);
    personalButton = new QPushButton(QString("Личный кабинет"), parent);
    genresButton = new QPushButton(QString("Жанры"), parent);
    authorsButton = new QPushButton(QString("Авторы"), parent);
    publishingButton = new QPushButton(QString("Издательства"), parent);

    connect(catalogButton, SIGNAL(clicked()), this, SLOT(slotCatalogButtonClicked()));
    connect(personalButton, SIGNAL(clicked()), this, SLOT(slotPersonalButtonClicked()));
    connect(genresButton, SIGNAL(clicked()), this, SLOT(slotGenresButtonClicked()));
    connect(authorsButton, SIGNAL(clicked()), this, SLOT(slotAuthorButtonClicked()));
    connect(publishingButton, SIGNAL(clicked()), this, SLOT(slotPublishingButtonClicked()));

    buttonLay->addWidget(catalogButton, buttonLay->rowCount(), 0, 1, 1);
    buttonLay->addWidget(personalButton, buttonLay->rowCount() - 1, 1, 1, 2);

    buttonLay->addWidget(genresButton, buttonLay->rowCount(), 0, 1, 1);
    buttonLay->addWidget(authorsButton, buttonLay->rowCount() - 1, 1, 1, 1);
    buttonLay->addWidget(publishingButton, buttonLay->rowCount() - 1, 2, 1, 1);

    buttonLay->setContentsMargins(8, 0, 8, 0);
    buttonLay->setHorizontalSpacing(1);
    buttonLay->setVerticalSpacing(0);

    mainLay->addLayout(buttonLay);
}

void MainWindow::deleteBottomWidget()
{
    if (bottomWidget)
    {
        qDebug("delete bottom widget");
        bottomWidget.reset();
    }
}

QString MainWindow::setFrameStyleSheet()
{
    return QString("QFrame"
                   "{"
                        "background-color: white"
                   "}");
}

void MainWindow::slotCatalogButtonClicked()
{
    deleteBottomWidget();

    bottomWidget = std::make_unique<CatalogWidget>(mainWidget);
    mainLay->addWidget(bottomWidget.get());
}

void MainWindow::slotPersonalButtonClicked()
{
    deleteBottomWidget();

    bottomWidget = std::make_unique<PersonalWidget>(mainWidget);
    mainLay->addWidget(bottomWidget.get());
}

void MainWindow::slotGenresButtonClicked()
{
    deleteBottomWidget();

    bottomWidget = std::make_unique<GenreWidget>(mainWidget);
    mainLay->addWidget(bottomWidget.get());
}

void MainWindow::slotAuthorButtonClicked()
{
    deleteBottomWidget();

    bottomWidget = std::make_unique<AuthorWidget>(mainWidget);
    mainLay->addWidget(bottomWidget.get());
}

void MainWindow::slotPublishingButtonClicked()
{
    deleteBottomWidget();

    bottomWidget = std::make_unique<PublishingWidget>(mainWidget);
    mainLay->addWidget(bottomWidget.get());
}

