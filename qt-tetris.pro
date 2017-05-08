#-------------------------------------------------
#
# Project created by QtCreator 2017-04-23T13:18:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qt-tetris
TEMPLATE = app

RC_ICONS += icon.ico


SOURCES += main.cpp\
        mainwindow.cpp \
        gameboard.cpp \
    cell.cpp \
    piece.cpp \
    settingswindow.cpp

HEADERS  += \
    mainwindow.h \
    gameboard.h \
    cell.h \
    piece.h \
    consts.h \
    settingswindow.h

FORMS    += mainwindow.ui \
    settingswindow.ui

RESOURCES += \
    res.qrc
