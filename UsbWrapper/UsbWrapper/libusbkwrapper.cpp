#include "libusbkwrapper.h"

LibUsbKWrapper::LibUsbKWrapper()
{
    qDebug("LibUsbKWrapper::LibUsbKWrapper()");
    this->driverInfo            =   new UsbInfo();
    this->driverSetting         =   new UsbSetting();
    this->driverInfo->Name      =   "LibusbK";
    this->driverInfo->Version   =   "1.0";
    this->driverInfo->OS        =   "Windows 32bits/64bits";
    this->driverSetting->Timeout        =   500;
    this->driverSetting->TimeoutMulti   =   10;
    this->driverSetting->Attempts       =   3;
    this->driverSetting->AttemptsMulti  =   1;
}
LibUsbKWrapper::~LibUsbKWrapper()
{
    qDebug() << "LibUsbKWrapper::~LibUsbKWrapper() UsbDriver: " << this->driverInfo->Name << " OS: " << this->driverInfo->OS;
}

QString LibUsbKWrapper::searchDevice        (qint16   *IdVendor,qint16  *IdProduct)
{
    qDebug() << "UsbWrapper::LibUsbKWrapper() UsbDriver: " << this->driverInfo->Name << " OS: " << this->driverInfo->OS;
    Q_UNUSED(IdVendor);
    Q_UNUSED(IdProduct);
    return this->driverInfo->Name;
}

int     LibUsbKWrapper::openDevice          (qint16   *IdVendor,qint16  *IdProduct)
{
    qDebug() << "UsbWrapper::openDevice() UsbDriver: " << this->driverInfo->Name << " OS: " << this->driverInfo->OS;
    Q_UNUSED(IdVendor);
    Q_UNUSED(IdProduct);
    return 0;
}
int     LibUsbKWrapper::closeDevice         ()
{
    qDebug() << "UsbWrapper::closeDevice() UsbDriver: " << this->driverInfo->Name << " OS: " << this->driverInfo->OS;
    return 0;
}
int     LibUsbKWrapper::controlWriteDevice  (unsigned char request, unsigned char *data, unsigned int length, int value, int index)
{
    qDebug() << "UsbWrapper::controlWriteDevice() UsbDriver: " << this->driverInfo->Name << " OS: " << this->driverInfo->OS;
    Q_UNUSED(request);
    Q_UNUSED(data);
    Q_UNUSED(length);
    Q_UNUSED(value);
    Q_UNUSED(index);
    return 0;
}
int     LibUsbKWrapper::controlReadDevice   (unsigned char request, unsigned char *data, unsigned int length, int value, int index)
{
    qDebug() << "UsbWrapper::controlReadDevice() UsbDriver: " << this->driverInfo->Name << " OS: " << this->driverInfo->OS;
    Q_UNUSED(request);
    Q_UNUSED(data);
    Q_UNUSED(length);
    Q_UNUSED(value);
    Q_UNUSED(index);
    return 0;
}
int     LibUsbKWrapper::controlTransfer     (unsigned char type, unsigned char request, unsigned char *data, unsigned int length, int value, int index)
{
    qDebug() << "UsbWrapper::controlTransfer() UsbDriver: " << this->driverInfo->Name << " OS: " << this->driverInfo->OS;
    Q_UNUSED(type);
    Q_UNUSED(request);
    Q_UNUSED(data);
    Q_UNUSED(length);
    Q_UNUSED(value);
    Q_UNUSED(index);
    return 0;
}
int     LibUsbKWrapper::bulkWriteDevice     (unsigned char *data, unsigned int length,int *transferred)
{
    qDebug() << "UsbWrapper::bulkWriteDevice() UsbDriver: " << this->driverInfo->Name << " OS: " << this->driverInfo->OS;
    Q_UNUSED(data);
    Q_UNUSED(length);
    Q_UNUSED(transferred);
    return 0;
}
int     LibUsbKWrapper::bulkReadDevice      (unsigned char *data, unsigned int length,int *transferred)
{
    qDebug() << "UsbWrapper::bulkReadDevice() UsbDriver: " << this->driverInfo->Name << " OS: " << this->driverInfo->OS;
    Q_UNUSED(data);
    Q_UNUSED(length);
    Q_UNUSED(transferred);
    return 0;
}
int     LibUsbKWrapper::interruptWriteDevice()
{
    qDebug() << "UsbWrapper::interruptWriteDevice() UsbDriver: " << this->driverInfo->Name << " OS: " << this->driverInfo->OS;
    return 0;
}
int     LibUsbKWrapper::interruptReadDevice ()
{
    qDebug() << "UsbWrapper::interruptReadDevice() UsbDriver: " << this->driverInfo->Name << " OS: " << this->driverInfo->OS;
    return 0;
}
void    LibUsbKWrapper::disconnect          ()
{
    qDebug() << "UsbWrapper::disconnect() UsbDriver: " << this->driverInfo->Name << " OS: " << this->driverInfo->OS;
    return;
}
bool    LibUsbKWrapper::isConnected         ()
{
    qDebug() << "UsbWrapper::isConnected() UsbDriver: " << this->driverInfo->Name << " OS: " << this->driverInfo->OS;
    return 0;
}
int     LibUsbKWrapper::initDevice          ()
{
    qDebug() << "UsbWrapper::initDevice() UsbDriver: " << this->driverInfo->Name << " OS: " << this->driverInfo->OS;
    return 0;
}
int     LibUsbKWrapper::exitDevice          ()
{
    qDebug() << "UsbWrapper::exitDevice() UsbDriver: " << this->driverInfo->Name << " OS: " << this->driverInfo->OS;
    return 0;
}
int     LibUsbKWrapper::kernelDriverActive  (int interfaceNumber)
{
    qDebug() << "UsbWrapper::kernelDriverActive() UsbDriver: " << this->driverInfo->Name << " OS: " << this->driverInfo->OS;
    Q_UNUSED(interfaceNumber);
    return 0;
}
int     LibUsbKWrapper::detachKernelDriver  (int interfaceNumber)
{
    qDebug() << "UsbWrapper::detachKernelDriver() UsbDriver: " << this->driverInfo->Name << " OS: " << this->driverInfo->OS;
    Q_UNUSED(interfaceNumber);
    return 0;
}
int     LibUsbKWrapper::claimInterface      (int interfaceNumber)
{
    qDebug() << "UsbWrapper::claimInterface() UsbDriver: " << this->driverInfo->Name << " OS: " << this->driverInfo->OS;
    Q_UNUSED(interfaceNumber);
    return 0;
}
int     LibUsbKWrapper::releaseInterface    (int interfaceNumber)
{
    qDebug() << "UsbWrapper::releaseInterface() UsbDriver: " << this->driverInfo->Name << " OS: " << this->driverInfo->OS;
    Q_UNUSED(interfaceNumber);
    return 0;
}
