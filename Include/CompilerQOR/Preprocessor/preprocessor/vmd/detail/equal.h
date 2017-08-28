
//  (C) Copyright Edward Diener 2011-2015
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(QOR_VMD_DETAIL_EQUAL_H)
#define QOR_VMD_DETAIL_EQUAL_H

#include "CompilerQOR/Preprocessor/preprocessor/cat.h"
#include "CompilerQOR/Preprocessor/preprocessor/detail/auto_rec.h"
#include "CompilerQOR/Preprocessor/preprocessor/facilities/empty.h"
#include "CompilerQOR/Preprocessor/preprocessor/facilities/overload.h"
#include "CompilerQOR/Preprocessor/preprocessor/logical/compl.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/recurse/equal/equal_headers.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/is_identifier.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/is_empty_list.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/not_empty.h"

#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/recurse/equal/equal_1.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/recurse/equal/equal_2.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/recurse/equal/equal_3.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/recurse/equal/equal_4.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/recurse/equal/equal_5.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/recurse/equal/equal_6.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/recurse/equal/equal_7.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/recurse/equal/equal_8.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/recurse/equal/equal_9.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/recurse/equal/equal_10.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/recurse/equal/equal_11.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/recurse/equal/equal_12.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/recurse/equal/equal_13.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/recurse/equal/equal_14.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/recurse/equal/equal_15.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/recurse/equal/equal_16.h"

#define QOR_VMD_DETAIL_EQUAL_SIMPLE_D_1(d,vseq1,vseq2) QOR_VMD_DETAIL_EQUAL_1_D(d,vseq1,vseq2)
#define QOR_VMD_DETAIL_EQUAL_SIMPLE_D_2(d,vseq1,vseq2) QOR_VMD_DETAIL_EQUAL_2_D(d,vseq1,vseq2)
#define QOR_VMD_DETAIL_EQUAL_SIMPLE_D_3(d,vseq1,vseq2) QOR_VMD_DETAIL_EQUAL_3_D(d,vseq1,vseq2)
#define QOR_VMD_DETAIL_EQUAL_SIMPLE_D_4(d,vseq1,vseq2) QOR_VMD_DETAIL_EQUAL_4_D(d,vseq1,vseq2)
#define QOR_VMD_DETAIL_EQUAL_SIMPLE_D_5(d,vseq1,vseq2) QOR_VMD_DETAIL_EQUAL_5_D(d,vseq1,vseq2)
#define QOR_VMD_DETAIL_EQUAL_SIMPLE_D_6(d,vseq1,vseq2) QOR_VMD_DETAIL_EQUAL_6_D(d,vseq1,vseq2)
#define QOR_VMD_DETAIL_EQUAL_SIMPLE_D_7(d,vseq1,vseq2) QOR_VMD_DETAIL_EQUAL_7_D(d,vseq1,vseq2)
#define QOR_VMD_DETAIL_EQUAL_SIMPLE_D_8(d,vseq1,vseq2) QOR_VMD_DETAIL_EQUAL_8_D(d,vseq1,vseq2)
#define QOR_VMD_DETAIL_EQUAL_SIMPLE_D_9(d,vseq1,vseq2) QOR_VMD_DETAIL_EQUAL_9_D(d,vseq1,vseq2)
#define QOR_VMD_DETAIL_EQUAL_SIMPLE_D_10(d,vseq1,vseq2) QOR_VMD_DETAIL_EQUAL_10_D(d,vseq1,vseq2)
#define QOR_VMD_DETAIL_EQUAL_SIMPLE_D_11(d,vseq1,vseq2) QOR_VMD_DETAIL_EQUAL_11_D(d,vseq1,vseq2)
#define QOR_VMD_DETAIL_EQUAL_SIMPLE_D_12(d,vseq1,vseq2) QOR_VMD_DETAIL_EQUAL_12_D(d,vseq1,vseq2)
#define QOR_VMD_DETAIL_EQUAL_SIMPLE_D_13(d,vseq1,vseq2) QOR_VMD_DETAIL_EQUAL_13_D(d,vseq1,vseq2)
#define QOR_VMD_DETAIL_EQUAL_SIMPLE_D_14(d,vseq1,vseq2) QOR_VMD_DETAIL_EQUAL_14_D(d,vseq1,vseq2)
#define QOR_VMD_DETAIL_EQUAL_SIMPLE_D_15(d,vseq1,vseq2) QOR_VMD_DETAIL_EQUAL_15_D(d,vseq1,vseq2)
#define QOR_VMD_DETAIL_EQUAL_SIMPLE_D_16(d,vseq1,vseq2) QOR_VMD_DETAIL_EQUAL_16_D(d,vseq1,vseq2)

