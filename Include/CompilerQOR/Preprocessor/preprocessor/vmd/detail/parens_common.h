
//  (C) Copyright Edward Diener 2011-2015
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(QOR_VMD_DETAIL_PARENS_COMMON_H)
#define QOR_VMD_DETAIL_PARENS_COMMON_H

#include "CompilerQOR/Preprocessor/preprocessor/facilities/expand.h"
#include "CompilerQOR/Preprocessor/preprocessor/punctuation/paren.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/empty.h"
  
#define QOR_VMD_DETAIL_BEGIN_PARENS_EXP2(...) ( __VA_ARGS__ ) QOR_VMD_EMPTY QOR_PP_LPAREN()
#define QOR_VMD_DETAIL_BEGIN_PARENS_EXP1(vseq) QOR_VMD_DETAIL_BEGIN_PARENS_EXP2 vseq QOR_PP_RPAREN()
#define QOR_VMD_DETAIL_BEGIN_PARENS(vseq) QOR_PP_EXPAND(QOR_VMD_DETAIL_BEGIN_PARENS_EXP1(vseq))

#define QOR_VMD_DETAIL_AFTER_PARENS_DATA(vseq) QOR_VMD_EMPTY vseq
#define QOR_VMD_DETAIL_SPLIT_PARENS(vseq) (QOR_VMD_DETAIL_BEGIN_PARENS(vseq),QOR_VMD_DETAIL_AFTER_PARENS_DATA(vseq))

#endif /* QOR_VMD_DETAIL_PARENS_COMMON_H */
