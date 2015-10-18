#include "usbwrapper.h"


UsbWrapper::UsbWrapper()
{
}
UsbWrapper::~UsbWrapper(){

}

QString *UsbWrapper::getUsbDriverName()
{

    return this->driverName;
}
unsigned char   UsbWrapper::getEndpointIn()
{
    return this->driverSetting->EnpointIN;
}

unsigned char   UsbWrapper::getEndpointOut()
{
    return this->driverSetting->EnpointOUT;
}

void            UsbWrapper::setEndpointIn(unsigned char endpoint)
{
    this->driverSetting->EnpointIN = endpoint;
}

void            UsbWrapper::setEndpointOut(unsigned char endpoint)
{
    this->driverSetting->EnpointOUT = endpoint;
}
