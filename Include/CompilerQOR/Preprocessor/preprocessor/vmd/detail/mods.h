
//  (C) Copyright Edward Diener 2011-2015
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(QOR_VMD_DETAIL_MODS_H)
#define QOR_VMD_DETAIL_MODS_H

#include "CompilerQOR/Preprocessor/preprocessor/arithmetic/inc.h"
#include "CompilerQOR/Preprocessor/preprocessor/comparison/equal.h"
#include "CompilerQOR/Preprocessor/preprocessor/comparison/greater.h"
#include "CompilerQOR/Preprocessor/preprocessor/control/iif.h"
#include "CompilerQOR/Preprocessor/preprocessor/control/while.h"
#include "CompilerQOR/Preprocessor/preprocessor/punctuation/is_begin_parens.h"
#include "CompilerQOR/Preprocessor/preprocessor/tuple/elem.h"
#include "CompilerQOR/Preprocessor/preprocessor/tuple/pop_front.h"
#include "CompilerQOR/Preprocessor/preprocessor/tuple/push_back.h"
#include "CompilerQOR/Preprocessor/preprocessor/tuple/replace.h"
#include "CompilerQOR/Preprocessor/preprocessor/tuple/size.h"
#include "CompilerQOR/Preprocessor/preprocessor/variadic/to_tuple.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/identity.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/is_empty.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/is_type.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/modifiers.h"

#define QOR_VMD_DETAIL_MODS_NO_RETURN 0
#define QOR_VMD_DETAIL_MODS_RETURN 1
#define QOR_VMD_DETAIL_MODS_RETURN_TUPLE 2
#define QOR_VMD_DETAIL_MODS_RETURN_ARRAY 3
#define QOR_VMD_DETAIL_MODS_RETURN_LIST 4
#define QOR_VMD_DETAIL_MODS_NO_AFTER 0
#define QOR_VMD_DETAIL_MODS_RETURN_AFTER 1
#define QOR_VMD_DETAIL_MODS_NO_INDEX 0
#define QOR_VMD_DETAIL_MODS_RETURN_INDEX 1
#define QOR_VMD_DETAIL_MODS_NO_ONLY_AFTER 0
#define QOR_VMD_DETAIL_MODS_RETURN_ONLY_AFTER 1

#define QOR_VMD_DETAIL_MODS_TUPLE_RETURN 0
#define QOR_VMD_DETAIL_MODS_TUPLE_AFTER 1
#define QOR_VMD_DETAIL_MODS_TUPLE_INDEX 2
#define QOR_VMD_DETAIL_MODS_TUPLE_OTHER 3
#define QOR_VMD_DETAIL_MODS_TUPLE_ONLY_AFTER 4
#define QOR_VMD_DETAIL_MODS_TUPLE_TYPE 5

#define QOR_VMD_DETAIL_MODS_DATA_INPUT 0
#define QOR_VMD_DETAIL_MODS_DATA_INDEX 1
#define QOR_VMD_DETAIL_MODS_DATA_SIZE 2
#define QOR_VMD_DETAIL_MODS_DATA_RESULT 3
#define QOR_VMD_DETAIL_MODS_DATA_ALLOW 4

#define QOR_VMD_DETAIL_MODS_STATE_INPUT(state) \
    QOR_PP_TUPLE_ELEM(QOR_VMD_DETAIL_MODS_DATA_INPUT,state) \
/**/

#define QOR_VMD_DETAIL_MODS_STATE_INDEX(state) \
    QOR_PP_TUPLE_ELEM(QOR_VMD_DETAIL_MODS_DATA_INDEX,state) \
/**/

#define QOR_VMD_DETAIL_MODS_STATE_SIZE(state) \
    QOR_PP_TUPLE_ELEM(QOR_VMD_DETAIL_MODS_DATA_SIZE,state) \
/**/

#define QOR_VMD_DETAIL_MODS_STATE_RESULT(state) \
    QOR_PP_TUPLE_ELEM(QOR_VMD_DETAIL_MODS_DATA_RESULT,state) \
/**/

