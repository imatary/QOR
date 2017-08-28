//Obex_protocol.h

#ifndef OBEX_PROTOCOL_H
#define OBEX_PROTOCOL_H

#include "CompilerQOR.h"
#include "CodeQOR/DataTypes/GUID.h"

#include <stdint.h>
#include "databuffer.h"
#include "obex_body.h"
#include "obex_hdr.h"
//#include "obex_const.h"

#ifndef ESOCKTNOSUPPORT
#	define ESOCKTNOSUPPORT 1044L
#endif

typedef unsigned long long BTH_ADDR, *PBTH_ADDR;

extern BTH_ADDR bluez_compat_bdaddr_any;
#define BDADDR_ANY     &bluez_compat_bdaddr_any

typedef unsigned int fd_t;

//------------------------------------------------------------------------------
/*
typedef struct _SOCKADDR_BTH
{
	unsigned short      addressFamily;  // Always AF_BTH
	BTH_ADDR    btAddr;         // Bluetooth device address
	nsCodeQOR::GUID        serviceClassId; // [OPTIONAL] system will query SDP for port
	unsigned long       port;           // RFCOMM channel or L2CAP PSM
} SOCKADDR_BTH, *PSOCKADDR_BTH;
*/
typedef Cmp_uint_ptr socket_t;
typedef int socklen_t;
/*
#define _SS_MAXSIZE 128                 // Maximum size
#define _SS_ALIGNSIZE (sizeof(__int64)) // Desired alignment

#if(_WIN32_WINNT >= 0x0600)
#define _SS_PAD1SIZE (_SS_ALIGNSIZE - sizeof(unsigned short))
#define _SS_PAD2SIZE (_SS_MAXSIZE - (sizeof(unsigned short) + _SS_PAD1SIZE + _SS_ALIGNSIZE))
#else
#define _SS_PAD1SIZE (_SS_ALIGNSIZE - sizeof (short))
#define _SS_PAD2SIZE (_SS_MAXSIZE - (sizeof (short) + _SS_PAD1SIZE + _SS_ALIGNSIZE))
#endif //(_WIN32_WINNT >= 0x0600)

//------------------------------------------------------------------------------
typedef struct sockaddr_storage 
{
	unsigned short ss_family;      // address family

	char __ss_pad1[_SS_PAD1SIZE];  // 6 byte pad, this is to make
								   //   implementation specific pad up to
								   //   alignment field that follows explicit
								   //   in the data structure
	__int64 __ss_align;            // Field to force desired structure
	char __ss_pad2[_SS_PAD2SIZE];  // 112 byte pad to achieve desired size;
								   //   _SS_MAXSIZE value minus size of
								   //   ss_family, __ss_pad1, and
								   //   __ss_align fields is 112
} SOCKADDR_STORAGE_LH, *PSOCKADDR_STORAGE_LH, *LPSOCKADDR_STORAGE_LH;
*/
//------------------------------------------------------------------------------
/** a socket instance */
struct obex_sock
{
	int domain;										/** socket domain */
	int proto;										/** socket protocol */
	socket_t fd;									/** the kernel descriptor for this socket */
	sockaddr_storage local;							/** the local address of this socket */
	sockaddr_storage remote;						/** the remote address of this socket */
	socklen_t addr_size;							/** the address size of this socket type */
	unsigned int flags;								/** socket OBEX_FL_* flags */
	bool(*set_sock_opts)(socket_t);				/** callback to set transport-specific socket options */
};

//------------------------------------------------------------------------------
struct btobex_rfcomm_data
{
	obex_sock* sock;
};

//------------------------------------------------------------------------------
struct fdobex_data
{
	fd_t readfd;  /* read descriptor */
	fd_t writefd; /* write descriptor */
};

