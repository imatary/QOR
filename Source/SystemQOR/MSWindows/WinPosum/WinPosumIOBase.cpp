
#include "WinPosum/WinPosumStream.h"
#include "WinPosum/WinPosumStreamImpl.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define _IOB_ENTRIES    20

// Lock symbols

#define _SIGNAL_LOCK    0       // lock for signal()                
#define _IOB_SCAN_LOCK  1       // _iob[] table lock                
#define _TMPNAM_LOCK    2       // lock global tempnam variables    
#define _CONIO_LOCK     3       // lock for conio routines          
#define _HEAP_LOCK      4       // lock for heap allocator routines 
#define _UNDNAME_LOCK   5       // lock for unDName() routine       
#define _TIME_LOCK      6       // lock for time functions          
#define _ENV_LOCK       7       // lock for environment variables   
#define _EXIT_LOCK1     8       // lock #1 for exit code            
#define _POPEN_LOCK     9       // lock for _popen/_pclose database 
#define _LOCKTAB_LOCK   10      // lock to protect semaphore lock table
#define _OSFHND_LOCK    11      // lock to protect _osfhnd array    
#define _SETLOCALE_LOCK 12      // lock for locale handles, etc.    
#define _MB_CP_LOCK     13      // lock for multibyte code page     
#define _TYPEINFO_LOCK  14      // lock for type_info access        
#define _DEBUG_LOCK     15      // lock for debug global structs    
#define _STREAM_LOCKS   16      // Table of stream locks            
#define _LAST_STREAM_LOCK  (_STREAM_LOCKS+_IOB_ENTRIES-1) // Last stream lock
#define _TOTAL_LOCKS        (_LAST_STREAM_LOCK+1)
#define _LOCK_BIT_INTS     (_TOTAL_LOCKS/(sizeof(unsigned)*8))+1   // # of ints to hold lock bits

#define _CRT_SPINCOUNT  4000
#define _INTERNAL_BUFSIZ    4096

#define _RT_STDIOINIT                   26
#define _RT_CRT_NOTINIT                 30
#define _RT_LOCK                        17

//------------------------------------------------------------------------------
namespace nsWin32
{



	//FILE descriptors; preset for stdin/out/err (note that the __tmpnum field is not initialized)


	char _bufin[ _INTERNAL_BUFSIZ ];

	//------------------------------------------------------------------------------
	FILE _iob[ _IOB_ENTRIES ] = 
	{
			// _ptr, _cnt, _base,  _flag, _file, _charbuf, _bufsiz

			// stdin (_iob[0])

			{ _bufin, 0, _bufin, _IOREAD | _IOYOURBUF, 0, 0, _INTERNAL_BUFSIZ },

			// stdout (_iob[1])

			{ NULL, 0, NULL, _IOWRT, 1, 0, 0 },

			// stderr (_iob[3])

			{ NULL, 0, NULL, _IOWRT, 2, 0, 0 },

	};

	//------------------------------------------------------------------------------
	void** __piob;

