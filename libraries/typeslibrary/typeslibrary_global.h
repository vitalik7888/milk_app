#ifndef TYPESLIBRARY_GLOBAL_H
#define TYPESLIBRARY_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(TYPESLIBRARY_LIBRARY)
#  define TYPESLIBRARYSHARED_EXPORT Q_DECL_EXPORT
#else
#  define TYPESLIBRARYSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // TYPESLIBRARY_GLOBAL_H
