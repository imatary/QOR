//EInstruction.cpp

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

//Implement an x86 instruction emittable

#include "ArchQOR.h"

#if		( QOR_ARCH == QOR_ARCH_X86_32 || QOR_ARCH == QOR_ARCH_X86_64 )

#include "ArchQOR/x86/HLAssembler/Emittables/EInstruction.h"
#include "ArchQOR/x86/HLAssembler/x86HLAContext.h"
#include <assert.h>

//------------------------------------------------------------------------------
namespace nsArch
{
	//------------------------------------------------------------------------------
	namespace nsx86
	{
		//------------------------------------------------------------------------------
		CEInstruction::CEInstruction( Cx86HLAIntrinsics* c, Cmp_unsigned__int32 code, COperand** operandsData, Cmp_unsigned__int32 operandsCount ) __QCMP_THROW : CEmittable( (nsArch::CHighLevelAssemblerBase*)c, EMITTABLE_INSTRUCTION )
		{
			m_uiCode = code;
			m_uiEmitOptions = c->getEmitOptions();			
			c->setEmitOptions( 0 );// Each created instruction takes emit options and clears it.

			m_pOperands = operandsData;
			m_uiOperandsCount = operandsCount;			
			m_pVariables = 0;
			m_uiVariablesCount = 0;
			m_pMemOp = 0;

			Cmp_unsigned__int32 i;
			for( i = 0; i < operandsCount; i++ )
			{
				if( m_pOperands[ i ]->isMem() )
				{
					m_pMemOp = dynamic_cast< CMem* >( m_pOperands[ i ] );
					break;
				}
			}

			const InstructionDescription* id = &instructionDescription[ m_uiCode ];
			m_bIsSpecial = id->isSpecial();
			m_bIsFPU = id->isFPU();
			m_bIsGPBLoUsed = false;
			m_bIsGPBHiUsed = false;

			if( m_bIsSpecial )
			{
				// ${SPECIAL_INSTRUCTION_HANDLING_BEGIN}
				switch( m_uiCode )
				{
				case INST_CPUID:
					// Special...
					break;

				case INST_CBW:
				case INST_CDQE:
				case INST_CWDE:
					// Special...
					break;

				case INST_CMPXCHG:
				case INST_CMPXCHG8B:
#	if ( QOR_ARCH_WORDSIZE == 64 )
				case INST_CMPXCHG16B:
#	endif // ASMJIT_X64
					// Special...
					break;

#	if ( QOR_ARCH_WORDSIZE == 64 )
				case INST_DAA:
				case INST_DAS:
					// Special...
					break;
#	endif // 

				case INST_IMUL:
					switch (operandsCount)
					{
					case 2:
						// IMUL dst, src is not special instruction.
						m_bIsSpecial = false;
						break;
					case 3:
						if( !( m_pOperands[ 0 ]->isVar() && m_pOperands[ 1 ]->isVar() && m_pOperands[ 2 ]->isVarMem() ) )
						{
							m_bIsSpecial = false;		// Only IMUL dst_lo, dst_hi, reg/mem is special, all others not.
						}
						break;
					}
					break;
				case INST_MUL:
				case INST_IDIV:
				case INST_DIV:
					// Special...
					break;

				case INST_MOV_PTR:
					// Special...
					break;

				case INST_LAHF:
				case INST_SAHF:
					// Special...
					break;

				case INST_MASKMOVQ:
				case INST_MASKMOVDQU:
					// Special...
					break;

				case INST_ENTER:
				case INST_LEAVE:
					// Special...
					break;

				case INST_RET:
					// Special...
					break;

				case INST_MONITOR:
				case INST_MWAIT:
					// Special...
					break;

				case INST_POP:
				case INST_POPAD:
				case INST_POPFD:
				case INST_POPFQ:
					// Special...
					break;

				case INST_PUSH:
				case INST_PUSHAD:
				case INST_PUSHFD:
				case INST_PUSHFQ:
					// Special...
					break;

				case INST_RCL:
				case INST_RCR:
				case INST_ROL:
				case INST_ROR:
				case INST_SAL:
				case INST_SAR:
				case INST_SHL:
				case INST_SHR:
					// Rot instruction is special only if last operand is variable (register).
					m_bIsSpecial = m_pOperands[ 1 ]->isVar();
					break;

				case INST_SHLD:
				case INST_SHRD:
					// Shld/Shrd instruction is special only if last operand is variable (register).
					m_bIsSpecial = m_pOperands[ 2 ]->isVar();
					break;

				case INST_RDTSC:
				case INST_RDTSCP:
					// Special...
					break;

				case INST_REP_LODSB:
				case INST_REP_LODSD:
				case INST_REP_LODSQ:
				case INST_REP_LODSW:
				case INST_REP_MOVSB:
				case INST_REP_MOVSD:
				case INST_REP_MOVSQ:
				case INST_REP_MOVSW:
				case INST_REP_STOSB:
				case INST_REP_STOSD:
				case INST_REP_STOSQ:
				case INST_REP_STOSW:
				case INST_REPE_CMPSB:
				case INST_REPE_CMPSD:
				case INST_REPE_CMPSQ:
				case INST_REPE_CMPSW:
				case INST_REPE_SCASB:
				case INST_REPE_SCASD:
				case INST_REPE_SCASQ:
				case INST_REPE_SCASW:
				case INST_REPNE_CMPSB:
				case INST_REPNE_CMPSD:
				case INST_REPNE_CMPSQ:
				case INST_REPNE_CMPSW:
				case INST_REPNE_SCASB:
				case INST_REPNE_SCASD:
				case INST_REPNE_SCASQ:
				case INST_REPNE_SCASW:
					// Special...
					break;

				default:
					assert( 0 );
				}
				// ${SPECIAL_INSTRUCTION_HANDLING_END}
			}
		}

		//------------------------------------------------------------------------------
		CEInstruction::~CEInstruction() __QCMP_THROW
		{
		}

