
//  (C) Copyright Edward Diener 2011-2015
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(QOR_VMD_DETAIL_IDENTIFIER_CONCAT_H)
#define QOR_VMD_DETAIL_IDENTIFIER_CONCAT_H

#include "CompilerQOR/Preprocessor/preprocessor/cat.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/idprefix.h"

#define QOR_VMD_DETAIL_IDENTIFIER_CONCATENATE(vseq) \
    QOR_PP_CAT \
        ( \
        QOR_VMD_DETAIL_IDENTIFIER_REGISTRATION_PREFIX, \
        vseq \
        ) \
/**/

#endif /* QOR_VMD_DETAIL_IDENTIFIER_CONCAT_H */
