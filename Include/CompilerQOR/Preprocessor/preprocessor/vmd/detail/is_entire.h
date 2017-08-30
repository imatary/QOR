
//  (C) Copyright Edward Diener 2011-2015
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(QOR_VMD_DETAIL_IS_ENTIRE_H)
#define QOR_VMD_DETAIL_IS_ENTIRE_H

#include "CompilerQOR/Preprocessor/preprocessor/logical/bitand.h"
#include "CompilerQOR/Preprocessor/preprocessor/tuple/elem.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/is_empty.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/not_empty.h"

#define QOR_VMD_DETAIL_IS_ENTIRE(tuple) \
    QOR_PP_BITAND \
        ( \
        QOR_VMD_DETAIL_NOT_EMPTY(QOR_PP_TUPLE_ELEM(0,tuple)), \
        QOR_VMD_IS_EMPTY(QOR_PP_TUPLE_ELEM(1,tuple)) \
        ) \
/**/

#endif /* QOR_VMD_DETAIL_IS_ENTIRE_H */
