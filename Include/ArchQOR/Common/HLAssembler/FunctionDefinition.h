//FunctionDefinition.h

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

#ifndef ARCHQOR_HLA_FUNCTIONDEF_H_2
#define ARCHQOR_HLA_FUNCTIONDEF_H_2

#include "CompilerQOR.h"
#include "ArchQOR/Common/Assembler/CodeGenerator.h"
#include "CodeQOR/DataTypes/GUID.h"
#include "CodeQOR/Macros/ClassIdentityMacros.h"

//------------------------------------------------------------------------------
namespace nsArch
{
	//TypeToId

//#	if defined(ASMJIT_HAS_PARTIAL_TEMPLATE_SPECIALIZATION)
#	if __QCMP_SUPPORTS( __QCMP_FEATURE_TEMPLATE_PARTIAL_SPECIALIZATION )

	//------------------------------------------------------------------------------
	template<typename T>
	struct TypeToId
	{
		enum 
		{ 
			Id = INVALID_VALUE 
		};
	};

	template<typename T>
	struct TypeToId<T*> 
	{ 
		enum 
		{ 
			Id = VARIABLE_TYPE_INTPTR 
		}; 
	};

#	else

	// Same trick is used in Qt, Boost, Fog and all other libraries that need something similar.
	//
	// It's easy. It's needed to use sizeof() to determine the size
	// of return value of this function. If size will be sizeof(char)
	// (this is our type) then type is pointer, otherwise it's not.

	template< typename T >
	char TypeToId_NoPtiHelper( T*(*)() );
	// And specialization.
	void* TypeToId_NoPtiHelper(...);

	//------------------------------------------------------------------------------
	template<typename T>
	struct TypeToId
	{
		// TypeInfo constants
		enum
		{
			// This is the hackery result.
			Id = ( sizeof(char) == sizeof( TypeToId_NoPtiHelper((T(*)())0) ) ? VARIABLE_TYPE_INTPTR : INVALID_VALUE )
		};
	};

#	endif 

#	define ASMJIT_DECLARE_TYPE_AS_ID(__T__, __Id__) \
	template<> \
	struct TypeToId<__T__> { enum { Id = __Id__ }; }

	// Declare void type and alternative.
	struct Void {};

#if	( __QCMP_COMPILER != __QCMP_CODEGEAR  )
	/*TODO: Move this to architecture specific HLA as variable tpyes don't always exist
	ASMJIT_DECLARE_TYPE_AS_ID(void, INVALID_VALUE);
	ASMJIT_DECLARE_TYPE_AS_ID(Void, INVALID_VALUE);

	ASMJIT_DECLARE_TYPE_AS_ID( Cmp__int8, VARIABLE_TYPE_GPD );
	ASMJIT_DECLARE_TYPE_AS_ID( Cmp_unsigned__int8, VARIABLE_TYPE_GPD );

	ASMJIT_DECLARE_TYPE_AS_ID( Cmp__int16, VARIABLE_TYPE_GPD );
	ASMJIT_DECLARE_TYPE_AS_ID( Cmp_unsigned__int16, VARIABLE_TYPE_GPD );

	ASMJIT_DECLARE_TYPE_AS_ID( Cmp__int32, VARIABLE_TYPE_GPD );
	ASMJIT_DECLARE_TYPE_AS_ID( Cmp_unsigned__int32, VARIABLE_TYPE_GPD );

#	if ( QOR_ARCH_WORDSIZE == 64 )
	ASMJIT_DECLARE_TYPE_AS_ID( Cmp__int64, VARIABLE_TYPE_GPQ );
	ASMJIT_DECLARE_TYPE_AS_ID( Cmp_unsigned__int64, VARIABLE_TYPE_GPQ );
#	endif // ASMJIT_X64

	ASMJIT_DECLARE_TYPE_AS_ID( float, VARIABLE_TYPE_FLOAT );
	ASMJIT_DECLARE_TYPE_AS_ID( double, VARIABLE_TYPE_DOUBLE );
	*/
#endif
	// Function Builder

	//------------------------------------------------------------------------------
	class __QOR_INTERFACE( __ARCHQOR ) CFunctionDefinition
	{

	public:

		__QOR_DECLARE_OCLASS_ID(CFunctionDefinition);

		CFunctionDefinition();
		~CFunctionDefinition();
		CFunctionDefinition( const CFunctionDefinition& src );
		CFunctionDefinition& operator = ( const CFunctionDefinition& src );

		//------------------------------------------------------------------------------
		// Get function arguments IDs.
		inline const Cmp_unsigned__int32* getArguments() const
		{
			return m_parguments;
		}

		//------------------------------------------------------------------------------
		// Get function arguments count.
		inline Cmp_unsigned__int32 getArgumentsCount() const
		{
			return m_uiArgumentsCount;
		}

