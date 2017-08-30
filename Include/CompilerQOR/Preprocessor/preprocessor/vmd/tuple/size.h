
//  (C) Copyright Edward Diener 2015
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(QOR_VMD_TUPLE_SIZE_H)
#define QOR_VMD_TUPLE_SIZE_H

#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/setup.h"

#if QOR_PP_VARIADICS

#include "CompilerQOR/Preprocessor/preprocessor/control/iif.h"
#include "CompilerQOR/Preprocessor/preprocessor/tuple/size.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/identity.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/is_empty.h"

/*

  The succeeding comments in this file are in doxygen format.

*/

/** \file
*/

/** \def QOR_VMD_TUPLE_SIZE(tuple)

    \brief  expands to the size of the tuple passed to it. 

    tuple = tuple whose size is to be extracted. 
    
    If the tuple is an empty tuple its size is 0.
    Otherwise the result is the number of elements in the tuple.
*/

#define QOR_VMD_TUPLE_SIZE(tuple) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_VMD_IS_EMPTY(tuple), \
            QOR_VMD_IDENTITY(0), \
            QOR_PP_TUPLE_SIZE \
            ) \
        (tuple) \
        ) \
/**/

#endif /* QOR_PP_VARIADICS */
#endif /* QOR_VMD_TUPLE_SIZE_H */