#define QOR_VMD_DETAIL_MODS_STATE_ALLOW(state) \
    QOR_PP_TUPLE_ELEM(QOR_VMD_DETAIL_MODS_DATA_ALLOW,state) \
/**/

#define QOR_VMD_DETAIL_MODS_STATE_IS_ALLOW_ALL(state) \
    QOR_VMD_DETAIL_IS_ALLOW_ALL(QOR_VMD_DETAIL_MODS_STATE_ALLOW(state)) \
/**/

#define QOR_VMD_DETAIL_MODS_STATE_IS_ALLOW_RETURN(state) \
    QOR_VMD_DETAIL_IS_ALLOW_RETURN(QOR_VMD_DETAIL_MODS_STATE_ALLOW(state)) \
/**/

#define QOR_VMD_DETAIL_MODS_STATE_IS_ALLOW_AFTER(state) \
    QOR_VMD_DETAIL_IS_ALLOW_AFTER(QOR_VMD_DETAIL_MODS_STATE_ALLOW(state)) \
/**/

#define QOR_VMD_DETAIL_MODS_STATE_IS_ALLOW_INDEX(state) \
    QOR_VMD_DETAIL_IS_ALLOW_INDEX(QOR_VMD_DETAIL_MODS_STATE_ALLOW(state)) \
/**/

#define QOR_VMD_DETAIL_MODS_STATE_CURRENT(state) \
    QOR_PP_TUPLE_ELEM(QOR_VMD_DETAIL_MODS_STATE_INDEX(state),QOR_VMD_DETAIL_MODS_STATE_INPUT(state)) \
/**/

#define QOR_VMD_DETAIL_MODS_STATE_TYPE(state) \
    QOR_PP_TUPLE_ELEM(QOR_VMD_DETAIL_MODS_TUPLE_RETURN,QOR_VMD_DETAIL_MODS_STATE_RESULT(state)) \
/**/

#define QOR_VMD_DETAIL_MODS_STATE_AFTER(state) \
    QOR_PP_TUPLE_ELEM(QOR_VMD_DETAIL_MODS_TUPLE_AFTER,QOR_VMD_DETAIL_MODS_STATE_RESULT(state)) \
/**/

#define QOR_VMD_DETAIL_MODS_STATE_ONLY_AFTER(state) \
    QOR_PP_TUPLE_ELEM(QOR_VMD_DETAIL_MODS_TUPLE_ONLY_AFTER,QOR_VMD_DETAIL_MODS_STATE_RESULT(state)) \
/**/

#define QOR_VMD_DETAIL_MODS_STATE_TINDEX(state) \
    QOR_PP_TUPLE_ELEM(QOR_VMD_DETAIL_MODS_TUPLE_INDEX,QOR_VMD_DETAIL_MODS_STATE_RESULT(state)) \
/**/

#define QOR_VMD_DETAIL_MODS_RESULT_RETURN_TYPE(result) \
    QOR_PP_TUPLE_ELEM(QOR_VMD_DETAIL_MODS_TUPLE_RETURN,result) \
/**/

#define QOR_VMD_DETAIL_MODS_IS_RESULT_AFTER(result) \
    QOR_PP_TUPLE_ELEM(QOR_VMD_DETAIL_MODS_TUPLE_AFTER,result) \
/**/

#define QOR_VMD_DETAIL_MODS_IS_RESULT_ONLY_AFTER(result) \
    QOR_PP_TUPLE_ELEM(QOR_VMD_DETAIL_MODS_TUPLE_ONLY_AFTER,result) \
/**/

#define QOR_VMD_DETAIL_MODS_IS_RESULT_INDEX(result) \
    QOR_PP_TUPLE_ELEM(QOR_VMD_DETAIL_MODS_TUPLE_INDEX,result) \
/**/

#define QOR_VMD_DETAIL_MODS_RESULT_OTHER(result) \
    QOR_PP_TUPLE_ELEM(QOR_VMD_DETAIL_MODS_TUPLE_OTHER,result) \
/**/

#define QOR_VMD_DETAIL_MODS_RESULT_TYPE(result) \
    QOR_PP_TUPLE_ELEM(QOR_VMD_DETAIL_MODS_TUPLE_TYPE,result) \
