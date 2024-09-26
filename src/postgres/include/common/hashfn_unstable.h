/*
 * hashfn_unstable.h
 *
 * Building blocks for creating fast inlineable hash functions. The
 * functions in this file are not guaranteed to be stable between versions,
 * and may differ by hardware platform. Hence they must not be used in
 * indexes or other on-disk structures. See hashfn.h if you need stability.
 *
 *
 * Portions Copyright (c) 2024, PostgreSQL Global Development Group
 *
 * src/include/common/hashfn_unstable.h
 */
#ifndef HASHFN_UNSTABLE_H
#define HASHFN_UNSTABLE_H

#include "port/pg_bitutils.h"
#include "port/pg_bswap.h"

/*
 * fasthash is a modification of code taken from
 * https://code.google.com/archive/p/fast-hash/source/default/source
 * under the terms of the MIT license. The original copyright
 * notice follows:
 */

/* The MIT License

   Copyright (C) 2012 Zilong Tan (eric.zltan@gmail.com)

   Permission is hereby granted, free of charge, to any person
   obtaining a copy of this software and associated documentation
   files (the "Software"), to deal in the Software without
   restriction, including without limitation the rights to use, copy,
   modify, merge, publish, distribute, sublicense, and/or sell copies
   of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be
   included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
   NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
   BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
   ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
   CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.
*/

/*
 * fasthash as implemented here has two interfaces:
 *
 * 1) Standalone functions, e.g. fasthash32() for a single value with a
 * known length. These return the same hash code as the original, at
 * least on little-endian machines.
 *
 * 2) Incremental interface. This can used for incorporating multiple
 * inputs. First, initialize the hash state (here with a zero seed):
 *
 * fasthash_state hs;
 * fasthash_init(&hs, 0);
 *
 * If the inputs are of types that can be trivially cast to uint64, it's
 * sufficient to do:
 *
 * hs.accum = value1;
 * fasthash_combine(&hs);
 * hs.accum = value2;
 * fasthash_combine(&hs);
 * ...
 *
 * For longer or variable-length input, fasthash_accum() is a more
 * flexible, but more verbose method. The standalone functions use this
 * internally, so see fasthash64() for an example of this.
 *
 * After all inputs have been mixed in, finalize the hash:
 *
 * hashcode = fasthash_final32(&hs, 0);
 *
 * The incremental interface allows an optimization for NUL-terminated
 * C strings:
 *
 * len = fasthash_accum_cstring(&hs, str);
 * hashcode = fasthash_final32(&hs, len);
 *
 * By handling the terminator on-the-fly, we can avoid needing a strlen()
 * call to tell us how many bytes to hash. Experimentation has found that
 * SMHasher fails unless we incorporate the length, so it is passed to
 * the finalizer as a tweak.
 */


typedef struct fasthash_state
{
	/* staging area for chunks of input */
	uint64		accum;

	uint64		hash;
} fasthash_state;

#define FH_SIZEOF_ACCUM sizeof(uint64)


/*
 * Initialize the hash state.
 *
 * 'seed' can be zero.
 */
static inline void
fasthash_init(fasthash_state *hs, uint64 seed)
{
	memset(hs, 0, sizeof(fasthash_state));
	hs->hash = seed ^ 0x880355f21e6d1965;
}

/* both the finalizer and part of the combining step */
static inline uint64
fasthash_mix(uint64 h, uint64 tweak)
{
	h ^= (h >> 23) + tweak;
	h *= 0x2127599bf4325c37;
	h ^= h >> 47;
	return h;
}

/* combine one chunk of input into the hash */
static inline void
fasthash_combine(fasthash_state *hs)
{
	hs->hash ^= fasthash_mix(hs->accum, 0);
	hs->hash *= 0x880355f21e6d1965;
}

