
//  (C) Copyright Edward Diener 2011-2015
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(QOR_VMD_DETAIL_IS_ARRAY_COMMON_H)
#define QOR_VMD_DETAIL_IS_ARRAY_COMMON_H

#include "CompilerQOR/Preprocessor/preprocessor/cat.h"
#include "CompilerQOR/Preprocessor/preprocessor/comparison/equal.h"
#include "CompilerQOR/Preprocessor/preprocessor/control/if.h"
#include "CompilerQOR/Preprocessor/preprocessor/control/iif.h"
#include "CompilerQOR/Preprocessor/preprocessor/facilities/empty.h"
#include "CompilerQOR/Preprocessor/preprocessor/tuple/elem.h"
#include "CompilerQOR/Preprocessor/preprocessor/tuple/size.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/identity.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/is_empty.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/is_number.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/is_tuple.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/is_empty_tuple.h"

#define QOR_VMD_DETAIL_IS_ARRAY_SYNTAX(tuple) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_PP_EQUAL(2,QOR_PP_TUPLE_SIZE(tuple)), \
            QOR_VMD_DETAIL_IS_ARRAY_CHECK_ARRAY_FORM, \
            QOR_VMD_IDENTITY(0) \
            ) \
        (tuple) \
        ) \
/**/

#define QOR_VMD_DETAIL_IS_ARRAY_SYNTAX_D(d,tuple) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_PP_EQUAL_D(d,2,QOR_PP_TUPLE_SIZE(tuple)), \
            QOR_VMD_DETAIL_IS_ARRAY_CHECK_ARRAY_FORM_D, \
            QOR_VMD_IDENTITY(0) \
            ) \
        (d,tuple) \
        ) \
/**/

/*

  Check if the first element of the tuple is equal to the number of tuple elements of the second element

*/

#define QOR_VMD_DETAIL_IS_ARRAY_CHECK_NUMERIC_MATCH_SIZE(x) \
    QOR_PP_EQUAL(QOR_PP_TUPLE_ELEM(0,x),QOR_PP_TUPLE_SIZE(QOR_PP_TUPLE_ELEM(1,x))) \
/**/

#define QOR_VMD_DETAIL_IS_ARRAY_CHECK_NUMERIC_MATCH_SIZE_D(d,x) \
    QOR_PP_EQUAL_D(d,QOR_PP_TUPLE_ELEM(0,x),QOR_PP_TUPLE_SIZE(QOR_PP_TUPLE_ELEM(1,x))) \
/**/

#define QOR_VMD_DETAIL_IS_ARRAY_CHECK_EMPTY(tuple) \
    QOR_VMD_DETAIL_IS_EMPTY_TUPLE_SIZE(QOR_PP_TUPLE_ELEM(1,tuple)) \
/**/

#define QOR_VMD_DETAIL_IS_ARRAY_CHECK_EMPTY_D(d,tuple) \
    QOR_VMD_DETAIL_IS_EMPTY_TUPLE_SIZE(QOR_PP_TUPLE_ELEM(1,tuple)) \
/**/

#define QOR_VMD_DETAIL_IS_ARRAY_CHECK_NUMERIC_MATCH(tuple) \
    QOR_PP_IF \
        ( \
        QOR_PP_TUPLE_ELEM(0,tuple), \
        QOR_VMD_DETAIL_IS_ARRAY_CHECK_NUMERIC_MATCH_SIZE, \
        QOR_VMD_DETAIL_IS_ARRAY_CHECK_EMPTY \
        ) \
    (tuple) \
/**/

#define QOR_VMD_DETAIL_IS_ARRAY_CHECK_NUMERIC_MATCH_D(d,tuple) \
    QOR_PP_IF \
        ( \
        QOR_PP_TUPLE_ELEM(0,tuple), \
        QOR_VMD_DETAIL_IS_ARRAY_CHECK_NUMERIC_MATCH_SIZE_D, \
        QOR_VMD_DETAIL_IS_ARRAY_CHECK_EMPTY_D \
        ) \
    (d,tuple) \
/**/

/*

  Check if the first element is numeric

*/

#define QOR_VMD_DETAIL_IS_ARRAY_CHECK_NUMERIC(tuple) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
          ( \
          QOR_VMD_DETAIL_IS_ARRAY_NUM(QOR_PP_TUPLE_ELEM(0,tuple)), \
          QOR_VMD_DETAIL_IS_ARRAY_CHECK_NUMERIC_MATCH, \
          QOR_VMD_IDENTITY(0) \
          ) \
        (tuple) \
        ) \