/**/

#define QOR_VMD_DETAIL_MODS_PRED(d,state) \
    QOR_PP_GREATER_D(d,QOR_VMD_DETAIL_MODS_STATE_SIZE(state),QOR_VMD_DETAIL_MODS_STATE_INDEX(state))
/**/

#define QOR_VMD_DETAIL_MODS_OP_CURRENT_RETURN_TYPE(d,state,number) \
    QOR_VMD_DETAIL_MODS_OP_CURRENT_UPDATE \
        ( \
        d, \
        QOR_PP_TUPLE_REPLACE_D \
            ( \
            d, \
            state, \
            QOR_VMD_DETAIL_MODS_DATA_RESULT, \
            QOR_PP_TUPLE_REPLACE_D \
                ( \
                d, \
                QOR_VMD_DETAIL_MODS_STATE_RESULT(state), \
                QOR_VMD_DETAIL_MODS_TUPLE_RETURN, \
                number \
                ) \
            ) \
        ) \
/**/

#define QOR_VMD_DETAIL_MODS_OP_CURRENT_ONLY_AFTER(d,state,id) \
    QOR_VMD_DETAIL_MODS_OP_CURRENT_UPDATE \
        ( \
        d, \
        QOR_PP_TUPLE_REPLACE_D \
            ( \
            d, \
            state, \
            QOR_VMD_DETAIL_MODS_DATA_RESULT, \
            QOR_PP_TUPLE_REPLACE_D \
                ( \
                d, \
                QOR_PP_TUPLE_REPLACE_D \
                    ( \
                    d, \
                    QOR_VMD_DETAIL_MODS_STATE_RESULT(state), \
                    QOR_VMD_DETAIL_MODS_TUPLE_ONLY_AFTER, \
                    1 \
                    ), \
                QOR_VMD_DETAIL_MODS_TUPLE_AFTER, \
                1 \
                ) \
            ) \
        ) \
/**/

#define QOR_VMD_DETAIL_MODS_OP_CURRENT_INDEX(d,state,number) \
    QOR_VMD_DETAIL_MODS_OP_CURRENT_UPDATE \
        ( \
        d, \
        QOR_PP_TUPLE_REPLACE_D \
            ( \
            d, \
            state, \
            QOR_VMD_DETAIL_MODS_DATA_RESULT, \
            QOR_PP_TUPLE_REPLACE_D \
                ( \
                d, \
                QOR_VMD_DETAIL_MODS_STATE_RESULT(state), \
                QOR_VMD_DETAIL_MODS_TUPLE_INDEX, \
                number \
                ) \
            ) \
        ) \
/**/

#define QOR_VMD_DETAIL_MODS_OP_CURRENT_GTT(d,state,id) \
    QOR_VMD_DETAIL_MODS_OP_CURRENT_RETURN_TYPE(d,state,QOR_VMD_DETAIL_MODS_RETURN_TUPLE) \
/**/

#define QOR_VMD_DETAIL_MODS_OP_CURRENT_ET(d,state,id) \
    QOR_VMD_DETAIL_MODS_OP_CURRENT_RETURN_TYPE(d,state,QOR_VMD_DETAIL_MODS_RETURN) \
/**/

#define QOR_VMD_DETAIL_MODS_OP_CURRENT_SA(d,state,id) \
    QOR_VMD_DETAIL_MODS_OP_CURRENT_RETURN_TYPE(d,state,QOR_VMD_DETAIL_MODS_RETURN_ARRAY) \
/**/

#define QOR_VMD_DETAIL_MODS_OP_CURRENT_SL(d,state,id) \
    QOR_VMD_DETAIL_MODS_OP_CURRENT_RETURN_TYPE(d,state,QOR_VMD_DETAIL_MODS_RETURN_LIST) \
/**/

#define QOR_VMD_DETAIL_MODS_OP_CURRENT_NT(d,state,id) \
    QOR_VMD_DETAIL_MODS_OP_CURRENT_RETURN_TYPE(d,state,QOR_VMD_DETAIL_MODS_NO_RETURN) \
