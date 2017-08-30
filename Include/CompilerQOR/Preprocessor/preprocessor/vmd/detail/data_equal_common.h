
//  (C) Copyright Edward Diener 2011-2015
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(QOR_VMD_DETAIL_DATA_EQUAL_COMMON_H)
#define QOR_VMD_DETAIL_DATA_EQUAL_COMMON_H

#include "CompilerQOR/Preprocessor/preprocessor/arithmetic/inc.h"
#include "CompilerQOR/Preprocessor/preprocessor/array/elem.h"
#include "CompilerQOR/Preprocessor/preprocessor/array/size.h"
#include "CompilerQOR/Preprocessor/preprocessor/comparison/equal.h"
#include "CompilerQOR/Preprocessor/preprocessor/control/iif.h"
#include "CompilerQOR/Preprocessor/preprocessor/list/at.h"
#include "CompilerQOR/Preprocessor/preprocessor/list/size.h"
#include "CompilerQOR/Preprocessor/preprocessor/logical/bitand.h"
#include "CompilerQOR/Preprocessor/preprocessor/logical/bitor.h"
#include "CompilerQOR/Preprocessor/preprocessor/logical/compl.h"
#include "CompilerQOR/Preprocessor/preprocessor/punctuation/is_begin_parens.h"
#include "CompilerQOR/Preprocessor/preprocessor/seq/elem.h"
#include "CompilerQOR/Preprocessor/preprocessor/seq/size.h"
#include "CompilerQOR/Preprocessor/preprocessor/tuple/elem.h"
#include "CompilerQOR/Preprocessor/preprocessor/tuple/pop_front.h"
#include "CompilerQOR/Preprocessor/preprocessor/tuple/push_back.h"
#include "CompilerQOR/Preprocessor/preprocessor/tuple/replace.h"
#include "CompilerQOR/Preprocessor/preprocessor/tuple/size.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/empty.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/is_empty.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/get_type.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/equal_type.h"

#define QOR_VMD_DETAIL_DATA_EQUAL_IS_BOTH_COMPOSITE(vseq1,vseq2) \
    QOR_PP_BITAND \
        ( \
        QOR_PP_IS_BEGIN_PARENS(vseq1), \
        QOR_PP_IS_BEGIN_PARENS(vseq2) \
        ) \
/**/

#define QOR_VMD_DETAIL_DATA_EQUAL_GET_ELEM_ARRAY(d,index,data) \
    QOR_PP_ARRAY_ELEM(index,data) \
/**/

#define QOR_VMD_DETAIL_DATA_EQUAL_GET_ELEM_LIST(d,index,data) \
    QOR_PP_LIST_AT_D(d,data,index) \
/**/

#define QOR_VMD_DETAIL_DATA_EQUAL_GET_ELEM_SEQ(d,index,data) \
    QOR_PP_SEQ_ELEM(index,data) \
/**/

#define QOR_VMD_DETAIL_DATA_EQUAL_GET_ELEM_TUPLE(d,index,data) \
    QOR_PP_TUPLE_ELEM(index,data) \
/**/

#define QOR_VMD_DETAIL_DATA_EQUAL_GET_SIZE_ARRAY(data) \
    QOR_PP_ARRAY_SIZE(data) \
/**/

#define QOR_VMD_DETAIL_DATA_EQUAL_GET_SIZE_LIST(data) \
    QOR_PP_LIST_SIZE(data) \
/**/

#define QOR_VMD_DETAIL_DATA_EQUAL_GET_SIZE_SEQ(data) \
    QOR_PP_SEQ_SIZE(data) \
/**/

#define QOR_VMD_DETAIL_DATA_EQUAL_GET_SIZE_TUPLE(data) \
    QOR_PP_TUPLE_SIZE(data) \
/**/

#define QOR_VMD_DETAIL_DATA_EQUAL_GET_SIZE_ARRAY_D(d,data) \
    QOR_PP_ARRAY_SIZE(data) \
/**/

#define QOR_VMD_DETAIL_DATA_EQUAL_GET_SIZE_LIST_D(d,data) \
    QOR_PP_LIST_SIZE_D(d,data) \
/**/

#define QOR_VMD_DETAIL_DATA_EQUAL_GET_SIZE_SEQ_D(d,data) \
    QOR_PP_SEQ_SIZE(data) \
/**/

#define QOR_VMD_DETAIL_DATA_EQUAL_GET_SIZE_TUPLE_D(d,data) \
    QOR_PP_TUPLE_SIZE(data) \
/**/