/**/

#define QOR_VMD_DETAIL_IS_ARRAY_CHECK_NUMERIC_D(d,tuple) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
          ( \
          QOR_VMD_DETAIL_IS_ARRAY_NUM(QOR_PP_TUPLE_ELEM(0,tuple)), \
          QOR_VMD_DETAIL_IS_ARRAY_CHECK_NUMERIC_MATCH_D, \
          QOR_VMD_IDENTITY(0) \
          ) \
        (d,tuple) \
        ) \
/**/

#define QOR_VMD_DETAIL_IS_ARRAY_CHECK_NUMBER(tuple) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_VMD_IS_NUMBER(QOR_PP_TUPLE_ELEM(0,tuple)), \
            QOR_VMD_DETAIL_IS_ARRAY_CHECK_NUMERIC, \
            QOR_VMD_IDENTITY(0) \
            ) \
        (tuple) \
        ) \
/**/

#define QOR_VMD_DETAIL_IS_ARRAY_CHECK_NUMBER_D(d,tuple) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_VMD_IS_NUMBER(QOR_PP_TUPLE_ELEM(0,tuple)), \
            QOR_VMD_DETAIL_IS_ARRAY_CHECK_NUMERIC_D, \
            QOR_VMD_IDENTITY(0) \
            ) \
        (d,tuple) \
        ) \
/**/

/*

  Check if the second element is a tuple

*/

#define QOR_VMD_DETAIL_IS_ARRAY_CHECK_ARRAY_FORM(tuple) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
          ( \
          QOR_VMD_IS_TUPLE(QOR_PP_TUPLE_ELEM(1,tuple)), \
          QOR_VMD_DETAIL_IS_ARRAY_CHECK_NUMBER, \
          QOR_VMD_IDENTITY(0) \
          ) \
        (tuple) \
        ) \
/**/

#define QOR_VMD_DETAIL_IS_ARRAY_CHECK_ARRAY_FORM_D(d,tuple) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
          ( \
          QOR_VMD_IS_TUPLE(QOR_PP_TUPLE_ELEM(1,tuple)), \
          QOR_VMD_DETAIL_IS_ARRAY_CHECK_NUMBER_D, \
          QOR_VMD_IDENTITY(0) \
          ) \
        (d,tuple) \
        ) \
/**/

