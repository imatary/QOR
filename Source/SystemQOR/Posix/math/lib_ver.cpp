
/* @(#)s_lib_ver.c 5.1 93/09/24 */
/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice 
 * is preserved.
 * ====================================================
 */

// MACRO for standards

#include "SystemQOR/Posix/Basemath.h"

//------------------------------------------------------------------------------
namespace nsBaseCRT
{

//define and initialize m_fdlib_version
	Cmath::__fdlibm_version Cmath::m_fdlib_version 
#ifdef _POSIX_MODE
	= _POSIX_;
#else
#	ifdef _XOPEN_MODE

	= _XOPEN_;

#	else
#		ifdef _SVID3_MODE

	= _SVID_;

#		else // default _IEEE_MODE

	= _IEEE_;

#		endif
#	endif
#endif

};//namespace nsBaseCRT
