
//  (C) Copyright Edward Diener 2011-2015
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(QOR_VMD_DETAIL_PARENS_H)
#define QOR_VMD_DETAIL_PARENS_H

#include "CompilerQOR/Preprocessor/preprocessor/control/iif.h"
#include "CompilerQOR/Preprocessor/preprocessor/punctuation/is_begin_parens.h"
#include "CompilerQOR/Preprocessor/preprocessor/variadic/elem.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/empty.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/mods.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/parens_split.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/parens_common.h"
  
#define QOR_VMD_DETAIL_PARENS_PROCESS(vseq) \
    QOR_PP_IIF \
      ( \
      QOR_PP_IS_BEGIN_PARENS(vseq), \
      QOR_VMD_DETAIL_BEGIN_PARENS, \
      QOR_VMD_EMPTY \
      ) \
    (vseq) \
/**/

#define QOR_VMD_DETAIL_PARENS(...) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_MODS_IS_RESULT_AFTER \
            ( \
            QOR_VMD_DETAIL_NEW_MODS(QOR_VMD_ALLOW_AFTER,__VA_ARGS__) \
            ), \
        QOR_VMD_DETAIL_PARENS_SPLIT, \
        QOR_VMD_DETAIL_PARENS_PROCESS \
        ) \
    (QOR_PP_VARIADIC_ELEM(0,__VA_ARGS__)) \
/**/

#define QOR_VMD_DETAIL_PARENS_D(d,...) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_MODS_IS_RESULT_AFTER \
            ( \
            QOR_VMD_DETAIL_NEW_MODS_D(d,QOR_VMD_ALLOW_AFTER,__VA_ARGS__) \
            ), \
        QOR_VMD_DETAIL_PARENS_SPLIT, \
        QOR_VMD_DETAIL_PARENS_PROCESS \
        ) \
    (QOR_PP_VARIADIC_ELEM(0,__VA_ARGS__)) \
/**/

#endif /* QOR_VMD_DETAIL_PARENS_H */
