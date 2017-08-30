
//  (C) Copyright Edward Diener 2011-2015
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(QOR_VMD_DETAIL_IS_LIST_H)
#define QOR_VMD_DETAIL_IS_LIST_H

#include "CompilerQOR/Preprocessor/preprocessor/cat.h"
#include "CompilerQOR/Preprocessor/preprocessor/comparison/equal.h"
#include "CompilerQOR/Preprocessor/preprocessor/control/iif.h"
#include "CompilerQOR/Preprocessor/preprocessor/control/while.h"
#include "CompilerQOR/Preprocessor/preprocessor/debug/assert.h"
#include "CompilerQOR/Preprocessor/preprocessor/facilities/empty.h"
#include "CompilerQOR/Preprocessor/preprocessor/logical/bitor.h"
#include "CompilerQOR/Preprocessor/preprocessor/logical/compl.h"
#include "CompilerQOR/Preprocessor/preprocessor/punctuation/is_begin_parens.h"
#include "CompilerQOR/Preprocessor/preprocessor/tuple/elem.h"
#include "CompilerQOR/Preprocessor/preprocessor/tuple/size.h"
#include "CompilerQOR/Preprocessor/preprocessor/variadic/elem.h"
#include "CompilerQOR/Preprocessor/preprocessor/variadic/size.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/identity.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/is_empty.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/is_identifier.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/is_tuple.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/nil_registration.h"

#define QOR_VMD_DETAIL_IS_LIST_PROCESS_TUPLE(d,x) \
    QOR_PP_IIF \
      ( \
      QOR_VMD_IS_TUPLE(x), \
      QOR_VMD_DETAIL_IS_LIST_PROCESS_TUPLE_SIZE, \
      QOR_VMD_DETAIL_IS_LIST_ASSERT \
      ) \
    (d,x) \
/**/

#define QOR_VMD_DETAIL_IS_LIST_PROCESS_TUPLE_SIZE(d,x) \
    QOR_PP_IIF \
      ( \
      QOR_PP_EQUAL_D(d,2,QOR_PP_TUPLE_SIZE(x)), \
      QOR_VMD_DETAIL_IS_LIST_RETURN_SECOND, \
      QOR_VMD_DETAIL_IS_LIST_ASSERT \
      ) \
    (x) \
/**/

#define QOR_VMD_DETAIL_IS_LIST_PRED(d,state) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
          ( \
          QOR_PP_IS_BEGIN_PARENS(state), \
          QOR_VMD_IDENTITY(1), \
          QOR_VMD_DETAIL_IS_LIST_NOT_QOR_PP_NIL \
          ) \
        (state) \
        ) \
/**/

#define QOR_VMD_DETAIL_IS_LIST_OP(d,state) \
    QOR_PP_IIF \
      ( \
      QOR_PP_IS_BEGIN_PARENS(state), \
      QOR_VMD_DETAIL_IS_LIST_PROCESS_TUPLE, \
      QOR_VMD_DETAIL_IS_LIST_PROCESS_IF_QOR_PP_NIL \
      ) \
    (d,state) \
/**/

#define QOR_VMD_DETAIL_IS_LIST_PROCESS_IF_QOR_PP_NIL(d,x) \
    QOR_PP_IIF \
      ( \
      QOR_VMD_DETAIL_IS_LIST_QOR_PP_NIL(x), \
      QOR_PP_NIL, \
      QOR_VMD_IS_LIST_FAILURE \
      ) \
/**/

#define QOR_VMD_DETAIL_IS_LIST_ASSERT(...) \
    QOR_VMD_IS_LIST_FAILURE \
/**/

#define QOR_VMD_DETAIL_IS_LIST_NOT_QOR_PP_NIL(x) \
    QOR_PP_COMPL \
      ( \
      QOR_PP_BITOR \
        ( \
        QOR_VMD_DETAIL_IS_LIST_QOR_PP_NIL(x), \
        QOR_VMD_DETAIL_IS_LIST_IS_FAILURE(x) \
        ) \
      ) \
/**/

