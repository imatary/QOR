
/* @(#)s_erf.c 5.1 93/09/24 */
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

/*Conversion to float by Ian Lance Taylor, Cygnus Support, ian@cygnus.com.
FUNCTION
        <<erf>>, <<erff>>, <<erfc>>, <<erfcf>>---error function 
INDEX
	erf
INDEX
	erff
INDEX
	erfc
INDEX
	erfcf

ANSI_SYNOPSIS
	#include <math.h>
	double erf(double <[x]>);
	float erff(float <[x]>);
	double erfc(double <[x]>);
	float erfcf(float <[x]>);
TRAD_SYNOPSIS
	#include <math.h>

	double erf(<[x]>)
	double <[x]>;

	float erff(<[x]>)
	float <[x]>;

	double erfc(<[x]>)
	double <[x]>;

	float erfcf(<[x]>)
	float <[x]>;

DESCRIPTION
	<<erf>> calculates an approximation to the ``error function'',
	which estimates the probability that an observation will fall within
	<[x]> standard deviations of the mean (assuming a normal
	distribution).
	@tex
	The error function is defined as
	$${2\over\sqrt\pi}\times\int_0^x e^{-t^2}dt$$
	 @end tex

	<<erfc>> calculates the complementary probability; that is,
	<<erfc(<[x]>)>> is <<1 - erf(<[x]>)>>.  <<erfc>> is computed directly,
	so that you can use it to avoid the loss of precision that would
	result from subtracting large probabilities (on large <[x]>) from 1.

	<<erff>> and <<erfcf>> differ from <<erf>> and <<erfc>> only in the
	argument and result types.

RETURNS
	For positive arguments, <<erf>> and all its variants return a
	probability---a number between 0 and 1.

PORTABILITY
	None of the variants of <<erf>> are ANSI C.
*/

/* double erf(double x)
 * double erfc(double x)
 *			     x
 *		      2      |\
 *     erf(x)  =  ---------  | exp(-t*t)dt
 *	 	   sqrt(pi) \| 
 *			     0
 *
 *     erfc(x) =  1-erf(x)
 *  Note that 
 *		erf(-x) = -erf(x)
 *		erfc(-x) = 2 - erfc(x)
 *
 * Method:
 *	1. For |x| in [0, 0.84375]
 *	    erf(x)  = x + x*R(x^2)
 *          erfc(x) = 1 - erf(x)           if x in [-.84375,0.25]
 *                  = 0.5 + ((0.5-x)-x*R)  if x in [0.25,0.84375]
 *	   where R = P/Q where P is an odd poly of degree 8 and
 *	   Q is an odd poly of degree 10.
 *						 -57.90
 *			| R - (erf(x)-x)/x | <= 2
 *	
 *
 *	   Remark. The formula is derived by noting
 *          erf(x) = (2/sqrt(pi))*(x - x^3/3 + x^5/10 - x^7/42 + ....)
 *	   and that
 *          2/sqrt(pi) = 1.128379167095512573896158903121545171688
 *	   is close to one. The interval is chosen because the fix
 *	   point of erf(x) is near 0.6174 (i.e., erf(x)=x when x is
 *	   near 0.6174), and by some experiment, 0.84375 is chosen to
 * 	   guarantee the error is less than one ulp for erf.
 *
 *      2. For |x| in [0.84375,1.25], let s = |x| - 1, and
 *         c = 0.84506291151 rounded to single (24 bits)
 *         	erf(x)  = sign(x) * (c  + P1(s)/Q1(s))
 *         	erfc(x) = (1-c)  - P1(s)/Q1(s) if x > 0
 *			  1+(c+P1(s)/Q1(s))    if x < 0
 *         	|P1/Q1 - (erf(|x|)-c)| <= 2**-59.06
 *	   Remark: here we use the taylor series expansion at x=1.
 *		erf(1+s) = erf(1) + s*Poly(s)
 *			 = 0.845.. + P1(s)/Q1(s)
 *	   That is, we use rational approximation to approximate
 *			erf(1+s) - (c = (single)0.84506291151)
 *	   Note that |P1/Q1|< 0.078 for x in [0.84375,1.25]
 *	   where 
 *		P1(s) = degree 6 poly in s
 *		Q1(s) = degree 6 poly in s
 *
 *      3. For x in [1.25,1/0.35(~2.857143)], 
 *         	erfc(x) = (1/x)*exp(-x*x-0.5625+R1/S1)
 *         	erf(x)  = 1 - erfc(x)
 *	   where 
 *		R1(z) = degree 7 poly in z, (z=1/x^2)
 *		S1(z) = degree 8 poly in z
 *
 *      4. For x in [1/0.35,28]
 *         	erfc(x) = (1/x)*exp(-x*x-0.5625+R2/S2) if x > 0
 *			= 2.0 - (1/x)*exp(-x*x-0.5625+R2/S2) if -6<x<0
 *			= 2.0 - tiny		(if x <= -6)
 *         	erf(x)  = sign(x)*(1.0 - erfc(x)) if x < 6, else
 *         	erf(x)  = sign(x)*(1.0 - tiny)
 *	   where
 *		R2(z) = degree 6 poly in z, (z=1/x^2)
 *		S2(z) = degree 7 poly in z
 *
 *      Note1:
 *	   To compute exp(-x*x-0.5625+R/S), let s be a single
 *	   precision number and s := x; then
 *		-x*x = -s*s + (s-x)*(s+x)
 *	        exp(-x*x-0.5626+R/S) = 
 *			exp(-s*s-0.5625)*exp((s-x)*(s+x)+R/S);
 *      Note2:
 *	   Here 4 and 5 make use of the asymptotic series
 *			  exp(-x*x)
 *		erfc(x) ~ ---------- * ( 1 + Poly(1/x^2) )
 *			  x*sqrt(pi)
 *	   We use rational approximation to approximate
 *      	g(s)=f(1/x^2) = log(erfc(x)*x) - x*x + 0.5625
 *	   Here is the error bound for R1/S1 and R2/S2
 *      	|R1/S1 - f(x)|  < 2**(-62.57)
 *      	|R2/S2 - f(x)|  < 2**(-61.52)
 *
 *      5. For inf > x >= 28
 *         	erf(x)  = sign(x) *(1 - tiny)  (raise inexact)
 *         	erfc(x) = tiny*tiny (raise underflow) if x > 0
 *			= 2 - tiny if x<0
 *
 *      7. Special case:
 *         	erf(0)  = 0, erf(inf)  = 1, erf(-inf) = -1,
 *         	erfc(0) = 1, erfc(inf) = 0, erfc(-inf) = 2, 
 *	   	erfc/erf(NaN) is NaN
 */