/* accumulate up to 8 bytes of input and combine it into the hash */
static inline void
fasthash_accum(fasthash_state *hs, const char *k, size_t len)
{
	uint32		lower_four;

	Assert(len <= FH_SIZEOF_ACCUM);
	hs->accum = 0;

	/*
	 * For consistency, bytewise loads must match the platform's endianness.
	 */
#ifdef WORDS_BIGENDIAN
	switch (len)
	{
		case 8:
			memcpy(&hs->accum, k, 8);
			break;
		case 7:
			hs->accum |= (uint64) k[6] << 8;
			/* FALLTHROUGH */
		case 6:
			hs->accum |= (uint64) k[5] << 16;
			/* FALLTHROUGH */
		case 5:
			hs->accum |= (uint64) k[4] << 24;
			/* FALLTHROUGH */
		case 4:
			memcpy(&lower_four, k, sizeof(lower_four));
			hs->accum |= (uint64) lower_four << 32;
			break;
		case 3:
			hs->accum |= (uint64) k[2] << 40;
			/* FALLTHROUGH */
		case 2:
			hs->accum |= (uint64) k[1] << 48;
			/* FALLTHROUGH */
		case 1:
			hs->accum |= (uint64) k[0] << 56;
			break;
		case 0:
			return;
	}
#else
	switch (len)
	{
		case 8:
			memcpy(&hs->accum, k, 8);
			break;
		case 7:
			hs->accum |= (uint64) k[6] << 48;
			/* FALLTHROUGH */
		case 6:
			hs->accum |= (uint64) k[5] << 40;
			/* FALLTHROUGH */
		case 5:
			hs->accum |= (uint64) k[4] << 32;
			/* FALLTHROUGH */
		case 4:
			memcpy(&lower_four, k, sizeof(lower_four));
			hs->accum |= lower_four;
			break;
		case 3:
			hs->accum |= (uint64) k[2] << 16;
			/* FALLTHROUGH */
		case 2:
			hs->accum |= (uint64) k[1] << 8;
			/* FALLTHROUGH */
		case 1:
			hs->accum |= (uint64) k[0];
			break;
		case 0:
			return;
	}
#endif

	fasthash_combine(hs);
}

/*
 * Set high bit in lowest byte where the input is zero, from:
 * https://graphics.stanford.edu/~seander/bithacks.html#ZeroInWord
 */
#define haszero64(v) \
	(((v) - 0x0101010101010101) & ~(v) & 0x8080808080808080)

/* get first byte in memory order */
#ifdef WORDS_BIGENDIAN
#define firstbyte64(v) ((v) >> 56)
#else
#define firstbyte64(v) ((v) & 0xFF)
#endif

/*
 * all-purpose workhorse for fasthash_accum_cstring
 */
static inline size_t
fasthash_accum_cstring_unaligned(fasthash_state *hs, const char *str)
{
	const char *const start = str;

	while (*str)
	{
		size_t		chunk_len = 0;

		while (chunk_len < FH_SIZEOF_ACCUM && str[chunk_len] != '\0')
			chunk_len++;

		fasthash_accum(hs, str, chunk_len);
		str += chunk_len;
	}

	return str - start;
}

/*
 * specialized workhorse for fasthash_accum_cstring
 *
 * With an aligned pointer, we consume the string a word at a time.
 * Loading the word containing the NUL terminator cannot segfault since
 * allocation boundaries are suitably aligned. To keep from setting
 * off alarms with address sanitizers, exclude this function from
 * such testing.
 */
pg_attribute_no_sanitize_address()
static inline size_t
fasthash_accum_cstring_aligned(fasthash_state *hs, const char *str)
{
	const char *const start = str;
	uint64		chunk;
	uint64		zero_byte_low;

	Assert(PointerIsAligned(start, uint64));

	/*
	 * For every chunk of input, check for zero bytes before mixing into the
	 * hash. The chunk with zeros must contain the NUL terminator. We arrange
	 * so that zero_byte_low tells us not only that a zero exists, but also
	 * where it is, so we can hash the remainder of the string.
	 *
	 * The haszero64 calculation will set bits corresponding to the lowest
	 * byte where a zero exists, so that suffices for little-endian machines.
	 * For big-endian machines, we would need bits set for the highest zero
	 * byte in the chunk, since the trailing junk past the terminator could
	 * contain additional zeros. haszero64 does not give us that, so we
	 * byteswap the chunk first.
	 */
	for (;;)
	{
		chunk = *(uint64 *) str;

#ifdef WORDS_BIGENDIAN
		zero_byte_low = haszero64(pg_bswap64(chunk));
#else
		zero_byte_low = haszero64(chunk);
#endif
		if (zero_byte_low)
			break;

		hs->accum = chunk;
		fasthash_combine(hs);
		str += FH_SIZEOF_ACCUM;
	}

	if (firstbyte64(chunk) != 0)
	{
		size_t		remainder;
		uint64		mask;

		/*
		 * The byte corresponding to the NUL will be 0x80, so the rightmost
		 * bit position will be in the range 15, 23, ..., 63. Turn this into
		 * byte position by dividing by 8.
		 */
		remainder = pg_rightmost_one_pos64(zero_byte_low) / BITS_PER_BYTE;

		/*
		 * Create a mask for the remaining bytes so we can combine them into
		 * the hash. This must have the same result as mixing the remaining
		 * bytes with fasthash_accum().
		 */
#ifdef WORDS_BIGENDIAN
		mask = ~UINT64CONST(0) << BITS_PER_BYTE * (FH_SIZEOF_ACCUM - remainder);
#else
		mask = ~UINT64CONST(0) >> BITS_PER_BYTE * (FH_SIZEOF_ACCUM - remainder);
#endif
		hs->accum = chunk & mask;
		fasthash_combine(hs);

		str += remainder;
	}

	return str - start;
}