#define QOR_VMD_DETAIL_EQUAL_SIMPLE_AUTO_REC_D(n) \
    QOR_VMD_DETAIL_EQUAL_IS_1 \
        ( \
        QOR_VMD_DETAIL_EQUAL_SIMPLE_D_ ## n(1,,) \
        ) \
/**/

#define QOR_VMD_DETAIL_EQUAL_SIMPLE_D \
    QOR_PP_CAT \
        ( \
        QOR_VMD_DETAIL_EQUAL_SIMPLE_D_, \
        QOR_PP_AUTO_REC(QOR_VMD_DETAIL_EQUAL_SIMPLE_AUTO_REC_D,16) \
        ) \
/**/


#define QOR_VMD_DETAIL_EQUAL_CNI_CHK(vseq1,vseq2,vtype) \
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
        QOR_VMD_DETAIL_DATA_EQUAL, \
        QOR_VMD_DETAIL_EQUAL_CNI_SMP \
        ) \
    (vseq1,vseq2,vtype) \
/**/

#define QOR_VMD_DETAIL_EQUAL_CNI_CHK_D(d,vseq1,vseq2,vtype) \
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
        QOR_VMD_DETAIL_DATA_EQUAL_D, \
        QOR_VMD_DETAIL_EQUAL_CNI_SMP_D \
        ) \
    (d,vseq1,vseq2,vtype) \
/**/

#define QOR_VMD_DETAIL_EQUAL_VSEQ(vseq1,vseq2,vtype) \
    QOR_VMD_DETAIL_DATA_EQUAL \
        ( \
        QOR_VMD_TO_SEQ(vseq1), \
        QOR_VMD_TO_SEQ(vseq2), \
        QOR_VMD_TYPE_SEQ \
        ) \
/**/

#define QOR_VMD_DETAIL_EQUAL_VSEQ_D(d,vseq1,vseq2,vtype) \
    QOR_VMD_DETAIL_DATA_EQUAL_D \
        ( \
        d, \
        QOR_VMD_TO_SEQ_D(d,vseq1), \
        QOR_VMD_TO_SEQ_D(d,vseq2), \
        QOR_VMD_TYPE_SEQ \
        ) \
/**/

#define QOR_VMD_DETAIL_EQUAL_CNI(vseq1,vseq2,vtype) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_EQUAL_TYPE \
            ( \
            vtype, \
            QOR_VMD_TYPE_SEQUENCE \
            ), \
        QOR_VMD_DETAIL_EQUAL_VSEQ, \
        QOR_VMD_DETAIL_EQUAL_CNI_CHK \
        ) \
    (vseq1,vseq2,vtype) \
/**/

#define QOR_VMD_DETAIL_EQUAL_CNI_D(d,vseq1,vseq2,vtype) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_EQUAL_TYPE_D \
            ( \
            d, \
            vtype, \
            QOR_VMD_TYPE_SEQUENCE \
            ), \
        QOR_VMD_DETAIL_EQUAL_VSEQ_D, \
        QOR_VMD_DETAIL_EQUAL_CNI_CHK_D \
        ) \
    (d,vseq1,vseq2,vtype) \
/**/

#define QOR_VMD_DETAIL_EQUAL_TEST_TYPE_CHECK_TUPLE(vseq1,vtype1,type) \
    QOR_PP_BITOR \
        ( \
        QOR_VMD_DETAIL_EQUAL_TYPE \
            ( \
            QOR_VMD_TYPE_ARRAY, \
            vtype1 \
            ), \
        QOR_PP_BITAND \
            ( \
            QOR_VMD_DETAIL_EQUAL_TYPE \
                ( \
                QOR_VMD_TYPE_LIST, \
                vtype1 \
                ), \
            QOR_PP_COMPL \
                ( \
                QOR_VMD_IS_EMPTY_LIST(vseq1) \
                ) \
            ) \
        ) \
/**/

