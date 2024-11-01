QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    adddialog.cpp \
    deletedialog.cpp \
    displaydialog.cpp \
    main.cpp \
    mainwindow.cpp \
    malfunctiontype.cpp \
    servicecenterdatabase.cpp \
    updatedialog.cpp

HEADERS += \
    adddialog.h \
    deletedialog.h \
    displaydialog.h \
    mainwindow.h \
    malfunctiontype.h \
    servicecenterdatabase.h \
    updatedialog.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    Lab3Again_en_UA.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
