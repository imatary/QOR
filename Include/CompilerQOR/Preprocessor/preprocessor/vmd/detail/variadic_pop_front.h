
//  (C) Copyright Edward Diener 2011-2015
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(QOR_VMD_DETAIL_VARIADIC_POP_FRONT_H)
#define QOR_VMD_DETAIL_VARIADIC_POP_FRONT_H

#include "CompilerQOR/Preprocessor/preprocessor/tuple/enum.h"
#include "CompilerQOR/Preprocessor/preprocessor/tuple/pop_front.h"
#include "CompilerQOR/Preprocessor/preprocessor/variadic/to_tuple.h"

#define QOR_VMD_DETAIL_VARIADIC_POP_FRONT(...) \
    QOR_PP_TUPLE_ENUM \
        ( \
        QOR_PP_TUPLE_POP_FRONT \
            ( \
            QOR_PP_VARIADIC_TO_TUPLE(__VA_ARGS__) \
            ) \
        ) \
/**/

#endif /* QOR_VMD_DETAIL_VARIADIC_POP_FRONT_H */
