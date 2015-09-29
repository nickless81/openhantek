#-------------------------------------------------
#
# Project created by QtCreator 2015-09-28T22:17:32
#
#-------------------------------------------------

QT       += testlib dbus

QT       -= gui

TARGET = usbhantek
TEMPLATE = lib

DEFINES += USBHANTEK_LIBRARY
# libusb version
LIBUSB_VERSION = $$(LIBUSB_VERSION)
contains(LIBUSB_VERSION, 0) {
        LIBS += -lusb
}
else {
        LIBUSB_VERSION = 1
        LIBS += -lusb-1.0
}
DEFINES += LIBUSB_VERSION=$${LIBUSB_VERSION}

SOURCES += \
    src/usbhantek.cpp \
    src/device.cpp \
    src/types.cpp

HEADERS += \
    include/usbhantek.h\
    include/usbhantek_global.h \
    include/device.h \
    include/types.h
INCLUDEPATH += include/
unix:!macx {
    # Settings for different operating systems
    target.path = /usr/lib
    INSTALLS += target
    contains(LIBUSB_VERSION, 0) {
        INCLUDEPATH += /usr/include/libusb
    }
    else {
        INCLUDEPATH += /usr/include/libusb-1.0
    }
}
