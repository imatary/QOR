
//  (C) Copyright Edward Diener 2011-2015
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(QOR_VMD_DETAIL_SEQUENCE_ELEM_H)
#define QOR_VMD_DETAIL_SEQUENCE_ELEM_H

#include "CompilerQOR/Preprocessor/preprocessor/arithmetic/dec.h"
#include "CompilerQOR/Preprocessor/preprocessor/comparison/greater.h"
#include "CompilerQOR/Preprocessor/preprocessor/control/expr_if.h"
#include "CompilerQOR/Preprocessor/preprocessor/control/expr_iif.h"
#include "CompilerQOR/Preprocessor/preprocessor/control/if.h"
#include "CompilerQOR/Preprocessor/preprocessor/control/iif.h"
#include "CompilerQOR/Preprocessor/preprocessor/logical/bitand.h"
#include "CompilerQOR/Preprocessor/preprocessor/logical/bitor.h"
#include "CompilerQOR/Preprocessor/preprocessor/logical/compl.h"
#include "CompilerQOR/Preprocessor/preprocessor/seq/elem.h"
#include "CompilerQOR/Preprocessor/preprocessor/seq/size.h"
#include "CompilerQOR/Preprocessor/preprocessor/tuple/elem.h"
#include "CompilerQOR/Preprocessor/preprocessor/tuple/push_back.h"
#include "CompilerQOR/Preprocessor/preprocessor/tuple/replace.h"
#include "CompilerQOR/Preprocessor/preprocessor/variadic/elem.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/empty.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/identity.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/is_empty.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/is_identifier.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/empty_result.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/equal_type.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/match_identifier.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/mods.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/not_empty.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/only_after.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/sequence_common.h"

