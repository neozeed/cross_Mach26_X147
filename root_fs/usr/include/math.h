/*
 * Copyright (c) 1985 Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 * All recipients should regard themselves as participants in an ongoing
 * research project and hence should feel obligated to report their
 * experiences (good or bad) with these elementary function codes, using
 * the sendbug(8) program, to the authors.
 *
 *	@(#)math.h	5.3 (Berkeley) 6/30/88
 *
 **********************************************************************
 * HISTORY
 * $Log:	math.h,v $
 * Revision 2.9  90/12/12  11:10:26  bww
 * 	Reorganized to factor out common declarations.
 * 	[90/12/12  11:04:45  bww]
 * 
 * Revision 2.8  90/11/16  16:15:04  bww
 * 	Define HUGE as infinity() on the SUN-4.  This is the way
 * 	SunOS provides this value which may or may not be an IEEE
 * 	standard that needs to be investigated further to determine
 * 	the proper way to commonly define it for all platforms.
 * 	From "[90/03/15  12:49:04  mja]" at CMU.
 * 	[90/11/16  16:14:14  bww]
 * 
 * Revision 2.7  90/08/26  13:37:52  bww
 * 	Added support for mac2.
 * 	[90/08/26  13:36:59  bww]
 * 
 * Revision 2.6  90/07/29  14:06:09  bww
 * 	Added support for i386.
 * 	From "8-May-90  Mary Thompson (mrt)" at CMU.
 * 	[90/07/29  14:05:58  bww]
 * 
 * Revision 2.5  89/10/26  16:53:36  bww
 * 	Add ibmrt case for copysign(), drem(), logb(), scalb() and finite().
 * 	From "[89/10/26  17:14:34  mja]" at CMU.
 * 	[89/10/26            bww]
 * 
 * Revision 2.4  89/08/14  13:43:52  bww
 * 	Added Multimax math.h declarations.  Corrected declaration
 * 	of complex.  From "[89/08/08  13:27:51  mbj]" at CMU.
 * 	Add HUGE and MAXFLOAT defintions for PMAX (mips).
 * 	From "[89/03/29            mja]" at CMU.
 * 	[89/08/14            bww]
 * 
 * Revision 2.3  89/06/30  12:11:02  bww
 * 	Added function prototype declarations.
 * 	[89/06/30  11:57:32  bww]
 * 
 * Revision 2.2  89/06/26  20:20:10  bww
 * 	Merged SUN3, IBMRT, Sequent, and Mutlimax changes into
 * 	4.3-tahoe version.
 * 	[89/06/26  20:14:25  bww]
 * 
 * Revision 1.2  89/06/04  19:17:59  bww
 * 	CMU CS as of 89/05/15
 * 	[89/06/04  19:14:49  bww]
 * 
 **********************************************************************
 */

#ifndef	_MATH_H_
#define	_MATH_H_

#if	__STDC__
typedef struct { double r, i; } complex;

extern double asinh(double), acosh(double), atanh(double);
extern double erf(double), erfc(double);
extern double exp(double), expm1(double), log(double);
extern double log10(double), log1p(double), pow(double, double);
extern double fabs(double), floor(double), ceil(double), rint(double);
extern double lgamma(double);
extern double hypot(double, double), cabs(complex);
extern double j0(double), j1(double), jn(int, double);
extern double y0(double), y1(double), yn(int, double);
extern double sin(double), cos(double), tan(double);
extern double asin(double), acos(double), atan(double), atan2(double, double);
extern double sinh(double), cosh(double), tanh(double);
extern double cbrt(double), sqrt(double);
extern double modf(double, double*), ldexp(double, int);
extern double frexp(double, int*), atof(const char*);
#else
extern double asinh(), acosh(), atanh();
extern double erf(), erfc();
extern double exp(), expm1(), log();
extern double log10(), log1p(), pow();
extern double fabs(), floor(), ceil(), rint();
extern double lgamma();
extern double hypot(), cabs();
extern double j0(), j1(), jn();
extern double y0(), y1(), yn();
extern double sin(), cos(), tan();
extern double asin(), acos(), atan(), atan2();
extern double sinh(), cosh(), tanh();
extern double cbrt(), sqrt();
extern double modf(), ldexp();
extern double frexp(), atof();
#endif

#if	defined(vax) || defined(sun) || defined(ibmrt) || defined(i386)
#if	__STDC__
extern double copysign(double, double), drem(double, double);
extern double logb(double), scalb(double, int);
extern int finite(double);
#else
extern double copysign(), drem();
extern double logb(), scalb();
extern int finite();
#endif
#endif	/* vax || sun || ibmrt || i386 */

