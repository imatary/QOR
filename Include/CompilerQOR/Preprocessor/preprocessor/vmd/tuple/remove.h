
//  (C) Copyright Edward Diener 2015
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(QOR_VMD_TUPLE_REMOVE_H)
#define QOR_VMD_TUPLE_REMOVE_H

#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/setup.h"

#if QOR_PP_VARIADICS

#include "CompilerQOR/Preprocessor/preprocessor/comparison/equal.h"
#include "CompilerQOR/Preprocessor/preprocessor/control/iif.h"
#include "CompilerQOR/Preprocessor/preprocessor/logical/bitand.h"
#include "CompilerQOR/Preprocessor/preprocessor/tuple/remove.h"
#include "CompilerQOR/Preprocessor/preprocessor/tuple/size.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/empty.h"

/*

  The succeeding comments in this file are in doxygen format.

*/

/** \file
*/

/** \def QOR_VMD_TUPLE_REMOVE(tuple,index)

    \brief removes an element from a tuple.

    tuple = tuple from which an element is to be removed.
    index = The zero-based position in tuple of the element to be removed.

    If index is greater or equal to the tuple size the result is undefined.
    If the tuple is a single element and the index is 0 the result is an empty tuple.
    Otherwise the result is a tuple after removing the index element.
*/

#define QOR_VMD_TUPLE_REMOVE(tuple,index) \
    QOR_PP_IIF \
        ( \
        QOR_PP_BITAND \
            ( \
            QOR_PP_EQUAL(index,0), \
            QOR_PP_EQUAL(QOR_PP_TUPLE_SIZE(tuple),1) \
            ), \
        QOR_VMD_EMPTY, \
        QOR_PP_TUPLE_REMOVE \
        ) \
    (tuple,index) \
/**/

/** \def QOR_VMD_TUPLE_REMOVE_D(d,tuple,index)

    \brief removes an element from a tuple. It reenters QOR_PP_WHILE with maximum efficiency.

    d     = The next available QOR_PP_WHILE iteration. 
    tuple = tuple from which an element is to be removed.
    index = The zero-based position in tuple of the element to be removed.

    If index is greater or equal to the tuple size the result is undefined.
    If the tuple is a single element and the index is 0 the result is an empty tuple.
    Otherwise the result is a tuple after removing the index element.
*/

#define QOR_VMD_TUPLE_REMOVE_D(d,tuple,index) \
    QOR_PP_IIF \
        ( \
        QOR_PP_BITAND \
            ( \
            QOR_PP_EQUAL_D(d,index,0), \
            QOR_PP_EQUAL_D(d,QOR_PP_TUPLE_SIZE(tuple),1) \
            ), \
        QOR_VMD_EMPTY, \
        QOR_PP_TUPLE_REMOVE_D \
        ) \
    (d,tuple,index) \
/**/

#endif /* QOR_PP_VARIADICS */
#endif /* QOR_VMD_TUPLE_REMOVE_H */
