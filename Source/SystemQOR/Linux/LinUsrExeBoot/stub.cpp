//stub.cpp

//Linux QOR executable bootstrap

#include "SystemQOR.h"
#include <stdlib.h>


/* Written 2011 Nicholas J. Kain, released as Public Domain */
/*
__asm__(".weak _init \n\
.weak _fini \n\
.text \n\
.global _start \n\
_start:  \n\
	xor %rbp,%rbp  \n\
	mov %rdx,%r9  \n\
	pop %rsi  \n\
	mov %rsp,%rdx  \n\
    andq $-16,%rsp  \n\
	mov $_fini,%r8  \n\
	mov $_init,%rcx  \n\
	mov $main,%rdi  \n\
	call __libc_start_main  \n\
1:	jmp 1b  \n\
")
*/

extern "C"
{


int main(int, char**, char**);
void _init() __attribute__((weak));
void _fini() __attribute__((weak));

__attribute__((noreturn)) int __libc_start_main( int (*main)(int,char **,char **), int argc, char **argv)
{
	char **envp = argv+argc+1;

#ifndef SHARED
//	__init_libc(envp, argv[0]);
//	_init();
//	uintptr_t a = (uintptr_t)&__init_array_start;
//	for (; a<(uintptr_t)&__init_array_end; a+=sizeof(void(*)()))
//		(*(void (**)())a)();
#endif

	/* Pass control to to application */
	exit(main(argc, argv, envp));
	//return -1;
}

void __cstart(long *p)
{
	int argc = p[0];
	char **argv = (char**)((void *)(p+1));
	__libc_start_main(main, argc, argv );//, _init, _fini, 0);
}


}//extern C

__asm__("\
.text \n\
.global _start \n\
_start: \n\
	xor %rbp,%rbp \n\
	mov %rsp,%rdi \n\
	andq $-16,%rsp \n\
	call __cstart \n\
");

