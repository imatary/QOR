
//  (C) Copyright Edward Diener 2015
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(QOR_VMD_SEQ_PUSH_BACK_H)
#define QOR_VMD_SEQ_PUSH_BACK_H

#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/setup.h"

#if QOR_PP_VARIADICS

#include "CompilerQOR/Preprocessor/preprocessor/control/iif.h"
#include "CompilerQOR/Preprocessor/preprocessor/seq/push_back.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/identity.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/is_empty.h"

/*

  The succeeding comments in this file are in doxygen format.

*/

/** \file
*/

/** \def QOR_VMD_SEQ_PUSH_BACK(seq,elem)

    \brief appends an element to the end of a seq. 

    seq = seq to to append an element to.
    elem  = element to append.

    If the seq is an empty seq the result is a seq with the single element.
    Otherwise the result is a seq after adding the element to the end.
*/

#define QOR_VMD_SEQ_PUSH_BACK(seq,elem) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_VMD_IS_EMPTY(seq), \
            QOR_VMD_IDENTITY((elem)), \
            QOR_PP_SEQ_PUSH_BACK \
            ) \
        (seq,elem) \
        ) \
/**/

#endif /* QOR_PP_VARIADICS */
#endif /* QOR_VMD_SEQ_PUSH_BACK_H */
