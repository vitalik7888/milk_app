#ifndef HTMLBUILDERLIBRARY_GLOBAL_H
#define HTMLBUILDERLIBRARY_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(HTMLBUILDERLIBRARY_LIBRARY)
#  define HTMLBUILDERLIBRARYSHARED_EXPORT Q_DECL_EXPORT
#else
#  define HTMLBUILDERLIBRARYSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // HTMLBUILDERLIBRARY_GLOBAL_H
