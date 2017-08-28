
//  (C) Copyright Edward Diener 2015
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(QOR_VMD_LIST_TO_TUPLE_H)
#define QOR_VMD_LIST_TO_TUPLE_H

#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/setup.h"

#if QOR_PP_VARIADICS

#include "CompilerQOR/Preprocessor/preprocessor/control/iif.h"
#include "CompilerQOR/Preprocessor/preprocessor/list/to_tuple.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/empty.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/is_empty_list.h"

/*

  The succeeding comments in this file are in doxygen format.

*/

/** \file
*/

/** \def QOR_VMD_LIST_TO_TUPLE(list)

    \brief converts a list to a tuple.

    list = list to be converted.
    
    If the list is an empty list (QOR_PP_NIL) it is converted to an empty tuple.
    Otherwise the list is converted to a tuple with the same number of elements as the list.
*/

#define QOR_VMD_LIST_TO_TUPLE(list) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_IS_EMPTY_LIST(list), \
        QOR_VMD_EMPTY, \
        QOR_PP_LIST_TO_TUPLE \
        ) \
    (list) \
/**/

#endif /* QOR_PP_VARIADICS */
#endif /* QOR_VMD_LIST_TO_TUPLE_H */
