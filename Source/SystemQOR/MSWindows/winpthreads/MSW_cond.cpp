/*
   Copyright (c) 2011 mingw-w64 project

   Permission is hereby granted, free of charge, to any person obtaining a
   copy of this software and associated documentation files (the "Software"),
   to deal in the Software without restriction, including without limitation
   the rights to use, copy, modify, merge, publish, distribute, sublicense,
   and/or sell copies of the Software, and to permit persons to whom the
   Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
   FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
   DEALINGS IN THE SOFTWARE.
*/

/*
 * Posix Condition Variables for Microsoft Windows.
 * 22-9-2010 Partly based on the ACE framework implementation.
 */

#include "SystemQOR.h"
#if		(QOR_SYS_OS == QOR_SYS_MSW)

#include "WinQL/Application/Threading/WinQLThread.h"
#include "WinQL/Application/Threading/WinQLSemaphore.h"
#include "WinQL/Application/Threading/WinQLEvent.h"
#include <errno.h>
#include <stdio.h>
#include <limits.h>
#include <time.h>
#include "SystemQOR/MSWindows/types/pthread_types.h"
#include "SystemQOR/MSWindows/MSW_pthread.h"
#include "../SystemQOR/MSWindows/Winpthreads/details/ref.h"
#include "../SystemQOR/MSWindows/Winpthreads/details/cond.h"
#include "../SystemQOR/MSWindows/Winpthreads/details/mutex.h"
#include "../SystemQOR/MSWindows/Winpthreads/details/spinlock.h"
#include "../SystemQOR/MSWindows/Winpthreads/details/thread.h"
#include "../SystemQOR/MSWindows/Winpthreads/details/misc.h"
//#include "winpthread_internal.h"

//--------------------------------------------------------------------------------
namespace nsWin32
{

	int __pthread_shallcancel (void);

	static int do_sema_b_wait( void* sema, int nointerrupt, unsigned long timeout, nsWin32::CCriticalSection* cs, long* val);
	static int do_sema_b_release( void* sema, long count, nsWin32::CCriticalSection* cs, long* val );
	static void cleanup_wait( void* arg );

	//--------------------------------------------------------------------------------
	typedef struct sCondWaitHelper 
	{
		cond_t *c;
		pthread_mutex_t *external_mutex;
		int *r;
	} sCondWaitHelper;

	int do_sema_b_wait_intern ( void* sema, int nointerrupt, unsigned long timeout );

#ifndef NDEBUG

	static int print_state = 0;
	static FILE *fo;

	//--------------------------------------------------------------------------------
	void cond_print_set(int state, FILE *f)
	{
		if( f )
		{
			fo = f;
		}
		if( !fo )
		{
			fo = stdout;
		}
		print_state = state;
	}

	//--------------------------------------------------------------------------------
	void cond_print( volatile pthread_cond_t* c, char* txt )
	{
		if( !print_state )
		{
			return;
		}
		cond_t* c_ = (cond_t*)*c;
		if( c_ == NULL ) 
		{
			fprintf( fo,"C%p %d %s\n", *c, (int)nsWin32::GetCurrentWin32Thread()->GetCurrentId(), txt );
		} 
		else 
		{
			fprintf(fo,"C%p %d V=%0X B=%d b=%p w=%ld %s\n",
				*c, 
				(int)nsWin32::GetCurrentWin32Thread()->GetCurrentId(), 
				(int)c_->valid, 
				(int)c_->busy,
				NULL,
				c_->waiters_count_,
				txt
				);
		}
	}

#endif

	static spin_t cond_locked = {0,LIFE_SPINLOCK,1};

	//--------------------------------------------------------------------------------
	static int cond_static_init( pthread_cond_t* c )
	{
		int r = 0;
  
		_spin_lite_lock( &cond_locked );
		if( c == NULL )
		{
			r = EINVAL;
		}
		else if( *c == PTHREAD_COND_INITIALIZER )
		{
			r = pthread_cond_init( c, NULL );
		}
		else
		{
			// We assume someone was faster ...
			r = 0;
		}
		_spin_lite_unlock( &cond_locked );
		return r;
	}

	//--------------------------------------------------------------------------------
	int Cpthread::condattr_destroy( pthread_condattr_t* a )
	{
		if( !a )
		{
			return EINVAL;
		}
		*a = 0;
		return 0;
	}

