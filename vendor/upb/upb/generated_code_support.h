/* Amalgamated source file */

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

#ifndef UPB_BASE_UPCAST_H_
#define UPB_BASE_UPCAST_H_

// Must be last.

// This macro provides a way to upcast message pointers in a way that is
// somewhat more bulletproof than blindly casting a pointer. Example:
//
// typedef struct {
//   upb_Message UPB_PRIVATE(base);
// } pkg_FooMessage;
//
// void f(pkg_FooMessage* msg) {
//   upb_Decode(UPB_UPCAST(msg), ...);
// }

#define UPB_UPCAST(x) (&(x)->base##_dont_copy_me__upb_internal_use_only)


#endif /* UPB_BASE_UPCAST_H_ */

#ifndef UPB_MESSAGE_ACCESSORS_H_
#define UPB_MESSAGE_ACCESSORS_H_

#include <stdint.h>

#ifndef UPB_BASE_STRING_VIEW_H_
#define UPB_BASE_STRING_VIEW_H_

#include <string.h>

// Must be last.

#define UPB_STRINGVIEW_INIT(ptr, len) \
  { ptr, len }

#define UPB_STRINGVIEW_FORMAT "%.*s"
#define UPB_STRINGVIEW_ARGS(view) (int)(view).size, (view).data

// LINT.IfChange(struct_definition)
typedef struct {
  const char* data;
  size_t size;
} upb_StringView;

