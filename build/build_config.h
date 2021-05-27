#ifndef BUILD_BUILD_CONFIG_H_
#define BUILD_BUILD_CONFIG_H_

// Define platform macro
#if defined(_WIN32)
#define OS_WIN	1
#elif defined(__APPLE__) && (defined(__i386__) || defined(__ARMEL__))
#define OS_IOS	1
#elif defined(__APPLE__)
#define OS_MACOSX	1
#elif defined(__linux__)
#define OS_LINUX	1
#elif defined(__FreeBSD__)
#define OS_FREEBSD	1
#else
	#error Please add support for your platform in build/build_config.harderr
#endif

// Compiler detection.
#if defined(__GNUC__)
#define COMPILER_GCC 1
#elif defined(_MSC_VER)
#define COMPILER_MSVC 1
#else
#error Please add support for your compiler in build/build_config.h
#endif

// Processor architecture detection.  For more info on what's defined, see:
//   http://msdn.microsoft.com/en-us/library/b0084kay.aspx
//   http://www.agner.org/optimize/calling_conventions.pdf
//   or with gcc, run: "echo | gcc -E -dM -"
#if defined(_M_X64) || defined(__x86_64__)
#define ARCH_CPU_X86_FAMILY 1
#define ARCH_CPU_X86_64     1
#define ARCH_CPU_64_BITS    1
#elif defined(_M_IX86) || defined(__i386__)
#define ARCH_CPU_X86_FAMILY 1
#define ARCH_CPU_X86        1
#define ARCH_CPU_32_BITS    1
#elif defined(__ARMEL__)
#define ARCH_CPU_ARM_FAMILY 1
#define ARCH_CPU_ARMEL      1
#define ARCH_CPU_32_BITS    1
#define WCHAR_T_IS_UNSIGNED 1
#else
#error Please add support for your architecture in build/build_config.h
#endif

// Type detection for wchar_t.
#if defined(OS_WIN)
#define WCHAR_T_IS_UTF16
#elif defined(OS_POSIX) && defined(COMPILER_GCC) && \
      defined(__WCHAR_MAX__) && \
      (__WCHAR_MAX__ == 0x7fffffff || __WCHAR_MAX__ == 0xffffffff)
#define WCHAR_T_IS_UTF32
#elif defined(OS_POSIX) && defined(COMPILER_GCC) && \
      defined(__WCHAR_MAX__) && \
      (__WCHAR_MAX__ == 0x7fff || __WCHAR_MAX__ == 0xffff)
// On Posix, we'll detect short wchar_t, but projects aren't guaranteed to
// compile in this mode (in particular, Chrome doesn't). This is intended for
// other projects using base who manage their own dependencies and make sure
// short wchar works for them.
#define WCHAR_T_IS_UTF16
#else
#error Please add support for your compiler in build/build_config.h
#endif

#endif // end BUILD_BUILD_CONFIG_H_