#define QOR_VMD_DETAIL_DATA_EQUAL_GET_ELEM(d,index,data,vtype) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_EQUAL_TYPE_D(d,vtype,QOR_VMD_TYPE_ARRAY), \
        QOR_VMD_DETAIL_DATA_EQUAL_GET_ELEM_ARRAY, \
        QOR_PP_IIF \
            ( \
            QOR_VMD_DETAIL_EQUAL_TYPE_D(d,vtype,QOR_VMD_TYPE_LIST), \
            QOR_VMD_DETAIL_DATA_EQUAL_GET_ELEM_LIST, \
            QOR_PP_IIF \
                ( \
                QOR_VMD_DETAIL_EQUAL_TYPE_D(d,vtype,QOR_VMD_TYPE_SEQ), \
                QOR_VMD_DETAIL_DATA_EQUAL_GET_ELEM_SEQ, \
                QOR_VMD_DETAIL_DATA_EQUAL_GET_ELEM_TUPLE \
                ) \
            ) \
        ) \
    (d,index,data) \
/**/

#define QOR_VMD_DETAIL_DATA_EQUAL_GET_SIZE(data,vtype) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_EQUAL_TYPE(vtype,QOR_VMD_TYPE_ARRAY), \
        QOR_VMD_DETAIL_DATA_EQUAL_GET_SIZE_ARRAY, \
        QOR_PP_IIF \
            ( \
            QOR_VMD_DETAIL_EQUAL_TYPE(vtype,QOR_VMD_TYPE_LIST), \
            QOR_VMD_DETAIL_DATA_EQUAL_GET_SIZE_LIST, \
            QOR_PP_IIF \
                ( \
                QOR_VMD_DETAIL_EQUAL_TYPE(vtype,QOR_VMD_TYPE_SEQ), \
                QOR_VMD_DETAIL_DATA_EQUAL_GET_SIZE_SEQ, \
                QOR_VMD_DETAIL_DATA_EQUAL_GET_SIZE_TUPLE \
                ) \
            ) \
        ) \
    (data) \
/**/

#define QOR_VMD_DETAIL_DATA_EQUAL_GET_SIZE_D(d,data,vtype) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_EQUAL_TYPE_D(d,vtype,QOR_VMD_TYPE_ARRAY), \
        QOR_VMD_DETAIL_DATA_EQUAL_GET_SIZE_ARRAY_D, \
        QOR_PP_IIF \
            ( \
            QOR_VMD_DETAIL_EQUAL_TYPE_D(d,vtype,QOR_VMD_TYPE_LIST), \
            QOR_VMD_DETAIL_DATA_EQUAL_GET_SIZE_LIST_D, \
            QOR_PP_IIF \
                ( \
                QOR_VMD_DETAIL_EQUAL_TYPE_D(d,vtype,QOR_VMD_TYPE_SEQ), \
                QOR_VMD_DETAIL_DATA_EQUAL_GET_SIZE_SEQ_D, \
                QOR_VMD_DETAIL_DATA_EQUAL_GET_SIZE_TUPLE_D \
                ) \
            ) \
        ) \
    (d,data) \
/**/

#define QOR_VMD_DETAIL_DATA_EQUAL_STATE_RESULT(state) \
    QOR_PP_TUPLE_ELEM(0,state) \
/**/

#define QOR_VMD_DETAIL_DATA_EQUAL_STATE_FIRST(state) \
    QOR_PP_TUPLE_ELEM(1,state) \
/**/

#define QOR_VMD_DETAIL_DATA_EQUAL_STATE_SECOND(state) \
    QOR_PP_TUPLE_ELEM(2,state) \
/**/

#define QOR_VMD_DETAIL_DATA_EQUAL_STATE_SIZE(state) \
    QOR_PP_TUPLE_ELEM(3,state) \
/**/

#define QOR_VMD_DETAIL_DATA_EQUAL_STATE_TYPE(state) \
    QOR_PP_TUPLE_ELEM(4,state) \
/**/

#define QOR_VMD_DETAIL_DATA_EQUAL_STATE_INDEX(state) \
    QOR_PP_TUPLE_ELEM(5,state) \
/**/

#define QOR_VMD_DETAIL_DATA_EQUAL_STATE_COMP(state) \
    QOR_PP_TUPLE_ELEM(6,state) \
/**/