#if	defined(mac2)
#if	__STDC__
extern double copysign(double, double);
extern double z_abs(const complex*);
extern int finite(double);
#else
extern double copysign();
extern double z_abs();
extern int finite();
#endif
#endif	/* mac2 */

#if	defined(vax) || defined(tahoe)
#if	__STDC__
extern double infnan(int);
#else
extern double infnan();
#endif
#endif	/* vax || tahoe */

/*
 * some useful constants
 */
#define M_E		2.7182818284590452354
#define M_LOG2E		1.4426950408889634074
#define M_LOG10E	0.43429448190325182765
#define M_LN2		0.69314718055994530942
#define M_LN10		2.30258509299404568402
#define M_PI		3.14159265358979323846
#define M_PI_2		1.57079632679489661923
#define M_PI_4		0.78539816339744830962
#define M_1_PI		0.31830988618379067154
#define M_2_PI		0.63661977236758134308
#define M_2_SQRTPI	1.12837916709551257390
#define M_SQRT2		1.41421356237309504880
#define M_SQRT1_2	0.70710678118654752440

#if	defined(vax) || defined(i386)
#define HUGE	1.701411733192644270e38
#endif

#if	defined(ibmrt)
#define HUGE	1.7976931348623158e308
#endif

#if	defined(mips)
#define	HUGE		1.8e+308
#define	MAXFLOAT	((float)3.40282346638528860e+38)
#endif	/* mips */

#if	defined(mac2)
#ifdef	__HAVE_68881__
#include <math-68881.h>
#else
#define HUGE	1.7976931348623158e308
#endif
#endif

#if	defined(multimax)
#ifndef MAXDOUBLE
# include <values.h>
#endif
#define HUGE	MAXDOUBLE
#endif

#if	defined(sun)
#if	defined(sun4)
extern double infinity();
#define	HUGE		infinity()
#else	/* sun4 */
#define MAXFLOAT	((float)3.40282346638528860e+38)
#define HUGE		99.e999
#endif	/* sun4 */
#endif	/* sun */

#if	defined(balance)
/* 
 * Single Precision Constant (derived from bc function):
 * 	scale = 90
 *	use 2^127*(2-2^(-23)) 
 *      and 2^127*(2-2^(-60)) to nail down the precison
 *
 * Double Precision Constant could be used but what if the poor
 * little user was using single precision and we tried to return
 * a HUGE constant into a single precision.  Poof! a double trap!
 *
 * Double wants to be:	#define HUGE	1.7976931348623158e308
 */
#define HUGE	3.40282346638528860e+38
#endif /* balance */

#if	defined(sun) || defined(multimax)
#ifndef	_POLY9
/*
 * features from sys v
 */
extern int errno, signgam;
extern double fmod(), gamma();
extern int matherr();

#define _ABS(x)	((x) < 0 ? -(x) : (x))
#define _REDUCE(TYPE, X, XN, C1, C2)	{ \
	double x1 = (double)(TYPE)X, x2 = X - x1; \
	X = x1 - (XN) * (C1); X += x2; X -= (XN) * (C2); }
#define _POLY1(x, c)	((c)[0] * (x) + (c)[1])
#define _POLY2(x, c)	(_POLY1((x), (c)) * (x) + (c)[2])
#define _POLY3(x, c)	(_POLY2((x), (c)) * (x) + (c)[3])
#define _POLY4(x, c)	(_POLY3((x), (c)) * (x) + (c)[4])
#define _POLY5(x, c)	(_POLY4((x), (c)) * (x) + (c)[5])
#define _POLY6(x, c)	(_POLY5((x), (c)) * (x) + (c)[6])
#define _POLY7(x, c)	(_POLY6((x), (c)) * (x) + (c)[7])
#define _POLY8(x, c)	(_POLY7((x), (c)) * (x) + (c)[8])
#define _POLY9(x, c)	(_POLY8((x), (c)) * (x) + (c)[9])

struct exception {
	int type;
	char *name;
	double arg1;
	double arg2;
	double retval;
};

#define DOMAIN		1
#define	SING		2
#define	OVERFLOW	3
#define	UNDERFLOW	4
#define	TLOSS		5
#define	PLOSS		6
#endif	/* _POLY9 */
#endif	/* sun || multimax */

#endif	/* _MATH_H_ */
