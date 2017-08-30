
//  (C) Copyright Edward Diener 2011-2015
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(QOR_VMD_DETAIL_ASSERT_H)
#define QOR_VMD_DETAIL_ASSERT_H

#include "CompilerQOR/Preprocessor/preprocessor/debug/assert.h"
#include "CompilerQOR/Preprocessor/preprocessor/variadic/elem.h"

#if QOR_VMD_MSVC

#include "CompilerQOR/Preprocessor/preprocessor/comparison/equal.h"
#include "CompilerQOR/Preprocessor/preprocessor/control/if.h"
#include "CompilerQOR/Preprocessor/preprocessor/control/iif.h"
#include "CompilerQOR/Preprocessor/preprocessor/variadic/size.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/empty.h"

#define QOR_VMD_DETAIL_ASSERT_VC_GEN_ERROR_OUTPUT(errstr) \
    QOR_PP_ASSERT(0) \
    typedef char errstr[-1]; \
/**/

#define QOR_VMD_DETAIL_ASSERT_VC_GEN_ERROR_DEFAULT(...) \
    QOR_VMD_DETAIL_ASSERT_VC_GEN_ERROR_OUTPUT(QOR_VMD_ASSERT_ERROR) \
/**/

#define QOR_VMD_DETAIL_ASSERT_VC_GEN_ERROR_ERRSTR(...) \
    QOR_VMD_DETAIL_ASSERT_VC_GEN_ERROR_OUTPUT(QOR_PP_VARIADIC_ELEM(1,__VA_ARGS__)) \
/**/

#define QOR_VMD_DETAIL_ASSERT_TRUE(...) \
    QOR_PP_IIF \
        ( \
        QOR_PP_EQUAL \
            ( \
            QOR_PP_VARIADIC_SIZE(__VA_ARGS__), \
            1 \
            ), \
        QOR_VMD_DETAIL_ASSERT_VC_GEN_ERROR_DEFAULT, \
        QOR_VMD_DETAIL_ASSERT_VC_GEN_ERROR_ERRSTR \
        ) \
    (__VA_ARGS__) \
/**/

#define QOR_VMD_DETAIL_ASSERT(...) \
    QOR_PP_IF \
      ( \
      QOR_PP_VARIADIC_ELEM(0,__VA_ARGS__), \
      QOR_VMD_EMPTY, \
      QOR_VMD_DETAIL_ASSERT_TRUE \
      ) \
    (__VA_ARGS__) \
/**/

#else

#define QOR_VMD_DETAIL_ASSERT_DO(cond) \
    QOR_PP_ASSERT(cond) \
/**/

#define QOR_VMD_DETAIL_ASSERT(...) \
    QOR_VMD_DETAIL_ASSERT_DO(QOR_PP_VARIADIC_ELEM(0,__VA_ARGS__)) \
/**/

#endif /* QOR_VMD_MSVC */
#endif /* QOR_VMD_DETAIL_ASSERT_H */
