#ifndef DEVICE_H
#define DEVICE_H

#include <QObject>
#include <QStringList>
#include <types.h>
#if LIBUSB_VERSION == 0
#include <usb.h>
#define libusb_device_handle usb_device_handle
#define libusb_device_descriptor usb_device_descriptor
#else
#include <libusb.h>
#endif

class Device : public QObject
{
    Q_OBJECT
public:
    Device(QObject *parent = 0);
    ~Device();

    QString search();
    void disconnect();
    bool isConnected();

    // Various methods to handle USB transfers
#if LIBUSB_VERSION != 0
    int bulkTransfer(unsigned char endpoint, unsigned char *data, unsigned int length, int attempts = HANTEK_ATTEMPTS, unsigned int timeout = HANTEK_TIMEOUT);
#endif
    int bulkWrite(unsigned char *data, unsigned int length, int attempts = HANTEK_ATTEMPTS);
    int bulkRead(unsigned char *data, unsigned int length, int attempts = HANTEK_ATTEMPTS);

    //int bulkCommand(Helper::DataArray<unsigned char> *command, int attempts = HANTEK_ATTEMPTS);
    int bulkReadMulti(unsigned char *data, unsigned int length, int attempts = HANTEK_ATTEMPTS_MULTI);

    int controlTransfer(unsigned char type, unsigned char request, unsigned char *data, unsigned int length, int value, int index, int attempts = HANTEK_ATTEMPTS);
    int controlWrite(unsigned char request, unsigned char *data, unsigned int length, int value = 0, int index = 0, int attempts = HANTEK_ATTEMPTS);
    int controlRead(unsigned char request, unsigned char *data, unsigned int length, int value = 0, int index = 0, int attempts = HANTEK_ATTEMPTS);

    int getConnectionSpeed();
    int getPacketSize();

};

#endif // DEVICE_H
