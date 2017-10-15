// is_begin_parens.h

#/* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2014.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
#/* See http://www.boost.org for most recent version. */

// Copyright Querysoft Limited 2017
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

#ifndef QOR_PREPROCESSOR_DETAIL_IS_BEGIN_PARENS_H
#define QOR_PREPROCESSOR_DETAIL_IS_BEGIN_PARENS_H

#if QOR_PP_VARIADICS_MSVC

#include "CompilerQOR/Preprocessor/preprocessor/facilities/empty.h"

#define QOR_PP_DETAIL_VD_IBP_CAT( a, b ) QOR_PP_DETAIL_VD_IBP_CAT_I( a, b )
#define QOR_PP_DETAIL_VD_IBP_CAT_I( a, b ) QOR_PP_DETAIL_VD_IBP_CAT_II( a##b )
#define QOR_PP_DETAIL_VD_IBP_CAT_II( res ) res

#define QOR_PP_DETAIL_IBP_SPLIT( i, ... )                                                                              \
	QOR_PP_DETAIL_VD_IBP_CAT(                                                                                          \
	    QOR_PP_DETAIL_IBP_PRIMITIVE_CAT( QOR_PP_DETAIL_IBP_SPLIT_, i )( __VA_ARGS__ ), QOR_PP_EMPTY() ) \
/**/

#define QOR_PP_DETAIL_IBP_IS_VARIADIC_C( ... ) 1 1

#else

#define QOR_PP_DETAIL_IBP_SPLIT( i, ... )                                                                              \
	QOR_PP_DETAIL_IBP_PRIMITIVE_CAT( QOR_PP_DETAIL_IBP_SPLIT_, i )                                                     \
	( __VA_ARGS__ ) \
/**/

#define QOR_PP_DETAIL_IBP_IS_VARIADIC_C( ... ) 1

#endif /* QOR_PP_VARIADICS_MSVC */

#define QOR_PP_DETAIL_IBP_SPLIT_0( a, ... ) a
#define QOR_PP_DETAIL_IBP_SPLIT_1( a, ... ) __VA_ARGS__

#define QOR_PP_DETAIL_IBP_CAT( a, ... ) QOR_PP_DETAIL_IBP_PRIMITIVE_CAT( a, __VA_ARGS__ )
#define QOR_PP_DETAIL_IBP_PRIMITIVE_CAT( a, ... ) a##__VA_ARGS__

#define QOR_PP_DETAIL_IBP_IS_VARIADIC_R_1 1,
#define QOR_PP_DETAIL_IBP_IS_VARIADIC_R_QOR_PP_DETAIL_IBP_IS_VARIADIC_C 0,

#endif // QOR_PREPROCESSOR_DETAIL_IS_BEGIN_PARENS_H