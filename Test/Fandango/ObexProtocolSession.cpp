
#include <errno.h>
#include "openobex/Obex_protocol.h"

//------------------------------------------------------------------------------
namespace nsQOR
{
	//------------------------------------------------------------------------------
	CObexSession::CObexSession(obex_event_t eventcb, unsigned int flags) : CObexCore( eventcb, flags )
	{

	}

	//------------------------------------------------------------------------------
	CObexSession::~CObexSession()
	{

	}

	//------------------------------------------------------------------------------
	void CObexSession::SetUserData(void * data)
	{
		userdata = data;
	}

	//------------------------------------------------------------------------------
	void* CObexSession::GetUserData()
	{
		return userdata;
	}

	//------------------------------------------------------------------------------
	void CObexSession::SetUserCallBack(obex_event_t peventcb, void * data)
	{
		// The callback can't be NULL 

		if (peventcb != nullptr) 
		{
			eventcb = peventcb;
			// Optionaly change the user data
			if (data != nullptr)
			{
				userdata = data;
			}
		}
	}

	//------------------------------------------------------------------------------
	int CObexSession::SetTransportMTU(uint16_t _mtu_rx, uint16_t _mtu_tx_max)
	{
		return 0;
	}

	//------------------------------------------------------------------------------
	int CObexSession::GetFD()
	{
		return 0;
	}

	//------------------------------------------------------------------------------
	int CObexSession::RegisterCTransport(obex_ctrans_t *ctrans)
	{
		return 0;
	}

	//------------------------------------------------------------------------------
	int	CObexSession::SetCustomData(void * data)
	{
		obex_transport* ptrans = trans;
		obex_ctrans_t* ctrans = (obex_ctrans_t*)(ptrans->data);

		ctrans->customdata = data;
		return 0;
	}

	//------------------------------------------------------------------------------
	void* CObexSession::GetCustomData()
	{
		obex_transport* ptrans = trans;
		obex_ctrans_t* ctrans = (obex_ctrans_t*)(ptrans->data);
		return ctrans->customdata;
	}

	//------------------------------------------------------------------------------
	int CObexSession::TransportConnect(sockaddr *saddr, int addlen)
	{
		return 0;
	}

	//------------------------------------------------------------------------------
	int	CObexSession::TransportDisconnect()
	{
		return 0;
	}

	//------------------------------------------------------------------------------
	int	CObexSession::CustomDataFeed(uint8_t *inputbuf, int actual)
	{
		return 0;
	}

	//------------------------------------------------------------------------------
	void CObexSession::SetTimeout(int64_t timeout)
	{

	}

	//------------------------------------------------------------------------------
	int CObexSession::Work()
	{
		int ret;

		if (state == STATE_IDLE)
		{
			ret = CObexCore::HandleInput();
			if (ret != RESULT_SUCCESS)
			{
				return ret;
			}
		}
		else if (substate == SUBSTATE_RX)
		{
			if (CheckSRMInput())
			{
				ret = CObexCore::HandleInput();
				if (ret != RESULT_SUCCESS)
				{
					return ret;
				}
			}
		}
		else if (substate == SUBSTATE_TX)
		{
			if (!MsgTXStatus())
			{
				if (!DataRequestTransmit())
				{
					enum obex_cmd cmd = OBEX_CMD_ABORT;

					if (object)
					{
						cmd = object->getcmd();
					}

					DeliverEvent(OBEX_EV_LINKERR, cmd, (obex_rsp)0, TRUE);
					mode = OBEX_MODE_SERVER;
					state = STATE_IDLE;
					return RESULT_ERROR;
				}

				if (!MsgTXStatus())
				{
					return RESULT_TIMEOUT;
				}
			}
		}

		switch (mode)
		{
		case OBEX_MODE_SERVER:
			return Server();

		case OBEX_MODE_CLIENT:
			return Client();

		default:
			return RESULT_ERROR;
		}

	}

	//------------------------------------------------------------------------------
	obex_data_direction CObexSession::GetDataDirection()
	{
		if (state == STATE_IDLE)
		{
			return OBEX_DATA_IN;
		}
		else if (substate == SUBSTATE_RX)
		{
			return OBEX_DATA_IN;
		}
		else if (substate == SUBSTATE_TX)
		{
			return OBEX_DATA_OUT;
		}
		else
		{
			return OBEX_DATA_NONE;
		}
	}

	//------------------------------------------------------------------------------
	int CObexSession::HandleInput(int timeout)
	{
		return 0;
	}

	//------------------------------------------------------------------------------
	int CObexSession::ServerRegister(sockaddr *saddr, int addrlen)
	{
		return 0;
	}

