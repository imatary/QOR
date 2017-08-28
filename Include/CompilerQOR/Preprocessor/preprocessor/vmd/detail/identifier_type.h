
//  (C) Copyright Edward Diener 2011-2015
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(QOR_VMD_DETAIL_IDENTIFIER_TYPE_H)
#define QOR_VMD_DETAIL_IDENTIFIER_TYPE_H

#include "CompilerQOR/Preprocessor/preprocessor/cat.h"
#include "CompilerQOR/Preprocessor/preprocessor/comparison/equal.h"
#include "CompilerQOR/Preprocessor/preprocessor/control/iif.h"
#include "CompilerQOR/Preprocessor/preprocessor/tuple/elem.h"
#include "CompilerQOR/Preprocessor/preprocessor/tuple/size.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/identity.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/is_tuple.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/idprefix.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/number_registration.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/type_registration.h"

#define QOR_VMD_DETAIL_IDENTIFIER_TYPE_CONCATENATE(id) \
    QOR_PP_CAT \
        ( \
        QOR_VMD_DETAIL_IDENTIFIER_SUBTYPE_REGISTRATION_PREFIX, \
        id \
        ) \
/**/

#define QOR_VMD_DETAIL_IDENTIFIER_TYPE_SIZE(cres) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_PP_EQUAL \
                ( \
                QOR_PP_TUPLE_SIZE(cres), \
                2 \
                ), \
            QOR_PP_TUPLE_ELEM, \
            QOR_VMD_IDENTITY(QOR_VMD_TYPE_IDENTIFIER) \
            ) \
        (0,cres) \
        ) \
/**/

#define QOR_VMD_DETAIL_IDENTIFIER_TYPE_SIZE_D(d,cres) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_PP_EQUAL_D \
                ( \
                d, \
                QOR_PP_TUPLE_SIZE(cres), \
                2 \
                ), \
            QOR_PP_TUPLE_ELEM, \
            QOR_VMD_IDENTITY(QOR_VMD_TYPE_IDENTIFIER) \
            ) \
        (0,cres) \
        ) \
/**/

#define QOR_VMD_DETAIL_IDENTIFIER_TYPE_CONCAT(cres) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_VMD_IS_TUPLE(cres), \
            QOR_VMD_DETAIL_IDENTIFIER_TYPE_SIZE, \
            QOR_VMD_IDENTITY(QOR_VMD_TYPE_IDENTIFIER) \
            ) \
        (cres) \
        ) \
/**/

#define QOR_VMD_DETAIL_IDENTIFIER_TYPE_CONCAT_D(d,cres) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_VMD_IS_TUPLE(cres), \
            QOR_VMD_DETAIL_IDENTIFIER_TYPE_SIZE_D, \
            QOR_VMD_IDENTITY(QOR_VMD_TYPE_IDENTIFIER) \
            ) \
        (d,cres) \
        ) \
/**/

/*

  Determines the type of an identifier.
  
  The type may be that of an identifier or else
  it may be a subtype.
  
  Assumes the 'id' is a valid identifier id
  
  Expands to the appropriate type

*/

#define QOR_VMD_DETAIL_IDENTIFIER_TYPE(id) \
    QOR_VMD_DETAIL_IDENTIFIER_TYPE_CONCAT \
        ( \
        QOR_VMD_DETAIL_IDENTIFIER_TYPE_CONCATENATE(id) \
        ) \
/**/

#define QOR_VMD_DETAIL_IDENTIFIER_TYPE_D(d,id) \
    QOR_VMD_DETAIL_IDENTIFIER_TYPE_CONCAT_D \
        ( \
        d, \
        QOR_VMD_DETAIL_IDENTIFIER_TYPE_CONCATENATE(id) \
        ) \
/**/

#endif /* QOR_VMD_DETAIL_IDENTIFIER_TYPE_H */
