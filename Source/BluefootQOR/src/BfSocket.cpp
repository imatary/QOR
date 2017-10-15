//BfSocket.cpp

// Copyright Querysoft Limited 2016
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

//Implements a Bluefoot Socket class

#include "BluefootQOR/BfSocket.h"
#include "CodeQOR/Tracing/FunctionContextBase.h"

#if( QOR_SYS_OS == QOR_SYS_MSW )
#include "WinQL/Application/Comms/Network/WinQLSocket.h"
#endif
//------------------------------------------------------------------------------
namespace nsBluefoot
{
	__QOR_IMPLEMENT_OCLASS_LUID(ISocket);

	//------------------------------------------------------------------------------
	ISocket::Address::Address()
	{
		memset(&data, 0, byte_size);
	}

	//------------------------------------------------------------------------------
	ISocket::Address::Address(unsigned short AddressFamily) : Address()
	{
		sa_family = AddressFamily;
	}

	//------------------------------------------------------------------------------
	CSocket::CSocket() : m_Impl( new_shared_ref<nsPlatform::CSocket>().AsRef< ISocket >())
	{
		__QCS_MEMBER_FCONTEXT("CSocket::CSocket");
	}

	//------------------------------------------------------------------------------
	CSocket::CSocket(ISocket::ref_type Impl) : m_Impl( Impl )
	{
		__QCS_MEMBER_FCONTEXT("CSocket::CSocket");
	}

	//------------------------------------------------------------------------------
	CSocket::~CSocket()
	{
		__QCS_MEMBER_FCONTEXT("CSocket::~CSocket");
		m_Impl.Dispose();
	}

	//------------------------------------------------------------------------------
	CSocket::CSocket(const CSocket& src)
	{
		__QCS_MEMBER_FCONTEXT("CSocket::CSocket");
		*this = src;
	}

	//------------------------------------------------------------------------------
	CSocket& CSocket::operator = (const CSocket& src)
	{
		__QCS_MEMBER_FCONTEXT("CSocket::operator=");
		m_Impl.Dispose();
		m_Impl = src.m_Impl;
		return *this;
	}

	//------------------------------------------------------------------------------
	void CSocket::Create(eAddressFamily AF, eType Type, eProtocol Protocol)
	{
		__QCS_MEMBER_FCONTEXT("CSocket::Create");
		m_Impl().Create(AF, Type, Protocol);
	}

	//------------------------------------------------------------------------------
	int CSocket::Bind( const Address& Address )
	{
		__QCS_MEMBER_FCONTEXT("CSocket::Bind");
		return m_Impl().Bind(Address);
	}

	//------------------------------------------------------------------------------
	int CSocket::Listen(int iBacklog)
	{
		__QCS_MEMBER_FCONTEXT("CSocket::Listen");
		return m_Impl().Listen(iBacklog);
	}

	//------------------------------------------------------------------------------
	ISocket::ref_type CSocket::Accept( Address& Addr )
	{
		__QCS_MEMBER_FCONTEXT("CSocket::Accept");
		return m_Impl().Accept(Addr);
	}

	//------------------------------------------------------------------------------
	int CSocket::Connect( const Address& Addr )
	{
		__QCS_MEMBER_FCONTEXT("CSocket::Connect");
		return m_Impl().Connect(Addr);
	}

	//------------------------------------------------------------------------------
	int CSocket::GetPeerName( Address& Addr )
	{
		__QCS_MEMBER_FCONTEXT("CSocket::GetPeerName");
		return m_Impl().GetPeerName( Addr );
	}

	//------------------------------------------------------------------------------
	int CSocket::GetSockName( Address& Addr )
	{
		__QCS_MEMBER_FCONTEXT("CSocket::GetSockName");
		return m_Impl().GetSockName( Addr );
	}

	//------------------------------------------------------------------------------
	int CSocket::GetSockOpt(int iLevel, int iOptName, char* pOptVal, int* pOptLen)
	{
		__QCS_MEMBER_FCONTEXT("CSocket::GetSockOpt");
		return m_Impl().GetSockOpt(iLevel, iOptName, pOptVal, pOptLen);
	}