//------------------------------------------------------------------------------
/** Possible data direction */
/*
enum obex_data_direction
{
	OBEX_DATA_NONE = 0,
	OBEX_DATA_IN = 1,
	OBEX_DATA_OUT = 2,
};
*/
//------------------------------------------------------------------------------
/** Obex response modes */
/*
enum obex_rsp_mode
{
	OBEX_RSP_MODE_NORMAL = 0, //< normal response mode 
	OBEX_RSP_MODE_SINGLE = 1, //< single response mode (SRM)
};
*/

//------------------------------------------------------------------------------
/** Possible events */
//enum obex_event
//{
//	/** Progress has been made */
//	OBEX_EV_PROGRESS = 0,
//	/** An incoming request is about to come */
//	OBEX_EV_REQHINT = 1,
//	/** An incoming request has arrived */
//	OBEX_EV_REQ = 2,
//	/** Request has finished */
//	OBEX_EV_REQDONE = 3,
//	/** Link has been disconnected */
//	OBEX_EV_LINKERR = 4,
//	/** Malformed data encountered */
//	OBEX_EV_PARSEERR = 5,
//	/** Connection accepted */
//	OBEX_EV_ACCEPTHINT = 6,
//	/** Request was aborted */
//	OBEX_EV_ABORT = 7,
//	/** Need to feed more data when sending a stream */
//	OBEX_EV_STREAMEMPTY = 8,
//	/** Time to pick up data when receiving a stream */
//	OBEX_EV_STREAMAVAIL = 9,
//	/** Unexpected data, not fatal */
//	OBEX_EV_UNEXPECTED = 10,
//	/** First packet of an incoming request has been parsed */
//	OBEX_EV_REQCHECK = 11,
//	/** A Continue response was received and a new request is about to be sent.
//	*  CancelRequest() can be used to stop the request processing.
//	*/
//	OBEX_EV_CONTINUE = 12,
//};

//------------------------------------------------------------------------------
/** Obex commands */
//enum obex_cmd
//{
//	OBEX_CMD_CONNECT = 0x00,
//	OBEX_CMD_DISCONNECT = 0x01,
//	OBEX_CMD_PUT = 0x02,
//	OBEX_CMD_GET = 0x03,
//	OBEX_CMD_SETPATH = 0x05,
//	OBEX_CMD_ACTION = 0x06,
//	OBEX_CMD_SESSION = 0x07, /**< used for reliable session support */
//	OBEX_CMD_ABORT = 0x7f,
//};
//#define OBEX_FINAL		0x80
//
////------------------------------------------------------------------------------
///** Obex responses */
//enum obex_rsp
//{
//	OBEX_RSP_CONTINUE = 0x10,
//	OBEX_RSP_SWITCH_PRO = 0x11,
//	OBEX_RSP_SUCCESS = 0x20,
//	OBEX_RSP_CREATED = 0x21,
//	OBEX_RSP_ACCEPTED = 0x22,
//	OBEX_RSP_NON_AUTHORITATIVE = 0x23,
//	OBEX_RSP_NO_CONTENT = 0x24,
//	OBEX_RSP_RESET_CONTENT = 0x25,
//	OBEX_RSP_PARTIAL_CONTENT = 0x26,
//	OBEX_RSP_MULTIPLE_CHOICES = 0x30,
//	OBEX_RSP_MOVED_PERMANENTLY = 0x31,
//	OBEX_RSP_MOVED_TEMPORARILY = 0x32,
//	OBEX_RSP_SEE_OTHER = 0x33,
//	OBEX_RSP_NOT_MODIFIED = 0x34,
//	OBEX_RSP_USE_PROXY = 0x35,
//	OBEX_RSP_BAD_REQUEST = 0x40,
//	OBEX_RSP_UNAUTHORIZED = 0x41,
//	OBEX_RSP_PAYMENT_REQUIRED = 0x42,
//	OBEX_RSP_FORBIDDEN = 0x43,
//	OBEX_RSP_NOT_FOUND = 0x44,
//	OBEX_RSP_METHOD_NOT_ALLOWED = 0x45,
//	OBEX_RSP_NOT_ACCEPTABLE = 0x46,
//	OBEX_RSP_PROXY_AUTH_REQUIRED = 0x47,
//	OBEX_RSP_REQUEST_TIME_OUT = 0x48,
//	OBEX_RSP_CONFLICT = 0x49,
//	OBEX_RSP_GONE = 0x4a,
//	OBEX_RSP_LENGTH_REQUIRED = 0x4b,
//	OBEX_RSP_PRECONDITION_FAILED = 0x4c,
//	OBEX_RSP_REQ_ENTITY_TOO_LARGE = 0x4d,
//	OBEX_RSP_REQ_URL_TOO_LARGE = 0x4e,
//	OBEX_RSP_UNSUPPORTED_MEDIA_TYPE = 0x4f,
//	OBEX_RSP_INTERNAL_SERVER_ERROR = 0x50,
//	OBEX_RSP_NOT_IMPLEMENTED = 0x51,
//	OBEX_RSP_BAD_GATEWAY = 0x52,
//	OBEX_RSP_SERVICE_UNAVAILABLE = 0x53,
//	OBEX_RSP_GATEWAY_TIMEOUT = 0x54,
//	OBEX_RSP_VERSION_NOT_SUPPORTED = 0x55,
//	OBEX_RSP_DATABASE_FULL = 0x60,
//	OBEX_RSP_DATABASE_LOCKED = 0x61,
//};

