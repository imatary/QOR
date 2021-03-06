//def.h

# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Paul Mensonides 2002.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */

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

#ifndef QOR_PREPROCESSOR_SLOT_DETAIL_DEF_H_1
#define QOR_PREPROCESSOR_SLOT_DETAIL_DEF_H_1

//QOR_PP_SLOT_OFFSET_x

#define QOR_PP_SLOT_OFFSET_10(x) (x) % 1000000000UL
#define QOR_PP_SLOT_OFFSET_9(x) QOR_PP_SLOT_OFFSET_10(x) % 100000000UL
#define QOR_PP_SLOT_OFFSET_8(x) QOR_PP_SLOT_OFFSET_9(x) % 10000000UL
#define QOR_PP_SLOT_OFFSET_7(x) QOR_PP_SLOT_OFFSET_8(x) % 1000000UL
#define QOR_PP_SLOT_OFFSET_6(x) QOR_PP_SLOT_OFFSET_7(x) % 100000UL
#define QOR_PP_SLOT_OFFSET_5(x) QOR_PP_SLOT_OFFSET_6(x) % 10000UL
#define QOR_PP_SLOT_OFFSET_4(x) QOR_PP_SLOT_OFFSET_5(x) % 1000UL
#define QOR_PP_SLOT_OFFSET_3(x) QOR_PP_SLOT_OFFSET_4(x) % 100UL
#define QOR_PP_SLOT_OFFSET_2(x) QOR_PP_SLOT_OFFSET_3(x) % 10UL

//QOR_PP_SLOT_CC_x

#define QOR_PP_SLOT_CC_2(a, b) QOR_PP_SLOT_CC_2_D(a, b)
#define QOR_PP_SLOT_CC_3(a, b, c) QOR_PP_SLOT_CC_3_D(a, b, c)
#define QOR_PP_SLOT_CC_4(a, b, c, d) QOR_PP_SLOT_CC_4_D(a, b, c, d)
#define QOR_PP_SLOT_CC_5(a, b, c, d, e) QOR_PP_SLOT_CC_5_D(a, b, c, d, e)
#define QOR_PP_SLOT_CC_6(a, b, c, d, e, f) QOR_PP_SLOT_CC_6_D(a, b, c, d, e, f)
#define QOR_PP_SLOT_CC_7(a, b, c, d, e, f, g) QOR_PP_SLOT_CC_7_D(a, b, c, d, e, f, g)
#define QOR_PP_SLOT_CC_8(a, b, c, d, e, f, g, h) QOR_PP_SLOT_CC_8_D(a, b, c, d, e, f, g, h)
#define QOR_PP_SLOT_CC_9(a, b, c, d, e, f, g, h, i) QOR_PP_SLOT_CC_9_D(a, b, c, d, e, f, g, h, i)
#define QOR_PP_SLOT_CC_10(a, b, c, d, e, f, g, h, i, j) QOR_PP_SLOT_CC_10_D(a, b, c, d, e, f, g, h, i, j)

#define QOR_PP_SLOT_CC_2_D(a, b) a ## b
#define QOR_PP_SLOT_CC_3_D(a, b, c) a ## b ## c
#define QOR_PP_SLOT_CC_4_D(a, b, c, d) a ## b ## c ## d
#define QOR_PP_SLOT_CC_5_D(a, b, c, d, e) a ## b ## c ## d ## e
#define QOR_PP_SLOT_CC_6_D(a, b, c, d, e, f) a ## b ## c ## d ## e ## f
#define QOR_PP_SLOT_CC_7_D(a, b, c, d, e, f, g) a ## b ## c ## d ## e ## f ## g
#define QOR_PP_SLOT_CC_8_D(a, b, c, d, e, f, g, h) a ## b ## c ## d ## e ## f ## g ## h
#define QOR_PP_SLOT_CC_9_D(a, b, c, d, e, f, g, h, i) a ## b ## c ## d ## e ## f ## g ## h ## i
#define QOR_PP_SLOT_CC_10_D(a, b, c, d, e, f, g, h, i, j) a ## b ## c ## d ## e ## f ## g ## h ## i ## j

#endif//QOR_PREPROCESSOR_SLOT_DETAIL_DEF_H_1
