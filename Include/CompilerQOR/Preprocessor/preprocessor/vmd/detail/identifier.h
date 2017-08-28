
//  (C) Copyright Edward Diener 2011-2015
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).

#if !defined(QOR_VMD_DETAIL_IDENTIFIER_H)
#define QOR_VMD_DETAIL_IDENTIFIER_H

#include "CompilerQOR/Preprocessor/preprocessor/arithmetic/dec.h"
#include "CompilerQOR/Preprocessor/preprocessor/comparison/equal.h"
#include "CompilerQOR/Preprocessor/preprocessor/control/expr_iif.h"
#include "CompilerQOR/Preprocessor/preprocessor/control/iif.h"
#include "CompilerQOR/Preprocessor/preprocessor/logical/bitand.h"
#include "CompilerQOR/Preprocessor/preprocessor/logical/bitor.h"
#include "CompilerQOR/Preprocessor/preprocessor/punctuation/is_begin_parens.h"
#include "CompilerQOR/Preprocessor/preprocessor/tuple/elem.h"
#include "CompilerQOR/Preprocessor/preprocessor/variadic/elem.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/identity.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/is_empty.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/identifier_concat.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/is_entire.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/match_identifier.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/mods.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/not_empty.h"
#include "CompilerQOR/Preprocessor/preprocessor/vmd/detail/parens.h"

#define QOR_VMD_DETAIL_IDENTIFIER_PROCESS_KEYS_SUCCESS(id,rest,keymatch,mods) \
    QOR_VMD_DETAIL_IDENTIFIER_SUCCESS_MODS(id,rest,QOR_PP_DEC(keymatch),mods) \
/**/

#define QOR_VMD_DETAIL_IDENTIFIER_PROCESS_KEYS_FAILURE(id,rest,keymatch,mods) \
    QOR_VMD_DETAIL_IDENTIFIER_FAILURE_MODS(mods) \
/**/

#define QOR_VMD_DETAIL_IDENTIFIER_PROCESS_KEYS_TUPLE_RESULT(id,rest,keymatch,mods) \
    QOR_PP_IIF \
        ( \
        QOR_PP_EQUAL(keymatch,0), \
        QOR_VMD_DETAIL_IDENTIFIER_PROCESS_KEYS_FAILURE, \
        QOR_VMD_DETAIL_IDENTIFIER_PROCESS_KEYS_SUCCESS \
        ) \
    (id,rest,keymatch,mods) \
/**/

#define QOR_VMD_DETAIL_IDENTIFIER_PROCESS_KEYS_TUPLE_RESULT_D(d,id,rest,keymatch,mods) \
    QOR_PP_IIF \
        ( \
        QOR_PP_EQUAL_D(d,keymatch,0), \
        QOR_VMD_DETAIL_IDENTIFIER_PROCESS_KEYS_FAILURE, \
        QOR_VMD_DETAIL_IDENTIFIER_PROCESS_KEYS_SUCCESS \
        ) \
    (id,rest,keymatch,mods) \
/**/

#define QOR_VMD_DETAIL_IDENTIFIER_PROCESS_KEYS_TUPLE(id,rest,keytuple,mods) \
    QOR_VMD_DETAIL_IDENTIFIER_PROCESS_KEYS_TUPLE_RESULT \
        ( \
        id, \
        rest, \
        QOR_VMD_DETAIL_MATCH_IDENTIFIER(id,keytuple), \
        mods \
        ) \
/**/

#define QOR_VMD_DETAIL_IDENTIFIER_PROCESS_KEYS_TUPLE_D(d,id,rest,keytuple,mods) \
    QOR_VMD_DETAIL_IDENTIFIER_PROCESS_KEYS_TUPLE_RESULT_D \
        ( \
        d, \
        id, \
        rest, \
        QOR_VMD_DETAIL_MATCH_IDENTIFIER_D(d,id,keytuple), \
        mods \
        ) \
/**/

#define QOR_VMD_DETAIL_IDENTIFIER_MAKE_SPLIT(tuple) \
    ( \
    QOR_PP_TUPLE_ELEM \
        ( \
        0, \
        QOR_PP_TUPLE_ELEM(0,tuple) \
        ), \
    QOR_PP_TUPLE_ELEM(1,tuple) \
    ) \
/**/

#define QOR_VMD_DETAIL_IDENTIFIER_SPLIT_SEQUENCE_CONCAT_DATA(tuple) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_VMD_IS_EMPTY \
                ( \
                QOR_PP_TUPLE_ELEM(0,tuple) \
                ), \
            QOR_VMD_IDENTITY(tuple), \
            QOR_VMD_DETAIL_IDENTIFIER_MAKE_SPLIT \
            ) \
        (tuple) \
        ) \
