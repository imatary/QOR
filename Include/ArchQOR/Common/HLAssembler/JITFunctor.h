//JITFunctor.h

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

#ifndef ARCHQOR_HLA_JITFUNCTOR_H_2
#define ARCHQOR_HLA_JITFUNCTOR_H_2

#include "CompilerQOR.h"
#include "ArchQOR/Common/Assembler/CodeGenerator.h"
#include "ArchQOR/Common/HLAssembler/HighLevelAssemblerBase.h"

//------------------------------------------------------------------------------
namespace nsArch
{
	//------------------------------------------------------------------------------
	class __QOR_INTERFACE(__ARCHQOR) CJITFunctorBase
	{
	public:

		//------------------------------------------------------------------------------
		CJITFunctorBase( CHighLevelAssemblerBase* pHLA, byte* pLaunchPad = 0 ) : m_bGenerated( false )
		, m_pHLA( pHLA )
		{
			Cmp_uint_ptr uiLaunchPadAddress = (Cmp_uint_ptr)(pLaunchPad);
			uiLaunchPadAddress = ( uiLaunchPadAddress | 0x08 ) & ( (Cmp_uint_ptr)(~0x07) );
			m_pLaunchPad = reinterpret_cast< byte* >( pLaunchPad );
		}

		//------------------------------------------------------------------------------
		~CJITFunctorBase()
		{
		}


	protected:

		bool m_bGenerated;
		CHighLevelAssemblerBase* m_pHLA;
		byte* m_pLaunchPad;

	};

	//------------------------------------------------------------------------------
	class __QOR_INTERFACE(__ARCHQOR) CVoidJITFunctor0 : public CJITFunctorBase
	{
	public:

		typedef void( *FP )( void );

		//------------------------------------------------------------------------------
		CVoidJITFunctor0( CHighLevelAssemblerBase* pHLA, byte* pLaunchPad  ) : CJITFunctorBase( pHLA, pLaunchPad )
		, m_pFunc( 0 )
		{
		}

		//------------------------------------------------------------------------------
		~CVoidJITFunctor0()
		{
		}

		//------------------------------------------------------------------------------
		void operator()()
		{
			if( !m_bGenerated )
			{
				m_pFunc = Generate();
			}

			if( !m_pFunc )
			{
				throw "Nul function pointer exception";
				//TODO: throw "Null function pointer exception";
			}

			(m_pFunc)();
		}

	protected:

		virtual FP Generate() = 0;

		FP m_pFunc;
	};

	//------------------------------------------------------------------------------
	template< typename RET >
	class __QOR_INTERFACE(__ARCHQOR) CJITFunctor0 : public CJITFunctorBase
	{
	public:

		typedef RET( *FP )( void );

		//------------------------------------------------------------------------------
		CJITFunctor0( CHighLevelAssemblerBase* pHLA, byte* pLaunchPad  ) : CJITFunctorBase( pHLA, pLaunchPad )
		, m_pFunc( 0 )
		{
		}

		//------------------------------------------------------------------------------
		~CJITFunctor0()
		{
		}

		//------------------------------------------------------------------------------
		RET operator()()
		{
			if( !m_bGenerated )
			{
				m_pFunc = Generate();
			}

			if( !m_pFunc )
			{
				//throw "Null function pointer exception";
			}

			return (m_pFunc)();
		}

	protected:

		virtual FP Generate() = 0;

		FP m_pFunc;
	};

	//------------------------------------------------------------------------------
	template< typename RET, typename P1 >
	class __QOR_INTERFACE(__ARCHQOR) CJITFunctor1 : public CJITFunctorBase
	{
	public:

		typedef RET( *FP )( P1 );

		//------------------------------------------------------------------------------
		CJITFunctor1( CHighLevelAssemblerBase* pHLA ) : CJITFunctorBase( pHLA )
		, m_pFunc( 0 )
		{
		}

		//------------------------------------------------------------------------------
		~CJITFunctor1()
		{
		}

		//------------------------------------------------------------------------------
		RET operator()( P1 p1, byte* pLaunchPad = 0 )
		{
			if( !m_bGenerated )
			{
				m_pFunc = Generate( pLaunchPad );
			}

			if( !m_pFunc )
			{
				//throw "Null function pointer exception";
			}

			return (m_pFunc)( p1 );
		}

	protected:

		virtual FP Generate( byte* pLaunchPad ) = 0;

		FP m_pFunc;
	};


	//------------------------------------------------------------------------------
	template< typename RET, typename P1, typename P2 >
	class __QOR_INTERFACE(__ARCHQOR) CJITFunctor2 : public CJITFunctorBase
	{
	public:

		typedef RET( *FP )( P1, P2 );

		//------------------------------------------------------------------------------
		CJITFunctor2( CHighLevelAssemblerBase* pHLA ) : CJITFunctorBase( pHLA )
		, m_pFunc( 0 )
		{
		}

		//------------------------------------------------------------------------------
		~CJITFunctor2()
		{
		}

		//------------------------------------------------------------------------------
		RET operator()( P1 p1, P2 p2 )
		{
			if( !m_bGenerated )
			{
				m_pFunc = Generate();
			}

			if( !m_pFunc )
			{
				//throw "Null function pointer exception";
			}

			return (m_pFunc)( p1, p2 );
		}

		//------------------------------------------------------------------------------
		operator FP( void )
		{
			if( !m_bGenerated )
			{
				m_pFunc = Generate();
			}

			return m_pFunc;
		}

	protected:

		virtual FP Generate( void ) = 0;

		FP m_pFunc;
	};

	//------------------------------------------------------------------------------
	template< typename RET, typename P1, typename P2, typename P3 >
	class __QOR_INTERFACE(__ARCHQOR) CJITFunctor3 : public CJITFunctorBase
	{
	public:

		typedef RET( *FP )( P1, P2, P3 );

		//------------------------------------------------------------------------------
		CJITFunctor3( CHighLevelAssemblerBase* pHLA ) : CJITFunctorBase( pHLA )
		, m_pFunc( 0 )
		{
		}

		//------------------------------------------------------------------------------
		~CJITFunctor3()
		{
		}

		//------------------------------------------------------------------------------
		RET operator()( P1 p1, P2 p2, P3 p3 )
		{
			if( !m_bGenerated )
			{
				m_pFunc = Generate();
			}

			if( !m_pFunc )
			{
				//throw "Null function pointer exception";
			}

			return (m_pFunc)( p1, p2, p3 );
		}

	protected:

		virtual FP Generate( void ) = 0;

		FP m_pFunc;
	};

}//nsArch

#endif//ARCHQOR_HLA_JITFUNCTOR_H_2