#ifdef __cplusplus
extern "C" {
#endif

UPB_API_INLINE upb_StringView upb_StringView_FromDataAndSize(const char* data,
                                                             size_t size) {
  upb_StringView ret;
  ret.data = data;
  ret.size = size;
  return ret;
}

UPB_INLINE upb_StringView upb_StringView_FromString(const char* data) {
  return upb_StringView_FromDataAndSize(data, strlen(data));
}

UPB_INLINE bool upb_StringView_IsEqual(upb_StringView a, upb_StringView b) {
  return (a.size == b.size) && (!a.size || !memcmp(a.data, b.data, a.size));
}

// Compares StringViews following strcmp rules.
// Please note this comparison is neither unicode nor locale aware.
UPB_INLINE int upb_StringView_Compare(upb_StringView a, upb_StringView b) {
  int result = memcmp(a.data, b.data, UPB_MIN(a.size, b.size));
  if (result != 0) return result;
  if (a.size < b.size) {
    return -1;
  } else if (a.size > b.size) {
    return 1;
  } else {
    return 0;
  }
}

// LINT.ThenChange(
//  GoogleInternalName1,
//  //depot/google3/third_party/upb/bits/golang/accessor.go:map_go_string,
//  //depot/google3/third_party/upb/bits/typescript/string_view.ts
// )

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /* UPB_BASE_STRING_VIEW_H_ */

/* upb_Arena is a specific allocator implementation that uses arena allocation.
 * The user provides an allocator that will be used to allocate the underlying
 * arena blocks.  Arenas by nature do not require the individual allocations
 * to be freed.  However the Arena does allow users to register cleanup
 * functions that will run when the arena is destroyed.
 *
 * A upb_Arena is *not* thread-safe, although some functions related to its
 * managing its lifetime are, and are documented as such.
 *
 * You could write a thread-safe arena allocator that satisfies the
 * upb_alloc interface, but it would not be as efficient for the
 * single-threaded case. */

#ifndef UPB_MEM_ARENA_H_
#define UPB_MEM_ARENA_H_

#include <stddef.h>
#include <stdint.h>


#ifndef UPB_MEM_ALLOC_H_
#define UPB_MEM_ALLOC_H_

#include <stddef.h>

// Must be last.

#ifdef __cplusplus
extern "C" {
#endif

typedef struct upb_alloc upb_alloc;

/* A combined `malloc()`/`free()` function.
 * If `size` is 0 then the function acts like `free()`, otherwise it acts like
 * `realloc()`.  Only `oldsize` bytes from a previous allocation are
 * preserved. If `actual_size` is not null and the allocator supports it, the
 * actual size of the resulting allocation is stored in `actual_size`. If
 * `actual_size` is not null, you must zero out the memory pointed to by
 * `actual_size` before calling. */
typedef void* upb_alloc_func(upb_alloc* alloc, void* ptr, size_t oldsize,
                             size_t size, size_t* actual_size);

/* A upb_alloc is a possibly-stateful allocator object.
 *
 * It could either be an arena allocator (which doesn't require individual
 * `free()` calls) or a regular `malloc()` (which does).  The client must
 * therefore free memory unless it knows that the allocator is an arena
 * allocator. */
struct upb_alloc {
  upb_alloc_func* func;
};

UPB_INLINE void* upb_malloc(upb_alloc* alloc, size_t size) {
  UPB_ASSERT(alloc);
  return alloc->func(alloc, NULL, 0, size, NULL);
}

typedef struct {
  void* p;
  size_t n;
} upb_SizedPtr;

UPB_INLINE upb_SizedPtr upb_SizeReturningMalloc(upb_alloc* alloc, size_t size) {
  UPB_ASSERT(alloc);
  upb_SizedPtr result;
  result.n = 0;
  result.p = alloc->func(alloc, NULL, 0, size, &result.n);
  result.n = result.p != NULL ? UPB_MAX(result.n, size) : 0;
  return result;
}

UPB_INLINE void* upb_realloc(upb_alloc* alloc, void* ptr, size_t oldsize,
                             size_t size) {
  UPB_ASSERT(alloc);
  return alloc->func(alloc, ptr, oldsize, size, NULL);
}

UPB_INLINE void upb_free(upb_alloc* alloc, void* ptr) {
  UPB_ASSERT(alloc);
  alloc->func(alloc, ptr, 0, 0, NULL);
}

UPB_INLINE void upb_free_sized(upb_alloc* alloc, void* ptr, size_t size) {
  UPB_ASSERT(alloc);
  alloc->func(alloc, ptr, size, 0, NULL);
}

// The global allocator used by upb. Uses the standard malloc()/free().

extern upb_alloc upb_alloc_global;

/* Functions that hard-code the global malloc.
 *
 * We still get benefit because we can put custom logic into our global
 * allocator, like injecting out-of-memory faults in debug/testing builds. */

UPB_INLINE void* upb_gmalloc(size_t size) {
  return upb_malloc(&upb_alloc_global, size);
}

UPB_INLINE void* upb_grealloc(void* ptr, size_t oldsize, size_t size) {
  return upb_realloc(&upb_alloc_global, ptr, oldsize, size);
}

UPB_INLINE void upb_gfree(void* ptr) { upb_free(&upb_alloc_global, ptr); }

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /* UPB_MEM_ALLOC_H_ */

#ifndef UPB_MEM_INTERNAL_ARENA_H_
#define UPB_MEM_INTERNAL_ARENA_H_

#include <stddef.h>
#include <stdint.h>
#include <string.h>


#ifndef UPB_PORT_SANITIZERS_H_
#define UPB_PORT_SANITIZERS_H_

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

// Must be last.

// Must be inside def.inc/undef.inc
#if UPB_HWASAN
#include <sanitizer/hwasan_interface.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

// UPB_ARENA_SIZE_HACK depends on this struct having size 1.
typedef struct {
  uint8_t state;
} upb_Xsan;

UPB_INLINE uint8_t _upb_Xsan_NextTag(upb_Xsan *xsan) {
#if UPB_HWASAN
  xsan->state++;
  if (xsan->state <= UPB_HWASAN_POISON_TAG) {
    xsan->state = UPB_HWASAN_POISON_TAG + 1;
  }
  return xsan->state;
#else
  return 0;
#endif
}

enum {
#if UPB_ASAN
  UPB_PRIVATE(kUpb_Asan_GuardSize) = 32,
#else
  UPB_PRIVATE(kUpb_Asan_GuardSize) = 0,
#endif
};

UPB_INLINE uint8_t UPB_PRIVATE(_upb_Xsan_GetTag)(const void *addr) {
#if UPB_HWASAN
  return __hwasan_get_tag_from_pointer(addr);
#else
  return 0;
#endif
}

UPB_INLINE void UPB_PRIVATE(upb_Xsan_Init)(upb_Xsan *xsan) {
#if UPB_HWASAN || UPB_TSAN
  xsan->state = 0;
#endif
}

// Marks the given region as poisoned, meaning that it is not accessible until
// it is unpoisoned.
UPB_INLINE void UPB_PRIVATE(upb_Xsan_PoisonRegion)(const void *addr,
                                                   size_t size) {
#if UPB_ASAN
  void __asan_poison_memory_region(void const volatile *addr, size_t size);
  __asan_poison_memory_region(addr, size);
#elif UPB_HWASAN
  __hwasan_tag_memory(addr, UPB_HWASAN_POISON_TAG, UPB_ALIGN_MALLOC(size));
#endif
}

UPB_INLINE void *UPB_PRIVATE(_upb_Xsan_UnpoisonRegion)(void *addr, size_t size,
                                                       uint8_t tag) {
#if UPB_ASAN
  UPB_UNUSED(tag);
  void __asan_unpoison_memory_region(void const volatile *addr, size_t size);
  __asan_unpoison_memory_region(addr, size);
  return addr;
#elif UPB_HWASAN
  __hwasan_tag_memory(addr, tag, UPB_ALIGN_MALLOC(size));
  return __hwasan_tag_pointer(addr, tag);
#else
  UPB_UNUSED(size);
  UPB_UNUSED(tag);

  // `addr` is the pointer that will be returned from arena alloc/realloc
  // functions.  In this code-path we know it must be non-NULL, but the compiler
  // doesn't know this unless we add a UPB_ASSUME() annotation.
  //
  // This will let the optimizer optimize away NULL-checks if it can see that
  // this path was taken.
  UPB_ASSUME(addr);
  return addr;
#endif
}

// Allows users to read and write to the given region, which will be considered
// distinct from other regions and may only be accessed through the returned
// pointer.
//
// `addr` must be aligned to the malloc alignment.  Size may be unaligned,
// and with ASAN we can respect `size` precisely, but with HWASAN we must
// round `size` up to the next multiple of the malloc alignment, so the caller
// must guarantee that rounding up `size` will not cause overlap with other
// regions.
UPB_INLINE void *UPB_PRIVATE(upb_Xsan_NewUnpoisonedRegion)(upb_Xsan *xsan,
                                                           void *addr,
                                                           size_t size) {
  return UPB_PRIVATE(_upb_Xsan_UnpoisonRegion)(addr, size,
                                               _upb_Xsan_NextTag(xsan));
}

// Resizes the given region to a new size, *without* invalidating any existing
// pointers to the region.
//
// `tagged_addr` must be a pointer that was previously returned from
// `upb_Xsan_NewUnpoisonedRegion`.  `old_size` must be the size that was
// originally passed to `upb_Xsan_NewUnpoisonedRegion`.
UPB_INLINE void *UPB_PRIVATE(upb_Xsan_ResizeUnpoisonedRegion)(void *tagged_addr,
                                                              size_t old_size,
                                                              size_t new_size) {
  UPB_PRIVATE(upb_Xsan_PoisonRegion)(tagged_addr, old_size);
  return UPB_PRIVATE(_upb_Xsan_UnpoisonRegion)(
      tagged_addr, new_size, UPB_PRIVATE(_upb_Xsan_GetTag)(tagged_addr));
}

// Compares two pointers and returns true if they are equal. This returns the
// correct result even if one or both of the pointers are tagged.
UPB_INLINE bool UPB_PRIVATE(upb_Xsan_PtrEq)(const void *a, const void *b) {
#if UPB_HWASAN
  return __hwasan_tag_pointer(a, 0) == __hwasan_tag_pointer(b, 0);
#else
  return a == b;
#endif
}

// These annotations improve TSAN's ability to detect data races.  By
// proactively accessing a non-atomic variable at the point where it is
// "logically" accessed, we can trigger TSAN diagnostics that might have
// otherwise been masked by subsequent atomic operations.

UPB_INLINE void UPB_PRIVATE(upb_Xsan_AccessReadOnly)(upb_Xsan *xsan) {
#if UPB_TSAN
  // For performance we avoid using a volatile variable.
  __asm__ volatile("" ::"r"(xsan->state));
#endif
}

UPB_INLINE void UPB_PRIVATE(upb_Xsan_AccessReadWrite)(upb_Xsan *xsan) {
#if UPB_TSAN
  // For performance we avoid using a volatile variable.
  __asm__ volatile("" : "+r"(xsan->state));
#endif
}

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif  // UPB_PORT_SANITIZERS_H_

// Must be last.

// This is QUITE an ugly hack, which specifies the number of pointers needed
// to equal (or exceed) the storage required for one upb_Arena.
//
// We need this because the decoder inlines a upb_Arena for performance but
// the full struct is not visible outside of arena.c. Yes, I know, it's awful.
#ifndef NDEBUG
#define UPB_ARENA_BASE_SIZE_HACK 11
#else
#define UPB_ARENA_BASE_SIZE_HACK 10
#endif

#define UPB_ARENA_SIZE_HACK \
  (UPB_ARENA_BASE_SIZE_HACK + (UPB_XSAN_STRUCT_SIZE * 2))

// LINT.IfChange(upb_Arena)

struct upb_Arena {
  char* UPB_ONLYBITS(ptr);
  const UPB_NODEREF char* UPB_ONLYBITS(end);
  UPB_XSAN_MEMBER
};

// LINT.ThenChange(//depot/google3/third_party/upb/bits/typescript/arena.ts:upb_Arena)

#ifdef __cplusplus
extern "C" {
#endif

void UPB_PRIVATE(_upb_Arena_SwapIn)(struct upb_Arena* des,
                                    const struct upb_Arena* src);
void UPB_PRIVATE(_upb_Arena_SwapOut)(struct upb_Arena* des,
                                     const struct upb_Arena* src);

UPB_INLINE size_t UPB_PRIVATE(_upb_ArenaHas)(const struct upb_Arena* a) {
  return (size_t)(a->UPB_ONLYBITS(end) - a->UPB_ONLYBITS(ptr));
}

UPB_INLINE size_t UPB_PRIVATE(_upb_Arena_AllocSpan)(size_t size) {
  return UPB_ALIGN_MALLOC(size) + UPB_PRIVATE(kUpb_Asan_GuardSize);
}

UPB_INLINE bool UPB_PRIVATE(_upb_Arena_WasLastAllocFromCurrentBlock)(
    const struct upb_Arena* a, void* ptr, size_t size) {
  return UPB_PRIVATE(upb_Xsan_PtrEq)(
      (char*)ptr + UPB_PRIVATE(_upb_Arena_AllocSpan)(size),
      a->UPB_ONLYBITS(ptr));
}

UPB_INLINE bool UPB_PRIVATE(_upb_Arena_IsAligned)(const void* ptr) {
  return (uintptr_t)ptr % UPB_MALLOC_ALIGN == 0;
}

UPB_API_INLINE void* upb_Arena_Malloc(struct upb_Arena* a, size_t size) {
  UPB_PRIVATE(upb_Xsan_AccessReadWrite)(UPB_XSAN(a));

  size_t span = UPB_PRIVATE(_upb_Arena_AllocSpan)(size);

  if (UPB_UNLIKELY(UPB_PRIVATE(_upb_ArenaHas)(a) < span)) {
    void* UPB_PRIVATE(_upb_Arena_SlowMalloc)(struct upb_Arena * a, size_t size);
    return UPB_PRIVATE(_upb_Arena_SlowMalloc)(a, span);
  }

  // We have enough space to do a fast malloc.
  void* ret = a->UPB_ONLYBITS(ptr);
  a->UPB_ONLYBITS(ptr) += span;
  UPB_ASSERT(UPB_PRIVATE(_upb_Arena_IsAligned)(ret));
  UPB_ASSERT(UPB_PRIVATE(_upb_Arena_IsAligned)(a->UPB_ONLYBITS(ptr)));

  return UPB_PRIVATE(upb_Xsan_NewUnpoisonedRegion)(UPB_XSAN(a), ret, size);
}

UPB_API_INLINE void upb_Arena_ShrinkLast(struct upb_Arena* a, void* ptr,
                                         size_t oldsize, size_t size) {
  UPB_ASSERT(ptr);
  UPB_ASSERT(size <= oldsize);

  UPB_PRIVATE(upb_Xsan_AccessReadWrite)(UPB_XSAN(a));
  UPB_PRIVATE(upb_Xsan_ResizeUnpoisonedRegion)(ptr, oldsize, size);

  if (UPB_PRIVATE(_upb_Arena_WasLastAllocFromCurrentBlock)(a, ptr, oldsize)) {
    // We can reclaim some memory.
    a->UPB_ONLYBITS(ptr) -= UPB_ALIGN_MALLOC(oldsize) - UPB_ALIGN_MALLOC(size);
  } else {
    // We can't reclaim any memory, but we need to verify that `ptr` really
    // does represent the most recent allocation.
#ifndef NDEBUG
    bool _upb_Arena_WasLastAlloc(struct upb_Arena * a, void* ptr,
                                 size_t oldsize);
    UPB_ASSERT(_upb_Arena_WasLastAlloc(a, ptr, oldsize));
#endif
  }
}

UPB_API_INLINE bool upb_Arena_TryExtend(struct upb_Arena* a, void* ptr,
                                        size_t oldsize, size_t size) {
  UPB_ASSERT(ptr);
  UPB_ASSERT(size > oldsize);

  UPB_PRIVATE(upb_Xsan_AccessReadWrite)(UPB_XSAN(a));
  size_t extend = UPB_ALIGN_MALLOC(size) - UPB_ALIGN_MALLOC(oldsize);

  if (UPB_PRIVATE(_upb_Arena_WasLastAllocFromCurrentBlock)(a, ptr, oldsize) &&
      UPB_PRIVATE(_upb_ArenaHas)(a) >= extend) {
    a->UPB_ONLYBITS(ptr) += extend;
    UPB_PRIVATE(upb_Xsan_ResizeUnpoisonedRegion)(ptr, oldsize, size);
    return true;
  }

  return false;
}

UPB_API_INLINE void* upb_Arena_Realloc(struct upb_Arena* a, void* ptr,
                                       size_t oldsize, size_t size) {
  UPB_PRIVATE(upb_Xsan_AccessReadWrite)(UPB_XSAN(a));

  void* ret;

  if (ptr && (size <= oldsize || upb_Arena_TryExtend(a, ptr, oldsize, size))) {
    // We can extend or shrink in place.
    if (size <= oldsize &&
        UPB_PRIVATE(_upb_Arena_WasLastAllocFromCurrentBlock)(a, ptr, oldsize)) {
      upb_Arena_ShrinkLast(a, ptr, oldsize, size);
    }
    ret = ptr;
  } else {
    // We need to copy into a new allocation.
    ret = upb_Arena_Malloc(a, size);
    if (ret && oldsize > 0) {
      memcpy(ret, ptr, UPB_MIN(oldsize, size));
    }
  }

  // We want to invalidate pointers to the old region if hwasan is enabled, so
  // we poison and unpoison even if ptr == ret.
  UPB_PRIVATE(upb_Xsan_PoisonRegion)(ptr, oldsize);
  return UPB_PRIVATE(upb_Xsan_NewUnpoisonedRegion)(UPB_XSAN(a), ret, size);
}

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /* UPB_MEM_INTERNAL_ARENA_H_ */

// Must be last.

typedef struct upb_Arena upb_Arena;

typedef void upb_AllocCleanupFunc(upb_alloc* alloc);

#ifdef __cplusplus
extern "C" {
#endif

// Creates an arena from the given initial block (if any -- mem may be NULL). If
// an initial block is specified, the arena's lifetime cannot be extended by
// |upb_Arena_IncRefFor| or |upb_Arena_Fuse|. Additional blocks will be
// allocated from |alloc|. If |alloc| is NULL, this is a fixed-size arena and
// cannot grow. If an initial block is specified, |n| is its length; if there is
// no initial block, |n| is a hint of the size that should be allocated for the
// first block of the arena, such that `upb_Arena_Malloc(hint)` will not require
// another call to |alloc|.
UPB_API upb_Arena* upb_Arena_Init(void* mem, size_t n, upb_alloc* alloc);

UPB_API void upb_Arena_Free(upb_Arena* a);
// Sets the cleanup function for the upb_alloc used by the arena. Only one
// cleanup function can be set, which will be called after all blocks are
// freed.
UPB_API void upb_Arena_SetAllocCleanup(upb_Arena* a,
                                       upb_AllocCleanupFunc* func);

// Fuses the lifetime of two arenas, such that no arenas that have been
// transitively fused together will be freed until all of them have reached a
// zero refcount. This operation is safe to use concurrently from multiple
// threads.
UPB_API bool upb_Arena_Fuse(const upb_Arena* a, const upb_Arena* b);

// This operation is safe to use concurrently from multiple threads.
UPB_API bool upb_Arena_IsFused(const upb_Arena* a, const upb_Arena* b);

// Returns the upb_alloc used by the arena.
UPB_API upb_alloc* upb_Arena_GetUpbAlloc(upb_Arena* a);

// This operation is safe to use concurrently from multiple threads.
bool upb_Arena_IncRefFor(const upb_Arena* a, const void* owner);
// This operation is safe to use concurrently from multiple threads.
void upb_Arena_DecRefFor(const upb_Arena* a, const void* owner);

// Creates a reference between the arenas `from` and `to`, guaranteeing that
// the latter will not be freed until `from` is freed.
//
// Users must avoid all of the following error conditions, which will be
// checked in debug mode but are UB in opt:
//
// - Creating reference cycles between arenas.
// - Creating a reference between two arenas that are fused, either now
//   or in the future.
//
// Creating a reference multiple times between the same two arenas is not UB but
// is considered wasteful and may be disallowed in the future.
//
// Note that fuses can participate in reference cycles. The following set of
// calls creates a cycle A -> B -> C -> A
//   Fuse(A, B);
//   Ref(B, C);
//   Ref(C, A);
//
// From this perspective, the second rule is just a special-case of the first.
// This set of calls is disallowed because it is effectively creating a
// cycle A -> B -> A
//   Fuse(A, B);
//   Ref(B, A);
//
// Fuse is special because it creates what is effectively a bidirectional
// ref, but it is not considered a cycle and will be collected correctly.
//
// Note that `from` is not `const`, so it may not be called concurrently
// with any other function on `from`.
//
// Returns whether the reference was created successfully.
bool upb_Arena_RefArena(upb_Arena* from, const upb_Arena* to);

#ifndef NDEBUG
// Returns true if upb_Arena_RefArena(from, to) was previously called.
// Note that this does not take fuses into account, and it does not follow
// chains of references; it must have been these two arenas exactly that
// created a reference.
bool upb_Arena_HasRef(const upb_Arena* from, const upb_Arena* to);
#endif

// This operation is safe to use concurrently from multiple threads.
uintptr_t upb_Arena_SpaceAllocated(const upb_Arena* a, size_t* fused_count);
// This operation is safe to use concurrently from multiple threads.
uint32_t upb_Arena_DebugRefCount(const upb_Arena* a);

#if UPB_ENABLE_REF_CYCLE_CHECKS
// Returns true if there is a chain of arena refs that spans `from` -> `to`.
// Fused arenas are taken into account; for example, this series of calls
// will cause the function to return true:
//
// 1. upb_Arena_Fuse(a, b)
// 2. upb_Arena_RefArena(from, a)
// 3. upb_Arena_RefArena(b, to)
//
// However this function does not return true if `from` and `to` are directly
// fused.
bool upb_Arena_HasRefChain(const upb_Arena* from, const upb_Arena* to);
#endif

UPB_API_INLINE upb_Arena* upb_Arena_New(void) {
  return upb_Arena_Init(NULL, 0, &upb_alloc_global);
}

UPB_API_INLINE upb_Arena* upb_Arena_NewSized(size_t size_hint) {
  return upb_Arena_Init(NULL, size_hint, &upb_alloc_global);
}

UPB_API_INLINE void* upb_Arena_Malloc(struct upb_Arena* a, size_t size);

UPB_API_INLINE void* upb_Arena_Realloc(upb_Arena* a, void* ptr, size_t oldsize,
                                       size_t size);

static const size_t UPB_PRIVATE(kUpbDefaultMaxBlockSize) =
    UPB_DEFAULT_MAX_BLOCK_SIZE;

// Sets the maximum block size for all arenas. This is a global configuration
// setting that will affect all existing and future arenas. If
// upb_Arena_Malloc() is called with a size larger than this, we will exceed
// this size and allocate a larger block.
//
// This API is meant for experimentation only. It will likely be removed in
// the future.
// This operation is safe to use concurrently from multiple threads.
void upb_Arena_SetMaxBlockSize(size_t max);

// Shrinks the last alloc from arena.
// REQUIRES: (ptr, oldsize) was the last malloc/realloc from this arena.
// We could also add a upb_Arena_TryShrinkLast() which is simply a no-op if
// this was not the last alloc.
UPB_API_INLINE void upb_Arena_ShrinkLast(upb_Arena* a, void* ptr,
                                         size_t oldsize, size_t size);

// Attempts to extend the given alloc from arena, in place. Is generally
// only likely to succeed for the most recent allocation from this arena. If it
// succeeds, returns true and `ptr`'s allocation is now `size` rather than
// `oldsize`. Returns false if the allocation cannot be extended; `ptr`'s
// allocation is unmodified. See also upb_Arena_Realloc.
// REQUIRES: `size > oldsize`; to shrink, use `upb_Arena_Realloc` or
// `upb_Arena_ShrinkLast`.
UPB_API_INLINE bool upb_Arena_TryExtend(upb_Arena* a, void* ptr, size_t oldsize,
                                        size_t size);

#ifdef UPB_TRACING_ENABLED
void upb_Arena_SetTraceHandler(void (*initArenaTraceHandler)(const upb_Arena*,
                                                             size_t size),
                               void (*fuseArenaTraceHandler)(const upb_Arena*,
                                                             const upb_Arena*),
                               void (*freeArenaTraceHandler)(const upb_Arena*));
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /* UPB_MEM_ARENA_H_ */

#ifndef UPB_MESSAGE_ARRAY_H_
#define UPB_MESSAGE_ARRAY_H_

#include <stddef.h>


#ifndef UPB_BASE_DESCRIPTOR_CONSTANTS_H_
#define UPB_BASE_DESCRIPTOR_CONSTANTS_H_

// Must be last.

// The types a field can have. Note that this list is not identical to the
// types defined in descriptor.proto, which gives INT32 and SINT32 separate
// types (we distinguish the two with the "integer encoding" enum below).
// This enum is an internal convenience only and has no meaning outside of upb.
typedef enum {
  kUpb_CType_Bool = 1,
  kUpb_CType_Float = 2,
  kUpb_CType_Int32 = 3,
  kUpb_CType_UInt32 = 4,
  kUpb_CType_Enum = 5,  // Enum values are int32. TODO: rename
  kUpb_CType_Message = 6,
  kUpb_CType_Double = 7,
  kUpb_CType_Int64 = 8,
  kUpb_CType_UInt64 = 9,
  kUpb_CType_String = 10,
  kUpb_CType_Bytes = 11
} upb_CType;

// The repeated-ness of each field; this matches descriptor.proto.
typedef enum {
  kUpb_Label_Optional = 1,
  kUpb_Label_Required = 2,
  kUpb_Label_Repeated = 3
} upb_Label;

// Descriptor types, as defined in descriptor.proto.
typedef enum {
  kUpb_FieldType_Double = 1,
  kUpb_FieldType_Float = 2,
  kUpb_FieldType_Int64 = 3,
  kUpb_FieldType_UInt64 = 4,
  kUpb_FieldType_Int32 = 5,
  kUpb_FieldType_Fixed64 = 6,
  kUpb_FieldType_Fixed32 = 7,
  kUpb_FieldType_Bool = 8,
  kUpb_FieldType_String = 9,
  kUpb_FieldType_Group = 10,
  kUpb_FieldType_Message = 11,
  kUpb_FieldType_Bytes = 12,
  kUpb_FieldType_UInt32 = 13,
  kUpb_FieldType_Enum = 14,
  kUpb_FieldType_SFixed32 = 15,
  kUpb_FieldType_SFixed64 = 16,
  kUpb_FieldType_SInt32 = 17,
  kUpb_FieldType_SInt64 = 18,
} upb_FieldType;

#define kUpb_FieldType_SizeOf 19

#ifdef __cplusplus
extern "C" {
#endif

// Convert from upb_FieldType to upb_CType
UPB_INLINE upb_CType upb_FieldType_CType(upb_FieldType field_type) {
  static const upb_CType c_type[] = {
      kUpb_CType_Double,   // kUpb_FieldType_Double
      kUpb_CType_Float,    // kUpb_FieldType_Float
      kUpb_CType_Int64,    // kUpb_FieldType_Int64
      kUpb_CType_UInt64,   // kUpb_FieldType_UInt64
      kUpb_CType_Int32,    // kUpb_FieldType_Int32
      kUpb_CType_UInt64,   // kUpb_FieldType_Fixed64
      kUpb_CType_UInt32,   // kUpb_FieldType_Fixed32
      kUpb_CType_Bool,     // kUpb_FieldType_Bool
      kUpb_CType_String,   // kUpb_FieldType_String
      kUpb_CType_Message,  // kUpb_FieldType_Group
      kUpb_CType_Message,  // kUpb_FieldType_Message
      kUpb_CType_Bytes,    // kUpb_FieldType_Bytes
      kUpb_CType_UInt32,   // kUpb_FieldType_UInt32
      kUpb_CType_Enum,     // kUpb_FieldType_Enum
      kUpb_CType_Int32,    // kUpb_FieldType_SFixed32
      kUpb_CType_Int64,    // kUpb_FieldType_SFixed64
      kUpb_CType_Int32,    // kUpb_FieldType_SInt32
      kUpb_CType_Int64,    // kUpb_FieldType_SInt64
  };

  // -1 here because the enum is one-based but the table is zero-based.
  return c_type[field_type - 1];
}

UPB_INLINE bool upb_FieldType_IsPackable(upb_FieldType field_type) {
  // clang-format off
  const unsigned kUnpackableTypes =
      (1 << kUpb_FieldType_String) |
      (1 << kUpb_FieldType_Bytes) |
      (1 << kUpb_FieldType_Message) |
      (1 << kUpb_FieldType_Group);
  // clang-format on
  return (1 << field_type) & ~kUnpackableTypes;
}

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /* UPB_BASE_DESCRIPTOR_CONSTANTS_H_ */

#ifndef UPB_MESSAGE_INTERNAL_ARRAY_H_
#define UPB_MESSAGE_INTERNAL_ARRAY_H_

#include <stdint.h>
#include <string.h>


// Must be last.

#define _UPB_ARRAY_MASK_IMM 0x4  // Frozen/immutable bit.
#define _UPB_ARRAY_MASK_LG2 0x3  // Encoded elem size.
#define _UPB_ARRAY_MASK_ALL (_UPB_ARRAY_MASK_IMM | _UPB_ARRAY_MASK_LG2)

#ifdef __cplusplus
extern "C" {
#endif

// LINT.IfChange(upb_Array)

// Our internal representation for repeated fields.
struct upb_Array {
  // This is a tagged pointer. Bits #0 and #1 encode the elem size as follows:
  //   0 maps to elem size 1
  //   1 maps to elem size 4
  //   2 maps to elem size 8
  //   3 maps to elem size 16
  //
  // Bit #2 contains the frozen/immutable flag.
  uintptr_t UPB_ONLYBITS(data);

  size_t UPB_ONLYBITS(size);     // The number of elements in the array.
  size_t UPB_PRIVATE(capacity);  // Allocated storage. Measured in elements.
};

UPB_INLINE void UPB_PRIVATE(_upb_Array_ShallowFreeze)(struct upb_Array* arr) {
  arr->UPB_ONLYBITS(data) |= _UPB_ARRAY_MASK_IMM;
}

UPB_API_INLINE bool upb_Array_IsFrozen(const struct upb_Array* arr) {
  return (arr->UPB_ONLYBITS(data) & _UPB_ARRAY_MASK_IMM) != 0;
}

UPB_INLINE void UPB_PRIVATE(_upb_Array_SetTaggedPtr)(struct upb_Array* array,
                                                     void* data, size_t lg2) {
  UPB_ASSERT(lg2 != 1);
  UPB_ASSERT(lg2 <= 4);
  const size_t bits = lg2 - (lg2 != 0);
  array->UPB_ONLYBITS(data) = (uintptr_t)data | bits;
}

UPB_INLINE size_t
UPB_PRIVATE(_upb_Array_ElemSizeLg2)(const struct upb_Array* array) {
  const size_t bits = array->UPB_ONLYBITS(data) & _UPB_ARRAY_MASK_LG2;
  const size_t lg2 = bits + (bits != 0);
  return lg2;
}

UPB_API_INLINE const void* upb_Array_DataPtr(const struct upb_Array* array) {
  UPB_PRIVATE(_upb_Array_ElemSizeLg2)(array);  // Check assertions.
  return (void*)(array->UPB_ONLYBITS(data) & ~(uintptr_t)_UPB_ARRAY_MASK_ALL);
}

UPB_API_INLINE void* upb_Array_MutableDataPtr(struct upb_Array* array) {
  return (void*)upb_Array_DataPtr(array);
}

UPB_INLINE struct upb_Array* UPB_PRIVATE(_upb_Array_NewMaybeAllowSlow)(
    upb_Arena* arena, size_t init_capacity, int elem_size_lg2,
    bool allow_slow) {
  UPB_ASSERT(elem_size_lg2 != 1);
  UPB_ASSERT(elem_size_lg2 <= 4);
  const size_t array_size =
      UPB_ALIGN_UP(sizeof(struct upb_Array), UPB_MALLOC_ALIGN);
  const size_t bytes = array_size + (init_capacity << elem_size_lg2);
  size_t span = UPB_PRIVATE(_upb_Arena_AllocSpan)(bytes);
  if (!allow_slow && UPB_PRIVATE(_upb_ArenaHas)(arena) < span) return NULL;
  struct upb_Array* array = (struct upb_Array*)upb_Arena_Malloc(arena, bytes);
  if (!array) return NULL;
  UPB_PRIVATE(_upb_Array_SetTaggedPtr)
  (array, UPB_PTR_AT(array, array_size, void), elem_size_lg2);
  array->UPB_ONLYBITS(size) = 0;
  array->UPB_PRIVATE(capacity) = init_capacity;
  return array;
}

UPB_INLINE struct upb_Array* UPB_PRIVATE(_upb_Array_New)(upb_Arena* arena,
                                                         size_t init_capacity,
                                                         int elem_size_lg2) {
  return UPB_PRIVATE(_upb_Array_NewMaybeAllowSlow)(arena, init_capacity,
                                                   elem_size_lg2, true);
}

UPB_INLINE struct upb_Array* UPB_PRIVATE(_upb_Array_TryFastNew)(
    upb_Arena* arena, size_t init_capacity, int elem_size_lg2) {
  return UPB_PRIVATE(_upb_Array_NewMaybeAllowSlow)(arena, init_capacity,
                                                   elem_size_lg2, false);
}

// Resizes the capacity of the array to be at least min_size.
bool UPB_PRIVATE(_upb_Array_Realloc)(struct upb_Array* array, size_t min_size,
                                     upb_Arena* arena);

UPB_FORCEINLINE
bool UPB_PRIVATE(_upb_Array_TryFastRealloc)(struct upb_Array* array,
                                            size_t capacity, int elem_size_lg2,
                                            upb_Arena* arena) {
  size_t old_bytes = array->UPB_PRIVATE(capacity) << elem_size_lg2;
  size_t new_bytes = capacity << elem_size_lg2;
  UPB_ASSUME(new_bytes > old_bytes);
  if (!upb_Arena_TryExtend(arena, array, old_bytes, new_bytes)) return false;
  array->UPB_PRIVATE(capacity) = capacity;
  return true;
}

UPB_API_INLINE bool upb_Array_Reserve(struct upb_Array* array, size_t size,
                                      upb_Arena* arena) {
  UPB_ASSERT(!upb_Array_IsFrozen(array));
  if (array->UPB_PRIVATE(capacity) < size)
    return UPB_PRIVATE(_upb_Array_Realloc)(array, size, arena);
  return true;
}

// Resize without initializing new elements.
UPB_INLINE bool UPB_PRIVATE(_upb_Array_ResizeUninitialized)(
    struct upb_Array* array, size_t size, upb_Arena* arena) {
  UPB_ASSERT(!upb_Array_IsFrozen(array));
  UPB_ASSERT(size <= array->UPB_ONLYBITS(size) ||
             arena);  // Allow NULL arena when shrinking.
  if (!upb_Array_Reserve(array, size, arena)) return false;
  array->UPB_ONLYBITS(size) = size;
  return true;
}

// This function is intended for situations where elem_size is compile-time
// constant or a known expression of the form (1 << lg2), so that the expression
// i*elem_size does not result in an actual multiplication.
UPB_INLINE void UPB_PRIVATE(_upb_Array_Set)(struct upb_Array* array, size_t i,
                                            const void* data,
                                            size_t elem_size) {
  UPB_ASSERT(!upb_Array_IsFrozen(array));
  UPB_ASSERT(i < array->UPB_ONLYBITS(size));
  UPB_ASSERT(elem_size == 1U << UPB_PRIVATE(_upb_Array_ElemSizeLg2)(array));
  char* arr_data = (char*)upb_Array_MutableDataPtr(array);
  memcpy(arr_data + (i * elem_size), data, elem_size);
}

UPB_API_INLINE size_t upb_Array_Size(const struct upb_Array* arr) {
  return arr->UPB_ONLYBITS(size);
}

UPB_API_INLINE size_t upb_Array_Capacity(const struct upb_Array* arr) {
  return arr->UPB_PRIVATE(capacity);
}

// LINT.ThenChange(GoogleInternalName0)

#ifdef __cplusplus
} /* extern "C" */
#endif

#undef _UPB_ARRAY_MASK_IMM
#undef _UPB_ARRAY_MASK_LG2
#undef _UPB_ARRAY_MASK_ALL


#endif /* UPB_MESSAGE_INTERNAL_ARRAY_H_ */

#ifndef UPB_MESSAGE_INTERNAL_TYPES_H_
#define UPB_MESSAGE_INTERNAL_TYPES_H_

#include <stdint.h>

// Must be last.

#define UPB_OPAQUE(x) x##_opaque

struct upb_Message {
  union {
    uintptr_t UPB_OPAQUE(internal);  // tagged pointer, low bit == frozen
    double d;  // Forces same size for 32-bit/64-bit builds
  };
};

#ifdef __cplusplus
extern "C" {
#endif

UPB_INLINE void UPB_PRIVATE(_upb_Message_ShallowFreeze)(
    struct upb_Message* msg) {
  msg->UPB_OPAQUE(internal) |= 1ULL;
}

UPB_API_INLINE bool upb_Message_IsFrozen(const struct upb_Message* msg) {
  return (msg->UPB_OPAQUE(internal) & 1ULL) != 0;
}

UPB_INLINE struct upb_Message_Internal* UPB_PRIVATE(_upb_Message_GetInternal)(
    const struct upb_Message* msg) {
  const uintptr_t tmp = msg->UPB_OPAQUE(internal) & ~1ULL;
  return (struct upb_Message_Internal*)tmp;
}

UPB_INLINE void UPB_PRIVATE(_upb_Message_SetInternal)(
    struct upb_Message* msg, struct upb_Message_Internal* internal) {
  UPB_ASSERT(!upb_Message_IsFrozen(msg));
  msg->UPB_OPAQUE(internal) = (uintptr_t)internal;
}

#ifdef __cplusplus
} /* extern "C" */
#endif

#undef UPB_OPAQUE


#endif /* UPB_MESSAGE_INTERNAL_TYPES_H_ */

// Users should include array.h or map.h instead.
// IWYU pragma: private, include "upb/message/array.h"

#ifndef UPB_MESSAGE_VALUE_H_
#define UPB_MESSAGE_VALUE_H_

#include <stdint.h>
#include <string.h>


// Must be last.

#ifdef __cplusplus
extern "C" {
#endif

typedef union {
  bool bool_val;
  float float_val;
  double double_val;
  int32_t int32_val;
  int64_t int64_val;
  uint32_t uint32_val;
  uint64_t uint64_val;
  const struct upb_Array* array_val;
  const struct upb_Map* map_val;
  const struct upb_Message* msg_val;
  upb_StringView str_val;

  // EXPERIMENTAL: A tagged upb_Message*.  Users must use this instead of
  // msg_val if unlinked sub-messages may possibly be in use.  See the
  // documentation in kUpb_DecodeOption_ExperimentalAllowUnlinked for more
  // information.
  uintptr_t tagged_msg_val;  // upb_TaggedMessagePtr

  // For an extension field, we are essentially treating ext->data (a
  // upb_MessageValue) as if it were a message with one field that lives at
  // offset 0. This works because upb_MessageValue is precisely one value that
  // can hold any type of data. Recall that an extension can be of any type
  // (scalar, repeated, or message). For a message extension, that will be a
  // single upb_Message* at offset 0 of the upb_MessageValue.
  struct upb_Message UPB_PRIVATE(ext_msg_val);
} upb_MessageValue;

UPB_API_INLINE upb_MessageValue upb_MessageValue_Zero(void) {
  upb_MessageValue zero;
  memset(&zero, 0, sizeof(zero));
  return zero;
}

typedef union {
  struct upb_Array* array;
  struct upb_Map* map;
  struct upb_Message* msg;
} upb_MutableMessageValue;

UPB_API_INLINE upb_MutableMessageValue upb_MutableMessageValue_Zero(void) {
  upb_MutableMessageValue zero;
  memset(&zero, 0, sizeof(zero));
  return zero;
}

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /* UPB_MESSAGE_VALUE_H_ */

#ifndef UPB_MINI_TABLE_MESSAGE_H_
#define UPB_MINI_TABLE_MESSAGE_H_

#include <stdint.h>


#ifndef UPB_MINI_TABLE_ENUM_H_
#define UPB_MINI_TABLE_ENUM_H_

#include <stdint.h>


#ifndef UPB_MINI_TABLE_INTERNAL_ENUM_H_
#define UPB_MINI_TABLE_INTERNAL_ENUM_H_

#include <stdint.h>

// Must be last.

struct upb_MiniTableEnum {
  uint32_t UPB_PRIVATE(mask_limit);   // Highest that can be tested with mask.
  uint32_t UPB_PRIVATE(value_count);  // Number of values after the bitfield.
  uint32_t UPB_PRIVATE(data)[];       // Bitmask + enumerated values follow.
};

#ifdef __cplusplus
extern "C" {
#endif

UPB_API_INLINE bool upb_MiniTableEnum_CheckValue(
    const struct upb_MiniTableEnum* e, uint32_t val) {
  if (UPB_LIKELY(val < 64)) {
    const uint64_t mask =
        e->UPB_PRIVATE(data)[0] | ((uint64_t)e->UPB_PRIVATE(data)[1] << 32);
    const uint64_t bit = 1ULL << val;
    return (mask & bit) != 0;
  }
  if (UPB_LIKELY(val < e->UPB_PRIVATE(mask_limit))) {
    const uint32_t mask = e->UPB_PRIVATE(data)[val / 32];
    const uint32_t bit = 1U << (val % 32);
    return (mask & bit) != 0;
  }

  // OPT: binary search long lists?
  const uint32_t* start =
      &e->UPB_PRIVATE(data)[e->UPB_PRIVATE(mask_limit) / 32];
  const uint32_t* limit = &e->UPB_PRIVATE(
      data)[e->UPB_PRIVATE(mask_limit) / 32 + e->UPB_PRIVATE(value_count)];
  for (const uint32_t* p = start; p < limit; p++) {
    if (*p == val) return true;
  }
  return false;
}

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /* UPB_MINI_TABLE_INTERNAL_ENUM_H_ */

// Must be last

typedef struct upb_MiniTableEnum upb_MiniTableEnum;

#ifdef __cplusplus
extern "C" {
#endif

// Validates enum value against range defined by enum mini table.
UPB_API_INLINE bool upb_MiniTableEnum_CheckValue(const upb_MiniTableEnum* e,
                                                 uint32_t val);

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /* UPB_MINI_TABLE_ENUM_H_ */

#ifndef UPB_MINI_TABLE_FIELD_H_
#define UPB_MINI_TABLE_FIELD_H_

#include <stdint.h>


#ifndef UPB_MINI_TABLE_INTERNAL_FIELD_H_
#define UPB_MINI_TABLE_INTERNAL_FIELD_H_

#include <stddef.h>
#include <stdint.h>


#ifndef UPB_MINI_TABLE_INTERNAL_SIZE_LOG2_H_
#define UPB_MINI_TABLE_INTERNAL_SIZE_LOG2_H_

#include <stddef.h>
#include <stdint.h>


// Must be last.

#ifdef __cplusplus
extern "C" {
#endif

// Return the log2 of the storage size in bytes for a upb_CType
UPB_INLINE int UPB_PRIVATE(_upb_CType_SizeLg2)(upb_CType c_type) {
  static const int8_t size[] = {
      0,               // kUpb_CType_Bool
      2,               // kUpb_CType_Float
      2,               // kUpb_CType_Int32
      2,               // kUpb_CType_UInt32
      2,               // kUpb_CType_Enum
      UPB_SIZE(2, 3),  // kUpb_CType_Message
      3,               // kUpb_CType_Double
      3,               // kUpb_CType_Int64
      3,               // kUpb_CType_UInt64
      UPB_SIZE(3, 4),  // kUpb_CType_String
      UPB_SIZE(3, 4),  // kUpb_CType_Bytes
  };

  // -1 here because the enum is one-based but the table is zero-based.
  return size[c_type - 1];
}

// Return the log2 of the storage size in bytes for a upb_FieldType
UPB_INLINE int UPB_PRIVATE(_upb_FieldType_SizeLg2)(upb_FieldType field_type) {
  static const int8_t size[] = {
      3,               // kUpb_FieldType_Double
      2,               // kUpb_FieldType_Float
      3,               // kUpb_FieldType_Int64
      3,               // kUpb_FieldType_UInt64
      2,               // kUpb_FieldType_Int32
      3,               // kUpb_FieldType_Fixed64
      2,               // kUpb_FieldType_Fixed32
      0,               // kUpb_FieldType_Bool
      UPB_SIZE(3, 4),  // kUpb_FieldType_String
      UPB_SIZE(2, 3),  // kUpb_FieldType_Group
      UPB_SIZE(2, 3),  // kUpb_FieldType_Message
      UPB_SIZE(3, 4),  // kUpb_FieldType_Bytes
      2,               // kUpb_FieldType_UInt32
      2,               // kUpb_FieldType_Enum
      2,               // kUpb_FieldType_SFixed32
      3,               // kUpb_FieldType_SFixed64
      2,               // kUpb_FieldType_SInt32
      3,               // kUpb_FieldType_SInt64
  };

  // -1 here because the enum is one-based but the table is zero-based.
  return size[field_type - 1];
}

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /* UPB_MINI_TABLE_INTERNAL_SIZE_LOG2_H_ */

// Must be last.

// LINT.IfChange(struct_definition)
struct upb_MiniTableField {
  uint32_t UPB_ONLYBITS(number);
  uint16_t UPB_ONLYBITS(offset);
  int16_t presence;  // If >0, hasbit_index.  If <0, ~oneof_index

  // Indexes into `upb_MiniTable.subs`
  // Will be set to `kUpb_NoSub` if `descriptortype` != MESSAGE/GROUP/ENUM
  uint16_t UPB_PRIVATE(submsg_index);

  uint8_t UPB_PRIVATE(descriptortype);

  // upb_FieldMode | upb_LabelFlags | (upb_FieldRep << kUpb_FieldRep_Shift)
  uint8_t UPB_ONLYBITS(mode);
};

#define kUpb_NoSub ((uint16_t)-1)

typedef enum {
  kUpb_FieldMode_Map = 0,
  kUpb_FieldMode_Array = 1,
  kUpb_FieldMode_Scalar = 2,
} upb_FieldMode;

// Mask to isolate the upb_FieldMode from field.mode.
#define kUpb_FieldMode_Mask 3

// Extra flags on the mode field.
typedef enum {
  kUpb_LabelFlags_IsPacked = 4,
  kUpb_LabelFlags_IsExtension = 8,
  // Indicates that this descriptor type is an "alternate type":
  //   - for Int32, this indicates that the actual type is Enum (but was
  //     rewritten to Int32 because it is an open enum that requires no check).
  //   - for Bytes, this indicates that the actual type is String (but does
  //     not require any UTF-8 check).
  kUpb_LabelFlags_IsAlternate = 16,
} upb_LabelFlags;

// Note: we sort by this number when calculating layout order.
typedef enum {
  kUpb_FieldRep_1Byte = 0,
  kUpb_FieldRep_4Byte = 1,
  kUpb_FieldRep_StringView = 2,
  kUpb_FieldRep_8Byte = 3,

  kUpb_FieldRep_NativePointer =
      UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte),
  kUpb_FieldRep_Max = kUpb_FieldRep_8Byte,
} upb_FieldRep;

#define kUpb_FieldRep_Shift 6

#ifdef __cplusplus
extern "C" {
#endif

UPB_INLINE upb_FieldMode
UPB_PRIVATE(_upb_MiniTableField_Mode)(const struct upb_MiniTableField* f) {
  return (upb_FieldMode)(f->UPB_ONLYBITS(mode) & kUpb_FieldMode_Mask);
}

UPB_INLINE upb_FieldRep
UPB_PRIVATE(_upb_MiniTableField_GetRep)(const struct upb_MiniTableField* f) {
  return (upb_FieldRep)(f->UPB_ONLYBITS(mode) >> kUpb_FieldRep_Shift);
}

UPB_API_INLINE bool upb_MiniTableField_IsArray(
    const struct upb_MiniTableField* f) {
  return UPB_PRIVATE(_upb_MiniTableField_Mode)(f) == kUpb_FieldMode_Array;
}

UPB_API_INLINE bool upb_MiniTableField_IsMap(
    const struct upb_MiniTableField* f) {
  return UPB_PRIVATE(_upb_MiniTableField_Mode)(f) == kUpb_FieldMode_Map;
}

UPB_API_INLINE bool upb_MiniTableField_IsScalar(
    const struct upb_MiniTableField* f) {
  return UPB_PRIVATE(_upb_MiniTableField_Mode)(f) == kUpb_FieldMode_Scalar;
}

UPB_INLINE bool UPB_PRIVATE(_upb_MiniTableField_IsAlternate)(
    const struct upb_MiniTableField* f) {
  return (f->UPB_ONLYBITS(mode) & kUpb_LabelFlags_IsAlternate) != 0;
}

UPB_API_INLINE bool upb_MiniTableField_IsExtension(
    const struct upb_MiniTableField* f) {
  return (f->UPB_ONLYBITS(mode) & kUpb_LabelFlags_IsExtension) != 0;
}

UPB_API_INLINE bool upb_MiniTableField_IsPacked(
    const struct upb_MiniTableField* f) {
  return (f->UPB_ONLYBITS(mode) & kUpb_LabelFlags_IsPacked) != 0;
}

UPB_API_INLINE upb_FieldType
upb_MiniTableField_Type(const struct upb_MiniTableField* f) {
  const upb_FieldType type = (upb_FieldType)f->UPB_PRIVATE(descriptortype);
  if (UPB_PRIVATE(_upb_MiniTableField_IsAlternate)(f)) {
    if (type == kUpb_FieldType_Int32) return kUpb_FieldType_Enum;
    if (type == kUpb_FieldType_Bytes) return kUpb_FieldType_String;
    UPB_ASSERT(false);
  }
  return type;
}

UPB_API_INLINE
upb_CType upb_MiniTableField_CType(const struct upb_MiniTableField* f) {
  return upb_FieldType_CType(upb_MiniTableField_Type(f));
}

UPB_INLINE bool UPB_PRIVATE(_upb_MiniTableField_HasHasbit)(
    const struct upb_MiniTableField* f) {
  return f->presence > 0;
}

UPB_INLINE char UPB_PRIVATE(_upb_MiniTableField_HasbitMask)(
    const struct upb_MiniTableField* f) {
  UPB_ASSERT(UPB_PRIVATE(_upb_MiniTableField_HasHasbit)(f));
  const uint16_t index = f->presence;
  return (char)(1 << (index % 8));
}

UPB_INLINE uint16_t UPB_PRIVATE(_upb_MiniTableField_HasbitOffset)(
    const struct upb_MiniTableField* f) {
  UPB_ASSERT(UPB_PRIVATE(_upb_MiniTableField_HasHasbit)(f));
  const uint16_t index = f->presence;
  return index / 8;
}

UPB_API_INLINE bool upb_MiniTableField_IsClosedEnum(
    const struct upb_MiniTableField* f) {
  return f->UPB_PRIVATE(descriptortype) == kUpb_FieldType_Enum;
}

UPB_API_INLINE bool upb_MiniTableField_IsInOneof(
    const struct upb_MiniTableField* f) {
  return f->presence < 0;
}

UPB_API_INLINE bool upb_MiniTableField_IsSubMessage(
    const struct upb_MiniTableField* f) {
  return f->UPB_PRIVATE(descriptortype) == kUpb_FieldType_Message ||
         f->UPB_PRIVATE(descriptortype) == kUpb_FieldType_Group;
}

UPB_API_INLINE bool upb_MiniTableField_HasPresence(
    const struct upb_MiniTableField* f) {
  if (upb_MiniTableField_IsExtension(f)) {
    return upb_MiniTableField_IsScalar(f);
  } else {
    return f->presence != 0;
  }
}

UPB_API_INLINE uint32_t
upb_MiniTableField_Number(const struct upb_MiniTableField* f) {
  return f->UPB_ONLYBITS(number);
}

UPB_INLINE uint16_t
UPB_PRIVATE(_upb_MiniTableField_Offset)(const struct upb_MiniTableField* f) {
  return f->UPB_ONLYBITS(offset);
}

UPB_INLINE size_t UPB_PRIVATE(_upb_MiniTableField_OneofOffset)(
    const struct upb_MiniTableField* f) {
  UPB_ASSERT(upb_MiniTableField_IsInOneof(f));
  return ~(ptrdiff_t)f->presence;
}

UPB_INLINE void UPB_PRIVATE(_upb_MiniTableField_CheckIsArray)(
    const struct upb_MiniTableField* f) {
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableField_GetRep)(f) ==
             kUpb_FieldRep_NativePointer);
  UPB_ASSUME(upb_MiniTableField_IsArray(f));
  UPB_ASSUME(f->presence == 0);
}

UPB_INLINE void UPB_PRIVATE(_upb_MiniTableField_CheckIsMap)(
    const struct upb_MiniTableField* f) {
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableField_GetRep)(f) ==
             kUpb_FieldRep_NativePointer);
  UPB_ASSUME(upb_MiniTableField_IsMap(f));
  UPB_ASSUME(f->presence == 0);
}

UPB_INLINE size_t UPB_PRIVATE(_upb_MiniTableField_ElemSizeLg2)(
    const struct upb_MiniTableField* f) {
  const upb_FieldType field_type = upb_MiniTableField_Type(f);
  return UPB_PRIVATE(_upb_FieldType_SizeLg2)(field_type);
}

// LINT.ThenChange(//depot/google3/third_party/upb/bits/typescript/mini_table_field.ts)

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /* UPB_MINI_TABLE_INTERNAL_FIELD_H_ */

// Must be last.

typedef struct upb_MiniTableField upb_MiniTableField;

#ifdef __cplusplus
extern "C" {
#endif

UPB_API_INLINE upb_CType upb_MiniTableField_CType(const upb_MiniTableField* f);

UPB_API_INLINE bool upb_MiniTableField_HasPresence(const upb_MiniTableField* f);

UPB_API_INLINE bool upb_MiniTableField_IsArray(const upb_MiniTableField* f);

UPB_API_INLINE bool upb_MiniTableField_IsClosedEnum(
    const upb_MiniTableField* f);

UPB_API_INLINE bool upb_MiniTableField_IsExtension(const upb_MiniTableField* f);

UPB_API_INLINE bool upb_MiniTableField_IsInOneof(const upb_MiniTableField* f);

UPB_API_INLINE bool upb_MiniTableField_IsMap(const upb_MiniTableField* f);

UPB_API_INLINE bool upb_MiniTableField_IsPacked(const upb_MiniTableField* f);

UPB_API_INLINE bool upb_MiniTableField_IsScalar(const upb_MiniTableField* f);

UPB_API_INLINE bool upb_MiniTableField_IsSubMessage(
    const upb_MiniTableField* f);

UPB_API_INLINE uint32_t upb_MiniTableField_Number(const upb_MiniTableField* f);

UPB_API_INLINE upb_FieldType
upb_MiniTableField_Type(const upb_MiniTableField* f);

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /* UPB_MINI_TABLE_FIELD_H_ */

#ifndef UPB_MINI_TABLE_INTERNAL_MESSAGE_H_
#define UPB_MINI_TABLE_INTERNAL_MESSAGE_H_

#include <stddef.h>
#include <stdint.h>


#ifndef UPB_MINI_TABLE_INTERNAL_SUB_H_
#define UPB_MINI_TABLE_INTERNAL_SUB_H_

// Must be last.

typedef union {
  const struct upb_MiniTable* const* UPB_PRIVATE(submsg);
  const struct upb_MiniTableEnum* UPB_PRIVATE(subenum);
} upb_MiniTableSubInternal;

union upb_MiniTableSub {
  const struct upb_MiniTable* UPB_PRIVATE(submsg);
  const struct upb_MiniTableEnum* UPB_PRIVATE(subenum);
};

#ifdef __cplusplus
extern "C" {
#endif

UPB_API_INLINE union upb_MiniTableSub upb_MiniTableSub_FromEnum(
    const struct upb_MiniTableEnum* subenum) {
  union upb_MiniTableSub out;
  out.UPB_PRIVATE(subenum) = subenum;
  return out;
}

UPB_API_INLINE union upb_MiniTableSub upb_MiniTableSub_FromMessage(
    const struct upb_MiniTable* submsg) {
  union upb_MiniTableSub out;
  out.UPB_PRIVATE(submsg) = submsg;
  return out;
}

UPB_API_INLINE const struct upb_MiniTableEnum* upb_MiniTableSub_Enum(
    const union upb_MiniTableSub sub) {
  return sub.UPB_PRIVATE(subenum);
}

UPB_API_INLINE const struct upb_MiniTable* upb_MiniTableSub_Message(
    const union upb_MiniTableSub sub) {
  return sub.UPB_PRIVATE(submsg);
}

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /* UPB_MINI_TABLE_INTERNAL_SUB_H_ */

// Must be last.

struct upb_Decoder;
struct upb_Message;

typedef UPB_PRESERVE_NONE const char* _upb_FieldParser(
    struct upb_Decoder* d, const char* ptr, struct upb_Message* msg,
    intptr_t table, uint64_t hasbits, uint64_t data);

typedef struct {
  uint64_t field_data;
  _upb_FieldParser* field_parser;
} _upb_FastTable_Entry;

typedef enum {
  kUpb_ExtMode_NonExtendable = 0,  // Non-extendable message.
  kUpb_ExtMode_Extendable = 1,     // Normal extendable message.
  kUpb_ExtMode_IsMessageSet = 2,   // MessageSet message.
  kUpb_ExtMode_IsMessageSet_ITEM =
      3,  // MessageSet item (temporary only, see decode.c)

  // During table building we steal a bit to indicate that the message is a map
  // entry.  *Only* used during table building!
  kUpb_ExtMode_IsMapEntry = 4,
} upb_ExtMode;

enum {
  kUpb_Message_Align = 8,
};

// upb_MiniTable represents the memory layout of a given upb_MessageDef.
// The members are public so generated code can initialize them,
// but users MUST NOT directly read or write any of its members.

// LINT.IfChange(minitable_struct_definition)
struct upb_MiniTable {
  const upb_MiniTableSubInternal* UPB_PRIVATE(subs);
  const struct upb_MiniTableField* UPB_ONLYBITS(fields);

  // Must be aligned to kUpb_Message_Align. Doesn't include internal members
  // like unknown fields, extension dict, pointer to msglayout, etc.
  uint16_t UPB_PRIVATE(size);

  uint16_t UPB_ONLYBITS(field_count);

  uint8_t UPB_PRIVATE(ext);  // upb_ExtMode, uint8_t here so sizeof(ext) == 1
  uint8_t UPB_PRIVATE(dense_below);
  uint8_t UPB_PRIVATE(table_mask);
  uint8_t UPB_PRIVATE(required_count);  // Required fields have the low hasbits.

#ifdef UPB_TRACING_ENABLED
  const char* UPB_PRIVATE(full_name);
#endif

#if UPB_FASTTABLE || !defined(__cplusplus)
  // Flexible array member is not supported in C++, but it is an extension in
  // every compiler that supports UPB_FASTTABLE.
  _upb_FastTable_Entry UPB_PRIVATE(fasttable)[];
#endif
};
// LINT.ThenChange(//depot/google3/third_party/upb/bits/typescript/mini_table.ts)

#ifdef __cplusplus
extern "C" {
#endif

UPB_INLINE void UPB_PRIVATE(upb_MiniTable_CheckInvariants)(
    const struct upb_MiniTable* mt) {
  UPB_STATIC_ASSERT(UPB_MALLOC_ALIGN >= kUpb_Message_Align, "Under aligned");
  UPB_STATIC_ASSERT(kUpb_Message_Align >= UPB_ALIGN_OF(void*), "Under aligned");
  UPB_ASSERT(mt->UPB_PRIVATE(size) % kUpb_Message_Align == 0);
}

UPB_INLINE const struct upb_MiniTable* UPB_PRIVATE(
    _upb_MiniTable_StrongReference)(const struct upb_MiniTable* mt) {
#if defined(__GNUC__)
  __asm__("" : : "r"(mt));
#else
  const struct upb_MiniTable* volatile unused = mt;
  (void)&unused;  // Use address to avoid an extra load of "unused".
#endif
  return mt;
}

UPB_INLINE const struct upb_MiniTable* UPB_PRIVATE(_upb_MiniTable_Empty)(void) {
  extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_Empty);

  return &UPB_PRIVATE(_kUpb_MiniTable_Empty);
}

UPB_API_INLINE int upb_MiniTable_FieldCount(const struct upb_MiniTable* m) {
  return m->UPB_ONLYBITS(field_count);
}

UPB_API_INLINE bool upb_MiniTable_IsMessageSet(const struct upb_MiniTable* m) {
  return m->UPB_PRIVATE(ext) == kUpb_ExtMode_IsMessageSet;
}

UPB_API_INLINE
const struct upb_MiniTableField* upb_MiniTable_FindFieldByNumber(
    const struct upb_MiniTable* m, uint32_t number) {
  const size_t i = ((size_t)number) - 1;  // 0 wraps to SIZE_MAX

  // Ideal case: index into dense fields
  if (i < m->UPB_PRIVATE(dense_below)) {
    UPB_ASSERT(m->UPB_ONLYBITS(fields)[i].UPB_ONLYBITS(number) == number);
    return &m->UPB_ONLYBITS(fields)[i];
  }

  // Early exit if the field number is out of range.
  int32_t hi = m->UPB_ONLYBITS(field_count) - 1;
  if (hi < 0 || number > m->UPB_ONLYBITS(fields)[hi].UPB_ONLYBITS(number)) {
    return NULL;
  }

  // Slow case: binary search
  uint32_t lo = m->UPB_PRIVATE(dense_below);
  const struct upb_MiniTableField* base = m->UPB_ONLYBITS(fields);
  while (hi >= (int32_t)lo) {
    uint32_t mid = (hi + lo) / 2;
    uint32_t num = base[mid].UPB_ONLYBITS(number);
    // These comparison operations allow, on ARM machines, to fuse all these
    // branches into one comparison followed by two CSELs to set the lo/hi
    // values, followed by a BNE to continue or terminate the loop. Since binary
    // search branches are generally unpredictable (50/50 in each direction),
    // this is a good deal. We use signed for the high, as this decrement may
    // underflow if mid is 0.
    int32_t hi_mid = mid - 1;
    uint32_t lo_mid = mid + 1;
    if (num == number) {
      return &base[mid];
    }
    if (UPB_UNPREDICTABLE(num < number)) {
      lo = lo_mid;
    } else {
      hi = hi_mid;
    }
  }

  return NULL;
}

UPB_INLINE bool UPB_PRIVATE(_upb_MiniTable_IsEmpty)(
    const struct upb_MiniTable* m) {
  extern const struct upb_MiniTable UPB_PRIVATE(_kUpb_MiniTable_Empty);

  return m == &UPB_PRIVATE(_kUpb_MiniTable_Empty);
}

UPB_API_INLINE const struct upb_MiniTableField* upb_MiniTable_GetFieldByIndex(
    const struct upb_MiniTable* m, uint32_t i) {
  return &m->UPB_ONLYBITS(fields)[i];
}

UPB_INLINE const struct upb_MiniTable* UPB_PRIVATE(
    _upb_MiniTable_GetSubTableByIndex)(const struct upb_MiniTable* m,
                                       uint32_t i) {
  return *m->UPB_PRIVATE(subs)[i].UPB_PRIVATE(submsg);
}

UPB_API_INLINE const struct upb_MiniTable* upb_MiniTable_SubMessage(
    const struct upb_MiniTable* m, const struct upb_MiniTableField* f) {
  if (upb_MiniTableField_CType(f) != kUpb_CType_Message) {
    return NULL;
  }
  return UPB_PRIVATE(_upb_MiniTable_GetSubTableByIndex)(
      m, f->UPB_PRIVATE(submsg_index));
}

UPB_API_INLINE const struct upb_MiniTable* upb_MiniTable_GetSubMessageTable(
    const struct upb_MiniTable* m, const struct upb_MiniTableField* f) {
  UPB_ASSUME(upb_MiniTableField_CType(f) == kUpb_CType_Message);
  const struct upb_MiniTable* ret = upb_MiniTable_SubMessage(m, f);
  UPB_ASSUME(ret);
  return UPB_PRIVATE(_upb_MiniTable_IsEmpty)(ret) ? NULL : ret;
}

UPB_API_INLINE bool upb_MiniTable_FieldIsLinked(
    const struct upb_MiniTable* m, const struct upb_MiniTableField* f) {
  return upb_MiniTable_GetSubMessageTable(m, f) != NULL;
}

UPB_API_INLINE const struct upb_MiniTable* upb_MiniTable_MapEntrySubMessage(
    const struct upb_MiniTable* m, const struct upb_MiniTableField* f) {
  UPB_ASSERT(upb_MiniTable_FieldIsLinked(m, f));  // Map entries must be linked.
  UPB_ASSERT(upb_MiniTableField_IsMap(f));        // Function precondition.
  return upb_MiniTable_SubMessage(m, f);
}

UPB_API_INLINE const struct upb_MiniTableEnum* upb_MiniTable_GetSubEnumTable(
    const struct upb_MiniTable* m, const struct upb_MiniTableField* f) {
  UPB_ASSERT(upb_MiniTableField_CType(f) == kUpb_CType_Enum);
  return m->UPB_PRIVATE(subs)[f->UPB_PRIVATE(submsg_index)].UPB_PRIVATE(
      subenum);
}

UPB_API_INLINE const struct upb_MiniTableField* upb_MiniTable_MapKey(
    const struct upb_MiniTable* m) {
  UPB_ASSERT(upb_MiniTable_FieldCount(m) == 2);
  const struct upb_MiniTableField* f = upb_MiniTable_GetFieldByIndex(m, 0);
  UPB_ASSERT(upb_MiniTableField_Number(f) == 1);
  return f;
}

UPB_API_INLINE const struct upb_MiniTableField* upb_MiniTable_MapValue(
    const struct upb_MiniTable* m) {
  UPB_ASSERT(upb_MiniTable_FieldCount(m) == 2);
  const struct upb_MiniTableField* f = upb_MiniTable_GetFieldByIndex(m, 1);
  UPB_ASSERT(upb_MiniTableField_Number(f) == 2);
  return f;
}

// Computes a bitmask in which the |m->required_count| lowest bits are set.
//
// Sample output:
//    RequiredMask(1) => 0b1 (0x1)
//    RequiredMask(5) => 0b11111 (0x1f)
UPB_INLINE uint64_t
UPB_PRIVATE(_upb_MiniTable_RequiredMask)(const struct upb_MiniTable* m) {
  int n = m->UPB_PRIVATE(required_count);
  UPB_ASSERT(0 < n && n <= 64);
  return (1ULL << n) - 1;
}

#ifdef UPB_TRACING_ENABLED
UPB_INLINE const char* upb_MiniTable_FullName(
    const struct upb_MiniTable* mini_table) {
  return mini_table->UPB_PRIVATE(full_name);
}
// Initializes tracing proto name from language runtimes that construct
// mini tables dynamically at runtime. The runtime is responsible for passing
// controlling lifetime of name such as storing in same arena as mini_table.
UPB_INLINE void upb_MiniTable_SetFullName(struct upb_MiniTable* mini_table,
                                          const char* full_name) {
  mini_table->UPB_PRIVATE(full_name) = full_name;
}
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /* UPB_MINI_TABLE_INTERNAL_MESSAGE_H_ */

// Must be last.

typedef struct upb_MiniTable upb_MiniTable;

#ifdef __cplusplus
extern "C" {
#endif

UPB_API_INLINE const upb_MiniTableField* upb_MiniTable_FindFieldByNumber(
    const upb_MiniTable* m, uint32_t number);

UPB_API_INLINE const upb_MiniTableField* upb_MiniTable_GetFieldByIndex(
    const upb_MiniTable* m, uint32_t index);

UPB_API_INLINE int upb_MiniTable_FieldCount(const upb_MiniTable* m);

UPB_API_INLINE bool upb_MiniTable_IsMessageSet(const upb_MiniTable* m);

// DEPRECATED: use upb_MiniTable_SubMessage() instead
// Returns the MiniTable for a message field, NULL if the field is unlinked.
UPB_API_INLINE const upb_MiniTable* upb_MiniTable_GetSubMessageTable(
    const upb_MiniTable* m, const upb_MiniTableField* f);

// Returns the MiniTable for a message field if it is a submessage, otherwise
// returns NULL.
//
// WARNING: if dynamic tree shaking is in use, the return value may be the
// "empty", zero-field placeholder message instead of the real message type.
// If the message is later linked, this function will begin returning the real
// message type.
UPB_API_INLINE const upb_MiniTable* upb_MiniTable_SubMessage(
    const upb_MiniTable* m, const upb_MiniTableField* f);

// Returns the MiniTable for a map field.  The given field must refer to a map.
UPB_API_INLINE const upb_MiniTable* upb_MiniTable_MapEntrySubMessage(
    const upb_MiniTable* m, const upb_MiniTableField* f);

// Returns the MiniTableEnum for a message field, NULL if the field is unlinked.
UPB_API_INLINE const upb_MiniTableEnum* upb_MiniTable_GetSubEnumTable(
    const upb_MiniTable* m, const upb_MiniTableField* f);

// Returns the MiniTableField for the key of a map.
UPB_API_INLINE const upb_MiniTableField* upb_MiniTable_MapKey(
    const upb_MiniTable* m);

// Returns the MiniTableField for the value of a map.
UPB_API_INLINE const upb_MiniTableField* upb_MiniTable_MapValue(
    const upb_MiniTable* m);

// Returns true if this MiniTable field is linked to a MiniTable for the
// sub-message.
UPB_API_INLINE bool upb_MiniTable_FieldIsLinked(const upb_MiniTable* m,
                                                const upb_MiniTableField* f);

// If this field is in a oneof, returns the first field in the oneof.
//
// Otherwise returns NULL.
//
// Usage:
//   const upb_MiniTableField* field = upb_MiniTable_GetOneof(m, f);
//   do {
//       ..
//   } while (upb_MiniTable_NextOneofField(m, &field);
//
const upb_MiniTableField* upb_MiniTable_GetOneof(const upb_MiniTable* m,
                                                 const upb_MiniTableField* f);

// Iterates to the next field in the oneof. If this is the last field in the
// oneof, returns false. The ordering of fields in the oneof is not
// guaranteed.
// REQUIRES: |f| is the field initialized by upb_MiniTable_GetOneof and updated
//           by prior upb_MiniTable_NextOneofField calls.
bool upb_MiniTable_NextOneofField(const upb_MiniTable* m,
                                  const upb_MiniTableField** f);

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /* UPB_MINI_TABLE_MESSAGE_H_ */

// Must be last.

typedef struct upb_Array upb_Array;

#ifdef __cplusplus
extern "C" {
#endif

// Creates a new array on the given arena that holds elements of this type.
UPB_API upb_Array* upb_Array_New(upb_Arena* a, upb_CType type);

// Returns the number of elements in the array.
UPB_API_INLINE size_t upb_Array_Size(const upb_Array* arr);

// Returns the number of elements in the array.
UPB_API_INLINE size_t upb_Array_Capacity(const upb_Array* arr);

// Returns the given element, which must be within the array's current size.
UPB_API upb_MessageValue upb_Array_Get(const upb_Array* arr, size_t i);

// Returns a non-null mutating pointer to the given element. `arr` must be an
// array of a message type, and `i` must be within the array's current size.
UPB_API struct upb_Message* upb_Array_GetMutable(upb_Array* arr, size_t i);

// Sets the given element, which must be within the array's current size.
UPB_API void upb_Array_Set(upb_Array* arr, size_t i, upb_MessageValue val);

// Appends an element to the array. Returns false on allocation failure.
UPB_API bool upb_Array_Append(upb_Array* array, upb_MessageValue val,
                              upb_Arena* arena);

// Moves elements within the array using memmove().
// Like memmove(), the source and destination elements may be overlapping.
UPB_API void upb_Array_Move(upb_Array* array, size_t dst_idx, size_t src_idx,
                            size_t count);

// Inserts one or more empty elements into the array.
// Existing elements are shifted right.
// The new elements have undefined state and must be set with `upb_Array_Set()`.
// REQUIRES: `i <= upb_Array_Size(arr)`
UPB_API bool upb_Array_Insert(upb_Array* array, size_t i, size_t count,
                              upb_Arena* arena);

// Deletes one or more elements from the array.
// Existing elements are shifted left.
// REQUIRES: `i + count <= upb_Array_Size(arr)`
UPB_API void upb_Array_Delete(upb_Array* array, size_t i, size_t count);

// Reserves |size| elements of storage for the array.
UPB_API_INLINE bool upb_Array_Reserve(struct upb_Array* array, size_t size,
                                      upb_Arena* arena);

// Changes the size of a vector. New elements are initialized to NULL/0.
// Returns false on allocation failure.
UPB_API bool upb_Array_Resize(upb_Array* array, size_t size, upb_Arena* arena);

// Returns pointer to array data.
UPB_API_INLINE const void* upb_Array_DataPtr(const upb_Array* arr);

// Returns mutable pointer to array data.
UPB_API_INLINE void* upb_Array_MutableDataPtr(upb_Array* arr);

// Mark an array and all of its descendents as frozen/immutable.
// If the array elements are messages then |m| must point to the minitable for
// those messages. Otherwise |m| must be NULL.
UPB_API void upb_Array_Freeze(upb_Array* arr, const upb_MiniTable* m);

// Returns whether an array has been frozen.
UPB_API_INLINE bool upb_Array_IsFrozen(const upb_Array* arr);

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /* UPB_MESSAGE_ARRAY_H_ */

#ifndef UPB_MESSAGE_INTERNAL_ACCESSORS_H_
#define UPB_MESSAGE_INTERNAL_ACCESSORS_H_

#include <stddef.h>
#include <stdint.h>
#include <string.h>


#ifndef UPB_BASE_INTERNAL_ENDIAN_H_
#define UPB_BASE_INTERNAL_ENDIAN_H_

#include <stdint.h>

// Must be last.

#ifdef __cplusplus
extern "C" {
#endif

UPB_INLINE bool upb_IsLittleEndian(void) {
  const int x = 1;
  return *(char*)&x == 1;
}

UPB_INLINE uint32_t upb_BigEndian32(uint32_t val) {
  if (upb_IsLittleEndian()) return val;

  return ((val & 0xff) << 24) | ((val & 0xff00) << 8) |
         ((val & 0xff0000) >> 8) | ((val & 0xff000000) >> 24);
}

UPB_INLINE uint64_t upb_BigEndian64(uint64_t val) {
  if (upb_IsLittleEndian()) return val;

  const uint64_t hi = ((uint64_t)upb_BigEndian32((uint32_t)val)) << 32;
  const uint64_t lo = upb_BigEndian32((uint32_t)(val >> 32));
  return hi | lo;
}

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /* UPB_BASE_INTERNAL_ENDIAN_H_ */

#ifndef UPB_MESSAGE_INTERNAL_EXTENSION_H_
#define UPB_MESSAGE_INTERNAL_EXTENSION_H_

#include <stddef.h>


#ifndef UPB_MESSAGE_INTERNAL_MAP_H_
#define UPB_MESSAGE_INTERNAL_MAP_H_

#include <stddef.h>
#include <stdint.h>
#include <string.h>


/*
 * upb_table
 *
 * This header is INTERNAL-ONLY!  Its interfaces are not public or stable!
 * This file defines very fast int->upb_value (inttable) and string->upb_value
 * (strtable) hash tables.
 *
 * The table uses chained scatter with Brent's variation (inspired by the Lua
 * implementation of hash tables).  The hash function for strings is Austin
 * Appleby's "MurmurHash."
 *
 * The inttable uses uintptr_t as its key, which guarantees it can be used to
 * store pointers or integers of at least 32 bits (upb isn't really useful on
 * systems where sizeof(void*) < 4).
 *
 * The table must be homogeneous (all values of the same type).  In debug
 * mode, we check this on insert and lookup.
 */

#ifndef UPB_HASH_COMMON_H_
#define UPB_HASH_COMMON_H_

#include <stdint.h>
#include <string.h>


// Must be last.

#ifdef __cplusplus
extern "C" {
#endif

/* upb_value ******************************************************************/

typedef struct {
  uint64_t val;
} upb_value;

/* For each value ctype, define the following set of functions:
 *
 * // Get/set an int32 from a upb_value.
 * int32_t upb_value_getint32(upb_value val);
 * void upb_value_setint32(upb_value *val, int32_t cval);
 *
 * // Construct a new upb_value from an int32.
 * upb_value upb_value_int32(int32_t val); */
#define FUNCS(name, membername, type_t, converter)                   \
  UPB_INLINE void upb_value_set##name(upb_value* val, type_t cval) { \
    val->val = (uint64_t)cval;                                       \
  }                                                                  \
  UPB_INLINE upb_value upb_value_##name(type_t val) {                \
    upb_value ret;                                                   \
    upb_value_set##name(&ret, val);                                  \
    return ret;                                                      \
  }                                                                  \
  UPB_INLINE type_t upb_value_get##name(upb_value val) {             \
    return (type_t)(converter)val.val;                               \
  }

FUNCS(int32, int32, int32_t, int32_t)
FUNCS(int64, int64, int64_t, int64_t)
FUNCS(uint32, uint32, uint32_t, uint32_t)
FUNCS(uint64, uint64, uint64_t, uint64_t)
FUNCS(bool, _bool, bool, bool)
FUNCS(cstr, cstr, char*, uintptr_t)
FUNCS(uintptr, uptr, uintptr_t, uintptr_t)
FUNCS(ptr, ptr, void*, uintptr_t)
FUNCS(constptr, constptr, const void*, uintptr_t)

#undef FUNCS

UPB_INLINE void upb_value_setfloat(upb_value* val, float cval) {
  memcpy(&val->val, &cval, sizeof(cval));
}

UPB_INLINE void upb_value_setdouble(upb_value* val, double cval) {
  memcpy(&val->val, &cval, sizeof(cval));
}

UPB_INLINE upb_value upb_value_float(float cval) {
  upb_value ret;
  upb_value_setfloat(&ret, cval);
  return ret;
}

UPB_INLINE upb_value upb_value_double(double cval) {
  upb_value ret;
  upb_value_setdouble(&ret, cval);
  return ret;
}

/* upb_key *****************************************************************/

// A uint32 size followed by that number of bytes stored contiguously.
typedef struct {
  uint32_t size;
  const char data[];
} upb_SizePrefixString;

/* Either:
 *   1. an actual integer key
 *   2. a SizePrefixString*, owned by us.
 *
 * ...depending on whether this is a string table or an int table. */
typedef union {
  uintptr_t num;
  const upb_SizePrefixString* str;
} upb_key;

UPB_INLINE upb_StringView upb_key_strview(upb_key key) {
  return upb_StringView_FromDataAndSize(key.str->data, key.str->size);
}

/* upb_table ******************************************************************/

typedef struct _upb_tabent {
  upb_value val;
  upb_key key;

  /* Internal chaining.  This is const so we can create static initializers for
   * tables.  We cast away const sometimes, but *only* when the containing
   * upb_table is known to be non-const.  This requires a bit of care, but
   * the subtlety is confined to table.c. */
  const struct _upb_tabent* next;
} upb_tabent;

typedef struct {
  upb_tabent* entries;
  /* Number of entries in the hash part. */
  uint32_t count;

  /* Mask to turn hash value -> bucket. The map's allocated size is mask + 1.*/
  uint32_t mask;
} upb_table;

UPB_INLINE size_t upb_table_size(const upb_table* t) { return t->mask + 1; }

// Internal-only functions, in .h file only out of necessity.

UPB_INLINE upb_key upb_key_empty(void) {
  upb_key ret;
  memset(&ret, 0, sizeof(upb_key));
  return ret;
}

UPB_INLINE bool upb_tabent_isempty(const upb_tabent* e) {
  upb_key key = e->key;
  UPB_ASSERT(sizeof(key.num) == sizeof(key.str));
  uintptr_t val;
  memcpy(&val, &key, sizeof(val));
  // Note: for upb_inttables a tab_key is a true integer key value, but the
  // inttable maintains the invariant that 0 value is always stored in the
  // compact table and never as a upb_tabent* so we can always use the 0
  // key value to identify an empty tabent.
  return val == 0;
}

uint32_t _upb_Hash(const void* p, size_t n, uint64_t seed);

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /* UPB_HASH_COMMON_H_ */

#ifndef UPB_HASH_INT_TABLE_H_
#define UPB_HASH_INT_TABLE_H_

#include <stddef.h>
#include <stdint.h>


// Must be last.

typedef struct {
  upb_table t;  // For entries that don't fit in the array part.
  // Array part of the table.
  // Pointers on this table are const so we can create static initializers for
  // tables.  We cast away const sometimes, but *only* when the containing
  // upb_table is known to be non-const.  This requires a bit of care, but
  // the subtlety is confined to table.c.
  const upb_value* array;
  // Track presence in the array part. Each bit at index (key % 8) at the
  // presence_mask[key/8] indicates if the element is present in the array part.
  const uint8_t* presence_mask;
  uint32_t array_size;   // Array part size.
  uint32_t array_count;  // Array part number of elements.
} upb_inttable;

#ifdef __cplusplus
extern "C" {
#endif

// Initialize a table. If memory allocation failed, false is returned and
// the table is uninitialized.
bool upb_inttable_init(upb_inttable* table, upb_Arena* a);

// Returns the number of values in the table.
size_t upb_inttable_count(const upb_inttable* t);

// Inserts the given key into the hashtable with the given value.
// The key must not already exist in the hash table.
// The value must not be UINTPTR_MAX.
//
// If a table resize was required but memory allocation failed, false is
// returned and the table is unchanged.
bool upb_inttable_insert(upb_inttable* t, uintptr_t key, upb_value val,
                         upb_Arena* a);

// Looks up key in this table, returning "true" if the key was found.
// If v is non-NULL, copies the value for this key into *v.
bool upb_inttable_lookup(const upb_inttable* t, uintptr_t key, upb_value* v);

// Removes an item from the table. Returns true if the remove was successful,
// and stores the removed item in *val if non-NULL.
bool upb_inttable_remove(upb_inttable* t, uintptr_t key, upb_value* val);

// Updates an existing entry in an inttable.
// If the entry does not exist, returns false and does nothing.
// Unlike insert/remove, this does not invalidate iterators.
bool upb_inttable_replace(upb_inttable* t, uintptr_t key, upb_value val);

// Optimizes the table for the current set of entries, for both memory use and
// lookup time. Client should call this after all entries have been inserted;
// inserting more entries is legal, but will likely require a table resize.
// Returns false if reallocation fails.
bool upb_inttable_compact(upb_inttable* t, upb_Arena* a);

// Clears the table.
void upb_inttable_clear(upb_inttable* t);

// Iteration over inttable:
//
//   intptr_t iter = UPB_INTTABLE_BEGIN;
//   uintptr_t key;
//   upb_value val;
//   while (upb_inttable_next(t, &key, &val, &iter)) {
//      // ...
//   }

#define UPB_INTTABLE_BEGIN -1

bool upb_inttable_next(const upb_inttable* t, uintptr_t* key, upb_value* val,
                       intptr_t* iter);
void upb_inttable_removeiter(upb_inttable* t, intptr_t* iter);
void upb_inttable_setentryvalue(upb_inttable* t, intptr_t iter, upb_value v);
bool upb_inttable_done(const upb_inttable* t, intptr_t i);
uintptr_t upb_inttable_iter_key(const upb_inttable* t, intptr_t iter);
upb_value upb_inttable_iter_value(const upb_inttable* t, intptr_t iter);

UPB_INLINE bool upb_inttable_arrhas(const upb_inttable* t, uintptr_t key) {
  return (t->presence_mask[key / 8] & (1 << (key % 8))) != 0;
}

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /* UPB_HASH_INT_TABLE_H_ */

#ifndef UPB_HASH_STR_TABLE_H_
#define UPB_HASH_STR_TABLE_H_

#include <stddef.h>
#include <stdint.h>
#include <string.h>


// Must be last.

typedef struct {
  upb_table t;
} upb_strtable;

#ifdef __cplusplus
extern "C" {
#endif

// Initialize a table. If memory allocation failed, false is returned and
// the table is uninitialized.
bool upb_strtable_init(upb_strtable* table, size_t expected_size, upb_Arena* a);

// Returns the number of values in the table.
UPB_INLINE size_t upb_strtable_count(const upb_strtable* t) {
  return t->t.count;
}

void upb_strtable_clear(upb_strtable* t);

// Inserts the given key into the hashtable with the given value.
// The key must not already exist in the hash table. The key is not required
// to be NULL-terminated, and the table will make an internal copy of the key.
//
// If a table resize was required but memory allocation failed, false is
// returned and the table is unchanged. */
bool upb_strtable_insert(upb_strtable* t, const char* key, size_t len,
                         upb_value val, upb_Arena* a);

// Looks up key in this table, returning "true" if the key was found.
// If v is non-NULL, copies the value for this key into *v.
bool upb_strtable_lookup2(const upb_strtable* t, const char* key, size_t len,
                          upb_value* v);

// For NULL-terminated strings.
UPB_INLINE bool upb_strtable_lookup(const upb_strtable* t, const char* key,
                                    upb_value* v) {
  return upb_strtable_lookup2(t, key, strlen(key), v);
}

// Removes an item from the table. Returns true if the remove was successful,
// and stores the removed item in *val if non-NULL.
bool upb_strtable_remove2(upb_strtable* t, const char* key, size_t len,
                          upb_value* val);

UPB_INLINE bool upb_strtable_remove(upb_strtable* t, const char* key,
                                    upb_value* v) {
  return upb_strtable_remove2(t, key, strlen(key), v);
}

// Exposed for testing only.
bool upb_strtable_resize(upb_strtable* t, size_t size_lg2, upb_Arena* a);

/* Iteration over strtable:
 *
 *   intptr_t iter = UPB_STRTABLE_BEGIN;
 *   upb_StringView key;
 *   upb_value val;
 *   while (upb_strtable_next2(t, &key, &val, &iter)) {
 *      // ...
 *   }
 */

#define UPB_STRTABLE_BEGIN -1

bool upb_strtable_next2(const upb_strtable* t, upb_StringView* key,
                        upb_value* val, intptr_t* iter);
void upb_strtable_removeiter(upb_strtable* t, intptr_t* iter);
void upb_strtable_setentryvalue(upb_strtable* t, intptr_t iter, upb_value v);

/* DEPRECATED iterators, slated for removal.
 *
 * Iterators for string tables.  We are subject to some kind of unusual
 * design constraints:
 *
 * For high-level languages:
 *  - we must be able to guarantee that we don't crash or corrupt memory even if
 *    the program accesses an invalidated iterator.
 *
 * For C++11 range-based for:
 *  - iterators must be copyable
 *  - iterators must be comparable
 *  - it must be possible to construct an "end" value.
 *
 * Iteration order is undefined.
 *
 * Modifying the table invalidates iterators.  upb_{str,int}table_done() is
 * guaranteed to work even on an invalidated iterator, as long as the table it
 * is iterating over has not been freed.  Calling next() or accessing data from
 * an invalidated iterator yields unspecified elements from the table, but it is
 * guaranteed not to crash and to return real table elements (except when done()
 * is true). */
/* upb_strtable_iter **********************************************************/

/*   upb_strtable_iter i;
 *   upb_strtable_begin(&i, t);
 *   for(; !upb_strtable_done(&i); upb_strtable_next(&i)) {
 *     const char *key = upb_strtable_iter_key(&i);
 *     const upb_value val = upb_strtable_iter_value(&i);
 *     // ...
 *   }
 */

typedef struct {
  const upb_strtable* t;
  size_t index;
} upb_strtable_iter;

UPB_INLINE const upb_tabent* str_tabent(const upb_strtable_iter* i) {
  return &i->t->t.entries[i->index];
}

void upb_strtable_begin(upb_strtable_iter* i, const upb_strtable* t);
void upb_strtable_next(upb_strtable_iter* i);
bool upb_strtable_done(const upb_strtable_iter* i);
upb_StringView upb_strtable_iter_key(const upb_strtable_iter* i);
upb_value upb_strtable_iter_value(const upb_strtable_iter* i);
void upb_strtable_iter_setdone(upb_strtable_iter* i);
bool upb_strtable_iter_isequal(const upb_strtable_iter* i1,
                               const upb_strtable_iter* i2);

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /* UPB_HASH_STR_TABLE_H_ */

// Must be last.

typedef enum {
  kUpb_MapInsertStatus_Inserted = 0,
  kUpb_MapInsertStatus_Replaced = 1,
  kUpb_MapInsertStatus_OutOfMemory = 2,
} upb_MapInsertStatus;

// EVERYTHING BELOW THIS LINE IS INTERNAL - DO NOT USE /////////////////////////

union upb_Map_Table {
  upb_strtable strtable;
  upb_inttable inttable;
};

struct upb_Map {
  // Size of key and val, based on the map type.
  // Strings are represented as '0' because they must be handled specially.
  char key_size;
  char val_size;
  bool UPB_PRIVATE(is_frozen);
  bool UPB_PRIVATE(is_strtable);

  union upb_Map_Table t;
};

#ifdef __cplusplus
extern "C" {
#endif

UPB_INLINE void UPB_PRIVATE(_upb_Map_ShallowFreeze)(struct upb_Map* map) {
  map->UPB_PRIVATE(is_frozen) = true;
}

UPB_API_INLINE bool upb_Map_IsFrozen(const struct upb_Map* map) {
  return map->UPB_PRIVATE(is_frozen);
}

// Converting between internal table representation and user values.
//
// _upb_map_tokey() and _upb_map_fromkey() are inverses.
// _upb_map_tovalue() and _upb_map_fromvalue() are inverses.
//
// These functions account for the fact that strings are treated differently
// from other types when stored in a map.

UPB_INLINE upb_StringView _upb_map_tokey(const void* key, size_t size) {
  if (size == UPB_MAPTYPE_STRING) {
    return *(upb_StringView*)key;
  } else {
    return upb_StringView_FromDataAndSize((const char*)key, size);
  }
}

UPB_INLINE uintptr_t _upb_map_tointkey(const void* key, size_t key_size) {
  uintptr_t intkey = 0;
  memcpy(&intkey, key, key_size);
  return intkey;
}

UPB_INLINE void _upb_map_fromkey(upb_StringView key, void* out, size_t size) {
  if (size == UPB_MAPTYPE_STRING) {
    memcpy(out, &key, sizeof(key));
  } else {
    memcpy(out, key.data, size);
  }
}

UPB_INLINE bool _upb_map_tovalue(const void* val, size_t size,
                                 upb_value* msgval, upb_Arena* a) {
  if (size == UPB_MAPTYPE_STRING) {
    upb_StringView* strp = (upb_StringView*)upb_Arena_Malloc(a, sizeof(*strp));
    if (!strp) return false;
    *strp = *(upb_StringView*)val;
    *msgval = upb_value_ptr(strp);
  } else {
    memcpy(msgval, val, size);
  }
  return true;
}

UPB_INLINE void _upb_map_fromvalue(upb_value val, void* out, size_t size) {
  if (size == UPB_MAPTYPE_STRING) {
    const upb_StringView* strp = (const upb_StringView*)upb_value_getptr(val);
    memcpy(out, strp, sizeof(upb_StringView));
  } else {
    memcpy(out, &val, size);
  }
}

UPB_INLINE bool _upb_map_next(const struct upb_Map* map, size_t* iter) {
  if (map->UPB_PRIVATE(is_strtable)) {
    upb_strtable_iter it;
    it.t = &map->t.strtable;
    it.index = *iter;
    upb_strtable_next(&it);
    *iter = it.index;
    return !upb_strtable_done(&it);
  } else {
    uintptr_t key;
    upb_value val;
    intptr_t int_iter = 0;
    memcpy(&int_iter, iter, sizeof(intptr_t));
    upb_inttable_next(&map->t.inttable, &key, &val, &int_iter);
    memcpy(iter, &int_iter, sizeof(size_t));
    return !upb_inttable_done(&map->t.inttable, int_iter);
  }
}

UPB_INLINE void _upb_Map_Clear(struct upb_Map* map) {
  UPB_ASSERT(!upb_Map_IsFrozen(map));

  if (map->UPB_PRIVATE(is_strtable)) {
    upb_strtable_clear(&map->t.strtable);
  } else {
    upb_inttable_clear(&map->t.inttable);
  }
}

UPB_INLINE bool _upb_Map_Delete(struct upb_Map* map, const void* key,
                                size_t key_size, upb_value* val) {
  UPB_ASSERT(!upb_Map_IsFrozen(map));

  if (map->UPB_PRIVATE(is_strtable)) {
    upb_StringView k = _upb_map_tokey(key, key_size);
    return upb_strtable_remove2(&map->t.strtable, k.data, k.size, val);
  } else {
    uintptr_t intkey = _upb_map_tointkey(key, key_size);
    return upb_inttable_remove(&map->t.inttable, intkey, val);
  }
}

UPB_INLINE bool _upb_Map_Get(const struct upb_Map* map, const void* key,
                             size_t key_size, void* val, size_t val_size) {
  upb_value tabval = {0};
  bool ret;
  if (map->UPB_PRIVATE(is_strtable)) {
    upb_StringView k = _upb_map_tokey(key, key_size);
    ret = upb_strtable_lookup2(&map->t.strtable, k.data, k.size, &tabval);
  } else {
    uintptr_t intkey = _upb_map_tointkey(key, key_size);
    ret = upb_inttable_lookup(&map->t.inttable, intkey, &tabval);
  }
  if (ret && val) {
    _upb_map_fromvalue(tabval, val, val_size);
  }
  return ret;
}

UPB_INLINE upb_MapInsertStatus _upb_Map_Insert(struct upb_Map* map,
                                               const void* key, size_t key_size,
                                               void* val, size_t val_size,
                                               upb_Arena* a) {
  UPB_ASSERT(!upb_Map_IsFrozen(map));

  // Prep the value.
  upb_value tabval = {0};
  if (!_upb_map_tovalue(val, val_size, &tabval, a)) {
    return kUpb_MapInsertStatus_OutOfMemory;
  }

  bool removed;
  if (map->UPB_PRIVATE(is_strtable)) {
    upb_StringView strkey = _upb_map_tokey(key, key_size);
    // TODO: add overwrite operation to minimize number of lookups.
    removed =
        upb_strtable_remove2(&map->t.strtable, strkey.data, strkey.size, NULL);
    if (!upb_strtable_insert(&map->t.strtable, strkey.data, strkey.size, tabval,
                             a)) {
      return kUpb_MapInsertStatus_OutOfMemory;
    }
  } else {
    uintptr_t intkey = _upb_map_tointkey(key, key_size);
    removed = upb_inttable_remove(&map->t.inttable, intkey, NULL);
    if (!upb_inttable_insert(&map->t.inttable, intkey, tabval, a)) {
      return kUpb_MapInsertStatus_OutOfMemory;
    }
  }
  return removed ? kUpb_MapInsertStatus_Replaced
                 : kUpb_MapInsertStatus_Inserted;
}

UPB_INLINE size_t _upb_Map_Size(const struct upb_Map* map) {
  if (map->UPB_PRIVATE(is_strtable)) {
    return map->t.strtable.t.count;
  } else {
    return upb_inttable_count(&map->t.inttable);
  }
}

// Strings/bytes are special-cased in maps.
extern char _upb_Map_CTypeSizeTable[12];

UPB_INLINE size_t _upb_Map_CTypeSize(upb_CType ctype) {
  return _upb_Map_CTypeSizeTable[ctype];
}

// Creates a new map on the given arena with this key/value type.
struct upb_Map* _upb_Map_New(upb_Arena* a, size_t key_size, size_t value_size);

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /* UPB_MESSAGE_INTERNAL_MAP_H_ */

#ifndef UPB_MINI_TABLE_EXTENSION_H_
#define UPB_MINI_TABLE_EXTENSION_H_

#include <stdint.h>


#ifndef UPB_MINI_TABLE_INTERNAL_EXTENSION_H_
#define UPB_MINI_TABLE_INTERNAL_EXTENSION_H_

#include <stddef.h>
#include <stdint.h>


// Must be last.

struct upb_MiniTableExtension {
  // Do not move this field. We need to be able to alias pointers.
  struct upb_MiniTableField UPB_PRIVATE(field);

  const struct upb_MiniTable* UPB_PRIVATE(extendee);
  union upb_MiniTableSub UPB_PRIVATE(sub);  // NULL unless submsg or proto2 enum
};

#ifdef __cplusplus
extern "C" {
#endif

UPB_API_INLINE upb_CType
upb_MiniTableExtension_CType(const struct upb_MiniTableExtension* e) {
  return upb_MiniTableField_CType(&e->UPB_PRIVATE(field));
}

UPB_API_INLINE uint32_t
upb_MiniTableExtension_Number(const struct upb_MiniTableExtension* e) {
  return e->UPB_PRIVATE(field).UPB_ONLYBITS(number);
}

UPB_API_INLINE const struct upb_MiniTable* upb_MiniTableExtension_Extendee(
    const struct upb_MiniTableExtension* e) {
  return e->UPB_PRIVATE(extendee);
}

UPB_API_INLINE const struct upb_MiniTable* upb_MiniTableExtension_GetSubMessage(
    const struct upb_MiniTableExtension* e) {
  if (upb_MiniTableExtension_CType(e) != kUpb_CType_Message) {
    return NULL;
  }
  return upb_MiniTableSub_Message(e->UPB_PRIVATE(sub));
}

UPB_API_INLINE const struct upb_MiniTableEnum*
upb_MiniTableExtension_GetSubEnum(const struct upb_MiniTableExtension* e) {
  if (upb_MiniTableExtension_CType(e) != kUpb_CType_Enum) {
    return NULL;
  }
  return upb_MiniTableSub_Enum(e->UPB_PRIVATE(sub));
}

UPB_API_INLINE bool upb_MiniTableExtension_SetSubMessage(
    struct upb_MiniTableExtension* e, const struct upb_MiniTable* m) {
  if (e->UPB_PRIVATE(field).UPB_PRIVATE(descriptortype) !=
      kUpb_FieldType_Message) {
    return false;
  }
  e->UPB_PRIVATE(sub).UPB_PRIVATE(submsg) = m;
  return true;
}

UPB_API_INLINE bool upb_MiniTableExtension_SetSubEnum(
    struct upb_MiniTableExtension* e, const struct upb_MiniTableEnum* en) {
  if (e->UPB_PRIVATE(field).UPB_PRIVATE(descriptortype) !=
      kUpb_FieldType_Enum) {
    return false;
  }
  e->UPB_PRIVATE(sub).UPB_PRIVATE(subenum) = en;
  return true;
}

UPB_API_INLINE const upb_MiniTableField* upb_MiniTableExtension_ToField(
    const struct upb_MiniTableExtension* e) {
  return &e->UPB_PRIVATE(field);
}

UPB_INLINE upb_FieldRep UPB_PRIVATE(_upb_MiniTableExtension_GetRep)(
    const struct upb_MiniTableExtension* e) {
  return UPB_PRIVATE(_upb_MiniTableField_GetRep)(&e->UPB_PRIVATE(field));
}

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /* UPB_MINI_TABLE_INTERNAL_EXTENSION_H_ */

// Must be last.

typedef struct upb_MiniTableExtension upb_MiniTableExtension;

#ifdef __cplusplus
extern "C" {
#endif

UPB_API_INLINE upb_CType
upb_MiniTableExtension_CType(const upb_MiniTableExtension* e);

UPB_API_INLINE uint32_t
upb_MiniTableExtension_Number(const upb_MiniTableExtension* e);

UPB_API_INLINE const upb_MiniTable* upb_MiniTableExtension_Extendee(
    const upb_MiniTableExtension* e);

UPB_API_INLINE const upb_MiniTable* upb_MiniTableExtension_GetSubMessage(
    const upb_MiniTableExtension* e);

UPB_API_INLINE const upb_MiniTableEnum* upb_MiniTableExtension_GetSubEnum(
    const upb_MiniTableExtension* e);

UPB_API_INLINE bool upb_MiniTableExtension_SetSubMessage(
    upb_MiniTableExtension* e, const upb_MiniTable* m);

UPB_API_INLINE bool upb_MiniTableExtension_SetSubEnum(
    upb_MiniTableExtension* e, const upb_MiniTableEnum* m);

UPB_API_INLINE const upb_MiniTableField* upb_MiniTableExtension_ToField(
    const upb_MiniTableExtension* e);

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /* UPB_MINI_TABLE_EXTENSION_H_ */

// Must be last.

// The internal representation of an extension is self-describing: it contains
// enough information that we can serialize it to binary format without needing
// to look it up in a upb_ExtensionRegistry.
//
// This representation allocates 16 bytes to data on 64-bit platforms.
// This is rather wasteful for scalars (in the extreme case of bool,
// it wastes 15 bytes). We accept this because we expect messages to be
// the most common extension type.
typedef struct {
  const upb_MiniTableExtension* ext;
  upb_MessageValue data;
} upb_Extension;

#ifdef __cplusplus
extern "C" {
#endif

// Adds the given extension data to the given message.
// |ext| is copied into the message instance.
// This logically replaces any previously-added extension with this number.
upb_Extension* UPB_PRIVATE(_upb_Message_GetOrCreateExtension)(
    struct upb_Message* msg, const upb_MiniTableExtension* ext,
    upb_Arena* arena);

// Returns an extension for a message with a given mini table,
// or NULL if no extension exists with this mini table.
const upb_Extension* UPB_PRIVATE(_upb_Message_Getext)(
    const struct upb_Message* msg, const upb_MiniTableExtension* ext);

UPB_INLINE bool UPB_PRIVATE(_upb_Extension_IsEmpty)(const upb_Extension* ext) {
  switch (
      UPB_PRIVATE(_upb_MiniTableField_Mode)(&ext->ext->UPB_PRIVATE(field))) {
    case kUpb_FieldMode_Scalar:
      return false;
    case kUpb_FieldMode_Array:
      return upb_Array_Size(ext->data.array_val) == 0;
    case kUpb_FieldMode_Map:
      return _upb_Map_Size(ext->data.map_val) == 0;
  }
  UPB_UNREACHABLE();
}

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /* UPB_MESSAGE_INTERNAL_EXTENSION_H_ */

/*
** Our memory representation for parsing tables and messages themselves.
** Functions in this file are used by generated code and possibly reflection.
**
** The definitions in this file are internal to upb.
**/

#ifndef UPB_MESSAGE_INTERNAL_MESSAGE_H_
#define UPB_MESSAGE_INTERNAL_MESSAGE_H_

#include <stdint.h>
#include <stdlib.h>
#include <string.h>


// Must be last.

#ifdef __cplusplus
extern "C" {
#endif

extern const float kUpb_FltInfinity;
extern const double kUpb_Infinity;
extern const double kUpb_NaN;

// Internal members of a upb_Message that track unknown fields and/or
// extensions. We can change this without breaking binary compatibility.

typedef struct upb_TaggedAuxPtr {
  // Two lowest bits form a tag:
  // 00 - non-aliased unknown data
  // 10 - aliased unknown data
  // 01 - extension
  uintptr_t ptr;
} upb_TaggedAuxPtr;

UPB_INLINE bool upb_TaggedAuxPtr_IsNull(upb_TaggedAuxPtr ptr) {
  return ptr.ptr == 0;
}

UPB_INLINE bool upb_TaggedAuxPtr_IsExtension(upb_TaggedAuxPtr ptr) {
  return ptr.ptr & 1;
}

UPB_INLINE bool upb_TaggedAuxPtr_IsUnknown(upb_TaggedAuxPtr ptr) {
  return (ptr.ptr != 0) && ((ptr.ptr & 1) == 0);
}

UPB_INLINE bool upb_TaggedAuxPtr_IsUnknownAliased(upb_TaggedAuxPtr ptr) {
  return (ptr.ptr != 0) && ((ptr.ptr & 2) == 2);
}

UPB_INLINE upb_Extension* upb_TaggedAuxPtr_Extension(upb_TaggedAuxPtr ptr) {
  UPB_ASSERT(upb_TaggedAuxPtr_IsExtension(ptr));
  return (upb_Extension*)(ptr.ptr & ~3ULL);
}

UPB_INLINE upb_StringView* upb_TaggedAuxPtr_UnknownData(upb_TaggedAuxPtr ptr) {
  UPB_ASSERT(!upb_TaggedAuxPtr_IsExtension(ptr));
  return (upb_StringView*)(ptr.ptr & ~3ULL);
}

UPB_INLINE upb_TaggedAuxPtr upb_TaggedAuxPtr_Null(void) {
  upb_TaggedAuxPtr ptr;
  ptr.ptr = 0;
  return ptr;
}

UPB_INLINE upb_TaggedAuxPtr
upb_TaggedAuxPtr_MakeExtension(const upb_Extension* e) {
  upb_TaggedAuxPtr ptr;
  ptr.ptr = (uintptr_t)e | 1;
  return ptr;
}

// This tag means that the original allocation for this field starts with the
// string view and ends with the end of the content referenced by the string
// view.
UPB_INLINE upb_TaggedAuxPtr
upb_TaggedAuxPtr_MakeUnknownData(const upb_StringView* sv) {
  upb_TaggedAuxPtr ptr;
  ptr.ptr = (uintptr_t)sv;
  return ptr;
}

// This tag implies no guarantee between the relationship of the string view and
// the data it points to.
UPB_INLINE upb_TaggedAuxPtr
upb_TaggedAuxPtr_MakeUnknownDataAliased(const upb_StringView* sv) {
  upb_TaggedAuxPtr ptr;
  ptr.ptr = (uintptr_t)sv | 2;
  return ptr;
}

typedef struct upb_Message_Internal {
  // Total number of entries set in aux_data
  uint32_t size;
  uint32_t capacity;
  // Tagged pointers to upb_StringView or upb_Extension
  upb_TaggedAuxPtr aux_data[];
} upb_Message_Internal;

#ifdef UPB_TRACING_ENABLED
UPB_API void upb_Message_LogNewMessage(const upb_MiniTable* m,
                                       const upb_Arena* arena);
UPB_API void upb_Message_SetNewMessageTraceHandler(
    void (*handler)(const upb_MiniTable*, const upb_Arena*));
#endif  // UPB_TRACING_ENABLED

// Inline version upb_Message_New(), for internal use.
UPB_INLINE struct upb_Message* _upb_Message_New(const upb_MiniTable* m,
                                                upb_Arena* a) {
  UPB_PRIVATE(upb_MiniTable_CheckInvariants)(m);
#ifdef UPB_TRACING_ENABLED
  upb_Message_LogNewMessage(m, a);
#endif  // UPB_TRACING_ENABLED

  const size_t size = m->UPB_PRIVATE(size);
  // Message sizes are aligned up when constructing minitables; telling the
  // compiler this avoids redoing alignment on the malloc fast path
  UPB_ASSUME(size % kUpb_Message_Align == 0);
  struct upb_Message* msg = (struct upb_Message*)upb_Arena_Malloc(a, size);
  if (UPB_UNLIKELY(!msg)) return NULL;
  memset(msg, 0, size);
  return msg;
}

// Discards the unknown fields for this message only.
void _upb_Message_DiscardUnknown_shallow(struct upb_Message* msg);

UPB_NOINLINE bool UPB_PRIVATE(_upb_Message_AddUnknownSlowPath)(
    struct upb_Message* msg, const char* data, size_t len, upb_Arena* arena,
    bool alias);

// Adds unknown data (serialized protobuf data) to the given message. The data
// must represent one or more complete and well formed proto fields.
//
// If `alias_base` is NULL, the bytes from `data` will be copied into the
// destination arena. Otherwise it must be a pointer to the beginning of the
// buffer that `data` points into, which signals that the message must alias
// the bytes instead of copying them. The value of `alias_base` is also used
// to mark the boundary of the buffer, so that we do not inappropriately
// coalesce two buffers that are separate objects but happen to be contiguous
// in memory.
UPB_INLINE bool UPB_PRIVATE(_upb_Message_AddUnknown)(struct upb_Message* msg,
                                                     const char* data,
                                                     size_t len,
                                                     upb_Arena* arena,
                                                     const char* alias_base) {
  UPB_ASSERT(!upb_Message_IsFrozen(msg));
  if (alias_base) {
    // Aliasing parse of a message with sequential unknown fields is a simple
    // pointer bump, so inline it.
    upb_Message_Internal* in = UPB_PRIVATE(_upb_Message_GetInternal)(msg);
    if (in && in->size) {
      upb_TaggedAuxPtr ptr = in->aux_data[in->size - 1];
      if (upb_TaggedAuxPtr_IsUnknown(ptr)) {
        upb_StringView* existing = upb_TaggedAuxPtr_UnknownData(ptr);
        // Fast path if the field we're adding is immediately after the last
        // added unknown field. However, we could be merging into an existing
        // message with an allocation that just happens to be positioned
        // immediately after the previous merged unknown field; this is
        // considered out-of-bounds and thus UB. Ensure it's in-bounds by
        // comparing with the original input pointer for our buffer.
        if (data != alias_base && existing->data + existing->size == data) {
          existing->size += len;
          return true;
        }
      }
    }
  }
  return UPB_PRIVATE(_upb_Message_AddUnknownSlowPath)(msg, data, len, arena,
                                                      alias_base != NULL);
}

// Adds unknown data (serialized protobuf data) to the given message.
// The data is copied into the message instance. Data when concatenated together
// must represent one or more complete and well formed proto fields, but the
// individual spans may point only to partial fields.
bool UPB_PRIVATE(_upb_Message_AddUnknownV)(struct upb_Message* msg,
                                           upb_Arena* arena,
                                           upb_StringView data[], size_t count);

// Ensures at least one slot is available in the aux_data of this message.
// Returns false if a reallocation is needed to satisfy the request, and fails.
bool UPB_PRIVATE(_upb_Message_ReserveSlot)(struct upb_Message* msg,
                                           upb_Arena* arena);

#define kUpb_Message_UnknownBegin 0
#define kUpb_Message_ExtensionBegin 0

UPB_INLINE bool upb_Message_NextUnknown(const struct upb_Message* msg,
                                        upb_StringView* data, uintptr_t* iter) {
  const upb_Message_Internal* in = UPB_PRIVATE(_upb_Message_GetInternal)(msg);
  size_t i = *iter;
  if (in) {
    while (i < in->size) {
      upb_TaggedAuxPtr tagged_ptr = in->aux_data[i++];
      if (upb_TaggedAuxPtr_IsUnknown(tagged_ptr)) {
        *data = *upb_TaggedAuxPtr_UnknownData(tagged_ptr);
        *iter = i;
        return true;
      }
    }
  }
  data->size = 0;
  data->data = NULL;
  *iter = i;
  return false;
}

UPB_INLINE bool upb_Message_HasUnknown(const struct upb_Message* msg) {
  upb_StringView data;
  uintptr_t iter = kUpb_Message_UnknownBegin;
  return upb_Message_NextUnknown(msg, &data, &iter);
}

UPB_INLINE bool upb_Message_NextExtension(const struct upb_Message* msg,
                                          const upb_MiniTableExtension** out_e,
                                          upb_MessageValue* out_v,
                                          uintptr_t* iter) {
  const upb_Message_Internal* in = UPB_PRIVATE(_upb_Message_GetInternal)(msg);
  uintptr_t i = *iter;
  if (in) {
    while (i < in->size) {
      upb_TaggedAuxPtr tagged_ptr = in->aux_data[i++];
      if (upb_TaggedAuxPtr_IsExtension(tagged_ptr)) {
        const upb_Extension* ext = upb_TaggedAuxPtr_Extension(tagged_ptr);

        // Empty repeated fields or maps semantically don't exist.
        if (UPB_PRIVATE(_upb_Extension_IsEmpty)(ext)) continue;

        *out_e = ext->ext;
        *out_v = ext->data;
        *iter = i;
        return true;
      }
    }
  }
  *iter = i;

  return false;
}

UPB_INLINE bool UPB_PRIVATE(_upb_Message_NextExtensionReverse)(
    const struct upb_Message* msg, const upb_MiniTableExtension** out_e,
    upb_MessageValue* out_v, uintptr_t* iter) {
  upb_Message_Internal* in = UPB_PRIVATE(_upb_Message_GetInternal)(msg);
  if (!in) return false;
  uintptr_t i = *iter;
  uint32_t size = in->size;
  while (i < size) {
    upb_TaggedAuxPtr tagged_ptr = in->aux_data[size - 1 - i];
    i++;
    if (!upb_TaggedAuxPtr_IsExtension(tagged_ptr)) {
      continue;
    }
    const upb_Extension* ext = upb_TaggedAuxPtr_Extension(tagged_ptr);

    // Empty repeated fields or maps semantically don't exist.
    if (UPB_PRIVATE(_upb_Extension_IsEmpty)(ext)) continue;

    *out_e = ext->ext;
    *out_v = ext->data;
    *iter = i;
    return true;
  }
  *iter = i;
  return false;
}

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /* UPB_MESSAGE_INTERNAL_MESSAGE_H_ */

#ifndef UPB_MINI_TABLE_INTERNAL_TAGGED_PTR_H_
#define UPB_MINI_TABLE_INTERNAL_TAGGED_PTR_H_

#include <stdint.h>


// Must be last.

#ifdef __cplusplus
extern "C" {
#endif

// Internal-only because empty messages cannot be created by the user.
UPB_INLINE uintptr_t
UPB_PRIVATE(_upb_TaggedMessagePtr_Pack)(struct upb_Message* ptr, bool empty) {
  UPB_ASSERT(((uintptr_t)ptr & 1) == 0);
  return (uintptr_t)ptr | (empty ? 1 : 0);
}

UPB_API_INLINE bool upb_TaggedMessagePtr_IsEmpty(uintptr_t ptr) {
  return ptr & 1;
}

UPB_INLINE struct upb_Message* UPB_PRIVATE(_upb_TaggedMessagePtr_GetMessage)(
    uintptr_t ptr) {
  return (struct upb_Message*)(ptr & ~(uintptr_t)1);
}

UPB_API_INLINE struct upb_Message* upb_TaggedMessagePtr_GetNonEmptyMessage(
    uintptr_t ptr) {
  UPB_ASSERT(!upb_TaggedMessagePtr_IsEmpty(ptr));
  return UPB_PRIVATE(_upb_TaggedMessagePtr_GetMessage)(ptr);
}

UPB_INLINE struct upb_Message* UPB_PRIVATE(
    _upb_TaggedMessagePtr_GetEmptyMessage)(uintptr_t ptr) {
  UPB_ASSERT(upb_TaggedMessagePtr_IsEmpty(ptr));
  return UPB_PRIVATE(_upb_TaggedMessagePtr_GetMessage)(ptr);
}

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /* UPB_MINI_TABLE_INTERNAL_TAGGED_PTR_H_ */

// Must be last.

#if defined(__GNUC__) && !defined(__clang__)
// GCC raises incorrect warnings in these functions.  It thinks that we are
// overrunning buffers, but we carefully write the functions in this file to
// guarantee that this is impossible.  GCC gets this wrong due it its failure
// to perform constant propagation as we expect:
//   - https://gcc.gnu.org/bugzilla/show_bug.cgi?id=108217
//   - https://gcc.gnu.org/bugzilla/show_bug.cgi?id=108226
//
// Unfortunately this also indicates that GCC is not optimizing away the
// switch() in cases where it should be, compromising the performance.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Warray-bounds"
#pragma GCC diagnostic ignored "-Wstringop-overflow"
#if __GNUC__ >= 11
#pragma GCC diagnostic ignored "-Wstringop-overread"
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

// LINT.IfChange(presence_logic)

// Hasbit access ///////////////////////////////////////////////////////////////

UPB_INLINE bool UPB_PRIVATE(_upb_Message_GetHasbit)(
    const struct upb_Message* msg, const upb_MiniTableField* f) {
  const uint16_t offset = UPB_PRIVATE(_upb_MiniTableField_HasbitOffset)(f);
  const char mask = UPB_PRIVATE(_upb_MiniTableField_HasbitMask)(f);

  return (*UPB_PTR_AT(msg, offset, const char) & mask) != 0;
}

UPB_INLINE void UPB_PRIVATE(_upb_Message_SetHasbit)(
    const struct upb_Message* msg, const upb_MiniTableField* f) {
  const uint16_t offset = UPB_PRIVATE(_upb_MiniTableField_HasbitOffset)(f);
  const char mask = UPB_PRIVATE(_upb_MiniTableField_HasbitMask)(f);

  (*UPB_PTR_AT(msg, offset, char)) |= mask;
}

UPB_INLINE void UPB_PRIVATE(_upb_Message_ClearHasbit)(
    const struct upb_Message* msg, const upb_MiniTableField* f) {
  const uint16_t offset = UPB_PRIVATE(_upb_MiniTableField_HasbitOffset)(f);
  const char mask = UPB_PRIVATE(_upb_MiniTableField_HasbitMask)(f);

  (*UPB_PTR_AT(msg, offset, char)) &= ~mask;
}

// Oneof case access ///////////////////////////////////////////////////////////

UPB_INLINE uint32_t* UPB_PRIVATE(_upb_Message_OneofCasePtr)(
    struct upb_Message* msg, const upb_MiniTableField* f) {
  return UPB_PTR_AT(msg, UPB_PRIVATE(_upb_MiniTableField_OneofOffset)(f),
                    uint32_t);
}

UPB_INLINE uint32_t UPB_PRIVATE(_upb_Message_GetOneofCase)(
    const struct upb_Message* msg, const upb_MiniTableField* f) {
  const uint32_t* ptr =
      UPB_PRIVATE(_upb_Message_OneofCasePtr)((struct upb_Message*)msg, f);

  return *ptr;
}

UPB_INLINE void UPB_PRIVATE(_upb_Message_SetOneofCase)(
    struct upb_Message* msg, const upb_MiniTableField* f) {
  uint32_t* ptr = UPB_PRIVATE(_upb_Message_OneofCasePtr)(msg, f);

  *ptr = upb_MiniTableField_Number(f);
}

// Returns true if the given field is the current oneof case.
// Does nothing if it is not the current oneof case.
UPB_INLINE bool UPB_PRIVATE(_upb_Message_ClearOneofCase)(
    struct upb_Message* msg, const upb_MiniTableField* f) {
  uint32_t* ptr = UPB_PRIVATE(_upb_Message_OneofCasePtr)(msg, f);

  if (*ptr != upb_MiniTableField_Number(f)) return false;
  *ptr = 0;
  return true;
}

UPB_API_INLINE uint32_t upb_Message_WhichOneofFieldNumber(
    const struct upb_Message* message, const upb_MiniTableField* oneof_field) {
  UPB_ASSUME(upb_MiniTableField_IsInOneof(oneof_field));
  return UPB_PRIVATE(_upb_Message_GetOneofCase)(message, oneof_field);
}

UPB_API_INLINE const upb_MiniTableField* upb_Message_WhichOneof(
    const struct upb_Message* msg, const upb_MiniTable* m,
    const upb_MiniTableField* f) {
  uint32_t field_number = upb_Message_WhichOneofFieldNumber(msg, f);
  if (field_number == 0) {
    // No field in the oneof is set.
    return NULL;
  }
  return upb_MiniTable_FindFieldByNumber(m, field_number);
}

// LINT.ThenChange(GoogleInternalName2)

// Returns false if the message is missing any of its required fields.
UPB_INLINE bool UPB_PRIVATE(_upb_Message_IsInitializedShallow)(
    const struct upb_Message* msg, const upb_MiniTable* m) {
  uint64_t bits;
  memcpy(&bits, msg + 1, sizeof(bits));
  bits = upb_BigEndian64(bits);
  return (UPB_PRIVATE(_upb_MiniTable_RequiredMask)(m) & ~bits) == 0;
}

UPB_INLINE void* UPB_PRIVATE(_upb_Message_MutableDataPtr)(
    struct upb_Message* msg, const upb_MiniTableField* f) {
  return (char*)msg + f->UPB_ONLYBITS(offset);
}

UPB_INLINE const void* UPB_PRIVATE(_upb_Message_DataPtr)(
    const struct upb_Message* msg, const upb_MiniTableField* f) {
  return (const char*)msg + f->UPB_ONLYBITS(offset);
}

UPB_INLINE void UPB_PRIVATE(_upb_Message_SetPresence)(
    struct upb_Message* msg, const upb_MiniTableField* f) {
  if (UPB_PRIVATE(_upb_MiniTableField_HasHasbit)(f)) {
    UPB_PRIVATE(_upb_Message_SetHasbit)(msg, f);
  } else if (upb_MiniTableField_IsInOneof(f)) {
    UPB_PRIVATE(_upb_Message_SetOneofCase)(msg, f);
  }
}

UPB_INLINE_IF_NOT_GCC void UPB_PRIVATE(_upb_MiniTableField_DataCopy)(
    const upb_MiniTableField* f, void* to, const void* from) {
  switch (UPB_PRIVATE(_upb_MiniTableField_GetRep)(f)) {
    case kUpb_FieldRep_1Byte:
      memcpy(to, from, 1);
      return;
    case kUpb_FieldRep_4Byte:
      memcpy(to, from, 4);
      return;
    case kUpb_FieldRep_8Byte:
      memcpy(to, from, 8);
      return;
    case kUpb_FieldRep_StringView: {
      memcpy(to, from, sizeof(upb_StringView));
      return;
    }
  }
  UPB_UNREACHABLE();
}

UPB_INLINE_IF_NOT_GCC bool UPB_PRIVATE(_upb_MiniTableField_DataEquals)(
    const upb_MiniTableField* f, const void* a, const void* b) {
  switch (UPB_PRIVATE(_upb_MiniTableField_GetRep)(f)) {
    case kUpb_FieldRep_1Byte:
      return memcmp(a, b, 1) == 0;
    case kUpb_FieldRep_4Byte:
      return memcmp(a, b, 4) == 0;
    case kUpb_FieldRep_8Byte:
      return memcmp(a, b, 8) == 0;
    case kUpb_FieldRep_StringView: {
      const upb_StringView sa = *(const upb_StringView*)a;
      const upb_StringView sb = *(const upb_StringView*)b;
      return upb_StringView_IsEqual(sa, sb);
    }
  }
  UPB_UNREACHABLE();
}

UPB_INLINE void UPB_PRIVATE(_upb_MiniTableField_DataClear)(
    const upb_MiniTableField* f, void* val) {
  const char zero[16] = {0};
  UPB_PRIVATE(_upb_MiniTableField_DataCopy)(f, val, zero);
}

UPB_INLINE bool UPB_PRIVATE(_upb_MiniTableField_DataIsZero)(
    const upb_MiniTableField* f, const void* val) {
  const char zero[16] = {0};
  return UPB_PRIVATE(_upb_MiniTableField_DataEquals)(f, val, zero);
}

// Here we define universal getter/setter functions for message fields.
// These look very branchy and inefficient, but as long as the MiniTableField
// values are known at compile time, all the branches are optimized away and
// we are left with ideal code.  This can happen either through through
// literals or UPB_ASSUME():
//
//   // Via struct literals.
//   bool FooMessage_set_bool_field(const upb_Message* msg, bool val) {
//     const upb_MiniTableField field = {1, 0, 0, /* etc... */};
//     // All value in "field" are compile-time known.
//     upb_Message_SetBaseField(msg, &field, &value);
//   }
//
//   // Via UPB_ASSUME().
//   UPB_INLINE bool upb_Message_SetBool(upb_Message* msg,
//                                       const upb_MiniTableField* field,
//                                       bool value, upb_Arena* a) {
//     UPB_ASSUME(field->UPB_PRIVATE(descriptortype) == kUpb_FieldType_Bool);
//     UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableField_GetRep)(field) ==
//                kUpb_FieldRep_1Byte);
//     upb_Message_SetField(msg, field, &value, a);
//   }
//
// As a result, we can use these universal getters/setters for *all* message
// accessors: generated code, MiniTable accessors, and reflection.  The only
// exception is the binary encoder/decoder, which need to be a bit more clever
// about how they read/write the message data, for efficiency.
//
// These functions work on both extensions and non-extensions. If the field
// of a setter is known to be a non-extension, the arena may be NULL and the
// returned bool value may be ignored since it will always succeed.

UPB_API_INLINE bool upb_Message_HasBaseField(const struct upb_Message* msg,
                                             const upb_MiniTableField* field) {
  UPB_ASSERT(upb_MiniTableField_HasPresence(field));
  UPB_ASSUME(!upb_MiniTableField_IsExtension(field));
  if (upb_MiniTableField_IsInOneof(field)) {
    return UPB_PRIVATE(_upb_Message_GetOneofCase)(msg, field) ==
           upb_MiniTableField_Number(field);
  } else {
    return UPB_PRIVATE(_upb_Message_GetHasbit)(msg, field);
  }
}

UPB_API_INLINE bool upb_Message_HasExtension(const struct upb_Message* msg,
                                             const upb_MiniTableExtension* e) {
  UPB_ASSERT(upb_MiniTableField_HasPresence(&e->UPB_PRIVATE(field)));
  return UPB_PRIVATE(_upb_Message_Getext)(msg, e) != NULL;
}

UPB_FORCEINLINE void _upb_Message_GetNonExtensionField(
    const struct upb_Message* msg, const upb_MiniTableField* field,
    const void* default_val, void* val) {
  UPB_ASSUME(!upb_MiniTableField_IsExtension(field));
  if ((upb_MiniTableField_IsInOneof(field) ||
       !UPB_PRIVATE(_upb_MiniTableField_DataIsZero)(field, default_val)) &&
      !upb_Message_HasBaseField(msg, field)) {
    UPB_PRIVATE(_upb_MiniTableField_DataCopy)(field, val, default_val);
    return;
  }
  UPB_PRIVATE(_upb_MiniTableField_DataCopy)
  (field, val, UPB_PRIVATE(_upb_Message_DataPtr)(msg, field));
}

UPB_INLINE void _upb_Message_GetExtensionField(
    const struct upb_Message* msg, const upb_MiniTableExtension* mt_ext,
    const void* default_val, void* val) {
  const upb_Extension* ext = UPB_PRIVATE(_upb_Message_Getext)(msg, mt_ext);
  const upb_MiniTableField* f = &mt_ext->UPB_PRIVATE(field);
  UPB_ASSUME(upb_MiniTableField_IsExtension(f));

  if (ext) {
    UPB_PRIVATE(_upb_MiniTableField_DataCopy)(f, val, &ext->data);
  } else {
    UPB_PRIVATE(_upb_MiniTableField_DataCopy)(f, val, default_val);
  }
}

// NOTE: The default_val is only used for fields that support presence.
// For repeated/map fields, the resulting upb_Array*/upb_Map* can be NULL if a
// upb_Array/upb_Map has not been allocated yet. Array/map fields do not have
// presence, so this is semantically identical to a pointer to an empty
// array/map, and must be treated the same for all semantic purposes.
UPB_API_INLINE upb_MessageValue upb_Message_GetField(
    const struct upb_Message* msg, const upb_MiniTableField* field,
    upb_MessageValue default_val) {
  upb_MessageValue ret;
  if (upb_MiniTableField_IsExtension(field)) {
    _upb_Message_GetExtensionField(msg, (upb_MiniTableExtension*)field,
                                   &default_val, &ret);
  } else {
    _upb_Message_GetNonExtensionField(msg, field, &default_val, &ret);
  }
  return ret;
}

UPB_API_INLINE void upb_Message_SetBaseField(struct upb_Message* msg,
                                             const upb_MiniTableField* f,
                                             const void* val) {
  UPB_ASSERT(!upb_Message_IsFrozen(msg));
  UPB_ASSUME(!upb_MiniTableField_IsExtension(f));
  UPB_PRIVATE(_upb_Message_SetPresence)(msg, f);
  UPB_PRIVATE(_upb_MiniTableField_DataCopy)
  (f, UPB_PRIVATE(_upb_Message_MutableDataPtr)(msg, f), val);
}

UPB_API_INLINE bool upb_Message_SetExtension(struct upb_Message* msg,
                                             const upb_MiniTableExtension* e,
                                             const void* val, upb_Arena* a) {
  UPB_ASSERT(!upb_Message_IsFrozen(msg));
  UPB_ASSERT(a);
  upb_Extension* ext =
      UPB_PRIVATE(_upb_Message_GetOrCreateExtension)(msg, e, a);
  if (!ext) return false;
  UPB_PRIVATE(_upb_MiniTableField_DataCopy)
  (&e->UPB_PRIVATE(field), &ext->data, val);
  return true;
}

// Sets the value of the given field in the given msg. The return value is true
// if the operation completed successfully, or false if memory allocation
// failed.
UPB_INLINE bool UPB_PRIVATE(_upb_Message_SetField)(struct upb_Message* msg,
                                                   const upb_MiniTableField* f,
                                                   upb_MessageValue val,
                                                   upb_Arena* a) {
  if (upb_MiniTableField_IsExtension(f)) {
    const upb_MiniTableExtension* ext = (const upb_MiniTableExtension*)f;
    return upb_Message_SetExtension(msg, ext, &val, a);
  } else {
    upb_Message_SetBaseField(msg, f, &val);
    return true;
  }
}

UPB_API_INLINE const upb_Array* upb_Message_GetArray(
    const struct upb_Message* msg, const upb_MiniTableField* f) {
  UPB_PRIVATE(_upb_MiniTableField_CheckIsArray)(f);
  upb_Array* ret;
  const upb_Array* default_val = NULL;
  _upb_Message_GetNonExtensionField(msg, f, &default_val, &ret);
  return ret;
}

UPB_API_INLINE bool upb_Message_GetBool(const struct upb_Message* msg,
                                        const upb_MiniTableField* f,
                                        bool default_val) {
  UPB_ASSUME(upb_MiniTableField_CType(f) == kUpb_CType_Bool);
  UPB_ASSUME(upb_MiniTableField_IsScalar(f));
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableField_GetRep)(f) == kUpb_FieldRep_1Byte);
  upb_MessageValue def;
  def.bool_val = default_val;
  return upb_Message_GetField(msg, f, def).bool_val;
}

UPB_API_INLINE double upb_Message_GetDouble(const struct upb_Message* msg,
                                            const upb_MiniTableField* f,
                                            double default_val) {
  UPB_ASSUME(upb_MiniTableField_CType(f) == kUpb_CType_Double);
  UPB_ASSUME(upb_MiniTableField_IsScalar(f));
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableField_GetRep)(f) == kUpb_FieldRep_8Byte);

  upb_MessageValue def;
  def.double_val = default_val;
  return upb_Message_GetField(msg, f, def).double_val;
}

UPB_API_INLINE float upb_Message_GetFloat(const struct upb_Message* msg,
                                          const upb_MiniTableField* f,
                                          float default_val) {
  UPB_ASSUME(upb_MiniTableField_CType(f) == kUpb_CType_Float);
  UPB_ASSUME(upb_MiniTableField_IsScalar(f));
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableField_GetRep)(f) == kUpb_FieldRep_4Byte);

  upb_MessageValue def;
  def.float_val = default_val;
  return upb_Message_GetField(msg, f, def).float_val;
}

UPB_API_INLINE int32_t upb_Message_GetInt32(const struct upb_Message* msg,
                                            const upb_MiniTableField* f,
                                            int32_t default_val) {
  UPB_ASSUME(upb_MiniTableField_CType(f) == kUpb_CType_Int32 ||
             upb_MiniTableField_CType(f) == kUpb_CType_Enum);
  UPB_ASSUME(upb_MiniTableField_IsScalar(f));
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableField_GetRep)(f) == kUpb_FieldRep_4Byte);

  upb_MessageValue def;
  def.int32_val = default_val;
  return upb_Message_GetField(msg, f, def).int32_val;
}

UPB_API_INLINE int64_t upb_Message_GetInt64(const struct upb_Message* msg,
                                            const upb_MiniTableField* f,
                                            int64_t default_val) {
  UPB_ASSUME(upb_MiniTableField_CType(f) == kUpb_CType_Int64);
  UPB_ASSUME(upb_MiniTableField_IsScalar(f));
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableField_GetRep)(f) == kUpb_FieldRep_8Byte);

  upb_MessageValue def;
  def.int64_val = default_val;
  return upb_Message_GetField(msg, f, def).int64_val;
}

UPB_INLINE void UPB_PRIVATE(_upb_Message_AssertMapIsUntagged)(
    const struct upb_Message* msg, const upb_MiniTableField* field) {
  UPB_UNUSED(msg);
  UPB_PRIVATE(_upb_MiniTableField_CheckIsMap)(field);
#ifndef NDEBUG
  uintptr_t default_val = 0;
  uintptr_t tagged;
  _upb_Message_GetNonExtensionField(msg, field, &default_val, &tagged);
  UPB_ASSERT(!upb_TaggedMessagePtr_IsEmpty(tagged));
#endif
}

UPB_API_INLINE const struct upb_Map* upb_Message_GetMap(
    const struct upb_Message* msg, const upb_MiniTableField* f) {
  UPB_PRIVATE(_upb_MiniTableField_CheckIsMap)(f);
  UPB_PRIVATE(_upb_Message_AssertMapIsUntagged)(msg, f);
  struct upb_Map* ret;
  const struct upb_Map* default_val = NULL;
  _upb_Message_GetNonExtensionField(msg, f, &default_val, &ret);
  return ret;
}

UPB_API_INLINE uintptr_t upb_Message_GetTaggedMessagePtr(
    const struct upb_Message* msg, const upb_MiniTableField* f,
    struct upb_Message* default_val) {
  UPB_ASSUME(upb_MiniTableField_CType(f) == kUpb_CType_Message);
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableField_GetRep)(f) ==
             UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte));
  UPB_ASSUME(upb_MiniTableField_IsScalar(f));
  uintptr_t tagged;
  _upb_Message_GetNonExtensionField(msg, f, &default_val, &tagged);
  return tagged;
}

// For internal use only; users cannot set tagged messages because only the
// parser and the message copier are allowed to directly create an empty
// message.
UPB_INLINE void UPB_PRIVATE(_upb_Message_SetTaggedMessagePtr)(
    struct upb_Message* msg, const upb_MiniTableField* f,
    uintptr_t sub_message) {
  UPB_ASSUME(upb_MiniTableField_CType(f) == kUpb_CType_Message);
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableField_GetRep)(f) ==
             UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte));
  UPB_ASSUME(upb_MiniTableField_IsScalar(f));
  upb_Message_SetBaseField(msg, f, &sub_message);
}