//------------------------------------------------------------------------------
namespace nsQOR
{
	class CObexObject;
	
	struct obex_headerdata_t;
	struct sockaddr;
	class __QOR_INTERFACE(__APPOCRITA) CObexSession;

	//------------------------------------------------------------------------------
	// Function definition for custom transports
	typedef struct
	{
		/** connect to a server (client-only) */
		int(*connect)(CObexSession *handle, void *customdata);
		/** disconnect (server/client) */
		int(*disconnect)(CObexSession *handle, void *customdata);
		/** listen to incoming connections (server-only) */
		int(*listen)(CObexSession *handle, void *customdata);
		/** remote connection input
		* This function is optional as it is an alternative to providing the
		* data with #OBEX_CustomDataFeed(). The memory that 'buf' points to has
		* enough room for RX MTU bytes. The minimum number of bytes needed to
		* go on is specified by 'size'.*/
		int(*read)(CObexSession *handle, void *customdata, uint8_t *buf, int size);
		/** remote connection output */
		int(*write)(CObexSession *handle, void *customdata, uint8_t *buf, int len);
		/** directly called by #OBEX_HandleInput */
		int(*handleinput)(CObexSession *handle, void *customdata, int timeout);
		void *customdata;
	} obex_ctrans_t;

	//------------------------------------------------------------------------------
	/** USB-specific OBEX service information
	* provided by optional Service Identification Functional Descriptor
	* (CDC WMC specification section 6.5.2.5)
	*/
	typedef struct
	{
		/** Role bit mask: bit 0 is set if client, unset if server */
		uint8_t role;
		/** Service UUID */
		uint8_t uuid[16];
		/** Service version */
		uint16_t version;
		/** Set if the service provides/expects
		*  an OBEX Default Server (spec section 6.5.2.5.2) */
		int is_default_uuid;
	} obex_usb_intf_service_t;

	//------------------------------------------------------------------------------
	/** USB-specific OBEX interface information */
	typedef struct
	{
		/** Manufacturer, e.g. Nokia */
		char *manufacturer;
		/** Product, e.g. Nokia 6680 */
		char *product;
		/** Product serial number */
		char *serial;
		/** USB device configuration description */
		char *configuration;
		/** Control interface description */
		char *control_interface;
		/** Idle data interface description, typically empty */
		char *data_interface_idle;
		/** Active data interface description, typically empty */
		char *data_interface_active;
		/** Service information descriptor, may be NULL if absent */
		obex_usb_intf_service_t *service;
		/** USB-IF vendor ID */
		unsigned int idVendor;
		/** USB-IF product ID */
		unsigned int idProduct;
		/** Bus number that a USB device is connected to */
		unsigned int bus_number;
		/** Device address on the bus */
		unsigned int device_address;
		/** USB device interface number */
		unsigned int interface_number;
		/** Internal information for the transport layer in the library */
		struct obex_usb_intf_transport_t *intf;
	} obex_usb_intf_t;

