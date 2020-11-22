#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "DialogIncludes.h"
#include "MainIncludes.h"
#include "bottom_widgets/catalog/CatalogWidget.h"
#include "bottom_widgets/BottomWidget.h"
#include <QFrame>

class MainWindow : public QMainWindow
{
    Q_OBJECT

    enum TypeWidget
    {
        widgetCatalog = 0,
        widgetPersonal = 1,
        widgetGenres = 2,
        widgetAuthors = 3,
        widgetPublishing = 4
    };

    QVBoxLayout *mainLay;

    QFrame *topFrame;
    QFrame *bottomFrame;

    QGridLayout *buttonLay;

    QPushButton *catalogButton;
    QPushButton *personalButton;
    QPushButton *genresButton;
    QPushButton *authorsButton;
    QPushButton *publishingButton;

    BottomWidget *catalogWidget;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void initUi();

    void createFrames();
    void createButtonLayout(QWidget *parent);
    void setActiveBottomWidget(int typeWidget);

    QString setFrameStyleSheet();
};
#endif // MAINWINDOW_H
