//VirtualMemoryManager.h

// Copyright (c) 2008-2010, Petr Kobalicek <kobalicek.petr@gmail.com>
// Copyright (c) Querysoft Limited 2012
//
// Permission is hereby granted, free of charge, to any person
// obtaining a copy of this software and associated documentation
// files (the "Software"), to deal in the Software without
// restriction, including without limitation the rights to use,
// copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following
// conditions:
//
// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
// OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
// HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.

#ifndef ARCHQOR_VIRTUALMEMORYMANAGER_H_2
#define ARCHQOR_VIRTUALMEMORYMANAGER_H_2

#include "CompilerQOR.h"
//#include "ArchQOR/Defs.h"
#include "ArchQOR/Common/Assembler/MemoryManager.h"
#include "CodeQOR/Modules/ProcessBase.h"
#include "CodeQOR/DataTypes/GUID.h"
#include "CodeQOR/Macros/ClassIdentityMacros.h"

//------------------------------------------------------------------------------
namespace nsArch
{
	//------------------------------------------------------------------------------
	// Reference implementation of memory manager that uses VirtualMemory class to allocate chunks of virtual memory and bit arrays to manage it.
	class __QOR_INTERFACE( __ARCHQOR ) CVirtualMemoryManager : public CMemoryManager
	{
	public:

		__QOR_DECLARE_OCLASS_ID(CVirtualMemoryManager);

		CVirtualMemoryManager() __QCMP_THROW;			// Create a VirtualMemoryManager instance.

		// Create a VirtualMemoryManager instance for process hProcess.
		//
		// This is specialized version of constructor available only for windows and
		// usable to alloc/free memory of different process.
		CVirtualMemoryManager( nsCodeQOR::CProcessBase* pProcess ) __QCMP_THROW;

		// Destroy the VirtualMemoryManager instance, this means also to free all blocks.
		virtual ~CVirtualMemoryManager() __QCMP_THROW;

		virtual void* alloc( Cmp_uint_ptr size, Cmp_unsigned__int32 type = MEMORY_ALLOC_FREEABLE ) __QCMP_THROW;
		virtual bool free( void* address ) __QCMP_THROW;
		virtual bool shrink( void* address, Cmp_uint_ptr used ) __QCMP_THROW;
		virtual void freeAll() __QCMP_THROW;

		virtual Cmp_uint_ptr getUsedBytes() __QCMP_THROW;
		virtual Cmp_uint_ptr getAllocatedBytes() __QCMP_THROW;

		// Get whether to keep allocated memory after memory manager is destroyed.
		bool getKeepVirtualMemory() const __QCMP_THROW;

		// Set whether to keep allocated memory after memory manager is
		// destroyed.
		//
		// This method is usable when patching code of remote process. You need to
		// allocate process memory, store generated assembler into it and patch the
		// method you want to redirect (into your code). This method affects only
		// VirtualMemoryManager destructor. After destruction all internal
		// structures are freed, only the process virtual memory remains.
		//
		// Memory allocated with MEMORY_ALLOC_PERMANENT is always kept.
		void setKeepVirtualMemory( bool keepVirtualMemory ) __QCMP_THROW;

#if defined(ASMJIT_MEMORY_MANAGER_DUMP)
		// Dump memory manager tree into file.
		// Generated output is using DOT language (from graphviz package).
		void dump( const char* fileName );
#endif // ASMJIT_MEMORY_MANAGER_DUMP

	protected:

		void* _d;		// Pointer to private data
	};

}//nsArch
#endif//ARCHQOR_VIRTUALMEMORYMANAGER_H_2