#define QOR_VMD_DETAIL_IS_ARRAY_NUM(x) QOR_VMD_IS_EMPTY(QOR_PP_CAT(QOR_VMD_DETAIL_IS_ARRAY_NUM_HELPER_, x) QOR_PP_EMPTY())
#define QOR_VMD_DETAIL_IS_ARRAY_NUM_HELPER_0
#define QOR_VMD_DETAIL_IS_ARRAY_NUM_HELPER_1
#define QOR_VMD_DETAIL_IS_ARRAY_NUM_HELPER_2
#define QOR_VMD_DETAIL_IS_ARRAY_NUM_HELPER_3
#define QOR_VMD_DETAIL_IS_ARRAY_NUM_HELPER_4
#define QOR_VMD_DETAIL_IS_ARRAY_NUM_HELPER_5
#define QOR_VMD_DETAIL_IS_ARRAY_NUM_HELPER_6
#define QOR_VMD_DETAIL_IS_ARRAY_NUM_HELPER_7
#define QOR_VMD_DETAIL_IS_ARRAY_NUM_HELPER_8
#define QOR_VMD_DETAIL_IS_ARRAY_NUM_HELPER_9
#define QOR_VMD_DETAIL_IS_ARRAY_NUM_HELPER_10
#define QOR_VMD_DETAIL_IS_ARRAY_NUM_HELPER_11
#define QOR_VMD_DETAIL_IS_ARRAY_NUM_HELPER_12
#define QOR_VMD_DETAIL_IS_ARRAY_NUM_HELPER_13
#define QOR_VMD_DETAIL_IS_ARRAY_NUM_HELPER_14
#define QOR_VMD_DETAIL_IS_ARRAY_NUM_HELPER_15
#define QOR_VMD_DETAIL_IS_ARRAY_NUM_HELPER_16
#define QOR_VMD_DETAIL_IS_ARRAY_NUM_HELPER_17
#define QOR_VMD_DETAIL_IS_ARRAY_NUM_HELPER_18
#define QOR_VMD_DETAIL_IS_ARRAY_NUM_HELPER_19
#define QOR_VMD_DETAIL_IS_ARRAY_NUM_HELPER_20
#define QOR_VMD_DETAIL_IS_ARRAY_NUM_HELPER_21
#define QOR_VMD_DETAIL_IS_ARRAY_NUM_HELPER_22
#define QOR_VMD_DETAIL_IS_ARRAY_NUM_HELPER_23
#define QOR_VMD_DETAIL_IS_ARRAY_NUM_HELPER_24
#define QOR_VMD_DETAIL_IS_ARRAY_NUM_HELPER_25
#define QOR_VMD_DETAIL_IS_ARRAY_NUM_HELPER_26
#define QOR_VMD_DETAIL_IS_ARRAY_NUM_HELPER_27
#define QOR_VMD_DETAIL_IS_ARRAY_NUM_HELPER_28
#define QOR_VMD_DETAIL_IS_ARRAY_NUM_HELPER_29
#define QOR_VMD_DETAIL_IS_ARRAY_NUM_HELPER_30
#define QOR_VMD_DETAIL_IS_ARRAY_NUM_HELPER_31
#define QOR_VMD_DETAIL_IS_ARRAY_NUM_HELPER_32
#define QOR_VMD_DETAIL_IS_ARRAY_NUM_HELPER_33
#define QOR_VMD_DETAIL_IS_ARRAY_NUM_HELPER_34
#define QOR_VMD_DETAIL_IS_ARRAY_NUM_HELPER_35
#define QOR_VMD_DETAIL_IS_ARRAY_NUM_HELPER_36
#define QOR_VMD_DETAIL_IS_ARRAY_NUM_HELPER_37
#define QOR_VMD_DETAIL_IS_ARRAY_NUM_HELPER_38
#define QOR_VMD_DETAIL_IS_ARRAY_NUM_HELPER_39
#define QOR_VMD_DETAIL_IS_ARRAY_NUM_HELPER_40
#define QOR_VMD_DETAIL_IS_ARRAY_NUM_HELPER_41
#define QOR_VMD_DETAIL_IS_ARRAY_NUM_HELPER_42
#define QOR_VMD_DETAIL_IS_ARRAY_NUM_HELPER_43
#define QOR_VMD_DETAIL_IS_ARRAY_NUM_HELPER_44
#define QOR_VMD_DETAIL_IS_ARRAY_NUM_HELPER_45
#define QOR_VMD_DETAIL_IS_ARRAY_NUM_HELPER_46
#define QOR_VMD_DETAIL_IS_ARRAY_NUM_HELPER_47
#define QOR_VMD_DETAIL_IS_ARRAY_NUM_HELPER_48
#define QOR_VMD_DETAIL_IS_ARRAY_NUM_HELPER_49
#define QOR_VMD_DETAIL_IS_ARRAY_NUM_HELPER_50
#define QOR_VMD_DETAIL_IS_ARRAY_NUM_HELPER_51
#define QOR_VMD_DETAIL_IS_ARRAY_NUM_HELPER_52
#define QOR_VMD_DETAIL_IS_ARRAY_NUM_HELPER_53
#define QOR_VMD_DETAIL_IS_ARRAY_NUM_HELPER_54
#define QOR_VMD_DETAIL_IS_ARRAY_NUM_HELPER_55
#define QOR_VMD_DETAIL_IS_ARRAY_NUM_HELPER_56
#define QOR_VMD_DETAIL_IS_ARRAY_NUM_HELPER_57
#define QOR_VMD_DETAIL_IS_ARRAY_NUM_HELPER_58
#define QOR_VMD_DETAIL_IS_ARRAY_NUM_HELPER_59
#define QOR_VMD_DETAIL_IS_ARRAY_NUM_HELPER_60
#define QOR_VMD_DETAIL_IS_ARRAY_NUM_HELPER_61
#define QOR_VMD_DETAIL_IS_ARRAY_NUM_HELPER_62
#define QOR_VMD_DETAIL_IS_ARRAY_NUM_HELPER_63
#define QOR_VMD_DETAIL_IS_ARRAY_NUM_HELPER_64

#endif /* QOR_VMD_DETAIL_IS_ARRAY_COMMON_H */