	//------------------------------------------------------------------------------
	/** IrDA-specific OBEX interface information */
	typedef struct
	{
		/** Address of local interface */
		uint32_t local;
		/** Address of remote device */
		uint32_t remote;
		/** Description */
		char *info;
		/** Charset used for description */
		uint8_t	charset;
		/** Hint bits */
		uint8_t	hints[2];

		/** service selector, filled by application, "OBEX" if NULL */
		const char *service;
	} obex_irda_intf_t;

	//------------------------------------------------------------------------------
	/** Generic OBEX interface information */
	typedef union
	{
		/** IrDA-specific OBEX interface information */
		obex_irda_intf_t irda;
		/** USB-specific OBEX interface information */
		obex_usb_intf_t usb;
	} obex_interface_t;

	//------------------------------------------------------------------------------
	struct obex_transport_ops
	{
		void * (*create)(void);
		bool(*init)(CObexSession*);
		void(*cleanup)(CObexSession*);

		result_t(*handle_input)(CObexSession*);
		ssize_t(*write)(CObexSession*, databuffer*);
		ssize_t(*read)(CObexSession*, void*, int);
		bool(*disconnect)(CObexSession*);

		int(*get_fd)(CObexSession*);
		bool(*set_local_addr)(CObexSession*, sockaddr*, size_t);
		bool(*set_remote_addr)(CObexSession*, sockaddr*, size_t);

		struct
		{
			bool(*listen)(CObexSession*);
			bool(*accept)(CObexSession*, const CObexSession*);
		} server;

		struct
		{
			bool(*connect)(CObexSession*);
			int(*find_interfaces)(CObexSession*, obex_interface_t**);
			void(*free_interface)(obex_interface_t*);
			bool(*select_interface)(CObexSession*, obex_interface_t*);
		} client;
	};

	//------------------------------------------------------------------------------
	typedef struct obex_transport
	{
		struct obex_transport_ops *ops;
		void *data;		/* Private data for the transport */

		int64_t timeout;	/* set timeout */
		bool connected;		/* Link connection state */
		bool server;		/* Listens on local interface */
	} obex_transport_t;


	//------------------------------------------------------------------------------
	class __QOR_INTERFACE(__APPOCRITA) CObexObject
	{
	public:

		CObexObject( CObexSession* pSession );
		~CObexObject();

		void SetTXNonHeaderData(databuffer* p);
		databuffer* GetTXNonHeaderData(void);
		void SetTXHeaderQueue(databuffer_list* p);
		databuffer_list* GetTXHeaderQueue(void);
		void SetTXIterator(obex_hdr_it* p);
		obex_hdr_it* GetTXIterator(void);
		void SetRXHeaderQueue(databuffer_list* p);
		databuffer_list* GetRXHeaderQueue(void);
		databuffer* GetRXNonHeaderData(void);
		void SetRXIterator(obex_hdr_it* p);
		obex_hdr_it* GetRXIterator(void);
		obex_cmd GetCommand(void);
		obex_rsp GetResponse(void);
		obex_rsp GetLastResponse(void);
		void SetHeaderOffset(uint16_t offset);
		uint16_t GetHeaderOffset(void);
		uint32_t GetHintedBodyLength(void);
		void SetHintedBodyLength(uint32_t len);
		void SetAbort(bool bAbort);
		bool IsAborting(void);
		void SetResponseMode(obex_rsp_mode ResponseMode);
		obex_rsp_mode GetResponseMode(void);
		void ClearBody(void);
		void SetBody(CObexHeader* p);
		CObexHeader* GetBody(void) const;
		void SetBodyRecv(IObexBody* p);
		IObexBody* GetBodyRecv(void) const;
		size_t get_size(void);
		int addheader(obex* self, CObexObject* object, uint8_t hi, obex_headerdata_t hv, uint32_t hv_size, unsigned int flags);//deprecated
		int getnextheader(uint8_t* hi, obex_headerdata_t* hv, uint32_t* hv_size);
		int reparseheaders(void);
		void setcmd(obex_cmd cmd);
		obex_cmd getcmd() const;
		int setrsp(obex_rsp rsp, obex_rsp lastrsp);
		int get_opcode(bool allowfinalcmd, enum obex_mode mode);
		bool append_data(databuffer* txmsg, size_t tx_left);
		int finished(bool allowfinal);
		int receive_nonhdr_data(const void* msgdata, size_t rx_left);
		int receive_headers(const void* msgdata, size_t tx_left, uint64_t filter);
		int set_body_receiver(IObexBody* b);
		const void * read_body(size_t* size);
		void Suspend(bool bSuspend);
		int suspend(void);
		int resume(void);