#define QOR_VMD_DETAIL_DATA_EQUAL_STATE_COMP_PROCESSING(d,state) \
    QOR_PP_BITAND \
        ( \
        QOR_PP_EQUAL_D \
            ( \
            d, \
            QOR_VMD_DETAIL_DATA_EQUAL_STATE_INDEX(state), \
            QOR_VMD_DETAIL_DATA_EQUAL_STATE_SIZE(state) \
            ), \
        QOR_PP_COMPL(QOR_VMD_DETAIL_DATA_EQUAL_STATE_COMP_EMPTY(state)) \
        ) \
/**/

#define QOR_VMD_DETAIL_DATA_EQUAL_STATE_COMP_EMPTY(state) \
    QOR_VMD_IS_EMPTY(QOR_VMD_DETAIL_DATA_EQUAL_STATE_COMP(state)) \
/**/

#define QOR_VMD_DETAIL_DATA_EQUAL_STATE_COMP_INDEX(state) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_DATA_EQUAL_STATE_COMP_EMPTY(state), \
        QOR_VMD_EMPTY, \
        QOR_PP_TUPLE_ELEM \
        ) \
    (0,QOR_VMD_DETAIL_DATA_EQUAL_STATE_COMP(state)) \
/**/

#define QOR_VMD_DETAIL_DATA_EQUAL_STATE_COMP_POP_NE_EMPTY(d,state) \
    QOR_PP_TUPLE_REPLACE_D \
        ( \
        d, \
        state, \
        6, \
        ) \
/**/

#define QOR_VMD_DETAIL_DATA_EQUAL_STATE_COMP_POP_NE_REMOVE(d,state) \
    QOR_PP_TUPLE_REPLACE_D \
        ( \
        d, \
        state, \
        6, \
        QOR_PP_TUPLE_POP_FRONT(QOR_VMD_DETAIL_DATA_EQUAL_STATE_COMP(state)) \
        ) \
/**/

#define QOR_VMD_DETAIL_DATA_EQUAL_STATE_COMP_POP(d,state) \
    QOR_PP_IIF \
        ( \
        QOR_PP_EQUAL_D(d,QOR_PP_TUPLE_SIZE(QOR_VMD_DETAIL_DATA_EQUAL_STATE_COMP(state)),1), \
        QOR_VMD_DETAIL_DATA_EQUAL_STATE_COMP_POP_NE_EMPTY, \
        QOR_VMD_DETAIL_DATA_EQUAL_STATE_COMP_POP_NE_REMOVE \
        ) \
    (d,state) \
/**/

#define QOR_VMD_DETAIL_DATA_EQUAL_STATE_COMP_PUSH_CREATE(d,state) \
    QOR_VMD_DETAIL_DATA_EQUAL_OP_SUCCESS \
        ( \
        d, \
        QOR_PP_TUPLE_REPLACE_D \
            ( \
            d, \
            state, \
            6, \
            (QOR_VMD_DETAIL_DATA_EQUAL_STATE_INDEX(state)) \
            ) \
        ) \
/**/

#define QOR_VMD_DETAIL_DATA_EQUAL_STATE_COMP_PUSH_ADD(d,state) \
    QOR_VMD_DETAIL_DATA_EQUAL_OP_SUCCESS \
        ( \
        d, \
        QOR_PP_TUPLE_REPLACE_D \
            ( \
            d, \
            state, \
            6, \
            QOR_PP_TUPLE_PUSH_BACK \
                ( \
                QOR_VMD_DETAIL_DATA_EQUAL_STATE_COMP(state), \
                QOR_VMD_DETAIL_DATA_EQUAL_STATE_INDEX(state) \
                ) \
            ) \
        ) \
/**/

#define QOR_VMD_DETAIL_DATA_EQUAL_STATE_COMP_PUSH(d,state) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_DATA_EQUAL_STATE_COMP_EMPTY(state), \
        QOR_VMD_DETAIL_DATA_EQUAL_STATE_COMP_PUSH_CREATE, \
        QOR_VMD_DETAIL_DATA_EQUAL_STATE_COMP_PUSH_ADD \
        ) \
    (d,state) \
/**/

#define QOR_VMD_DETAIL_DATA_EQUAL_STATE_GET_INDEX(d,state) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_DATA_EQUAL_STATE_COMP_PROCESSING(d,state), \
        QOR_VMD_DETAIL_DATA_EQUAL_STATE_COMP_INDEX, \
        QOR_VMD_DETAIL_DATA_EQUAL_STATE_INDEX \
        ) \
    (state) \
/**/

