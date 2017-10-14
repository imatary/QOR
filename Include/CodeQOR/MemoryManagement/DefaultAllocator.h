//DefaultAllocator.h

// Copyright Querysoft Limited 2013, 2016
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

//Allocator template for simple unlimited allocation without garbage collection, pooling or preallocation

#ifndef CODEQOR_MEMMAN_ALLOCDEFAULT_H_1
#define CODEQOR_MEMMAN_ALLOCDEFAULT_H_1

#include "CompilerQOR.h"

#ifdef	__QCMP_OPTIMIZEINCLUDE
#pragma	__QCMP_OPTIMIZEINCLUDE
#endif//__QCMP_OPTIMIZEINCLUDE

#include "CodeQOR/Traits/MemoryTraits.h"
#include "CodeQOR/Instancing/DefaultInstancer.h"
#include <new>

//--------------------------------------------------------------------------------
namespace nsCodeQOR
{
    //--------------------------------------------------------------------------------
    template< typename TInstancer, typename T >
    class CDefaultAllocator
    {
    public:

		//--------------------------------------------------------------------------------
		//Calculate underlying allocation from boxed address by subtracting size of a pointer
		static void* Unbox(const void* pBoxed)
		{
			void* pBack = const_cast< byte* >((reinterpret_cast<const byte*>(pBoxed)) - sizeof(void*));
			return pBack;
		}

		//--------------------------------------------------------------------------------
		//Allocate memory with a pointer sized header that contains a back pointer to the stack allocated box
		static T* BoxAllocate(const void* pBack, unsigned int uiCount = 1)
		{			
			TInstancer Instancer;
			T* pResult = 0;
			if (uiCount == 1)
			{
				byte* pMemory = Instancer.Source().Source(sizeof(void*)+sizeof(T));
				pResult = reinterpret_cast<T*>(pMemory + sizeof(void*));
				*(reinterpret_cast<void**>(pMemory)) = const_cast< void* >(pBack);
			}
			else
			{
				byte* pMemory = Instancer.Source().Source( sizeof(unsigned int) + sizeof(void*) + (sizeof(T) * uiCount));
				*(reinterpret_cast< unsigned int* >(pMemory)) = uiCount;
				*(reinterpret_cast< void** >(pMemory + sizeof( unsigned int ) ) ) = const_cast< void* >(pBack);
				pResult = reinterpret_cast< T* >(pMemory + sizeof(void*) + sizeof(unsigned int));
			}
			return pResult;
		}

		//--------------------------------------------------------------------------------
		//Allocate raw byte space for n instances of type T. If n != 1 then allocate a unsigned int sized header to record n
		static T* RawAllocate( unsigned int uiCount = 1 )
		{			
			TInstancer Instancer;
			T* pResult = 0;
			if( uiCount == 1 )
			{
				byte* pMemory = Instancer.Source().Source(sizeof(T));
				pResult = reinterpret_cast<T*>(pMemory);
			}
			else
			{
				byte* pMemory = Instancer.Source().Source( sizeof( unsigned int ) + ( sizeof( T ) * uiCount ) );
				*( reinterpret_cast< unsigned int* >( pMemory ) ) = uiCount;
				pResult = reinterpret_cast< T* >( pMemory + sizeof( unsigned int ) );
			}
			return pResult;
		}

		//--------------------------------------------------------------------------------
		//Allocate 1 T using the instancer or uiCount Ts initializing them in place
        static T* Allocate( unsigned int uiCount = 1 )
        {
				TInstancer Instancer;
                T* pResult = 0;
                if( uiCount == 1 )
                {
                        pResult = Instancer.Instance();
                }
                else
                {
                        byte* pMemory = Instancer.Source().Source( sizeof( unsigned int ) + ( sizeof( T ) * uiCount ) );
                        *( reinterpret_cast< unsigned int* >( pMemory ) ) = uiCount;
                        pResult = reinterpret_cast< T* >( pMemory + sizeof( unsigned int ) );
                        T* pInit = pResult;

                        for( unsigned int uiLoop = 0; uiLoop < uiCount; uiLoop++ )
                        {
                                new (pInit)T;
                                pInit++;
                        }
                }
                return pResult;
        }

        //--------------------------------------------------------------------------------
        static T* Reallocate( T* pT, unsigned long ulOldCount, unsigned long ulNewCount, bool bPreserve = true )
        {
                if( !bPreserve )
                {
                        Free( pT, ulOldCount );
                        return Allocate( ulNewCount );
                }

                T* pNewT = Allocate( ulNewCount );
                unsigned long ulCount = 0;
                while( ulCount < ulOldCount && ulCount < ulNewCount )
                {
                        pNewT[ulCount] = pT[ulCount];
                        ulCount++;
                }
                Free( pT, ulOldCount );
                return pNewT;
        }


        //--------------------------------------------------------------------------------
		//Reverse a call to Allocate by using the instancer or destructing more than 1 T in place
        static void Free( T* pT, unsigned int uiCount = 1 )
        {
				TInstancer Instancer;
                if( pT != 0 )
                {
                        if( uiCount == 1 )
                        {
                                Instancer.Release( pT );
                        }
                        else
                        {
                                byte* pMemory = reinterpret_cast< byte* >( pT );
                                uiCount = *( reinterpret_cast< unsigned int* >( pMemory - sizeof( unsigned int ) ) );

                                for( unsigned int uiLoop = 0; uiLoop < uiCount; uiLoop++ )
                                {
                                        pT->~T();
                                        pT++;
                                }
                                Instancer.Source().Free( pMemory - sizeof( unsigned int ), sizeof(unsigned int) + ( sizeof( T ) * uiCount ) );
                        }
                }
        }

		//--------------------------------------------------------------------------------
		//Reverse a Boxed allocation or 1 or more Ts
		static void BoxFree(T* pT, unsigned int uiCount = 1)
		{
			TInstancer Instancer;
			if (pT != 0)
			{
				if (uiCount == 1)
				{
					pT->~T();
					byte* pMemory = reinterpret_cast<byte*>(pT) - sizeof(void*);
					Instancer.Source().Free( pMemory, sizeof(void*) + sizeof(T));
				}
				else
				{
					byte* pMemory = reinterpret_cast< byte* >(pT);
					uiCount = *(reinterpret_cast< unsigned int* >(pMemory - (sizeof(unsigned int)+sizeof(void*)) ));

					for (unsigned int uiLoop = 0; uiLoop < uiCount; uiLoop++)
					{
						pT->~T();
						pT++;
					}
					Instancer.Source().Free(pMemory - ( sizeof(unsigned int) + sizeof(void*) ), sizeof(unsigned int) + sizeof(void*) + (sizeof(T) * uiCount));
				}
			}
		}
	private:

		CDefaultAllocator(){}
		~CDefaultAllocator(){}
    };

}//nsCodeQOR

#endif//CODEQOR_MEMMAN_ALLOCDEFAULT_H_1
