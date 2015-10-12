#include "libusbwrapper.h"
LibUsbWrapper::LibUsbWrapper()
{
    this->driverInfo            =   new UsbInfo();
#if LIBUSB_VERSION == 0
    this->driverName            =   new QString("Libusb-0.1");
    this->driverInfo->Name      = "Libusb-0.1";
    this->driverInfo->Version   =   "0.1";
#else
    this->driverName            =   new QString("Libusb-1.0");
    this->driverInfo->Name      = "Libusb-1.0";
    this->driverInfo->Version   =   "1.0";
#endif
    this->driverInfo->OS        =   "Linux 32bits/64bits";
    this->driverSetting         = new UsbSetting();
    this->driverSetting->Timeout        =   500;
    this->driverSetting->TimeoutMulti   =   10;
    this->driverSetting->Attempts       =   3;
    this->driverSetting->AttemptsMulti  =   1;

}
LibUsbWrapper::~LibUsbWrapper()
{
    qDebug() << "LibUsbWrapper::~LibUsbWrapper()() UsbDriver: " << *this->driverName;
    this->disconnect();
}

//publics inherited
QString LibUsbWrapper::searchDevice(qint16   *IdVendor,qint16  *IdProduct){
    qDebug() << "UsbWrapper::openDevice() UsbDriver: " << *this->driverName;
    //IdVendor: For example 0x04B4,0x04B5
    //IdProduct:For example 0x6022,0x602a
    QString message;
    int error =this->initDevice();
    if(error<0){
        qDebug() << "Error Initialized USB driver";
        message = tr("Failed to initialized USB driver");
        return message;
    }
    QString deviceAddress;
    Q_UNUSED(deviceAddress);
    int errorCode = LIBUSB_SUCCESS;
    Q_UNUSED(errorCode);//FIXME
#if LIBUSB_VERSION == 0
    errorCode = usb_find_busses();
    if(errorCode >= 0){
        errorCode = usb_find_devices();
    }
    if(errorCode < 0){
        return tr("Failed to get device list: %1").arg(Helper::libUsbErrorString(errorCode));
    }
    struct usb_device *device = NULL;
    // Iterate through all usb devices
    for(struct usb_bus *bus = usb_busses; bus; bus = bus->next) {
        for(device = bus->devices; device; device = device->next) {
            // Check VID and PID
            if(device->descriptor.idVendor == *IdVendor && device->descriptor.idProduct == *IdProduct) {
                emit this->connected();
                message = tr("USB Device found");
            }
        }
    }
    message = tr("No USB Device found");
#else
    libusb_device **deviceList;
    libusb_device *device;

    if(this->handle){
        this->closeDevice();
        //libusb_close(this->handle);//move this to closeDevice method
    }
    ssize_t deviceCount = libusb_get_device_list(this->context, &deviceList);
    if(deviceCount < 0){
        message = tr("Failed to get device list");
        return message;
    }
    // Iterate through all usb devices
    //this->model = MODEL_UNKNOWN;
    for(ssize_t deviceIterator = 0; deviceIterator < deviceCount; ++deviceIterator) {
        device = deviceList[deviceIterator];
        // Get device descriptor
        if(libusb_get_device_descriptor(device, &(this->descriptor)) < 0){
            continue;
        }
        // Check VID and PID
        if(this->descriptor.idVendor == *IdVendor && this->descriptor.idProduct == *IdProduct) {
            emit this->connected();
            message = tr("USB Device found");
        }
    }
    message = tr("No USB Device found");
#endif
    return message;
}
int LibUsbWrapper::openDevice(qint16   *IdVendor,qint16  *IdProduct){
    qDebug() << "UsbWrapper::openDevice() UsbDriver: " << *this->driverName;
    Q_UNUSED(IdVendor); //For example 0x04B4,0x04B5
    Q_UNUSED(IdProduct);//For example 0x6022,0x602a

    return 0;
}

