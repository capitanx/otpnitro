#-------------------------------------------------
#
# Project created by QtCreator 2014-07-29T00:11:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qotpnitro
TEMPLATE = app

os2:RC_FILE = qotpnitro_os2.rc
win32:RC_FILE = qotpnitro_w32.rc

mac:OSX_BUNDLE.files = Contents/Info.plist
mac:OSX_BUNDLE.path = Contents
mac:OSX_RESOURCES.files = Contents/Resources/qotpnitro.icns ../libotpnitro.so
mac:OSX_RESOURCES.path = Contents/Resources
mac:QMAKE_BUNDLE_DATA = OSX_BUNDLE OSX_RESOURCES
mac:QMAKE_POST_LINK = install_name_tool -change libotpnitro.so @executable_path/../Resources/libotpnitro.so qotpnitro.app/Contents/MacOS/qotpnitro; macdeployqt qotpnitro.app

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
