#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
#if defined(QTPEXELS_LIB)
#define QTPEXELS_EXPORT Q_DECL_EXPORT
#else
#define QTPEXELS_EXPORT Q_DECL_IMPORT
#endif
#else
#define QTPEXELS_EXPORT
#endif
