#ifndef USBWRAPPER_H
#define USBWRAPPER_H

#include "usbwrapper_global.h"

class USBWRAPPERSHARED_EXPORT UsbWrapper : public QObject {
    Q_OBJECT

public:
    UsbWrapper();
    ~UsbWrapper();
    virtual QString searchDevice(
            qint16  *IdVendor,
            qint16  *IdProduct)             = 0;
    virtual int     openDevice(
            qint16   *IdVendor,
            qint16  *IdProduct)             = 0;
    virtual int     closeDevice()           = 0;
    virtual int     controlWriteDevice(
            unsigned char request,
            unsigned char *data,
            unsigned int length,
            int value, int index)           = 0;
    virtual int     controlReadDevice(
            unsigned char request,
            unsigned char *data,
            unsigned int length,
            int value, int index)           = 0;
    virtual int     bulkWriteDevice(
            unsigned char *data,
            unsigned int length)            = 0;
    virtual int     bulkReadDevice(
            unsigned char *data,
            unsigned int length)            = 0;
    virtual int     bulkReadDeviceMulti(
            unsigned char *data,
            unsigned int length)            = 0;
    virtual int     interruptWriteDevice()  = 0;
    virtual int     interruptReadDevice()   = 0;
    virtual void    disconnect()            = 0;
    virtual bool    isConnected()           = 0;
    virtual int     initDevice()            = 0;
    virtual int     exitDevice()            = 0;
    unsigned char   getEndpointIn();
    unsigned char   getEndpointOut();
    void            setEndpointIn(unsigned char endpoint);
    void            setEndpointOut(unsigned char endpoint);
    QString *getUsbDriverName();
protected:
    QString     *driverName;    //For example libusb-1.0,libusb0.1,WinUSB,etc
    UsbInfo     *driverInfo;
    UsbSetting  *driverSetting;
signals:
    void connected      (); ///< The device has been connected and initialized
    void disconnected   (); ///< The device has been disconnected
    void open           ();
    void close          ();
    void usbError       (int errorCode);

public slots:
};

#endif // USBWRAPPER_H

