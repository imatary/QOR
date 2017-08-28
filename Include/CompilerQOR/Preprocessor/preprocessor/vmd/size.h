
//  (C) Copyright Edward Diener 2011-2015
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(QOR_VMD_SIZE_H)
#define QOR_VMD_SIZE_H

#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/setup.h"

#if QOR_PP_VARIADICS

#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/sequence_size.h"

/*

  The succeeding comments in this file are in doxygen format.

*/

/** \file
*/

/** \def QOR_VMD_SIZE(sequence)

    \brief Returns the size of a sequence.

    sequence  = A sequence to test.

    returns   = If the sequence is empty returns 0, else returns the number of elements
                in the sequence.
    
*/

#define QOR_VMD_SIZE(sequence) \
    QOR_VMD_DETAIL_SEQUENCE_SIZE(sequence) \
/**/

/** \def QOR_VMD_SIZE_D(d,sequence)

    \brief Returns the size of a sequence. Re-entrant version.

    d         = The next available QOR_PP_WHILE iteration. 
    sequence  = A sequence to test.

    returns   = If the sequence is empty returns 0, else returns the number of elements
                in the sequence.
    
*/

#define QOR_VMD_SIZE_D(d,sequence) \
    QOR_VMD_DETAIL_SEQUENCE_SIZE_D(d,sequence) \
/**/

#endif /* QOR_PP_VARIADICS */
#endif /* QOR_VMD_SIZE_H */