	static struct 
	{
			CRITICAL_SECTION* lock;
			enum { lkNormal = 0, lkPrealloc, lkDeleted } kind;
	} 
	_locktable[_TOTAL_LOCKS] = 
	{
			{ NULL, lkPrealloc }, /* 0  == _SIGNAL_LOCK      */
			{ NULL, lkPrealloc }, /* 1  == _IOB_SCAN_LOCK    */
			{ NULL, lkNormal   }, /* 2  == _TMPNAM_LOCK      - not preallocated */
			{ NULL, lkPrealloc }, /* 3  == _CONIO_LOCK       */
			{ NULL, lkPrealloc }, /* 4  == _HEAP_LOCK        */
			{ NULL, lkNormal   }, /* 5  == _UNDNAME_LOCK     - not preallocated */
			{ NULL, lkPrealloc }, /* 6  == _TIME_LOCK        */
			{ NULL, lkPrealloc }, /* 7  == _ENV_LOCK         */
			{ NULL, lkPrealloc }, /* 8  == _EXIT_LOCK1       */
			{ NULL, lkNormal   }, /* 9  == _POPEN_LOCK       - not preallocated */
			{ NULL, lkPrealloc }, /* 10 == _LOCKTAB_LOCK     */
			{ NULL, lkNormal   }, /* 11 == _OSFHND_LOCK      - not preallocated */
			{ NULL, lkPrealloc }, /* 12 == _SETLOCALE_LOCK   */
			{ NULL, lkPrealloc }, /* 13 == _MB_CP_LOCK       */
			{ NULL, lkPrealloc }, /* 14 == _TYPEINFO_LOCK    */
	#ifdef _DEBUG
			{ NULL, lkPrealloc }, /* 15 == _DEBUG_LOCK       */
	#else  /* _DEBUG */
			{ NULL, lkNormal },   /* 15 == _DEBUG_LOCK       */
	#endif  /* _DEBUG */

			{ NULL, lkPrealloc }, /* 16 == _STREAM_LOCKS+0 - stdin  */
			{ NULL, lkPrealloc }, /* 17 == _STREAM_LOCKS+1 - stdout */
			{ NULL, lkPrealloc }, /* 18 == _STREAM_LOCKS+2 - stderr */
	/*      { NULL, lkNormal   }, /* ... */
	};


#define _NSTREAM_   512

	int _nstream = _NSTREAM_;

	//------------------------------------------------------------------------------
	int __initstdio(void)
	{
        int i;

#ifndef CRTDLL
        /* If the user has not supplied a definition of _nstream, set it
         * to _NSTREAM_. If the user has supplied a value that is too small
         * set _nstream to the minimum acceptable value (_IOB_ENTRIES).
         */
        if ( _nstream ==  0 )
            _nstream = _NSTREAM_;
        else if ( _nstream < _IOB_ENTRIES )
            _nstream = _IOB_ENTRIES;
#endif  /* CRTDLL */

        // Allocate the __piob array. Try for _nstream entries first. If this fails then reset _nstream to _IOB_ENTRIES and try again. If it still fails, bail out with an RTE.         
        if( ( __piob = (void **)calloc( _nstream, sizeof(void *) ) ) == NULL ) 
		{
            _nstream = _IOB_ENTRIES;
            if( ( __piob = (void **)calloc( _nstream, sizeof(void *) ) ) == NULL )
			{
                return _RT_STDIOINIT;
			}
        }

        //Initialize the first _IOB_ENTRIES to point to the corresponding entries in _iob[].
         
        for( i = 0 ; i < _IOB_ENTRIES ; i++ )
		{
            __piob[i] = (void *)&_iob[i];
		}
        return 0;
	}

	// callable exit flag
	char _exitflag = 0;

	//------------------------------------------------------------------------------
	void __endstdio(void)
	{
		// flush all streams
		_flushall();

		// if in callable exit, close all streams
		if( _exitflag )
		{
			_fcloseall();
		}
		free(__piob);
		__piob = NULL;
	}

	//------------------------------------------------------------------------------
	void __cdecl _FF_MSGBANNER( void )
	{
		/*
		if( ( _set_error_mode( _REPORT_ERRMODE ) == _OUT_TO_STDERR) || ( ( _set_error_mode( _REPORT_ERRMODE ) == _OUT_TO_DEFAULT ) && ( __app_type == _CONSOLE_APP ) ) )
		{
			_NMSG_WRITE(_RT_CRNL);  // new line to begin error message
			_NMSG_WRITE(_RT_BANNER); // run-time error message banner
		}
		*/
	}

