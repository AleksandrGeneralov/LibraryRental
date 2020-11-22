QT = core \
    gui \
    sql \
    svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += src \
               icons \

SOURCES += \
    src/DataStructures.cpp \
    src/data_base/SqlCreator.cpp \
    src/data_base/SqlManager.cpp \
    src/data_base/SqlUtils.cpp \
    src/gui/AuthenticationDialog.cpp \
    main.cpp \
    src/gui/MessageDialog.cpp \
    src/gui/RegistrationDialog.cpp \
    src/gui/bottom_widgets/author/AuthorModel.cpp \
    src/gui/bottom_widgets/author/AuthorTable.cpp \
    src/gui/bottom_widgets/author/AuthorWidget.cpp \
    src/gui/bottom_widgets/catalog/CatalogModel.cpp \
    src/gui/bottom_widgets/catalog/CatalogTable.cpp \
    src/gui/bottom_widgets/catalog/CatalogWidget.cpp \
    src/gui/bottom_widgets/genre/GenreModel.cpp \
    src/gui/bottom_widgets/genre/GenreTable.cpp \
    src/gui/bottom_widgets/genre/GenreWidget.cpp \
    src/gui/bottom_widgets/publishing/PublishingModel.cpp \
    src/gui/bottom_widgets/publishing/PublishingTable.cpp \
    src/gui/bottom_widgets/publishing/PublishingWidget.cpp \
    src/gui/mainwindow.cpp

HEADERS += \
    src/DataStructures.h \
    src/data_base/SqlCreator.h \
    src/data_base/SqlDefine.h \
    src/data_base/SqlManager.h \
    src/data_base/SqlUtils.h \
    src/gui/AuthenticationDialog.h \
    src/gui/DialogIncludes.h \
    src/MainIncludes.h \
    src/gui/MessageDialog.h \
    src/gui/RegistrationDialog.h \
    src/gui/bottom_widgets/BottomModel.h \
    src/gui/bottom_widgets/BottomTable.h \
    src/gui/bottom_widgets/BottomWidget.h \
    src/gui/bottom_widgets/author/AuthorModel.h \
    src/gui/bottom_widgets/author/AuthorTable.h \
    src/gui/bottom_widgets/author/AuthorWidget.h \
    src/gui/bottom_widgets/catalog/CatalogModel.h \
    src/gui/bottom_widgets/catalog/CatalogTable.h \
    src/gui/bottom_widgets/catalog/CatalogWidget.h \
    src/gui/bottom_widgets/genre/GenreModel.h \
    src/gui/bottom_widgets/genre/GenreTable.h \
    src/gui/bottom_widgets/genre/GenreWidget.h \
    src/gui/bottom_widgets/publishing/PublishingModel.h \
    src/gui/bottom_widgets/publishing/PublishingTable.h \
    src/gui/bottom_widgets/publishing/PublishingWidget.h \
    src/gui/mainwindow.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
