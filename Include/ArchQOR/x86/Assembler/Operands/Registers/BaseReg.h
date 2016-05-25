//BaseReg.h

// Copyright (c) 2008-2010, Petr Kobalicek <kobalicek.petr@gmail.com>
// Copyright (c) Querysoft Limited 2012
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

// Base class for all x86 registers.

#ifndef ARCHQOR_X86PC_ASSEMBLERBASEREG_H_2
#define ARCHQOR_X86PC_ASSEMBLERBASEREG_H_2

#include "../Operand.h"

//------------------------------------------------------------------------------
namespace nsArch
{
//------------------------------------------------------------------------------
namespace nsx86
{
	//------------------------------------------------------------------------------
	// Base class for all x86 registers.
	class __QOR_INTERFACE( __ARCHQOR ) CBaseReg : public COperand
	{
	public:

        virtual ~CBaseReg() __QCMP_THROW;
		CBaseReg( Cmp_unsigned__int32 code, Cmp_unsigned__int32 size ) __QCMP_THROW;        // Create a new base register.
		CBaseReg( const CBaseReg& other ) __QCMP_THROW;     // Create a new reference to other.
		CBaseReg( const nsCodeQOR::_DontInitialize& dontInitialize ) __QCMP_THROW;

		virtual void Init( const CBaseReg& other ) __QCMP_THROW;
		virtual COperand* Clone( CZone& zone ) const;

		Cmp_unsigned__int32 getRegCode() const __QCMP_THROW;        // Get register code, see REG.
		Cmp_unsigned__int32 getRegType() const __QCMP_THROW;        // Get register type, see REG.
		Cmp_unsigned__int32 getRegIndex() const __QCMP_THROW;       // Get register index (value from 0 to 7/15).
		virtual bool isRegCode( Cmp_unsigned__int32 code ) const __QCMP_THROW;      // Get whether register code is equal to code.
		virtual bool isRegType( Cmp_unsigned__int32 type ) const __QCMP_THROW;      // Get whether register code is equal to type.
		virtual bool isRegTypeMem( Cmp_unsigned__int32 regType ) const __QCMP_THROW;        // Get whether operand is register of regType type or memory.
		virtual bool isRegIndex( Cmp_unsigned__int32 index ) const __QCMP_THROW;        // Get whether register index is equal to index.
		void setCode( Cmp_unsigned__int32 code ) __QCMP_THROW;      // Set register code to code.
		void setSize( Cmp_unsigned__int32 size ) __QCMP_THROW;      // Set register size to size.

		CBaseReg& operator = ( const CBaseReg& other ) __QCMP_THROW;
		bool operator == ( const CBaseReg& other ) const __QCMP_THROW;
		bool operator != ( const CBaseReg& other ) const __QCMP_THROW;
		virtual bool isExtendedRegisterUsed() const __QCMP_THROW;       // Get whether the extended register (additional eight registers introduced by 64-bit mode) is used.

	protected:

		Cmp_unsigned__int32 m_Code;				// Register code or variable, see REG and INVALID_VALUE.
	};

}//nsx86
}//nsArch

#endif//ARCHQOR_X86PC_ASSEMBLERBASEREG_H_2