UPB_API_INLINE const struct upb_Message* upb_Message_GetMessage(
    const struct upb_Message* msg, const upb_MiniTableField* f) {
  uintptr_t tagged = upb_Message_GetTaggedMessagePtr(msg, f, NULL);
  return upb_TaggedMessagePtr_GetNonEmptyMessage(tagged);
}

UPB_API_INLINE upb_Array* upb_Message_GetMutableArray(
    struct upb_Message* msg, const upb_MiniTableField* f) {
  UPB_PRIVATE(_upb_MiniTableField_CheckIsArray)(f);
  return (upb_Array*)upb_Message_GetArray(msg, f);
}

UPB_API_INLINE struct upb_Map* upb_Message_GetMutableMap(
    struct upb_Message* msg, const upb_MiniTableField* f) {
  return (struct upb_Map*)upb_Message_GetMap(msg, f);
}

UPB_API_INLINE struct upb_Message* upb_Message_GetMutableMessage(
    struct upb_Message* msg, const upb_MiniTableField* f) {
  return (struct upb_Message*)upb_Message_GetMessage(msg, f);
}

UPB_API_INLINE upb_Array* upb_Message_GetOrCreateMutableArray(
    struct upb_Message* msg, const upb_MiniTableField* f, upb_Arena* arena) {
  UPB_ASSERT(arena);
  UPB_PRIVATE(_upb_MiniTableField_CheckIsArray)(f);
  upb_Array* array = upb_Message_GetMutableArray(msg, f);
  if (!array) {
    array = UPB_PRIVATE(_upb_Array_New)(
        arena, 4, UPB_PRIVATE(_upb_MiniTableField_ElemSizeLg2)(f));
    // Check again due to: https://godbolt.org/z/7WfaoKG1r
    UPB_PRIVATE(_upb_MiniTableField_CheckIsArray)(f);
    upb_MessageValue val;
    val.array_val = array;
    UPB_PRIVATE(_upb_Message_SetField)(msg, f, val, arena);
  }
  return array;
}

