#-------------------------------------------------
#
# Project created by QtCreator 2015-10-08T20:48:55
#
#-------------------------------------------------

QT       += dbus

QT       -= gui

TARGET = UsbWrapper
TEMPLATE = lib

DEFINES += USBWRAPPER_LIBRARY

SOURCES += usbwrapper.cpp

HEADERS += usbwrapper.h\
        usbwrapper_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
