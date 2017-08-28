
//  (C) Copyright Edward Diener 2011-2015
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(QOR_VMD_DETAIL_IS_EMPTY_ARRAY_H)
#define QOR_VMD_DETAIL_IS_EMPTY_ARRAY_H

#include "CompilerQOR/Preprocessor/preprocessor/array/size.h"
#include "CompilerQOR/Preprocessor/preprocessor/logical/not.h"

#define QOR_VMD_DETAIL_IS_EMPTY_ARRAY_SIZE(array) \
    QOR_PP_NOT \
        ( \
        QOR_PP_ARRAY_SIZE(array) \
        ) \
/**/

#endif /* QOR_VMD_DETAIL_IS_EMPTY_ARRAY_H */
