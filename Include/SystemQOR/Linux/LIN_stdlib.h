//LIN_stdlib.h

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

//Linux overrides for stdlib

#ifndef SYSTEMQOR_LIN_STDLIB_H_3
#define SYSTEMQOR_LIN_STDLIB_H_3

#include "SystemQOR/Linux/types/stdlib_types.h"
#include "SystemQOR/Linux/types/malloc_types.h"
#include "SystemQOR/Posix/Basestdlib.h"

//--------------------------------------------------------------------------------
namespace nsLinux
{
	//--------------------------------------------------------------------------------
	class __QOR_INTERFACE( __QSYS ) Cstdlib : public nsBaseCRT::Cstdlib
	{
	public:

		Cstdlib(){}
		virtual ~Cstdlib(){}

		static nsBaseCRT::Cstdlib* Thestdlib( void );

		virtual void* malloc( size_t );
		virtual void* calloc( size_t, size_t );
		virtual void* realloc( void*, size_t );
		virtual void free( void* );
		virtual void* valloc( size_t );
		virtual void* memalign( size_t, size_t );
		virtual size_t malloc_usable_size( void* );

		virtual int atoi (const char *);
		virtual long atol (const char *);
		virtual long long atoll (const char *);
		virtual double atof (const char *);

		virtual float strtof (const char *__restrict, char **__restrict);
		virtual double strtod (const char *__restrict, char **__restrict);
		virtual long double strtold (const char *__restrict, char **__restrict);

		virtual long strtol (const char *__restrict, char **__restrict, int);
		virtual unsigned long strtoul (const char *__restrict, char **__restrict, int);
		virtual long long strtoll (const char *__restrict, char **__restrict, int);
		virtual unsigned long long strtoull (const char *__restrict, char **__restrict, int);

		virtual int rand (void);
		virtual void srand (unsigned);

		virtual void *aligned_alloc(size_t alignment, size_t size);

		virtual _Noreturn void abort (void);
		virtual int atexit (void (*) (void));
		virtual _Noreturn void exit (int);
		virtual _Noreturn void _Exit (int);
		virtual int at_quick_exit (void (*) (void));
		virtual _Noreturn void quick_exit (int);

		virtual char *getenv (const char *);

		virtual int system (const char *);

		virtual void *bsearch (const void *, const void *, size_t, size_t, int (*)(const void *, const void *));
		virtual void qsort (void *, size_t, size_t, int (*)(const void *, const void *));

		virtual int abs (int);
		virtual long labs (long);
		virtual long long llabs (long long);

		virtual div_t div (int, int);
		virtual ldiv_t ldiv (long, long);
		virtual lldiv_t lldiv (long long, long long);

		virtual int mblen (const char *, size_t);
		virtual int mbtowc (wchar_t *__restrict, const char *__restrict, size_t);
		virtual int wctomb (char *, wchar_t);
		virtual size_t mbstowcs (wchar_t *__restrict, const char *__restrict, size_t);
		virtual size_t wcstombs (char *__restrict, const wchar_t *__restrict, size_t);

#if defined(_POSIX_SOURCE) || defined(_POSIX_C_SOURCE) || defined(_XOPEN_SOURCE) || defined(_GNU_SOURCE) || defined(_BSD_SOURCE)

		virtual int posix_memalign (void **, size_t, size_t);
		virtual int setenv (const char *, const char *, int);
		virtual int unsetenv (const char *);
		virtual int mkstemp (char *);
		virtual int mkostemp (char *, int);
		virtual char *mkdtemp (char *);
		virtual int getsubopt (char **, char *const *, char **);
		virtual int rand_r (unsigned *);
#endif

#if defined(_XOPEN_SOURCE) || defined(_GNU_SOURCE) || defined(_BSD_SOURCE)
		virtual char *realpath (const char *__restrict, char *__restrict);
		virtual long int random (void);
		virtual void srandom (unsigned int);
		virtual char *initstate (unsigned int, char *, size_t);
		virtual char *setstate ( const char *);
		virtual int putenv ( const char *);
		virtual int posix_openpt (int);
		virtual int grantpt (int);
		virtual int unlockpt (int);
		virtual char *ptsname (int);
		virtual char *l64a (long);
		virtual long a64l (const char *);
		virtual void setkey (const char *);
		virtual double drand48 (void);
		virtual double erand48 (unsigned short [3]);
		virtual long int lrand48 (void);
		virtual long int nrand48 (unsigned short [3]);
		virtual long mrand48 (void);
		virtual long jrand48 (unsigned short [3]);
		virtual void srand48 (long);
		virtual unsigned short *seed48 (unsigned short [3]);
		virtual void lcong48 (unsigned short [7]);
#endif

#if defined(_GNU_SOURCE) || defined(_BSD_SOURCE)
		virtual char *mktemp (char *);
		virtual int mkstemps (char *, int);
		virtual int mkostemps (char *, int, int);
		//virtual void *valloc (size_t);
		//virtual void *memalign(size_t, size_t);
		virtual int getloadavg(double *, int);
		virtual int clearenv(void);
#endif

#ifdef _GNU_SOURCE
		virtual int ptsname_r(int, char *, size_t);
		virtual char *ecvt(double, int, int *, int *);
		virtual char *fcvt(double, int, int *, int *);
		virtual char *gcvt(double, int, char *);
		virtual float strtof_l(const char *__restrict, char **__restrict, struct __locale_struct *);
		virtual double strtod_l(const char *__restrict, char **__restrict, struct __locale_struct *);
		virtual long double strtold_l(const char *__restrict, char **__restrict, struct __locale_struct *);
#endif

		static int WaitExitStatus( int status );
		static int WaitIfExited( int status );
		static int WaitIfSignaled( int status );
		static int WaitIfStopped( int status );
		static int WaitStopSignal( int status );
		static int WaitTermSignal( int status );
		static int WaitUntraced( void );
		static int WaitNoHang( void );

	private:

		Cstdlib( const Cstdlib& );
		Cstdlib& operator = ( const Cstdlib& );

        long double strtox( const char *s, char** p, int prec );
	};

}//nsLinux

#endif//SYSTEMQOR_LIN_STDLIB_H_3