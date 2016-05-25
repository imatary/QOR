//SMTP.h

#ifndef BLUEFOOT_PROTOCOLS_SMTP_H_3
#define BLUEFOOT_PROTOCOLS_SMTP_H_3

//Defines a client side Simple Mail Transfer Protocol implementation

#include "CodeQOR/DataTypes/GUID.h"
#include "CodeQOR/Macros/ClassIdentityMacros.h"
#include "CodeQOR/DataStructures/TLRef.h"
#include "BluefootQOR/Protocol.h"

//------------------------------------------------------------------------------
namespace nsBluefoot
{	
	//------------------------------------------------------------------------------
	class __QOR_INTERFACE( __BLUEFOOTQOR ) CBFSMTPProtocol : public CBFProtocol
	{
	public:

		typedef nsCodeQOR::CTLRef< CBFSMTPProtocol > refType;

		//--------------------------------------------------------------------------------
		enum eSMTPPhase
		{
			Initial,
			Hello,
			Auth,
			Login,
			Password,
			From,
			To,
			Data,
			Header,
			Message,
			Attachment,
			EndOfAttachments,
			EndOfMessage,
			Quit,
		};

		__QOR_DECLARE_OCLASS_ID( CBFSMTPProtocol );

		CBFSMTPProtocol();
		virtual ~CBFSMTPProtocol();
		CBFSMTPProtocol(const CBFSMTPProtocol& src);
		CBFSMTPProtocol& operator = (const CBFSMTPProtocol& src);

		virtual bool OnProtocolStateChange( void );				//single step the state machine

		virtual void GetNextReadCount( void );
		virtual void GetNextWriteCount( void );

		virtual void OnConnectionError( void );
		virtual void OnConnected( void );
		virtual void OnDisconnectionError( void );
		virtual void OnDisconnected( void );
		virtual void OnReadSuccess( unsigned long ulUnitsRead );
		virtual void OnReadError( void );
		virtual void OnWriteSuccess( void );
		virtual void OnWriteError( void );
		virtual bool Read( unsigned long ulUnitSize = 1 );
		virtual bool Write( void );
		virtual bool OnRead( unsigned long ulUnitsToWrite, unsigned long& ulUnitsWritten, byte* pBuffer, unsigned long ulUnitSize = 1 );
		virtual bool OnWrite(unsigned long ulUnitsToRead, unsigned long& ulUnitsRead, unsigned long ulUnitSize = 1 );
		virtual bool OnWrite( unsigned long ulUnitSize = 1 );

		refType Ref( void )
		{
			return refType( this );
		}

	protected:

		eSMTPPhase m_Phase;
	};


}//nsBluefoot

#endif//BLUEFOOT_PROTOCOLS_SMTP_H_3
