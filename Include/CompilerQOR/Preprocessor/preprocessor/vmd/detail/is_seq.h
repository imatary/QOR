
//  (C) Copyright Edward Diener 2011-2015
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(QOR_VMD_DETAIL_IS_SEQ_H)
#define QOR_VMD_DETAIL_IS_SEQ_H

#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/is_entire.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/seq.h"

#define QOR_VMD_DETAIL_IS_SEQ(seq) \
    QOR_VMD_DETAIL_IS_ENTIRE \
        ( \
        QOR_VMD_DETAIL_SEQ_SPLIT(seq) \
        ) \
/**/

#define QOR_VMD_DETAIL_IS_SEQ_D(d,seq) \
    QOR_VMD_DETAIL_IS_ENTIRE \
        ( \
        QOR_VMD_DETAIL_SEQ_SPLIT_D(d,seq) \
        ) \
/**/

#endif /* QOR_VMD_DETAIL_IS_SEQ_H */
