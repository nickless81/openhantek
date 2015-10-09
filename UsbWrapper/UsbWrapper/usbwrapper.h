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
    virtual int     controlWriteDevice()    = 0;
    virtual int     controlReadDevice()     = 0;
    virtual int     bulkWriteDevice()       = 0;
    virtual int     bulkReadDevice()        = 0;
    virtual int     interruptWriteDevice()  = 0;
    virtual int     interruptReadDevice()   = 0;
    virtual void    disconnect()            = 0;
    virtual bool    isConnected()           = 0;
    QString *getUsbDriverName();
protected:
    virtual int initDevice()                = 0;
    virtual int exitDevice()                = 0;
    QString     *driverName;    //For example libusb-1.0,libusb0.1,WinUSB,etc
signals:
    virtual void connected()                = 0; ///< The device has been connected and initialized
    virtual void disconnected()             = 0; ///< The device has been disconnected

public slots:
};

#endif // USBWRAPPER_H
