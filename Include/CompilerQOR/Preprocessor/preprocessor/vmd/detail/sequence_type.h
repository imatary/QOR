
//  (C) Copyright Edward Diener 2011-2015
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(QOR_VMD_DETAIL_SEQUENCE_TYPE_H)
#define QOR_VMD_DETAIL_SEQUENCE_TYPE_H

#include "CompilerQOR/Preprocessor/preprocessor/comparison/equal.h"
#include "CompilerQOR/Preprocessor/preprocessor/control/iif.h"
#include "CompilerQOR/Preprocessor/preprocessor/tuple/elem.h"
#include "CompilerQOR/Preprocessor/preprocessor/variadic/elem.h"
#include "CompilerQOR/Preprocessor/preprocessor/variadic/size.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/identity.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/is_empty.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/equal_type.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/is_array_common.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/is_list.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/modifiers.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/mods.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/sequence_elem.h"

#define QOR_VMD_DETAIL_SEQUENCE_TYPE_TUPLE_ARRAY(dtuple) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_IS_ARRAY_SYNTAX(QOR_PP_TUPLE_ELEM(1,dtuple)), \
        QOR_VMD_TYPE_ARRAY, \
        QOR_VMD_TYPE_TUPLE \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_TYPE_TUPLE_ARRAY_D(d,dtuple) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_IS_ARRAY_SYNTAX_D(d,QOR_PP_TUPLE_ELEM(1,dtuple)), \
        QOR_VMD_TYPE_ARRAY, \
        QOR_VMD_TYPE_TUPLE \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_TYPE_TUPLE_LIST(dtuple) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_IS_LIST(QOR_PP_TUPLE_ELEM(1,dtuple)), \
        QOR_VMD_TYPE_LIST, \
        QOR_VMD_TYPE_TUPLE \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_TYPE_TUPLE_LIST_D(d,dtuple) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_IS_LIST_D(d,QOR_PP_TUPLE_ELEM(1,dtuple)), \
        QOR_VMD_TYPE_LIST, \
        QOR_VMD_TYPE_TUPLE \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_TYPE_TUPLE_BOTH(dtuple) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_VMD_DETAIL_EQUAL_TYPE \
                ( \
                QOR_VMD_TYPE_TUPLE, \
                QOR_VMD_DETAIL_SEQUENCE_TYPE_TUPLE_LIST(dtuple) \
                ), \
            QOR_VMD_DETAIL_SEQUENCE_TYPE_TUPLE_ARRAY, \
            QOR_VMD_IDENTITY(QOR_VMD_TYPE_LIST) \
            ) \
        (dtuple) \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_TYPE_TUPLE_BOTH_D(d,dtuple) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_VMD_DETAIL_EQUAL_TYPE_D \
                ( \
                d, \
                QOR_VMD_TYPE_TUPLE, \
                QOR_VMD_DETAIL_SEQUENCE_TYPE_TUPLE_LIST_D(d,dtuple) \
                ), \
            QOR_VMD_DETAIL_SEQUENCE_TYPE_TUPLE_ARRAY_D, \
            QOR_VMD_IDENTITY(QOR_VMD_TYPE_LIST) \
            ) \
        (d,dtuple) \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_TYPE_TUPLE_MODS(dtuple,rtype) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_PP_EQUAL(rtype,QOR_VMD_DETAIL_MODS_RETURN_ARRAY), \
            QOR_VMD_DETAIL_SEQUENCE_TYPE_TUPLE_ARRAY, \
            QOR_PP_IIF \
                ( \
                QOR_PP_EQUAL(rtype,QOR_VMD_DETAIL_MODS_RETURN_LIST), \
                QOR_VMD_DETAIL_SEQUENCE_TYPE_TUPLE_LIST, \
                QOR_PP_IIF \
                    ( \
                    QOR_PP_EQUAL(rtype,QOR_VMD_DETAIL_MODS_RETURN_TUPLE), \
                    QOR_VMD_IDENTITY(QOR_PP_TUPLE_ELEM(0,dtuple)), \
                    QOR_VMD_DETAIL_SEQUENCE_TYPE_TUPLE_BOTH \
                    ) \
                ) \
            ) \
        ) \
    (dtuple) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_TYPE_TUPLE_MODS_D(d,dtuple,rtype) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_PP_EQUAL_D(d,rtype,QOR_VMD_DETAIL_MODS_RETURN_ARRAY), \
            QOR_VMD_DETAIL_SEQUENCE_TYPE_TUPLE_ARRAY_D, \
            QOR_PP_IIF \
                ( \
                QOR_PP_EQUAL_D(d,rtype,QOR_VMD_DETAIL_MODS_RETURN_LIST), \
                QOR_VMD_DETAIL_SEQUENCE_TYPE_TUPLE_LIST_D, \
                QOR_PP_IIF \
                    ( \
                    QOR_PP_EQUAL_D(d,rtype,QOR_VMD_DETAIL_MODS_RETURN_TUPLE), \
                    QOR_VMD_IDENTITY(QOR_PP_TUPLE_ELEM(0,dtuple)), \
                    QOR_VMD_DETAIL_SEQUENCE_TYPE_TUPLE_BOTH_D \
                    ) \
                ) \
            ) \
        ) \
    (d,dtuple) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_TYPE_TUPLE_MORE(dtuple,...) \
    QOR_VMD_DETAIL_SEQUENCE_TYPE_TUPLE_MODS \
        ( \
        dtuple, \
        QOR_VMD_DETAIL_MODS_RESULT_RETURN_TYPE \
            ( \
            QOR_VMD_DETAIL_NEW_MODS(QOR_VMD_ALLOW_ALL,__VA_ARGS__) \
            ) \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_TYPE_TUPLE_MORE_D(d,dtuple,...) \
    QOR_VMD_DETAIL_SEQUENCE_TYPE_TUPLE_MODS_D \
        ( \
        d, \
        dtuple, \
        QOR_VMD_DETAIL_MODS_RESULT_RETURN_TYPE \
            ( \
            QOR_VMD_DETAIL_NEW_MODS_D(d,QOR_VMD_ALLOW_ALL,__VA_ARGS__) \
            ) \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_TYPE_TUPLE_UNARY(dtuple,...) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_VMD_DETAIL_EQUAL_TYPE(QOR_VMD_TYPE_TUPLE,QOR_PP_TUPLE_ELEM(0,dtuple)), \
            QOR_VMD_DETAIL_SEQUENCE_TYPE_TUPLE_MORE, \
            QOR_VMD_IDENTITY(QOR_PP_TUPLE_ELEM(0,dtuple)) \
            ) \
        (dtuple,__VA_ARGS__) \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_TYPE_TUPLE_UNARY_D(d,dtuple,...) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_VMD_DETAIL_EQUAL_TYPE_D(d,QOR_VMD_TYPE_TUPLE,QOR_PP_TUPLE_ELEM(0,dtuple)), \
            QOR_VMD_DETAIL_SEQUENCE_TYPE_TUPLE_MORE_D, \
            QOR_VMD_IDENTITY(QOR_PP_TUPLE_ELEM(0,dtuple)) \
            ) \
        (d,dtuple,__VA_ARGS__) \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_TYPE_TUPLE_SEQUENCE(tuple,...) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_VMD_IS_EMPTY(QOR_PP_TUPLE_ELEM(1,tuple)), \
            QOR_VMD_DETAIL_SEQUENCE_TYPE_TUPLE_UNARY, \
            QOR_VMD_IDENTITY(QOR_VMD_TYPE_SEQUENCE) \
            ) \
        (QOR_PP_TUPLE_ELEM(0,tuple),__VA_ARGS__) \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_TYPE_TUPLE_SEQUENCE_D(d,tuple,...) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_VMD_IS_EMPTY(QOR_PP_TUPLE_ELEM(1,tuple)), \
            QOR_VMD_DETAIL_SEQUENCE_TYPE_TUPLE_UNARY_D, \
            QOR_VMD_IDENTITY(QOR_VMD_TYPE_SEQUENCE) \
            ) \
        (d,QOR_PP_TUPLE_ELEM(0,tuple),__VA_ARGS__) \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_TYPE_TUPLE(tuple,...) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_VMD_IS_EMPTY(QOR_PP_TUPLE_ELEM(0,tuple)), \
            QOR_VMD_IDENTITY(QOR_VMD_TYPE_EMPTY), \
            QOR_VMD_DETAIL_SEQUENCE_TYPE_TUPLE_SEQUENCE \
            ) \
        (tuple,__VA_ARGS__) \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_TYPE_TUPLE_D(d,tuple,...) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_VMD_IS_EMPTY(QOR_PP_TUPLE_ELEM(0,tuple)), \
            QOR_VMD_IDENTITY(QOR_VMD_TYPE_EMPTY), \
            QOR_VMD_DETAIL_SEQUENCE_TYPE_TUPLE_SEQUENCE_D \
            ) \
        (d,tuple,__VA_ARGS__) \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_TYPE(...) \
    QOR_VMD_DETAIL_SEQUENCE_TYPE_TUPLE \
        ( \
        QOR_VMD_DETAIL_SEQUENCE_ELEM \
            ( \
            QOR_VMD_ALLOW_ALL, \
            0, \
            QOR_PP_VARIADIC_ELEM(0,__VA_ARGS__), \
            QOR_VMD_RETURN_AFTER, \
            QOR_VMD_RETURN_TYPE_TUPLE \
            ), \
        __VA_ARGS__ \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_TYPE_D(d,...) \
    QOR_VMD_DETAIL_SEQUENCE_TYPE_TUPLE_D \
        ( \
        d, \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_D \
            ( \
            d, \
            QOR_VMD_ALLOW_ALL, \
            0, \
            QOR_PP_VARIADIC_ELEM(0,__VA_ARGS__), \
            QOR_VMD_RETURN_AFTER, \
            QOR_VMD_RETURN_TYPE_TUPLE \
            ), \
        __VA_ARGS__ \
        ) \
/**/

#endif /* QOR_VMD_DETAIL_SEQUENCE_TYPE_H */