		//------------------------------------------------------------------------------
		void CEInstruction::getVariable( VarData* _candidate, VarAllocRecord*& cur, VarAllocRecord*& var )
		{
			for( var = cur; ;)
			{
				if( var == m_pVariables )
				{
					var = cur++;
					var->vdata = _candidate;
					var->vflags = 0;
					var->regMask = 0xFFFFFFFF;
					break;
				}
				
				var--;
				
				if( var->vdata == _candidate )
				{
					break;
				}
			}
			
			assert( var != 0 );
		}

		//------------------------------------------------------------------------------
		void CEInstruction::prepare( CHLAssemblerContextBase& hlac ) __QCMP_THROW
		{
			Cx86HLAContext& cc = dynamic_cast< Cx86HLAContext& >( hlac );
			/*
#	define __GET_VARIABLE(__vardata__) \
			{ \
			VarData* _candidate = __vardata__; \
			\
			for (var = cur; ;) \
			{ \
			if (var == m_pVariables) \
			{ \
			var = cur++; \
			var->vdata = _candidate; \
			var->vflags = 0; \
			var->regMask = 0xFFFFFFFF; \
			break; \
			} \
			\
			var--; \
			\
			if (var->vdata == _candidate) \
			{ \
			break; \
			} \
			} \
			\
			assert(var != 0); \
			}
			*/
			m_uiOffset = cc.GetCurrentOffset();

			const InstructionDescription* id = &instructionDescription[ m_uiCode ];

			Cmp_unsigned__int32 i, len = m_uiOperandsCount;
			Cmp_unsigned__int32 variablesCount = 0;

			for( i = 0; i < len; i++ )
			{
				COperand* o = m_pOperands[ i ];

				if( o->isVar() )
				{
					assert( o->getId() != INVALID_VALUE );
					VarData* vdata = ( dynamic_cast< Cx86HLAIntrinsics* >( m_pHLAssembler ) )->_getVarData( o->getId() );
					assert( vdata != 0 );

					CBaseVar* pVar = dynamic_cast< CBaseVar* >( o );
					if( pVar && pVar->isGPVar() )
					{
						if( pVar->isGPBLo() ) 
						{ 
							m_bIsGPBLoUsed = true; 
							vdata->registerGPBLoCount++; 
						};
						if( pVar->isGPBHi() ) 
						{ 
							m_bIsGPBHiUsed = true; 
							vdata->registerGPBHiCount++; 
						};
					}

					if( vdata->workOffset != m_uiOffset )
					{
						if( !cc._isActive( vdata ) )
						{
							cc._addActive( vdata );
						}

						vdata->workOffset = m_uiOffset;
						variablesCount++;
					}
				}
				else if( o->isMem() )
				{
					CMem& m( dynamic_cast< CMem& >( *o ) );
					if( ( m.getId() & OPERAND_ID_TYPE_MASK ) == OPERAND_ID_TYPE_VAR )
					{
						VarData* vdata = ( dynamic_cast< Cx86HLAIntrinsics* >( m_pHLAssembler ) )->_getVarData( m.getId() );
						assert( vdata != 0 );

						cc._markMemoryUsed( vdata );

						if( vdata->workOffset != m_uiOffset )
						{
							if( !cc._isActive( vdata ) )
							{
								cc._addActive( vdata );
							}

							vdata->workOffset = m_uiOffset;
							variablesCount++;
						}
					}
					else if( ( m.getBase() & OPERAND_ID_TYPE_MASK ) == OPERAND_ID_TYPE_VAR )
					{
						VarData* vdata = ( dynamic_cast< Cx86HLAIntrinsics* >( m_pHLAssembler ) )->_getVarData( m.getBase() );
						assert( vdata != 0 );

						if( vdata->workOffset != m_uiOffset )
						{
							if( !cc._isActive( vdata ) )
							{
								cc._addActive( vdata );
							}

							vdata->workOffset = m_uiOffset;
							variablesCount++;
						}
					}

					if( ( m.getIndex() & OPERAND_ID_TYPE_MASK ) == OPERAND_ID_TYPE_VAR )
					{
						VarData* vdata = ( dynamic_cast< Cx86HLAIntrinsics* >( m_pHLAssembler ) )->_getVarData( m.getIndex() );
						assert( vdata != 0 );

						if( vdata->workOffset != m_uiOffset )
						{
							if( !cc._isActive( vdata ) )
							{
								cc._addActive( vdata );
							}

							vdata->workOffset = m_uiOffset;
							variablesCount++;
						}
					}
				}
			}

			if( !variablesCount )
			{
				cc.IncrementCurrentOffset();
				return;
			}

			m_pVariables = reinterpret_cast< VarAllocRecord* >( ( dynamic_cast< Cx86HLAIntrinsics* >( m_pHLAssembler ) )->getZone().zalloc( sizeof( VarAllocRecord ) * variablesCount ) );
			if( !m_pVariables )
			{
				( dynamic_cast< Cx86HLAIntrinsics* >( m_pHLAssembler ) )->setError( ERROR_NO_HEAP_MEMORY );
				cc.IncrementCurrentOffset();
				return;
			}

			m_uiVariablesCount = variablesCount;

			VarAllocRecord* cur = m_pVariables;
			VarAllocRecord* var = 0;

			bool _isGPBUsed = m_bIsGPBLoUsed || m_bIsGPBHiUsed;
			Cmp_unsigned__int32 gpRestrictMask = nsCodeQOR::maskUpToIndex( REG_NUM_GP );

#	if ( QOR_ARCH_WORDSIZE == 64 )
			if( m_bIsGPBHiUsed )
			{
				gpRestrictMask &= nsCodeQOR::maskFromIndex( REG_INDEX_EAX ) |
					nsCodeQOR::maskFromIndex( REG_INDEX_EBX ) |
					nsCodeQOR::maskFromIndex( REG_INDEX_ECX ) |
					nsCodeQOR::maskFromIndex( REG_INDEX_EDX ) |
					nsCodeQOR::maskFromIndex( REG_INDEX_EBP ) |
					nsCodeQOR::maskFromIndex( REG_INDEX_ESI ) |
					nsCodeQOR::maskFromIndex( REG_INDEX_EDI ) ;
			}
#	endif // ASMJIT_X64

			for( i = 0; i < len; i++ )
			{
				COperand* o = m_pOperands[ i ];

				if( o->isVar() )
				{
					VarData* vdata = ( dynamic_cast< Cx86HLAIntrinsics* >( m_pHLAssembler ) )->_getVarData( o->getId() );
					assert( vdata != 0 );

					//__GET_VARIABLE( vdata )
					getVariable( vdata, cur, var );
					var->vflags |= VARIABLE_ALLOC_REGISTER;

					CBaseVar* pVar = dynamic_cast< CBaseVar* >( o );
					if( _isGPBUsed )
					{
						CGPVar* pGPVar = dynamic_cast< CGPVar* >( pVar );

#	if ( QOR_ARCH_WORDSIZE == 32 )
						if( pGPVar->isGPB() )
						{
							var->regMask &= nsCodeQOR::maskFromIndex( REG_INDEX_EAX ) |
									nsCodeQOR::maskFromIndex( REG_INDEX_EBX ) |
									nsCodeQOR::maskFromIndex( REG_INDEX_ECX ) |
									nsCodeQOR::maskFromIndex( REG_INDEX_EDX ) ;
						}
#	else
						// Restrict all BYTE registers to RAX/RBX/RCX/RDX if HI BYTE register
						// is used (REX prefix makes HI BYTE addressing unencodable).
						if( m_bIsGPBHiUsed )
						{
							if( pGPVar->isGPB() )
							{
								var->regMask &= nsCodeQOR::maskFromIndex( REG_INDEX_EAX ) |
										nsCodeQOR::maskFromIndex( REG_INDEX_EBX ) |
										nsCodeQOR::maskFromIndex( REG_INDEX_ECX ) |
										nsCodeQOR::maskFromIndex( REG_INDEX_EDX );
							}
						}
#	endif // 
					}

					if( isSpecial() )
					{
						// ${SPECIAL_INSTRUCTION_HANDLING_BEGIN}
						switch( m_uiCode )
						{
						case INST_CPUID:
							switch( i )
							{
							case 0:
								vdata->registerRWCount++;
								var->vflags |= VARIABLE_ALLOC_READWRITE | VARIABLE_ALLOC_SPECIAL;
								var->regMask = nsCodeQOR::maskFromIndex( REG_INDEX_EAX );
								gpRestrictMask &= ~var->regMask;
								break;
							case 1:
								vdata->registerWriteCount++;
								var->vflags |= VARIABLE_ALLOC_WRITE | VARIABLE_ALLOC_SPECIAL;
								var->regMask = nsCodeQOR::maskFromIndex( REG_INDEX_EBX );
								gpRestrictMask &= ~var->regMask;
								break;
							case 2:
								vdata->registerWriteCount++;
								var->vflags |= VARIABLE_ALLOC_WRITE | VARIABLE_ALLOC_SPECIAL;
								var->regMask = nsCodeQOR::maskFromIndex( REG_INDEX_ECX );
								gpRestrictMask &= ~var->regMask;
								break;
							case 3:
								vdata->registerWriteCount++;
								var->vflags |= VARIABLE_ALLOC_WRITE | VARIABLE_ALLOC_SPECIAL;
								var->regMask = nsCodeQOR::maskFromIndex( REG_INDEX_EDX );
								gpRestrictMask &= ~var->regMask;
								break;

							default:
								assert( 0 );
							}
							break;

						case INST_CBW:
						case INST_CDQE:
						case INST_CWDE:
							switch( i )
							{
							case 0:
								vdata->registerRWCount++;
								var->vflags |= VARIABLE_ALLOC_READWRITE | VARIABLE_ALLOC_SPECIAL;
								var->regMask = nsCodeQOR::maskFromIndex( REG_INDEX_EAX );
								gpRestrictMask &= ~var->regMask;
								break;

							default:
								assert( 0 );
							}
							break;

						case INST_CMPXCHG:
							switch( i )
							{
							case 0:
								vdata->registerRWCount++;
								var->vflags |= VARIABLE_ALLOC_READWRITE | VARIABLE_ALLOC_SPECIAL;
								var->regMask = nsCodeQOR::maskFromIndex( REG_INDEX_EAX );
								gpRestrictMask &= ~var->regMask;
								break;
							case 1:
								vdata->registerRWCount++;
								var->vflags |= VARIABLE_ALLOC_READWRITE;
								break;
							case 2:
								vdata->registerReadCount++;
								var->vflags |= VARIABLE_ALLOC_READ;
								break;

								default:
								assert( 0 );
							}
							break;

						case INST_CMPXCHG8B:
#	if ( QOR_ARCH_WORDSIZE == 64 )
						case INST_CMPXCHG16B:
#	endif // ASMJIT_X64
							switch( i )
							{
							case 0:
								vdata->registerRWCount++;
								var->vflags |= VARIABLE_ALLOC_READWRITE | VARIABLE_ALLOC_SPECIAL;
								var->regMask = nsCodeQOR::maskFromIndex( REG_INDEX_EDX );
								gpRestrictMask &= ~var->regMask;
								break;
							case 1:
								vdata->registerRWCount++;
								var->vflags |= VARIABLE_ALLOC_READWRITE | VARIABLE_ALLOC_SPECIAL;
								var->regMask = nsCodeQOR::maskFromIndex( REG_INDEX_EAX );
								gpRestrictMask &= ~var->regMask;
								break;
							case 2:
								vdata->registerReadCount++;
								var->vflags |= VARIABLE_ALLOC_READ | VARIABLE_ALLOC_SPECIAL;
								var->regMask = nsCodeQOR::maskFromIndex( REG_INDEX_ECX );
								gpRestrictMask &= ~var->regMask;
								break;
							case 3:
								vdata->registerReadCount++;
								var->vflags |= VARIABLE_ALLOC_READ | VARIABLE_ALLOC_SPECIAL;
								var->regMask = nsCodeQOR::maskFromIndex( REG_INDEX_EBX );
								gpRestrictMask &= ~var->regMask;
								break;

							default:
								assert( 0 );
							}
							break;

#	if ( QOR_ARCH_WORDSIZE == 32 )
							case INST_DAA:
							case INST_DAS:
								assert( i == 0 );
								vdata->registerRWCount++;
								var->vflags |= VARIABLE_ALLOC_READWRITE | VARIABLE_ALLOC_SPECIAL;
								var->regMask = nsCodeQOR::maskFromIndex( REG_INDEX_EAX );
								gpRestrictMask &= ~var->regMask;
								break;
#	endif // ( QOR_ARCH_WORDSIZE == 32 )

						case INST_IMUL:
						case INST_MUL:
						case INST_IDIV:
						case INST_DIV:
							switch( i )
							{
							case 0:
								vdata->registerWriteCount++;
								var->vflags |= VARIABLE_ALLOC_WRITE | VARIABLE_ALLOC_SPECIAL;
								var->regMask = nsCodeQOR::maskFromIndex( REG_INDEX_EDX );
								gpRestrictMask &= ~var->regMask;
								break;
							case 1:
								vdata->registerRWCount++;
								var->vflags |= VARIABLE_ALLOC_READWRITE | VARIABLE_ALLOC_SPECIAL;
								var->regMask = nsCodeQOR::maskFromIndex( REG_INDEX_EAX );
								gpRestrictMask &= ~var->regMask;
								break;
							case 2:
								vdata->registerReadCount++;
								var->vflags |= VARIABLE_ALLOC_READ;
								break;

							default:
								assert( 0 );
							}
							break;

						case INST_MOV_PTR:
							switch( i )
							{
							case 0:
								vdata->registerWriteCount++;
								var->vflags |= VARIABLE_ALLOC_WRITE | VARIABLE_ALLOC_SPECIAL;
								var->regMask = nsCodeQOR::maskFromIndex( REG_INDEX_EAX );
								gpRestrictMask &= ~var->regMask;
								break;
							case 1:
								vdata->registerReadCount++;
								var->vflags |= VARIABLE_ALLOC_READ | VARIABLE_ALLOC_SPECIAL;
								var->regMask = nsCodeQOR::maskFromIndex( REG_INDEX_EAX );
								gpRestrictMask &= ~var->regMask;
								break;
							default:
								assert( 0 );
							}
							break;

						case INST_LAHF:
							assert( i == 0 );
							vdata->registerWriteCount++;
							var->vflags |= VARIABLE_ALLOC_WRITE | VARIABLE_ALLOC_SPECIAL;
							var->regMask = nsCodeQOR::maskFromIndex( REG_INDEX_EAX );
							gpRestrictMask &= ~var->regMask;
							break;

						case INST_SAHF:
							assert( i == 0 );
							vdata->registerReadCount++;
							var->vflags |= VARIABLE_ALLOC_READ | VARIABLE_ALLOC_SPECIAL;
							var->regMask = nsCodeQOR::maskFromIndex( REG_INDEX_EAX );
							gpRestrictMask &= ~var->regMask;
							break;

						case INST_MASKMOVQ:
						case INST_MASKMOVDQU:
							switch( i )
							{
							case 0:
								vdata->registerReadCount++;
								var->vflags |= VARIABLE_ALLOC_READ | VARIABLE_ALLOC_SPECIAL;
								var->regMask = nsCodeQOR::maskFromIndex( REG_INDEX_EDI );
								gpRestrictMask &= ~var->regMask;
								break;
							case 1:
							case 2:
								vdata->registerReadCount++;
								var->vflags |= VARIABLE_ALLOC_READ;
								break;
							}
							break;

						case INST_ENTER:
						case INST_LEAVE:
							// TODO: SPECIAL INSTRUCTION.
							break;

						case INST_RET:
							// TODO: SPECIAL INSTRUCTION.
							break;

						case INST_MONITOR:
						case INST_MWAIT:
							// TODO: MONITOR/MWAIT (COMPILER).
							break;

						case INST_POP:
							// TODO: SPECIAL INSTRUCTION.
							break;

						case INST_POPAD:
						case INST_POPFD:
						case INST_POPFQ:
							// TODO: SPECIAL INSTRUCTION.
							break;

						case INST_PUSH:
							// TODO: SPECIAL INSTRUCTION.
							break;

						case INST_PUSHAD:
						case INST_PUSHFD:
						case INST_PUSHFQ:
							// TODO: SPECIAL INSTRUCTION.
							break;

						case INST_RCL:
						case INST_RCR:
						case INST_ROL:
						case INST_ROR:
						case INST_SAL:
						case INST_SAR:
						case INST_SHL:
						case INST_SHR:
							switch( i )
							{
							case 0:
								vdata->registerRWCount++;
								var->vflags |= VARIABLE_ALLOC_READWRITE;
								break;
							case 1:
								vdata->registerReadCount++;
								var->vflags |= VARIABLE_ALLOC_READ | VARIABLE_ALLOC_SPECIAL;
								var->regMask = nsCodeQOR::maskFromIndex( REG_INDEX_ECX );
								gpRestrictMask &= ~var->regMask;
								break;

							default:
								assert( 0 );
							}
							break;

						case INST_SHLD:
						case INST_SHRD:
							switch( i )
							{
							case 0:
								vdata->registerRWCount++;
								var->vflags |= VARIABLE_ALLOC_READWRITE;
								break;
							case 1:
								vdata->registerReadCount++;
								var->vflags |= VARIABLE_ALLOC_READ;
								break;
							case 2:
								vdata->registerReadCount++;
								var->vflags |= VARIABLE_ALLOC_READ | VARIABLE_ALLOC_SPECIAL;
								var->regMask = nsCodeQOR::maskFromIndex( REG_INDEX_ECX );
								gpRestrictMask &= ~var->regMask;
								break;

							default:
								assert( 0 );
							}
							break;

						case INST_RDTSC:
						case INST_RDTSCP:
							switch( i )
							{
							case 0:
								vdata->registerWriteCount++;
								var->vflags |= VARIABLE_ALLOC_WRITE | VARIABLE_ALLOC_SPECIAL;
								var->regMask = nsCodeQOR::maskFromIndex( REG_INDEX_EDX );
								gpRestrictMask &= ~var->regMask;
								break;
							case 1:
								vdata->registerWriteCount++;
								var->vflags |= VARIABLE_ALLOC_WRITE | VARIABLE_ALLOC_SPECIAL;
								var->regMask = nsCodeQOR::maskFromIndex( REG_INDEX_EAX );
								gpRestrictMask &= ~var->regMask;
								break;
							case 2:
								assert( m_uiCode == INST_RDTSCP );
								vdata->registerWriteCount++;
								var->vflags |= VARIABLE_ALLOC_WRITE | VARIABLE_ALLOC_SPECIAL;
								var->regMask = nsCodeQOR::maskFromIndex( REG_INDEX_ECX );
								gpRestrictMask &= ~var->regMask;
								break;

							default:
								assert( 0 );
							}
							break;

						case INST_REP_LODSB:
						case INST_REP_LODSD:
						case INST_REP_LODSQ:
						case INST_REP_LODSW:
							switch( i )
							{
							case 0:
								vdata->registerWriteCount++;
								var->vflags |= VARIABLE_ALLOC_WRITE | VARIABLE_ALLOC_SPECIAL;
								var->regMask = nsCodeQOR::maskFromIndex( REG_INDEX_EAX );
								gpRestrictMask &= ~var->regMask;
								break;
							case 1:
								vdata->registerReadCount++;
								var->vflags |= VARIABLE_ALLOC_READ | VARIABLE_ALLOC_SPECIAL;
								var->regMask = nsCodeQOR::maskFromIndex( REG_INDEX_ESI );
								gpRestrictMask &= ~var->regMask;
								break;
							case 2:
								vdata->registerRWCount++;
								var->vflags |= VARIABLE_ALLOC_READWRITE | VARIABLE_ALLOC_SPECIAL;
								var->regMask = nsCodeQOR::maskFromIndex( REG_INDEX_ECX );
								gpRestrictMask &= ~var->regMask;
								break;
							default:
								assert( 0 );
							}
							break;

						case INST_REP_MOVSB:
						case INST_REP_MOVSD:
						case INST_REP_MOVSQ:
						case INST_REP_MOVSW:
						case INST_REPE_CMPSB:
						case INST_REPE_CMPSD:
						case INST_REPE_CMPSQ:
						case INST_REPE_CMPSW:
						case INST_REPNE_CMPSB:
						case INST_REPNE_CMPSD:
						case INST_REPNE_CMPSQ:
						case INST_REPNE_CMPSW:
							switch( i )
							{
							case 0:
								vdata->registerReadCount++;
								var->vflags |= VARIABLE_ALLOC_READ | VARIABLE_ALLOC_SPECIAL;
								var->regMask = nsCodeQOR::maskFromIndex( REG_INDEX_EDI );
								gpRestrictMask &= ~var->regMask;
								break;
							case 1:
								vdata->registerReadCount++;
								var->vflags |= VARIABLE_ALLOC_READ | VARIABLE_ALLOC_SPECIAL;
								var->regMask = nsCodeQOR::maskFromIndex( REG_INDEX_ESI );
								gpRestrictMask &= ~var->regMask;
								break;
							case 2:
								vdata->registerRWCount++;
								var->vflags |= VARIABLE_ALLOC_READWRITE | VARIABLE_ALLOC_SPECIAL;
								var->regMask = nsCodeQOR::maskFromIndex( REG_INDEX_ECX );
								gpRestrictMask &= ~var->regMask;
								break;
							default:
								assert( 0 );
							}
							break;

						case INST_REP_STOSB:
						case INST_REP_STOSD:
						case INST_REP_STOSQ:
						case INST_REP_STOSW:
							switch( i )
							{
							case 0:
								vdata->registerReadCount++;
								var->vflags |= VARIABLE_ALLOC_READ | VARIABLE_ALLOC_SPECIAL;
								var->regMask = nsCodeQOR::maskFromIndex( REG_INDEX_EDI );
								gpRestrictMask &= ~var->regMask;
								break;
							case 1:
								vdata->registerReadCount++;
								var->vflags |= VARIABLE_ALLOC_READ | VARIABLE_ALLOC_SPECIAL;
								var->regMask = nsCodeQOR::maskFromIndex( REG_INDEX_EAX );
								gpRestrictMask &= ~var->regMask;
								break;
							case 2:
								vdata->registerRWCount++;
								var->vflags |= VARIABLE_ALLOC_READWRITE | VARIABLE_ALLOC_SPECIAL;
								var->regMask = nsCodeQOR::maskFromIndex( REG_INDEX_ECX );
								gpRestrictMask &= ~var->regMask;
								break;
							default:
								assert( 0 );
							}
							break;

						case INST_REPE_SCASB:
						case INST_REPE_SCASD:
						case INST_REPE_SCASQ:
						case INST_REPE_SCASW:
						case INST_REPNE_SCASB:
						case INST_REPNE_SCASD:
						case INST_REPNE_SCASQ:
						case INST_REPNE_SCASW:
							switch( i )
							{
							case 0:
								vdata->registerReadCount++;
								var->vflags |= VARIABLE_ALLOC_READ | VARIABLE_ALLOC_SPECIAL;
								var->regMask = nsCodeQOR::maskFromIndex( REG_INDEX_EDI );
								gpRestrictMask &= ~var->regMask;
								break;
							case 1:
								vdata->registerReadCount++;
								var->vflags |= VARIABLE_ALLOC_READ | VARIABLE_ALLOC_SPECIAL;
								var->regMask = nsCodeQOR::maskFromIndex( REG_INDEX_EAX );
								gpRestrictMask &= ~var->regMask;
								break;
							case 2:
								vdata->registerRWCount++;
								var->vflags |= VARIABLE_ALLOC_READWRITE | VARIABLE_ALLOC_SPECIAL;
								var->regMask = nsCodeQOR::maskFromIndex( REG_INDEX_ECX );
								gpRestrictMask &= ~var->regMask;
								break;
							default:
								assert( 0 );
							}
							break;

						default:
							assert( 0 );
						}
						// ${SPECIAL_INSTRUCTION_HANDLING_END}
					}
					else
					{
						if( i == 0 )
						{
							// CMP/TEST instruction.
							if( id->code == INST_CMP || id->code == INST_TEST )
							{
								// Read-only case.
								vdata->registerReadCount++;
								var->vflags |= VARIABLE_ALLOC_READ;
							}
							// CVTTSD2SI/CVTTSS2SI instructions.
							else if( id->code == INST_CVTTSD2SI || id->code == INST_CVTTSS2SI )
							{
								// In 32-bit mode the whole destination is replaced. In 64-bit mode
								// we need to check whether the destination operand size is 64-bits.
#if ( QOR_ARCH_WORDSIZE == 64 )
								if (m_pOperands[0]->isRegType(REG_TYPE_GPQ))
								{
#endif // X64
									// Write-only case.
									vdata->registerWriteCount++;
									var->vflags |= VARIABLE_ALLOC_WRITE;
#if ( QOR_ARCH_WORDSIZE == 64 )
								}
								else
								{
									// Read/Write.
									vdata->registerRWCount++;
									var->vflags |= VARIABLE_ALLOC_READWRITE;
								}
#endif // ASMJIT_X64
							}
							// MOV/MOVSS/MOVSD instructions.
							//
							// If instruction is MOV (source replaces the destination) or 
							// MOVSS/MOVSD and source operand is memory location then register
							// allocator should know that previous destination value is lost 
							// (write only operation).
							else if( ( id->isMov()) || ( ( id->code == INST_MOVSS || id->code == INST_MOVSD ) /* && _operands[1].isMem() */ ) || ( id->code == INST_IMUL && m_uiOperandsCount == 3 && !isSpecial() ) )
							{
								// Write-only case.
								vdata->registerWriteCount++;
								var->vflags |= VARIABLE_ALLOC_WRITE;
							}
							else if( id->code == INST_LEA )
							{
								// Write.
								vdata->registerWriteCount++;
								var->vflags |= VARIABLE_ALLOC_WRITE;
							}
							else
							{
								// Read/Write.
								vdata->registerRWCount++;
								var->vflags |= VARIABLE_ALLOC_READWRITE;
							}
						}
						else
						{
							// Second, third, ... operands are read-only.
							vdata->registerReadCount++;
							var->vflags |= VARIABLE_ALLOC_READ;
						}

						if( !m_pMemOp && i < 2 && ( id->oflags[ i ] & InstructionDescription::O_MEM ) != 0 )
						{
							var->vflags |= VARIABLE_ALLOC_MEMORY;
						}
					}

					// If variable must be in specific register we could add some hint to allocator.
					if( var->vflags & VARIABLE_ALLOC_SPECIAL )
					{
						vdata->prefRegisterMask |= nsCodeQOR::maskFromIndex( var->regMask );
						cc._newRegisterHomeIndex( vdata, nsCodeQOR::findFirstBit( var->regMask ) );
					}
				}
				else if( o->isMem() )
				{
					CMem& m( dynamic_cast< CMem& >( *o ) );
					if( ( m.getId() & OPERAND_ID_TYPE_MASK ) == OPERAND_ID_TYPE_VAR )
					{
						VarData* vdata = ( dynamic_cast< Cx86HLAIntrinsics* >( m_pHLAssembler ) )->_getVarData( m.getId() );
						assert( vdata != 0 );

						//__GET_VARIABLE( vdata )
						getVariable( vdata, cur, var );

						if( i == 0 )
						{
							// If variable is MOV instruction type (source replaces the destination)
							// or variable is MOVSS/MOVSD instruction then register allocator should
							// know that previous destination value is lost (write only operation).
							if( id->isMov() || ( ( id->code == INST_MOVSS || id->code == INST_MOVSD ) ) )
							{
								// Write only case.
								vdata->memoryWriteCount++;
							}
							else
							{
								vdata->memoryRWCount++;
							}
						}
						else
						{
							vdata->memoryReadCount++;
						}
					}
					else if( ( m.getBase() & OPERAND_ID_TYPE_MASK ) == OPERAND_ID_TYPE_VAR )
					{
						VarData* vdata = ( dynamic_cast< Cx86HLAIntrinsics* >( m_pHLAssembler ) )->_getVarData( m.getBase() );
						assert( vdata != 0 );

						//__GET_VARIABLE( vdata )
						getVariable( vdata, cur, var );
						vdata->registerReadCount++;
						var->vflags |= VARIABLE_ALLOC_REGISTER | VARIABLE_ALLOC_READ;
						var->regMask &= gpRestrictMask;
					}

					if( ( m.getIndex() & OPERAND_ID_TYPE_MASK ) == OPERAND_ID_TYPE_VAR )
					{
						VarData* vdata = ( dynamic_cast< Cx86HLAIntrinsics* >( m_pHLAssembler ) )->_getVarData( m.getIndex() );
						assert( vdata != 0 );

						//__GET_VARIABLE( vdata )
						getVariable( vdata, cur, var );
						vdata->registerReadCount++;
						var->vflags |= VARIABLE_ALLOC_REGISTER | VARIABLE_ALLOC_READ;
						var->regMask &= gpRestrictMask;
					}
				}
			}

			// Traverse all variables and update firstEmittable / lastEmittable. This
			// function is called from iterator that scans emittables using forward
			// direction so we can use this knowledge to optimize the process.
			
			// Similar to ECall::prepare().
			for( i = 0; i < m_uiVariablesCount; i++ )
			{
				VarData* v = m_pVariables[ i ].vdata;

				// Update GP register allocator restrictions.
				if( isVariableInteger( v->type ) )
				{
					if( m_pVariables[ i ].regMask == 0xFFFFFFFF )
					{
						m_pVariables[ i ].regMask &= gpRestrictMask;
					}
				}

				// Update first/last emittable (begin of variable scope).
				if( v->firstEmittable == 0 )
				{
					v->firstEmittable = this;
				}
				v->lastEmittable = this;
			}

			// There are some instructions that can be used to clear register or to set
			// register to some value (ideal case is all zeros or all ones).
			//
			// xor/pxor reg, reg    ; Set all bits in reg to 0.
			// sub/psub reg, reg    ; Set all bits in reg to 0.
			// andn reg, reg        ; Set all bits in reg to 0.
			// pcmpgt reg, reg      ; Set all bits in reg to 0.
			// pcmpeq reg, reg      ; Set all bits in reg to 1.

			if( m_uiVariablesCount == 1 && m_uiOperandsCount > 1 && m_pOperands[ 0 ]->isVar() && m_pOperands[ 1 ]->isVar() && !m_pMemOp )
			{
				switch( m_uiCode )
				{
				// XOR Instructions.
				case INST_XOR:
				case INST_XORPD:
				case INST_XORPS:
				case INST_PXOR:

				// ANDN Instructions.
				case INST_PANDN:

				// SUB Instructions.
				case INST_SUB:
				case INST_PSUBB:
				case INST_PSUBW:
				case INST_PSUBD:
				case INST_PSUBQ:
				case INST_PSUBSB:
				case INST_PSUBSW:
				case INST_PSUBUSB:
				case INST_PSUBUSW:

				// PCMPEQ Instructions.
				case INST_PCMPEQB:
				case INST_PCMPEQW:
				case INST_PCMPEQD:
				case INST_PCMPEQQ:

				// PCMPGT Instructions.
				case INST_PCMPGTB:
				case INST_PCMPGTW:
				case INST_PCMPGTD:
				case INST_PCMPGTQ:
					// Clear the read flag. This prevents variable alloc/spill.
					m_pVariables[ 0 ].vflags = VARIABLE_ALLOC_WRITE;
					m_pVariables[ 0 ].vdata->registerReadCount--;
					break;
				}
			}
			cc.IncrementCurrentOffset();

//#	undef __GET_VARIABLE
		}

