#ifndef LIBUSBWRAPPER_H
#define LIBUSBWRAPPER_H

#include <QObject>
#include "usbwrapper.h"
#if LIBUSB_VERSION == 0
    #include <usb.h>
    #define libusb_device_handle usb_device_handle
    #define libusb_device_descriptor usb_device_descriptor
#else
    #include <libusb.h>
#endif
#include "usbwrapper_global.h"
class LibUsbWrapper : public UsbWrapper
{
public:
    LibUsbWrapper();
    ~LibUsbWrapper();
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
private:
    // Libusb specific variables
#if LIBUSB_VERSION != 0
    libusb_context *context; ///< The usb context used for this device
#endif
#if LIBUSB_VERSION == 0
    usb_dev_handle *handle;             ///< The USB handle for the oscilloscope
    usb_device_descriptor descriptor;   ///< The device descriptor of the oscilloscope
#else
    libusb_device_handle *handle;       ///< The USB handle for the oscilloscope
    libusb_device_descriptor descriptor;///< The device descriptor of the oscilloscope
#endif
    int interface;      ///< The number of the claimed interface
    int error;          ///< The libusb error, that happened on initialization
    // Various methods to handle USB transfers
#if LIBUSB_VERSION != 0
    int bulkTransfer    (unsigned char endpoint, unsigned char *data, unsigned int length,int *transferred, int attempts, unsigned int timeout);
#endif
    int bulkWrite       (unsigned char *data, unsigned int length,int *transferred);
    int bulkRead        (unsigned char *data, unsigned int length,int *transferred);

    /*
    int getConnectionSpeed();
    int getPacketSize();
    */
};

#endif // LIBUSBWRAPPER_H
