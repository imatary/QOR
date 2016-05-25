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

#ifndef WIN_PTHREADS_MISC_H
#define WIN_PTHREADS_MISC_H

//#include "SystemQOR/MSWindows/winpthreads/pthread_compat.h"

#ifndef assert

#ifndef ASSERT_TRACE
# define ASSERT_TRACE 0
#else
# undef ASSERT_TRACE
# define ASSERT_TRACE 0
#endif

# define assert(e) \
   ((e) ? ((ASSERT_TRACE) ? fprintf(stderr, \
                                    "Assertion succeeded: (%s), file %s, line %d\n", \
                        #e, __FILE__, (int) __LINE__), \
                                fflush(stderr) : \
                             0) : \
          (fprintf(stderr, "Assertion failed: (%s), file %s, line %d\n", \
                   #e, __FILE__, (int) __LINE__), exit(1), 0))

# define fixme(e) \
   ((e) ? ((ASSERT_TRACE) ? fprintf(stderr, \
                                    "Assertion succeeded: (%s), file %s, line %d\n", \
                        #e, __FILE__, (int) __LINE__), \
                                fflush(stderr) : \
                             0) : \
          (fprintf(stderr, "FIXME: (%s), file %s, line %d\n", \
                   #e, __FILE__, (int) __LINE__), 0, 0))

#endif

#define PTR2INT(x)	((int)(uintptr_t)(x))

typedef intmax_t LONGBAG;

#define CHECK_HANDLE(h) { DWORD dwFlags; \
    if (!(h) || ((h) == INVALID_HANDLE_VALUE) || !GetHandleInformation((h), &dwFlags)) \
    return EINVAL; }

#define CHECK_PTR(p)    if (!(p)) return EINVAL;

#define UPD_RESULT(x,r)    { int _r=(x); r = r ? r : _r; }

#define CHECK_THREAD(t)  { \
    CHECK_PTR(t); \
    CHECK_HANDLE(t->h); }

template< typename A, typename B >
static inline B CheckObject( A& o, B e )
{
	unsigned long dwFlags;
    if( !( o ) )
	{
		return e;
	}

	if( !( (o)->h ) || ( ( (o)->h) == Invalid_Handle_Value ) || !(o)->h->Handle()->GetInformation( &dwFlags ) ) 
	{
		return e;
	}

	return B(0);
}

/*
#define CHECK_OBJECT(o, e)  { unsigned long dwFlags; \
    if (!(o)) return e; \
    if (!((o)->h) || (((o)->h) == Invalid_Handle_Value ) || !GetHandleInformation(((o)->h), &dwFlags)) \
        return e; }
*/
#define VALID(x)    if (!(p)) return EINVAL;

/* ms can be 64 bit, solve wrap-around issues: */
static __QCMP_INLINE unsigned long dwMilliSecs(unsigned long long ms)
{
  if (ms >= 0xffffffffULL) return 0xfffffffful;
  return (unsigned long) ms;
}

#ifndef _mm_pause
#define _mm_pause()			{__asm__ __volatile__("pause");}
#endif
/*
#ifndef _ReadWriteBarrier
#define _ReadWriteBarrier   __sync_synchronize
#endif
*/
void _cdecl _ReadWriteBarrier( void );

#pragma intrinsic(_ReadWriteBarrier)

#ifndef YieldProcessor
#define YieldProcessor      _mm_pause
#endif


#endif
