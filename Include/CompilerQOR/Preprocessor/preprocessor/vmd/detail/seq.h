
//  (C) Copyright Edward Diener 2011-2015
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(QOR_VMD_DETAIL_SEQ_H)
#define QOR_VMD_DETAIL_SEQ_H

#include "CompilerQOR/Preprocessor/preprocessor/comparison/equal.h"
#include "CompilerQOR/Preprocessor/preprocessor/control/iif.h"
#include "CompilerQOR/Preprocessor/preprocessor/control/while.h"
#include "CompilerQOR/Preprocessor/preprocessor/facilities/empty.h"
#include "CompilerQOR/Preprocessor/preprocessor/seq/push_back.h"
#include "CompilerQOR/Preprocessor/preprocessor/tuple/elem.h"
#include "CompilerQOR/Preprocessor/preprocessor/tuple/push_back.h"
#include "CompilerQOR/Preprocessor/preprocessor/tuple/size.h"
#include "CompilerQOR/Preprocessor/preprocessor/variadic/elem.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/is_empty.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/empty_result.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/mods.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/not_empty.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/parens.h"

#define QOR_VMD_DETAIL_SEQ_STATE_INIT(seq) \
    QOR_PP_TUPLE_PUSH_BACK \
        ( \
        QOR_PP_TUPLE_PUSH_BACK \
            ( \
            QOR_VMD_DETAIL_PARENS(seq,QOR_VMD_RETURN_AFTER), \
            QOR_PP_EMPTY() \
            ), \
        QOR_PP_EMPTY() \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQ_STATE_INIT_D(d,seq) \
    QOR_PP_TUPLE_PUSH_BACK \
        ( \
        QOR_PP_TUPLE_PUSH_BACK \
            ( \
            QOR_VMD_DETAIL_PARENS_D(d,seq,QOR_VMD_RETURN_AFTER), \
            QOR_PP_EMPTY() \
            ), \
        QOR_PP_EMPTY() \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQ_STATE_PRED(d,state) \
    QOR_VMD_DETAIL_NOT_EMPTY \
        ( \
        QOR_PP_TUPLE_ELEM(0,state) \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQ_STATE_OP_SET_FAILURE(d,state) \
    ( \
    QOR_PP_EMPTY(), \
    QOR_PP_EMPTY(), \
    QOR_PP_TUPLE_ELEM(2,state), \
    QOR_PP_TUPLE_ELEM(3,state) \
    ) \
/**/

#define QOR_VMD_DETAIL_SEQ_STATE_OP_MAKE_SEQ(d,state) \
    QOR_PP_TUPLE_ELEM(0,state) \
/**/

#define QOR_VMD_DETAIL_SEQ_STATE_OP_UPGRADE_SEQ(d,state) \
    QOR_PP_SEQ_PUSH_BACK \
        ( \
        QOR_PP_TUPLE_ELEM(2,state), \
        QOR_PP_TUPLE_ELEM \
            ( \
            0, \
            QOR_PP_TUPLE_ELEM(0,state) \
            ) \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQ_STATE_OP_SET_SUCCESS(d,state) \
    ( \
    QOR_PP_EMPTY(), \
    QOR_PP_EMPTY(), \
    QOR_PP_IIF \
        ( \
        QOR_VMD_IS_EMPTY \
            ( \
              QOR_PP_TUPLE_ELEM(2,state) \
            ), \
        QOR_VMD_DETAIL_SEQ_STATE_OP_MAKE_SEQ, \
        QOR_VMD_DETAIL_SEQ_STATE_OP_UPGRADE_SEQ \
        ) \
    (d,state), \
    QOR_PP_EMPTY() \
    ) \
/**/

#define QOR_VMD_DETAIL_SEQ_STATE_OP_SET_CONTINUE(d,state) \
    QOR_PP_TUPLE_PUSH_BACK \
        ( \
        QOR_PP_TUPLE_PUSH_BACK \
            ( \
            QOR_VMD_DETAIL_PARENS_D(d,QOR_PP_TUPLE_ELEM(1,state),QOR_VMD_RETURN_AFTER), \
            QOR_PP_IIF \
                ( \
                QOR_VMD_IS_EMPTY \
                    ( \
                    QOR_PP_TUPLE_ELEM(2,state) \
                    ), \
                QOR_VMD_DETAIL_SEQ_STATE_OP_MAKE_SEQ, \
                QOR_VMD_DETAIL_SEQ_STATE_OP_UPGRADE_SEQ \
                ) \
            (d,state) \
            ), \
        QOR_PP_TUPLE_ELEM(1,state) \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQ_STATE_OP_CHECK_REST(d,state) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_IS_EMPTY \
            ( \
              QOR_PP_TUPLE_ELEM(1,state) \
            ), \
        QOR_VMD_DETAIL_SEQ_STATE_OP_SET_SUCCESS, \
        QOR_VMD_DETAIL_SEQ_STATE_OP_SET_CONTINUE \
        ) \
    (d,state) \
/**/

#define QOR_VMD_DETAIL_SEQ_STATE_OP(d,state) \
    QOR_PP_IIF \
        ( \
        QOR_PP_EQUAL_D \
            ( \
            d, \
            1, \
            QOR_PP_TUPLE_SIZE \
                ( \
                  QOR_PP_TUPLE_ELEM(0,state) \
                ) \
            ), \
        QOR_VMD_DETAIL_SEQ_STATE_OP_CHECK_REST, \
        QOR_VMD_DETAIL_SEQ_STATE_OP_SET_FAILURE \
        ) \
    (d,state) \
/**/

#define QOR_VMD_DETAIL_SEQ_STATE_RESULT(state) \
    ( \
    QOR_PP_TUPLE_ELEM(2,state), \
    QOR_PP_TUPLE_ELEM(3,state) \
    ) \
/**/

#define QOR_VMD_DETAIL_SEQ_PROCESS(seq) \
    QOR_VMD_DETAIL_SEQ_STATE_RESULT \
      ( \
      QOR_PP_WHILE \
        ( \
        QOR_VMD_DETAIL_SEQ_STATE_PRED, \
        QOR_VMD_DETAIL_SEQ_STATE_OP, \
        QOR_VMD_DETAIL_SEQ_STATE_INIT(seq) \
        ) \
      ) \
/**/

#define QOR_VMD_DETAIL_SEQ_SPLIT(seq) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_IS_EMPTY(seq), \
        QOR_VMD_DETAIL_EMPTY_RESULT, \
        QOR_VMD_DETAIL_SEQ_PROCESS \
        ) \
    (seq) \
/**/

#define QOR_VMD_DETAIL_SEQ_BEGIN(seq) \
    QOR_PP_TUPLE_ELEM(0,QOR_VMD_DETAIL_SEQ_SPLIT(seq)) \
/**/

#define QOR_VMD_DETAIL_SEQ_PROCESS_D(d,seq) \
    QOR_VMD_DETAIL_SEQ_STATE_RESULT \
      ( \
      QOR_PP_WHILE_ ## d \
        ( \
        QOR_VMD_DETAIL_SEQ_STATE_PRED, \
        QOR_VMD_DETAIL_SEQ_STATE_OP, \
        QOR_VMD_DETAIL_SEQ_STATE_INIT_D(d,seq) \
        ) \
      ) \
/**/

#define QOR_VMD_DETAIL_SEQ_SPLIT_D(d,seq) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_IS_EMPTY(seq), \
        QOR_VMD_DETAIL_EMPTY_RESULT, \
        QOR_VMD_DETAIL_SEQ_PROCESS_D \
        ) \
    (d,seq) \
/**/

#define QOR_VMD_DETAIL_SEQ_BEGIN_D(d,seq) \
    QOR_PP_TUPLE_ELEM(0,QOR_VMD_DETAIL_SEQ_SPLIT_D(d,seq)) \
/**/

#define QOR_VMD_DETAIL_SEQ_D(d,...) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_MODS_IS_RESULT_AFTER \
            ( \
            QOR_VMD_DETAIL_NEW_MODS_D(d,QOR_VMD_ALLOW_AFTER,__VA_ARGS__) \
            ), \
        QOR_VMD_DETAIL_SEQ_SPLIT_D, \
        QOR_VMD_DETAIL_SEQ_BEGIN_D \
        ) \
    (d,QOR_PP_VARIADIC_ELEM(0,__VA_ARGS__)) \
/**/

#define QOR_VMD_DETAIL_SEQ(...) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_MODS_IS_RESULT_AFTER \
            ( \
            QOR_VMD_DETAIL_NEW_MODS(QOR_VMD_ALLOW_AFTER,__VA_ARGS__) \
            ), \
        QOR_VMD_DETAIL_SEQ_SPLIT, \
        QOR_VMD_DETAIL_SEQ_BEGIN \
        ) \
    (QOR_PP_VARIADIC_ELEM(0,__VA_ARGS__)) \
/**/

#endif /* QOR_VMD_DETAIL_SEQ_H */
