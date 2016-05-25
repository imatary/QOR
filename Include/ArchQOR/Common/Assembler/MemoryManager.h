//MemoryManager.h

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

#ifndef ARCHQOR_MEMORYMANAGER_H_2
#define ARCHQOR_MEMORYMANAGER_H_2

#include "CompilerQOR.h"
//#include "ArchQOR/Defs.h"
#include "ArchQOR/Common/HLAssembler/Defs.h"
#include "CodeQOR/DataTypes/GUID.h"
#include "CodeQOR/Macros/ClassIdentityMacros.h"

//------------------------------------------------------------------------------
namespace nsArch
{
	//------------------------------------------------------------------------------
	// This class is abstract. You can get default virtual memory manager using
	// getGlobal() method. If you want to create more memory managers with same
	// functionality as global memory manager use VirtualMemoryManager class.
	class __QOR_INTERFACE( __ARCHQOR ) CMemoryManager
	{
	public:

		__QOR_DECLARE_OCLASS_ID(CMemoryManager);

		CMemoryManager() __QCMP_THROW;				// Create memory manager instance.
		virtual ~CMemoryManager() __QCMP_THROW;		// Destroy memory manager instance, this means also to free all memory blocks.

		// Allocate a size bytes of virtual memory.
		// Note that if you are implementing your own virtual memory manager then you
		// can quietly ignore type of allocation. This is mainly for ArchQOR to memory
		// manager that allocated memory will be never freed.
		virtual void* alloc( Cmp_uint_ptr size, Cmp_unsigned__int32 type = MEMORY_ALLOC_FREEABLE ) __QCMP_THROW = 0;		
		virtual bool free( void* address ) __QCMP_THROW = 0;							// Free previously allocated memory at a given address.		
		virtual bool shrink( void* address, Cmp_uint_ptr used ) __QCMP_THROW = 0;		// Free some tail memory.		
		virtual void freeAll() __QCMP_THROW = 0;										// Free all allocated memory.
		virtual Cmp_uint_ptr getUsedBytes() __QCMP_THROW = 0;							// Get how many bytes are currently used.
		virtual Cmp_uint_ptr getAllocatedBytes() __QCMP_THROW = 0;						// Get how many bytes are currently allocated.

		// Get global memory manager instance.
		// Global instance is instance of CVirtualMemoryManager class. Global memory
		// manager is used by default by Assembler::make() and HLA::make() methods.
		static CMemoryManager* getGlobal() __QCMP_THROW;
	};

}//nsArch

#endif//ARCHQOR_MEMORYMANAGER_H_2