#define QOR_VMD_DETAIL_EQUAL_TEST_TYPE_CHECK_TUPLE_D(d,vseq1,vtype1,type) \
    QOR_PP_BITOR \
        ( \
        QOR_VMD_DETAIL_EQUAL_TYPE_D \
            ( \
            d, \
            QOR_VMD_TYPE_ARRAY, \
            vtype1 \
            ), \
        QOR_PP_BITAND \
            ( \
            QOR_VMD_DETAIL_EQUAL_TYPE_D \
                ( \
                d, \
                QOR_VMD_TYPE_LIST, \
                vtype1 \
                ), \
            QOR_PP_COMPL \
                ( \
                QOR_VMD_IS_EMPTY_LIST_D(d,vseq1) \
                ) \
            ) \
        ) \
/**/

#define QOR_VMD_DETAIL_EQUAL_TEST_TYPE_CHECK_IDENTIFIER(vseq1,vtype1,type) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_VMD_DETAIL_EQUAL_TYPE \
                ( \
                QOR_VMD_TYPE_IDENTIFIER, \
                type \
                ), \
            QOR_VMD_IS_IDENTIFIER, \
            QOR_VMD_IDENTITY(0) \
            ) \
        (vseq1) \
        ) \
/**/

#define QOR_VMD_DETAIL_EQUAL_TEST_TYPE_CHECK_IDENTIFIER_D(d,vseq1,vtype1,type) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_VMD_DETAIL_EQUAL_TYPE_D \
                ( \
                d, \
                QOR_VMD_TYPE_IDENTIFIER, \
                type \
                ), \
            QOR_VMD_IS_IDENTIFIER_D, \
            QOR_VMD_IDENTITY(0) \
            ) \
        (d,vseq1) \
        ) \
/**/

#define QOR_VMD_DETAIL_EQUAL_TEST_TYPE_CHECK(vseq1,vtype1,type) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_EQUAL_TYPE \
            ( \
            QOR_VMD_TYPE_TUPLE, \
            type \
            ), \
        QOR_VMD_DETAIL_EQUAL_TEST_TYPE_CHECK_TUPLE, \
        QOR_VMD_DETAIL_EQUAL_TEST_TYPE_CHECK_IDENTIFIER \
        ) \
    (vseq1,vtype1,type) \
/**/

#define QOR_VMD_DETAIL_EQUAL_TEST_TYPE_CHECK_D(d,vseq1,vtype1,type) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_EQUAL_TYPE_D \
            ( \
            d, \
            QOR_VMD_TYPE_TUPLE, \
            type \
            ), \
        QOR_VMD_DETAIL_EQUAL_TEST_TYPE_CHECK_TUPLE_D, \
        QOR_VMD_DETAIL_EQUAL_TEST_TYPE_CHECK_IDENTIFIER_D \
        ) \
    (d,vseq1,vtype1,type) \
/**/

#define QOR_VMD_DETAIL_EQUAL_TEST_TYPE(vseq1,vtype1,type) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_VMD_DETAIL_EQUAL_TYPE \
                ( \
                vtype1, \
                type \
                ), \
            QOR_VMD_IDENTITY(1), \
            QOR_VMD_DETAIL_EQUAL_TEST_TYPE_CHECK \
            ) \
        (vseq1,vtype1,type)    \
        ) \
/**/

#define QOR_VMD_DETAIL_EQUAL_TEST_TYPE_D(d,vseq1,vtype1,type) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_VMD_DETAIL_EQUAL_TYPE_D \
                ( \
                d, \
                vtype1, \
                type \
                ), \
            QOR_VMD_IDENTITY(1), \
            QOR_VMD_DETAIL_EQUAL_TEST_TYPE_CHECK_D \
            ) \
        (d,vseq1,vtype1,type)    \
        ) \
/**/

#define QOR_VMD_DETAIL_EQUAL_WT_CHECK(vseq1,vseq2,vtype1,vtype2,type) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_PP_BITAND \
                ( \
                QOR_VMD_DETAIL_EQUAL_TYPE \
                    ( \
                    vtype1, \
                    vtype2 \
                    ), \
                QOR_VMD_IDENTITY_RESULT \
                    ( \
                    QOR_PP_IIF \
                        ( \
                        QOR_VMD_DETAIL_NOT_EMPTY(type), \
                        QOR_VMD_DETAIL_EQUAL_TEST_TYPE, \
                        QOR_VMD_IDENTITY(1) \
                        ) \
                    (vseq1,vtype1,type) \
                    ) \
                ), \
            QOR_VMD_DETAIL_EQUAL_CNI, \
            QOR_VMD_IDENTITY(0) \
            ) \
        (vseq1,vseq2,vtype1) \
        ) \
/**/

