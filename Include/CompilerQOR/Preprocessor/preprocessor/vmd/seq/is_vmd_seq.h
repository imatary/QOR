
//  (C) Copyright Edward Diener 2015
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(QOR_VMD_IS_VMD_SEQ_H)
#define QOR_VMD_IS_VMD_SEQ_H

#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/setup.h"

#if QOR_PP_VARIADICS

#include "CompilerQOR/Preprocessor/preprocessor/control/iif.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/identity.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/is_empty.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/is_seq.h"

/*

  The succeeding comments in this file are in doxygen format.

*/

/** \file
*/

/** \def QOR_VMD_IS_VMD_SEQ(sequence)

    \brief Determines if a sequence is a VMD seq.

    The macro checks that the sequence is a VMD seq.
    A VMD seq, which may be a Boost PP seq or emptiness, is a superset of a Boost PP seq.
    It returns 1 if it is a VMD seq, else if returns 0.
    
    sequence = a possible Boost PP seq

    returns = 1 if it a VMD seq, else returns 0.
    
*/

#define QOR_VMD_IS_VMD_SEQ(sequence) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_VMD_IS_EMPTY(sequence), \
            QOR_VMD_IDENTITY(1), \
            QOR_VMD_IS_SEQ \
            ) \
        (sequence) \
        ) \
/**/

#endif /* QOR_PP_VARIADICS */
#endif /* QOR_VMD_IS_VMD_SEQ_H */