/**/

#define QOR_VMD_DETAIL_MODS_OP_CURRENT_AFT(d,state,id) \
    QOR_VMD_DETAIL_MODS_OP_CURRENT_UPDATE \
        ( \
        d, \
        QOR_PP_TUPLE_REPLACE_D \
            ( \
            d, \
            state, \
            QOR_VMD_DETAIL_MODS_DATA_RESULT, \
            QOR_PP_TUPLE_REPLACE_D \
                ( \
                d, \
                QOR_VMD_DETAIL_MODS_STATE_RESULT(state), \
                QOR_VMD_DETAIL_MODS_TUPLE_AFTER, \
                QOR_VMD_DETAIL_MODS_RETURN_AFTER \
                ) \
            ) \
        ) \
/**/

#define QOR_VMD_DETAIL_MODS_OP_CURRENT_NOAFT(d,state,id) \
    QOR_VMD_DETAIL_MODS_OP_CURRENT_UPDATE \
        ( \
        d, \
        QOR_PP_TUPLE_REPLACE_D \
            ( \
            d, \
            state, \
            QOR_VMD_DETAIL_MODS_DATA_RESULT, \
            QOR_PP_TUPLE_REPLACE_D \
                ( \
                d, \
                QOR_PP_TUPLE_REPLACE_D \
                    ( \
                    d, \
                    QOR_VMD_DETAIL_MODS_STATE_RESULT(state), \
                    QOR_VMD_DETAIL_MODS_TUPLE_ONLY_AFTER, \
                    0 \
                    ), \
                QOR_VMD_DETAIL_MODS_TUPLE_AFTER, \
                QOR_VMD_DETAIL_MODS_NO_AFTER \
                ) \
            ) \
        ) \
/**/

#define QOR_VMD_DETAIL_MODS_OP_CURRENT_IND(d,state,id) \
    QOR_VMD_DETAIL_MODS_OP_CURRENT_INDEX(d,state,QOR_VMD_DETAIL_MODS_RETURN_INDEX) \
/**/

#define QOR_VMD_DETAIL_MODS_OP_CURRENT_NO_IND(d,state,id) \
    QOR_VMD_DETAIL_MODS_OP_CURRENT_INDEX(d,state,QOR_VMD_DETAIL_MODS_NO_INDEX) \
/**/

#define QOR_VMD_DETAIL_MODS_OP_CURRENT_UNKNOWN_CTUPLE_REPLACE(d,state,id) \
    QOR_PP_TUPLE_REPLACE_D \
        ( \
        d, \
        QOR_VMD_DETAIL_MODS_STATE_RESULT(state), \
        QOR_VMD_DETAIL_MODS_TUPLE_OTHER, \
        QOR_PP_VARIADIC_TO_TUPLE(id) \
        ) \
/**/

#define QOR_VMD_DETAIL_MODS_OP_CURRENT_UNKNOWN_CTUPLE_ADD(d,state,id) \
    QOR_PP_TUPLE_REPLACE_D \
        ( \
        d, \
        QOR_VMD_DETAIL_MODS_STATE_RESULT(state), \
        QOR_VMD_DETAIL_MODS_TUPLE_OTHER, \
        QOR_PP_TUPLE_PUSH_BACK \
            ( \
            QOR_VMD_DETAIL_MODS_RESULT_OTHER(QOR_VMD_DETAIL_MODS_STATE_RESULT(state)), \
            id \
            ) \
        ) \
/**/

#define QOR_VMD_DETAIL_MODS_OP_CURRENT_UNKNOWN_CTUPLE(d,state,id) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_IS_EMPTY \
            ( \
            QOR_VMD_DETAIL_MODS_RESULT_OTHER(QOR_VMD_DETAIL_MODS_STATE_RESULT(state)) \
            ), \
        QOR_VMD_DETAIL_MODS_OP_CURRENT_UNKNOWN_CTUPLE_REPLACE, \
        QOR_VMD_DETAIL_MODS_OP_CURRENT_UNKNOWN_CTUPLE_ADD \
        ) \
    (d,state,id) \
