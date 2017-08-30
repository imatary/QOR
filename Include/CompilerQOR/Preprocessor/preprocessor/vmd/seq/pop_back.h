
//  (C) Copyright Edward Diener 2015
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(QOR_VMD_SEQ_POP_BACK_H)
#define QOR_VMD_SEQ_POP_BACK_H

#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/setup.h"

#if QOR_PP_VARIADICS

#include "CompilerQOR/Preprocessor/preprocessor/comparison/equal.h"
#include "CompilerQOR/Preprocessor/preprocessor/control/iif.h"
#include "CompilerQOR/Preprocessor/preprocessor/seq/pop_back.h"
#include "CompilerQOR/Preprocessor/preprocessor/seq/size.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/empty.h"

/*

  The succeeding comments in this file are in doxygen format.

*/

/** \file
*/

/** \def QOR_VMD_SEQ_POP_BACK(seq)

    \brief pops an element from the end of a seq. 

    seq = seq to pop an element from.

    If the seq is an empty seq the result is undefined.
    If the seq is a single element the result is an empty seq.
    Otherwise the result is a seq after removing the last element.
*/

#define QOR_VMD_SEQ_POP_BACK(seq) \
    QOR_PP_IIF \
        ( \
        QOR_PP_EQUAL(QOR_PP_SEQ_SIZE(seq),1), \
        QOR_VMD_EMPTY, \
        QOR_PP_SEQ_POP_BACK \
        ) \
    (seq) \
/**/

#endif /* QOR_PP_VARIADICS */
#endif /* QOR_VMD_SEQ_POP_BACK_H */
