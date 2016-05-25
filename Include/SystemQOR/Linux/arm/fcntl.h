//#define O_CREAT        0100
//#define O_EXCL         0200
//#define O_NOCTTY       0400
//#define O_TRUNC       01000
//#define O_APPEND      02000
//#define O_NONBLOCK    04000
//#define O_DSYNC      010000
//#define O_SYNC     04010000
//#define O_RSYNC    04010000
//#define O_DIRECTORY  040000
//#define O_NOFOLLOW  0100000
//#define O_CLOEXEC  02000000

namespace nsLinux
{
    __QCMP_STATIC_CONSTANT( unsigned int, OCreate                    = 0100 );
    __QCMP_STATIC_CONSTANT( unsigned int, OExclusive                 = 0200 );
    __QCMP_STATIC_CONSTANT( unsigned int, ONoCTTY                    = 0400 );
    __QCMP_STATIC_CONSTANT( unsigned int, OTruncate                  = 01000 );
    __QCMP_STATIC_CONSTANT( unsigned int, OAppend                    = 02000 );
    __QCMP_STATIC_CONSTANT( unsigned int, ONonBlocking               = 04000 );
    __QCMP_STATIC_CONSTANT( unsigned int, DSync                      = 010000 );
    __QCMP_STATIC_CONSTANT( unsigned int, OSync                      = 04010000 );
    __QCMP_STATIC_CONSTANT( unsigned int, ORSync                     = 04010000 );
    __QCMP_STATIC_CONSTANT( unsigned int, ODirectory                 = 040000 );
    __QCMP_STATIC_CONSTANT( unsigned int, ONoFollow                  = 0100000 );
    __QCMP_STATIC_CONSTANT( unsigned int, OCloseOnExec               = 02000000 );

    __QCMP_STATIC_CONSTANT( int, FGetDescriptorFlags        = 1 );
    __QCMP_STATIC_CONSTANT( int, FSetDescriptorFlags        = 2 );
    __QCMP_STATIC_CONSTANT( int, FGetFlags                  = 3 );
    __QCMP_STATIC_CONSTANT( int, FSetFlags                  = 4 );
}
#define O_ASYNC      020000
#define O_DIRECT    0200000
#define O_LARGEFILE 0400000
#define O_NOATIME  01000000
#define O_TMPFILE 020040000
#define O_NDELAY O_NONBLOCK

#define F_DUPFD  0
//#define F_GETFD  1
//#define F_SETFD  2
//#define F_GETFL  3
//#define F_SETFL  4

#define F_SETOWN 8
#define F_GETOWN 9
#define F_SETSIG 10
#define F_GETSIG 11

#define F_GETLK 12
#define F_SETLK 13
#define F_SETLKW 14

#define F_SETOWN_EX 15
#define F_GETOWN_EX 16

#define F_GETOWNER_UIDS 17
