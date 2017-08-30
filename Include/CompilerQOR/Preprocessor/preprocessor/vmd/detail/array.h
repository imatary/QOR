
//  (C) Copyright Edward Diener 2011-2015
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(QOR_VMD_DETAIL_ARRAY_H)
#define QOR_VMD_DETAIL_ARRAY_H

#include "CompilerQOR/Preprocessor/preprocessor/control/expr_iif.h"
#include "CompilerQOR/Preprocessor/preprocessor/control/iif.h"
#include "CompilerQOR/Preprocessor/preprocessor/tuple/elem.h"
#include "CompilerQOR/Preprocessor/preprocessor/variadic/elem.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/empty.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/identity.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/is_empty.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/empty_result.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/is_array_common.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/mods.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/tuple.h"

#define QOR_VMD_DETAIL_ARRAY_CHECK_FOR_ARRAY(tuple) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_VMD_DETAIL_IS_ARRAY_SYNTAX \
                ( \
                QOR_PP_TUPLE_ELEM \
                    ( \
                    0, \
                    tuple \
                    ) \
                ), \
            QOR_VMD_IDENTITY(tuple), \
            QOR_VMD_DETAIL_EMPTY_RESULT \
            ) \
        (tuple)    \
        ) \
/**/

#define QOR_VMD_DETAIL_ARRAY_CHECK_FOR_ARRAY_D(d,tuple) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_VMD_DETAIL_IS_ARRAY_SYNTAX_D \
                ( \
                d, \
                QOR_PP_TUPLE_ELEM \
                    ( \
                    0, \
                    tuple \
                    ) \
                ), \
            QOR_VMD_IDENTITY(tuple), \
            QOR_VMD_DETAIL_EMPTY_RESULT \
            ) \
        (tuple)    \
        ) \
/**/

#define QOR_VMD_DETAIL_ARRAY_PROCESS(tuple) \
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
        QOR_VMD_DETAIL_ARRAY_CHECK_FOR_ARRAY \
        ) \
    (tuple) \
/**/

#define QOR_VMD_DETAIL_ARRAY_PROCESS_D(d,tuple) \
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
        QOR_VMD_DETAIL_ARRAY_CHECK_FOR_ARRAY_D \
        ) \
    (d,tuple) \
/**/

#define QOR_VMD_DETAIL_ARRAY_SPLIT(param) \
    QOR_VMD_DETAIL_ARRAY_PROCESS \
        ( \
        QOR_VMD_DETAIL_TUPLE(param,QOR_VMD_RETURN_AFTER) \
        ) \
/**/

#define QOR_VMD_DETAIL_ARRAY_SPLIT_D(d,param) \
    QOR_VMD_DETAIL_ARRAY_PROCESS_D \
        ( \
        d, \
        QOR_VMD_DETAIL_TUPLE_D(d,param,QOR_VMD_RETURN_AFTER) \
        ) \
/**/

#define QOR_VMD_DETAIL_ARRAY_BEGIN_CHECK_FOR_ARRAY(tuple) \
    QOR_PP_EXPR_IIF \
        ( \
        QOR_VMD_DETAIL_IS_ARRAY_SYNTAX(tuple), \
        tuple \
        ) \
/**/

#define QOR_VMD_DETAIL_ARRAY_BEGIN_CHECK_FOR_ARRAY_D(d,tuple) \
    QOR_PP_EXPR_IIF \
        ( \
        QOR_VMD_DETAIL_IS_ARRAY_SYNTAX_D(d,tuple), \
        tuple \
        ) \
/**/

#define QOR_VMD_DETAIL_ARRAY_BEGIN_TUPLE(tuple) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_IS_EMPTY(tuple), \
        QOR_VMD_EMPTY, \
        QOR_VMD_DETAIL_ARRAY_BEGIN_CHECK_FOR_ARRAY \
        ) \
    (tuple) \
/**/

#define QOR_VMD_DETAIL_ARRAY_BEGIN_TUPLE_D(d,tuple) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_IS_EMPTY(tuple), \
        QOR_VMD_EMPTY, \
        QOR_VMD_DETAIL_ARRAY_BEGIN_CHECK_FOR_ARRAY_D \
        ) \
    (d,tuple) \
/**/

#define QOR_VMD_DETAIL_ARRAY_BEGIN(param) \
    QOR_VMD_DETAIL_ARRAY_BEGIN_TUPLE \
        ( \
        QOR_VMD_DETAIL_TUPLE(param) \
        ) \
/**/

#define QOR_VMD_DETAIL_ARRAY_BEGIN_D(d,param) \
    QOR_VMD_DETAIL_ARRAY_BEGIN_TUPLE_D \
        ( \
        d, \
        QOR_VMD_DETAIL_TUPLE_D(d,param) \
        ) \
/**/

#define QOR_VMD_DETAIL_ARRAY(...) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_MODS_IS_RESULT_AFTER \
            ( \
            QOR_VMD_DETAIL_NEW_MODS(QOR_VMD_ALLOW_AFTER,__VA_ARGS__) \
            ), \
        QOR_VMD_DETAIL_ARRAY_SPLIT, \
        QOR_VMD_DETAIL_ARRAY_BEGIN \
        ) \
    (QOR_PP_VARIADIC_ELEM(0,__VA_ARGS__)) \
/**/

#define QOR_VMD_DETAIL_ARRAY_D(d,...) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_MODS_IS_RESULT_AFTER \
            ( \
            QOR_VMD_DETAIL_NEW_MODS(QOR_VMD_ALLOW_AFTER,__VA_ARGS__) \
            ), \
        QOR_VMD_DETAIL_ARRAY_SPLIT_D, \
        QOR_VMD_DETAIL_ARRAY_BEGIN_D \
        ) \
    (d,QOR_PP_VARIADIC_ELEM(0,__VA_ARGS__)) \
/**/

#endif /* QOR_VMD_DETAIL_ARRAY_H */
