
//  (C) Copyright Edward Diener 2011-2015
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(QOR_VMD_DETAIL_NOT_EMPTY_H)
#define QOR_VMD_DETAIL_NOT_EMPTY_H

#include "CompilerQOR/Preprocessor/preprocessor/logical/compl.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/is_empty.h"

#define QOR_VMD_DETAIL_NOT_EMPTY(par) \
    QOR_PP_COMPL \
        ( \
        QOR_VMD_IS_EMPTY(par) \
        ) \
/**/

#endif /* QOR_VMD_DETAIL_NOT_EMPTY_H */
