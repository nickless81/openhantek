#ifndef LIBUSBKWRAPPER_H
#define LIBUSBKWRAPPER_H
#include "usbwrapper.h"
/*
FIXME: Add include for libusbK.h
*/
#include "usbwrapper_global.h"

class LibUsbKWrapper : public UsbWrapper
{
public:
    LibUsbKWrapper();
    ~LibUsbKWrapper();
    QString searchDevice        (qint16   *IdVendor,qint16  *IdProduct);
    int     openDevice          (qint16   *IdVendor,qint16  *IdProduct);
    int     closeDevice         ();
    int     controlWriteDevice  (unsigned char request, unsigned char *data, unsigned int length, int value, int index);
    int     controlReadDevice   (unsigned char request, unsigned char *data, unsigned int length, int value, int index);
    int     controlTransfer     (unsigned char type, unsigned char request, unsigned char *data, unsigned int length, int value, int index);
    int     bulkWriteDevice     (unsigned char *data, unsigned int length,int *transferred);
    int     bulkReadDevice      (unsigned char *data, unsigned int length,int *transferred);
    int     interruptWriteDevice();
    int     interruptReadDevice ();
    void    disconnect          ();
    bool    isConnected         ();
    int     initDevice          ();
    int     exitDevice          ();
    int     kernelDriverActive  (int interfaceNumber);
    int     detachKernelDriver  (int interfaceNumber);
    int     claimInterface      (int interfaceNumber);
    int     releaseInterface    (int interfaceNumber);
};

#endif // LIBUSBKWRAPPER_H
