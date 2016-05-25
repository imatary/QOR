// MSW_fenv.cpp

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

#include "SystemQOR.h"

#if		(QOR_SYS_OS == QOR_SYS_MSW)

#include "SystemQOR/MSWindows/MSW_fenv.h"
#include "WinQL/System/WinQLSystem.h"
#include "CodeQOR/Tracing/FunctionContextBase.h"

namespace nsWin32
{
	//--------------------------------------------------------------------------------
	Cfenv::Cfenv()
	{
		__QCS_MEMBER_FCONTEXT( "Cfenv::Cfenv" );
	}

	//--------------------------------------------------------------------------------
	Cfenv::~Cfenv()
	{
		__QCS_MEMBER_FCONTEXT( "Cfenv::~Cfenv" );
	}

	//--------------------------------------------------------------------------------
	///The feclearexcept() function shall attempt to clear the supported floating-point exceptions represented by excepts.
	///If the argument is zero or if all the specified exceptions were successfully cleared, feclearexcept() shall return zero. Otherwise, it shall return a non-zero value.
	int Cfenv::feclearexcept( int excepts )
	{
		__QCS_MEMBER_FCONTEXT( "Cfenv::feclearexcept" );
		nsArch::nsx86::C387FPU& fpu = dynamic_cast< nsArch::nsx86::C387FPU& >( TheMachine()->Logic().FPU() );
		return fpu.feclearexcept( excepts );		
	}

	//--------------------------------------------------------------------------------
	///The fegetexceptflag() function shall attempt to store an implementation-defined 
	///representation of the states of the floating-point status flags indicated by the 
	///argument excepts in the object pointed to by the argument flagp.
	///If the representation was successfully stored, fegetexceptflag() shall return zero. 
	///Otherwise, it shall return a non-zero value.
	int Cfenv::fegetexceptflag( fexcept_t* flagp, int excepts )
	{
		__QCS_MEMBER_FCONTEXT( "Cfenv::fegetexceptflag" );
		nsArch::nsx86::C387FPU& fpu = dynamic_cast< nsArch::nsx86::C387FPU& >( TheMachine()->Logic().FPU() );
		return fpu.fegetexceptflag( flagp, excepts );
	}

	//--------------------------------------------------------------------------------
	///The feraiseexcept() function shall attempt to raise the supported floating-point 
	///exceptions represented by the argument excepts. The order in which these 
	///floating-point exceptions are raised is unspecified. Whether the feraiseexcept() 
	///function additionally raises the inexact floating-point exception whenever it 
	///raises the overflow or underflow floating-point exception is implementation-defined.
	///If the argument is zero or if all the specified exceptions were successfully raised,
	///feraiseexcept() shall return zero. Otherwise, it shall return a non-zero value.
	int Cfenv::feraiseexcept( int excepts )
	{
		__QCS_MEMBER_FCONTEXT( "Cfenv::feraiseexcept" );
		nsArch::nsx86::C387FPU& fpu = dynamic_cast< nsArch::nsx86::C387FPU& >( TheMachine()->Logic().FPU() );
		return fpu.feraiseexcept( excepts );
	}

	//--------------------------------------------------------------------------------
	///The fesetexceptflag() function shall attempt to set the floating-point status 
	///flags indicated by the argument excepts to the states stored in the object pointed 
	///to by flagp. The value pointed to by flagp shall have been set by a previous call 
	///to fegetexceptflag() whose second argument represented at least those floating-point 
	///exceptions represented by the argument excepts. This function does not raise 
	///floating-point exceptions, but only sets the state of the flags.
	///If the excepts argument is zero or if all the specified exceptions were successfully 
	///set, fesetexceptflag() shall return zero. Otherwise, it shall return a non-zero 
	///value.
	int Cfenv::fesetexceptflag( const fexcept_t* flagp, int excepts )
	{
		__QCS_MEMBER_FCONTEXT( "Cfenv::fesetexceptflag" );
		nsArch::nsx86::C387FPU& fpu = dynamic_cast< nsArch::nsx86::C387FPU& >( TheMachine()->Logic().FPU() );
		return fpu.fesetexceptflag( flagp, excepts );
	}

	//--------------------------------------------------------------------------------
	///The fetestexcept() function shall return the value of the bitwise-inclusive OR 
	///of the floating-point exception macros corresponding to the currently set 
	///floating-point exceptions included in excepts.
	int Cfenv::fetestexcept( int excepts )
	{
		__QCS_MEMBER_FCONTEXT( "Cfenv::fetestexcept" );
		nsArch::nsx86::C387FPU& fpu = dynamic_cast< nsArch::nsx86::C387FPU& >( TheMachine()->Logic().FPU() );
		return fpu.fetestexcept( excepts );
	}

