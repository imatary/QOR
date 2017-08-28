
//  (C) Copyright Edward Diener 2015
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(QOR_VMD_SEQ_REMOVE_H)
#define QOR_VMD_SEQ_REMOVE_H

#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/setup.h"

#if QOR_PP_VARIADICS

#include "CompilerQOR/Preprocessor/preprocessor/comparison/equal.h"
#include "CompilerQOR/Preprocessor/preprocessor/control/iif.h"
#include "CompilerQOR/Preprocessor/preprocessor/logical/bitand.h"
#include "CompilerQOR/Preprocessor/preprocessor/seq/remove.h"
#include "CompilerQOR/Preprocessor/preprocessor/seq/size.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/empty.h"

/*

  The succeeding comments in this file are in doxygen format.

*/

/** \file
*/

/** \def QOR_VMD_SEQ_REMOVE(seq,index)

    \brief removes an element from a seq.

    seq = seq from which an element is to be removed.
    index = The zero-based position in seq of the element to be removed.

    If index is greater or equal to the seq size the result is undefined.
    If the seq is a single element and the index is 0 the result is an empty seq.
    Otherwise the result is a seq after removing the index element.
*/

#define QOR_VMD_SEQ_REMOVE(seq,index) \
    QOR_PP_IIF \
        ( \
        QOR_PP_BITAND \
            ( \
            QOR_PP_EQUAL(index,0), \
            QOR_PP_EQUAL(QOR_PP_SEQ_SIZE(seq),1) \
            ), \
        QOR_VMD_EMPTY, \
        QOR_PP_SEQ_REMOVE \
        ) \
    (seq,index) \
/**/

#endif /* QOR_PP_VARIADICS */
#endif /* QOR_VMD_SEQ_REMOVE_H */