#include "SystemQOR/Posix/Basemath.h"

//------------------------------------------------------------------------------
namespace nsBaseCRT
{
	//------------------------------------------------------------------------------
	float Cmath::erff( float x ) 
	{
		static const float tiny= 1e-30;
		static const float half= 5.0000000000e-01; // 0x3F000000
		static const float one = 1.0000000000e+00; // 0x3F800000
		static const float two = 2.0000000000e+00; // 0x40000000
		// c = (subfloat)0.84506291151
		static const float erx = 8.4506291151e-01; // 0x3f58560b

		//Coefficients for approximation to  erfc in [1.25,1/0.35]
		 
		static const float ra0 = -9.8649440333e-03; // 0xbc21a093
		static const float ra1 = -6.9385856390e-01; // 0xbf31a0b7
		static const float ra2 = -1.0558626175e+01; // 0xc128f022
		static const float ra3 = -6.2375331879e+01; // 0xc2798057
		static const float ra4 = -1.6239666748e+02; // 0xc322658c
		static const float ra5 = -1.8460508728e+02; // 0xc3389ae7
		static const float ra6 = -8.1287437439e+01; // 0xc2a2932b
		static const float ra7 = -9.8143291473e+00; // 0xc11d077e
		static const float sa1 =  1.9651271820e+01; // 0x419d35ce
		static const float sa2 =  1.3765776062e+02; // 0x4309a863
		static const float sa3 =  4.3456588745e+02; // 0x43d9486f
		static const float sa4 =  6.4538726807e+02; // 0x442158c9
		static const float sa5 =  4.2900814819e+02; // 0x43d6810b
		static const float sa6 =  1.0863500214e+02; // 0x42d9451f
		static const float sa7 =  6.5702495575e+00; // 0x40d23f7c
		static const float sa8 = -6.0424413532e-02; // 0xbd777f97

		static const float rb0 = -9.8649431020e-03; // 0xbc21a092
		static const float rb1 = -7.9928326607e-01; // 0xbf4c9dd4
		static const float rb2 = -1.7757955551e+01; // 0xc18e104b
		static const float rb3 = -1.6063638306e+02; // 0xc320a2ea
		static const float rb4 = -6.3756646729e+02; // 0xc41f6441
		static const float rb5 = -1.0250950928e+03; // 0xc480230b
		static const float rb6 = -4.8351919556e+02; // 0xc3f1c275
		static const float sb1 =  3.0338060379e+01; // 0x41f2b459
		static const float sb2 =  3.2579251099e+02; // 0x43a2e571
		static const float sb3 =  1.5367296143e+03; // 0x44c01759
		static const float sb4 =  3.1998581543e+03; // 0x4547fdbb
		static const float sb5 =  2.5530502930e+03; // 0x451f90ce
		static const float sb6 =  4.7452853394e+02; // 0x43ed43a7
		static const float sb7 = -2.2440952301e+01; // 0xc1b38712

		//Coefficients for approximation to erf on [0,0.84375]
		static const float efx =  1.2837916613e-01; // 0x3e0375d4
		static const float efx8=  1.0270333290e+00; // 0x3f8375d4
		static const float pp0  =  1.2837916613e-01; // 0x3e0375d4
		static const float pp1  = -3.2504209876e-01; // 0xbea66beb
		static const float pp2  = -2.8481749818e-02; // 0xbce9528f
		static const float pp3  = -5.7702702470e-03; // 0xbbbd1489
		static const float pp4  = -2.3763017452e-05; // 0xb7c756b1
		static const float qq1  =  3.9791721106e-01; // 0x3ecbbbce
		static const float qq2  =  6.5022252500e-02; // 0x3d852a63
		static const float qq3  =  5.0813062117e-03; // 0x3ba68116
		static const float qq4  =  1.3249473704e-04; // 0x390aee49
		static const float qq5  = -3.9602282413e-06; // 0xb684e21a

		//Coefficients for approximation to erf in [0.84375,1.25] 
		static const float pa0  = -2.3621185683e-03; // 0xbb1acdc6
		static const float pa1  =  4.1485610604e-01; // 0x3ed46805
		static const float pa2  = -3.7220788002e-01; // 0xbebe9208
		static const float pa3  =  3.1834661961e-01; // 0x3ea2fe54
		static const float pa4  = -1.1089469492e-01; // 0xbde31cc2
		static const float pa5  =  3.5478305072e-02; // 0x3d1151b3
		static const float pa6  = -2.1663755178e-03; // 0xbb0df9c0
		static const float qa1  =  1.0642088205e-01; // 0x3dd9f331
		static const float qa2  =  5.4039794207e-01; // 0x3f0a5785
		static const float qa3  =  7.1828655899e-02; // 0x3d931ae7
		static const float qa4  =  1.2617121637e-01; // 0x3e013307
		static const float qa5  =  1.3637083583e-02; // 0x3c5f6e13
		static const float qa6  =  1.1984500103e-02; // 0x3c445aa3

		Cmp_signed__int32 hx, ix, i;
		float R, S, P, Q, s, y, z, r;
		get_float_word( hx, x );
		ix = hx & 0x7fffffff;
		if( !uword_isfinite( ix ) ) 
		{
			// erf(nan)=nan
			i = ((Cmp_unsigned__int32) hx >> 31 ) << 1;
			return (float)( 1 - i ) + one / x; // erf(+-inf)=+-1
		}

		if( ix < 0x3f580000 ) 
		{
			// |x|<0.84375
			if( ix < 0x31800000 ) 
			{
				// |x|<2**-28
				if( ix < 0x04000000 ) 
				{
					//avoid underflow
					return (float)0.125 * ( (float)8.0 * x + efx8 * x );
				}
				return x + efx * x;
			}

			z = x * x;
			r = pp0 + z * ( pp1 + z * ( pp2 + z * ( pp3 + z * pp4 ) ) );
			s = one + z * ( qq1 + z * ( qq2 + z * ( qq3 + z * ( qq4 + z * qq5 ) ) ) );
			y = r / s;
			return x + x * y;
		}

		if( ix < 0x3fa00000 ) 
		{
			// 0.84375 <= |x| < 1.25
			s = fabsf( x ) - one;
			P = pa0 + s * ( pa1 + s * ( pa2 + s * ( pa3 + s * ( pa4 + s * ( pa5 + s * pa6 ) ) ) ) );
			Q = one + s * ( qa1 + s * ( qa2 + s * ( qa3 + s * ( qa4 + s * ( qa5 + s * qa6 ) ) ) ) );
			if( hx >= 0 )
			{
				return erx + P / Q;
			}
			else
			{
				return -erx - P / Q;
			}
		}

		if( ix >= 0x40c00000 ) 
		{
			// inf>|x|>=6
			if( hx >= 0 )
			{
				return one - tiny;
			}
			else
			{
				return tiny - one;
			}
		}

		x = fabsf( x );
		s = one / ( x * x );
		if( ix < 0x4036DB6E ) 
		{
			// |x| < 1/0.35
			R = ra0 + s * ( ra1 + s * ( ra2 + s * ( ra3 + s * ( ra4 + s * ( ra5 + s * ( ra6 + s * ra7 ) ) ) ) ) );
			S = one + s * ( sa1 + s * ( sa2 + s * ( sa3 + s * ( sa4 + s * ( sa5 + s * ( sa6 + s * ( sa7 + s * sa8 ) ) ) ) ) ) );
		} 
		else 
		{	
			// |x| >= 1/0.35
			R = rb0 + s * ( rb1 + s * ( rb2 + s * ( rb3 + s * ( rb4 + s * ( rb5 + s * rb6 ) ) ) ) );
			S = one + s * ( sb1 + s * ( sb2 + s * ( sb3 + s * ( sb4 + s * ( sb5 + s * ( sb6 + s * sb7 ) ) ) ) ) );
		}

		get_float_word( ix, x );
		set_float_word( z, ix & 0xfffff000 );
		r = __ieee754_expf( -z * z - (float)0.5625 ) * __ieee754_expf( ( z - x ) * ( z + x ) + R / S );
		if( hx >= 0 )
		{
			return one - r / x;
		}
		else 
		{
			return  r / x - one;
		}
	}