/*
 * Mix 'str' into the hash state and return the length of the string.
 */
static inline size_t
fasthash_accum_cstring(fasthash_state *hs, const char *str)
{
#if SIZEOF_VOID_P >= 8

	size_t		len;
#ifdef USE_ASSERT_CHECKING
	size_t		len_check;
	fasthash_state hs_check;

	memcpy(&hs_check, hs, sizeof(fasthash_state));
	len_check = fasthash_accum_cstring_unaligned(&hs_check, str);
#endif
	if (PointerIsAligned(str, uint64))
	{
		len = fasthash_accum_cstring_aligned(hs, str);
		Assert(len_check == len);
		Assert(hs_check.hash == hs->hash);
		return len;
	}
#endif							/* SIZEOF_VOID_P */

	/*
	 * It's not worth it to try to make the word-at-a-time optimization work
	 * on 32-bit platforms.
	 */
	return fasthash_accum_cstring_unaligned(hs, str);
}

/*
 * The finalizer
 *
 * 'tweak' is intended to be the input length when the caller doesn't know
 * the length ahead of time, such as for NUL-terminated strings, otherwise
 * zero.
 */
static inline uint64
fasthash_final64(fasthash_state *hs, uint64 tweak)
{
	return fasthash_mix(hs->hash, tweak);
}

/*
 * Reduce a 64-bit hash to a 32-bit hash.
 *
 * This optional step provides a bit more additional mixing compared to
 * just taking the lower 32-bits.
 */
static inline uint32
fasthash_reduce32(uint64 h)
{
	/*
	 * Convert the 64-bit hashcode to Fermat residue, which shall retain
	 * information from both the higher and lower parts of hashcode.
	 */
	return h - (h >> 32);
}

/* finalize and reduce */
static inline uint32
fasthash_final32(fasthash_state *hs, uint64 tweak)
{
	return fasthash_reduce32(fasthash_final64(hs, tweak));
}

/*
 * The original fasthash64 function, re-implemented using the incremental
 * interface. Returns a 64-bit hashcode. 'len' controls not only how
 * many bytes to hash, but also modifies the internal seed.
 * 'seed' can be zero.
 */
static inline uint64
fasthash64(const char *k, size_t len, uint64 seed)
{
	fasthash_state hs;

	fasthash_init(&hs, 0);

	/* re-initialize the seed according to input length */
	hs.hash = seed ^ (len * 0x880355f21e6d1965);

	while (len >= FH_SIZEOF_ACCUM)
	{
		fasthash_accum(&hs, k, FH_SIZEOF_ACCUM);
		k += FH_SIZEOF_ACCUM;
		len -= FH_SIZEOF_ACCUM;
	}

	fasthash_accum(&hs, k, len);
	return fasthash_final64(&hs, 0);
}

/* like fasthash64, but returns a 32-bit hashcode */
static inline uint32
fasthash32(const char *k, size_t len, uint64 seed)
{
	return fasthash_reduce32(fasthash64(k, len, seed));
}

/*
 * Convenience function for hashing NUL-terminated strings
 */
static inline uint32
hash_string(const char *s)
{
	fasthash_state hs;
	size_t		s_len;

	fasthash_init(&hs, 0);

	/*
	 * Combine string into the hash and save the length for tweaking the final
	 * mix.
	 */
	s_len = fasthash_accum_cstring(&hs, s);

	return fasthash_final32(&hs, s_len);
}

#endif							/* HASHFN_UNSTABLE_H */