	//--------------------------------------------------------------------------------
	int Cpthread::condattr_init( pthread_condattr_t* a )
	{
		if( !a )
		{
			return EINVAL;
		}
		*a = 0;
		return 0;
	}

	//--------------------------------------------------------------------------------
	int Cpthread::condattr_getpshared( const pthread_condattr_t* a, int* s )
	{
		if( !a || !s )
		{
			return EINVAL;
		}
		*s = *a;
		return 0;
	}

	//--------------------------------------------------------------------------------
	int Cpthread::condattr_getclock( const pthread_condattr_t* a, clockid_t* clock_id )
	{
		if( !a || !clock_id )
		{
			return EINVAL;
		}
		*clock_id = 0;
		return 0;
	}

	//--------------------------------------------------------------------------------
	int Cpthread::condattr_setclock( pthread_condattr_t* a, clockid_t clock_id )
	{
		if( !a || clock_id != 0 )
		{
			return EINVAL;
		}
		return 0;
	}

	//--------------------------------------------------------------------------------
	int __pthread_clock_nanosleep( clockid_t clock_id, int flags, const timespec* rqtp, timespec* rmtp )
	{
		unsigned long long tick, tick2;
		unsigned long long delay;
		unsigned long dw;

		if( clock_id != CLOCK_REALTIME && clock_id != CLOCK_MONOTONIC && clock_id != CLOCK_PROCESS_CPUTIME_ID )
		{
			return EINVAL;
		}

		if( ( flags & TIMER_ABSTIME ) != 0 )
		{
			delay = Cpthread::rel_time_in_ms( rqtp );
		}
		else
		{
			delay = Cpthread::time_in_ms_from_timespec (rqtp);
		}

		do
		{
			dw = (unsigned long)( delay >= 99999ULL ? 99999ULL : delay );
			tick = Cpthread::time_in_ms();
			Cpthread::delay_np_ms( dw );
			tick2 = Cpthread::time_in_ms();
			tick2 -= tick;
			if( tick2 >= delay )
			{
				delay = 0;
			}
			else
			{
				delay -= tick2;
			}
		}
		while( delay != 0ULL );

		if( rmtp )
		{
			memset( rmtp, 0, sizeof( *rmtp ) );
		}
		return 0;
	}

	//--------------------------------------------------------------------------------
	int Cpthread::condattr_setpshared( pthread_condattr_t* a, int s )
	{
		if( !a || ( s != PTHREAD_PROCESS_SHARED && s != PTHREAD_PROCESS_PRIVATE ) )
		{
			return EINVAL;
		}

		if( s == PTHREAD_PROCESS_SHARED )
		{
			*a = PTHREAD_PROCESS_PRIVATE;
			return ENOSYS;
		}
		*a = s;
		return 0;
	}

	//--------------------------------------------------------------------------------
	int Cpthread::cond_init( pthread_cond_t* c, const pthread_condattr_t* a )
	{
		cond_t* _c;
		int r = 0;
    
		if( !c )
		{
			return EINVAL;
		}

		if( a && (int)(*a) == PTHREAD_PROCESS_SHARED )
		{
			return ENOSYS;
		}

		if( !( _c = (cond_t*)(pthread_cond_t)calloc( 1,sizeof( *_c ) ) ) ) 
		{
			return ENOMEM; 
		}

		_c->valid  = DEAD_COND;
		_c->waiters_count_ = 0;
		_c->waiters_count_gone_ = 0;
		_c->waiters_count_unblock_ = 0;

		_c->sema_q = new nsWin32::CSemaphore( (nsWin32::LPSECURITY_ATTRIBUTES)(0),       /* no security */
		0,          /* initially 0 */
		0x7fffffff, /* max count */
		NULL,      /* unnamed  */
		0,
		nsWin32::Standard_Rights_All | nsWin32::Semaphore_Modify_State );

		_c->sema_b = new nsWin32::CSemaphore( (nsWin32::LPSECURITY_ATTRIBUTES)(0),		/* no security */
		0,          /* initially 0 */
		0x7fffffff, /* max count */
		NULL,
		0,
		nsWin32::Standard_Rights_All | nsWin32::Semaphore_Modify_State );  

		if( _c->sema_q == NULL || _c->sema_b == NULL ) 
		{
			if (_c->sema_q != NULL)
			{
				delete _c->sema_q;
			}
			if( _c->sema_b != NULL )
			{
				delete _c->sema_b;
			}
			free( _c );
			r = EAGAIN;
		} 
		else 
		{
			_c->waiters_count_lock_ = new nsWin32::CCriticalSection();
			_c->waiters_b_lock_ = new nsWin32::CCriticalSection();
			_c->waiters_q_lock_ = new nsWin32::CCriticalSection();
			_c->value_q = 0;
			_c->value_b = 1;
		}

		if( !r )
		{
			_c->valid = LIFE_COND;
			*c = (pthread_cond_t)_c;
		}
		else
		{
			*c = NULL;
		}
		return r;
	}