/**/

#define QOR_VMD_DETAIL_IDENTIFIER_SPLIT_SEQUENCE_CONCAT(vcseq) \
    QOR_VMD_DETAIL_IDENTIFIER_SPLIT_SEQUENCE_CONCAT_DATA \
        ( \
        QOR_VMD_DETAIL_PARENS(vcseq,QOR_VMD_RETURN_AFTER) \
        ) \
/**/

#define QOR_VMD_DETAIL_IDENTIFIER_GETID_TID(tid) \
    QOR_VMD_IDENTITY_RESULT \
        ( \
        QOR_PP_IIF \
            ( \
            QOR_VMD_IS_EMPTY(tid), \
            QOR_VMD_IDENTITY(tid), \
            QOR_PP_TUPLE_ELEM \
            ) \
        (0,tid) \
        ) \
/**/

#define QOR_VMD_DETAIL_IDENTIFIER_GETID_SEQUENCE(vseq) \
    QOR_VMD_DETAIL_IDENTIFIER_GETID_TID \
        ( \
        QOR_VMD_DETAIL_PARENS(QOR_VMD_DETAIL_IDENTIFIER_CONCATENATE(vseq)) \
        ) \
/**/

#define QOR_VMD_DETAIL_IDENTIFIER_SPLIT_SEQUENCE(vseq) \
     QOR_VMD_DETAIL_IDENTIFIER_SPLIT_SEQUENCE_CONCAT \
        ( \
        QOR_VMD_DETAIL_IDENTIFIER_CONCATENATE(vseq) \
        ) \
/**/

#define QOR_VMD_DETAIL_IDENTIFIER_PROCESS_KEYS(id,rest,mods) \
    QOR_VMD_DETAIL_IDENTIFIER_PROCESS_KEYS_TUPLE \
        ( \
        id, \
        rest, \
        QOR_VMD_DETAIL_MODS_RESULT_OTHER(mods), \
        mods \
        ) \
/**/

#define QOR_VMD_DETAIL_IDENTIFIER_PROCESS_KEYS_D(d,id,rest,mods) \
    QOR_VMD_DETAIL_IDENTIFIER_PROCESS_KEYS_TUPLE_D \
        ( \
        d, \
        id, \
        rest, \
        QOR_VMD_DETAIL_MODS_RESULT_OTHER(mods), \
        mods \
        ) \
/**/

#define QOR_VMD_DETAIL_IDENTIFIER_JUST(id,rest,mods) \
    QOR_VMD_DETAIL_IDENTIFIER_SUCCESS_MODS(id,rest,0,mods) \
/**/

#define QOR_VMD_DETAIL_IDENTIFIER_JUST_D(d,id,rest,mods) \
    QOR_VMD_DETAIL_IDENTIFIER_SUCCESS_MODS(id,rest,0,mods) \
/**/

#define QOR_VMD_DETAIL_IDENTIFIER_CHECK_KEYS(id,rest,mods) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_IS_EMPTY \
            ( \
            QOR_VMD_DETAIL_MODS_RESULT_OTHER(mods) \
            ), \
        QOR_VMD_DETAIL_IDENTIFIER_JUST, \
        QOR_VMD_DETAIL_IDENTIFIER_PROCESS_KEYS \
        ) \
    (id,rest,mods) \
/**/

#define QOR_VMD_DETAIL_IDENTIFIER_CHECK_KEYS_D(d,id,rest,mods) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_IS_EMPTY \
            ( \
            QOR_VMD_DETAIL_MODS_RESULT_OTHER(mods) \
            ), \
        QOR_VMD_DETAIL_IDENTIFIER_JUST_D, \
        QOR_VMD_DETAIL_IDENTIFIER_PROCESS_KEYS_D \
        ) \
    (d,id,rest,mods) \
/**/

#define QOR_VMD_DETAIL_IDENTIFIER_MKEYS(mods) \
    QOR_PP_BITAND \
        ( \
        QOR_VMD_DETAIL_MODS_IS_RESULT_INDEX(mods), \
        QOR_VMD_DETAIL_NOT_EMPTY \
            ( \
            QOR_VMD_DETAIL_MODS_RESULT_OTHER(mods) \
            ) \
        ) \
/**/