int LibUsbWrapper::closeDevice(){
    qDebug() << "UsbWrapper::closeDevice() UsbDriver: " << *this->driverName;
    if(!this->handle){
        return -1;
    }
    // Close device handle
#if LIBUSB_VERSION == 0
    usb_close(this->handle);
#else
    libusb_close(this->handle);
#endif
    this->handle = 0;
    return 0;
}
int LibUsbWrapper::controlWriteDevice(){
    qDebug() << "UsbWrapper::controlWriteDevice() UsbDriver: " << *this->driverName;
    return 0;
}
int LibUsbWrapper::controlReadDevice(){
    qDebug() << "UsbWrapper::controlReadDevice() UsbDriver: " << *this->driverName;
    return 0;
}
int LibUsbWrapper::bulkWriteDevice(){
    qDebug() << "UsbWrapper::bulkWriteDevice() UsbDriver: " << *this->driverName;
    return 0;
}
int LibUsbWrapper::bulkReadDevice(){
    qDebug() << "UsbWrapper::bulkReadDevice() UsbDriver: " << *this->driverName;
    return 0;
}
int LibUsbWrapper::interruptWriteDevice(){
    qDebug() << "UsbWrapper::interruptWriteDevice() UsbDriver: " << *this->driverName;
    return 0;
}
int LibUsbWrapper::interruptReadDevice(){
    qDebug() << "UsbWrapper::interruptReadDevice() UsbDriver: " << *this->driverName;
    return 0;
}
void LibUsbWrapper::disconnect(){
    qDebug() << "UsbWrapper::disconnect() UsbDriver: " << *this->driverName;
    if(!this->handle){
        return;
    }
    // Release claimed interface
#if LIBUSB_VERSION == 0
    usb_release_interface(this->handle, this->interface);
#else
    libusb_release_interface(this->handle, this->interface);
#endif
    this->interface = -1;
    this->closeDevice();
    emit disconnected();
    return;
}
/// \brief Check if the oscilloscope is connected.
/// \return true, if a connection is up.
bool LibUsbWrapper::isConnected(){
    qDebug() << "UsbWrapper::isConnected() UsbDriver: " << *this->driverName;
    return this->handle != 0;
}

//private inherited
int LibUsbWrapper::initDevice(){
    qDebug() << "UsbWrapper::initDevice() UsbDriver: " << *this->driverName;
    this->handle            =  0;
    this->interface         = -1;
    this->outPacketLength   =  0;
    this->inPacketLength    =  0;
#if LIBUSB_VERSION == 0
    usb_init();
    return LIBUSB_SUCCESS;
#else
    return libusb_init(&(this->context));
#endif
}
int LibUsbWrapper::exitDevice(){
    qDebug() << "UsbWrapper::exitDevice() UsbDriver: " << *this->driverName;
    return 0;
}
// Various methods to handle USB transfers
#if LIBUSB_VERSION != 0
int LibUsbWrapper::bulkTransfer(unsigned char endpoint, unsigned char *data, unsigned int length)
{
    int attempts            = this->driverSetting->Attempts;
    unsigned int timeout    = this->driverSetting->Timeout;
    Q_UNUSED(endpoint);
    Q_UNUSED(data);
    Q_UNUSED(length);
    Q_UNUSED(attempts);
    Q_UNUSED(timeout);
    return 0;
}
#endif
int LibUsbWrapper::bulkWrite       (unsigned char *data, unsigned int length)
{
    int attempts    = this->driverSetting->Attempts;
    Q_UNUSED(data);
    Q_UNUSED(length);
    Q_UNUSED(attempts);
    return 0;
}
int LibUsbWrapper::bulkRead        (unsigned char *data, unsigned int length)
{
    int attempts = this->driverSetting->Attempts;
    Q_UNUSED(data);
    Q_UNUSED(length);
    Q_UNUSED(attempts);
    return 0;
}
int LibUsbWrapper::bulkReadMulti   (unsigned char *data, unsigned int length)
{
    int attempts    = this->driverSetting->AttemptsMulti;
    Q_UNUSED(data);
    Q_UNUSED(length);
    Q_UNUSED(attempts);
    return 0;
}

int LibUsbWrapper::controlTransfer (unsigned char type, unsigned char request, unsigned char *data, unsigned int length, int value, int index)
{
    int attempts    = this->driverSetting->Attempts;
    Q_UNUSED(type);
    Q_UNUSED(request);
    Q_UNUSED(data);
    Q_UNUSED(length);
    Q_UNUSED(value);
    Q_UNUSED(index);
    Q_UNUSED(attempts);
    return 0;
}
int LibUsbWrapper::controlWrite    (unsigned char request, unsigned char *data, unsigned int length)
{
    int value       = 0;
    int index       = 0;
    int attempts    = this->driverSetting->Attempts;
    Q_UNUSED(request);
    Q_UNUSED(data);
    Q_UNUSED(length);
    Q_UNUSED(value);
    Q_UNUSED(index);
    Q_UNUSED(attempts);
    return 0;
}
int LibUsbWrapper::controlRead     (unsigned char request, unsigned char *data, unsigned int length)
{
    int value = 0;
    int index = 0;
    int attempts = this->driverSetting->Attempts;
    Q_UNUSED(request);
    Q_UNUSED(data);
    Q_UNUSED(length);
    Q_UNUSED(value);
    Q_UNUSED(index);
    Q_UNUSED(attempts);
    return 0;
}
