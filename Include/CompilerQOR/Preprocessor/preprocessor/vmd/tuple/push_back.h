
//  (C) Copyright Edward Diener 2015
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(QOR_VMD_TUPLE_PUSH_BACK_H)
#define QOR_VMD_TUPLE_PUSH_BACK_H

#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/setup.h"

#if QOR_PP_VARIADICS

#include "CompilerQOR/Preprocessor/preprocessor/control/iif.h"
#include "CompilerQOR/Preprocessor/preprocessor/tuple/push_back.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/identity.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/is_empty.h"

/*

  The succeeding comments in this file are in doxygen format.

*/

/** \file
*/

/** \def QOR_VMD_TUPLE_PUSH_BACK(tuple,elem)

    \brief appends an element to the end of a tuple. 

    tuple = tuple to to append an element to.
    elem  = element to append.

    If the tuple is an empty tuple the result is a tuple with the single element.
    Otherwise the result is a tuple after adding the element to the end.
*/

#define QOR_VMD_TUPLE_PUSH_BACK(tuple,elem) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_VMD_IS_EMPTY(tuple), \
            QOR_VMD_IDENTITY((elem)), \
            QOR_PP_TUPLE_PUSH_BACK \
            ) \
        (tuple,elem) \
        ) \
/**/

#endif /* QOR_PP_VARIADICS */
#endif /* QOR_VMD_TUPLE_PUSH_BACK_H */