/**/

#define QOR_VMD_DETAIL_MODS_OP_CURRENT_UNKNOWN_TYPE_RETURN(d,state,id) \
    QOR_PP_TUPLE_REPLACE_D \
        ( \
        d, \
        QOR_VMD_DETAIL_MODS_STATE_RESULT(state), \
        QOR_VMD_DETAIL_MODS_TUPLE_RETURN, \
        QOR_PP_IIF \
            ( \
            QOR_VMD_DETAIL_EQUAL_TYPE_D(d,id,QOR_VMD_TYPE_ARRAY), \
            QOR_VMD_DETAIL_MODS_RETURN_ARRAY, \
            QOR_PP_IIF \
                ( \
                QOR_VMD_DETAIL_EQUAL_TYPE_D(d,id,QOR_VMD_TYPE_LIST), \
                QOR_VMD_DETAIL_MODS_RETURN_LIST, \
                QOR_VMD_DETAIL_MODS_RETURN_TUPLE \
                ) \
            ) \
        ) \
/**/

#define QOR_VMD_DETAIL_MODS_OP_CURRENT_UNKNOWN_TYPE(d,state,id) \
    QOR_PP_TUPLE_REPLACE_D \
        ( \
        d, \
        QOR_VMD_DETAIL_MODS_OP_CURRENT_UNKNOWN_TYPE_RETURN(d,state,id), \
        QOR_VMD_DETAIL_MODS_TUPLE_TYPE, \
        id \
        ) \
/**/

#define QOR_VMD_DETAIL_MODS_OP_CURRENT_UNKNOWN(d,state,id) \
    QOR_VMD_DETAIL_MODS_OP_CURRENT_UPDATE \
        ( \
        d, \
        QOR_PP_TUPLE_REPLACE_D \
            ( \
            d, \
            state, \
            QOR_VMD_DETAIL_MODS_DATA_RESULT, \
            QOR_PP_IIF \
                ( \
                QOR_PP_BITAND \
                    ( \
                    QOR_VMD_DETAIL_MODS_STATE_IS_ALLOW_ALL(state), \
                    QOR_VMD_IS_TYPE_D(d,id) \
                    ), \
                QOR_VMD_DETAIL_MODS_OP_CURRENT_UNKNOWN_TYPE, \
                QOR_VMD_DETAIL_MODS_OP_CURRENT_UNKNOWN_CTUPLE \
                ) \
            (d,state,id) \
            ) \
        ) \
/**/

#define QOR_VMD_DETAIL_MODS_OP_CURRENT_UPDATE(d,state) \
    QOR_PP_TUPLE_REPLACE_D \
        ( \
        d, \
        state, \
        QOR_VMD_DETAIL_MODS_DATA_INDEX, \
        QOR_PP_INC(QOR_VMD_DETAIL_MODS_STATE_INDEX(state)) \
        ) \
/**/

