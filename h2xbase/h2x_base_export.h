#ifndef H2XBASE_H2X_BASE_EXPORT__H
#define H2XBASE_H2X_BASE_EXPORT__H

#if defined(H2XCOMPONENT_BUILD)

#if defined(WIN32)

#if defined(H2XBASE_IMPLEMENTATION)

#define H2XBASE_EXPORT __declspec(dllexport)
#define H2XBASE_EXPORT_PRIVATE __declspec(dllexport)

#else // defined(H2XBASE_IMPLEMENTATION)

#define H2XBASE_EXPORT __declspec(dllimport)
#define H2XBASE_EXPORT_PRIVATE __declspec(dllimport)

#endif

#else // defined(WIN32)

#if defined(H2XBASE_IMPLEMENTATION)

#define H2XBASE_EXPORT __attribute__((visibility("default")))
#define H2XBASE_EXPORT_PRIVATE __attribute__((visibility("default")))

#else

#define H2XBASE_EXPORT
#define H2XBASE_EXPORT_PRIVATE

#endif

#endif

#else // defined (H2XBASECOMPONENT_BUILD)

#define H2XBASE_EXPORT
#define H2XBASE_EXPORT_PRIVATE

#endif 

#endif // !H2XBASE_H2X_BASE_EXPORT__H