		//------------------------------------------------------------------------------
		inline Cmp_unsigned__int32 getArgument( Cmp_unsigned__int32 id ) const
		{
			//assert(id < m_uiArgumentsCount);
			return m_parguments[ id ];
		}

		//------------------------------------------------------------------------------
		// Get function return value.
		inline Cmp_unsigned__int32 getReturnValue() const
		{
			return m_uiReturnValue;
		}

	protected:

		//------------------------------------------------------------------------------
		void SetDefinition(const Cmp_unsigned__int32* arguments, Cmp_unsigned__int32 argumentsCount, Cmp_unsigned__int32 returnValue )
		{
			m_parguments = arguments;
			m_uiArgumentsCount = argumentsCount;
			m_uiReturnValue = returnValue;
		}

		const Cmp_unsigned__int32* m_parguments;
		Cmp_unsigned__int32 m_uiArgumentsCount;
		Cmp_unsigned__int32 m_uiReturnValue;
	};

	//------------------------------------------------------------------------------
	// Custom function builder for up to 32 function arguments.
	class FunctionBuilderX : public CFunctionDefinition
	{
	public:

		//------------------------------------------------------------------------------
		inline FunctionBuilderX()
		{
			SetDefinition( _argumentsData, 0, static_cast< Cmp_unsigned__int32 >( INVALID_VALUE ) );
		}

		//------------------------------------------------------------------------------
		template< typename T >
		inline void addArgument()
		{
			addArgumentRaw( TypeToId< T >::Id );
		}

		//------------------------------------------------------------------------------
		template< typename T >
		inline void setArgument( Cmp_unsigned__int32 id )
		{
			setArgumentRaw( id, TypeToId< T >::Id );
		}

		//------------------------------------------------------------------------------
		template< typename T >
		inline void setReturnValue()
		{
			setReturnValueRaw( TypeToId< T >::Id );
		}

		//------------------------------------------------------------------------------
		inline void addArgumentRaw( Cmp_unsigned__int32 type )
		{
			//assert( m_uiArgumentsCount < FUNC_MAX_ARGS );
			_argumentsData[ m_uiArgumentsCount++ ] = type;
		}

		//------------------------------------------------------------------------------
		inline void setArgumentRaw( Cmp_unsigned__int32 id, Cmp_unsigned__int32 type )
		{
			//assert( id < m_uiArgumentsCount );
			_argumentsData[ id ] = type;
		}

		//------------------------------------------------------------------------------
		inline void setReturnValueRaw( Cmp_unsigned__int32 returnValue )
		{
			m_uiReturnValue = returnValue;
		}

	protected:

		Cmp_unsigned__int32 _argumentsData[ FUNC_MAX_ARGS ];
	};

	//------------------------------------------------------------------------------
	// Class used to build function without arguments.
	template<typename RET>
	struct FunctionBuilder0 : public CFunctionDefinition
	{
		FunctionBuilder0()
		{
			SetDefinition( 0 , 0, TypeToId< RET >::Id );
		}
	};

	//------------------------------------------------------------------------------
	// Class used to build function with 1 argument.
	template<typename RET, typename P0>
	struct FunctionBuilder1 : public CFunctionDefinition
	{
		FunctionBuilder1()
		{
			static const Cmp_unsigned__int32 args[] =
			{
				TypeToId< P0 >::Id
			};
			SetDefinition( args, __QCS_ARRAY_SIZE( args ), TypeToId< RET >::Id );
		}
	};

	//------------------------------------------------------------------------------
	// Class used to build function with 2 arguments.
	template<typename RET, typename P0, typename P1>
	struct FunctionBuilder2 : public CFunctionDefinition
	{
		FunctionBuilder2()
		{
			static const Cmp_unsigned__int32 args[] =
			{
				TypeToId< P0 >::Id,
				TypeToId< P1 >::Id
			};
			SetDefinition( args, __QCS_ARRAY_SIZE( args ), TypeToId< RET >::Id );
		}
	};

	//------------------------------------------------------------------------------
	// Class used to build function with 3 arguments.
	template< typename RET, typename P0, typename P1, typename P2 >
	struct FunctionBuilder3 : public CFunctionDefinition
	{
		FunctionBuilder3()
		{
			static const Cmp_unsigned__int32 args[] =
			{
				TypeToId< P0 >::Id,
				TypeToId< P1 >::Id,
				TypeToId< P2 >::Id
			};
			SetDefinition( args, __QCS_ARRAY_SIZE( args ), TypeToId< RET >::Id );
		}
	};

