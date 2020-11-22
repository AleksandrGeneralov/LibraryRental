#include "mainwindow.h"

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
    QWidget *mainWidget = new QWidget(this);
    mainLay = new QVBoxLayout();
    mainWidget->setLayout(mainLay);

//    createFrames();
    createButtonLayout(mainWidget);

    catalogWidget = new CatalogWidget(mainWidget);
//    QVBoxLayout *bottomLay = new QVBoxLayout();
//    bottomLay->addWidget(catalogWidget);
//    bottomFrame->setLayout(bottomLay);

//    mainLay->addWidget(topFrame);
    mainLay->addWidget(catalogWidget);

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
    buttonLay = new QGridLayout(parent);

    catalogButton = new QPushButton(QString("Каталог"), parent);
    personalButton = new QPushButton(QString("Личный кабинет"), parent);
    genresButton = new QPushButton(QString("Жанры"), parent);
    authorsButton = new QPushButton(QString("Авторы"), parent);
    publishingButton = new QPushButton(QString("Издательства"), parent);

    buttonLay->addWidget(catalogButton, buttonLay->rowCount(), 0, 1, 1);
    buttonLay->addWidget(personalButton, buttonLay->rowCount() - 1, 1, 1, 2);

    buttonLay->addWidget(genresButton, buttonLay->rowCount(), 0, 1, 1);
    buttonLay->addWidget(authorsButton, buttonLay->rowCount() - 1, 1, 1, 1);
    buttonLay->addWidget(publishingButton, buttonLay->rowCount() - 1, 2, 1, 1);

    buttonLay->setContentsMargins(8, 0, 8, 0);
    buttonLay->setHorizontalSpacing(1);
    buttonLay->setVerticalSpacing(0);

//    for (int i = 0; i < buttonLay->rowCount(); i++)
//    {
//        buttonLay->setRowMinimumHeight(i, 50);
//    }

    mainLay->addLayout(buttonLay);
}

void MainWindow::setActiveBottomWidget(int typeWidget)
{

}

QString MainWindow::setFrameStyleSheet()
{
    return QString("QFrame"
                   "{"
                        "background-color: white"
                   "}");
}