		//------------------------------------------------------------------------------
		nsArch::CEmittable* CEInstruction::translate( CHLAssemblerContextBase& hlac ) __QCMP_THROW
		{
			Cx86HLAContext& cc = dynamic_cast< Cx86HLAContext& >( hlac );
			Cmp_unsigned__int32 i;
			Cmp_unsigned__int32 variablesCount = m_uiVariablesCount;

			if( variablesCount > 0 )
			{
				// These variables are used by the instruction and we set current offset
				// to their work offsets -> getSpillCandidate never return the variable
				// used this instruction.
				for( i = 0; i < variablesCount; i++ )
				{
					m_pVariables->vdata->workOffset = cc.GetCurrentOffset();
				}

				// Alloc variables used by the instruction (special first).
				for( i = 0; i < variablesCount; i++ )
				{
					VarAllocRecord& r = m_pVariables[ i ];
					// Alloc variables with specific register first.
					if( ( r.vflags & VARIABLE_ALLOC_SPECIAL ) != 0 )
					{
						cc.allocVar( r.vdata, r.regMask, r.vflags );
					}
				}

				for( i = 0; i < variablesCount; i++ )
				{
					VarAllocRecord& r = m_pVariables[ i ];
					// Alloc variables without specific register last.
					if( ( r.vflags & VARIABLE_ALLOC_SPECIAL ) == 0 )
					{
						cc.allocVar( r.vdata, r.regMask, r.vflags );
					}
				}

				cc.translateOperands( m_pOperands, m_uiOperandsCount );
			}

			if( m_pMemOp && ( m_pMemOp->getId() & OPERAND_ID_TYPE_MASK ) == OPERAND_ID_TYPE_VAR )
			{
				VarData* vdata = ( dynamic_cast< Cx86HLAIntrinsics* >( m_pHLAssembler ) )->_getVarData( m_pMemOp->getId() );
				assert( vdata != 0 );

				switch( vdata->state )
				{
				case VARIABLE_STATE_UNUSED:
					vdata->state = VARIABLE_STATE_MEMORY;
					break;
				case VARIABLE_STATE_REGISTER:
					vdata->changed = false;
					cc.unuseVar( vdata, VARIABLE_STATE_MEMORY );
					break;
				}
			}

			for( i = 0; i < variablesCount; i++ )
			{
				cc._unuseVarOnEndOfScope( this, &m_pVariables[ i ] );
			}

			return translated();
		}