/*

    Given modifications and the requested type, 
    determine whether or not we should be checking for specific identifiers
    
    1 = check for specific identifiers
    0 = do no check for specific identifiers

*/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_CHECK_FOR_IDENTIFIERS(nm,type) \
    QOR_PP_BITAND \
        ( \
        QOR_VMD_DETAIL_EQUAL_TYPE \
            ( \
            type, \
            QOR_VMD_TYPE_IDENTIFIER \
            ), \
        QOR_VMD_DETAIL_NOT_EMPTY \
            ( \
            QOR_VMD_DETAIL_MODS_RESULT_OTHER(nm) \
            ) \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_CHECK_FOR_IDENTIFIERS_D(d,nm,type) \
    QOR_PP_BITAND \
        ( \
        QOR_VMD_DETAIL_EQUAL_TYPE_D \
            ( \
            d, \
            type, \
            QOR_VMD_TYPE_IDENTIFIER \
            ), \
        QOR_VMD_DETAIL_NOT_EMPTY \
            ( \
            QOR_VMD_DETAIL_MODS_RESULT_OTHER(nm) \
            ) \
        ) \
/**/

/*

    Given modifications, determine whether or not an index should be part of the result
    
    1 = index should be part of the result
    0 = index should not be part of the result

*/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_IS_INDEX_RESULT(nm) \
    QOR_PP_BITAND \
        ( \
        QOR_VMD_DETAIL_MODS_IS_RESULT_INDEX(nm), \
        QOR_PP_BITAND \
            ( \
            QOR_VMD_DETAIL_EQUAL_TYPE \
                ( \
                QOR_VMD_DETAIL_MODS_RESULT_TYPE(nm), \
                QOR_VMD_TYPE_IDENTIFIER \
                ), \
            QOR_VMD_DETAIL_NOT_EMPTY \
                ( \
                QOR_VMD_DETAIL_MODS_RESULT_OTHER(nm) \
                ) \
            ) \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_IS_INDEX_RESULT_D(d,nm) \
    QOR_PP_BITAND \
        ( \
        QOR_VMD_DETAIL_MODS_IS_RESULT_INDEX(nm), \
        QOR_PP_BITAND \
            ( \
            QOR_VMD_DETAIL_EQUAL_TYPE_D \
                ( \
                d, \
                QOR_VMD_DETAIL_MODS_RESULT_TYPE(nm), \
                QOR_VMD_TYPE_IDENTIFIER \
                ), \
            QOR_VMD_DETAIL_NOT_EMPTY \
                ( \
                QOR_VMD_DETAIL_MODS_RESULT_OTHER(nm) \
                ) \
            ) \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_FAILURE_RESULT_INDEX(nm) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_MODS_IS_RESULT_AFTER(nm), \
        (,,), \
        (,) \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_FAILURE_RESULT_NO_INDEX(nm) \
    QOR_PP_EXPR_IIF \
        ( \
        QOR_VMD_DETAIL_MODS_IS_RESULT_AFTER(nm), \
        (,) \
        ) \
/**/

/*

    Returns a failure result given the modifications

*/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_FAILURE_RESULT(nm) \
    QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_FIN \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_VMD_DETAIL_SEQUENCE_ELEM_IS_INDEX_RESULT(nm), \
            QOR_VMD_DETAIL_SEQUENCE_ELEM_FAILURE_RESULT_INDEX, \
            QOR_VMD_DETAIL_SEQUENCE_ELEM_FAILURE_RESULT_NO_INDEX \
            ) \
        (nm),nm, \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_FAILURE_RESULT_D(d,nm) \
    QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_FIN \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_VMD_DETAIL_SEQUENCE_ELEM_IS_INDEX_RESULT_D(d,nm), \
            QOR_VMD_DETAIL_SEQUENCE_ELEM_FAILURE_RESULT_INDEX, \
            QOR_VMD_DETAIL_SEQUENCE_ELEM_FAILURE_RESULT_NO_INDEX \
            ) \
        (nm),nm, \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_GET_RESULT_TYPE_TUPLE(res) \
    QOR_PP_TUPLE_ELEM \
        ( \
        0, \
        QOR_PP_TUPLE_ELEM(0,res) \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_GET_RESULT_TYPE_ONLY(res) \
    QOR_PP_TUPLE_ELEM(0,res) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_GET_RESULT_DATA_TUPLE(res) \
    QOR_PP_TUPLE_ELEM \
        ( \
        1, \
        QOR_PP_TUPLE_ELEM(0,res) \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_GET_RESULT_DATA_ONLY(res) \
    QOR_PP_TUPLE_ELEM(1,res) \
/**/

/*

  Gets the 'data' of the result given the result and modifications

*/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_GET_RESULT_DATA(res,nm) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_SEQUENCE_STATE_IS_AFTER(nm), \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_GET_RESULT_DATA_TUPLE, \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_GET_RESULT_DATA_ONLY \
        ) \
    (res) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_GET_RESULT_DATA_D(d,res,nm) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_SEQUENCE_STATE_IS_AFTER_D(d,nm), \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_GET_RESULT_DATA_TUPLE, \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_GET_RESULT_DATA_ONLY \
        ) \
    (res) \
/**/

/*

  Gets the 'type' of the result given the result and modifications

*/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_GET_RESULT_TYPE(res,nm) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_SEQUENCE_STATE_IS_AFTER(nm), \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_GET_RESULT_TYPE_TUPLE, \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_GET_RESULT_TYPE_ONLY \
        ) \
    (res) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_GET_RESULT_TYPE_D(d,res,nm) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_SEQUENCE_STATE_IS_AFTER_D(d,nm), \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_GET_RESULT_TYPE_TUPLE, \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_GET_RESULT_TYPE_ONLY \
        ) \
    (res) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_HAS_FAILED_TUPLE(res) \
    QOR_VMD_IS_EMPTY \
        ( \
        QOR_PP_TUPLE_ELEM(0,res) \
        ) \
/**/

