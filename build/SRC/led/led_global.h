#ifndef LED_GLOBAL_H
#define LED_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(LED_LIBRARY)
#  define LEDSHARED_EXPORT Q_DECL_EXPORT
#else
#  define LEDSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // LED_GLOBAL_H
