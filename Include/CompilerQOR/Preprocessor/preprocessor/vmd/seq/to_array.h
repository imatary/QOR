
//  (C) Copyright Edward Diener 2015
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(QOR_VMD_SEQ_TO_ARRAY_H)
#define QOR_VMD_SEQ_TO_ARRAY_H

#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/setup.h"

#if QOR_PP_VARIADICS

#include "CompilerQOR/Preprocessor/preprocessor/control/iif.h"
#include "CompilerQOR/Preprocessor/preprocessor/seq/to_array.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/identity.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/is_empty.h"

/*

  The succeeding comments in this file are in doxygen format.

*/

/** \file
*/

/** \def QOR_VMD_SEQ_TO_ARRAY(seq)

    \brief converts a seq to an array.

    seq = seq to be converted.
    
    If the seq is an empty seq it is converted to an array with 0 elements.
    Otherwise the seq is converted to an array with the same number of elements as the seq.
*/

#define QOR_VMD_SEQ_TO_ARRAY(seq) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_VMD_IS_EMPTY(seq), \
            QOR_VMD_IDENTITY((0,())), \
            QOR_PP_SEQ_TO_ARRAY \
            ) \
        (seq) \
        ) \
/**/

#endif /* QOR_PP_VARIADICS */
#endif /* QOR_VMD_SEQ_TO_ARRAY_H */
