
//  (C) Copyright Edward Diener 2011-2015
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(QOR_VMD_ASSERT_IS_EMPTY_H)
#define QOR_VMD_ASSERT_IS_EMPTY_H

#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/setup.h"

#if QOR_PP_VARIADICS

#if QOR_VMD_ASSERT_DATA

#include "CompilerQOR/Preprocessor/preprocessor/vmd/assert.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/is_empty.h"

#endif

/*

  The succeeding comments in this file are in doxygen format.

*/

/** \file
*/

/** \def QOR_VMD_ASSERT_IS_EMPTY(...)

    \brief Asserts that the input is empty.

    The macro checks to see if the input is empty or not.
    If it is not empty, it forces a compiler error.
    
    The macro is a variadic macro taking any input.
    For the VC++8 compiler (VS2005) the macro takes a single parameter of input to check and not variadic data.
    
    The macro normally checks for emptiness only in 
    debug mode. However an end-user can force the macro 
    to check or not check by defining the macro 
    QOR_VMD_ASSERT_DATA to 1 or 0 respectively.

    .... = variadic input, for VC++8 this must be a single parameter.

    returns = Normally the macro returns nothing. 
    
              If the input is empty, nothing is output.
              
              For VC++, because there is no sure way of forcing  
              a compiler error from within a macro without producing
              output, if the input is not empty the 
              macro forces a compiler error by outputting invalid C++.
              
              For all other compilers a compiler error is forced 
              without producing output if the input is not empty.
    
    It is recommended to append QOR_PP_EMPTY() to whatever input
    is being tested in order to avoid possible warning messages 
    from some compilers about no parameters being passed to the macro
    when the input is truly empty.
    
*/

#if QOR_VMD_MSVC_V8

#if !QOR_VMD_ASSERT_DATA

#define QOR_VMD_ASSERT_IS_EMPTY(input)

#else

#define QOR_VMD_ASSERT_IS_EMPTY(input) \
    QOR_VMD_ASSERT \
          ( \
          QOR_VMD_IS_EMPTY(input), \
          QOR_VMD_IS_EMPTY_ASSERT_ERROR \
          ) \
/**/

#endif // !QOR_VMD_ASSERT_DATA

#else

#if !QOR_VMD_ASSERT_DATA

#define QOR_VMD_ASSERT_IS_EMPTY(...)

#else

#define QOR_VMD_ASSERT_IS_EMPTY(...) \
    QOR_VMD_ASSERT \
          ( \
          QOR_VMD_IS_EMPTY(__VA_ARGS__), \
          QOR_VMD_IS_EMPTY_ASSERT_ERROR \
          ) \
/**/

#endif // !QOR_VMD_ASSERT_DATA

#endif /* QOR_VMD_MSVC_V8 */

#endif /* QOR_PP_VARIADICS */
#endif /* QOR_VMD_ASSERT_IS_EMPTY_H */
