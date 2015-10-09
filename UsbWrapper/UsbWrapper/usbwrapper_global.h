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
#endif // USBWRAPPER_GLOBAL_H