UPB_INLINE struct upb_Map* _upb_Message_GetOrCreateMutableMap(
    struct upb_Message* msg, const upb_MiniTableField* field, size_t key_size,
    size_t val_size, upb_Arena* arena) {
  UPB_PRIVATE(_upb_MiniTableField_CheckIsMap)(field);
  UPB_PRIVATE(_upb_Message_AssertMapIsUntagged)(msg, field);
  struct upb_Map* map = NULL;
  struct upb_Map* default_map_value = NULL;
  _upb_Message_GetNonExtensionField(msg, field, &default_map_value, &map);
  if (!map) {
    map = _upb_Map_New(arena, key_size, val_size);
    // Check again due to: https://godbolt.org/z/7WfaoKG1r
    UPB_PRIVATE(_upb_MiniTableField_CheckIsMap)(field);
    upb_Message_SetBaseField(msg, field, &map);
  }
  return map;
}

UPB_API_INLINE struct upb_Map* upb_Message_GetOrCreateMutableMap(
    struct upb_Message* msg, const upb_MiniTable* map_entry_mini_table,
    const upb_MiniTableField* f, upb_Arena* arena) {
  UPB_ASSUME(upb_MiniTableField_CType(f) == kUpb_CType_Message);
  const upb_MiniTableField* map_entry_key_field =
      &map_entry_mini_table->UPB_ONLYBITS(fields)[0];
  const upb_MiniTableField* map_entry_value_field =
      &map_entry_mini_table->UPB_ONLYBITS(fields)[1];
  return _upb_Message_GetOrCreateMutableMap(
      msg, f, _upb_Map_CTypeSize(upb_MiniTableField_CType(map_entry_key_field)),
      _upb_Map_CTypeSize(upb_MiniTableField_CType(map_entry_value_field)),
      arena);
}

UPB_API_INLINE struct upb_Message* upb_Message_GetOrCreateMutableMessage(
    struct upb_Message* msg, const upb_MiniTable* mini_table,
    const upb_MiniTableField* f, upb_Arena* arena) {
  UPB_ASSERT(arena);
  UPB_ASSUME(upb_MiniTableField_CType(f) == kUpb_CType_Message);
  UPB_ASSUME(!upb_MiniTableField_IsExtension(f));
  struct upb_Message* sub_message =
      *UPB_PTR_AT(msg, f->UPB_ONLYBITS(offset), struct upb_Message*);
  if (!sub_message) {
    const upb_MiniTable* sub_mini_table =
        upb_MiniTable_SubMessage(mini_table, f);
    UPB_ASSERT(sub_mini_table);
    sub_message = _upb_Message_New(sub_mini_table, arena);
    *UPB_PTR_AT(msg, f->UPB_ONLYBITS(offset), struct upb_Message*) =
        sub_message;
    UPB_PRIVATE(_upb_Message_SetPresence)(msg, f);
  }
  return sub_message;
}

UPB_API_INLINE upb_StringView
upb_Message_GetString(const struct upb_Message* msg,
                      const upb_MiniTableField* f, upb_StringView default_val) {
  UPB_ASSUME(upb_MiniTableField_CType(f) == kUpb_CType_String ||
             upb_MiniTableField_CType(f) == kUpb_CType_Bytes);
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableField_GetRep)(f) ==
             kUpb_FieldRep_StringView);

  upb_MessageValue def;
  def.str_val = default_val;
  return upb_Message_GetField(msg, f, def).str_val;
}

UPB_API_INLINE uint32_t upb_Message_GetUInt32(const struct upb_Message* msg,
                                              const upb_MiniTableField* f,
                                              uint32_t default_val) {
  UPB_ASSUME(upb_MiniTableField_CType(f) == kUpb_CType_UInt32);
  UPB_ASSUME(upb_MiniTableField_IsScalar(f));
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableField_GetRep)(f) == kUpb_FieldRep_4Byte);

  upb_MessageValue def;
  def.uint32_val = default_val;
  return upb_Message_GetField(msg, f, def).uint32_val;
}

UPB_API_INLINE uint64_t upb_Message_GetUInt64(const struct upb_Message* msg,
                                              const upb_MiniTableField* f,
                                              uint64_t default_val) {
  UPB_ASSUME(upb_MiniTableField_CType(f) == kUpb_CType_UInt64);
  UPB_ASSUME(upb_MiniTableField_IsScalar(f));
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableField_GetRep)(f) == kUpb_FieldRep_8Byte);

  upb_MessageValue def;
  def.uint64_val = default_val;
  return upb_Message_GetField(msg, f, def).uint64_val;
}

// BaseField Setters ///////////////////////////////////////////////////////////

UPB_API_INLINE void upb_Message_SetBaseFieldBool(struct upb_Message* msg,
                                                 const upb_MiniTableField* f,
                                                 bool value) {
  UPB_ASSUME(upb_MiniTableField_CType(f) == kUpb_CType_Bool);
  UPB_ASSUME(upb_MiniTableField_IsScalar(f));
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableField_GetRep)(f) == kUpb_FieldRep_1Byte);
  upb_Message_SetBaseField(msg, f, &value);
}

UPB_API_INLINE void upb_Message_SetBaseFieldDouble(struct upb_Message* msg,
                                                   const upb_MiniTableField* f,
                                                   double value) {
  UPB_ASSUME(upb_MiniTableField_CType(f) == kUpb_CType_Double);
  UPB_ASSUME(upb_MiniTableField_IsScalar(f));
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableField_GetRep)(f) == kUpb_FieldRep_8Byte);
  upb_Message_SetBaseField(msg, f, &value);
}

UPB_API_INLINE void upb_Message_SetBaseFieldFloat(struct upb_Message* msg,
                                                  const upb_MiniTableField* f,
                                                  float value) {
  UPB_ASSUME(upb_MiniTableField_CType(f) == kUpb_CType_Float);
  UPB_ASSUME(upb_MiniTableField_IsScalar(f));
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableField_GetRep)(f) == kUpb_FieldRep_4Byte);
  upb_Message_SetBaseField(msg, f, &value);
}

