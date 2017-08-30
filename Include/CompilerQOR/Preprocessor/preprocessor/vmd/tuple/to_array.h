
//  (C) Copyright Edward Diener 2015
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(QOR_VMD_TUPLE_TO_ARRAY_H)
#define QOR_VMD_TUPLE_TO_ARRAY_H

#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/setup.h"

#if QOR_PP_VARIADICS

#include "CompilerQOR/Preprocessor/preprocessor/control/iif.h"
#include "CompilerQOR/Preprocessor/preprocessor/tuple/to_array.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/identity.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/is_empty.h"

/*

  The succeeding comments in this file are in doxygen format.

*/

/** \file
*/

/** \def QOR_VMD_TUPLE_TO_ARRAY(tuple)

    \brief converts a tuple to an array.

    tuple = tuple to be converted.
    
    If the tuple is an empty tuple it is converted to an array with 0 elements.
    Otherwise the tuple is converted to an array with the same number of elements as the tuple.
*/

#define QOR_VMD_TUPLE_TO_ARRAY(tuple) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_VMD_IS_EMPTY(tuple), \
            QOR_VMD_IDENTITY((0,())), \
            QOR_PP_TUPLE_TO_ARRAY \
            ) \
        (tuple) \
        ) \
/**/

#endif /* QOR_PP_VARIADICS */
#endif /* QOR_VMD_TUPLE_TO_ARRAY_H */
