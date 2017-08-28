
//  (C) Copyright Edward Diener 2011-2015
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(QOR_VMD_DETAIL_SEQUENCE_COMMON_H)
#define QOR_VMD_DETAIL_SEQUENCE_COMMON_H

#include "CompilerQOR/Preprocessor/preprocessor/arithmetic/inc.h"
#include "CompilerQOR/Preprocessor/preprocessor/array/push_back.h"
#include "CompilerQOR/Preprocessor/preprocessor/cat.h"
#include "CompilerQOR/Preprocessor/preprocessor/comparison/equal.h"
#include "CompilerQOR/Preprocessor/preprocessor/comparison/less_equal.h"
#include "CompilerQOR/Preprocessor/preprocessor/comparison/not_equal.h"
#include "CompilerQOR/Preprocessor/preprocessor/control/iif.h"
#include "CompilerQOR/Preprocessor/preprocessor/control/while.h"
#include "CompilerQOR/Preprocessor/preprocessor/list/append.h"
#include "CompilerQOR/Preprocessor/preprocessor/logical/bitor.h"
#include "CompilerQOR/Preprocessor/preprocessor/punctuation/is_begin_parens.h"
#include "CompilerQOR/Preprocessor/preprocessor/seq/push_back.h"
#include "CompilerQOR/Preprocessor/preprocessor/seq/size.h"
#include "CompilerQOR/Preprocessor/preprocessor/tuple/elem.h"
#include "CompilerQOR/Preprocessor/preprocessor/tuple/push_back.h"
#include "CompilerQOR/Preprocessor/preprocessor/tuple/replace.h"
#include "CompilerQOR/Preprocessor/preprocessor/tuple/size.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/empty.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/identity.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/is_empty.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/is_empty_list.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/array.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/equal_type.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/identifier.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/identifier_type.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/list.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/modifiers.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/mods.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/seq.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/tuple.h"

#define QOR_VMD_DETAIL_SEQUENCE_STATE_INPUT_ELEM 0
#define QOR_VMD_DETAIL_SEQUENCE_STATE_RESULT_ELEM 1
#define QOR_VMD_DETAIL_SEQUENCE_STATE_ELEM_ELEM 2
#define QOR_VMD_DETAIL_SEQUENCE_STATE_OUTTYPE_ELEM 3
#define QOR_VMD_DETAIL_SEQUENCE_STATE_FROM_ELEM 4
#define QOR_VMD_DETAIL_SEQUENCE_STATE_TYPES_ELEM 5
#define QOR_VMD_DETAIL_SEQUENCE_STATE_INDEX_ELEM 6

