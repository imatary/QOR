
//  (C) Copyright Edward Diener 2011-2015
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(QOR_VMD_DETAIL_DATA_EQUAL_9_H)
#define QOR_VMD_DETAIL_DATA_EQUAL_9_H

#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/recurse/data_equal/data_equal_headers.h"

#define QOR_VMD_DETAIL_DATA_EQUAL_9_OP_TEQ_CMP_PARENS(d,em1,em2) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_VMD_DETAIL_DATA_EQUAL_IS_BOTH_COMPOSITE(em1,em2), \
            QOR_VMD_IDENTITY(2), \
            QOR_VMD_DETAIL_EQUAL_SIMPLE_D \
            ) \
        (d,em1,em2) \
        ) \
/**/

#define QOR_VMD_DETAIL_DATA_EQUAL_9_OP_TEQ_CMP_PARENS_D(d,em1,em2) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_VMD_DETAIL_DATA_EQUAL_IS_BOTH_COMPOSITE(em1,em2), \
            QOR_VMD_IDENTITY(2), \
            QOR_VMD_DETAIL_EQUAL_SIMPLE_D \
            ) \
        (d,em1,em2) \
        ) \
/**/

#define QOR_VMD_DETAIL_DATA_EQUAL_9_OP_TEQ_CMP(d,state,em1,em2) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_DATA_EQUAL_STATE_COMP_PROCESSING(d,state), \
        QOR_VMD_DETAIL_EQUAL_SIMPLE_D, \
        QOR_VMD_DETAIL_DATA_EQUAL_9_OP_TEQ_CMP_PARENS \
        ) \
    (d,em1,em2) \
/**/

#define QOR_VMD_DETAIL_DATA_EQUAL_9_OP_TEQ_CMP_D(d,state,em1,em2) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_DATA_EQUAL_STATE_COMP_PROCESSING(d,state), \
        QOR_VMD_DETAIL_EQUAL_SIMPLE_D, \
        QOR_VMD_DETAIL_DATA_EQUAL_9_OP_TEQ_CMP_PARENS_D \
        ) \
    (d,em1,em2) \
/**/

#define QOR_VMD_DETAIL_DATA_EQUAL_9_OP_TEQ(d,state) \
    QOR_VMD_DETAIL_DATA_EQUAL_9_OP_TEQ_CMP \
        ( \
        d, \
        state, \
        QOR_VMD_DETAIL_DATA_EQUAL_STATE_GET_FIRST_ELEMENT(d,state), \
        QOR_VMD_DETAIL_DATA_EQUAL_STATE_GET_SECOND_ELEMENT(d,state) \
        ) \
/**/

#define QOR_VMD_DETAIL_DATA_EQUAL_9_OP_TEQ_D(d,state) \
    QOR_VMD_DETAIL_DATA_EQUAL_9_OP_TEQ_CMP_D \
        ( \
        d, \
        state, \
        QOR_VMD_DETAIL_DATA_EQUAL_STATE_GET_FIRST_ELEMENT(d,state), \
        QOR_VMD_DETAIL_DATA_EQUAL_STATE_GET_SECOND_ELEMENT(d,state) \
        ) \
/**/

#define QOR_VMD_DETAIL_DATA_EQUAL_9_OP(d,state) \
    QOR_VMD_DETAIL_DATA_EQUAL_OP_RESULT \
        ( \
        d, \
        state, \
        QOR_VMD_DETAIL_DATA_EQUAL_9_OP_TEQ(d,state) \
        ) \
/**/

#define QOR_VMD_DETAIL_DATA_EQUAL_9_OP_D(d,state) \
    QOR_VMD_DETAIL_DATA_EQUAL_OP_RESULT \
        ( \
        d, \
        state, \
        QOR_VMD_DETAIL_DATA_EQUAL_9_OP_TEQ_D(d,state) \
        ) \
/**/

#define QOR_VMD_DETAIL_DATA_EQUAL_9_LOOP(dataf,datas,sz,vtype) \
    QOR_PP_TUPLE_ELEM \
        ( \
        0, \
        QOR_PP_WHILE \
            ( \
            QOR_VMD_DETAIL_DATA_EQUAL_PRED, \
            QOR_VMD_DETAIL_DATA_EQUAL_9_OP, \
                ( \
                1, \
                dataf, \
                datas, \
                sz, \
                vtype, \
                0, \
                ) \
            ) \
        ) \
/**/

#define QOR_VMD_DETAIL_DATA_EQUAL_9_LOOP_D(d,dataf,datas,sz,vtype) \
    QOR_PP_TUPLE_ELEM \
        ( \
        0, \
        QOR_PP_WHILE_ ## d \
            ( \
            QOR_VMD_DETAIL_DATA_EQUAL_PRED, \
            QOR_VMD_DETAIL_DATA_EQUAL_9_OP_D, \
                ( \
                1, \
                dataf, \
                datas, \
                sz, \
                vtype, \
                0, \
                ) \
            ) \
        ) \
/**/

#define QOR_VMD_DETAIL_DATA_EQUAL_9_SZ(dataf,datas,szf,szs,vtype) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_PP_EQUAL(szf,szs), \
            QOR_VMD_DETAIL_DATA_EQUAL_9_LOOP, \
            QOR_VMD_IDENTITY(0) \
            ) \
        (dataf,datas,szf,vtype) \
        ) \
/**/

#define QOR_VMD_DETAIL_DATA_EQUAL_9_SZ_D(d,dataf,datas,szf,szs,vtype) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_PP_EQUAL_D(d,szf,szs), \
            QOR_VMD_DETAIL_DATA_EQUAL_9_LOOP_D, \
            QOR_VMD_IDENTITY(0) \
            ) \
        (d,dataf,datas,szf,vtype) \
        ) \
/**/

#define QOR_VMD_DETAIL_DATA_EQUAL_9(dataf,datas,vtype) \
    QOR_VMD_DETAIL_DATA_EQUAL_9_SZ \
        ( \
        dataf, \
        datas, \
        QOR_VMD_DETAIL_DATA_EQUAL_GET_SIZE(dataf,vtype), \
        QOR_VMD_DETAIL_DATA_EQUAL_GET_SIZE(datas,vtype), \
        vtype \
        ) \
/**/

#define QOR_VMD_DETAIL_DATA_EQUAL_9_D(d,dataf,datas,vtype) \
    QOR_VMD_DETAIL_DATA_EQUAL_9_SZ_D \
        ( \
        d, \
        dataf, \
        datas, \
        QOR_VMD_DETAIL_DATA_EQUAL_GET_SIZE_D(d,dataf,vtype), \
        QOR_VMD_DETAIL_DATA_EQUAL_GET_SIZE_D(d,datas,vtype), \
        vtype \
        ) \
/**/

#endif /* QOR_VMD_DETAIL_DATA_EQUAL_9_H */
