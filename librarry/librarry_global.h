#ifndef LIBRARRY_GLOBAL_H
#define LIBRARRY_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(LIBRARRY_LIBRARY)
#  define LIBRARRY_EXPORT Q_DECL_EXPORT
#else
#  define LIBRARRY_EXPORT Q_DECL_IMPORT
#endif

#endif // LIBRARRY_GLOBAL_H
