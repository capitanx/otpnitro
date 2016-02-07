#-------------------------------------------------
#
# Project created by QtCreator 2016-02-04T00:47:06
#
#-------------------------------------------------

QT       -= core gui

TARGET = otpnitro
TEMPLATE = lib

DEFINES += OTPNITRO_LIBRARY

SOURCES += \
    config.cpp \
    crypto.cpp \
    page.cpp \
    rand.cpp \
    text.cpp

HEADERS += \
    config.h \
    crypto.h \
    otpnitro.h \
    page.h \
    rand.h \
    text.h

unix {
    target.path = /usr/lib
    INSTALLS += target

	first.commands = cp libotpnitro.so ../otpnitro/
	QMAKE_EXTRA_TARGETS += first
}
