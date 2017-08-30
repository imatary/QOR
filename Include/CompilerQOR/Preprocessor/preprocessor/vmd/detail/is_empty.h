
//  (C) Copyright Edward Diener 2011-2015
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(QOR_VMD_DETAIL_IS_EMPTY_H)
#define QOR_VMD_DETAIL_IS_EMPTY_H

#include "CompilerQOR/Preprocessor/preprocessor/punctuation/is_begin_parens.h"

#if QOR_VMD_MSVC

//# pragma warning(once:4002)

#define QOR_VMD_DETAIL_IS_EMPTY_IIF_0(t, b) b
#define QOR_VMD_DETAIL_IS_EMPTY_IIF_1(t, b) t

#if QOR_VMD_MSVC_V8

#define QOR_VMD_DETAIL_IS_EMPTY_PROCESS(param) \
    QOR_PP_IS_BEGIN_PARENS \
        ( \
        QOR_VMD_DETAIL_IS_EMPTY_NON_FUNCTION_C param () \
        ) \
/**/

#else

#define QOR_VMD_DETAIL_IS_EMPTY_PROCESS(...) \
    QOR_PP_IS_BEGIN_PARENS \
        ( \
        QOR_VMD_DETAIL_IS_EMPTY_NON_FUNCTION_C __VA_ARGS__ () \
        ) \
/**/

#endif

#else

#define QOR_VMD_DETAIL_IS_EMPTY_IIF_0(t, ...) __VA_ARGS__
#define QOR_VMD_DETAIL_IS_EMPTY_IIF_1(t, ...) t

#define QOR_VMD_DETAIL_IS_EMPTY_PROCESS(...) \
    QOR_PP_IS_BEGIN_PARENS \
        ( \
        QOR_VMD_DETAIL_IS_EMPTY_NON_FUNCTION_C __VA_ARGS__ () \
        ) \
/**/

#endif /* QOR_VMD_MSVC */

#define QOR_VMD_DETAIL_IS_EMPTY_PRIMITIVE_CAT(a, b) a ## b
#define QOR_VMD_DETAIL_IS_EMPTY_IIF(bit) \
    QOR_VMD_DETAIL_IS_EMPTY_PRIMITIVE_CAT(QOR_VMD_DETAIL_IS_EMPTY_IIF_,bit) \
/**/

#define QOR_VMD_DETAIL_IS_EMPTY_NON_FUNCTION_C(...) ()
#define QOR_VMD_DETAIL_IS_EMPTY_GEN_ZERO(...) 0

#endif /* QOR_VMD_DETAIL_IS_EMPTY_H */