	//------------------------------------------------------------------------------
	float Cmath::erfcf( float x ) 
	{
		static const float tiny= 1e-30;
		static const float half= 5.0000000000e-01; // 0x3F000000
		static const float one = 1.0000000000e+00; // 0x3F800000
		static const float two = 2.0000000000e+00; // 0x40000000
		// c = (subfloat)0.84506291151
		static const float erx = 8.4506291151e-01; // 0x3f58560b

		//Coefficients for approximation to  erfc in [1.25,1/0.35]
		 
		static const float ra0 = -9.8649440333e-03; // 0xbc21a093
		static const float ra1 = -6.9385856390e-01; // 0xbf31a0b7
		static const float ra2 = -1.0558626175e+01; // 0xc128f022
		static const float ra3 = -6.2375331879e+01; // 0xc2798057
		static const float ra4 = -1.6239666748e+02; // 0xc322658c
		static const float ra5 = -1.8460508728e+02; // 0xc3389ae7
		static const float ra6 = -8.1287437439e+01; // 0xc2a2932b
		static const float ra7 = -9.8143291473e+00; // 0xc11d077e
		static const float sa1 =  1.9651271820e+01; // 0x419d35ce
		static const float sa2 =  1.3765776062e+02; // 0x4309a863
		static const float sa3 =  4.3456588745e+02; // 0x43d9486f
		static const float sa4 =  6.4538726807e+02; // 0x442158c9
		static const float sa5 =  4.2900814819e+02; // 0x43d6810b
		static const float sa6 =  1.0863500214e+02; // 0x42d9451f
		static const float sa7 =  6.5702495575e+00; // 0x40d23f7c
		static const float sa8 = -6.0424413532e-02; // 0xbd777f97
		//Coefficients for approximation to  erfc in [1/.35,28]
		 
		static const float rb0 = -9.8649431020e-03; // 0xbc21a092
		static const float rb1 = -7.9928326607e-01; // 0xbf4c9dd4
		static const float rb2 = -1.7757955551e+01; // 0xc18e104b
		static const float rb3 = -1.6063638306e+02; // 0xc320a2ea
		static const float rb4 = -6.3756646729e+02; // 0xc41f6441
		static const float rb5 = -1.0250950928e+03; // 0xc480230b
		static const float rb6 = -4.8351919556e+02; // 0xc3f1c275
		static const float sb1 =  3.0338060379e+01; // 0x41f2b459
		static const float sb2 =  3.2579251099e+02; // 0x43a2e571
		static const float sb3 =  1.5367296143e+03; // 0x44c01759
		static const float sb4 =  3.1998581543e+03; // 0x4547fdbb
		static const float sb5 =  2.5530502930e+03; // 0x451f90ce
		static const float sb6 =  4.7452853394e+02; // 0x43ed43a7
		static const float sb7 = -2.2440952301e+01; // 0xc1b38712

		//Coefficients for approximation to erf on [0,0.84375]
		static const float efx =  1.2837916613e-01; // 0x3e0375d4
		static const float efx8=  1.0270333290e+00; // 0x3f8375d4
		static const float pp0  =  1.2837916613e-01; // 0x3e0375d4
		static const float pp1  = -3.2504209876e-01; // 0xbea66beb
		static const float pp2  = -2.8481749818e-02; // 0xbce9528f
		static const float pp3  = -5.7702702470e-03; // 0xbbbd1489
		static const float pp4  = -2.3763017452e-05; // 0xb7c756b1
		static const float qq1  =  3.9791721106e-01; // 0x3ecbbbce
		static const float qq2  =  6.5022252500e-02; // 0x3d852a63
		static const float qq3  =  5.0813062117e-03; // 0x3ba68116
		static const float qq4  =  1.3249473704e-04; // 0x390aee49
		static const float qq5  = -3.9602282413e-06; // 0xb684e21a

		//Coefficients for approximation to erf in [0.84375,1.25] 
		static const float pa0  = -2.3621185683e-03; // 0xbb1acdc6
		static const float pa1  =  4.1485610604e-01; // 0x3ed46805
		static const float pa2  = -3.7220788002e-01; // 0xbebe9208
		static const float pa3  =  3.1834661961e-01; // 0x3ea2fe54
		static const float pa4  = -1.1089469492e-01; // 0xbde31cc2
		static const float pa5  =  3.5478305072e-02; // 0x3d1151b3
		static const float pa6  = -2.1663755178e-03; // 0xbb0df9c0
		static const float qa1  =  1.0642088205e-01; // 0x3dd9f331
		static const float qa2  =  5.4039794207e-01; // 0x3f0a5785
		static const float qa3  =  7.1828655899e-02; // 0x3d931ae7
		static const float qa4  =  1.2617121637e-01; // 0x3e013307
		static const float qa5  =  1.3637083583e-02; // 0x3c5f6e13
		static const float qa6  =  1.1984500103e-02; // 0x3c445aa3

		Cmp_signed__int32 hx, ix;
		float R, S, P, Q, s, y, z, r;
		get_float_word( hx, x );
		ix = hx & 0x7fffffff;
		if( !uword_isfinite( ix ) ) 
		{
			// erfc(nan)=nan
			// erfc(+-inf)=0,2
			return (float)( ((Cmp_unsigned__int32) hx >> 31 ) << 1 ) + one / x;
		}

		if( ix < 0x3f580000 ) 
		{
			// |x|<0.84375
			if( ix < 0x23800000 ) // |x|<2**-56
			{
				return one - x;
			}
			z = x * x;
			r = pp0 + z * ( pp1 + z * ( pp2 + z * ( pp3 + z * pp4 ) ) );
			s = one + z * ( qq1 + z * ( qq2 + z * ( qq3 + z * ( qq4 + z * qq5 ) ) ) );
			y = r / s;
			if( hx < 0x3e800000 ) 
			{
				// x<1/4
				return one - ( x + x * y );
			} 
			else 
			{
				r = x * y;
				r += ( x - half );
				return half - r;
			}
		}

		if( ix < 0x3fa00000 ) 
		{
			// 0.84375 <= |x| < 1.25
			s = fabsf( x ) - one;
			P = pa0 + s * ( pa1 + s * ( pa2 + s * ( pa3 + s * ( pa4 + s * ( pa5 + s * pa6 ) ) ) ) );
			Q = one + s * ( qa1 + s * ( qa2 + s * ( qa3 + s * ( qa4 + s * ( qa5 + s * qa6 ) ) ) ) );
			if( hx >= 0 )
			{
				z  = one - erx;
				return z - P / Q; 
			} 
			else 
			{
				z = erx + P / Q;
				return one + z;
			}
		}

		if( ix < 0x41e00000 ) 
		{
			// |x|<28
			x = fabsf( x );
			s = one / ( x * x );
			if( ix < 0x4036DB6D ) 
			{	
				// |x| < 1/.35 ~ 2.857143
				R = ra0 + s * ( ra1 + s * ( ra2 + s * ( ra3 + s * ( ra4 + s * ( ra5 + s * ( ra6 + s * ra7 ) ) ) ) ) );
				S = one + s * ( sa1 + s * ( sa2 + s * ( sa3 + s * ( sa4 + s * ( sa5 + s * ( sa6 + s * ( sa7 + s * sa8 ) ) ) ) ) ) );
			} 
			else 
			{
				// |x| >= 1/.35 ~ 2.857143
				if( hx < 0 && ix >= 0x40c00000 ) 
				{
					return two - tiny;// x < -6
				}
				R = rb0 + s * ( rb1 + s * ( rb2 + s * ( rb3 + s * ( rb4 + s * ( rb5 + s * rb6 ) ) ) ) );
				S = one + s * ( sb1 + s * ( sb2 + s * ( sb3 + s * ( sb4 + s * ( sb5 + s * ( sb6 + s * sb7 ) ) ) ) ) );
			}
			get_float_word( ix, x );
			set_float_word( z, ix & 0xfffff000 );
			r = __ieee754_expf( -z * z - (float)0.5625 ) * __ieee754_expf( ( z - x ) * ( z + x ) + R / S );
			if( hx > 0 )
			{
				return r / x;
			}
			else
			{
				return two - r / x;
			}
		} 
		else 
		{
			if( hx > 0 )
			{
				return tiny * tiny;
			}
			else 
			{
				return two - tiny;
			}
		}
	}

#ifdef _DOUBLE_IS_32BITS