	protected:
		CObexSession* m_pSession;
	};
	
	typedef void(*obex_event_t)(CObexSession* handle, CObexObject* obj, int mode, int event, int obex_cmd, int obex_rsp);

	//------------------------------------------------------------------------------
	class __QOR_INTERFACE(__APPOCRITA) CObexCore
	{
	public:

		CObexCore(obex_event_t eventcb, unsigned int flags);
		virtual ~CObexCore();

	protected:

		result_t Client(void);

		result_t Server(void);

		int InsertConnectFrame(CObexObject* object);
		int ParseConnectFrame(CObexObject* object);

		//obex_msg
		bool MsgPrepare(CObexObject* object, bool allowfinal);
		int MsgGetSpace(CObexObject* object, unsigned int flags);
		bool MsgRXStatus(void) const;
		bool MsgTXStatus(void) const;
		int MsgGetOpcode(void) const;
		size_t MsgGetLen(void) const;
		void MsgPreReceive(void);
		int MsgReceiveFiltered(CObexObject* object, uint64_t filter, bool first_run);
		int MsgReceive(CObexObject* object);
		int MsgPostReceive(void);

		//obex
		void DeliverEvent(obex_event event, obex_cmd cmd, obex_rsp rsp, bool delete_object);
		result_t HandleInput(void);
		result_t Work(void);
		obex_data_direction GetDataDirection(void);
		result_t DataIndication(void);
		void DataReceiveFinished( void);

		int SetMTU(uint16_t mtu_rx, uint16_t mtu_tx_max);
		
		bool DataRequestInit(void);
		int CancelRequest(int nice);
		void DataRequestPrepare(int opcode);
		bool DataRequestTransmit(void);	
		bool CheckSRMInput(void);

		uint16_t mtu_tx;		/* Maximum OBEX TX packet size */
		uint16_t mtu_rx;		/* Maximum OBEX RX packet size */
		uint16_t mtu_tx_max;		/* Maximum TX we can accept */

		obex_state state;
		obex_substate substate;
		obex_mode mode;
		obex_rsp_mode rsp_mode;	/* OBEX_RSP_MODE_* */

		unsigned int init_flags;
		unsigned int srm_flags;		/* Flags for single response mode */

		databuffer* tx_msg;	/* Reusable transmit message */
		databuffer* rx_msg;	/* Reusable receive message */

		CObexObject* object;	/* Current object being transfered */
		obex_event_t eventcb;		/* Event-callback */
		obex_event abort_event;	/**< event for application when server aborts */

		obex_transport_t* trans;	/* Transport being used */

		obex_interface_t* interfaces;	/* Array of discovered interfaces */
		int interfaces_number;		/* Number of discovered interfaces */

		void* userdata;		/* For user */

	};

	//------------------------------------------------------------------------------
	class __QOR_INTERFACE(__APPOCRITA) CObexSession : public CObexCore
	{
	public:

