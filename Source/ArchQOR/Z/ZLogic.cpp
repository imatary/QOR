//ZLogic.cpp

// Copyright Querysoft Limited 2015
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

//Implement logical architecture for Z machine

#include "ArchQOR.h"

#if		( QOR_ARCH == QOR_ARCH_Z )

#include "CodeQOR/Tracing/FunctionContextBase.h"

//------------------------------------------------------------------------------
namespace nsArch
{
	//------------------------------------------------------------------------------
	namespace nsZ
	{
		//------------------------------------------------------------------------------
		__QOR_IMPLEMENT_OCLASS_LUID(CLogicalArch);

		//------------------------------------------------------------------------------
		CLogicalArch::CLogicalArch() : m_CPU( &m_CG )
		{
			__QCS_MEMBER_FCONTEXT("CLogicalArch::CLogicalArch");
		}

		//--------------------------------------------------------------------------------
		CLogicalArch::~CLogicalArch()
		{
			__QCS_MEMBER_FCONTEXT("CLogicalArch::~CLogicalArch");
		}

		//--------------------------------------------------------------------------------
		CCPUBase& CLogicalArch::CPU()
		{
			__QCS_MEMBER_FCONTEXT("CLogicalArch::CPU");
			return m_CPU;
		}

		//--------------------------------------------------------------------------------
		CFPUBase& CLogicalArch::FPU()
		{
			__QCS_MEMBER_FCONTEXT("CLogicalArch::FPU");
			CFPUBase* pFPU = dynamic_cast< CFPUBase* >( &m_CPU );
			return *pFPU;
		}

		//--------------------------------------------------------------------------------
		CGPUBase& CLogicalArch::GPU()
		{
			__QCS_MEMBER_FCONTEXT("CLogicalArch::GPU");
			return m_GPU;
		}

	}//nsZ
}//nsArch

#endif//( QOR_ARCH == QOR_ARCH_Z )