	//------------------------------------------------------------------------------
	double erf( double x )
	{
		return (double)erff( (float)x );
	}

	//------------------------------------------------------------------------------
	double erfc( double x )
	{
		return (double)erfcf( (float)x );
	}

#else

	//------------------------------------------------------------------------------
	double Cmath::erf( double x )
	{
		// c = (float)0.84506291151
		static const double erx =  8.45062911510467529297e-01; // 0x3FEB0AC1, 0x60000000

		static const double tiny= 1e-300;
		static const double half=  5.00000000000000000000e-01; // 0x3FE00000, 0x00000000
		static const double one =  1.00000000000000000000e+00; // 0x3FF00000, 0x00000000
		static const double two =  2.00000000000000000000e+00; // 0x40000000, 0x00000000

		//Coefficients for approximation to  erf on [0,0.84375]
		static const double efx =  1.28379167095512586316e-01; // 0x3FC06EBA, 0x8214DB69
		static const double efx8=  1.02703333676410069053e+00; // 0x3FF06EBA, 0x8214DB69
		static const double pp0  =  1.28379167095512558561e-01; // 0x3FC06EBA, 0x8214DB68
		static const double pp1  = -3.25042107247001499370e-01; // 0xBFD4CD7D, 0x691CB913
		static const double pp2  = -2.84817495755985104766e-02; // 0xBF9D2A51, 0xDBD7194F
		static const double pp3  = -5.77027029648944159157e-03; // 0xBF77A291, 0x236668E4
		static const double pp4  = -2.37630166566501626084e-05; // 0xBEF8EAD6, 0x120016AC
		static const double qq1  =  3.97917223959155352819e-01; // 0x3FD97779, 0xCDDADC09
		static const double qq2  =  6.50222499887672944485e-02; // 0x3FB0A54C, 0x5536CEBA
		static const double qq3  =  5.08130628187576562776e-03; // 0x3F74D022, 0xC4D36B0F
		static const double qq4  =  1.32494738004321644526e-04; // 0x3F215DC9, 0x221C1A10
		static const double qq5  = -3.96022827877536812320e-06; // 0xBED09C43, 0x42A26120

		//Coefficients for approximation to  erf  in [0.84375,1.25] 
		static const double pa0  = -2.36211856075265944077e-03; // 0xBF6359B8, 0xBEF77538
		static const double pa1  =  4.14856118683748331666e-01; // 0x3FDA8D00, 0xAD92B34D
		static const double pa2  = -3.72207876035701323847e-01; // 0xBFD7D240, 0xFBB8C3F1
		static const double pa3  =  3.18346619901161753674e-01; // 0x3FD45FCA, 0x805120E4
		static const double pa4  = -1.10894694282396677476e-01; // 0xBFBC6398, 0x3D3E28EC
		static const double pa5  =  3.54783043256182359371e-02; // 0x3FA22A36, 0x599795EB
		static const double pa6  = -2.16637559486879084300e-03; // 0xBF61BF38, 0x0A96073F
		static const double qa1  =  1.06420880400844228286e-01; // 0x3FBB3E66, 0x18EEE323
		static const double qa2  =  5.40397917702171048937e-01; // 0x3FE14AF0, 0x92EB6F33
		static const double qa3  =  7.18286544141962662868e-02; // 0x3FB2635C, 0xD99FE9A7
		static const double qa4  =  1.26171219808761642112e-01; // 0x3FC02660, 0xE763351F
		static const double qa5  =  1.36370839120290507362e-02; // 0x3F8BEDC2, 0x6B51DD1C
		static const double qa6  =  1.19844998467991074170e-02; // 0x3F888B54, 0x5735151D

		//Coefficients for approximation to  erfc in [1.25,1/0.35]
		static const double ra0  = -9.86494403484714822705e-03; // 0xBF843412, 0x600D6435
		static const double ra1  = -6.93858572707181764372e-01; // 0xBFE63416, 0xE4BA7360
		static const double ra2  = -1.05586262253232909814e+01; // 0xC0251E04, 0x41B0E726
		static const double ra3  = -6.23753324503260060396e+01; // 0xC04F300A, 0xE4CBA38D
		static const double ra4  = -1.62396669462573470355e+02; // 0xC0644CB1, 0x84282266
		static const double ra5  = -1.84605092906711035994e+02; // 0xC067135C, 0xEBCCABB2
		static const double ra6  = -8.12874355063065934246e+01; // 0xC0545265, 0x57E4D2F2
		static const double ra7  = -9.81432934416914548592e+00; // 0xC023A0EF, 0xC69AC25C
		static const double sa1  =  1.96512716674392571292e+01; // 0x4033A6B9, 0xBD707687
		static const double sa2  =  1.37657754143519042600e+02; // 0x4061350C, 0x526AE721
		static const double sa3  =  4.34565877475229228821e+02; // 0x407B290D, 0xD58A1A71
		static const double sa4  =  6.45387271733267880336e+02; // 0x40842B19, 0x21EC2868
		static const double sa5  =  4.29008140027567833386e+02; // 0x407AD021, 0x57700314
		static const double sa6  =  1.08635005541779435134e+02; // 0x405B28A3, 0xEE48AE2C
		static const double sa7  =  6.57024977031928170135e+00; // 0x401A47EF, 0x8E484A93
		static const double sa8  = -6.04244152148580987438e-02; // 0xBFAEEFF2, 0xEE749A62

		static const float rb0 = -9.8649431020e-03; // 0xbc21a092
		static const float rb1 = -7.9928326607e-01; // 0xbf4c9dd4
		static const float rb2 = -1.7757955551e+01; // 0xc18e104b
		static const float rb3 = -1.6063638306e+02; // 0xc320a2ea
		static const float rb4 = -6.3756646729e+02; // 0xc41f6441
		static const float rb5 = -1.0250950928e+03; // 0xc480230b
		static const float rb6 = -4.8351919556e+02; // 0xc3f1c275
		static const float sb1 =  3.0338060379e+01; // 0x41f2b459
		static const float sb2 =  3.2579251099e+02; // 0x43a2e571
		static const float sb3 =  1.5367296143e+03; // 0x44c01759
		static const float sb4 =  3.1998581543e+03; // 0x4547fdbb
		static const float sb5 =  2.5530502930e+03; // 0x451f90ce
		static const float sb6 =  4.7452853394e+02; // 0x43ed43a7
		static const float sb7 = -2.2440952301e+01; // 0xc1b38712

		Cmp_signed__int32 hx, ix, i;
		double R, S, P, Q, s, y, z, r;
		get_high_word( hx, x );
		ix = hx & 0x7fffffff;
		if( ix >= 0x7ff00000 ) 
		{
			// erf(nan)=nan
			i = ( (Cmp_unsigned__int32)hx >> 31 ) << 1;
			return (double)( 1 - i ) + one / x; // erf(+-inf)=+-1
		}

		if( ix < 0x3feb0000 ) 
		{ 
			// |x|<0.84375
			if( ix < 0x3e300000 ) 
			{
				// |x|<2**-28
				if( ix < 0x00800000 ) 
				{
					return 0.125 * ( 8.0 * x + efx8 * x );  //avoid underflow
				}
				return x + efx * x;
			}
			z = x * x;
			r = pp0 + z * ( pp1 + z * ( pp2 + z * ( pp3 + z * pp4 ) ) );
			s = one + z * ( qq1 + z * ( qq2 + z * ( qq3 + z * ( qq4 + z * qq5 ) ) ) );
			y = r / s;
			return x + x * y;
		}

		if( ix < 0x3ff40000 ) 
		{
			// 0.84375 <= |x| < 1.25
			s = fabs( x ) - one;
			P = pa0 + s * ( pa1 + s * ( pa2 + s * ( pa3 + s * ( pa4 + s * ( pa5 + s * pa6 ) ) ) ) );
			Q = one + s * ( qa1 + s * ( qa2 + s * ( qa3 + s * ( qa4 + s * ( qa5 + s * qa6 ) ) ) ) );
			if( hx >= 0 )
			{
				return erx + P / Q;
			}
			else 
			{
				return -erx - P / Q;
			}
		}

		if( ix >= 0x40180000 ) 
		{
			// inf>|x|>=6
			if( hx >= 0)
			{
				return one - tiny;
			}
			else
			{
				return tiny - one;
			}
		}

		x = fabs( x );
		s = one / ( x * x );
		if( ix< 0x4006DB6E ) 
		{	
			// |x| < 1/0.35
			R = ra0 + s * ( ra1 + s * ( ra2 + s * ( ra3 + s * ( ra4 + s * ( ra5 + s * ( ra6 + s * ra7 ) ) ) ) ) );
			S = one + s * ( sa1 + s * ( sa2 + s * ( sa3 + s * ( sa4 + s * ( sa5 + s * ( sa6 + s * ( sa7 + s * sa8 ) ) ) ) ) ) );
		} 
		else 
		{	
			// |x| >= 1/0.35
			R = rb0 + s * ( rb1 + s * ( rb2 + s * ( rb3 + s * ( rb4 + s * ( rb5 + s * rb6 ) ) ) ) );
			S = one + s * ( sb1 + s * ( sb2 + s * ( sb3 + s * ( sb4 + s * ( sb5 + s * ( sb6 + s * sb7 ) ) ) ) ) );
		}
		z = x;
		set_low_word( z, 0 );
		r = __ieee754_exp( -z * z - 0.5625 ) * __ieee754_exp( ( z - x ) * ( z + x ) + R / S );
		if( hx >= 0 )
		{
			return one - r / x;
		}
		else 
		{
			return  r / x - one;
		}
	}

