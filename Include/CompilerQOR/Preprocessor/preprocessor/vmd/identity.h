
//  (C) Copyright Edward Diener 2011-2015
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(QOR_VMD_IDENTITY_H)
#define QOR_VMD_IDENTITY_H

#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/setup.h"

#if QOR_PP_VARIADICS

#if QOR_VMD_MSVC
#include "CompilerQOR/Preprocessor/preprocessor/cat.h"
#endif
#include "CompilerQOR/Preprocessor/preprocessor/vmd/empty.h"

/*

  The succeeding comments in this file are in doxygen format.

*/

/** \file
*/

/** \def QOR_VMD_IDENTITY(item)

    \brief Macro which expands to its argument when invoked with any number of parameters.

    item = any single argument
    
    When QOR_VMD_IDENTITY(item) is subsequently invoked with any number of parameters it expands
    to 'item'. Subsequently invoking the macro is done as 'QOR_VMD_IDENTITY(item)(zero_or_more_arguments)'.
    
    The macro is equivalent to the Boost PP macro QOR_PP_IDENTITY(item) with the difference
    being that QOR_PP_IDENTITY(item) is always invoked with no arguments, as in
    'QOR_VMD_IDENTITY(item)()' whereas QOR_VMD_IDENTITY can be invoked with any number of
    arguments.
    
    The macro is meant to be used in QOR_PP_IF and QOR_PP_IIF statements when only one
    of the clauses needs to be invoked with calling another macro and the other is meant to
    return an 'item'.
    
    returns = the macro as 'QOR_VMD_IDENTITY(item)', when invoked with any number of parameters
              as in '(zero_or_more_arguments)', returns 'item'. The macro itself returns
              'item QOR_VMD_EMPTY'.
    
*/

#define QOR_VMD_IDENTITY(item) item QOR_VMD_EMPTY

/** \def QOR_VMD_IDENTITY_RESULT(result)

    \brief Macro which wraps any result which can return its value using QOR_VMD_IDENTITY or 'item QOR_VMD_EMPTY'.

    result = any single result returned when QOR_VMD_IDENTITY is used or 'item QOR_VMD_EMPTY'.
    
    The reason for this macro is to smooth over a problem when using VC++ with QOR_VMD_IDENTITY.
    If your QOR_VMD_IDENTITY macro can be used where VC++ is the compiler then you need to
    surround your macro code which could return a result with this macro in order that VC++ handles
    QOR_VMD_IDENTITY correctly.
    
    If you are not using VC++ you do not have to use this macro, but doing so does no harm.
    
*/

#if QOR_VMD_MSVC
#define QOR_VMD_IDENTITY_RESULT(result) QOR_PP_CAT(result,)
#else
#define QOR_VMD_IDENTITY_RESULT(result) result
#endif

#endif /* QOR_PP_VARIADICS */
#endif /* QOR_VMD_IDENTITY_H */
