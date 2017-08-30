
//  (C) Copyright Edward Diener 2011-2015
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(QOR_VMD_DETAIL_PARENS_SPLIT_H)
#define QOR_VMD_DETAIL_PARENS_SPLIT_H

#include "CompilerQOR/Preprocessor/preprocessor/control/iif.h"
#include "CompilerQOR/Preprocessor/preprocessor/punctuation/is_begin_parens.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/empty_result.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/parens_common.h"
  
#define QOR_VMD_DETAIL_PARENS_SPLIT(vseq) \
    QOR_PP_IIF \
      ( \
      QOR_PP_IS_BEGIN_PARENS(vseq), \
      QOR_VMD_DETAIL_SPLIT_PARENS, \
      QOR_VMD_DETAIL_EMPTY_RESULT \
      ) \
    (vseq) \
/**/
#endif /* QOR_VMD_DETAIL_PARENS_SPLIT_H */
