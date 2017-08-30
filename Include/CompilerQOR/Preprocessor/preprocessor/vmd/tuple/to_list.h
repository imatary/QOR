
//  (C) Copyright Edward Diener 2015
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(QOR_VMD_TUPLE_TO_LIST_H)
#define QOR_VMD_TUPLE_TO_LIST_H

#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/setup.h"

#if QOR_PP_VARIADICS

#include "CompilerQOR/Preprocessor/preprocessor/control/iif.h"
#include "CompilerQOR/Preprocessor/preprocessor/tuple/to_list.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/identity.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/is_empty.h"

/*

  The succeeding comments in this file are in doxygen format.

*/

/** \file
*/

/** \def QOR_VMD_TUPLE_TO_LIST(tuple)

    \brief converts a tuple to a list.

    tuple = tuple to be converted.
    
    If the tuple is an empty tuple it is converted to an empty list (QOR_PP_NIL).
    Otherwise the tuple is converted to a list with the same number of elements as the tuple.
*/

#define QOR_VMD_TUPLE_TO_LIST(tuple) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_VMD_IS_EMPTY(tuple), \
            QOR_VMD_IDENTITY(QOR_PP_NIL), \
            QOR_PP_TUPLE_TO_LIST \
            ) \
        (tuple) \
        ) \
/**/

#endif /* QOR_PP_VARIADICS */
#endif /* QOR_VMD_TUPLE_TO_LIST_H */