UPB_API_INLINE void upb_Message_SetBaseFieldInt32(struct upb_Message* msg,
                                                  const upb_MiniTableField* f,
                                                  int32_t value) {
  UPB_ASSUME(upb_MiniTableField_CType(f) == kUpb_CType_Int32 ||
             upb_MiniTableField_CType(f) == kUpb_CType_Enum);
  UPB_ASSUME(upb_MiniTableField_IsScalar(f));
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableField_GetRep)(f) == kUpb_FieldRep_4Byte);
  upb_Message_SetBaseField(msg, f, &value);
}

UPB_API_INLINE void upb_Message_SetBaseFieldInt64(struct upb_Message* msg,
                                                  const upb_MiniTableField* f,
                                                  int64_t value) {
  UPB_ASSUME(upb_MiniTableField_CType(f) == kUpb_CType_Int64);
  UPB_ASSUME(upb_MiniTableField_IsScalar(f));
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableField_GetRep)(f) == kUpb_FieldRep_8Byte);
  upb_Message_SetBaseField(msg, f, &value);
}

UPB_API_INLINE void upb_Message_SetBaseFieldMessage(struct upb_Message* msg,
                                                    const upb_MiniTableField* f,
                                                    struct upb_Message* value) {
  UPB_PRIVATE(_upb_Message_SetTaggedMessagePtr)
  (msg, f, UPB_PRIVATE(_upb_TaggedMessagePtr_Pack)(value, false));
}

UPB_API_INLINE void upb_Message_SetBaseFieldString(struct upb_Message* msg,
                                                   const upb_MiniTableField* f,
                                                   upb_StringView value) {
  UPB_ASSUME(upb_MiniTableField_CType(f) == kUpb_CType_String ||
             upb_MiniTableField_CType(f) == kUpb_CType_Bytes);
  UPB_ASSUME(upb_MiniTableField_IsScalar(f));
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableField_GetRep)(f) ==
             kUpb_FieldRep_StringView);
  upb_Message_SetBaseField(msg, f, &value);
}

UPB_API_INLINE void upb_Message_SetBaseFieldUInt32(struct upb_Message* msg,
                                                   const upb_MiniTableField* f,
                                                   uint32_t value) {
  UPB_ASSUME(upb_MiniTableField_CType(f) == kUpb_CType_UInt32);
  UPB_ASSUME(upb_MiniTableField_IsScalar(f));
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableField_GetRep)(f) == kUpb_FieldRep_4Byte);
  upb_Message_SetBaseField(msg, f, &value);
}

UPB_API_INLINE void upb_Message_SetBaseFieldUInt64(struct upb_Message* msg,
                                                   const upb_MiniTableField* f,
                                                   uint64_t value) {
  UPB_ASSUME(upb_MiniTableField_CType(f) == kUpb_CType_UInt64);
  UPB_ASSUME(upb_MiniTableField_IsScalar(f));
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableField_GetRep)(f) == kUpb_FieldRep_8Byte);
  upb_Message_SetBaseField(msg, f, &value);
}

UPB_API_INLINE void upb_Message_SetClosedEnum(struct upb_Message* msg,
                                              const upb_MiniTable* m,
                                              const upb_MiniTableField* f,
                                              int32_t value) {
  UPB_ASSERT(upb_MiniTableField_IsClosedEnum(f));
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableField_GetRep)(f) == kUpb_FieldRep_4Byte);
  UPB_ASSERT(
      upb_MiniTableEnum_CheckValue(upb_MiniTable_GetSubEnumTable(m, f), value));
  upb_Message_SetBaseField(msg, f, &value);
}

// Extension Setters ///////////////////////////////////////////////////////////

UPB_API_INLINE bool upb_Message_SetExtensionMessage(
    struct upb_Message* msg, const upb_MiniTableExtension* e,
    struct upb_Message* value, upb_Arena* a) {
  UPB_ASSERT(value);
  UPB_ASSUME(upb_MiniTableExtension_CType(e) == kUpb_CType_Message);
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableExtension_GetRep)(e) ==
             UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte));
  return upb_Message_SetExtension(msg, e, &value, a);
}

UPB_API_INLINE bool upb_Message_SetExtensionBool(
    struct upb_Message* msg, const upb_MiniTableExtension* e, bool value,
    upb_Arena* a) {
  UPB_ASSUME(upb_MiniTableExtension_CType(e) == kUpb_CType_Bool);
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableExtension_GetRep)(e) ==
             kUpb_FieldRep_1Byte);
  return upb_Message_SetExtension(msg, e, &value, a);
}

UPB_API_INLINE bool upb_Message_SetExtensionDouble(
    struct upb_Message* msg, const upb_MiniTableExtension* e, double value,
    upb_Arena* a) {
  UPB_ASSUME(upb_MiniTableExtension_CType(e) == kUpb_CType_Double);
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableExtension_GetRep)(e) ==
             kUpb_FieldRep_8Byte);
  return upb_Message_SetExtension(msg, e, &value, a);
}

UPB_API_INLINE bool upb_Message_SetExtensionFloat(
    struct upb_Message* msg, const upb_MiniTableExtension* e, float value,
    upb_Arena* a) {
  UPB_ASSUME(upb_MiniTableExtension_CType(e) == kUpb_CType_Float);
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableExtension_GetRep)(e) ==
             kUpb_FieldRep_4Byte);
  return upb_Message_SetExtension(msg, e, &value, a);
}

UPB_API_INLINE bool upb_Message_SetExtensionInt32(
    struct upb_Message* msg, const upb_MiniTableExtension* e, int32_t value,
    upb_Arena* a) {
  UPB_ASSUME(upb_MiniTableExtension_CType(e) == kUpb_CType_Int32 ||
             upb_MiniTableExtension_CType(e) == kUpb_CType_Enum);
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableExtension_GetRep)(e) ==
             kUpb_FieldRep_4Byte);
  return upb_Message_SetExtension(msg, e, &value, a);
}

UPB_API_INLINE bool upb_Message_SetExtensionInt64(
    struct upb_Message* msg, const upb_MiniTableExtension* e, int64_t value,
    upb_Arena* a) {
  UPB_ASSUME(upb_MiniTableExtension_CType(e) == kUpb_CType_Int64);
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableExtension_GetRep)(e) ==
             kUpb_FieldRep_8Byte);
  return upb_Message_SetExtension(msg, e, &value, a);
}

UPB_API_INLINE bool upb_Message_SetExtensionString(
    struct upb_Message* msg, const upb_MiniTableExtension* e,
    upb_StringView value, upb_Arena* a) {
  UPB_ASSUME(upb_MiniTableExtension_CType(e) == kUpb_CType_String ||
             upb_MiniTableExtension_CType(e) == kUpb_CType_Bytes);
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableExtension_GetRep)(e) ==
             kUpb_FieldRep_StringView);
  return upb_Message_SetExtension(msg, e, &value, a);
}

UPB_API_INLINE bool upb_Message_SetExtensionUInt32(
    struct upb_Message* msg, const upb_MiniTableExtension* e, uint32_t value,
    upb_Arena* a) {
  UPB_ASSUME(upb_MiniTableExtension_CType(e) == kUpb_CType_UInt32);
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableExtension_GetRep)(e) ==
             kUpb_FieldRep_4Byte);
  return upb_Message_SetExtension(msg, e, &value, a);
}

UPB_API_INLINE bool upb_Message_SetExtensionUInt64(
    struct upb_Message* msg, const upb_MiniTableExtension* e, uint64_t value,
    upb_Arena* a) {
  UPB_ASSUME(upb_MiniTableExtension_CType(e) == kUpb_CType_UInt64);
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableExtension_GetRep)(e) ==
             kUpb_FieldRep_8Byte);
  return upb_Message_SetExtension(msg, e, &value, a);
}

// Universal Setters ///////////////////////////////////////////////////////////

UPB_API_INLINE bool upb_Message_SetBool(struct upb_Message* msg,
                                        const upb_MiniTableField* f, bool value,
                                        upb_Arena* a) {
  return upb_MiniTableField_IsExtension(f)
             ? upb_Message_SetExtensionBool(
                   msg, (const upb_MiniTableExtension*)f, value, a)
             : (upb_Message_SetBaseFieldBool(msg, f, value), true);
}

UPB_API_INLINE bool upb_Message_SetDouble(struct upb_Message* msg,
                                          const upb_MiniTableField* f,
                                          double value, upb_Arena* a) {
  return upb_MiniTableField_IsExtension(f)
             ? upb_Message_SetExtensionDouble(
                   msg, (const upb_MiniTableExtension*)f, value, a)
             : (upb_Message_SetBaseFieldDouble(msg, f, value), true);
}

UPB_API_INLINE bool upb_Message_SetFloat(struct upb_Message* msg,
                                         const upb_MiniTableField* f,
                                         float value, upb_Arena* a) {
  return upb_MiniTableField_IsExtension(f)
             ? upb_Message_SetExtensionFloat(
                   msg, (const upb_MiniTableExtension*)f, value, a)
             : (upb_Message_SetBaseFieldFloat(msg, f, value), true);
}

UPB_API_INLINE bool upb_Message_SetInt32(struct upb_Message* msg,
                                         const upb_MiniTableField* f,
                                         int32_t value, upb_Arena* a) {
  return upb_MiniTableField_IsExtension(f)
             ? upb_Message_SetExtensionInt32(
                   msg, (const upb_MiniTableExtension*)f, value, a)
             : (upb_Message_SetBaseFieldInt32(msg, f, value), true);
}

UPB_API_INLINE bool upb_Message_SetInt64(struct upb_Message* msg,
                                         const upb_MiniTableField* f,
                                         int64_t value, upb_Arena* a) {
  return upb_MiniTableField_IsExtension(f)
             ? upb_Message_SetExtensionInt64(
                   msg, (const upb_MiniTableExtension*)f, value, a)
             : (upb_Message_SetBaseFieldInt64(msg, f, value), true);
}

// Sets the value of a message-typed field. The mini_tables of `msg` and
// `value` must have been linked for this to work correctly.
UPB_API_INLINE void upb_Message_SetMessage(struct upb_Message* msg,
                                           const upb_MiniTableField* f,
                                           struct upb_Message* value) {
  UPB_ASSERT(!upb_MiniTableField_IsExtension(f));
  upb_Message_SetBaseFieldMessage(msg, f, value);
}

// Sets the value of a `string` or `bytes` field. The bytes of the value are not
// copied, so it is the caller's responsibility to ensure that they remain valid
// for the lifetime of `msg`. That might be done by copying them into the given
// arena, or by fusing that arena with the arena the bytes live in, for example.
UPB_API_INLINE bool upb_Message_SetString(struct upb_Message* msg,
                                          const upb_MiniTableField* f,
                                          upb_StringView value, upb_Arena* a) {
  return upb_MiniTableField_IsExtension(f)
             ? upb_Message_SetExtensionString(
                   msg, (const upb_MiniTableExtension*)f, value, a)
             : (upb_Message_SetBaseFieldString(msg, f, value), true);
}

UPB_API_INLINE bool upb_Message_SetUInt32(struct upb_Message* msg,
                                          const upb_MiniTableField* f,
                                          uint32_t value, upb_Arena* a) {
  return upb_MiniTableField_IsExtension(f)
             ? upb_Message_SetExtensionUInt32(
                   msg, (const upb_MiniTableExtension*)f, value, a)
             : (upb_Message_SetBaseFieldUInt32(msg, f, value), true);
}

UPB_API_INLINE bool upb_Message_SetUInt64(struct upb_Message* msg,
                                          const upb_MiniTableField* f,
                                          uint64_t value, upb_Arena* a) {
  return upb_MiniTableField_IsExtension(f)
             ? upb_Message_SetExtensionUInt64(
                   msg, (const upb_MiniTableExtension*)f, value, a)
             : (upb_Message_SetBaseFieldUInt64(msg, f, value), true);
}

UPB_API_INLINE void upb_Message_Clear(struct upb_Message* msg,
                                      const upb_MiniTable* m) {
  UPB_ASSERT(!upb_Message_IsFrozen(msg));
  upb_Message_Internal* in = UPB_PRIVATE(_upb_Message_GetInternal)(msg);
  memset(msg, 0, m->UPB_PRIVATE(size));
  if (in) {
    // Reset the internal buffer to empty.
    in->size = 0;
  }
}

UPB_API_INLINE void upb_Message_ClearBaseField(struct upb_Message* msg,
                                               const upb_MiniTableField* f) {
  UPB_ASSERT(!upb_Message_IsFrozen(msg));
  if (UPB_PRIVATE(_upb_MiniTableField_HasHasbit)(f)) {
    UPB_PRIVATE(_upb_Message_ClearHasbit)(msg, f);
  } else if (upb_MiniTableField_IsInOneof(f)) {
    uint32_t* ptr = UPB_PRIVATE(_upb_Message_OneofCasePtr)(msg, f);
    if (*ptr != upb_MiniTableField_Number(f)) return;
    *ptr = 0;
  }
  const char zeros[16] = {0};
  UPB_PRIVATE(_upb_MiniTableField_DataCopy)
  (f, UPB_PRIVATE(_upb_Message_MutableDataPtr)(msg, f), zeros);
}

UPB_API_INLINE void upb_Message_ClearExtension(
    struct upb_Message* msg, const upb_MiniTableExtension* e) {
  UPB_ASSERT(!upb_Message_IsFrozen(msg));
  upb_Message_Internal* in = UPB_PRIVATE(_upb_Message_GetInternal)(msg);
  if (!in) return;
  for (size_t i = 0; i < in->size; i++) {
    upb_TaggedAuxPtr tagged_ptr = in->aux_data[i];
    if (upb_TaggedAuxPtr_IsExtension(tagged_ptr)) {
      const upb_Extension* ext = upb_TaggedAuxPtr_Extension(tagged_ptr);
      if (ext->ext == e) {
        in->aux_data[i] = upb_TaggedAuxPtr_Null();
        return;
      }
    }
  }
}

UPB_API_INLINE void upb_Message_ClearOneof(struct upb_Message* msg,
                                           const upb_MiniTable* m,
                                           const upb_MiniTableField* f) {
  UPB_ASSERT(!upb_Message_IsFrozen(msg));
  uint32_t field_number = upb_Message_WhichOneofFieldNumber(msg, f);
  if (field_number == 0) {
    // No field in the oneof is set.
    return;
  }

  const upb_MiniTableField* field =
      upb_MiniTable_FindFieldByNumber(m, field_number);
  upb_Message_ClearBaseField(msg, field);
}

UPB_API_INLINE void* upb_Message_ResizeArrayUninitialized(
    struct upb_Message* msg, const upb_MiniTableField* f, size_t size,
    upb_Arena* arena) {
  UPB_PRIVATE(_upb_MiniTableField_CheckIsArray)(f);
  upb_Array* arr = upb_Message_GetOrCreateMutableArray(msg, f, arena);
  if (!arr || !UPB_PRIVATE(_upb_Array_ResizeUninitialized)(arr, size, arena)) {
    return NULL;
  }
  return upb_Array_MutableDataPtr(arr);
}

UPB_API_INLINE bool upb_Message_GetExtensionBool(
    const struct upb_Message* msg, const upb_MiniTableExtension* e,
    bool default_val) {
  UPB_ASSUME(upb_MiniTableExtension_CType(e) == kUpb_CType_Bool);
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableExtension_GetRep)(e) ==
             kUpb_FieldRep_1Byte);
  bool ret;
  _upb_Message_GetExtensionField(msg, e, &default_val, &ret);
  return ret;
}

UPB_API_INLINE double upb_Message_GetExtensionDouble(
    const struct upb_Message* msg, const upb_MiniTableExtension* e,
    double default_val) {
  UPB_ASSUME(upb_MiniTableExtension_CType(e) == kUpb_CType_Double);
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableExtension_GetRep)(e) ==
             kUpb_FieldRep_8Byte);
  double ret;
  _upb_Message_GetExtensionField(msg, e, &default_val, &ret);
  return ret;
}

UPB_API_INLINE float upb_Message_GetExtensionFloat(
    const struct upb_Message* msg, const upb_MiniTableExtension* e,
    float default_val) {
  float ret;
  UPB_ASSUME(upb_MiniTableExtension_CType(e) == kUpb_CType_Float);
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableExtension_GetRep)(e) ==
             kUpb_FieldRep_4Byte);
  _upb_Message_GetExtensionField(msg, e, &default_val, &ret);
  return ret;
}

UPB_API_INLINE int32_t upb_Message_GetExtensionInt32(
    const struct upb_Message* msg, const upb_MiniTableExtension* e,
    int32_t default_val) {
  UPB_ASSUME(upb_MiniTableExtension_CType(e) == kUpb_CType_Int32 ||
             upb_MiniTableExtension_CType(e) == kUpb_CType_Enum);
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableExtension_GetRep)(e) ==
             kUpb_FieldRep_4Byte);
  int32_t ret;
  _upb_Message_GetExtensionField(msg, e, &default_val, &ret);
  return ret;
}

UPB_API_INLINE int64_t upb_Message_GetExtensionInt64(
    const struct upb_Message* msg, const upb_MiniTableExtension* e,
    int64_t default_val) {
  UPB_ASSUME(upb_MiniTableExtension_CType(e) == kUpb_CType_Int64);
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableExtension_GetRep)(e) ==
             kUpb_FieldRep_8Byte);
  int64_t ret;
  _upb_Message_GetExtensionField(msg, e, &default_val, &ret);
  return ret;
}

UPB_API_INLINE uint32_t upb_Message_GetExtensionUInt32(
    const struct upb_Message* msg, const upb_MiniTableExtension* e,
    uint32_t default_val) {
  UPB_ASSUME(upb_MiniTableExtension_CType(e) == kUpb_CType_UInt32);
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableExtension_GetRep)(e) ==
             kUpb_FieldRep_4Byte);
  uint32_t ret;
  _upb_Message_GetExtensionField(msg, e, &default_val, &ret);
  return ret;
}

UPB_API_INLINE uint64_t upb_Message_GetExtensionUInt64(
    const struct upb_Message* msg, const upb_MiniTableExtension* e,
    uint64_t default_val) {
  UPB_ASSUME(upb_MiniTableExtension_CType(e) == kUpb_CType_UInt64);
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableExtension_GetRep)(e) ==
             kUpb_FieldRep_8Byte);
  uint64_t ret;
  _upb_Message_GetExtensionField(msg, e, &default_val, &ret);
  return ret;
}

UPB_API_INLINE upb_StringView upb_Message_GetExtensionString(
    const struct upb_Message* msg, const upb_MiniTableExtension* e,
    upb_StringView default_val) {
  UPB_ASSUME(upb_MiniTableExtension_CType(e) == kUpb_CType_String ||
             upb_MiniTableExtension_CType(e) == kUpb_CType_Bytes);
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableExtension_GetRep)(e) ==
             kUpb_FieldRep_StringView);
  upb_StringView ret;
  _upb_Message_GetExtensionField(msg, e, &default_val, &ret);
  return ret;
}

UPB_API_INLINE struct upb_Message* upb_Message_GetExtensionMessage(
    const struct upb_Message* msg, const upb_MiniTableExtension* e,
    struct upb_Message* default_val) {
  UPB_ASSUME(upb_MiniTableExtension_CType(e) == kUpb_CType_Message);
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableExtension_GetRep)(e) ==
             UPB_SIZE(kUpb_FieldRep_4Byte, kUpb_FieldRep_8Byte));
  struct upb_Message* ret;
  _upb_Message_GetExtensionField(msg, e, &default_val, &ret);
  return ret;
}

// Repeated
UPB_API_INLINE const upb_Array* upb_Message_GetExtensionArray(
    const struct upb_Message* msg, const upb_MiniTableExtension* e) {
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableField_GetRep)(&e->UPB_PRIVATE(field)) ==
             kUpb_FieldRep_NativePointer);
  UPB_ASSUME(upb_MiniTableField_IsArray(&e->UPB_PRIVATE(field)));
  UPB_ASSUME(e->UPB_PRIVATE(field).presence == 0);
  upb_Array* ret;
  const upb_Array* default_val = NULL;
  _upb_Message_GetExtensionField(msg, e, &default_val, &ret);
  return ret;
}

UPB_API_INLINE upb_Array* upb_Message_GetExtensionMutableArray(
    struct upb_Message* msg, const upb_MiniTableExtension* e) {
  UPB_ASSERT(!upb_Message_IsFrozen(msg));
  UPB_ASSUME(UPB_PRIVATE(_upb_MiniTableField_GetRep)(&e->UPB_PRIVATE(field)) ==
             kUpb_FieldRep_NativePointer);
  UPB_ASSUME(upb_MiniTableField_IsArray(&e->UPB_PRIVATE(field)));
  UPB_ASSUME(e->UPB_PRIVATE(field).presence == 0);
  upb_Array* ret;
  upb_Array* default_val = NULL;
  _upb_Message_GetExtensionField(msg, e, &default_val, &ret);
  return ret;
}

#ifdef __cplusplus
} /* extern "C" */
#endif

#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC diagnostic pop
#endif


#endif  // UPB_MESSAGE_INTERNAL_ACCESSORS_H_

#ifndef UPB_MESSAGE_MAP_H_
#define UPB_MESSAGE_MAP_H_

#include <stddef.h>


// Must be last.

typedef struct upb_Map upb_Map;

