#include "usbwrapper.h"


UsbWrapper::UsbWrapper()
{
}
UsbWrapper::~UsbWrapper(){

}

QString *UsbWrapper::getUsbDriverName()
{

    return &this->driverInfo->Name;
}
unsigned char   UsbWrapper::getEndpointIn()
{
    return this->driverSetting->EnpointIN;
}

unsigned char   UsbWrapper::getEndpointOut()
{
    return this->driverSetting->EnpointOUT;
}
unsigned int    UsbWrapper::getTimeout()
{
    return this->driverSetting->Timeout;
}

int             UsbWrapper::setEndpointIn(unsigned char endpoint)
{
    if(this->driverSetting != NULL)
    {
        this->driverSetting->EnpointIN = endpoint;
        return 0;
    }
    return -1;
}

int             UsbWrapper::setEndpointOut(unsigned char endpoint)
{
    if(this->driverSetting != NULL)
    {
        this->driverSetting->EnpointOUT = endpoint;
        return 0;
    }
    return -1;
}
int             UsbWrapper::setTimeout(unsigned int Timeout)
{
    if(this->driverSetting != NULL)
    {
        this->driverSetting->Timeout = Timeout;
        return 0;
    }
    return -1;
}