#define QOR_VMD_DETAIL_IDENTIFIER_SUCCESS_MODS(id,rest,keymatch,mods) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_IDENTIFIER_MKEYS(mods), \
        QOR_PP_IIF \
            ( \
            QOR_VMD_DETAIL_MODS_IS_RESULT_AFTER(mods), \
            (id,rest,keymatch), \
            (id,keymatch) \
            ), \
        QOR_PP_IIF \
            ( \
            QOR_VMD_DETAIL_MODS_IS_RESULT_AFTER(mods), \
            (id,rest), \
            id \
            ) \
        ) \
/**/

#define QOR_VMD_DETAIL_IDENTIFIER_FAILURE_MODS(mods) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_IDENTIFIER_MKEYS(mods), \
        QOR_PP_IIF \
            ( \
            QOR_VMD_DETAIL_MODS_IS_RESULT_AFTER(mods), \
            (,,), \
            (,) \
            ), \
        QOR_PP_EXPR_IIF \
            ( \
            QOR_VMD_DETAIL_MODS_IS_RESULT_AFTER(mods), \
            (,) \
            ) \
        ) \
/**/

#define QOR_VMD_DETAIL_IDENTIFIER_FAILURE_REST(id,rest,mods) \
    QOR_VMD_DETAIL_IDENTIFIER_FAILURE_MODS(mods) \
/**/

#define QOR_VMD_DETAIL_IDENTIFIER_FAILURE_REST_D(d,id,rest,mods) \
    QOR_VMD_DETAIL_IDENTIFIER_FAILURE_MODS(mods) \
/**/

#define QOR_VMD_DETAIL_IDENTIFIER_ID_REST(id,rest,mods) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_IS_EMPTY(id), \
        QOR_VMD_DETAIL_IDENTIFIER_FAILURE_REST, \
        QOR_VMD_DETAIL_IDENTIFIER_CHECK_KEYS \
        ) \
    (id,rest,mods) \
/**/

#define QOR_VMD_DETAIL_IDENTIFIER_ID_REST_D(d,id,rest,mods) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_IS_EMPTY(id), \
        QOR_VMD_DETAIL_IDENTIFIER_FAILURE_REST_D, \
        QOR_VMD_DETAIL_IDENTIFIER_CHECK_KEYS_D \
        ) \
    (d,id,rest,mods) \
/**/

#define QOR_VMD_DETAIL_IDENTIFIER_PROCESS_DATA(tuple,mods) \
    QOR_VMD_DETAIL_IDENTIFIER_ID_REST \
        ( \
        QOR_PP_TUPLE_ELEM(0,tuple), \
        QOR_PP_TUPLE_ELEM(1,tuple), \
        mods \
        ) \
/**/

#define QOR_VMD_DETAIL_IDENTIFIER_PROCESS_ID(id,mods) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_IS_EMPTY(id), \
        QOR_VMD_DETAIL_IDENTIFIER_FAILURE_REST, \
        QOR_VMD_DETAIL_IDENTIFIER_CHECK_KEYS \
        ) \
    (id,,mods) \
/**/

#define QOR_VMD_DETAIL_IDENTIFIER_PROCESS_ID_D(d,id,mods) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_IS_EMPTY(id), \
        QOR_VMD_DETAIL_IDENTIFIER_FAILURE_REST_D, \
        QOR_VMD_DETAIL_IDENTIFIER_CHECK_KEYS_D \
        ) \
    (d,id,,mods) \
/**/

#define QOR_VMD_DETAIL_IDENTIFIER_PROCESS_DATA_D(d,tuple,mods) \
    QOR_VMD_DETAIL_IDENTIFIER_ID_REST_D \
        ( \
        d, \
        QOR_PP_TUPLE_ELEM(0,tuple), \
        QOR_PP_TUPLE_ELEM(1,tuple), \
        mods \
        ) \
/**/

#define QOR_VMD_DETAIL_IDENTIFIER_SEQUENCE_AFTER(vseq,mods) \
    QOR_VMD_DETAIL_IDENTIFIER_PROCESS_DATA \
        ( \
        QOR_VMD_DETAIL_IDENTIFIER_SPLIT_SEQUENCE(vseq), \
        mods \
        ) \
/**/

#define QOR_VMD_DETAIL_IDENTIFIER_SEQUENCE_AFTER_D(d,vseq,mods) \
    QOR_VMD_DETAIL_IDENTIFIER_PROCESS_DATA_D \
        ( \
        d, \
        QOR_VMD_DETAIL_IDENTIFIER_SPLIT_SEQUENCE(vseq), \
        mods \
        ) \
/**/

#define QOR_VMD_DETAIL_IDENTIFIER_SEQUENCE_ID(vseq,mods) \
    QOR_VMD_DETAIL_IDENTIFIER_PROCESS_ID \
        ( \
        QOR_VMD_DETAIL_IDENTIFIER_GETID_SEQUENCE(vseq), \
        mods \
        ) \
