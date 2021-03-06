//MemoryManager.cpp

// Copyright (c) 2008-2010, Petr Kobalicek <kobalicek.petr@gmail.com>
// Copyright (c) Querysoft Limited 2012, 2015
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

#include "ArchQOR.h"
#include "ArchQOR/Common/Assembler/MemoryManager.h"
#include "ArchQOR/Common/Assembler/VirtualMemoryManager.h"
#include <string.h>
#include <assert.h>
#include "CodeQOR/Tracing/FunctionContextBase.h"

//------------------------------------------------------------------------------
namespace nsArch
{
	//------------------------------------------------------------------------------
	__QOR_IMPLEMENT_OCLASS_LUID(CMemoryManager);

	//------------------------------------------------------------------------------
	CMemoryManager::CMemoryManager() __QCMP_THROW
	{
		__QCS_MEMBER_FCONTEXT("CMemoryManager::CMemoryManager");
	}

	//------------------------------------------------------------------------------
	CMemoryManager::~CMemoryManager() __QCMP_THROW
	{
		__QCS_MEMBER_FCONTEXT("CMemoryManager::~CMemoryManager");
	}

	//------------------------------------------------------------------------------
	CMemoryManager* CMemoryManager::getGlobal() __QCMP_THROW
	{
		__QCS_FCONTEXT("CMemoryManager::getGlobal");
		static CVirtualMemoryManager memmgr;
		return &memmgr;
	}


#if defined(ASMJIT_MEMORY_MANAGER_DUMP)

	//------------------------------------------------------------------------------
	struct __QCMP_LOCAL GraphVizContext
	{
		GraphVizContext();
		~GraphVizContext();

		bool openFile(const char* fileName);
		void closeFile();

		void dumpNode(MemNode* node);
		void connect(MemNode* node, MemNode* other, const char* dst);

		FILE* file;
	};

	//------------------------------------------------------------------------------
	GraphVizContext::GraphVizContext() : file(NULL)
	{
	}

	//------------------------------------------------------------------------------
	GraphVizContext::~GraphVizContext()
	{
		closeFile();
	}

	//------------------------------------------------------------------------------
	bool GraphVizContext::openFile(const char* fileName)
	{
		file = fopen(fileName, "w");
		return file != NULL;
	}

	//------------------------------------------------------------------------------
	void GraphVizContext::closeFile()
	{
		if (file) { fclose(file); file = NULL; }
	}

	//------------------------------------------------------------------------------
	void GraphVizContext::dumpNode(MemNode* node)
	{
		fprintf(file, "  NODE_%p [shape=record, style=filled, color=%s, label=\"<L>|<C>Mem: %p, Used: %d/%d|<R>\"];\n",
		node,
		node->red ? "red" : "gray",
		node->mem, node->used, node->size);

		if (node->node[0]) connect(node, node->node[0], "L");
		if (node->node[1]) connect(node, node->node[1], "R");
	}

	//------------------------------------------------------------------------------
	void GraphVizContext::connect(MemNode* node, MemNode* other, const char* dst)
	{
		dumpNode(other);

		fprintf(file, "  NODE_%p:%s -> NODE_%p:C", node, dst, other);
		if (other->red) fprintf(file, " [style=bold, color=red]");
		fprintf(file, ";\n");
	}

	//------------------------------------------------------------------------------
	void VirtualMemoryManager::dump(const char* fileName)
	{
		MemoryManagerPrivate* d = reinterpret_cast<MemoryManagerPrivate*>(_d);
		GraphVizContext ctx;
		if (!ctx.openFile(fileName)) return;

		fprintf(ctx.file, "digraph {\n");
		if (d->_root) ctx.dumpNode(d->_root);
		fprintf(ctx.file, "}\n");
	}
#endif // ASMJIT_MEMORY_MANAGER_DUMP

}//nsArch
