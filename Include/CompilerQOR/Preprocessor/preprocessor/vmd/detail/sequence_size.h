
//  (C) Copyright Edward Diener 2011-2015
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(QOR_VMD_DETAIL_SEQUENCE_SIZE_H)
#define QOR_VMD_DETAIL_SEQUENCE_SIZE_H

#include "CompilerQOR/Preprocessor/preprocessor/array/size.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/sequence_to_array.h"

#define QOR_VMD_DETAIL_SEQUENCE_SIZE(vseq) \
    QOR_PP_ARRAY_SIZE(QOR_VMD_DETAIL_SEQUENCE_TO_ARRAY(vseq)) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_SIZE_D(d,vseq) \
    QOR_PP_ARRAY_SIZE(QOR_VMD_DETAIL_SEQUENCE_TO_ARRAY_D(d,vseq)) \
/**/

#endif /* QOR_VMD_DETAIL_SEQUENCE_SIZE_H */
