/*
 ****************************************************************************
 * HISTORY
 * $Log:	alloca.h,v $
 * Revision 1.3  90/12/03  17:43:51  bww
 * 	Also use __builtin_alloca under GNU C.
 * 	[90/12/03  17:43:26  bww]
 * 
 * Revision 1.2  90/03/01  16:00:30  bww
 * 	CMU CS as of 90/02/27
 * 	[90/03/01  16:00:27  bww]
 * 
 * Revision 1.1  90/02/27  20:55:52  mja
 * 	Created.
 * 
 ****************************************************************************
 *
 *  Certain compilers (such as on the SUN-4) have alloca() built-in and need
 *  the standard name to be redefined to trigger properly.
 */

#if	__GNUC__ || defined(sun4)
#define alloca(x)	__builtin_alloca(x)
#endif