#define QOR_VMD_DETAIL_EQUAL_WT_CHECK_D(d,vseq1,vseq2,vtype1,vtype2,type) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_PP_BITAND \
                ( \
                QOR_VMD_DETAIL_EQUAL_TYPE_D \
                    ( \
                    d, \
                    vtype1, \
                    vtype2 \
                    ), \
                QOR_VMD_IDENTITY_RESULT \
                    ( \
                    QOR_PP_IIF \
                        ( \
                        QOR_VMD_DETAIL_NOT_EMPTY(type), \
                        QOR_VMD_DETAIL_EQUAL_TEST_TYPE_D, \
                        QOR_VMD_IDENTITY(1) \
                        ) \
                    (d,vseq1,vtype1,type) \
                    ) \
                ), \
            QOR_VMD_DETAIL_EQUAL_CNI_D, \
            QOR_VMD_IDENTITY(0) \
            ) \
        (d,vseq1,vseq2,vtype1) \
        ) \
/**/

#define QOR_VMD_DETAIL_EQUAL_WT_CONVERT(vseq1,vseq2,vtype1,vtype2,type) \
    QOR_VMD_DETAIL_EQUAL_WT_CHECK \
        ( \
        vseq1, \
        vseq2, \
        QOR_VMD_DETAIL_ADJUST_TUPLE_TYPE(vseq1,vtype1), \
        QOR_VMD_DETAIL_ADJUST_TUPLE_TYPE(vseq2,vtype2), \
        type \
        ) \
/**/

#define QOR_VMD_DETAIL_EQUAL_WT_CONVERT_D(d,vseq1,vseq2,vtype1,vtype2,type) \
    QOR_VMD_DETAIL_EQUAL_WT_CHECK_D \
        ( \
        d, \
        vseq1, \
        vseq2, \
        QOR_VMD_DETAIL_ADJUST_TUPLE_TYPE_D(d,vseq1,vtype1), \
        QOR_VMD_DETAIL_ADJUST_TUPLE_TYPE_D(d,vseq2,vtype2), \
        type \
        ) \
/**/

#define QOR_VMD_DETAIL_EQUAL_WT(vseq1,vseq2,vtype1,vtype2,type) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_VMD_DETAIL_EQUAL_IS_TUPLE_MISMATCH(vseq1,vseq2,vtype1,vtype2), \
            QOR_VMD_IDENTITY(0), \
            QOR_VMD_DETAIL_EQUAL_WT_CONVERT \
            ) \
        (vseq1,vseq2,vtype1,vtype2,type) \
        ) \
/**/

#define QOR_VMD_DETAIL_EQUAL_WT_D(d,vseq1,vseq2,vtype1,vtype2,type) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_VMD_DETAIL_EQUAL_IS_TUPLE_MISMATCH_D(d,vseq1,vseq2,vtype1,vtype2), \
            QOR_VMD_IDENTITY(0), \
            QOR_VMD_DETAIL_EQUAL_WT_CONVERT_D \
            ) \
        (d,vseq1,vseq2,vtype1,vtype2,type) \
        ) \
/**/

#define QOR_VMD_DETAIL_EQUAL_GTYPE(vseq1,vseq2,type) \
    QOR_VMD_DETAIL_EQUAL_WT \
        ( \
        vseq1, \
        vseq2, \
        QOR_VMD_GET_TYPE(vseq1,QOR_VMD_RETURN_TYPE_TUPLE), \
        QOR_VMD_GET_TYPE(vseq2,QOR_VMD_RETURN_TYPE_TUPLE), \
        type \
        ) \
/**/

#define QOR_VMD_DETAIL_EQUAL_GTYPE_D(d,vseq1,vseq2,type) \
    QOR_VMD_DETAIL_EQUAL_WT_D \
        ( \
        d, \
        vseq1, \
        vseq2, \
        QOR_VMD_GET_TYPE_D(d,vseq1,QOR_VMD_RETURN_TYPE_TUPLE), \
        QOR_VMD_GET_TYPE_D(d,vseq2,QOR_VMD_RETURN_TYPE_TUPLE), \
        type \
        ) \
/**/

#define QOR_VMD_DETAIL_EQUAL_EBP(vseq1,vseq2,be1,be2,type) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_PP_BITAND \
                ( \
                QOR_VMD_DETAIL_EQUAL_CHK_MATCH(be1,be2), \
                QOR_VMD_DETAIL_EQUAL_CHK_PARENS_MATCH(vseq1,vseq2) \
                ), \
            QOR_VMD_DETAIL_EQUAL_GTYPE, \
            QOR_VMD_IDENTITY(0) \
            ) \
        (vseq1,vseq2,type) \
        ) \
