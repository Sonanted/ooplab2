QT += widgets

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle

SOURCES += \
        main.cpp \
        mainwindow.cpp

HEADERS += \
    mainwindow.h \
    prefixtree.h

FORMS += \
    mainwindow.ui
