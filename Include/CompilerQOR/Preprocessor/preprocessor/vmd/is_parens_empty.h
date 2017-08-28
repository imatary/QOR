
//  (C) Copyright Edward Diener 2011-2015
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(QOR_VMD_IS_PARENS_EMPTY_H)
#define QOR_VMD_IS_PARENS_EMPTY_H

#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/setup.h"

#if QOR_PP_VARIADICS

#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/is_empty_tuple.h"

/*

  The succeeding comments in this file are in doxygen format.

*/

/** \file
*/

/** \def QOR_VMD_IS_PARENS_EMPTY(sequence)

    \brief Determines if the sequence is a set of parens with no data.

    sequence = a VMD sequence

    returns = 1 if the sequence is a set of parens with no data,
              else returns 0.
              
    A set of parens with no data may be:
    
    1) a tuple whose size is a single element which is empty
    
                or
                
    2) a single element seq whose data is empty
    
*/

#define QOR_VMD_IS_PARENS_EMPTY(sequence) \
    QOR_VMD_DETAIL_IS_EMPTY_TUPLE(sequence) \
/**/

/** \def QOR_VMD_IS_PARENS_EMPTY_D(d,sequence)

    \brief Determines if the sequence is a set of parens with no data. Re-entrant version.

    d        = The next available QOR_PP_WHILE iteration.
    sequence = a VMD sequence

    returns = 1 if the sequence is a set of parens with no data,
              else returns 0.
              
    A set of parens with no data may be:
    
    1) a tuple whose size is a single element which is empty
    
                or
                
    2) a single element seq whose data is empty
    
*/

#define QOR_VMD_IS_PARENS_EMPTY_D(d,sequence) \
    QOR_VMD_DETAIL_IS_EMPTY_TUPLE_D(d,sequence) \
/**/

#endif /* QOR_PP_VARIADICS */
#endif /* QOR_VMD_IS_PARENS_EMPTY_H */
