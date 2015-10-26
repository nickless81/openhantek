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

SOURCES +=  usbwrapper.cpp \
            libusbwrapper.cpp \
            libusbkwrapper.cpp

HEADERS +=  usbwrapper.h\
            usbwrapper_global.h \
            libusbwrapper.h \
            libusbkwrapper.h

unix {
    target.path = /usr/lib
    INSTALLS += target
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
}
unix:!mac {
    contains(LIBUSB_VERSION, 0) {
        INCLUDEPATH += /usr/include/libusb
    }
    else {
        INCLUDEPATH += /usr/include/libusb-1.0
    }
}
