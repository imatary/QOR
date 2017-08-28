
//  (C) Copyright Edward Diener 2011-2015
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(QOR_VMD_DETAIL_EQUAL_12_H)
#define QOR_VMD_DETAIL_EQUAL_12_H

#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/recurse/equal/equal_headers.h"

#define QOR_VMD_DETAIL_EQUAL_12_CNI_CHK(vseq1,vseq2,vtype) \
    QOR_PP_IIF \
        ( \
        QOR_PP_BITOR \
            ( \
            QOR_PP_BITOR \
                ( \
                QOR_VMD_DETAIL_EQUAL_TYPE(vtype,QOR_VMD_TYPE_ARRAY), \
                QOR_VMD_DETAIL_EQUAL_TYPE(vtype,QOR_VMD_TYPE_LIST) \
                ), \
            QOR_PP_BITOR \
                ( \
                QOR_VMD_DETAIL_EQUAL_TYPE(vtype,QOR_VMD_TYPE_SEQ), \
                QOR_VMD_DETAIL_EQUAL_TYPE(vtype,QOR_VMD_TYPE_TUPLE) \
                ) \
            ), \
        QOR_VMD_DETAIL_DATA_EQUAL_12, \
        QOR_VMD_DETAIL_EQUAL_CNI_SMP \
        ) \
    (vseq1,vseq2,vtype) \
/**/

#define QOR_VMD_DETAIL_EQUAL_12_CNI_CHK_D(d,vseq1,vseq2,vtype) \
    QOR_PP_IIF \
        ( \
        QOR_PP_BITOR \
            ( \
            QOR_PP_BITOR \
                ( \
                QOR_VMD_DETAIL_EQUAL_TYPE_D(d,vtype,QOR_VMD_TYPE_ARRAY), \
                QOR_VMD_DETAIL_EQUAL_TYPE_D(d,vtype,QOR_VMD_TYPE_LIST) \
                ), \
            QOR_PP_BITOR \
                ( \
                QOR_VMD_DETAIL_EQUAL_TYPE_D(d,vtype,QOR_VMD_TYPE_SEQ), \
                QOR_VMD_DETAIL_EQUAL_TYPE_D(d,vtype,QOR_VMD_TYPE_TUPLE) \
                ) \
            ), \
        QOR_VMD_DETAIL_DATA_EQUAL_12_D, \
        QOR_VMD_DETAIL_EQUAL_CNI_SMP_D \
        ) \
    (d,vseq1,vseq2,vtype) \
/**/

#define QOR_VMD_DETAIL_EQUAL_12_VSEQ(vseq1,vseq2,vtype) \
    QOR_VMD_DETAIL_DATA_EQUAL_12 \
        ( \
        QOR_VMD_TO_SEQ(vseq1), \
        QOR_VMD_TO_SEQ(vseq2), \
        QOR_VMD_TYPE_SEQ \
        ) \
/**/

#define QOR_VMD_DETAIL_EQUAL_12_VSEQ_D(d,vseq1,vseq2,vtype) \
    QOR_VMD_DETAIL_DATA_EQUAL_12_D \
        ( \
        d, \
        QOR_VMD_TO_SEQ_D(d,vseq1), \
        QOR_VMD_TO_SEQ_D(d,vseq2), \
        QOR_VMD_TYPE_SEQ \
        ) \
/**/

#define QOR_VMD_DETAIL_EQUAL_12_CNI(vseq1,vseq2,vtype) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_EQUAL_TYPE \
            ( \
            vtype, \
            QOR_VMD_TYPE_SEQUENCE \
            ), \
        QOR_VMD_DETAIL_EQUAL_12_VSEQ, \
        QOR_VMD_DETAIL_EQUAL_12_CNI_CHK \
        ) \
    (vseq1,vseq2,vtype) \
/**/

#define QOR_VMD_DETAIL_EQUAL_12_CNI_D(d,vseq1,vseq2,vtype) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_EQUAL_TYPE_D \
            ( \
            d, \
            vtype, \
            QOR_VMD_TYPE_SEQUENCE \
            ), \
        QOR_VMD_DETAIL_EQUAL_12_VSEQ_D, \
        QOR_VMD_DETAIL_EQUAL_12_CNI_CHK_D \
        ) \
    (d,vseq1,vseq2,vtype) \
/**/

#define QOR_VMD_DETAIL_EQUAL_12_WT_CHECK(vseq1,vseq2,vtype1,vtype2) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_VMD_DETAIL_EQUAL_TYPE \
                ( \
                vtype1, \
                vtype2 \
                ), \
            QOR_VMD_DETAIL_EQUAL_12_CNI, \
            QOR_VMD_IDENTITY(0) \
            ) \
        (vseq1,vseq2,vtype1) \
        ) \
/**/

#define QOR_VMD_DETAIL_EQUAL_12_WT_CHECK_D(d,vseq1,vseq2,vtype1,vtype2) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_VMD_DETAIL_EQUAL_TYPE_D \
                ( \
                d, \
                vtype1, \
                vtype2 \
                ), \
            QOR_VMD_DETAIL_EQUAL_12_CNI_D, \
            QOR_VMD_IDENTITY(0) \
            ) \
        (d,vseq1,vseq2,vtype1) \
        ) \
/**/

#define QOR_VMD_DETAIL_EQUAL_12_WT_CONVERT(vseq1,vseq2,vtype1,vtype2) \
    QOR_VMD_DETAIL_EQUAL_12_WT_CHECK \
        ( \
        vseq1, \
        vseq2, \
        QOR_VMD_DETAIL_ADJUST_TUPLE_TYPE(vseq1,vtype1), \
        QOR_VMD_DETAIL_ADJUST_TUPLE_TYPE(vseq2,vtype2) \
        ) \