#ifdef __cplusplus
extern "C" {
#endif

// Creates a new map on the given arena with the given key/value size.
UPB_API upb_Map* upb_Map_New(upb_Arena* a, upb_CType key_type,
                             upb_CType value_type);

// Returns the number of entries in the map.
UPB_API size_t upb_Map_Size(const upb_Map* map);

// Stores a value for the given key into |*val| (or the zero value if the key is
// not present). Returns whether the key was present. The |val| pointer may be
// NULL, in which case the function tests whether the given key is present.
UPB_API bool upb_Map_Get(const upb_Map* map, upb_MessageValue key,
                         upb_MessageValue* val);

// Returns a mutable pointer to the value for the given key. Returns NULL if the
// key is not present.
// This function is only legal to call for maps that contain messages.
UPB_API struct upb_Message* upb_Map_GetMutable(upb_Map* map,
                                               upb_MessageValue key);

// Removes all entries in the map.
UPB_API void upb_Map_Clear(upb_Map* map);

// Sets the given key to the given value, returning whether the key was inserted
// or replaced. If the key was inserted, then any existing iterators will be
// invalidated.
UPB_API upb_MapInsertStatus upb_Map_Insert(upb_Map* map, upb_MessageValue key,
                                           upb_MessageValue val,
                                           upb_Arena* arena);

// Sets the given key to the given value. Returns false if memory allocation
// failed. If the key is newly inserted, then any existing iterators will be
// invalidated.
UPB_API_INLINE bool upb_Map_Set(upb_Map* map, upb_MessageValue key,
                                upb_MessageValue val, upb_Arena* arena) {
  return upb_Map_Insert(map, key, val, arena) !=
         kUpb_MapInsertStatus_OutOfMemory;
}

// Deletes this key from the table. Returns true if the key was present.
// If present and |val| is non-NULL, stores the deleted value.
UPB_API bool upb_Map_Delete(upb_Map* map, upb_MessageValue key,
                            upb_MessageValue* val);

// Map iteration:
//
// size_t iter = kUpb_Map_Begin;
// upb_MessageValue key, val;
// while (upb_Map_Next(map, &key, &val, &iter)) {
//   ...
// }

#define kUpb_Map_Begin ((size_t)-1)

// Advances to the next entry. Returns false if no more entries are present.
// Otherwise returns true and populates both *key and *value.
UPB_API bool upb_Map_Next(const upb_Map* map, upb_MessageValue* key,
                          upb_MessageValue* val, size_t* iter);

// Sets the value for the entry pointed to by iter.
// WARNING: this does not currently work for string values!
UPB_API void upb_Map_SetEntryValue(upb_Map* map, size_t iter,
                                   upb_MessageValue val);

// DEPRECATED iterator, slated for removal.

/* Map iteration:
 *
 * size_t iter = kUpb_Map_Begin;
 * while (upb_MapIterator_Next(map, &iter)) {
 *   upb_MessageValue key = upb_MapIterator_Key(map, iter);
 *   upb_MessageValue val = upb_MapIterator_Value(map, iter);
 * }
 */

// Advances to the next entry. Returns false if no more entries are present.
UPB_API bool upb_MapIterator_Next(const upb_Map* map, size_t* iter);

// Returns true if the iterator still points to a valid entry, or false if the
// iterator is past the last element. It is an error to call this function with
// kUpb_Map_Begin (you must call next() at least once first).
UPB_API bool upb_MapIterator_Done(const upb_Map* map, size_t iter);

// Returns the key and value for this entry of the map.
UPB_API upb_MessageValue upb_MapIterator_Key(const upb_Map* map, size_t iter);
UPB_API upb_MessageValue upb_MapIterator_Value(const upb_Map* map, size_t iter);

// Mark a map and all of its descendents as frozen/immutable.
// If the map values are messages then |m| must point to the minitable for
// those messages. Otherwise |m| must be NULL.
UPB_API void upb_Map_Freeze(upb_Map* map, const upb_MiniTable* m);

// Returns whether a map has been frozen.
UPB_API_INLINE bool upb_Map_IsFrozen(const upb_Map* map);

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /* UPB_MESSAGE_MAP_H_ */

// Public APIs for message operations that do not depend on the schema.
//
// MiniTable-based accessors live in accessors.h.

#ifndef UPB_MESSAGE_MESSAGE_H_
#define UPB_MESSAGE_MESSAGE_H_

#include <stddef.h>
#include <stdint.h>


// Must be last.

typedef struct upb_Message upb_Message;

#ifdef __cplusplus
extern "C" {
#endif

// Creates a new message with the given mini_table on the given arena.
UPB_API upb_Message* upb_Message_New(const upb_MiniTable* m, upb_Arena* arena);

//
// Unknown data may be stored non-contiguously. Each segment stores a block of
// unknown fields. To iterate over segments:
//
//   uintptr_t iter = kUpb_Message_UnknownBegin;
//   upb_StringView data;
//   while (upb_Message_NextUnknown(msg, &data, &iter)) {
//     // Use data
//   }
// Iterates in the order unknown fields were parsed.

#define kUpb_Message_UnknownBegin 0
#define kUpb_Message_ExtensionBegin 0

UPB_INLINE bool upb_Message_NextUnknown(const upb_Message* msg,
                                        upb_StringView* data, uintptr_t* iter);

UPB_INLINE bool upb_Message_HasUnknown(const upb_Message* msg);

// Removes a segment of unknown data from the message, advancing to the next
// segment.  Returns false if the removed segment was at the end of the last
// chunk.
//
// This must be done while iterating:
//
//   uintptr_t iter = kUpb_Message_UnknownBegin;
//   upb_StringView data;
//   // Iterate chunks
//   while (upb_Message_NextUnknown(msg, &data, &iter)) {
//     // Iterate within a chunk, deleting ranges
//     while (ShouldDeleteSubSegment(&data)) {
//       // Data now points to the region to be deleted
//       switch (upb_Message_DeleteUnknown(msg, &data, &iter)) {
//         case kUpb_Message_DeleteUnknown_DeletedLast: return ok;
//         case kUpb_Message_DeleteUnknown_IterUpdated: break;
//         // If DeleteUnknown returned kUpb_Message_DeleteUnknown_IterUpdated,
//         // then data now points to the remaining unknown fields after the
//         // region that was just deleted.
//         case kUpb_Message_DeleteUnknown_AllocFail: return err;
//       }
//     }
//   }
//
// The range given in `data` must be contained inside the most recently
// returned region.
typedef enum upb_Message_DeleteUnknownStatus {
  kUpb_DeleteUnknown_DeletedLast,
  kUpb_DeleteUnknown_IterUpdated,
  kUpb_DeleteUnknown_AllocFail,
} upb_Message_DeleteUnknownStatus;
upb_Message_DeleteUnknownStatus upb_Message_DeleteUnknown(upb_Message* msg,
                                                          upb_StringView* data,
                                                          uintptr_t* iter,
                                                          upb_Arena* arena);

// Returns the number of extensions present in this message.
size_t upb_Message_ExtensionCount(const upb_Message* msg);

// Iterates extensions in wire order
UPB_INLINE bool upb_Message_NextExtension(const upb_Message* msg,
                                          const upb_MiniTableExtension** out_e,
                                          upb_MessageValue* out_v,
                                          uintptr_t* iter);

// Iterates extensions in reverse wire order
UPB_INLINE bool UPB_PRIVATE(_upb_Message_NextExtensionReverse)(
    const struct upb_Message* msg, const upb_MiniTableExtension** out_e,
    upb_MessageValue* out_v, uintptr_t* iter);

// Mark a message and all of its descendents as frozen/immutable.
UPB_API void upb_Message_Freeze(upb_Message* msg, const upb_MiniTable* m);

// Returns whether a message has been frozen.
UPB_API_INLINE bool upb_Message_IsFrozen(const upb_Message* msg);

#ifdef UPB_TRACING_ENABLED
UPB_API void upb_Message_LogNewMessage(const upb_MiniTable* m,
                                       const upb_Arena* arena);

UPB_API void upb_Message_SetNewMessageTraceHandler(
    void (*handler)(const upb_MiniTable* m, const upb_Arena* arena));
#endif  // UPB_TRACING_ENABLED

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /* UPB_MESSAGE_MESSAGE_H_ */

#ifndef UPB_MINI_TABLE_TAGGED_PTR_H_
#define UPB_MINI_TABLE_TAGGED_PTR_H_

#include <stdint.h>


// Must be last.

// When a upb_Message* is stored in a message, array, or map, it is stored in a
// tagged form. If the tag bit is set, the referenced upb_Message is of type
// _kUpb_MiniTable_Empty (a sentinel message type with no fields) instead of
// that field's true message type. This forms the basis of what we call
// "dynamic tree shaking."
//
// See the documentation for kUpb_DecodeOption_ExperimentalAllowUnlinked for
// more information.

typedef uintptr_t upb_TaggedMessagePtr;

#ifdef __cplusplus
extern "C" {
#endif

// Users who enable unlinked sub-messages must use this to test whether a
// message is empty before accessing it. If a message is empty, it must be
// first promoted using the interfaces in message/promote.h.
UPB_API_INLINE bool upb_TaggedMessagePtr_IsEmpty(upb_TaggedMessagePtr ptr);

UPB_API_INLINE upb_Message* upb_TaggedMessagePtr_GetNonEmptyMessage(
    upb_TaggedMessagePtr ptr);

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /* UPB_MINI_TABLE_TAGGED_PTR_H_ */

// Must be last.

#ifdef __cplusplus
extern "C" {
#endif

// Functions ending in BaseField() take a (upb_MiniTableField*) argument
// and work only on non-extension fields.
//
// Functions ending in Extension() take a (upb_MiniTableExtension*) argument
// and work only on extensions.

UPB_API_INLINE void upb_Message_Clear(upb_Message* msg, const upb_MiniTable* m);

UPB_API_INLINE void upb_Message_ClearBaseField(upb_Message* msg,
                                               const upb_MiniTableField* f);

UPB_API_INLINE void upb_Message_ClearExtension(upb_Message* msg,
                                               const upb_MiniTableExtension* e);

UPB_API_INLINE void upb_Message_ClearOneof(upb_Message* msg,
                                           const upb_MiniTable* m,
                                           const upb_MiniTableField* f);

UPB_API_INLINE bool upb_Message_HasBaseField(const upb_Message* msg,
                                             const upb_MiniTableField* f);

UPB_API_INLINE bool upb_Message_HasExtension(const upb_Message* msg,
                                             const upb_MiniTableExtension* e);

UPB_API_INLINE upb_MessageValue
upb_Message_GetField(const upb_Message* msg, const upb_MiniTableField* f,
                     upb_MessageValue default_val);

UPB_API_INLINE upb_TaggedMessagePtr upb_Message_GetTaggedMessagePtr(
    const upb_Message* msg, const upb_MiniTableField* field,
    upb_Message* default_val);

UPB_API_INLINE const upb_Array* upb_Message_GetArray(
    const upb_Message* msg, const upb_MiniTableField* f);

UPB_API_INLINE bool upb_Message_GetBool(const upb_Message* msg,
                                        const upb_MiniTableField* f,
                                        bool default_val);

UPB_API_INLINE double upb_Message_GetDouble(const upb_Message* msg,
                                            const upb_MiniTableField* field,
                                            double default_val);

UPB_API_INLINE float upb_Message_GetFloat(const upb_Message* msg,
                                          const upb_MiniTableField* f,
                                          float default_val);

UPB_API_INLINE int32_t upb_Message_GetInt32(const upb_Message* msg,
                                            const upb_MiniTableField* f,
                                            int32_t default_val);

UPB_API_INLINE int64_t upb_Message_GetInt64(const upb_Message* msg,
                                            const upb_MiniTableField* f,
                                            int64_t default_val);

UPB_API_INLINE const upb_Map* upb_Message_GetMap(const upb_Message* msg,
                                                 const upb_MiniTableField* f);

UPB_API_INLINE const upb_Message* upb_Message_GetMessage(
    const upb_Message* msg, const upb_MiniTableField* f);

UPB_API_INLINE upb_Array* upb_Message_GetMutableArray(
    upb_Message* msg, const upb_MiniTableField* f);

UPB_API_INLINE upb_Map* upb_Message_GetMutableMap(upb_Message* msg,
                                                  const upb_MiniTableField* f);

UPB_API_INLINE upb_Message* upb_Message_GetMutableMessage(
    upb_Message* msg, const upb_MiniTableField* f);

UPB_API_INLINE upb_Array* upb_Message_GetOrCreateMutableArray(
    upb_Message* msg, const upb_MiniTableField* f, upb_Arena* arena);

UPB_API_INLINE upb_Map* upb_Message_GetOrCreateMutableMap(
    upb_Message* msg, const upb_MiniTable* map_entry_mini_table,
    const upb_MiniTableField* f, upb_Arena* arena);

UPB_API_INLINE upb_Message* upb_Message_GetOrCreateMutableMessage(
    upb_Message* msg, const upb_MiniTable* mini_table,
    const upb_MiniTableField* f, upb_Arena* arena);

UPB_API_INLINE upb_StringView
upb_Message_GetString(const upb_Message* msg, const upb_MiniTableField* field,
                      upb_StringView default_val);

UPB_API_INLINE uint32_t upb_Message_GetUInt32(const upb_Message* msg,
                                              const upb_MiniTableField* f,
                                              uint32_t default_val);

UPB_API_INLINE uint64_t upb_Message_GetUInt64(const upb_Message* msg,
                                              const upb_MiniTableField* f,
                                              uint64_t default_val);

UPB_API_INLINE void upb_Message_SetClosedEnum(
    upb_Message* msg, const upb_MiniTable* msg_mini_table,
    const upb_MiniTableField* f, int32_t value);

// BaseField Setters ///////////////////////////////////////////////////////////

UPB_API_INLINE void upb_Message_SetBaseField(upb_Message* msg,
                                             const upb_MiniTableField* f,
                                             const void* val);

UPB_API_INLINE void upb_Message_SetBaseFieldBool(struct upb_Message* msg,
                                                 const upb_MiniTableField* f,
                                                 bool value);

UPB_API_INLINE void upb_Message_SetBaseFieldDouble(struct upb_Message* msg,
                                                   const upb_MiniTableField* f,
                                                   double value);

UPB_API_INLINE void upb_Message_SetBaseFieldFloat(struct upb_Message* msg,
                                                  const upb_MiniTableField* f,
                                                  float value);

UPB_API_INLINE void upb_Message_SetBaseFieldInt32(struct upb_Message* msg,
                                                  const upb_MiniTableField* f,
                                                  int32_t value);

UPB_API_INLINE void upb_Message_SetBaseFieldInt64(struct upb_Message* msg,
                                                  const upb_MiniTableField* f,
                                                  int64_t value);

UPB_API_INLINE void upb_Message_SetBaseFieldMessage(struct upb_Message* msg,
                                                    const upb_MiniTableField* f,
                                                    upb_Message* value);

UPB_API_INLINE void upb_Message_SetBaseFieldString(struct upb_Message* msg,
                                                   const upb_MiniTableField* f,
                                                   upb_StringView value);

UPB_API_INLINE void upb_Message_SetBaseFieldUInt32(struct upb_Message* msg,
                                                   const upb_MiniTableField* f,
                                                   uint32_t value);

UPB_API_INLINE void upb_Message_SetBaseFieldUInt64(struct upb_Message* msg,
                                                   const upb_MiniTableField* f,
                                                   uint64_t value);

// Extension Getters ///////////////////////////////////////////////////////////
UPB_API_INLINE bool upb_Message_GetExtensionBool(
    const upb_Message* msg, const upb_MiniTableExtension* f, bool default_val);

UPB_API_INLINE double upb_Message_GetExtensionDouble(
    const upb_Message* msg, const upb_MiniTableExtension* f,
    double default_val);

UPB_API_INLINE float upb_Message_GetExtensionFloat(
    const upb_Message* msg, const upb_MiniTableExtension* f, float default_val);

UPB_API_INLINE int32_t upb_Message_GetExtensionInt32(
    const upb_Message* msg, const upb_MiniTableExtension* f,
    int32_t default_val);

UPB_API_INLINE int64_t upb_Message_GetExtensionInt64(
    const upb_Message* msg, const upb_MiniTableExtension* f,
    int64_t default_val);

UPB_API_INLINE uint32_t upb_Message_GetExtensionUInt32(
    const upb_Message* msg, const upb_MiniTableExtension* f,
    uint32_t default_val);

UPB_API_INLINE uint64_t upb_Message_GetExtensionUInt64(
    const upb_Message* msg, const upb_MiniTableExtension* f,
    uint64_t default_val);

UPB_API_INLINE upb_StringView upb_Message_GetExtensionString(
    const upb_Message* msg, const upb_MiniTableExtension* f,
    upb_StringView default_val);

UPB_API_INLINE upb_Message* upb_Message_GetExtensionMessage(
    const upb_Message* msg, const upb_MiniTableExtension* f,
    struct upb_Message* default_val);

UPB_API_INLINE const upb_Array* upb_Message_GetExtensionArray(
    const upb_Message* msg, const upb_MiniTableExtension* f);

UPB_API_INLINE upb_Array* upb_Message_GetExtensionMutableArray(
    upb_Message* msg, const upb_MiniTableExtension* f);

// Extension Setters ///////////////////////////////////////////////////////////

UPB_API_INLINE bool upb_Message_SetExtension(upb_Message* msg,
                                             const upb_MiniTableExtension* e,
                                             const void* value, upb_Arena* a);

UPB_API_INLINE bool upb_Message_SetExtensionMessage(
    struct upb_Message* msg, const upb_MiniTableExtension* e,
    struct upb_Message* value, upb_Arena* a);

UPB_API_INLINE bool upb_Message_SetExtensionBool(
    struct upb_Message* msg, const upb_MiniTableExtension* e, bool value,
    upb_Arena* a);

UPB_API_INLINE bool upb_Message_SetExtensionDouble(
    struct upb_Message* msg, const upb_MiniTableExtension* e, double value,
    upb_Arena* a);

UPB_API_INLINE bool upb_Message_SetExtensionFloat(
    struct upb_Message* msg, const upb_MiniTableExtension* e, float value,
    upb_Arena* a);

UPB_API_INLINE bool upb_Message_SetExtensionInt32(
    struct upb_Message* msg, const upb_MiniTableExtension* e, int32_t value,
    upb_Arena* a);

UPB_API_INLINE bool upb_Message_SetExtensionInt64(
    struct upb_Message* msg, const upb_MiniTableExtension* e, int64_t value,
    upb_Arena* a);

UPB_API_INLINE bool upb_Message_SetExtensionString(
    struct upb_Message* msg, const upb_MiniTableExtension* e,
    upb_StringView value, upb_Arena* a);

UPB_API_INLINE bool upb_Message_SetExtensionUInt32(
    struct upb_Message* msg, const upb_MiniTableExtension* e, uint32_t value,
    upb_Arena* a);

UPB_API_INLINE bool upb_Message_SetExtensionUInt64(
    struct upb_Message* msg, const upb_MiniTableExtension* e, uint64_t value,
    upb_Arena* a);

// Universal Setters ///////////////////////////////////////////////////////////

UPB_API_INLINE bool upb_Message_SetBool(upb_Message* msg,
                                        const upb_MiniTableField* f, bool value,
                                        upb_Arena* a);

UPB_API_INLINE bool upb_Message_SetDouble(upb_Message* msg,
                                          const upb_MiniTableField* f,
                                          double value, upb_Arena* a);

UPB_API_INLINE bool upb_Message_SetFloat(upb_Message* msg,
                                         const upb_MiniTableField* f,
                                         float value, upb_Arena* a);

UPB_API_INLINE bool upb_Message_SetInt32(upb_Message* msg,
                                         const upb_MiniTableField* f,
                                         int32_t value, upb_Arena* a);

UPB_API_INLINE bool upb_Message_SetInt64(upb_Message* msg,
                                         const upb_MiniTableField* f,
                                         int64_t value, upb_Arena* a);

// Unlike the other similarly-named setters, this function can only be
// called on base fields. Prefer upb_Message_SetBaseFieldMessage().
UPB_API_INLINE void upb_Message_SetMessage(upb_Message* msg,
                                           const upb_MiniTableField* f,
                                           upb_Message* value);

UPB_API_INLINE bool upb_Message_SetString(upb_Message* msg,
                                          const upb_MiniTableField* f,
                                          upb_StringView value, upb_Arena* a);

UPB_API_INLINE bool upb_Message_SetUInt32(upb_Message* msg,
                                          const upb_MiniTableField* f,
                                          uint32_t value, upb_Arena* a);

UPB_API_INLINE bool upb_Message_SetUInt64(upb_Message* msg,
                                          const upb_MiniTableField* f,
                                          uint64_t value, upb_Arena* a);

////////////////////////////////////////////////////////////////////////////////

UPB_API_INLINE void* upb_Message_ResizeArrayUninitialized(
    upb_Message* msg, const upb_MiniTableField* f, size_t size,
    upb_Arena* arena);

UPB_API_INLINE uint32_t upb_Message_WhichOneofFieldNumber(
    const upb_Message* message, const upb_MiniTableField* oneof_field);

// For a field `f` which is in a oneof, return the field of that
// oneof that is actually set (or NULL if none).
UPB_API_INLINE const upb_MiniTableField* upb_Message_WhichOneof(
    const upb_Message* msg, const upb_MiniTable* m,
    const upb_MiniTableField* f);

// Updates a map entry given an entry message.
bool upb_Message_SetMapEntry(upb_Map* map, const upb_MiniTable* mini_table,
                             const upb_MiniTableField* field,
                             upb_Message* map_entry_message, upb_Arena* arena);

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif  // UPB_MESSAGE_ACCESSORS_H_

// These functions are only used by generated code.

#ifndef UPB_MESSAGE_MAP_GENCODE_UTIL_H_
#define UPB_MESSAGE_MAP_GENCODE_UTIL_H_

// This header file is referenced by multiple files. Leave it empty.
// TODO: b/399481227 - Remove this header file, after all the references are
// cleaned up.
#endif /* UPB_MESSAGE_MAP_GENCODE_UTIL_H_ */

#ifndef UPB_MINI_TABLE_DECODE_H_
#define UPB_MINI_TABLE_DECODE_H_

#include <stddef.h>


#ifndef UPB_BASE_STATUS_H_
#define UPB_BASE_STATUS_H_

#include <stdarg.h>

// Must be last.

#define _kUpb_Status_MaxMessage 511

typedef struct {
  bool ok;
  char msg[_kUpb_Status_MaxMessage];  // Error message; NULL-terminated.
} upb_Status;

#ifdef __cplusplus
extern "C" {
#endif

UPB_API const char* upb_Status_ErrorMessage(const upb_Status* status);
UPB_API bool upb_Status_IsOk(const upb_Status* status);

// These are no-op if |status| is NULL.
UPB_API void upb_Status_Clear(upb_Status* status);
void upb_Status_SetErrorMessage(upb_Status* status, const char* msg);
void upb_Status_SetErrorFormat(upb_Status* status, const char* fmt, ...)
    UPB_PRINTF(2, 3);
void upb_Status_VSetErrorFormat(upb_Status* status, const char* fmt,
                                va_list args) UPB_PRINTF(2, 0);
void upb_Status_VAppendErrorFormat(upb_Status* status, const char* fmt,
                                   va_list args) UPB_PRINTF(2, 0);

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /* UPB_BASE_STATUS_H_ */

#ifndef UPB_MINI_TABLE_SUB_H_
#define UPB_MINI_TABLE_SUB_H_


// Must be last.

typedef union upb_MiniTableSub upb_MiniTableSub;

#ifdef __cplusplus
extern "C" {
#endif

// Constructors

UPB_API_INLINE upb_MiniTableSub
upb_MiniTableSub_FromEnum(const upb_MiniTableEnum* subenum);

UPB_API_INLINE upb_MiniTableSub
upb_MiniTableSub_FromMessage(const upb_MiniTable* submsg);

// Getters

UPB_API_INLINE const upb_MiniTableEnum* upb_MiniTableSub_Enum(
    upb_MiniTableSub sub);

UPB_API_INLINE const upb_MiniTable* upb_MiniTableSub_Message(
    upb_MiniTableSub sub);

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /* UPB_MINI_TABLE_SUB_H_ */

// Export the newer headers, for legacy users.  New users should include the
// more specific headers directly.
// IWYU pragma: begin_exports

#ifndef UPB_MINI_DESCRIPTOR_BUILD_ENUM_H_
#define UPB_MINI_DESCRIPTOR_BUILD_ENUM_H_


// Must be last.

#ifdef __cplusplus
extern "C" {
#endif

// Builds a upb_MiniTableEnum from an enum mini descriptor.
// The mini descriptor must be for an enum, not a message.
UPB_API upb_MiniTableEnum* upb_MiniTableEnum_Build(const char* data, size_t len,
                                                   upb_Arena* arena,
                                                   upb_Status* status);

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif  // UPB_MINI_DESCRIPTOR_BUILD_ENUM_H_

// Functions for linking MiniTables together once they are built from a
// MiniDescriptor.
//
// These functions have names like upb_MiniTable_Link() because they operate on
// MiniTables.  We put them here, rather than in the mini_table/ directory,
// because they are only needed when building MiniTables from MiniDescriptors.
// The interfaces in mini_table/ assume that MiniTables are immutable.

#ifndef UPB_MINI_DESCRIPTOR_LINK_H_
#define UPB_MINI_DESCRIPTOR_LINK_H_


// Must be last.

#ifdef __cplusplus
extern "C" {
#endif

// Links a sub-message field to a MiniTable for that sub-message. If a
// sub-message field is not linked, it will be treated as an unknown field
// during parsing, and setting the field will not be allowed. It is possible
// to link the message field later, at which point it will no longer be treated
// as unknown. However there is no synchronization for this operation, which
// means parallel mutation requires external synchronization.
// Returns success/failure.
UPB_API bool upb_MiniTable_SetSubMessage(upb_MiniTable* table,
                                         upb_MiniTableField* field,
                                         const upb_MiniTable* sub);

// Links an enum field to a MiniTable for that enum.
// All enum fields must be linked prior to parsing.
// Returns success/failure.
UPB_API bool upb_MiniTable_SetSubEnum(upb_MiniTable* table,
                                      upb_MiniTableField* field,
                                      const upb_MiniTableEnum* sub);

// Returns a list of fields that require linking at runtime, to connect the
// MiniTable to its sub-messages and sub-enums.  The list of fields will be
// written to the `subs` array, which must have been allocated by the caller
// and must be large enough to hold a list of all fields in the message.
//
// The order of the fields returned by this function is significant: it matches
// the order expected by upb_MiniTable_Link() below.
//
// The return value packs the sub-message count and sub-enum count into a single
// integer like so:
//  return (msg_count << 16) | enum_count;
UPB_API uint32_t upb_MiniTable_GetSubList(const upb_MiniTable* mt,
                                          const upb_MiniTableField** subs);

// Links a message to its sub-messages and sub-enums.  The caller must pass
// arrays of sub-tables and sub-enums, in the same length and order as is
// returned by upb_MiniTable_GetSubList() above.  However, individual elements
// of the sub_tables may be NULL if those sub-messages were tree shaken.
//
// Returns false if either array is too short, or if any of the tables fails
// to link.
UPB_API bool upb_MiniTable_Link(upb_MiniTable* mt,
                                const upb_MiniTable** sub_tables,
                                size_t sub_table_count,
                                const upb_MiniTableEnum** sub_enums,
                                size_t sub_enum_count);

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif  // UPB_MINI_DESCRIPTOR_LINK_H_
// IWYU pragma: end_exports

// Must be last.

typedef enum {
  kUpb_MiniTablePlatform_32Bit,
  kUpb_MiniTablePlatform_64Bit,
  kUpb_MiniTablePlatform_Native =
      UPB_SIZE(kUpb_MiniTablePlatform_32Bit, kUpb_MiniTablePlatform_64Bit),
} upb_MiniTablePlatform;

#ifdef __cplusplus
extern "C" {
#endif

// Builds a mini table from the data encoded in the buffer [data, len]. If any
// errors occur, returns NULL and sets a status message. In the success case,
// the caller must call upb_MiniTable_SetSub*() for all message or proto2 enum
// fields to link the table to the appropriate sub-tables.
upb_MiniTable* _upb_MiniTable_Build(const char* data, size_t len,
                                    upb_MiniTablePlatform platform,
                                    upb_Arena* arena, upb_Status* status);

UPB_API_INLINE upb_MiniTable* upb_MiniTable_Build(const char* data, size_t len,
                                                  upb_Arena* arena,
                                                  upb_Status* status) {
  return _upb_MiniTable_Build(data, len, kUpb_MiniTablePlatform_Native, arena,
                              status);
}

// Initializes a MiniTableExtension buffer that has already been allocated.
// This is needed by upb_FileDef and upb_MessageDef, which allocate all of the
// extensions together in a single contiguous array.
const char* _upb_MiniTableExtension_Init(const char* data, size_t len,
                                         upb_MiniTableExtension* ext,
                                         const upb_MiniTable* extendee,
                                         upb_MiniTableSub sub,
                                         upb_MiniTablePlatform platform,
                                         upb_Status* status);

UPB_API_INLINE const char* upb_MiniTableExtension_Init(
    const char* data, size_t len, upb_MiniTableExtension* ext,
    const upb_MiniTable* extendee, upb_MiniTableSub sub, upb_Status* status) {
  return _upb_MiniTableExtension_Init(data, len, ext, extendee, sub,
                                      kUpb_MiniTablePlatform_Native, status);
}

UPB_API upb_MiniTableExtension* _upb_MiniTableExtension_Build(
    const char* data, size_t len, const upb_MiniTable* extendee,
    upb_MiniTableSub sub, upb_MiniTablePlatform platform, upb_Arena* arena,
    upb_Status* status);

UPB_API_INLINE upb_MiniTableExtension* upb_MiniTableExtension_Build(
    const char* data, size_t len, const upb_MiniTable* extendee,
    upb_Arena* arena, upb_Status* status) {
  upb_MiniTableSub sub = upb_MiniTableSub_FromMessage(NULL);
  return _upb_MiniTableExtension_Build(
      data, len, extendee, sub, kUpb_MiniTablePlatform_Native, arena, status);
}

UPB_API_INLINE upb_MiniTableExtension* upb_MiniTableExtension_BuildMessage(
    const char* data, size_t len, const upb_MiniTable* extendee,
    const upb_MiniTable* submsg, upb_Arena* arena, upb_Status* status) {
  upb_MiniTableSub sub = upb_MiniTableSub_FromMessage(submsg);
  return _upb_MiniTableExtension_Build(
      data, len, extendee, sub, kUpb_MiniTablePlatform_Native, arena, status);
}

UPB_API_INLINE upb_MiniTableExtension* upb_MiniTableExtension_BuildEnum(
    const char* data, size_t len, const upb_MiniTable* extendee,
    const upb_MiniTableEnum* subenum, upb_Arena* arena, upb_Status* status) {
  upb_MiniTableSub sub = upb_MiniTableSub_FromEnum(subenum);
  return _upb_MiniTableExtension_Build(
      data, len, extendee, sub, kUpb_MiniTablePlatform_Native, arena, status);
}

// Like upb_MiniTable_Build(), but the user provides a buffer of layout data so
// it can be reused from call to call, avoiding repeated
// upb_grealloc()/upb_gfree().
//
// The caller owns `*buf` both before and after the call, and must upb_gfree()
// it when it is no longer in use.  The function will upb_grealloc() `*buf` as
// necessary, updating `*size` accordingly.
upb_MiniTable* upb_MiniTable_BuildWithBuf(const char* data, size_t len,
                                          upb_MiniTablePlatform platform,
                                          upb_Arena* arena, void** buf,
                                          size_t* buf_size, upb_Status* status);

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /* UPB_MINI_TABLE_DECODE_H_ */

#ifndef UPB_MINI_TABLE_EXTENSION_REGISTRY_H_
#define UPB_MINI_TABLE_EXTENSION_REGISTRY_H_

#include <stddef.h>
#include <stdint.h>


// Must be last.

#ifdef __cplusplus
extern "C" {
#endif

/* Extension registry: a dynamic data structure that stores a map of:
 *   (upb_MiniTable, number) -> extension info
 *
 * upb_decode() uses upb_ExtensionRegistry to look up extensions while parsing
 * binary format.
 *
 * upb_ExtensionRegistry is part of the mini-table (msglayout) family of
 * objects. Like all mini-table objects, it is suitable for reflection-less
 * builds that do not want to expose names into the binary.
 *
 * Unlike most mini-table types, upb_ExtensionRegistry requires dynamic memory
 * allocation and dynamic initialization:
 * * If reflection is being used, then upb_DefPool will construct an appropriate
 *   upb_ExtensionRegistry automatically.
 * * For a mini-table only build, the user must manually construct the
 *   upb_ExtensionRegistry and populate it with all of the extensions the user
 * cares about.
 * * A third alternative is to manually unpack relevant extensions after the
 *   main parse is complete, similar to how Any works. This is perhaps the
 *   nicest solution from the perspective of reducing dependencies, avoiding
 *   dynamic memory allocation, and avoiding the need to parse uninteresting
 *   extensions.  The downsides are:
 *     (1) parse errors are not caught during the main parse
 *     (2) the CPU hit of parsing comes during access, which could cause an
 *         undesirable stutter in application performance.
 *
 * Users cannot directly get or put into this map. Users can only add the
 * extensions from a generated module and pass the extension registry to the
 * binary decoder.
 *
 * A upb_DefPool provides a upb_ExtensionRegistry, so any users who use
 * reflection do not need to populate a upb_ExtensionRegistry directly.
 */

typedef struct upb_ExtensionRegistry upb_ExtensionRegistry;

typedef enum {
  kUpb_ExtensionRegistryStatus_Ok = 0,
  kUpb_ExtensionRegistryStatus_DuplicateEntry = 1,
  kUpb_ExtensionRegistryStatus_OutOfMemory = 2,
  kUpb_ExtensionRegistryStatus_InvalidExtension = 3,
} upb_ExtensionRegistryStatus;

// Creates a upb_ExtensionRegistry in the given arena.
// The arena must outlive any use of the extreg.
UPB_API upb_ExtensionRegistry* upb_ExtensionRegistry_New(upb_Arena* arena);

UPB_API upb_ExtensionRegistryStatus upb_ExtensionRegistry_Add(
    upb_ExtensionRegistry* r, const upb_MiniTableExtension* e);

// Adds the given extension info for the array |e| of size |count| into the
// registry. If there are any errors, the entire array is backed out.
// The extensions must outlive the registry.
// Possible errors include OOM or an extension number that already exists.
upb_ExtensionRegistryStatus upb_ExtensionRegistry_AddArray(
    upb_ExtensionRegistry* r, const upb_MiniTableExtension** e, size_t count);

#ifdef UPB_LINKARR_DECLARE

// Adds all extensions linked into the binary into the registry.  The set of
// linked extensions is assembled by the linker using linker arrays.  This
// will likely not work properly if the extensions are split across multiple
// shared libraries.
//
// Returns true if all extensions were added successfully, false on out of
// memory or if any extensions were already present.
//
// This API is currently not available on MSVC (though it *is* available on
// Windows using clang-cl).
UPB_API bool upb_ExtensionRegistry_AddAllLinkedExtensions(
    upb_ExtensionRegistry* r);

#endif  // UPB_LINKARR_DECLARE

// Looks up the extension (if any) defined for message type |t| and field
// number |num|. Returns the extension if found, otherwise NULL.
UPB_API const upb_MiniTableExtension* upb_ExtensionRegistry_Lookup(
    const upb_ExtensionRegistry* r, const upb_MiniTable* t, uint32_t num);

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /* UPB_MINI_TABLE_EXTENSION_REGISTRY_H_ */

#ifndef UPB_MINI_TABLE_FILE_H_
#define UPB_MINI_TABLE_FILE_H_


#ifndef UPB_MINI_TABLE_INTERNAL_FILE_H_
#define UPB_MINI_TABLE_INTERNAL_FILE_H_

// Must be last.

struct upb_MiniTableFile {
  const struct upb_MiniTable** UPB_PRIVATE(msgs);
  const struct upb_MiniTableEnum** UPB_PRIVATE(enums);
  const struct upb_MiniTableExtension** UPB_PRIVATE(exts);
  int UPB_PRIVATE(msg_count);
  int UPB_PRIVATE(enum_count);
  int UPB_PRIVATE(ext_count);
};

#ifdef __cplusplus
extern "C" {
#endif

UPB_API_INLINE int upb_MiniTableFile_EnumCount(
    const struct upb_MiniTableFile* f) {
  return f->UPB_PRIVATE(enum_count);
}

UPB_API_INLINE int upb_MiniTableFile_ExtensionCount(
    const struct upb_MiniTableFile* f) {
  return f->UPB_PRIVATE(ext_count);
}

UPB_API_INLINE int upb_MiniTableFile_MessageCount(
    const struct upb_MiniTableFile* f) {
  return f->UPB_PRIVATE(msg_count);
}

UPB_API_INLINE const struct upb_MiniTableEnum* upb_MiniTableFile_Enum(
    const struct upb_MiniTableFile* f, int i) {
  UPB_ASSERT(i < f->UPB_PRIVATE(enum_count));
  return f->UPB_PRIVATE(enums)[i];
}

UPB_API_INLINE const struct upb_MiniTableExtension* upb_MiniTableFile_Extension(
    const struct upb_MiniTableFile* f, int i) {
  UPB_ASSERT(i < f->UPB_PRIVATE(ext_count));
  return f->UPB_PRIVATE(exts)[i];
}

UPB_API_INLINE const struct upb_MiniTable* upb_MiniTableFile_Message(
    const struct upb_MiniTableFile* f, int i) {
  UPB_ASSERT(i < f->UPB_PRIVATE(msg_count));
  return f->UPB_PRIVATE(msgs)[i];
}

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /* UPB_MINI_TABLE_INTERNAL_FILE_H_ */

// Must be last.

typedef struct upb_MiniTableFile upb_MiniTableFile;

#ifdef __cplusplus
extern "C" {
#endif

UPB_API_INLINE const upb_MiniTableEnum* upb_MiniTableFile_Enum(
    const upb_MiniTableFile* f, int i);

UPB_API_INLINE int upb_MiniTableFile_EnumCount(const upb_MiniTableFile* f);

UPB_API_INLINE const upb_MiniTableExtension* upb_MiniTableFile_Extension(
    const upb_MiniTableFile* f, int i);

UPB_API_INLINE int upb_MiniTableFile_ExtensionCount(const upb_MiniTableFile* f);

UPB_API_INLINE const upb_MiniTable* upb_MiniTableFile_Message(
    const upb_MiniTableFile* f, int i);

UPB_API_INLINE int upb_MiniTableFile_MessageCount(const upb_MiniTableFile* f);

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /* UPB_MINI_TABLE_FILE_H_ */

// upb_decode: parsing into a upb_Message using a upb_MiniTable.

#ifndef UPB_WIRE_DECODE_H_
#define UPB_WIRE_DECODE_H_

#include <stddef.h>
#include <stdint.h>


// Must be last.

#ifdef __cplusplus
extern "C" {
#endif

// LINT.IfChange
enum {
  /* If set, strings and unknown fields will alias the input buffer instead of
   * copying into the arena. */
  kUpb_DecodeOption_AliasString = 1,

  /* If set, the parse will return failure if any message is missing any
   * required fields when the message data ends.  The parse will still continue,
   * and the failure will only be reported at the end.
   *
   * IMPORTANT CAVEATS:
   *
   * 1. This can throw a false positive failure if an incomplete message is seen
   *    on the wire but is later completed when the sub-message occurs again.
   *    For this reason, a second pass is required to verify a failure, to be
   *    truly robust.
   *
   * 2. This can return a false success if you are decoding into a message that
   *    already has some sub-message fields present.  If the sub-message does
   *    not occur in the binary payload, we will never visit it and discover the
   *    incomplete sub-message.  For this reason, this check is only useful for
   *    implementing ParseFromString() semantics.  For MergeFromString(), a
   *    post-parse validation step will always be necessary. */
  kUpb_DecodeOption_CheckRequired = 2,

  /* EXPERIMENTAL:
   *
   * If set, the parser will allow parsing of sub-message fields that were not
   * previously linked using upb_MiniTable_SetSubMessage().  The data will be
   * parsed into an internal "empty" message type that cannot be accessed
   * directly, but can be later promoted into the true message type if the
   * sub-message fields are linked at a later time.
   *
   * Users should set this option if they intend to perform dynamic tree shaking
   * and promoting using the interfaces in message/promote.h.  If this option is
   * enabled, it is important that the resulting messages are only accessed by
   * code that is aware of promotion rules:
   *
   * 1. Message pointers in upb_Message, upb_Array, and upb_Map are represented
   *    by a tagged pointer upb_TaggedMessagePointer.  The tag indicates whether
   *    the message uses the internal "empty" type.
   *
   * 2. Any code *reading* these message pointers must test whether the "empty"
   *    tag bit is set, using the interfaces in mini_table/types.h.  However
   *    writing of message pointers should always use plain upb_Message*, since
   *    users are not allowed to create "empty" messages.
   *
   * 3. It is always safe to test whether a field is present or test the array
   *    length; these interfaces will reflect that empty messages are present,
   *    even though their data cannot be accessed without promoting first.
   *
   * 4. If a message pointer is indeed tagged as empty, the message may not be
   *    accessed directly, only promoted through the interfaces in
   *    message/promote.h.
   *
   * 5. Tagged/empty messages may never be created by the user.  They may only
   *    be created by the parser or the message-copying logic in message/copy.h.
   */
  kUpb_DecodeOption_ExperimentalAllowUnlinked = 4,

  /* EXPERIMENTAL:
   *
   * If set, decoding will enforce UTF-8 validation for string fields, even for
   * proto2 or fields with `features.utf8_validation = NONE`. Normally, only
   * proto3 string fields will be validated for UTF-8. Decoding will return
   * kUpb_DecodeStatus_BadUtf8 for non-UTF-8 strings, which is the same behavior
   * as non-UTF-8 proto3 string fields.
   */
  kUpb_DecodeOption_AlwaysValidateUtf8 = 8,

  /* EXPERIMENTAL:
   *
   * If set, the fasttable decoder will not be used. */
  kUpb_DecodeOption_DisableFastTable = 16,
};
// LINT.ThenChange(//depot/google3/third_party/protobuf/rust/upb.rs:decode_status)

UPB_INLINE uint32_t upb_DecodeOptions_MaxDepth(uint16_t depth) {
  return (uint32_t)depth << 16;
}

uint16_t upb_DecodeOptions_GetEffectiveMaxDepth(uint32_t options);

// Enforce an upper bound on recursion depth.
UPB_INLINE int upb_Decode_LimitDepth(uint32_t decode_options, uint32_t limit) {
  uint32_t max_depth = upb_DecodeOptions_GetEffectiveMaxDepth(decode_options);
  if (max_depth > limit) max_depth = limit;
  return upb_DecodeOptions_MaxDepth(max_depth) | (decode_options & 0xffff);
}

// LINT.IfChange
typedef enum {
  kUpb_DecodeStatus_Ok = 0,
  kUpb_DecodeStatus_Malformed = 1,    // Wire format was corrupt
  kUpb_DecodeStatus_OutOfMemory = 2,  // Arena alloc failed
  kUpb_DecodeStatus_BadUtf8 = 3,      // String field had bad UTF-8
  kUpb_DecodeStatus_MaxDepthExceeded =
      4,  // Exceeded upb_DecodeOptions_MaxDepth

  // kUpb_DecodeOption_CheckRequired failed (see above), but the parse otherwise
  // succeeded.
  kUpb_DecodeStatus_MissingRequired = 5,

  // Unlinked sub-message field was present, but
  // kUpb_DecodeOptions_ExperimentalAllowUnlinked was not specified in the list
  // of options.
  kUpb_DecodeStatus_UnlinkedSubMessage = 6,
} upb_DecodeStatus;
// LINT.ThenChange(//depot/google3/third_party/protobuf/rust/upb.rs:decode_status)

UPB_API upb_DecodeStatus upb_Decode(const char* buf, size_t size,
                                    upb_Message* msg, const upb_MiniTable* mt,
                                    const upb_ExtensionRegistry* extreg,
                                    int options, upb_Arena* arena);

// Same as upb_Decode but with a varint-encoded length prepended.
// On success 'num_bytes_read' will be set to the how many bytes were read,
// on failure the contents of num_bytes_read is undefined.
UPB_API upb_DecodeStatus upb_DecodeLengthPrefixed(
    const char* buf, size_t size, upb_Message* msg, size_t* num_bytes_read,
    const upb_MiniTable* mt, const upb_ExtensionRegistry* extreg, int options,
    upb_Arena* arena);

// For testing: decode with tracing.
UPB_API upb_DecodeStatus upb_DecodeWithTrace(
    const char* buf, size_t size, upb_Message* msg, const upb_MiniTable* mt,
    const upb_ExtensionRegistry* extreg, int options, upb_Arena* arena,
    char* trace_buf, size_t trace_size);

// Utility function for wrapper languages to get an error string from a
// upb_DecodeStatus.
UPB_API const char* upb_DecodeStatus_String(upb_DecodeStatus status);
#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /* UPB_WIRE_DECODE_H_ */

// upb_Encode: parsing from a upb_Message using a upb_MiniTable.

#ifndef UPB_WIRE_ENCODE_H_
#define UPB_WIRE_ENCODE_H_

#include <stddef.h>
#include <stdint.h>


// Must be last.

#ifdef __cplusplus
extern "C" {
#endif

enum {
  /* If set, the results of serializing will be deterministic across all
   * instances of this binary. There are no guarantees across different
   * binary builds.
   *
   * If your proto contains maps, the encoder will need to malloc()/free()
   * memory during encode. */
  kUpb_EncodeOption_Deterministic = 1,

  // When set, unknown fields are not encoded.
  kUpb_EncodeOption_SkipUnknown = 2,

  // When set, the encode will fail if any required fields are missing.
  kUpb_EncodeOption_CheckRequired = 4,
};

// LINT.IfChange
typedef enum {
  kUpb_EncodeStatus_Ok = 0,
  kUpb_EncodeStatus_OutOfMemory = 1,  // Arena alloc failed
  kUpb_EncodeStatus_MaxDepthExceeded = 2,

  // One or more required fields are missing. Only returned if
  // kUpb_EncodeOption_CheckRequired is set.
  kUpb_EncodeStatus_MissingRequired = 3,
} upb_EncodeStatus;
// LINT.ThenChange(//depot/google3/third_party/protobuf/rust/upb.rs:encode_status)

UPB_INLINE uint32_t upb_EncodeOptions_MaxDepth(uint16_t depth) {
  return (uint32_t)depth << 16;
}

uint16_t upb_EncodeOptions_GetEffectiveMaxDepth(uint32_t options);

// Enforce an upper bound on recursion depth.
UPB_INLINE int upb_Encode_LimitDepth(uint32_t encode_options, uint32_t limit) {
  uint32_t max_depth = upb_EncodeOptions_GetEffectiveMaxDepth(encode_options);
  if (max_depth > limit) max_depth = limit;
  return upb_EncodeOptions_MaxDepth(max_depth) | (encode_options & 0xffff);
}

UPB_API upb_EncodeStatus upb_Encode(const upb_Message* msg,
                                    const upb_MiniTable* l, int options,
                                    upb_Arena* arena, char** buf, size_t* size);

// Encodes the message prepended by a varint of the serialized length.
UPB_API upb_EncodeStatus upb_EncodeLengthPrefixed(const upb_Message* msg,
                                                  const upb_MiniTable* l,
                                                  int options, upb_Arena* arena,
                                                  char** buf, size_t* size);
// Utility function for wrapper languages to get an error string from a
// upb_EncodeStatus.
UPB_API const char* upb_EncodeStatus_String(upb_EncodeStatus status);

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /* UPB_WIRE_ENCODE_H_ */

#ifndef UPB_BASE_INTERNAL_LOG2_H_
#define UPB_BASE_INTERNAL_LOG2_H_

// Must be last.

#ifdef __cplusplus
extern "C" {
#endif

UPB_INLINE int upb_Log2Ceiling(int x) {
  if (x <= 1) return 0;
#ifdef __GNUC__
  return 32 - __builtin_clz(x - 1);
#else
  int lg2 = 0;
  while ((1 << lg2) < x) lg2++;
  return lg2;
#endif
}

UPB_INLINE int upb_RoundUpToPowerOfTwo(int x) {
  return 1 << upb_Log2Ceiling(x);
}

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /* UPB_BASE_INTERNAL_LOG2_H_ */

#ifndef UPB_PORT_ATOMIC_H_
#define UPB_PORT_ATOMIC_H_


#ifdef UPB_USE_C11_ATOMICS

// IWYU pragma: begin_exports
#include <stdatomic.h>
#include <stdbool.h>
// IWYU pragma: end_exports

#define upb_Atomic_Init(addr, val) atomic_init(addr, val)
#define upb_Atomic_Load(addr, order) atomic_load_explicit(addr, order)
#define upb_Atomic_Store(addr, val, order) \
  atomic_store_explicit(addr, val, order)
#define upb_Atomic_Exchange(addr, val, order) \
  atomic_exchange_explicit(addr, val, order)
#define upb_Atomic_CompareExchangeStrong(addr, expected, desired,      \
                                         success_order, failure_order) \
  atomic_compare_exchange_strong_explicit(addr, expected, desired,     \
                                          success_order, failure_order)
#define upb_Atomic_CompareExchangeWeak(addr, expected, desired, success_order, \
                                       failure_order)                          \
  atomic_compare_exchange_weak_explicit(addr, expected, desired,               \
                                        success_order, failure_order)

#elif defined(UPB_USE_MSC_ATOMICS)
#include <intrin.h>
#include <stdbool.h>
#include <stdint.h>

#define upb_Atomic_Init(addr, val) (*(addr) = val)

#if defined(_WIN64)
// MSVC, without C11 atomics, does not have any way in pure C to force
// load-acquire store-release behavior, so we hack it with exchanges.
#pragma intrinsic(_InterlockedExchange64)
#define upb_Atomic_Store(addr, val, order) \
  (void)_InterlockedExchange64((uint64_t volatile *)addr, (uint64_t)val)

#pragma intrinsic(_InterlockedCompareExchange64)
static uintptr_t upb_Atomic_LoadMsc(uint64_t volatile *addr) {
  // Compare exchange with an unlikely value reduces the risk of a spurious
  // (but harmless) store
  return _InterlockedCompareExchange64(addr, 0xDEADC0DEBAADF00D,
                                       0xDEADC0DEBAADF00D);
}
// If _Generic is available, use it to avoid emitting a "'uintptr_t' differs in
// levels of indirection from 'void *'" or -Wint-conversion compiler warning.
#if __STDC_VERSION__ >= 201112L
#define upb_Atomic_Load(addr, order)                           \
  _Generic(addr,                                               \
      UPB_ATOMIC(uintptr_t) *: upb_Atomic_LoadMsc(             \
                                 (uint64_t volatile *)(addr)), \
      default: (void *)upb_Atomic_LoadMsc((uint64_t volatile *)(addr)))

#define upb_Atomic_Exchange(addr, val, order)                                 \
  _Generic(addr,                                                              \
      UPB_ATOMIC(uintptr_t) *: _InterlockedExchange64(                        \
                                 (uint64_t volatile *)(addr), (uint64_t)val), \
      default: (void *)_InterlockedExchange64((uint64_t volatile *)addr,      \
                                              (uint64_t)val))
#else
// Compare exchange with an unlikely value reduces the risk of a spurious
// (but harmless) store
#define upb_Atomic_Load(addr, order) \
  (void *)upb_Atomic_LoadMsc((uint64_t volatile *)(addr))

#define upb_Atomic_Exchange(addr, val, order) \
  (void *)_InterlockedExchange64((uint64_t volatile *)addr, (uint64_t)val)
#endif

#pragma intrinsic(_InterlockedCompareExchange64)
static bool upb_Atomic_CompareExchangeMscP(uint64_t volatile *addr,
                                           uint64_t *expected,
                                           uint64_t desired) {
  uint64_t expect_val = *expected;
  uint64_t actual_val =
      _InterlockedCompareExchange64(addr, desired, expect_val);
  if (expect_val != actual_val) {
    *expected = actual_val;
    return false;
  }
  return true;
}

#define upb_Atomic_CompareExchangeStrong(addr, expected, desired,      \
                                         success_order, failure_order) \
  upb_Atomic_CompareExchangeMscP((uint64_t volatile *)addr,            \
                                 (uint64_t *)expected, (uint64_t)desired)

#define upb_Atomic_CompareExchangeWeak(addr, expected, desired, success_order, \
                                       failure_order)                          \
  upb_Atomic_CompareExchangeMscP((uint64_t volatile *)addr,                    \
                                 (uint64_t *)expected, (uint64_t)desired)

#else  // 32 bit pointers
#pragma intrinsic(_InterlockedExchange)
#define upb_Atomic_Store(addr, val, order) \
  (void)_InterlockedExchange((uint32_t volatile *)addr, (uint32_t)val)

#pragma intrinsic(_InterlockedCompareExchange)
static uintptr_t upb_Atomic_LoadMsc(uint32_t volatile *addr) {
  // Compare exchange with an unlikely value reduces the risk of a spurious
  // (but harmless) store
  return _InterlockedCompareExchange(addr, 0xDEADC0DE, 0xDEADC0DE);
}
// If _Generic is available, use it to avoid emitting 'uintptr_t' differs in
// levels of indirection from 'void *'
#if __STDC_VERSION__ >= 201112L
#define upb_Atomic_Load(addr, order)                           \
  _Generic(addr,                                               \
      UPB_ATOMIC(uintptr_t) *: upb_Atomic_LoadMsc(             \
                                 (uint32_t volatile *)(addr)), \
      default: (void *)upb_Atomic_LoadMsc((uint32_t volatile *)(addr)))

#define upb_Atomic_Exchange(addr, val, order)                                 \
  _Generic(addr,                                                              \
      UPB_ATOMIC(uintptr_t) *: _InterlockedExchange(                          \
                                 (uint32_t volatile *)(addr), (uint32_t)val), \
      default: (void *)_InterlockedExchange64((uint32_t volatile *)addr,      \
                                              (uint32_t)val))
#else
#define upb_Atomic_Load(addr, order) \
  (void *)upb_Atomic_LoadMsc((uint32_t volatile *)(addr))

#define upb_Atomic_Exchange(addr, val, order) \
  (void *)_InterlockedExchange((uint32_t volatile *)addr, (uint32_t)val)
#endif

#pragma intrinsic(_InterlockedCompareExchange)
static bool upb_Atomic_CompareExchangeMscP(uint32_t volatile *addr,
                                           uint32_t *expected,
                                           uint32_t desired) {
  uint32_t expect_val = *expected;
  uint32_t actual_val = _InterlockedCompareExchange(addr, desired, expect_val);
  if (expect_val != actual_val) {
    *expected = actual_val;
    return false;
  }
  return true;
}

#define upb_Atomic_CompareExchangeStrong(addr, expected, desired,      \
                                         success_order, failure_order) \
  upb_Atomic_CompareExchangeMscP((uint32_t volatile *)addr,            \
                                 (uint32_t *)expected, (uint32_t)desired)

#define upb_Atomic_CompareExchangeWeak(addr, expected, desired, success_order, \
                                       failure_order)                          \
  upb_Atomic_CompareExchangeMscP((uint32_t volatile *)addr,                    \
                                 (uint32_t *)expected, (uint32_t)desired)
#endif

#else  // No atomics

#if !defined(UPB_SUPPRESS_MISSING_ATOMICS)
// NOLINTNEXTLINE
#error Your compiler does not support atomic instructions, which UPB uses. If you do not use UPB on multiple threads, you can suppress this error by defining UPB_SUPPRESS_MISSING_ATOMICS.
#endif

#include <string.h>

#define upb_Atomic_Init(addr, val) (*addr = val)
#define upb_Atomic_Load(addr, order) (*addr)
#define upb_Atomic_Store(addr, val, order) (*(addr) = val)

UPB_INLINE void* _upb_NonAtomic_Exchange(void* addr, void* value) {
  void* old;
  memcpy(&old, addr, sizeof(value));
  memcpy(addr, &value, sizeof(value));
  return old;
}

#define upb_Atomic_Exchange(addr, val, order) _upb_NonAtomic_Exchange(addr, val)

// `addr` and `expected` are logically double pointers.
UPB_INLINE bool _upb_NonAtomic_CompareExchangeStrongP(void* addr,
                                                      void* expected,
                                                      void* desired) {
  if (memcmp(addr, expected, sizeof(desired)) == 0) {
    memcpy(addr, &desired, sizeof(desired));
    return true;
  } else {
    memcpy(expected, addr, sizeof(desired));
    return false;
  }
}

#define upb_Atomic_CompareExchangeStrong(addr, expected, desired,      \
                                         success_order, failure_order) \
  _upb_NonAtomic_CompareExchangeStrongP((void*)addr, (void*)expected,  \
                                        (void*)desired)
#define upb_Atomic_CompareExchangeWeak(addr, expected, desired, success_order, \
                                       failure_order)                          \
  upb_Atomic_CompareExchangeStrong(addr, expected, desired, 0, 0)

#endif


#endif  // UPB_PORT_ATOMIC_H_

#ifndef UPB_MESSAGE_COMPARE_H_
#define UPB_MESSAGE_COMPARE_H_

#include <stddef.h>


// Must be last.

enum {
  // If set, upb_Message_IsEqual() will attempt to compare unknown fields.
  // By its very nature this comparison is inexact.
  kUpb_CompareOption_IncludeUnknownFields = (1 << 0)
};

#ifdef __cplusplus
extern "C" {
#endif

// Returns true if no known fields or extensions are set in the message.
UPB_API bool upb_Message_IsEmpty(const upb_Message* msg,
                                 const upb_MiniTable* m);

UPB_API bool upb_Message_IsEqual(const upb_Message* msg1,
                                 const upb_Message* msg2,
                                 const upb_MiniTable* m, int options);

// If |ctype| is a message then |m| must point to its minitable.
UPB_API_INLINE bool upb_MessageValue_IsEqual(upb_MessageValue val1,
                                             upb_MessageValue val2,
                                             upb_CType ctype,
                                             const upb_MiniTable* m,
                                             int options) {
  switch (ctype) {
    case kUpb_CType_Bool:
      return val1.bool_val == val2.bool_val;

    case kUpb_CType_Float:
    case kUpb_CType_Int32:
    case kUpb_CType_UInt32:
    case kUpb_CType_Enum:
      return val1.int32_val == val2.int32_val;

    case kUpb_CType_Double:
    case kUpb_CType_Int64:
    case kUpb_CType_UInt64:
      return val1.int64_val == val2.int64_val;

    case kUpb_CType_String:
    case kUpb_CType_Bytes:
      return upb_StringView_IsEqual(val1.str_val, val2.str_val);

    case kUpb_CType_Message:
      return upb_Message_IsEqual(val1.msg_val, val2.msg_val, m, options);

    default:
      UPB_UNREACHABLE();
      return false;
  }
}

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif  // UPB_MESSAGE_COMPARE_H_

#ifndef UPB_MESSAGE_INTERNAL_COMPARE_UNKNOWN_H_
#define UPB_MESSAGE_INTERNAL_COMPARE_UNKNOWN_H_

#include <stddef.h>

// Must be last.

#ifdef __cplusplus
extern "C" {
#endif

// Returns true if unknown fields from the two messages are equal when sorted
// and varints are made canonical.
//
// This function is discouraged, as the comparison is inherently lossy without
// schema data:
//
//  1. We don't know whether delimited fields are sub-messages. Unknown
//     sub-messages will therefore not have their fields sorted and varints
//     canonicalized.
//  2. We don't know about oneof/non-repeated fields, which should semantically
//     discard every value except the last.

typedef enum {
  kUpb_UnknownCompareResult_Equal = 0,
  kUpb_UnknownCompareResult_NotEqual = 1,
  kUpb_UnknownCompareResult_OutOfMemory = 2,
  kUpb_UnknownCompareResult_MaxDepthExceeded = 3,
} upb_UnknownCompareResult;

upb_UnknownCompareResult UPB_PRIVATE(_upb_Message_UnknownFieldsAreEqual)(
    const upb_Message* msg1, const upb_Message* msg2, int max_depth);

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /* UPB_MESSAGE_INTERNAL_COMPARE_UNKNOWN_H_ */

#ifndef GOOGLE_UPB_UPB_MESSAGE_INTERNAL_ITERATOR_H__
#define GOOGLE_UPB_UPB_MESSAGE_INTERNAL_ITERATOR_H__

#include <stddef.h>
#include <stdint.h>


// Must be last.

#define kUpb_BaseField_Begin ((size_t)-1)
bool UPB_PRIVATE(_upb_Message_NextBaseField)(const upb_Message* msg,
                                             const upb_MiniTable* m,
                                             const upb_MiniTableField** out_f,
                                             upb_MessageValue* out_v,
                                             uintptr_t* iter);

#endif  // GOOGLE_UPB_UPB_MESSAGE_INTERNAL_ITERATOR_H__

#ifndef UPB_MESSAGE_COMPAT_H_
#define UPB_MESSAGE_COMPAT_H_

#include <stdint.h>


// Must be last.

// upb does not support mixing minitables from different sources but these
// functions are still used by some existing users so for now we make them
// available here. This may or may not change in the future so do not add
// them to new code.

#ifdef __cplusplus
extern "C" {
#endif

// Same as upb_Message_NextExtension but iterates in reverse wire order
bool upb_Message_NextExtensionReverse(const upb_Message* msg,
                                      const upb_MiniTableExtension** result,
                                      uintptr_t* iter);
// Returns the minitable with the given field number, or NULL on failure.
const upb_MiniTableExtension* upb_Message_FindExtensionByNumber(
    const upb_Message* msg, uint32_t field_number);

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /* UPB_MESSAGE_COMPAT_H_ */

#ifndef UPB_WIRE_EPS_COPY_INPUT_STREAM_H_
#define UPB_WIRE_EPS_COPY_INPUT_STREAM_H_

#include <stdint.h>
#include <string.h>


// Must be last.

#ifdef __cplusplus
extern "C" {
#endif

// The maximum number of bytes a single protobuf field can take up in the
// wire format.  We only want to do one bounds check per field, so the input
// stream guarantees that after upb_EpsCopyInputStream_IsDone() is called,
// the decoder can read this many bytes without performing another bounds
// check.  The stream will copy into a patch buffer as necessary to guarantee
// this invariant. Since tags can only be up to 5 bytes, and a max-length scalar
// field can be 10 bytes, only 15 is required; but sizing up to 16 permits more
// efficient fixed size copies.
#define kUpb_EpsCopyInputStream_SlopBytes 16

typedef struct {
  const char* end;        // Can read up to SlopBytes bytes beyond this.
  const char* limit_ptr;  // For bounds checks, = end + UPB_MIN(limit, 0)
  uintptr_t input_delta;  // Diff between the original input pointer and patch
  const char* buffer_start;  // Pointer to the original input buffer
  int limit;                 // Submessage limit relative to end
  bool error;                // To distinguish between EOF and error.
  bool aliasing;
#ifndef NDEBUG
  int guaranteed_bytes;
#endif
  // Allocate double the size of what's required; this permits a fixed-size copy
  // from the input buffer, regardless of how many bytes actually remain in the
  // input buffer.
  char patch[kUpb_EpsCopyInputStream_SlopBytes * 2];
} upb_EpsCopyInputStream;

// Returns true if the stream is in the error state. A stream enters the error
// state when the user reads past a limit (caught in IsDone()) or the
// ZeroCopyInputStream returns an error.
UPB_INLINE bool upb_EpsCopyInputStream_IsError(upb_EpsCopyInputStream* e) {
  return e->error;
}

typedef const char* upb_EpsCopyInputStream_BufferFlipCallback(
    upb_EpsCopyInputStream* e, const char* old_end, const char* new_start);

typedef const char* upb_EpsCopyInputStream_IsDoneFallbackFunc(
    upb_EpsCopyInputStream* e, const char* ptr, int overrun);

UPB_INLINE void UPB_PRIVATE(upb_EpsCopyInputStream_BoundsChecked)(
    upb_EpsCopyInputStream* e) {
#ifndef NDEBUG
  e->guaranteed_bytes = kUpb_EpsCopyInputStream_SlopBytes;
#endif
}

UPB_INLINE void UPB_PRIVATE(upb_EpsCopyInputStream_BoundsHit)(
    upb_EpsCopyInputStream* e) {
#ifndef NDEBUG
  e->guaranteed_bytes = 0;
#endif
}

// Signals the maximum number that the operation about to be performed may
// consume.
UPB_INLINE void UPB_PRIVATE(upb_EpsCopyInputStream_ConsumeBytes)(
    upb_EpsCopyInputStream* e, int n) {
#ifndef NDEBUG
  if (e) {
    UPB_ASSERT(e->guaranteed_bytes >= n);
    e->guaranteed_bytes -= n;
  }
#endif
}

// Initializes a upb_EpsCopyInputStream using the contents of the buffer
// [*ptr, size].  Updates `*ptr` as necessary to guarantee that at least
// kUpb_EpsCopyInputStream_SlopBytes are available to read.
UPB_INLINE void upb_EpsCopyInputStream_Init(upb_EpsCopyInputStream* e,
                                            const char** ptr, size_t size,
                                            bool enable_aliasing) {
  e->buffer_start = *ptr;
  if (size <= kUpb_EpsCopyInputStream_SlopBytes) {
    memset(&e->patch, 0, 32);
    if (size) memcpy(&e->patch, *ptr, size);
    e->input_delta = (uintptr_t)*ptr - (uintptr_t)e->patch;
    *ptr = e->patch;
    e->end = *ptr + size;
    e->limit = 0;
  } else {
    e->end = *ptr + size - kUpb_EpsCopyInputStream_SlopBytes;
    e->limit = kUpb_EpsCopyInputStream_SlopBytes;
    e->input_delta = 0;
  }
  e->aliasing = enable_aliasing;
  e->limit_ptr = e->end;
  e->error = false;
  UPB_PRIVATE(upb_EpsCopyInputStream_BoundsChecked)(e);
}

typedef enum {
  // The current stream position is at a limit.
  kUpb_IsDoneStatus_Done,

  // The current stream position is not at a limit.
  kUpb_IsDoneStatus_NotDone,

  // The current stream position is not at a limit, and the stream needs to
  // be flipped to a new buffer before more data can be read.
  kUpb_IsDoneStatus_NeedFallback,
} upb_IsDoneStatus;

// Returns the status of the current stream position.  This is a low-level
// function, it is simpler to call upb_EpsCopyInputStream_IsDone() if possible.
UPB_INLINE upb_IsDoneStatus upb_EpsCopyInputStream_IsDoneStatus(
    upb_EpsCopyInputStream* e, const char* ptr, int* overrun) {
  *overrun = ptr - e->end;
  if (UPB_LIKELY(ptr < e->limit_ptr)) {
    UPB_PRIVATE(upb_EpsCopyInputStream_BoundsChecked)(e);
    return kUpb_IsDoneStatus_NotDone;
  } else if (UPB_LIKELY(*overrun == e->limit)) {
    UPB_PRIVATE(upb_EpsCopyInputStream_BoundsHit)(e);
    return kUpb_IsDoneStatus_Done;
  } else {
    UPB_PRIVATE(upb_EpsCopyInputStream_BoundsHit)(e);
    return kUpb_IsDoneStatus_NeedFallback;
  }
}

// Returns true if the stream has hit a limit, either the current delimited
// limit or the overall end-of-stream. As a side effect, this function may flip
// the pointer to a new buffer if there are less than
// kUpb_EpsCopyInputStream_SlopBytes of data to be read in the current buffer.
//
// Postcondition: if the function returns false, there are at least
// kUpb_EpsCopyInputStream_SlopBytes of data available to read at *ptr.
UPB_INLINE bool upb_EpsCopyInputStream_IsDoneWithCallback(
    upb_EpsCopyInputStream* e, const char** ptr,
    upb_EpsCopyInputStream_IsDoneFallbackFunc* func) {
  int overrun;
  switch (upb_EpsCopyInputStream_IsDoneStatus(e, *ptr, &overrun)) {
    case kUpb_IsDoneStatus_Done:
      UPB_PRIVATE(upb_EpsCopyInputStream_BoundsHit)(e);
      return true;
    case kUpb_IsDoneStatus_NotDone:
      UPB_PRIVATE(upb_EpsCopyInputStream_BoundsChecked)(e);
      return false;
    case kUpb_IsDoneStatus_NeedFallback:
      *ptr = func(e, *ptr, overrun);
      if (*ptr) {
        UPB_PRIVATE(upb_EpsCopyInputStream_BoundsChecked)(e);
      } else {
        UPB_PRIVATE(upb_EpsCopyInputStream_BoundsHit)(e);
      }
      return *ptr == NULL;
  }
  UPB_UNREACHABLE();
}

const char* _upb_EpsCopyInputStream_IsDoneFallbackNoCallback(
    upb_EpsCopyInputStream* e, const char* ptr, int overrun);

// A simpler version of IsDoneWithCallback() that does not support a buffer flip
// callback. Useful in cases where we do not need to insert custom logic at
// every buffer flip.
//
// If this returns true, the user must call upb_EpsCopyInputStream_IsError()
// to distinguish between EOF and error.
UPB_INLINE bool upb_EpsCopyInputStream_IsDone(upb_EpsCopyInputStream* e,
                                              const char** ptr) {
  return upb_EpsCopyInputStream_IsDoneWithCallback(
      e, ptr, _upb_EpsCopyInputStream_IsDoneFallbackNoCallback);
}

// Returns the total number of bytes that are safe to read from the current
// buffer without reading uninitialized or unallocated memory.
//
// Note that this check does not respect any semantic limits on the stream,
// either limits from PushLimit() or the overall stream end, so some of these
// bytes may have unpredictable, nonsense values in them. The guarantee is only
// that the bytes are valid to read from the perspective of the C language
// (ie. you can read without triggering UBSAN or ASAN).
UPB_INLINE size_t upb_EpsCopyInputStream_BytesAvailable(
    upb_EpsCopyInputStream* e, const char* ptr) {
  return (e->end - ptr) + kUpb_EpsCopyInputStream_SlopBytes;
}

// Returns true if the given delimited field size is valid (it does not extend
// beyond any previously-pushed limits).  `ptr` should point to the beginning
// of the field data, after the delimited size.
//
// Note that this does *not* guarantee that all of the data for this field is in
// the current buffer.
UPB_INLINE bool upb_EpsCopyInputStream_CheckSize(
    const upb_EpsCopyInputStream* e, const char* ptr, int size) {
  UPB_ASSERT(size >= 0);
  return size <= e->limit - (ptr - e->end);
}

UPB_INLINE bool _upb_EpsCopyInputStream_CheckSizeAvailable(
    upb_EpsCopyInputStream* e, const char* ptr, int size, bool submessage) {
  // This is one extra branch compared to the more normal:
  //   return (size_t)(end - ptr) < size;
  // However it is one less computation if we are just about to use "ptr + len":
  //   https://godbolt.org/z/35YGPz
  // In microbenchmarks this shows a small improvement.
  uintptr_t uptr = (uintptr_t)ptr;
  uintptr_t uend = (uintptr_t)e->limit_ptr;
  uintptr_t res = uptr + (size_t)size;
  if (!submessage) uend += kUpb_EpsCopyInputStream_SlopBytes;
  // NOTE: this check depends on having a linear address space.  This is not
  // technically guaranteed by uintptr_t.
  bool ret = res >= uptr && res <= uend;
  if (size < 0) UPB_ASSERT(!ret);
  return ret;
}

// Returns true if the given delimited field size is valid (it does not extend
// beyond any previously-pushed limited) *and* all of the data for this field is
// available to be read in the current buffer.
//
// If the size is negative, this function will always return false. This
// property can be useful in some cases.
UPB_INLINE bool upb_EpsCopyInputStream_CheckDataSizeAvailable(
    upb_EpsCopyInputStream* e, const char* ptr, int size) {
  return _upb_EpsCopyInputStream_CheckSizeAvailable(e, ptr, size, false);
}

// Returns true if the given sub-message size is valid (it does not extend
// beyond any previously-pushed limited) *and* all of the data for this
// sub-message is available to be parsed in the current buffer.
//
// This implies that all fields from the sub-message can be parsed from the
// current buffer while maintaining the invariant that we always have at least
// kUpb_EpsCopyInputStream_SlopBytes of data available past the beginning of
// any individual field start.
//
// If the size is negative, this function will always return false. This
// property can be useful in some cases.
UPB_INLINE bool upb_EpsCopyInputStream_CheckSubMessageSizeAvailable(
    upb_EpsCopyInputStream* e, const char* ptr, int size) {
  return _upb_EpsCopyInputStream_CheckSizeAvailable(e, ptr, size, true);
}

// Returns true if aliasing_enabled=true was passed to
// upb_EpsCopyInputStream_Init() when this stream was initialized.
UPB_INLINE bool upb_EpsCopyInputStream_AliasingEnabled(
    upb_EpsCopyInputStream* e) {
  return e->aliasing;
}

// Returns true if aliasing_enabled=true was passed to
// upb_EpsCopyInputStream_Init() when this stream was initialized *and* we can
// alias into the region [ptr, size] in an input buffer.
UPB_INLINE bool upb_EpsCopyInputStream_AliasingAvailable(
    upb_EpsCopyInputStream* e, const char* ptr, size_t size) {
  // When EpsCopyInputStream supports streaming, this will need to become a
  // runtime check.
  return e->aliasing &&
         upb_EpsCopyInputStream_CheckDataSizeAvailable(e, ptr, size);
}

// Returns a pointer into an input buffer that corresponds to the parsing
// pointer `ptr`.  The returned pointer may be the same as `ptr`, but also may
// be different if we are currently parsing out of the patch buffer.
UPB_INLINE const char* upb_EpsCopyInputStream_GetInputPtr(
    upb_EpsCopyInputStream* e, const char* ptr) {
  // This somewhat silly looking add-and-subtract behavior provides provenance
  // from the original input buffer's pointer. After optimization it produces
  // the same assembly as just casting `(uintptr_t)ptr+input_delta`
  // https://godbolt.org/z/zosG88oPn
  size_t position =
      (uintptr_t)ptr + e->input_delta - (uintptr_t)e->buffer_start;
  return e->buffer_start + position;
}

// Returns a pointer into an input buffer that corresponds to the parsing
// pointer `ptr`.  The returned pointer may be the same as `ptr`, but also may
// be different if we are currently parsing out of the patch buffer.
//
// REQUIRES: Aliasing must be available for the given pointer. If the input is a
// flat buffer and aliasing is enabled, then aliasing will always be available.
UPB_INLINE const char* upb_EpsCopyInputStream_GetAliasedPtr(
    upb_EpsCopyInputStream* e, const char* ptr) {
  UPB_ASSUME(upb_EpsCopyInputStream_AliasingAvailable(e, ptr, 0));
  return upb_EpsCopyInputStream_GetInputPtr(e, ptr);
}

// Reads string data from the input, aliasing into the input buffer instead of
// copying. The parsing pointer is passed in `*ptr`, and will be updated if
// necessary to point to the actual input buffer. Returns the new parsing
// pointer, which will be advanced past the string data.
//
// REQUIRES: Aliasing must be available for this data region (test with
// upb_EpsCopyInputStream_AliasingAvailable().
UPB_INLINE const char* upb_EpsCopyInputStream_ReadStringAliased(
    upb_EpsCopyInputStream* e, const char** ptr, size_t size) {
  UPB_ASSUME(upb_EpsCopyInputStream_AliasingAvailable(e, *ptr, size));
  const char* ret = *ptr + size;
  *ptr = upb_EpsCopyInputStream_GetAliasedPtr(e, *ptr);
  UPB_ASSUME(ret != NULL);
  return ret;
}

// Skips `size` bytes of data from the input and returns a pointer past the end.
// Returns NULL on end of stream or error.
UPB_INLINE const char* upb_EpsCopyInputStream_Skip(upb_EpsCopyInputStream* e,
                                                   const char* ptr, int size) {
  if (!upb_EpsCopyInputStream_CheckDataSizeAvailable(e, ptr, size)) return NULL;
  return ptr + size;
}

// Copies `size` bytes of data from the input `ptr` into the buffer `to`, and
// returns a pointer past the end. Returns NULL on end of stream or error.
UPB_INLINE const char* upb_EpsCopyInputStream_Copy(upb_EpsCopyInputStream* e,
                                                   const char* ptr, void* to,
                                                   int size) {
  if (!upb_EpsCopyInputStream_CheckDataSizeAvailable(e, ptr, size)) return NULL;
  memcpy(to, ptr, size);
  return ptr + size;
}

// Reads string data from the stream and advances the pointer accordingly.
// If aliasing was enabled when the stream was initialized, then the returned
// pointer will point into the input buffer if possible, otherwise new data
// will be allocated from arena and copied into. We may be forced to copy even
// if aliasing was enabled if the input data spans input buffers.
//
// Returns NULL if memory allocation failed, or we reached a premature EOF.
UPB_INLINE const char* upb_EpsCopyInputStream_ReadString(
    upb_EpsCopyInputStream* e, const char** ptr, size_t size,
    upb_Arena* arena) {
  if (upb_EpsCopyInputStream_AliasingAvailable(e, *ptr, size)) {
    return upb_EpsCopyInputStream_ReadStringAliased(e, ptr, size);
  } else {
    // We need to allocate and copy.
    if (!upb_EpsCopyInputStream_CheckDataSizeAvailable(e, *ptr, size)) {
      return NULL;
    }
    UPB_ASSERT(arena);
    char* data = (char*)upb_Arena_Malloc(arena, size);
    if (!data) return NULL;
    const char* ret = upb_EpsCopyInputStream_Copy(e, *ptr, data, size);
    *ptr = data;
    return ret;
  }
}

UPB_INLINE void _upb_EpsCopyInputStream_CheckLimit(upb_EpsCopyInputStream* e) {
  UPB_ASSERT(e->limit_ptr == e->end + UPB_MIN(0, e->limit));
}

// Pushes a limit onto the stack of limits for the current stream.  The limit
// will extend for `size` bytes beyond the position in `ptr`.  Future calls to
// upb_EpsCopyInputStream_IsDone() will return `true` when the stream position
// reaches this limit.
//
// Returns a delta that the caller must store and supply to PopLimit() below.
UPB_INLINE int upb_EpsCopyInputStream_PushLimit(upb_EpsCopyInputStream* e,
                                                const char* ptr, int size) {
  int limit = size + (int)(ptr - e->end);
  int delta = e->limit - limit;
  _upb_EpsCopyInputStream_CheckLimit(e);
  UPB_ASSERT(limit <= e->limit);
  e->limit = limit;
  e->limit_ptr = e->end + UPB_MIN(0, limit);
  _upb_EpsCopyInputStream_CheckLimit(e);
  return delta;
}

// Pops the last limit that was pushed on this stream.  This may only be called
// once IsDone() returns true.  The user must pass the delta that was returned
// from PushLimit().
UPB_INLINE void upb_EpsCopyInputStream_PopLimit(upb_EpsCopyInputStream* e,
                                                const char* ptr,
                                                int saved_delta) {
  UPB_ASSERT(ptr - e->end == e->limit);
  _upb_EpsCopyInputStream_CheckLimit(e);
  e->limit += saved_delta;
  e->limit_ptr = e->end + UPB_MIN(0, e->limit);
  _upb_EpsCopyInputStream_CheckLimit(e);
}

UPB_INLINE const char* _upb_EpsCopyInputStream_IsDoneFallbackInline(
    upb_EpsCopyInputStream* e, const char* ptr, int overrun,
    upb_EpsCopyInputStream_BufferFlipCallback* callback) {
  if (overrun < e->limit) {
    // Need to copy remaining data into patch buffer.
    UPB_ASSERT(overrun < kUpb_EpsCopyInputStream_SlopBytes);
    const char* old_end = ptr;
    const char* new_start = &e->patch[0] + overrun;
    memset(e->patch + kUpb_EpsCopyInputStream_SlopBytes, 0,
           kUpb_EpsCopyInputStream_SlopBytes);
    memcpy(e->patch, e->end, kUpb_EpsCopyInputStream_SlopBytes);
    ptr = new_start;
    e->end = &e->patch[kUpb_EpsCopyInputStream_SlopBytes];
    e->limit -= kUpb_EpsCopyInputStream_SlopBytes;
    e->limit_ptr = e->end + e->limit;
    UPB_ASSERT(ptr < e->limit_ptr);
    e->input_delta = (uintptr_t)old_end - (uintptr_t)new_start;
    const char* ret = callback(e, old_end, new_start);
    if (ret) {
      UPB_PRIVATE(upb_EpsCopyInputStream_BoundsChecked)(e);
    }
    return ret;
  } else {
    UPB_ASSERT(overrun > e->limit);
    e->error = true;
    return callback(e, NULL, NULL);
  }
}

typedef const char* upb_EpsCopyInputStream_ParseDelimitedFunc(
    upb_EpsCopyInputStream* e, const char* ptr, void* ctx);

// Tries to perform a fast-path handling of the given delimited message data.
// If the sub-message beginning at `*ptr` and extending for `len` is short and
// fits within this buffer, calls `func` with `ctx` as a parameter, where the
// pushing and popping of limits is handled automatically and with lower cost
// than the normal PushLimit()/PopLimit() sequence.
UPB_FORCEINLINE bool upb_EpsCopyInputStream_TryParseDelimitedFast(
    upb_EpsCopyInputStream* e, const char** ptr, int len,
    upb_EpsCopyInputStream_ParseDelimitedFunc* func, void* ctx) {
  if (!upb_EpsCopyInputStream_CheckSubMessageSizeAvailable(e, *ptr, len)) {
    return false;
  }

  // Fast case: Sub-message is <128 bytes and fits in the current buffer.
  // This means we can preserve limit/limit_ptr verbatim.
  const char* saved_limit_ptr = e->limit_ptr;
  int saved_limit = e->limit;
  e->limit_ptr = *ptr + len;
  e->limit = e->limit_ptr - e->end;
  UPB_ASSERT(e->limit_ptr == e->end + UPB_MIN(0, e->limit));
  *ptr = func(e, *ptr, ctx);
  e->limit_ptr = saved_limit_ptr;
  e->limit = saved_limit;
  UPB_ASSERT(e->limit_ptr == e->end + UPB_MIN(0, e->limit));
  return true;
}

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif  // UPB_WIRE_EPS_COPY_INPUT_STREAM_H_

#ifndef UPB_WIRE_READER_H_
#define UPB_WIRE_READER_H_

#include <stddef.h>
#include <stdint.h>
#include <string.h>


#ifndef UPB_WIRE_INTERNAL_READER_H_
#define UPB_WIRE_INTERNAL_READER_H_

#include <stddef.h>
#include <stdint.h>


// Must be last.

#define kUpb_WireReader_WireTypeBits 3
#define kUpb_WireReader_WireTypeMask 7

typedef struct {
  const char* ptr;
  uint64_t val;
} UPB_PRIVATE(_upb_WireReader_LongVarint);

#ifdef __cplusplus
extern "C" {
#endif

UPB_PRIVATE(_upb_WireReader_LongVarint)
UPB_PRIVATE(_upb_WireReader_ReadLongVarint32)(const char* ptr, uint32_t val);
UPB_PRIVATE(_upb_WireReader_LongVarint)
UPB_PRIVATE(_upb_WireReader_ReadLongVarint64)(const char* ptr, uint64_t val);

UPB_FORCEINLINE const char* UPB_PRIVATE(_upb_WireReader_ReadVarint)(
    const char* ptr, uint64_t* val, upb_EpsCopyInputStream* stream) {
  UPB_PRIVATE(upb_EpsCopyInputStream_ConsumeBytes)(stream, 10);
  uint8_t byte = *ptr;
  if (UPB_LIKELY((byte & 0x80) == 0)) {
    *val = byte;
    return ptr + 1;
  }
  UPB_PRIVATE(_upb_WireReader_LongVarint)
  res = UPB_PRIVATE(_upb_WireReader_ReadLongVarint64)(ptr, byte);
  if (UPB_UNLIKELY(!res.ptr)) return NULL;
  *val = res.val;
  return res.ptr;
}

UPB_FORCEINLINE const char* UPB_PRIVATE(_upb_WireReader_ReadTag)(
    const char* ptr, uint32_t* val, upb_EpsCopyInputStream* stream) {
  UPB_PRIVATE(upb_EpsCopyInputStream_ConsumeBytes)(stream, 5);
  uint8_t byte = *ptr;
  if (UPB_LIKELY((byte & 0x80) == 0)) {
    *val = byte;
    return ptr + 1;
  }
  UPB_PRIVATE(_upb_WireReader_LongVarint)
  res = UPB_PRIVATE(_upb_WireReader_ReadLongVarint32)(ptr, byte);
  if (UPB_UNLIKELY(!res.ptr)) return NULL;
  *val = res.val;
  return res.ptr;
}

UPB_API_INLINE uint32_t upb_WireReader_GetFieldNumber(uint32_t tag) {
  return tag >> kUpb_WireReader_WireTypeBits;
}

UPB_API_INLINE uint8_t upb_WireReader_GetWireType(uint32_t tag) {
  return tag & kUpb_WireReader_WireTypeMask;
}

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif  // UPB_WIRE_INTERNAL_READER_H_

#ifndef UPB_WIRE_TYPES_H_
#define UPB_WIRE_TYPES_H_

// A list of types as they are encoded on the wire.
typedef enum {
  kUpb_WireType_Varint = 0,
  kUpb_WireType_64Bit = 1,
  kUpb_WireType_Delimited = 2,
  kUpb_WireType_StartGroup = 3,
  kUpb_WireType_EndGroup = 4,
  kUpb_WireType_32Bit = 5
} upb_WireType;

#endif /* UPB_WIRE_TYPES_H_ */

// Must be last.

// The upb_WireReader interface is suitable for general-purpose parsing of
// protobuf binary wire format. It is designed to be used along with
// upb_EpsCopyInputStream for buffering, and all parsing routines in this file
// assume that at least kUpb_EpsCopyInputStream_SlopBytes worth of data is
// available to read without any bounds checks.

#ifdef __cplusplus
extern "C" {
#endif

// Parses a tag into `tag`, and returns a pointer past the end of the tag, or
// NULL if there was an error in the tag data.
//
// REQUIRES: there must be at least 10 bytes of data available at `ptr`.
// Bounds checks must be performed before calling this function, preferably
// by calling upb_EpsCopyInputStream_IsDone().
UPB_FORCEINLINE const char* upb_WireReader_ReadTag(
    const char* ptr, uint32_t* tag, upb_EpsCopyInputStream* stream) {
  return UPB_PRIVATE(_upb_WireReader_ReadTag)(ptr, tag, stream);
}

// Given a tag, returns the field number.
UPB_API_INLINE uint32_t upb_WireReader_GetFieldNumber(uint32_t tag);

// Given a tag, returns the wire type.
UPB_API_INLINE uint8_t upb_WireReader_GetWireType(uint32_t tag);

UPB_INLINE const char* upb_WireReader_ReadVarint(
    const char* ptr, uint64_t* val, upb_EpsCopyInputStream* stream) {
  return UPB_PRIVATE(_upb_WireReader_ReadVarint)(ptr, val, stream);
}

// Skips data for a varint, returning a pointer past the end of the varint, or
// NULL if there was an error in the varint data.
//
// REQUIRES: there must be at least 10 bytes of data available at `ptr`.
// Bounds checks must be performed before calling this function, preferably
// by calling upb_EpsCopyInputStream_IsDone().
UPB_INLINE const char* upb_WireReader_SkipVarint(
    const char* ptr, upb_EpsCopyInputStream* stream) {
  uint64_t val;
  return upb_WireReader_ReadVarint(ptr, &val, stream);
}

// Reads a varint indicating the size of a delimited field into `size`, or
// NULL if there was an error in the varint data.
//
// REQUIRES: there must be at least 10 bytes of data available at `ptr`.
// Bounds checks must be performed before calling this function, preferably
// by calling upb_EpsCopyInputStream_IsDone().
UPB_INLINE const char* upb_WireReader_ReadSize(const char* ptr, int* size,
                                               upb_EpsCopyInputStream* stream) {
  uint64_t size64;
  ptr = upb_WireReader_ReadVarint(ptr, &size64, stream);
  if (!ptr || size64 >= INT32_MAX) return NULL;
  *size = size64;
  return ptr;
}

// Reads a fixed32 field, performing byte swapping if necessary.
//
// REQUIRES: there must be at least 4 bytes of data available at `ptr`.
// Bounds checks must be performed before calling this function, preferably
// by calling upb_EpsCopyInputStream_IsDone().
UPB_INLINE const char* upb_WireReader_ReadFixed32(
    const char* ptr, void* val, upb_EpsCopyInputStream* stream) {
  UPB_PRIVATE(upb_EpsCopyInputStream_ConsumeBytes)(stream, 4);
  uint32_t uval;
  memcpy(&uval, ptr, 4);
  uval = upb_BigEndian32(uval);
  memcpy(val, &uval, 4);
  return ptr + 4;
}

// Reads a fixed64 field, performing byte swapping if necessary.
//
// REQUIRES: there must be at least 4 bytes of data available at `ptr`.
// Bounds checks must be performed before calling this function, preferably
// by calling upb_EpsCopyInputStream_IsDone().
UPB_INLINE const char* upb_WireReader_ReadFixed64(
    const char* ptr, void* val, upb_EpsCopyInputStream* stream) {
  UPB_PRIVATE(upb_EpsCopyInputStream_ConsumeBytes)(stream, 8);
  uint64_t uval;
  memcpy(&uval, ptr, 8);
  uval = upb_BigEndian64(uval);
  memcpy(val, &uval, 8);
  return ptr + 8;
}

const char* UPB_PRIVATE(_upb_WireReader_SkipGroup)(
    const char* ptr, uint32_t tag, int depth_limit,
    upb_EpsCopyInputStream* stream);

// Skips data for a group, returning a pointer past the end of the group, or
// NULL if there was an error parsing the group.  The `tag` argument should be
// the start group tag that begins the group.  The `depth_limit` argument
// indicates how many levels of recursion the group is allowed to have before
// reporting a parse error (this limit exists to protect against stack
// overflow).
//
// TODO: evaluate how the depth_limit should be specified. Do users need
// control over this?
UPB_INLINE const char* upb_WireReader_SkipGroup(
    const char* ptr, uint32_t tag, upb_EpsCopyInputStream* stream) {
  return UPB_PRIVATE(_upb_WireReader_SkipGroup)(ptr, tag, 100, stream);
}

UPB_INLINE const char* _upb_WireReader_SkipValue(
    const char* ptr, uint32_t tag, int depth_limit,
    upb_EpsCopyInputStream* stream) {
  switch (upb_WireReader_GetWireType(tag)) {
    case kUpb_WireType_Varint:
      return upb_WireReader_SkipVarint(ptr, stream);
    case kUpb_WireType_32Bit:
      UPB_PRIVATE(upb_EpsCopyInputStream_ConsumeBytes)(stream, 4);
      return ptr + 4;
    case kUpb_WireType_64Bit:
      UPB_PRIVATE(upb_EpsCopyInputStream_ConsumeBytes)(stream, 8);
      return ptr + 8;
    case kUpb_WireType_Delimited: {
      int size;
      ptr = upb_WireReader_ReadSize(ptr, &size, stream);
      if (!ptr || !upb_EpsCopyInputStream_CheckSize(stream, ptr, size)) {
        return NULL;
      }
      ptr += size;
      return ptr;
    }
    case kUpb_WireType_StartGroup:
      return UPB_PRIVATE(_upb_WireReader_SkipGroup)(ptr, tag, depth_limit,
                                                    stream);
    case kUpb_WireType_EndGroup:
      return NULL;  // Should be handled before now.
    default:
      return NULL;  // Unknown wire type.
  }
}

// Skips data for a wire value of any type, returning a pointer past the end of
// the data, or NULL if there was an error parsing the group. The `tag` argument
// should be the tag that was just parsed. The `depth_limit` argument indicates
// how many levels of recursion a group is allowed to have before reporting a
// parse error (this limit exists to protect against stack overflow).
//
// REQUIRES: there must be at least 10 bytes of data available at `ptr`.
// Bounds checks must be performed before calling this function, preferably
// by calling upb_EpsCopyInputStream_IsDone().
//
// TODO: evaluate how the depth_limit should be specified. Do users need
// control over this?
UPB_INLINE const char* upb_WireReader_SkipValue(
    const char* ptr, uint32_t tag, upb_EpsCopyInputStream* stream) {
  return _upb_WireReader_SkipValue(ptr, tag, 100, stream);
}

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif  // UPB_WIRE_READER_H_

#ifndef UPB_MESSAGE_COPY_H_
#define UPB_MESSAGE_COPY_H_


// Must be last.

#ifdef __cplusplus
extern "C" {
#endif

// Deep clones a message using the provided target arena.
upb_Message* upb_Message_DeepClone(const upb_Message* msg,
                                   const upb_MiniTable* m, upb_Arena* arena);

// Shallow clones a message using the provided target arena.
upb_Message* upb_Message_ShallowClone(const upb_Message* msg,
                                      const upb_MiniTable* m, upb_Arena* arena);

// Deep clones array contents.
upb_Array* upb_Array_DeepClone(const upb_Array* array, upb_CType value_type,
                               const upb_MiniTable* sub, upb_Arena* arena);

// Deep clones map contents.
upb_Map* upb_Map_DeepClone(const upb_Map* map, upb_CType key_type,
                           upb_CType value_type,
                           const upb_MiniTable* map_entry_table,
                           upb_Arena* arena);

// Deep copies the message from src to dst.
bool upb_Message_DeepCopy(upb_Message* dst, const upb_Message* src,
                          const upb_MiniTable* m, upb_Arena* arena);

// Shallow copies the message from src to dst.
void upb_Message_ShallowCopy(upb_Message* dst, const upb_Message* src,
                             const upb_MiniTable* m);

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif  // UPB_MESSAGE_COPY_H_

// EVERYTHING BELOW THIS LINE IS INTERNAL - DO NOT USE /////////////////////////

#ifndef UPB_MESSAGE_INTERNAL_MAP_SORTER_H_
#define UPB_MESSAGE_INTERNAL_MAP_SORTER_H_

#include <stdint.h>
#include <stdlib.h>
#include <string.h>


#ifndef UPB_MESSAGE_INTERNAL_MAP_ENTRY_H_
#define UPB_MESSAGE_INTERNAL_MAP_ENTRY_H_

#include <stdint.h>


// Map entries aren't actually stored for map fields, they are only used during
// parsing. (It helps a lot if all map entry messages have the same layout.)
// The mini_table layout code will ensure that all map entries have this layout.
//
// Note that users can and do create map entries directly, which will also use
// this layout.

typedef struct {
  struct upb_Message message;
  // We only need 2 hasbits max, but due to alignment we'll use 8 bytes here,
  // and the uint64_t helps make this clear.
  uint64_t hasbits;
  union {
    upb_StringView str;  // For str/bytes.
    upb_value val;       // For all other types.
    double d[2];         // Padding for 32-bit builds.
  } k;
  union {
    upb_StringView str;  // For str/bytes.
    upb_value val;       // For all other types.
    double d[2];         // Padding for 32-bit builds.
  } v;
} upb_MapEntry;

#endif  // UPB_MESSAGE_INTERNAL_MAP_ENTRY_H_

// Must be last.

#ifdef __cplusplus
extern "C" {
#endif

// _upb_mapsorter sorts maps and provides ordered iteration over the entries.
// Since maps can be recursive (map values can be messages which contain other
// maps), _upb_mapsorter can contain a stack of maps.

typedef struct {
  void const** entries;
  int size;
  int cap;
} _upb_mapsorter;

typedef struct {
  int start;
  int pos;
  int end;
} _upb_sortedmap;

UPB_INLINE void _upb_mapsorter_init(_upb_mapsorter* s) {
  s->entries = NULL;
  s->size = 0;
  s->cap = 0;
}

UPB_INLINE void _upb_mapsorter_destroy(_upb_mapsorter* s) {
  if (s->entries) upb_gfree(s->entries);
}

UPB_INLINE bool _upb_sortedmap_next(_upb_mapsorter* s,
                                    const struct upb_Map* map,
                                    _upb_sortedmap* sorted, upb_MapEntry* ent) {
  if (sorted->pos == sorted->end) return false;
  const upb_tabent* tabent = (const upb_tabent*)s->entries[sorted->pos++];
  if (map->UPB_PRIVATE(is_strtable)) {
    upb_StringView key = upb_key_strview(tabent->key);
    _upb_map_fromkey(key, &ent->k, map->key_size);
  } else {
    uintptr_t key = tabent->key.num;
    memcpy(&ent->k, &key, map->key_size);
  }
  upb_value val = {tabent->val.val};
  _upb_map_fromvalue(val, &ent->v, map->val_size);
  return true;
}

UPB_INLINE bool _upb_sortedmap_nextext(_upb_mapsorter* s,
                                       _upb_sortedmap* sorted,
                                       const upb_Extension** ext) {
  if (sorted->pos == sorted->end) return false;
  *ext = (const upb_Extension*)s->entries[sorted->pos++];
  return true;
}

UPB_INLINE void _upb_mapsorter_popmap(_upb_mapsorter* s,
                                      _upb_sortedmap* sorted) {
  s->size = sorted->start;
}

bool _upb_mapsorter_pushmap(_upb_mapsorter* s, upb_FieldType key_type,
                            const struct upb_Map* map, _upb_sortedmap* sorted);

bool _upb_mapsorter_pushexts(_upb_mapsorter* s, const upb_Message_Internal* in,
                             _upb_sortedmap* sorted);

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /* UPB_MESSAGE_INTERNAL_MAP_SORTER_H_ */

#ifndef UPB_MESSAGE_PROMOTE_H_
#define UPB_MESSAGE_PROMOTE_H_


// Must be last.

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  kUpb_GetExtension_Ok,
  kUpb_GetExtension_NotPresent,
  kUpb_GetExtension_ParseError,
  kUpb_GetExtension_OutOfMemory,
} upb_GetExtension_Status;

typedef enum {
  kUpb_GetExtensionAsBytes_Ok,
  kUpb_GetExtensionAsBytes_NotPresent,
  kUpb_GetExtensionAsBytes_EncodeError,
} upb_GetExtensionAsBytes_Status;

// Returns a message value or promotes an unknown field to an extension.
//
// TODO: Only supports extension fields that are messages,
// expand support to include non-message types.
upb_GetExtension_Status upb_Message_GetOrPromoteExtension(
    upb_Message* msg, const upb_MiniTableExtension* ext_table,
    int decode_options, upb_Arena* arena, upb_MessageValue* value);

typedef enum {
  kUpb_FindUnknown_Ok,
  kUpb_FindUnknown_NotPresent,
  kUpb_FindUnknown_ParseError,
} upb_FindUnknown_Status;

typedef struct {
  upb_FindUnknown_Status status;
  // Start of unknown field data in message arena.
  const char* ptr;
  // Size of unknown field data.
  size_t len;
  uintptr_t iter;
} upb_FindUnknownRet;

// Finds first occurrence of unknown data by tag id in message.
// A depth_limit of zero means to just use the upb default depth limit.
upb_FindUnknownRet upb_Message_FindUnknown(const upb_Message* msg,
                                           uint32_t field_number,
                                           int depth_limit);

typedef enum {
  kUpb_UnknownToMessage_Ok,
  kUpb_UnknownToMessage_ParseError,
  kUpb_UnknownToMessage_OutOfMemory,
  kUpb_UnknownToMessage_NotFound,
} upb_UnknownToMessage_Status;

typedef struct {
  upb_UnknownToMessage_Status status;
  upb_Message* message;
} upb_UnknownToMessageRet;

// Promotes an "empty" non-repeated message field in `parent` to a message of
// the correct type.
//
// Preconditions:
//
// 1. The message field must currently be in the "empty" state (this must have
//    been previously verified by the caller by calling
//    `upb_Message_GetTaggedMessagePtr()` and observing that the message is
//    indeed empty).
//
// 2. This `field` must have previously been linked.
//
// If the promotion succeeds, `parent` will have its data for `field` replaced
// by the promoted message, which is also returned in `*promoted`.  If the
// return value indicates an error status, `parent` and `promoted` are
// unchanged.
upb_DecodeStatus upb_Message_PromoteMessage(upb_Message* parent,
                                            const upb_MiniTable* mini_table,
                                            const upb_MiniTableField* field,
                                            int decode_options,
                                            upb_Arena* arena,
                                            upb_Message** promoted);

// Promotes any "empty" messages in this array to a message of the correct type
// `mini_table`.  This function should only be called for arrays of messages.
//
// If the return value indicates an error status, some but not all elements may
// have been promoted, but the array itself will not be corrupted.
upb_DecodeStatus upb_Array_PromoteMessages(upb_Array* arr,
                                           const upb_MiniTable* mini_table,
                                           int decode_options,
                                           upb_Arena* arena);

// Promotes any "empty" entries in this map to a message of the correct type
// `mini_table`.  This function should only be called for maps that have a
// message type as the map value.
//
// If the return value indicates an error status, some but not all elements may
// have been promoted, but the map itself will not be corrupted.
upb_DecodeStatus upb_Map_PromoteMessages(upb_Map* map,
                                         const upb_MiniTable* mini_table,
                                         int decode_options, upb_Arena* arena);

// Utility function for wrapper languages to get an error string from a
// upb_UnknownToMessageStatus.
const char* upb_FindUnknownStatus_String(upb_FindUnknown_Status status);

////////////////////////////////////////////////////////////////////////////////
// OLD promotion interfaces, will be removed!
////////////////////////////////////////////////////////////////////////////////

// Promotes unknown data inside message to a upb_Message parsing the unknown.
//
// The unknown data is removed from message after field value is set
// using upb_Message_SetMessage.
//
// WARNING!: See b/267655898
upb_UnknownToMessageRet upb_MiniTable_PromoteUnknownToMessage(
    upb_Message* msg, const upb_MiniTable* mini_table,
    const upb_MiniTableField* field, const upb_MiniTable* sub_mini_table,
    int decode_options, upb_Arena* arena);

// Promotes all unknown data that matches field tag id to repeated messages
// in upb_Array.
//
// The unknown data is removed from message after upb_Array is populated.
// Since repeated messages can't be packed we remove each unknown that
// contains the target tag id.
upb_UnknownToMessage_Status upb_MiniTable_PromoteUnknownToMessageArray(
    upb_Message* msg, const upb_MiniTableField* field,
    const upb_MiniTable* mini_table, int decode_options, upb_Arena* arena);

// Promotes all unknown data that matches field tag id to upb_Map.
//
// The unknown data is removed from message after upb_Map is populated.
// Since repeated messages can't be packed we remove each unknown that
// contains the target tag id.
upb_UnknownToMessage_Status upb_MiniTable_PromoteUnknownToMap(
    upb_Message* msg, const upb_MiniTable* mini_table,
    const upb_MiniTableField* field, int decode_options, upb_Arena* arena);

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif  // UPB_MESSAGE_PROMOTE_H_
#ifndef GOOGLE_UPB_UPB_MESSAGE_MERGE_H__
#define GOOGLE_UPB_UPB_MESSAGE_MERGE_H__


// Must be last.

#ifdef __cplusplus
extern "C" {
#endif

UPB_API bool upb_Message_MergeFrom(upb_Message* dst, const upb_Message* src,
                                   const upb_MiniTable* mt,
                                   const upb_ExtensionRegistry* extreg,
                                   upb_Arena* arena);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif  // GOOGLE_UPB_UPB_MESSAGE_MERGE_H__

#ifndef UPB_MINI_DESCRIPTOR_INTERNAL_BASE92_H_
#define UPB_MINI_DESCRIPTOR_INTERNAL_BASE92_H_

#include <stdint.h>


// Must be last.

#ifdef __cplusplus
extern "C" {
#endif

UPB_INLINE char _upb_ToBase92(int8_t ch) {
  extern const char _kUpb_ToBase92[];
  UPB_ASSERT(0 <= ch && ch < 92);
  return _kUpb_ToBase92[ch];
}

UPB_INLINE char _upb_FromBase92(uint8_t ch) {
  extern const int8_t _kUpb_FromBase92[];
  if (' ' > ch || ch > '~') return -1;
  return _kUpb_FromBase92[ch - ' '];
}

UPB_INLINE const char* _upb_Base92_DecodeVarint(const char* ptr,
                                                const char* end, char first_ch,
                                                uint8_t min, uint8_t max,
                                                uint32_t* out_val) {
  uint32_t val = 0;
  uint32_t shift = 0;
  const int bits_per_char =
      upb_Log2Ceiling(_upb_FromBase92(max) - _upb_FromBase92(min));
  char ch = first_ch;
  while (1) {
    uint32_t bits = _upb_FromBase92(ch) - _upb_FromBase92(min);
    val |= bits << shift;
    if (ptr == end || *ptr < min || max < *ptr) {
      *out_val = val;
      UPB_ASSUME(ptr != NULL);
      return ptr;
    }
    ch = *ptr++;
    shift += bits_per_char;
    if (shift >= 32) return NULL;
  }
}

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif  // UPB_MINI_DESCRIPTOR_INTERNAL_BASE92_H_

#ifndef UPB_MINI_DESCRIPTOR_INTERNAL_DECODER_H_
#define UPB_MINI_DESCRIPTOR_INTERNAL_DECODER_H_


// Must be last.

// upb_MdDecoder: used internally for decoding MiniDescriptors for messages,
// extensions, and enums.
typedef struct {
  const char* end;
  upb_Status* status;
  jmp_buf err;
} upb_MdDecoder;

UPB_PRINTF(2, 3)
UPB_NORETURN UPB_INLINE void upb_MdDecoder_ErrorJmp(upb_MdDecoder* d,
                                                    const char* fmt, ...) {
  if (d->status) {
    va_list argp;
    upb_Status_SetErrorMessage(d->status, "Error building mini table: ");
    va_start(argp, fmt);
    upb_Status_VAppendErrorFormat(d->status, fmt, argp);
    va_end(argp);
  }
  UPB_LONGJMP(d->err, 1);
}

UPB_INLINE void upb_MdDecoder_CheckOutOfMemory(upb_MdDecoder* d,
                                               const void* ptr) {
  if (!ptr) upb_MdDecoder_ErrorJmp(d, "Out of memory");
}

UPB_INLINE const char* upb_MdDecoder_DecodeBase92Varint(
    upb_MdDecoder* d, const char* ptr, char first_ch, uint8_t min, uint8_t max,
    uint32_t* out_val) {
  ptr = _upb_Base92_DecodeVarint(ptr, d->end, first_ch, min, max, out_val);
  if (!ptr) upb_MdDecoder_ErrorJmp(d, "Overlong varint");
  return ptr;
}


#endif  // UPB_MINI_DESCRIPTOR_INTERNAL_DECODER_H_

#ifndef UPB_MINI_DESCRIPTOR_INTERNAL_MODIFIERS_H_
#define UPB_MINI_DESCRIPTOR_INTERNAL_MODIFIERS_H_

// Must be last.

typedef enum {
  kUpb_FieldModifier_IsRepeated = 1 << 0,
  kUpb_FieldModifier_IsPacked = 1 << 1,
  kUpb_FieldModifier_IsClosedEnum = 1 << 2,
  kUpb_FieldModifier_IsProto3Singular = 1 << 3,
  kUpb_FieldModifier_IsRequired = 1 << 4,
  kUpb_FieldModifier_ValidateUtf8 = 1 << 5,
} kUpb_FieldModifier;

// These modifiers are also used on the wire.
typedef enum {
  kUpb_MessageModifier_ValidateUtf8 = 1 << 0,
  kUpb_MessageModifier_DefaultIsPacked = 1 << 1,
  kUpb_MessageModifier_IsExtendable = 1 << 2,
} kUpb_MessageModifier;


#endif  // UPB_MINI_DESCRIPTOR_INTERNAL_MODIFIERS_H_

#ifndef UPB_MINI_DESCRIPTOR_INTERNAL_WIRE_CONSTANTS_H_
#define UPB_MINI_DESCRIPTOR_INTERNAL_WIRE_CONSTANTS_H_


// Must be last.

typedef enum {
  kUpb_EncodedType_Double = 0,
  kUpb_EncodedType_Float = 1,
  kUpb_EncodedType_Fixed32 = 2,
  kUpb_EncodedType_Fixed64 = 3,
  kUpb_EncodedType_SFixed32 = 4,
  kUpb_EncodedType_SFixed64 = 5,
  kUpb_EncodedType_Int32 = 6,
  kUpb_EncodedType_UInt32 = 7,
  kUpb_EncodedType_SInt32 = 8,
  kUpb_EncodedType_Int64 = 9,
  kUpb_EncodedType_UInt64 = 10,
  kUpb_EncodedType_SInt64 = 11,
  kUpb_EncodedType_OpenEnum = 12,
  kUpb_EncodedType_Bool = 13,
  kUpb_EncodedType_Bytes = 14,
  kUpb_EncodedType_String = 15,
  kUpb_EncodedType_Group = 16,
  kUpb_EncodedType_Message = 17,
  kUpb_EncodedType_ClosedEnum = 18,

  kUpb_EncodedType_RepeatedBase = 20,
} upb_EncodedType;

typedef enum {
  kUpb_EncodedFieldModifier_FlipPacked = 1 << 0,
  kUpb_EncodedFieldModifier_IsRequired = 1 << 1,
  kUpb_EncodedFieldModifier_IsProto3Singular = 1 << 2,
  kUpb_EncodedFieldModifier_FlipValidateUtf8 = 1 << 3,
} upb_EncodedFieldModifier;

enum {
  kUpb_EncodedValue_MinField = ' ',
  kUpb_EncodedValue_MaxField = 'I',
  kUpb_EncodedValue_MinModifier = 'L',
  kUpb_EncodedValue_MaxModifier = '[',
  kUpb_EncodedValue_End = '^',
  kUpb_EncodedValue_MinSkip = '_',
  kUpb_EncodedValue_MaxSkip = '~',
  kUpb_EncodedValue_OneofSeparator = '~',
  kUpb_EncodedValue_FieldSeparator = '|',
  kUpb_EncodedValue_MinOneofField = ' ',
  kUpb_EncodedValue_MaxOneofField = 'b',
  kUpb_EncodedValue_MaxEnumMask = 'A',
};

enum {
  kUpb_EncodedVersion_EnumV1 = '!',
  kUpb_EncodedVersion_ExtensionV1 = '#',
  kUpb_EncodedVersion_MapV1 = '%',
  kUpb_EncodedVersion_MessageV1 = '$',
  kUpb_EncodedVersion_MessageSetV1 = '&',
};


#endif  // UPB_MINI_DESCRIPTOR_INTERNAL_WIRE_CONSTANTS_H_

#ifndef UPB_MINI_DESCRIPTOR_INTERNAL_ENCODE_H_
#define UPB_MINI_DESCRIPTOR_INTERNAL_ENCODE_H_

#include <stdint.h>


// Must be last.

// If the input buffer has at least this many bytes available, the encoder call
// is guaranteed to succeed (as long as field number order is maintained).
#define kUpb_MtDataEncoder_MinSize 16

typedef struct {
  char* end;  // Limit of the buffer passed as a parameter.
  // Aliased to internal-only members in .cc.
  char internal[32];
} upb_MtDataEncoder;

#ifdef __cplusplus
extern "C" {
#endif

// Encodes field/oneof information for a given message.  The sequence of calls
// should look like:
//
//   upb_MtDataEncoder e;
//   char buf[256];
//   char* ptr = buf;
//   e.end = ptr + sizeof(buf);
//   unit64_t msg_mod = ...; // bitwise & of kUpb_MessageModifiers or zero
//   ptr = upb_MtDataEncoder_StartMessage(&e, ptr, msg_mod);
//   // Fields *must* be in field number order.
//   ptr = upb_MtDataEncoder_PutField(&e, ptr, ...);
//   ptr = upb_MtDataEncoder_PutField(&e, ptr, ...);
//   ptr = upb_MtDataEncoder_PutField(&e, ptr, ...);
//
//   // If oneofs are present.  Oneofs must be encoded after regular fields.
//   ptr = upb_MiniTable_StartOneof(&e, ptr)
//   ptr = upb_MiniTable_PutOneofField(&e, ptr, ...);
//   ptr = upb_MiniTable_PutOneofField(&e, ptr, ...);
//
//   ptr = upb_MiniTable_StartOneof(&e, ptr);
//   ptr = upb_MiniTable_PutOneofField(&e, ptr, ...);
//   ptr = upb_MiniTable_PutOneofField(&e, ptr, ...);
//
// Oneofs must be encoded after all regular fields.
char* upb_MtDataEncoder_StartMessage(upb_MtDataEncoder* e, char* ptr,
                                     uint64_t msg_mod);
char* upb_MtDataEncoder_PutField(upb_MtDataEncoder* e, char* ptr,
                                 upb_FieldType type, uint32_t field_num,
                                 uint64_t field_mod);
char* upb_MtDataEncoder_StartOneof(upb_MtDataEncoder* e, char* ptr);
char* upb_MtDataEncoder_PutOneofField(upb_MtDataEncoder* e, char* ptr,
                                      uint32_t field_num);

// Encodes the set of values for a given enum. The values must be given in
// order (after casting to uint32_t), and repeats are not allowed.
char* upb_MtDataEncoder_StartEnum(upb_MtDataEncoder* e, char* ptr);
char* upb_MtDataEncoder_PutEnumValue(upb_MtDataEncoder* e, char* ptr,
                                     uint32_t val);
char* upb_MtDataEncoder_EndEnum(upb_MtDataEncoder* e, char* ptr);

// Encodes an entire mini descriptor for an extension.
char* upb_MtDataEncoder_EncodeExtension(upb_MtDataEncoder* e, char* ptr,
                                        upb_FieldType type, uint32_t field_num,
                                        uint64_t field_mod);

// Encodes an entire mini descriptor for a map.
char* upb_MtDataEncoder_EncodeMap(upb_MtDataEncoder* e, char* ptr,
                                  upb_FieldType key_type,
                                  upb_FieldType value_type, uint64_t key_mod,
                                  uint64_t value_mod);

// Encodes an entire mini descriptor for a message set.
char* upb_MtDataEncoder_EncodeMessageSet(upb_MtDataEncoder* e, char* ptr);

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /* UPB_MINI_DESCRIPTOR_INTERNAL_ENCODE_H_ */

#ifndef UPB_MINI_TABLE_COMPAT_H_
#define UPB_MINI_TABLE_COMPAT_H_


// Must be last.

// upb does not support mixing minitables from different sources but these
// functions are still used by some existing users so for now we make them
// available here. This may or may not change in the future so do not add
// them to new code.

#ifdef __cplusplus
extern "C" {
#endif

// Checks if memory layout of src is compatible with dst.
bool upb_MiniTable_Compatible(const upb_MiniTable* src,
                              const upb_MiniTable* dst);

typedef enum {
  kUpb_MiniTableEquals_NotEqual,
  kUpb_MiniTableEquals_Equal,
  kUpb_MiniTableEquals_OutOfMemory,
} upb_MiniTableEquals_Status;

// Checks equality of mini tables originating from different language runtimes.
upb_MiniTableEquals_Status upb_MiniTable_Equals(const upb_MiniTable* src,
                                                const upb_MiniTable* dst);

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /* UPB_MINI_TABLE_COMPAT_H_ */

#ifndef UPB_WIRE_INTERNAL_CONSTANTS_H_
#define UPB_WIRE_INTERNAL_CONSTANTS_H_

#define kUpb_WireFormat_DefaultDepthLimit 100

// MessageSet wire format is:
//   message MessageSet {
//     repeated group Item = 1 {
//       required int32 type_id = 2;
//       required bytes message = 3;
//     }
//   }

enum {
  kUpb_MsgSet_Item = 1,
  kUpb_MsgSet_TypeId = 2,
  kUpb_MsgSet_Message = 3,
};

#endif /* UPB_WIRE_INTERNAL_CONSTANTS_H_ */

/*
 * Internal implementation details of the decoder that are shared between
 * decode.c and decode_fast.c.
 */

#ifndef UPB_WIRE_INTERNAL_DECODER_H_
#define UPB_WIRE_INTERNAL_DECODER_H_

#include <setjmp.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "utf8_range.h"

// Must be last.

#define DECODE_NOGROUP (uint32_t)-1

typedef struct upb_Decoder {
  upb_EpsCopyInputStream input;
  const upb_ExtensionRegistry* extreg;
  upb_Message* original_msg;  // Pointer to preserve data to
  int depth;                  // Tracks recursion depth to bound stack usage.
  uint32_t end_group;  // field number of END_GROUP tag, else DECODE_NOGROUP.
  uint16_t options;
  bool missing_required;
  bool message_is_done;
  union {
    upb_Arena arena;
    void* foo[UPB_ARENA_SIZE_HACK];
  };
  upb_DecodeStatus status;
  jmp_buf err;

#ifndef NDEBUG
  const char* debug_tagstart;
  const char* debug_valstart;
  char* trace_ptr;
  char* trace_end;
#endif
} upb_Decoder;

UPB_INLINE const char* upb_Decoder_Init(upb_Decoder* d, const char* buf,
                                        size_t size,
                                        const upb_ExtensionRegistry* extreg,
                                        int options, upb_Arena* arena,
                                        char* trace_buf, size_t trace_size) {
  upb_EpsCopyInputStream_Init(&d->input, &buf, size,
                              options & kUpb_DecodeOption_AliasString);

  d->extreg = extreg;
  d->depth = upb_DecodeOptions_GetEffectiveMaxDepth(options);
  d->end_group = DECODE_NOGROUP;
  d->options = (uint16_t)options;
  d->missing_required = false;
  d->status = kUpb_DecodeStatus_Ok;
  d->message_is_done = false;
#ifndef NDEBUG
  d->trace_ptr = trace_buf;
  d->trace_end = UPB_PTRADD(trace_buf, trace_size);
#endif
  if (trace_buf) *trace_buf = 0;  // Null-terminate.

  // Violating the encapsulation of the arena for performance reasons.
  // This is a temporary arena that we swap into and swap out of when we are
  // done.  The temporary arena only needs to be able to handle allocation,
  // not fuse or free, so it does not need many of the members to be initialized
  // (particularly parent_or_count).
  UPB_PRIVATE(_upb_Arena_SwapIn)(&d->arena, arena);
  return buf;
}

UPB_INLINE upb_DecodeStatus upb_Decoder_Destroy(upb_Decoder* d,
                                                upb_Arena* arena) {
  UPB_PRIVATE(_upb_Arena_SwapOut)(arena, &d->arena);
  return d->status;
}

// Trace events are used to trace the progress of the decoder.
// Events:
//   'D'  Fast dispatch
//   'F'  Field successfully parsed fast.
//   '<'  Fallback to MiniTable parser.
//   'M'  Field successfully parsed with MiniTable.
//   'X'  Truncated -- trace buffer is full, further events were discarded.
UPB_INLINE void _upb_Decoder_Trace(upb_Decoder* d, char event) {
#ifndef NDEBUG
  if (d->trace_ptr == NULL) return;
  if (d->trace_ptr == d->trace_end - 1) {
    d->trace_ptr[-1] = 'X';  // Truncated.
    return;
  }
  d->trace_ptr[0] = event;
  d->trace_ptr[1] = '\0';
  d->trace_ptr++;
#endif
};

UPB_INLINE
bool _upb_Decoder_VerifyUtf8Inline(const char* ptr, int len) {
  return utf8_range_IsValid(ptr, len);
}

const char* _upb_Decoder_CheckRequired(upb_Decoder* d, const char* ptr,
                                       const upb_Message* msg,
                                       const upb_MiniTable* m);

/* x86-64 pointers always have the high 16 bits matching. So we can shift
 * left 8 and right 8 without loss of information. */
UPB_INLINE intptr_t decode_totable(const upb_MiniTable* tablep) {
  return ((intptr_t)tablep << 8) | tablep->UPB_PRIVATE(table_mask);
}

UPB_INLINE const upb_MiniTable* decode_totablep(intptr_t table) {
  return (const upb_MiniTable*)(table >> 8);
}

const char* _upb_Decoder_IsDoneFallback(upb_EpsCopyInputStream* e,
                                        const char* ptr, int overrun);

const char* _upb_Decoder_DecodeMessage(upb_Decoder* d, const char* ptr,
                                       upb_Message* msg,
                                       const upb_MiniTable* layout);

UPB_INLINE bool _upb_Decoder_IsDone(upb_Decoder* d, const char** ptr) {
  return upb_EpsCopyInputStream_IsDoneWithCallback(
      &d->input, ptr, &_upb_Decoder_IsDoneFallback);
}

UPB_NORETURN void* _upb_Decoder_ErrorJmp(upb_Decoder* d,
                                         upb_DecodeStatus status);

UPB_INLINE const char* _upb_Decoder_BufferFlipCallback(
    upb_EpsCopyInputStream* e, const char* old_end, const char* new_start) {
  upb_Decoder* d = (upb_Decoder*)e;
  if (!old_end) _upb_Decoder_ErrorJmp(d, kUpb_DecodeStatus_Malformed);
  return new_start;
}


#endif /* UPB_WIRE_INTERNAL_DECODER_H_ */
#ifndef GOOGLE_UPB_UPB_WIRE_WRITER_H__
#define GOOGLE_UPB_UPB_WIRE_WRITER_H__

#include <stdint.h>

// Must be last.

UPB_FORCEINLINE uint32_t
UPB_PRIVATE(upb_WireWriter_VarintUnusedSizeFromLeadingZeros64)(uint64_t clz) {
  // Calculate how many bytes of the possible 10 bytes we will *not* encode,
  // because they are part of a zero prefix. For the number 300, it would use 2
  // bytes encoded, so the number of bytes to skip would be 8. Adding 7 to the
  // clz input ensures that we're rounding up.
  return (((uint32_t)clz + 7) * 9) >> 6;
}


#endif  // GOOGLE_UPB_UPB_WIRE_WRITER_H__

#ifndef UPB_WIRE_BYTE_SIZE_H_
#define UPB_WIRE_BYTE_SIZE_H_

#include <stddef.h>


// Must be last.

#ifdef __cplusplus
extern "C" {
#endif

UPB_API size_t upb_ByteSize(const upb_Message* msg, const upb_MiniTable* mt);

#ifdef __cplusplus
}  // extern "C"
#endif


#endif  // UPB_WIRE_BYTE_SIZE_H_

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