	//------------------------------------------------------------------------------
	int CSocket::SetSockOpt(int iLevel, int iOptName, const char* pOptVal, int iOptLen)
	{
		__QCS_MEMBER_FCONTEXT("CSocket::SetSockOpt");
		return m_Impl().SetSockOpt(iLevel, iOptName, pOptVal, iOptLen);
	}

	//------------------------------------------------------------------------------
	int CSocket::AsyncReceive(char* pBuffer, int iLen, void* pSyncObject)
	{
		__QCS_MEMBER_FCONTEXT("CSocket::AsyncReceive");
		return m_Impl().AsyncReceive(pBuffer, iLen, pSyncObject );
	}

	//------------------------------------------------------------------------------
	int CSocket::Receive(char* buf, int len, int flags)
	{
		__QCS_MEMBER_FCONTEXT("CSocket::Receive");
		return m_Impl().Receive(buf, len, flags);
	}

	//------------------------------------------------------------------------------
	int CSocket::ReceiveFrom(char* Buffer, int iLen, int iFlags, Address& From )
	{
		__QCS_MEMBER_FCONTEXT("CSocket::ReceiveFrom");
		return m_Impl().ReceiveFrom(Buffer, iLen, iFlags, From );
	}

	//------------------------------------------------------------------------------
	int CSocket::AsyncSend(char* Buffer, int iLen, void* pSyncObject )
	{
		__QCS_MEMBER_FCONTEXT("CSocket::AsyncSend");
		return m_Impl().AsyncSend(Buffer, iLen, pSyncObject);
	}

	//------------------------------------------------------------------------------
	int CSocket::Send(const char* Buffer, int iLen)
	{
		__QCS_MEMBER_FCONTEXT("CSocket::Send");
		return m_Impl().Send(Buffer, iLen);
	}

	//------------------------------------------------------------------------------
	int CSocket::SendTo(const char* Buffer, int iLen, int iFlags, const Address& To )
	{
		__QCS_MEMBER_FCONTEXT("CSocket::SendTo");
		return m_Impl().SendTo(Buffer, iLen, iFlags, To );
	}

	//------------------------------------------------------------------------------
	int CSocket::Shutdown(int iHow)
	{
		__QCS_MEMBER_FCONTEXT("CSocket::Shutdown");
		return m_Impl().Shutdown( iHow );
	}

	//------------------------------------------------------------------------------
	Cmp_uint_ptr CSocket::ID(void)
	{
		__QCS_MEMBER_FCONTEXT("CSocket::ID");
		return m_Impl().ID();
	}

	//------------------------------------------------------------------------------
	int CSocket::GetLastError(void)
	{
		__QCS_MEMBER_FCONTEXT("CSocket::GetLastError");
		return m_Impl().GetLastError();
	}




	__QOR_IMPLEMENT_OCLASS_LUID(CSocketConnector);

	//--------------------------------------------------------------------------------
	CSocketConnector::CSocketConnector(CConnectionPool* pPool) : CPlug(pPool)
	, m_Type(CSocket::Sock_Stream)
	, m_AddressFamily(CSocket::AF_INet)
	, m_iProtocol(CSocket::IPProto_TCP)
	, m_Socket( new_shared_ref< CSocket >().AsRef<ISocket>() )
	{
		__QCS_MEMBER_FCONTEXT("CSocketConnector::CSocketConnector");
		memset(&m_Address, 0, sizeof(ISocket::Address));
	}

	//--------------------------------------------------------------------------------
	CSocketConnector::~CSocketConnector()
	{
		__QCS_MEMBER_FCONTEXT("CSocketConnector::~CSocketConnector");
		if (m_bConnected)
		{
			Disconnect();
		}
	}

	//--------------------------------------------------------------------------------
	void CSocketConnector::SetAddress( const ISocket::Address& Address)
	{
		m_AddressFamily = static_cast< CSocket::eAddressFamily >(Address.sa_family);
		m_Address = Address;
	}

	//--------------------------------------------------------------------------------
	void CSocketConnector::SetType(CSocket::eType Type)
	{
		m_Type = Type;
	}

	//--------------------------------------------------------------------------------
	CSocket::eType CSocketConnector::GetType(void)
	{
		return m_Type;
	}

	//--------------------------------------------------------------------------------
	void CSocketConnector::SetAddressFamily(CSocket::eAddressFamily AddressFamily)
	{
		m_AddressFamily = AddressFamily;
	}