#define QOR_VMD_DETAIL_MODS_OP_CURRENT_ALLOW_ALL(d,state,id) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_IS_RETURN_TYPE_TUPLE(id), \
        QOR_VMD_DETAIL_MODS_OP_CURRENT_GTT, \
        QOR_PP_IIF \
            ( \
            QOR_VMD_DETAIL_IS_RETURN_TYPE(id), \
            QOR_VMD_DETAIL_MODS_OP_CURRENT_ET, \
            QOR_PP_IIF \
                ( \
                QOR_VMD_DETAIL_IS_RETURN_TYPE_ARRAY(id), \
                QOR_VMD_DETAIL_MODS_OP_CURRENT_SA, \
                QOR_PP_IIF \
                    ( \
                    QOR_VMD_DETAIL_IS_RETURN_TYPE_LIST(id), \
                    QOR_VMD_DETAIL_MODS_OP_CURRENT_SL, \
                    QOR_PP_IIF \
                        ( \
                        QOR_VMD_DETAIL_IS_RETURN_NO_TYPE(id), \
                        QOR_VMD_DETAIL_MODS_OP_CURRENT_NT, \
                        QOR_PP_IIF \
                            ( \
                            QOR_VMD_DETAIL_IS_RETURN_AFTER(id), \
                            QOR_VMD_DETAIL_MODS_OP_CURRENT_AFT, \
                            QOR_PP_IIF \
                                ( \
                                QOR_VMD_DETAIL_IS_RETURN_NO_AFTER(id), \
                                QOR_VMD_DETAIL_MODS_OP_CURRENT_NOAFT, \
                                QOR_PP_IIF \
                                    ( \
                                    QOR_VMD_DETAIL_IS_RETURN_ONLY_AFTER(id), \
                                    QOR_VMD_DETAIL_MODS_OP_CURRENT_ONLY_AFTER, \
                                    QOR_PP_IIF \
                                        ( \
                                        QOR_VMD_DETAIL_IS_RETURN_INDEX(id), \
                                        QOR_VMD_DETAIL_MODS_OP_CURRENT_IND, \
                                        QOR_PP_IIF \
                                            ( \
                                            QOR_VMD_DETAIL_IS_RETURN_NO_INDEX(id), \
                                            QOR_VMD_DETAIL_MODS_OP_CURRENT_NO_IND, \
                                            QOR_VMD_DETAIL_MODS_OP_CURRENT_UNKNOWN \
                                            ) \
                                        ) \
                                    ) \
                                ) \
                            ) \
                        ) \
                    ) \
                ) \
            ) \
        ) \
    (d,state,id) \
/**/

#define QOR_VMD_DETAIL_MODS_OP_CURRENT_ALLOW_RETURN(d,state,id) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_IS_RETURN_TYPE_TUPLE(id), \
        QOR_VMD_DETAIL_MODS_OP_CURRENT_GTT, \
        QOR_PP_IIF \
            ( \
            QOR_VMD_DETAIL_IS_RETURN_TYPE(id), \
            QOR_VMD_DETAIL_MODS_OP_CURRENT_ET, \
            QOR_PP_IIF \
                ( \
                QOR_VMD_DETAIL_IS_RETURN_TYPE_ARRAY(id), \
                QOR_VMD_DETAIL_MODS_OP_CURRENT_SA, \
                QOR_PP_IIF \
                    ( \
                    QOR_VMD_DETAIL_IS_RETURN_TYPE_LIST(id), \
                    QOR_VMD_DETAIL_MODS_OP_CURRENT_SL, \
                    QOR_PP_IIF \
                        ( \
                        QOR_VMD_DETAIL_IS_RETURN_NO_TYPE(id), \
                        QOR_VMD_DETAIL_MODS_OP_CURRENT_NT, \
                        QOR_VMD_DETAIL_MODS_OP_CURRENT_UNKNOWN \
                        ) \
                    ) \
                ) \
            ) \
        ) \
    (d,state,id) \
/**/

#define QOR_VMD_DETAIL_MODS_OP_CURRENT_ALLOW_AFTER(d,state,id) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_IS_RETURN_AFTER(id), \
        QOR_VMD_DETAIL_MODS_OP_CURRENT_AFT, \
        QOR_PP_IIF \
            ( \
            QOR_VMD_DETAIL_IS_RETURN_NO_AFTER(id), \
            QOR_VMD_DETAIL_MODS_OP_CURRENT_NOAFT, \
            QOR_PP_IIF \
                ( \
                QOR_VMD_DETAIL_IS_RETURN_ONLY_AFTER(id), \
                QOR_VMD_DETAIL_MODS_OP_CURRENT_ONLY_AFTER, \
                QOR_VMD_DETAIL_MODS_OP_CURRENT_UNKNOWN \
                ) \
            ) \
        ) \
    (d,state,id) \
/**/