#define QOR_VMD_DETAIL_IS_LIST_QOR_PP_NIL(x) \
    QOR_VMD_IS_EMPTY \
      ( \
      QOR_PP_CAT \
        ( \
        QOR_VMD_DETAIL_IS_LIST_NIL_HELPER_, \
        x \
        ) QOR_PP_EMPTY() \
      ) \
/**/

#define QOR_VMD_DETAIL_IS_LIST_NIL_HELPER_QOR_PP_NIL

#define QOR_VMD_DETAIL_IS_LIST_IS_FAILURE(x) \
    QOR_VMD_IS_EMPTY \
      ( \
      QOR_PP_CAT(QOR_VMD_DETAIL_IS_LIST_FHELPER_,x) QOR_PP_EMPTY() \
      ) \
/**/

#define QOR_VMD_DETAIL_IS_LIST_FHELPER_QOR_VMD_IS_LIST_FAILURE

#define QOR_VMD_DETAIL_IS_LIST_RETURN_SECOND(x) \
    QOR_PP_TUPLE_ELEM(1,x) \
/**/

#define QOR_VMD_DETAIL_IS_LIST_RESULT(x) \
    QOR_PP_COMPL \
        ( \
        QOR_VMD_DETAIL_IS_LIST_IS_FAILURE(x) \
        ) \
/**/

#define QOR_VMD_DETAIL_IS_LIST_WLOOP(list) \
    QOR_VMD_DETAIL_IS_LIST_RESULT \
      ( \
      QOR_PP_WHILE \
        ( \
        QOR_VMD_DETAIL_IS_LIST_PRED, \
        QOR_VMD_DETAIL_IS_LIST_OP, \
        list \
        ) \
      ) \
/**/

#define QOR_VMD_DETAIL_IS_LIST_WLOOP_D(d,list) \
    QOR_VMD_DETAIL_IS_LIST_RESULT \
      ( \
      QOR_PP_WHILE_ ## d \
        ( \
        QOR_VMD_DETAIL_IS_LIST_PRED, \
        QOR_VMD_DETAIL_IS_LIST_OP, \
        list \
        ) \
      ) \
/**/

#define QOR_VMD_DETAIL_IS_LIST_IS_EMPTY_LIST_PROCESS(list) \
    QOR_VMD_IS_IDENTIFIER(list,QOR_PP_NIL) \
/**/

#define QOR_VMD_DETAIL_IS_LIST_IS_EMPTY_LIST_PROCESS_D(d,list) \
    QOR_VMD_IS_IDENTIFIER_D(d,list,QOR_PP_NIL) \
/**/

#define QOR_VMD_DETAIL_IS_LIST_PROCESS(param) \
    QOR_PP_IIF \
      ( \
      QOR_PP_IS_BEGIN_PARENS(param), \
      QOR_VMD_DETAIL_IS_LIST_WLOOP, \
      QOR_VMD_DETAIL_IS_LIST_IS_EMPTY_LIST_PROCESS \
      ) \
    (param) \
/**/

#define QOR_VMD_DETAIL_IS_LIST(param) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
          ( \
          QOR_VMD_IS_EMPTY(param), \
          QOR_VMD_IDENTITY(0), \
          QOR_VMD_DETAIL_IS_LIST_PROCESS \
          ) \
        (param) \
        ) \
/**/

#define QOR_VMD_DETAIL_IS_LIST_PROCESS_D(d,param) \
    QOR_PP_IIF \
      ( \
      QOR_PP_IS_BEGIN_PARENS(param), \
      QOR_VMD_DETAIL_IS_LIST_WLOOP_D, \
      QOR_VMD_DETAIL_IS_LIST_IS_EMPTY_LIST_PROCESS_D \
      ) \
    (d,param) \
/**/

#define QOR_VMD_DETAIL_IS_LIST_D(d,param) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
          ( \
          QOR_VMD_IS_EMPTY(param), \
          QOR_VMD_IDENTITY(0), \
          QOR_VMD_DETAIL_IS_LIST_PROCESS_D \
          ) \
        (d,param) \
        ) \
/**/

#endif /* QOR_VMD_DETAIL_IS_LIST_H */
