
//  (C) Copyright Edward Diener 2011-2015
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(QOR_VMD_DETAIL_MATCH_IDENTIFIER_COMMON_H)
#define QOR_VMD_DETAIL_MATCH_IDENTIFIER_COMMON_H

#include "CompilerQOR/Preprocessor/preprocessor/cat.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/is_empty.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/idprefix.h"

#define QOR_VMD_DETAIL_MATCH_IDENTIFIER_OP_CREATE_ID_RESULT(id,keyid) \
    QOR_PP_CAT \
        ( \
        QOR_VMD_DETAIL_IDENTIFIER_DETECTION_PREFIX, \
        QOR_PP_CAT \
            ( \
            keyid, \
            QOR_PP_CAT \
                ( \
                _, \
                id \
                ) \
            ) \
        ) \
/**/

#define QOR_VMD_DETAIL_MATCH_IDENTIFIER_OP_CMP_IDS(id,keyid) \
    QOR_VMD_IS_EMPTY \
        ( \
        QOR_VMD_DETAIL_MATCH_IDENTIFIER_OP_CREATE_ID_RESULT(id,keyid) \
        ) \
/**/

#endif /* QOR_VMD_DETAIL_MATCH_IDENTIFIER_COMMON_H */