/*

    Determines whether the result from the element access has failed or not
    
    returns 1 if it has failed, otherwise 0.

*/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_HAS_FAILED(res,nm) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_SEQUENCE_STATE_IS_AFTER(nm), \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_HAS_FAILED_TUPLE, \
        QOR_VMD_IS_EMPTY \
        ) \
    (res) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_HAS_FAILED_D(d,res,nm) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_SEQUENCE_STATE_IS_AFTER_D(d,nm), \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_HAS_FAILED_TUPLE, \
        QOR_VMD_IS_EMPTY \
        ) \
    (res) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_FSEQ_ONLY_CHELM(seq,elem) \
    QOR_PP_IIF \
        ( \
        QOR_PP_GREATER(QOR_PP_SEQ_SIZE(seq),elem), \
        QOR_PP_SEQ_ELEM, \
        QOR_VMD_EMPTY \
        ) \
    (elem,seq) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_FSEQ_ONLY_CHELM_D(d,seq,elem) \
    QOR_PP_IIF \
        ( \
        QOR_PP_GREATER_D(d,QOR_PP_SEQ_SIZE(seq),elem), \
        QOR_PP_SEQ_ELEM, \
        QOR_VMD_EMPTY \
        ) \
    (elem,seq) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_FSEQ_AFTER_CHELM_RES(data,elem) \
    ( \
    QOR_PP_SEQ_ELEM(elem,QOR_PP_TUPLE_ELEM(0,data)), \
    QOR_PP_TUPLE_ELEM(1,data) \
    ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_FSEQ_AFTER_CHELM(data,elem) \
    QOR_PP_IIF \
        ( \
        QOR_PP_GREATER(QOR_PP_SEQ_SIZE(QOR_PP_TUPLE_ELEM(0,data)),elem), \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_FSEQ_AFTER_CHELM_RES, \
        QOR_VMD_DETAIL_EMPTY_RESULT \
        ) \
    (data,elem) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_FSEQ_AFTER_CHELM_D(d,data,elem) \
    QOR_PP_IIF \
        ( \
        QOR_PP_GREATER_D(d,QOR_PP_SEQ_SIZE(QOR_PP_TUPLE_ELEM(0,data)),elem), \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_FSEQ_AFTER_CHELM_RES, \
        QOR_VMD_DETAIL_EMPTY_RESULT \
        ) \
    (data,elem) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_FSEQ_ONLY(seq,elem) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_IS_EMPTY(seq), \
        QOR_VMD_EMPTY, \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_FSEQ_ONLY_CHELM \
        ) \
    (seq,elem) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_FSEQ_ONLY_D(d,seq,elem) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_IS_EMPTY(seq), \
        QOR_VMD_EMPTY, \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_FSEQ_ONLY_CHELM_D \
        ) \
    (d,seq,elem) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_FSEQ_AFTER(data,elem) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_IS_EMPTY(QOR_PP_TUPLE_ELEM(0,data)), \
        QOR_VMD_DETAIL_EMPTY_RESULT, \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_FSEQ_AFTER_CHELM \
        ) \
    (data,elem) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_FSEQ_AFTER_D(d,data,elem) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_IS_EMPTY(QOR_PP_TUPLE_ELEM(0,data)), \
        QOR_VMD_DETAIL_EMPTY_RESULT, \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_FSEQ_AFTER_CHELM_D \
        ) \
    (d,data,elem) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_FSEQ(seq,elem,nm) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_SEQUENCE_STATE_IS_AFTER(nm), \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_FSEQ_AFTER, \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_FSEQ_ONLY \
        ) \
    (seq,elem) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_FSEQ_D(d,seq,elem,nm) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_SEQUENCE_STATE_IS_AFTER_D(d,nm), \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_FSEQ_AFTER_D, \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_FSEQ_ONLY_D \
        ) \
    (d,seq,elem) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_GET_VSEQ(...) \
    QOR_PP_VARIADIC_ELEM(0,__VA_ARGS__) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PROCESS(elem,vseq,nm) \
    QOR_VMD_DETAIL_SEQUENCE_ELEM_FSEQ \
        ( \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_PROCESS_TUPLE \
            ( \
            vseq, \
            elem, \
            QOR_VMD_TYPE_SEQ, \
            nm \
            ), \
        elem, \
        nm \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PROCESS_D(d,elem,vseq,nm) \
    QOR_VMD_DETAIL_SEQUENCE_ELEM_FSEQ_D \
        ( \
        d, \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_PROCESS_TUPLE_D \
            ( \
            d, \
            vseq, \
            elem, \
            QOR_VMD_TYPE_SEQ, \
            nm \
            ), \
        elem, \
        nm \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_EMPTY(elem,vseq,nm) \
    QOR_PP_EXPR_IIF \
        ( \
        QOR_VMD_DETAIL_SEQUENCE_STATE_IS_AFTER(nm), \
        (,) \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_EMPTY_D(d,elem,vseq,nm) \
    QOR_PP_EXPR_IIF \
        ( \
        QOR_VMD_DETAIL_SEQUENCE_STATE_IS_AFTER_D(d,nm), \
        (,) \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_CE(elem,vseq,nm) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_NOT_EMPTY(vseq), \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PROCESS, \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_EMPTY \
        ) \
    (elem,vseq,nm) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_CE_D(d,elem,vseq,nm) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_NOT_EMPTY(vseq), \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PROCESS_D, \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_EMPTY_D \
        ) \
    (d,elem,vseq,nm) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_FIN_D(d,res,nm,type) \
    QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_FIN(res,nm,type) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_FIN(res,nm,type) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_VMD_DETAIL_MODS_IS_RESULT_ONLY_AFTER(nm), \
            QOR_PP_TUPLE_ELEM, \
            QOR_VMD_IDENTITY(res) \
            ) \
        (1,res) \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PT_INDEX_JRES(data,index) \
    QOR_PP_IF \
        ( \
        index, \
        (data,QOR_PP_DEC(index)), \
        (,) \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PT_JRES(data,index) \
    QOR_PP_EXPR_IF \
        ( \
        index, \
        data \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PT_MATCH(data,nm,index) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_MODS_IS_RESULT_INDEX(nm), \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PT_INDEX_JRES, \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PT_JRES \
        ) \
    (data,index) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PT_CHECK_ONLY_ID_TUP(data,nm) \
    QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PT_MATCH \
        ( \
        data, \
        nm, \
        QOR_VMD_DETAIL_MATCH_IDENTIFIER \
            ( \
            data, \
            QOR_VMD_DETAIL_MODS_RESULT_OTHER(nm) \
            ) \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PT_CHECK_ONLY_ID_TUP_D(d,data,nm) \
    QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PT_MATCH \
        ( \
        data, \
        nm, \
        QOR_VMD_DETAIL_MATCH_IDENTIFIER_D \
            ( \
            d, \
            data, \
            QOR_VMD_DETAIL_MODS_RESULT_OTHER(nm) \
            ) \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PT_CHECK_ONLY_ID(data,nm,type) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_VMD_DETAIL_SEQUENCE_ELEM_CHECK_FOR_IDENTIFIERS(nm,type), \
            QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PT_CHECK_ONLY_ID_TUP,    \
            QOR_VMD_IDENTITY(data) \
            ) \
        (data,nm) \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PT_CHECK_ONLY_ID_D(d,data,nm,type) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_VMD_DETAIL_SEQUENCE_ELEM_CHECK_FOR_IDENTIFIERS_D(d,nm,type), \
            QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PT_CHECK_ONLY_ID_TUP_D,    \
            QOR_VMD_IDENTITY(data) \
            ) \
        (d,data,nm) \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PT_CHECK_ONLY(res,nm,type) \
    QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PT_CHECK_ONLY_ID \
        ( \
        QOR_PP_TUPLE_ELEM(1,res), \
        nm, \
        type \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PT_CHECK_ONLY_D(d,res,nm,type) \
    QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PT_CHECK_ONLY_ID_D \
        ( \
        d, \
        QOR_PP_TUPLE_ELEM(1,res), \
        nm, \
        type \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PT_CHECK_SPLIT_CHANGE(res,nm,type) \
    QOR_PP_TUPLE_REPLACE \
        ( \
        res, \
        0, \
        QOR_PP_TUPLE_ELEM \
            ( \
            1, \
            QOR_PP_TUPLE_ELEM(0,res) \
            ) \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PT_CHECK_SPLIT_CHANGE_D(d,res,nm,type) \
    QOR_PP_TUPLE_REPLACE_D \
        ( \
        d, \
        res, \
        0, \
        QOR_PP_TUPLE_ELEM \
            ( \
            1, \
            QOR_PP_TUPLE_ELEM(0,res) \
            ) \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PT_CHECK_SPLIT_ONLY_CAFTER(res,nm,type) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_MODS_IS_RESULT_ONLY_AFTER(nm), \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_FIN, \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PT_CHECK_SPLIT_CHANGE \
        ) \
    (res,nm,type) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PT_CHECK_SPLIT_ONLY_CAFTER_D(d,res,nm,type) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_MODS_IS_RESULT_ONLY_AFTER(nm), \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_FIN_D, \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PT_CHECK_SPLIT_CHANGE_D \
        ) \
    (d,res,nm,type) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PT_CHECK_SPLIT_SUCCESS(res,nm,type,index) \
    QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PT_CHECK_SPLIT_ONLY_CAFTER \
        ( \
        QOR_PP_TUPLE_PUSH_BACK(res,QOR_PP_DEC(index)), \
        nm, \
        type \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PT_CHECK_SPLIT_SUCCESS_D(d,res,nm,type,index) \
    QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PT_CHECK_SPLIT_ONLY_CAFTER_D \
        ( \
        d, \
        QOR_PP_TUPLE_PUSH_BACK(res,QOR_PP_DEC(index)), \
        nm, \
        type \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PT_CHECK_SPLIT_FAILURE(res,nm,type,index) \
    QOR_VMD_DETAIL_SEQUENCE_ELEM_FAILURE_RESULT(nm) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PT_CHECK_SPLIT_FAILURE_D(d,res,nm,type,index) \
    QOR_VMD_DETAIL_SEQUENCE_ELEM_FAILURE_RESULT_D(d,nm) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PT_CHECK_SPLIT_INDEX_JRES(res,nm,type,index) \
    QOR_PP_IF \
        ( \
        index, \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PT_CHECK_SPLIT_SUCCESS, \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PT_CHECK_SPLIT_FAILURE \
        ) \
    (res,nm,type,index)    \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PT_CHECK_SPLIT_INDEX_JRES_D(d,res,nm,type,index) \
    QOR_PP_IF \
        ( \
        index, \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PT_CHECK_SPLIT_SUCCESS_D, \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PT_CHECK_SPLIT_FAILURE_D \
        ) \
    (d,res,nm,type,index)    \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PT_CHECK_SPLIT_JRES_FAILURE(res,nm,type) \
    QOR_VMD_DETAIL_SEQUENCE_ELEM_FAILURE_RESULT(nm) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PT_CHECK_SPLIT_JRES_FAILURE_D(d,res,nm,type) \
    QOR_VMD_DETAIL_SEQUENCE_ELEM_FAILURE_RESULT_D(d,nm) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PT_CHECK_SPLIT_JRES(res,nm,type,index) \
    QOR_PP_IF \
        ( \
        index, \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PT_CHECK_SPLIT_ONLY_CAFTER, \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PT_CHECK_SPLIT_JRES_FAILURE \
        ) \
    (res,nm,type) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PT_CHECK_SPLIT_JRES_D(d,res,nm,type,index) \
    QOR_PP_IF \
        ( \
        index, \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PT_CHECK_SPLIT_ONLY_CAFTER_D, \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PT_CHECK_SPLIT_JRES_FAILURE_D \
        ) \
    (d,res,nm,type) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PT_CHECK_SPLIT_ID_RES(res,nm,type,index) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_MODS_IS_RESULT_INDEX(nm), \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PT_CHECK_SPLIT_INDEX_JRES, \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PT_CHECK_SPLIT_JRES \
        ) \
    (res,nm,type,index)    \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PT_CHECK_SPLIT_ID_RES_D(d,res,nm,type,index) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_MODS_IS_RESULT_INDEX(nm), \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PT_CHECK_SPLIT_INDEX_JRES_D, \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PT_CHECK_SPLIT_JRES_D \
        ) \
    (d,res,nm,type,index)    \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PT_CHECK_SPLIT_ID(res,nm,type) \
    QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PT_CHECK_SPLIT_ID_RES \
        ( \
        res, \
        nm, \
        type, \
        QOR_VMD_DETAIL_MATCH_IDENTIFIER \
            ( \
            QOR_VMD_DETAIL_SEQUENCE_ELEM_GET_RESULT_DATA(res,nm), \
            QOR_VMD_DETAIL_MODS_RESULT_OTHER(nm) \
            ) \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PT_CHECK_SPLIT_ID_D(d,res,nm,type) \
    QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PT_CHECK_SPLIT_ID_RES_D \
        ( \
        d, \
        res, \
        nm, \
        type, \
        QOR_VMD_DETAIL_MATCH_IDENTIFIER_D \
            ( \
            d, \
            QOR_VMD_DETAIL_SEQUENCE_ELEM_GET_RESULT_DATA_D(d,res,nm), \
            QOR_VMD_DETAIL_MODS_RESULT_OTHER(nm) \
            ) \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PT_CHECK_SPLIT(res,nm,type) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_CHECK_FOR_IDENTIFIERS(nm,type), \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PT_CHECK_SPLIT_ID, \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PT_CHECK_SPLIT_ONLY_CAFTER \
        ) \
    (res,nm,type) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PT_CHECK_SPLIT_D(d,res,nm,type) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_CHECK_FOR_IDENTIFIERS_D(d,nm,type), \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PT_CHECK_SPLIT_ID_D, \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PT_CHECK_SPLIT_ONLY_CAFTER_D \
        ) \
    (d,res,nm,type) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PT_CHECK(res,nm,type) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_SEQUENCE_STATE_IS_AFTER(nm), \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PT_CHECK_SPLIT, \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PT_CHECK_ONLY \
        ) \
    (res,nm,type) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PT_CHECK_D(d,res,nm,type) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_SEQUENCE_STATE_IS_AFTER_D(d,nm), \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PT_CHECK_SPLIT_D, \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PT_CHECK_ONLY_D \
        ) \
    (d,res,nm,type) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PT_FAILED(res,nm,type) \
    QOR_VMD_DETAIL_SEQUENCE_ELEM_FAILURE_RESULT(nm) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PT_FAILED_D(d,res,nm,type) \
    QOR_VMD_DETAIL_SEQUENCE_ELEM_FAILURE_RESULT_D(d,nm) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_MATCHING_TYPE_ID(res,nm,type) \
    QOR_VMD_IS_IDENTIFIER \
        ( \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_GET_RESULT_DATA(res,nm) \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_MATCHING_TYPE_ID_D(d,res,nm,type) \
    QOR_VMD_IS_IDENTIFIER_D \
        ( \
        d, \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_GET_RESULT_DATA_D(d,res,nm) \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_MATCHING_TYPE_OTHER(res,nm,type) \
    QOR_VMD_DETAIL_EQUAL_TYPE \
        ( \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_GET_RESULT_TYPE(res,nm), \
        type \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_MATCHING_TYPE_OTHER_D(d,res,nm,type) \
    QOR_VMD_DETAIL_EQUAL_TYPE_D \
        ( \
        d, \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_GET_RESULT_TYPE_D(d,res,nm), \
        type \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_MATCHING_TYPE(res,nm,type) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_EQUAL_TYPE \
            ( \
            QOR_VMD_TYPE_IDENTIFIER, \
            type \
            ), \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_MATCHING_TYPE_ID, \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_MATCHING_TYPE_OTHER \
        ) \
    (res,nm,type) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_MATCHING_TYPE_D(d,res,nm,type) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_EQUAL_TYPE_D \
            ( \
            d, \
            QOR_VMD_TYPE_IDENTIFIER, \
            type \
            ), \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_MATCHING_TYPE_ID_D, \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_MATCHING_TYPE_OTHER_D \
        ) \
    (d,res,nm,type) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PT(res,nm,type) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_MATCHING_TYPE(res,nm,type), \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PT_CHECK, \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PT_FAILED \
        ) \
    (res,nm,type) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PT_D(d,res,nm,type) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_MATCHING_TYPE_D(d,res,nm,type), \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PT_CHECK_D, \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PT_FAILED_D \
        ) \
    (d,res,nm,type) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_TYPE_NF(res,nm,type) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_IS_EMPTY(type), \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_FIN, \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PT \
        ) \
    (res,nm,type) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_TYPE_NF_D(d,res,nm,type) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_IS_EMPTY(type), \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_FIN_D, \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_PT_D \
        ) \
    (d,res,nm,type) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_TYPE_FAILED(res,nm,type) \
    QOR_VMD_DETAIL_SEQUENCE_ELEM_FAILURE_RESULT(nm) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_TYPE_FAILED_D(d,res,nm,type) \
    QOR_VMD_DETAIL_SEQUENCE_ELEM_FAILURE_RESULT_D(d,nm) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_TYPE(res,nm,type) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_HAS_FAILED(res,nm), \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_TYPE_FAILED, \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_TYPE_NF \
        ) \
    (res,nm,type) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_TYPE_D(d,res,nm,type) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_HAS_FAILED_D(d,res,nm), \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_TYPE_FAILED_D, \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_TYPE_NF_D \
        ) \
    (d,res,nm,type) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_COA(res,nm) \
    QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_TYPE \
        ( \
        res, \
        nm, \
        QOR_VMD_DETAIL_MODS_RESULT_TYPE(nm) \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_COA_D(d,res,nm) \
    QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_TYPE_D \
        ( \
        d, \
        res, \
        nm, \
        QOR_VMD_DETAIL_MODS_RESULT_TYPE(nm) \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_NM(elem,vseq,nm) \
    QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_COA \
        ( \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_CE(elem,vseq,nm), \
        nm \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_D(d,elem,vseq,nm) \
    QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_COA_D \
        ( \
        d, \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_CE_D(d,elem,vseq,nm), \
        nm \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM(allow,elem,...) \
    QOR_VMD_DETAIL_SEQUENCE_ELEM_NM \
        ( \
        elem, \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_GET_VSEQ(__VA_ARGS__), \
        QOR_VMD_DETAIL_NEW_MODS(allow,__VA_ARGS__) \
        ) \
/**/

#define QOR_VMD_DETAIL_SEQUENCE_ELEM_D(d,allow,elem,...) \
    QOR_VMD_DETAIL_SEQUENCE_ELEM_NM_D \
        ( \
        d, \
        elem, \
        QOR_VMD_DETAIL_SEQUENCE_ELEM_GET_VSEQ(__VA_ARGS__), \
        QOR_VMD_DETAIL_NEW_MODS_D(d,allow,__VA_ARGS__) \
        ) \
/**/

#endif /* QOR_VMD_DETAIL_SEQUENCE_ELEM_H */
