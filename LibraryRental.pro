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
    src/data_base/SqlCreator.cpp \
    src/data_base/SqlManager.cpp \
    src/data_base/SqlUtils.cpp \
    src/gui/AuthenticationDialog.cpp \
    main.cpp \
    src/gui/MessageDialog.cpp \
    src/gui/RegistrationDialog.cpp \
    src/gui/mainwindow.cpp

HEADERS += \
    src/data_base/SqlCreator.h \
    src/data_base/SqlDefine.h \
    src/data_base/SqlManager.h \
    src/data_base/SqlUtils.h \
    src/gui/AuthenticationDialog.h \
    src/gui/DialogIncludes.h \
    src/gui/MainIncludes.h \
    src/gui/MessageDialog.h \
    src/gui/RegistrationDialog.h \
    src/gui/mainwindow.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
