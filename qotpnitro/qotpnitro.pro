#-------------------------------------------------
#
# Project created by QtCreator 2014-07-29T00:11:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qotpnitro
TEMPLATE = app

RC_FILE = qotpnitro.rc

LIBS += -L.. -lotpnitro

INCLUDEPATH += ..

SOURCES += main.cpp\
        mainwindow.cpp \
    helpdialog.cpp \
    settingsdialog.cpp \
    encodedialog.cpp \
    genbookdialog.cpp \
    burndialog.cpp

HEADERS  += mainwindow.h \
    helpdialog.h \
    settingsdialog.h \
    encodedialog.h \
    genbookdialog.h \
    burndialog.h

FORMS    += mainwindow.ui \
    helpdialog.ui \
    settingsdialog.ui \
    encodedialog.ui \
    genbookdialog.ui \
    burndialog.ui

RESOURCES += \
    icons.qrc