	//--------------------------------------------------------------------------------
	int Cpthread::cond_destroy( pthread_cond_t* c )
	{
		cond_t* _c;
		int r;
		if( !c || !*c )
		{
			return EINVAL;
		}

		if( *c == PTHREAD_COND_INITIALIZER )
		{
			_spin_lite_lock( &cond_locked );
			if( *c == PTHREAD_COND_INITIALIZER )
			{
				*c = NULL;
				r = 0;
			}
			else
			{
				r = EBUSY;
			}
			_spin_lite_unlock( &cond_locked );
			return r;
		}

		_c = (cond_t *) *c;
		r = do_sema_b_wait( _c->sema_b, 0, nsWin32::Infinite, _c->waiters_b_lock_, &_c->value_b );

		if( r != 0 )
		{
			return r;
		}

		if( !_c->waiters_count_lock_->TryEnter() )
		{
			do_sema_b_release (_c->sema_b, 1, _c->waiters_b_lock_,&_c->value_b);
			return EBUSY;
		}

		if( _c->waiters_count_ > _c->waiters_count_gone_ || _c->busy != 0 )
		{
			r = do_sema_b_release( _c->sema_b, 1, _c->waiters_b_lock_,&_c->value_b );
			if( !r )
			{
				r = EBUSY;
			}
			_c->waiters_count_lock_->Leave();
			return r;
		}

		*c = NULL;
		do_sema_b_release( _c->sema_b, 1, _c->waiters_b_lock_, &_c->value_b );
      
		delete _c->sema_q;
		delete _c->sema_b;

		_c->waiters_count_lock_->Leave();
		delete _c->waiters_count_lock_;
		delete _c->waiters_b_lock_;
		delete _c->waiters_q_lock_;
		_c->valid  = DEAD_COND;
		free( _c );
		return 0;
	}

	//--------------------------------------------------------------------------------
	int Cpthread::cond_signal( pthread_cond_t* c )
	{
		cond_t *_c;
		int r;
    
		if( !c || !*c )
		{
			return EINVAL;
		}

		_c = (cond_t *)*c;
		if( _c == (cond_t *)PTHREAD_COND_INITIALIZER )
		{
			return 0;
		}
		else if( _c->valid != (unsigned int)LIFE_COND )
		{
			return EINVAL;
		}

		_c->waiters_count_lock_->Enter();
		// If there aren't any waiters, then this is a no-op.
		if( _c->waiters_count_unblock_ != 0 )
		{
			if( _c->waiters_count_ == 0 )
			{
				_c->waiters_count_lock_->Leave();
				pthread_testcancel();
				return 0;
			}
			_c->waiters_count_ -= 1;
			_c->waiters_count_unblock_ += 1;
		}
		else if( _c->waiters_count_ > _c->waiters_count_gone_ )
		{
			r = do_sema_b_wait( _c->sema_b, 1, nsWin32::Infinite, _c->waiters_b_lock_,&_c->value_b );
			if( r != 0 )
			{
				_c->waiters_count_lock_->Leave();
				pthread_testcancel();
				return r;
			}

			if( _c->waiters_count_gone_ != 0 )
			{
				_c->waiters_count_ -= _c->waiters_count_gone_;
				_c->waiters_count_gone_ = 0;
			}

			_c->waiters_count_ -= 1;
			_c->waiters_count_unblock_ = 1;
		}
		else
		{
			_c->waiters_count_lock_->Leave();
			pthread_testcancel();
			return 0;
		}

		_c->waiters_count_lock_->Leave();
		r = do_sema_b_release( _c->sema_q, 1, _c->waiters_q_lock_, &_c->value_q);
		pthread_testcancel();
		return r;
	}

