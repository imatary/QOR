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

#ifndef WIN_PTHREAD_H
#define WIN_PTHREAD_H

//#include <windows.h>
#include <setjmp.h>
#include "rwlock.h"
#include "spinlock.h"


int _pthread_tryjoin(pthread_t t, void **res);
void _pthread_setnobreak(int);
#ifdef WINPTHREAD_DBG
void thread_print_set(int state);
void thread_print(volatile pthread_t t, char *txt);
#endif
int  __pthread_shallcancel(void);
//__CQOR_INTERFACE _pthread_v* __pth_gpointer_locked( pthread_t id );

#endif