	//------------------------------------------------------------------------------
	CObexSession* CObexSession::ServerAccept(obex_event_t peventcb, void * pdata)
	{
		CObexSession* pSession = nullptr;

		// If we have started receiving something, it's too late...
		if (object != nullptr)
		{
			return nullptr;
		}

		// Set callback and callback data as needed
		if (peventcb == nullptr)
		{
			peventcb = eventcb;
		}

		if (pdata == nullptr)
		{
			pdata = userdata;
		}

		// Allocate new instance
		pSession = new CObexSession(peventcb, init_flags);
		if (pSession == nullptr)
		{
			return nullptr;
		}

		pSession->userdata = pdata;

		if (pSession != this)
		{
			pSession->trans = new obex_transport_t;// obex_transport_create(this->trans->ops);

			pSession->trans->ops = trans->ops;
			pSession->trans->data = nullptr;
			if (pSession->trans->ops->create)
			{
				pSession->trans->data = pSession->trans->ops->create();
			}

			pSession->trans->timeout = -1; /* no time-out */
			pSession->trans->connected = false;
			pSession->trans->server = false;
		}

		pSession->trans->server = false;
		if (pSession->trans->ops->server.accept)
		{
			pSession->trans->connected = pSession->trans->ops->server.accept(pSession, this);
		}

		if (!pSession->trans->connected)
		{
			goto out_err;
		}


		pSession->mtu_tx = mtu_tx;
		if (pSession->SetMTU( mtu_rx, mtu_tx_max))
		{
			goto out_err;
		}

		pSession->mode = OBEX_MODE_SERVER;
		pSession->state = STATE_IDLE;
		pSession->rsp_mode = rsp_mode;

		return pSession;

	out_err:

		delete pSession;
		return nullptr;

	}

	//------------------------------------------------------------------------------
	int CObexSession::Request(CObexObject* pobject)
	{
		result_t result;

		if (pobject != nullptr)
		{

			if (object)
			{
				//DEBUG(1, "We are busy.\n");
				return -EBUSY;
			}

			pobject->SetResponseMode(rsp_mode);
			object = pobject;
			mode = OBEX_MODE_CLIENT;
			state = STATE_REQUEST;
			substate = SUBSTATE_TX_PREPARE;

			// Prepare the packet but do not send it
			result = Client();
			if (result < 0)
			{
				object = nullptr;
				mode = OBEX_MODE_SERVER;
				state = STATE_IDLE;
				return -EIO;
			}
		}
		return 0;
	}

	//------------------------------------------------------------------------------
	int CObexSession::CancelRequest(int nice)
	{
		// If we have no ongoing request do nothing
		if (object == nullptr)
		{
			return 0;
		}

		// Abort request without sending abort
		if (!nice)
		{
			// Deliver event will delete the object
			DeliverEvent(OBEX_EV_ABORT, (obex_cmd)0, (obex_rsp)0, true);
			
			tx_msg->clear(tx_msg->get_length());
			rx_msg->clear(rx_msg->get_length());
			// Since we didn't send ABORT to peer we are out of sync and need to disconnect transport immediately, so we signal link error to app
			DeliverEvent(OBEX_EV_LINKERR, (obex_cmd)0, (obex_rsp)0, false);
			return 1;

		}
		else
		{
			// The client or server code will take action at the right time.
			object->SetAbort(true);
			return 1;
		}
	}

	//------------------------------------------------------------------------------
	int CObexSession::SuspendRequest()
	{
		return object->suspend();
	}

	//------------------------------------------------------------------------------
	int CObexSession::ResumeRequest()
	{
		return object->resume();
	}

	//------------------------------------------------------------------------------
	CObexObject* CObexSession::ObjectNew(uint8_t cmd)
	{
		CObexObject* pobject;

		pobject = new CObexObject( this );
		if (pobject == nullptr)
		{
			return nullptr;
		}

		pobject->setcmd((obex_cmd)cmd);
		// Need some special handling on connect-frame
		if (cmd == OBEX_CMD_CONNECT)
		{
			if (InsertConnectFrame(pobject) < 0)
			{
				delete pobject;
				pobject = nullptr;
			}
		}

		return pobject;
	}

	/*
	//------------------------------------------------------------------------------
	int CObexSession::ObjectDelete(CObexObject* pobject)
	{

	}

	//------------------------------------------------------------------------------
	int CObexSession::ObjectGetSpace(CObexObject* pobject, unsigned int flags)
	{

	}
	*/
	//------------------------------------------------------------------------------
	void CObexSession::SetReponseMode(obex_rsp_mode _rsp_mode)
	{
		switch (_rsp_mode) 
		{
		case OBEX_RSP_MODE_NORMAL:
		case OBEX_RSP_MODE_SINGLE:
			rsp_mode = _rsp_mode;
			if(object)
			{
				object->SetResponseMode(_rsp_mode);
			}
			break;

		default:
			break;
		}
	}

