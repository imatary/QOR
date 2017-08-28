
//  (C) Copyright Edward Diener 2015
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(QOR_VMD_TUPLE_PUSH_FRONT_H)
#define QOR_VMD_TUPLE_PUSH_FRONT_H

#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/setup.h"

#if QOR_PP_VARIADICS

#include "CompilerQOR/Preprocessor/preprocessor/control/iif.h"
#include "CompilerQOR/Preprocessor/preprocessor/tuple/push_front.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/identity.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/is_empty.h"

/*

  The succeeding comments in this file are in doxygen format.

*/

/** \file
*/

/** \def QOR_VMD_TUPLE_PUSH_FRONT(tuple,elem)

    \brief inserts an element at the beginning of a tuple. 

    tuple = tuple to insert an element at.
    elem  = element to insert.

    If the tuple is an empty tuple the result is a tuple with the single element.
    Otherwise the result is a tuple after inserting the element at the beginning.
*/

#define QOR_VMD_TUPLE_PUSH_FRONT(tuple,elem) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_VMD_IS_EMPTY(tuple), \
            QOR_VMD_IDENTITY((elem)), \
            QOR_PP_TUPLE_PUSH_FRONT \
            ) \
        (tuple,elem) \
        ) \
/**/

#endif /* QOR_PP_VARIADICS */
#endif /* QOR_VMD_TUPLE_PUSH_FRONT_H */
