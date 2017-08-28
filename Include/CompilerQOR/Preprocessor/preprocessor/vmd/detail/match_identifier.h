
//  (C) Copyright Edward Diener 2011-2015
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(QOR_VMD_DETAIL_MATCH_IDENTIFIER_H)
#define QOR_VMD_DETAIL_MATCH_IDENTIFIER_H

#include "CompilerQOR/Preprocessor/preprocessor/arithmetic/inc.h"
#include "CompilerQOR/Preprocessor/preprocessor/cat.h"
#include "CompilerQOR/Preprocessor/preprocessor/comparison/equal.h"
#include "CompilerQOR/Preprocessor/preprocessor/comparison/not_equal.h"
#include "CompilerQOR/Preprocessor/preprocessor/control/iif.h"
#include "CompilerQOR/Preprocessor/preprocessor/control/while.h"
#include "CompilerQOR/Preprocessor/preprocessor/logical/bitand.h"
#include "CompilerQOR/Preprocessor/preprocessor/tuple/elem.h"
#include "CompilerQOR/Preprocessor/preprocessor/tuple/replace.h"
#include "CompilerQOR/Preprocessor/preprocessor/tuple/size.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/is_empty.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/idprefix.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/match_identifier_common.h"

#define QOR_VMD_DETAIL_MATCH_IDENTIFIER_STATE_ID(state) \
    QOR_PP_TUPLE_ELEM(0,state) \
/**/

#define QOR_VMD_DETAIL_MATCH_IDENTIFIER_STATE_KEY_TUPLE(state) \
    QOR_PP_TUPLE_ELEM(1,state) \
/**/

#define QOR_VMD_DETAIL_MATCH_IDENTIFIER_STATE_KEY_TUPLE_SIZE(state) \
    QOR_PP_TUPLE_ELEM(2,state) \
/**/

#define QOR_VMD_DETAIL_MATCH_IDENTIFIER_STATE_KEY_CURRENT(state) \
    QOR_PP_TUPLE_ELEM \
        ( \
        QOR_VMD_DETAIL_MATCH_IDENTIFIER_STATE_INDEX(state), \
        QOR_VMD_DETAIL_MATCH_IDENTIFIER_STATE_KEY_TUPLE(state) \
        ) \
/**/

#define QOR_VMD_DETAIL_MATCH_IDENTIFIER_STATE_INDEX(state) \
    QOR_PP_TUPLE_ELEM(3,state) \
/**/

#define QOR_VMD_DETAIL_MATCH_IDENTIFIER_STATE_RESULT(state) \
    QOR_PP_TUPLE_ELEM(4,state) \
/**/

#define QOR_VMD_DETAIL_MATCH_IDENTIFIER_PRED(d,state) \
    QOR_PP_BITAND \
        ( \
        QOR_PP_EQUAL_D \
            ( \
            d, \
            QOR_VMD_DETAIL_MATCH_IDENTIFIER_STATE_RESULT(state), \
            0 \
            ), \
        QOR_PP_NOT_EQUAL_D \
            ( \
            d, \
            QOR_VMD_DETAIL_MATCH_IDENTIFIER_STATE_INDEX(state), \
            QOR_VMD_DETAIL_MATCH_IDENTIFIER_STATE_KEY_TUPLE_SIZE(state) \
            ) \
        ) \
/**/

#define QOR_VMD_DETAIL_MATCH_IDENTIFIER_OP_FOUND(d,state) \
    QOR_PP_TUPLE_REPLACE_D \
        ( \
        d, \
        state, \
        4, \
        QOR_PP_INC \
            ( \
            QOR_VMD_DETAIL_MATCH_IDENTIFIER_STATE_INDEX(state) \
            ) \
        ) \
/**/

#define QOR_VMD_DETAIL_MATCH_IDENTIFIER_OP_CONTINUE(d,state) \
    QOR_PP_TUPLE_REPLACE_D \
        ( \
        d, \
        state, \
        3, \
        QOR_PP_INC \
            ( \
            QOR_VMD_DETAIL_MATCH_IDENTIFIER_STATE_INDEX(state) \
            ) \
        ) \
/**/

#define QOR_VMD_DETAIL_MATCH_IDENTIFIER_OP(d,state) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_MATCH_IDENTIFIER_OP_CMP_IDS \
            ( \
            QOR_VMD_DETAIL_MATCH_IDENTIFIER_STATE_ID(state), \
            QOR_VMD_DETAIL_MATCH_IDENTIFIER_STATE_KEY_CURRENT(state) \
            ), \
        QOR_VMD_DETAIL_MATCH_IDENTIFIER_OP_FOUND, \
        QOR_VMD_DETAIL_MATCH_IDENTIFIER_OP_CONTINUE \
        ) \
    (d,state) \
/**/

/*

  Return index starting with 1 of the tuple id the identifier matches, or 0 if there are no matches.

*/

#define QOR_VMD_DETAIL_MATCH_IDENTIFIER(id,keytuple) \
    QOR_PP_TUPLE_ELEM \
        ( \
        4, \
        QOR_PP_WHILE \
            ( \
            QOR_VMD_DETAIL_MATCH_IDENTIFIER_PRED, \
            QOR_VMD_DETAIL_MATCH_IDENTIFIER_OP, \
                ( \
                id, \
                keytuple, \
                QOR_PP_TUPLE_SIZE(keytuple), \
                0, \
                0 \
                ) \
            ) \
        ) \
/**/

/*

  Return index starting with 1 of the tuple id the identifier matches, or 0 if there are no matches.

*/

#define QOR_VMD_DETAIL_MATCH_IDENTIFIER_D(d,id,keytuple) \
    QOR_PP_TUPLE_ELEM \
        ( \
        4, \
        QOR_PP_WHILE_ ## d \
            ( \
            QOR_VMD_DETAIL_MATCH_IDENTIFIER_PRED, \
            QOR_VMD_DETAIL_MATCH_IDENTIFIER_OP, \
                ( \
                id, \
                keytuple, \
                QOR_PP_TUPLE_SIZE(keytuple), \
                0, \
                0 \
                ) \
            ) \
        ) \
/**/

#endif /* QOR_VMD_DETAIL_MATCH_IDENTIFIER_H */
