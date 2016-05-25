#if defined(_POSIX_SOURCE) || defined(_POSIX_C_SOURCE) || defined(_XOPEN_SOURCE) || defined(_GNU_SOURCE) || defined(_BSD_SOURCE)

namespace nsLinux
{
    __QCMP_STATIC_CONSTANT( int, PageSize       = 4096 );
    __QCMP_STATIC_CONSTANT( int, LongBit        = 32 );

}//nsLinux

//#define PAGE_SIZE 4096
//#define LONG_BIT 32
#endif

//#define LONG_MAX  0x7fffffffL
//#define LLONG_MAX  0x7fffffffffffffffLL
namespace nsLinux
{
    __QCMP_STATIC_CONSTANT( long long, LongLongMax      = 0x7fffffffffffffffLL );
    __QCMP_STATIC_CONSTANT( long, LongMax       = 0x7fffffffL );
}//nsLinux
