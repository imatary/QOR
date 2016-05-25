//MemoryMarker.h

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

#ifndef ARCHQOR_MEMORYMARKER_H_2
#define ARCHQOR_MEMORYMARKER_H_2

#include "ArchQOR.h"
#include "CodeQOR/Macros/codingmacros.h"
#include "CodeQOR/Macros/ClassIdentityMacros.h"
#include "CodeQOR/DataTypes/GUID.h"

//------------------------------------------------------------------------------
namespace nsArch
{
	//------------------------------------------------------------------------------
	class __QOR_INTERFACE( __ARCHQOR ) CMemoryMarker
	{
	public:

		__QOR_DECLARE_OCLASS_ID(CMemoryMarker);

		CMemoryMarker() __QCMP_THROW;
		virtual ~CMemoryMarker() __QCMP_THROW;

		virtual void mark( const void* ptr, Cmp_uint_ptr size ) __QCMP_THROW = 0;

	private:

		__QCS_DECLARE_NONCOPYABLE( CMemoryMarker );

	};

}//nsArch

#endif//ARCHQOR_MEMORYMARKER_H_2