	//--------------------------------------------------------------------------------
	int Cpthread::cond_broadcast (pthread_cond_t *c)
	{
		cond_t *_c;
		int r;
		int relCnt = 0;    

		if( !c || !*c )
		{
			return EINVAL;
		}

		_c = (cond_t *)*c;
		if( _c == (cond_t*)PTHREAD_COND_INITIALIZER )
		{
			return 0;
		}
		else if( _c->valid != (unsigned int)LIFE_COND )
		{
			return EINVAL;
		}

		_c->waiters_count_lock_->Enter();
		// If there aren't any waiters, then this is a no-op.
		if( _c->waiters_count_unblock_ != 0 )
		{
			if( _c->waiters_count_ == 0 )
			{
				_c->waiters_count_lock_->Leave();
				pthread_testcancel();
				return 0;
			}
			relCnt = _c->waiters_count_;
			_c->waiters_count_ = 0;
			_c->waiters_count_unblock_ += relCnt;
		}
		else if( _c->waiters_count_ > _c->waiters_count_gone_ )
		{
			r = do_sema_b_wait( _c->sema_b, 1, nsWin32::Infinite, _c->waiters_b_lock_,&_c->value_b );
			if( r != 0 )
			{
				_c->waiters_count_lock_->Leave();
				pthread_testcancel();
				return r;
			}

			if( _c->waiters_count_gone_ != 0 )
			{
				_c->waiters_count_ -= _c->waiters_count_gone_;
				_c->waiters_count_gone_ = 0;
			}

			relCnt = _c->waiters_count_;
			_c->waiters_count_ = 0;
			_c->waiters_count_unblock_ = relCnt;
		}
		else
		{
			_c->waiters_count_lock_->Leave();
			pthread_testcancel();
			return 0;
		}

		_c->waiters_count_lock_->Leave();
		r = do_sema_b_release( _c->sema_q, relCnt, _c->waiters_q_lock_, &_c->value_q );
		pthread_testcancel();
		return r;
	}

	//--------------------------------------------------------------------------------
	int Cpthread::cond_wait( pthread_cond_t* c, pthread_mutex_t* external_mutex )
	{
		sCondWaitHelper ch;
		cond_t *_c;
		int r;

		pthread_testcancel();

		if( !c || *c == NULL )
		{
			return EINVAL;
		}

		_c = (cond_t *)*c;
		if( *c == PTHREAD_COND_INITIALIZER )
		{
			r = cond_static_init(c);
			if( r != 0 && r != EBUSY )
			{
				return r;
			}
			_c = (cond_t *) *c;
		}
		else if( _c->valid != (unsigned int)LIFE_COND )
		{
			return EINVAL;
		}
		    
		r = do_sema_b_wait( _c->sema_b, 0, nsWin32::Infinite, _c->waiters_b_lock_, &_c->value_b );
		if( r != 0 )
		{
			return r;
		}
		_c->waiters_count_lock_->Enter();
		_c->waiters_count_++;
		_c->waiters_count_lock_->Leave();
		r = do_sema_b_release( _c->sema_b, 1, _c->waiters_b_lock_,&_c->value_b );
		if( r != 0 )
		{
			return r;
		}

		ch.c = _c;
		ch.r = &r;
		ch.external_mutex = external_mutex;
    
		cleanup_push( cleanup_wait, (void *)&ch );
		r = pthread_mutex_unlock( external_mutex );
		
		if( !r )
		{
			r = do_sema_b_wait( _c->sema_q, 0, nsWin32::Infinite, _c->waiters_q_lock_, &_c->value_q );
		}

		cleanup_pop( 1 );
		return r;
	}

	//--------------------------------------------------------------------------------
	int Cpthread::cond_timedwait( pthread_cond_t* c, pthread_mutex_t* external_mutex, const timespec* t )
	{
		sCondWaitHelper ch;
		unsigned long dwr;
		int r;
		cond_t *_c;

		pthread_testcancel();

		if( !c || !*c )
		{
			return EINVAL;
		}

		_c = (cond_t *)*c;
		if( _c == (cond_t *)PTHREAD_COND_INITIALIZER )
		{
			r = cond_static_init(c);
			if( r && r != EBUSY )
			{
				return r;
			}
			_c = (cond_t *) *c;
		} 
		else if( (_c)->valid != (unsigned int)LIFE_COND )
		{
			return EINVAL;
		}

		dwr = dwMilliSecs( Cpthread::rel_time_in_ms( t ) );
		r = do_sema_b_wait( _c->sema_b, 0, nsWin32::Infinite, _c->waiters_b_lock_,&_c->value_b );
		if( r != 0 )
		{
			return r;
		}

		_c->waiters_count_++;
		r = do_sema_b_release( _c->sema_b, 1, _c->waiters_b_lock_,&_c->value_b );

		if( r != 0 )
		{
			return r;
		}

		ch.c = _c;
		ch.r = &r;
		ch.external_mutex = external_mutex;
		{ 
			cleanup_push( cleanup_wait, (void*)&ch );

			r = pthread_mutex_unlock( external_mutex );
			if( !r )
			{
				r = do_sema_b_wait( _c->sema_q, 0, dwr, _c->waiters_q_lock_,&_c->value_q );
			}

			cleanup_pop( 1 );
		}
		return r;
	}

