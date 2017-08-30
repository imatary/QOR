
//  (C) Copyright Edward Diener 2011-2015
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(QOR_VMD_DETAIL_EQUAL_COMMON_H)
#define QOR_VMD_DETAIL_EQUAL_COMMON_H

#include "CompilerQOR/Preprocessor/preprocessor/cat.h"
#include "CompilerQOR/Preprocessor/preprocessor/comparison/equal.h"
#include "CompilerQOR/Preprocessor/preprocessor/comparison/not_equal.h"
#include "CompilerQOR/Preprocessor/preprocessor/control/iif.h"
#include "CompilerQOR/Preprocessor/preprocessor/logical/bitand.h"
#include "CompilerQOR/Preprocessor/preprocessor/logical/bitor.h"
#include "CompilerQOR/Preprocessor/preprocessor/logical/bitxor.h"
#include "CompilerQOR/Preprocessor/preprocessor/logical/compl.h"
#include "CompilerQOR/Preprocessor/preprocessor/punctuation/is_begin_parens.h"
#include "CompilerQOR/Preprocessor/preprocessor/tuple/size.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/get_type.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/identity.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/is_empty.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/match_single_identifier.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/equal_type.h"

#define QOR_VMD_DETAIL_EQUAL_CONCAT_1 (1)

#define QOR_VMD_DETAIL_EQUAL_IS_1(res) \
    QOR_PP_IS_BEGIN_PARENS \
        ( \
        QOR_PP_CAT \
            ( \
            QOR_VMD_DETAIL_EQUAL_CONCAT_, \
            res \
            ) \
        ) \
/**/

#define QOR_VMD_DETAIL_EQUAL_MATCH_SINGLE_IDENTIFIER(d,vseq1,vseq2) \
    QOR_VMD_DETAIL_MATCH_SINGLE_IDENTIFIER(vseq1,vseq2) \
/**/

#define QOR_VMD_DETAIL_EQUAL_CNI_SMP(vseq1,vseq2,vtype) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_EQUAL_TYPE(vtype,QOR_VMD_TYPE_NUMBER), \
        QOR_PP_EQUAL, \
        QOR_PP_IIF \
            ( \
            QOR_VMD_DETAIL_EQUAL_TYPE(vtype,QOR_VMD_TYPE_TYPE), \
            QOR_VMD_DETAIL_EQUAL_TYPE, \
            QOR_VMD_DETAIL_MATCH_SINGLE_IDENTIFIER \
            ) \
        ) \
    (vseq1,vseq2) \
/**/

#define QOR_VMD_DETAIL_EQUAL_CNI_SMP_D(d,vseq1,vseq2,vtype) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_EQUAL_TYPE_D(d,vtype,QOR_VMD_TYPE_NUMBER), \
        QOR_PP_EQUAL_D, \
        QOR_PP_IIF \
            ( \
            QOR_VMD_DETAIL_EQUAL_TYPE_D(d,vtype,QOR_VMD_TYPE_TYPE), \
            QOR_VMD_DETAIL_EQUAL_TYPE_D, \
            QOR_VMD_DETAIL_EQUAL_MATCH_SINGLE_IDENTIFIER \
            ) \
        ) \
    (d,vseq1,vseq2) \
/**/

#define QOR_VMD_DETAIL_EQUAL_IS_TUPLE_MISMATCH_SIZE(vseq1,vseq2) \
    QOR_PP_NOT_EQUAL \
        ( \
        QOR_PP_TUPLE_SIZE(vseq1), \
        QOR_PP_TUPLE_SIZE(vseq2) \
        ) \
/**/

#define QOR_VMD_DETAIL_EQUAL_IS_TUPLE_MISMATCH_SIZE_D(d,vseq1,vseq2) \
    QOR_PP_NOT_EQUAL_D \
        ( \
        d, \
        QOR_PP_TUPLE_SIZE(vseq1), \
        QOR_PP_TUPLE_SIZE(vseq2) \
        ) \
/**/

#define QOR_VMD_DETAIL_EQUAL_IS_TUPLE_MISMATCH(vseq1,vseq2,vtype1,vtype2) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_PP_BITAND \
                ( \
                QOR_VMD_DETAIL_EQUAL_TYPE(vtype1,QOR_VMD_TYPE_TUPLE), \
                QOR_VMD_DETAIL_EQUAL_TYPE(vtype2,QOR_VMD_TYPE_TUPLE) \
                ), \
            QOR_VMD_DETAIL_EQUAL_IS_TUPLE_MISMATCH_SIZE, \
            QOR_VMD_IDENTITY(0) \
            ) \
        (vseq1,vseq2) \
        ) \
/**/

#define QOR_VMD_DETAIL_EQUAL_IS_TUPLE_MISMATCH_D(d,vseq1,vseq2,vtype1,vtype2) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_PP_BITAND \
                ( \
                QOR_VMD_DETAIL_EQUAL_TYPE_D(d,vtype1,QOR_VMD_TYPE_TUPLE), \
                QOR_VMD_DETAIL_EQUAL_TYPE_D(d,vtype2,QOR_VMD_TYPE_TUPLE) \
                ), \
            QOR_VMD_DETAIL_EQUAL_IS_TUPLE_MISMATCH_SIZE_D, \
            QOR_VMD_IDENTITY(0) \
            ) \
        (d,vseq1,vseq2) \
        ) \
/**/

#define QOR_VMD_DETAIL_EQUAL_BOTH_EMPTY(...) 1

#define QOR_VMD_DETAIL_EQUAL_CHK_MATCH(bp1,bp2) \
    QOR_PP_COMPL \
        ( \
        QOR_PP_BITXOR \
            ( \
            bp1, \
            bp2 \
            ) \
        ) \
/**/

#define QOR_VMD_DETAIL_EQUAL_CHK_PARENS_MATCH(vseq1,vseq2) \
    QOR_VMD_DETAIL_EQUAL_CHK_MATCH \
        ( \
        QOR_PP_IS_BEGIN_PARENS(vseq1), \
        QOR_PP_IS_BEGIN_PARENS(vseq2) \
        ) \
/**/

#define QOR_VMD_DETAIL_EQUAL_CHK_EMPTY_MATCH(vseq1,vseq2) \
    QOR_VMD_DETAIL_EQUAL_CHK_MATCH \
        ( \
        QOR_VMD_IS_EMPTY(vseq1), \
        QOR_VMD_IS_EMPTY(vseq2) \
        ) \
/**/

#endif /* QOR_VMD_DETAIL_EQUAL_COMMON_H */