		CObexSession(obex_event_t eventcb, unsigned int flags);
		~CObexSession();

		void SetUserData(void * data);
		void* GetUserData();
		void SetUserCallBack(obex_event_t eventcb, void * data);
		int SetTransportMTU(uint16_t mtu_rx, uint16_t mtu_tx_max);
		int GetFD();

		int RegisterCTransport(obex_ctrans_t *ctrans);
		int	SetCustomData(void * data);
		void* GetCustomData();

		int TransportConnect(sockaddr *saddr, int addlen);
		int	TransportDisconnect();
		int	CustomDataFeed(uint8_t *inputbuf, int actual);

		void SetTimeout(int64_t timeout);
		int Work();
		obex_data_direction GetDataDirection();
		int HandleInput(int timeout);

		int ServerRegister(sockaddr *saddr, int addrlen);
		CObexSession* ServerAccept(obex_event_t eventcb, void * data);

		int Request(CObexObject* object);
		int CancelRequest(int nice);
		int SuspendRequest();
		int ResumeRequest();

		CObexObject* ObjectNew(uint8_t cmd);
		int ObjectDelete(CObexObject* object);
		int ObjectGetSpace(CObexObject* object, unsigned int flags);

		void SetReponseMode(obex_rsp_mode rsp_mode);

		int ObjectAddHeader(CObexObject* object, uint8_t hi, obex_headerdata_t hv, uint32_t hv_size, unsigned int flags);
		int ObjectGetNextHeader(CObexObject* object, uint8_t *hi, obex_headerdata_t *hv, uint32_t *hv_size);
		int ObjectReParseHeaders(CObexObject* object);
		int ObjectSetRsp(CObexObject* object, uint8_t rsp, uint8_t lastrsp);
		int ObjectGetNonHdrData(CObexObject* object, uint8_t **buffer);
		int ObjectSetNonHdrData(CObexObject* object, const uint8_t *buffer, unsigned int len);
		int ObjectSetHdrOffset(CObexObject* object, unsigned int offset);
		int ObjectReadStream(CObexObject* object, const uint8_t **buf);
		int ObjectGetCommand(CObexObject* object);

		//TcpOBEX API (IPv4/IPv6)

		int TcpServerRegister( sockaddr *addr, int addrlen);
		int TcpTransportConnect(sockaddr *addr, int addrlen);

		//IrOBEX API 

		int IrServerRegister(const char *service);
		int IrTransportConnect(const char *service);

		//Bluetooth OBEX API
		int BtServerRegister(const unsigned long long* src, uint8_t channel);
		int BtTransportConnect(const unsigned long long* src, const unsigned long long* dst, uint8_t channel);

		//OBEX File API
		int FdTransportSetup(int rfd, int wfd, int mtu);

		//OBEX interface discovery API 

		int  EnumerateInterfaces();
		obex_interface_t*  GetInterfaceByIndex(int i);
		int  InterfaceConnect(obex_interface_t *intf);
		void FreeInterfaces();

	};

	

	//------------------------------------------------------------------------------
	class __QOR_INTERFACE(__APPOCRITA) CObexProtocolWrapper
	{
	public:
		
		//OBEX API

		CObexSession* Init(int transport, obex_event_t eventcb, unsigned int flags);
		/*
		int ObjectSetRsp(CObexObject* object, uint8_t rsp, uint8_t lastrsp);
		int ObjectGetNonHdrData(CObexObject* object, uint8_t **buffer);
		int ObjectSetNonHdrData(CObexObject* object, const uint8_t *buffer, unsigned int len);
		int ObjectSetHdrOffset(CObexObject* object, unsigned int offset);
		int ObjectReadStream(CObexSession *self, CObexObject* object, const uint8_t **buf);
		int ObjectGetCommand(CObexSession *self, CObexObject* object);
		*/

		char* ResponseToString(int rsp);	
	};

}//nsQOR

#endif//OBEX_PROTOCOL_H
