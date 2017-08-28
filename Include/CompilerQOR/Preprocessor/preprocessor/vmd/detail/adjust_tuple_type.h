
//  (C) Copyright Edward Diener 2011-2015
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(QOR_VMD_DETAIL_ADJUST_TUPLE_TYPE_H)
#define QOR_VMD_DETAIL_ADJUST_TUPLE_TYPE_H

#include "CompilerQOR/Preprocessor/preprocessor/control/iif.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/identity.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/equal_type.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/is_array_common.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/is_list.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/type_registration.h"

#define QOR_VMD_DETAIL_ADJUST_TUPLE_TYPE_CHECK_ARRAY(data,type) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_IS_ARRAY_SYNTAX(data), \
        QOR_VMD_TYPE_ARRAY, \
        type \
        ) \
/**/

#define QOR_VMD_DETAIL_ADJUST_TUPLE_TYPE_CHECK_ARRAY_D(d,data,type) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_IS_ARRAY_SYNTAX_D(d,data), \
        QOR_VMD_TYPE_ARRAY, \
        type \
        ) \
/**/

#define QOR_VMD_DETAIL_ADJUST_TUPLE_TYPE_CHECK_LIST(data,type) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_VMD_DETAIL_IS_LIST_WLOOP(data), \
            QOR_VMD_IDENTITY(QOR_VMD_TYPE_LIST), \
            QOR_VMD_DETAIL_ADJUST_TUPLE_TYPE_CHECK_ARRAY \
            ) \
        (data,type) \
        ) \
/**/

#define QOR_VMD_DETAIL_ADJUST_TUPLE_TYPE_CHECK_LIST_D(d,data,type) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_VMD_DETAIL_IS_LIST_WLOOP_D(d,data), \
            QOR_VMD_IDENTITY(QOR_VMD_TYPE_LIST), \
            QOR_VMD_DETAIL_ADJUST_TUPLE_TYPE_CHECK_ARRAY_D \
            ) \
        (d,data,type) \
        ) \
/**/

/*

  Input is any VMD data and a VMD type for that data
  
  If the type is a tuple, checks to see if it is a more specific
  type and, if it is, returns that type,
  otherwise returns the type passed as a parameter

*/

#define QOR_VMD_DETAIL_ADJUST_TUPLE_TYPE(data,type) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_VMD_DETAIL_EQUAL_TYPE(QOR_VMD_TYPE_TUPLE,type), \
            QOR_VMD_DETAIL_ADJUST_TUPLE_TYPE_CHECK_LIST, \
            QOR_VMD_IDENTITY(type) \
            ) \
        (data,type) \
        ) \
/**/

#define QOR_VMD_DETAIL_ADJUST_TUPLE_TYPE_D(d,data,type) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_VMD_DETAIL_EQUAL_TYPE_D(d,QOR_VMD_TYPE_TUPLE,type), \
            QOR_VMD_DETAIL_ADJUST_TUPLE_TYPE_CHECK_LIST_D, \
            QOR_VMD_IDENTITY(type) \
            ) \
        (d,data,type) \
        ) \
/**/

#endif /* QOR_VMD_DETAIL_ADJUST_TUPLE_TYPE_H */
