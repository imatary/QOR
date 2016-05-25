//trace.cpp

// Copyright Querysoft Limited 2013
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
//
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

//Generic trace implementation
//An exported standard C interface which forwards calls to the matching C++ implementaion for the platform

#include "CQOR/CQORPolicy.h"
#include <trace.h>
#include <errno.h>
#include "SystemQOR.h"
#include QOR_SYS_PLATFORMHEADER(trace.h)
#include "CodeQOR/Tracing/FunctionContextBase.h"
#include "CodeQOR/ErrorSystem/Error.h"
#include "CQOR.h"

//--------------------------------------------------------------------------------
namespace
{
	nsPlatform::Ctrace _trace;
}//anonymous

__QCMP_STARTLINKAGE_C

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int posix_trace_attr_destroy( ::trace_attr_t* pAttr )
{
    __QCS_FCONTEXT( "posix_trace_attr_destroy" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _trace.posix_trace_attr_destroy( pAttr );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int posix_trace_attr_getclockres( const ::trace_attr_t* pAttr, ::timespec* pResolution )
{
    __QCS_FCONTEXT( "posix_trace_attr_getclockres" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _trace.posix_trace_attr_getclockres( pAttr, pResolution );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int posix_trace_attr_getcreatetime( const ::trace_attr_t* pAttr, ::timespec* pCreateTime )
{
    __QCS_FCONTEXT( "posix_trace_attr_getcreatetime" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _trace.posix_trace_attr_getcreatetime( pAttr, pCreateTime );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int posix_trace_attr_getgenversion( const ::trace_attr_t* pAttr, char* szGenVersion )
{
    __QCS_FCONTEXT( "posix_trace_attr_getgenversion" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _trace.posix_trace_attr_getgenversion( pAttr, szGenVersion );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int posix_trace_attr_getinherited( const ::trace_attr_t* __QCMP_RESTRICT pAttr, int* __QCMP_RESTRICT inheritancepolicy )
{
    __QCS_FCONTEXT( "posix_trace_attr_getinherited" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _trace.posix_trace_attr_getinherited( pAttr, inheritancepolicy );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int posix_trace_attr_getlogfullpolicy( const ::trace_attr_t* __QCMP_RESTRICT pAttr, int* __QCMP_RESTRICT logpolicy )
{
    __QCS_FCONTEXT( "posix_trace_attr_getlogfullpolicy" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _trace.posix_trace_attr_getlogfullpolicy( pAttr, logpolicy );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int posix_trace_attr_getlogsize( const ::trace_attr_t* __QCMP_RESTRICT pAttr, size_t* __QCMP_RESTRICT logsize )
{
    __QCS_FCONTEXT( "posix_trace_attr_getlogsize" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _trace.posix_trace_attr_getlogsize( pAttr, logsize );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int posix_trace_attr_getmaxdatasize( const ::trace_attr_t* __QCMP_RESTRICT pAttr, size_t* __QCMP_RESTRICT pMaxDataSize )
{
    __QCS_FCONTEXT( "posix_trace_attr_getmaxdatasize" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _trace.posix_trace_attr_getmaxdatasize( pAttr, pMaxDataSize );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int posix_trace_attr_getmaxsystemeventsize( const ::trace_attr_t* __QCMP_RESTRICT pAttr, size_t* __QCMP_RESTRICT pEventSize )
{
    __QCS_FCONTEXT( "posix_trace_attr_getmaxsystemeventsize" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _trace.posix_trace_attr_getmaxsystemeventsize( pAttr, pEventSize );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int posix_trace_attr_getmaxusereventsize( const ::trace_attr_t* __QCMP_RESTRICT pAttr, size_t DataLen, size_t* __QCMP_RESTRICT pEventSize )
{
    __QCS_FCONTEXT( "posix_trace_attr_getmaxusereventsize" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _trace.posix_trace_attr_getmaxusereventsize( pAttr, DataLen, pEventSize );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int posix_trace_attr_getname( const ::trace_attr_t* pAttr, char* szTraceName )
{
    __QCS_FCONTEXT( "posix_trace_attr_getname" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _trace.posix_trace_attr_getname( pAttr, szTraceName );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int posix_trace_attr_getstreamfullpolicy( const ::trace_attr_t* __QCMP_RESTRICT pAttr, int* __QCMP_RESTRICT pStreamPolicy )
{
    __QCS_FCONTEXT( "posix_trace_attr_getstreamfullpolicy" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _trace.posix_trace_attr_getstreamfullpolicy( pAttr, pStreamPolicy );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int posix_trace_attr_getstreamsize( const ::trace_attr_t* __QCMP_RESTRICT pAttr, size_t* __QCMP_RESTRICT pStreamSize )
{
    __QCS_FCONTEXT( "posix_trace_attr_getstreamsize" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _trace.posix_trace_attr_getstreamsize( pAttr, pStreamSize );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int posix_trace_attr_init( ::trace_attr_t* pAttr )
{
    __QCS_FCONTEXT( "posix_trace_attr_init" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _trace.posix_trace_attr_init( pAttr );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int posix_trace_attr_setinherited( ::trace_attr_t* pAttr, int inheritancepolicy )
{
    __QCS_FCONTEXT( "posix_trace_attr_setinherited" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _trace.posix_trace_attr_setinherited( pAttr, inheritancepolicy );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int posix_trace_attr_setlogfullpolicy( ::trace_attr_t* pAttr, int logpolicy )
{
    __QCS_FCONTEXT( "posix_trace_attr_setlogfullpolicy" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _trace.posix_trace_attr_setlogfullpolicy( pAttr, logpolicy );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int posix_trace_attr_setlogsize( ::trace_attr_t* pAttr, size_t logsize )
{
    __QCS_FCONTEXT( "posix_trace_attr_setlogsize" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _trace.posix_trace_attr_setlogsize( pAttr, logsize );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int posix_trace_attr_setmaxdatasize( ::trace_attr_t* pAttr, size_t MaxDataSize )
{
    __QCS_FCONTEXT( "posix_trace_attr_setmaxdatasize" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _trace.posix_trace_attr_setmaxdatasize( pAttr, MaxDataSize );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int posix_trace_attr_setname( ::trace_attr_t* pAttr, const char* szName )
{
    __QCS_FCONTEXT( "posix_trace_attr_setname" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _trace.posix_trace_attr_setname( pAttr, szName );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int posix_trace_attr_setstreamfullpolicy( ::trace_attr_t* pAttr, int fullpolicy )
{
    __QCS_FCONTEXT( "posix_trace_attr_setstreamfullpolicy" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _trace.posix_trace_attr_setstreamfullpolicy( pAttr, fullpolicy );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int posix_trace_attr_setstreamsize( ::trace_attr_t* pAttr, size_t StreamSize )
{
    __QCS_FCONTEXT( "posix_trace_attr_setstreamsize" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _trace.posix_trace_attr_setstreamsize( pAttr, StreamSize );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int posix_trace_clear( ::trace_id_t trid )
{
    __QCS_FCONTEXT( "posix_trace_clear" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _trace.posix_trace_clear( trid );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int posix_trace_close( ::trace_id_t trid )
{
    __QCS_FCONTEXT( "posix_trace_close" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _trace.posix_trace_close( trid );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int posix_trace_create( ::pid_t pid, const ::trace_attr_t* __QCMP_RESTRICT pAttr, ::trace_id_t* __QCMP_RESTRICT ptrid )
{
    __QCS_FCONTEXT( "posix_trace_create" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _trace.posix_trace_create( pid, pAttr, ptrid );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int posix_trace_create_withlog( ::pid_t pid, const ::trace_attr_t* __QCMP_RESTRICT pAttr, int fd, ::trace_id_t* __QCMP_RESTRICT ptrid )
{
    __QCS_FCONTEXT( "posix_trace_create_withlog" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _trace.posix_trace_create_withlog( pid, pAttr, fd, ptrid );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) void posix_trace_event( ::trace_event_id_t EventID, const void* __QCMP_RESTRICT pData, size_t DataLen )
{
    __QCS_FCONTEXT( "posix_trace_event" );

    __QCS_PROTECT
    {
        _trace.posix_trace_event( EventID, pData, DataLen );
    }__QCS_ENDPROTECT
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int posix_trace_eventid_equal( ::trace_id_t trid, ::trace_event_id_t event1, ::trace_event_id_t event2 )
{
    __QCS_FCONTEXT( "posix_trace_eventid_equal" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _trace.posix_trace_eventid_equal( trid, event1, event2 );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int posix_trace_eventid_get_name( ::trace_id_t trid, ::trace_event_id_t event1, char* szName )
{
    __QCS_FCONTEXT( "posix_trace_eventid_get_name" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _trace.posix_trace_eventid_get_name( trid, event1, szName );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int posix_trace_eventid_open( const char* __QCMP_RESTRICT szEventName, ::trace_event_id_t* __QCMP_RESTRICT pEventID )
{
    __QCS_FCONTEXT( "posix_trace_eventid_open" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _trace.posix_trace_eventid_open( szEventName, pEventID );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int posix_trace_eventset_add( ::trace_event_id_t pEventID, ::trace_event_set_t* pSet )
{
    __QCS_FCONTEXT( "posix_trace_eventset_add" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _trace.posix_trace_eventset_add( pEventID, pSet );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int posix_trace_eventset_del( ::trace_event_id_t pEventID, ::trace_event_set_t* pSet )
{
    __QCS_FCONTEXT( "posix_trace_eventset_del" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _trace.posix_trace_eventset_del( pEventID, pSet );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int posix_trace_eventset_empty( ::trace_event_set_t* pSet )
{
    __QCS_FCONTEXT( "posix_trace_eventset_empty" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _trace.posix_trace_eventset_empty( pSet );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int posix_trace_eventset_fill( ::trace_event_set_t* pSet, int iWhat )
{
    __QCS_FCONTEXT( "posix_trace_eventset_fill" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _trace.posix_trace_eventset_fill( pSet, iWhat );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int posix_trace_eventset_ismember( ::trace_event_id_t EventID, const ::trace_event_set_t* __QCMP_RESTRICT pSet, int* __QCMP_RESTRICT pIsMember )
{
    __QCS_FCONTEXT( "posix_trace_eventset_ismember" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _trace.posix_trace_eventset_ismember( EventID, pSet, pIsMember );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int posix_trace_eventtypelist_getnext_id( ::trace_id_t trid, ::trace_event_id_t* __QCMP_RESTRICT pEvent, int* __QCMP_RESTRICT pUnavailable )
{
    __QCS_FCONTEXT( "posix_trace_eventtypelist_getnext_id" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _trace.posix_trace_eventtypelist_getnext_id( trid, pEvent, pUnavailable );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int posix_trace_eventtypelist_rewind( ::trace_id_t trid )
{
    __QCS_FCONTEXT( "posix_trace_eventtypelist_rewind" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _trace.posix_trace_eventtypelist_rewind( trid );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int posix_trace_flush( ::trace_id_t trid )
{
    __QCS_FCONTEXT( "posix_trace_flush" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _trace.posix_trace_flush( trid );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int posix_trace_get_attr( ::trace_id_t trid, ::trace_attr_t* pAttr )
{
    __QCS_FCONTEXT( "posix_trace_get_attr" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _trace.posix_trace_get_attr( trid, pAttr );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int posix_trace_get_filter( ::trace_id_t trid, ::trace_event_set_t* pSet )
{
    __QCS_FCONTEXT( "posix_trace_get_filter" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _trace.posix_trace_get_filter( trid, pSet );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int posix_trace_get_status( ::trace_id_t trid, ::posix_trace_status_info* pStatusInfo )
{
    __QCS_FCONTEXT( "posix_trace_get_status" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _trace.posix_trace_get_status( trid, pStatusInfo );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int posix_trace_getnext_event( ::trace_id_t trid, ::posix_trace_event_info* __QCMP_RESTRICT pEvent, void* __QCMP_RESTRICT pData, size_t NumBytes, size_t* __QCMP_RESTRICT pDataLen, int* __QCMP_RESTRICT pUnavailable )
{
    __QCS_FCONTEXT( "posix_trace_getnext_event" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _trace.posix_trace_getnext_event( trid, pEvent, pData, NumBytes, pDataLen, pUnavailable );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int posix_trace_open( int fd, ::trace_id_t* ptrid )
{
    __QCS_FCONTEXT( "posix_trace_open" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _trace.posix_trace_open( fd, ptrid );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int posix_trace_rewind( ::trace_id_t trid )
{
    __QCS_FCONTEXT( "posix_trace_rewind" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _trace.posix_trace_rewind( trid );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int posix_trace_set_filter( ::trace_id_t trid, const ::trace_event_set_t* pSet, int iHow )
{
    __QCS_FCONTEXT( "posix_trace_set_filter" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _trace.posix_trace_set_filter( trid, pSet, iHow );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int posix_trace_shutdown( ::trace_id_t trid )
{
    __QCS_FCONTEXT( "posix_trace_shutdown" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _trace.posix_trace_shutdown( trid );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int posix_trace_start( ::trace_id_t trid )
{
    __QCS_FCONTEXT( "posix_trace_start" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _trace.posix_trace_start( trid );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int posix_trace_stop( ::trace_id_t trid )
{
    __QCS_FCONTEXT( "posix_trace_stop" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _trace.posix_trace_stop( trid );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int posix_trace_timedgetnext_event( ::trace_id_t trid, ::posix_trace_event_info* __QCMP_RESTRICT pEvent, void* __QCMP_RESTRICT pData, size_t NumBytes, size_t* __QCMP_RESTRICT pDataLen, int* __QCMP_RESTRICT pUnavailable, const ::timespec* __QCMP_RESTRICT pAbsTime )
{
    __QCS_FCONTEXT( "posix_trace_timedgetnext_event" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _trace.posix_trace_timedgetnext_event( trid, pEvent, pData, NumBytes, pDataLen, pUnavailable, pAbsTime );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int posix_trace_trid_eventid_open( ::trace_id_t trid, const char* __QCMP_RESTRICT szEventName, ::trace_event_id_t* __QCMP_RESTRICT pEvent )
{
    __QCS_FCONTEXT( "posix_trace_trid_eventid_open" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _trace.posix_trace_trid_eventid_open( trid, szEventName, pEvent );
    }__QCS_ENDPROTECT
    return iResult;
}

//--------------------------------------------------------------------------------
__QOR_INTERFACE( __CQOR ) int posix_trace_trygetnext_event( ::trace_id_t trid, ::posix_trace_event_info* __QCMP_RESTRICT pEvent, void* __QCMP_RESTRICT pData, size_t NumBytes, size_t* __QCMP_RESTRICT pDataLen, int* __QCMP_RESTRICT pUnavailable )
{
    __QCS_FCONTEXT( "posix_trace_trygetnext_event" );

    int iResult = 0;
    __QCS_PROTECT
    {
        iResult = _trace.posix_trace_trygetnext_event( trid, pEvent, pData, NumBytes, pDataLen, pUnavailable );
    }__QCS_ENDPROTECT
    return iResult;
}

__QCMP_ENDLINKAGE_C

