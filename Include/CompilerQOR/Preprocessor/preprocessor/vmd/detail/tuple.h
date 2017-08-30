
//  (C) Copyright Edward Diener 2011-2015
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(QOR_VMD_DETAIL_TUPLE_H)
#define QOR_VMD_DETAIL_TUPLE_H

#include "CompilerQOR/Preprocessor/preprocessor/comparison/equal.h"
#include "CompilerQOR/Preprocessor/preprocessor/control/iif.h"
#include "CompilerQOR/Preprocessor/preprocessor/punctuation/is_begin_parens.h"
#include "CompilerQOR/Preprocessor/preprocessor/tuple/size.h"
#include "CompilerQOR/Preprocessor/preprocessor/variadic/elem.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/empty.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/is_empty.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/identity.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/empty_result.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/mods.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/parens.h"
  
#define QOR_VMD_DETAIL_TUPLE_BST_CS(vseq) \
    QOR_PP_EQUAL(QOR_PP_TUPLE_SIZE(QOR_VMD_DETAIL_BEGIN_PARENS(vseq)),1) \
/**/

#define QOR_VMD_DETAIL_TUPLE_BST_CS_D(d,vseq) \
    QOR_PP_EQUAL_D(d,QOR_PP_TUPLE_SIZE(QOR_VMD_DETAIL_BEGIN_PARENS(vseq)),1) \
/**/

#define QOR_VMD_DETAIL_TUPLE_BST(vseq) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_PP_IS_BEGIN_PARENS(vseq), \
            QOR_VMD_DETAIL_TUPLE_BST_CS, \
            QOR_VMD_IDENTITY(0) \
            ) \
        (vseq) \
        ) \
/**/

#define QOR_VMD_DETAIL_TUPLE_BST_D(d,vseq) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_PP_IS_BEGIN_PARENS(vseq), \
            QOR_VMD_DETAIL_TUPLE_BST_CS_D, \
            QOR_VMD_IDENTITY(0) \
            ) \
        (d,vseq) \
        ) \
/**/

#define QOR_VMD_DETAIL_TUPLE_BSEQ_NXT(vseq) \
    QOR_VMD_DETAIL_TUPLE_BST(QOR_VMD_DETAIL_AFTER_PARENS_DATA(vseq)) \
/**/

#define QOR_VMD_DETAIL_TUPLE_BSEQ_NXT_D(d,vseq) \
    QOR_VMD_DETAIL_TUPLE_BST_D(d,QOR_VMD_DETAIL_AFTER_PARENS_DATA(vseq)) \
/**/

#define QOR_VMD_DETAIL_TUPLE_BSEQ(vseq) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_VMD_DETAIL_TUPLE_BST(vseq), \
            QOR_VMD_DETAIL_TUPLE_BSEQ_NXT, \
            QOR_VMD_IDENTITY(0) \
            ) \
        (vseq) \
        ) \
/**/

#define QOR_VMD_DETAIL_TUPLE_BSEQ_D(d,vseq) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_VMD_DETAIL_TUPLE_BST_D(d,vseq), \
            QOR_VMD_DETAIL_TUPLE_BSEQ_NXT_D, \
            QOR_VMD_IDENTITY(0) \
            ) \
        (d,vseq) \
        ) \
/**/

#define QOR_VMD_DETAIL_TUPLE_SPLIT_CHK_SEQ(vseq) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_TUPLE_BSEQ(vseq), \
        QOR_VMD_DETAIL_EMPTY_RESULT, \
        QOR_VMD_DETAIL_SPLIT_PARENS \
        ) \
    (vseq) \
/**/

#define QOR_VMD_DETAIL_TUPLE_SPLIT_CHK_SEQ_D(d,vseq) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_TUPLE_BSEQ_D(d,vseq), \
        QOR_VMD_DETAIL_EMPTY_RESULT, \
        QOR_VMD_DETAIL_SPLIT_PARENS \
        ) \
    (vseq) \
/**/

#define QOR_VMD_DETAIL_TUPLE_SPLIT(vseq) \
    QOR_PP_IIF \
      ( \
      QOR_PP_IS_BEGIN_PARENS(vseq), \
      QOR_VMD_DETAIL_TUPLE_SPLIT_CHK_SEQ, \
      QOR_VMD_DETAIL_EMPTY_RESULT \
      ) \
    (vseq) \
/**/

#define QOR_VMD_DETAIL_TUPLE_SPLIT_D(d,vseq) \
    QOR_PP_IIF \
      ( \
      QOR_PP_IS_BEGIN_PARENS(vseq), \
      QOR_VMD_DETAIL_TUPLE_SPLIT_CHK_SEQ_D, \
      QOR_VMD_DETAIL_EMPTY_RESULT \
      ) \
    (d,vseq) \
/**/

#define QOR_VMD_DETAIL_TUPLE_PROCESS_CHK_SEQ(vseq) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_TUPLE_BSEQ(vseq), \
        QOR_VMD_EMPTY, \
        QOR_VMD_DETAIL_BEGIN_PARENS \
        ) \
    (vseq) \
/**/

#define QOR_VMD_DETAIL_TUPLE_PROCESS_CHK_SEQ_D(d,vseq) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_TUPLE_BSEQ_D(d,vseq), \
        QOR_VMD_EMPTY, \
        QOR_VMD_DETAIL_BEGIN_PARENS \
        ) \
    (vseq) \
/**/

#define QOR_VMD_DETAIL_TUPLE_PROCESS(vseq) \
    QOR_PP_IIF \
      ( \
      QOR_PP_IS_BEGIN_PARENS(vseq), \
      QOR_VMD_DETAIL_TUPLE_PROCESS_CHK_SEQ, \
      QOR_VMD_EMPTY \
      ) \
    (vseq) \
/**/

#define QOR_VMD_DETAIL_TUPLE_PROCESS_D(d,vseq) \
    QOR_PP_IIF \
      ( \
      QOR_PP_IS_BEGIN_PARENS(vseq), \
      QOR_VMD_DETAIL_TUPLE_PROCESS_CHK_SEQ_D, \
      QOR_VMD_EMPTY \
      ) \
    (d,vseq) \
/**/

#define QOR_VMD_DETAIL_TUPLE(...) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_MODS_IS_RESULT_AFTER \
            ( \
            QOR_VMD_DETAIL_NEW_MODS(QOR_VMD_ALLOW_AFTER,__VA_ARGS__) \
            ), \
        QOR_VMD_DETAIL_TUPLE_SPLIT, \
        QOR_VMD_DETAIL_TUPLE_PROCESS \
        ) \
    (QOR_PP_VARIADIC_ELEM(0,__VA_ARGS__)) \
/**/

#define QOR_VMD_DETAIL_TUPLE_D(d,...) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_MODS_IS_RESULT_AFTER \
            ( \
            QOR_VMD_DETAIL_NEW_MODS(QOR_VMD_ALLOW_AFTER,__VA_ARGS__) \
            ), \
        QOR_VMD_DETAIL_TUPLE_SPLIT_D, \
        QOR_VMD_DETAIL_TUPLE_PROCESS_D \
        ) \
    (d,QOR_PP_VARIADIC_ELEM(0,__VA_ARGS__)) \
/**/

#endif /* QOR_VMD_DETAIL_TUPLE_H */
