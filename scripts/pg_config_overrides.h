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

/* Windows */
#if defined(_WIN32) || defined(_WIN64)
#undef HAVE_COPYFILE
#undef HAVE_COPYFILE_H
#undef HAVE_DECL_F_FULLFSYNC
#define HAVE_DECL_F_FULLFSYNC 0
#undef HAVE_DECL_PREADV
#define HAVE_DECL_PREADV 0
#undef HAVE_DECL_PWRITEV
#define HAVE_DECL_PWRITEV 0
#undef HAVE_DECL_STRLCAT
#define HAVE_DECL_STRLCAT 0
#undef HAVE_DECL_STRLCPY
#define HAVE_DECL_STRLCPY 0
#undef HAVE_GETIFADDRS
#undef HAVE_GETPEEREID
#undef HAVE_IFADDRS_H
#undef HAVE_INET_ATON
#undef HAVE_INT_OPTRESET
#undef HAVE_KQUEUE
#undef HAVE_LANGINFO_H
#undef HAVE_MEMSET_S
#undef HAVE_MKDTEMP
#undef HAVE_PTHREAD
#undef HAVE_PTHREAD_BARRIER_WAIT
#undef HAVE_PTHREAD_IS_THREADED_NP
#undef HAVE_PTHREAD_PRIO_INHERIT
#undef HAVE_STRERROR_R
#undef HAVE_STRLCAT
#undef HAVE_STRLCPY
#undef HAVE_STRSIGNAL
#undef HAVE_STRUCT_SOCKADDR_SA_LEN
#undef HAVE_STRUCT_TM_TM_ZONE
#undef HAVE_SYSLOG
#undef HAVE_SYS_EVENT_H
#undef HAVE_SYS_UCRED_H
#undef HAVE_TERMIOS_H
#undef HAVE_UNION_SEMUN
#undef HAVE_USELOCALE
#define HAVE__CONFIGTHREADLOCALE 1
#undef STRERROR_R_INT
#undef USE_SYSV_SEMAPHORES
#undef USE_SYSV_SHARED_MEMORY
#define USE_WIN32_SEMAPHORES 1
#define USE_WIN32_SHARED_MEMORY 1
#undef PG_PRINTF_ATTRIBUTE
#if defined(__clang__)
#define PG_PRINTF_ATTRIBUTE printf
#elif defined(__MINGW32__) || defined(__MINGW64__) || defined(__MSYS__) || defined(__CYGWIN__)
#define PG_PRINTF_ATTRIBUTE gnu_printf
#endif
#if defined(__MINGW32__) || defined(__MINGW64__) || defined(__MSYS__) || defined(__CYGWIN__)
#undef HAVE_MBSTOWCS_L
#undef HAVE_WCSTOMBS_L
#define HAVE_CRTDEFS_H 1
#define HAVE_PTHREAD_BARRIER_WAIT 1
#endif
#endif

/* Microsoft Visual Studio Compiler */
#ifdef _MSC_VER
#undef HAVE_COMPUTED_GOTO
#undef HAVE_GCC__ATOMIC_INT32_CAS
#undef HAVE_GCC__ATOMIC_INT64_CAS
#undef HAVE_GCC__SYNC_CHAR_TAS
#undef HAVE_GCC__SYNC_INT32_CAS
#undef HAVE_GCC__SYNC_INT32_TAS
#undef HAVE_GCC__SYNC_INT64_CAS
#undef HAVE_GETOPT
#undef HAVE_GETOPT_H
#undef HAVE_GETOPT_LONG
#undef HAVE_INTTYPES_H
#undef HAVE_INT_OPTERR
#undef HAVE_LIBM
#undef HAVE_STRINGS_H
#undef HAVE_STRUCT_OPTION
#undef HAVE_TYPEOF
#undef HAVE_VISIBILITY_ATTRIBUTE
#undef HAVE__BOOL
#undef HAVE__BUILTIN_BSWAP16
#undef HAVE__BUILTIN_BSWAP32
#undef HAVE__BUILTIN_BSWAP64
#undef HAVE__BUILTIN_CLZ
#undef HAVE__BUILTIN_CONSTANT_P
#undef HAVE__BUILTIN_CTZ
#undef HAVE__BUILTIN_FRAME_ADDRESS
#undef HAVE__BUILTIN_OP_OVERFLOW
#undef HAVE__BUILTIN_POPCOUNT
#undef HAVE__BUILTIN_TYPES_COMPATIBLE_P
#undef HAVE__BUILTIN_UNREACHABLE
#ifndef __cplusplus
#define inline __inline
#endif
#undef restrict
#define __thread __declspec( thread )
#endif