#define QOR_VMD_DETAIL_MODS_OP_CURRENT_ALLOW_INDEX(d,state,id) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_IS_RETURN_AFTER(id), \
        QOR_VMD_DETAIL_MODS_OP_CURRENT_AFT, \
        QOR_PP_IIF \
            ( \
            QOR_VMD_DETAIL_IS_RETURN_NO_AFTER(id), \
            QOR_VMD_DETAIL_MODS_OP_CURRENT_NOAFT, \
            QOR_PP_IIF \
                ( \
                QOR_VMD_DETAIL_IS_RETURN_ONLY_AFTER(id), \
                QOR_VMD_DETAIL_MODS_OP_CURRENT_ONLY_AFTER, \
                QOR_PP_IIF \
                    ( \
                    QOR_VMD_DETAIL_IS_RETURN_INDEX(id), \
                    QOR_VMD_DETAIL_MODS_OP_CURRENT_IND, \
                    QOR_PP_IIF \
                        ( \
                        QOR_VMD_DETAIL_IS_RETURN_NO_INDEX(id), \
                        QOR_VMD_DETAIL_MODS_OP_CURRENT_NO_IND, \
                        QOR_VMD_DETAIL_MODS_OP_CURRENT_UNKNOWN \
                        ) \
                    ) \
                ) \
            ) \
        ) \
    (d,state,id) \
/**/

#define QOR_VMD_DETAIL_MODS_OP_CURRENT_ALLOW_UPDATE(d,state,id) \
    QOR_VMD_DETAIL_MODS_OP_CURRENT_UPDATE(d,state) \
/**/

#define QOR_VMD_DETAIL_MODS_OP_CURRENT_ID(d,state,id) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_MODS_STATE_IS_ALLOW_ALL(state), \
        QOR_VMD_DETAIL_MODS_OP_CURRENT_ALLOW_ALL, \
        QOR_PP_IIF \
            ( \
            QOR_VMD_DETAIL_MODS_STATE_IS_ALLOW_RETURN(state), \
            QOR_VMD_DETAIL_MODS_OP_CURRENT_ALLOW_RETURN, \
            QOR_PP_IIF \
                ( \
                QOR_VMD_DETAIL_MODS_STATE_IS_ALLOW_AFTER(state), \
                QOR_VMD_DETAIL_MODS_OP_CURRENT_ALLOW_AFTER, \
                QOR_PP_IIF \
                    ( \
                    QOR_VMD_DETAIL_MODS_STATE_IS_ALLOW_INDEX(state), \
                    QOR_VMD_DETAIL_MODS_OP_CURRENT_ALLOW_INDEX, \
                    QOR_VMD_DETAIL_MODS_OP_CURRENT_ALLOW_UPDATE \
                    ) \
                ) \
            ) \
        ) \
    (d,state,id) \
/**/

#define QOR_VMD_DETAIL_MODS_OP_CURRENT_TUPLE(d,state,id) \
    QOR_VMD_DETAIL_MODS_OP_CURRENT_UPDATE \
        ( \
        d, \
        QOR_PP_TUPLE_REPLACE_D \
            ( \
            d, \
            state, \
            QOR_VMD_DETAIL_MODS_DATA_RESULT, \
            QOR_PP_TUPLE_REPLACE_D \
                ( \
                d, \
                QOR_VMD_DETAIL_MODS_STATE_RESULT(state), \
                QOR_VMD_DETAIL_MODS_TUPLE_OTHER, \
                id \
                ) \
            ) \
        ) \
/**/

#define QOR_VMD_DETAIL_MODS_OP_CURRENT(d,state,id) \
    QOR_PP_IIF \
        ( \
        QOR_PP_IS_BEGIN_PARENS(id), \
        QOR_VMD_DETAIL_MODS_OP_CURRENT_TUPLE, \
        QOR_VMD_DETAIL_MODS_OP_CURRENT_ID \
        ) \
    (d,state,id) \
/**/

#define QOR_VMD_DETAIL_MODS_OP(d,state) \
    QOR_VMD_DETAIL_MODS_OP_CURRENT(d,state,QOR_VMD_DETAIL_MODS_STATE_CURRENT(state)) \
/**/

#define QOR_VMD_DETAIL_MODS_LOOP(allow,tuple) \
    QOR_PP_TUPLE_ELEM \
        ( \
        3, \
        QOR_PP_WHILE \
            ( \
            QOR_VMD_DETAIL_MODS_PRED, \
            QOR_VMD_DETAIL_MODS_OP, \
                ( \
                tuple, \
                0, \
                QOR_PP_TUPLE_SIZE(tuple), \
                (0,0,0,,0,), \
                allow \
                ) \
            ) \
        ) \
