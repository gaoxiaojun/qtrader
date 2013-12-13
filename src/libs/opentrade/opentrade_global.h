#ifndef OPENTRADE_GLOBAL_H
#define OPENTRADE_GLOBAL_H

#include <qglobal.h>

#if defined(OPENTRADE_LIBRARY)
#  define OPENTRADE_EXPORT Q_DECL_EXPORT
#else
#  define OPENTRADE_EXPORT Q_DECL_IMPORT
#endif

#endif // OPENTRADE_GLOBAL_H
