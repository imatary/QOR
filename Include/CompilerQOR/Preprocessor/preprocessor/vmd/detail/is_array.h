
//  (C) Copyright Edward Diener 2011-2015
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(QOR_VMD_DETAIL_IS_ARRAY_H)
#define QOR_VMD_DETAIL_IS_ARRAY_H

#include "CompilerQOR/Preprocessor/preprocessor/control/iif.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/identity.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/is_tuple.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/is_array_common.h"

#define QOR_VMD_DETAIL_IS_ARRAY(vseq) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_VMD_IS_TUPLE(vseq), \
            QOR_VMD_DETAIL_IS_ARRAY_SYNTAX, \
            QOR_VMD_IDENTITY(0) \
            ) \
        (vseq) \
        ) \
/**/

#define QOR_VMD_DETAIL_IS_ARRAY_D(d,vseq) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_VMD_IS_TUPLE(vseq), \
            QOR_VMD_DETAIL_IS_ARRAY_SYNTAX_D, \
            QOR_VMD_IDENTITY(0) \
            ) \
        (d,vseq) \
        ) \
/**/

#endif /* QOR_VMD_DETAIL_IS_ARRAY_H */
