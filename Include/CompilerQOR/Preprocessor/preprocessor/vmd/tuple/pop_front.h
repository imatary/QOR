
//  (C) Copyright Edward Diener 2015
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(QOR_VMD_TUPLE_POP_FRONT_H)
#define QOR_VMD_TUPLE_POP_FRONT_H

#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/setup.h"

#if QOR_PP_VARIADICS

#include "CompilerQOR/Preprocessor/preprocessor/comparison/equal.h"
#include "CompilerQOR/Preprocessor/preprocessor/control/iif.h"
#include "CompilerQOR/Preprocessor/preprocessor/tuple/pop_front.h"
#include "CompilerQOR/Preprocessor/preprocessor/tuple/size.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/empty.h"

/*

  The succeeding comments in this file are in doxygen format.

*/

/** \file
*/

/** \def QOR_VMD_TUPLE_POP_FRONT(tuple)

    \brief pops an element from the front of a tuple. 

    tuple = tuple to pop an element from.

    If the tuple is an empty tuple the result is undefined.
    If the tuple is a single element the result is an empty tuple.
    Otherwise the result is a tuple after removing the first element.
*/

#define QOR_VMD_TUPLE_POP_FRONT(tuple) \
    QOR_PP_IIF \
        ( \
        QOR_PP_EQUAL(QOR_PP_TUPLE_SIZE(tuple),1), \
        QOR_VMD_EMPTY, \
        QOR_PP_TUPLE_POP_FRONT \
        ) \
    (tuple) \
/**/

/** \def QOR_VMD_TUPLE_POP_FRONT_Z(z,tuple)

    \brief pops an element from the front of a tuple. It reenters QOR_PP_REPEAT with maximum efficiency.

    z     = the next available QOR_PP_REPEAT dimension.
    tuple = tuple to pop an element from.

    If the tuple is an empty tuple the result is undefined.
    If the tuple is a single element the result is an empty tuple.
    Otherwise the result is a tuple after removing the first element.
*/

#define QOR_VMD_TUPLE_POP_FRONT_Z(z,tuple) \
    QOR_PP_IIF \
        ( \
        QOR_PP_EQUAL(QOR_PP_TUPLE_SIZE(tuple),1), \
        QOR_VMD_EMPTY, \
        QOR_PP_TUPLE_POP_FRONT_Z \
        ) \
    (z,tuple) \
/**/

#endif /* QOR_PP_VARIADICS */
#endif /* QOR_VMD_TUPLE_POP_FRONT_H */
