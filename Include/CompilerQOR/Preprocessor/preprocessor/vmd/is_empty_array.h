
//  (C) Copyright Edward Diener 2011-2015
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(QOR_VMD_IS_EMPTY_ARRAY_H)
#define QOR_VMD_IS_EMPTY_ARRAY_H

#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/setup.h"

#if QOR_PP_VARIADICS

#include "CompilerQOR/Preprocessor/preprocessor/control/iif.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/is_array.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/identity.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/is_empty_array.h"

/*

  The succeeding comments in this file are in doxygen format.

*/

/** \file
*/

/** \def QOR_VMD_IS_EMPTY_ARRAY(sequence)

    \brief Tests whether a sequence is an empty Boost PP array.

    An empty Boost PP array is a two element tuple where the first
    size element is 0 and the second element is a tuple with a single 
    empty element, ie. '(0,())'.
    
    sequence = a possible empty array

    returns = 1 if the sequence is an empty Boost PP array
              0 if it is not.
              
    The macro will generate a preprocessing error if the sequence
    is in the form of an array but its first tuple element, instead
    of being a number, is a preprocessor token which VMD cannot parse,
    as in the example '(&0,())' which is a valid tuple but an invalid
    array.
    
*/

#define QOR_VMD_IS_EMPTY_ARRAY(sequence) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_VMD_IS_ARRAY(sequence), \
            QOR_VMD_DETAIL_IS_EMPTY_ARRAY_SIZE, \
            QOR_VMD_IDENTITY(0) \
            ) \
        (sequence) \
        ) \
/**/

/** \def QOR_VMD_IS_EMPTY_ARRAY_D(d,sequence)

    \brief Tests whether a sequence is an empty Boost PP array. Re-entrant version.

    An empty Boost PP array is a two element tuple where the first
    size element is 0 and the second element is a tuple with a single 
    empty element, ie. '(0,())'.
    
    d        = The next available QOR_PP_WHILE iteration. 
    sequence = a possible empty array

    returns = 1 if the sequence is an empty Boost PP array
              0 if it is not.
              
    The macro will generate a preprocessing error if the sequence
    is in the form of an array but its first tuple element, instead
    of being a number, is a preprocessor token which VMD cannot parse,
    as in the example '(&0,())' which is a valid tuple but an invalid
    array.
    
*/

#define QOR_VMD_IS_EMPTY_ARRAY_D(d,sequence) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_VMD_IS_ARRAY_D(d,sequence), \
            QOR_VMD_DETAIL_IS_EMPTY_ARRAY_SIZE, \
            QOR_VMD_IDENTITY(0) \
            ) \
        (sequence) \
        ) \
/**/

#endif /* QOR_PP_VARIADICS */
#endif /* QOR_VMD_IS_EMPTY_ARRAY_H */