	//--------------------------------------------------------------------------------
	CSocket::eAddressFamily CSocketConnector::GetAddressFamily(void)
	{
		return m_AddressFamily;
	}

	//--------------------------------------------------------------------------------
	void CSocketConnector::SetProtocol(ISocket::eProtocol Protocol)
	{
		m_iProtocol = Protocol;
	}

	//--------------------------------------------------------------------------------
	ISocket::eProtocol CSocketConnector::GetProtocol(void)
	{
		return m_iProtocol;
	}
	//--------------------------------------------------------------------------------
	bool CSocketConnector::Connect()
	{
		__QCS_MEMBER_FCONTEXT("CSocketConnector::Connect");

		m_Socket().Create(m_AddressFamily, m_Type, m_iProtocol);

		if (m_Socket().ID() != 0 && m_Socket().ID() != (Cmp_uint_ptr)(-1))
		{
			m_Address.sa_family = static_cast< unsigned short >(m_AddressFamily);
			m_bConnected = m_Socket().Connect(m_Address) == 0 ? true : false;

			if (!AsyncConnection())
			{
				m_bConnected ? OnConnected() : OnConnectionError();
			}
		}
		return m_bConnected;
	}

	//--------------------------------------------------------------------------------
	void CSocketConnector::Disconnect()
	{
		__QCS_MEMBER_FCONTEXT("CSocketConnector::Disconnect");

		m_Socket().Shutdown(0);

		m_bConnected = false;
		if (!AsyncConnection())
		{
			//bClosed ? OnDisconnected() : OnDisconnectionError();
		}
	}

	//--------------------------------------------------------------------------------
	bool CSocketConnector::HandlePendingConnectionResult(bool bConnected)
	{
		__QCS_MEMBER_FCONTEXT("CSocketConnector::HandlePendingConnectionResult");

		if (bConnected)
		{
			return true;
		}

		return false;
	}




	//------------------------------------------------------------------------------
	__QOR_IMPLEMENT_OCLASS_LUID(CSocketSource);
	//------------------------------------------------------------------------------
	CSocketSource::CSocketSource(CSocketConnector* pSocketConnector) : CIOSource(pSocketConnector)
	{
		__QCS_MEMBER_FCONTEXT("CSocketSource::CSocketSouce");
	}

	//------------------------------------------------------------------------------
	CSocketSource::~CSocketSource()
	{
		__QCS_MEMBER_FCONTEXT("CSocketSource::~CSocketSouce");
	}

	//------------------------------------------------------------------------------
	bool CSocketSource::Read(unsigned long& ulNumberOfUnitsRead, unsigned long ulNumberOfUnitsToRead)
	{
		__QCS_MEMBER_FCONTEXT("CSocketSource::Read");
		bool bResult = false;
		CSocketConnector* pConnector = dynamic_cast< CSocketConnector* >(m_pIOSourceConnector);
		if (pConnector && pConnector->IsConnected())
		{
			byte* pBuffer = GetBuffer()->WriteRequest(ulNumberOfUnitsToRead);

			if (pConnector->AsyncConnection())
			{
				bResult = pConnector->Socket()->AsyncReceive((char*)pBuffer, ulNumberOfUnitsToRead * GetBuffer()->GetUnitSize(), pConnector->GetSyncObject()) ? true : false;
				ulNumberOfUnitsRead = 0;

				if (!bResult)
				{
					OnReadError(pConnector->Socket()->GetLastError(), ulNumberOfUnitsRead);
				}
			}
			else
			{
				if (pConnector->Socket()->Receive((char*)pBuffer, ulNumberOfUnitsToRead * GetBuffer()->GetUnitSize(), 0) > 0 )
				{
					ulNumberOfUnitsRead = ulNumberOfUnitsToRead;
					GetBuffer()->WriteAcknowledge(ulNumberOfUnitsRead);
					bResult = true;
				}

				if (bResult && ulNumberOfUnitsRead == 0)
				{
					OnEndOfData();
				}
				else
				{
					if (bResult)
					{
						OnReadSuccess(ulNumberOfUnitsRead);
					}
					else
					{
						OnReadError(pConnector->Socket()->GetLastError(), ulNumberOfUnitsRead);
					}
				}
			}
		}
		return bResult;
	}