#define QOR_VMD_DETAIL_DATA_EQUAL_STATE_GET_FIRST_ELEMENT(d,state) \
    QOR_VMD_DETAIL_DATA_EQUAL_GET_ELEM \
        ( \
        d, \
        QOR_VMD_DETAIL_DATA_EQUAL_STATE_GET_INDEX(d,state), \
        QOR_VMD_DETAIL_DATA_EQUAL_STATE_FIRST(state), \
        QOR_VMD_DETAIL_DATA_EQUAL_STATE_TYPE(state) \
        ) \
/**/

#define QOR_VMD_DETAIL_DATA_EQUAL_STATE_GET_SECOND_ELEMENT(d,state) \
    QOR_VMD_DETAIL_DATA_EQUAL_GET_ELEM \
        ( \
        d, \
        QOR_VMD_DETAIL_DATA_EQUAL_STATE_GET_INDEX(d,state), \
        QOR_VMD_DETAIL_DATA_EQUAL_STATE_SECOND(state), \
        QOR_VMD_DETAIL_DATA_EQUAL_STATE_TYPE(state) \
        ) \
/**/

#define QOR_VMD_DETAIL_DATA_EQUAL_PRED(d,state) \
    QOR_PP_BITAND \
        ( \
        QOR_PP_EQUAL_D \
            ( \
            d, \
            QOR_VMD_DETAIL_DATA_EQUAL_STATE_RESULT(state), \
            1 \
            ), \
        QOR_PP_BITOR \
            ( \
            QOR_PP_NOT_EQUAL_D \
                ( \
                d, \
                QOR_VMD_DETAIL_DATA_EQUAL_STATE_INDEX(state), \
                QOR_VMD_DETAIL_DATA_EQUAL_STATE_SIZE(state) \
                ), \
            QOR_PP_COMPL \
                ( \
                QOR_VMD_DETAIL_DATA_EQUAL_STATE_COMP_EMPTY(state) \
                ) \
            ) \
        ) \
/**/

#define QOR_VMD_DETAIL_DATA_EQUAL_OP_SUCCESS_NCP(d,state) \
    QOR_PP_TUPLE_REPLACE_D \
        ( \
        d, \
        state, \
        5, \
        QOR_PP_INC(QOR_VMD_DETAIL_DATA_EQUAL_STATE_INDEX(state)) \
        ) \
/**/

#define QOR_VMD_DETAIL_DATA_EQUAL_OP_SUCCESS(d,state) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_DATA_EQUAL_STATE_COMP_PROCESSING(d,state), \
        QOR_VMD_DETAIL_DATA_EQUAL_STATE_COMP_POP, \
        QOR_VMD_DETAIL_DATA_EQUAL_OP_SUCCESS_NCP \
        ) \
    (d,state) \
/**/

#define QOR_VMD_DETAIL_DATA_EQUAL_OP_FAILURE(d,state) \
    QOR_PP_TUPLE_REPLACE_D \
        ( \
        d, \
        state, \
        0, \
        0 \
        ) \
/**/

#define QOR_VMD_DETAIL_DATA_EQUAL_OP_RESULT(d,state,result) \
    QOR_PP_IIF \
        ( \
        QOR_PP_EQUAL_D(d,result,0), \
        QOR_VMD_DETAIL_DATA_EQUAL_OP_FAILURE, \
        QOR_PP_IIF \
            ( \
            QOR_PP_EQUAL_D(d,result,1), \
            QOR_VMD_DETAIL_DATA_EQUAL_OP_SUCCESS, \
            QOR_VMD_DETAIL_DATA_EQUAL_STATE_COMP_PUSH \
            ) \
        ) \
    (d,state) \
/**/

#define QOR_VMD_DETAIL_DATA_EQUAL_TYPE(emf,ems,vtype) \
    QOR_PP_BITAND \
        ( \
        QOR_VMD_DETAIL_EQUAL_TYPE \
            ( \
            QOR_VMD_GET_TYPE(emf), \
            vtype \
            ), \
        QOR_VMD_DETAIL_EQUAL_TYPE \
            ( \
            QOR_VMD_GET_TYPE(ems), \
            vtype \
            ) \
        ) \
/**/

#define QOR_VMD_DETAIL_DATA_EQUAL_TYPE_D(d,emf,ems,vtype) \
    QOR_PP_BITAND \
        ( \
        QOR_VMD_DETAIL_EQUAL_TYPE_D \
            ( \
            d, \
            QOR_VMD_GET_TYPE(emf), \
            vtype \
            ), \
        QOR_VMD_DETAIL_EQUAL_TYPE_D \
            ( \
            d, \
            QOR_VMD_GET_TYPE(ems), \
            vtype \
            ) \
        ) \
/**/

#endif /* QOR_VMD_DETAIL_DATA_EQUAL_COMMON_H */
