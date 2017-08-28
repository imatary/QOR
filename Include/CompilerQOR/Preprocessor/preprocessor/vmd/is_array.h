
//  (C) Copyright Edward Diener 2011-2015
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(QOR_VMD_IS_ARRAY_H)
#define QOR_VMD_IS_ARRAY_H

#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/setup.h"

#if QOR_PP_VARIADICS

#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/is_array.h"

/*

  The succeeding comments in this file are in doxygen format.

*/

/** \file
*/

/** \def QOR_VMD_IS_ARRAY(sequence)

    \brief Determines if a sequence is a Boost PP array.

    The macro checks that the sequence is a Boost PP array.
    It returns 1 if it is an array, else if returns 0.

    sequence = a possible Boost PP array.

    returns  = 1 if it is an array, else returns 0.
    
    The macro will generate a preprocessing error if the input
    is in the form of an array but its first tuple element, instead
    of being a number, is a preprocessor token which VMD cannot parse,
    as in the example '(&2,(0,1))' which is a valid tuple but an invalid
    array.
    
*/

#define QOR_VMD_IS_ARRAY(sequence) \
    QOR_VMD_DETAIL_IS_ARRAY(sequence) \
/**/

/** \def QOR_VMD_IS_ARRAY_D(d,sequence)

    \brief Determines if a sequence is a Boost PP array. Re-entrant version.

    The macro checks that the sequence is a Boost PP array.
    It returns 1 if it is an array, else if returns 0.

    d        = The next available QOR_PP_WHILE iteration. 
    sequence = a possible Boost PP array.

    returns = 1 if it is an array, else returns 0.
    
    The macro will generate a preprocessing error if the input
    is in the form of an array but its first tuple element, instead
    of being a number, is a preprocessor token which VMD cannot parse,
    as in the example '(&2,(0,1))' which is a valid tuple but an invalid
    array.
    
*/

#define QOR_VMD_IS_ARRAY_D(d,sequence) \
    QOR_VMD_DETAIL_IS_ARRAY_D(d,sequence) \
/**/

#endif /* QOR_PP_VARIADICS */
#endif /* QOR_VMD_IS_ARRAY_H */
