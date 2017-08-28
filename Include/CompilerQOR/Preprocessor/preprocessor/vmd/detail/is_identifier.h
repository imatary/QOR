
//  (C) Copyright Edward Diener 2011-2015
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(QOR_VMD_DETAIL_IS_IDENTIFIER_H)
#define QOR_VMD_DETAIL_IS_IDENTIFIER_H

#include "CompilerQOR/Preprocessor/preprocessor/comparison/equal.h"
#include "CompilerQOR/Preprocessor/preprocessor/control/iif.h"
#include "CompilerQOR/Preprocessor/preprocessor/logical/bitor.h"
#include "CompilerQOR/Preprocessor/preprocessor/punctuation/is_begin_parens.h"
#include "CompilerQOR/Preprocessor/preprocessor/tuple/elem.h"
#include "CompilerQOR/Preprocessor/preprocessor/variadic/size.h"
#include "CompilerQOR/Preprocessor/preprocessor/variadic/elem.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/identity.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/is_empty.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/is_tuple.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/identifier.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/identifier_concat.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/not_empty.h"

#define QOR_VMD_DETAIL_IS_IDENTIFIER_VSEQ_MATCH(tup) \
    QOR_VMD_DETAIL_NOT_EMPTY \
        ( \
        QOR_PP_TUPLE_ELEM(0,tup) \
        ) \
/**/

#define QOR_VMD_DETAIL_IS_IDENTIFIER_VSEQ_TUPLE(ptup) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_VMD_IS_TUPLE(ptup), \
            QOR_VMD_DETAIL_IS_IDENTIFIER_VSEQ_MATCH, \
            QOR_VMD_IDENTITY(0) \
            ) \
        (ptup) \
        ) \
/**/

#define QOR_VMD_DETAIL_IS_IDENTIFIER_VSEQ_ID(vseq) \
    QOR_VMD_DETAIL_IS_IDENTIFIER_VSEQ_TUPLE \
        ( \
        QOR_VMD_DETAIL_IDENTIFIER_CONCATENATE(vseq) \
        ) \
/**/

#define QOR_VMD_DETAIL_IS_IDENTIFIER_VSEQ(vseq) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
          ( \
          QOR_PP_BITOR \
            ( \
            QOR_VMD_IS_EMPTY(vseq), \
            QOR_PP_IS_BEGIN_PARENS(vseq) \
            ), \
          QOR_VMD_IDENTITY(0), \
          QOR_VMD_DETAIL_IS_IDENTIFIER_VSEQ_ID \
          ) \
        (vseq) \
        ) \
/**/

#define QOR_VMD_DETAIL_IS_IDENTIFIER_SINGLE(...) \
    QOR_VMD_DETAIL_IS_IDENTIFIER_VSEQ(QOR_PP_VARIADIC_ELEM(0,__VA_ARGS__)) \
/**/

#define QOR_VMD_DETAIL_IS_IDENTIFIER_SINGLE_D(d,...) \
    QOR_VMD_DETAIL_IS_IDENTIFIER_VSEQ(QOR_PP_VARIADIC_ELEM(0,__VA_ARGS__)) \
/**/

#define QOR_VMD_DETAIL_IS_IDENTIFIER(...) \
    QOR_PP_IIF \
        ( \
        QOR_PP_EQUAL(QOR_PP_VARIADIC_SIZE(__VA_ARGS__),1), \
        QOR_VMD_DETAIL_IS_IDENTIFIER_SINGLE, \
        QOR_VMD_DETAIL_IS_IDENTIFIER_MULTIPLE \
        ) \
    (__VA_ARGS__) \
/**/

#define QOR_VMD_DETAIL_IS_IDENTIFIER_D(d,...) \
    QOR_PP_IIF \
        ( \
        QOR_PP_EQUAL_D(d,QOR_PP_VARIADIC_SIZE(__VA_ARGS__),1), \
        QOR_VMD_DETAIL_IS_IDENTIFIER_SINGLE_D, \
        QOR_VMD_DETAIL_IS_IDENTIFIER_MULTIPLE_D \
        ) \
    (d,__VA_ARGS__) \
/**/

#endif /* QOR_VMD_DETAIL_IS_IDENTIFIER_H */
