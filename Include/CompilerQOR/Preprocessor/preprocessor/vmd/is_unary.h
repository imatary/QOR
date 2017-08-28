
//  (C) Copyright Edward Diener 2011-2015
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(QOR_VMD_IS_UNARY_H)
#define QOR_VMD_IS_UNARY_H

#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/setup.h"

#if QOR_PP_VARIADICS

#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/sequence_arity.h"

/*

  The succeeding comments in this file are in doxygen format.

*/

/** \file
*/

/** \def QOR_VMD_IS_UNARY(sequence)

    \brief Determines if the sequence has only a single element, referred to as a single-element sequence.
    
    sequence = a VMD sequence

    returns = 1 if the sequence is a single-element sequence, else returns 0.
    
    If the size of a sequence is known it is faster comparing that size to be equal
    to one to find out if the sequence is single-element. But if the size of the
    sequence is not known it is faster calling this macro than getting the size and
    doing the previously mentioned comparison in order to determine if the sequence
    is single-element or not.
    
*/

#define QOR_VMD_IS_UNARY(sequence) \
    QOR_VMD_DETAIL_IS_UNARY(sequence) \
/**/

/** \def QOR_VMD_IS_UNARY_D(d,sequence)

    \brief Determines if the sequence has only a single element, referred to as a single-element sequence. Re-entrant version.
    
    d        = The next available QOR_PP_WHILE iteration.
    sequence = a sequence

    returns = 1 if the sequence is a single-element sequence, else returns 0.
    
    If the size of a sequence is known it is faster comparing that size to be equal
    to one to find out if the sequence is single-element. But if the size of the
    sequence is not known it is faster calling this macro than getting the size and
    doing the previously mentioned comparison in order to determine if the sequence
    is single-element or not.
    
*/

#define QOR_VMD_IS_UNARY_D(d,sequence) \
    QOR_VMD_DETAIL_IS_UNARY_D(d,sequence) \
/**/

#endif /* QOR_PP_VARIADICS */
#endif /* QOR_VMD_IS_UNARY_H */
