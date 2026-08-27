/* Amalgamated source file */
#include "upb/generated_code_support.h"

/*
 * This is where we define internal portability macros used across upb.
 *
 * All of these macros are undef'd in undef.inc to avoid leaking them to users.
 *
 * The correct usage is:
 *
 *   #include "upb/foobar.h"
 *   #include "upb/baz.h"
 *
 *   // MUST be last included header.
 *   #include "upb/port/def.inc"
 *
 *   // Code for this file.
 *   // <...>
 *
 *   // Can be omitted for .c files, required for .h.
 *   #include "upb/port/undef.inc"
 *
 * This file is private and must not be included by users!
 */

#if !((defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || \
      (defined(__cplusplus) && __cplusplus >= 201703L) ||           \
      (defined(_MSC_VER) && _MSC_VER >= 1900))
#error upb requires C99 or C++17 or MSVC >= 2015.
#endif

// Portable check for GCC minimum version:
// https://gcc.gnu.org/onlinedocs/cpp/Common-Predefined-Macros.html
#if defined(__GNUC__) && defined(__GNUC_MINOR__) && defined(__GNUC_PATCHLEVEL__)
#define UPB_GNUC_MIN(x, y) \
  (__GNUC__ > (x) || __GNUC__ == (x) && __GNUC_MINOR__ >= (y))
#else
#define UPB_GNUC_MIN(x, y) 0
#endif

// Macros for checking for compiler attributes, defined here to avoid the
// problem described in
// https://gcc.gnu.org/onlinedocs/cpp/_005f_005fhas_005fattribute.html.
#ifdef __has_attribute
#define UPB_HAS_ATTRIBUTE(x) __has_attribute(x)
#else
#define UPB_HAS_ATTRIBUTE(x) 0
#endif

#ifdef __has_builtin
#define UPB_HAS_BUILTIN(x) __has_builtin(x)
#else
#define UPB_HAS_BUILTIN(x) 0
#endif

#ifdef __has_extension
#define UPB_HAS_EXTENSION(x) __has_extension(x)
#else
#define UPB_HAS_EXTENSION(x) 0
#endif

#ifdef __has_feature
#define UPB_HAS_FEATURE(x) __has_feature(x)
#else
#define UPB_HAS_FEATURE(x) 0
#endif

#include <assert.h>
#include <setjmp.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef UINTPTR_MAX
Error, UINTPTR_MAX is undefined
#endif

#if UINTPTR_MAX == 0xffffffff
#define UPB_SIZE(size32, size64) size32
#else
#define UPB_SIZE(size32, size64) size64
#endif

/* If we always read/write as a consistent type to each address, this shouldn't
 * violate aliasing.
 */
#define UPB_PTR_AT(msg, ofs, type) ((type *)((char *)(msg) + (ofs)))

// A flexible array member may have lower alignment requirements than the struct
// overall - in that case, it can overlap with the trailing padding of the rest
// of the struct, and a naive sizeof(base) + sizeof(flex) * count calculation
// will not take into account that overlap, and allocate more than is required.
#define UPB_SIZEOF_FLEX(type, member, count) \
  UPB_MAX(sizeof(type), offsetof(type, member[count]))

#define UPB_SIZEOF_FLEX_WOULD_OVERFLOW(type, member, count) \
  (((SIZE_MAX - offsetof(type, member[0])) /                \
    (offsetof(type, member[1]) - offsetof(type, member[0]))) < (size_t)count)

#define UPB_ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

#define UPB_MAPTYPE_STRING 0

// UPB_EXPORT: always generate a public symbol.
#if defined(__GNUC__) || defined(__clang__)
#define UPB_EXPORT __attribute__((visibility("default"))) __attribute__((used))
#else
#define UPB_EXPORT
#endif

// UPB_INLINE: inline if possible, emit standalone code if required.
#ifdef __cplusplus
#define UPB_INLINE inline
#elif defined(__GNUC__) || defined(__clang__)
#define UPB_INLINE static __inline__
#else
#define UPB_INLINE static
#endif

// UPB_INLINE_IF_NOT_GCC: because gcc can be very noisy at times.
#if defined(__GNUC__) && !defined(__clang__)
#define UPB_INLINE_IF_NOT_GCC static
#else
#define UPB_INLINE_IF_NOT_GCC UPB_INLINE
#endif

#ifdef UPB_BUILD_API
#define UPB_API UPB_EXPORT
#define UPB_API_INLINE UPB_EXPORT
#else
#define UPB_API
#define UPB_API_INLINE UPB_INLINE
#endif

#ifdef EXPORT_UPBC
#define UPBC_API UPB_EXPORT
#else
#define UPBC_API
#endif

#if UPB_HAS_FEATURE(address_sanitizer) || defined(__SANITIZE_ADDRESS__)
#define UPB_ASAN 1
#else
#define UPB_ASAN 0
#endif

#if UPB_HAS_FEATURE(hwaddress_sanitizer)
#define UPB_HWASAN 1
#define UPB_HWASAN_POISON_TAG 17
#define UPB_MALLOC_ALIGN 16
#else
#define UPB_HWASAN 0
#define UPB_MALLOC_ALIGN 8
#endif

#if UPB_HAS_FEATURE(thread_sanitizer) || defined(__SANITIZE_THREAD__)
#define UPB_TSAN 1
#else
#define UPB_TSAN 0
#endif

// An unfortunate concession to C++17 and MSVC, which don't support zero-sized
// structs.
#if UPB_ASAN || UPB_HWASAN || UPB_TSAN
#define UPB_XSAN_MEMBER upb_Xsan xsan;
#define UPB_XSAN(st) (&(st)->xsan)
#define UPB_XSAN_STRUCT_SIZE 1
#else
#define UPB_XSAN_MEMBER
#define UPB_XSAN(st) (NULL)
#define UPB_XSAN_STRUCT_SIZE 0
#endif

#define UPB_ALIGN_UP(size, align) (((size) + (align) - 1) / (align) * (align))
#define UPB_ALIGN_DOWN(size, align) ((size) / (align) * (align))
#define UPB_ALIGN_MALLOC(size) UPB_ALIGN_UP(size, UPB_MALLOC_ALIGN)

#if __STDC_VERSION__ >= 202311L || UPB_HAS_EXTENSION(cxx_alignof) || \
    defined(__cplusplus)
#define UPB_ALIGN_OF(type) alignof(type)
#elif __STDC_VERSION__ >= 201112L || UPB_HAS_EXTENSION(c_alignof)
#define UPB_ALIGN_OF(type) _Alignof(type)
#elif UPB_GNUC_MIN(2, 95)
#define UPB_ALIGN_OF(type) __alignof__(type)
#elif defined(_MSC_VER)
#define UPB_ALIGN_OF(type) __alignof(type)
#else
#define UPB_ALIGN_OF(type) \
  offsetof(                \
      struct {             \
        char c;            \
        type member;       \
      },                   \
      member)
#endif

#ifdef _MSC_VER
// Some versions of our Windows compiler don't support the C11 syntax.
#define UPB_ALIGN_AS(x) __declspec(align(x))
#elif defined(__GNUC__)
#define UPB_ALIGN_AS(x) __attribute__((aligned(x)))
#else
#define UPB_ALIGN_AS(x) _Alignas(x)
#endif

#if __STDC_VERSION__ >= 202311L || UPB_HAS_EXTENSION(cxx_static_assert) || \
    defined(__cplusplus)
#define UPB_STATIC_ASSERT(val, msg) static_assert((val), msg)
#elif __STDC_VERSION__ >= 201112L || UPB_HAS_EXTENSION(c_static_assert) || \
    UPB_GNUC_MIN(4, 6)
#define UPB_STATIC_ASSERT(val, msg) _Static_assert((val), msg)
#else
// Unfortunately this hack doesn't work inside struct declarations, but it works
// everywhere else
#define UPB_STATIC_ASSERT_CONCAT_IMPL(s1, s2) s1##s2
#define UPB_STATIC_ASSERT_CONCAT(s1, s2) UPB_STATIC_ASSERT_CONCAT_IMPL(s1, s2)
#ifdef __COUNTER__
#define UPB_STATIC_ASSERT(condition, message)                      \
  typedef char UPB_STATIC_ASSERT_CONCAT(static_assertion_failure_, \
                                        __COUNTER__)[(condition) ? 1 : -1]
#else
#define UPB_STATIC_ASSERT(condition, message)                      \
  typedef char UPB_STATIC_ASSERT_CONCAT(static_assertion_failure_, \
                                        __LINE__)[(condition) ? 1 : -1]
#endif
#endif

// Hints to the compiler about likely/unlikely branches.
#if defined(__GNUC__) || defined(__clang__)
#define UPB_LIKELY(x) __builtin_expect((bool)(x), 1)
#define UPB_UNLIKELY(x) __builtin_expect((bool)(x), 0)
#else
#define UPB_LIKELY(x) (x)
#define UPB_UNLIKELY(x) (x)
#endif

#if UPB_HAS_BUILTIN(__builtin_expect_with_probability)
#define UPB_UNPREDICTABLE(x) \
  __builtin_expect_with_probability((bool)(x), 1, 0.5)
#else
#define UPB_UNPREDICTABLE(x) (x)
#endif

// Macros for function attributes on compilers that support them.
#if defined(__GNUC__) || defined(__clang__)
#define UPB_FORCEINLINE __inline__ __attribute__((always_inline)) static
#define UPB_NOINLINE __attribute__((noinline))
#define UPB_NORETURN __attribute__((__noreturn__))
#define UPB_PRINTF(str, first_vararg) \
  __attribute__((format(printf, str, first_vararg)))
#elif defined(_MSC_VER)
#define UPB_NOINLINE
#define UPB_FORCEINLINE static
#define UPB_NORETURN __declspec(noreturn)
#define UPB_PRINTF(str, first_vararg)
#else /* !defined(__GNUC__) */
#define UPB_FORCEINLINE static
#define UPB_NOINLINE
#define UPB_NORETURN
#define UPB_PRINTF(str, first_vararg)
#endif

#if defined(__clang__)
#define UPB_NODEREF __attribute__((noderef))
#else
#define UPB_NODEREF
#endif

#define UPB_MAX(x, y) ((x) > (y) ? (x) : (y))
#define UPB_MIN(x, y) ((x) < (y) ? (x) : (y))

#define UPB_UNUSED(var) (void)(var)

// UPB_ASSUME(): in release mode, we tell the compiler to assume this is true.
#ifdef NDEBUG
#ifdef __GNUC__
#define UPB_ASSUME(expr) \
  if (!(expr)) __builtin_unreachable()
#elif defined _MSC_VER
#define UPB_ASSUME(expr) \
  if (!(expr)) __assume(0)
#else
#define UPB_ASSUME(expr) \
  do {                   \
  } while (false && (expr))
#endif
#else
#define UPB_ASSUME(expr) assert(expr)
#endif

/* UPB_ASSERT(): in release mode, we use the expression without letting it be
 * evaluated.  This prevents "unused variable" warnings. */
#ifdef NDEBUG
#define UPB_ASSERT(expr) \
  do {                   \
  } while (false && (expr))
#else
#define UPB_ASSERT(expr) assert(expr)
#endif

#if !defined(NDEBUG) && !defined(UPB_TSAN)
#define UPB_ENABLE_REF_CYCLE_CHECKS 1
#else
#define UPB_ENABLE_REF_CYCLE_CHECKS 0
#endif

#if defined(__GNUC__) || defined(__clang__)
#define UPB_UNREACHABLE()    \
  do {                       \
    assert(0);               \
    __builtin_unreachable(); \
  } while (0)
#elif defined(_MSC_VER)
#define UPB_UNREACHABLE() \
  do {                    \
    assert(0);            \
    __assume(0);          \
  } while (0)
#else
#define UPB_UNREACHABLE() \
  do {                    \
    assert(0);            \
  } while (0)
#endif

#ifdef __ANDROID__
#define UPB_DEFAULT_MAX_BLOCK_SIZE 8192
#else
#define UPB_DEFAULT_MAX_BLOCK_SIZE 32768
#endif

/* UPB_SETJMP() / UPB_LONGJMP() */
// Android uses a custom libc that does not implement all of posix, but it has
// had sigsetjmp/siglongjmp forever on arm and since API 12 on x86. Apple has
// sigsetjmp, but does not define the posix feature test macro.
#if defined(__APPLE__) || defined(_POSIX_C_SOURCE) || defined(__ANDROID__)
// avoid setting/restoring signal mask, which involves costly syscalls
#define UPB_SETJMP(buf) sigsetjmp(buf, 0)
#define UPB_LONGJMP(buf, val) siglongjmp(buf, val)
#elif defined(WASM_WAMR)
#define UPB_SETJMP(buf) 0
#define UPB_LONGJMP(buf, val) abort()
#else
#define UPB_SETJMP(buf) setjmp(buf)
#define UPB_LONGJMP(buf, val) longjmp(buf, val)
#endif

#if ((__STDC_VERSION__ >= 201112L) && !defined(__STDC_NO_ATOMICS__)) || \
    UPB_HAS_EXTENSION(c_atomic) ||                                      \
    defined(__GNUC__)  // GCC supported atomics as an extension before it
                       // supported __has_extension
#define UPB_USE_C11_ATOMICS
#elif defined(_MSC_VER)
#define UPB_USE_MSC_ATOMICS
#endif

#if defined(UPB_USE_C11_ATOMICS)
#define UPB_ATOMIC(T) _Atomic(T)
#elif defined(UPB_USE_MSC_ATOMICS)
#define UPB_ATOMIC(T) volatile T
#else
#define UPB_ATOMIC(T) T
#endif

/* UPB_PTRADD(ptr, ofs): add pointer while avoiding "NULL + 0" UB */
#define UPB_PTRADD(ptr, ofs) ((ofs) ? (ptr) + (ofs) : (ptr))

#define UPB_PRIVATE(x) x##_dont_copy_me__upb_internal_use_only

#ifdef UPB_ALLOW_PRIVATE_ACCESS__FOR_BITS_ONLY
#define UPB_ONLYBITS(x) x
#else
#define UPB_ONLYBITS(x) UPB_PRIVATE(x)
#endif

/* Configure whether fasttable is switched on or not. *************************/

#if UPB_HAS_ATTRIBUTE(musttail)
#define UPB_MUSTTAIL __attribute__((musttail))
#else
#define UPB_MUSTTAIL
#endif

#if UPB_HAS_ATTRIBUTE(preserve_none)
#define UPB_PRESERVE_NONE __attribute__((preserve_none))
#else
#define UPB_PRESERVE_NONE
#endif

/* This check is not fully robust: it does not require that we have "musttail"
 * support available. We need tail calls to avoid consuming arbitrary amounts
 * of stack space.
 *
 * GCC/Clang can mostly be trusted to generate tail calls as long as
 * optimization is enabled, but, debug builds will not generate tail calls
 * unless "musttail" is available.
 *
 * We should probably either:
 *   1. require that the compiler supports musttail.
 *   2. add some fallback code for when musttail isn't available (ie. return
 *      instead of tail calling). This is safe and portable, but this comes at
 *      a CPU cost.
 */
#if (defined(__x86_64__) || defined(__aarch64__)) && defined(__GNUC__)
#define UPB_FASTTABLE_SUPPORTED 1
#else
#define UPB_FASTTABLE_SUPPORTED 0
#endif

/* define UPB_ENABLE_FASTTABLE to force fast table support.
 * This is useful when we want to ensure we are really getting fasttable,
 * for example for testing or benchmarking. */
#if defined(UPB_ENABLE_FASTTABLE)
#if !UPB_FASTTABLE_SUPPORTED
#error fasttable is x86-64/ARM64 only and requires GCC or Clang.
#endif
#define UPB_FASTTABLE 1
/* Define UPB_TRY_ENABLE_FASTTABLE to use fasttable if possible.
 * This is useful for releasing code that might be used on multiple platforms,
 * for example the PHP or Ruby C extensions. */
#elif defined(UPB_TRY_ENABLE_FASTTABLE)
#define UPB_FASTTABLE UPB_FASTTABLE_SUPPORTED
#else
#define UPB_FASTTABLE 0
#endif

/* UPB_FASTTABLE_INIT() allows protos compiled for fasttable to gracefully
 * degrade to non-fasttable if the runtime or platform do not support it. */
#if !UPB_FASTTABLE
#define UPB_FASTTABLE_INIT(...)
#define UPB_FASTTABLE_MASK(mask) -1
#else
#define UPB_FASTTABLE_INIT(...) __VA_ARGS__
#define UPB_FASTTABLE_MASK(mask) mask
#endif

#undef UPB_FASTTABLE_SUPPORTED

/* Disable proto2 arena behavior (TEMPORARY) **********************************/

#ifdef UPB_DISABLE_CLOSED_ENUM_CHECKING
#define UPB_TREAT_CLOSED_ENUMS_LIKE_OPEN 1
#else
#define UPB_TREAT_CLOSED_ENUMS_LIKE_OPEN 0
#endif

#if defined(__cplusplus)
#if defined(__clang__) || UPB_GNUC_MIN(6, 0)
// https://gcc.gnu.org/gcc-6/changes.html
#define UPB_DEPRECATED [[deprecated]]
#else
#define UPB_DEPRECATED
#endif
#else
#define UPB_DEPRECATED
#endif

#if defined(UPB_IS_GOOGLE3) && \
    (!defined(UPB_BOOTSTRAP_STAGE) || UPB_BOOTSTRAP_STAGE != 0)
#define UPB_DESC(sym) proto2_##sym
#define UPB_DESC_MINITABLE(sym) &proto2__##sym##_msg_init
#elif defined(UPB_IS_GOOGLE3) && defined(UPB_BOOTSTRAP_STAGE) && \
    UPB_BOOTSTRAP_STAGE == 0
#define UPB_DESC(sym) proto2_##sym
#define UPB_DESC_MINITABLE(sym) proto2__##sym##_msg_init()
#elif defined(UPB_BOOTSTRAP_STAGE) && UPB_BOOTSTRAP_STAGE == 0
#define UPB_DESC(sym) google_protobuf_##sym
#define UPB_DESC_MINITABLE(sym) google__protobuf__##sym##_msg_init()
#else
#define UPB_DESC(sym) google_protobuf_##sym
#define UPB_DESC_MINITABLE(sym) &google__protobuf__##sym##_msg_init
#endif

#undef UPB_IS_GOOGLE3

#ifdef __clang__
#define UPB_NO_SANITIZE_ADDRESS __attribute__((no_sanitize("address")))
#else
#define UPB_NO_SANITIZE_ADDRESS
#endif

// Linker arrays combine elements from multiple translation units into a single
// array that can be iterated over at runtime.
//
// It is an alternative to pre-main "registration" functions.
//
// Usage:
//
//   // In N translation units.
//   UPB_LINKARR_APPEND(foo_array) static int elems[3] = {1, 2, 3};
//
//   // At runtime:
//   UPB_LINKARR_DECLARE(foo_array, int);
//
//   void f() {
//     const int* start = UPB_LINKARR_START(foo_array);
//     const int* stop = UPB_LINKARR_STOP(foo_array);
//     for (const int* p = start; p < stop; p++) {
//       // Windows can introduce zero padding, so we have to skip zeroes.
//       if (*p != 0) {
//         vec.push_back(*p);
//       }
//     }
//   }

#if defined(__ELF__) || defined(__wasm__)

#define UPB_LINKARR_APPEND(name) \
  __attribute__((section("linkarr_" #name))) UPB_NO_SANITIZE_ADDRESS
#define UPB_LINKARR_DECLARE(name, type) \
  extern type __start_linkarr_##name;   \
  extern type __stop_linkarr_##name;    \
  UPB_LINKARR_APPEND(name) type UPB_linkarr_internal_empty_##name[1]
#define UPB_LINKARR_START(name) (&__start_linkarr_##name)
#define UPB_LINKARR_STOP(name) (&__stop_linkarr_##name)

#elif defined(__MACH__)

/* As described in: https://stackoverflow.com/a/22366882 */
#define UPB_LINKARR_APPEND(name) \
  __attribute__((section("__DATA,__la_" #name))) UPB_NO_SANITIZE_ADDRESS
#define UPB_LINKARR_DECLARE(name, type)     \
  extern type __start_linkarr_##name __asm( \
      "section$start$__DATA$__la_" #name);  \
  extern type __stop_linkarr_##name __asm(  \
      "section$end$__DATA$"                 \
      "__la_" #name);                       \
  UPB_LINKARR_APPEND(name) type UPB_linkarr_internal_empty_##name[1]
#define UPB_LINKARR_START(name) (&__start_linkarr_##name)
#define UPB_LINKARR_STOP(name) (&__stop_linkarr_##name)

#elif defined(_MSC_VER) && defined(__clang__)

/* See:
 *   https://devblogs.microsoft.com/oldnewthing/20181107-00/?p=100155
 *   https://devblogs.microsoft.com/oldnewthing/20181108-00/?p=100165
 *   https://devblogs.microsoft.com/oldnewthing/20181109-00/?p=100175 */

// Usage of __attribute__ here probably means this is Clang-specific, and would
// not work on MSVC.
#define UPB_LINKARR_APPEND(name) \
  __declspec(allocate("la_" #name "$j")) UPB_NO_SANITIZE_ADDRESS
#define UPB_LINKARR_DECLARE(name, type)                               \
  __declspec(allocate("la_" #name "$a")) type __start_linkarr_##name; \
  __declspec(allocate("la_" #name "$z")) type __stop_linkarr_##name;  \
  UPB_LINKARR_APPEND(name) type UPB_linkarr_internal_empty_##name[1] = {0}
#define UPB_LINKARR_START(name) (&__start_linkarr_##name)
#define UPB_LINKARR_STOP(name) (&__stop_linkarr_##name)

#else

// Linker arrays are not supported on this platform.  Make appends a no-op but
// don't define the other macros.
#define UPB_LINKARR_APPEND(name)

#endif

// Future versions of upb will include breaking changes to some APIs.
// This macro can be set to enable these API changes ahead of time, so that
// user code can be updated before upgrading versions of protobuf.
#ifdef UPB_FUTURE_BREAKING_CHANGES

#endif

#ifndef UPB_GENERATED_CODE_SUPPORT_H_
#define UPB_GENERATED_CODE_SUPPORT_H_

// This is a bit awkward; we want to conditionally include the fast decoder,
// but we generally don't let macros like UPB_FASTTABLE leak into user code.
// We can't #include "decode_fast.h" inside the port/def.inc, because the
// inc files strictly prohibit recursive inclusion, and decode_fast.h includes
// port/def.inc. So instead we use this two-part dance to conditionally include
// decode_fast.h.
#if UPB_FASTTABLE
#define UPB_INCLUDE_FAST_DECODE
#endif

// IWYU pragma: begin_exports
#ifdef UPB_INCLUDE_FAST_DECODE
#endif
// IWYU pragma: end_exports

#undef UPB_INCLUDE_FAST_DECODE

#endif  // UPB_GENERATED_CODE_SUPPORT_H_


#include <errno.h>
#include <float.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

// Must be last.

void upb_Status_Clear(upb_Status* status) {
  if (!status) return;
  status->ok = true;
  status->msg[0] = '\0';
}

bool upb_Status_IsOk(const upb_Status* status) { return status->ok; }

const char* upb_Status_ErrorMessage(const upb_Status* status) {
  return status->msg;
}

void upb_Status_SetErrorMessage(upb_Status* status, const char* msg) {
  if (!status) return;
  status->ok = false;
  strncpy(status->msg, msg, _kUpb_Status_MaxMessage - 1);
  status->msg[_kUpb_Status_MaxMessage - 1] = '\0';
}

void upb_Status_SetErrorFormat(upb_Status* status, const char* fmt, ...) {
  va_list args;
  va_start(args, fmt);
  upb_Status_VSetErrorFormat(status, fmt, args);
  va_end(args);
}

void upb_Status_VSetErrorFormat(upb_Status* status, const char* fmt,
                                va_list args) {
  if (!status) return;
  status->ok = false;
  vsnprintf(status->msg, sizeof(status->msg), fmt, args);
  status->msg[_kUpb_Status_MaxMessage - 1] = '\0';
}

void upb_Status_VAppendErrorFormat(upb_Status* status, const char* fmt,
                                   va_list args) {
  size_t len;
  if (!status) return;
  status->ok = false;
  len = strlen(status->msg);
  vsnprintf(status->msg + len, sizeof(status->msg) - len, fmt, args);
  status->msg[_kUpb_Status_MaxMessage - 1] = '\0';
}

/*
 * upb_table Implementation
 *
 * Implementation is heavily inspired by Lua's ltable.c.
 */


#include <stdint.h>
#include <string.h>


// Must be last.

#define UPB_MAXARRSIZE 16  // 2**16 = 64k.

// From Chromium.
#define ARRAY_SIZE(x) \
  ((sizeof(x) / sizeof(0 [x])) / ((size_t)(!(sizeof(x) % sizeof(0 [x])))))

/* The minimum utilization of the array part of a mixed hash/array table.  This
 * is a speed/memory-usage tradeoff (though it's not straightforward because of
 * cache effects).  The lower this is, the more memory we'll use. */
static const double MIN_DENSITY = 0.1;

#if defined(__has_builtin)
#if __has_builtin(__builtin_popcount)
#define UPB_FAST_POPCOUNT32(i) __builtin_popcount(i)
#endif
#elif defined(__GNUC__)
#define UPB_FAST_POPCOUNT32(i) __builtin_popcount(i)
#elif defined(_MSC_VER) && (defined(_M_IX86) || defined(_M_X64))
// Only use __popcnt on x86/x64 architectures for MSVC
#define UPB_FAST_POPCOUNT32(i) __popcnt(i)
#endif

UPB_INLINE int _upb_popcnt32(uint32_t i) {
#ifdef UPB_FAST_POPCOUNT32
  return UPB_FAST_POPCOUNT32(i);
#else
  int count = 0;
  while (i != 0) {
    count += i & 1;
    i >>= 1;
  }
  return count;
#endif
}

#undef UPB_FAST_POPCOUNT32

UPB_INLINE uint8_t _upb_log2_table_size(upb_table* t) {
  return _upb_popcnt32(t->mask);
}

static bool is_pow2(uint64_t v) { return v == 0 || (v & (v - 1)) == 0; }

static int log2ceil(uint64_t v) {
  int ret = 0;
  bool pow2 = is_pow2(v);
  while (v >>= 1) ret++;
  ret = pow2 ? ret : ret + 1;  // Ceiling.
  return UPB_MIN(UPB_MAXARRSIZE, ret);
}

/* A type to represent the lookup key of either a strtable or an inttable. */
typedef union {
  uintptr_t num;
  upb_StringView str;
} lookupkey_t;

static lookupkey_t strkey2(const char* str, size_t len) {
  return (lookupkey_t){.str = upb_StringView_FromDataAndSize(str, len)};
}

static lookupkey_t intkey(uintptr_t key) { return (lookupkey_t){.num = key}; }

typedef uint32_t hashfunc_t(upb_key key);
typedef bool eqlfunc_t(upb_key k1, lookupkey_t k2);

/* Base table (shared code) ***************************************************/

static uint32_t upb_inthash(uintptr_t key) {
  if (sizeof(uintptr_t) == 8) {
    return (uint32_t)key ^ (uint32_t)(key >> 32);
  } else {
    UPB_ASSERT(sizeof(uintptr_t) == 4);
    return (uint32_t)key;
  }
}

static const upb_tabent* upb_getentry(const upb_table* t, uint32_t hash) {
  return t->entries + (hash & t->mask);
}

static bool isfull(upb_table* t) {
  uint32_t size = upb_table_size(t);
  // 0.875 load factor
  return t->count == (size - (size >> 3));
}

static bool init(upb_table* t, uint8_t size_lg2, upb_Arena* a) {
  if (size_lg2 >= 32) {
    return false;
  }
  t->count = 0;
  uint32_t size = 1 << size_lg2;
  t->mask = size - 1;  // 0 mask if size_lg2 is 0
  if (upb_table_size(t) > (SIZE_MAX / sizeof(upb_tabent))) {
    return false;
  }
  size_t bytes = upb_table_size(t) * sizeof(upb_tabent);
  if (bytes > 0) {
    t->entries = upb_Arena_Malloc(a, bytes);
    if (!t->entries) return false;
    memset(t->entries, 0, bytes);
  } else {
    t->entries = NULL;
  }
  return true;
}

static upb_tabent* emptyent(upb_table* t, upb_tabent* e) {
  upb_tabent* begin = t->entries;
  upb_tabent* end = begin + upb_table_size(t);
  for (e = e + 1; e < end; e++) {
    if (upb_tabent_isempty(e)) return e;
  }
  for (e = begin; e < end; e++) {
    if (upb_tabent_isempty(e)) return e;
  }
  UPB_ASSERT(false);
  return NULL;
}

static upb_tabent* getentry_mutable(upb_table* t, uint32_t hash) {
  return (upb_tabent*)upb_getentry(t, hash);
}

static const upb_tabent* findentry(const upb_table* t, lookupkey_t key,
                                   uint32_t hash, eqlfunc_t* eql) {
  const upb_tabent* e;

  if (t->count == 0) return NULL;
  e = upb_getentry(t, hash);
  if (upb_tabent_isempty(e)) return NULL;
  while (1) {
    if (eql(e->key, key)) return e;
    if ((e = e->next) == NULL) return NULL;
  }
}

static upb_tabent* findentry_mutable(upb_table* t, lookupkey_t key,
                                     uint32_t hash, eqlfunc_t* eql) {
  return (upb_tabent*)findentry(t, key, hash, eql);
}

static bool lookup(const upb_table* t, lookupkey_t key, upb_value* v,
                   uint32_t hash, eqlfunc_t* eql) {
  const upb_tabent* e = findentry(t, key, hash, eql);
  if (e) {
    if (v) *v = e->val;
    return true;
  } else {
    return false;
  }
}

/* The given key must not already exist in the table. */
static void insert(upb_table* t, lookupkey_t key, upb_key tabkey, upb_value val,
                   uint32_t hash, hashfunc_t* hashfunc, eqlfunc_t* eql) {
  upb_tabent* mainpos_e;
  upb_tabent* our_e;

  UPB_ASSERT(findentry(t, key, hash, eql) == NULL);

  t->count++;
  mainpos_e = getentry_mutable(t, hash);
  our_e = mainpos_e;

  if (upb_tabent_isempty(mainpos_e)) {
    /* Our main position is empty; use it. */
    our_e->next = NULL;
  } else {
    /* Collision. */
    upb_tabent* new_e = emptyent(t, mainpos_e);
    /* Head of collider's chain. */
    upb_tabent* chain = getentry_mutable(t, hashfunc(mainpos_e->key));
    if (chain == mainpos_e) {
      /* Existing ent is in its main position (it has the same hash as us, and
       * is the head of our chain).  Insert to new ent and append to this chain.
       */
      new_e->next = mainpos_e->next;
      mainpos_e->next = new_e;
      our_e = new_e;
    } else {
      /* Existing ent is not in its main position (it is a node in some other
       * chain).  This implies that no existing ent in the table has our hash.
       * Evict it (updating its chain) and use its ent for head of our chain. */
      *new_e = *mainpos_e; /* copies next. */
      while (chain->next != mainpos_e) {
        chain = (upb_tabent*)chain->next;
        UPB_ASSERT(chain);
      }
      chain->next = new_e;
      our_e = mainpos_e;
      our_e->next = NULL;
    }
  }
  our_e->key = tabkey;
  our_e->val = val;
  UPB_ASSERT(findentry(t, key, hash, eql) == our_e);
}

static bool rm(upb_table* t, lookupkey_t key, upb_value* val, uint32_t hash,
               eqlfunc_t* eql) {
  upb_tabent* chain = getentry_mutable(t, hash);
  if (upb_tabent_isempty(chain)) return false;
  if (eql(chain->key, key)) {
    /* Element to remove is at the head of its chain. */
    t->count--;
    if (val) *val = chain->val;
    if (chain->next) {
      upb_tabent* move = (upb_tabent*)chain->next;
      *chain = *move;
      move->key = upb_key_empty();
    } else {
      chain->key = upb_key_empty();
    }
    return true;
  } else {
    /* Element to remove is either in a non-head position or not in the
     * table. */
    while (chain->next && !eql(chain->next->key, key)) {
      chain = (upb_tabent*)chain->next;
    }
    if (chain->next) {
      /* Found element to remove. */
      upb_tabent* rm = (upb_tabent*)chain->next;
      t->count--;
      if (val) *val = chain->next->val;
      rm->key = upb_key_empty();
      chain->next = rm->next;
      return true;
    } else {
      /* Element to remove is not in the table. */
      return false;
    }
  }
}

static size_t next(const upb_table* t, size_t i) {
  do {
    if (++i >= upb_table_size(t)) return SIZE_MAX - 1; /* Distinct from -1. */
  } while (upb_tabent_isempty(&t->entries[i]));

  return i;
}

static size_t begin(const upb_table* t) { return next(t, -1); }

/* upb_strtable ***************************************************************/

// A simple "subclass" of upb_table that only adds a hash function for strings.

static upb_SizePrefixString* upb_SizePrefixString_Copy(upb_StringView s,
                                                       upb_Arena* a) {
  // A 2GB string will fail at serialization time, but we accept up to 4GB in
  // memory here.
  if (s.size > UINT32_MAX) return NULL;
  upb_SizePrefixString* str =
      upb_Arena_Malloc(a, sizeof(uint32_t) + s.size + 1);
  if (str == NULL) return NULL;
  str->size = s.size;
  char* data = (char*)str->data;
  if (s.size) memcpy(data, s.data, s.size);
  data[s.size] = '\0';
  return str;
}

/* Adapted from ABSL's wyhash. */

static uint64_t UnalignedLoad64(const void* p) {
  uint64_t val;
  memcpy(&val, p, 8);
  return val;
}

static uint32_t UnalignedLoad32(const void* p) {
  uint32_t val;
  memcpy(&val, p, 4);
  return val;
}

#if defined(_MSC_VER) && defined(_M_X64)
#include <intrin.h>
#endif

/* Computes a * b, returning the low 64 bits of the result and storing the high
 * 64 bits in |*high|. */
static uint64_t upb_umul128(uint64_t v0, uint64_t v1, uint64_t* out_high) {
#ifdef __SIZEOF_INT128__
  __uint128_t p = v0;
  p *= v1;
  *out_high = (uint64_t)(p >> 64);
  return (uint64_t)p;
#elif defined(_MSC_VER) && defined(_M_X64)
  return _umul128(v0, v1, out_high);
#else
  uint64_t a32 = v0 >> 32;
  uint64_t a00 = v0 & 0xffffffff;
  uint64_t b32 = v1 >> 32;
  uint64_t b00 = v1 & 0xffffffff;
  uint64_t high = a32 * b32;
  uint64_t low = a00 * b00;
  uint64_t mid1 = a32 * b00;
  uint64_t mid2 = a00 * b32;
  low += (mid1 << 32) + (mid2 << 32);
  // Omit carry bit, for mixing we do not care about exact numerical precision.
  high += (mid1 >> 32) + (mid2 >> 32);
  *out_high = high;
  return low;
#endif
}

static uint64_t WyhashMix(uint64_t v0, uint64_t v1) {
  uint64_t high;
  uint64_t low = upb_umul128(v0, v1, &high);
  return low ^ high;
}

static uint64_t Wyhash(const void* data, size_t len, uint64_t seed,
                       const uint64_t salt[]) {
  const uint8_t* ptr = (const uint8_t*)data;
  uint64_t starting_length = (uint64_t)len;
  uint64_t current_state = seed ^ salt[0];

  if (len > 64) {
    // If we have more than 64 bytes, we're going to handle chunks of 64
    // bytes at a time. We're going to build up two separate hash states
    // which we will then hash together.
    uint64_t duplicated_state = current_state;

    do {
      uint64_t a = UnalignedLoad64(ptr);
      uint64_t b = UnalignedLoad64(ptr + 8);
      uint64_t c = UnalignedLoad64(ptr + 16);
      uint64_t d = UnalignedLoad64(ptr + 24);
      uint64_t e = UnalignedLoad64(ptr + 32);
      uint64_t f = UnalignedLoad64(ptr + 40);
      uint64_t g = UnalignedLoad64(ptr + 48);
      uint64_t h = UnalignedLoad64(ptr + 56);

      uint64_t cs0 = WyhashMix(a ^ salt[1], b ^ current_state);
      uint64_t cs1 = WyhashMix(c ^ salt[2], d ^ current_state);
      current_state = (cs0 ^ cs1);

      uint64_t ds0 = WyhashMix(e ^ salt[3], f ^ duplicated_state);
      uint64_t ds1 = WyhashMix(g ^ salt[4], h ^ duplicated_state);
      duplicated_state = (ds0 ^ ds1);

      ptr += 64;
      len -= 64;
    } while (len > 64);

    current_state = current_state ^ duplicated_state;
  }

  // We now have a data `ptr` with at most 64 bytes and the current state
  // of the hashing state machine stored in current_state.
  while (len > 16) {
    uint64_t a = UnalignedLoad64(ptr);
    uint64_t b = UnalignedLoad64(ptr + 8);

    current_state = WyhashMix(a ^ salt[1], b ^ current_state);

    ptr += 16;
    len -= 16;
  }

  // We now have a data `ptr` with at most 16 bytes.
  uint64_t a = 0;
  uint64_t b = 0;
  if (len > 8) {
    // When we have at least 9 and at most 16 bytes, set A to the first 64
    // bits of the input and B to the last 64 bits of the input. Yes, they will
    // overlap in the middle if we are working with less than the full 16
    // bytes.
    a = UnalignedLoad64(ptr);
    b = UnalignedLoad64(ptr + len - 8);
  } else if (len > 3) {
    // If we have at least 4 and at most 8 bytes, set A to the first 32
    // bits and B to the last 32 bits.
    a = UnalignedLoad32(ptr);
    b = UnalignedLoad32(ptr + len - 4);
  } else if (len > 0) {
    // If we have at least 1 and at most 3 bytes, read all of the provided
    // bits into A, with some adjustments.
    a = ((ptr[0] << 16) | (ptr[len >> 1] << 8) | ptr[len - 1]);
    b = 0;
  } else {
    a = 0;
    b = 0;
  }

  uint64_t w = WyhashMix(a ^ salt[1], b ^ current_state);
  uint64_t z = salt[1] ^ starting_length;
  return WyhashMix(w, z);
}

const uint64_t kWyhashSalt[5] = {
    0x243F6A8885A308D3ULL, 0x13198A2E03707344ULL, 0xA4093822299F31D0ULL,
    0x082EFA98EC4E6C89ULL, 0x452821E638D01377ULL,
};

uint32_t _upb_Hash(const void* p, size_t n, uint64_t seed) {
  return Wyhash(p, n, seed, kWyhashSalt);
}

static const void* const _upb_seed;

// Returns a random seed for upb's hash function. This does not provide
// high-quality randomness, but it should be enough to prevent unit tests from
// relying on a deterministic map ordering. By returning the address of a
// variable, we are able to get some randomness for free provided that ASLR is
// enabled.
static uint64_t _upb_Seed(void) { return (uint64_t)&_upb_seed; }

static uint32_t _upb_Hash_NoSeed(const char* p, size_t n) {
  return _upb_Hash(p, n, _upb_Seed());
}

static uint32_t strhash(upb_key key) {
  return _upb_Hash_NoSeed(key.str->data, key.str->size);
}

static bool streql(upb_key k1, lookupkey_t k2) {
  const upb_SizePrefixString* k1s = k1.str;
  const upb_StringView k2s = k2.str;
  return k1s->size == k2s.size &&
         (k1s->size == 0 || memcmp(k1s->data, k2s.data, k1s->size) == 0);
}

/** Calculates the number of entries required to hold an expected number of
 * values, within the table's load factor. */
static size_t _upb_entries_needed_for(size_t expected_size) {
  size_t need_entries = expected_size + 1 + expected_size / 7;
  UPB_ASSERT(need_entries - (need_entries >> 3) >= expected_size);
  return need_entries;
}

bool upb_strtable_init(upb_strtable* t, size_t expected_size, upb_Arena* a) {
  int size_lg2 = upb_Log2Ceiling(_upb_entries_needed_for(expected_size));
  return init(&t->t, size_lg2, a);
}

void upb_strtable_clear(upb_strtable* t) {
  size_t bytes = upb_table_size(&t->t) * sizeof(upb_tabent);
  t->t.count = 0;
  memset((char*)t->t.entries, 0, bytes);
}

bool upb_strtable_resize(upb_strtable* t, size_t size_lg2, upb_Arena* a) {
  upb_strtable new_table;
  if (!init(&new_table.t, size_lg2, a)) return false;

  intptr_t iter = UPB_STRTABLE_BEGIN;
  upb_StringView sv;
  upb_value val;
  while (upb_strtable_next2(t, &sv, &val, &iter)) {
    // Unlike normal insert, does not copy string data or possibly reallocate
    // the table
    // The data pointer used in the table is guaranteed to point at a
    // upb_SizePrefixString, we just need to back up by the size of the uint32_t
    // length prefix.
    const upb_SizePrefixString* keystr =
        (const upb_SizePrefixString*)(sv.data - sizeof(uint32_t));
    UPB_ASSERT(keystr->data == sv.data);
    UPB_ASSERT(keystr->size == sv.size);

    lookupkey_t lookupkey = {.str = sv};
    upb_key tabkey = {.str = keystr};
    uint32_t hash = _upb_Hash_NoSeed(sv.data, sv.size);
    insert(&new_table.t, lookupkey, tabkey, val, hash, &strhash, &streql);
  }
  *t = new_table;
  return true;
}

bool upb_strtable_insert(upb_strtable* t, const char* k, size_t len,
                         upb_value v, upb_Arena* a) {
  if (isfull(&t->t)) {
    /* Need to resize.  New table of double the size, add old elements to it. */
    if (!upb_strtable_resize(t, _upb_log2_table_size(&t->t) + 1, a)) {
      return false;
    }
  }

  upb_StringView sv = upb_StringView_FromDataAndSize(k, len);
  upb_SizePrefixString* size_prefix_string = upb_SizePrefixString_Copy(sv, a);
  if (!size_prefix_string) return false;

  lookupkey_t lookupkey = {.str = sv};
  upb_key key = {.str = size_prefix_string};
  uint32_t hash = _upb_Hash_NoSeed(k, len);
  insert(&t->t, lookupkey, key, v, hash, &strhash, &streql);
  return true;
}

bool upb_strtable_lookup2(const upb_strtable* t, const char* key, size_t len,
                          upb_value* v) {
  uint32_t hash = _upb_Hash_NoSeed(key, len);
  return lookup(&t->t, strkey2(key, len), v, hash, &streql);
}

bool upb_strtable_remove2(upb_strtable* t, const char* key, size_t len,
                          upb_value* val) {
  uint32_t hash = _upb_Hash_NoSeed(key, len);
  return rm(&t->t, strkey2(key, len), val, hash, &streql);
}

/* Iteration */

void upb_strtable_begin(upb_strtable_iter* i, const upb_strtable* t) {
  i->t = t;
  i->index = begin(&t->t);
}

void upb_strtable_next(upb_strtable_iter* i) {
  i->index = next(&i->t->t, i->index);
}

bool upb_strtable_done(const upb_strtable_iter* i) {
  if (!i->t) return true;
  return i->index >= upb_table_size(&i->t->t) ||
         upb_tabent_isempty(str_tabent(i));
}

upb_StringView upb_strtable_iter_key(const upb_strtable_iter* i) {
  UPB_ASSERT(!upb_strtable_done(i));
  return upb_key_strview(str_tabent(i)->key);
}

upb_value upb_strtable_iter_value(const upb_strtable_iter* i) {
  UPB_ASSERT(!upb_strtable_done(i));
  return str_tabent(i)->val;
}

void upb_strtable_iter_setdone(upb_strtable_iter* i) {
  i->t = NULL;
  i->index = SIZE_MAX;
}

bool upb_strtable_iter_isequal(const upb_strtable_iter* i1,
                               const upb_strtable_iter* i2) {
  if (upb_strtable_done(i1) && upb_strtable_done(i2)) return true;
  return i1->t == i2->t && i1->index == i2->index;
}

bool upb_strtable_next2(const upb_strtable* t, upb_StringView* key,
                        upb_value* val, intptr_t* iter) {
  size_t tab_idx = next(&t->t, *iter);
  if (tab_idx < upb_table_size(&t->t)) {
    upb_tabent* ent = &t->t.entries[tab_idx];
    *key = upb_key_strview(ent->key);
    *val = ent->val;
    *iter = tab_idx;
    return true;
  }

  return false;
}

void upb_strtable_removeiter(upb_strtable* t, intptr_t* iter) {
  intptr_t i = *iter;
  upb_tabent* ent = &t->t.entries[i];
  upb_tabent* prev = NULL;

  // Linear search, not great.
  upb_tabent* end = &t->t.entries[upb_table_size(&t->t)];
  for (upb_tabent* e = t->t.entries; e != end; e++) {
    if (e->next == ent) {
      prev = e;
      break;
    }
  }

  if (prev) {
    prev->next = ent->next;
  }

  t->t.count--;
  ent->key = upb_key_empty();
  ent->next = NULL;
}

void upb_strtable_setentryvalue(upb_strtable* t, intptr_t iter, upb_value v) {
  t->t.entries[iter].val = v;
}

/* upb_inttable ***************************************************************/

/* For inttables we use a hybrid structure where small keys are kept in an
 * array and large keys are put in the hash table. */

// The sentinel value used in the dense array part. Note that callers must
// ensure that inttable is never used with a value of this sentinel type
// (pointers and u32 values will never be; i32 needs to be handled carefully
// to avoid sign-extending into this value).
static const upb_value kInttableSentinel = {.val = UINT64_MAX};
static uint32_t presence_mask_arr_size(uint32_t array_size) {
  return (array_size + 7) / 8;  // sizeof(uint8_t) is always 1.
}

static uint32_t inthash(upb_key key) { return upb_inthash(key.num); }

static bool inteql(upb_key k1, lookupkey_t k2) { return k1.num == k2.num; }

static upb_value* mutable_array(upb_inttable* t) {
  return (upb_value*)t->array;
}

static const upb_value* inttable_array_get(const upb_inttable* t,
                                           uintptr_t key) {
  UPB_ASSERT(key < t->array_size);
  const upb_value* val = &t->array[key];
  return upb_inttable_arrhas(t, key) ? val : NULL;
}

static upb_value* inttable_val(upb_inttable* t, uintptr_t key) {
  if (key < t->array_size) {
    return (upb_value*)inttable_array_get(t, key);
  } else {
    upb_tabent* e =
        findentry_mutable(&t->t, intkey(key), upb_inthash(key), &inteql);
    return e ? &e->val : NULL;
  }
}

static const upb_value* inttable_val_const(const upb_inttable* t,
                                           uintptr_t key) {
  return inttable_val((upb_inttable*)t, key);
}

size_t upb_inttable_count(const upb_inttable* t) {
  return t->t.count + t->array_count;
}

static void check(upb_inttable* t) {
  UPB_UNUSED(t);
#if defined(UPB_DEBUG_TABLE) && !defined(NDEBUG)
  {
    // This check is very expensive (makes inserts/deletes O(N)).
    size_t count = 0;
    intptr_t iter = UPB_INTTABLE_BEGIN;
    uintptr_t key;
    upb_value val;
    while (upb_inttable_next(t, &key, &val, &iter)) {
      UPB_ASSERT(upb_inttable_lookup(t, key, NULL));
    }
    UPB_ASSERT(count == upb_inttable_count(t));
  }
#endif
}

bool upb_inttable_sizedinit(upb_inttable* t, uint32_t asize, int hsize_lg2,
                            upb_Arena* a) {
  if (!init(&t->t, hsize_lg2, a)) return false;
  /* Always make the array part at least 1 long, so that we know key 0
   * won't be in the hash part, which simplifies things. */
  t->array_size = UPB_MAX(1, asize);
  t->array_count = 0;
#if UINT32_MAX >= SIZE_MAX
  if (UPB_UNLIKELY(SIZE_MAX / sizeof(upb_value) < t->array_size)) {
    return false;
  }
#endif

  // Allocate the array part and the presence mask array in one allocation.
  size_t array_bytes = t->array_size * sizeof(upb_value);
  uint32_t presence_bytes = presence_mask_arr_size(t->array_size);
  uintptr_t total_bytes = array_bytes + presence_bytes;
  if (UPB_UNLIKELY(total_bytes > SIZE_MAX)) {
    return false;
  }
  void* alloc = upb_Arena_Malloc(a, total_bytes);
  if (!alloc) {
    return false;
  }
  t->array = alloc;
  memset(mutable_array(t), 0xff, array_bytes);
  t->presence_mask = (uint8_t*)alloc + array_bytes;
  memset((uint8_t*)t->presence_mask, 0, presence_bytes);

  check(t);
  return true;
}

bool upb_inttable_init(upb_inttable* t, upb_Arena* a) {
  // The init size of the table part to match that of strtable.
  return upb_inttable_sizedinit(t, 0, 3, a);
}

bool upb_inttable_insert(upb_inttable* t, uintptr_t key, upb_value val,
                         upb_Arena* a) {
  if (key < t->array_size) {
    UPB_ASSERT(!upb_inttable_arrhas(t, key));
    t->array_count++;
    mutable_array(t)[key] = val;
    ((uint8_t*)t->presence_mask)[key / 8] |= (1 << (key % 8));
  } else {
    if (isfull(&t->t)) {
      /* Need to resize the hash part, but we re-use the array part. */
      size_t i;
      upb_table new_table;

      if (!init(&new_table, _upb_log2_table_size(&t->t) + 1, a)) {
        return false;
      }

      for (i = begin(&t->t); i < upb_table_size(&t->t); i = next(&t->t, i)) {
        const upb_tabent* e = &t->t.entries[i];
        insert(&new_table, intkey(e->key.num), e->key, e->val, inthash(e->key),
               &inthash, &inteql);
      }

      UPB_ASSERT(t->t.count == new_table.count);

      t->t = new_table;
    }
    upb_key tabkey = {.num = key};
    insert(&t->t, intkey(key), tabkey, val, upb_inthash(key), &inthash,
           &inteql);
  }
  check(t);
  return true;
}

bool upb_inttable_lookup(const upb_inttable* t, uintptr_t key, upb_value* v) {
  const upb_value* table_v = inttable_val_const(t, key);
  if (!table_v) return false;
  if (v) *v = *table_v;
  return true;
}

bool upb_inttable_replace(upb_inttable* t, uintptr_t key, upb_value val) {
  upb_value* table_v = inttable_val(t, key);
  if (!table_v) return false;
  *table_v = val;
  return true;
}

bool upb_inttable_remove(upb_inttable* t, uintptr_t key, upb_value* val) {
  bool success;
  if (key < t->array_size) {
    if (upb_inttable_arrhas(t, key)) {
      t->array_count--;
      if (val) {
        *val = t->array[key];
      }
      mutable_array(t)[key] = kInttableSentinel;
      ((uint8_t*)t->presence_mask)[key / 8] &= ~(1 << (key % 8));
      success = true;
    } else {
      success = false;
    }
  } else {
    success = rm(&t->t, intkey(key), val, upb_inthash(key), &inteql);
  }
  check(t);
  return success;
}

bool upb_inttable_compact(upb_inttable* t, upb_Arena* a) {
  /* A power-of-two histogram of the table keys. */
  uint32_t counts[UPB_MAXARRSIZE + 1] = {0};

  /* The max key in each bucket. */
  uintptr_t max[UPB_MAXARRSIZE + 1] = {0};

  {
    intptr_t iter = UPB_INTTABLE_BEGIN;
    uintptr_t key;
    upb_value val;
    while (upb_inttable_next(t, &key, &val, &iter)) {
      int bucket = log2ceil(key);
      max[bucket] = UPB_MAX(max[bucket], key);
      counts[bucket]++;
    }
  }

  /* Find the largest power of two that satisfies the MIN_DENSITY
   * definition (while actually having some keys). */
  uint32_t arr_count = upb_inttable_count(t);

  // Scan all buckets except capped bucket
  int size_lg2 = ARRAY_SIZE(counts) - 1;
  for (; size_lg2 > 0; size_lg2--) {
    if (counts[size_lg2] == 0) {
      /* We can halve again without losing any entries. */
      continue;
    } else if (arr_count >= (1 << size_lg2) * MIN_DENSITY) {
      break;
    }

    arr_count -= counts[size_lg2];
  }

  UPB_ASSERT(arr_count <= upb_inttable_count(t));

  upb_inttable new_t;
  {
    /* Insert all elements into new, perfectly-sized table. */
    uintptr_t arr_size = max[size_lg2] + 1; /* +1 so arr[max] will fit. */
    uint32_t hash_count = upb_inttable_count(t) - arr_count;
    size_t hash_size = hash_count ? _upb_entries_needed_for(hash_count) : 0;
    int hashsize_lg2 = log2ceil(hash_size);

    if (!upb_inttable_sizedinit(&new_t, arr_size, hashsize_lg2, a)) {
      return false;
    }

    {
      intptr_t iter = UPB_INTTABLE_BEGIN;
      uintptr_t key;
      upb_value val;
      while (upb_inttable_next(t, &key, &val, &iter)) {
        upb_inttable_insert(&new_t, key, val, a);
      }
    }

    UPB_ASSERT(new_t.array_size == arr_size);
  }
  *t = new_t;
  return true;
}

void upb_inttable_clear(upb_inttable* t) {
  // Clear the array part.
  size_t array_bytes = t->array_size * sizeof(upb_value);
  t->array_count = 0;
  // Clear the array by setting all bits to 1, as UINT64_MAX is the sentinel
  // value for an empty array.
  memset(mutable_array(t), 0xff, array_bytes);
  // Clear the presence mask array.
  memset((uint8_t*)t->presence_mask, 0, presence_mask_arr_size(t->array_size));
  // Clear the table part.
  size_t bytes = upb_table_size(&t->t) * sizeof(upb_tabent);
  t->t.count = 0;
  memset((char*)t->t.entries, 0, bytes);
}

// Iteration.

bool upb_inttable_next(const upb_inttable* t, uintptr_t* key, upb_value* val,
                       intptr_t* iter) {
  intptr_t i = *iter;
  if ((size_t)(i + 1) <= t->array_size) {
    while ((size_t)++i < t->array_size) {
      const upb_value* ent = inttable_array_get(t, i);
      if (ent) {
        *key = i;
        *val = *ent;
        *iter = i;
        return true;
      }
    }
    i--;  // Back up to exactly one position before the start of the table.
  }

  size_t tab_idx = next(&t->t, i - t->array_size);
  if (tab_idx < upb_table_size(&t->t)) {
    upb_tabent* ent = &t->t.entries[tab_idx];
    *key = ent->key.num;
    *val = ent->val;
    *iter = tab_idx + t->array_size;
    return true;
  } else {
    // We should set the iterator any way. When we are done, the iterator value
    // is invalidated. `upb_inttable_done` will check on the iterator value to
    // determine if the iteration is done.
    *iter = INTPTR_MAX - 1;  // To disambiguate from UPB_INTTABLE_BEGIN, to
                             // match the behavior of `upb_strtable_iter`.
    return false;
  }
}

void upb_inttable_removeiter(upb_inttable* t, intptr_t* iter) {
  intptr_t i = *iter;
  if ((size_t)i < t->array_size) {
    t->array_count--;
    mutable_array(t)[i].val = -1;
  } else {
    upb_tabent* ent = &t->t.entries[i - t->array_size];
    upb_tabent* prev = NULL;

    // Linear search, not great.
    upb_tabent* end = &t->t.entries[upb_table_size(&t->t)];
    for (upb_tabent* e = t->t.entries; e != end; e++) {
      if (e->next == ent) {
        prev = e;
        break;
      }
    }

    if (prev) {
      prev->next = ent->next;
    }

    t->t.count--;
    ent->key = upb_key_empty();
    ent->next = NULL;
  }
}

void upb_inttable_setentryvalue(upb_inttable* t, intptr_t iter, upb_value v) {
  if ((size_t)iter < t->array_size) {
    mutable_array(t)[iter] = v;
  } else {
    upb_tabent* ent = &t->t.entries[iter - t->array_size];
    ent->val = v;
  }
}

bool upb_inttable_done(const upb_inttable* t, intptr_t iter) {
  if ((uintptr_t)iter >= t->array_size + upb_table_size(&t->t)) {
    return true;
  } else if ((size_t)iter < t->array_size) {
    return !upb_inttable_arrhas(t, iter);
  } else {
    return upb_tabent_isempty(&t->t.entries[iter - t->array_size]);
  }
}

uintptr_t upb_inttable_iter_key(const upb_inttable* t, intptr_t iter) {
  UPB_ASSERT(!upb_inttable_done(t, iter));
  return (size_t)iter < t->array_size
             ? iter
             : t->t.entries[iter - t->array_size].key.num;
}

upb_value upb_inttable_iter_value(const upb_inttable* t, intptr_t iter) {
  UPB_ASSERT(!upb_inttable_done(t, iter));
  if ((size_t)iter < t->array_size) {
    return t->array[iter];
  } else {
    return t->t.entries[iter - t->array_size].val;
  }
}


#include <stdlib.h>

// Must be last.

static void* upb_global_allocfunc(upb_alloc* alloc, void* ptr, size_t oldsize,
                                  size_t size, size_t* actual_size) {
  UPB_UNUSED(alloc);
  UPB_UNUSED(oldsize);
  UPB_UNUSED(actual_size);
  if (size == 0) {
    free(ptr);
    return NULL;
  } else {
    return realloc(ptr, size);
  }
}

upb_alloc upb_alloc_global = {&upb_global_allocfunc};


#include <string.h>


#ifdef UPB_TRACING_ENABLED
#include <stdatomic.h>
#endif

#include <stddef.h>
#include <stdint.h>


// Must be last.

static UPB_ATOMIC(size_t) g_max_block_size = UPB_DEFAULT_MAX_BLOCK_SIZE;

void upb_Arena_SetMaxBlockSize(size_t max) {
  upb_Atomic_Store(&g_max_block_size, max, memory_order_relaxed);
}

typedef struct upb_MemBlock {
  struct upb_MemBlock* next;
  // Size of the actual allocation.
  // Size of 0 means this is a upb_ArenaRef.
  size_t size;
  // Data follows.
} upb_MemBlock;

// A special block type that indicates a reference to another arena.
// When this arena is freed, a ref is released on the referenced arena.
// size must be 0.
typedef struct upb_ArenaRef {
  upb_MemBlock prefix;  // size is always zero
  const upb_Arena* arena;
#ifndef NDEBUG
  const struct upb_ArenaRef* next_ref;
#endif
} upb_ArenaRef;

typedef struct upb_ArenaInternal {
  // upb_alloc* together with a low bit which signals if there is an initial
  // block.
  uintptr_t block_alloc;

  // Linked list of blocks to free/cleanup.
  upb_MemBlock* blocks;

#ifndef NDEBUG
  // Stack of pointers to other arenas that this arena owns.
  // Used for debug-only ref cycle checks.
  UPB_ATOMIC(const upb_ArenaRef*) refs;
#endif

  // A growing hint of what the *next* block should be sized
  size_t size_hint;

  // All non atomic members used during allocation must be above this point, and
  // are used by _SwapIn/_SwapOut

  // Total space allocated in blocks, atomic only for SpaceAllocated
  UPB_ATOMIC(uintptr_t) space_allocated;

  // The cleanup for the allocator. This is called after all the blocks are
  // freed in an arena.
  upb_AllocCleanupFunc* upb_alloc_cleanup;

  // When multiple arenas are fused together, each arena points to a parent
  // arena (root points to itself). The root tracks how many live arenas
  // reference it.

  // The low bit is tagged:
  //   0: pointer to parent
  //   1: count, left shifted by one
  UPB_ATOMIC(uintptr_t) parent_or_count;

  // All nodes that are fused together are in a singly-linked list.
  // == NULL at end of list.
  UPB_ATOMIC(struct upb_ArenaInternal*) next;

  // - If the low bit is set, is a pointer to the tail of the list (populated
  //   for roots, set to self for roots with no fused arenas). This is best
  //   effort, and it may not always reflect the true tail, but it will always
  //   be a valid node in the list. This is useful for finding the list tail
  //   without having to walk the entire list.
  // - If the low bit is not set, is a pointer to the previous node in the list,
  //   such that a->previous_or_tail->next == a.
  UPB_ATOMIC(uintptr_t) previous_or_tail;

  // We use a different UPB_XSAN_MEMBER than the one in upb_Arena because the
  // two are distinct synchronization domains.  The upb_Arena.ptr member is
  // not published in the allocation path, so it is not synchronized with
  // respect to operations performed in this file such as Fuse, Free,
  // SpaceAllocated, etc.  This means that it is not safe to read or write
  // the upb_Arena.ptr member in those functions.
  UPB_XSAN_MEMBER
} upb_ArenaInternal;

// All public + private state for an arena.
typedef struct {
  upb_Arena head;
  upb_ArenaInternal body;
} upb_ArenaState;

typedef struct {
  upb_ArenaInternal* root;
  uintptr_t tagged_count;
} upb_ArenaRoot;

static const size_t kUpb_MemblockReserve =
    UPB_ALIGN_MALLOC(sizeof(upb_MemBlock));

static const size_t kUpb_ArenaRefReserve =
    UPB_ALIGN_MALLOC(sizeof(upb_ArenaRef));

// Extracts the (upb_ArenaInternal*) from a (upb_Arena*)
static upb_ArenaInternal* upb_Arena_Internal(const upb_Arena* a) {
  return &((upb_ArenaState*)a)->body;
}

static bool _upb_Arena_IsTaggedRefcount(uintptr_t parent_or_count) {
  return (parent_or_count & 1) == 1;
}

static bool _upb_Arena_IsTaggedPointer(uintptr_t parent_or_count) {
  return (parent_or_count & 1) == 0;
}

static uintptr_t _upb_Arena_RefCountFromTagged(uintptr_t parent_or_count) {
  UPB_ASSERT(_upb_Arena_IsTaggedRefcount(parent_or_count));
  return parent_or_count >> 1;
}

static uintptr_t _upb_Arena_TaggedFromRefcount(uintptr_t refcount) {
  uintptr_t parent_or_count = (refcount << 1) | 1;
  UPB_ASSERT(_upb_Arena_IsTaggedRefcount(parent_or_count));
  return parent_or_count;
}

static upb_ArenaInternal* _upb_Arena_PointerFromTagged(
    uintptr_t parent_or_count) {
  UPB_ASSERT(_upb_Arena_IsTaggedPointer(parent_or_count));
  return (upb_ArenaInternal*)parent_or_count;
}

static uintptr_t _upb_Arena_TaggedFromPointer(upb_ArenaInternal* ai) {
  uintptr_t parent_or_count = (uintptr_t)ai;
  UPB_ASSERT(_upb_Arena_IsTaggedPointer(parent_or_count));
  return parent_or_count;
}

static bool _upb_Arena_IsTaggedTail(uintptr_t previous_or_tail) {
  return (previous_or_tail & 1) == 1;
}

static bool _upb_Arena_IsTaggedPrevious(uintptr_t previous_or_tail) {
  return (previous_or_tail & 1) == 0;
}

static upb_ArenaInternal* _upb_Arena_TailFromTagged(
    uintptr_t previous_or_tail) {
  UPB_ASSERT(_upb_Arena_IsTaggedTail(previous_or_tail));
  return (upb_ArenaInternal*)(previous_or_tail ^ 1);
}

static uintptr_t _upb_Arena_TaggedFromTail(upb_ArenaInternal* tail) {
  uintptr_t previous_or_tail = (uintptr_t)tail | 1;
  UPB_ASSERT(_upb_Arena_IsTaggedTail(previous_or_tail));
  return previous_or_tail;
}

static upb_ArenaInternal* _upb_Arena_PreviousFromTagged(
    uintptr_t previous_or_tail) {
  UPB_ASSERT(_upb_Arena_IsTaggedPrevious(previous_or_tail));
  return (upb_ArenaInternal*)previous_or_tail;
}

static uintptr_t _upb_Arena_TaggedFromPrevious(upb_ArenaInternal* ai) {
  uintptr_t previous = (uintptr_t)ai;
  UPB_ASSERT(_upb_Arena_IsTaggedPrevious(previous));
  return previous;
}

static upb_alloc* _upb_ArenaInternal_BlockAlloc(upb_ArenaInternal* ai) {
  return (upb_alloc*)(ai->block_alloc & ~0x1);
}

static uintptr_t _upb_Arena_MakeBlockAlloc(upb_alloc* alloc, bool has_initial) {
  uintptr_t alloc_uint = (uintptr_t)alloc;
  UPB_ASSERT((alloc_uint & 1) == 0);
  return alloc_uint | (has_initial ? 1 : 0);
}

static bool _upb_ArenaInternal_HasInitialBlock(upb_ArenaInternal* ai) {
  return ai->block_alloc & 0x1;
}

#ifdef UPB_TRACING_ENABLED
static void (*_init_arena_trace_handler)(const upb_Arena*, size_t size) = NULL;
static void (*_fuse_arena_trace_handler)(const upb_Arena*,
                                         const upb_Arena*) = NULL;
static void (*_free_arena_trace_handler)(const upb_Arena*) = NULL;

void upb_Arena_SetTraceHandler(
    void (*initArenaTraceHandler)(const upb_Arena*, size_t size),
    void (*fuseArenaTraceHandler)(const upb_Arena*, const upb_Arena*),
    void (*freeArenaTraceHandler)(const upb_Arena*)) {
  _init_arena_trace_handler = initArenaTraceHandler;
  _fuse_arena_trace_handler = fuseArenaTraceHandler;
  _free_arena_trace_handler = freeArenaTraceHandler;
}

void upb_Arena_LogInit(const upb_Arena* arena, size_t size) {
  if (_init_arena_trace_handler) {
    _init_arena_trace_handler(arena, size);
  }
}
void upb_Arena_LogFuse(const upb_Arena* arena1, const upb_Arena* arena2) {
  if (_fuse_arena_trace_handler) {
    _fuse_arena_trace_handler(arena1, arena2);
  }
}
void upb_Arena_LogFree(const upb_Arena* arena) {
  if (_free_arena_trace_handler) {
    _free_arena_trace_handler(arena);
  }
}
#endif  // UPB_TRACING_ENABLED

// If the param a is already the root, provides no memory order of refcount.
// If it has a parent, then acquire memory order is provided for both the root
// and the refcount. Thread safe.
static upb_ArenaRoot _upb_Arena_FindRoot(upb_ArenaInternal* ai) {
  uintptr_t poc = upb_Atomic_Load(&ai->parent_or_count, memory_order_relaxed);
  if (_upb_Arena_IsTaggedRefcount(poc)) {
    // Fast, relaxed path - arenas that have never been fused to a parent only
    // need relaxed memory order, since they're returning themselves and the
    // refcount.
    return (upb_ArenaRoot){.root = ai, .tagged_count = poc};
  }
  // Slow path needs acquire order; reloading is cheaper than a fence on ARM
  // (LDA vs DMB ISH). Even though this is a reread, we know it must be a tagged
  // pointer because if this Arena isn't a root, it can't ever become one.
  poc = upb_Atomic_Load(&ai->parent_or_count, memory_order_acquire);
  do {
    upb_ArenaInternal* next = _upb_Arena_PointerFromTagged(poc);
    UPB_PRIVATE(upb_Xsan_AccessReadOnly)(UPB_XSAN(next));
    UPB_ASSERT(ai != next);
    poc = upb_Atomic_Load(&next->parent_or_count, memory_order_acquire);

    if (_upb_Arena_IsTaggedPointer(poc)) {
      // To keep complexity down, we lazily collapse levels of the tree.  This
      // keeps it flat in the final case, but doesn't cost much incrementally.
      //
      // Path splitting keeps time complexity down, see:
      //   https://en.wikipedia.org/wiki/Disjoint-set_data_structure
      UPB_ASSERT(ai != _upb_Arena_PointerFromTagged(poc));
      upb_Atomic_Store(&ai->parent_or_count, poc, memory_order_release);
    }
    ai = next;
  } while (_upb_Arena_IsTaggedPointer(poc));
  return (upb_ArenaRoot){.root = ai, .tagged_count = poc};
}

uintptr_t upb_Arena_SpaceAllocated(const upb_Arena* arena,
                                   size_t* fused_count) {
  upb_ArenaInternal* ai = upb_Arena_Internal(arena);
  uintptr_t memsize = 0;
  size_t local_fused_count = 0;
  // Our root would get updated by any racing fuses before our target arena
  // became reachable from the root via the linked list; in order to preserve
  // monotonic output (any arena counted by a previous invocation is counted by
  // this one), we instead iterate forwards and backwards so that we only see
  // the results of completed fuses.
  uintptr_t previous_or_tail =
      upb_Atomic_Load(&ai->previous_or_tail, memory_order_acquire);
  while (_upb_Arena_IsTaggedPrevious(previous_or_tail)) {
    upb_ArenaInternal* previous =
        _upb_Arena_PreviousFromTagged(previous_or_tail);
    UPB_ASSERT(previous != ai);
    UPB_PRIVATE(upb_Xsan_AccessReadOnly)(UPB_XSAN(previous));
    // Unfortunate macro behavior; prior to C11 when using nonstandard atomics
    // this returns a void* and can't be used with += without an intermediate
    // conversion to an integer.
    // Relaxed is safe - no subsequent reads depend this one
    uintptr_t allocated =
        upb_Atomic_Load(&previous->space_allocated, memory_order_relaxed);
    memsize += allocated;
    previous_or_tail =
        upb_Atomic_Load(&previous->previous_or_tail, memory_order_acquire);
    local_fused_count++;
  }
  while (ai != NULL) {
    UPB_PRIVATE(upb_Xsan_AccessReadOnly)(UPB_XSAN(ai));
    // Unfortunate macro behavior; prior to C11 when using nonstandard atomics
    // this returns a void* and can't be used with += without an intermediate
    // conversion to an integer.
    // Relaxed is safe - no subsequent reads depend this one
    uintptr_t allocated =
        upb_Atomic_Load(&ai->space_allocated, memory_order_relaxed);
    memsize += allocated;
    ai = upb_Atomic_Load(&ai->next, memory_order_acquire);
    local_fused_count++;
  }

  if (fused_count) *fused_count = local_fused_count;
  return memsize;
}

uint32_t upb_Arena_DebugRefCount(const upb_Arena* a) {
  uintptr_t tagged = _upb_Arena_FindRoot(upb_Arena_Internal(a)).tagged_count;
  return (uint32_t)_upb_Arena_RefCountFromTagged(tagged);
}

#if UPB_ENABLE_REF_CYCLE_CHECKS

bool upb_Arena_HasRefChain(const upb_Arena* from, const upb_Arena* to) {
  upb_ArenaInternal* ai = upb_Arena_Internal(from);
  upb_ArenaInternal* current;

  if (upb_Arena_IsFused(from, to)) return true;

  // 1. Traverse backward to the start of a consistent segment.
  uintptr_t previous_or_tail =
      upb_Atomic_Load(&ai->previous_or_tail, memory_order_acquire);
  while (_upb_Arena_IsTaggedPrevious(previous_or_tail)) {
    ai = _upb_Arena_PreviousFromTagged(previous_or_tail);
    UPB_PRIVATE(upb_Xsan_AccessReadOnly)(UPB_XSAN(ai));
    previous_or_tail =
        upb_Atomic_Load(&ai->previous_or_tail, memory_order_acquire);
  }

  // 2. Traverse forward through all arenas in the fuse group.
  current = ai;
  while (current != NULL) {
    UPB_PRIVATE(upb_Xsan_AccessReadOnly)(UPB_XSAN(current));
    const upb_ArenaRef* ref =
        upb_Atomic_Load(&current->refs, memory_order_acquire);
    while (ref != NULL) {
      if (ref->arena == to || upb_Arena_HasRefChain(ref->arena, to)) {
        return true;
      }
      ref = ref->next_ref;
    }
    current = upb_Atomic_Load(&current->next, memory_order_acquire);
  }
  return false;
}

#endif

// Adds an allocated block to the head of the list.
static void _upb_Arena_AddBlock(upb_Arena* a, void* ptr, size_t offset,
                                size_t block_size) {
  upb_ArenaInternal* ai = upb_Arena_Internal(a);
  upb_MemBlock* block = ptr;

  block->size = block_size;
  UPB_ASSERT(offset >= kUpb_MemblockReserve);
  char* start = UPB_PTR_AT(block, offset, char);
  upb_MemBlock* head = ai->blocks;
  block->next = head;
  ai->blocks = block;
  UPB_PRIVATE(upb_Xsan_Init)(UPB_XSAN(a));
  a->UPB_PRIVATE(ptr) = start;
  a->UPB_PRIVATE(end) = UPB_PTR_AT(block, block_size, char);
  UPB_PRIVATE(upb_Xsan_PoisonRegion)(start, a->UPB_PRIVATE(end) - start);
  UPB_ASSERT(UPB_PRIVATE(_upb_ArenaHas)(a) >= block_size - offset);
}

// Fulfills the allocation request by allocating a new block. Returns NULL on
// allocation failure.
void* UPB_PRIVATE(_upb_Arena_SlowMalloc)(upb_Arena* a, size_t size) {
  upb_ArenaInternal* ai = upb_Arena_Internal(a);
  if (!ai->block_alloc) return NULL;
  size_t last_size = 128;
  size_t current_free = 0;
  upb_MemBlock* last_block = ai->blocks;
  if (last_block) {
    last_size = last_block->size;
    current_free = a->UPB_PRIVATE(end) - a->UPB_PRIVATE(ptr);
  }

  // Relaxed order is safe here as we don't need any ordering with the setter.
  size_t max_block_size =
      upb_Atomic_Load(&g_max_block_size, memory_order_relaxed);

  // Don't naturally grow beyond the max block size.
  size_t target_size = UPB_MIN(last_size * 2, max_block_size);
  size_t future_free = UPB_MAX(size, target_size - kUpb_MemblockReserve) - size;
  // We want to preserve exponential growth in block size without wasting too
  // much unused space at the end of blocks. Once the head of our blocks list is
  // large enough to always trigger a max-sized block for all subsequent
  // allocations, allocate blocks that would net reduce free space behind it.
  if (last_block && current_free > future_free &&
      target_size < max_block_size) {
    last_size = ai->size_hint;
    // Recalculate sizes with possibly larger last_size
    target_size = UPB_MIN(last_size * 2, max_block_size);
    future_free = UPB_MAX(size, target_size - kUpb_MemblockReserve) - size;
  }
  bool insert_after_head = false;
  // Only insert after head if an allocated block is present; we don't want to
  // continue allocating out of the initial block because we'll have no way of
  // restoring the size of our allocated block if we add another.
  if (last_block && current_free >= future_free) {
    // If we're still going to net reduce free space with this new block, then
    // only allocate the precise size requested and keep the current last block
    // as the active block for future allocations.
    insert_after_head = true;
    target_size = size + kUpb_MemblockReserve;
    // Add something to our previous size each time, so that eventually we
    // will reach the max block size. Allocations larger than the max block size
    // will always get their own backing allocation, so don't include them.
    if (target_size <= max_block_size) {
      ai->size_hint = UPB_MIN(ai->size_hint + (size >> 1), max_block_size >> 1);
    }
  }
  // We may need to exceed the max block size if the user requested a large
  // allocation.
  size_t block_size = UPB_MAX(kUpb_MemblockReserve + size, target_size);
  upb_alloc* block_alloc = _upb_ArenaInternal_BlockAlloc(ai);
  upb_SizedPtr alloc_result = upb_SizeReturningMalloc(block_alloc, block_size);

  if (!alloc_result.p) return NULL;

  upb_MemBlock* block = alloc_result.p;
  size_t actual_block_size = alloc_result.n;

  // Atomic add not required here, as threads won't race allocating blocks, plus
  // atomic fetch-add is slower than load/add/store on arm devices compiled
  // targetting pre-v8.1. Relaxed order is safe as nothing depends on order of
  // size allocated.

  uintptr_t old_space_allocated =
      upb_Atomic_Load(&ai->space_allocated, memory_order_relaxed);
  upb_Atomic_Store(&ai->space_allocated,
                   old_space_allocated + actual_block_size,
                   memory_order_relaxed);
  if (UPB_UNLIKELY(insert_after_head)) {
    upb_ArenaInternal* ai = upb_Arena_Internal(a);
    block->size = actual_block_size;
    upb_MemBlock* head = ai->blocks;
    block->next = head->next;
    head->next = block;

    char* allocated = UPB_PTR_AT(block, kUpb_MemblockReserve, char);
    UPB_PRIVATE(upb_Xsan_PoisonRegion)(allocated + size,
                                       UPB_PRIVATE(kUpb_Asan_GuardSize));
    return allocated;
  } else {
    ai->size_hint = actual_block_size;
    _upb_Arena_AddBlock(a, block, kUpb_MemblockReserve, actual_block_size);
    UPB_ASSERT(UPB_PRIVATE(_upb_ArenaHas)(a) >= size);
    return upb_Arena_Malloc(a, size - UPB_PRIVATE(kUpb_Asan_GuardSize));
  }
}

static upb_Arena* _upb_Arena_InitSlow(upb_alloc* alloc, size_t first_size) {
  const size_t first_block_overhead =
      UPB_ALIGN_MALLOC(kUpb_MemblockReserve + sizeof(upb_ArenaState));
  upb_ArenaState* a;

  // We need to malloc the initial block.

  size_t block_size =
      first_block_overhead + UPB_MAX(256, UPB_ALIGN_MALLOC(first_size) +
                                              UPB_PRIVATE(kUpb_Asan_GuardSize));
  upb_SizedPtr alloc_result;
  if (!alloc ||
      !(alloc_result = upb_SizeReturningMalloc(alloc, block_size)).p) {
    return NULL;
  }
  char* mem = alloc_result.p;
  size_t actual_block_size = alloc_result.n;

  a = UPB_PTR_AT(mem, kUpb_MemblockReserve, upb_ArenaState);
  a->body.block_alloc = _upb_Arena_MakeBlockAlloc(alloc, 0);
  a->body.size_hint = actual_block_size;
  upb_Atomic_Init(&a->body.parent_or_count, _upb_Arena_TaggedFromRefcount(1));
  upb_Atomic_Init(&a->body.next, NULL);
  upb_Atomic_Init(&a->body.previous_or_tail,
                  _upb_Arena_TaggedFromTail(&a->body));
  upb_Atomic_Init(&a->body.space_allocated, actual_block_size);
  a->body.blocks = NULL;
#ifndef NDEBUG
  a->body.refs = NULL;
#endif
  a->body.upb_alloc_cleanup = NULL;
  UPB_PRIVATE(upb_Xsan_Init)(UPB_XSAN(&a->body));

  _upb_Arena_AddBlock(&a->head, mem, first_block_overhead, actual_block_size);

  return &a->head;
}

upb_Arena* upb_Arena_Init(void* mem, size_t n, upb_alloc* alloc) {
  UPB_STATIC_ASSERT(
      sizeof(void*) * UPB_ARENA_SIZE_HACK >= sizeof(upb_ArenaState),
      "Need to update UPB_ARENA_SIZE_HACK");
  upb_ArenaState* a;

  if (mem) {
    /* Align initial pointer up so that we return properly-aligned pointers. */
    void* aligned = (void*)UPB_ALIGN_MALLOC((uintptr_t)mem);
    size_t delta = (uintptr_t)aligned - (uintptr_t)mem;
    n = delta <= n ? n - delta : 0;
    mem = aligned;
  }
  if (UPB_UNLIKELY(n < sizeof(upb_ArenaState) || !mem)) {
    upb_Arena* ret = _upb_Arena_InitSlow(alloc, mem ? 0 : n);
#ifdef UPB_TRACING_ENABLED
    upb_Arena_LogInit(ret, n);
#endif
    return ret;
  }

  a = mem;

  upb_Atomic_Init(&a->body.parent_or_count, _upb_Arena_TaggedFromRefcount(1));
  upb_Atomic_Init(&a->body.next, NULL);
  upb_Atomic_Init(&a->body.previous_or_tail,
                  _upb_Arena_TaggedFromTail(&a->body));
  upb_Atomic_Init(&a->body.space_allocated, 0);
  a->body.blocks = NULL;
#ifndef NDEBUG
  a->body.refs = NULL;
#endif
  a->body.size_hint = 128;
  a->body.upb_alloc_cleanup = NULL;
  a->body.block_alloc = _upb_Arena_MakeBlockAlloc(alloc, 1);
  a->head.UPB_PRIVATE(ptr) = (void*)UPB_ALIGN_MALLOC((uintptr_t)(a + 1));
  a->head.UPB_PRIVATE(end) = UPB_PTR_AT(mem, n, char);
  UPB_PRIVATE(upb_Xsan_Init)(UPB_XSAN(&a->body));
#ifdef UPB_TRACING_ENABLED
  upb_Arena_LogInit(&a->head, n);
#endif
  return &a->head;
}

static void _upb_Arena_DoFree(upb_ArenaInternal* ai) {
  UPB_ASSERT(_upb_Arena_RefCountFromTagged(ai->parent_or_count) == 1);
  while (ai != NULL) {
    UPB_PRIVATE(upb_Xsan_AccessReadWrite)(UPB_XSAN(ai));
    // Load first since arena itself is likely from one of its blocks. Relaxed
    // order is safe because fused arena ordering is provided by the reference
    // count, and fuse is not permitted to race with the final decrement.
    upb_ArenaInternal* next_arena =
        (upb_ArenaInternal*)upb_Atomic_Load(&ai->next, memory_order_relaxed);
    // Freeing may have memory barriers that confuse tsan, so assert immediately
    // after load here
    if (next_arena) {
      UPB_PRIVATE(upb_Xsan_AccessReadWrite)(UPB_XSAN(next_arena));
    }
    upb_alloc* block_alloc = _upb_ArenaInternal_BlockAlloc(ai);
    upb_MemBlock* block = ai->blocks;
    upb_AllocCleanupFunc* alloc_cleanup = *ai->upb_alloc_cleanup;
    while (block != NULL) {
      // Load first since we are deleting block.
      upb_MemBlock* next_block = block->next;
      if (block->size == 0) {
        // If the block is an arena ref, then we need to release our ref on the
        // referenced arena.
        upb_ArenaRef* ref = (upb_ArenaRef*)block;
        upb_Arena_DecRefFor((upb_Arena*)ref->arena, ai);
      } else {
        upb_free_sized(block_alloc, block, block->size);
      }
      block = next_block;
    }
    if (alloc_cleanup != NULL) {
      alloc_cleanup(block_alloc);
    }
    ai = next_arena;
  }
}

void upb_Arena_Free(upb_Arena* a) {
  upb_ArenaInternal* ai = upb_Arena_Internal(a);
  // Cannot be replaced with _upb_Arena_FindRoot, as that provides only a
  // relaxed read of the refcount if ai is already the root.
  uintptr_t poc = upb_Atomic_Load(&ai->parent_or_count, memory_order_acquire);
retry:
  while (_upb_Arena_IsTaggedPointer(poc)) {
    ai = _upb_Arena_PointerFromTagged(poc);
    UPB_PRIVATE(upb_Xsan_AccessReadOnly)(UPB_XSAN(ai));
    poc = upb_Atomic_Load(&ai->parent_or_count, memory_order_acquire);
  }

  // compare_exchange or fetch_sub are RMW operations, which are more
  // expensive then direct loads.  As an optimization, we only do RMW ops
  // when we need to update things for other threads to see.
  if (poc == _upb_Arena_TaggedFromRefcount(1)) {
#ifdef UPB_TRACING_ENABLED
    upb_Arena_LogFree(a);
#endif
    _upb_Arena_DoFree(ai);
    return;
  }

  if (upb_Atomic_CompareExchangeWeak(
          &ai->parent_or_count, &poc,
          _upb_Arena_TaggedFromRefcount(_upb_Arena_RefCountFromTagged(poc) - 1),
          memory_order_release, memory_order_acquire)) {
    // We were >1 and we decremented it successfully, so we are done.
    return;
  }

  // We failed our update, so someone has done something, retry the whole
  // process, but the failed exchange reloaded `poc` for us.
  goto retry;
}

// Logically performs the following operation, in a way that is safe against
// racing fuses:
//   ret = TAIL(parent)
//   ret->next = child
//   return ret
//
// The caller is therefore guaranteed that ret->next == child.
static upb_ArenaInternal* _upb_Arena_LinkForward(
    upb_ArenaInternal* const parent, upb_ArenaInternal* child) {
  UPB_PRIVATE(upb_Xsan_AccessReadOnly)(UPB_XSAN(parent));
  uintptr_t parent_previous_or_tail =
      upb_Atomic_Load(&parent->previous_or_tail, memory_order_acquire);

  // Optimization: use parent->previous_or_tail to skip to TAIL(parent) in O(1)
  // time when possible. This is the common case because we just fused into
  // parent, suggesting that it should be a root with a cached tail.
  //
  // However, if there was a racing fuse, parent may no longer be a root, in
  // which case we need to walk the entire list to find the tail. The tail
  // pointer is also not guaranteed to be the true tail, so even when the
  // optimization is taken, we still need to walk list nodes to find the true
  // tail.
  upb_ArenaInternal* parent_tail =
      _upb_Arena_IsTaggedTail(parent_previous_or_tail)
          ? _upb_Arena_TailFromTagged(parent_previous_or_tail)
          : parent;

  UPB_PRIVATE(upb_Xsan_AccessReadOnly)(UPB_XSAN(parent_tail));
  upb_ArenaInternal* parent_tail_next =
      upb_Atomic_Load(&parent_tail->next, memory_order_acquire);

  do {
    // Walk the list to find the true tail (a node with next == NULL).
    while (parent_tail_next != NULL) {
      parent_tail = parent_tail_next;
      UPB_PRIVATE(upb_Xsan_AccessReadOnly)(UPB_XSAN(parent_tail));
      parent_tail_next =
          upb_Atomic_Load(&parent_tail->next, memory_order_acquire);
    }
  } while (!upb_Atomic_CompareExchangeWeak(  // Replace a NULL next with child.
      &parent_tail->next, &parent_tail_next, child, memory_order_release,
      memory_order_acquire));

  return parent_tail;
}

// Updates parent->previous_or_tail = child->previous_or_tail in hopes that the
// latter represents the true tail of the newly-combined list.
//
// This is a best-effort operation that may set the tail to a stale value, and
// may fail to update the tail at all.
void _upb_Arena_UpdateParentTail(upb_ArenaInternal* parent,
                                 upb_ArenaInternal* child) {
  // We are guaranteed that child->previous_or_tail is tagged, because we have
  // just transitioned child from root -> non-root, which is an exclusive
  // operation that can only happen once. So we are the exclusive updater of
  // child->previous_or_tail that can transition it from tagged to untagged.
  //
  // However, we are not guaranteed that child->previous_or_tail is the true
  // tail.  A racing fuse may have appended to child's list but not yet updated
  // child->previous_or_tail.
  uintptr_t child_previous_or_tail =
      upb_Atomic_Load(&child->previous_or_tail, memory_order_acquire);
  upb_ArenaInternal* new_parent_tail =
      _upb_Arena_TailFromTagged(child_previous_or_tail);
  UPB_PRIVATE(upb_Xsan_AccessReadOnly)(UPB_XSAN(new_parent_tail));

  // If another thread fused with parent, such that it is no longer a root,
  // don't overwrite their previous pointer with our tail. Relaxed order is fine
  // here as we only inspect the tag bit.
  uintptr_t parent_previous_or_tail =
      upb_Atomic_Load(&parent->previous_or_tail, memory_order_relaxed);
  if (_upb_Arena_IsTaggedTail(parent_previous_or_tail)) {
    upb_Atomic_CompareExchangeStrong(
        &parent->previous_or_tail, &parent_previous_or_tail,
        _upb_Arena_TaggedFromTail(new_parent_tail), memory_order_release,
        memory_order_relaxed);
  }
}

static void _upb_Arena_LinkBackward(upb_ArenaInternal* child,
                                    upb_ArenaInternal* old_parent_tail) {
  // Link child to parent going backwards, for SpaceAllocated.  This transitions
  // child->previous_or_tail from tail (tagged) to previous (untagged), after
  // which its value is immutable.
  //
  // - We are guaranteed that no other threads are also attempting to perform
  //   this transition (tail -> previous), because we just updated
  //   old_parent_tail->next from NULL to non-NULL, an exclusive operation that
  //   can only happen once.
  //
  // - _upb_Arena_UpdateParentTail() uses CAS to ensure that it
  //    does not perform the reverse transition (previous -> tail).
  //
  // - We are guaranteed that old_parent_tail is the correct "previous" pointer,
  //   even in the presence of racing fuses that are adding more nodes to the
  //   list, because _upb_Arena_LinkForward() guarantees that:
  //       old_parent_tail->next == child.
  upb_Atomic_Store(&child->previous_or_tail,
                   _upb_Arena_TaggedFromPrevious(old_parent_tail),
                   memory_order_release);
}

static void _upb_Arena_DoFuseArenaLists(upb_ArenaInternal* const parent,
                                        upb_ArenaInternal* child) {
  upb_ArenaInternal* old_parent_tail = _upb_Arena_LinkForward(parent, child);
  _upb_Arena_UpdateParentTail(parent, child);
  _upb_Arena_LinkBackward(child, old_parent_tail);
}

void upb_Arena_SetAllocCleanup(upb_Arena* a, upb_AllocCleanupFunc* func) {
  UPB_PRIVATE(upb_Xsan_AccessReadWrite)(UPB_XSAN(a));
  upb_ArenaInternal* ai = upb_Arena_Internal(a);
  UPB_ASSERT(ai->upb_alloc_cleanup == NULL);
  ai->upb_alloc_cleanup = func;
}

// Thread safe.
static upb_ArenaInternal* _upb_Arena_DoFuse(upb_ArenaInternal** ai1,
                                            upb_ArenaInternal** ai2,
                                            uintptr_t* ref_delta) {
  // `parent_or_count` has two distinct modes
  // -  parent pointer mode
  // -  refcount mode
  //
  // In parent pointer mode, it may change what pointer it refers to in the
  // tree, but it will always approach a root.  Any operation that walks the
  // tree to the root may collapse levels of the tree concurrently.
  upb_ArenaRoot r1 = _upb_Arena_FindRoot(*ai1);
  upb_ArenaRoot r2 = _upb_Arena_FindRoot(*ai2);

  if (r1.root == r2.root) return r1.root;  // Already fused.

  *ai1 = r1.root;
  *ai2 = r2.root;

  // Avoid cycles by always fusing into the root with the lower address.
  if ((uintptr_t)r1.root > (uintptr_t)r2.root) {
    upb_ArenaRoot tmp = r1;
    r1 = r2;
    r2 = tmp;
  }

  // The moment we install `r1` as the parent for `r2` all racing frees may
  // immediately begin decrementing `r1`'s refcount (including pending
  // increments to that refcount and their frees!).  We need to add `r2`'s refs
  // now, so that `r1` can withstand any unrefs that come from r2.
  //
  // Note that while it is possible for `r2`'s refcount to increase
  // asynchronously, we will not actually do the reparenting operation below
  // unless `r2`'s refcount is unchanged from when we read it.
  //
  // Note that we may have done this previously, either to this node or a
  // different node, during a previous and failed DoFuse() attempt. But we will
  // not lose track of these refs because we always add them to our overall
  // delta.
  uintptr_t r2_untagged_count = r2.tagged_count & ~1;
  uintptr_t with_r2_refs = r1.tagged_count + r2_untagged_count;
  if (!upb_Atomic_CompareExchangeStrong(
          &r1.root->parent_or_count, &r1.tagged_count, with_r2_refs,
          memory_order_release, memory_order_acquire)) {
    return NULL;
  }

  // Perform the actual fuse by removing the refs from `r2` and swapping in the
  // parent pointer.
  if (!upb_Atomic_CompareExchangeStrong(
          &r2.root->parent_or_count, &r2.tagged_count,
          _upb_Arena_TaggedFromPointer(r1.root), memory_order_release,
          memory_order_acquire)) {
    // We'll need to remove the excess refs we added to r1 previously.
    *ref_delta += r2_untagged_count;
    return NULL;
  }

  // Now that the fuse has been performed (and can no longer fail) we need to
  // append `r2` to `r1`'s linked list.
  _upb_Arena_DoFuseArenaLists(r1.root, r2.root);
  return r1.root;
}

// Thread safe.
static bool _upb_Arena_FixupRefs(upb_ArenaInternal* new_root,
                                 uintptr_t ref_delta) {
  if (ref_delta == 0) return true;  // No fixup required.
  // Relaxed order is safe here as if the value is a pointer, we don't deref it
  // or publish it anywhere else. The refcount does provide memory order
  // between allocations on arenas and the eventual free and thus normally
  // requires acquire/release; but in this case any edges provided by the refs
  // we are cleaning up were already provided by the fuse operation itself. It's
  // not valid for a decrement that could cause the overall fused arena to reach
  // a zero refcount to race with this function, as that could result in a
  // use-after-free anyway.
  uintptr_t poc =
      upb_Atomic_Load(&new_root->parent_or_count, memory_order_relaxed);
  if (_upb_Arena_IsTaggedPointer(poc)) return false;
  uintptr_t with_refs = poc - ref_delta;
  UPB_ASSERT(!_upb_Arena_IsTaggedPointer(with_refs));
  // Relaxed order on success is safe here, for the same reasons as the relaxed
  // read above. Relaxed order is safe on failure because the updated value is
  // stored in a local variable which goes immediately out of scope; the retry
  // loop will reread what it needs with proper memory order.
  return upb_Atomic_CompareExchangeStrong(&new_root->parent_or_count, &poc,
                                          with_refs, memory_order_relaxed,
                                          memory_order_relaxed);
}

bool upb_Arena_Fuse(const upb_Arena* a1, const upb_Arena* a2) {
  if (a1 == a2) return true;  // trivial fuse

#ifdef UPB_TRACING_ENABLED
  upb_Arena_LogFuse(a1, a2);
#endif

  upb_ArenaInternal* ai1 = upb_Arena_Internal(a1);
  upb_ArenaInternal* ai2 = upb_Arena_Internal(a2);

  // Do not fuse initial blocks since we cannot lifetime extend them.
  // Any other fuse scenario is allowed.
  if (_upb_ArenaInternal_HasInitialBlock(ai1) ||
      _upb_ArenaInternal_HasInitialBlock(ai2)) {
    return false;
  }

  // The number of refs we ultimately need to transfer to the new root.
  uintptr_t ref_delta = 0;
  while (true) {
    upb_ArenaInternal* new_root = _upb_Arena_DoFuse(&ai1, &ai2, &ref_delta);
    if (new_root != NULL && _upb_Arena_FixupRefs(new_root, ref_delta)) {
#if UPB_ENABLE_REF_CYCLE_CHECKS
      UPB_ASSERT(!upb_Arena_HasRefChain(a1, a2));
#endif
      return true;
    }
  }
}

bool upb_Arena_IsFused(const upb_Arena* a, const upb_Arena* b) {
  if (a == b) return true;  // trivial fuse
  upb_ArenaInternal* ra = _upb_Arena_FindRoot(upb_Arena_Internal(a)).root;
  upb_ArenaInternal* rb = upb_Arena_Internal(b);
  while (true) {
    rb = _upb_Arena_FindRoot(rb).root;
    if (ra == rb) return true;
    upb_ArenaInternal* tmp = _upb_Arena_FindRoot(ra).root;
    if (ra == tmp) return false;
    // a's root changed since we last checked.  Retry.
    ra = tmp;
  }
}

bool upb_Arena_IncRefFor(const upb_Arena* a, const void* owner) {
  upb_ArenaInternal* ai = upb_Arena_Internal(a);
  if (_upb_ArenaInternal_HasInitialBlock(ai)) return false;
  upb_ArenaRoot r;
  r.root = ai;

retry:
  r = _upb_Arena_FindRoot(r.root);
  if (upb_Atomic_CompareExchangeWeak(
          &r.root->parent_or_count, &r.tagged_count,
          _upb_Arena_TaggedFromRefcount(
              _upb_Arena_RefCountFromTagged(r.tagged_count) + 1),
          // Relaxed order is safe on success, incrementing the refcount
          // need not perform any synchronization with the eventual free of the
          // arena - that's provided by decrements.
          memory_order_relaxed,
          // Relaxed order is safe on failure as r.tagged_count is immediately
          // overwritten by retrying the find root operation.
          memory_order_relaxed)) {
    // We incremented it successfully, so we are done.
    return true;
  }
  // We failed update due to parent switching on the arena.
  goto retry;
}

void upb_Arena_DecRefFor(const upb_Arena* a, const void* owner) {
  upb_Arena_Free((upb_Arena*)a);
}

bool upb_Arena_RefArena(upb_Arena* from, const upb_Arena* to) {
  UPB_ASSERT(!upb_Arena_IsFused(from, to));
  if (_upb_ArenaInternal_HasInitialBlock(upb_Arena_Internal(to))) {
    // We can't increment a ref to `to`, so return early.
    return false;
  }

  upb_ArenaInternal* ai = upb_Arena_Internal(from);
  upb_ArenaRef* ref = upb_Arena_Malloc(from, kUpb_ArenaRefReserve);

  if (!ref) {
    return false;
  }

  // When 'from' is freed, a ref on 'to' will be released.
  // Intentionally ignore return value, since we already check up above if this
  // call will succeed.
  bool result = upb_Arena_IncRefFor(to, from);
  UPB_ASSERT(result);

  // When we add a reference from `from` to `to`, we need to keep track of the
  // ref in the `from` arena's linked list of refs. This allows us to
  // walk all refs for `from` when `from` is freed, and thus allows us to
  // decrement the refcount on `to` when `from` is freed.
  ref->prefix.next = ai->blocks;
  ref->prefix.size = 0;
  ref->arena = to;
  ai->blocks = (upb_MemBlock*)ref;

#ifndef NDEBUG
  // Add to the dedicated list of refs.
  // This function is not thread-safe from `from`, so a simple load/store is
  // sufficient.
  ref->next_ref = upb_Atomic_Load(&ai->refs, memory_order_relaxed);
  upb_Atomic_Store(&ai->refs, ref, memory_order_release);
#endif

#if UPB_ENABLE_REF_CYCLE_CHECKS
  UPB_ASSERT(!upb_Arena_HasRefChain(to, from));  // Forbid cycles.
#endif

  return true;
}

#ifndef NDEBUG
bool upb_Arena_HasRef(const upb_Arena* from, const upb_Arena* to) {
  const upb_ArenaInternal* ai = upb_Arena_Internal(from);
  const upb_ArenaRef* ref = upb_Atomic_Load(&ai->refs, memory_order_acquire);
  while (ref != NULL) {
    if (upb_Arena_IsFused(ref->arena, to)) {
      return true;
    }
    ref = ref->next_ref;
  }
  return false;
}
#endif

upb_alloc* upb_Arena_GetUpbAlloc(upb_Arena* a) {
  UPB_PRIVATE(upb_Xsan_AccessReadOnly)(UPB_XSAN(a));
  upb_ArenaInternal* ai = upb_Arena_Internal(a);
  return _upb_ArenaInternal_BlockAlloc(ai);
}

void UPB_PRIVATE(_upb_Arena_SwapIn)(upb_Arena* des, const upb_Arena* src) {
  memcpy(des, src, offsetof(upb_ArenaState, body.space_allocated));
  upb_ArenaInternal* desi = upb_Arena_Internal(des);
  upb_ArenaInternal* srci = upb_Arena_Internal(src);
  uintptr_t new_space_allocated =
      upb_Atomic_Load(&srci->space_allocated, memory_order_relaxed);
  upb_Atomic_Store(&desi->space_allocated, new_space_allocated,
                   memory_order_relaxed);
}

void UPB_PRIVATE(_upb_Arena_SwapOut)(upb_Arena* des, const upb_Arena* src) {
  UPB_PRIVATE(_upb_Arena_SwapIn)(des, src);
}

bool _upb_Arena_WasLastAlloc(struct upb_Arena* a, void* ptr, size_t oldsize) {
  upb_ArenaInternal* ai = upb_Arena_Internal(a);
  upb_MemBlock* block = ai->blocks;
  if (block == NULL) return false;
  // Skip any arena refs.
  while (block != NULL && block->size == 0) {
    block = block->next;
  }
  if (block == NULL) return false;
  block = block->next;
  if (block == NULL) return false;
  char* start = UPB_PTR_AT(block, kUpb_MemblockReserve, char);
  return UPB_PRIVATE(upb_Xsan_PtrEq)(ptr, start) &&
         UPB_PRIVATE(_upb_Arena_AllocSpan)(oldsize) ==
             block->size - kUpb_MemblockReserve;
}


#include <stddef.h>
#include <stdint.h>


// Must be last.


#ifdef __cplusplus
extern "C" {
#endif

bool upb_Message_IsEmpty(const upb_Message* msg, const upb_MiniTable* m) {
  if (upb_Message_ExtensionCount(msg)) return false;

  const upb_MiniTableField* f;
  upb_MessageValue v;
  size_t iter = kUpb_BaseField_Begin;
  return !UPB_PRIVATE(_upb_Message_NextBaseField)(msg, m, &f, &v, &iter);
}

static bool _upb_Array_IsEqual(const upb_Array* arr1, const upb_Array* arr2,
                               upb_CType ctype, const upb_MiniTable* m,
                               int options) {
  // Check for trivial equality.
  if (arr1 == arr2) return true;

  // Must have identical element counts.
  const size_t size1 = arr1 ? upb_Array_Size(arr1) : 0;
  const size_t size2 = arr2 ? upb_Array_Size(arr2) : 0;
  if (size1 != size2) return false;

  for (size_t i = 0; i < size1; i++) {
    const upb_MessageValue val1 = upb_Array_Get(arr1, i);
    const upb_MessageValue val2 = upb_Array_Get(arr2, i);

    if (!upb_MessageValue_IsEqual(val1, val2, ctype, m, options)) return false;
  }

  return true;
}

static bool _upb_Map_IsEqual(const upb_Map* map1, const upb_Map* map2,
                             const upb_MiniTable* m, int options) {
  // Check for trivial equality.
  if (map1 == map2) return true;

  // Must have identical element counts.
  size_t size1 = map1 ? upb_Map_Size(map1) : 0;
  size_t size2 = map2 ? upb_Map_Size(map2) : 0;
  if (size1 != size2) return false;

  const upb_MiniTableField* f = upb_MiniTable_MapValue(m);
  const upb_MiniTable* m2_value = upb_MiniTable_SubMessage(m, f);
  const upb_CType ctype = upb_MiniTableField_CType(f);

  upb_MessageValue key, val1, val2;
  size_t iter = kUpb_Map_Begin;
  while (upb_Map_Next(map1, &key, &val1, &iter)) {
    if (!upb_Map_Get(map2, key, &val2)) return false;
    if (!upb_MessageValue_IsEqual(val1, val2, ctype, m2_value, options))
      return false;
  }

  return true;
}

static bool _upb_Message_BaseFieldsAreEqual(const upb_Message* msg1,
                                            const upb_Message* msg2,
                                            const upb_MiniTable* m,
                                            int options) {
  // Iterate over all base fields for each message.
  // The order will always match if the messages are equal.
  size_t iter1 = kUpb_BaseField_Begin;
  size_t iter2 = kUpb_BaseField_Begin;

  for (;;) {
    const upb_MiniTableField *f1, *f2;
    upb_MessageValue val1, val2;

    const bool got1 =
        UPB_PRIVATE(_upb_Message_NextBaseField)(msg1, m, &f1, &val1, &iter1);
    const bool got2 =
        UPB_PRIVATE(_upb_Message_NextBaseField)(msg2, m, &f2, &val2, &iter2);

    if (got1 != got2) return false;  // Must have identical field counts.
    if (!got1) return true;          // Loop termination condition.
    if (f1 != f2) return false;      // Must have identical fields set.

    const upb_MiniTable* subm = upb_MiniTable_SubMessage(m, f1);
    const upb_CType ctype = upb_MiniTableField_CType(f1);

    bool eq;
    switch (UPB_PRIVATE(_upb_MiniTableField_Mode)(f1)) {
      case kUpb_FieldMode_Array:
        eq = _upb_Array_IsEqual(val1.array_val, val2.array_val, ctype, subm,
                                options);
        break;
      case kUpb_FieldMode_Map:
        eq = _upb_Map_IsEqual(val1.map_val, val2.map_val, subm, options);
        break;
      case kUpb_FieldMode_Scalar:
        eq = upb_MessageValue_IsEqual(val1, val2, ctype, subm, options);
        break;
    }
    if (!eq) return false;
  }
}

static bool _upb_Message_ExtensionsAreEqual(const upb_Message* msg1,
                                            const upb_Message* msg2,
                                            const upb_MiniTable* m,
                                            int options) {
  const upb_MiniTableExtension* e;
  upb_MessageValue val1;

  // Iterate over all extensions for msg1, and search msg2 for each extension.
  size_t count1 = 0;
  size_t iter1 = kUpb_Message_ExtensionBegin;
  while (upb_Message_NextExtension(msg1, &e, &val1, &iter1)) {
    const upb_Extension* ext2 = UPB_PRIVATE(_upb_Message_Getext)(msg2, e);
    if (!ext2) return false;

    count1++;

    const upb_MessageValue val2 = ext2->data;
    const upb_MiniTableField* f = &e->UPB_PRIVATE(field);
    const upb_MiniTable* subm = upb_MiniTableField_IsSubMessage(f)
                                    ? upb_MiniTableExtension_GetSubMessage(e)
                                    : NULL;
    const upb_CType ctype = upb_MiniTableField_CType(f);

    bool eq;
    switch (UPB_PRIVATE(_upb_MiniTableField_Mode)(f)) {
      case kUpb_FieldMode_Array:
        eq = _upb_Array_IsEqual(val1.array_val, val2.array_val, ctype, subm,
                                options);
        break;
      case kUpb_FieldMode_Map:
        UPB_UNREACHABLE();  // Maps cannot be extensions.
        break;
      case kUpb_FieldMode_Scalar: {
        eq = upb_MessageValue_IsEqual(val1, val2, ctype, subm, options);
        break;
      }
    }
    if (!eq) return false;
  }

  // Must have identical extension counts (this catches the case where msg2
  // has extensions that msg1 doesn't).
  if (count1 != upb_Message_ExtensionCount(msg2)) return false;

  return true;
}

bool upb_Message_IsEqual(const upb_Message* msg1, const upb_Message* msg2,
                         const upb_MiniTable* m, int options) {
  if (UPB_UNLIKELY(msg1 == msg2)) return true;

  if (!_upb_Message_BaseFieldsAreEqual(msg1, msg2, m, options)) return false;
  if (!_upb_Message_ExtensionsAreEqual(msg1, msg2, m, options)) return false;

  if (!(options & kUpb_CompareOption_IncludeUnknownFields)) return true;

  // The wire encoder enforces a maximum depth of 100 so we match that here.
  return UPB_PRIVATE(_upb_Message_UnknownFieldsAreEqual)(msg1, msg2, 100) ==
         kUpb_UnknownCompareResult_Equal;
}


#include <stddef.h>
#include <stdint.h>


// Must be last.

bool upb_Message_NextExtensionReverse(const upb_Message* msg,
                                      const upb_MiniTableExtension** result,
                                      uintptr_t* iter) {
  upb_MessageValue val;
  return UPB_PRIVATE(_upb_Message_NextExtensionReverse)(msg, result, &val,
                                                        iter);
}

const upb_MiniTableExtension* upb_Message_FindExtensionByNumber(
    const upb_Message* msg, uint32_t field_number) {
  uintptr_t iter = kUpb_Message_ExtensionBegin;
  const upb_MiniTableExtension* result;
  while (upb_Message_NextExtensionReverse(msg, &result, &iter)) {
    if (upb_MiniTableExtension_Number(result) == field_number) return result;
  }
  return NULL;
}


#include <stdint.h>
#include <string.h>


// Must be last.

upb_Array* upb_Array_New(upb_Arena* a, upb_CType type) {
  const int lg2 = UPB_PRIVATE(_upb_CType_SizeLg2)(type);
  return UPB_PRIVATE(_upb_Array_New)(a, 4, lg2);
}

upb_MessageValue upb_Array_Get(const upb_Array* arr, size_t i) {
  UPB_ASSERT(i < upb_Array_Size(arr));
  upb_MessageValue ret;
  const char* data = upb_Array_DataPtr(arr);
  const int lg2 = UPB_PRIVATE(_upb_Array_ElemSizeLg2)(arr);
  memcpy(&ret, data + (i << lg2), 1 << lg2);
  return ret;
}

upb_Message* upb_Array_GetMutable(upb_Array* arr, size_t i) {
  UPB_ASSERT(i < upb_Array_Size(arr));
  size_t elem_size = sizeof(upb_Message*);
  UPB_ASSERT(elem_size == (1 << UPB_PRIVATE(_upb_Array_ElemSizeLg2)(arr)));
  char* data = upb_Array_MutableDataPtr(arr);
  upb_Message* ret;
  memcpy(&ret, data + (i * elem_size), elem_size);
  UPB_ASSERT(!upb_Message_IsFrozen(ret));
  return ret;
}

void upb_Array_Set(upb_Array* arr, size_t i, upb_MessageValue val) {
  UPB_ASSERT(!upb_Array_IsFrozen(arr));
  UPB_ASSERT(i < upb_Array_Size(arr));
  char* data = upb_Array_MutableDataPtr(arr);
  const int lg2 = UPB_PRIVATE(_upb_Array_ElemSizeLg2)(arr);
  memcpy(data + (i << lg2), &val, 1 << lg2);
}

bool upb_Array_Append(upb_Array* arr, upb_MessageValue val, upb_Arena* arena) {
  UPB_ASSERT(!upb_Array_IsFrozen(arr));
  UPB_ASSERT(arena);
  if (!UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
          arr, arr->UPB_PRIVATE(size) + 1, arena)) {
    return false;
  }
  upb_Array_Set(arr, arr->UPB_PRIVATE(size) - 1, val);
  return true;
}

void upb_Array_Move(upb_Array* arr, size_t dst_idx, size_t src_idx,
                    size_t count) {
  UPB_ASSERT(!upb_Array_IsFrozen(arr));
  const int lg2 = UPB_PRIVATE(_upb_Array_ElemSizeLg2)(arr);
  char* data = upb_Array_MutableDataPtr(arr);
  memmove(&data[dst_idx << lg2], &data[src_idx << lg2], count << lg2);
}

bool upb_Array_Insert(upb_Array* arr, size_t i, size_t count,
                      upb_Arena* arena) {
  UPB_ASSERT(!upb_Array_IsFrozen(arr));
  UPB_ASSERT(arena);
  UPB_ASSERT(i <= arr->UPB_PRIVATE(size));
  UPB_ASSERT(count + arr->UPB_PRIVATE(size) >= count);
  const size_t oldsize = arr->UPB_PRIVATE(size);
  if (!UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
          arr, arr->UPB_PRIVATE(size) + count, arena)) {
    return false;
  }
  upb_Array_Move(arr, i + count, i, oldsize - i);
  return true;
}

/*
 *              i        end      arr->size
 * |------------|XXXXXXXX|--------|
 */
void upb_Array_Delete(upb_Array* arr, size_t i, size_t count) {
  UPB_ASSERT(!upb_Array_IsFrozen(arr));
  const size_t end = i + count;
  UPB_ASSERT(i <= end);
  UPB_ASSERT(end <= arr->UPB_PRIVATE(size));
  upb_Array_Move(arr, i, end, arr->UPB_PRIVATE(size) - end);
  arr->UPB_PRIVATE(size) -= count;
}

bool upb_Array_Resize(upb_Array* arr, size_t size, upb_Arena* arena) {
  UPB_ASSERT(!upb_Array_IsFrozen(arr));
  const size_t oldsize = arr->UPB_PRIVATE(size);
  if (UPB_UNLIKELY(
          !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(arr, size, arena))) {
    return false;
  }
  const size_t newsize = arr->UPB_PRIVATE(size);
  if (newsize > oldsize) {
    const int lg2 = UPB_PRIVATE(_upb_Array_ElemSizeLg2)(arr);
    char* data = upb_Array_MutableDataPtr(arr);
    memset(data + (oldsize << lg2), 0, (newsize - oldsize) << lg2);
  }
  return true;
}

bool UPB_PRIVATE(_upb_Array_Realloc)(upb_Array* array, size_t min_capacity,
                                     upb_Arena* arena) {
  size_t new_capacity = UPB_MAX(array->UPB_PRIVATE(capacity), 4);
  const int lg2 = UPB_PRIVATE(_upb_Array_ElemSizeLg2)(array);
  size_t old_bytes = array->UPB_PRIVATE(capacity) << lg2;
  void* ptr = upb_Array_MutableDataPtr(array);

  // Log2 ceiling of size.
  while (new_capacity < min_capacity) new_capacity *= 2;

  const size_t new_bytes = new_capacity << lg2;
  ptr = upb_Arena_Realloc(arena, ptr, old_bytes, new_bytes);
  if (!ptr) return false;

  UPB_PRIVATE(_upb_Array_SetTaggedPtr)(array, ptr, lg2);
  array->UPB_PRIVATE(capacity) = new_capacity;
  return true;
}

void upb_Array_Freeze(upb_Array* arr, const upb_MiniTable* m) {
  if (upb_Array_IsFrozen(arr)) return;
  UPB_PRIVATE(_upb_Array_ShallowFreeze)(arr);

  if (m) {
    const size_t size = upb_Array_Size(arr);

    for (size_t i = 0; i < size; i++) {
      upb_MessageValue val = upb_Array_Get(arr, i);
      upb_Message_Freeze((upb_Message*)val.msg_val, m);
    }
  }
}


#include <stdint.h>
#include <stdlib.h>


// Must be last.

typedef struct upb_UnknownFields upb_UnknownFields;

typedef struct {
  uint32_t tag;
  union {
    uint64_t varint;
    uint64_t uint64;
    uint32_t uint32;
    upb_StringView delimited;
    upb_UnknownFields* group;
  } data;
} upb_UnknownField;

struct upb_UnknownFields {
  size_t size;
  size_t capacity;
  upb_UnknownField* fields;
};

typedef struct {
  upb_EpsCopyInputStream stream;
  upb_Arena* arena;
  upb_UnknownField* tmp;
  size_t tmp_size;
  int depth;
  upb_UnknownCompareResult status;
  jmp_buf err;
} upb_UnknownField_Context;

typedef struct {
  upb_UnknownField* arr_base;
  upb_UnknownField* arr_ptr;
  upb_UnknownField* arr_end;
  uint32_t last_tag;
  bool sorted;
} upb_UnknownFields_Builder;

UPB_NORETURN static void upb_UnknownFields_OutOfMemory(
    upb_UnknownField_Context* ctx) {
  ctx->status = kUpb_UnknownCompareResult_OutOfMemory;
  UPB_LONGJMP(ctx->err, 1);
}

static void upb_UnknownFields_Grow(upb_UnknownField_Context* ctx,
                                   upb_UnknownField** base,
                                   upb_UnknownField** ptr,
                                   upb_UnknownField** end) {
  size_t old = (*ptr - *base);
  size_t new = UPB_MAX(4, old * 2);

  *base = upb_Arena_Realloc(ctx->arena, *base, old * sizeof(**base),
                            new * sizeof(**base));
  if (!*base) upb_UnknownFields_OutOfMemory(ctx);

  *ptr = *base + old;
  *end = *base + new;
}

// We have to implement our own sort here, since qsort() is not an in-order
// sort. Here we use merge sort, the simplest in-order sort.
static void upb_UnknownFields_Merge(upb_UnknownField* arr, size_t start,
                                    size_t mid, size_t end,
                                    upb_UnknownField* tmp) {
  memcpy(tmp, &arr[start], (end - start) * sizeof(*tmp));

  upb_UnknownField* ptr1 = tmp;
  upb_UnknownField* end1 = &tmp[mid - start];
  upb_UnknownField* ptr2 = &tmp[mid - start];
  upb_UnknownField* end2 = &tmp[end - start];
  upb_UnknownField* out = &arr[start];

  while (ptr1 < end1 && ptr2 < end2) {
    if (ptr1->tag <= ptr2->tag) {
      *out++ = *ptr1++;
    } else {
      *out++ = *ptr2++;
    }
  }

  if (ptr1 < end1) {
    memcpy(out, ptr1, (end1 - ptr1) * sizeof(*out));
  } else if (ptr2 < end2) {
    memcpy(out, ptr1, (end2 - ptr2) * sizeof(*out));
  }
}

static void upb_UnknownFields_SortRecursive(upb_UnknownField* arr, size_t start,
                                            size_t end, upb_UnknownField* tmp) {
  if (end - start > 1) {
    size_t mid = start + ((end - start) / 2);
    upb_UnknownFields_SortRecursive(arr, start, mid, tmp);
    upb_UnknownFields_SortRecursive(arr, mid, end, tmp);
    upb_UnknownFields_Merge(arr, start, mid, end, tmp);
  }
}

static void upb_UnknownFields_Sort(upb_UnknownField_Context* ctx,
                                   upb_UnknownFields* fields) {
  if (ctx->tmp_size < fields->size) {
    const int oldsize = ctx->tmp_size * sizeof(*ctx->tmp);
    ctx->tmp_size = UPB_MAX(8, ctx->tmp_size);
    while (ctx->tmp_size < fields->size) ctx->tmp_size *= 2;
    const int newsize = ctx->tmp_size * sizeof(*ctx->tmp);
    ctx->tmp = upb_grealloc(ctx->tmp, oldsize, newsize);
  }
  upb_UnknownFields_SortRecursive(fields->fields, 0, fields->size, ctx->tmp);
}

static upb_UnknownFields* upb_UnknownFields_BuildFromBuffer(
    upb_UnknownField_Context* ctx, const char** buf);

// Combines two unknown fields into one.
static void upb_CombineUnknownFields(upb_UnknownField_Context* ctx,
                                     upb_UnknownFields_Builder* builder,
                                     const char** buf) {
  upb_UnknownField* arr_base = builder->arr_base;
  upb_UnknownField* arr_ptr = builder->arr_ptr;
  upb_UnknownField* arr_end = builder->arr_end;
  const char* ptr = *buf;
  uint32_t last_tag = builder->last_tag;
  bool sorted = builder->sorted;

  // Parse the unknown field data. It is an invariant of the data structure that
  // unknown field data is valid, so parse errors here should be impossible.
  while (!upb_EpsCopyInputStream_IsDone(&ctx->stream, &ptr)) {
    uint32_t tag;
    ptr = upb_WireReader_ReadTag(ptr, &tag, &ctx->stream);
    UPB_ASSERT(tag <= UINT32_MAX);
    int wire_type = upb_WireReader_GetWireType(tag);
    if (wire_type == kUpb_WireType_EndGroup) break;
    if (tag < last_tag) sorted = false;
    last_tag = tag;

    if (arr_ptr == arr_end) {
      upb_UnknownFields_Grow(ctx, &arr_base, &arr_ptr, &arr_end);
    }
    upb_UnknownField* field = arr_ptr;
    field->tag = tag;
    arr_ptr++;

    switch (wire_type) {
      case kUpb_WireType_Varint:
        ptr = upb_WireReader_ReadVarint(ptr, &field->data.varint, &ctx->stream);
        UPB_ASSERT(ptr);
        break;
      case kUpb_WireType_64Bit:
        ptr =
            upb_WireReader_ReadFixed64(ptr, &field->data.uint64, &ctx->stream);
        UPB_ASSERT(ptr);
        break;
      case kUpb_WireType_32Bit:
        ptr =
            upb_WireReader_ReadFixed32(ptr, &field->data.uint32, &ctx->stream);
        UPB_ASSERT(ptr);
        break;
      case kUpb_WireType_Delimited: {
        int size;
        ptr = upb_WireReader_ReadSize(ptr, &size, &ctx->stream);
        UPB_ASSERT(ptr);
        const char* s_ptr = ptr;
        ptr = upb_EpsCopyInputStream_ReadStringAliased(&ctx->stream, &s_ptr,
                                                       size);
        UPB_ASSERT(ptr);
        field->data.delimited.data = s_ptr;
        field->data.delimited.size = size;
        break;
      }
      case kUpb_WireType_StartGroup:
        if (--ctx->depth < 0) {
          ctx->status = kUpb_UnknownCompareResult_MaxDepthExceeded;
          UPB_LONGJMP(ctx->err, 1);
        }
        field->data.group = upb_UnknownFields_BuildFromBuffer(ctx, &ptr);
        ctx->depth++;
        break;
      default:
        UPB_UNREACHABLE();
    }
  }
  *buf = ptr;
  builder->arr_base = arr_base;
  builder->arr_ptr = arr_ptr;
  builder->arr_end = arr_end;
  builder->sorted = sorted;
  builder->last_tag = last_tag;
}

static upb_UnknownFields* upb_UnknownFields_DoBuild(
    upb_UnknownField_Context* ctx, upb_UnknownFields_Builder* builder) {
  upb_UnknownFields* ret = upb_Arena_Malloc(ctx->arena, sizeof(*ret));
  if (!ret) upb_UnknownFields_OutOfMemory(ctx);
  ret->fields = builder->arr_base;
  ret->size = builder->arr_ptr - builder->arr_base;
  ret->capacity = builder->arr_end - builder->arr_base;
  if (!builder->sorted) {
    upb_UnknownFields_Sort(ctx, ret);
  }
  return ret;
}

// Builds a upb_UnknownFields data structure from the binary data in buf.
static upb_UnknownFields* upb_UnknownFields_BuildFromBuffer(
    upb_UnknownField_Context* ctx, const char** buf) {
  upb_UnknownFields_Builder builder = {
      .arr_base = NULL,
      .arr_ptr = NULL,
      .arr_end = NULL,
      .sorted = true,
      .last_tag = 0,
  };
  const char* ptr = *buf;
  upb_CombineUnknownFields(ctx, &builder, &ptr);
  upb_UnknownFields* fields = upb_UnknownFields_DoBuild(ctx, &builder);
  *buf = ptr;
  return fields;
}

// Builds a upb_UnknownFields data structure from the unknown fields of a
// upb_Message.
static upb_UnknownFields* upb_UnknownFields_Build(upb_UnknownField_Context* ctx,
                                                  const upb_Message* msg) {
  upb_UnknownFields_Builder builder = {
      .arr_base = NULL,
      .arr_ptr = NULL,
      .arr_end = NULL,
      .sorted = true,
      .last_tag = 0,
  };
  uintptr_t iter = kUpb_Message_UnknownBegin;
  upb_StringView view;
  while (upb_Message_NextUnknown(msg, &view, &iter)) {
    upb_EpsCopyInputStream_Init(&ctx->stream, &view.data, view.size, true);
    upb_CombineUnknownFields(ctx, &builder, &view.data);
    UPB_ASSERT(upb_EpsCopyInputStream_IsDone(&ctx->stream, &view.data) &&
               !upb_EpsCopyInputStream_IsError(&ctx->stream));
  }
  upb_UnknownFields* fields = upb_UnknownFields_DoBuild(ctx, &builder);
  return fields;
}

// Compares two sorted upb_UnknownFields structures for equality.
static bool upb_UnknownFields_IsEqual(const upb_UnknownFields* uf1,
                                      const upb_UnknownFields* uf2) {
  if (uf1->size != uf2->size) return false;
  for (size_t i = 0, n = uf1->size; i < n; i++) {
    upb_UnknownField* f1 = &uf1->fields[i];
    upb_UnknownField* f2 = &uf2->fields[i];
    if (f1->tag != f2->tag) return false;
    int wire_type = f1->tag & 7;
    switch (wire_type) {
      case kUpb_WireType_Varint:
        if (f1->data.varint != f2->data.varint) return false;
        break;
      case kUpb_WireType_64Bit:
        if (f1->data.uint64 != f2->data.uint64) return false;
        break;
      case kUpb_WireType_32Bit:
        if (f1->data.uint32 != f2->data.uint32) return false;
        break;
      case kUpb_WireType_Delimited:
        if (!upb_StringView_IsEqual(f1->data.delimited, f2->data.delimited)) {
          return false;
        }
        break;
      case kUpb_WireType_StartGroup:
        if (!upb_UnknownFields_IsEqual(f1->data.group, f2->data.group)) {
          return false;
        }
        break;
      default:
        UPB_UNREACHABLE();
    }
  }
  return true;
}

static upb_UnknownCompareResult upb_UnknownField_DoCompare(
    upb_UnknownField_Context* ctx, const upb_Message* msg1,
    const upb_Message* msg2) {
  upb_UnknownCompareResult ret;
  // First build both unknown fields into a sorted data structure (similar
  // to the UnknownFieldSet in C++).
  upb_UnknownFields* uf1 = upb_UnknownFields_Build(ctx, msg1);
  upb_UnknownFields* uf2 = upb_UnknownFields_Build(ctx, msg2);

  // Now perform the equality check on the sorted structures.
  if (upb_UnknownFields_IsEqual(uf1, uf2)) {
    ret = kUpb_UnknownCompareResult_Equal;
  } else {
    ret = kUpb_UnknownCompareResult_NotEqual;
  }
  return ret;
}

static upb_UnknownCompareResult upb_UnknownField_Compare(
    upb_UnknownField_Context* const ctx, const upb_Message* msg1,
    const upb_Message* msg2) {
  upb_UnknownCompareResult ret;
  if (UPB_SETJMP(ctx->err) == 0) {
    ret = upb_UnknownField_DoCompare(ctx, msg1, msg2);
  } else {
    ret = ctx->status;
    UPB_ASSERT(ret != kUpb_UnknownCompareResult_Equal);
  }

  upb_Arena_Free(ctx->arena);
  upb_gfree(ctx->tmp);
  return ret;
}

upb_UnknownCompareResult UPB_PRIVATE(_upb_Message_UnknownFieldsAreEqual)(
    const upb_Message* msg1, const upb_Message* msg2, int max_depth) {
  bool msg1_empty = !upb_Message_HasUnknown(msg1);
  bool msg2_empty = !upb_Message_HasUnknown(msg2);
  if (msg1_empty && msg2_empty) return kUpb_UnknownCompareResult_Equal;
  if (msg1_empty || msg2_empty) return kUpb_UnknownCompareResult_NotEqual;

  upb_UnknownField_Context ctx = {
      .arena = upb_Arena_New(),
      .depth = max_depth,
      .tmp = NULL,
      .tmp_size = 0,
      .status = kUpb_UnknownCompareResult_Equal,
  };

  if (!ctx.arena) return kUpb_UnknownCompareResult_OutOfMemory;

  return upb_UnknownField_Compare(&ctx, msg1, msg2);
}


#include <stdint.h>
#include <string.h>


// Must be last.

const upb_Extension* UPB_PRIVATE(_upb_Message_Getext)(
    const struct upb_Message* msg, const upb_MiniTableExtension* e) {
  upb_Message_Internal* in = UPB_PRIVATE(_upb_Message_GetInternal)(msg);
  if (!in) return NULL;

  for (size_t i = 0; i < in->size; i++) {
    upb_TaggedAuxPtr tagged_ptr = in->aux_data[i];
    if (upb_TaggedAuxPtr_IsExtension(tagged_ptr)) {
      const upb_Extension* ext = upb_TaggedAuxPtr_Extension(tagged_ptr);
      if (ext->ext == e) {
        return ext;
      }
    }
  }

  return NULL;
}

upb_Extension* UPB_PRIVATE(_upb_Message_GetOrCreateExtension)(
    struct upb_Message* msg, const upb_MiniTableExtension* e, upb_Arena* a) {
  UPB_ASSERT(!upb_Message_IsFrozen(msg));
  upb_Extension* ext = (upb_Extension*)UPB_PRIVATE(_upb_Message_Getext)(msg, e);
  if (ext) return ext;

  if (!UPB_PRIVATE(_upb_Message_ReserveSlot)(msg, a)) return NULL;
  upb_Message_Internal* in = UPB_PRIVATE(_upb_Message_GetInternal)(msg);
  ext = upb_Arena_Malloc(a, sizeof(upb_Extension));
  if (!ext) return NULL;
  memset(ext, 0, sizeof(upb_Extension));
  ext->ext = e;
  in->aux_data[in->size++] = upb_TaggedAuxPtr_MakeExtension(ext);
  return ext;
}


#include <stddef.h>


// Must be last.

bool UPB_PRIVATE(_upb_Message_NextBaseField)(const upb_Message* msg,
                                             const upb_MiniTable* m,
                                             const upb_MiniTableField** out_f,
                                             upb_MessageValue* out_v,
                                             size_t* iter) {
  const size_t count = upb_MiniTable_FieldCount(m);
  size_t i = *iter;

  while (++i < count) {
    const upb_MiniTableField* f = upb_MiniTable_GetFieldByIndex(m, i);
    const void* src = UPB_PRIVATE(_upb_Message_DataPtr)(msg, f);

    upb_MessageValue val;
    UPB_PRIVATE(_upb_MiniTableField_DataCopy)(f, &val, src);

    // Skip field if unset or empty.
    if (upb_MiniTableField_HasPresence(f)) {
      if (!upb_Message_HasBaseField(msg, f)) continue;
    } else {
      if (UPB_PRIVATE(_upb_MiniTableField_DataIsZero)(f, src)) continue;

      if (upb_MiniTableField_IsArray(f)) {
        if (upb_Array_Size(val.array_val) == 0) continue;
      } else if (upb_MiniTableField_IsMap(f)) {
        if (upb_Map_Size(val.map_val) == 0) continue;
      }
    }

    *out_f = f;
    *out_v = val;
    *iter = i;
    return true;
  }

  return false;
}


#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>


// Must be last.

// The latest win32 SDKs have an invalid definition of NAN.
// https://developercommunity.visualstudio.com/t/NAN-is-no-longer-compile-time-constant-i/10688907
//
// Unfortunately, the `0.0 / 0.0` workaround doesn't work in Clang under C23, so
// try __builtin_nan first, if that exists.
#ifdef _WIN32
#ifdef __has_builtin
#if __has_builtin(__builtin_nan)
#define UPB_NAN __builtin_nan("0")
#endif
#if __has_builtin(__builtin_inf)
#define UPB_INFINITY __builtin_inf()
#endif
#endif
#ifndef UPB_NAN
#define UPB_NAN 0.0 / 0.0
#endif
#ifndef UPB_INFINITY
#define UPB_INFINITY 1.0 / 0.0
#endif
#else
// For !_WIN32, assume math.h works.
#define UPB_NAN NAN
#define UPB_INFINITY INFINITY
#endif

const float kUpb_FltInfinity = UPB_INFINITY;
const double kUpb_Infinity = UPB_INFINITY;
const double kUpb_NaN = UPB_NAN;

static size_t _upb_Message_SizeOfInternal(uint32_t count) {
  return UPB_SIZEOF_FLEX(upb_Message_Internal, aux_data, count);
}

bool UPB_PRIVATE(_upb_Message_ReserveSlot)(struct upb_Message* msg,
                                           upb_Arena* a) {
  UPB_ASSERT(!upb_Message_IsFrozen(msg));
  upb_Message_Internal* in = UPB_PRIVATE(_upb_Message_GetInternal)(msg);
  if (!in) {
    // No internal data, allocate from scratch.
    uint32_t capacity = 4;
    in = upb_Arena_Malloc(a, _upb_Message_SizeOfInternal(capacity));
    if (!in) return false;
    in->size = 0;
    in->capacity = capacity;
    UPB_PRIVATE(_upb_Message_SetInternal)(msg, in);
  } else if (in->capacity == in->size) {
    // Internal data is too small, reallocate.
    uint32_t new_capacity = upb_RoundUpToPowerOfTwo(in->size + 1);
    in = upb_Arena_Realloc(a, in, _upb_Message_SizeOfInternal(in->capacity),
                           _upb_Message_SizeOfInternal(new_capacity));
    if (!in) return false;
    in->capacity = new_capacity;
    UPB_PRIVATE(_upb_Message_SetInternal)(msg, in);
  }
  UPB_ASSERT(in->capacity - in->size >= 1);
  return true;
}

#ifdef UPB_TRACING_ENABLED
static void (*_message_trace_handler)(const upb_MiniTable*, const upb_Arena*);

void upb_Message_LogNewMessage(const upb_MiniTable* m, const upb_Arena* arena) {
  if (_message_trace_handler) {
    _message_trace_handler(m, arena);
  }
}

void upb_Message_SetNewMessageTraceHandler(void (*handler)(const upb_MiniTable*,
                                                           const upb_Arena*)) {
  _message_trace_handler = handler;
}
#endif  // UPB_TRACING_ENABLED


#include <stdbool.h>
#include <stdint.h>
#include <string.h>


// Must be last.

static upb_StringView upb_Clone_StringView(upb_StringView str,
                                           upb_Arena* arena) {
  if (str.size == 0) {
    return upb_StringView_FromDataAndSize(NULL, 0);
  }
  void* cloned_data = upb_Arena_Malloc(arena, str.size);
  upb_StringView cloned_str =
      upb_StringView_FromDataAndSize(cloned_data, str.size);
  memcpy(cloned_data, str.data, str.size);
  return cloned_str;
}

static bool upb_Clone_MessageValue(void* value, upb_CType value_type,
                                   const upb_MiniTable* sub, upb_Arena* arena) {
  switch (value_type) {
    case kUpb_CType_Bool:
    case kUpb_CType_Float:
    case kUpb_CType_Int32:
    case kUpb_CType_UInt32:
    case kUpb_CType_Enum:
    case kUpb_CType_Double:
    case kUpb_CType_Int64:
    case kUpb_CType_UInt64:
      return true;
    case kUpb_CType_String:
    case kUpb_CType_Bytes: {
      upb_StringView source = *(upb_StringView*)value;
      int size = source.size;
      void* cloned_data = upb_Arena_Malloc(arena, size);
      if (cloned_data == NULL) {
        return false;
      }
      *(upb_StringView*)value =
          upb_StringView_FromDataAndSize(cloned_data, size);
      memcpy(cloned_data, source.data, size);
      return true;
    } break;
    case kUpb_CType_Message: {
      const upb_TaggedMessagePtr source = *(upb_TaggedMessagePtr*)value;
      bool is_empty = upb_TaggedMessagePtr_IsEmpty(source);
      if (is_empty) sub = UPB_PRIVATE(_upb_MiniTable_Empty)();
      UPB_ASSERT(source);
      upb_Message* clone = upb_Message_DeepClone(
          UPB_PRIVATE(_upb_TaggedMessagePtr_GetMessage)(source), sub, arena);
      *(upb_TaggedMessagePtr*)value =
          UPB_PRIVATE(_upb_TaggedMessagePtr_Pack)(clone, is_empty);
      return clone != NULL;
    } break;
  }
  UPB_UNREACHABLE();
}

upb_Map* upb_Map_DeepClone(const upb_Map* map, upb_CType key_type,
                           upb_CType value_type,
                           const upb_MiniTable* map_entry_table,
                           upb_Arena* arena) {
  upb_Map* cloned_map = _upb_Map_New(arena, map->key_size, map->val_size);
  if (cloned_map == NULL) {
    return NULL;
  }
  upb_MessageValue key, val;
  size_t iter = kUpb_Map_Begin;
  while (upb_Map_Next(map, &key, &val, &iter)) {
    const upb_MiniTableField* value_field =
        upb_MiniTable_MapValue(map_entry_table);
    const upb_MiniTable* value_sub =
        upb_MiniTableField_CType(value_field) == kUpb_CType_Message
            ? upb_MiniTable_GetSubMessageTable(map_entry_table, value_field)
            : NULL;
    upb_CType value_field_type = upb_MiniTableField_CType(value_field);
    if (!upb_Clone_MessageValue(&val, value_field_type, value_sub, arena)) {
      return NULL;
    }
    if (!upb_Map_Set(cloned_map, key, val, arena)) {
      return NULL;
    }
  }
  return cloned_map;
}

static upb_Map* upb_Message_Map_DeepClone(const upb_Map* map,
                                          const upb_MiniTable* mini_table,
                                          const upb_MiniTableField* f,
                                          upb_Message* clone,
                                          upb_Arena* arena) {
  UPB_ASSERT(!upb_Message_IsFrozen(clone));
  const upb_MiniTable* map_entry_table =
      upb_MiniTable_MapEntrySubMessage(mini_table, f);
  UPB_ASSERT(map_entry_table);

  const upb_MiniTableField* key_field = upb_MiniTable_MapKey(map_entry_table);
  const upb_MiniTableField* value_field =
      upb_MiniTable_MapValue(map_entry_table);

  upb_Map* cloned_map = upb_Map_DeepClone(
      map, upb_MiniTableField_CType(key_field),
      upb_MiniTableField_CType(value_field), map_entry_table, arena);
  if (!cloned_map) {
    return NULL;
  }
  upb_Message_SetBaseField(clone, f, &cloned_map);
  return cloned_map;
}

upb_Array* upb_Array_DeepClone(const upb_Array* array, upb_CType value_type,
                               const upb_MiniTable* sub, upb_Arena* arena) {
  const size_t size = upb_Array_Size(array);
  const int lg2 = UPB_PRIVATE(_upb_CType_SizeLg2)(value_type);
  upb_Array* cloned_array = UPB_PRIVATE(_upb_Array_New)(arena, size, lg2);
  if (!cloned_array) {
    return NULL;
  }
  if (!UPB_PRIVATE(_upb_Array_ResizeUninitialized)(cloned_array, size, arena)) {
    return NULL;
  }
  for (size_t i = 0; i < size; ++i) {
    upb_MessageValue val = upb_Array_Get(array, i);
    if (!upb_Clone_MessageValue(&val, value_type, sub, arena)) {
      return NULL;
    }
    upb_Array_Set(cloned_array, i, val);
  }
  return cloned_array;
}

static bool upb_Message_Array_DeepClone(const upb_Array* array,
                                        const upb_MiniTable* mini_table,
                                        const upb_MiniTableField* field,
                                        upb_Message* clone, upb_Arena* arena) {
  UPB_ASSERT(!upb_Message_IsFrozen(clone));
  UPB_PRIVATE(_upb_MiniTableField_CheckIsArray)(field);
  upb_Array* cloned_array = upb_Array_DeepClone(
      array, upb_MiniTableField_CType(field),
      upb_MiniTableField_CType(field) == kUpb_CType_Message
          ? upb_MiniTable_GetSubMessageTable(mini_table, field)
          : NULL,
      arena);

  // Clear out upb_Array* due to parent memcpy.
  upb_Message_SetBaseField(clone, field, &cloned_array);
  return true;
}

static bool upb_Clone_ExtensionValue(
    const upb_MiniTableExtension* mini_table_ext, const upb_Extension* source,
    upb_Extension* dest, upb_Arena* arena) {
  dest->data = source->data;
  return upb_Clone_MessageValue(
      &dest->data, upb_MiniTableExtension_CType(mini_table_ext),
      upb_MiniTableExtension_GetSubMessage(mini_table_ext), arena);
}

upb_Message* _upb_Message_Copy(upb_Message* dst, const upb_Message* src,
                               const upb_MiniTable* mini_table,
                               upb_Arena* arena) {
  UPB_ASSERT(!upb_Message_IsFrozen(dst));
  upb_StringView empty_string = upb_StringView_FromDataAndSize(NULL, 0);
  // Only copy message area skipping upb_Message_Internal.
  memcpy(dst + 1, src + 1, mini_table->UPB_PRIVATE(size) - sizeof(upb_Message));
  for (int i = 0; i < upb_MiniTable_FieldCount(mini_table); ++i) {
    const upb_MiniTableField* field =
        upb_MiniTable_GetFieldByIndex(mini_table, i);
    if (upb_MiniTableField_IsScalar(field)) {
      switch (upb_MiniTableField_CType(field)) {
        case kUpb_CType_Message: {
          upb_TaggedMessagePtr tagged =
              upb_Message_GetTaggedMessagePtr(src, field, NULL);
          const upb_Message* sub_message =
              UPB_PRIVATE(_upb_TaggedMessagePtr_GetMessage)(tagged);
          if (sub_message != NULL) {
            // If the message is currently in an unlinked, "empty" state we keep
            // it that way, because we don't want to deal with decode options,
            // decode status, or possible parse failure here.
            bool is_empty = upb_TaggedMessagePtr_IsEmpty(tagged);
            const upb_MiniTable* sub_message_table =
                is_empty ? UPB_PRIVATE(_upb_MiniTable_Empty)()
                         : upb_MiniTable_GetSubMessageTable(mini_table, field);
            upb_Message* dst_sub_message =
                upb_Message_DeepClone(sub_message, sub_message_table, arena);
            if (dst_sub_message == NULL) {
              return NULL;
            }
            UPB_PRIVATE(_upb_Message_SetTaggedMessagePtr)
            (dst, field,
             UPB_PRIVATE(_upb_TaggedMessagePtr_Pack)(dst_sub_message,
                                                     is_empty));
          }
        } break;
        case kUpb_CType_String:
        case kUpb_CType_Bytes: {
          upb_StringView str = upb_Message_GetString(src, field, empty_string);
          if (str.size != 0) {
            if (!upb_Message_SetString(
                    dst, field, upb_Clone_StringView(str, arena), arena)) {
              return NULL;
            }
          }
        } break;
        default:
          // Scalar, already copied.
          break;
      }
    } else {
      if (upb_MiniTableField_IsMap(field)) {
        const upb_Map* map = upb_Message_GetMap(src, field);
        if (map != NULL) {
          if (!upb_Message_Map_DeepClone(map, mini_table, field, dst, arena)) {
            return NULL;
          }
        }
      } else {
        const upb_Array* array = upb_Message_GetArray(src, field);
        if (array != NULL) {
          if (!upb_Message_Array_DeepClone(array, mini_table, field, dst,
                                           arena)) {
            return NULL;
          }
        }
      }
    }
  }
  // Clone extensions.
  upb_Message_Internal* in = UPB_PRIVATE(_upb_Message_GetInternal)(src);
  if (!in) return dst;

  for (size_t i = 0; i < in->size; i++) {
    upb_TaggedAuxPtr tagged_ptr = in->aux_data[i];
    if (upb_TaggedAuxPtr_IsExtension(tagged_ptr)) {
      // Clone extension
      const upb_Extension* msg_ext = upb_TaggedAuxPtr_Extension(tagged_ptr);
      const upb_MiniTableField* field = &msg_ext->ext->UPB_PRIVATE(field);
      upb_Extension* dst_ext = UPB_PRIVATE(_upb_Message_GetOrCreateExtension)(
          dst, msg_ext->ext, arena);
      if (!dst_ext) return NULL;
      if (upb_MiniTableField_IsScalar(field)) {
        if (!upb_Clone_ExtensionValue(msg_ext->ext, msg_ext, dst_ext, arena)) {
          return NULL;
        }
      } else {
        upb_Array* msg_array = (upb_Array*)msg_ext->data.array_val;
        UPB_ASSERT(msg_array);
        upb_Array* cloned_array = upb_Array_DeepClone(
            msg_array, upb_MiniTableField_CType(field),
            upb_MiniTableExtension_GetSubMessage(msg_ext->ext), arena);
        if (!cloned_array) {
          return NULL;
        }
        dst_ext->data.array_val = cloned_array;
      }
    } else if (upb_TaggedAuxPtr_IsUnknown(tagged_ptr)) {
      // Clone unknown
      upb_StringView* unknown = upb_TaggedAuxPtr_UnknownData(tagged_ptr);
      // Make a copy into destination arena.
      if (!UPB_PRIVATE(_upb_Message_AddUnknown)(dst, unknown->data,
                                                unknown->size, arena, NULL)) {
        return NULL;
      }
    }
  }

  return dst;
}

bool upb_Message_DeepCopy(upb_Message* dst, const upb_Message* src,
                          const upb_MiniTable* mini_table, upb_Arena* arena) {
  UPB_ASSERT(!upb_Message_IsFrozen(dst));
  upb_Message_Clear(dst, mini_table);
  return _upb_Message_Copy(dst, src, mini_table, arena) != NULL;
}

// Deep clones a message using the provided target arena.
//
// Returns NULL on failure.
upb_Message* upb_Message_DeepClone(const upb_Message* msg,
                                   const upb_MiniTable* m, upb_Arena* arena) {
  upb_Message* clone = upb_Message_New(m, arena);
  return _upb_Message_Copy(clone, msg, m, arena);
}

// Performs a shallow copy. TODO: Extend to handle unknown fields.
void upb_Message_ShallowCopy(upb_Message* dst, const upb_Message* src,
                             const upb_MiniTable* m) {
  UPB_ASSERT(!upb_Message_IsFrozen(dst));
  memcpy(dst, src, m->UPB_PRIVATE(size));
}

// Performs a shallow clone. Ignores unknown fields.
upb_Message* upb_Message_ShallowClone(const upb_Message* msg,
                                      const upb_MiniTable* m,
                                      upb_Arena* arena) {
  upb_Message* clone = upb_Message_New(m, arena);
  upb_Message_ShallowCopy(clone, msg, m);
  return clone;
}


#include <stdint.h>
#include <stdlib.h>
#include <string.h>


// Must be last.

static int _upb_mapsorter_intkeys(const void* _a, const void* _b) {
  const upb_tabent* const* a = _a;
  const upb_tabent* const* b = _b;
  uintptr_t a_key = (*a)->key.num;
  uintptr_t b_key = (*b)->key.num;
  return a_key < b_key ? -1 : a_key > b_key;
}

static void _upb_mapsorter_getkeys(const void* _a, const void* _b, void* a_key,
                                   void* b_key, size_t size) {
  const upb_tabent* const* a = _a;
  const upb_tabent* const* b = _b;
  upb_StringView a_tabkey = upb_key_strview((*a)->key);
  upb_StringView b_tabkey = upb_key_strview((*b)->key);
  _upb_map_fromkey(a_tabkey, a_key, size);
  _upb_map_fromkey(b_tabkey, b_key, size);
}

static int _upb_mapsorter_cmpi64(const void* _a, const void* _b) {
  int64_t a, b;
  _upb_mapsorter_getkeys(_a, _b, &a, &b, 8);
  return a < b ? -1 : a > b;
}

static int _upb_mapsorter_cmpu64(const void* _a, const void* _b) {
  uint64_t a, b;
  _upb_mapsorter_getkeys(_a, _b, &a, &b, 8);
  return a < b ? -1 : a > b;
}

static int _upb_mapsorter_cmpi32(const void* _a, const void* _b) {
  int32_t a, b;
  _upb_mapsorter_getkeys(_a, _b, &a, &b, 4);
  return a < b ? -1 : a > b;
}

static int _upb_mapsorter_cmpu32(const void* _a, const void* _b) {
  uint32_t a, b;
  _upb_mapsorter_getkeys(_a, _b, &a, &b, 4);
  return a < b ? -1 : a > b;
}

static int _upb_mapsorter_cmpbool(const void* _a, const void* _b) {
  bool a, b;
  _upb_mapsorter_getkeys(_a, _b, &a, &b, 1);
  return a < b ? -1 : a > b;
}

static int _upb_mapsorter_cmpstr(const void* _a, const void* _b) {
  upb_StringView a, b;
  _upb_mapsorter_getkeys(_a, _b, &a, &b, UPB_MAPTYPE_STRING);
  size_t common_size = UPB_MIN(a.size, b.size);
  int cmp = memcmp(a.data, b.data, common_size);
  if (cmp) return -cmp;
  return a.size < b.size ? -1 : a.size > b.size;
}

static int (*const compar[kUpb_FieldType_SizeOf])(const void*, const void*) = {
    [kUpb_FieldType_Int64] = _upb_mapsorter_cmpi64,
    [kUpb_FieldType_SFixed64] = _upb_mapsorter_cmpi64,
    [kUpb_FieldType_SInt64] = _upb_mapsorter_cmpi64,

    [kUpb_FieldType_UInt64] = _upb_mapsorter_cmpu64,
    [kUpb_FieldType_Fixed64] = _upb_mapsorter_cmpu64,

    [kUpb_FieldType_Int32] = _upb_mapsorter_cmpi32,
    [kUpb_FieldType_SInt32] = _upb_mapsorter_cmpi32,
    [kUpb_FieldType_SFixed32] = _upb_mapsorter_cmpi32,
    [kUpb_FieldType_Enum] = _upb_mapsorter_cmpi32,

    [kUpb_FieldType_UInt32] = _upb_mapsorter_cmpu32,
    [kUpb_FieldType_Fixed32] = _upb_mapsorter_cmpu32,

    [kUpb_FieldType_Bool] = _upb_mapsorter_cmpbool,

    [kUpb_FieldType_String] = _upb_mapsorter_cmpstr,
    [kUpb_FieldType_Bytes] = _upb_mapsorter_cmpstr,
};

static bool _upb_mapsorter_resize(_upb_mapsorter* s, _upb_sortedmap* sorted,
                                  int size) {
  sorted->start = s->size;
  sorted->pos = sorted->start;
  sorted->end = sorted->start + size;

  if (sorted->end > s->cap) {
    const int oldsize = s->cap * sizeof(*s->entries);
    s->cap = upb_RoundUpToPowerOfTwo(sorted->end);
    const int newsize = s->cap * sizeof(*s->entries);
    s->entries = upb_grealloc(s->entries, oldsize, newsize);
    if (!s->entries) return false;
  }

  s->size = sorted->end;
  return true;
}

bool _upb_mapsorter_pushmap(_upb_mapsorter* s, upb_FieldType key_type,
                            const upb_Map* map, _upb_sortedmap* sorted) {
  int map_size;
  if (map->UPB_PRIVATE(is_strtable)) {
    map_size = _upb_Map_Size(map);
  } else {
    // For inttable, only sort the table entries, since the array part is
    // already in a sorted order.
    map_size = map->t.inttable.t.count;
  }

  if (!_upb_mapsorter_resize(s, sorted, map_size)) return false;

  // Copy non-empty entries from the table to s->entries.
  const void** dst = &s->entries[sorted->start];
  const upb_tabent* src;
  const upb_tabent* end;
  if (map->UPB_PRIVATE(is_strtable)) {
    src = map->t.strtable.t.entries;
    end = src + upb_table_size(&map->t.strtable.t);
  } else {
    // For inttable, only sort the table entries, since the array part is
    // already in a sorted order.
    src = map->t.inttable.t.entries;
    end = src + upb_table_size(&map->t.inttable.t);
  }
  for (; src < end; src++) {
    if (!upb_tabent_isempty(src)) {
      *dst = src;
      dst++;
    }
  }
  UPB_ASSERT(dst == &s->entries[sorted->end]);

  // Sort entries according to the key type.
  qsort(&s->entries[sorted->start], map_size, sizeof(*s->entries),
        map->UPB_PRIVATE(is_strtable) ? compar[key_type]
                                      : _upb_mapsorter_intkeys);
  return true;
}

static int _upb_mapsorter_cmpext(const void* _a, const void* _b) {
  const upb_Extension* const* a = _a;
  const upb_Extension* const* b = _b;
  uint32_t a_num = upb_MiniTableExtension_Number((*a)->ext);
  uint32_t b_num = upb_MiniTableExtension_Number((*b)->ext);
  UPB_ASSERT(a_num != b_num);
  return a_num < b_num ? -1 : 1;
}

bool _upb_mapsorter_pushexts(_upb_mapsorter* s, const upb_Message_Internal* in,
                             _upb_sortedmap* sorted) {
  size_t count = 0;
  for (size_t i = 0; i < in->size; i++) {
    count += upb_TaggedAuxPtr_IsExtension(in->aux_data[i]);
  }
  if (!_upb_mapsorter_resize(s, sorted, count)) return false;
  if (count == 0) return true;
  const upb_Extension** entry =
      (const upb_Extension**)&s->entries[sorted->start];
  for (size_t i = 0; i < in->size; i++) {
    upb_TaggedAuxPtr tagged_ptr = in->aux_data[i];
    if (upb_TaggedAuxPtr_IsExtension(tagged_ptr)) {
      *entry++ = upb_TaggedAuxPtr_Extension(tagged_ptr);
    }
  }
  qsort(&s->entries[sorted->start], count, sizeof(*s->entries),
        _upb_mapsorter_cmpext);
  return true;
}


#include <stdint.h>
#include <string.h>


// Must be last.

// Strings/bytes are special-cased in maps.
char _upb_Map_CTypeSizeTable[12] = {
    [kUpb_CType_Bool] = 1,
    [kUpb_CType_Float] = 4,
    [kUpb_CType_Int32] = 4,
    [kUpb_CType_UInt32] = 4,
    [kUpb_CType_Enum] = 4,
    [kUpb_CType_Message] = sizeof(void*),
    [kUpb_CType_Double] = 8,
    [kUpb_CType_Int64] = 8,
    [kUpb_CType_UInt64] = 8,
    [kUpb_CType_String] = UPB_MAPTYPE_STRING,
    [kUpb_CType_Bytes] = UPB_MAPTYPE_STRING,
};

upb_Map* upb_Map_New(upb_Arena* a, upb_CType key_type, upb_CType value_type) {
  return _upb_Map_New(a, _upb_Map_CTypeSize(key_type),
                      _upb_Map_CTypeSize(value_type));
}

size_t upb_Map_Size(const upb_Map* map) { return _upb_Map_Size(map); }

bool upb_Map_Get(const upb_Map* map, upb_MessageValue key,
                 upb_MessageValue* val) {
  return _upb_Map_Get(map, &key, map->key_size, val, map->val_size);
}

struct upb_Message* upb_Map_GetMutable(upb_Map* map, upb_MessageValue key) {
  UPB_ASSERT(map->val_size == sizeof(upb_Message*));
  upb_Message* val = NULL;
  if (_upb_Map_Get(map, &key, map->key_size, &val, sizeof(upb_Message*))) {
    return val;
  } else {
    return NULL;
  }
}

void upb_Map_Clear(upb_Map* map) { _upb_Map_Clear(map); }

upb_MapInsertStatus upb_Map_Insert(upb_Map* map, upb_MessageValue key,
                                   upb_MessageValue val, upb_Arena* arena) {
  UPB_ASSERT(arena);
  return (upb_MapInsertStatus)_upb_Map_Insert(map, &key, map->key_size, &val,
                                              map->val_size, arena);
}

bool upb_Map_Delete(upb_Map* map, upb_MessageValue key, upb_MessageValue* val) {
  upb_value v;
  const bool removed = _upb_Map_Delete(map, &key, map->key_size, &v);
  if (val) _upb_map_fromvalue(v, val, map->val_size);
  return removed;
}

bool upb_Map_Next(const upb_Map* map, upb_MessageValue* key,
                  upb_MessageValue* val, size_t* iter) {
  upb_value v;
  bool ret;
  if (map->UPB_PRIVATE(is_strtable)) {
    upb_StringView strkey;
    ret = upb_strtable_next2(&map->t.strtable, &strkey, &v, (intptr_t*)iter);
    if (ret) {
      _upb_map_fromkey(strkey, key, map->key_size);
    }
  } else {
    uintptr_t intkey;
    ret = upb_inttable_next(&map->t.inttable, &intkey, &v, (intptr_t*)iter);
    if (ret) {
      memcpy(key, &intkey, map->key_size);
    }
  }
  if (ret) {
    _upb_map_fromvalue(v, val, map->val_size);
  }
  return ret;
}

UPB_API void upb_Map_SetEntryValue(upb_Map* map, size_t iter,
                                   upb_MessageValue val) {
  upb_value v;
  _upb_map_tovalue(&val, map->val_size, &v, NULL);
  if (map->UPB_PRIVATE(is_strtable)) {
    upb_strtable_setentryvalue(&map->t.strtable, iter, v);
  } else {
    upb_inttable_setentryvalue(&map->t.inttable, iter, v);
  }
}

bool upb_MapIterator_Next(const upb_Map* map, size_t* iter) {
  return _upb_map_next(map, iter);
}

bool upb_MapIterator_Done(const upb_Map* map, size_t iter) {
  UPB_ASSERT(iter != kUpb_Map_Begin);
  if (map->UPB_PRIVATE(is_strtable)) {
    upb_strtable_iter i;
    i.t = &map->t.strtable;
    i.index = iter;
    return upb_strtable_done(&i);
  } else {
    return upb_inttable_done(&map->t.inttable, iter);
  }
}

// Returns the key and value for this entry of the map.
upb_MessageValue upb_MapIterator_Key(const upb_Map* map, size_t iter) {
  upb_MessageValue ret;
  if (map->UPB_PRIVATE(is_strtable)) {
    upb_strtable_iter i;
    i.t = &map->t.strtable;
    i.index = iter;
    _upb_map_fromkey(upb_strtable_iter_key(&i), &ret, map->key_size);
  } else {
    uintptr_t intkey = upb_inttable_iter_key(&map->t.inttable, iter);
    memcpy(&ret, &intkey, map->key_size);
  }
  return ret;
}

upb_MessageValue upb_MapIterator_Value(const upb_Map* map, size_t iter) {
  upb_value v;
  if (map->UPB_PRIVATE(is_strtable)) {
    upb_strtable_iter i;
    i.t = &map->t.strtable;
    i.index = iter;
    v = upb_strtable_iter_value(&i);
  } else {
    v = upb_inttable_iter_value(&map->t.inttable, iter);
  }

  upb_MessageValue ret;
  _upb_map_fromvalue(v, &ret, map->val_size);
  return ret;
}

void upb_Map_Freeze(upb_Map* map, const upb_MiniTable* m) {
  if (upb_Map_IsFrozen(map)) return;
  UPB_PRIVATE(_upb_Map_ShallowFreeze)(map);

  if (m) {
    size_t iter = kUpb_Map_Begin;
    upb_MessageValue key, val;

    while (upb_Map_Next(map, &key, &val, &iter)) {
      upb_Message_Freeze((upb_Message*)val.msg_val, m);
    }
  }
}

// EVERYTHING BELOW THIS LINE IS INTERNAL - DO NOT USE /////////////////////////

upb_Map* _upb_Map_New(upb_Arena* a, size_t key_size, size_t value_size) {
  upb_Map* map = upb_Arena_Malloc(a, sizeof(upb_Map));
  if (!map) return NULL;

  if (key_size <= sizeof(uintptr_t) && key_size != UPB_MAPTYPE_STRING) {
    if (!upb_inttable_init(&map->t.inttable, a)) return NULL;
    map->UPB_PRIVATE(is_strtable) = false;
  } else {
    if (!upb_strtable_init(&map->t.strtable, 4, a)) return NULL;
    map->UPB_PRIVATE(is_strtable) = true;
  }
  map->key_size = key_size;
  map->val_size = value_size;
  map->UPB_PRIVATE(is_frozen) = false;

  return map;
}



// Must be last.

bool upb_Message_SetMapEntry(upb_Map* map, const upb_MiniTable* m,
                             const upb_MiniTableField* f,
                             upb_Message* map_entry_message, upb_Arena* arena) {
  UPB_ASSERT(!upb_Message_IsFrozen(map_entry_message));
  const upb_MiniTable* map_entry_mini_table =
      upb_MiniTable_MapEntrySubMessage(m, f);
  UPB_ASSERT(map_entry_mini_table);
  const upb_MiniTableField* map_entry_key_field =
      upb_MiniTable_MapKey(map_entry_mini_table);
  const upb_MiniTableField* map_entry_value_field =
      upb_MiniTable_MapValue(map_entry_mini_table);
  // Map key/value cannot have explicit defaults,
  // hence assuming a zero default is valid.
  upb_MessageValue default_val = upb_MessageValue_Zero();
  upb_MessageValue map_entry_key =
      upb_Message_GetField(map_entry_message, map_entry_key_field, default_val);
  upb_MessageValue map_entry_value = upb_Message_GetField(
      map_entry_message, map_entry_value_field, default_val);
  return upb_Map_Set(map, map_entry_key, map_entry_value, arena);
}


#include <stdbool.h>
#include <stdint.h>
#include <string.h>


// Must be last.

// Parses unknown data by merging into existing base_message or creating a
// new message usingg mini_table.
static upb_UnknownToMessageRet upb_MiniTable_ParseUnknownMessage(
    const char* unknown_data, size_t unknown_size,
    const upb_MiniTable* mini_table, upb_Message* base_message,
    int decode_options, upb_Arena* arena) {
  upb_UnknownToMessageRet ret;
  ret.message =
      base_message ? base_message : _upb_Message_New(mini_table, arena);
  if (!ret.message) {
    ret.status = kUpb_UnknownToMessage_OutOfMemory;
    return ret;
  }
  // Decode sub message using unknown field contents.
  const char* data = unknown_data;
  uint32_t tag;
  uint64_t message_len = 0;
  data = upb_WireReader_ReadTag(data, &tag, NULL);
  data = upb_WireReader_ReadVarint(data, &message_len, NULL);
  upb_DecodeStatus status = upb_Decode(data, message_len, ret.message,
                                       mini_table, NULL, decode_options, arena);
  if (status == kUpb_DecodeStatus_OutOfMemory) {
    ret.status = kUpb_UnknownToMessage_OutOfMemory;
  } else if (status == kUpb_DecodeStatus_Ok) {
    ret.status = kUpb_UnknownToMessage_Ok;
  } else {
    ret.status = kUpb_UnknownToMessage_ParseError;
  }
  return ret;
}

upb_GetExtension_Status upb_Message_GetOrPromoteExtension(
    upb_Message* msg, const upb_MiniTableExtension* ext_table,
    int decode_options, upb_Arena* arena, upb_MessageValue* value) {
  UPB_ASSERT(!upb_Message_IsFrozen(msg));
  UPB_ASSERT(upb_MiniTableExtension_CType(ext_table) == kUpb_CType_Message);
  const upb_Extension* extension =
      UPB_PRIVATE(_upb_Message_Getext)(msg, ext_table);
  if (extension) {
    memcpy(value, &extension->data, sizeof(upb_MessageValue));
    return kUpb_GetExtension_Ok;
  }

  // Check unknown fields, if available promote.
  int found_count = 0;
  uint32_t field_number = upb_MiniTableExtension_Number(ext_table);
  const upb_MiniTable* extension_table =
      upb_MiniTableExtension_GetSubMessage(ext_table);
  // Will be populated on first parse and then reused
  upb_Message* extension_msg = NULL;
  int depth_limit = 100;
  uintptr_t iter = kUpb_Message_UnknownBegin;
  upb_StringView data;
  while (upb_Message_NextUnknown(msg, &data, &iter)) {
    const char* ptr = data.data;
    upb_EpsCopyInputStream stream;
    upb_EpsCopyInputStream_Init(&stream, &ptr, data.size, true);
    while (!upb_EpsCopyInputStream_IsDone(&stream, &ptr)) {
      uint32_t tag;
      const char* unknown_begin = ptr;
      ptr = upb_WireReader_ReadTag(ptr, &tag, &stream);
      if (!ptr) return kUpb_GetExtension_ParseError;
      if (field_number == upb_WireReader_GetFieldNumber(tag)) {
        found_count++;
        const char* start =
            upb_EpsCopyInputStream_GetAliasedPtr(&stream, unknown_begin);
        ptr = _upb_WireReader_SkipValue(ptr, tag, depth_limit, &stream);
        if (!ptr) return kUpb_GetExtension_ParseError;
        // Because we know that the input is a flat buffer, it is safe to
        // perform pointer arithmetic on aliased pointers.
        size_t len = upb_EpsCopyInputStream_GetAliasedPtr(&stream, ptr) - start;
        upb_UnknownToMessageRet parse_result =
            upb_MiniTable_ParseUnknownMessage(start, len, extension_table,
                                              /* base_message= */ extension_msg,
                                              decode_options, arena);
        switch (parse_result.status) {
          case kUpb_UnknownToMessage_OutOfMemory:
            return kUpb_GetExtension_OutOfMemory;
          case kUpb_UnknownToMessage_ParseError:
            return kUpb_GetExtension_ParseError;
          case kUpb_UnknownToMessage_NotFound:
            return kUpb_GetExtension_NotPresent;
          case kUpb_UnknownToMessage_Ok:
            extension_msg = parse_result.message;
        }
      } else {
        ptr = _upb_WireReader_SkipValue(ptr, tag, depth_limit, &stream);
        if (!ptr) return kUpb_GetExtension_ParseError;
      }
    }
  }
  if (!extension_msg) {
    return kUpb_GetExtension_NotPresent;
  }

  upb_Extension* ext =
      UPB_PRIVATE(_upb_Message_GetOrCreateExtension)(msg, ext_table, arena);
  if (!ext) {
    return kUpb_GetExtension_OutOfMemory;
  }
  ext->data.msg_val = extension_msg;

  while (found_count > 0) {
    upb_FindUnknownRet found = upb_Message_FindUnknown(msg, field_number, 0);
    UPB_ASSERT(found.status == kUpb_FindUnknown_Ok);
    upb_StringView view = {.data = found.ptr, .size = found.len};
    if (upb_Message_DeleteUnknown(msg, &view, &found.iter, arena) ==
        kUpb_DeleteUnknown_AllocFail) {
      return kUpb_GetExtension_OutOfMemory;
    }
    found_count--;
  }
  value->msg_val = extension_msg;
  return kUpb_GetExtension_Ok;
}

static upb_FindUnknownRet upb_FindUnknownRet_ParseError(void) {
  return (upb_FindUnknownRet){.status = kUpb_FindUnknown_ParseError};
}

upb_FindUnknownRet upb_Message_FindUnknown(const upb_Message* msg,
                                           uint32_t field_number,
                                           int depth_limit) {
  depth_limit = depth_limit ? depth_limit : 100;
  upb_FindUnknownRet ret;
  ret.iter = kUpb_Message_UnknownBegin;
  upb_StringView data;
  while (upb_Message_NextUnknown(msg, &data, &ret.iter)) {
    upb_EpsCopyInputStream stream;
    const char* ptr = data.data;
    upb_EpsCopyInputStream_Init(&stream, &ptr, data.size, true);

    while (!upb_EpsCopyInputStream_IsDone(&stream, &ptr)) {
      uint32_t tag;
      const char* unknown_begin = ptr;
      ptr = upb_WireReader_ReadTag(ptr, &tag, &stream);
      if (!ptr) return upb_FindUnknownRet_ParseError();
      if (field_number == upb_WireReader_GetFieldNumber(tag)) {
        ret.status = kUpb_FindUnknown_Ok;
        ret.ptr = upb_EpsCopyInputStream_GetAliasedPtr(&stream, unknown_begin);
        ptr = _upb_WireReader_SkipValue(ptr, tag, depth_limit, &stream);
        // Because we know that the input is a flat buffer, it is safe to
        // perform pointer arithmetic on aliased pointers.
        ret.len = upb_EpsCopyInputStream_GetAliasedPtr(&stream, ptr) - ret.ptr;
        return ret;
      }

      ptr = _upb_WireReader_SkipValue(ptr, tag, depth_limit, &stream);
      if (!ptr) return upb_FindUnknownRet_ParseError();
    }
  }
  ret.status = kUpb_FindUnknown_NotPresent;
  ret.ptr = NULL;
  ret.len = 0;
  ret.iter = kUpb_Message_UnknownBegin;
  return ret;
}

static upb_DecodeStatus upb_Message_PromoteOne(upb_TaggedMessagePtr* tagged,
                                               const upb_MiniTable* mini_table,
                                               int decode_options,
                                               upb_Arena* arena) {
  upb_Message* empty =
      UPB_PRIVATE(_upb_TaggedMessagePtr_GetEmptyMessage)(*tagged);
  upb_Message* promoted = upb_Message_New(mini_table, arena);
  if (!promoted) return kUpb_DecodeStatus_OutOfMemory;
  upb_StringView unknown_data;
  uintptr_t iter = kUpb_Message_UnknownBegin;
  while (upb_Message_NextUnknown(empty, &unknown_data, &iter)) {
    upb_DecodeStatus status =
        upb_Decode(unknown_data.data, unknown_data.size, promoted, mini_table,
                   NULL, decode_options, arena);
    if (status != kUpb_DecodeStatus_Ok) {
      return status;
    }
  }
  *tagged = UPB_PRIVATE(_upb_TaggedMessagePtr_Pack)(promoted, false);
  return kUpb_DecodeStatus_Ok;
}

upb_DecodeStatus upb_Message_PromoteMessage(upb_Message* parent,
                                            const upb_MiniTable* mini_table,
                                            const upb_MiniTableField* field,
                                            int decode_options,
                                            upb_Arena* arena,
                                            upb_Message** promoted) {
  UPB_ASSERT(!upb_Message_IsFrozen(parent));
  const upb_MiniTable* sub_table =
      upb_MiniTable_GetSubMessageTable(mini_table, field);
  UPB_ASSERT(sub_table);
  upb_TaggedMessagePtr tagged =
      upb_Message_GetTaggedMessagePtr(parent, field, NULL);
  upb_DecodeStatus ret =
      upb_Message_PromoteOne(&tagged, sub_table, decode_options, arena);
  if (ret == kUpb_DecodeStatus_Ok) {
    *promoted = upb_TaggedMessagePtr_GetNonEmptyMessage(tagged);
    upb_Message_SetMessage(parent, field, *promoted);
  }
  return ret;
}

upb_DecodeStatus upb_Array_PromoteMessages(upb_Array* arr,
                                           const upb_MiniTable* mini_table,
                                           int decode_options,
                                           upb_Arena* arena) {
  void** data = upb_Array_MutableDataPtr(arr);
  size_t size = upb_Array_Size(arr);
  for (size_t i = 0; i < size; i++) {
    upb_TaggedMessagePtr tagged;
    memcpy(&tagged, &data[i], sizeof(tagged));
    if (!upb_TaggedMessagePtr_IsEmpty(tagged)) continue;
    upb_DecodeStatus status =
        upb_Message_PromoteOne(&tagged, mini_table, decode_options, arena);
    if (status != kUpb_DecodeStatus_Ok) return status;
    memcpy(&data[i], &tagged, sizeof(tagged));
  }
  return kUpb_DecodeStatus_Ok;
}

upb_DecodeStatus upb_Map_PromoteMessages(upb_Map* map,
                                         const upb_MiniTable* mini_table,
                                         int decode_options, upb_Arena* arena) {
  size_t iter = kUpb_Map_Begin;
  upb_MessageValue key, val;
  while (upb_Map_Next(map, &key, &val, &iter)) {
    if (!upb_TaggedMessagePtr_IsEmpty(val.tagged_msg_val)) continue;
    upb_DecodeStatus status = upb_Message_PromoteOne(
        &val.tagged_msg_val, mini_table, decode_options, arena);
    if (status != kUpb_DecodeStatus_Ok) return status;
    upb_Map_SetEntryValue(map, iter, val);
  }
  return kUpb_DecodeStatus_Ok;
}

////////////////////////////////////////////////////////////////////////////////
// OLD promotion functions, will be removed!
////////////////////////////////////////////////////////////////////////////////

// Warning: See TODO
upb_UnknownToMessageRet upb_MiniTable_PromoteUnknownToMessage(
    upb_Message* msg, const upb_MiniTable* mini_table,
    const upb_MiniTableField* field, const upb_MiniTable* sub_mini_table,
    int decode_options, upb_Arena* arena) {
  UPB_ASSERT(!upb_Message_IsFrozen(msg));
  upb_FindUnknownRet unknown;
  // We need to loop and merge unknowns that have matching tag field->number.
  upb_Message* message = NULL;
  // Callers should check that message is not set first before calling
  // PromotoUnknownToMessage.
  UPB_ASSERT(upb_MiniTable_GetSubMessageTable(mini_table, field) ==
             sub_mini_table);
  bool is_oneof = upb_MiniTableField_IsInOneof(field);
  if (!is_oneof || UPB_PRIVATE(_upb_Message_GetOneofCase)(msg, field) ==
                       upb_MiniTableField_Number(field)) {
    UPB_ASSERT(upb_Message_GetMessage(msg, field) == NULL);
  }
  upb_UnknownToMessageRet ret;
  ret.status = kUpb_UnknownToMessage_Ok;
  do {
    unknown = upb_Message_FindUnknown(
        msg, upb_MiniTableField_Number(field),
        upb_DecodeOptions_GetEffectiveMaxDepth(decode_options));
    switch (unknown.status) {
      case kUpb_FindUnknown_Ok: {
        const char* unknown_data = unknown.ptr;
        size_t unknown_size = unknown.len;
        ret = upb_MiniTable_ParseUnknownMessage(unknown_data, unknown_size,
                                                sub_mini_table, message,
                                                decode_options, arena);
        if (ret.status == kUpb_UnknownToMessage_Ok) {
          message = ret.message;
          upb_StringView del =
              upb_StringView_FromDataAndSize(unknown_data, unknown_size);
          upb_Message_DeleteUnknown(msg, &del, &(unknown.iter), arena);
        }
      } break;
      case kUpb_FindUnknown_ParseError:
        ret.status = kUpb_UnknownToMessage_ParseError;
        break;
      case kUpb_FindUnknown_NotPresent:
        // If we parsed at least one unknown, we are done.
        ret.status =
            message ? kUpb_UnknownToMessage_Ok : kUpb_UnknownToMessage_NotFound;
        break;
    }
  } while (unknown.status == kUpb_FindUnknown_Ok);
  if (message) {
    if (is_oneof) {
      UPB_PRIVATE(_upb_Message_SetOneofCase)(msg, field);
    }
    upb_Message_SetMessage(msg, field, message);
    ret.message = message;
  }
  return ret;
}

// Moves repeated messages in unknowns to a upb_Array.
//
// Since the repeated field is not a scalar type we don't check for
// kUpb_LabelFlags_IsPacked.
// TODO: Optimize. Instead of converting messages one at a time,
// scan all unknown data once and compact.
upb_UnknownToMessage_Status upb_MiniTable_PromoteUnknownToMessageArray(
    upb_Message* msg, const upb_MiniTableField* field,
    const upb_MiniTable* mini_table, int decode_options, upb_Arena* arena) {
  UPB_ASSERT(!upb_Message_IsFrozen(msg));

  upb_Array* repeated_messages = upb_Message_GetMutableArray(msg, field);
  // Find all unknowns with given field number and parse.
  upb_FindUnknownRet unknown;
  do {
    unknown = upb_Message_FindUnknown(
        msg, upb_MiniTableField_Number(field),
        upb_DecodeOptions_GetEffectiveMaxDepth(decode_options));
    if (unknown.status == kUpb_FindUnknown_Ok) {
      upb_UnknownToMessageRet ret = upb_MiniTable_ParseUnknownMessage(
          unknown.ptr, unknown.len, mini_table,
          /* base_message= */ NULL, decode_options, arena);
      if (ret.status == kUpb_UnknownToMessage_Ok) {
        upb_MessageValue value;
        value.msg_val = ret.message;
        // Allocate array on demand before append.
        if (!repeated_messages) {
          upb_Message_ResizeArrayUninitialized(msg, field, 0, arena);
          repeated_messages = upb_Message_GetMutableArray(msg, field);
        }
        if (!upb_Array_Append(repeated_messages, value, arena)) {
          return kUpb_UnknownToMessage_OutOfMemory;
        }
        upb_StringView del =
            upb_StringView_FromDataAndSize(unknown.ptr, unknown.len);
        upb_Message_DeleteUnknown(msg, &del, &unknown.iter, arena);
      } else {
        return ret.status;
      }
    }
  } while (unknown.status == kUpb_FindUnknown_Ok);
  return kUpb_UnknownToMessage_Ok;
}

// Moves repeated messages in unknowns to a upb_Map.
upb_UnknownToMessage_Status upb_MiniTable_PromoteUnknownToMap(
    upb_Message* msg, const upb_MiniTable* mini_table,
    const upb_MiniTableField* field, int decode_options, upb_Arena* arena) {
  UPB_ASSERT(!upb_Message_IsFrozen(msg));

  const upb_MiniTable* map_entry_mini_table =
      upb_MiniTable_MapEntrySubMessage(mini_table, field);
  UPB_ASSERT(upb_MiniTable_FieldCount(map_entry_mini_table) == 2);
  // Find all unknowns with given field number and parse.
  upb_FindUnknownRet unknown;
  while (1) {
    unknown = upb_Message_FindUnknown(
        msg, upb_MiniTableField_Number(field),
        upb_DecodeOptions_GetEffectiveMaxDepth(decode_options));
    if (unknown.status != kUpb_FindUnknown_Ok) break;
    upb_UnknownToMessageRet ret = upb_MiniTable_ParseUnknownMessage(
        unknown.ptr, unknown.len, map_entry_mini_table,
        /* base_message= */ NULL, decode_options, arena);
    if (ret.status != kUpb_UnknownToMessage_Ok) return ret.status;
    // Allocate map on demand before append.
    upb_Map* map = upb_Message_GetOrCreateMutableMap(msg, map_entry_mini_table,
                                                     field, arena);
    upb_Message* map_entry_message = ret.message;
    bool insert_success = upb_Message_SetMapEntry(map, mini_table, field,
                                                  map_entry_message, arena);
    if (!insert_success) return kUpb_UnknownToMessage_OutOfMemory;
    upb_StringView del =
        upb_StringView_FromDataAndSize(unknown.ptr, unknown.len);
    upb_Message_DeleteUnknown(msg, &del, &unknown.iter, arena);
  }
  return kUpb_UnknownToMessage_Ok;
}

const char* upb_FindUnknownStatus_String(upb_FindUnknown_Status status) {
  switch (status) {
    case kUpb_FindUnknown_Ok:
      return "Ok";
    case kUpb_FindUnknown_ParseError:
      return "Parse error";
    case kUpb_FindUnknown_NotPresent:
      return "Field not found";
    default:
      return "Unknown status";
  }
}


#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>


// Must be last.

upb_Message* upb_Message_New(const upb_MiniTable* m, upb_Arena* a) {
  return _upb_Message_New(m, a);
}

UPB_NOINLINE bool UPB_PRIVATE(_upb_Message_AddUnknownSlowPath)(upb_Message* msg,
                                                               const char* data,
                                                               size_t len,
                                                               upb_Arena* arena,
                                                               bool alias) {
  {
    upb_Message_Internal* in = UPB_PRIVATE(_upb_Message_GetInternal)(msg);
    // Alias fast path was already checked in the inline function that calls
    // this one
    if (!alias && in && in->size) {
      upb_TaggedAuxPtr ptr = in->aux_data[in->size - 1];
      if (upb_TaggedAuxPtr_IsUnknown(ptr)) {
        upb_StringView* existing = upb_TaggedAuxPtr_UnknownData(ptr);
        if (!upb_TaggedAuxPtr_IsUnknownAliased(ptr)) {
          // If part of the existing field was deleted at the beginning, we can
          // reconstruct it by comparing the address of the end with the address
          // of the entry itself; having the non-aliased tag means that the
          // string_view and the data it points to are part of the same original
          // upb_Arena_Malloc allocation, and the end of the string view
          // represents the end of that allocation.
          size_t prev_alloc_size =
              (existing->data + existing->size) - (char*)existing;
          if (SIZE_MAX - prev_alloc_size >= len) {
            size_t new_alloc_size = prev_alloc_size + len;
            if (upb_Arena_TryExtend(arena, existing, prev_alloc_size,
                                    new_alloc_size)) {
              memcpy(UPB_PTR_AT(existing, prev_alloc_size, void), data, len);
              existing->size += len;
              return true;
            }
          }
        }
      }
    }
  }
  // TODO: b/376969853  - Add debug check that the unknown field is an overall
  // valid proto field
  if (!UPB_PRIVATE(_upb_Message_ReserveSlot)(msg, arena)) {
    return false;
  }
  upb_StringView* view;
  if (alias) {
    view = upb_Arena_Malloc(arena, sizeof(upb_StringView));
    if (!view) return false;
    view->data = data;
  } else {
    view = upb_Arena_Malloc(arena, sizeof(upb_StringView) + len);
    if (!view) return false;
    char* copy = UPB_PTR_AT(view, sizeof(upb_StringView), char);
    memcpy(copy, data, len);
    view->data = copy;
  }
  view->size = len;
  upb_Message_Internal* in = UPB_PRIVATE(_upb_Message_GetInternal)(msg);
  in->aux_data[in->size++] = alias
                                 ? upb_TaggedAuxPtr_MakeUnknownDataAliased(view)
                                 : upb_TaggedAuxPtr_MakeUnknownData(view);
  return true;
}

bool UPB_PRIVATE(_upb_Message_AddUnknownV)(struct upb_Message* msg,
                                           upb_Arena* arena,
                                           upb_StringView data[],
                                           size_t count) {
  UPB_ASSERT(!upb_Message_IsFrozen(msg));
  UPB_ASSERT(count > 0);
  size_t total_len = 0;
  for (size_t i = 0; i < count; i++) {
    if (SIZE_MAX - total_len < data[i].size) {
      return false;
    }
    total_len += data[i].size;
  }

  {
    upb_Message_Internal* in = UPB_PRIVATE(_upb_Message_GetInternal)(msg);
    if (in && in->size) {
      upb_TaggedAuxPtr ptr = in->aux_data[in->size - 1];
      if (upb_TaggedAuxPtr_IsUnknown(ptr)) {
        upb_StringView* existing = upb_TaggedAuxPtr_UnknownData(ptr);
        if (!upb_TaggedAuxPtr_IsUnknownAliased(ptr)) {
          size_t prev_alloc_size =
              (existing->data + existing->size) - (char*)existing;
          if (SIZE_MAX - prev_alloc_size >= total_len) {
            size_t new_alloc_size = prev_alloc_size + total_len;
            if (upb_Arena_TryExtend(arena, existing, prev_alloc_size,
                                    new_alloc_size)) {
              char* copy = UPB_PTR_AT(existing, prev_alloc_size, char);
              for (size_t i = 0; i < count; i++) {
                memcpy(copy, data[i].data, data[i].size);
                copy += data[i].size;
              }
              existing->size += total_len;
              return true;
            }
          }
        }
      }
    }
  }

  if (SIZE_MAX - sizeof(upb_StringView) < total_len) return false;
  if (!UPB_PRIVATE(_upb_Message_ReserveSlot)(msg, arena)) return false;

  upb_StringView* view =
      upb_Arena_Malloc(arena, sizeof(upb_StringView) + total_len);
  if (!view) return false;
  char* copy = UPB_PTR_AT(view, sizeof(upb_StringView), char);
  view->data = copy;
  view->size = total_len;
  for (size_t i = 0; i < count; i++) {
    memcpy(copy, data[i].data, data[i].size);
    copy += data[i].size;
  }
  // TODO: b/376969853  - Add debug check that the unknown field is an overall
  // valid proto field
  upb_Message_Internal* in = UPB_PRIVATE(_upb_Message_GetInternal)(msg);
  in->aux_data[in->size++] = upb_TaggedAuxPtr_MakeUnknownData(view);
  return true;
}

void _upb_Message_DiscardUnknown_shallow(upb_Message* msg) {
  UPB_ASSERT(!upb_Message_IsFrozen(msg));
  upb_Message_Internal* in = UPB_PRIVATE(_upb_Message_GetInternal)(msg);
  if (!in) return;
  uint32_t size = 0;
  for (uint32_t i = 0; i < in->size; i++) {
    upb_TaggedAuxPtr tagged_ptr = in->aux_data[i];
    if (upb_TaggedAuxPtr_IsExtension(tagged_ptr)) {
      in->aux_data[size++] = tagged_ptr;
    }
  }
  in->size = size;
}

upb_Message_DeleteUnknownStatus upb_Message_DeleteUnknown(upb_Message* msg,
                                                          upb_StringView* data,
                                                          uintptr_t* iter,
                                                          upb_Arena* arena) {
  UPB_ASSERT(!upb_Message_IsFrozen(msg));
  UPB_ASSERT(*iter != kUpb_Message_UnknownBegin);
  upb_Message_Internal* in = UPB_PRIVATE(_upb_Message_GetInternal)(msg);
  UPB_ASSERT(in);
  UPB_ASSERT(*iter <= in->size);
  upb_TaggedAuxPtr unknown_ptr = in->aux_data[*iter - 1];
  UPB_ASSERT(upb_TaggedAuxPtr_IsUnknown(unknown_ptr));
  upb_StringView* unknown = upb_TaggedAuxPtr_UnknownData(unknown_ptr);
  if (unknown->data == data->data && unknown->size == data->size) {
    // Remove whole field
    in->aux_data[*iter - 1] = upb_TaggedAuxPtr_Null();
  } else if (unknown->data == data->data) {
    // Strip prefix
    unknown->data += data->size;
    unknown->size -= data->size;
    *data = *unknown;
    return kUpb_DeleteUnknown_IterUpdated;
  } else if (unknown->data + unknown->size == data->data + data->size) {
    // Truncate existing field
    unknown->size -= data->size;
    if (!upb_TaggedAuxPtr_IsUnknownAliased(unknown_ptr)) {
      in->aux_data[*iter - 1] =
          upb_TaggedAuxPtr_MakeUnknownDataAliased(unknown);
    }
  } else {
    UPB_ASSERT(unknown->data < data->data &&
               unknown->data + unknown->size > data->data + data->size);
    // Split in the middle
    upb_StringView* prefix = unknown;
    upb_StringView* suffix = upb_Arena_Malloc(arena, sizeof(upb_StringView));
    if (!suffix) {
      return kUpb_DeleteUnknown_AllocFail;
    }
    if (!UPB_PRIVATE(_upb_Message_ReserveSlot)(msg, arena)) {
      return kUpb_DeleteUnknown_AllocFail;
    }
    in = UPB_PRIVATE(_upb_Message_GetInternal)(msg);
    if (*iter != in->size) {
      // Shift later entries down so that unknown field ordering is preserved
      memmove(&in->aux_data[*iter + 1], &in->aux_data[*iter],
              sizeof(upb_TaggedAuxPtr) * (in->size - *iter));
    }
    in->aux_data[*iter] = upb_TaggedAuxPtr_MakeUnknownDataAliased(suffix);
    if (!upb_TaggedAuxPtr_IsUnknownAliased(unknown_ptr)) {
      in->aux_data[*iter - 1] = upb_TaggedAuxPtr_MakeUnknownDataAliased(prefix);
    }
    in->size++;
    suffix->data = data->data + data->size;
    suffix->size = (prefix->data + prefix->size) - suffix->data;
    prefix->size = data->data - prefix->data;
  }
  return upb_Message_NextUnknown(msg, data, iter)
             ? kUpb_DeleteUnknown_IterUpdated
             : kUpb_DeleteUnknown_DeletedLast;
}

size_t upb_Message_ExtensionCount(const upb_Message* msg) {
  upb_Message_Internal* in = UPB_PRIVATE(_upb_Message_GetInternal)(msg);
  if (!in) return 0;
  const upb_MiniTableExtension* ext;
  upb_MessageValue val;
  uintptr_t iter = kUpb_Message_ExtensionBegin;
  size_t count = 0;
  while (upb_Message_NextExtension(msg, &ext, &val, &iter)) {
    count++;
  }
  return count;
}

void upb_Message_Freeze(upb_Message* msg, const upb_MiniTable* m) {
  if (upb_Message_IsFrozen(msg)) return;
  UPB_PRIVATE(_upb_Message_ShallowFreeze)(msg);

  // Base Fields.
  const size_t field_count = upb_MiniTable_FieldCount(m);

  for (size_t i = 0; i < field_count; i++) {
    const upb_MiniTableField* f = upb_MiniTable_GetFieldByIndex(m, i);
    const upb_MiniTable* m2 = upb_MiniTable_SubMessage(m, f);

    switch (UPB_PRIVATE(_upb_MiniTableField_Mode)(f)) {
      case kUpb_FieldMode_Array: {
        upb_Array* arr = upb_Message_GetMutableArray(msg, f);
        if (arr) upb_Array_Freeze(arr, m2);
        break;
      }
      case kUpb_FieldMode_Map: {
        upb_Map* map = upb_Message_GetMutableMap(msg, f);
        if (map) {
          const upb_MiniTableField* f2 = upb_MiniTable_MapValue(m2);
          const upb_MiniTable* m3 = upb_MiniTable_SubMessage(m2, f2);
          upb_Map_Freeze(map, m3);
        }
        break;
      }
      case kUpb_FieldMode_Scalar: {
        if (m2) {
          upb_Message* msg2 = upb_Message_GetMutableMessage(msg, f);
          if (msg2) upb_Message_Freeze(msg2, m2);
        }
        break;
      }
    }
  }

  // Extensions.
  upb_Message_Internal* in = UPB_PRIVATE(_upb_Message_GetInternal)(msg);
  // TODO: b/376969853 - use iterator API
  uint32_t size = in ? in->size : 0;
  for (size_t i = 0; i < size; i++) {
    upb_TaggedAuxPtr tagged_ptr = in->aux_data[i];
    if (!upb_TaggedAuxPtr_IsExtension(tagged_ptr)) {
      continue;
    }
    const upb_Extension* ext = upb_TaggedAuxPtr_Extension(tagged_ptr);
    const upb_MiniTableExtension* e = ext->ext;
    const upb_MiniTableField* f = &e->UPB_PRIVATE(field);
    const upb_MiniTable* m2 = upb_MiniTableExtension_GetSubMessage(e);

    upb_MessageValue val;
    memcpy(&val, &(ext->data), sizeof(upb_MessageValue));

    switch (UPB_PRIVATE(_upb_MiniTableField_Mode)(f)) {
      case kUpb_FieldMode_Array: {
        upb_Array* arr = (upb_Array*)val.array_val;
        if (arr) upb_Array_Freeze(arr, m2);
        break;
      }
      case kUpb_FieldMode_Map:
        UPB_UNREACHABLE();  // Maps cannot be extensions.
        break;
      case kUpb_FieldMode_Scalar:
        if (upb_MiniTableField_IsSubMessage(f)) {
          upb_Message* msg2 = (upb_Message*)val.msg_val;
          if (msg2) upb_Message_Freeze(msg2, m2);
        }
        break;
    }
  }
}

#include "stddef.h"

// Must be last.

bool upb_Message_MergeFrom(upb_Message* dst, const upb_Message* src,
                           const upb_MiniTable* mt,
                           const upb_ExtensionRegistry* extreg,
                           upb_Arena* arena) {
  char* buf = NULL;
  size_t size = 0;
  // This tmp arena is used to hold the bytes for `src` serialized. This bends
  // the typical "no hidden allocations" design of upb, but under a properly
  // optimized implementation this extra allocation would not be necessary and
  // so we don't want to unnecessarily have the bad API or bloat the passed-in
  // arena with this very-short-term allocation.
  upb_Arena* encode_arena = upb_Arena_New();
  upb_EncodeStatus e_status = upb_Encode(src, mt, 0, encode_arena, &buf, &size);
  if (e_status != kUpb_EncodeStatus_Ok) {
    upb_Arena_Free(encode_arena);
    return false;
  }
  upb_DecodeStatus d_status = upb_Decode(buf, size, dst, mt, extreg, 0, arena);
  if (d_status != kUpb_DecodeStatus_Ok) {
    upb_Arena_Free(encode_arena);
    return false;
  }
  upb_Arena_Free(encode_arena);
  return true;
}


#include <stddef.h>
#include <stdint.h>
#include <string.h>


// Must be last.

bool upb_MiniTable_SetSubMessage(upb_MiniTable* table,
                                 upb_MiniTableField* field,
                                 const upb_MiniTable* sub) {
  UPB_ASSERT((uintptr_t)table->UPB_PRIVATE(fields) <= (uintptr_t)field &&
             (uintptr_t)field < (uintptr_t)(table->UPB_PRIVATE(fields) +
                                            table->UPB_PRIVATE(field_count)));
  UPB_ASSERT(sub);

  const bool sub_is_map = sub->UPB_PRIVATE(ext) & kUpb_ExtMode_IsMapEntry;

  switch (field->UPB_PRIVATE(descriptortype)) {
    case kUpb_FieldType_Message:
      if (sub_is_map) {
        const bool table_is_map =
            table->UPB_PRIVATE(ext) & kUpb_ExtMode_IsMapEntry;
        if (UPB_UNLIKELY(table_is_map)) return false;

        field->UPB_PRIVATE(mode) =
            (field->UPB_PRIVATE(mode) & ~kUpb_FieldMode_Mask) |
            kUpb_FieldMode_Map;
      }
      break;

    case kUpb_FieldType_Group:
      if (UPB_UNLIKELY(sub_is_map)) return false;
      break;

    default:
      return false;
  }

  int idx = field->UPB_PRIVATE(submsg_index);
  upb_MiniTableSubInternal* table_subs = (void*)table->UPB_PRIVATE(subs);
  // TODO: Add this assert back once YouTube is updated to not call
  // this function repeatedly.
  // UPB_ASSERT(UPB_PRIVATE(_upb_MiniTable_IsEmpty)(table_sub->submsg));
  memcpy((void*)table_subs[idx].UPB_PRIVATE(submsg), &sub, sizeof(void*));
  return true;
}

bool upb_MiniTable_SetSubEnum(upb_MiniTable* table, upb_MiniTableField* field,
                              const upb_MiniTableEnum* sub) {
  UPB_ASSERT((uintptr_t)table->UPB_PRIVATE(fields) <= (uintptr_t)field &&
             (uintptr_t)field < (uintptr_t)(table->UPB_PRIVATE(fields) +
                                            table->UPB_PRIVATE(field_count)));
  UPB_ASSERT(sub);

  if (field->UPB_PRIVATE(descriptortype) != kUpb_FieldType_Enum) {
    return false;
  }

  if ((table->UPB_PRIVATE(ext) & kUpb_ExtMode_IsMapEntry) &&
      !upb_MiniTableEnum_CheckValue(sub, 0)) {
    // An enum used in a map must include 0 as a value.  This matches a check
    // performed in protoc ("Enum value in map must define 0 as the first
    // value").  Protoc should ensure that we never get here.
    //
    // This ends up being important if we receive wire messages where a map
    // entry omits the value (and thus defaults to 0).
    return false;
  }

  upb_MiniTableSub* table_sub =
      (void*)&table->UPB_PRIVATE(subs)[field->UPB_PRIVATE(submsg_index)];
  *table_sub = upb_MiniTableSub_FromEnum(sub);
  return true;
}

uint32_t upb_MiniTable_GetSubList(const upb_MiniTable* m,
                                  const upb_MiniTableField** subs) {
  uint32_t msg_count = 0;
  uint32_t enum_count = 0;

  for (int i = 0; i < upb_MiniTable_FieldCount(m); i++) {
    const upb_MiniTableField* f = upb_MiniTable_GetFieldByIndex(m, i);
    if (upb_MiniTableField_CType(f) == kUpb_CType_Message) {
      *subs = f;
      ++subs;
      msg_count++;
    }
  }

  for (int i = 0; i < upb_MiniTable_FieldCount(m); i++) {
    const upb_MiniTableField* f = upb_MiniTable_GetFieldByIndex(m, i);
    if (upb_MiniTableField_IsClosedEnum(f)) {
      *subs = f;
      ++subs;
      enum_count++;
    }
  }

  return (msg_count << 16) | enum_count;
}

// The list of sub_tables and sub_enums must exactly match the number and order
// of sub-message fields and sub-enum fields given by upb_MiniTable_GetSubList()
// above.
bool upb_MiniTable_Link(upb_MiniTable* m, const upb_MiniTable** sub_tables,
                        size_t sub_table_count,
                        const upb_MiniTableEnum** sub_enums,
                        size_t sub_enum_count) {
  uint32_t msg_count = 0;
  uint32_t enum_count = 0;

  for (int i = 0; i < upb_MiniTable_FieldCount(m); i++) {
    upb_MiniTableField* f =
        (upb_MiniTableField*)upb_MiniTable_GetFieldByIndex(m, i);
    if (upb_MiniTableField_CType(f) == kUpb_CType_Message) {
      const upb_MiniTable* sub = sub_tables[msg_count++];
      if (msg_count > sub_table_count) return false;
      if (sub && !upb_MiniTable_SetSubMessage(m, f, sub)) return false;
    }
  }

  for (int i = 0; i < upb_MiniTable_FieldCount(m); i++) {
    upb_MiniTableField* f =
        (upb_MiniTableField*)upb_MiniTable_GetFieldByIndex(m, i);
    if (upb_MiniTableField_IsClosedEnum(f)) {
      const upb_MiniTableEnum* sub = sub_enums[enum_count++];
      if (enum_count > sub_enum_count) return false;
      if (sub && !upb_MiniTable_SetSubEnum(m, f, sub)) return false;
    }
  }

  return (msg_count == sub_table_count) && (enum_count == sub_enum_count);
}


#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>


// Our awkward dance for including fasttable only when it is enabled.
#if UPB_FASTTABLE
#define UPB_INCLUDE_FAST_DECODE
#endif

#ifdef UPB_INCLUDE_FAST_DECODE
#endif

#undef UPB_INCLUDE_FAST_DECODE

// Must be last.

// We reserve unused hasbits to make room for upb_Message fields.
#define kUpb_Reserved_Hasbytes sizeof(struct upb_Message)

// 64 is the first hasbit that we currently use.
#define kUpb_Reserved_Hasbits (kUpb_Reserved_Hasbytes * 8)

#define kUpb_OneOfLayoutItem_IndexSentinel ((uint16_t)-1)

// Stores the field number of the present value of the oneof
#define kUpb_OneOf_CaseFieldRep (kUpb_FieldRep_4Byte)

// The maximum field number that can be encoded on the wire.
// Note that this limit does not apply to MessageSet, which can have field
// numbers up to INT32_MAX.
#define kUpb_MaxFieldNumber ((1 << 29) - 1)

typedef struct {
  // Index of the corresponding field. The field's offset will be the index of
  // the next field in a linked list.
  uint16_t field_index;
  // This enum is stored in bytes to avoid trailing padding while preserving
  // two-byte alignment.
  uint8_t /* upb_FieldRep*/ rep;
} upb_OneOfLayoutItem;

typedef struct {
  upb_OneOfLayoutItem* data;
  size_t size;
  size_t buf_capacity_bytes;
} upb_OneOfLayoutItemVector;

typedef struct {
  upb_MdDecoder base;
  upb_MiniTableField* fields;
  upb_MiniTablePlatform platform;
  upb_OneOfLayoutItemVector oneofs;
  upb_Arena* arena;
  // Initially tracks the count of each field rep type; then, during assignment,
  // tracks the base offset for the next processed field of the given rep.
  uint16_t rep_counts_offsets[kUpb_FieldRep_Max + 1];
  bool is_extension;

  // When building fasttables, we don't know the total size of the table until
  // we're done decoding, so we allocate a temporary table on the stack and
  // allocate the real thing from the arena later.
  upb_MiniTable table;
} upb_MtDecoder;

// In each field's offset, we temporarily store a presence classifier:
enum PresenceClass {
  kNoPresence = 0,
  kHasbitPresence = 1,
  kRequiredPresence = 2,
  kOneofBase = 3,
  // Negative values refer to a specific oneof with that number.  Positive
  // values >= kOneofBase indicate that this field is in a oneof, and specify
  // the next field in this oneof's linked list.
};

static bool upb_MtDecoder_FieldIsPackable(upb_MiniTableField* field) {
  return (field->UPB_PRIVATE(mode) & kUpb_FieldMode_Array) &&
         upb_FieldType_IsPackable(field->UPB_PRIVATE(descriptortype));
}

typedef struct {
  uint16_t submsg_count;
  uint16_t subenum_count;
} upb_SubCounts;

static void upb_MiniTable_SetTypeAndSub(upb_MiniTableField* field,
                                        upb_FieldType type,
                                        upb_SubCounts* sub_counts,
                                        uint64_t msg_modifiers,
                                        bool is_proto3_enum) {
  if (is_proto3_enum) {
    UPB_ASSERT(type == kUpb_FieldType_Enum);
    type = kUpb_FieldType_Int32;
    field->UPB_PRIVATE(mode) |= kUpb_LabelFlags_IsAlternate;
  } else if (type == kUpb_FieldType_String &&
             !(msg_modifiers & kUpb_MessageModifier_ValidateUtf8)) {
    type = kUpb_FieldType_Bytes;
    field->UPB_PRIVATE(mode) |= kUpb_LabelFlags_IsAlternate;
  }

  field->UPB_PRIVATE(descriptortype) = type;

  if (upb_MtDecoder_FieldIsPackable(field) &&
      (msg_modifiers & kUpb_MessageModifier_DefaultIsPacked)) {
    field->UPB_PRIVATE(mode) |= kUpb_LabelFlags_IsPacked;
  }

  if (type == kUpb_FieldType_Message || type == kUpb_FieldType_Group) {
    field->UPB_PRIVATE(submsg_index) = sub_counts->submsg_count++;
  } else if (type == kUpb_FieldType_Enum) {
    // We will need to update this later once we know the total number of
    // submsg fields.
    field->UPB_PRIVATE(submsg_index) = sub_counts->subenum_count++;
  } else {
    field->UPB_PRIVATE(submsg_index) = kUpb_NoSub;
  }
}

static const char kUpb_EncodedToType[] = {
    [kUpb_EncodedType_Double] = kUpb_FieldType_Double,
    [kUpb_EncodedType_Float] = kUpb_FieldType_Float,
    [kUpb_EncodedType_Int64] = kUpb_FieldType_Int64,
    [kUpb_EncodedType_UInt64] = kUpb_FieldType_UInt64,
    [kUpb_EncodedType_Int32] = kUpb_FieldType_Int32,
    [kUpb_EncodedType_Fixed64] = kUpb_FieldType_Fixed64,
    [kUpb_EncodedType_Fixed32] = kUpb_FieldType_Fixed32,
    [kUpb_EncodedType_Bool] = kUpb_FieldType_Bool,
    [kUpb_EncodedType_String] = kUpb_FieldType_String,
    [kUpb_EncodedType_Group] = kUpb_FieldType_Group,
    [kUpb_EncodedType_Message] = kUpb_FieldType_Message,
    [kUpb_EncodedType_Bytes] = kUpb_FieldType_Bytes,
    [kUpb_EncodedType_UInt32] = kUpb_FieldType_UInt32,
    [kUpb_EncodedType_OpenEnum] = kUpb_FieldType_Enum,
    [kUpb_EncodedType_SFixed32] = kUpb_FieldType_SFixed32,
    [kUpb_EncodedType_SFixed64] = kUpb_FieldType_SFixed64,
    [kUpb_EncodedType_SInt32] = kUpb_FieldType_SInt32,
    [kUpb_EncodedType_SInt64] = kUpb_FieldType_SInt64,
    [kUpb_EncodedType_ClosedEnum] = kUpb_FieldType_Enum,
};

static void upb_MiniTable_SetField(upb_MtDecoder* d, uint8_t ch,
                                   upb_MiniTableField* field,
                                   uint64_t msg_modifiers,
                                   upb_SubCounts* sub_counts) {
  static const char kUpb_EncodedToFieldRep[] = {
      [kUpb_EncodedType_Double] = kUpb_FieldRep_8Byte,
      [kUpb_EncodedType_Float] = kUpb_FieldRep_4Byte,
      [kUpb_EncodedType_Int64] = kUpb_FieldRep_8Byte,
      [kUpb_EncodedType_UInt64] = kUpb_FieldRep_8Byte,
      [kUpb_EncodedType_Int32] = kUpb_FieldRep_4Byte,
      [kUpb_EncodedType_Fixed64] = kUpb_FieldRep_8Byte,
      [kUpb_EncodedType_Fixed32] = kUpb_FieldRep_4Byte,
      [kUpb_EncodedType_Bool] = kUpb_FieldRep_1Byte,
      [kUpb_EncodedType_String] = kUpb_FieldRep_StringView,
      [kUpb_EncodedType_Bytes] = kUpb_FieldRep_StringView,
      [kUpb_EncodedType_UInt32] = kUpb_FieldRep_4Byte,
      [kUpb_EncodedType_OpenEnum] = kUpb_FieldRep_4Byte,
      [kUpb_EncodedType_SFixed32] = kUpb_FieldRep_4Byte,
      [kUpb_EncodedType_SFixed64] = kUpb_FieldRep_8Byte,
      [kUpb_EncodedType_SInt32] = kUpb_FieldRep_4Byte,
      [kUpb_EncodedType_SInt64] = kUpb_FieldRep_8Byte,
      [kUpb_EncodedType_ClosedEnum] = kUpb_FieldRep_4Byte,
  };

  char pointer_rep = d->platform == kUpb_MiniTablePlatform_32Bit
                         ? kUpb_FieldRep_4Byte
                         : kUpb_FieldRep_8Byte;

  int8_t type = _upb_FromBase92(ch);
  if (ch >= _upb_ToBase92(kUpb_EncodedType_RepeatedBase)) {
    type -= kUpb_EncodedType_RepeatedBase;
    field->UPB_PRIVATE(mode) = kUpb_FieldMode_Array;
    field->UPB_PRIVATE(mode) |= pointer_rep << kUpb_FieldRep_Shift;
    field->UPB_PRIVATE(offset) = kNoPresence;
  } else {
    field->UPB_PRIVATE(mode) = kUpb_FieldMode_Scalar;
    field->UPB_PRIVATE(offset) = kHasbitPresence;
    if (type == kUpb_EncodedType_Group || type == kUpb_EncodedType_Message) {
      field->UPB_PRIVATE(mode) |= pointer_rep << kUpb_FieldRep_Shift;
    } else if ((unsigned long)type >= sizeof(kUpb_EncodedToFieldRep)) {
      upb_MdDecoder_ErrorJmp(&d->base, "Invalid field type: %d", (int)type);
    } else {
      field->UPB_PRIVATE(mode) |= kUpb_EncodedToFieldRep[type]
                                  << kUpb_FieldRep_Shift;
    }
  }
  if ((unsigned long)type >= sizeof(kUpb_EncodedToType)) {
    upb_MdDecoder_ErrorJmp(&d->base, "Invalid field type: %d", (int)type);
  }
  upb_MiniTable_SetTypeAndSub(field, kUpb_EncodedToType[type], sub_counts,
                              msg_modifiers, type == kUpb_EncodedType_OpenEnum);
}

static void upb_MtDecoder_ModifyField(upb_MtDecoder* d,
                                      uint32_t message_modifiers,
                                      uint32_t field_modifiers,
                                      upb_MiniTableField* field) {
  if (field_modifiers & kUpb_EncodedFieldModifier_FlipPacked) {
    if (!upb_MtDecoder_FieldIsPackable(field)) {
      upb_MdDecoder_ErrorJmp(&d->base,
                             "Cannot flip packed on unpackable field %" PRIu32,
                             upb_MiniTableField_Number(field));
    }
    field->UPB_PRIVATE(mode) ^= kUpb_LabelFlags_IsPacked;
  }

  if (field_modifiers & kUpb_EncodedFieldModifier_FlipValidateUtf8) {
    if (field->UPB_PRIVATE(descriptortype) != kUpb_FieldType_Bytes ||
        !(field->UPB_PRIVATE(mode) & kUpb_LabelFlags_IsAlternate)) {
      upb_MdDecoder_ErrorJmp(&d->base,
                             "Cannot flip ValidateUtf8 on field %" PRIu32
                             ", type=%d, mode=%d",
                             upb_MiniTableField_Number(field),
                             (int)field->UPB_PRIVATE(descriptortype),
                             (int)field->UPB_PRIVATE(mode));
    }
    field->UPB_PRIVATE(descriptortype) = kUpb_FieldType_String;
    field->UPB_PRIVATE(mode) &= ~kUpb_LabelFlags_IsAlternate;
  }

  bool singular = field_modifiers & kUpb_EncodedFieldModifier_IsProto3Singular;
  bool required = field_modifiers & kUpb_EncodedFieldModifier_IsRequired;

  // Validate.
  if ((singular || required) && field->UPB_PRIVATE(offset) != kHasbitPresence) {
    upb_MdDecoder_ErrorJmp(&d->base,
                           "Invalid modifier(s) for repeated field %" PRIu32,
                           upb_MiniTableField_Number(field));
  }
  if (singular && required) {
    upb_MdDecoder_ErrorJmp(
        &d->base, "Field %" PRIu32 " cannot be both singular and required",
        upb_MiniTableField_Number(field));
  }

  if (singular && upb_MiniTableField_IsSubMessage(field)) {
    upb_MdDecoder_ErrorJmp(&d->base,
                           "Field %" PRIu32 " cannot be a singular submessage",
                           upb_MiniTableField_Number(field));
  }

  if (singular) field->UPB_PRIVATE(offset) = kNoPresence;
  if (required) {
    field->UPB_PRIVATE(offset) = kRequiredPresence;
  }
}

static void upb_MtDecoder_PushOneof(upb_MtDecoder* d,
                                    upb_OneOfLayoutItem item) {
  if (item.field_index == kUpb_OneOfLayoutItem_IndexSentinel) {
    upb_MdDecoder_ErrorJmp(&d->base, "Empty oneof");
  }
  if ((d->oneofs.size + 1) * sizeof(*d->oneofs.data) >
      d->oneofs.buf_capacity_bytes) {
    size_t new_cap = UPB_MAX(8, d->oneofs.size * 2) * sizeof(*d->oneofs.data);
    d->oneofs.data =
        upb_grealloc(d->oneofs.data, d->oneofs.buf_capacity_bytes, new_cap);
    upb_MdDecoder_CheckOutOfMemory(&d->base, d->oneofs.data);
    d->oneofs.buf_capacity_bytes = new_cap;
  }
  item.field_index -= kOneofBase;

  d->rep_counts_offsets[kUpb_OneOf_CaseFieldRep]++;
  d->rep_counts_offsets[item.rep]++;
  d->oneofs.data[d->oneofs.size++] = item;
}

static size_t upb_MtDecoder_SizeOfRep(upb_FieldRep rep,
                                      upb_MiniTablePlatform platform) {
  enum { string_view_size_32 = 8, string_view_size_64 = 16 };
  UPB_STATIC_ASSERT(sizeof(upb_StringView) ==
                        UPB_SIZE(string_view_size_32, string_view_size_64),
                    "StringView size mismatch");
  static const uint8_t kRepToSize32[] = {
      [kUpb_FieldRep_1Byte] = 1,
      [kUpb_FieldRep_4Byte] = 4,
      [kUpb_FieldRep_StringView] = string_view_size_32,
      [kUpb_FieldRep_8Byte] = 8,
  };
  static const uint8_t kRepToSize64[] = {
      [kUpb_FieldRep_1Byte] = 1,
      [kUpb_FieldRep_4Byte] = 4,
      [kUpb_FieldRep_StringView] = string_view_size_64,
      [kUpb_FieldRep_8Byte] = 8,
  };
  return platform == kUpb_MiniTablePlatform_32Bit ? kRepToSize32[rep]
                                                  : kRepToSize64[rep];
}

static size_t upb_MtDecoder_AlignOfRep(upb_FieldRep rep,
                                       upb_MiniTablePlatform platform) {
  enum { string_view_align_32 = 4, string_view_align_64 = 8 };
  UPB_STATIC_ASSERT(UPB_ALIGN_OF(upb_StringView) ==
                        UPB_SIZE(string_view_align_32, string_view_align_64),
                    "StringView size mismatch");

  static const uint8_t kRepToAlign32[] = {
      [kUpb_FieldRep_1Byte] = 1,
      [kUpb_FieldRep_4Byte] = 4,
      [kUpb_FieldRep_StringView] = string_view_align_32,
      [kUpb_FieldRep_8Byte] = 8,
  };
  static const uint8_t kRepToAlign64[] = {
      [kUpb_FieldRep_1Byte] = 1,
      [kUpb_FieldRep_4Byte] = 4,
      [kUpb_FieldRep_StringView] = string_view_align_64,
      [kUpb_FieldRep_8Byte] = 8,
  };
  return platform == kUpb_MiniTablePlatform_32Bit ? kRepToAlign32[rep]
                                                  : kRepToAlign64[rep];
}

static const char* upb_MtDecoder_DecodeOneofField(upb_MtDecoder* d,
                                                  const char* ptr,
                                                  char first_ch,
                                                  upb_OneOfLayoutItem* item) {
  uint32_t field_num;
  ptr = upb_MdDecoder_DecodeBase92Varint(
      &d->base, ptr, first_ch, kUpb_EncodedValue_MinOneofField,
      kUpb_EncodedValue_MaxOneofField, &field_num);
  upb_MiniTableField* f =
      (void*)upb_MiniTable_FindFieldByNumber(&d->table, field_num);

  if (!f) {
    upb_MdDecoder_ErrorJmp(&d->base,
                           "Couldn't add field number %" PRIu32
                           " to oneof, no such field number.",
                           field_num);
  }
  if (f->UPB_PRIVATE(offset) != kHasbitPresence) {
    upb_MdDecoder_ErrorJmp(
        &d->base,
        "Cannot add repeated, required, or singular field %" PRIu32
        " to oneof.",
        field_num);
  }

  // Oneof storage must be large enough to accommodate the largest member.
  int rep = f->UPB_PRIVATE(mode) >> kUpb_FieldRep_Shift;
  size_t new_size = upb_MtDecoder_SizeOfRep(rep, d->platform);
  size_t new_align = upb_MtDecoder_AlignOfRep(rep, d->platform);
  size_t current_size = upb_MtDecoder_SizeOfRep(item->rep, d->platform);
  size_t current_align = upb_MtDecoder_AlignOfRep(item->rep, d->platform);

  if (new_size > current_size ||
      (new_size == current_size && new_align > current_align)) {
    UPB_ASSERT(new_align >= current_align);
    item->rep = rep;
  } else {
    UPB_ASSERT(current_align >= new_align);
  }
  // Prepend this field to the linked list.
  f->UPB_PRIVATE(offset) = item->field_index;
  item->field_index = (f - d->fields) + kOneofBase;
  return ptr;
}

static const char* upb_MtDecoder_DecodeOneofs(upb_MtDecoder* d,
                                              const char* ptr) {
  upb_OneOfLayoutItem item = {
      .rep = 0, .field_index = kUpb_OneOfLayoutItem_IndexSentinel};
  while (ptr < d->base.end) {
    char ch = *ptr++;
    if (ch == kUpb_EncodedValue_FieldSeparator) {
      // Field separator, no action needed.
    } else if (ch == kUpb_EncodedValue_OneofSeparator) {
      // End of oneof.
      upb_MtDecoder_PushOneof(d, item);
      item.field_index =
          kUpb_OneOfLayoutItem_IndexSentinel;  // Move to next oneof.
    } else {
      ptr = upb_MtDecoder_DecodeOneofField(d, ptr, ch, &item);
    }
  }

  // Push final oneof.
  upb_MtDecoder_PushOneof(d, item);
  return ptr;
}

static const char* upb_MtDecoder_ParseModifier(upb_MtDecoder* d,
                                               const char* ptr, char first_ch,
                                               upb_MiniTableField* last_field,
                                               uint64_t* msg_modifiers) {
  uint32_t mod;
  ptr = upb_MdDecoder_DecodeBase92Varint(&d->base, ptr, first_ch,
                                         kUpb_EncodedValue_MinModifier,
                                         kUpb_EncodedValue_MaxModifier, &mod);
  if (last_field) {
    upb_MtDecoder_ModifyField(d, *msg_modifiers, mod, last_field);
  } else {
    if (d->is_extension) {
      upb_MdDecoder_ErrorJmp(&d->base,
                             "Extensions cannot have message modifiers");
    }
    *msg_modifiers = mod;
  }

  return ptr;
}

static void* upb_MtDecoder_CheckedMalloc(upb_MtDecoder* d, size_t size) {
  void* ptr = upb_Arena_Malloc(d->arena, size);
  upb_MdDecoder_CheckOutOfMemory(&d->base, ptr);
  return ptr;
}

static void upb_MtDecoder_AllocateSubs(upb_MtDecoder* d,
                                       upb_SubCounts sub_counts) {
  uint32_t total_count = sub_counts.submsg_count + sub_counts.subenum_count;
  size_t subs_bytes = sizeof(*d->table.UPB_PRIVATE(subs)) * total_count;
  size_t ptrs_bytes = sizeof(upb_MiniTable*) * sub_counts.submsg_count;
  upb_MiniTableSubInternal* subs =
      subs_bytes ? upb_MtDecoder_CheckedMalloc(d, subs_bytes) : NULL;
  const upb_MiniTable** subs_ptrs =
      ptrs_bytes ? upb_MtDecoder_CheckedMalloc(d, ptrs_bytes) : NULL;
  uint32_t i = 0;
  for (; i < sub_counts.submsg_count; i++) {
    subs_ptrs[i] = UPB_PRIVATE(_upb_MiniTable_Empty)();
    subs[i].UPB_PRIVATE(submsg) = &subs_ptrs[i];
  }
  if (sub_counts.subenum_count) {
    upb_MiniTableField* f = d->fields;
    upb_MiniTableField* end_f = f + d->table.UPB_PRIVATE(field_count);
    for (; f < end_f; f++) {
      if (f->UPB_PRIVATE(descriptortype) == kUpb_FieldType_Enum) {
        f->UPB_PRIVATE(submsg_index) += sub_counts.submsg_count;
      }
    }
    for (; i < sub_counts.submsg_count + sub_counts.subenum_count; i++) {
      subs[i].UPB_PRIVATE(subenum) = NULL;
    }
  }
  d->table.UPB_PRIVATE(subs) = subs;
}

static const char* upb_MtDecoder_Parse(upb_MtDecoder* d, const char* ptr,
                                       size_t len, void* fields,
                                       size_t field_size, uint16_t* field_count,
                                       upb_SubCounts* sub_counts) {
  uint64_t msg_modifiers = 0;
  uint32_t last_field_number = 0;
  upb_MiniTableField* last_field = NULL;
  bool need_dense_below = !d->is_extension;

  d->base.end = UPB_PTRADD(ptr, len);

  while (ptr < d->base.end) {
    char ch = *ptr++;
    if (ch <= kUpb_EncodedValue_MaxField) {
      if (d->is_extension && last_field) {
        // For extensions, consume only a single field and then return.
        return --ptr;
      }
      upb_MiniTableField* field = fields;
      *field_count += 1;
      fields = (char*)fields + field_size;
      uint32_t number = ++last_field_number;
      if (number == 0 || (number > kUpb_MaxFieldNumber && !d->is_extension)) {
        upb_MdDecoder_ErrorJmp(&d->base, "Invalid field number: %" PRIu32,
                               number);
      }
      field->UPB_PRIVATE(number) = number;
      last_field = field;
      upb_MiniTable_SetField(d, ch, field, msg_modifiers, sub_counts);
    } else if (kUpb_EncodedValue_MinModifier <= ch &&
               ch <= kUpb_EncodedValue_MaxModifier) {
      ptr = upb_MtDecoder_ParseModifier(d, ptr, ch, last_field, &msg_modifiers);
      if (msg_modifiers & kUpb_MessageModifier_IsExtendable) {
        d->table.UPB_PRIVATE(ext) |= kUpb_ExtMode_Extendable;
      }
    } else if (ch == kUpb_EncodedValue_End) {
      if (d->is_extension) {
        upb_MdDecoder_ErrorJmp(&d->base, "Extensions cannot have oneofs.");
      }
      ptr = upb_MtDecoder_DecodeOneofs(d, ptr);
    } else if (kUpb_EncodedValue_MinSkip <= ch &&
               ch <= kUpb_EncodedValue_MaxSkip) {
      if (need_dense_below) {
        d->table.UPB_PRIVATE(dense_below) = d->table.UPB_PRIVATE(field_count);
        need_dense_below = false;
      }
      uint32_t skip;
      ptr = upb_MdDecoder_DecodeBase92Varint(&d->base, ptr, ch,
                                             kUpb_EncodedValue_MinSkip,
                                             kUpb_EncodedValue_MaxSkip, &skip);
      last_field_number += skip;
      last_field_number--;  // Next field seen will increment.
    } else {
      upb_MdDecoder_ErrorJmp(&d->base, "Invalid char: %c", ch);
    }
  }

  if (need_dense_below) {
    d->table.UPB_PRIVATE(dense_below) = d->table.UPB_PRIVATE(field_count);
  }

  return ptr;
}

static void upb_MtDecoder_ParseMessage(upb_MtDecoder* d, const char* data,
                                       size_t len) {
  // Buffer length is an upper bound on the number of fields. We will return
  // what we don't use.
  if (SIZE_MAX / sizeof(*d->fields) < len) {
    upb_MdDecoder_ErrorJmp(&d->base, "Out of memory");
  }
  d->fields = upb_Arena_Malloc(d->arena, sizeof(*d->fields) * len);
  upb_MdDecoder_CheckOutOfMemory(&d->base, d->fields);

  upb_SubCounts sub_counts = {0, 0};
  d->table.UPB_PRIVATE(field_count) = 0;
  d->table.UPB_PRIVATE(fields) = d->fields;
  upb_MtDecoder_Parse(d, data, len, d->fields, sizeof(*d->fields),
                      &d->table.UPB_PRIVATE(field_count), &sub_counts);

  upb_Arena_ShrinkLast(d->arena, d->fields, sizeof(*d->fields) * len,
                       sizeof(*d->fields) * d->table.UPB_PRIVATE(field_count));
  d->table.UPB_PRIVATE(fields) = d->fields;
  upb_MtDecoder_AllocateSubs(d, sub_counts);
}

static void upb_MtDecoder_CalculateAlignments(upb_MtDecoder* d) {
  // Add alignment counts for non-oneof fields (oneofs were added already)
  int n = d->table.UPB_PRIVATE(field_count);
  for (int i = 0; i < n; i++) {
    upb_MiniTableField* f = &d->fields[i];
    if (f->UPB_PRIVATE(offset) >= kOneofBase) continue;
    d->rep_counts_offsets[f->UPB_PRIVATE(mode) >> kUpb_FieldRep_Shift]++;
  }

  // Reserve properly aligned space for each type of field representation
  // present in this message. When we iterate over the fields, they will obtain
  // their offset from within the region matching their alignment requirements.
  size_t base = d->table.UPB_PRIVATE(size);
  // Start with the lowest alignment requirement, going up, because:
  // 1. If there are presence bits, we won't be aligned to start, but adding
  //    some lower-alignment fields may get us closer without wasting space to
  //    padding.
  // 2. The allocator enforces 8 byte alignment, so moving intermediate padding
  //    to trailing padding doesn't save us anything.
  for (upb_FieldRep rep = kUpb_FieldRep_1Byte; rep <= kUpb_FieldRep_Max;
       rep++) {
    uint16_t count = d->rep_counts_offsets[rep];
    if (count) {
      base = UPB_ALIGN_UP(base, upb_MtDecoder_AlignOfRep(rep, d->platform));
      // This entry now tracks the base offset for this field representation
      // type, instead of the count
      d->rep_counts_offsets[rep] = base;
      base += upb_MtDecoder_SizeOfRep(rep, d->platform) * count;
    }
  }
  static const size_t max = UINT16_MAX;
  if (base > max) {
    upb_MdDecoder_ErrorJmp(
        &d->base, "Message size exceeded maximum size of %zu bytes", max);
  }
  d->table.UPB_PRIVATE(size) = (uint16_t)base;
}

static size_t upb_MiniTable_DivideRoundUp(size_t n, size_t d) {
  return (n + d - 1) / d;
}

static void upb_MtDecoder_AssignHasbits(upb_MtDecoder* d) {
  int n = d->table.UPB_PRIVATE(field_count);
  size_t last_hasbit = kUpb_Reserved_Hasbits - 1;

  // First assign required fields, which must have the lowest hasbits.
  for (int i = 0; i < n; i++) {
    upb_MiniTableField* field =
        (upb_MiniTableField*)&d->table.UPB_PRIVATE(fields)[i];
    if (field->UPB_PRIVATE(offset) == kRequiredPresence) {
      field->presence = ++last_hasbit;
    } else if (field->UPB_PRIVATE(offset) == kNoPresence) {
      field->presence = 0;
    }
  }
  if (last_hasbit > kUpb_Reserved_Hasbits + 63) {
    upb_MdDecoder_ErrorJmp(&d->base, "Too many required fields");
  }

  d->table.UPB_PRIVATE(required_count) =
      last_hasbit - (kUpb_Reserved_Hasbits - 1);

  // Next assign non-required hasbit fields.
  for (int i = 0; i < n; i++) {
    upb_MiniTableField* field =
        (upb_MiniTableField*)&d->table.UPB_PRIVATE(fields)[i];
    if (field->UPB_PRIVATE(offset) == kHasbitPresence) {
      field->presence = ++last_hasbit;
    }
  }

  d->table.UPB_PRIVATE(size) =
      last_hasbit ? upb_MiniTable_DivideRoundUp(last_hasbit + 1, 8) : 0;
}

static size_t upb_MtDecoder_Place(upb_MtDecoder* d, upb_FieldRep rep) {
  size_t size = upb_MtDecoder_SizeOfRep(rep, d->platform);
  size_t offset = d->rep_counts_offsets[rep];
  d->rep_counts_offsets[rep] += size;
  return offset;
}

static void upb_MtDecoder_AssignOffsets(upb_MtDecoder* d) {
  upb_MiniTableField* field_end =
      UPB_PTRADD(d->fields, d->table.UPB_PRIVATE(field_count));
  for (upb_MiniTableField* field = d->fields; field < field_end; field++) {
    if (field->UPB_PRIVATE(offset) >= kOneofBase) continue;
    field->UPB_PRIVATE(offset) =
        upb_MtDecoder_Place(d, field->UPB_PRIVATE(mode) >> kUpb_FieldRep_Shift);
  }

  upb_OneOfLayoutItem* oneof_end = UPB_PTRADD(d->oneofs.data, d->oneofs.size);

  for (upb_OneOfLayoutItem* item = d->oneofs.data; item < oneof_end; item++) {
    upb_MiniTableField* f = &d->fields[item->field_index];
    uint16_t case_offset = upb_MtDecoder_Place(d, kUpb_OneOf_CaseFieldRep);
    uint16_t data_offset = upb_MtDecoder_Place(d, item->rep);
    while (true) {
      f->presence = ~case_offset;
      uint16_t next_offset = f->UPB_PRIVATE(offset);
      f->UPB_PRIVATE(offset) = data_offset;
      if (next_offset == kUpb_OneOfLayoutItem_IndexSentinel) break;
      UPB_ASSERT(next_offset - kOneofBase < d->table.UPB_PRIVATE(field_count));
      f = &d->fields[next_offset - kOneofBase];
    }
  }

  // Since messages are always allocated on arenas, we can save repeatedly
  // realigning by doing alignment at minitable construction time. We don't want
  // to align to UPB_MALLOC_ALIGN because it can change with sanitizers, and if
  // we're generating code we don't want to calculate size differently depending
  // on the proto compiler's host or build configuration.
  d->table.UPB_PRIVATE(size) =
      UPB_ALIGN_UP(d->table.UPB_PRIVATE(size), kUpb_Message_Align);
}

static void upb_MtDecoder_ValidateEntryField(upb_MtDecoder* d,
                                             const upb_MiniTableField* f,
                                             uint32_t expected_num) {
  const char* name = expected_num == 1 ? "key" : "val";
  const uint32_t f_number = upb_MiniTableField_Number(f);
  if (f_number != expected_num) {
    upb_MdDecoder_ErrorJmp(&d->base,
                           "map %s did not have expected number (%d vs %d)",
                           name, expected_num, f_number);
  }

  if (!upb_MiniTableField_IsScalar(f)) {
    upb_MdDecoder_ErrorJmp(
        &d->base, "map %s cannot be repeated or map, or be in oneof", name);
  }

  uint32_t not_ok_types;
  if (expected_num == 1) {
    not_ok_types = (1 << kUpb_FieldType_Float) | (1 << kUpb_FieldType_Double) |
                   (1 << kUpb_FieldType_Message) | (1 << kUpb_FieldType_Group) |
                   (1 << kUpb_FieldType_Bytes) | (1 << kUpb_FieldType_Enum);
  } else {
    not_ok_types = 1 << kUpb_FieldType_Group;
  }

  if ((1 << upb_MiniTableField_Type(f)) & not_ok_types) {
    upb_MdDecoder_ErrorJmp(&d->base, "map %s cannot have type %d", name,
                           (int)f->UPB_PRIVATE(descriptortype));
  }
}

static void upb_MtDecoder_ParseMap(upb_MtDecoder* d, const char* data,
                                   size_t len) {
  upb_MtDecoder_ParseMessage(d, data, len);
  upb_MtDecoder_AssignHasbits(d);

  if (UPB_UNLIKELY(d->table.UPB_PRIVATE(field_count) != 2)) {
    upb_MdDecoder_ErrorJmp(&d->base, "%hu fields in map",
                           d->table.UPB_PRIVATE(field_count));
    UPB_UNREACHABLE();
  }

  if (d->oneofs.size != 0) {
    upb_MdDecoder_ErrorJmp(&d->base, "Map entry cannot have oneof");
  }

  upb_MtDecoder_ValidateEntryField(d, &d->table.UPB_PRIVATE(fields)[0], 1);
  upb_MtDecoder_ValidateEntryField(d, &d->table.UPB_PRIVATE(fields)[1], 2);

  d->fields[0].UPB_PRIVATE(offset) = offsetof(upb_MapEntry, k);
  d->fields[1].UPB_PRIVATE(offset) = offsetof(upb_MapEntry, v);
  d->table.UPB_PRIVATE(size) = sizeof(upb_MapEntry);

  // Map entries have a special bit set to signal it's a map entry, used in
  // upb_MiniTable_SetSubMessage() below.
  d->table.UPB_PRIVATE(ext) |= kUpb_ExtMode_IsMapEntry;
}

static void upb_MtDecoder_ParseMessageSet(upb_MtDecoder* d, const char* data,
                                          size_t len) {
  if (len > 0) {
    upb_MdDecoder_ErrorJmp(&d->base, "Invalid message set encode length: %zu",
                           len);
  }

  upb_MiniTable* ret = &d->table;
  ret->UPB_PRIVATE(size) = kUpb_Reserved_Hasbytes;
  ret->UPB_PRIVATE(field_count) = 0;
  ret->UPB_PRIVATE(ext) = kUpb_ExtMode_IsMessageSet;
  ret->UPB_PRIVATE(dense_below) = 0;
  ret->UPB_PRIVATE(table_mask) = -1;
  ret->UPB_PRIVATE(required_count) = 0;
}

static upb_MiniTable* upb_MtDecoder_DoBuildMiniTableWithBuf(
    upb_MtDecoder* decoder, const char* data, size_t len, void** buf,
    size_t* buf_size) {
  decoder->table.UPB_PRIVATE(size) = kUpb_Reserved_Hasbytes;
  decoder->table.UPB_PRIVATE(field_count) = 0;
  decoder->table.UPB_PRIVATE(ext) = kUpb_ExtMode_NonExtendable;
  decoder->table.UPB_PRIVATE(dense_below) = 0;
  decoder->table.UPB_PRIVATE(table_mask) = -1;
  decoder->table.UPB_PRIVATE(required_count) = 0;
#ifdef UPB_TRACING_ENABLED
  // MiniTables built from MiniDescriptors will not be able to vend the message
  // name unless it is explicitly set with upb_MiniTable_SetFullName().
  decoder->table.UPB_PRIVATE(full_name) = 0;
#endif

  // Strip off and verify the version tag.
  if (!len--) goto done;
  const char vers = *data++;

  switch (vers) {
    case kUpb_EncodedVersion_MapV1:
      upb_MtDecoder_ParseMap(decoder, data, len);
      break;

    case kUpb_EncodedVersion_MessageV1:
      upb_MtDecoder_ParseMessage(decoder, data, len);
      upb_MtDecoder_AssignHasbits(decoder);
      upb_MtDecoder_CalculateAlignments(decoder);
      upb_MtDecoder_AssignOffsets(decoder);
      break;

    case kUpb_EncodedVersion_MessageSetV1:
      upb_MtDecoder_ParseMessageSet(decoder, data, len);
      break;

    default:
      upb_MdDecoder_ErrorJmp(&decoder->base, "Invalid message version: %c",
                             vers);
  }

done:
  *buf = decoder->oneofs.data;
  *buf_size = decoder->oneofs.buf_capacity_bytes;
  size_t mt_size = sizeof(upb_MiniTable);

#if UPB_FASTTABLE
  upb_DecodeFast_TableEntry fasttable[32];
  int fasttable_size = upb_DecodeFast_BuildTable(&decoder->table, fasttable);
  mt_size += fasttable_size * sizeof(fasttable[0]);
#endif

  upb_MiniTable* ret = upb_Arena_Malloc(decoder->arena, mt_size);
  memcpy(ret, &decoder->table, sizeof(*ret));

#if UPB_FASTTABLE
  ret->UPB_PRIVATE(table_mask) = upb_DecodeFast_GetTableMask(fasttable_size);
  for (int i = 0; i < fasttable_size; i++) {
    ret->UPB_PRIVATE(fasttable)[i].field_data = fasttable[i].function_data;
    ret->UPB_PRIVATE(fasttable)[i].field_parser =
        upb_DecodeFast_GetFunctionPointer(fasttable[i].function_idx);
  }
#endif
  UPB_PRIVATE(upb_MiniTable_CheckInvariants)(ret);
  return ret;
}

static upb_MiniTable* upb_MtDecoder_BuildMiniTableWithBuf(
    upb_MtDecoder* const decoder, const char* const data, const size_t len,
    void** const buf, size_t* const buf_size) {
  if (UPB_SETJMP(decoder->base.err) != 0) {
    *buf = decoder->oneofs.data;
    *buf_size = decoder->oneofs.buf_capacity_bytes;
    return NULL;
  }

  return upb_MtDecoder_DoBuildMiniTableWithBuf(decoder, data, len, buf,
                                               buf_size);
}

upb_MiniTable* upb_MiniTable_BuildWithBuf(const char* data, size_t len,
                                          upb_MiniTablePlatform platform,
                                          upb_Arena* arena, void** buf,
                                          size_t* buf_size,
                                          upb_Status* status) {
  upb_MtDecoder decoder = {
      .base = {.status = status},
      .platform = platform,
      .is_extension = false,
      .oneofs =
          {
              .data = *buf,
              .buf_capacity_bytes = *buf_size,
              .size = 0,
          },
      .arena = arena,
  };

  return upb_MtDecoder_BuildMiniTableWithBuf(&decoder, data, len, buf,
                                             buf_size);
}

static const char* upb_MtDecoder_DoBuildMiniTableExtension(
    upb_MtDecoder* decoder, const char* data, size_t len,
    upb_MiniTableExtension* ext, const upb_MiniTable* extendee,
    upb_MiniTableSub sub) {
  if (!(extendee->UPB_PRIVATE(ext) &
        (kUpb_ExtMode_Extendable | kUpb_ExtMode_IsMessageSet))) {
    upb_MdDecoder_ErrorJmp(&decoder->base, "Extendee is not extendable");
  }

  // If the string is non-empty then it must begin with a version tag.
  if (len) {
    if (*data != kUpb_EncodedVersion_ExtensionV1) {
      upb_MdDecoder_ErrorJmp(&decoder->base, "Invalid ext version: %c", *data);
    }
    data++;
    len--;
  }

  uint16_t count = 0;
  upb_SubCounts sub_counts = {0, 0};
  const char* ret = upb_MtDecoder_Parse(decoder, data, len, ext, sizeof(*ext),
                                        &count, &sub_counts);
  if (!ret || count != 1) return NULL;

  upb_MiniTableField* f = &ext->UPB_PRIVATE(field);

  f->UPB_PRIVATE(mode) |= kUpb_LabelFlags_IsExtension;
  f->UPB_PRIVATE(offset) = 0;
  f->presence = 0;

  if (extendee->UPB_PRIVATE(ext) & kUpb_ExtMode_IsMessageSet) {
    // Extensions of MessageSet must be messages.
    if (!upb_MiniTableField_IsSubMessage(f)) return NULL;

    // Extensions of MessageSet must be non-repeating.
    if (upb_MiniTableField_IsArray(f)) return NULL;
  }

  ext->UPB_PRIVATE(extendee) = extendee;
  ext->UPB_PRIVATE(sub) = sub;

  return ret;
}

static const char* upb_MtDecoder_BuildMiniTableExtension(
    upb_MtDecoder* const decoder, const char* const data, const size_t len,
    upb_MiniTableExtension* const ext, const upb_MiniTable* const extendee,
    const upb_MiniTableSub sub) {
  if (UPB_SETJMP(decoder->base.err) != 0) return NULL;
  return upb_MtDecoder_DoBuildMiniTableExtension(decoder, data, len, ext,
                                                 extendee, sub);
}

const char* _upb_MiniTableExtension_Init(const char* data, size_t len,
                                         upb_MiniTableExtension* ext,
                                         const upb_MiniTable* extendee,
                                         upb_MiniTableSub sub,
                                         upb_MiniTablePlatform platform,
                                         upb_Status* status) {
  upb_MtDecoder decoder = {
      .base = {.status = status},
      .arena = NULL,
      .platform = platform,
      .is_extension = true,
  };

  return upb_MtDecoder_BuildMiniTableExtension(&decoder, data, len, ext,
                                               extendee, sub);
}

upb_MiniTableExtension* _upb_MiniTableExtension_Build(
    const char* data, size_t len, const upb_MiniTable* extendee,
    upb_MiniTableSub sub, upb_MiniTablePlatform platform, upb_Arena* arena,
    upb_Status* status) {
  upb_MiniTableExtension* ext =
      upb_Arena_Malloc(arena, sizeof(upb_MiniTableExtension));
  if (UPB_UNLIKELY(!ext)) return NULL;

  const char* ptr = _upb_MiniTableExtension_Init(data, len, ext, extendee, sub,
                                                 platform, status);
  if (UPB_UNLIKELY(!ptr)) return NULL;

  return ext;
}

upb_MiniTable* _upb_MiniTable_Build(const char* data, size_t len,
                                    upb_MiniTablePlatform platform,
                                    upb_Arena* arena, upb_Status* status) {
  void* buf = NULL;
  size_t size = 0;
  upb_MiniTable* ret = upb_MiniTable_BuildWithBuf(data, len, platform, arena,
                                                  &buf, &size, status);
  upb_gfree(buf);
  return ret;
}


const char _kUpb_ToBase92[] = {
    ' ', '!', '#', '$', '%', '&', '(', ')', '*', '+', ',', '-', '.', '/',
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '=',
    '>', '?', '@', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
    'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y',
    'Z', '[', ']', '^', '_', '`', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
    'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
    'w', 'x', 'y', 'z', '{', '|', '}', '~',
};

const int8_t _kUpb_FromBase92[] = {
    0,  1,  -1, 2,  3,  4,  5,  -1, 6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 16,
    17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35,
    36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54,
    55, 56, 57, -1, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72,
    73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91,
};


#include <assert.h>
#include <stddef.h>
#include <stdint.h>


// Must be last.

typedef struct {
  uint64_t present_values_mask;
  uint32_t last_written_value;
} upb_MtDataEncoderInternal_EnumState;

typedef struct {
  uint64_t msg_modifiers;
  uint32_t last_field_num;
  enum {
    kUpb_OneofState_NotStarted,
    kUpb_OneofState_StartedOneof,
    kUpb_OneofState_EmittedOneofField,
  } oneof_state;
} upb_MtDataEncoderInternal_MsgState;

typedef struct {
  char* buf_start;  // Only for checking kUpb_MtDataEncoder_MinSize.
  union {
    upb_MtDataEncoderInternal_EnumState enum_state;
    upb_MtDataEncoderInternal_MsgState msg_state;
  } state;
} upb_MtDataEncoderInternal;

static upb_MtDataEncoderInternal* upb_MtDataEncoder_GetInternal(
    upb_MtDataEncoder* e, char* buf_start) {
  UPB_ASSERT(sizeof(upb_MtDataEncoderInternal) <= sizeof(e->internal));
  upb_MtDataEncoderInternal* ret = (upb_MtDataEncoderInternal*)e->internal;
  ret->buf_start = buf_start;
  return ret;
}

static char* upb_MtDataEncoder_PutRaw(upb_MtDataEncoder* e, char* ptr,
                                      char ch) {
  upb_MtDataEncoderInternal* in = (upb_MtDataEncoderInternal*)e->internal;
  UPB_ASSERT(ptr - in->buf_start < kUpb_MtDataEncoder_MinSize);
  if (ptr == e->end) return NULL;
  *ptr++ = ch;
  return ptr;
}

static char* upb_MtDataEncoder_Put(upb_MtDataEncoder* e, char* ptr, char ch) {
  return upb_MtDataEncoder_PutRaw(e, ptr, _upb_ToBase92(ch));
}

static char* upb_MtDataEncoder_PutBase92Varint(upb_MtDataEncoder* e, char* ptr,
                                               uint32_t val, int min, int max) {
  int shift = upb_Log2Ceiling(_upb_FromBase92(max) - _upb_FromBase92(min) + 1);
  UPB_ASSERT(shift <= 6);
  uint32_t mask = (1 << shift) - 1;
  do {
    uint32_t bits = val & mask;
    ptr = upb_MtDataEncoder_Put(e, ptr, bits + _upb_FromBase92(min));
    if (!ptr) return NULL;
    val >>= shift;
  } while (val);
  return ptr;
}

char* upb_MtDataEncoder_PutModifier(upb_MtDataEncoder* e, char* ptr,
                                    uint64_t mod) {
  if (mod) {
    ptr = upb_MtDataEncoder_PutBase92Varint(e, ptr, mod,
                                            kUpb_EncodedValue_MinModifier,
                                            kUpb_EncodedValue_MaxModifier);
  }
  return ptr;
}

char* upb_MtDataEncoder_EncodeExtension(upb_MtDataEncoder* e, char* ptr,
                                        upb_FieldType type, uint32_t field_num,
                                        uint64_t field_mod) {
  upb_MtDataEncoderInternal* in = upb_MtDataEncoder_GetInternal(e, ptr);
  in->state.msg_state.msg_modifiers = 0;
  in->state.msg_state.last_field_num = 0;
  in->state.msg_state.oneof_state = kUpb_OneofState_NotStarted;

  ptr = upb_MtDataEncoder_PutRaw(e, ptr, kUpb_EncodedVersion_ExtensionV1);
  if (!ptr) return NULL;

  return upb_MtDataEncoder_PutField(e, ptr, type, field_num, field_mod);
}

char* upb_MtDataEncoder_EncodeMap(upb_MtDataEncoder* e, char* ptr,
                                  upb_FieldType key_type,
                                  upb_FieldType value_type, uint64_t key_mod,
                                  uint64_t value_mod) {
  upb_MtDataEncoderInternal* in = upb_MtDataEncoder_GetInternal(e, ptr);
  in->state.msg_state.msg_modifiers = 0;
  in->state.msg_state.last_field_num = 0;
  in->state.msg_state.oneof_state = kUpb_OneofState_NotStarted;

  ptr = upb_MtDataEncoder_PutRaw(e, ptr, kUpb_EncodedVersion_MapV1);
  if (!ptr) return NULL;

  ptr = upb_MtDataEncoder_PutField(e, ptr, key_type, 1, key_mod);
  if (!ptr) return NULL;

  return upb_MtDataEncoder_PutField(e, ptr, value_type, 2, value_mod);
}

char* upb_MtDataEncoder_EncodeMessageSet(upb_MtDataEncoder* e, char* ptr) {
  (void)upb_MtDataEncoder_GetInternal(e, ptr);
  return upb_MtDataEncoder_PutRaw(e, ptr, kUpb_EncodedVersion_MessageSetV1);
}

char* upb_MtDataEncoder_StartMessage(upb_MtDataEncoder* e, char* ptr,
                                     uint64_t msg_mod) {
  upb_MtDataEncoderInternal* in = upb_MtDataEncoder_GetInternal(e, ptr);
  in->state.msg_state.msg_modifiers = msg_mod;
  in->state.msg_state.last_field_num = 0;
  in->state.msg_state.oneof_state = kUpb_OneofState_NotStarted;

  ptr = upb_MtDataEncoder_PutRaw(e, ptr, kUpb_EncodedVersion_MessageV1);
  if (!ptr) return NULL;

  return upb_MtDataEncoder_PutModifier(e, ptr, msg_mod);
}

static char* _upb_MtDataEncoder_MaybePutFieldSkip(upb_MtDataEncoder* e,
                                                  char* ptr,
                                                  uint32_t field_num) {
  upb_MtDataEncoderInternal* in = (upb_MtDataEncoderInternal*)e->internal;
  if (field_num <= in->state.msg_state.last_field_num) return NULL;
  if (in->state.msg_state.last_field_num + 1 != field_num) {
    // Put skip.
    UPB_ASSERT(field_num > in->state.msg_state.last_field_num);
    uint32_t skip = field_num - in->state.msg_state.last_field_num;
    ptr = upb_MtDataEncoder_PutBase92Varint(
        e, ptr, skip, kUpb_EncodedValue_MinSkip, kUpb_EncodedValue_MaxSkip);
    if (!ptr) return NULL;
  }
  in->state.msg_state.last_field_num = field_num;
  return ptr;
}

static char* _upb_MtDataEncoder_PutFieldType(upb_MtDataEncoder* e, char* ptr,
                                             upb_FieldType type,
                                             uint64_t field_mod) {
  static const char kUpb_TypeToEncoded[] = {
      [kUpb_FieldType_Double] = kUpb_EncodedType_Double,
      [kUpb_FieldType_Float] = kUpb_EncodedType_Float,
      [kUpb_FieldType_Int64] = kUpb_EncodedType_Int64,
      [kUpb_FieldType_UInt64] = kUpb_EncodedType_UInt64,
      [kUpb_FieldType_Int32] = kUpb_EncodedType_Int32,
      [kUpb_FieldType_Fixed64] = kUpb_EncodedType_Fixed64,
      [kUpb_FieldType_Fixed32] = kUpb_EncodedType_Fixed32,
      [kUpb_FieldType_Bool] = kUpb_EncodedType_Bool,
      [kUpb_FieldType_String] = kUpb_EncodedType_String,
      [kUpb_FieldType_Group] = kUpb_EncodedType_Group,
      [kUpb_FieldType_Message] = kUpb_EncodedType_Message,
      [kUpb_FieldType_Bytes] = kUpb_EncodedType_Bytes,
      [kUpb_FieldType_UInt32] = kUpb_EncodedType_UInt32,
      [kUpb_FieldType_Enum] = kUpb_EncodedType_OpenEnum,
      [kUpb_FieldType_SFixed32] = kUpb_EncodedType_SFixed32,
      [kUpb_FieldType_SFixed64] = kUpb_EncodedType_SFixed64,
      [kUpb_FieldType_SInt32] = kUpb_EncodedType_SInt32,
      [kUpb_FieldType_SInt64] = kUpb_EncodedType_SInt64,
  };

  int encoded_type = kUpb_TypeToEncoded[type];

  if (field_mod & kUpb_FieldModifier_IsClosedEnum) {
    UPB_ASSERT(type == kUpb_FieldType_Enum);
    encoded_type = kUpb_EncodedType_ClosedEnum;
  }

  if (field_mod & kUpb_FieldModifier_IsRepeated) {
    // Repeated fields shift the type number up (unlike other modifiers which
    // are bit flags).
    encoded_type += kUpb_EncodedType_RepeatedBase;
  }

  return upb_MtDataEncoder_Put(e, ptr, encoded_type);
}

static char* _upb_MtDataEncoder_MaybePutModifiers(upb_MtDataEncoder* e,
                                                  char* ptr, upb_FieldType type,
                                                  uint64_t field_mod) {
  upb_MtDataEncoderInternal* in = (upb_MtDataEncoderInternal*)e->internal;
  uint32_t encoded_modifiers = 0;
  if ((field_mod & kUpb_FieldModifier_IsRepeated) &&
      upb_FieldType_IsPackable(type)) {
    bool field_is_packed = field_mod & kUpb_FieldModifier_IsPacked;
    bool default_is_packed = in->state.msg_state.msg_modifiers &
                             kUpb_MessageModifier_DefaultIsPacked;
    if (field_is_packed != default_is_packed) {
      encoded_modifiers |= kUpb_EncodedFieldModifier_FlipPacked;
    }
  }

  if (type == kUpb_FieldType_String) {
    bool field_validates_utf8 = field_mod & kUpb_FieldModifier_ValidateUtf8;
    bool message_validates_utf8 =
        in->state.msg_state.msg_modifiers & kUpb_MessageModifier_ValidateUtf8;
    if (field_validates_utf8 != message_validates_utf8) {
      // Old binaries do not recognize the field modifier.  We need the failure
      // mode to be too lax rather than too strict.  Our caller should have
      // handled this (see _upb_MessageDef_ValidateUtf8()).
      assert(!message_validates_utf8);
      encoded_modifiers |= kUpb_EncodedFieldModifier_FlipValidateUtf8;
    }
  }

  if (field_mod & kUpb_FieldModifier_IsProto3Singular) {
    encoded_modifiers |= kUpb_EncodedFieldModifier_IsProto3Singular;
  }

  if (field_mod & kUpb_FieldModifier_IsRequired) {
    encoded_modifiers |= kUpb_EncodedFieldModifier_IsRequired;
  }

  return upb_MtDataEncoder_PutModifier(e, ptr, encoded_modifiers);
}

char* upb_MtDataEncoder_PutField(upb_MtDataEncoder* e, char* ptr,
                                 upb_FieldType type, uint32_t field_num,
                                 uint64_t field_mod) {
  upb_MtDataEncoder_GetInternal(e, ptr);

  ptr = _upb_MtDataEncoder_MaybePutFieldSkip(e, ptr, field_num);
  if (!ptr) return NULL;

  ptr = _upb_MtDataEncoder_PutFieldType(e, ptr, type, field_mod);
  if (!ptr) return NULL;

  return _upb_MtDataEncoder_MaybePutModifiers(e, ptr, type, field_mod);
}

char* upb_MtDataEncoder_StartOneof(upb_MtDataEncoder* e, char* ptr) {
  upb_MtDataEncoderInternal* in = upb_MtDataEncoder_GetInternal(e, ptr);
  if (in->state.msg_state.oneof_state == kUpb_OneofState_NotStarted) {
    ptr = upb_MtDataEncoder_Put(e, ptr, _upb_FromBase92(kUpb_EncodedValue_End));
  } else {
    ptr = upb_MtDataEncoder_Put(
        e, ptr, _upb_FromBase92(kUpb_EncodedValue_OneofSeparator));
  }
  in->state.msg_state.oneof_state = kUpb_OneofState_StartedOneof;
  return ptr;
}

char* upb_MtDataEncoder_PutOneofField(upb_MtDataEncoder* e, char* ptr,
                                      uint32_t field_num) {
  upb_MtDataEncoderInternal* in = upb_MtDataEncoder_GetInternal(e, ptr);
  if (in->state.msg_state.oneof_state == kUpb_OneofState_EmittedOneofField) {
    ptr = upb_MtDataEncoder_Put(
        e, ptr, _upb_FromBase92(kUpb_EncodedValue_FieldSeparator));
    if (!ptr) return NULL;
  }
  ptr = upb_MtDataEncoder_PutBase92Varint(e, ptr, field_num, _upb_ToBase92(0),
                                          _upb_ToBase92(63));
  in->state.msg_state.oneof_state = kUpb_OneofState_EmittedOneofField;
  return ptr;
}

char* upb_MtDataEncoder_StartEnum(upb_MtDataEncoder* e, char* ptr) {
  upb_MtDataEncoderInternal* in = upb_MtDataEncoder_GetInternal(e, ptr);
  in->state.enum_state.present_values_mask = 0;
  in->state.enum_state.last_written_value = 0;

  return upb_MtDataEncoder_PutRaw(e, ptr, kUpb_EncodedVersion_EnumV1);
}

static char* upb_MtDataEncoder_FlushDenseEnumMask(upb_MtDataEncoder* e,
                                                  char* ptr) {
  upb_MtDataEncoderInternal* in = (upb_MtDataEncoderInternal*)e->internal;
  ptr = upb_MtDataEncoder_Put(e, ptr, in->state.enum_state.present_values_mask);
  in->state.enum_state.present_values_mask = 0;
  in->state.enum_state.last_written_value += 5;
  return ptr;
}

char* upb_MtDataEncoder_PutEnumValue(upb_MtDataEncoder* e, char* ptr,
                                     uint32_t val) {
  // TODO: optimize this encoding.
  upb_MtDataEncoderInternal* in = upb_MtDataEncoder_GetInternal(e, ptr);
  UPB_ASSERT(val >= in->state.enum_state.last_written_value);
  uint32_t delta = val - in->state.enum_state.last_written_value;
  if (delta >= 5 && in->state.enum_state.present_values_mask) {
    ptr = upb_MtDataEncoder_FlushDenseEnumMask(e, ptr);
    if (!ptr) {
      return NULL;
    }
    delta -= 5;
  }

  if (delta >= 5) {
    ptr = upb_MtDataEncoder_PutBase92Varint(
        e, ptr, delta, kUpb_EncodedValue_MinSkip, kUpb_EncodedValue_MaxSkip);
    in->state.enum_state.last_written_value += delta;
    delta = 0;
  }

  UPB_ASSERT((in->state.enum_state.present_values_mask >> delta) == 0);
  in->state.enum_state.present_values_mask |= 1ULL << delta;
  return ptr;
}

char* upb_MtDataEncoder_EndEnum(upb_MtDataEncoder* e, char* ptr) {
  upb_MtDataEncoderInternal* in = upb_MtDataEncoder_GetInternal(e, ptr);
  if (!in->state.enum_state.present_values_mask) return ptr;
  return upb_MtDataEncoder_FlushDenseEnumMask(e, ptr);
}


#include <stddef.h>
#include <stdint.h>


// Must be last.

typedef struct {
  upb_MdDecoder base;
  upb_Arena* arena;
  upb_MiniTableEnum* enum_table;
  uint32_t enum_value_count;
  uint32_t enum_data_count;
  uint32_t enum_data_capacity;
} upb_MdEnumDecoder;

static size_t upb_MiniTableEnum_Size(uint32_t count) {
  return UPB_SIZEOF_FLEX(upb_MiniTableEnum, UPB_PRIVATE(data), count);
}

static upb_MiniTableEnum* _upb_MiniTable_AddEnumDataMember(upb_MdEnumDecoder* d,
                                                           uint32_t val) {
  if (d->enum_data_count == d->enum_data_capacity) {
    size_t old_sz = upb_MiniTableEnum_Size(d->enum_data_capacity);
    if (d->enum_data_capacity > UINT32_MAX / 2) {
      upb_MdDecoder_ErrorJmp(&d->base, "Out of memory");
    }
    uint32_t new_capacity = UPB_MAX(2, d->enum_data_capacity * 2);
    if (UPB_SIZEOF_FLEX_WOULD_OVERFLOW(upb_MiniTableEnum, UPB_PRIVATE(data),
                                       new_capacity)) {
      upb_MdDecoder_ErrorJmp(&d->base, "Out of memory");
    }
    size_t new_sz = upb_MiniTableEnum_Size(new_capacity);
    d->enum_table = upb_Arena_Realloc(d->arena, d->enum_table, old_sz, new_sz);
    upb_MdDecoder_CheckOutOfMemory(&d->base, d->enum_table);
    d->enum_data_capacity = new_capacity;
  }
  d->enum_table->UPB_PRIVATE(data)[d->enum_data_count++] = val;
  return d->enum_table;
}

static void upb_MiniTableEnum_BuildValue(upb_MdEnumDecoder* d, uint32_t val) {
  upb_MiniTableEnum* table = d->enum_table;
  d->enum_value_count++;
  if (table->UPB_PRIVATE(value_count) ||
      (val > 512 && d->enum_value_count < val / 32)) {
    if (table->UPB_PRIVATE(value_count) == 0) {
      UPB_ASSERT(d->enum_data_count == table->UPB_PRIVATE(mask_limit) / 32);
    }
    table = _upb_MiniTable_AddEnumDataMember(d, val);
    table->UPB_PRIVATE(value_count)++;
  } else {
    uint32_t new_mask_limit = ((val / 32) + 1) * 32;
    while (table->UPB_PRIVATE(mask_limit) < new_mask_limit) {
      table = _upb_MiniTable_AddEnumDataMember(d, 0);
      table->UPB_PRIVATE(mask_limit) += 32;
    }
    table->UPB_PRIVATE(data)[val / 32] |= 1ULL << (val % 32);
  }
}

static upb_MiniTableEnum* upb_MtDecoder_DoBuildMiniTableEnum(
    upb_MdEnumDecoder* d, const char* data, size_t len) {
  // If the string is non-empty then it must begin with a version tag.
  if (len) {
    if (*data != kUpb_EncodedVersion_EnumV1) {
      upb_MdDecoder_ErrorJmp(&d->base, "Invalid enum version: %c", *data);
    }
    data++;
    len--;
  }

  upb_MdDecoder_CheckOutOfMemory(&d->base, d->enum_table);

  // Guarantee at least 64 bits of mask without checking mask size.
  d->enum_table->UPB_PRIVATE(mask_limit) = 64;
  d->enum_table = _upb_MiniTable_AddEnumDataMember(d, 0);
  d->enum_table = _upb_MiniTable_AddEnumDataMember(d, 0);

  d->enum_table->UPB_PRIVATE(value_count) = 0;

  const char* ptr = data;
  uint32_t base = 0;

  while (ptr < d->base.end) {
    char ch = *ptr++;
    if (ch <= kUpb_EncodedValue_MaxEnumMask) {
      uint32_t mask = _upb_FromBase92(ch);
      for (int i = 0; i < 5; i++, base++, mask >>= 1) {
        if (mask & 1) upb_MiniTableEnum_BuildValue(d, base);
      }
    } else if (kUpb_EncodedValue_MinSkip <= ch &&
               ch <= kUpb_EncodedValue_MaxSkip) {
      uint32_t skip;
      ptr = upb_MdDecoder_DecodeBase92Varint(&d->base, ptr, ch,
                                             kUpb_EncodedValue_MinSkip,
                                             kUpb_EncodedValue_MaxSkip, &skip);
      base += skip;
    } else {
      upb_MdDecoder_ErrorJmp(&d->base, "Unexpected character: %c", ch);
    }
  }

  return d->enum_table;
}

static upb_MiniTableEnum* upb_MtDecoder_BuildMiniTableEnum(
    upb_MdEnumDecoder* const decoder, const char* const data,
    size_t const len) {
  if (UPB_SETJMP(decoder->base.err) != 0) return NULL;
  return upb_MtDecoder_DoBuildMiniTableEnum(decoder, data, len);
}

upb_MiniTableEnum* upb_MiniTableEnum_Build(const char* data, size_t len,
                                           upb_Arena* arena,
                                           upb_Status* status) {
  uint32_t initial_capacity = 2;
  upb_MdEnumDecoder decoder = {
      .base =
          {
              .end = UPB_PTRADD(data, len),
              .status = status,
          },
      .arena = arena,
      .enum_table =
          upb_Arena_Malloc(arena, upb_MiniTableEnum_Size(initial_capacity)),
      .enum_value_count = 0,
      .enum_data_count = 0,
      .enum_data_capacity = initial_capacity,
  };

  return upb_MtDecoder_BuildMiniTableEnum(&decoder, data, len);
}


#include <stddef.h>
#include <stdint.h>


// Must be last.

// Checks if source and target mini table fields are identical.
//
// If the field is a sub message and sub messages are identical we record
// the association in table.
//
// Hashing the source sub message mini table and it's equivalent in the table
// stops recursing when a cycle is detected and instead just checks if the
// destination table is equal.
static upb_MiniTableEquals_Status upb_deep_check(const upb_MiniTable* src,
                                                 const upb_MiniTable* dst,
                                                 upb_inttable* table,
                                                 upb_Arena** arena) {
  if (src->UPB_PRIVATE(field_count) != dst->UPB_PRIVATE(field_count))
    return kUpb_MiniTableEquals_NotEqual;
  bool marked_src = false;
  for (int i = 0; i < upb_MiniTable_FieldCount(src); i++) {
    const upb_MiniTableField* src_field = upb_MiniTable_GetFieldByIndex(src, i);
    const upb_MiniTableField* dst_field = upb_MiniTable_FindFieldByNumber(
        dst, upb_MiniTableField_Number(src_field));

    if (upb_MiniTableField_CType(src_field) !=
        upb_MiniTableField_CType(dst_field))
      return false;
    if (src_field->UPB_PRIVATE(mode) != dst_field->UPB_PRIVATE(mode))
      return false;
    if (src_field->UPB_PRIVATE(offset) != dst_field->UPB_PRIVATE(offset))
      return false;
    if (src_field->presence != dst_field->presence) return false;
    if (src_field->UPB_PRIVATE(submsg_index) !=
        dst_field->UPB_PRIVATE(submsg_index))
      return kUpb_MiniTableEquals_NotEqual;

    // Go no further if we are only checking for compatibility.
    if (!table) continue;

    if (upb_MiniTableField_CType(src_field) == kUpb_CType_Message) {
      if (!*arena) {
        *arena = upb_Arena_New();
        if (!upb_inttable_init(table, *arena)) {
          return kUpb_MiniTableEquals_OutOfMemory;
        }
      }
      if (!marked_src) {
        marked_src = true;
        upb_value val;
        val.val = (uint64_t)dst;
        if (!upb_inttable_insert(table, (uintptr_t)src, val, *arena)) {
          return kUpb_MiniTableEquals_OutOfMemory;
        }
      }
      const upb_MiniTable* sub_src =
          upb_MiniTable_GetSubMessageTable(src, src_field);
      const upb_MiniTable* sub_dst =
          upb_MiniTable_GetSubMessageTable(dst, dst_field);
      if (sub_src != NULL) {
        upb_value cmp;
        if (upb_inttable_lookup(table, (uintptr_t)sub_src, &cmp)) {
          // We already compared this src before. Check if same dst.
          if (cmp.val != (uint64_t)sub_dst) {
            return kUpb_MiniTableEquals_NotEqual;
          }
        } else {
          // Recurse if not already visited.
          upb_MiniTableEquals_Status s =
              upb_deep_check(sub_src, sub_dst, table, arena);
          if (s != kUpb_MiniTableEquals_Equal) {
            return s;
          }
        }
      }
    }
  }
  return kUpb_MiniTableEquals_Equal;
}

bool upb_MiniTable_Compatible(const upb_MiniTable* src,
                              const upb_MiniTable* dst) {
  return upb_deep_check(src, dst, NULL, NULL);
}

upb_MiniTableEquals_Status upb_MiniTable_Equals(const upb_MiniTable* src,
                                                const upb_MiniTable* dst) {
  // Arena allocated on demand for hash table.
  upb_Arena* arena = NULL;
  // Table to keep track of visited mini tables to guard against cycles.
  upb_inttable table;
  upb_MiniTableEquals_Status status = upb_deep_check(src, dst, &table, &arena);
  if (arena) {
    upb_Arena_Free(arena);
  }
  return status;
}


#include <stddef.h>
#include <stdint.h>
#include <string.h>


// Must be last.

#define EXTREG_KEY_SIZE (sizeof(upb_MiniTable*) + sizeof(uint32_t))

struct upb_ExtensionRegistry {
  upb_Arena* arena;
  upb_strtable exts;  // Key is upb_MiniTable* concatenated with fieldnum.
};

static void extreg_key(char* buf, const upb_MiniTable* l, uint32_t fieldnum) {
  memcpy(buf, &l, sizeof(l));
  memcpy(buf + sizeof(l), &fieldnum, sizeof(fieldnum));
}

upb_ExtensionRegistry* upb_ExtensionRegistry_New(upb_Arena* arena) {
  upb_ExtensionRegistry* r = upb_Arena_Malloc(arena, sizeof(*r));
  if (!r) return NULL;
  r->arena = arena;
  if (!upb_strtable_init(&r->exts, 8, arena)) return NULL;
  return r;
}

UPB_API upb_ExtensionRegistryStatus upb_ExtensionRegistry_Add(
    upb_ExtensionRegistry* r, const upb_MiniTableExtension* e) {
  uint32_t fieldnum = upb_MiniTableExtension_Number(e);
  const upb_MiniTable* extendee = upb_MiniTableExtension_Extendee(e);

  const uint32_t kMaxFieldNumber = (1 << 29) - 1;
  if (fieldnum == 0 ||
      (fieldnum > kMaxFieldNumber && !upb_MiniTable_IsMessageSet(extendee))) {
    return kUpb_ExtensionRegistryStatus_InvalidExtension;
  }

  char buf[EXTREG_KEY_SIZE];
  extreg_key(buf, extendee, fieldnum);

  if (upb_strtable_lookup2(&r->exts, buf, EXTREG_KEY_SIZE, NULL)) {
    return kUpb_ExtensionRegistryStatus_DuplicateEntry;
  }

  if (!upb_strtable_insert(&r->exts, buf, EXTREG_KEY_SIZE,
                           upb_value_constptr(e), r->arena)) {
    return kUpb_ExtensionRegistryStatus_OutOfMemory;
  }
  return kUpb_ExtensionRegistryStatus_Ok;
}

upb_ExtensionRegistryStatus upb_ExtensionRegistry_AddArray(
    upb_ExtensionRegistry* r, const upb_MiniTableExtension** e, size_t count) {
  const upb_MiniTableExtension** start = e;
  const upb_MiniTableExtension** end = UPB_PTRADD(e, count);
  upb_ExtensionRegistryStatus status = kUpb_ExtensionRegistryStatus_Ok;
  for (; e < end; e++) {
    status = upb_ExtensionRegistry_Add(r, *e);
    if (status != kUpb_ExtensionRegistryStatus_Ok) goto failure;
  }
  return kUpb_ExtensionRegistryStatus_Ok;

failure:
  // Back out the entries previously added.
  for (end = e, e = start; e < end; e++) {
    const upb_MiniTableExtension* ext = *e;
    char buf[EXTREG_KEY_SIZE];
    extreg_key(buf, ext->UPB_PRIVATE(extendee),
               upb_MiniTableExtension_Number(ext));
    upb_strtable_remove2(&r->exts, buf, EXTREG_KEY_SIZE, NULL);
  }
  UPB_ASSERT(status != kUpb_ExtensionRegistryStatus_Ok);
  return status;
}

#ifdef UPB_LINKARR_DECLARE

UPB_LINKARR_DECLARE(upb_AllExts, const upb_MiniTableExtension);

bool upb_ExtensionRegistry_AddAllLinkedExtensions(upb_ExtensionRegistry* r) {
  const upb_MiniTableExtension* start = UPB_LINKARR_START(upb_AllExts);
  const upb_MiniTableExtension* stop = UPB_LINKARR_STOP(upb_AllExts);
  for (const upb_MiniTableExtension* p = start; p < stop; p++) {
    // Windows can introduce zero padding, so we have to skip zeroes.
    if (upb_MiniTableExtension_Number(p) != 0) {
      if (upb_ExtensionRegistry_Add(r, p) != kUpb_ExtensionRegistryStatus_Ok) {
        return false;
      }
    }
  }
  return true;
}

#endif  // UPB_LINKARR_DECLARE

const upb_MiniTableExtension* upb_ExtensionRegistry_Lookup(
    const upb_ExtensionRegistry* r, const upb_MiniTable* t, uint32_t num) {
  char buf[EXTREG_KEY_SIZE];
  upb_value v;
  extreg_key(buf, t, num);
  if (upb_strtable_lookup2(&r->exts, buf, EXTREG_KEY_SIZE, &v)) {
    return upb_value_getconstptr(v);
  } else {
    return NULL;
  }
}


#include <stddef.h>


// Must be last.

// A MiniTable for an empty message, used for unlinked sub-messages that are
// built via MiniDescriptors.  Messages that use this MiniTable may possibly
// be linked later, in which case this MiniTable will be replaced with a real
// one.  This pattern is known as "dynamic tree shaking", and it introduces
// complication because sub-messages may either be the "empty" type or the
// "real" type.  A tagged bit indicates the difference.
const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_Empty) = {
    .UPB_PRIVATE(subs) = NULL,
    .UPB_PRIVATE(fields) = NULL,
    .UPB_PRIVATE(size) = sizeof(struct upb_Message),
    .UPB_PRIVATE(field_count) = 0,
    .UPB_PRIVATE(ext) = kUpb_ExtMode_NonExtendable,
    .UPB_PRIVATE(dense_below) = 0,
    .UPB_PRIVATE(table_mask) = -1,
    .UPB_PRIVATE(required_count) = 0,
};

// A MiniTable for a statically tree shaken message.  Messages that use this
// MiniTable are guaranteed to remain unlinked; unlike the empty message, this
// MiniTable is never replaced, which greatly simplifies everything, because the
// type of a sub-message is always known, without consulting a tagged bit.
const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_StaticallyTreeShaken) = {
    .UPB_PRIVATE(subs) = NULL,
    .UPB_PRIVATE(fields) = NULL,
    .UPB_PRIVATE(size) = sizeof(struct upb_Message),
    .UPB_PRIVATE(field_count) = 0,
    .UPB_PRIVATE(ext) = kUpb_ExtMode_NonExtendable,
    .UPB_PRIVATE(dense_below) = 0,
    .UPB_PRIVATE(table_mask) = -1,
    .UPB_PRIVATE(required_count) = 0,
};


#include <stddef.h>
#include <stdint.h>


// Must be last.

const upb_MiniTableField* upb_MiniTable_GetOneof(const upb_MiniTable* m,
                                                 const upb_MiniTableField* f) {
  if (UPB_UNLIKELY(!upb_MiniTableField_IsInOneof(f))) {
    return NULL;
  }
  const upb_MiniTableField* ptr = &m->UPB_PRIVATE(fields)[0];
  const upb_MiniTableField* end =
      &m->UPB_PRIVATE(fields)[m->UPB_PRIVATE(field_count)];
  for (; ptr < end; ptr++) {
    if (ptr->presence == (*f).presence) {
      return ptr;
    }
  }
  return NULL;
}

bool upb_MiniTable_NextOneofField(const upb_MiniTable* m,
                                  const upb_MiniTableField** f) {
  const upb_MiniTableField* ptr = *f;
  const upb_MiniTableField* end =
      &m->UPB_PRIVATE(fields)[m->UPB_PRIVATE(field_count)];
  while (++ptr < end) {
    if (ptr->presence == (*f)->presence) {
      *f = ptr;
      return true;
    }
  }
  return false;
}


#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>


// Our awkward dance for including fasttable only when it is enabled.
#if UPB_FASTTABLE
#define UPB_INCLUDE_FAST_DECODE
#endif

#ifdef UPB_INCLUDE_FAST_DECODE
#endif

#undef UPB_INCLUDE_FAST_DECODE

// Must be last.

// A few fake field types for our tables.
enum {
  kUpb_FakeFieldType_FieldNotFound = 0,
  kUpb_FakeFieldType_MessageSetItem = 19,
};

// DecodeOp: an action to be performed for a wire-type/field-type combination.
enum {
  // Special ops: we don't write data to regular fields for these.
  kUpb_DecodeOp_UnknownField = -1,
  kUpb_DecodeOp_MessageSetItem = -2,

  // Scalar-only ops.
  kUpb_DecodeOp_Scalar1Byte = 0,
  kUpb_DecodeOp_Scalar4Byte = 2,
  kUpb_DecodeOp_Scalar8Byte = 3,

  // Scalar/repeated ops.
  kUpb_DecodeOp_String = 4,
  kUpb_DecodeOp_Bytes = 5,
  kUpb_DecodeOp_SubMessage = 6,

  // Repeated-only ops (also see macros below).
  kUpb_DecodeOp_PackedEnum = 13,
};

// For packed fields it is helpful to be able to recover the lg2 of the data
// size from the op.
#define OP_FIXPCK_LG2(n) (n + 5) /* n in [2, 3] => op in [7, 8] */
#define OP_VARPCK_LG2(n) (n + 9) /* n in [0, 2, 3] => op in [9, 11, 12] */

typedef union {
  bool bool_val;
  uint32_t uint32_val;
  uint64_t uint64_val;
  uint32_t size;
} wireval;

// Ideally these two functions should take the owning MiniTable pointer as a
// first argument, then we could just put them in mini_table/message.h as nice
// clean getters. But we don't have that so instead we gotta write these
// Frankenfunctions that take an array of subtables.
// TODO: Move these to mini_table/ anyway since there are other places
// that could use them.

// Returns the MiniTable corresponding to a given MiniTableField
// from an array of MiniTableSubs.
static const upb_MiniTable* _upb_MiniTableSubs_MessageByField(
    const upb_MiniTableSubInternal* subs, const upb_MiniTableField* field) {
  return *subs[field->UPB_PRIVATE(submsg_index)].UPB_PRIVATE(submsg);
}

// Returns the MiniTableEnum corresponding to a given MiniTableField
// from an array of MiniTableSub.
static const upb_MiniTableEnum* _upb_MiniTableSubs_EnumByField(
    const upb_MiniTableSubInternal* subs, const upb_MiniTableField* field) {
  return subs[field->UPB_PRIVATE(submsg_index)].UPB_PRIVATE(subenum);
}

static void _upb_Decoder_VerifyUtf8(upb_Decoder* d, const char* buf, int len) {
  if (!_upb_Decoder_VerifyUtf8Inline(buf, len)) {
    _upb_Decoder_ErrorJmp(d, kUpb_DecodeStatus_BadUtf8);
  }
}

static bool _upb_Decoder_Reserve(upb_Decoder* d, upb_Array* arr, size_t elem) {
  bool need_realloc =
      arr->UPB_PRIVATE(capacity) - arr->UPB_PRIVATE(size) < elem;
  if (need_realloc && !UPB_PRIVATE(_upb_Array_Realloc)(
                          arr, arr->UPB_PRIVATE(size) + elem, &d->arena)) {
    _upb_Decoder_ErrorJmp(d, kUpb_DecodeStatus_OutOfMemory);
  }
  return need_realloc;
}

typedef struct {
  const char* ptr;
  uint64_t val;
} _upb_DecodeLongVarintReturn;

UPB_NOINLINE
static _upb_DecodeLongVarintReturn _upb_Decoder_DecodeLongVarint(
    const char* ptr, uint64_t val, upb_Decoder* d) {
  uint64_t byte;
  for (int i = 1; i < 10; i++) {
    byte = (uint8_t)ptr[i];
    val += (byte - 1) << (i * 7);
    if (!(byte & 0x80)) {
      return (_upb_DecodeLongVarintReturn){.ptr = ptr + i + 1, .val = val};
    }
  }
  _upb_Decoder_ErrorJmp(d, kUpb_DecodeStatus_Malformed);
}

UPB_NOINLINE
static _upb_DecodeLongVarintReturn _upb_Decoder_DecodeLongTag(const char* ptr,
                                                              uint64_t val,
                                                              upb_Decoder* d) {
  uint64_t byte;
  for (int i = 1; i < 5; i++) {
    byte = (uint8_t)ptr[i];
    val += (byte - 1) << (i * 7);
    if (!(byte & 0x80)) {
      if (val > UINT32_MAX) {
        break;
      }
      return (_upb_DecodeLongVarintReturn){.ptr = ptr + i + 1, .val = val};
    }
  }
  _upb_Decoder_ErrorJmp(d, kUpb_DecodeStatus_Malformed);
}

UPB_FORCEINLINE
const char* _upb_Decoder_DecodeVarint(upb_Decoder* d, const char* ptr,
                                      uint64_t* val) {
  UPB_PRIVATE(upb_EpsCopyInputStream_ConsumeBytes)(&d->input, 10);
  uint64_t byte = (uint8_t)*ptr;
  if (UPB_LIKELY((byte & 0x80) == 0)) {
    *val = byte;
    return ptr + 1;
  } else {
    _upb_DecodeLongVarintReturn res =
        _upb_Decoder_DecodeLongVarint(ptr, byte, d);
    *val = res.val;
    return res.ptr;
  }
}

UPB_FORCEINLINE
const char* _upb_Decoder_DecodeTag(upb_Decoder* d, const char* ptr,
                                   uint32_t* val) {
  UPB_PRIVATE(upb_EpsCopyInputStream_ConsumeBytes)(&d->input, 5);
  uint64_t byte = (uint8_t)*ptr;
  if (UPB_LIKELY((byte & 0x80) == 0)) {
    *val = byte;
    return ptr + 1;
  } else {
    _upb_DecodeLongVarintReturn res = _upb_Decoder_DecodeLongTag(ptr, byte, d);
    *val = res.val;
    return res.ptr;
  }
}

UPB_FORCEINLINE
const char* upb_Decoder_DecodeSize(upb_Decoder* d, const char* ptr,
                                   uint32_t* size) {
  uint64_t size64;
  ptr = _upb_Decoder_DecodeVarint(d, ptr, &size64);
  if (size64 >= INT32_MAX ||
      !upb_EpsCopyInputStream_CheckSize(&d->input, ptr, (int)size64)) {
    _upb_Decoder_ErrorJmp(d, kUpb_DecodeStatus_Malformed);
  }
  *size = size64;
  return ptr;
}

static void _upb_Decoder_MungeInt32(wireval* val) {
  if (!upb_IsLittleEndian()) {
    /* The next stage will memcpy(dst, &val, 4) */
    val->uint32_val = val->uint64_val;
  }
}

static void _upb_Decoder_Munge(const upb_MiniTableField* field, wireval* val) {
  switch (field->UPB_PRIVATE(descriptortype)) {
    case kUpb_FieldType_Bool:
      val->bool_val = val->uint64_val != 0;
      break;
    case kUpb_FieldType_SInt32: {
      uint32_t n = val->uint64_val;
      val->uint32_val = (n >> 1) ^ -(int32_t)(n & 1);
      break;
    }
    case kUpb_FieldType_SInt64: {
      uint64_t n = val->uint64_val;
      val->uint64_val = (n >> 1) ^ -(int64_t)(n & 1);
      break;
    }
    case kUpb_FieldType_Int32:
    case kUpb_FieldType_UInt32:
      _upb_Decoder_MungeInt32(val);
      break;
    case kUpb_FieldType_Enum:
      UPB_UNREACHABLE();
  }
}

static upb_Message* _upb_Decoder_NewSubMessage2(upb_Decoder* d,
                                                const upb_MiniTable* subl,
                                                const upb_MiniTableField* field,
                                                upb_TaggedMessagePtr* target) {
  UPB_ASSERT(subl);
  upb_Message* msg = _upb_Message_New(subl, &d->arena);
  if (!msg) _upb_Decoder_ErrorJmp(d, kUpb_DecodeStatus_OutOfMemory);

  // Extensions should not be unlinked. A message extension should not be
  // registered until its sub-message type is available to be linked.
  bool is_empty = UPB_PRIVATE(_upb_MiniTable_IsEmpty)(subl);
  bool is_extension = field->UPB_PRIVATE(mode) & kUpb_LabelFlags_IsExtension;
  UPB_ASSERT(!(is_empty && is_extension));

  if (is_empty && !(d->options & kUpb_DecodeOption_ExperimentalAllowUnlinked)) {
    _upb_Decoder_ErrorJmp(d, kUpb_DecodeStatus_UnlinkedSubMessage);
  }

  upb_TaggedMessagePtr tagged =
      UPB_PRIVATE(_upb_TaggedMessagePtr_Pack)(msg, is_empty);
  memcpy(target, &tagged, sizeof(tagged));
  return msg;
}

static upb_Message* _upb_Decoder_NewSubMessage(
    upb_Decoder* d, const upb_MiniTableSubInternal* subs,
    const upb_MiniTableField* field, upb_TaggedMessagePtr* target) {
  const upb_MiniTable* subl = _upb_MiniTableSubs_MessageByField(subs, field);
  return _upb_Decoder_NewSubMessage2(d, subl, field, target);
}

static upb_Message* _upb_Decoder_ReuseSubMessage(
    upb_Decoder* d, const upb_MiniTableSubInternal* subs,
    const upb_MiniTableField* field, upb_TaggedMessagePtr* target) {
  upb_TaggedMessagePtr tagged = *target;
  const upb_MiniTable* subl = _upb_MiniTableSubs_MessageByField(subs, field);
  UPB_ASSERT(subl);
  if (!upb_TaggedMessagePtr_IsEmpty(tagged) ||
      UPB_PRIVATE(_upb_MiniTable_IsEmpty)(subl)) {
    return UPB_PRIVATE(_upb_TaggedMessagePtr_GetMessage)(tagged);
  }

  // We found an empty message from a previous parse that was performed before
  // this field was linked.  But it is linked now, so we want to allocate a new
  // message of the correct type and promote data into it before continuing.
  upb_Message* existing =
      UPB_PRIVATE(_upb_TaggedMessagePtr_GetEmptyMessage)(tagged);
  upb_Message* promoted = _upb_Decoder_NewSubMessage(d, subs, field, target);
  uintptr_t iter = kUpb_Message_UnknownBegin;
  upb_StringView unknown;
  while (upb_Message_NextUnknown(existing, &unknown, &iter)) {
    upb_DecodeStatus status =
        upb_Decode(unknown.data, unknown.size, promoted, subl, d->extreg,
                   d->options, &d->arena);
    if (status != kUpb_DecodeStatus_Ok) _upb_Decoder_ErrorJmp(d, status);
  }
  return promoted;
}

static const char* _upb_Decoder_ReadString(upb_Decoder* d, const char* ptr,
                                           int size, upb_StringView* str) {
  const char* str_ptr = ptr;
  ptr = upb_EpsCopyInputStream_ReadString(&d->input, &str_ptr, size, &d->arena);
  if (!ptr) _upb_Decoder_ErrorJmp(d, kUpb_DecodeStatus_OutOfMemory);
  str->data = str_ptr;
  str->size = size;
  return ptr;
}

UPB_FORCEINLINE
const char* _upb_Decoder_RecurseSubMessage(upb_Decoder* d, const char* ptr,
                                           upb_Message* submsg,
                                           const upb_MiniTable* subl,
                                           uint32_t expected_end_group) {
  if (--d->depth < 0) {
    _upb_Decoder_ErrorJmp(d, kUpb_DecodeStatus_MaxDepthExceeded);
  }
  ptr = _upb_Decoder_DecodeMessage(d, ptr, submsg, subl);
  d->depth++;
  if (d->end_group != expected_end_group) {
    _upb_Decoder_ErrorJmp(d, kUpb_DecodeStatus_Malformed);
  }
  return ptr;
}

UPB_FORCEINLINE
const char* _upb_Decoder_DecodeSubMessage(upb_Decoder* d, const char* ptr,
                                          upb_Message* submsg,
                                          const upb_MiniTableSubInternal* subs,
                                          const upb_MiniTableField* field,
                                          int size) {
  int saved_delta = upb_EpsCopyInputStream_PushLimit(&d->input, ptr, size);
  const upb_MiniTable* subl = _upb_MiniTableSubs_MessageByField(subs, field);
  UPB_ASSERT(subl);
  ptr = _upb_Decoder_RecurseSubMessage(d, ptr, submsg, subl, DECODE_NOGROUP);
  upb_EpsCopyInputStream_PopLimit(&d->input, ptr, saved_delta);
  return ptr;
}

UPB_FORCEINLINE
const char* _upb_Decoder_DecodeGroup(upb_Decoder* d, const char* ptr,
                                     upb_Message* submsg,
                                     const upb_MiniTable* subl,
                                     uint32_t number) {
  if (_upb_Decoder_IsDone(d, &ptr)) {
    _upb_Decoder_ErrorJmp(d, kUpb_DecodeStatus_Malformed);
  }
  ptr = _upb_Decoder_RecurseSubMessage(d, ptr, submsg, subl, number);
  d->end_group = DECODE_NOGROUP;
  return ptr;
}

UPB_FORCEINLINE
const char* _upb_Decoder_DecodeUnknownGroup(upb_Decoder* d, const char* ptr,
                                            uint32_t number) {
  return _upb_Decoder_DecodeGroup(d, ptr, NULL, NULL, number);
}

UPB_FORCEINLINE
const char* _upb_Decoder_DecodeKnownGroup(upb_Decoder* d, const char* ptr,
                                          upb_Message* submsg,
                                          const upb_MiniTableSubInternal* subs,
                                          const upb_MiniTableField* field) {
  const upb_MiniTable* subl = _upb_MiniTableSubs_MessageByField(subs, field);
  UPB_ASSERT(subl);
  return _upb_Decoder_DecodeGroup(d, ptr, submsg, subl,
                                  field->UPB_PRIVATE(number));
}

#define kUpb_Decoder_EncodeVarint32MaxSize 5
static char* upb_Decoder_EncodeVarint32(uint32_t val, char* ptr) {
  do {
    uint8_t byte = val & 0x7fU;
    val >>= 7;
    if (val) byte |= 0x80U;
    *(ptr++) = byte;
  } while (val);
  return ptr;
}

UPB_FORCEINLINE
void _upb_Decoder_AddEnumValueToUnknown(upb_Decoder* d, upb_Message* msg,
                                        const upb_MiniTableField* field,
                                        wireval* val) {
  // Unrecognized enum goes into unknown fields.
  // For packed fields the tag could be arbitrarily far in the past,
  // so we just re-encode the tag and value here.
  const uint32_t tag =
      ((uint32_t)field->UPB_PRIVATE(number) << 3) | kUpb_WireType_Varint;
  upb_Message* unknown_msg =
      field->UPB_PRIVATE(mode) & kUpb_LabelFlags_IsExtension ? d->original_msg
                                                             : msg;
  char buf[2 * kUpb_Decoder_EncodeVarint32MaxSize];
  char* end = buf;
  end = upb_Decoder_EncodeVarint32(tag, end);
  end = upb_Decoder_EncodeVarint32(val->uint64_val, end);

  if (!UPB_PRIVATE(_upb_Message_AddUnknown)(unknown_msg, buf, end - buf,
                                            &d->arena, NULL)) {
    _upb_Decoder_ErrorJmp(d, kUpb_DecodeStatus_OutOfMemory);
  }
}

UPB_FORCEINLINE
const char* _upb_Decoder_DecodeFixedPacked(upb_Decoder* d, const char* ptr,
                                           upb_Array* arr, wireval* val,
                                           const upb_MiniTableField* field,
                                           int lg2) {
  int mask = (1 << lg2) - 1;
  size_t count = val->size >> lg2;
  if ((val->size & mask) != 0) {
    // Length isn't a round multiple of elem size.
    _upb_Decoder_ErrorJmp(d, kUpb_DecodeStatus_Malformed);
  }
  _upb_Decoder_Reserve(d, arr, count);
  void* mem = UPB_PTR_AT(upb_Array_MutableDataPtr(arr),
                         arr->UPB_PRIVATE(size) << lg2, void);
  arr->UPB_PRIVATE(size) += count;
  // Note: if/when the decoder supports multi-buffer input, we will need to
  // handle buffer seams here.
  if (upb_IsLittleEndian()) {
    ptr = upb_EpsCopyInputStream_Copy(&d->input, ptr, mem, val->size);
  } else {
    int delta = upb_EpsCopyInputStream_PushLimit(&d->input, ptr, val->size);
    char* dst = mem;
    while (!_upb_Decoder_IsDone(d, &ptr)) {
      if (lg2 == 2) {
        ptr = upb_WireReader_ReadFixed32(ptr, dst, &d->input);
        dst += 4;
      } else {
        UPB_ASSERT(lg2 == 3);
        ptr = upb_WireReader_ReadFixed64(ptr, dst, &d->input);
        dst += 8;
      }
    }
    upb_EpsCopyInputStream_PopLimit(&d->input, ptr, delta);
  }

  return ptr;
}

UPB_FORCEINLINE
const char* _upb_Decoder_DecodeVarintPacked(upb_Decoder* d, const char* ptr,
                                            upb_Array* arr, wireval* val,
                                            const upb_MiniTableField* field,
                                            int lg2) {
  int scale = 1 << lg2;
  int saved_limit = upb_EpsCopyInputStream_PushLimit(&d->input, ptr, val->size);
  char* out = UPB_PTR_AT(upb_Array_MutableDataPtr(arr),
                         arr->UPB_PRIVATE(size) << lg2, void);
  while (!_upb_Decoder_IsDone(d, &ptr)) {
    wireval elem;
    ptr = _upb_Decoder_DecodeVarint(d, ptr, &elem.uint64_val);
    _upb_Decoder_Munge(field, &elem);
    if (_upb_Decoder_Reserve(d, arr, 1)) {
      out = UPB_PTR_AT(upb_Array_MutableDataPtr(arr),
                       arr->UPB_PRIVATE(size) << lg2, void);
    }
    arr->UPB_PRIVATE(size)++;
    memcpy(out, &elem, scale);
    out += scale;
  }
  upb_EpsCopyInputStream_PopLimit(&d->input, ptr, saved_limit);
  return ptr;
}

UPB_NOINLINE
static const char* _upb_Decoder_DecodeEnumPacked(
    upb_Decoder* d, const char* ptr, upb_Message* msg, upb_Array* arr,
    const upb_MiniTableSubInternal* subs, const upb_MiniTableField* field,
    wireval* val) {
  const upb_MiniTableEnum* e = _upb_MiniTableSubs_EnumByField(subs, field);
  int saved_limit = upb_EpsCopyInputStream_PushLimit(&d->input, ptr, val->size);
  char* out = UPB_PTR_AT(upb_Array_MutableDataPtr(arr),
                         arr->UPB_PRIVATE(size) * 4, void);
  while (!_upb_Decoder_IsDone(d, &ptr)) {
    wireval elem;
    ptr = _upb_Decoder_DecodeVarint(d, ptr, &elem.uint64_val);
    if (!upb_MiniTableEnum_CheckValue(e, elem.uint64_val)) {
      _upb_Decoder_AddEnumValueToUnknown(d, msg, field, &elem);
      continue;
    }
    if (_upb_Decoder_Reserve(d, arr, 1)) {
      out = UPB_PTR_AT(upb_Array_MutableDataPtr(arr),
                       arr->UPB_PRIVATE(size) * 4, void);
    }
    arr->UPB_PRIVATE(size)++;
    memcpy(out, &elem, 4);
    out += 4;
  }
  upb_EpsCopyInputStream_PopLimit(&d->input, ptr, saved_limit);
  return ptr;
}

static upb_Array* _upb_Decoder_CreateArray(upb_Decoder* d,
                                           const upb_MiniTableField* field) {
  const upb_FieldType field_type = field->UPB_PRIVATE(descriptortype);
  const size_t lg2 = UPB_PRIVATE(_upb_FieldType_SizeLg2)(field_type);
  upb_Array* ret = UPB_PRIVATE(_upb_Array_New)(&d->arena, 4, lg2);
  if (!ret) _upb_Decoder_ErrorJmp(d, kUpb_DecodeStatus_OutOfMemory);
  return ret;
}

static const char* _upb_Decoder_DecodeToArray(
    upb_Decoder* d, const char* ptr, upb_Message* msg,
    const upb_MiniTableSubInternal* subs, const upb_MiniTableField* field,
    wireval* val, int op) {
  upb_Array** arrp = UPB_PTR_AT(msg, field->UPB_PRIVATE(offset), void);
  upb_Array* arr = *arrp;
  void* mem;

  if (arr) {
    _upb_Decoder_Reserve(d, arr, 1);
  } else {
    arr = _upb_Decoder_CreateArray(d, field);
    *arrp = arr;
  }

  switch (op) {
    case kUpb_DecodeOp_Scalar1Byte:
    case kUpb_DecodeOp_Scalar4Byte:
    case kUpb_DecodeOp_Scalar8Byte:
      /* Append scalar value. */
      mem = UPB_PTR_AT(upb_Array_MutableDataPtr(arr),
                       arr->UPB_PRIVATE(size) << op, void);
      arr->UPB_PRIVATE(size)++;
      memcpy(mem, val, 1 << op);
      return ptr;
    case kUpb_DecodeOp_String:
      _upb_Decoder_VerifyUtf8(d, ptr, val->size);
      /* Fallthrough. */
    case kUpb_DecodeOp_Bytes: {
      /* Append bytes. */
      upb_StringView* str = (upb_StringView*)upb_Array_MutableDataPtr(arr) +
                            arr->UPB_PRIVATE(size);
      arr->UPB_PRIVATE(size)++;
      return _upb_Decoder_ReadString(d, ptr, val->size, str);
    }
    case kUpb_DecodeOp_SubMessage: {
      /* Append submessage / group. */
      upb_TaggedMessagePtr* target = UPB_PTR_AT(
          upb_Array_MutableDataPtr(arr), arr->UPB_PRIVATE(size) * sizeof(void*),
          upb_TaggedMessagePtr);
      upb_Message* submsg = _upb_Decoder_NewSubMessage(d, subs, field, target);
      arr->UPB_PRIVATE(size)++;
      if (UPB_UNLIKELY(field->UPB_PRIVATE(descriptortype) ==
                       kUpb_FieldType_Group)) {
        return _upb_Decoder_DecodeKnownGroup(d, ptr, submsg, subs, field);
      } else {
        return _upb_Decoder_DecodeSubMessage(d, ptr, submsg, subs, field,
                                             val->size);
      }
    }
    case OP_FIXPCK_LG2(2):
    case OP_FIXPCK_LG2(3):
      return _upb_Decoder_DecodeFixedPacked(d, ptr, arr, val, field,
                                            op - OP_FIXPCK_LG2(0));
    case OP_VARPCK_LG2(0):
    case OP_VARPCK_LG2(2):
    case OP_VARPCK_LG2(3):
      return _upb_Decoder_DecodeVarintPacked(d, ptr, arr, val, field,
                                             op - OP_VARPCK_LG2(0));
    case kUpb_DecodeOp_PackedEnum:
      return _upb_Decoder_DecodeEnumPacked(d, ptr, msg, arr, subs, field, val);
    default:
      UPB_UNREACHABLE();
  }
}

static upb_Map* _upb_Decoder_CreateMap(upb_Decoder* d,
                                       const upb_MiniTable* entry) {
  // Maps descriptor type -> upb map size
  static const uint8_t kSizeInMap[] = {
      [0] = -1,  // invalid descriptor type
      [kUpb_FieldType_Double] = 8,
      [kUpb_FieldType_Float] = 4,
      [kUpb_FieldType_Int64] = 8,
      [kUpb_FieldType_UInt64] = 8,
      [kUpb_FieldType_Int32] = 4,
      [kUpb_FieldType_Fixed64] = 8,
      [kUpb_FieldType_Fixed32] = 4,
      [kUpb_FieldType_Bool] = 1,
      [kUpb_FieldType_String] = UPB_MAPTYPE_STRING,
      [kUpb_FieldType_Group] = sizeof(void*),
      [kUpb_FieldType_Message] = sizeof(void*),
      [kUpb_FieldType_Bytes] = UPB_MAPTYPE_STRING,
      [kUpb_FieldType_UInt32] = 4,
      [kUpb_FieldType_Enum] = 4,
      [kUpb_FieldType_SFixed32] = 4,
      [kUpb_FieldType_SFixed64] = 8,
      [kUpb_FieldType_SInt32] = 4,
      [kUpb_FieldType_SInt64] = 8,
  };

  const upb_MiniTableField* key_field = &entry->UPB_PRIVATE(fields)[0];
  const upb_MiniTableField* val_field = &entry->UPB_PRIVATE(fields)[1];
  char key_size = kSizeInMap[key_field->UPB_PRIVATE(descriptortype)];
  char val_size = kSizeInMap[val_field->UPB_PRIVATE(descriptortype)];
  UPB_ASSERT(key_field->UPB_PRIVATE(offset) == offsetof(upb_MapEntry, k));
  UPB_ASSERT(val_field->UPB_PRIVATE(offset) == offsetof(upb_MapEntry, v));
  upb_Map* ret = _upb_Map_New(&d->arena, key_size, val_size);
  if (!ret) _upb_Decoder_ErrorJmp(d, kUpb_DecodeStatus_OutOfMemory);
  return ret;
}

UPB_NOINLINE static void _upb_Decoder_AddMapEntryUnknown(
    upb_Decoder* d, upb_Message* msg, const upb_MiniTableField* field,
    upb_Message* ent_msg, const upb_MiniTable* entry) {
  char* buf;
  size_t size;
  upb_EncodeStatus status =
      upb_Encode(ent_msg, entry, 0, &d->arena, &buf, &size);
  if (status != kUpb_EncodeStatus_Ok) {
    _upb_Decoder_ErrorJmp(d, kUpb_DecodeStatus_OutOfMemory);
  }
  char delim_buf[2 * kUpb_Decoder_EncodeVarint32MaxSize];
  char* delim_end = delim_buf;
  uint32_t tag =
      ((uint32_t)field->UPB_PRIVATE(number) << 3) | kUpb_WireType_Delimited;
  delim_end = upb_Decoder_EncodeVarint32(tag, delim_end);
  delim_end = upb_Decoder_EncodeVarint32(size, delim_end);
  upb_StringView unknown[] = {
      {delim_buf, delim_end - delim_buf},
      {buf, size},
  };

  if (!UPB_PRIVATE(_upb_Message_AddUnknownV)(msg, &d->arena, unknown, 2)) {
    _upb_Decoder_ErrorJmp(d, kUpb_DecodeStatus_OutOfMemory);
  }
}

static const char* _upb_Decoder_DecodeToMap(
    upb_Decoder* d, const char* ptr, upb_Message* msg,
    const upb_MiniTableSubInternal* subs, const upb_MiniTableField* field,
    wireval* val) {
  upb_Map** map_p = UPB_PTR_AT(msg, field->UPB_PRIVATE(offset), upb_Map*);
  upb_Map* map = *map_p;
  upb_MapEntry ent;
  UPB_ASSERT(upb_MiniTableField_Type(field) == kUpb_FieldType_Message);
  const upb_MiniTable* entry = _upb_MiniTableSubs_MessageByField(subs, field);

  UPB_ASSERT(entry);
  UPB_ASSERT(entry->UPB_PRIVATE(field_count) == 2);
  UPB_ASSERT(upb_MiniTableField_IsScalar(&entry->UPB_PRIVATE(fields)[0]));
  UPB_ASSERT(upb_MiniTableField_IsScalar(&entry->UPB_PRIVATE(fields)[1]));

  if (!map) {
    map = _upb_Decoder_CreateMap(d, entry);
    *map_p = map;
  }

  // Parse map entry.
  memset(&ent, 0, sizeof(ent));

  if (entry->UPB_PRIVATE(fields)[1].UPB_PRIVATE(descriptortype) ==
          kUpb_FieldType_Message ||
      entry->UPB_PRIVATE(fields)[1].UPB_PRIVATE(descriptortype) ==
          kUpb_FieldType_Group) {
    // Create proactively to handle the case where it doesn't appear.
    upb_TaggedMessagePtr msg;
    _upb_Decoder_NewSubMessage(d, entry->UPB_PRIVATE(subs),
                               &entry->UPB_PRIVATE(fields)[1], &msg);
    ent.v.val = upb_value_uintptr(msg);
  }

  ptr = _upb_Decoder_DecodeSubMessage(d, ptr, &ent.message, subs, field,
                                      val->size);
  if (upb_Message_HasUnknown(&ent.message)) {
    _upb_Decoder_AddMapEntryUnknown(d, msg, field, &ent.message, entry);
  } else {
    if (_upb_Map_Insert(map, &ent.k, map->key_size, &ent.v, map->val_size,
                        &d->arena) == kUpb_MapInsertStatus_OutOfMemory) {
      _upb_Decoder_ErrorJmp(d, kUpb_DecodeStatus_OutOfMemory);
    }
  }
  return ptr;
}

static const char* _upb_Decoder_DecodeToSubMessage(
    upb_Decoder* d, const char* ptr, upb_Message* msg,
    const upb_MiniTableSubInternal* subs, const upb_MiniTableField* field,
    wireval* val, int op) {
  void* mem = UPB_PTR_AT(msg, field->UPB_PRIVATE(offset), void);
  int type = field->UPB_PRIVATE(descriptortype);

  // Set presence if necessary.
  if (UPB_PRIVATE(_upb_MiniTableField_HasHasbit)(field)) {
    UPB_PRIVATE(_upb_Message_SetHasbit)(msg, field);
  } else if (upb_MiniTableField_IsInOneof(field)) {
    // Oneof case
    uint32_t* oneof_case = UPB_PRIVATE(_upb_Message_OneofCasePtr)(msg, field);
    if (op == kUpb_DecodeOp_SubMessage &&
        *oneof_case != field->UPB_PRIVATE(number)) {
      memset(mem, 0, sizeof(void*));
    }
    *oneof_case = field->UPB_PRIVATE(number);
  }

  // Store into message.
  switch (op) {
    case kUpb_DecodeOp_SubMessage: {
      upb_TaggedMessagePtr* submsgp = mem;
      upb_Message* submsg;
      if (*submsgp) {
        submsg = _upb_Decoder_ReuseSubMessage(d, subs, field, submsgp);
      } else {
        submsg = _upb_Decoder_NewSubMessage(d, subs, field, submsgp);
      }
      if (UPB_UNLIKELY(type == kUpb_FieldType_Group)) {
        ptr = _upb_Decoder_DecodeKnownGroup(d, ptr, submsg, subs, field);
      } else {
        ptr = _upb_Decoder_DecodeSubMessage(d, ptr, submsg, subs, field,
                                            val->size);
      }
      break;
    }
    case kUpb_DecodeOp_String:
      _upb_Decoder_VerifyUtf8(d, ptr, val->size);
      /* Fallthrough. */
    case kUpb_DecodeOp_Bytes:
      return _upb_Decoder_ReadString(d, ptr, val->size, mem);
    case kUpb_DecodeOp_Scalar8Byte:
      memcpy(mem, val, 8);
      break;
    case kUpb_DecodeOp_Scalar4Byte:
      memcpy(mem, val, 4);
      break;
    case kUpb_DecodeOp_Scalar1Byte:
      memcpy(mem, val, 1);
      break;
    default:
      UPB_UNREACHABLE();
  }

  return ptr;
}

static const char* upb_Decoder_SkipField(upb_Decoder* d, const char* ptr,
                                         uint32_t tag) {
  int field_number = tag >> 3;
  int wire_type = tag & 7;
  switch (wire_type) {
    case kUpb_WireType_Varint: {
      uint64_t val;
      return _upb_Decoder_DecodeVarint(d, ptr, &val);
    }
    case kUpb_WireType_64Bit:
      return ptr + 8;
    case kUpb_WireType_32Bit:
      return ptr + 4;
    case kUpb_WireType_Delimited: {
      uint32_t size;
      ptr = upb_Decoder_DecodeSize(d, ptr, &size);
      return ptr + size;
    }
    case kUpb_WireType_StartGroup:
      return _upb_Decoder_DecodeUnknownGroup(d, ptr, field_number);
    default:
      _upb_Decoder_ErrorJmp(d, kUpb_DecodeStatus_Malformed);
  }
}

enum {
  kStartItemTag = ((kUpb_MsgSet_Item << 3) | kUpb_WireType_StartGroup),
  kEndItemTag = ((kUpb_MsgSet_Item << 3) | kUpb_WireType_EndGroup),
  kTypeIdTag = ((kUpb_MsgSet_TypeId << 3) | kUpb_WireType_Varint),
  kMessageTag = ((kUpb_MsgSet_Message << 3) | kUpb_WireType_Delimited),
};

static void upb_Decoder_AddKnownMessageSetItem(
    upb_Decoder* d, upb_Message* msg, const upb_MiniTableExtension* item_mt,
    const char* data, uint32_t size) {
  upb_Extension* ext =
      UPB_PRIVATE(_upb_Message_GetOrCreateExtension)(msg, item_mt, &d->arena);
  if (UPB_UNLIKELY(!ext)) {
    _upb_Decoder_ErrorJmp(d, kUpb_DecodeStatus_OutOfMemory);
  }
  upb_Message* submsg = _upb_Decoder_NewSubMessage2(
      d, ext->ext->UPB_PRIVATE(sub).UPB_PRIVATE(submsg),
      &ext->ext->UPB_PRIVATE(field), &ext->data.tagged_msg_val);
  upb_DecodeStatus status = upb_Decode(
      data, size, submsg, upb_MiniTableExtension_GetSubMessage(item_mt),
      d->extreg, d->options, &d->arena);
  if (status != kUpb_DecodeStatus_Ok) _upb_Decoder_ErrorJmp(d, status);
}

static void upb_Decoder_AddUnknownMessageSetItem(upb_Decoder* d,
                                                 upb_Message* msg,
                                                 uint32_t type_id,
                                                 const char* message_data,
                                                 uint32_t message_size) {
  char buf[6 * kUpb_Decoder_EncodeVarint32MaxSize];
  char* ptr = buf;
  ptr = upb_Decoder_EncodeVarint32(kStartItemTag, ptr);
  ptr = upb_Decoder_EncodeVarint32(kTypeIdTag, ptr);
  ptr = upb_Decoder_EncodeVarint32(type_id, ptr);
  ptr = upb_Decoder_EncodeVarint32(kMessageTag, ptr);
  ptr = upb_Decoder_EncodeVarint32(message_size, ptr);
  char* split = ptr;

  ptr = upb_Decoder_EncodeVarint32(kEndItemTag, ptr);
  char* end = ptr;
  upb_StringView unknown[] = {
      {buf, split - buf},
      {message_data, message_size},
      {split, end - split},
  };
  if (!UPB_PRIVATE(_upb_Message_AddUnknownV)(msg, &d->arena, unknown, 3)) {
    _upb_Decoder_ErrorJmp(d, kUpb_DecodeStatus_OutOfMemory);
  }
}

static void upb_Decoder_AddMessageSetItem(upb_Decoder* d, upb_Message* msg,
                                          const upb_MiniTable* t,
                                          uint32_t type_id, const char* data,
                                          uint32_t size) {
  const upb_MiniTableExtension* item_mt =
      upb_ExtensionRegistry_Lookup(d->extreg, t, type_id);
  if (item_mt) {
    upb_Decoder_AddKnownMessageSetItem(d, msg, item_mt, data, size);
  } else {
    upb_Decoder_AddUnknownMessageSetItem(d, msg, type_id, data, size);
  }
}

static const char* upb_Decoder_DecodeMessageSetItem(
    upb_Decoder* d, const char* ptr, upb_Message* msg,
    const upb_MiniTable* layout) {
  uint32_t type_id = 0;
  upb_StringView preserved = {NULL, 0};
  typedef enum {
    kUpb_HaveId = 1 << 0,
    kUpb_HavePayload = 1 << 1,
  } StateMask;
  StateMask state_mask = 0;
  while (!_upb_Decoder_IsDone(d, &ptr)) {
    uint32_t tag;
    ptr = _upb_Decoder_DecodeTag(d, ptr, &tag);
    switch (tag) {
      case kEndItemTag:
        return ptr;
      case kTypeIdTag: {
        uint64_t tmp;
        ptr = _upb_Decoder_DecodeVarint(d, ptr, &tmp);
        if (state_mask & kUpb_HaveId) break;  // Ignore dup.
        state_mask |= kUpb_HaveId;
        type_id = tmp;
        if (state_mask & kUpb_HavePayload) {
          upb_Decoder_AddMessageSetItem(d, msg, layout, type_id, preserved.data,
                                        preserved.size);
        }
        break;
      }
      case kMessageTag: {
        uint32_t size;
        ptr = upb_Decoder_DecodeSize(d, ptr, &size);
        const char* data = upb_EpsCopyInputStream_GetInputPtr(&d->input, ptr);
        ptr += size;
        if (state_mask & kUpb_HavePayload) break;  // Ignore dup.
        state_mask |= kUpb_HavePayload;
        if (state_mask & kUpb_HaveId) {
          upb_Decoder_AddMessageSetItem(d, msg, layout, type_id, data, size);
        } else {
          // Out of order, we must preserve the payload.
          preserved.data = data;
          preserved.size = size;
        }
        break;
      }
      default:
        // We do not preserve unexpected fields inside a message set item.
        ptr = upb_Decoder_SkipField(d, ptr, tag);
        break;
    }
  }
  _upb_Decoder_ErrorJmp(d, kUpb_DecodeStatus_Malformed);
}

static upb_MiniTableField upb_Decoder_FieldNotFoundField = {
    0, 0, 0, 0, kUpb_FakeFieldType_FieldNotFound, 0};

UPB_NOINLINE const upb_MiniTableField* _upb_Decoder_FindExtensionField(
    upb_Decoder* d, const upb_MiniTable* t, uint32_t field_number, int ext_mode,
    int wire_type) {
  // Treat a message set as an extendable message if it is a delimited field.
  // This provides compatibility with encoders that are unaware of message
  // sets and serialize them as normal extensions.
  if (ext_mode == kUpb_ExtMode_Extendable ||
      (ext_mode == kUpb_ExtMode_IsMessageSet &&
       wire_type == kUpb_WireType_Delimited)) {
    const upb_MiniTableExtension* ext =
        upb_ExtensionRegistry_Lookup(d->extreg, t, field_number);
    if (ext) return &ext->UPB_PRIVATE(field);
  } else if (ext_mode == kUpb_ExtMode_IsMessageSet) {
    if (field_number == kUpb_MsgSet_Item) {
      static upb_MiniTableField item = {
          0, 0, 0, 0, kUpb_FakeFieldType_MessageSetItem, 0};
      return &item;
    }
  }
  return &upb_Decoder_FieldNotFoundField;
}

static const upb_MiniTableField* _upb_Decoder_FindField(upb_Decoder* d,
                                                        const upb_MiniTable* t,
                                                        uint32_t field_number,
                                                        int wire_type) {
  if (t == NULL) return &upb_Decoder_FieldNotFoundField;

  const upb_MiniTableField* field =
      upb_MiniTable_FindFieldByNumber(t, field_number);
  if (field) return field;

  if (d->extreg && t->UPB_PRIVATE(ext)) {
    return _upb_Decoder_FindExtensionField(d, t, field_number,
                                           t->UPB_PRIVATE(ext), wire_type);
  }

  return &upb_Decoder_FieldNotFoundField;  // Unknown field.
}

static int _upb_Decoder_GetVarintOp(const upb_MiniTableField* field) {
  static const int8_t kVarintOps[] = {
      [kUpb_FakeFieldType_FieldNotFound] = kUpb_DecodeOp_UnknownField,
      [kUpb_FieldType_Double] = kUpb_DecodeOp_UnknownField,
      [kUpb_FieldType_Float] = kUpb_DecodeOp_UnknownField,
      [kUpb_FieldType_Int64] = kUpb_DecodeOp_Scalar8Byte,
      [kUpb_FieldType_UInt64] = kUpb_DecodeOp_Scalar8Byte,
      [kUpb_FieldType_Int32] = kUpb_DecodeOp_Scalar4Byte,
      [kUpb_FieldType_Fixed64] = kUpb_DecodeOp_UnknownField,
      [kUpb_FieldType_Fixed32] = kUpb_DecodeOp_UnknownField,
      [kUpb_FieldType_Bool] = kUpb_DecodeOp_Scalar1Byte,
      [kUpb_FieldType_String] = kUpb_DecodeOp_UnknownField,
      [kUpb_FieldType_Group] = kUpb_DecodeOp_UnknownField,
      [kUpb_FieldType_Message] = kUpb_DecodeOp_UnknownField,
      [kUpb_FieldType_Bytes] = kUpb_DecodeOp_UnknownField,
      [kUpb_FieldType_UInt32] = kUpb_DecodeOp_Scalar4Byte,
      [kUpb_FieldType_Enum] = kUpb_DecodeOp_Scalar4Byte,
      [kUpb_FieldType_SFixed32] = kUpb_DecodeOp_UnknownField,
      [kUpb_FieldType_SFixed64] = kUpb_DecodeOp_UnknownField,
      [kUpb_FieldType_SInt32] = kUpb_DecodeOp_Scalar4Byte,
      [kUpb_FieldType_SInt64] = kUpb_DecodeOp_Scalar8Byte,
      [kUpb_FakeFieldType_MessageSetItem] = kUpb_DecodeOp_UnknownField,
  };

  return kVarintOps[field->UPB_PRIVATE(descriptortype)];
}

UPB_FORCEINLINE
void _upb_Decoder_CheckUnlinked(upb_Decoder* d, const upb_MiniTable* mt,
                                const upb_MiniTableField* field, int* op) {
  // If sub-message is not linked, treat as unknown.
  if (field->UPB_PRIVATE(mode) & kUpb_LabelFlags_IsExtension) return;
  const upb_MiniTable* mt_sub =
      _upb_MiniTableSubs_MessageByField(mt->UPB_PRIVATE(subs), field);
  if ((d->options & kUpb_DecodeOption_ExperimentalAllowUnlinked) ||
      !UPB_PRIVATE(_upb_MiniTable_IsEmpty)(mt_sub)) {
    return;
  }
#ifndef NDEBUG
  const upb_MiniTableField* oneof = upb_MiniTable_GetOneof(mt, field);
  if (oneof) {
    // All other members of the oneof must be message fields that are also
    // unlinked.
    do {
      UPB_ASSERT(upb_MiniTableField_CType(oneof) == kUpb_CType_Message);
      const upb_MiniTable* oneof_sub =
          *mt->UPB_PRIVATE(subs)[oneof->UPB_PRIVATE(submsg_index)].UPB_PRIVATE(
              submsg);
      UPB_ASSERT(!oneof_sub);
    } while (upb_MiniTable_NextOneofField(mt, &oneof));
  }
#endif  // NDEBUG
  *op = kUpb_DecodeOp_UnknownField;
}

UPB_FORCEINLINE
void _upb_Decoder_MaybeVerifyUtf8(upb_Decoder* d,
                                  const upb_MiniTableField* field, int* op) {
  if ((field->UPB_ONLYBITS(mode) & kUpb_LabelFlags_IsAlternate) &&
      UPB_UNLIKELY(d->options & kUpb_DecodeOption_AlwaysValidateUtf8))
    *op = kUpb_DecodeOp_String;
}

static int _upb_Decoder_GetDelimitedOp(upb_Decoder* d, const upb_MiniTable* mt,
                                       const upb_MiniTableField* field) {
  enum { kRepeatedBase = 19 };

  static const int8_t kDelimitedOps[] = {
      // For non-repeated field type.
      [kUpb_FakeFieldType_FieldNotFound] =
          kUpb_DecodeOp_UnknownField,  // Field not found.
      [kUpb_FieldType_Double] = kUpb_DecodeOp_UnknownField,
      [kUpb_FieldType_Float] = kUpb_DecodeOp_UnknownField,
      [kUpb_FieldType_Int64] = kUpb_DecodeOp_UnknownField,
      [kUpb_FieldType_UInt64] = kUpb_DecodeOp_UnknownField,
      [kUpb_FieldType_Int32] = kUpb_DecodeOp_UnknownField,
      [kUpb_FieldType_Fixed64] = kUpb_DecodeOp_UnknownField,
      [kUpb_FieldType_Fixed32] = kUpb_DecodeOp_UnknownField,
      [kUpb_FieldType_Bool] = kUpb_DecodeOp_UnknownField,
      [kUpb_FieldType_String] = kUpb_DecodeOp_String,
      [kUpb_FieldType_Group] = kUpb_DecodeOp_UnknownField,
      [kUpb_FieldType_Message] = kUpb_DecodeOp_SubMessage,
      [kUpb_FieldType_Bytes] = kUpb_DecodeOp_Bytes,
      [kUpb_FieldType_UInt32] = kUpb_DecodeOp_UnknownField,
      [kUpb_FieldType_Enum] = kUpb_DecodeOp_UnknownField,
      [kUpb_FieldType_SFixed32] = kUpb_DecodeOp_UnknownField,
      [kUpb_FieldType_SFixed64] = kUpb_DecodeOp_UnknownField,
      [kUpb_FieldType_SInt32] = kUpb_DecodeOp_UnknownField,
      [kUpb_FieldType_SInt64] = kUpb_DecodeOp_UnknownField,
      [kUpb_FakeFieldType_MessageSetItem] = kUpb_DecodeOp_SubMessage,
      // For repeated field type.
      [kRepeatedBase + kUpb_FieldType_Double] = OP_FIXPCK_LG2(3),
      [kRepeatedBase + kUpb_FieldType_Float] = OP_FIXPCK_LG2(2),
      [kRepeatedBase + kUpb_FieldType_Int64] = OP_VARPCK_LG2(3),
      [kRepeatedBase + kUpb_FieldType_UInt64] = OP_VARPCK_LG2(3),
      [kRepeatedBase + kUpb_FieldType_Int32] = OP_VARPCK_LG2(2),
      [kRepeatedBase + kUpb_FieldType_Fixed64] = OP_FIXPCK_LG2(3),
      [kRepeatedBase + kUpb_FieldType_Fixed32] = OP_FIXPCK_LG2(2),
      [kRepeatedBase + kUpb_FieldType_Bool] = OP_VARPCK_LG2(0),
      [kRepeatedBase + kUpb_FieldType_String] = kUpb_DecodeOp_String,
      [kRepeatedBase + kUpb_FieldType_Group] = kUpb_DecodeOp_SubMessage,
      [kRepeatedBase + kUpb_FieldType_Message] = kUpb_DecodeOp_SubMessage,
      [kRepeatedBase + kUpb_FieldType_Bytes] = kUpb_DecodeOp_Bytes,
      [kRepeatedBase + kUpb_FieldType_UInt32] = OP_VARPCK_LG2(2),
      [kRepeatedBase + kUpb_FieldType_Enum] = kUpb_DecodeOp_PackedEnum,
      [kRepeatedBase + kUpb_FieldType_SFixed32] = OP_FIXPCK_LG2(2),
      [kRepeatedBase + kUpb_FieldType_SFixed64] = OP_FIXPCK_LG2(3),
      [kRepeatedBase + kUpb_FieldType_SInt32] = OP_VARPCK_LG2(2),
      [kRepeatedBase + kUpb_FieldType_SInt64] = OP_VARPCK_LG2(3),
      // Omitting kUpb_FakeFieldType_MessageSetItem, because we never emit a
      // repeated msgset type
  };

  int ndx = field->UPB_PRIVATE(descriptortype);
  if (upb_MiniTableField_IsArray(field)) ndx += kRepeatedBase;
  int op = kDelimitedOps[ndx];

  /* libpg_query local patch: decode proto3 string fields as bytes to skip
   * UTF-8 validation (SQL literals may be non-UTF-8). See vendor/upb/README. */
  if (op == kUpb_DecodeOp_String) op = kUpb_DecodeOp_Bytes;

  if (op == kUpb_DecodeOp_SubMessage) {
    _upb_Decoder_CheckUnlinked(d, mt, field, &op);
  } else if (op == kUpb_DecodeOp_Bytes) {
    _upb_Decoder_MaybeVerifyUtf8(d, field, &op);
  }

  return op;
}

UPB_FORCEINLINE
const char* _upb_Decoder_DecodeWireValue(upb_Decoder* d, const char* ptr,
                                         const upb_MiniTable* mt,
                                         const upb_MiniTableField* field,
                                         int wire_type, wireval* val, int* op) {
  static const unsigned kFixed32OkMask = (1 << kUpb_FieldType_Float) |
                                         (1 << kUpb_FieldType_Fixed32) |
                                         (1 << kUpb_FieldType_SFixed32);

  static const unsigned kFixed64OkMask = (1 << kUpb_FieldType_Double) |
                                         (1 << kUpb_FieldType_Fixed64) |
                                         (1 << kUpb_FieldType_SFixed64);

  switch (wire_type) {
    case kUpb_WireType_Varint:
      ptr = _upb_Decoder_DecodeVarint(d, ptr, &val->uint64_val);
      if (upb_MiniTableField_IsClosedEnum(field)) {
        const upb_MiniTableEnum* e =
            upb_MiniTableField_IsExtension(field)
                ? upb_MiniTableExtension_GetSubEnum(
                      (const upb_MiniTableExtension*)field)
                : upb_MiniTable_GetSubEnumTable(mt, field);
        if (!upb_MiniTableEnum_CheckValue(e, val->uint64_val)) {
          *op = kUpb_DecodeOp_UnknownField;
          return ptr;
        }
      } else {
        _upb_Decoder_Munge(field, val);
      }
      *op = _upb_Decoder_GetVarintOp(field);
      return ptr;
    case kUpb_WireType_32Bit:
      *op = kUpb_DecodeOp_Scalar4Byte;
      if (((1 << field->UPB_PRIVATE(descriptortype)) & kFixed32OkMask) == 0) {
        *op = kUpb_DecodeOp_UnknownField;
      }
      return upb_WireReader_ReadFixed32(ptr, &val->uint32_val, &d->input);
    case kUpb_WireType_64Bit:
      *op = kUpb_DecodeOp_Scalar8Byte;
      if (((1 << field->UPB_PRIVATE(descriptortype)) & kFixed64OkMask) == 0) {
        *op = kUpb_DecodeOp_UnknownField;
      }
      return upb_WireReader_ReadFixed64(ptr, &val->uint64_val, &d->input);
    case kUpb_WireType_Delimited:
      ptr = upb_Decoder_DecodeSize(d, ptr, &val->size);
      *op = _upb_Decoder_GetDelimitedOp(d, mt, field);
      return ptr;
    case kUpb_WireType_StartGroup:
      val->uint32_val = field->UPB_PRIVATE(number);
      if (field->UPB_PRIVATE(descriptortype) == kUpb_FieldType_Group) {
        *op = kUpb_DecodeOp_SubMessage;
        _upb_Decoder_CheckUnlinked(d, mt, field, op);
      } else if (field->UPB_PRIVATE(descriptortype) ==
                 kUpb_FakeFieldType_MessageSetItem) {
        *op = kUpb_DecodeOp_MessageSetItem;
      } else {
        *op = kUpb_DecodeOp_UnknownField;
      }
      return ptr;
    default:
      break;
  }
  _upb_Decoder_ErrorJmp(d, kUpb_DecodeStatus_Malformed);
}

UPB_FORCEINLINE
const char* _upb_Decoder_DecodeKnownField(upb_Decoder* d, const char* ptr,
                                          upb_Message* msg,
                                          const upb_MiniTable* layout,
                                          const upb_MiniTableField* field,
                                          int op, wireval* val) {
  const upb_MiniTableSubInternal* subs = layout->UPB_PRIVATE(subs);
  uint8_t mode = field->UPB_PRIVATE(mode);
  upb_MiniTableSubInternal ext_sub;

  if (UPB_UNLIKELY(mode & kUpb_LabelFlags_IsExtension)) {
    const upb_MiniTableExtension* ext_layout =
        (const upb_MiniTableExtension*)field;
    upb_Extension* ext = UPB_PRIVATE(_upb_Message_GetOrCreateExtension)(
        msg, ext_layout, &d->arena);
    if (UPB_UNLIKELY(!ext)) {
      _upb_Decoder_ErrorJmp(d, kUpb_DecodeStatus_OutOfMemory);
    }
    d->original_msg = msg;
    msg = &ext->data.UPB_PRIVATE(ext_msg_val);
    if (upb_MiniTableField_IsSubMessage(&ext->ext->UPB_PRIVATE(field))) {
      ext_sub.UPB_PRIVATE(submsg) =
          &ext->ext->UPB_PRIVATE(sub).UPB_PRIVATE(submsg);
    } else {
      ext_sub.UPB_PRIVATE(subenum) =
          ext->ext->UPB_PRIVATE(sub).UPB_PRIVATE(subenum);
    }
    subs = &ext_sub;
  }

  switch (mode & kUpb_FieldMode_Mask) {
    case kUpb_FieldMode_Array:
      return _upb_Decoder_DecodeToArray(d, ptr, msg, subs, field, val, op);
    case kUpb_FieldMode_Map:
      return _upb_Decoder_DecodeToMap(d, ptr, msg, subs, field, val);
    case kUpb_FieldMode_Scalar:
      return _upb_Decoder_DecodeToSubMessage(d, ptr, msg, subs, field, val, op);
    default:
      UPB_UNREACHABLE();
  }
}

static const char* _upb_Decoder_DecodeUnknownField(upb_Decoder* d,
                                                   const char* ptr,
                                                   upb_Message* msg,
                                                   int field_number,
                                                   int wire_type, wireval val) {
  if (field_number == 0) _upb_Decoder_ErrorJmp(d, kUpb_DecodeStatus_Malformed);

  // Since unknown fields are the uncommon case, we do a little extra work here
  // to walk backwards through the buffer to find the field start.  This frees
  // up a register in the fast paths (when the field is known), which leads to
  // significant speedups in benchmarks. Note that ptr may point into the slop
  // space, beyond the normal end of the input buffer.
  const char* start = ptr;

  if (wire_type == kUpb_WireType_Delimited) ptr += val.size;
  if (msg) {
    switch (wire_type) {
      case kUpb_WireType_Varint:
      case kUpb_WireType_Delimited:
        // Skip the last byte
        start--;
        // Skip bytes until we encounter the final byte of the tag varint.
        while (start[-1] & 0x80) start--;
        break;
      case kUpb_WireType_32Bit:
        start -= 4;
        break;
      case kUpb_WireType_64Bit:
        start -= 8;
        break;
      default:
        break;
    }

    assert(start == d->debug_valstart);
    {
      // The varint parser does not enforce that integers are encoded with their
      // minimum size; for example the value 1 could be encoded with three
      // bytes: 0x81, 0x80, 0x00. These unnecessary trailing zeroes mean that we
      // cannot skip backwards by the minimum encoded size of the tag; and
      // unlike the loop for delimited or varint fields, we can't stop at a
      // sentinel value because anything can precede a tag. Instead, parse back
      // one byte at a time until we read the same tag value that was parsed
      // earlier.
      uint32_t tag = ((uint32_t)field_number << 3) | wire_type;
      uint32_t seen = 0;
      do {
        start--;
        seen <<= 7;
        seen |= *start & 0x7f;
      } while (seen != tag);
    }
    assert(start == d->debug_tagstart);

    const char* input_start =
        upb_EpsCopyInputStream_GetInputPtr(&d->input, start);
    if (wire_type == kUpb_WireType_StartGroup) {
      ptr = _upb_Decoder_DecodeUnknownGroup(d, ptr, field_number);
    }
    // Normally, bounds checks for fixed or varint fields are performed after
    // the field is parsed; it's OK for the field to overrun the end of the
    // buffer, because it'll just read into slop space. However, because this
    // path reads bytes from the input buffer rather than the patch buffer,
    // bounds checks are needed before adding the unknown field.
    _upb_Decoder_IsDone(d, &ptr);
    const char* input_ptr = upb_EpsCopyInputStream_GetInputPtr(&d->input, ptr);
    if (!UPB_PRIVATE(_upb_Message_AddUnknown)(
            msg, input_start, input_ptr - input_start, &d->arena,
            d->input.aliasing ? d->input.buffer_start : NULL)) {
      _upb_Decoder_ErrorJmp(d, kUpb_DecodeStatus_OutOfMemory);
    }
  } else if (wire_type == kUpb_WireType_StartGroup) {
    ptr = _upb_Decoder_DecodeUnknownGroup(d, ptr, field_number);
  }
  return ptr;
}

UPB_FORCEINLINE
const char* _upb_Decoder_DecodeFieldTag(upb_Decoder* d, const char* ptr,
                                        int* field_number, int* wire_type) {
#ifndef NDEBUG
  d->debug_tagstart = ptr;
#endif

  uint32_t tag;
  UPB_ASSERT(ptr < d->input.limit_ptr);
  ptr = _upb_Decoder_DecodeTag(d, ptr, &tag);
  *field_number = tag >> 3;
  *wire_type = tag & 7;
  return ptr;
}

UPB_FORCEINLINE
const char* _upb_Decoder_DecodeFieldData(upb_Decoder* d, const char* ptr,
                                         upb_Message* msg,
                                         const upb_MiniTable* mt,
                                         int field_number, int wire_type) {
#ifndef NDEBUG
  d->debug_valstart = ptr;
#endif

  int op;
  wireval val;

  const upb_MiniTableField* field =
      _upb_Decoder_FindField(d, mt, field_number, wire_type);
  ptr = _upb_Decoder_DecodeWireValue(d, ptr, mt, field, wire_type, &val, &op);

  if (op >= 0) {
    return _upb_Decoder_DecodeKnownField(d, ptr, msg, mt, field, op, &val);
  } else {
    switch (op) {
      case kUpb_DecodeOp_UnknownField:
        return _upb_Decoder_DecodeUnknownField(d, ptr, msg, field_number,
                                               wire_type, val);
      case kUpb_DecodeOp_MessageSetItem:
        return upb_Decoder_DecodeMessageSetItem(d, ptr, msg, mt);
      default:
        UPB_UNREACHABLE();
    }
  }
}

static const char* _upb_Decoder_EndMessage(upb_Decoder* d, const char* ptr) {
  d->message_is_done = true;
  return ptr;
}

UPB_FORCEINLINE
const char* _upb_Decoder_DecodeFieldNoFast(upb_Decoder* d, const char* ptr,
                                           upb_Message* msg,
                                           const upb_MiniTable* mt) {
  int field_number;
  int wire_type;

  ptr = _upb_Decoder_DecodeFieldTag(d, ptr, &field_number, &wire_type);

  if (wire_type == kUpb_WireType_EndGroup) {
    d->end_group = field_number;
    return _upb_Decoder_EndMessage(d, ptr);
  }

  ptr = _upb_Decoder_DecodeFieldData(d, ptr, msg, mt, field_number, wire_type);
  _upb_Decoder_Trace(d, 'M');
  return ptr;
}

UPB_FORCEINLINE
const char* _upb_Decoder_DecodeField(upb_Decoder* d, const char* ptr,
                                     upb_Message* msg, const upb_MiniTable* mt,
                                     uint64_t last_field_index, uint64_t data) {
#ifdef UPB_ENABLE_FASTTABLE
  if (mt && mt->UPB_PRIVATE(table_mask) != (unsigned char)-1 &&
      !(d->options & kUpb_DecodeOption_DisableFastTable)) {
    intptr_t table = decode_totable(mt);
    ptr = upb_DecodeFast_Dispatch(d, ptr, msg, table, 0, 0);
    if (d->message_is_done) return ptr;
    _upb_Decoder_Trace(d, '<');
  } else if (_upb_Decoder_IsDone(d, &ptr)) {
    return _upb_Decoder_EndMessage(d, ptr);
  }
#else
  if (_upb_Decoder_IsDone(d, &ptr)) {
    return _upb_Decoder_EndMessage(d, ptr);
  }
#endif

  return _upb_Decoder_DecodeFieldNoFast(d, ptr, msg, mt);
}

UPB_NOINLINE
const char* _upb_Decoder_DecodeMessage(upb_Decoder* d, const char* ptr,
                                       upb_Message* msg,
                                       const upb_MiniTable* mt) {
  UPB_ASSERT(d->message_is_done == false);

  do {
    ptr = _upb_Decoder_DecodeField(d, ptr, msg, mt, 0, 0);
  } while (!d->message_is_done);
  d->message_is_done = false;

  return UPB_UNLIKELY(mt && mt->UPB_PRIVATE(required_count))
             ? _upb_Decoder_CheckRequired(d, ptr, msg, mt)
             : ptr;
}

static upb_DecodeStatus _upb_Decoder_DecodeTop(struct upb_Decoder* d,
                                               const char* buf,
                                               upb_Message* msg,
                                               const upb_MiniTable* m) {
  _upb_Decoder_DecodeMessage(d, buf, msg, m);
  if (d->end_group != DECODE_NOGROUP) return kUpb_DecodeStatus_Malformed;
  if (d->missing_required) return kUpb_DecodeStatus_MissingRequired;
  return kUpb_DecodeStatus_Ok;
}

static upb_DecodeStatus upb_Decoder_Decode(upb_Decoder* const decoder,
                                           const char* const buf,
                                           upb_Message* const msg,
                                           const upb_MiniTable* const m,
                                           upb_Arena* const arena) {
  if (UPB_SETJMP(decoder->err) == 0) {
    decoder->status = _upb_Decoder_DecodeTop(decoder, buf, msg, m);
  } else {
    UPB_ASSERT(decoder->status != kUpb_DecodeStatus_Ok);
  }

  return upb_Decoder_Destroy(decoder, arena);
}

static uint16_t upb_DecodeOptions_GetMaxDepth(uint32_t options) {
  return options >> 16;
}

uint16_t upb_DecodeOptions_GetEffectiveMaxDepth(uint32_t options) {
  uint16_t max_depth = upb_DecodeOptions_GetMaxDepth(options);
  return max_depth ? max_depth : kUpb_WireFormat_DefaultDepthLimit;
}

upb_DecodeStatus upb_Decode(const char* buf, size_t size, upb_Message* msg,
                            const upb_MiniTable* mt,
                            const upb_ExtensionRegistry* extreg, int options,
                            upb_Arena* arena) {
  UPB_ASSERT(!upb_Message_IsFrozen(msg));
  upb_Decoder decoder;
  buf = upb_Decoder_Init(&decoder, buf, size, extreg, options, arena, NULL, 0);

  return upb_Decoder_Decode(&decoder, buf, msg, mt, arena);
}

upb_DecodeStatus upb_DecodeWithTrace(const char* buf, size_t size,
                                     upb_Message* msg, const upb_MiniTable* mt,
                                     const upb_ExtensionRegistry* extreg,
                                     int options, upb_Arena* arena,
                                     char* trace_buf, size_t trace_size) {
  UPB_ASSERT(!upb_Message_IsFrozen(msg));
  upb_Decoder decoder;
  buf = upb_Decoder_Init(&decoder, buf, size, extreg, options, arena, trace_buf,
                         trace_size);

  return upb_Decoder_Decode(&decoder, buf, msg, mt, arena);
}

upb_DecodeStatus upb_DecodeLengthPrefixed(const char* buf, size_t size,
                                          upb_Message* msg,
                                          size_t* num_bytes_read,
                                          const upb_MiniTable* mt,
                                          const upb_ExtensionRegistry* extreg,
                                          int options, upb_Arena* arena) {
  // To avoid needing to make a Decoder just to decode the initial length,
  // hand-decode the leading varint for the message length here.
  uint64_t msg_len = 0;
  for (size_t i = 0;; ++i) {
    if (i >= size || i > 9) {
      return kUpb_DecodeStatus_Malformed;
    }
    uint64_t b = *buf;
    buf++;
    msg_len += (b & 0x7f) << (i * 7);
    if ((b & 0x80) == 0) {
      *num_bytes_read = i + 1 + msg_len;
      break;
    }
  }

  // If the total number of bytes we would read (= the bytes from the varint
  // plus however many bytes that varint says we should read) is larger then the
  // input buffer then error as malformed.
  if (*num_bytes_read > size) {
    return kUpb_DecodeStatus_Malformed;
  }
  if (msg_len > INT32_MAX) {
    return kUpb_DecodeStatus_Malformed;
  }

  return upb_Decode(buf, msg_len, msg, mt, extreg, options, arena);
}

const char* upb_DecodeStatus_String(upb_DecodeStatus status) {
  switch (status) {
    case kUpb_DecodeStatus_Ok:
      return "Ok";
    case kUpb_DecodeStatus_Malformed:
      return "Wire format was corrupt";
    case kUpb_DecodeStatus_OutOfMemory:
      return "Arena alloc failed";
    case kUpb_DecodeStatus_BadUtf8:
      return "String field had bad UTF-8";
    case kUpb_DecodeStatus_MaxDepthExceeded:
      return "Exceeded upb_DecodeOptions_MaxDepth";
    case kUpb_DecodeStatus_MissingRequired:
      return "Missing required field";
    case kUpb_DecodeStatus_UnlinkedSubMessage:
      return "Unlinked sub-message field was present";
    default:
      return "Unknown decode status";
  }
}

#undef OP_FIXPCK_LG2
#undef OP_VARPCK_LG2



// Must be last.

UPB_NOINLINE
const char* _upb_Decoder_CheckRequired(upb_Decoder* d, const char* ptr,
                                       const upb_Message* msg,
                                       const upb_MiniTable* m) {
  UPB_ASSERT(m->UPB_PRIVATE(required_count));
  if (UPB_UNLIKELY(d->options & kUpb_DecodeOption_CheckRequired)) {
    d->missing_required =
        !UPB_PRIVATE(_upb_Message_IsInitializedShallow)(msg, m);
  }
  return ptr;
}

UPB_NORETURN void* _upb_Decoder_ErrorJmp(upb_Decoder* d,
                                         upb_DecodeStatus status) {
  UPB_ASSERT(status != kUpb_DecodeStatus_Ok);
  d->status = status;
  UPB_LONGJMP(d->err, 1);
}

UPB_NOINLINE
const char* _upb_Decoder_IsDoneFallback(upb_EpsCopyInputStream* e,
                                        const char* ptr, int overrun) {
  return _upb_EpsCopyInputStream_IsDoneFallbackInline(
      e, ptr, overrun, _upb_Decoder_BufferFlipCallback);
}

// We encode backwards, to avoid pre-computing lengths (one-pass encode).


#include <setjmp.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>


// Must be last.

// Returns the MiniTable corresponding to a given MiniTableField
// from an array of MiniTableSubs.
static const upb_MiniTable* _upb_Encoder_GetSubMiniTable(
    const upb_MiniTableSubInternal* subs, const upb_MiniTableField* field) {
  return *subs[field->UPB_PRIVATE(submsg_index)].UPB_PRIVATE(submsg);
}

static uint32_t encode_zz32(int32_t n) {
  return ((uint32_t)n << 1) ^ (n >> 31);
}
static uint64_t encode_zz64(int64_t n) {
  return ((uint64_t)n << 1) ^ (n >> 63);
}

typedef struct {
  upb_EncodeStatus status;
  jmp_buf err;
  upb_Arena* arena;
  // These should only be used for arithmetic and reallocation to allow full
  // aliasing analysis on the ptr argument.
  const char UPB_NODEREF *buf, *limit;
  int options;
  int depth;
  _upb_mapsorter sorter;
} upb_encstate;

static size_t upb_roundup_pow2(size_t bytes) {
  size_t ret = 128;
  while (ret < bytes) {
    ret *= 2;
  }
  return ret;
}

UPB_NORETURN static void encode_err(upb_encstate* e, upb_EncodeStatus s) {
  UPB_ASSERT(s != kUpb_EncodeStatus_Ok);
  e->status = s;
  UPB_LONGJMP(e->err, 1);
}

UPB_NOINLINE
static char* encode_growbuffer(char* ptr, upb_encstate* e, size_t bytes) {
  size_t old_size = e->limit - e->buf;
  size_t needed_size = bytes + (e->limit - ptr);
  size_t new_size = upb_roundup_pow2(needed_size);
  char* new_buf =
      upb_Arena_Realloc(e->arena, (void*)e->buf, old_size, new_size);

  if (!new_buf) encode_err(e, kUpb_EncodeStatus_OutOfMemory);

  // We want previous data at the end, realloc() put it at the beginning.
  // TODO: This is somewhat inefficient since we are copying twice.
  // Maybe create a realloc() that copies to the end of the new buffer?
  if (old_size > 0) {
    memmove(new_buf + new_size - old_size, new_buf, old_size);
  }

  e->buf = new_buf;
  e->limit = new_buf + new_size;
  return new_buf + new_size - needed_size;
}

/* Call to ensure that at least `bytes` bytes are available for writing at
 * ptr. */
UPB_FORCEINLINE
char* encode_reserve(char* ptr, upb_encstate* e, size_t bytes) {
  if ((size_t)(ptr - e->buf) < bytes) {
    return encode_growbuffer(ptr, e, bytes);
  }

  return ptr - bytes;
}

/* Writes the given bytes to the buffer, handling reserve/advance. */
static char* encode_bytes(char* ptr, upb_encstate* e, const void* data,
                          size_t len) {
  if (len == 0) return ptr; /* memcpy() with zero size is UB */
  ptr = encode_reserve(ptr, e, len);
  memcpy(ptr, data, len);
  return ptr;
}

static char* encode_fixed64(char* ptr, upb_encstate* e, uint64_t val) {
  val = upb_BigEndian64(val);
  return encode_bytes(ptr, e, &val, sizeof(uint64_t));
}

static char* encode_fixed32(char* ptr, upb_encstate* e, uint32_t val) {
  val = upb_BigEndian32(val);
  return encode_bytes(ptr, e, &val, sizeof(uint32_t));
}

#define UPB_PB_VARINT_MAX_LEN 10

// Need gnu extended inline asm; msan can't instrument stores in inline assembly
#if defined(__aarch64__) && (defined(__GNUC__) || defined(__clang__)) && \
    !UPB_HAS_FEATURE(memory_sanitizer)
#define UPB_ARM64_ASM
#endif

#ifdef UPB_ARM64_ASM
UPB_NOINLINE static char* encode_longvarint_arm64(char* ptr, upb_encstate* e,
                                                  uint64_t val) {
  ptr = encode_reserve(ptr, e, UPB_PB_VARINT_MAX_LEN);
  uint64_t clz;
  __asm__("clz %[cnt], %[val]\n" : [cnt] "=r"(clz) : [val] "r"(val));

  uint32_t skip =
      UPB_PRIVATE(upb_WireWriter_VarintUnusedSizeFromLeadingZeros64)(clz);

  ptr += skip;
  uint64_t addr, mask;
  __asm__ volatile(
      "adr %[addr], 0f\n"
      // Each arm64 instruction encodes to 4 bytes, and it takes two
      // intructions to process each byte of output, so we branch ahead by
      //  (4 + 4) * skip to avoid the remaining bytes.
      "add %[addr], %[addr], %[cnt], lsl #3\n"
      "mov %w[mask], #0x80\n"
      "br %[addr]\n"
      "0:\n"
      // We don't need addr any more, but we've got the register for our whole
      // assembly block so we'll use it as scratch to store the shift+masked
      // values before storing them.
      // The following stores are unsigned offset stores:
      // strb Wt, [Xn, #imm]
      "orr %[addr], %[mask], %[val], lsr #56\n"
      "strb %w[addr], [%[ptr], #8]\n"
      "orr %[addr], %[mask], %[val], lsr #49\n"
      "strb %w[addr], [%[ptr], #7]\n"
      "orr %[addr], %[mask], %[val], lsr #42\n"
      "strb %w[addr], [%[ptr], #6]\n"
      "orr %[addr], %[mask], %[val], lsr #35\n"
      "strb %w[addr], [%[ptr], #5]\n"
      "orr %[addr], %[mask], %[val], lsr #28\n"
      "strb %w[addr], [%[ptr], #4]\n"
      "orr %w[addr], %w[mask], %w[val], lsr #21\n"
      "strb %w[addr], [%[ptr], #3]\n"
      "orr %w[addr], %w[mask], %w[val], lsr #14\n"
      "strb %w[addr], [%[ptr], #2]\n"
      "orr %w[addr], %w[mask], %w[val], lsr #7\n"
      "strb %w[addr], [%[ptr], #1]\n"
      "orr %w[addr], %w[val], #0x80\n"
      "strb %w[addr], [%[ptr]]\n"
      : [addr] "=&r"(addr), [mask] "=&r"(mask)
      : [val] "r"(val), [ptr] "r"(ptr), [cnt] "r"((uint64_t)skip)
      : "memory");
  // Encode the final byte after the continuation bytes.
  uint32_t continuations = UPB_PB_VARINT_MAX_LEN - 1 - skip;
  ptr[continuations] = val >> (7 * continuations);
  return ptr;
}
#else
UPB_NOINLINE
static char* encode_longvarint(char* ptr, upb_encstate* e, uint64_t val) {
  ptr = encode_reserve(ptr, e, UPB_PB_VARINT_MAX_LEN);
  size_t len = 0;
  do {
    uint8_t byte = val & 0x7fU;
    val >>= 7;
    if (val) byte |= 0x80U;
    ptr[len++] = byte;
  } while (val);
  char* start = ptr + UPB_PB_VARINT_MAX_LEN - len;
  memmove(start, ptr, len);
  return start;
}
#endif

UPB_FORCEINLINE
char* encode_varint(char* ptr, upb_encstate* e, uint64_t val) {
  if (val < 128 && ptr != e->buf) {
    --ptr;
    *ptr = val;
    return ptr;
  } else {
#ifdef UPB_ARM64_ASM
    return encode_longvarint_arm64(ptr, e, val);
#else
    return encode_longvarint(ptr, e, val);
#endif
  }
}

static char* encode_double(char* ptr, upb_encstate* e, double d) {
  uint64_t u64;
  UPB_ASSERT(sizeof(double) == sizeof(uint64_t));
  memcpy(&u64, &d, sizeof(uint64_t));
  return encode_fixed64(ptr, e, u64);
}

static char* encode_float(char* ptr, upb_encstate* e, float d) {
  uint32_t u32;
  UPB_ASSERT(sizeof(float) == sizeof(uint32_t));
  memcpy(&u32, &d, sizeof(uint32_t));
  return encode_fixed32(ptr, e, u32);
}

static char* encode_tag(char* ptr, upb_encstate* e, uint32_t field_number,
                        uint8_t wire_type) {
  return encode_varint(ptr, e, (field_number << 3) | wire_type);
}

static char* encode_fixedarray(char* ptr, upb_encstate* e, const upb_Array* arr,
                               size_t elem_size, uint32_t tag) {
  size_t bytes = upb_Array_Size(arr) * elem_size;
  const char* data = upb_Array_DataPtr(arr);
  const char* arr_ptr = data + bytes - elem_size;

  if (tag || !upb_IsLittleEndian()) {
    while (true) {
      if (elem_size == 4) {
        uint32_t val;
        memcpy(&val, arr_ptr, sizeof(val));
        val = upb_BigEndian32(val);
        ptr = encode_bytes(ptr, e, &val, elem_size);
      } else {
        UPB_ASSERT(elem_size == 8);
        uint64_t val;
        memcpy(&val, arr_ptr, sizeof(val));
        val = upb_BigEndian64(val);
        ptr = encode_bytes(ptr, e, &val, elem_size);
      }

      if (tag) {
        ptr = encode_varint(ptr, e, tag);
      }
      if (arr_ptr == data) break;
      arr_ptr -= elem_size;
    }
    return ptr;
  } else {
    return encode_bytes(ptr, e, data, bytes);
  }
}

static char* encode_message(char* ptr, upb_encstate* e, const upb_Message* msg,
                            const upb_MiniTable* m, size_t* size);

static char* encode_TaggedMessagePtr(char* ptr, upb_encstate* e,
                                     upb_TaggedMessagePtr tagged,
                                     const upb_MiniTable* m, size_t* size) {
  if (upb_TaggedMessagePtr_IsEmpty(tagged)) {
    m = UPB_PRIVATE(_upb_MiniTable_Empty)();
  }
  return encode_message(
      ptr, e, UPB_PRIVATE(_upb_TaggedMessagePtr_GetMessage)(tagged), m, size);
}

static char* encode_scalar(char* ptr, upb_encstate* e, const void* _field_mem,
                           const upb_MiniTableSubInternal* subs,
                           const upb_MiniTableField* f) {
  const char* field_mem = _field_mem;
  int wire_type;

#define CASE(ctype, type, wtype, encodeval) \
  {                                         \
    ctype val = *(ctype*)field_mem;         \
    ptr = encode_##type(ptr, e, encodeval); \
    wire_type = wtype;                      \
    break;                                  \
  }

  switch (f->UPB_PRIVATE(descriptortype)) {
    case kUpb_FieldType_Double:
      CASE(double, double, kUpb_WireType_64Bit, val);
    case kUpb_FieldType_Float:
      CASE(float, float, kUpb_WireType_32Bit, val);
    case kUpb_FieldType_Int64:
    case kUpb_FieldType_UInt64:
      CASE(uint64_t, varint, kUpb_WireType_Varint, val);
    case kUpb_FieldType_UInt32:
      CASE(uint32_t, varint, kUpb_WireType_Varint, val);
    case kUpb_FieldType_Int32:
    case kUpb_FieldType_Enum:
      CASE(int32_t, varint, kUpb_WireType_Varint, (int64_t)val);
    case kUpb_FieldType_SFixed64:
    case kUpb_FieldType_Fixed64:
      CASE(uint64_t, fixed64, kUpb_WireType_64Bit, val);
    case kUpb_FieldType_Fixed32:
    case kUpb_FieldType_SFixed32:
      CASE(uint32_t, fixed32, kUpb_WireType_32Bit, val);
    case kUpb_FieldType_Bool:
      CASE(bool, varint, kUpb_WireType_Varint, val);
    case kUpb_FieldType_SInt32:
      CASE(int32_t, varint, kUpb_WireType_Varint, encode_zz32(val));
    case kUpb_FieldType_SInt64:
      CASE(int64_t, varint, kUpb_WireType_Varint, encode_zz64(val));
    case kUpb_FieldType_String:
    case kUpb_FieldType_Bytes: {
      upb_StringView view = *(upb_StringView*)field_mem;
      ptr = encode_bytes(ptr, e, view.data, view.size);
      ptr = encode_varint(ptr, e, view.size);
      wire_type = kUpb_WireType_Delimited;
      break;
    }
    case kUpb_FieldType_Group: {
      size_t size;
      upb_TaggedMessagePtr submsg = *(upb_TaggedMessagePtr*)field_mem;
      const upb_MiniTable* subm = _upb_Encoder_GetSubMiniTable(subs, f);
      if (submsg == 0) {
        return ptr;
      }
      if (--e->depth == 0) encode_err(e, kUpb_EncodeStatus_MaxDepthExceeded);
      ptr = encode_tag(ptr, e, upb_MiniTableField_Number(f),
                       kUpb_WireType_EndGroup);
      ptr = encode_TaggedMessagePtr(ptr, e, submsg, subm, &size);
      wire_type = kUpb_WireType_StartGroup;
      e->depth++;
      break;
    }
    case kUpb_FieldType_Message: {
      size_t size;
      upb_TaggedMessagePtr submsg = *(upb_TaggedMessagePtr*)field_mem;
      const upb_MiniTable* subm = _upb_Encoder_GetSubMiniTable(subs, f);
      if (submsg == 0) {
        return ptr;
      }
      if (--e->depth == 0) encode_err(e, kUpb_EncodeStatus_MaxDepthExceeded);
      ptr = encode_TaggedMessagePtr(ptr, e, submsg, subm, &size);
      ptr = encode_varint(ptr, e, size);
      wire_type = kUpb_WireType_Delimited;
      e->depth++;
      break;
    }
    default:
      UPB_UNREACHABLE();
  }
#undef CASE

  return encode_tag(ptr, e, upb_MiniTableField_Number(f), wire_type);
}

static char* encode_array(char* ptr, upb_encstate* e, const upb_Message* msg,
                          const upb_MiniTableSubInternal* subs,
                          const upb_MiniTableField* f) {
  const upb_Array* arr = *UPB_PTR_AT(msg, f->UPB_PRIVATE(offset), upb_Array*);
  bool packed = upb_MiniTableField_IsPacked(f);
  size_t pre_len = e->limit - ptr;

  if (arr == NULL || upb_Array_Size(arr) == 0) {
    return ptr;
  }

#define VARINT_CASE(ctype, encode)                                         \
  {                                                                        \
    const ctype* start = upb_Array_DataPtr(arr);                           \
    const ctype* arr_ptr = start + upb_Array_Size(arr);                    \
    uint32_t tag =                                                         \
        packed ? 0 : (f->UPB_PRIVATE(number) << 3) | kUpb_WireType_Varint; \
    do {                                                                   \
      arr_ptr--;                                                           \
      ptr = encode_varint(ptr, e, encode);                                 \
      if (tag) {                                                           \
        ptr = encode_varint(ptr, e, tag);                                  \
      }                                                                    \
    } while (arr_ptr != start);                                            \
  }                                                                        \
  break;

#define TAG(wire_type) (packed ? 0 : (f->UPB_PRIVATE(number) << 3 | wire_type))

  switch (f->UPB_PRIVATE(descriptortype)) {
    case kUpb_FieldType_Double:
      ptr = encode_fixedarray(ptr, e, arr, sizeof(double),
                              TAG(kUpb_WireType_64Bit));
      break;
    case kUpb_FieldType_Float:
      ptr = encode_fixedarray(ptr, e, arr, sizeof(float),
                              TAG(kUpb_WireType_32Bit));
      break;
    case kUpb_FieldType_SFixed64:
    case kUpb_FieldType_Fixed64:
      ptr = encode_fixedarray(ptr, e, arr, sizeof(uint64_t),
                              TAG(kUpb_WireType_64Bit));
      break;
    case kUpb_FieldType_Fixed32:
    case kUpb_FieldType_SFixed32:
      ptr = encode_fixedarray(ptr, e, arr, sizeof(uint32_t),
                              TAG(kUpb_WireType_32Bit));
      break;
    case kUpb_FieldType_Int64:
    case kUpb_FieldType_UInt64:
      VARINT_CASE(uint64_t, *arr_ptr);
    case kUpb_FieldType_UInt32:
      VARINT_CASE(uint32_t, *arr_ptr);
    case kUpb_FieldType_Int32:
    case kUpb_FieldType_Enum:
      VARINT_CASE(int32_t, (int64_t)*arr_ptr);
    case kUpb_FieldType_Bool:
      VARINT_CASE(bool, *arr_ptr);
    case kUpb_FieldType_SInt32:
      VARINT_CASE(int32_t, encode_zz32(*arr_ptr));
    case kUpb_FieldType_SInt64:
      VARINT_CASE(int64_t, encode_zz64(*arr_ptr));
    case kUpb_FieldType_String:
    case kUpb_FieldType_Bytes: {
      const upb_StringView* start = upb_Array_DataPtr(arr);
      const upb_StringView* str_ptr = start + upb_Array_Size(arr);
      do {
        str_ptr--;
        ptr = encode_bytes(ptr, e, str_ptr->data, str_ptr->size);
        ptr = encode_varint(ptr, e, str_ptr->size);
        ptr = encode_tag(ptr, e, upb_MiniTableField_Number(f),
                         kUpb_WireType_Delimited);
      } while (str_ptr != start);
      return ptr;
    }
    case kUpb_FieldType_Group: {
      const upb_TaggedMessagePtr* start = upb_Array_DataPtr(arr);
      const upb_TaggedMessagePtr* arr_ptr = start + upb_Array_Size(arr);
      const upb_MiniTable* subm = _upb_Encoder_GetSubMiniTable(subs, f);
      if (--e->depth == 0) encode_err(e, kUpb_EncodeStatus_MaxDepthExceeded);
      do {
        size_t size;
        arr_ptr--;
        ptr = encode_tag(ptr, e, upb_MiniTableField_Number(f),
                         kUpb_WireType_EndGroup);
        ptr = encode_TaggedMessagePtr(ptr, e, *arr_ptr, subm, &size);
        ptr = encode_tag(ptr, e, upb_MiniTableField_Number(f),
                         kUpb_WireType_StartGroup);
      } while (arr_ptr != start);
      e->depth++;
      return ptr;
    }
    case kUpb_FieldType_Message: {
      const upb_TaggedMessagePtr* start = upb_Array_DataPtr(arr);
      const upb_TaggedMessagePtr* arr_ptr = start + upb_Array_Size(arr);
      const upb_MiniTable* subm = _upb_Encoder_GetSubMiniTable(subs, f);
      if (--e->depth == 0) encode_err(e, kUpb_EncodeStatus_MaxDepthExceeded);
      do {
        size_t size;
        arr_ptr--;
        ptr = encode_TaggedMessagePtr(ptr, e, *arr_ptr, subm, &size);
        ptr = encode_varint(ptr, e, size);
        ptr = encode_tag(ptr, e, upb_MiniTableField_Number(f),
                         kUpb_WireType_Delimited);
      } while (arr_ptr != start);
      e->depth++;
      return ptr;
    }
  }
#undef VARINT_CASE

  if (packed) {
    ptr = encode_varint(ptr, e, e->limit - ptr - pre_len);
    ptr = encode_tag(ptr, e, upb_MiniTableField_Number(f),
                     kUpb_WireType_Delimited);
  }
  return ptr;
}

static char* encode_mapentry(char* ptr, upb_encstate* e, uint32_t number,
                             const upb_MiniTable* layout,
                             const upb_MapEntry* ent) {
  const upb_MiniTableField* key_field = upb_MiniTable_MapKey(layout);
  const upb_MiniTableField* val_field = upb_MiniTable_MapValue(layout);
  size_t pre_len = e->limit - ptr;
  size_t size;
  ptr = encode_scalar(ptr, e, &ent->v, layout->UPB_PRIVATE(subs), val_field);
  ptr = encode_scalar(ptr, e, &ent->k, layout->UPB_PRIVATE(subs), key_field);
  size = (e->limit - ptr) - pre_len;
  ptr = encode_varint(ptr, e, size);
  ptr = encode_tag(ptr, e, number, kUpb_WireType_Delimited);
  return ptr;
}

static char* encode_map(char* ptr, upb_encstate* e, const upb_Message* msg,
                        const upb_MiniTableSubInternal* subs,
                        const upb_MiniTableField* f) {
  const upb_Map* map = *UPB_PTR_AT(msg, f->UPB_PRIVATE(offset), const upb_Map*);
  const upb_MiniTable* layout = _upb_Encoder_GetSubMiniTable(subs, f);
  UPB_ASSERT(upb_MiniTable_FieldCount(layout) == 2);

  if (!map || !upb_Map_Size(map)) return ptr;

  if (e->options & kUpb_EncodeOption_Deterministic) {
    if (!map->UPB_PRIVATE(is_strtable)) {
      // For inttable, first encode the array part, then sort the table entries.
      intptr_t iter = UPB_INTTABLE_BEGIN;
      while ((size_t)++iter < map->t.inttable.array_size) {
        upb_value value = map->t.inttable.array[iter];
        if (upb_inttable_arrhas(&map->t.inttable, iter)) {
          upb_MapEntry ent;
          memcpy(&ent.k, &iter, sizeof(iter));
          _upb_map_fromvalue(value, &ent.v, map->val_size);
          ptr = encode_mapentry(ptr, e, upb_MiniTableField_Number(f), layout,
                                &ent);
        }
      }
    }
    _upb_sortedmap sorted;
    _upb_mapsorter_pushmap(
        &e->sorter, layout->UPB_PRIVATE(fields)[0].UPB_PRIVATE(descriptortype),
        map, &sorted);
    upb_MapEntry ent;
    while (_upb_sortedmap_next(&e->sorter, map, &sorted, &ent)) {
      ptr = encode_mapentry(ptr, e, upb_MiniTableField_Number(f), layout, &ent);
    }
    _upb_mapsorter_popmap(&e->sorter, &sorted);
  } else {
    upb_value val;
    if (map->UPB_PRIVATE(is_strtable)) {
      intptr_t iter = UPB_STRTABLE_BEGIN;
      upb_StringView strkey;
      while (upb_strtable_next2(&map->t.strtable, &strkey, &val, &iter)) {
        upb_MapEntry ent;
        _upb_map_fromkey(strkey, &ent.k, map->key_size);
        _upb_map_fromvalue(val, &ent.v, map->val_size);
        ptr =
            encode_mapentry(ptr, e, upb_MiniTableField_Number(f), layout, &ent);
      }
    } else {
      intptr_t iter = UPB_INTTABLE_BEGIN;
      uintptr_t intkey = 0;
      while (upb_inttable_next(&map->t.inttable, &intkey, &val, &iter)) {
        upb_MapEntry ent;
        memcpy(&ent.k, &intkey, map->key_size);
        _upb_map_fromvalue(val, &ent.v, map->val_size);
        ptr =
            encode_mapentry(ptr, e, upb_MiniTableField_Number(f), layout, &ent);
      }
    }
  }
  return ptr;
}

static bool encode_shouldencode(const upb_Message* msg,
                                const upb_MiniTableField* f) {
  if (f->presence == 0) {
    // Proto3 presence or map/array.
    const void* mem = UPB_PTR_AT(msg, f->UPB_PRIVATE(offset), void);
    switch (UPB_PRIVATE(_upb_MiniTableField_GetRep)(f)) {
      case kUpb_FieldRep_1Byte: {
        char ch;
        memcpy(&ch, mem, 1);
        return ch != 0;
      }
      case kUpb_FieldRep_4Byte: {
        uint32_t u32;
        memcpy(&u32, mem, 4);
        return u32 != 0;
      }
      case kUpb_FieldRep_8Byte: {
        uint64_t u64;
        memcpy(&u64, mem, 8);
        return u64 != 0;
      }
      case kUpb_FieldRep_StringView: {
        const upb_StringView* str = (const upb_StringView*)mem;
        return str->size != 0;
      }
      default:
        UPB_UNREACHABLE();
    }
  } else if (UPB_PRIVATE(_upb_MiniTableField_HasHasbit)(f)) {
    // Proto2 presence: hasbit.
    return UPB_PRIVATE(_upb_Message_GetHasbit)(msg, f);
  } else {
    // Field is in a oneof.
    return UPB_PRIVATE(_upb_Message_GetOneofCase)(msg, f) ==
           upb_MiniTableField_Number(f);
  }
}

static char* encode_field(char* ptr, upb_encstate* e, const upb_Message* msg,
                          const upb_MiniTableSubInternal* subs,
                          const upb_MiniTableField* field) {
  switch (UPB_PRIVATE(_upb_MiniTableField_Mode)(field)) {
    case kUpb_FieldMode_Array:
      return encode_array(ptr, e, msg, subs, field);
    case kUpb_FieldMode_Map:
      return encode_map(ptr, e, msg, subs, field);
    case kUpb_FieldMode_Scalar:
      return encode_scalar(ptr, e,
                           UPB_PTR_AT(msg, field->UPB_PRIVATE(offset), void),
                           subs, field);
    default:
      UPB_UNREACHABLE();
  }
}

static char* encode_msgset_item(char* ptr, upb_encstate* e,
                                const upb_MiniTableExtension* ext,
                                const upb_MessageValue ext_val) {
  size_t size;
  ptr = encode_tag(ptr, e, kUpb_MsgSet_Item, kUpb_WireType_EndGroup);
  ptr = encode_message(ptr, e, ext_val.msg_val,
                       upb_MiniTableExtension_GetSubMessage(ext), &size);
  ptr = encode_varint(ptr, e, size);
  ptr = encode_tag(ptr, e, kUpb_MsgSet_Message, kUpb_WireType_Delimited);
  ptr = encode_varint(ptr, e, upb_MiniTableExtension_Number(ext));
  ptr = encode_tag(ptr, e, kUpb_MsgSet_TypeId, kUpb_WireType_Varint);
  ptr = encode_tag(ptr, e, kUpb_MsgSet_Item, kUpb_WireType_StartGroup);
  return ptr;
}

static char* encode_ext(char* ptr, upb_encstate* e,
                        const upb_MiniTableExtension* ext,
                        upb_MessageValue ext_val, bool is_message_set) {
  if (UPB_UNLIKELY(is_message_set)) {
    ptr = encode_msgset_item(ptr, e, ext, ext_val);
  } else {
    upb_MiniTableSubInternal sub;
    if (upb_MiniTableField_IsSubMessage(&ext->UPB_PRIVATE(field))) {
      sub.UPB_PRIVATE(submsg) = &ext->UPB_PRIVATE(sub).UPB_PRIVATE(submsg);
    } else {
      sub.UPB_PRIVATE(subenum) = ext->UPB_PRIVATE(sub).UPB_PRIVATE(subenum);
    }
    ptr = encode_field(ptr, e, &ext_val.UPB_PRIVATE(ext_msg_val), &sub,
                       &ext->UPB_PRIVATE(field));
  }
  return ptr;
}

static char* encode_exts(char* ptr, upb_encstate* e, const upb_MiniTable* m,
                         const upb_Message* msg) {
  if (m->UPB_PRIVATE(ext) == kUpb_ExtMode_NonExtendable) return ptr;

  upb_Message_Internal* in = UPB_PRIVATE(_upb_Message_GetInternal)(msg);
  if (!in) return ptr;

  /* Encode all extensions together. Unlike C++, we do not attempt to keep
   * these in field number order relative to normal fields or even to each
   * other. */
  uintptr_t iter = kUpb_Message_ExtensionBegin;
  const upb_MiniTableExtension* ext;
  upb_MessageValue ext_val;
  if (!UPB_PRIVATE(_upb_Message_NextExtensionReverse)(msg, &ext, &ext_val,
                                                      &iter)) {
    // Message has no extensions.
    return ptr;
  }

  if (e->options & kUpb_EncodeOption_Deterministic) {
    _upb_sortedmap sorted;
    if (!_upb_mapsorter_pushexts(&e->sorter, in, &sorted)) {
      // TODO: b/378744096 - handle alloc failure
    }
    const upb_Extension* ext;
    while (_upb_sortedmap_nextext(&e->sorter, &sorted, &ext)) {
      ptr = encode_ext(ptr, e, ext->ext, ext->data,
                       m->UPB_PRIVATE(ext) == kUpb_ExtMode_IsMessageSet);
    }
    _upb_mapsorter_popmap(&e->sorter, &sorted);
  } else {
    do {
      ptr = encode_ext(ptr, e, ext, ext_val,
                       m->UPB_PRIVATE(ext) == kUpb_ExtMode_IsMessageSet);
    } while (UPB_PRIVATE(_upb_Message_NextExtensionReverse)(msg, &ext, &ext_val,
                                                            &iter));
  }
  return ptr;
}

static char* encode_message(char* ptr, upb_encstate* e, const upb_Message* msg,
                            const upb_MiniTable* m, size_t* size) {
  size_t pre_len = e->limit - ptr;

  if (e->options & kUpb_EncodeOption_CheckRequired) {
    if (m->UPB_PRIVATE(required_count)) {
      if (!UPB_PRIVATE(_upb_Message_IsInitializedShallow)(msg, m)) {
        encode_err(e, kUpb_EncodeStatus_MissingRequired);
      }
    }
  }

  if ((e->options & kUpb_EncodeOption_SkipUnknown) == 0) {
    size_t unknown_size = 0;
    uintptr_t iter = kUpb_Message_UnknownBegin;
    upb_StringView unknown;
    // Need to write in reverse order, but iteration is in-order; scan to
    // reserve capacity up front, then write in-order
    while (upb_Message_NextUnknown(msg, &unknown, &iter)) {
      unknown_size += unknown.size;
    }
    if (unknown_size != 0) {
      ptr = encode_reserve(ptr, e, unknown_size);
      char* tmp_ptr = ptr;
      iter = kUpb_Message_UnknownBegin;
      while (upb_Message_NextUnknown(msg, &unknown, &iter)) {
        memcpy(tmp_ptr, unknown.data, unknown.size);
        tmp_ptr += unknown.size;
      }
    }
  }

  ptr = encode_exts(ptr, e, m, msg);

  if (upb_MiniTable_FieldCount(m)) {
    const upb_MiniTableField* f =
        &m->UPB_PRIVATE(fields)[m->UPB_PRIVATE(field_count)];
    const upb_MiniTableField* first = &m->UPB_PRIVATE(fields)[0];
    while (f != first) {
      f--;
      if (encode_shouldencode(msg, f)) {
        ptr = encode_field(ptr, e, msg, m->UPB_PRIVATE(subs), f);
      }
    }
  }

  *size = (e->limit - ptr) - pre_len;
  return ptr;
}

static upb_EncodeStatus upb_Encoder_Encode(char* ptr,
                                           upb_encstate* const encoder,
                                           const upb_Message* const msg,
                                           const upb_MiniTable* const l,
                                           char** const buf, size_t* const size,
                                           bool prepend_len) {
  // Unfortunately we must continue to perform hackery here because there are
  // code paths which blindly copy the returned pointer without bothering to
  // check for errors until much later (b/235839510). So we still set *buf to
  // NULL on error and we still set it to non-NULL on a successful empty result.
  if (UPB_SETJMP(encoder->err) == 0) {
    size_t encoded_msg_size;
    ptr = encode_message(ptr, encoder, msg, l, &encoded_msg_size);
    if (prepend_len) {
      ptr = encode_varint(ptr, encoder, encoded_msg_size);
    }
    *size = encoder->limit - ptr;
    if (*size == 0) {
      static char ch;
      *buf = &ch;
    } else {
      UPB_ASSERT(ptr);
      *buf = ptr;
    }
  } else {
    UPB_ASSERT(encoder->status != kUpb_EncodeStatus_Ok);
    *buf = NULL;
    *size = 0;
  }

  _upb_mapsorter_destroy(&encoder->sorter);
  return encoder->status;
}

static uint16_t upb_EncodeOptions_GetMaxDepth(uint32_t options) {
  return options >> 16;
}

uint16_t upb_EncodeOptions_GetEffectiveMaxDepth(uint32_t options) {
  uint16_t max_depth = upb_EncodeOptions_GetMaxDepth(options);
  return max_depth ? max_depth : kUpb_WireFormat_DefaultDepthLimit;
}

static upb_EncodeStatus _upb_Encode(const upb_Message* msg,
                                    const upb_MiniTable* l, int options,
                                    upb_Arena* arena, char** buf, size_t* size,
                                    bool prepend_len) {
  upb_encstate e;

  e.status = kUpb_EncodeStatus_Ok;
  e.arena = arena;
  e.buf = NULL;
  e.limit = NULL;
  e.depth = upb_EncodeOptions_GetEffectiveMaxDepth(options);
  e.options = options;
  _upb_mapsorter_init(&e.sorter);

  return upb_Encoder_Encode(NULL, &e, msg, l, buf, size, prepend_len);
}

upb_EncodeStatus upb_Encode(const upb_Message* msg, const upb_MiniTable* l,
                            int options, upb_Arena* arena, char** buf,
                            size_t* size) {
  return _upb_Encode(msg, l, options, arena, buf, size, false);
}

upb_EncodeStatus upb_EncodeLengthPrefixed(const upb_Message* msg,
                                          const upb_MiniTable* l, int options,
                                          upb_Arena* arena, char** buf,
                                          size_t* size) {
  return _upb_Encode(msg, l, options, arena, buf, size, true);
}

const char* upb_EncodeStatus_String(upb_EncodeStatus status) {
  switch (status) {
    case kUpb_EncodeStatus_Ok:
      return "Ok";
    case kUpb_EncodeStatus_MissingRequired:
      return "Missing required field";
    case kUpb_EncodeStatus_MaxDepthExceeded:
      return "Max depth exceeded";
    case kUpb_EncodeStatus_OutOfMemory:
      return "Arena alloc failed";
    default:
      return "Unknown encode status";
  }
}


#include <stddef.h>
#include <stdint.h>


// Must be last.

UPB_NOINLINE UPB_PRIVATE(_upb_WireReader_LongVarint)
    UPB_PRIVATE(_upb_WireReader_ReadLongVarint64)(const char* ptr,
                                                  uint64_t val) {
  UPB_PRIVATE(_upb_WireReader_LongVarint) ret = {NULL, 0};
  uint64_t byte;
  for (int i = 1; i < 10; i++) {
    byte = (uint8_t)ptr[i];
    val += (byte - 1) << (i * 7);
    if (!(byte & 0x80)) {
      ret.ptr = ptr + i + 1;
      ret.val = val;
      return ret;
    }
  }
  return ret;
}

UPB_NOINLINE UPB_PRIVATE(_upb_WireReader_LongVarint)
    UPB_PRIVATE(_upb_WireReader_ReadLongVarint32)(const char* ptr,
                                                  uint32_t val) {
  UPB_PRIVATE(_upb_WireReader_LongVarint) ret = {NULL, 0};
  uint64_t byte;
  for (int i = 1; i < 5; i++) {
    byte = (uint8_t)ptr[i];
    val += (byte - 1) << (i * 7);
    if (!(byte & 0x80)) {
      ret.ptr = ptr + i + 1;
      ret.val = val;
      return ret;
    }
  }
  return ret;
}

const char* UPB_PRIVATE(_upb_WireReader_SkipGroup)(
    const char* ptr, uint32_t tag, int depth_limit,
    upb_EpsCopyInputStream* stream) {
  if (--depth_limit == 0) return NULL;
  uint32_t end_group_tag = (tag & ~7ULL) | kUpb_WireType_EndGroup;
  while (!upb_EpsCopyInputStream_IsDone(stream, &ptr)) {
    uint32_t tag;
    ptr = upb_WireReader_ReadTag(ptr, &tag, stream);
    if (!ptr) return NULL;
    if (tag == end_group_tag) return ptr;
    ptr = _upb_WireReader_SkipValue(ptr, tag, depth_limit, stream);
    if (!ptr) return NULL;
  }
  return ptr;
}


static const char* _upb_EpsCopyInputStream_NoOpCallback(
    upb_EpsCopyInputStream* e, const char* old_end, const char* new_start) {
  return new_start;
}

const char* _upb_EpsCopyInputStream_IsDoneFallbackNoCallback(
    upb_EpsCopyInputStream* e, const char* ptr, int overrun) {
  return _upb_EpsCopyInputStream_IsDoneFallbackInline(
      e, ptr, overrun, _upb_EpsCopyInputStream_NoOpCallback);
}


#include <stddef.h>


// Must be last.

#ifdef __cplusplus
extern "C" {
#endif

size_t upb_ByteSize(const upb_Message* msg, const upb_MiniTable* mt) {
  upb_Arena* arena = upb_Arena_New();
  char* buf;
  size_t res = 0;

  upb_Encode(msg, mt, 0, arena, &buf, &res);

  upb_Arena_Free(arena);
  return res;
}

#ifdef __cplusplus
}  // extern "C"
#endif
// This should #undef all macros #defined in def.inc

#undef UPB_SIZE
#undef UPB_PTR_AT
#undef UPB_SIZEOF_FLEX
#undef UPB_SIZEOF_FLEX_WOULD_OVERFLOW
#undef UPB_MAPTYPE_STRING
#undef UPB_EXPORT
#undef UPB_INLINE
#undef UPB_API
#undef UPBC_API
#undef UPB_API_INLINE
#undef UPB_API_INLINE_IF_NOT_GCC
#undef UPB_ALIGN_UP
#undef UPB_ALIGN_DOWN
#undef UPB_ALIGN_MALLOC
#undef UPB_ALIGN_OF
#undef UPB_ALIGN_AS
#undef UPB_STATIC_ASSERT
#undef UPB_STATIC_ASSERT_CONCAT
#undef UPB_STATIC_ASSERT_CONCAT_IMPL
#undef UPB_LIKELY
#undef UPB_UNLIKELY
#undef UPB_UNPREDICTABLE
#undef UPB_FORCEINLINE
#undef UPB_NOINLINE
#undef UPB_NORETURN
#undef UPB_PRINTF
#undef UPB_NODEREF
#undef UPB_MAX
#undef UPB_MIN
#undef UPB_UNUSED
#undef UPB_ASSUME
#undef UPB_ASSERT
#undef UPB_UNREACHABLE
#undef UPB_DEFAULT_MAX_BLOCK_SIZE
#undef UPB_SETJMP
#undef UPB_LONGJMP
#undef UPB_PTRADD
#undef UPB_MUSTTAIL
#undef UPB_PRESERVE_NONE
#undef UPB_FASTTABLE_SUPPORTED
#undef UPB_FASTTABLE_MASK
#undef UPB_FASTTABLE
#undef UPB_FASTTABLE_INIT
#undef UPB_POISON_MEMORY_REGION
#undef UPB_UNPOISON_MEMORY_REGION
#undef UPB_ASAN
#undef UPB_HWASAN
#undef UPB_HWASAN_POISON_TAG
#undef UPB_MALLOC_ALIGN
#undef UPB_TSAN
#undef UPB_TREAT_CLOSED_ENUMS_LIKE_OPEN
#undef UPB_DEPRECATED
#undef UPB_GNUC_MIN
#undef UPB_DESCRIPTOR_UPB_H_FILENAME
#undef UPB_DESC
#undef UPB_DESC_MINITABLE
#undef UPB_IS_GOOGLE3
#undef UPB_ATOMIC
#undef UPB_USE_C11_ATOMICS
#undef UPB_USE_MSC_ATOMICS
#undef UPB_PRIVATE
#undef UPB_ONLYBITS
#undef UPB_LINKARR_DECLARE
#undef UPB_LINKARR_APPEND
#undef UPB_LINKARR_START
#undef UPB_LINKARR_STOP
#undef UPB_FUTURE_BREAKING_CHANGES
#undef UPB_HAS_ATTRIBUTE
#undef UPB_HAS_BUILTIN
#undef UPB_HAS_EXTENSION
#undef UPB_HAS_FEATURE
#undef UPB_XSAN_MEMBER
#undef UPB_XSAN
#undef UPB_XSAN_STRUCT_SIZE
#undef UPB_ENABLE_REF_CYCLE_CHECKS
