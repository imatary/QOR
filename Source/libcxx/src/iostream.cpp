//===------------------------ iostream.cpp --------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "__std_stream"
#include "string"
#include "new"

_LIBCPP_BEGIN_NAMESPACE_STD

static mbstate_t state_types[6] = {};

/*__QCMP_ALIGNAS(__stdinbuf<char>)*/ static char __cin[sizeof(__stdinbuf <char>)];
/*__QCMP_ALIGNAS(__stdoutbuf<char>)*/ static char __cout[sizeof(__stdoutbuf<char>)];
/*__QCMP_ALIGNAS(__stdoutbuf<char>)*/ static char __cerr[sizeof(__stdoutbuf<char>)];
/*__QCMP_ALIGNAS(__stdinbuf<wchar_t>)*/ static char __wcin[sizeof(__stdinbuf <wchar_t>)];
/*__QCMP_ALIGNAS(__stdoutbuf<wchar_t>)*/ static char __wcout[sizeof(__stdoutbuf<wchar_t>)];
/*__QCMP_ALIGNAS(__stdoutbuf<wchar_t>)*/ static char __wcerr[sizeof(__stdoutbuf<wchar_t>)];


_LIBCPP_FUNC_VIS char cin_mem[sizeof(istream)];
_LIBCPP_FUNC_VIS char cout_mem[sizeof(ostream)];
_LIBCPP_FUNC_VIS char cerr_mem[sizeof(ostream)];
_LIBCPP_FUNC_VIS char clog_mem[sizeof(ostream)];
_LIBCPP_FUNC_VIS char wcin_mem[sizeof(wistream)];
_LIBCPP_FUNC_VIS char wcout_mem[sizeof(wostream)];
_LIBCPP_FUNC_VIS char wcerr_mem[sizeof(wostream)];
_LIBCPP_FUNC_VIS char wclog_mem[sizeof(wostream)];

_LIBCPP_FUNC_VIS istream& cin = *(reinterpret_cast<istream*>(&cin_mem[0]));
_LIBCPP_FUNC_VIS ostream& cout = *(reinterpret_cast<ostream*>(&cout_mem[0]));
_LIBCPP_FUNC_VIS ostream& cerr = *(reinterpret_cast<ostream*>(&cerr_mem[0]));
_LIBCPP_FUNC_VIS ostream& clog = *(reinterpret_cast<ostream*>(&clog_mem[0]));
_LIBCPP_FUNC_VIS wistream& wcin = *(reinterpret_cast<wistream*>(&wcin_mem[0]));
_LIBCPP_FUNC_VIS wostream& wcout = *(reinterpret_cast<wostream*>(&wcout_mem[0]));
_LIBCPP_FUNC_VIS wostream& wcerr = *(reinterpret_cast<wostream*>(&wcerr_mem[0]));
_LIBCPP_FUNC_VIS wostream& wclog = *(reinterpret_cast<wostream*>(&wclog_mem[0]));

/*__QCMP_ALIGNAS(istream)*/  //_LIBCPP_FUNC_VIS char cin[sizeof(istream)];
/*__QCMP_ALIGNAS(ostream)*/  //_LIBCPP_FUNC_VIS char cout[sizeof(ostream)];
/*__QCMP_ALIGNAS(ostream)*/  //_LIBCPP_FUNC_VIS char cerr[sizeof(ostream)];
/*__QCMP_ALIGNAS(ostream)*/  //_LIBCPP_FUNC_VIS char clog[sizeof(ostream)];
/*__QCMP_ALIGNAS(wistream)*/ //_LIBCPP_FUNC_VIS char wcin[sizeof(wistream)];
/*__QCMP_ALIGNAS(wostream)*/ //_LIBCPP_FUNC_VIS char wcout[sizeof(wostream)];
/*__QCMP_ALIGNAS(wostream)*/ //_LIBCPP_FUNC_VIS char wcerr[sizeof(wostream)];
/*__QCMP_ALIGNAS(wostream)*/ //_LIBCPP_FUNC_VIS char wclog[sizeof(wostream)];

ios_base::Init __start_std_streams;

ios_base::Init::Init()
{
    istream* cin_ptr  = ::new(cin_mem)  istream(::new(__cin)  __stdinbuf <char>(stdin, state_types+0) );
    ostream* cout_ptr = ::new(cout_mem) ostream(::new(__cout) __stdoutbuf<char>(stdout, state_types+1));
    ostream* cerr_ptr = ::new(cerr_mem) ostream(::new(__cerr) __stdoutbuf<char>(stderr, state_types+2));
                        ::new(clog_mem) ostream(cerr_ptr->rdbuf());
    cin_ptr->tie(cout_ptr);
    _VSTD::unitbuf(*cerr_ptr);
    cerr_ptr->tie(cout_ptr);

    wistream* wcin_ptr  = ::new(wcin_mem)  wistream(::new(__wcin)  __stdinbuf <wchar_t>(stdin, state_types+3) );
    wostream* wcout_ptr = ::new(wcout_mem) wostream(::new(__wcout) __stdoutbuf<wchar_t>(stdout, state_types+4));
    wostream* wcerr_ptr = ::new(wcerr_mem) wostream(::new(__wcerr) __stdoutbuf<wchar_t>(stderr, state_types+5));
                          ::new(wclog_mem) wostream(wcerr_ptr->rdbuf());
    wcin_ptr->tie(wcout_ptr);
    _VSTD::unitbuf(*wcerr_ptr);
    wcerr_ptr->tie(wcout_ptr);

	&cin;// = reinterpret_cast<istream*>(&cin_mem[0]);
}

ios_base::Init::~Init()
{
    ostream* cout_ptr = reinterpret_cast<ostream*>(cout_mem);
    ostream* clog_ptr = reinterpret_cast<ostream*>(clog_mem);
    cout_ptr->flush();
    clog_ptr->flush();

    wostream* wcout_ptr = reinterpret_cast<wostream*>(wcout_mem);
    wostream* wclog_ptr = reinterpret_cast<wostream*>(wclog_mem);
    wcout_ptr->flush();
    wclog_ptr->flush();
}

_LIBCPP_END_NAMESPACE_STD
