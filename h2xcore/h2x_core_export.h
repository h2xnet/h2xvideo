#ifndef H2XCORE_H2X_CORE_EXPORT__H
#define H2XCORE_H2X_CORE_EXPORT__H

#if defined(H2XCOMPONENT_BUILD)

#if defined(WIN32)

#if defined(H2XCORE_IMPLEMENTATION)

#define H2XCORE_EXPORT __declspec(dllexport)
#define H2XCORE_EXPORT_PRIVATE __declspec(dllexport)

#else // defined(H2XCORE_IMPLEMENTATION)

#define H2XCORE_EXPORT __declspec(dllimport)
#define H2XCORE_EXPORT_PRIVATE __declspec(dllimport)

#endif

#else // defined(WIN32)

#if defined(H2XCORE_IMPLEMENTATION)

#define H2XCORE_EXPORT __attribute__((visibility("default")))
#define H2XCORE_EXPORT_PRIVATE __attribute__((visibility("default")))

#else

#define H2XCORE_EXPORT
#define H2XCORE_EXPORT_PRIVATE

#endif

#endif

#else // defined (H2XCORECOMPONENT_BUILD)

#define H2XCORE_EXPORT
#define H2XCORE_EXPORT_PRIVATE

#endif 

#endif // !H2XCORE_H2X_CORE_EXPORT__H