		//------------------------------------------------------------------------------
		void CEInstruction::emit( CHighLevelAssemblerBase& ab ) __QCMP_THROW
		{

			CCPU* pAssembler = dynamic_cast< CCPU* >( ( dynamic_cast< Cx86HLAIntrinsics& >( ab ) ).getAssembler() );

			pAssembler->SetComment( m_szComment );
			pAssembler->SetEmitOptions( m_uiEmitOptions );

			if( isSpecial() )
			{
				// ${SPECIAL_INSTRUCTION_HANDLING_BEGIN}
				switch( m_uiCode )
				{
				case INST_CPUID:
					pAssembler->_emitInstruction( m_uiCode );
					return;

				case INST_CBW:
				case INST_CDQE:
				case INST_CWDE:
					pAssembler->_emitInstruction( m_uiCode );
					return;

				case INST_CMPXCHG:
					pAssembler->_emitInstruction( m_uiCode, m_pOperands[ 1 ], m_pOperands[ 2 ] );
					return;

				case INST_CMPXCHG8B:
#if ( QOR_ARCH_WORDSIZE == 64 )
					case INST_CMPXCHG16B:
#endif // ASMJIT_X64
					pAssembler->_emitInstruction( m_uiCode, m_pOperands[ 4 ] );
					return;

#if ( QOR_ARCH_WORDSIZE == 64 )
				case INST_DAA:
				case INST_DAS:
					pAssembler->_emitInstruction( m_uiCode );
					return;
#endif // 

				case INST_IMUL:
				case INST_MUL:
				case INST_IDIV:
				case INST_DIV:
					// INST dst_lo (implicit), dst_hi (implicit), src (explicit)
					assert( m_uiOperandsCount == 3 );
					pAssembler->_emitInstruction( m_uiCode, m_pOperands[ 2 ] );
					return;

				case INST_MOV_PTR:
					break;

				case INST_LAHF:
				case INST_SAHF:
					pAssembler->_emitInstruction( m_uiCode );
					return;

				case INST_MASKMOVQ:
				case INST_MASKMOVDQU:
					pAssembler->_emitInstruction( m_uiCode, m_pOperands[ 1 ], m_pOperands[ 2 ] );
					return;

				case INST_ENTER:
				case INST_LEAVE:
					// TODO: SPECIAL INSTRUCTION.
					break;

				case INST_RET:
					// TODO: SPECIAL INSTRUCTION.
					break;

				case INST_MONITOR:
				case INST_MWAIT:
					// TODO: MONITOR/MWAIT (COMPILER).
					break;

				case INST_POP:
				case INST_POPAD:
				case INST_POPFD:
				case INST_POPFQ:
					// TODO: SPECIAL INSTRUCTION.
					break;

				case INST_PUSH:
				case INST_PUSHAD:
				case INST_PUSHFD:
				case INST_PUSHFQ:
					// TODO: SPECIAL INSTRUCTION.
					break;

				case INST_RCL:
				case INST_RCR:
				case INST_ROL:
				case INST_ROR:
				case INST_SAL:
				case INST_SAR:
				case INST_SHL:
				case INST_SHR:
					pAssembler->_emitInstruction( m_uiCode, m_pOperands[ 0 ], &Cx86CPUCore::cl );
					return;

				case INST_SHLD:
				case INST_SHRD:
					pAssembler->_emitInstruction( m_uiCode, m_pOperands[ 0 ], m_pOperands[ 1 ], &Cx86CPUCore::cl );
					return;

				case INST_RDTSC:
				case INST_RDTSCP:
					pAssembler->_emitInstruction( m_uiCode );
					return;

				case INST_REP_LODSB:
				case INST_REP_LODSD:
				case INST_REP_LODSQ:
				case INST_REP_LODSW:
				case INST_REP_MOVSB:
				case INST_REP_MOVSD:
				case INST_REP_MOVSQ:
				case INST_REP_MOVSW:
				case INST_REP_STOSB:
				case INST_REP_STOSD:
				case INST_REP_STOSQ:
				case INST_REP_STOSW:
				case INST_REPE_CMPSB:
				case INST_REPE_CMPSD:
				case INST_REPE_CMPSQ:
				case INST_REPE_CMPSW:
				case INST_REPE_SCASB:
				case INST_REPE_SCASD:
				case INST_REPE_SCASQ:
				case INST_REPE_SCASW:
				case INST_REPNE_CMPSB:
				case INST_REPNE_CMPSD:
				case INST_REPNE_CMPSQ:
				case INST_REPNE_CMPSW:
				case INST_REPNE_SCASB:
				case INST_REPNE_SCASD:
				case INST_REPNE_SCASQ:
				case INST_REPNE_SCASW:
					pAssembler->_emitInstruction( m_uiCode );
					return;

				default:
					assert( 0 );
				}
				// ${SPECIAL_INSTRUCTION_HANDLING_END}
			}

			switch( m_uiOperandsCount )
			{
			case 0:
				pAssembler->_emitInstruction( m_uiCode );
				break;
			case 1:
				pAssembler->_emitInstruction( m_uiCode, m_pOperands[ 0 ] );
				break;
			case 2:
				pAssembler->_emitInstruction( m_uiCode, m_pOperands[ 0 ], m_pOperands[ 1 ] );
				break;
			case 3:
				pAssembler->_emitInstruction( m_uiCode, m_pOperands[ 0 ], m_pOperands[ 1 ], m_pOperands[ 2 ] );
				break;
			default:
				assert( 0 );
				break;
			}
		}

		//------------------------------------------------------------------------------
		int CEInstruction::getMaxSize() const __QCMP_THROW
		{
			// TODO: Do something more exact.
			return 15;
		}

		//------------------------------------------------------------------------------
		bool CEInstruction::tryUnuseVar( nsArch::CommonVarData* vdata ) __QCMP_THROW
		{
			VarData* v = reinterpret_cast< VarData* >( vdata );
			for( Cmp_unsigned__int32 i = 0; i < m_uiVariablesCount; i++ )
			{
				if( m_pVariables[ i ].vdata == v )
				{
					m_pVariables[ i ].vflags |= VARIABLE_ALLOC_UNUSE_AFTER_USE;
					return true;
				}
			}

			return false;
		}

		//------------------------------------------------------------------------------
		CETarget* CEInstruction::getJumpTarget() const __QCMP_THROW
		{
			return 0;
		}

	}//nsx86
}//nsArch

#endif//( QOR_ARCH == QOR_ARCH_X86_32 || QOR_ARCH == QOR_ARCH_X86_64 )