/**/

#define QOR_VMD_DETAIL_EQUAL_EBP_D(d,vseq1,vseq2,be1,be2,type) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_PP_BITAND \
                ( \
                QOR_VMD_DETAIL_EQUAL_CHK_MATCH(be1,be2), \
                QOR_VMD_DETAIL_EQUAL_CHK_PARENS_MATCH(vseq1,vseq2) \
                ), \
            QOR_VMD_DETAIL_EQUAL_GTYPE_D, \
            QOR_VMD_IDENTITY(0) \
            ) \
        (d,vseq1,vseq2,type) \
        ) \
/**/

#define QOR_VMD_DETAIL_EQUAL_EMPTY(vseq1,vseq2,be1,be2,type) \
    QOR_PP_IIF \
        ( \
        QOR_PP_BITAND(be1,be2), \
        QOR_VMD_DETAIL_EQUAL_BOTH_EMPTY, \
        QOR_VMD_DETAIL_EQUAL_EBP \
        ) \
    (vseq1,vseq2,be1,be2,type) \
/**/

#define QOR_VMD_DETAIL_EQUAL_EMPTY_D(d,vseq1,vseq2,be1,be2,type) \
    QOR_PP_IIF \
        ( \
        QOR_PP_BITAND(be1,be2), \
        QOR_VMD_DETAIL_EQUAL_BOTH_EMPTY, \
        QOR_VMD_DETAIL_EQUAL_EBP_D \
        ) \
    (d,vseq1,vseq2,be1,be2,type) \
/**/

#define QOR_VMD_DETAIL_EQUAL_OV1(vseq1,vseq2) \
    QOR_VMD_DETAIL_EQUAL_EMPTY \
        ( \
        vseq1, \
        vseq2, \
        QOR_VMD_IS_EMPTY(vseq1), \
        QOR_VMD_IS_EMPTY(vseq2), \
        ) \
/**/

#define QOR_VMD_DETAIL_EQUAL_OV2(vseq1,vseq2,type) \
    QOR_VMD_DETAIL_EQUAL_EMPTY \
        ( \
        vseq1, \
        vseq2, \
        QOR_VMD_IS_EMPTY(vseq1), \
        QOR_VMD_IS_EMPTY(vseq2), \
        type \
        ) \
/**/

#define QOR_VMD_DETAIL_EQUAL_D_OV1(d,vseq1,vseq2) \
    QOR_VMD_DETAIL_EQUAL_EMPTY_D \
        ( \
        d, \
        vseq1, \
        vseq2, \
        QOR_VMD_IS_EMPTY(vseq1), \
        QOR_VMD_IS_EMPTY(vseq2), \
        ) \
/**/

#define QOR_VMD_DETAIL_EQUAL_D_OV2(d,vseq1,vseq2,type) \
    QOR_VMD_DETAIL_EQUAL_EMPTY_D \
        ( \
        d, \
        vseq1, \
        vseq2, \
        QOR_VMD_IS_EMPTY(vseq1), \
        QOR_VMD_IS_EMPTY(vseq2), \
        type \
        ) \
/**/

#if QOR_VMD_MSVC

#define QOR_VMD_DETAIL_EQUAL(vseq1,...) \
    QOR_PP_CAT(QOR_PP_OVERLOAD(QOR_VMD_DETAIL_EQUAL_OV,__VA_ARGS__)(vseq1,__VA_ARGS__),QOR_PP_EMPTY()) \
/**/

#define QOR_VMD_DETAIL_EQUAL_D(d,vseq1,...) \
    QOR_PP_CAT(QOR_PP_OVERLOAD(QOR_VMD_DETAIL_EQUAL_D_OV,__VA_ARGS__)(d,vseq1,__VA_ARGS__),QOR_PP_EMPTY()) \
/**/

#else

#define QOR_VMD_DETAIL_EQUAL(vseq1,...) \
    QOR_PP_OVERLOAD(QOR_VMD_DETAIL_EQUAL_OV,__VA_ARGS__)(vseq1,__VA_ARGS__) \
/**/

#define QOR_VMD_DETAIL_EQUAL_D(d,vseq1,...) \
    QOR_PP_OVERLOAD(QOR_VMD_DETAIL_EQUAL_D_OV,__VA_ARGS__)(d,vseq1,__VA_ARGS__) \
/**/

#endif

#endif /* QOR_VMD_DETAIL_EQUAL_H */
