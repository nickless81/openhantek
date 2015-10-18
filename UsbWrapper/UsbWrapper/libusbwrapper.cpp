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
#if LIBUSB_VERSION == 0 //FIXME
    errorCode = usb_find_busses();
    if(errorCode >= 0){
        errorCode = usb_find_devices();
    }
    if(errorCode < 0){
        this->exitDevice();
        return tr("Failed to get device list: %1").arg(Helper::libUsbErrorString(errorCode));
    }
    struct usb_device *device = NULL;
    // Iterate through all usb devices
    for(struct usb_bus *bus = usb_busses; bus; bus = bus->next)
    {
        for(device = bus->devices; device; device = device->next)
        {
            // Check VID and PID
            if(device->descriptor.idVendor == *IdVendor && device->descriptor.idProduct == *IdProduct)
            {
                emit this->connected();
                this->exitDevice();
                message = tr("USB Device found");
            }
        }
    }
    message = tr("No USB Device found");
#else
    libusb_device **deviceList;
    libusb_device *device;

    if(this->handle){
        //this->closeDevice();
        this->exitDevice();
        //libusb_close(this->handle);//move this to closeDevice method
    }
    ssize_t deviceCount = libusb_get_device_list(this->context, &deviceList);
    if(deviceCount < 0){
        message = tr("Failed to get device list");
        this->exitDevice();
        return message;
    }
    // Iterate through all usb devices
    for(ssize_t deviceIterator = 0; deviceIterator < deviceCount; ++deviceIterator) {
        device = deviceList[deviceIterator];
        // Get device descriptor
        if(libusb_get_device_descriptor(device, &(this->descriptor)) < 0){
            continue;
        }
        // Check VID and PID
        if(this->descriptor.idVendor == *IdVendor && this->descriptor.idProduct == *IdProduct) {
            emit this->connected();
            this->exitDevice();
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

#if LIBUSB_VERSION == 0 //FIXME
    struct usb_device *device = NULL;
    errorCode = usb_find_busses();
    if(errorCode >= 0){
        errorCode = usb_find_devices();
    }
    if(errorCode < 0){
        //return tr("Failed to get device list: %1").arg(Helper::libUsbErrorString(errorCode));
        return errorCode;
    }
    struct usb_device *device = NULL;
    // Iterate through all usb devices
    for(struct usb_bus *bus = usb_busses; bus; bus = bus->next)
    {
        for(device = bus->devices; device; device = device->next)
        {
            // Check VID and PID
            if(device->descriptor.idVendor == *IdVendor && device->descriptor.idProduct == *IdProduct)
            {

                qDebug("USB Device open");
                this->handle = usb_open(device);
            }
        }
    }
    message = tr("No USB Device found");
#else
    libusb_device **deviceList;
    libusb_device *device;
    ssize_t deviceCount = libusb_get_device_list(this->context, &deviceList);
    if(deviceCount < 0){
        qDebug("Failed to get device list");
        return deviceCount ;
    }
    // Iterate through all usb devices
    for(ssize_t deviceIterator = 0; deviceIterator < deviceCount; ++deviceIterator)
    {
        device = deviceList[deviceIterator];
        // Get device descriptor
        if(libusb_get_device_descriptor(device, &(this->descriptor)) < 0){
            continue;
        }
        // Check VID and PID
        if(this->descriptor.idVendor == *IdVendor && this->descriptor.idProduct == *IdProduct)
        {
            this->handle = libusb_open_device_with_vid_pid(this->context,this->descriptor.idVendor,this->descriptor.idProduct);
            emit this->open();
            qDebug("USB Device open");
        }
    }
#endif
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
    emit close();
    this->handle = 0;
    return 0;
}
int LibUsbWrapper::controlWriteDevice(unsigned char request, unsigned char *data, unsigned int length, int value, int index){
    qDebug() << "UsbWrapper::controlWriteDevice() UsbDriver: " << *this->driverName;
    if(!this->handle)
    {
        return LIBUSB_ERROR_NO_DEVICE;
    }
    return this->controlTransfer(LIBUSB_REQUEST_TYPE_VENDOR | LIBUSB_ENDPOINT_OUT,request,data, length,value,index);
}
int LibUsbWrapper::controlReadDevice(unsigned char request, unsigned char *data, unsigned int length, int value, int index){
    qDebug() << "UsbWrapper::controlReadDevice() UsbDriver: " << *this->driverName;
    if(!this->handle)
    {
        return LIBUSB_ERROR_NO_DEVICE;
    }
    return this->controlTransfer(LIBUSB_REQUEST_TYPE_VENDOR | LIBUSB_ENDPOINT_IN,request,data, length,value,index);
}
int LibUsbWrapper::bulkWriteDevice(unsigned char *data, unsigned int length){
    qDebug() << "UsbWrapper::bulkWriteDevice() UsbDriver: " << *this->driverName;
    return this->bulkWrite(data, length);
}
int LibUsbWrapper::bulkReadDevice(unsigned char *data, unsigned int length){
    qDebug() << "UsbWrapper::bulkReadDevice() UsbDriver: " << *this->driverName;
    return this->bulkRead(data,length);
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
#if LIBUSB_VERSION == 0
    usb_exit();
    return LIBUSB_SUCCESS;
#else
    if(this->context)
    {
        //FIXME
        //return libusb_exit(this->context);
        return 0;
    }
#endif
    return -1;
}
// Various methods to handle USB transfers
#if LIBUSB_VERSION != 0
int LibUsbWrapper::bulkTransfer(unsigned char endpoint, unsigned char *data, unsigned int length, int attempts,unsigned int timeout)
{
    if(!this->handle)
    {
        return LIBUSB_ERROR_NO_DEVICE;
    }
    int errorCode = LIBUSB_ERROR_TIMEOUT;
    int transferred;
    for(int attempt = 0; (attempt < attempts || attempts == -1) && errorCode == LIBUSB_ERROR_TIMEOUT; ++attempt)
        errorCode = libusb_bulk_transfer(this->handle, endpoint, data, length, &transferred, timeout);

    if(errorCode == LIBUSB_ERROR_NO_DEVICE)
    {
        this->disconnect();
    }
    if(errorCode < 0)
    {
        return errorCode;
    }else
    {
        return transferred;
    }
    return 0;
}
#endif
int LibUsbWrapper::bulkWrite       (unsigned char *data, unsigned int length)
{
    if(!this->handle)
    {
        return LIBUSB_ERROR_NO_DEVICE;
    }
    /*
    //FIXME
    int errorCode = this->getConnectionSpeed();
    if(errorCode < 0)
    {
        return errorCode;
    }
    */
#if LIBUSB_VERSION == 0
    errorCode = LIBUSB_ERROR_TIMEOUT;
    for(int attempt = 0; (attempt < this->driverSetting->Attempts || this->driverSetting->Attempts == -1) && errorCode == LIBUSB_ERROR_TIMEOUT; ++attempt)
    {
        errorCode = usb_bulk_write(this->handle, this->driverSetting->EnpointOUT, (char *) data, length, this->driverSetting->Timeout);
    }
    if(errorCode == LIBUSB_ERROR_NO_DEVICE)
    {
        this->disconnect();
    }
    return errorCode;
#else
    return this->bulkTransfer(this->driverSetting->EnpointOUT, data, length,this->driverSetting->Attempts,this->driverSetting->Timeout);
#endif
}
int LibUsbWrapper::bulkRead        (unsigned char *data, unsigned int length)
{
    if(!this->handle)
    {
        return LIBUSB_ERROR_NO_DEVICE;
    }
    /*
    //FIXME
    int errorCode = this->getConnectionSpeed();
    if(errorCode < 0)
    {
        return errorCode;
    }
    */
#if LIBUSB_VERSION == 0
    errorCode = LIBUSB_ERROR_TIMEOUT;
    for(int attempt = 0; (attempt < this->driverSetting->Attempts || this->driverSetting->Attempts == -1) && errorCode == LIBUSB_ERROR_TIMEOUT; ++attempt)
    {
        errorCode = usb_bulk_read(this->handle, this->driverSetting->EnpointIN, (char *) data, length, this->driverSetting->Timeout);
    }
    if(errorCode == LIBUSB_ERROR_NO_DEVICE)
    {
        this->disconnect();
    }
    return errorCode;
#else
    return this->bulkTransfer(this->driverSetting->EnpointIN, data, length,this->driverSetting->Attempts,this->driverSetting->Timeout);
#endif
    return 0;
}
int LibUsbWrapper::bulkReadMulti   (unsigned char *data, unsigned int length)
{
    if(!this->handle)
    {
        return LIBUSB_ERROR_NO_DEVICE;
    }
    int errorCode = 0;
    /*
    errorCode = this->getConnectionSpeed();
    if(errorCode < 0)
    {
        return errorCode;
    }
    */
    errorCode = this->inPacketLength;
    unsigned int packet, received = 0;
    for(packet = 0; received < length && errorCode == this->inPacketLength; ++packet)
    {
#if LIBUSB_VERSION == 0
        errorCode = LIBUSB_ERROR_TIMEOUT;
        for(int attempt = 0; (attempt < this->driverSetting->AttemptsMulti || this->driverSetting->AttemptsMulti == -1) && errorCode == LIBUSB_ERROR_TIMEOUT; ++attempt)
        {
            errorCode = usb_bulk_read(this->handle, this->driverSetting->EnpointIN, (char *) data + packet * this->inPacketLength, qMin(length - received, (unsigned int) this->inPacketLength), this->driverSetting->Timeout);
        }
#else
        errorCode = this->bulkTransfer(this->driverSetting->EnpointIN, data + packet * this->inPacketLength, qMin(length - received, (unsigned int) this->inPacketLength), this->driverSetting->AttemptsMulti, this->driverSetting->TimeoutMulti);
#endif
        if(errorCode > 0)
        {
            received += errorCode;
        }
    }
    if(received > 0)
    {
        return received;
    }else
    {
        return errorCode;
    }
}

int LibUsbWrapper::controlTransfer (unsigned char type, unsigned char request, unsigned char *data, unsigned int length, int value, int index)
{
    if(!this->handle)
    {
        return LIBUSB_ERROR_NO_DEVICE;
    }
    int errorCode = LIBUSB_ERROR_TIMEOUT;
    for(int attempt = 0; (attempt < this->driverSetting->Attempts || this->driverSetting->Attempts == -1) && errorCode == LIBUSB_ERROR_TIMEOUT; ++attempt)
    {
#if LIBUSB_VERSION == 0
        errorCode = usb_control_msg(this->handle, type, request, value, index, (char *) data, length, this->driverSetting->Timeout);
#else
        errorCode = libusb_control_transfer(this->handle, type, request, value, index, data, length, this->driverSetting->Timeout);
#endif
    }
    if(errorCode == LIBUSB_ERROR_NO_DEVICE)
        this->disconnect();
    return errorCode;
    return 0;
}
