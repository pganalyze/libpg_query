/* This causes compatibility problems on some Linux distros, with "xlocale.h" not being available */
#undef HAVE_LOCALE_T
#undef LOCALE_T_IN_XLOCALE
#undef WCSTOMBS_L_IN_XLOCALE

/* Support gcc earlier than 4.6.0 and MSVC */
#undef HAVE__STATIC_ASSERT

/* Avoid dependency on execinfo (requires extra library on musl-libc based systems, not supported on Windows) */
#undef HAVE_EXECINFO_H
#undef HAVE_BACKTRACE_SYMBOLS

/* Avoid dependency on hardware popcount instructions (POPQNTQ) on x86 */
#undef HAVE_X86_64_POPCNTQ

/* Avoid dependency on cpuid.h (only supported on x86 systems) */
#undef HAVE__GET_CPUID

/* Avoid CRC extension usage to ensure we are not architecture-dependent */
#undef USE_ARMV8_CRC32C
#undef USE_SSE42_CRC32C_WITH_RUNTIME_CHECK

/* Ensure we do not fail on systems that have strchrnul support (FreeBSD, NetBSD and newer glibc) */
#include <stdlib.h>
#if defined(__FreeBSD__) || defined(__NetBSD__) || (defined(__GLIBC__) && ((__GLIBC__ == 2 && __GLIBC_MINOR__ >= 38) || __GLIBC__ > 2))
#define HAVE_STRCHRNUL
#endif

/* 32-bit */
#if defined(_WIN32) || __SIZEOF_POINTER__ == 4
#undef ALIGNOF_DOUBLE
#define ALIGNOF_DOUBLE 4
#undef ALIGNOF_LONG
#define ALIGNOF_LONG 4
#define ALIGNOF_LONG_LONG_INT 4
#undef ALIGNOF_PG_INT128_TYPE
#undef HAVE_LONG_INT_64
#define HAVE_LONG_LONG_INT_64 1
#undef INT64_MODIFIER
#define INT64_MODIFIER "ll"
#undef PG_INT128_TYPE
#undef PG_INT64_TYPE
#define PG_INT64_TYPE long long int
#undef SIZEOF_LONG
#define SIZEOF_LONG 4
#undef SIZEOF_OFF_T
#define SIZEOF_OFF_T 4
#undef SIZEOF_SIZE_T
#define SIZEOF_SIZE_T 4
#undef SIZEOF_VOID_P
#define SIZEOF_VOID_P 4
#endif
