

#include "openobex/Obex_protocol.h"

//------------------------------------------------------------------------------
namespace nsQOR
{
	//------------------------------------------------------------------------------
	void obex_library_init(void)
	{
		char *env;
		/*
#if OBEX_DEBUG
		obex_debug = OBEX_DEBUG;
#else
		obex_debug = -1;
#endif
		env = getenv("OBEX_DEBUG");
		if (env)
			obex_debug = atoi(env);

#if OBEX_DUMP
		obex_dump = OBEX_DUMP;
#else
		obex_dump = 0;
#endif
		env = getenv("OBEX_DUMP");
		if (env)
			obex_dump = atoi(env);
		*/
	}

	//------------------------------------------------------------------------------
	CObexSession* CObexProtocolWrapper::Init(int transport, obex_event_t eventcb, unsigned int flags)
	{
		CObexSession* pSession = nullptr;

		if (eventcb != nullptr)
		{
			obex_library_init();
			pSession = new CObexSession(eventcb, flags);

			/*TODO: Abstract from transport more fully
			if (!obex_transport_init(pSession, transport))
			{
				delete pSession;
				pSession = nullptr;
			}
			*/
		}
		return pSession;
	}

	//------------------------------------------------------------------------------
	char* CObexProtocolWrapper::ResponseToString(int rsp)
	{
		switch (rsp)
		{
		case OBEX_RSP_CONTINUE:
			return "Continue";
		case OBEX_RSP_SWITCH_PRO:
			return "Switching protocols";
		case OBEX_RSP_SUCCESS:
			return "OK, Success";
		case OBEX_RSP_CREATED:
			return "Created";
		case OBEX_RSP_ACCEPTED:
			return "Accepted";
		case OBEX_RSP_NO_CONTENT:
			return "No Content";
		case OBEX_RSP_BAD_REQUEST:
			return "Bad Request";
		case OBEX_RSP_UNAUTHORIZED:
			return "Unauthorized";
		case OBEX_RSP_PAYMENT_REQUIRED:
			return "Payment required";
		case OBEX_RSP_FORBIDDEN:
			return "Forbidden";
		case OBEX_RSP_NOT_FOUND:
			return "Not found";
		case OBEX_RSP_METHOD_NOT_ALLOWED:
			return "Method not allowed";
		case OBEX_RSP_CONFLICT:
			return "Conflict";
		case OBEX_RSP_INTERNAL_SERVER_ERROR:
			return "Internal server error";
		case OBEX_RSP_NOT_IMPLEMENTED:
			return "Not implemented!";
		case OBEX_RSP_DATABASE_FULL:
			return "Database full";
		case OBEX_RSP_DATABASE_LOCKED:
			return "Database locked";
		default:
			return "Unknown response";
		}
	}

}//nsQOR

