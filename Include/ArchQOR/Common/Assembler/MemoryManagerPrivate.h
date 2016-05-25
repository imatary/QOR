//MemoryManagerPrivate.h

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

#ifndef ARCHQOR_MEMORYMANAGERPRIVATE_H_2
#define ARCHQOR_MEMORYMANAGERPRIVATE_H_2

#include "CompilerQOR.h"
//#include "ArchQOR/Defs.h"
#include "ArchQOR/Common/Assembler/VirtualMemory.h"

//------------------------------------------------------------------------------
namespace nsArch
{

	//------------------------------------------------------------------------------
	template< typename T >
	struct __QCMP_LOCAL RbNode
	{
		// [Node red-black tree tree, key is mem pointer].
		// Implementation is based on article by Julienne Walker (Public Domain),
		// including C code and original comments. Thanks for the excellent article.

		T* node[ 2 ];					// Left[0] and right[1] nodes.
		Cmp_unsigned__int32 red;		// Whether the node is RED.

		// [Chunk Memory]
		Cmp_unsigned__int8* mem;		// Virtual memory address.
	};

	//------------------------------------------------------------------------------
	struct __QCMP_LOCAL MemNode : public RbNode< MemNode >
	{
		// Node double-linked list

		MemNode* prev;           // Prev node in list.
		MemNode* next;           // Next node in list.

		// Chunk Data

		Cmp_uint_ptr size;          // How many bytes contain this node.
		Cmp_uint_ptr blocks;        // How many blocks are here.
		Cmp_uint_ptr density;       // Minimum count of allocated bytes in this node (also alignment).
		Cmp_uint_ptr used;          // How many bytes are used in this node.
		Cmp_uint_ptr largestBlock;  // Contains largest block that can be allocated.
		Cmp_uint_ptr* baUsed;       // Contains bits about used blocks. (0 = unused, 1 = used).
		Cmp_uint_ptr* baCont;       // Contains bits about continuous blocks. (0 = stop, 1 = continue).

		// Methods

		//------------------------------------------------------------------------------
		// Get available space.
		inline Cmp_uint_ptr getAvailable() const __QCMP_THROW
		{
			return size - used;
		}

		//------------------------------------------------------------------------------
		inline void fillData( MemNode* other )
		{
			mem = other->mem;
			size = other->size;
			blocks = other->blocks;
			density = other->density;
			used = other->used;
			largestBlock = other->largestBlock;
			baUsed = other->baUsed;
			baCont = other->baCont;
		}
	};


	//------------------------------------------------------------------------------
	class __QCMP_LOCAL PermanentNode
	{
	public:
		Cmp_unsigned__int8* mem;            // Base pointer (virtual memory address).
		Cmp_uint_ptr size;					// Count of bytes allocated.
		Cmp_uint_ptr used;					// Count of bytes used.
		PermanentNode* prev;				// Pointer to prev chunk or NULL.

		// Get available space.
		inline Cmp_uint_ptr getAvailable() const __QCMP_THROW
		{
			return size - used;
		}
	};

	//------------------------------------------------------------------------------
	class __QCMP_LOCAL MemoryManagerPrivate
	{
	public:

		MemoryManagerPrivate( nsCodeQOR::CProcessBase* hProcess) __QCMP_THROW;
		~MemoryManagerPrivate() __QCMP_THROW;

		// [Allocation]

		MemNode* createNode(Cmp_uint_ptr size, Cmp_uint_ptr density) __QCMP_THROW;

		void* allocPermanent(Cmp_uint_ptr vsize) __QCMP_THROW;
		void* allocFreeable(Cmp_uint_ptr vsize) __QCMP_THROW;

		bool free(void* address) __QCMP_THROW;
		bool shrink(void* address, Cmp_uint_ptr used) __QCMP_THROW;
		void freeAll(bool keepVirtualMemory) __QCMP_THROW;

		//------------------------------------------------------------------------------
		// Helpers to avoid ifdefs in the code.
		inline Cmp_unsigned__int8* allocVirtualMemory(Cmp_uint_ptr size, Cmp_uint_ptr* vsize) __QCMP_THROW
		{
#	if ( QOR_SYS_OS != QOR_SYS_MSW )
			return (Cmp_unsigned__int8*)CVirtualMemory::alloc(size, vsize, true);
#	else
			return (Cmp_unsigned__int8*)CVirtualMemory::s_OSPageAllocator.Alloc( _hProcess, size, vsize, true );//allocProcessMemory(_hProcess, size, vsize, true);
#	endif
		}

		//------------------------------------------------------------------------------
		inline void freeVirtualMemory(void* vmem, Cmp_uint_ptr vsize) __QCMP_THROW
		{
#	if ( QOR_SYS_OS != QOR_SYS_MSW )
			CVirtualMemory::free(vmem, vsize);
#	else
			CVirtualMemory::s_OSPageAllocator.Free( _hProcess, vmem, vsize );
#	endif
		}

		// [NodeList RB-Tree]
		bool checkTree() __QCMP_THROW;

		void insertNode( MemNode* node ) __QCMP_THROW;
		MemNode* removeNode( MemNode* node ) __QCMP_THROW;
		MemNode* findPtr( Cmp_unsigned__int8* mem ) __QCMP_THROW;

		nsCodeQOR::CProcessBase* _hProcess;            // Process where to allocate memory.

		//Lock _lock;                  // Lock for thread safety.

		Cmp_uint_ptr _newChunkSize;     // Default node size.
		Cmp_uint_ptr _newChunkDensity;  // Default node density.
		Cmp_uint_ptr _allocated;        // How many bytes are allocated.
		Cmp_uint_ptr _used;             // How many bytes are used.

		// Memory nodes list.
		MemNode* _first;
		MemNode* _last;
		MemNode* _optimal;
		MemNode* _root;					// Memory nodes tree.

		PermanentNode* _permanent;		// Permanent memory.
		bool _keepVirtualMemory;		// Whether to keep virtual memory after destroy.
	};

}//nsArch

#endif//ARCHQOR_MEMORYMANAGERPRIVATE_H_2