/**/

#define QOR_VMD_DETAIL_IDENTIFIER_SEQUENCE_ID_D(d,vseq,mods) \
    QOR_VMD_DETAIL_IDENTIFIER_PROCESS_ID_D \
        ( \
        d, \
        QOR_VMD_DETAIL_IDENTIFIER_GETID_SEQUENCE(vseq), \
        mods \
        ) \
/**/

#define QOR_VMD_DETAIL_IDENTIFIER_SEQUENCE(vseq,mods) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_MODS_IS_RESULT_AFTER(mods), \
        QOR_VMD_DETAIL_IDENTIFIER_SEQUENCE_AFTER, \
        QOR_VMD_DETAIL_IDENTIFIER_SEQUENCE_ID \
        ) \
    (vseq,mods) \
/**/

#define QOR_VMD_DETAIL_IDENTIFIER_SEQUENCE_D(d,vseq,mods) \
    QOR_PP_IIF \
        ( \
        QOR_VMD_DETAIL_MODS_IS_RESULT_AFTER(mods), \
        QOR_VMD_DETAIL_IDENTIFIER_SEQUENCE_AFTER_D, \
        QOR_VMD_DETAIL_IDENTIFIER_SEQUENCE_ID_D \
        ) \
    (d,vseq,mods) \
/**/

#define QOR_VMD_DETAIL_IDENTIFIER_EX_FAILURE(vseq,mods) \
    QOR_VMD_DETAIL_IDENTIFIER_FAILURE_MODS(mods) \
/**/

#define QOR_VMD_DETAIL_IDENTIFIER_EX_FAILURE_D(d,vseq,mods) \
    QOR_VMD_DETAIL_IDENTIFIER_FAILURE_MODS(mods) \
/**/

#define QOR_VMD_DETAIL_IDENTIFIER_EX(vseq,mods) \
    QOR_PP_IIF \
      ( \
      QOR_PP_BITOR \
          ( \
          QOR_VMD_IS_EMPTY(vseq), \
          QOR_PP_IS_BEGIN_PARENS(vseq) \
          ), \
      QOR_VMD_DETAIL_IDENTIFIER_EX_FAILURE, \
      QOR_VMD_DETAIL_IDENTIFIER_SEQUENCE \
      ) \
    (vseq,mods) \
/**/

#define QOR_VMD_DETAIL_IDENTIFIER_EX_D(d,vseq,mods) \
    QOR_PP_IIF \
      ( \
      QOR_PP_BITOR \
          ( \
          QOR_VMD_IS_EMPTY(vseq), \
          QOR_PP_IS_BEGIN_PARENS(vseq) \
          ), \
      QOR_VMD_DETAIL_IDENTIFIER_EX_FAILURE_D, \
      QOR_VMD_DETAIL_IDENTIFIER_SEQUENCE_D \
      ) \
    (d,vseq,mods) \
/**/

#define QOR_VMD_DETAIL_IDENTIFIER(...) \
    QOR_VMD_DETAIL_IDENTIFIER_EX \
        ( \
        QOR_PP_VARIADIC_ELEM(0,__VA_ARGS__), \
        QOR_VMD_DETAIL_NEW_MODS(QOR_VMD_ALLOW_INDEX,__VA_ARGS__) \
        ) \
/**/

#define QOR_VMD_DETAIL_IDENTIFIER_D(d,...) \
    QOR_VMD_DETAIL_IDENTIFIER_EX_D \
        ( \
        d, \
        QOR_PP_VARIADIC_ELEM(0,__VA_ARGS__), \
        QOR_VMD_DETAIL_NEW_MODS_D(d,QOR_VMD_ALLOW_INDEX,__VA_ARGS__) \
        ) \
/**/

#define QOR_VMD_DETAIL_IS_IDENTIFIER_MULTIPLE(...) \
    QOR_VMD_DETAIL_IS_ENTIRE \
        ( \
        QOR_VMD_DETAIL_IDENTIFIER(__VA_ARGS__,QOR_VMD_RETURN_AFTER) \
        ) \
/**/

#define QOR_VMD_DETAIL_IS_IDENTIFIER_MULTIPLE_D(d,...) \
    QOR_VMD_DETAIL_IS_ENTIRE \
        ( \
        QOR_VMD_DETAIL_IDENTIFIER_D(d,__VA_ARGS__,QOR_VMD_RETURN_AFTER) \
        ) \
/**/

#endif /* QOR_VMD_DETAIL_IDENTIFIER_H */
