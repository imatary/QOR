
//  (C) Copyright Edward Diener 2011-2015
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(QOR_VMD_DETAIL_SEQUENCE_ARITY_H)
#define QOR_VMD_DETAIL_SEQUENCE_ARITY_H

#include "CompilerQOR/Preprocessor/preprocessor/logical/bitand.h"
#include "CompilerQOR/Preprocessor/preprocessor/logical/bitnor.h"
#include "CompilerQOR/Preprocessor/preprocessor/tuple/elem.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/is_empty.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/modifiers.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/not_empty.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/sequence_elem.h"

#define QOR_VMD_DETAIL_IS_MULTI_TUPLE(tuple) \
    QOR_PP_BITNOR \
        ( \
        QOR_VMD_IS_EMPTY(QOR_PP_TUPLE_ELEM(0,tuple)), \
        QOR_VMD_IS_EMPTY(QOR_PP_TUPLE_ELEM(1,tuple)) \
        ) \
/**/

#define QOR_VMD_DETAIL_IS_UNARY_TUPLE(tuple) \
    QOR_PP_BITAND \
        ( \
        QOR_VMD_DETAIL_NOT_EMPTY(QOR_PP_TUPLE_ELEM(0,tuple)), \
        QOR_VMD_IS_EMPTY(QOR_PP_TUPLE_ELEM(1,tuple)) \
        ) \
/**/

// UNARY

#define QOR_VMD_DETAIL_IS_UNARY(vseq) \
    QOR_VMD_DETAIL_IS_UNARY_TUPLE \
        ( \
        QOR_VMD_DETAIL_SEQUENCE_ELEM(QOR_VMD_ALLOW_AFTER,0,vseq,QOR_VMD_RETURN_AFTER) \
        ) \
/**/

#define QOR_VMD_DETAIL_IS_UNARY_D(d,vseq) \
    QOR_VMD_DETAIL_IS_UNARY_TUPLE \
        ( \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_D(d,QOR_VMD_ALLOW_AFTER,0,vseq,QOR_VMD_RETURN_AFTER) \
        ) \
/**/

// MULTI

#define QOR_VMD_DETAIL_IS_MULTI(vseq) \
    QOR_VMD_DETAIL_IS_MULTI_TUPLE \
        ( \
        QOR_VMD_DETAIL_SEQUENCE_ELEM(QOR_VMD_ALLOW_AFTER,0,vseq,QOR_VMD_RETURN_AFTER) \
        ) \
/**/

#define QOR_VMD_DETAIL_IS_MULTI_D(d,vseq) \
    QOR_VMD_DETAIL_IS_MULTI_TUPLE \
        ( \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_D(d,QOR_VMD_ALLOW_AFTER,0,vseq,QOR_VMD_RETURN_AFTER) \
        ) \
/**/

#endif /* QOR_VMD_DETAIL_SEQUENCE_ARITY_H */