/**/

#define QOR_VMD_DETAIL_MODS_LOOP_D(d,allow,tuple) \
    QOR_PP_TUPLE_ELEM \
        ( \
        3, \
        QOR_PP_WHILE_ ## d \
            ( \
            QOR_VMD_DETAIL_MODS_PRED, \
            QOR_VMD_DETAIL_MODS_OP, \
                ( \
                tuple, \
                0, \
                QOR_PP_TUPLE_SIZE(tuple), \
                (0,0,0,,0,), \
                allow \
                ) \
            ) \
        ) \
/**/

#define QOR_VMD_DETAIL_NEW_MODS_VAR(allow,tuple) \
    QOR_VMD_DETAIL_MODS_LOOP \
        ( \
        allow, \
        QOR_PP_TUPLE_POP_FRONT(tuple) \
        ) \
/**/

#define QOR_VMD_DETAIL_NEW_MODS_VAR_D(d,allow,tuple) \
    QOR_VMD_DETAIL_MODS_LOOP_D \
        ( \
        d, \
        allow, \
        QOR_PP_TUPLE_POP_FRONT(tuple) \
        ) \
/**/

#define QOR_VMD_DETAIL_NEW_MODS_IR(allow,tuple) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_PP_EQUAL(QOR_PP_TUPLE_SIZE(tuple),1), \
            QOR_VMD_IDENTITY((0,0,0,,0,)), \
            QOR_VMD_DETAIL_NEW_MODS_VAR \
            ) \
        (allow,tuple) \
        ) \
/**/

#define QOR_VMD_DETAIL_NEW_MODS_IR_D(d,allow,tuple) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_PP_EQUAL_D(d,QOR_PP_TUPLE_SIZE(tuple),1), \
            QOR_VMD_IDENTITY((0,0,0,,0,)), \
            QOR_VMD_DETAIL_NEW_MODS_VAR_D \
            ) \
        (d,allow,tuple) \
        ) \
/**/

/*

  Returns a six-element tuple:
  
  First tuple element  = 0 No type return
                         1 Exact type return
                         2 General tuple type return
                         3 Array return
                         4 List return
                         
  Second tuple element = 0 No after return
                         1 After return
                         
  Third tuple element  = 0 No identifier index
                         1 Identifier Index
                         
  Fourth tuple element = Tuple of other identifiers
  
  Fifth tuple element  = 0 No after only return
                         1 After only return
                         
  Sixth tuple element  = Type identifier
                         
  Input                = allow, either
                         QOR_VMD_ALLOW_ALL
                         QOR_VMD_ALLOW_RETURN
                         QOR_VMD_ALLOW_AFTER
                         QOR_VMD_ALLOW_INDEX
                         
                           ..., modifiers, first variadic is discarded
                         Possible modifiers are:
                         
                         QOR_VMD_RETURN_NO_TYPE = (0,0)
                         QOR_VMD_RETURN_TYPE = (1,0)
                         QOR_VMD_RETURN_TYPE_TUPLE = (2,0)
                         QOR_VMD_RETURN_TYPE_ARRAY = (3,0)
                         QOR_VMD_RETURN_TYPE_LIST = (4,0)
                         
                         QOR_VMD_RETURN_NO_AFTER = (0,0)
                         QOR_VMD_RETURN_AFTER = (0,1)
  
*/

#define QOR_VMD_DETAIL_NEW_MODS(allow,...) \
    QOR_VMD_DETAIL_NEW_MODS_IR(allow,QOR_PP_VARIADIC_TO_TUPLE(__VA_ARGS__)) \
/**/

#define QOR_VMD_DETAIL_NEW_MODS_D(d,allow,...) \
    QOR_VMD_DETAIL_NEW_MODS_IR_D(d,allow,QOR_PP_VARIADIC_TO_TUPLE(__VA_ARGS__)) \
/**/

#endif /* QOR_VMD_DETAIL_MODS_H */
