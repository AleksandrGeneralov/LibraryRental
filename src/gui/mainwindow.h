#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "DialogIncludes.h"
#include "MainIncludes.h"
#include "bottom_widgets/BottomWidget.h"
#include "bottom_widgets/personal/PersonalWidget.h"
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

    std::unique_ptr<BottomWidget> bottomWidget;
    std::unique_ptr<PersonalWidget> personalWidget;
    QWidget *mainWidget;

    std::unique_ptr<FullUserInfo> user;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setUser(std::unique_ptr<FullUserInfo> user);

private:
    void initUi();

    void createFrames();
    void createButtonLayout(QWidget *parent);

    void deleteBottomWidget();
    void deleteCatalogWidget();

    QString setFrameStyleSheet();

private slots:
    void slotCatalogButtonClicked();
    void slotPersonalButtonClicked();
    void slotGenresButtonClicked();
    void slotAuthorButtonClicked();
    void slotPublishingButtonClicked();
};
#endif // MAINWINDOW_H