	//--------------------------------------------------------------------------------
	static void cleanup_wait(void *arg)
	{
		int n, r;
		sCondWaitHelper *ch = (sCondWaitHelper *) arg;
		cond_t *_c;

		_c = ch->c;
		_c->waiters_count_lock_->Enter();
		n = _c->waiters_count_unblock_;
		if( n != 0 )
		{
			_c->waiters_count_unblock_ -= 1;
		}
		else if( ( INT_MAX / 2 ) - 1 == _c->waiters_count_gone_ )
		{
			_c->waiters_count_gone_ += 1;
			r = do_sema_b_wait( _c->sema_b, 1, nsWin32::Infinite, _c->waiters_b_lock_, &_c->value_b );
			if( r != 0 )
			{
				_c->waiters_count_lock_->Leave();
				ch->r[ 0 ] = r;
				return;
			}
			_c->waiters_count_ -= _c->waiters_count_gone_;
			r = do_sema_b_release( _c->sema_b, 1, _c->waiters_b_lock_, &_c->value_b );
			if( r != 0 )
			{
				_c->waiters_count_lock_->Leave();
				ch->r[ 0 ] = r;
				return;
			}
			_c->waiters_count_gone_ = 0;
		}
		else
		{
			_c->waiters_count_gone_ += 1;
		}
		_c->waiters_count_lock_->Leave();

		if( n == 1 )
		{
			r = do_sema_b_release( _c->sema_b, 1, _c->waiters_b_lock_, &_c->value_b );
			if( r != 0 )
			{
				ch->r[ 0 ] = r;
				return;
			}
		}
		r = pthread_mutex_lock( ch->external_mutex );
		if( r != 0 )
		{
			ch->r[ 0 ] = r;
		}
	}

	//--------------------------------------------------------------------------------
	static int do_sema_b_wait( void* sema, int nointerrupt, unsigned long timeout, nsWin32::CCriticalSection* cs, long* val )
	{
		int r;
		long v;
		cs->Enter();
		nsWin32::CInterlockedHelper InterlockedHelper;
		InterlockedHelper.Decrement( val );
		v = val[ 0 ];
		cs->Leave();
		if( v >= 0 )
		{
			return 0;
		}
		r = do_sema_b_wait_intern( sema, nointerrupt, timeout );
		cs->Enter();
		if( r != 0 )
		{
			InterlockedHelper.Increment( val );
		}
		cs->Leave();
		return r;
	}

