#ifndef __COMPONENTS_GLOBAL_H__
#define __COMPONENTS_GLOBAL_H__

#include <QObject>
#include <QtGlobal>
#include <QLoggingCategory>

#if defined(COMPONENTS_LIBRARY)
#  define COMPONENTS_EXPORT Q_DECL_EXPORT
#elif defined(COMPONENTS_STATIC_LIBRARY)
#  define COMPONENTS_EXPORT
#else
#  define COMPONENTS_EXPORT Q_DECL_IMPORT
#endif
#if (QT_VERSION < 0x050500)
#undef qCInfo
#define qCInfo qCCritical
#endif
Q_DECLARE_LOGGING_CATEGORY(logger_components)
#endif
