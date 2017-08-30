
//  (C) Copyright Edward Diener 2011-2015
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(QOR_VMD_DETAIL_LIST_H)
#define QOR_VMD_DETAIL_LIST_H

#include "CompilerQOR/Preprocessor/preprocessor/control/iif.h"
#include "CompilerQOR/Preprocessor/preprocessor/punctuation/is_begin_parens.h"
#include "CompilerQOR/Preprocessor/preprocessor/tuple/elem.h"
#include "CompilerQOR/Preprocessor/preprocessor/tuple/pop_back.h"
#include "CompilerQOR/Preprocessor/preprocessor/variadic/elem.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/is_empty.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/empty_result.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/identifier.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/is_list.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/mods.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/parens.h"

#define QOR_VMD_DETAIL_LIST_CHECK_FOR_LIST(tuple) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_IS_LIST \
            ( \
            QOR_PP_TUPLE_ELEM \
                ( \
                0, \
                tuple \
                ) \
            ), \
        tuple, \
        (,) \
        ) \
/**/

#define QOR_VMD_DETAIL_LIST_CHECK_FOR_LIST_D(d,tuple) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_IS_LIST_D \
            ( \
            d, \
            QOR_PP_TUPLE_ELEM \
                ( \
                0, \
                tuple \
                ) \
            ), \
        tuple, \
        (,) \
        ) \
/**/

#define QOR_VMD_DETAIL_LIST_CHECK_RETURN(tuple) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_IS_EMPTY \
            ( \
            QOR_PP_TUPLE_ELEM \
                ( \
                0, \
                tuple \
                ) \
            ), \
        QOR_VMD_DETAIL_EMPTY_RESULT, \
        QOR_VMD_DETAIL_LIST_CHECK_FOR_LIST \
        ) \
    (tuple) \
/**/

#define QOR_VMD_DETAIL_LIST_CHECK_RETURN_D(d,tuple) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_IS_EMPTY \
            ( \
            QOR_PP_TUPLE_ELEM \
                ( \
                0, \
                tuple \
                ) \
            ), \
        QOR_VMD_DETAIL_EMPTY_RESULT, \
        QOR_VMD_DETAIL_LIST_CHECK_FOR_LIST_D \
        ) \
    (d,tuple) \
/**/

#define QOR_VMD_DETAIL_LIST_EMPTY_LIST(list) \
    QOR_VMD_DETAIL_IDENTIFIER(list,QOR_PP_NIL,QOR_VMD_RETURN_AFTER,QOR_VMD_RETURN_INDEX) \
/**/

#define QOR_VMD_DETAIL_LIST_EMPTY_LIST_D(d,list) \
    QOR_VMD_DETAIL_IDENTIFIER_D(d,list,QOR_PP_NIL,QOR_VMD_RETURN_AFTER,QOR_VMD_RETURN_INDEX) \
/**/

#define QOR_VMD_DETAIL_LIST_TUPLE(param) \
    QOR_VMD_DETAIL_LIST_CHECK_RETURN \
        ( \
        QOR_VMD_DETAIL_PARENS(param,QOR_VMD_RETURN_AFTER) \
        ) \
/**/

#define QOR_VMD_DETAIL_LIST_TUPLE_D(d,param) \
    QOR_VMD_DETAIL_LIST_CHECK_RETURN_D \
        ( \
        d, \
        QOR_VMD_DETAIL_PARENS_D(d,param,QOR_VMD_RETURN_AFTER) \
        ) \
/**/

#define QOR_VMD_DETAIL_LIST_EMPTY_PROCESS(tuple) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_IS_EMPTY \
            ( \
            QOR_PP_TUPLE_ELEM(0,tuple) \
            ), \
        (,), \
        tuple \
        ) \
/**/

#define QOR_VMD_DETAIL_LIST_EMPTY(list) \
    QOR_VMD_DETAIL_LIST_EMPTY_PROCESS \
        ( \
        QOR_VMD_DETAIL_LIST_EMPTY_LIST(list) \
        ) \
/**/

#define QOR_VMD_DETAIL_LIST_EMPTY_D(d,list) \
    QOR_VMD_DETAIL_LIST_EMPTY_PROCESS \
        ( \
        QOR_VMD_DETAIL_LIST_EMPTY_LIST_D(d,list) \
        ) \
/**/

#define QOR_VMD_DETAIL_LIST_PROCESS(list) \
    QOR_PP_IIF \
        ( \
        QOR_PP_IS_BEGIN_PARENS(list), \
        QOR_VMD_DETAIL_LIST_TUPLE, \
        QOR_VMD_DETAIL_LIST_EMPTY \
        ) \
    (list) \
/**/

#define QOR_VMD_DETAIL_LIST_SPLIT(list) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_IS_EMPTY(list), \
        QOR_VMD_DETAIL_EMPTY_RESULT, \
        QOR_VMD_DETAIL_LIST_PROCESS \
        ) \
    (list) \
/**/

#define QOR_VMD_DETAIL_LIST_BEGIN(list) \
    QOR_PP_TUPLE_ELEM(0,QOR_VMD_DETAIL_LIST_SPLIT(list)) \
/**/

#define QOR_VMD_DETAIL_LIST_PROCESS_D(d,list) \
    QOR_PP_IIF \
        ( \
        QOR_PP_IS_BEGIN_PARENS(list), \
        QOR_VMD_DETAIL_LIST_TUPLE_D, \
        QOR_VMD_DETAIL_LIST_EMPTY_D \
        ) \
    (d,list) \
/**/

#define QOR_VMD_DETAIL_LIST_SPLIT_D(d,list) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_IS_EMPTY(list), \
        QOR_VMD_DETAIL_EMPTY_RESULT, \
        QOR_VMD_DETAIL_LIST_PROCESS_D \
        ) \
    (d,list) \
/**/

#define QOR_VMD_DETAIL_LIST_BEGIN_D(d,list) \
    QOR_PP_TUPLE_ELEM(0,QOR_VMD_DETAIL_LIST_SPLIT_D(d,list)) \
/**/

#define QOR_VMD_DETAIL_LIST_D(d,...) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_MODS_IS_RESULT_AFTER \
            ( \
            QOR_VMD_DETAIL_NEW_MODS_D(d,QOR_VMD_ALLOW_AFTER,__VA_ARGS__) \
            ), \
        QOR_VMD_DETAIL_LIST_SPLIT_D, \
        QOR_VMD_DETAIL_LIST_BEGIN_D \
        ) \
    (d,QOR_PP_VARIADIC_ELEM(0,__VA_ARGS__)) \
/**/

#define QOR_VMD_DETAIL_LIST(...) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_MODS_IS_RESULT_AFTER \
            ( \
            QOR_VMD_DETAIL_NEW_MODS(QOR_VMD_ALLOW_AFTER,__VA_ARGS__) \
            ), \
        QOR_VMD_DETAIL_LIST_SPLIT, \
        QOR_VMD_DETAIL_LIST_BEGIN \
        ) \
    (QOR_PP_VARIADIC_ELEM(0,__VA_ARGS__)) \
/**/

#endif /* QOR_VMD_DETAIL_LIST_H */
