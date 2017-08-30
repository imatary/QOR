
//  (C) Copyright Edward Diener 2011-2015
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(QOR_VMD_DETAIL_IS_TYPE_TYPE_H)
#define QOR_VMD_DETAIL_IS_TYPE_TYPE_H

#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/type_registration.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/match_single_identifier.h"

/*

    Check to see if the 'id' is QOR_VMD_TYPE_TYPE
    
    Returns 1 if it is, else 0

*/

#define QOR_VMD_DETAIL_IS_TYPE_TYPE(id) \
    QOR_VMD_DETAIL_MATCH_SINGLE_IDENTIFIER(id,QOR_VMD_TYPE_TYPE) \
/**/

#endif /* QOR_VMD_DETAIL_IS_TYPE_TYPE_H */
