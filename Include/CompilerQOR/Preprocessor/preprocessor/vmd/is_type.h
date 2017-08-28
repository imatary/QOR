
//  (C) Copyright Edward Diener 2011-2015
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(QOR_VMD_IS_TYPE_H)
#define QOR_VMD_IS_TYPE_H

#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/setup.h"

#if QOR_PP_VARIADICS

#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/is_type.h"

/*

  The succeeding comments in this file are in doxygen format.

*/

/** \file
*/

/** \def QOR_VMD_IS_TYPE(sequence)

    \brief Tests whether a sequence is a VMD type.

    sequence = a possible VMD type
    
    returns = 1 if the sequence is a VMD type, 
              0 if it is not.
    
    If the sequence is not a VMD data type this macro could lead to
    a preprocessor error. This is because the macro
    uses preprocessor concatenation to determine if the sequence
    is an identifier once it is determined that the sequence does not
    start with parentheses. If the data being concatenated would
    lead to an invalid preprocessor token the compiler can issue
    a preprocessor error.
    
*/

#define QOR_VMD_IS_TYPE(sequence) \
    QOR_VMD_DETAIL_IS_TYPE(sequence) \
/**/

/** \def QOR_VMD_IS_TYPE_D(d,sequence)

    \brief Tests whether a sequence is a VMD type. Re-entrant version.

    d        = The next available QOR_PP_WHILE iteration. 
    sequence = a possible VMD type
    
    returns = 1 if the sequence is a VMD type, 
              0 if it is not.
    
    If the sequence is not a VMD data type this macro could lead to
    a preprocessor error. This is because the macro
    uses preprocessor concatenation to determine if the sequence
    is an identifier once it is determined that the sequence does not
    start with parentheses. If the data being concatenated would
    lead to an invalid preprocessor token the compiler can issue
    a preprocessor error.
    
*/

#define QOR_VMD_IS_TYPE_D(d,sequence) \
    QOR_VMD_DETAIL_IS_TYPE_D(d,sequence) \
/**/

#endif /* QOR_PP_VARIADICS */
#endif /* QOR_VMD_IS_TYPE_H */
