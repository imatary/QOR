//===------------------------- typeinfo.cpp -------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "SystemQOR.h"
#include <stdlib.h>
#if __APPLE__
#include <cxxabi.h>
#endif

#include "typeinfo"

namespace std
{
	bad_array_new_length::bad_array_new_length()
	{
	}

	bad_array_new_length::~bad_array_new_length()
	{
	}

	const char* bad_array_new_length::what() const
	{
		return "bad_array_new_length";
	}
}//std