	//------------------------------------------------------------------------------
	bool CSocketSource::IsAtEnd(void)
	{
		__QCS_MEMBER_FCONTEXT("CSocketSource::IsAtEnd");
		bool bResult = false;
		return bResult;
	}




	//------------------------------------------------------------------------------
	__QOR_IMPLEMENT_OCLASS_LUID(CSocketSink);
	//------------------------------------------------------------------------------
	CSocketSink::CSocketSink(CSocketConnector* pSocketConnector) : CIOSink(pSocketConnector)
	{
		__QCS_MEMBER_FCONTEXT("CSocketSink::CSocketSink");
	}

	//------------------------------------------------------------------------------
	CSocketSink::~CSocketSink()
	{
		__QCS_MEMBER_FCONTEXT("CSocketSink::~CSocketSink");
	}

	//------------------------------------------------------------------------------
	bool CSocketSink::AsyncWrite(unsigned long& ulNumberOfUnitsWritten, unsigned long ulNumberOfUnitsToWrite, ISocket::ref_type Socket, void* pSyncObject )
	{
		bool bResult = false;
		byte* pBuffer = GetSource()->GetBuffer()->ReadRequest(ulNumberOfUnitsToWrite);
		ulNumberOfUnitsWritten = 0;

		if (pBuffer)
		{
			unsigned long ulUnitSize = GetSource()->GetBuffer()->GetUnitSize();
			int iBytes = Socket->AsyncSend((char*)(pBuffer), ulNumberOfUnitsToWrite * ulUnitSize, pSyncObject);
			ulNumberOfUnitsWritten = static_cast<unsigned int>( iBytes ) / ulUnitSize;
			bResult = (ulNumberOfUnitsWritten > 0) ? true : false;
		}
		
		if (!bResult )
		{
			WriteError.OnSignaled();
		}
		return bResult;
	}

	//------------------------------------------------------------------------------
	bool CSocketSink::SyncWrite(unsigned long& ulNumberOfUnitsWritten, unsigned long ulNumberOfUnitsToWrite, ISocket::ref_type Socket)
	{
		bool bResult = false;
		byte* pBuffer = GetSource()->GetBuffer()->ReadRequest(ulNumberOfUnitsToWrite);
		if (pBuffer && ulNumberOfUnitsToWrite > 0)
		{
			unsigned long ulUnitSize = GetSource()->GetBuffer()->GetUnitSize();
			ulNumberOfUnitsWritten = 0;
			int iBytes = Socket->Send((char*)(pBuffer), ulNumberOfUnitsToWrite * ulUnitSize);
			ulNumberOfUnitsWritten = static_cast<unsigned int>(iBytes) / ulUnitSize;
			bResult = (ulNumberOfUnitsWritten > 0) ? true : false;
			
			GetSource()->GetBuffer()->ReadAcknowledge(ulNumberOfUnitsWritten);
		}

		if (bResult)
		{
			WriteSuccess.Signal();
		}
		else
		{
			WriteError.Signal();
		}
		return bResult;
	}

	//------------------------------------------------------------------------------
	bool CSocketSink::Write(unsigned long& ulNumberOfUnitsWritten, unsigned long ulNumberOfUnitsToWrite)
	{
		__QCS_MEMBER_FCONTEXT("CSocketSink::Write");

		if (GetMode() == ePull)
		{
			unsigned long ulUnitsRead = 0;
			GetSource()->Read(ulUnitsRead, ulNumberOfUnitsToWrite);
		}

		bool bResult = false;
		CSocketConnector* pConnector = dynamic_cast< CSocketConnector* >(m_pIOSinkConnector);
		if (pConnector && pConnector->IsConnected())
		{
			if (pConnector->AsyncConnection())
			{
				bResult = AsyncWrite( ulNumberOfUnitsWritten, ulNumberOfUnitsToWrite, pConnector->Socket(), pConnector->GetSyncObject() );
			}
			else
			{
				bResult = SyncWrite(ulNumberOfUnitsWritten, ulNumberOfUnitsToWrite, pConnector->Socket());
			}
		}
		return bResult;
	}

	//------------------------------------------------------------------------------
	bool CSocketSink::Flush(void)
	{
		__QCS_MEMBER_FCONTEXT("CSocketSink::Flush");
		bool bResult = true;
		return bResult;
	}

}//nsBluefoot