	//------------------------------------------------------------------------------
	// Class used to build function with 4 arguments.
	template< typename RET, typename P0, typename P1, typename P2, typename P3 >
	struct FunctionBuilder4 : public CFunctionDefinition
	{
		FunctionBuilder4()
		{
			static const Cmp_unsigned__int32 args[] =
			{
				TypeToId< P0 >::Id,
				TypeToId< P1 >::Id,
				TypeToId< P2 >::Id,
				TypeToId< P3 >::Id
			};
			_setDefinition( args, __QCS_ARRAY_SIZE( args ), TypeToId< RET >::Id );
		}
	};

	//------------------------------------------------------------------------------
	// Class used to build function with 5 arguments.
	template< typename RET, typename P0, typename P1, typename P2, typename P3, typename P4 >
	struct FunctionBuilder5 : public CFunctionDefinition
	{
		FunctionBuilder5()
		{
			static const Cmp_unsigned__int32 args[] =
			{
				TypeToId< P0 >::Id,
				TypeToId< P1 >::Id,
				TypeToId< P2 >::Id,
				TypeToId< P3 >::Id,
				TypeToId< P4 >::Id
			};
			_setDefinition( args, __QCS_ARRAY_SIZE( args ), TypeToId< RET >::Id );
		}
	};

	//------------------------------------------------------------------------------
	// Class used to build function with 6 arguments.
	template<typename RET, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5>
	struct FunctionBuilder6 : public CFunctionDefinition
	{
		FunctionBuilder6()
		{
			static const Cmp_unsigned__int32 args[] =
			{
				TypeToId< P0 >::Id,
				TypeToId< P1 >::Id,
				TypeToId< P2 >::Id,
				TypeToId< P3 >::Id,
				TypeToId< P4 >::Id,
				TypeToId< P5 >::Id
			};
			_setDefinition( args, __QCS_ARRAY_SIZE( args ), TypeToId< RET >::Id );
		}
	};

	//------------------------------------------------------------------------------
	// Class used to build function with 7 arguments.
	template<typename RET, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
	struct FunctionBuilder7 : public CFunctionDefinition
	{
		FunctionBuilder7()
		{
			static const Cmp_unsigned__int32 args[] =
			{
				TypeToId< P0 >::Id,
				TypeToId< P1 >::Id,
				TypeToId< P2 >::Id,
				TypeToId< P3 >::Id,
				TypeToId< P4 >::Id,
				TypeToId< P5 >::Id,
				TypeToId< P6 >::Id
			};
			SetDefinition( args, __QCS_ARRAY_SIZE( args ), TypeToId< RET >::Id );
		}
	};

	//------------------------------------------------------------------------------
	// Class used to build function with 8 arguments.
	template<typename RET, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>
	struct FunctionBuilder8 : public CFunctionDefinition
	{
		FunctionBuilder8()
		{
			static const Cmp_unsigned__int32 args[] =
			{
				TypeToId< P0 >::Id,
				TypeToId< P1 >::Id,
				TypeToId< P2 >::Id,
				TypeToId< P3 >::Id,
				TypeToId< P4 >::Id,
				TypeToId< P5 >::Id,
				TypeToId< P6 >::Id,
				TypeToId< P7 >::Id
			};
			SetDefinition( args, __QCS_ARRAY_SIZE( args ), TypeToId< RET >::Id );
		}
	};

	//------------------------------------------------------------------------------
	// Class used to build function with 9 arguments.
	template<typename RET, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8>
	struct FunctionBuilder9 : public CFunctionDefinition
	{
		FunctionBuilder9()
		{
			static const Cmp_unsigned__int32 args[] =
			{
				TypeToId< P0 >::Id,
				TypeToId< P1 >::Id,
				TypeToId< P2 >::Id,
				TypeToId< P3 >::Id,
				TypeToId< P4 >::Id,
				TypeToId< P5 >::Id,
				TypeToId< P6 >::Id,
				TypeToId< P7 >::Id,
				TypeToId< P8 >::Id
			};
			SetDefinition( args, __QCS_ARRAY_SIZE( args ), TypeToId< RET >::Id );
		}
	};

	//------------------------------------------------------------------------------
	// Class used to build function with 10 arguments.
	template< typename RET, typename P0, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9 >
	struct FunctionBuilder10 : public CFunctionDefinition
	{
		FunctionBuilder10()
		{
			static const Cmp_unsigned__int32 args[] =
			{
				TypeToId< P0 >::Id,
				TypeToId< P1 >::Id,
				TypeToId< P2 >::Id,
				TypeToId< P3 >::Id,
				TypeToId< P4 >::Id,
				TypeToId< P5 >::Id,
				TypeToId< P6 >::Id,
				TypeToId< P7 >::Id,
				TypeToId< P8 >::Id,
				TypeToId< P9 >::Id
			};
			SetDefinition( args, __QCS_ARRAY_SIZE( args ), TypeToId< RET >::Id );
		}
	};

}//nsArch

#endif//ARCHQOR_HLA_FUNCTIONDEF_H_2