	//--------------------------------------------------------------------------------
	int do_sema_b_wait_intern( void* sema, int nointerrupt, unsigned long timeout)
	{
		nsWin32::CSemaphore* pSemaphore = reinterpret_cast< nsWin32::CSemaphore* >( sema );
		nsWin32::CWaitHelper WaitHelper;
		nsWin32::CSyncHandleSet Arr;
		//void* arr[ 2 ];
		unsigned long maxH = 1;
		int r = 0;
		unsigned long res, dt;
		if( nointerrupt == 1 )
		{
			res = WaitHelper.WaitForSingleObject( pSemaphore->Handle(), timeout );
			switch (res) 
			{
			case nsWin32::Wait_Timeout:
				r = ETIMEDOUT;
				break;
			case nsWin32::Wait_Abandoned:
				r = EPERM;
				break;
			case nsWin32::Wait_Object_0:
				break;
			default:
				//We can only return EINVAL though it might not be posix compliant
				r = EINVAL;
			}

			if( r != 0 && r != EINVAL && WaitHelper.WaitForSingleObject( pSemaphore->Handle(), 0 ) == nsWin32::Wait_Object_0 )
			{
				r = 0;
			}
			return r;
		}

		
		nsWin32::CEvent* pEvent = reinterpret_cast< nsWin32::CEvent* >( Cpthread::getevent( pthread_self() ) );
		Arr.Add( pSemaphore->Handle() );
		
		if( pEvent != 0 )
		{
			Arr.Add( pEvent->Handle() );
			maxH += 1;
		}

		if( maxH == 2 )
		{
			res = WaitHelper.WaitForMultipleObjects( Arr, 0, timeout );
			switch (res) 
			{
			case nsWin32::Wait_Timeout:
				r = ETIMEDOUT;
				break;
			case ( nsWin32::Wait_Object_0 + 1 ):
				{
					pEvent->Reset();
					if( nointerrupt != 2 )
					{
						pthread_testcancel();
					}
					return EINVAL;
				}
			case nsWin32::Wait_Abandoned:
				r = EPERM;
				break;
			case nsWin32::Wait_Object_0:
				r = 0;
				break;
			default:
				//We can only return EINVAL though it might not be posix compliant
				r = EINVAL;
			}

			if( r != 0 && r != EINVAL && WaitHelper.WaitForSingleObject( *Arr[ 0 ], 0 ) == nsWin32::Wait_Object_0 )
			{
				r = 0;
			}

			if( r != 0 && __pthread_shallcancel() )
			{
				return EINVAL;
			}

			return r;
		}

		if( timeout == nsWin32::Infinite )
		{
			do 
			{
				res = WaitHelper.WaitForSingleObject( pSemaphore->Handle(), 40 );
				switch (res) 
				{
				case nsWin32::Wait_Timeout:
					r = ETIMEDOUT;
					break;
				case nsWin32::Wait_Abandoned:
					r = EPERM;
					break;
				case nsWin32::Wait_Object_0:
					r = 0;
					break;
				default:
					//We can only return EINVAL though it might not be posix compliant
					r = EINVAL;
				}

				if( r != 0 && __pthread_shallcancel() )
				{
					if( nointerrupt != 2 )
					{
						pthread_testcancel();
					}
					return EINVAL;
				}

			} while( r == ETIMEDOUT );

			if( r != 0 && r != EINVAL && WaitHelper.WaitForSingleObject( pSemaphore->Handle(), 0 ) == nsWin32::Wait_Object_0 )
			{
				r = 0;
			}
			return r;
		}

		dt = 20;
		do 
		{
			if( dt > timeout)
			{
				dt = timeout;
			}

			res = WaitHelper.WaitForSingleObject( pSemaphore->Handle(), dt );
			switch (res) 
			{
			case nsWin32::Wait_Timeout:
				r = ETIMEDOUT;
				break;
			case nsWin32::Wait_Abandoned:
				r = EPERM;
				break;
			case nsWin32::Wait_Object_0:
				r = 0;
				break;
			default:
				//We can only return EINVAL though it might not be posix compliant
				r = EINVAL;
			}

			timeout -= dt;
			if( timeout != 0 && r != 0 && __pthread_shallcancel() )
			{
				return EINVAL;
			}
		} while( r == ETIMEDOUT && timeout != 0 );

		if( r != 0 && r == ETIMEDOUT && WaitHelper.WaitForSingleObject( pSemaphore->Handle(), 0 ) == nsWin32::Wait_Object_0 )
		{
			r = 0;
		}

		if( r != 0 && nointerrupt != 2 )
		{
			pthread_testcancel();
		}
		return r;
	}

	//--------------------------------------------------------------------------------
	static int do_sema_b_release( void* sema, long count, nsWin32::CCriticalSection* cs, long *val)
	{
		int wc;
		cs->Enter();
		nsWin32::CInterlockedHelper InterlockedHelper;
		if( ( (long long) val[ 0 ] + (long long) count ) > (long long) 0x7fffffffLL )
		{
			cs->Leave();
			return ERANGE;
		}
		wc = -val[ 0 ];
		InterlockedHelper.ExchangeAdd( val, count );
  
		if( wc <= 0 )
		{
			cs->Leave();
			return 0;
		}
		else
		{
			nsWin32::CSemaphore* pSemaphore = reinterpret_cast< nsWin32::CSemaphore* >( sema );
			//nsWin32::nsSync::CSemaphore Semaphore( sema );
			if( pSemaphore->Release( wc < count ? wc : count, 0 ) )
			{
				cs->Leave();
				return 0;
			}
		}

		InterlockedHelper.ExchangeAdd( val, -count );
		cs->Leave();
		return EINVAL;  
	}

}//nsWin32

#endif//(QOR_SYS_OS == QOR_SYS_MSW)