	/*
	int ObjectAddHeader(CObexObject* object, uint8_t hi, obex_headerdata_t hv, uint32_t hv_size, unsigned int flags);
	int ObjectGetNextHeader(CObexObject* object, uint8_t *hi, obex_headerdata_t *hv, uint32_t *hv_size);
	int ObjectReParseHeaders(CObexObject* object);
	int ObjectSetRsp(CObexObject* object, uint8_t rsp, uint8_t lastrsp);
	int ObjectGetNonHdrData(CObexObject* object, uint8_t **buffer);
	int ObjectSetNonHdrData(CObexObject* object, const uint8_t *buffer, unsigned int len);
	int ObjectSetHdrOffset(CObexObject* object, unsigned int offset);
	int ObjectReadStream(CObexObject* object, const uint8_t **buf);
	int ObjectGetCommand(CObexObject* object);
	*/
	//TcpOBEX API (IPv4/IPv6)

	//------------------------------------------------------------------------------
	int CObexSession::TcpServerRegister(sockaddr *addr, int addrlen)
	{
		return -1;
	}

	//------------------------------------------------------------------------------
	int CObexSession::TcpTransportConnect(sockaddr *addr, int addrlen)
	{
		return -1;
	}

	//IrOBEX API 
	//------------------------------------------------------------------------------
	int CObexSession::IrServerRegister(const char *service)
	{
		return -1;
	}

	//------------------------------------------------------------------------------
	int CObexSession::IrTransportConnect(const char *service)
	{
		return-1;
	}

	//Bluetooth OBEX API
	//------------------------------------------------------------------------------
	int CObexSession::BtServerRegister(const unsigned long long* src, uint8_t channel)
	{
		return -1;
	}

	//------------------------------------------------------------------------------
	int CObexSession::BtTransportConnect(const unsigned long long* src, const unsigned long long* dst, uint8_t channel)
	{
		if(object) 
		{
			//DEBUG(1, "We are busy.\n");
			return -EBUSY;
		}

		if (dst != nullptr)
		{
			if (src == nullptr)
			{
				src = BDADDR_ANY;
			}

			//TODO:
			return -1;
		}
		else
		{
			return -1;
		}
	}

	//OBEX File API
	//------------------------------------------------------------------------------
	int CObexSession::FdTransportSetup(int rfd, int wfd, int mtu)
	{
		if(object) 
		{
			//DEBUG(1, "We are busy.\n");
			return -EBUSY;
		}

		fdobex_data* data = (fdobex_data*)(trans->data);

		data->readfd = (fd_t)rfd;
		data->writefd = (fd_t)wfd;

		if (trans->connected)
		{
			return -1;
		}

		if (trans->ops->client.connect)
		{
			trans->connected = trans->ops->client.connect(this);
		}

		return trans->connected ? 1 : -1;
	}

	//OBEX interface discovery API 
	//------------------------------------------------------------------------------
	int  CObexSession::EnumerateInterfaces()
	{
		FreeInterfaces();
		
		//struct obex_transport_ops *ops = self->trans->ops;
		int i = 0;

		if (interfaces)
		{
			return interfaces_number;
		}

		if (trans->ops->client.find_interfaces)
		{
			i = trans->ops->client.find_interfaces(this, &interfaces);
		}

		interfaces_number = i;
		return interfaces_number;
	}

	//------------------------------------------------------------------------------
	obex_interface_t* CObexSession::GetInterfaceByIndex(int i)
	{
		if (i >= interfaces_number || i < 0)
		{
			return nullptr;
		}
		return &interfaces[i];
	}

	//------------------------------------------------------------------------------
	int  CObexSession::InterfaceConnect(obex_interface_t *intf)
	{
		if(object) 
		{
			//DEBUG(1, "We are busy.\n");
			return -EBUSY;
		}

		if (intf != nullptr)
		{

			if (trans->ops->client.select_interface)
			{
				if (!trans->ops->client.select_interface(this, intf))
				{
					return -1;
				}

				if (trans->connected)
				{
					return -1;
				}

				if (trans->ops->client.connect)
				{
					trans->connected = trans->ops->client.connect(this);
				}

				return trans->connected ? 1 : -1;
			}
			else
			{
				return -ESOCKTNOSUPPORT;
			}
		}
		else
		{
			return -1;
		}
	}

	//------------------------------------------------------------------------------
	void CObexSession::FreeInterfaces()
	{
		int i, _interfaces_number;

		_interfaces_number = interfaces_number;
		interfaces_number = 0;

		if (interfaces == nullptr)
		{
			return;
		}

		if (trans->ops->client.free_interface == nullptr)
		{
			goto done;
		}

		for (i = 0; i < interfaces_number; i++)
		{
			trans->ops->client.free_interface(&interfaces[i]);
		}

	done:
		delete interfaces;
		interfaces = nullptr;
	}

}//nsQOR
