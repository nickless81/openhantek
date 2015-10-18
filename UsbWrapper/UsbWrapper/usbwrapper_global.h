#ifndef USBWRAPPER_GLOBAL_H
#define USBWRAPPER_GLOBAL_H

#include <QtCore/qglobal.h>
#include <QString>
#include <QDebug>
#if defined(USBWRAPPER_LIBRARY)
#  define USBWRAPPERSHARED_EXPORT Q_DECL_EXPORT
#else
#  define USBWRAPPERSHARED_EXPORT Q_DECL_IMPORT
#endif
//Adds enum types here!
typedef struct
{
    QString         Name;
    QString         OS;
    QString         Version;
}UsbInfo;
typedef struct
{
    unsigned int    Timeout;
    unsigned int    TimeoutMulti;
    int             Attempts;
    int             AttemptsMulti;
    unsigned char   EnpointIN;
    unsigned char   EnpointOUT;
}UsbSetting;
typedef enum
{
    USB_SUCCESS              =   0,
    USB_DEVICE_CONNECTED     =   2,
    USB_ERROR_INVALID_PARAM  =  -2,//FIXME
    USB_ERROR_ACCESS         =  -3,
    USB_ERROR_NO_DEVICE      =  -4,
    USB_ERROR_TIMEOUT        =  -7,
    USB_ERROR_NO_MEM         = -11,//FIXME
    USB_ERROR_NO_DEVICELIST  = -12,
    USB_ERROR_OTHER          = -99
}UsbErrorTypeDef;
#endif // USBWRAPPER_GLOBAL_H