#define QOR_VMD_DETAIL_SEQUENCE_STATE_INPUT(state) \
    QOR_PP_TUPLE_ELEM(QOR_VMD_DETAIL_SEQUENCE_STATE_INPUT_ELEM,state) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_STATE_RESULT(state) \
    QOR_PP_TUPLE_ELEM(QOR_VMD_DETAIL_SEQUENCE_STATE_RESULT_ELEM,state) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_STATE_ELEM(state) \
        QOR_PP_TUPLE_ELEM(QOR_VMD_DETAIL_SEQUENCE_STATE_ELEM_ELEM,state) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_STATE_OUTTYPE(state) \
        QOR_PP_TUPLE_ELEM(QOR_VMD_DETAIL_SEQUENCE_STATE_OUTTYPE_ELEM,state) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_STATE_FROM(state) \
        QOR_PP_TUPLE_ELEM(QOR_VMD_DETAIL_SEQUENCE_STATE_FROM_ELEM,state) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_STATE_IS_RETURN(d,from,number) \
    QOR_PP_EQUAL_D \
        ( \
        d, \
        QOR_PP_TUPLE_ELEM(0,from), \
        number \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_STATE_IS_NO_RETURN(d,from) \
    QOR_VMD_DETAIL_SEQUENCE_STATE_IS_RETURN(d,from,QOR_VMD_DETAIL_MODS_NO_RETURN) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_STATE_IS_EXACT_RETURN(d,from) \
    QOR_VMD_DETAIL_SEQUENCE_STATE_IS_RETURN(d,from,QOR_VMD_DETAIL_MODS_RETURN) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_STATE_IS_GENERAL_RETURN(d,from) \
    QOR_VMD_DETAIL_SEQUENCE_STATE_IS_RETURN(d,from,QOR_VMD_DETAIL_MODS_RETURN_TUPLE) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_STATE_IS_ARRAY_RETURN(d,from) \
    QOR_VMD_DETAIL_SEQUENCE_STATE_IS_RETURN(d,from,QOR_VMD_DETAIL_MODS_RETURN_ARRAY) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_STATE_IS_LIST_RETURN(d,from) \
    QOR_VMD_DETAIL_SEQUENCE_STATE_IS_RETURN(d,from,QOR_VMD_DETAIL_MODS_RETURN_LIST) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_STATE_IS_AFTER(from) \
    QOR_PP_EQUAL \
        ( \
        QOR_PP_TUPLE_ELEM(1,from), \
        QOR_VMD_DETAIL_MODS_RETURN_AFTER \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_STATE_IS_AFTER_D(d,from) \
    QOR_PP_EQUAL_D \
        ( \
        d, \
        QOR_PP_TUPLE_ELEM(1,from), \
        QOR_VMD_DETAIL_MODS_RETURN_AFTER \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_STATE_TYPES(state) \
        QOR_PP_TUPLE_ELEM(QOR_VMD_DETAIL_SEQUENCE_STATE_TYPES_ELEM,state) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_STATE_INDEX(state) \
        QOR_PP_TUPLE_ELEM(QOR_VMD_DETAIL_SEQUENCE_STATE_INDEX_ELEM,state) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_STATE_RESULT_IS_EMPTY(state) \
    QOR_VMD_IS_EMPTY \
        ( \
        QOR_VMD_DETAIL_SEQUENCE_STATE_RESULT(state) \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_STATE_RESULT_ADD_FROM_EMPTY(state,data) \
    (data) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_STATE_RESULT_ADD_TO_SEQ(state,data) \
    QOR_PP_SEQ_PUSH_BACK(QOR_VMD_DETAIL_SEQUENCE_STATE_RESULT(state),data) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_STATE_RESULT_ADD_TO_TUPLE(state,data) \
    QOR_PP_TUPLE_PUSH_BACK(QOR_VMD_DETAIL_SEQUENCE_STATE_RESULT(state),data) \
/**/

// Array

#define QOR_VMD_DETAIL_SEQUENCE_STATE_RESULT_ADD_QOR_VMD_TYPE_ARRAY(d,state,data) \
    QOR_PP_ARRAY_PUSH_BACK(QOR_VMD_DETAIL_SEQUENCE_STATE_RESULT(state),data) \
/**/

// List

#define QOR_VMD_DETAIL_SEQUENCE_STATE_RESULT_ADD_QOR_VMD_TYPE_LIST(d,state,data) \
    QOR_PP_LIST_APPEND_D(d,QOR_VMD_DETAIL_SEQUENCE_STATE_RESULT(state),(data,QOR_PP_NIL)) \
/**/

// Seq

#define QOR_VMD_DETAIL_SEQUENCE_STATE_RESULT_ADD_QOR_VMD_TYPE_SEQ(d,state,data) \
    QOR_PP_IIF \
         ( \
         QOR_VMD_DETAIL_SEQUENCE_STATE_RESULT_IS_EMPTY(state), \
         QOR_VMD_DETAIL_SEQUENCE_STATE_RESULT_ADD_FROM_EMPTY, \
         QOR_VMD_DETAIL_SEQUENCE_STATE_RESULT_ADD_TO_SEQ \
         ) \
     (state,data) \
/**/

// Tuple

#define QOR_VMD_DETAIL_SEQUENCE_STATE_RESULT_ADD_QOR_VMD_TYPE_TUPLE(d,state,data) \
    QOR_PP_IIF \
         ( \
         QOR_VMD_DETAIL_SEQUENCE_STATE_RESULT_IS_EMPTY(state), \
         QOR_VMD_DETAIL_SEQUENCE_STATE_RESULT_ADD_FROM_EMPTY, \
         QOR_VMD_DETAIL_SEQUENCE_STATE_RESULT_ADD_TO_TUPLE \
         ) \
     (state,data) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_STATE_RESULT_ADD_GET_NAME(state) \
    QOR_PP_CAT \
        ( \
        QOR_VMD_DETAIL_SEQUENCE_STATE_RESULT_ADD_, \
        QOR_VMD_DETAIL_SEQUENCE_STATE_OUTTYPE(state) \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_STATE_RESULT_ADD_PROCESS(d,name,state,data) \
    name(d,state,data) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_STATE_RESULT_ADD_GET_DATA(d,state,tuple) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_VMD_DETAIL_SEQUENCE_STATE_IS_NO_RETURN \
                ( \
                d, \
                QOR_VMD_DETAIL_SEQUENCE_STATE_FROM(state) \
                ), \
            QOR_PP_TUPLE_ELEM, \
            QOR_VMD_IDENTITY(tuple) \
            ) \
        (1,tuple) \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_STATE_RESULT_ADD(d,state,ttuple) \
    QOR_VMD_DETAIL_SEQUENCE_STATE_RESULT_ADD_PROCESS \
        ( \
        d, \
        QOR_VMD_DETAIL_SEQUENCE_STATE_RESULT_ADD_GET_NAME(state), \
        state, \
        QOR_VMD_DETAIL_SEQUENCE_STATE_RESULT_ADD_GET_DATA(d,state,ttuple) \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_PROCESSING_ELEM_CHECK(d,state) \
    QOR_PP_EQUAL_D \
        ( \
        d, \
        QOR_PP_SEQ_SIZE(QOR_VMD_DETAIL_SEQUENCE_STATE_RESULT(state)), \
        QOR_VMD_DETAIL_SEQUENCE_STATE_ELEM(state) \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_PROCESSING_ELEM(d,state) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_VMD_IS_EMPTY(QOR_VMD_DETAIL_SEQUENCE_STATE_ELEM(state)), \
            QOR_VMD_IDENTITY(0), \
            QOR_VMD_DETAIL_SEQUENCE_PROCESSING_ELEM_CHECK \
            ) \
        (d,state) \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_STATE_GET_TYPE(state) \
        QOR_PP_TUPLE_ELEM \
            ( \
            0, \
            QOR_PP_TUPLE_ELEM(QOR_VMD_DETAIL_SEQUENCE_STATE_INDEX(state),QOR_VMD_DETAIL_SEQUENCE_STATE_TYPES(state)) \
            ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_STATE_GET_TYPE_REENTRANT(state) \
        QOR_PP_TUPLE_ELEM \
            ( \
            1, \
            QOR_PP_TUPLE_ELEM(QOR_VMD_DETAIL_SEQUENCE_STATE_INDEX(state),QOR_VMD_DETAIL_SEQUENCE_STATE_TYPES(state)) \
            ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_INNER_OP_UNKNOWN(d,state) \
    ( \
    , \
    QOR_VMD_DETAIL_SEQUENCE_STATE_RESULT_ADD(d,state,(QOR_VMD_TYPE_UNKNOWN,QOR_VMD_DETAIL_SEQUENCE_STATE_INPUT(state))), \
    QOR_VMD_DETAIL_SEQUENCE_STATE_ELEM(state), \
    QOR_VMD_DETAIL_SEQUENCE_STATE_OUTTYPE(state), \
    QOR_VMD_DETAIL_SEQUENCE_STATE_FROM(state), \
    QOR_VMD_DETAIL_SEQUENCE_STATE_TYPES(state), \
    QOR_PP_INC(QOR_VMD_DETAIL_SEQUENCE_STATE_INDEX(state)) \
    ) \
/**/

#define    QOR_VMD_DETAIL_SEQUENCE_GET_FULL_TYPE_CHECK_ID(d,type,id) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_VMD_DETAIL_EQUAL_TYPE_D(d,type,QOR_VMD_TYPE_IDENTIFIER), \
            QOR_VMD_DETAIL_IDENTIFIER_TYPE_D, \
            QOR_VMD_IDENTITY(type) \
            ) \
        (d,id) \
        ) \
/**/

#define    QOR_VMD_DETAIL_SEQUENCE_GET_FULL_TYPE(d,state,tuple) \
    QOR_VMD_DETAIL_SEQUENCE_GET_FULL_TYPE_CHECK_ID \
        ( \
        d, \
        QOR_PP_CAT \
            ( \
            QOR_VMD_TYPE_, \
            QOR_VMD_DETAIL_SEQUENCE_STATE_GET_TYPE(state) \
            ), \
        QOR_PP_TUPLE_ELEM(0,tuple) \
        ) \
/**/

#define    QOR_VMD_DETAIL_SEQUENCE_TYPE_FOUND_PROCESS(d,state,tuple) \
    ( \
    QOR_PP_TUPLE_ELEM(1,tuple), \
    QOR_VMD_DETAIL_SEQUENCE_STATE_RESULT_ADD \
        ( \
        d, \
        state, \
            ( \
            QOR_VMD_DETAIL_SEQUENCE_GET_FULL_TYPE(d,state,tuple), \
            QOR_PP_TUPLE_ELEM(0,tuple) \
            ) \
        ), \
    QOR_VMD_DETAIL_SEQUENCE_STATE_ELEM(state), \
    QOR_VMD_DETAIL_SEQUENCE_STATE_OUTTYPE(state), \
    QOR_VMD_DETAIL_SEQUENCE_STATE_FROM(state), \
    QOR_VMD_DETAIL_SEQUENCE_STATE_TYPES(state), \
    QOR_PP_INC(QOR_PP_TUPLE_SIZE(QOR_VMD_DETAIL_SEQUENCE_STATE_TYPES(state))) \
    ) \
/**/

#define    QOR_VMD_DETAIL_SEQUENCE_TYPE_FOUND_SEQ_SINGLE(d,tuple) \
    QOR_PP_EQUAL_D(d,QOR_PP_SEQ_SIZE(QOR_PP_TUPLE_ELEM(0,tuple)),1) \
/**/

#define    QOR_VMD_DETAIL_SEQUENCE_TYPE_FOUND_SEQ(d,state,tuple) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_VMD_DETAIL_EQUAL_TYPE_D \
                ( \
                d, \
                QOR_VMD_DETAIL_SEQUENCE_GET_FULL_TYPE(d,state,tuple), \
                QOR_VMD_TYPE_SEQ \
                ), \
            QOR_VMD_DETAIL_SEQUENCE_TYPE_FOUND_SEQ_SINGLE, \
            QOR_VMD_IDENTITY(0) \
            ) \
        (d,tuple) \
        ) \
/**/

#define    QOR_VMD_DETAIL_SEQUENCE_TYPE_FOUND(d,state,tuple) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_SEQUENCE_TYPE_FOUND_SEQ(d,state,tuple), \
        QOR_VMD_DETAIL_SEQUENCE_INCREMENT_INDEX, \
        QOR_VMD_DETAIL_SEQUENCE_TYPE_FOUND_PROCESS \
        ) \
    (d,state,tuple) \
/**/

#define    QOR_VMD_DETAIL_SEQUENCE_INCREMENT_INDEX(d,state,tuple) \
    QOR_PP_TUPLE_REPLACE_D(d,state,QOR_VMD_DETAIL_SEQUENCE_STATE_INDEX_ELEM,QOR_PP_INC(QOR_VMD_DETAIL_SEQUENCE_STATE_INDEX(state))) \
/**/

#define    QOR_VMD_DETAIL_SEQUENCE_TEST_TYPE_TUPLE(d,state,tuple) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_IS_EMPTY \
            ( \
            QOR_PP_TUPLE_ELEM(0,tuple) \
            ), \
        QOR_VMD_DETAIL_SEQUENCE_INCREMENT_INDEX, \
        QOR_VMD_DETAIL_SEQUENCE_TYPE_FOUND \
        ) \
    (d,state,tuple) \
/**/

#define    QOR_VMD_DETAIL_SEQUENCE_TEST_TYPE(d,call,state) \
    QOR_VMD_DETAIL_SEQUENCE_TEST_TYPE_TUPLE \
        ( \
        d, \
        state, \
        call(QOR_VMD_DETAIL_SEQUENCE_STATE_INPUT(state),QOR_VMD_RETURN_AFTER) \
        ) \
/**/
    
#define    QOR_VMD_DETAIL_SEQUENCE_TEST_TYPE_D(d,call,state) \
    QOR_VMD_DETAIL_SEQUENCE_TEST_TYPE_TUPLE \
        ( \
        d, \
        state, \
        call(d,QOR_VMD_DETAIL_SEQUENCE_STATE_INPUT(state),QOR_VMD_RETURN_AFTER) \
        ) \
/**/
    
#define QOR_VMD_DETAIL_SEQUENCE_GCLRT(state) \
    QOR_PP_CAT \
        ( \
        QOR_VMD_DETAIL_, \
        QOR_PP_CAT(QOR_VMD_DETAIL_SEQUENCE_STATE_GET_TYPE(state),_D) \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_GCLPL(state) \
    QOR_PP_CAT \
        ( \
        QOR_VMD_DETAIL_, \
        QOR_VMD_DETAIL_SEQUENCE_STATE_GET_TYPE(state) \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_INNER_OP_TEST_GCL(state,rflag) \
    QOR_PP_IIF \
        ( \
        rflag, \
        QOR_VMD_DETAIL_SEQUENCE_GCLRT, \
        QOR_VMD_DETAIL_SEQUENCE_GCLPL \
        ) \
    (state) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_INNER_OP_TEST_RT_CALL(d,call,state,rflag) \
    QOR_PP_IIF \
        ( \
        rflag, \
        QOR_VMD_DETAIL_SEQUENCE_TEST_TYPE_D, \
        QOR_VMD_DETAIL_SEQUENCE_TEST_TYPE \
        ) \
    (d,call,state) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_INNER_OP_TEST_RT(d,state,rflag) \
    QOR_VMD_DETAIL_SEQUENCE_INNER_OP_TEST_RT_CALL \
        ( \
        d, \
        QOR_VMD_DETAIL_SEQUENCE_INNER_OP_TEST_GCL(state,rflag), \
        state, \
        rflag \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_INNER_OP_TEST(d,state) \
    QOR_VMD_DETAIL_SEQUENCE_INNER_OP_TEST_RT \
        ( \
        d, \
        state, \
        QOR_VMD_DETAIL_SEQUENCE_STATE_GET_TYPE_REENTRANT(state) \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_INNER_OP(d,state) \
    QOR_PP_IIF \
        ( \
        QOR_PP_EQUAL_D \
            ( \
            d, \
            QOR_VMD_DETAIL_SEQUENCE_STATE_INDEX(state), \
            QOR_PP_TUPLE_SIZE(QOR_VMD_DETAIL_SEQUENCE_STATE_TYPES(state)) \
            ), \
        QOR_VMD_DETAIL_SEQUENCE_INNER_OP_UNKNOWN, \
        QOR_VMD_DETAIL_SEQUENCE_INNER_OP_TEST \
        ) \
    (d,state) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_INNER_PRED(d,state) \
    QOR_PP_NOT_EQUAL_D \
        ( \
        d, \
        QOR_VMD_DETAIL_SEQUENCE_STATE_INDEX(state), \
        QOR_PP_INC(QOR_PP_TUPLE_SIZE(QOR_VMD_DETAIL_SEQUENCE_STATE_TYPES(state))) \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_OP_PAREN_TUPLE_TYPES_ELEM_FROM(d,from) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_SEQUENCE_STATE_IS_GENERAL_RETURN(d,from), \
        ((SEQ,1),(TUPLE,1)), \
        QOR_PP_IIF \
            ( \
            QOR_VMD_DETAIL_SEQUENCE_STATE_IS_EXACT_RETURN(d,from), \
            ((SEQ,1),(LIST,1),(ARRAY,1),(TUPLE,1)), \
            QOR_PP_IIF \
                ( \
                QOR_VMD_DETAIL_SEQUENCE_STATE_IS_ARRAY_RETURN(d,from), \
                ((SEQ,1),(ARRAY,1),(TUPLE,1)), \
                QOR_PP_IIF \
                    ( \
                    QOR_VMD_DETAIL_SEQUENCE_STATE_IS_LIST_RETURN(d,from), \
                    ((SEQ,1),(LIST,1),(TUPLE,1)), \
                    ((SEQ,1),(TUPLE,1)) \
                    ) \
                ) \
            ) \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_OP_PAREN_TUPLE_TYPES_ELEM(d,state) \
    QOR_VMD_DETAIL_SEQUENCE_OP_PAREN_TUPLE_TYPES_ELEM_FROM \
        ( \
        d, \
        QOR_VMD_DETAIL_SEQUENCE_STATE_FROM(state) \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_OP_PAREN_TUPLE_TYPES_ANY(d,state) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_VMD_IS_EMPTY \
                ( \
                QOR_VMD_DETAIL_SEQUENCE_STATE_ELEM(state) \
                ), \
            QOR_VMD_DETAIL_SEQUENCE_OP_PAREN_TUPLE_TYPES_ELEM, \
            QOR_VMD_IDENTITY(((SEQ,1),(TUPLE,1))) \
            ) \
        (d,state) \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_OP_PAREN_TUPLE_TYPES(d,state) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_SEQUENCE_PROCESSING_ELEM(d,state), \
        QOR_VMD_DETAIL_SEQUENCE_OP_PAREN_TUPLE_TYPES_ELEM, \
        QOR_VMD_DETAIL_SEQUENCE_OP_PAREN_TUPLE_TYPES_ANY \
        ) \
    (d,state) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_OP_PAREN(d,state) \
    QOR_PP_WHILE_ ## d \
        ( \
        QOR_VMD_DETAIL_SEQUENCE_INNER_PRED, \
        QOR_VMD_DETAIL_SEQUENCE_INNER_OP, \
        QOR_PP_TUPLE_PUSH_BACK \
            ( \
            QOR_PP_TUPLE_PUSH_BACK \
                ( \
                state, \
                QOR_VMD_DETAIL_SEQUENCE_OP_PAREN_TUPLE_TYPES(d,state) \
                ), \
            0 \
            ) \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_OP_ID_LOOP(d,state) \
    QOR_PP_WHILE_ ## d \
        ( \
        QOR_VMD_DETAIL_SEQUENCE_INNER_PRED, \
        QOR_VMD_DETAIL_SEQUENCE_INNER_OP, \
        QOR_PP_TUPLE_PUSH_BACK(QOR_PP_TUPLE_PUSH_BACK(state,((IDENTIFIER,1))),0) \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_OP_ID_EL(d,state) \
    ( \
    QOR_PP_TUPLE_ELEM(1,QOR_VMD_DETAIL_LIST_D(d,QOR_VMD_DETAIL_SEQUENCE_STATE_INPUT(state),QOR_VMD_RETURN_AFTER)), \
    QOR_VMD_DETAIL_SEQUENCE_STATE_RESULT_ADD(d,state,(QOR_VMD_TYPE_LIST,QOR_PP_NIL)), \
    QOR_VMD_DETAIL_SEQUENCE_STATE_ELEM(state), \
    QOR_VMD_DETAIL_SEQUENCE_STATE_OUTTYPE(state), \
    QOR_VMD_DETAIL_SEQUENCE_STATE_FROM(state) \
    ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_OP_ID(d,state) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_IS_EMPTY_LIST_D \
            ( \
            d, \
            QOR_VMD_DETAIL_IDENTIFIER_D \
                ( \
                d, \
                QOR_VMD_DETAIL_SEQUENCE_STATE_INPUT(state) \
                ) \
            ), \
        QOR_VMD_DETAIL_SEQUENCE_OP_ID_EL, \
        QOR_VMD_DETAIL_SEQUENCE_OP_ID_LOOP \
        ) \
    (d,state) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_OP_REDUCE_STATE(state) \
    ( \
    QOR_VMD_DETAIL_SEQUENCE_STATE_INPUT(state), \
    QOR_VMD_DETAIL_SEQUENCE_STATE_RESULT(state), \
    QOR_VMD_DETAIL_SEQUENCE_STATE_ELEM(state), \
    QOR_VMD_DETAIL_SEQUENCE_STATE_OUTTYPE(state), \
    QOR_VMD_DETAIL_SEQUENCE_STATE_FROM(state) \
    ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_OP(d,state) \
    QOR_VMD_DETAIL_SEQUENCE_OP_REDUCE_STATE \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_PP_IS_BEGIN_PARENS \
                ( \
                QOR_VMD_DETAIL_SEQUENCE_STATE_INPUT(state) \
                ), \
            QOR_VMD_DETAIL_SEQUENCE_OP_PAREN, \
            QOR_VMD_DETAIL_SEQUENCE_OP_ID \
            ) \
        (d,state) \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_PRED_CELEM_SZ(d,state) \
    QOR_PP_LESS_EQUAL_D \
        ( \
        d, \
        QOR_PP_SEQ_SIZE(QOR_VMD_DETAIL_SEQUENCE_STATE_RESULT(state)), \
        QOR_VMD_DETAIL_SEQUENCE_STATE_ELEM(state) \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_PRED_CELEM(d,state) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_PP_BITOR \
                ( \
                QOR_VMD_IS_EMPTY \
                    ( \
                    QOR_VMD_DETAIL_SEQUENCE_STATE_ELEM(state) \
                    ), \
                QOR_VMD_IS_EMPTY \
                    ( \
                    QOR_VMD_DETAIL_SEQUENCE_STATE_RESULT(state) \
                    ) \
                ), \
            QOR_VMD_IDENTITY(1), \
            QOR_VMD_DETAIL_SEQUENCE_PRED_CELEM_SZ \
            ) \
        (d,state) \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_PRED(d,state) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_VMD_IS_EMPTY \
                ( \
                QOR_VMD_DETAIL_SEQUENCE_STATE_INPUT(state) \
                ), \
            QOR_VMD_IDENTITY(0), \
            QOR_VMD_DETAIL_SEQUENCE_PRED_CELEM \
            ) \
        (d,state) \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_EMPTY_TYPE_CHECK(output) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_EQUAL_TYPE(output,QOR_VMD_TYPE_ARRAY), \
        (0,()), \
        QOR_PP_NIL \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_EMPTY_TYPE_CHECK_D(d,output) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_EQUAL_TYPE_D(d,output,QOR_VMD_TYPE_ARRAY), \
        (0,()), \
        QOR_PP_NIL \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_EMPTY_TYPE(output) \
    QOR_PP_IIF \
        ( \
        QOR_PP_BITOR \
            ( \
            QOR_VMD_DETAIL_EQUAL_TYPE(output,QOR_VMD_TYPE_SEQ), \
            QOR_VMD_DETAIL_EQUAL_TYPE(output,QOR_VMD_TYPE_TUPLE) \
            ), \
        QOR_VMD_EMPTY, \
        QOR_VMD_DETAIL_SEQUENCE_EMPTY_TYPE_CHECK \
        ) \
    (output) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_EMPTY_TYPE_D(d,output) \
    QOR_PP_IIF \
        ( \
        QOR_PP_BITOR \
            ( \
            QOR_VMD_DETAIL_EQUAL_TYPE_D(d,output,QOR_VMD_TYPE_SEQ), \
            QOR_VMD_DETAIL_EQUAL_TYPE_D(d,output,QOR_VMD_TYPE_TUPLE) \
            ), \
        QOR_VMD_EMPTY, \
        QOR_VMD_DETAIL_SEQUENCE_EMPTY_TYPE_CHECK_D \
        ) \
    (d,output) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_PROCESS_TUPLE_GET(state) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_SEQUENCE_STATE_IS_AFTER \
            ( \
            QOR_VMD_DETAIL_SEQUENCE_STATE_FROM(state) \
            ), \
            ( \
            QOR_VMD_DETAIL_SEQUENCE_STATE_RESULT(state), \
            QOR_VMD_DETAIL_SEQUENCE_STATE_INPUT(state) \
            ), \
            QOR_VMD_DETAIL_SEQUENCE_STATE_RESULT(state) \
        ) 
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_PROCESS_TUPLE_GET_D(d,state) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_SEQUENCE_STATE_IS_AFTER_D \
            ( \
            d, \
            QOR_VMD_DETAIL_SEQUENCE_STATE_FROM(state) \
            ), \
            ( \
            QOR_VMD_DETAIL_SEQUENCE_STATE_RESULT(state), \
            QOR_VMD_DETAIL_SEQUENCE_STATE_INPUT(state) \
            ), \
            QOR_VMD_DETAIL_SEQUENCE_STATE_RESULT(state) \
        ) 
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_PROCESS_TUPLE(vseq,elem,output,from) \
    QOR_VMD_DETAIL_SEQUENCE_ELEM_PROCESS_TUPLE_GET \
        ( \
        QOR_PP_WHILE \
            ( \
            QOR_VMD_DETAIL_SEQUENCE_PRED, \
            QOR_VMD_DETAIL_SEQUENCE_OP, \
                ( \
                vseq, \
                QOR_VMD_DETAIL_SEQUENCE_EMPTY_TYPE \
                    ( \
                    output \
                    ), \
                elem, \
                output, \
                from \
                ) \
            ) \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_PROCESS_TUPLE_D(d,vseq,elem,output,from) \
    QOR_VMD_DETAIL_SEQUENCE_ELEM_PROCESS_TUPLE_GET_D \
        ( \
        d, \
        QOR_PP_WHILE_ ## d \
            ( \
            QOR_VMD_DETAIL_SEQUENCE_PRED, \
            QOR_VMD_DETAIL_SEQUENCE_OP, \
                ( \
                vseq, \
                QOR_VMD_DETAIL_SEQUENCE_EMPTY_TYPE_D \
                    ( \
                    d, \
                    output \
                    ), \
                elem, \
                output, \
                from \
                ) \
            ) \
        ) \
/**/

#endif /* QOR_VMD_DETAIL_SEQUENCE_COMMON_H */
