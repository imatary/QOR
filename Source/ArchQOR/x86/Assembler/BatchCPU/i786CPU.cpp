//i786CPU.cpp

// Copyright (c) 2008-2010, Petr Kobalicek <kobalicek.petr@gmail.com>
// Copyright (c) Querysoft Limited 2013
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

//Implement i786 Assembler intrinsics for x86PC platform

#include "ArchQOR.h"

#if		( QOR_ARCH == QOR_ARCH_X86_32 || QOR_ARCH == QOR_ARCH_X86_64 )

#include "ArchQOR/x86/Assembler/BatchCPU/i786CPU.h"

//------------------------------------------------------------------------------
namespace nsArch
{
	namespace nsx86
	{
		//------------------------------------------------------------------------------
		Ci786CPU::Ci786CPU( CCodeGeneratorBase* codeGenerator ) : Ci686CPU( codeGenerator )
		{
		}

		//------------------------------------------------------------------------------
		Ci786CPU::~Ci786CPU() __QCMP_THROW
		{
		}


		//------------------------------------------------------------------------------
		CP7FPU::CP7FPU( Cx86CPUCore& refCPU ) : CP6FPU( refCPU )
		{
		}

		//------------------------------------------------------------------------------
		CP7FPU::~CP7FPU()
		{
		}

	}//nsx86
}//nsArch

#endif//( QOR_ARCH == QOR_ARCH_X86_32 || QOR_ARCH == QOR_ARCH_X86_64 )