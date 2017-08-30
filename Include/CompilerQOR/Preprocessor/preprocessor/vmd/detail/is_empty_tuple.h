
//  (C) Copyright Edward Diener 2011-2015
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(QOR_VMD_DETAIL_IS_EMPTY_TUPLE_H)
#define QOR_VMD_DETAIL_IS_EMPTY_TUPLE_H

#include "CompilerQOR/Preprocessor/preprocessor/comparison/equal.h"
#include "CompilerQOR/Preprocessor/preprocessor/control/iif.h"
#include "CompilerQOR/Preprocessor/preprocessor/tuple/elem.h"
#include "CompilerQOR/Preprocessor/preprocessor/tuple/size.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/identity.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/is_empty.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/is_tuple.h"

#define QOR_VMD_DETAIL_IS_EMPTY_TUPLE_CEM(tuple) \
    QOR_VMD_IS_EMPTY(QOR_PP_TUPLE_ELEM(0,tuple)) \
/**/

#define QOR_VMD_DETAIL_IS_EMPTY_TUPLE_SIZE(tuple) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_PP_EQUAL(QOR_PP_TUPLE_SIZE(tuple),1), \
            QOR_VMD_DETAIL_IS_EMPTY_TUPLE_CEM, \
            QOR_VMD_IDENTITY(0) \
            ) \
        (tuple) \
        ) \
/**/

#define QOR_VMD_DETAIL_IS_EMPTY_TUPLE_SIZE_D(d,tuple) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_PP_EQUAL_D(d,QOR_PP_TUPLE_SIZE(tuple),1), \
            QOR_VMD_DETAIL_IS_EMPTY_TUPLE_CEM, \
            QOR_VMD_IDENTITY(0) \
            ) \
        (tuple) \
        ) \
/**/

#define QOR_VMD_DETAIL_IS_EMPTY_TUPLE(tuple) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_VMD_IS_TUPLE(tuple), \
            QOR_VMD_DETAIL_IS_EMPTY_TUPLE_SIZE, \
            QOR_VMD_IDENTITY(0) \
            ) \
        (tuple) \
        ) \
/**/

#define QOR_VMD_DETAIL_IS_EMPTY_TUPLE_D(d,tuple) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_VMD_IS_TUPLE(tuple), \
            QOR_VMD_DETAIL_IS_EMPTY_TUPLE_SIZE_D, \
            QOR_VMD_IDENTITY(0) \
            ) \
        (d,tuple) \
        ) \
/**/

#endif /* QOR_VMD_DETAIL_IS_EMPTY_TUPLE_H */
