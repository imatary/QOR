
//  (C) Copyright Edward Diener 2011-2015
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(QOR_VMD_DETAIL_IS_TYPE_H)
#define QOR_VMD_DETAIL_IS_TYPE_H

#include "CompilerQOR/Preprocessor/preprocessor/control/iif.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/identity.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/identifier_type.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/is_type_type.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/is_identifier.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/type_registration.h"

#define QOR_VMD_DETAIL_IS_TYPE_IMP_TYPE(vseq) \
    QOR_VMD_DETAIL_IS_TYPE_TYPE \
        ( \
        QOR_VMD_DETAIL_IDENTIFIER_TYPE(vseq) \
        ) \
/**/

#define QOR_VMD_DETAIL_IS_TYPE_IMP_TYPE_D(d,vseq) \
    QOR_VMD_DETAIL_IS_TYPE_TYPE \
        ( \
        QOR_VMD_DETAIL_IDENTIFIER_TYPE_D(d,vseq) \
        ) \
/**/

#define QOR_VMD_DETAIL_IS_TYPE(vseq) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_VMD_DETAIL_IS_IDENTIFIER_SINGLE(vseq), \
            QOR_VMD_DETAIL_IS_TYPE_IMP_TYPE, \
            QOR_VMD_IDENTITY(0) \
            ) \
        (vseq) \
        ) \
/**/

#define QOR_VMD_DETAIL_IS_TYPE_D(d,vseq) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_VMD_DETAIL_IS_IDENTIFIER_SINGLE_D(d,vseq), \
            QOR_VMD_DETAIL_IS_TYPE_IMP_TYPE_D, \
            QOR_VMD_IDENTITY(0) \
            ) \
        (d,vseq) \
        ) \
/**/

#endif /* QOR_VMD_DETAIL_IS_TYPE_H */