	//--------------------------------------------------------------------------------
	///The fegetround() function shall get the current rounding direction.
	///The fegetround() function shall return the value of the rounding direction macro 
	///representing the current rounding direction or a negative value if there is no 
	///such rounding direction macro or the current rounding direction is not determinable.
	int Cfenv::fegetround( void )
	{
		__QCS_MEMBER_FCONTEXT( "Cfenv::fegetround" );
		nsArch::nsx86::C387FPU& fpu = dynamic_cast< nsArch::nsx86::C387FPU& >( TheMachine()->Logic().FPU() );
		return fpu.fegetround();
	}

	//--------------------------------------------------------------------------------
	///The fesetround() function shall establish the rounding direction represented by 
	///its argument round. If the argument is not equal to the value of a rounding 
	///direction macro, the rounding direction is not changed.
	int Cfenv::fesetround( int round )
	{
		__QCS_MEMBER_FCONTEXT( "Cfenv::fesetround" );
		nsArch::nsx86::C387FPU& fpu = dynamic_cast< nsArch::nsx86::C387FPU& >( TheMachine()->Logic().FPU() );
		return fpu.fesetround( round );
	}

	//--------------------------------------------------------------------------------
	///The fegetenv() function shall attempt to store the current floating-point 
	///environment in the object pointed to by envp.
	///If the representation was successfully stored, fegetenv() shall return zero. 
	///Otherwise, it shall return a non-zero value. 
	int Cfenv::fegetenv( fenv_t* envp )
	{
		__QCS_MEMBER_FCONTEXT( "Cfenv::fegetenv" );
		nsArch::nsx86::C387FPU& fpu = dynamic_cast< nsArch::nsx86::C387FPU& >( TheMachine()->Logic().FPU() );
		return fpu.fegetenv( envp );
	}

	//--------------------------------------------------------------------------------
	///The feholdexcept() function shall save the current floating-point environment 
	///in the object pointed to by envp, clear the floating-point status flags, and then 
	///install a non-stop (continue on floating-point exceptions) mode, if available, 
	///for all floating-point exceptions.
	///The feholdexcept() function shall return zero if and only if non-stop 
	///floating-point exception handling was successfully installed.
	int Cfenv::feholdexcept( fenv_t* envp )
	{
		__QCS_MEMBER_FCONTEXT( "Cfenv::feholdexcept" );
		nsArch::nsx86::C387FPU& fpu = dynamic_cast< nsArch::nsx86::C387FPU& >( TheMachine()->Logic().FPU() );
		return fpu.feholdexcept( envp );
	}

	//--------------------------------------------------------------------------------
	///The fesetenv() function shall attempt to establish the floating-point environment 
	///represented by the object pointed to by envp. The argument envp shall point to an 
	///object set by a call to fegetenv() or feholdexcept(), or equal a floating-point 
	///environment macro. The fesetenv() function does not raise floating-point exceptions, 
	///but only installs the state of the floating-point status flags represented through 
	//its argument.
	///If the environment was successfully established, fesetenv() shall return zero. 
	///Otherwise, it shall return a non-zero value.
	int Cfenv::fesetenv( const fenv_t* envp )
	{
		__QCS_MEMBER_FCONTEXT( "Cfenv::fesetenv" );
		nsArch::nsx86::C387FPU& fpu = dynamic_cast< nsArch::nsx86::C387FPU& >( TheMachine()->Logic().FPU() );
		return fpu.fesetenv( envp );
	}

	//--------------------------------------------------------------------------------
	///The feupdateenv() function shall attempt to save the currently raised 
	///floating-point exceptions in its automatic storage, attempt to install the 
	///floating-point environment represented by the object pointed to by envp, and then 
	///attempt to raise the saved floating-point exceptions. The argument envp shall 
	///point to an object set by a call to feholdexcept() or fegetenv(), or equal a 
	///floating-point environment macro.
	int Cfenv::feupdateenv( const fenv_t* envp )
	{
		__QCS_MEMBER_FCONTEXT( "Cfenv::feupdateenv" );
		nsArch::nsx86::C387FPU& fpu = dynamic_cast< nsArch::nsx86::C387FPU& >( TheMachine()->Logic().FPU() );
		return fpu.feupdateenv( envp );
	}

}//nsWin32


#endif//(QOR_SYS_OS == QOR_SYS_MSW)