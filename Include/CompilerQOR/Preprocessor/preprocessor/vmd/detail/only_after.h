
//  (C) Copyright Edward Diener 2011-2015
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(QOR_VMD_DETAIL_ONLY_AFTER_H)
#define QOR_VMD_DETAIL_ONLY_AFTER_H

#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/mods.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/modifiers.h"

/*

    Determines whether or not the QOR_VMD_RETURN_ONLY_AFTER modifiers has been passed
    as a variadic parameter.
    
    Returns 1 = QOR_VMD_RETURN_ONLY_AFTER has been passed
            0 = QOR_VMD_RETURN_ONLY_AFTER has not been passed

*/

#define QOR_VMD_DETAIL_ONLY_AFTER(...) \
    QOR_VMD_DETAIL_MODS_IS_RESULT_ONLY_AFTER \
        ( \
        QOR_VMD_DETAIL_NEW_MODS(QOR_VMD_ALLOW_AFTER,__VA_ARGS__) \
        ) \
/**/

#define QOR_VMD_DETAIL_ONLY_AFTER_D(d,...) \
    QOR_VMD_DETAIL_MODS_IS_RESULT_ONLY_AFTER \
        ( \
        QOR_VMD_DETAIL_NEW_MODS_D(d,QOR_VMD_ALLOW_AFTER,__VA_ARGS__) \
        ) \
/**/

#endif /* QOR_VMD_DETAIL_ONLY_AFTER_H */