	//------------------------------------------------------------------------------
	int _mtinitlocknum( int locknum )
	{
        CRITICAL_SECTION* pcs;
        int retval = true;

        /*Check if CRT is initialized. The check if _crtheap is initialized
         * will do the job. More over we had to add this test in initlocks because
         * in debug version we don't endup calling lock before calling malloc_base,
         * where we check for crtheap.
         */
        if( _crtheap == 0 ) 
		{
#if !defined (_CRT_APP) || defined (_DEBUG)
            _FF_MSGBANNER();    // write run-time error banner
            _NMSG_WRITE( _RT_CRT_NOTINIT );  // write message
#endif  /* !defined (_CRT_APP) || defined (_DEBUG) */
            __crtExitProcess(255);  /* normally _exit(255) */
        }


        if( _locktable[locknum].lock != NULL )
		{
            return 1;
		}

        if( ( pcs = reinterpret_cast< CRITICAL_SECTION* >( malloc( sizeof(CRITICAL_SECTION) ) ) ) == NULL ) 
		{
            errno = ENOMEM;
            return 0;
        }

        _lock( _LOCKTAB_LOCK );
        __try
		{
            if( _locktable[locknum].lock == NULL ) 
			{
                InitializeCriticalSectionEx(pcs, _CRT_SPINCOUNT, 0);
                _locktable[locknum].lock = pcs;
            }
            else 
			{
                free( pcs );
            }
		}
        __finally
		{
            _unlock( _LOCKTAB_LOCK );
		}

        return retval;
	}

	//------------------------------------------------------------------------------
	void _lock( int locknum )
	{

		//Create/open the lock, if necessary

		if( _locktable[ locknum ].lock == NULL ) 
		{
			if( !_mtinitlocknum( locknum ) )
			{
				_amsg_exit( _RT_LOCK );
			}
		}

		//Enter the critical section.

		EnterCriticalSection( _locktable[ locknum ].lock );
	}

	//------------------------------------------------------------------------------
	void _unlock( int locknum )
	{
		LeaveCriticalSection( _locktable[ locknum ].lock );
	}

	//------------------------------------------------------------------------------
	CPosumStream* _getstream ( void )
	{
		CPosumStream* retval = NULL;
		int i;

	    // Get the iob[] scan lock
		_lock(_IOB_SCAN_LOCK);
		__try 
		{

        //Loop through the __piob table looking for a free stream, or the first NULL entry.
        
        for ( i = 0 ; i < _nstream ; i++ ) 
		{

            if( __piob[i] != NULL ) 
			{
                /*
                * if the stream is not inuse, return it.
                */
                if ( !inuse( (FILE *)__piob[i] ) && !str_locked( (FILE *)__piob[i] ) ) 
				{
                    /* Allocate the FILE lock, in case it hasn't already been
                    * allocated (only necessary for the first _IOB_ENTRIES
                    * locks, not including stdin/stdout/stderr).  Return
                    * failure if lock can't be allocated.
                    */
                    if ( i > 2 && i < _IOB_ENTRIES )
					{
                        if ( !_mtinitlocknum( _STREAM_LOCKS + i ) )
						{
                            break;
						}
					}

                    _lock_str2(i, __piob[i]);

                    if ( inuse( (FILE *)__piob[i] ) ) 
					{
                        _unlock_str2(i, __piob[i]);
                        continue;
                    }
                    retval = (FILE *)__piob[i];
                    break;
                }
            }
            else 
			{
                //allocate a new _FILEX, set _piob[i] to it and return a pointer to it.
                __piob[i] = new CPosumStream();

                if( __piob[i] = != NULL ) 
				{
                    InitializeCriticalSectionEx(&(((_FILEX *)__piob[i])->lock), _CRT_SPINCOUNT, 0);
                    EnterCriticalSection( &(((_FILEX *)__piob[i])->lock) );
                    retval = (FILE *)__piob[i];
                    retval->_flag = 0;
                }

                break;
            }
        }

        //Initialize the return stream.
        
        if( retval != NULL ) 
		{
            // make sure that _IOLOCKED is preserved (if set) and zero out the other bits of _flag
            retval->_flag &= _IOLOCKED;
            retval->_cnt = 0;
            retval->_tmpfname = retval->_ptr = retval->_base = NULL;
            retval->_file = -1;
        }

		}
		__finally 
		{
			_unlock(_IOB_SCAN_LOCK);
		}

		return retval;
	}

}//nsWin32
