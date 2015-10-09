#include "usbwrapper.h"


UsbWrapper::UsbWrapper()
{
}
UsbWrapper::~UsbWrapper(){

}

QString *UsbWrapper::getUsbDriverName(){

    return this->driverName;
}
