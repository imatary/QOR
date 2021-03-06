//endian_types.h

// Copyright Querysoft Limited 2013
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
//
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.


#ifndef SYSTEMQOR_LIN_TYPES_ENDIAN_H_3
#define SYSTEMQOR_LIN_TYPES_ENDIAN_H_3

#include "SystemQOR/Linux/LIN_features.h"

#define __LITTLE_ENDIAN 1234
#define __BIG_ENDIAN 4321
#define __PDP_ENDIAN 3412

#if defined(__GNUC__) && defined(__BYTE_ORDER__)
#	define __BYTE_ORDER __BYTE_ORDER__
#else
#include QOR_SYS_ARCHHEADER(endian.h)
#endif

#if defined(_GNU_SOURCE) || defined(_BSD_SOURCE)

#	define BIG_ENDIAN __BIG_ENDIAN
#	define LITTLE_ENDIAN __LITTLE_ENDIAN
#	define PDP_ENDIAN __PDP_ENDIAN
#	define BYTE_ORDER __BYTE_ORDER

#	include "SystemQOR/Linux/types/stdint_types.h"

#	if __BYTE_ORDER == __LITTLE_ENDIAN
#		define htobe16(x) __bswap16(x)
#		define be16toh(x) __bswap16(x)
#		define betoh16(x) __bswap16(x)
#		define htobe32(x) __bswap32(x)
#		define be32toh(x) __bswap32(x)
#		define betoh32(x) __bswap32(x)
#		define htobe64(x) __bswap64(x)
#		define be64toh(x) __bswap64(x)
#		define betoh64(x) __bswap64(x)
#		define htole16(x) (uint16_t)(x)
#		define le16toh(x) (uint16_t)(x)
#		define letoh16(x) (uint16_t)(x)
#		define htole32(x) (uint32_t)(x)
#		define le32toh(x) (uint32_t)(x)
#		define letoh32(x) (uint32_t)(x)
#		define htole64(x) (uint64_t)(x)
#		define le64toh(x) (uint64_t)(x)
#		define letoh64(x) (uint64_t)(x)
#	else
#		define htobe16(x) (uint16_t)(x)
#		define be16toh(x) (uint16_t)(x)
#		define betoh16(x) (uint16_t)(x)
#		define htobe32(x) (uint32_t)(x)
#		define be32toh(x) (uint32_t)(x)
#		define betoh32(x) (uint32_t)(x)
#		define htobe64(x) (uint64_t)(x)
#		define be64toh(x) (uint64_t)(x)
#		define betoh64(x) (uint64_t)(x)
#		define htole16(x) __bswap16(x)
#		define le16toh(x) __bswap16(x)
#		define letoh16(x) __bswap16(x)
#		define htole32(x) __bswap32(x)
#		define le32toh(x) __bswap32(x)
#		define letoh32(x) __bswap32(x)
#		define htole64(x) __bswap64(x)
#		define le64toh(x) __bswap64(x)
#		define letoh64(x) __bswap64(x)
#endif

#endif

#endif//SYSTEMQOR_LIN_TYPES_ENDIAN_H_3
