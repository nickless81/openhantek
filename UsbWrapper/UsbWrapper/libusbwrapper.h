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
#define TIMEOUT              500 ///< Timeout for USB transfers in ms
#define TIMEOUT_MULTI         10 ///< Timeout for multi packet USB transfers in ms
#define ATTEMPTS               3 ///< The number of transfer attempts
#define ATTEMPTS_MULTI         1 ///< The number of multi packet transfer attempts

class LibUsbWrapper : public UsbWrapper
{
public:
    LibUsbWrapper();
    ~LibUsbWrapper();
    QString searchDevice        (qint16   *IdVendor,qint16  *IdProduct);
    int     openDevice          (qint16   *IdVendor,qint16  *IdProduct);
    int     closeDevice         ();
    int     controlWriteDevice  ();
    int     controlReadDevice   ();
    int     bulkWriteDevice     ();
    int     bulkReadDevice      ();
    int     interruptWriteDevice();
    int     interruptReadDevice ();
    void    disconnect          ();
    bool    isConnected         ();
private:
    int initDevice();
    int exitDevice();
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
    int outPacketLength;///< Packet length for the OUT endpoint
    int inPacketLength; ///< Packet length for the IN endpoint
    // Various methods to handle USB transfers
#if LIBUSB_VERSION != 0
    int bulkTransfer(unsigned char endpoint, unsigned char *data, unsigned int length, int attempts = ATTEMPTS, unsigned int timeout = TIMEOUT);
#endif
    int bulkWrite       (unsigned char *data, unsigned int length, int attempts = ATTEMPTS);
    int bulkRead        (unsigned char *data, unsigned int length, int attempts = ATTEMPTS);
    int bulkReadMulti   (unsigned char *data, unsigned int length, int attempts = ATTEMPTS_MULTI);

    int controlTransfer (unsigned char type, unsigned char request, unsigned char *data, unsigned int length, int value, int index, int attempts = ATTEMPTS);
    int controlWrite    (unsigned char request, unsigned char *data, unsigned int length, int value = 0, int index = 0, int attempts = ATTEMPTS);
    int controlRead     (unsigned char request, unsigned char *data, unsigned int length, int value = 0, int index = 0, int attempts = ATTEMPTS);
    /*
    int getConnectionSpeed();
    int getPacketSize();
    */
signals:
    void connected();   ///< The device has been connected and initialized
    void disconnected();///< The device has been disconnected
};

#endif // LIBUSBWRAPPER_H

/*
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

            int bulkCommand(Helper::DataArray<unsigned char> *command, int attempts = HANTEK_ATTEMPTS);
            int bulkReadMulti(unsigned char *data, unsigned int length, int attempts = HANTEK_ATTEMPTS_MULTI);

            int controlTransfer(unsigned char type, unsigned char request, unsigned char *data, unsigned int length, int value, int index, int attempts = HANTEK_ATTEMPTS);
            int controlWrite(unsigned char request, unsigned char *data, unsigned int length, int value = 0, int index = 0, int attempts = HANTEK_ATTEMPTS);
            int controlRead(unsigned char request, unsigned char *data, unsigned int length, int value = 0, int index = 0, int attempts = HANTEK_ATTEMPTS);

            int getConnectionSpeed();
            int getPacketSize();
            Model getModel();

        protected:
            // Lists for enums
            QList<unsigned short int> modelIds; ///< Product ID for each ::Model
            QStringList modelStrings; ///< The name as QString for each ::Model

            // Command buffers
            ControlBeginCommand *beginCommandControl; ///< Buffer for the CONTROL_BEGINCOMMAND control command

            // Libusb specific variables
#if LIBUSB_VERSION != 0
            libusb_context *context; ///< The usb context used for this device
#endif
            Model model; ///< The model of the connected oscilloscope
#if LIBUSB_VERSION == 0
            usb_dev_handle *handle; ///< The USB handle for the oscilloscope
            usb_device_descriptor descriptor; ///< The device descriptor of the oscilloscope
#else
            libusb_device_handle *handle; ///< The USB handle for the oscilloscope
            libusb_device_descriptor descriptor; ///< The device descriptor of the oscilloscope
#endif
            int interface; ///< The number of the claimed interface
            int error; ///< The libusb error, that happened on initialization
            int outPacketLength; ///< Packet length for the OUT endpoint
            int inPacketLength; ///< Packet length for the IN endpoint

        signals:
            void connected(); ///< The device has been connected and initialized
            void disconnected(); ///< The device has been disconnected

        public slots:

 * */