	//------------------------------------------------------------------------------
	double Cmath::erfc( double x ) 
	{
		static const double erx =  8.45062911510467529297e-01; // 0x3FEB0AC1, 0x60000000

		static const double tiny= 1e-300;
		static const double half=  5.00000000000000000000e-01; // 0x3FE00000, 0x00000000
		static const double one =  1.00000000000000000000e+00; // 0x3FF00000, 0x00000000
		static const double two =  2.00000000000000000000e+00; // 0x40000000, 0x00000000

		//Coefficients for approximation to  erf  in [0.84375,1.25] 
		static const double pa0  = -2.36211856075265944077e-03; // 0xBF6359B8, 0xBEF77538
		static const double pa1  =  4.14856118683748331666e-01; // 0x3FDA8D00, 0xAD92B34D
		static const double pa2  = -3.72207876035701323847e-01; // 0xBFD7D240, 0xFBB8C3F1
		static const double pa3  =  3.18346619901161753674e-01; // 0x3FD45FCA, 0x805120E4
		static const double pa4  = -1.10894694282396677476e-01; // 0xBFBC6398, 0x3D3E28EC
		static const double pa5  =  3.54783043256182359371e-02; // 0x3FA22A36, 0x599795EB
		static const double pa6  = -2.16637559486879084300e-03; // 0xBF61BF38, 0x0A96073F
		static const double qa1  =  1.06420880400844228286e-01; // 0x3FBB3E66, 0x18EEE323
		static const double qa2  =  5.40397917702171048937e-01; // 0x3FE14AF0, 0x92EB6F33
		static const double qa3  =  7.18286544141962662868e-02; // 0x3FB2635C, 0xD99FE9A7
		static const double qa4  =  1.26171219808761642112e-01; // 0x3FC02660, 0xE763351F
		static const double qa5  =  1.36370839120290507362e-02; // 0x3F8BEDC2, 0x6B51DD1C
		static const double qa6  =  1.19844998467991074170e-02; // 0x3F888B54, 0x5735151D

		//Coefficients for approximation to  erf on [0,0.84375]
		static const double efx =  1.28379167095512586316e-01; // 0x3FC06EBA, 0x8214DB69
		static const double efx8=  1.02703333676410069053e+00; // 0x3FF06EBA, 0x8214DB69
		static const double pp0  =  1.28379167095512558561e-01; // 0x3FC06EBA, 0x8214DB68
		static const double pp1  = -3.25042107247001499370e-01; // 0xBFD4CD7D, 0x691CB913
		static const double pp2  = -2.84817495755985104766e-02; // 0xBF9D2A51, 0xDBD7194F
		static const double pp3  = -5.77027029648944159157e-03; // 0xBF77A291, 0x236668E4
		static const double pp4  = -2.37630166566501626084e-05; // 0xBEF8EAD6, 0x120016AC
		static const double qq1  =  3.97917223959155352819e-01; // 0x3FD97779, 0xCDDADC09
		static const double qq2  =  6.50222499887672944485e-02; // 0x3FB0A54C, 0x5536CEBA
		static const double qq3  =  5.08130628187576562776e-03; // 0x3F74D022, 0xC4D36B0F
		static const double qq4  =  1.32494738004321644526e-04; // 0x3F215DC9, 0x221C1A10
		static const double qq5  = -3.96022827877536812320e-06; // 0xBED09C43, 0x42A26120

		//Coefficients for approximation to  erfc in [1.25,1/0.35]
		static const double ra0  = -9.86494403484714822705e-03; // 0xBF843412, 0x600D6435
		static const double ra1  = -6.93858572707181764372e-01; // 0xBFE63416, 0xE4BA7360
		static const double ra2  = -1.05586262253232909814e+01; // 0xC0251E04, 0x41B0E726
		static const double ra3  = -6.23753324503260060396e+01; // 0xC04F300A, 0xE4CBA38D
		static const double ra4  = -1.62396669462573470355e+02; // 0xC0644CB1, 0x84282266
		static const double ra5  = -1.84605092906711035994e+02; // 0xC067135C, 0xEBCCABB2
		static const double ra6  = -8.12874355063065934246e+01; // 0xC0545265, 0x57E4D2F2
		static const double ra7  = -9.81432934416914548592e+00; // 0xC023A0EF, 0xC69AC25C
		static const double sa1  =  1.96512716674392571292e+01; // 0x4033A6B9, 0xBD707687
		static const double sa2  =  1.37657754143519042600e+02; // 0x4061350C, 0x526AE721
		static const double sa3  =  4.34565877475229228821e+02; // 0x407B290D, 0xD58A1A71
		static const double sa4  =  6.45387271733267880336e+02; // 0x40842B19, 0x21EC2868
		static const double sa5  =  4.29008140027567833386e+02; // 0x407AD021, 0x57700314
		static const double sa6  =  1.08635005541779435134e+02; // 0x405B28A3, 0xEE48AE2C
		static const double sa7  =  6.57024977031928170135e+00; // 0x401A47EF, 0x8E484A93
		static const double sa8  = -6.04244152148580987438e-02; // 0xBFAEEFF2, 0xEE749A62
		//Coefficients for approximation to  erfc in [1/.35,28]
		static const double rb0  = -9.86494292470009928597e-03; // 0xBF843412, 0x39E86F4A
		static const double rb1  = -7.99283237680523006574e-01; // 0xBFE993BA, 0x70C285DE
		static const double rb2  = -1.77579549177547519889e+01; // 0xC031C209, 0x555F995A
		static const double rb3  = -1.60636384855821916062e+02; // 0xC064145D, 0x43C5ED98
		static const double rb4  = -6.37566443368389627722e+02; // 0xC083EC88, 0x1375F228
		static const double rb5  = -1.02509513161107724954e+03; // 0xC0900461, 0x6A2E5992
		static const double rb6  = -4.83519191608651397019e+02; // 0xC07E384E, 0x9BDC383F
		static const double sb1  =  3.03380607434824582924e+01; // 0x403E568B, 0x261D5190
		static const double sb2  =  3.25792512996573918826e+02; // 0x40745CAE, 0x221B9F0A
		static const double sb3  =  1.53672958608443695994e+03; // 0x409802EB, 0x189D5118
		static const double sb4  =  3.19985821950859553908e+03; // 0x40A8FFB7, 0x688C246A
		static const double sb5  =  2.55305040643316442583e+03; // 0x40A3F219, 0xCEDF3BE6
		static const double sb6  =  4.74528541206955367215e+02; // 0x407DA874, 0xE79FE763
		static const double sb7  = -2.24409524465858183362e+01; // 0xC03670E2, 0x42712D62

		Cmp_signed__int32 hx, ix;
		double R, S, P, Q, s, y, z, r;
		get_high_word( hx, x );
		ix = hx & 0x7fffffff;
		if( ix >= 0x7ff00000 ) 
		{
			// erfc(nan)=nan
			// erfc(+-inf)=0,2
			return (double)( ((Cmp_unsigned__int32) hx >> 31 ) << 1 ) + one / x;
		}

		if( ix < 0x3feb0000 ) 
		{
			// |x|<0.84375
			if( ix < 0x3c700000 )  	// |x|<2**-56
			{
				return one - x;
			}
			z = x * x;
			r = pp0 + z * ( pp1 + z * ( pp2 + z * ( pp3 + z * pp4 ) ) );
			s = one + z * ( qq1 + z * ( qq2 + z * ( qq3 + z * ( qq4 + z * qq5 ) ) ) );
			y = r / s;
			if( hx < 0x3fd00000 ) 
			{  	
				// x<1/4
				return one - ( x + x * y );
			} 
			else 
			{
				r = x * y;
				r += ( x - half );
				return half - r ;
			}
		}

		if( ix < 0x3ff40000 ) 
		{
			// 0.84375 <= |x| < 1.25
			s = fabs( x ) - one;
			P = pa0 + s * ( pa1 + s * ( pa2 + s * ( pa3 + s * ( pa4 + s * ( pa5 + s * pa6 ) ) ) ) );
			Q = one + s * ( qa1 + s * ( qa2 + s * ( qa3 + s * ( qa4 + s * ( qa5 + s * qa6 ) ) ) ) );
			if( hx >= 0 ) 
			{
				z  = one - erx;
				return z - P / Q; 
			} 
			else 
			{
				z = erx + P / Q;
				return one + z;
			}
		}

		if( ix < 0x403c0000 ) 
		{
			// |x|<28
			x = fabs( x );
			s = one / ( x * x );
			if( ix< 0x4006DB6D ) 
			{	
				// |x| < 1/.35 ~ 2.857143
				R = ra0 + s * ( ra1 + s * ( ra2 + s * ( ra3 + s * ( ra4 + s * ( ra5 + s * ( ra6 + s * ra7 ) ) ) ) ) );
				S = one + s * ( sa1 + s * ( sa2 + s * ( sa3 + s * ( sa4 + s * ( sa5 + s * ( sa6 + s * ( sa7 + s * sa8 ) ) ) ) ) ) );
			} 
			else 
			{
				// |x| >= 1/.35 ~ 2.857143
				if( hx < 0 && ix >= 0x40180000 )
				{
					return two - tiny;// x < -6
				}
				R = rb0 + s * ( rb1 + s * ( rb2 + s * ( rb3 + s * ( rb4 + s * ( rb5 + s * rb6 ) ) ) ) );
				S = one + s * ( sb1 + s * ( sb2 + s * ( sb3 + s * ( sb4 + s * ( sb5 + s * ( sb6 + s * sb7 ) ) ) ) ) );
			}
			z  = x;
			set_low_word( z, 0 );
			r = __ieee754_exp( -z * z - 0.5625 )* __ieee754_exp( ( z - x ) * ( z + x ) + R / S );
			if( hx > 0 )
			{
				return r / x;
			}
			else 
			{
				return two - r / x;
			}
		} 
		else 
		{
			if( hx > 0 )
			{
				return tiny * tiny;
			}
			else 
			{
				return two - tiny;
			}
		}
	}

#endif//_DOUBLE_IS_32BITS

};//namespace nsBaseCRT
