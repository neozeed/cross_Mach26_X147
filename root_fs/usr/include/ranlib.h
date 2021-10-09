/*	ranlib.h	4.2	87/04/06	*/

/*
 * HISTORY
 * $Log:	ranlib.h,v $
 * Revision 2.2  89/07/22  16:12:12  bww
 * 	Added ran_comsize_or_dt field for the Multimax.
 * 	From "[89/07/18  10:01:54  mbj]" at CMU.
 * 	[89/07/22            bww]
 * 
 */

#define	RANLIBMAG	"__.SYMDEF"

/*
 * Structure of the __.SYMDEF table of contents for an archive.
 * __.SYMDEF begins with a word giving the number of ranlib structures
 * which immediately follow, and then continues with a string
 * table consisting of a word giving the number of bytes of strings
 * which follow and then the strings themselves.
 * The ran_strx fields index the string table whose first byte is numbered 0.
 *
#if	multimax
 * The last field is an integer that has three different meanings
 * depending upon its value. If ran_comsize_or_dt is greater than
 * zero, then the symbol is declared to be common of this size.
 * If it is zero, then the symbol is defined in the data section.
 * If it is -1, then the symbol is defined in the text section.
#endif
 */
struct	ranlib {
	union {
		off_t	ran_strx;	/* string table index of */
		char	*ran_name;	/* symbol defined by */
	} ran_un;
	off_t	ran_off;		/* library member at this offset */
#if	multimax
	long	ran_comsize_or_dt;
#endif
};