/**/

#define QOR_VMD_DETAIL_EQUAL_12_WT_CONVERT_D(d,vseq1,vseq2,vtype1,vtype2) \
    QOR_VMD_DETAIL_EQUAL_12_WT_CHECK_D \
        ( \
        d, \
        vseq1, \
        vseq2, \
        QOR_VMD_DETAIL_ADJUST_TUPLE_TYPE_D(d,vseq1,vtype1), \
        QOR_VMD_DETAIL_ADJUST_TUPLE_TYPE_D(d,vseq2,vtype2) \
        ) \
/**/

#define QOR_VMD_DETAIL_EQUAL_12_WT(vseq1,vseq2,vtype1,vtype2) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_VMD_DETAIL_EQUAL_IS_TUPLE_MISMATCH(vseq1,vseq2,vtype1,vtype2), \
            QOR_VMD_IDENTITY(0), \
            QOR_VMD_DETAIL_EQUAL_12_WT_CONVERT \
            ) \
        (vseq1,vseq2,vtype1,vtype2) \
        ) \
/**/

#define QOR_VMD_DETAIL_EQUAL_12_WT_D(d,vseq1,vseq2,vtype1,vtype2) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_VMD_DETAIL_EQUAL_IS_TUPLE_MISMATCH_D(d,vseq1,vseq2,vtype1,vtype2), \
            QOR_VMD_IDENTITY(0), \
            QOR_VMD_DETAIL_EQUAL_12_WT_CONVERT_D \
            ) \
        (d,vseq1,vseq2,vtype1,vtype2) \
        ) \
/**/

#define QOR_VMD_DETAIL_EQUAL_12_GTYPE(vseq1,vseq2) \
    QOR_VMD_DETAIL_EQUAL_12_WT \
        ( \
        vseq1, \
        vseq2, \
        QOR_VMD_GET_TYPE(vseq1,QOR_VMD_RETURN_TYPE_TUPLE), \
        QOR_VMD_GET_TYPE(vseq2,QOR_VMD_RETURN_TYPE_TUPLE) \
        ) \
/**/

#define QOR_VMD_DETAIL_EQUAL_12_GTYPE_D(d,vseq1,vseq2) \
    QOR_VMD_DETAIL_EQUAL_12_WT_D \
        ( \
        d, \
        vseq1, \
        vseq2, \
        QOR_VMD_GET_TYPE_D(d,vseq1,QOR_VMD_RETURN_TYPE_TUPLE), \
        QOR_VMD_GET_TYPE_D(d,vseq2,QOR_VMD_RETURN_TYPE_TUPLE) \
        ) \
/**/

#define QOR_VMD_DETAIL_EQUAL_12_EBP(vseq1,vseq2,be1,be2) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_PP_BITAND \
                ( \
                QOR_VMD_DETAIL_EQUAL_CHK_MATCH(be1,be2), \
                QOR_VMD_DETAIL_EQUAL_CHK_PARENS_MATCH(vseq1,vseq2) \
                ), \
            QOR_VMD_DETAIL_EQUAL_12_GTYPE, \
            QOR_VMD_IDENTITY(0) \
            ) \
        (vseq1,vseq2) \
        ) \
/**/

#define QOR_VMD_DETAIL_EQUAL_12_EBP_D(d,vseq1,vseq2,be1,be2) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_PP_BITAND \
                ( \
                QOR_VMD_DETAIL_EQUAL_CHK_MATCH(be1,be2), \
                QOR_VMD_DETAIL_EQUAL_CHK_PARENS_MATCH(vseq1,vseq2) \
                ), \
            QOR_VMD_DETAIL_EQUAL_12_GTYPE_D, \
            QOR_VMD_IDENTITY(0) \
            ) \
        (d,vseq1,vseq2) \
        ) \
/**/

#define QOR_VMD_DETAIL_EQUAL_12_EMPTY(vseq1,vseq2,be1,be2) \
    QOR_PP_IIF \
        ( \
        QOR_PP_BITAND(be1,be2), \
        QOR_VMD_DETAIL_EQUAL_BOTH_EMPTY, \
        QOR_VMD_DETAIL_EQUAL_12_EBP \
        ) \
    (vseq1,vseq2,be1,be2) \
/**/

#define QOR_VMD_DETAIL_EQUAL_12_EMPTY_D(d,vseq1,vseq2,be1,be2) \
    QOR_PP_IIF \
        ( \
        QOR_PP_BITAND(be1,be2), \
        QOR_VMD_DETAIL_EQUAL_BOTH_EMPTY, \
        QOR_VMD_DETAIL_EQUAL_12_EBP_D \
        ) \
    (d,vseq1,vseq2,be1,be2) \
/**/

#define QOR_VMD_DETAIL_EQUAL_12(vseq1,vseq2) \
    QOR_VMD_DETAIL_EQUAL_12_EMPTY \
        ( \
        vseq1, \
        vseq2, \
        QOR_VMD_IS_EMPTY(vseq1), \
        QOR_VMD_IS_EMPTY(vseq2) \
        ) \
/**/

#define QOR_VMD_DETAIL_EQUAL_12_D(d,vseq1,vseq2) \
    QOR_VMD_DETAIL_EQUAL_12_EMPTY_D \
        ( \
        d, \
        vseq1, \
        vseq2, \
        QOR_VMD_IS_EMPTY(vseq1), \
        QOR_VMD_IS_EMPTY(vseq2) \
        ) \
/**/

#endif /* QOR_VMD_DETAIL_EQUAL_12_H */
