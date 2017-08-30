
//  (C) Copyright Edward Diener 2011-2015
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(QOR_VMD_TO_LIST_H)
#define QOR_VMD_TO_LIST_H

#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/setup.h"

#if QOR_PP_VARIADICS

#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/sequence_to_list.h"

/*

  The succeeding comments in this file are in doxygen format.

*/

/** \file
*/

/** \def QOR_VMD_TO_LIST(...)

    \brief Converts a sequence to a Boost PP list whose elements are the elements of the sequence.

    ...       = Variadic parameters.
    
    The first variadic parameter is required and is the sequence to convert.
    
    Further optional variadic parameters can be return type parameters. Return type
    parameters allow each element in the sequence to be converted to a two-element
    tuple where the first tuple element is the type and the second tuple element
    is the element data.
    
    The QOR_VMD_RETURN_NO_TYPE, the default, does not return the type as part of each
    converted element but just the data. All of the rest return the type and data as the
    two-element tuple. If QOR_VMD_RETURN_TYPE is specified the specific type of the element
    is returned in the tuple. If QOR_VMD_RETURN_TYPE_ARRAY is specified an array type is 
    returned if the element is an array, else a tuple type is returned if the element is a tuple, 
    else the actual type is returned for non-tuple data. If QOR_VMD_RETURN_TYPE_LIST is specified
    a list type is returned if the element is a list, else a tuple type is returned if the element 
    is a tuple, else the actual type is returned for non-tuple data. If QOR_VMD_RETURN_TYPE_TUPLE 
    is specified a tuple type is returned for all tuple-like data, else the actual type is returned 
    for non-tuple data. If more than one return type optional parameter is specified the last one 
    specified determines the return type.
    
    returns   = A Boost PP list. The sequence is empty the Boost PP list is an empty list.
                If an optional return type other than QOR_VMD_RETURN_NO_TYPE
                is specified the type and the data of each element is
                returned as the list element. Otherwise just the data
                is returned as the list element, which is the default.
    
*/

#define QOR_VMD_TO_LIST(...) \
    QOR_VMD_DETAIL_SEQUENCE_TO_LIST(__VA_ARGS__) \
/**/

/** \def QOR_VMD_TO_LIST_D(d,...)

    \brief Converts a sequence to a Boost PP list whose elements are the elements of the sequence. Re-entrant version.

    d         = The next available QOR_PP_WHILE iteration. 
    ...       = Variadic parameters.
    
    The first variadic parameter is required and is the sequence to convert.
    
    Further optional variadic parameters can be return type parameters. Return type
    parameters allow each element in the sequence to be converted to a two-element
    tuple where the first tuple element is the type and the second tuple element
    is the element data.
    
    The QOR_VMD_RETURN_NO_TYPE, the default, does not return the type as part of each
    converted element but just the data. All of the rest return the type and data as the
    two-element tuple. If QOR_VMD_RETURN_TYPE is specified the specific type of the element
    is returned in the tuple. If QOR_VMD_RETURN_TYPE_ARRAY is specified an array type is 
    returned if the element is an array, else a tuple type is returned if the element is a tuple, 
    else the actual type is returned for non-tuple data. If QOR_VMD_RETURN_TYPE_LIST is specified
    a list type is returned if the element is a list, else a tuple type is returned if the element 
    is a tuple, else the actual type is returned for non-tuple data. If QOR_VMD_RETURN_TYPE_TUPLE 
    is specified a tuple type is returned for all tuple-like data, else the actual type is returned 
    for non-tuple data. If more than one return type optional parameter is specified the last one 
    specified determines the return type.
    
    returns   = A Boost PP list. The sequence is empty the Boost PP list is an empty list.
                If an optional return type other than QOR_VMD_RETURN_NO_TYPE
                is specified the type and the data of each element is
                returned as the list element. Otherwise just the data
                is returned as the list element, which is the default.
    
*/

#define QOR_VMD_TO_LIST_D(d,...) \
    QOR_VMD_DETAIL_SEQUENCE_TO_LIST_D(d,__VA_ARGS__) \
/**/

#endif /* QOR_PP_VARIADICS */
#endif /* QOR_VMD_TO_LIST_H */
