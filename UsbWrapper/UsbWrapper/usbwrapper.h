#ifndef USBWRAPPER_H
#define USBWRAPPER_H

#include "usbwrapper_global.h"

class USBWRAPPERSHARED_EXPORT UsbWrapper : public QObject {
    Q_OBJECT

public:
    UsbWrapper();
    ~UsbWrapper();
    virtual QString searchDevice        (qint16  *IdVendor,qint16  *IdProduct)  = 0;
    virtual int     openDevice          (qint16  *IdVendor,qint16  *IdProduct)  = 0;
    virtual int     closeDevice         ()  = 0;
    virtual int     controlWriteDevice  (unsigned char request,unsigned char *data,unsigned int length,int value, int index)    = 0;
    virtual int     controlReadDevice   (unsigned char request,unsigned char *data,unsigned int length,int value, int index)    = 0;
    virtual int     controlTransfer     (unsigned char type,unsigned char request,unsigned char *data,unsigned int length,int value, int index) = 0;
    virtual int     bulkWriteDevice     (unsigned char *data,unsigned int length,int *transferred)  = 0;
    virtual int     bulkReadDevice      (unsigned char *data,unsigned int length,int *transferred)  = 0;
    virtual int     interruptWriteDevice()  = 0;
    virtual int     interruptReadDevice ()  = 0;
    virtual void    disconnect          ()  = 0;
    virtual bool    isConnected         ()  = 0;
    virtual int     initDevice          ()  = 0;
    virtual int     exitDevice          ()  = 0;
    virtual int     kernelDriverActive  (int interfaceNumber)   = 0;
    virtual int     detachKernelDriver  (int interfaceNumber)   = 0;
    virtual int     claimInterface      (int interfaceNumber)   = 0;
    virtual int     releaseInterface    (int interfaceNumber)   = 0;
    unsigned char   getEndpointIn       ();
    unsigned char   getEndpointOut      ();
    unsigned int    getTimeout          ();
    int             setEndpointIn       (unsigned char endpoint);
    int             setEndpointOut      (unsigned char endpoint);
    int             setTimeout          (unsigned int Timeout);
    QString         *getUsbDriverName   ();
protected:
    UsbInfo     *driverInfo;
    UsbSetting  *driverSetting;
};

#endif // USBWRAPPER_H

