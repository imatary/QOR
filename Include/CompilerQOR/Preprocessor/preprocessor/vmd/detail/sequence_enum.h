
//  (C) Copyright Edward Diener 2011-2015
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(QOR_VMD_DETAIL_SEQUENCE_ENUM_H)
#define QOR_VMD_DETAIL_SEQUENCE_ENUM_H

#include "CompilerQOR/Preprocessor/preprocessor/control/iif.h"
#include "CompilerQOR/Preprocessor/preprocessor/tuple/enum.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/empty.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/is_empty.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/sequence_to_tuple.h"

#define QOR_VMD_DETAIL_SEQUENCE_ENUM_PROCESS(tuple) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_IS_EMPTY(tuple), \
        QOR_VMD_EMPTY, \
        QOR_PP_TUPLE_ENUM \
        ) \
    (tuple) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ENUM(...) \
    QOR_VMD_DETAIL_SEQUENCE_ENUM_PROCESS \
        ( \
        QOR_VMD_DETAIL_SEQUENCE_TO_TUPLE(__VA_ARGS__) \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ENUM_D(d,...) \
    QOR_VMD_DETAIL_SEQUENCE_ENUM_PROCESS \
        ( \
        QOR_VMD_DETAIL_SEQUENCE_TO_TUPLE_D(d,__VA_ARGS__) \
        ) \
/**/

#endif /* QOR_VMD_DETAIL_SEQUENCE_ENUM_H */
