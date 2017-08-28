
//  (C) Copyright Edward Diener 2011-2015
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(QOR_VMD_EMPTY_H)
#define QOR_VMD_EMPTY_H

#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/setup.h"

#if QOR_PP_VARIADICS

/*

  The succeeding comments in this file are in doxygen format.

*/

/** \file
*/

/** \def QOR_VMD_EMPTY(...)

    \brief Outputs emptiness.

    ... = any variadic parameters. The parameters are ignored.
    
    This macro is used to output emptiness ( nothing ) no matter
    what is passed to it.
    
    If you use this macro to return a result, as in 'result QOR_VMD_EMPTY'
    subsequently invoked, you should surround the result with 
    QOR_VMD_IDENTITY_RESULT to smooth over a VC++ problem.
    
*/
    
#define QOR_VMD_EMPTY(...)

#endif /* QOR_PP_VARIADICS */
#endif /* QOR_VMD_EMPTY_H */
