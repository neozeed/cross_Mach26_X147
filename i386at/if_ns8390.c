/*
 * Mach Operating System
 * Copyright (c) 1990 Carnegie-Mellon University
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	if_ns8390.c,v $
 * Revision 2.1.1.10  91/03/28  08:45:51  rvb
 * 	elii_bnc was not as advertised in the manual.  Now it is.
 * 	Also config_3c503 more closely follows spec.
 * 	[91/03/12            rvb]
 * 
 * Revision 2.1.1.9  91/01/30  08:50:26  rvb
 * 	Get packet sizes correct for logging and for 3.0
 * 
 * 
 * Revision 2.6  91/01/09  16:07:19  rpd
 * 	Fixed typo in ns8390probe.
 * 	[91/01/09            rpd]
 * 
 * Revision 2.5  91/01/08  17:35:46  rpd
 * 	Changed NET_KMSG_GET to net_kmsg_get.
 * 	[91/01/08            rpd]
 * 
 * Revision 2.4  91/01/08  17:33:05  rpd
 * 	A few bug fixes.
 * 	[91/01/08  16:41:04  rvb]
 * 
 * 	Make this a generic driver for ns8390 from wd8003 because
 * 	we now will also support etherlink ii.
 * 	[91/01/04  12:25:21  rvb]
 * 
 * Revision 2.1.1.7  90/11/27  13:43:18  rvb
 * 	Synched 2.5 & 3.0 at I386q (r2.1.1.7) & XMK35 (r2.3)
 * 	[90/11/15            rvb]
 * 
 * Revision 2.2  90/10/01  14:23:09  jeffreyh
 * 	Changes for MACH_KERNEL. 
 * 	initial checkin.
 * 	[90/09/27  18:22:09  jeffreyh]
 *
 * Revision 2.1.1.6  90/09/18  08:38:39  rvb
 * 	Unfortunately, the switches to bank 0 seem necessary so are back
 * 	in.
 * 	[90/09/08            rvb]
 * 
 * Revision 2.1.1.5  90/08/25  15:42:58  rvb
 * 	Use take_<>_irq() vs direct manipulations of ivect and friends.
 * 	[90/08/20            rvb]
 * 
 * 	Flush unnecessary switches to bank 0. Use error counters
 * 	vs printouts.  Fix DSF_RUNNING.  Some more cleanup.
 * 	[90/08/14            rvb]
 * 
 * Revision 2.1.1.4  90/07/28  10:00:40  rvb
 * 	Get correct counter offsets
 * 
 * Revision 2.1.1.3  90/07/27  17:16:05  rvb
 * 	No multicast for now.
 * 
 * Revision 2.1.1.2  90/07/27  11:25:11  rvb
 * 	Add boardID support for wd80xxyyy family of boards.	[rweiss]
 * 	Bunch of cleanup and ...		[rweiss&rvb]
 * 
 * Revision 2.1.1.1  90/07/10  11:44:46  rvb
 * 	Added to system.
 * 	[90/07/06            rvb]
 *
 *
 *   Author: Ron Weiss (rweiss)
 *
 */
 
/* NOTE:
 *	There are three outstanding bug/features in this implementation.
 * They may even be hardware misfeatures.  The conditions are registered
 * by counters maintained by the software.
 *	1: over_write is a condition that means that the board wants to store
 * packets, but there is no room.  So new packets are lost.  What seems to
 * be happening is that we get an over_write condition, but there are no
 * or just a few packets in the board's ram.  Also it seems that we get
 * several over_writes in a row.
 *	2: Since there is only one transmit buffer, we need a lock to indicate
 * whether it is in use.  We clear this lock when we get a transmit interrupt.
 * Sometimes we go to transmit and although there is no transmit in progress,
 * the lock is set.  (In this case, we just ignore the lock.)  It would look
 * like we can miss transmit interrupts?
 *	3: We tried to clean up the unnecessary switches to bank 0.  
 * Unfortunately, when you do an ifconfig "down", the system tend to lock up
 * a few seconds later (this was when DSF_RUNNING) was not being set before.
 * But even with DSF_RUNNING, on an EISA bus machine we ALWAYS lock up after
 * a few seconds. 
 */

/*
 * Western Digital 8003E Mach Ethernet driver (for intel 80386)
 * Copyright (c) 1990 by Open Software Foundation (OSF).
 */

/*
  Copyright 1990 by Open Software Foundation,
Cambridge, MA.

		All Rights Reserved

  Permission to use, copy, modify, and distribute this software and
its documentation for any purpose and without fee is hereby granted,
provided that the above copyright notice appears in all copies and
that both the copyright notice and this permission notice appear in
supporting documentation, and that the name of OSF or Open Software
Foundation not be used in advertising or publicity pertaining to
distribution of the software without specific, written prior
permission.

  OSF DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE
<INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS,
IN NO EVENT SHALL OSF BE LIABLE FOR ANY SPECIAL, INDIRECT, OR
CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
LOSS OF USE, DATA OR PROFITS, WHETHER IN ACTION OF CONTRACT,
NEGLIGENCE, OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

#define IF_CNTRS	MACH
#include	<ns8390.h>

#ifdef	MACH_KERNEL
#include	<kern/time_out.h>
#include	<device/device_types.h>
#include	<device/errno.h>
#include	<device/io_req.h>
#include	<device/if_hdr.h>
#include	<device/if_ether.h>
#include	<device/net_status.h>
#include	<device/net_io.h>
#else	MACH_KERNEL
#include	<sys/param.h>
#include	<mach/machine/vm_param.h>
#include	<sys/systm.h>
#include	<sys/mbuf.h>
#include	<sys/buf.h>
#include	<sys/protosw.h>
#include	<sys/socket.h>
#include	<sys/vmmac.h>
#include	<sys/ioctl.h>
#include	<sys/errno.h>
#include	<sys/syslog.h>

#include	<net/if.h>
#include	<net/netisr.h>
#include	<net/route.h>

#ifdef	INET
#include	<netinet/in.h>
#include	<netinet/in_systm.h>
#include	<netinet/in_var.h>
#include	<netinet/ip.h>
#include	<netinet/if_ether.h>
#endif

#ifdef	NS
#include	<netns/ns.h>
#include	<netns/ns_if.h>
#endif
#endif	MACH_KERNEL

#include	<i386/ipl.h>
#include	<i386at/atbus.h>
#include	<i386at/if_ns8390.h>
#include	<i386at/if_wd8003.h>
#include	<i386at/if_3c503.h>

#define	SPLNET	spl6


int	ns8390probe();
int	ns8390attach();
int	ns8390intr();
int	ns8390init();
int	ns8390output();
int	ns8390ioctl();
int	ns8390reset();
int     ns8390rcv();
int	ns8390watch();
int     ns8390get_CURR();
int     ns8390over_write();

int	(*ns8390intrs[])() = {	ns8390intr, 0};

struct	isa_dev	*ns8390info[NNS8390];

struct	isa_driver	ns8390driver =
	{ns8390probe, 0, ns8390attach, "ns8390", 0, 0, 0};

int	watchdog_id;

char *wd8003_card = "wd";
char *elii_card = "el";
/*		  2e0, 2a0, 280,  250,   350,   330,   310, 300*/
int elii_irq[8] = {5,   2,   2, 0x711, 0x711, 0x711, 0x711,  5};
int elii_bnc[8] = {1,   0,   1, 0x711, 0x711, 0x711, 0x711,  0};
/*int elii_bnc[8] = {0, 1,   1,     1,     1,     1,     0,  1}; */

typedef struct {
#ifdef	MACH_KERNEL
	struct	ifnet	ds_if;		/* generic interface header */
	u_char	ds_addr[6];		/* Ethernet hardware address */
#else	MACH_KERNEL
	struct	arpcom	ns8390_ac;
#define	ds_if	ns8390_ac.ac_if
#define	ds_addr	ns8390_ac.ac_enaddr
#endif	MACH_KERNEL
	int	flags;
	int     timer;
	int     interrupt;
	char 	*nic;
	u_char   address[ETHER_ADDR_SIZE];
#if	CMUCS
	short	mode;
#endif	CMUCS
	int     tbusy;
	char    *sram;		/* beginning of the shared memory RAM buffer */
	int     read_nxtpkt_ptr;/* pointer to next packet available */
	int     pstart;		/* page start hold */
	int     pstop;		/* page stop hold */
	int     tpsr;		/* transmit page start hold */
	int     fifo_depth;	/* NIC fifo threshold */
	char	*card;
	int     board_id;
}
ns8390_softc_t;

ns8390_softc_t	ns8390_softc[NNS8390];

struct ns8390_cntrs {
u_int	ovw,
	jabber,
	crc,
	frame,
	miss,
	fifo,
	rcv;
u_int	xmt,
	xmti,
	busy,
	heart;
} ns8390_cntrs[NNS8390];

#ifdef	IF_CNTRS
int ns_narp = 1, ns_arp = 0;
int ns_ein[32], ns_eout[32]; 
int ns_lin[128/8], ns_lout[128/8]; 
static
log_2(no)
unsigned long no;
{
	return ({ unsigned long _temp__;
		asm("bsr %1, %0; jne 0f; xorl %0, %0; 0:" :
		    "=r" (_temp__) : "a" (no));
		_temp__;});
}
#endif	IF_CNTRS

int  imr_hold = PRXE|PTXE|RXEE|TXEE|OVWE|CNTE;  /* Interrupts mask bits */

/*
 * ns8390probe:
 *
 *	This function "probes" or checks for the wd8003 board on the bus to see
 *	if it is there.  As far as I can tell, the best break between this
 *	routine and the attach code is to simply determine whether the board
 *      is configured in properly. Currently my approach to this is to test the
 *      base I/O special offset for the Western Digital unique byte sequence
 *      identifier.  If the bytes match we assume board is there.
 *	The config code expects to see a successful return from the probe
 *	routine before attach will be called.
 *
 * input	: address device is mapped to, and unit # being checked
 * output	: a '1' is returned if the board exists, and a 0 otherwise
 *
 */

ns8390probe(dev)
struct isa_dev	*dev;
{
	caddr_t		hdwbase = dev->dev_addr;
	int		unit = dev->dev_unit;
	ns8390_softc_t	*sp = &ns8390_softc[unit];
	int		tmp;

	if ((unit < 0) || (unit > NNS8390)) {
		printf("ns8390 ethernet unit %d out of range\n", unit);
		return(0);
	}
	if (	((u_char) inb(hdwbase+LAR) == (u_char) WD_NODE_ADDR_0) &&
		((u_char) inb(hdwbase+LAR2) == (u_char) WD_NODE_ADDR_1) &&
		((u_char) inb(hdwbase+LAR3) == (u_char) WD_NODE_ADDR_2)) {
			ns8390info[unit] = dev;
			sp->card = wd8003_card;
			sp->nic = hdwbase + OFF_8390;
				/* enable mem access to board */
			sp->board_id = wd80xxget_board_id(dev);

			*(sp->address)      = inb(hdwbase+LAR);
			*(sp->address + 1)  = inb(hdwbase+LAR + 1);
			*(sp->address + 2)  = inb(hdwbase+LAR + 2);
			*(sp->address + 3)  = inb(hdwbase+LAR + 3);
			*(sp->address + 4)  = inb(hdwbase+LAR + 4);
			*(sp->address + 5)  = inb(hdwbase+LAR + 5);
			return (1);
		}  /* checks the address of the board to verify that it is a WD */
	if (tmp = inb(hdwbase+BCFR)) {
		switch(tmp) {
		case (1<<7):	sp->board_id = 7; break;	/*irq5 xvcr*/
#ifdef	not_currently_possible
		case (1<<6):	sp->board_id = 6; break;
		case (1<<5):	sp->board_id = 5; break;
		case (1<<4):	sp->board_id = 4; break;
		case (1<<3):	sp->board_id = 3; break;
#endif	not_currently_possible
		case (1<<2):	sp->board_id = 2; break;	/*irq2 bnc*/
		case (1<<1):	sp->board_id = 1; break;	/*irq2 xvcr*/
		case (1<<0):	sp->board_id = 0; break;	/*irq5 bnc*/
		default:	return 0;
		}
		switch (inb(hdwbase+PCFR)) {
		case (1<<7):	dev->dev_start = (caddr_t) 0xDC000; break;
		case (1<<6):	dev->dev_start = (caddr_t) 0xD8000; break;
#ifdef	not_currently_possible
		case (1<<5):	dev->dev_start = (caddr_t) 0xCC000; break;
		case (1<<4):	dev->dev_start = (caddr_t) 0xC8000; break;
#endif	not_currently_possible
		default:
			printf("EtherLink II with NO memory configured\n");
			return 0;
		}
		ns8390info[unit] = dev;
		dev->dev_pic = elii_irq[sp->board_id];
		if (dev->dev_pic == 2)
			dev->dev_pic = 9;
		sp->card = elii_card;
		sp->nic = hdwbase;
		return 1;
	}
	return(0);
}

/*
 * ns8390attach:
 *
 *	This function attaches a ns8390 board to the "system".  The rest of
 *	runtime structures are initialized here (this routine is called after
 *	a successful probe of the board).  Once the ethernet address is read
 *	and stored, the board's ifnet structure is attached and readied.
 *
 * input	: isa_dev structure setup in autoconfig
 * output	: board structs and ifnet is setup
 *
 */

ns8390attach(dev)
struct isa_dev	*dev;
{
	ns8390_softc_t	*sp;
	struct	ifnet	*ifp;
	u_char		unit;
	int             temp;

	take_dev_irq(dev);
	unit = (u_char)dev->dev_unit;
	sp = &ns8390_softc[unit];
	printf("%s%d:  port = %x, spl = %d, pic = %d. ",
		sp->card, unit, dev->dev_addr, dev->dev_spl, dev->dev_pic);

	(volatile char *)sp->sram =
	    (volatile char *) phystokv(dev->dev_start);
	dev->dev_addr = (char *) phystokv(dev->dev_addr);
	sp->timer = -1;
	sp->flags = 0;
	sp->mode  = 0;

	if (!ns8390hwrst(unit)) {
		printf("%s%d: attach(): reset failed.\n",
			sp->card, unit);
		return;
	}
		/* N.B. sp->address is not determined till
		 * hwrst time. */
	*(sp->ds_addr)      = *(sp->address);
	*(sp->ds_addr + 1)  = *(sp->address + 1);
	*(sp->ds_addr + 2)  = *(sp->address + 2);
	*(sp->ds_addr + 3)  = *(sp->address + 3);
	*(sp->ds_addr + 4)  = *(sp->address + 4);
	*(sp->ds_addr + 5)  = *(sp->address + 5);

	printf("ethernet id [%x:%x:%x:%x:%x:%x]\n",
		sp->address[0],sp->address[1],sp->address[2],
		sp->address[3],sp->address[4],sp->address[5]);
	ifp = &(sp->ds_if);
	ifp->if_unit = unit;
	ifp->if_mtu = ETHERMTU;
	ifp->if_flags = IFF_BROADCAST;
#ifdef	MACH_KERNEL
	ifp->if_header_size = sizeof(struct ether_header);
	ifp->if_header_format = HDR_ETHERNET;
	ifp->if_address_size = 6;
	ifp->if_address = (char *)&sp->address[0];
	if_init_queues(ifp);
#else	MACH_KERNEL
	ifp->if_name = sp->card;
	ifp->if_init = ns8390init;
	ifp->if_output = ns8390output;
	ifp->if_ioctl = ns8390ioctl;
	ifp->if_reset = ns8390reset;
	ifp->if_next = NULL;
	if_attach(ifp);
#ifdef notdef
	watchdog_id = timeout(ns8390watch, &(ifp->if_unit), 20*HZ);
#endif
#endif	MACH_KERNEL
}

/*
 * ns8390watch():
 *
 */

int
ns8390watch(b_ptr)
caddr_t	b_ptr;
{
	int	x,
		y,
		opri,
		unit;
	int     temp_cr;
	caddr_t nic;

	unit = *b_ptr;
#ifdef	MACH_KERNEL
	timeout(ns8390watch,b_ptr,20*HZ);
#else	MACH_KERNEL
	watchdog_id = timeout(ns8390watch,b_ptr,20*HZ);
#endif	MACH_KERNEL
	nic = ns8390_softc[unit].nic;
	temp_cr = inb(nic+CR);
	outb(nic + CR, (temp_cr & 0x3f) | PS0);
	printf("<<< ISR=%x CURR=%x rdnxt=%x BNDY=%x>>> ",
		inb(nic + ISR),
		ns8390get_CURR(unit), ns8390_softc[unit].read_nxtpkt_ptr,
		inb(nic+BNDY));
	outb(nic+CR,temp_cr);
}

#ifdef	MACH_KERNEL
int ns8390start();	/* forward */

/*ARGSUSED*/
wd8003open(dev, flag)
	dev_t	dev;
	int	flag;
{
	register int	unit = minor(dev);

	if (ns8390_softc[unit].card != wd8003_card)
		return (ENXIO);
	if (unit < 0 || unit >= NNS8390 ||
		ns8390_softc[unit].nic == 0)
	    return (ENXIO);

	ns8390_softc[unit].ds_if.if_flags |= IFF_UP;
	ns8390init(unit);
	return(0);
}

eliiopen(dev, flag)
	dev_t	dev;
	int	flag;
{
	register int	unit = minor(dev);

	if (ns8390_softc[unit].card != elii_card)
		return (ENXIO);
	if (unit < 0 || unit >= NNS8390 ||
		ns8390_softc[unit].nic == 0)
	    return (ENXIO);

	ns8390_softc[unit].ds_if.if_flags |= IFF_UP;
	ns8390init(unit);
	return(0);
}

ns8390output(dev, ior)
	dev_t		dev;
	io_req_t	ior;
{
	register int	unit = minor(dev);

	if (unit < 0 || unit >= NNS8390 ||
		ns8390_softc[unit].nic == 0)
	    return (ENXIO);
	return (net_write(&ns8390_softc[unit].ds_if, ns8390start, ior));
}

ns8390setinput(dev, receive_port, priority, filter, filter_count)
	dev_t		dev;
	mach_port_t	receive_port;
	int		priority;
	filter_t	filter[];
	unsigned int	filter_count;
{
	register int unit = minor(dev);

	if (unit < 0 || unit >= NNS8390 ||
		ns8390_softc[unit].nic == 0)
	    return (ENXIO);

	return (net_set_filter(&ns8390_softc[unit].ds_if,
			receive_port, priority,
			filter, filter_count));
}

#else	MACH_KERNEL
/*
 * ns8390output:
 *
 *	This routine is called by the "if" layer to output a packet to
 *	the network.  This code resolves the local ethernet address, and
 *	puts it into the mbuf if there is room.  If not, then a new mbuf
 *	is allocated with the header information and precedes the data
 *	to be transmitted.  The routine ns8390xmt() which actually
 *      transmits the data expects the ethernet header to precede the
 *      data in the mbuf.
 *
 * input:	ifnet structure pointer, an mbuf with data, and address
 *		to be resolved
 * output:	mbuf is updated to hold enet address, or a new mbuf
 *	  	with the address is added
 *
 */

ns8390output(ifp, m0, dst)
struct ifnet	*ifp;
struct mbuf	*m0;
struct sockaddr *dst;
{
	register ns8390_softc_t		*is = &ns8390_softc[ifp->if_unit];
	u_char				edst[6];
	struct in_addr 			idst;
	register struct mbuf		*m = m0;
	register struct ether_header	*eh;
	register int 			off;
	int				usetrailers;
	int 				type, opri, error;

	if ((ifp->if_flags & (IFF_UP|IFF_RUNNING)) != (IFF_UP|IFF_RUNNING)) {
		printf("%s%d output(): Turning off board %d\n",
			is->card, ifp->if_unit);
		ns8390intoff(ifp->if_unit);
		error = ENETDOWN;
		goto bad;
	}
	switch (dst->sa_family) {
#ifdef INET
	case AF_INET:
		idst = ((struct sockaddr_in *)dst)->sin_addr;
		if (!arpresolve(&is->ns8390_ac, m, &idst, edst, &usetrailers)){
			return (0);	/* if not yet resolved */
		}
		off = ntohs((u_short)mtod(m, struct ip *)->ip_len) - m->m_len;
		if (usetrailers && off > 0 && (off & 0x1ff) == 0 &&
		    m->m_off >= MMINOFF + 2 * sizeof (u_short)) {
			type = ETHERTYPE_TRAIL + (off>>9);
			m->m_off -= 2 * sizeof (u_short);
			m->m_len += 2 * sizeof (u_short);
			*mtod(m, u_short *) = htons((u_short)ETHERTYPE_IP);
			*(mtod(m, u_short *) + 1) = htons((u_short)m->m_len);
			goto gottrailertype;
		}
		type = ETHERTYPE_IP;
		off = 0;
		goto gottype;
#endif
#ifdef NS
	case AF_NS:
		type = ETHERTYPE_NS;
		bcopy((caddr_t)&(((struct sockaddr_ns *)dst)->sns_addr.x_host),
		      (caddr_t)edst,
		      sizeof (edst));
		off = 0;
		goto gottype;
#endif
	case AF_UNSPEC:
		eh = (struct ether_header *)dst->sa_data;
		bcopy((caddr_t)eh->ether_dhost, (caddr_t)edst, sizeof (edst));
		type = eh->ether_type;
		goto gottype;
	default:
		printf("%s%d output(): can't handle af%d\n",
			is->card, ifp->if_unit,
			dst->sa_family);
		error = EAFNOSUPPORT;
		goto bad;
	}
gottrailertype:
	/*
	 * Packet to be sent as trailer: move first packet
	 * (control information) to end of chain.
	 */
	while (m->m_next)
		m = m->m_next;
	m->m_next = m0;
	m = m0->m_next;
	m0->m_next = 0;
	m0 = m;
gottype:
	/*
	 * Add local net header.  If no space in first mbuf,
	 * allocate another.
	 */
	if (m->m_off > MMAXOFF ||
	    MMINOFF + sizeof (struct ether_header) > m->m_off) {
		m = m_get(M_DONTWAIT, MT_HEADER);
		if (m == 0) {
			error = ENOBUFS;
			goto bad;
		}
		m->m_next = m0;
		m->m_off = MMINOFF;
		m->m_len = sizeof (struct ether_header);
	} else {
		m->m_off -= sizeof (struct ether_header);
		m->m_len += sizeof (struct ether_header);
	}
	eh = mtod(m, struct ether_header *);
	eh->ether_type = htons((u_short)type);
	bcopy((caddr_t)edst, (caddr_t)eh->ether_dhost, sizeof (edst));
	bcopy((caddr_t)is->address,
	      (caddr_t)eh->ether_shost,
	      sizeof(edst));
	/*
	 * Queue message on interface, and start output if interface
	 * not yet active.
	 */
	opri = SPLNET();
	if (IF_QFULL(&ifp->if_snd)) {
		IF_DROP(&ifp->if_snd);
		splx(opri);
		m_freem(m);
		return (ENOBUFS);
	}
	IF_ENQUEUE(&ifp->if_snd, m);
	/*
 	 * Some action needs to be added here for checking whether the
	 * board is already transmitting.  If it is, we don't want to
 	 * start it up (ie call ns8390start()).  We will attempt to send
 	 * packets that are queued up after an interrupt occurs.  Some
 	 * flag checking action has to happen here and/or in the start
 	 * routine.  This note is here to remind me that some thought
 	 * is needed and there is a potential problem here.
	 *
	 */
	ns8390start(ifp->if_unit);
	splx(opri);
	return (0);
bad:
	m_freem(m0);
	return (error);
}
#endif MACH_KERNEL

/*
 * ns8390reset:
 *
 *	This routine is in part an entry point for the "if" code.  Since most
 *	of the actual initialization has already (we hope already) been done
 *	by calling ns8390attach().
 *
 * input	: unit number or board number to reset
 * output	: board is reset
 *
 */

int
ns8390reset(unit)
int	unit;
{

	ns8390_softc[unit].ds_if.if_flags &= ~IFF_RUNNING;
	return(ns8390init(unit));
}

/*
 * ns8390init:
 *
 *	Another routine that interfaces the "if" layer to this driver.
 *	Simply resets the structures that are used by "upper layers".
 *	As well as calling ns8390hwrst that does reset the ns8390 board.
 *
 * input	: board number
 * output	: structures (if structs) and board are reset
 *
 */

int
ns8390init(unit)
int	unit;
{
	struct	ifnet	*ifp;
	int		stat;
	unsigned long	oldpri;

	ifp = &(ns8390_softc[unit].ds_if);
#ifdef	MACH_KERNEL
#else	MACH_KERNEL
	if (ifp->if_addrlist == (struct ifaddr *)0) {
		return;
	}
#endif	MACH_KERNEL
	oldpri = SPLNET();
	if ((stat = ns8390hwrst(unit)) == TRUE) {
		ns8390_softc[unit].ds_if.if_flags |= IFF_RUNNING;
		ns8390_softc[unit].flags |= DSF_RUNNING;
		ns8390_softc[unit].tbusy = 0;
		ns8390start(unit);
	} else
		printf("%s%d init(): trouble resetting board %d\n",
			ns8390_softc[unit].card, unit);
	ns8390_softc[unit].timer = 5;
	splx(oldpri);
	return(stat);
}

/*
 * ns8390start:
 *
 *	This is yet another interface routine that simply tries to output a
 *	in an mbuf after a reset.
 *
 * input	: board number
 * output	: stuff sent to board if any there
 *
 */

ns8390start(unit)
int	unit;
{
	register ns8390_softc_t *is = &ns8390_softc[unit];
	struct	ifnet		*ifp;
#ifdef	MACH_KERNEL
	io_req_t	m;
#else	MACH_KERNEL
	struct	mbuf	*m;
#endif	MACH_KERNEL

	if (is->tbusy) {
		caddr_t nic = ns8390_softc[unit].nic;
		if (!(inb(nic+CR) & TXP)) {
			is->tbusy = 0;
			ns8390_cntrs[unit].busy++;
		} else
			return;
	}

	ifp = &(ns8390_softc[unit].ds_if);

	IF_DEQUEUE(&ifp->if_snd, m);
#ifdef	MACH_KERNEL
	if (m != 0)
#else	MACH_KERNEL
	if (m != (struct mbuf *)0)
#endif	MACH_KERNEL
	{
		is->tbusy++;
		ns8390_cntrs[unit].xmt++;
		ns8390xmt(unit, m);
	}
}

#ifdef	MACH_KERNEL
/*ARGSUSED*/
ns8390getstat(dev, flavor, status, count)
	dev_t		dev;
	int		flavor;
	dev_status_t	status;		/* pointer to OUT array */
	unsigned int	*count;		/* out */
{
	register int	unit = minor(dev);

	if (unit < 0 || unit >= NNS8390 ||
		ns8390_softc[unit].nic == 0)
	    return (ENXIO);

	return (net_getstat(&ns8390_softc[unit].ds_if,
			    flavor,
			    status,
			    count));
}
ns8390setstat(dev, flavor, status, count)
	dev_t		dev;
	int		flavor;
	dev_status_t	status;
	unsigned int	count;
{
	register int	unit = minor(dev);
	register ns8390_softc_t *sp;

	if (unit < 0 || unit >= NNS8390 ||
		ns8390_softc[unit].nic == 0)
	    return (ENXIO);

	sp = &ns8390_softc[unit];

	switch (flavor) {
	    case NET_STATUS:
	    {
		/*
		 * All we can change are flags, and not many of those.
		 */
		register struct net_status *ns = (struct net_status *)status;
		int	mode = 0;

		if (count < NET_STATUS_COUNT)
		    return (D_INVALID_SIZE);

		if (ns->flags & IFF_ALLMULTI)
		    mode |= MOD_ENAL;
		if (ns->flags & IFF_PROMISC)
		    mode |= MOD_PROM;

		/*
		 * Force a complete reset if the receive mode changes
		 * so that these take effect immediately.
		 */
		if (sp->mode != mode) {
		    sp->mode = mode;
		    if (sp->flags & DSF_RUNNING) {
			sp->flags &= ~(DSF_LOCK | DSF_RUNNING);
			ns8390init(unit);
		    }
		}
		break;
	    }

	    default:
		return (D_INVALID_OPERATION);
	}
	return (D_SUCCESS);
}
#else	MACH_KERNEL
/*
 * ns8390ioctl:
 *
 *	This routine processes an ioctl request from the "if" layer
 *	above.
 *
 * input	: pointer the appropriate "if" struct, command, and data
 * output	: based on command appropriate action is taken on the
 *	 	  ns8390 board(s) or related structures
 * return	: error is returned containing exit conditions
 *
 */

int
ns8390ioctl(ifp, cmd, data)
struct ifnet	*ifp;
int	cmd;
caddr_t	data;
{
	register struct ifaddr	*ifa = (struct ifaddr *)data;
	register ns8390_softc_t *is;
	int			opri, error;
	short			 mode = 0;

	is = &ns8390_softc[ifp->if_unit];
	opri = SPLNET();
	error = 0;
	switch (cmd) {
	case SIOCSIFADDR:
		ifp->if_flags |= IFF_UP;
		ns8390init(ifp->if_unit);
		switch (ifa->ifa_addr.sa_family) {
#ifdef INET
		case AF_INET:
			((struct arpcom *)ifp)->ac_ipaddr =
			    IA_SIN(ifa)->sin_addr;
			arpwhohas((struct arpcom *)ifp, &IA_SIN(ifa)->sin_addr);
			break;
#endif
#ifdef NS
		case AF_NS:
			{
				register struct ns_addr *ina =
				    &(IA_SNS(ifa)->sns_addr);
				if (ns_nullhost(*ina))
					ina->x_host =
					    *(union ns_host *)(ds->ds_addr);
				else
????
					ns8390seteh(ina->x_host.c_host,
						    ns8390_softc[ifp->if_unit].base);
				break;
			}
#endif
		}
		break;
	case SIOCSIFFLAGS:
#if	CMUCS
		if (ifp->if_flags & IFF_ALLMULTI)
			mode |= MOD_ENAL;
		if (ifp->if_flags & IFF_PROMISC)
			mode |= MOD_PROM;
		/*
		 * force a complete reset if the receive multicast/
		 * promiscuous mode changes so that these take
		 * effect immediately.
		 *
		 */
		if (is->mode != mode) {
			is->mode = mode;
			if (is->flags & DSF_RUNNING) {
				is->flags &=
				    ~(DSF_LOCK|DSF_RUNNING);
				ns8390init(ifp->if_unit);
			}
		}
#endif	CMUCS
		if ((ifp->if_flags & IFF_UP) == 0 &&
		    is->flags & DSF_RUNNING) {
			printf("%s%d ioctl(): turning off board %d\n",
				is->card, ifp->if_unit);
			is->flags &= ~(DSF_LOCK | DSF_RUNNING);
			is->timer = -1;
			ns8390intoff(ifp->if_unit);
			ns8390over_write(ifp->if_unit);
		} else
		    if (ifp->if_flags & IFF_UP &&
		    (is->flags & DSF_RUNNING) == 0)
			ns8390init(ifp->if_unit);
		break;
#ifdef	IF_CNTRS
	case SIOCCIFCNTRS:
		if (!suser()) {
			error = EPERM;
			break;
		}
		bzero((caddr_t)ns_ein, sizeof (ns_ein));
		bzero((caddr_t)ns_eout, sizeof (ns_eout));
		bzero((caddr_t)ns_lin, sizeof (ns_lin));
		bzero((caddr_t)ns_lout, sizeof (ns_lout));
		bzero((caddr_t)&ns_arp, sizeof (int));
		bzero((caddr_t)&ns8390_cntrs, sizeof (ns8390_cntrs));
		break;
#endif	IF_CNTRS
	default:
		error = EINVAL;
	}
	splx(opri);
	return (error);
}
#endif	MACH_KERNEL

/*
 * ns8390hwrst:
 *
 *	This routine resets the ns8390 board that corresponds to the
 *	board number passed in.
 *
 * input	: board number to do a hardware reset
 * output	: board is reset
 *
 */

int
ns8390hwrst(unit)
int unit;
{
	caddr_t nic = ns8390_softc[unit].nic;
	int	count;
	u_char	stat;
	int spl = SPLNET();

	if (ns8390_softc[unit].card == wd8003_card && 
	    config_wd8003(unit) == FALSE) {
		printf("%s%d hwrst(): config_wd8003 failed.\n",
			ns8390_softc[unit].card, unit);
		splx(spl);
		return(FALSE);
	}
	if (ns8390_softc[unit].card == elii_card && 
	    config_3c503(unit) == FALSE) {
		printf("%s%d hwrst(): config_3c503 failed.\n",
			ns8390_softc[unit].card, unit);
		splx(spl);
		return(FALSE);
	}
	if (config_nic(unit) == FALSE) {
		printf("%s%d hwrst(): config_nic failed.\n",
			ns8390_softc[unit].card, unit);
		splx(spl);
		return(FALSE);
	}
	splx(spl);
	return(TRUE);
}

/*
 * ns8390intr:
 *
 *	This function is the interrupt handler for the ns8390 ethernet
 *	board.  This routine will be called whenever either a packet
 *	is received, or a packet has successfully been transfered and
 *	the unit is ready to transmit another packet.
 *
 * input	: board number that interrupted
 * output	: either a packet is received, or a packet is transfered
 *
 */
int
ns8390intr(unit)
{
	int	opri, i;
	int     isr_status;
	int     temp_cr;
	caddr_t nic = ns8390_softc[unit].nic;

	temp_cr = inb(nic+CR);
	outb(nic+CR, (temp_cr & 0x3f) | PS0);
	outb(nic+IMR, 0);                   /* stop board interrupts */
	outb(nic+CR, temp_cr);
	while (isr_status = inb(nic+ISR)) {
		outb(nic+ISR, isr_status);          /* clear interrupt status */

		if ((isr_status & (OVW|RXE)) == RXE) {
			int rsr = inb(nic+RSR);
			if (rsr & DFR) ns8390_cntrs[unit].jabber++;
			if (rsr & ~(DFR|PHY|FAE|CRC|PRX))
				printf("%s%d intr(): isr = %x, RSR = %x\n",
					ns8390_softc[unit].card, unit,
					isr_status, rsr);
		} else if (isr_status & OVW) {
			ns8390_cntrs[unit].ovw++;
			ns8390over_write(unit);
		}
		if (isr_status & PRX) {			/* DFR & PRX is possible */
		 	ns8390rcv(unit);
		}

	        if (isr_status & TXE) {
			int tsr = inb(nic+TSR);
			tsr &= ~0x2;		/* unadvertised special */
			if (tsr == (CDH|ABT))
				ns8390_cntrs[unit].heart++;
			else
				printf("%s%d intr(): isr = %x, TSR = %x\n",
					ns8390_softc[unit].card, unit,
					isr_status, tsr);
			ns8390_softc[unit].tbusy = 0;
	 		ns8390start(unit);
	        } else if (isr_status & PTX) {
			ns8390_cntrs[unit].xmti++;
			ns8390_softc[unit].tbusy = 0;
	 		ns8390start(unit);
		}

		if (isr_status & CNT) {
			int c0 = inb(nic+CNTR0);
			int c1 = inb(nic+CNTR1);
			int c2 = inb(nic+CNTR2);
			ns8390_cntrs[unit].frame += c0;
			ns8390_cntrs[unit].crc += c1;
			ns8390_cntrs[unit].miss += c2;
#ifdef	COUNTERS
			printf("%s%d intr(): isr = %x, FRAME %x, CRC %x, MISS %x\n",
				ns8390_softc[unit].card, unit,
				isr_status, c0, c1, c2);
			printf("%s%d intr(): TOTAL   , FRAME %x, CRC %x, MISS %x\n",
				ns8390_softc[unit].card, unit,
				ns8390_cntrs[unit].frame,
				ns8390_cntrs[unit].crc,
				ns8390_cntrs[unit].miss);
#endif	COUNTERS
			outb(nic+ISR, isr_status);	/* clear interrupt status again */
		}
	}
	temp_cr=inb(nic+CR);
	outb(nic+CR, (temp_cr & 0x3f) | PS0);
	outb(nic+IMR, imr_hold);
	outb(nic+CR, temp_cr);
	return(0);
}

/*
 *  Called if on board buffer has been completely filled by ns8390intr.  It stops
 *  the board, reads in all the buffers that are currently in the buffer, and
 *  then restart board.
 */
ns8390over_write(unit)
int unit;
{
	caddr_t	nic = ns8390_softc[unit].nic;
	int	no;
	int	count = 0;

	outb(nic+CR, ABR|STP|PS0);        /* clear the receive buffer */
	outb(nic+RBCR0, 0);
	outb(nic+RBCR1, 0);
	while ((!(inb (nic + ISR) & RST)) && (count < 10000))
		count++;
	if (count == 10000) {
		printf("%s%d: over_write(): would not reset.\n",
			ns8390_softc[unit].card, unit);
	}
	no = ns8390rcv(unit);
#ifdef	OVWBUG
	printf("%s%d over_write(): ns8390 OVW ... %d.\n",
		ns8390_softc[unit].card, unit, no);
#endif	OVWBUG
	outb(nic+TCR, LB1);               /* External loopback mode */
	outb(nic+CR, ABR|STA|PS0);
	outb(nic+TCR, 0);
	return;
}

/*
 * ns8390rcv:
 *
 *	This routine is called by the interrupt handler to initiate a
 *	packet transfer from the board to the "if" layer above this
 *	driver.  This routine checks if a buffer has been successfully
 *	received by the ns8390.  If so, it does the actual transfer of the
 *      board data (including the ethernet header) into a packet (consisting
 *      of an mbuf chain) and enqueues it to a higher level.
 *      Then check again whether there are any packets in the receive ring,
 *      if so, read the next packet, until there are no more.
 *
 * input	: number of the board to check
 * output	: if a packet is available, it is "sent up"
 */
ns8390rcv(unit)
int unit;
{
	register ns8390_softc_t	*is = &ns8390_softc[unit];
	register struct ifnet	*ifp = &is->ds_if;
	caddr_t			nic = is->nic;
	int			packets = 0;
	struct ether_header	eh;
	u_short			mlen, len, bytes_in_mbuf, bytes;
	u_short			remaining;
	int			temp_cr;
	u_char			*mb_p;


	/* calculation of pkt size */
	int nic_overcount;         /* NIC says 1 or 2 more than we need */
	int pkt_size;              /* calculated size of received data */
	int wrap_size;             /* size of data before wrapping it */
	int header_nxtpkt_ptr;     /* NIC's next pkt ptr in rcv header */
	int low_byte_count;        /* low byte count of read from rcv header */
	int high_byte_count;       /* calculated high byte count */


	volatile char *sram_nxtpkt_ptr;   /* mem location of next packet */
	volatile char *sram_getdata_ptr;  /* next location to be read */
#ifdef	MACH_KERNEL
	ipc_kmsg_t	new_kmsg;
	struct ether_header *ehp;
	struct packet_header *pkt;
#else	MACH_KERNEL
	struct mbuf *m, *tm;              /* initial allocation of mem; temp */
#endif	MACH_KERNEL


	if ((ifp->if_flags & (IFF_UP|IFF_RUNNING)) != (IFF_UP|IFF_RUNNING)) {
		temp_cr = inb(nic+CR); /* get current CR value */
		outb(nic+CR,((temp_cr & 0x3F)|PS0|STP));
		outb(nic+IMR, 0);      /* Interrupt Mask Register  */
		outb(nic+CR, temp_cr);
		return -1;
	}

	while(is->read_nxtpkt_ptr != ns8390get_CURR(unit))   {

		/* while there is a packet to read from the buffer */

		if ((is->read_nxtpkt_ptr < is->pstart) ||
		    (is->read_nxtpkt_ptr >= is->pstop)) {
			ns8390hwrst(unit);
			return -1;
		}    /* if next packet pointer is out of receive ring bounds */

		packets++;
		ns8390_cntrs[unit].rcv++;
		sram_nxtpkt_ptr = (char *) (is->sram + (is->read_nxtpkt_ptr << 8));

		/* get packet size and location of next packet */
		header_nxtpkt_ptr = *(sram_nxtpkt_ptr + 1);
		header_nxtpkt_ptr &= 0xFF;
		low_byte_count = *(sram_nxtpkt_ptr + 2);
		low_byte_count &= 0xFF;

		if ((low_byte_count + NIC_HEADER_SIZE) > NIC_PAGE_SIZE)
			nic_overcount = 2;
		else
			nic_overcount = 1;
		if (header_nxtpkt_ptr > is->read_nxtpkt_ptr) {
			wrap_size = 0;
			high_byte_count = header_nxtpkt_ptr - is->read_nxtpkt_ptr -
			    nic_overcount;
		} else {
			wrap_size = (int) (is->pstop - is->read_nxtpkt_ptr - nic_overcount);
			high_byte_count = is->pstop - is->read_nxtpkt_ptr +
			    header_nxtpkt_ptr - is->pstart - nic_overcount;
		}
		pkt_size = (high_byte_count << 8) | (low_byte_count & 0xFF);
		/* does not seem to include NIC_HEADER_SIZE */
		len = pkt_size;

		sram_getdata_ptr = sram_nxtpkt_ptr + NIC_HEADER_SIZE;
		bcopy16 (sram_getdata_ptr,
			     &eh,
			     sizeof(struct ether_header));
		sram_getdata_ptr += sizeof(struct ether_header);
		len -= (sizeof(struct ether_header) + 4);	/* crc size */
#ifdef	MACH_KERNEL
		new_kmsg = net_kmsg_get();
		if (new_kmsg == IKM_NULL) {
			/*
		   	 * Drop the packet.
			*/
			is->ds_if.if_rcvdrops++;    
		  /*
		   * not only do we want to return, we need to drop the packet on
		   * the floor to clear the interrupt.
		   */
		  ns8390lost_frame(unit);
		  return;/* packets;*/
		}
		ehp = (struct ether_header *) (&net_kmsg(new_kmsg)->header[0]);
		pkt = (struct packet_header *) (&net_kmsg(new_kmsg)->packet[0]);
		*ehp = eh;
		if (len >
		    (wrap_size = (is->sram + (is->pstop << 8) - sram_getdata_ptr))) {
		    /* if needs to wrap */
		    bcopy (sram_getdata_ptr, (char *) (pkt + 1), wrap_size);
		    sram_getdata_ptr = (volatile char *) (is->sram +
							  (is->pstart << 8));
		} else {   /* normal getting data from buffer */
		    wrap_size = 0;
		}
		bcopy (sram_getdata_ptr, (char *) (pkt + 1) + wrap_size,
					 len - wrap_size);
#else	MACH_KERNEL
#define NEW
#ifdef	NEW
		m = (struct mbuf *) 0;
		eh.ether_type = ntohs(eh.ether_type);
		MGET(m, M_DONTWAIT, MT_DATA);
		if (m == (struct mbuf *) 0) {
			printf("%s%d rcv(): Lost frame\n",
				ns8390_softc[unit].card, unit);
			ns8390lost_frame(unit); /* update NIC pointers and registers */
			return packets;
		}
m->m_next = (struct mbuf *) 0;
		tm = m;
		m->m_len = MLEN;
		if (len > 2 * MLEN - sizeof (struct ifnet **)) {
			MCLGET(m);
		}
		*(mtod(tm, struct ifnet **)) = ifp;
		mlen = sizeof (struct ifnet **);
		bytes_in_mbuf = m->m_len - sizeof(struct ifnet **);
		mb_p = mtod(tm, u_char *) + sizeof (struct ifnet **);
		bytes = min(bytes_in_mbuf, len);
		remaining =  (int) (is->sram + (is->pstop << 8) -
				    sram_getdata_ptr);
		bytes = min(bytes, remaining);
		do {
			bcopy16 (sram_getdata_ptr, mb_p, bytes);
			mlen += bytes;

			if (!(bytes_in_mbuf -= bytes)) {
				MGET(tm->m_next, M_DONTWAIT, MT_DATA);
				tm = tm->m_next;
				if (tm == (struct mbuf *)0) {
					printf("%s%d rcv(): No mbufs, lost frame\n",
						ns8390_softc[unit].card, unit);
					m_freem(m);              /* free the mbuf chain */
					ns8390lost_frame(unit);  /* update NIC pointers and registers */
					return;
				}
				mlen = 0;
				tm->m_len = MLEN;
				bytes_in_mbuf = MLEN;
				mb_p = mtod(tm, u_char *);
			} else
				mb_p += bytes;

			if (!(len  -= bytes)) {
				tm->m_len = mlen;
				break;
			} else if (bytes == remaining) {
				sram_getdata_ptr = (volatile char *) (is->sram +
				    (is->pstart << 8));
				bytes = len;
				remaining = ETHERMTU;
			} else {
				sram_getdata_ptr += bytes;
				remaining -= bytes;
			}

			bytes = min(bytes_in_mbuf, len);
			bytes = min(bytes, remaining);
		} while(1);
#else	NEW
		m = (struct mbuf *) 0;
		eh.ether_type = ntohs(eh.ether_type);

		while ( len ) {
			if (m == (struct mbuf *) 0) {
				m = m_get(M_DONTWAIT, MT_DATA);
				if (m == (struct mbuf *) 0) {
					printf("%s%d rcv(): Lost frame\n",
					ns8390_softc[unit].card, unit);
					ns8390lost_frame(unit); /* update NIC pointers and registers */
					return packets;
				}
				tm = m;
				tm->m_off = MMINOFF;


				/*
				 * first mbuf in the packet must contain a pointer to the
				 * ifnet structure.  other mbufs that follow and make up
				 * the packet do not need this pointer in the mbuf.
				 *
				 */

				*(mtod(tm, struct ifnet **)) = ifp;
				tm->m_len = sizeof(struct ifnet **);

		        /* end of first buffer of packet */
			} else {
				tm->m_next = m_get(M_DONTWAIT, MT_DATA);
				tm = tm->m_next;
				if (tm == (struct mbuf *) 0) {
					printf("%s%d rcv(): No mbufs, lost frame\n",
						ns8390_softc[unit].card, unit);
					m_freem(m);              /* free the mbuf chain */
					ns8390lost_frame(unit);  /* update NIC pointers and registers */
					return packets;
				}
				tm->m_off = MMINOFF;
				tm->m_len = 0;
			}

			tlen = MIN( MLEN - tm->m_len, len);
			/* size of mbuf so you know how much you can copy from board */
			tm->m_next = (struct mbuf *) 0;
			if (sram_getdata_ptr + tlen >=
			    (volatile char *) (is->sram + (is->pstop << 8))) {
				/* if needs to wrap */
				wrap_size = (int) (is->sram + (is->pstop << 8) -
				    sram_getdata_ptr);
				bcopy16 (sram_getdata_ptr,
					     mtod(tm, char*) + tm->m_len,
					     wrap_size);
				tm->m_len += wrap_size;
				len -= wrap_size;

				sram_getdata_ptr = (volatile char *) (is->sram +
				    (is->pstart << 8));
			} else {   /* normal getting data from buffer */
			        bcopy16 (sram_getdata_ptr,
					     mtod(tm, char*) + tm->m_len,
					     tlen);
				sram_getdata_ptr += tlen;
				tm->m_len += tlen;
				len -= tlen;

			}
		}

#endif	NEW
#ifdef	IF_CNTRS
		ns_ein[log_2(pkt_size)]++;
		if (pkt_size < 128) ns_lin[(pkt_size)>>3]++;

		if (eh.ether_type == ETHERTYPE_ARP) {
			ns_arp++;
			if (ns_narp) {
				ns_ein[log_2(pkt_size)]--;
				if (pkt_size < 128) ns_lin[(pkt_size)>>3]--;
			}
		}
#endif	IF_CNTRS
#endif	MACH_KERNEL
		is->read_nxtpkt_ptr = *(sram_nxtpkt_ptr + 1);
		is->read_nxtpkt_ptr &= 0xFF;

		temp_cr = inb(nic+CR);
		outb(nic+CR, (temp_cr & 0x3f) | PS0);

		if (is->read_nxtpkt_ptr == ns8390get_CURR(unit))
			if (is->read_nxtpkt_ptr == is->pstart)
				outb(nic+BNDY, is->pstop - 1);
			else
				outb(nic+BNDY, is->read_nxtpkt_ptr - 1);
		else
			outb(nic+BNDY, is->read_nxtpkt_ptr);

		outb(nic+CR, temp_cr);

#ifdef	MACH_KERNEL
		pkt->type = ehp->ether_type;
		pkt->length = len + sizeof(struct packet_header);
		/*
		 * Send the packet through the input filters.
		 */
	  net_filter(ifp, new_kmsg, pkt->length);
#else	MACH_KERNEL
		if (!ns8390send_packet_up(m, &eh, is))
			m_freem(m);
#endif	MACH_KERNEL
	}
	return packets;

}

#ifdef	MACH_KERNEL
#else	MACH_KERNEL
/*
 * Send a packet composed of an mbuf chain to the higher levels
 *
 */
ns8390send_packet_up(m, eh, is)
struct mbuf *m;
struct ether_header *eh;
ns8390_softc_t *is;
{
	register struct ifqueue	*inq;
        int			opri;

	switch (eh->ether_type) {
#ifdef INET
	case ETHERTYPE_IP:
		schednetisr(NETISR_IP);
		inq = &ipintrq;
		break;
	case ETHERTYPE_ARP:
		arpinput(&is->ns8390_ac, m);
		return(TRUE);
#endif
#ifdef NS
	case ETHERTYPE_NS:
		schednetisr(NETISR_NS);
		inq = &nsintrq;
		break;
#endif
	default:
		return(FALSE);
	}
	opri = SPLNET();
	if (IF_QFULL(inq)) {
		IF_DROP(inq);
		splx(opri);
		return(FALSE);
	}
	IF_ENQUEUE(inq, m);
	splx(opri);
	return(TRUE);
}
#endif	MACH_KERNEL

/*
 *  ns8390lost_frame:
 *  this routine called by ns8390read after memory for mbufs could not be
 *  allocated.  It sets the boundary pointers and registers to the next
 *  packet location.
 */

ns8390lost_frame(unit)
int unit;
{
	ns8390_softc_t *is = &ns8390_softc[unit];
	caddr_t        nic = is->nic;
	volatile char  *sram_nxtpkt_ptr;
	int            temp_cr;



	sram_nxtpkt_ptr = (volatile char *) (is->sram +
	    (is->read_nxtpkt_ptr << 8));

	is->read_nxtpkt_ptr = *(sram_nxtpkt_ptr + 1);
	is->read_nxtpkt_ptr &= 0xFF;

	temp_cr = inb(nic+CR);
	outb(nic+CR, (temp_cr & 0x3f) | PS0);

	/* update boundary register */
	if (is->read_nxtpkt_ptr == ns8390get_CURR(unit))
		if (is->read_nxtpkt_ptr == is->pstart)
			outb(nic+BNDY, is->pstop - 1);
		else
			outb(nic+BNDY, is->read_nxtpkt_ptr - 1);
	else
		outb(nic+BNDY, is->read_nxtpkt_ptr);

	outb(nic+CR, temp_cr);

	return;
}

/*
 * ns8390get_CURR():
 *
 * Returns the value of the register CURR, which points to the next
 * available space for NIC to receive from network unto receive ring.
 *
 */

int
ns8390get_CURR(unit)
int unit;
{
	caddr_t nic = ns8390_softc[unit].nic;
	int	temp_cr;
	int	ret_val;

	temp_cr = inb(nic+CR);                  /* get current CR value */
	outb(nic+CR, ((temp_cr & 0x3F) | PS1)); /* select page 1 registers */
	ret_val = inb(nic+CURR);                /* read CURR value */
	outb(nic+CR, temp_cr);
	return (ret_val & 0xFF);
}

/*
 * ns8390xmt:
 *
 *	This routine fills in the appropriate registers and memory
 *	locations on the ns8390 board and starts the board off on
 *	the transmit.
 *
 * input	: board number of interest, and a pointer to the mbuf
 * output	: board memory and registers are set for xfer and attention
 *
 */

ns8390xmt(unit, m)
int	unit;
#ifdef	MACH_KERNEL
io_req_t	m;
#else	MACH_KERNEL
struct	mbuf	*m;
#endif	MACH_KERNEL
{
	ns8390_softc_t		*is = &ns8390_softc[unit];
	caddr_t			nic = is->nic;
	struct ether_header	*eh;
	int			i;
	int			opri;
	u_short			count = 0;	/* amount of data already copied */
	volatile char		*sram_write_pkt;
#ifdef	MACH_KERNEL
#else	MACH_KERNEL
	register struct	mbuf	*tm_p;
#endif	MACH_KERNEL
	/* begining of physical address of transmition buffer */

	sram_write_pkt = is->sram + is->tpsr * 0x100; 

#ifdef	MACH_KERNEL
	count = m->io_count;
	bcopy (m->io_data, sram_write_pkt,  count);
#else	MACH_KERNEL
	for(tm_p = m; tm_p != (struct mbuf *)0; tm_p = tm_p->m_next)  {
		if (count + tm_p->m_len > ETHERMTU + sizeof (struct ether_header))
			break;
		if (tm_p->m_len == 0)
			continue;
		bcopy16 (mtod(tm_p, caddr_t),
			     sram_write_pkt + count,
			     tm_p->m_len);
		count += tm_p->m_len;
	}
#ifdef	IF_CNTRS
	ns_eout[log_2(count+4/*crc*/)]++;
	if (count < 128)  ns_lout[(count+4/*crc*/)>>3]++;
#endif	IF_CNTRS
#endif	MACH_KERNEL
	while (count < ETHERMIN+sizeof(struct ether_header)) {
		*(sram_write_pkt + count) = 0;
		count++;
	}
	outb(nic+CR, ABR|STA|PS0);		/* select page 0 */
	outb(nic+TPSR, is->tpsr);		/* xmt page start at 0 of RAM */
	outb(nic+TBCR1, count >> 8);		/* upper byte of count */
	outb(nic+TBCR0, count & 0xFF);		/* lower byte of count */
	outb(nic+CR, TXP|ABR|STA);		/* start transmission */

#ifdef	MACH_KERNEL
	iodone(m);
	m=0;
#else	MACH_KERNEL
	/* If this is a broadcast packet, loop it back to rcv.  */
	eh = mtod( m, struct ether_header *);
	for (i=0; ((i < 6) && (eh->ether_dhost[i] == 0xff)); i++)  ;
	if (i == 6) {
		if (!ns8390send_packet_up(m, eh, is))
			m_freem(m);
	} else
		m_freem(m);
#endif	MACH_KERNEL
	return;
}

config_nic(unit)
int unit;
{
	ns8390_softc_t *is = &ns8390_softc[unit];
	caddr_t   nic = is->nic;
	int       i;
	int       temp;
	int       count = 0;

	outb (nic+CR, PS0|ABR|STP);             /* soft reset and page 0 */
	while ((!(inb (nic + ISR) & RST)) && (count < 10000))
		count++;
	if (count == 10000) {
		printf("%s%d: config_nic(): would not reset.\n",
			ns8390_softc[unit].card, unit);
	}

	temp = ((is->fifo_depth & 0x0c) << 3) | BMS;    /* fifo depth | not loopback */
	if (is->board_id & SLOT_16BIT)
		temp |= WTS;			/* word xfer select (16 bit cards ) */
	outb (nic+DCR, temp);
	outb (nic+TCR, 0);
	outb (nic+RCR, MON);			/* receive configuration register */
	outb (nic+PSTART, is->pstart);		/* recieve ring starts 2k into RAM */
	outb (nic+PSTOP, is->pstop);		/* stop at last RAM buffer rcv location */
	outb (nic+BNDY, is->pstart);		/* boundary pointer for page 0 */

	outb (nic+CR, PS1|ABR|STP);		/* maintain rst | sel page 1 */
	is->read_nxtpkt_ptr = is->pstart + 1;	/* internal next packet pointer */
	outb (nic+CURR, is->read_nxtpkt_ptr);	/* Current page register */
	for(i=0; i<ETHER_ADDR_SIZE; i++)
		outb (nic+PAR0+i, is->address[i]);
	for(i=0; i<8; i++)
		outb (nic+MAR0+i, 0);

	outb (nic+CR, PS0|STP|ABR);
	outb (nic+ISR, 0xff);			/* clear all interrupt status bits */
	outb (nic+IMR, imr_hold);		/* Enable interrupts */
	outb (nic+RBCR0, 0);			/* clear remote byte count */
	outb (nic+RBCR1, 0);

	outb (nic+CR, PS0|STA|ABR);		/* start NIC | select page 0 */	outb (nic+RCR, AB);			/* receive configuration register */

	return TRUE;
}

/*
 * config_ns8390:
 *
 *	This routine does a standard config of a wd8003 family board, with
 *      the proper modifications to different boards within this family.
 *
 */
config_wd8003(unit)
int	unit;
{
	ns8390_softc_t *is = &ns8390_softc[unit];
	caddr_t   hdwbase = ns8390info[unit]->dev_addr;
	int       i;
	int       RAMsize;
	volatile char  *RAMbase;
	int       addr_temp;

	is->tpsr = 0;			/* transmit page start hold */
	is->pstart = 0x06;		/* receive page start hold */
	is->read_nxtpkt_ptr = is->pstart + 1; /* internal next packet pointer */
	is->fifo_depth = 0x08;		/* NIC fifo threshold */
	switch (is->board_id & RAM_SIZE_MASK) {
	case RAM_SIZE_8K:  
		RAMsize =  0x2000;	break;
	case RAM_SIZE_16K: 
		RAMsize =  0x4000;	break;
	case RAM_SIZE_32K: 
		RAMsize =  0x8000;	break;
	case RAM_SIZE_64K: 
		RAMsize = 0x10000;	break;
	default:           
		RAMsize =  0x2000;	break;
	}
	is->pstop = (((int)RAMsize >> 8) & 0x0ff);      /* rcv page stop hold */
	if (((is->board_id & WD8013EBT) == WD8013EBT) &&
	    (is->board_id & SLOT_16BIT))
		outb(hdwbase+LAAR, LAN16ENB | LA19| MEM16ENB | SOFTINT);

	/* enable 16 bit access from lan controller */
	/***?? Should this be after MSR? */
	/*	if (is->board_id & STATIC_ID_MASK & ns8390EB) ****/
	/***?? CONFIGURE THE 8003EB to tell it base io, etc... */

	RAMbase = ns8390info[unit]->dev_start;
	addr_temp = ((int)(RAMbase) >> 13) & 0x3f; /* convert to be written to MSR */
	outb(hdwbase+MSR, addr_temp | MENB);        /* initialize MSR */

	return TRUE;
}

/*
 * config_ns8390:
 *
 *	This routine does a standard config of a 3 com etherlink II board.
 *
 */
config_3c503(unit)
int	unit;
{
	ns8390_softc_t	*is = &ns8390_softc[unit];
	struct isa_dev	*dev = ns8390info[unit];
	caddr_t		hdwbase = dev->dev_addr;
	int		RAMsize = dev->dev_len;
	int		i;

	is->tpsr =   0x20;		/* transmit page start hold */
	is->sram = (char *)phystokv(dev->dev_start) - is->tpsr * 0x100;
					/* When NIC says page 20, this means go to
					   the beginning of the sram range */
	is->pstart = 0x26;		/* receive page start hold */
	is->read_nxtpkt_ptr = is->pstart + 1; /* internal next packet pointer */
	is->fifo_depth = 0x08;		/* NIC fifo threshold */
	is->pstop = is->tpsr + ((RAMsize >> 8) & 0x0ff);      /* rcv page stop hold */

	outb(hdwbase+CTLR, CTLR_RST|CTLR_THIN);
	outb(hdwbase+CTLR, CTLR_THIN);
	outb(hdwbase+CTLR, CTLR_STA_ADDR|CTLR_THIN);
	for (i = 0; i < 6; i++)
		is->address[i] = inb(hdwbase+i);
	outb(hdwbase+CTLR, elii_bnc[is->board_id]?CTLR_THIN:CTLR_THICK);
	outb(hdwbase+PSTR, is->pstart);
	outb(hdwbase+PSPR, is->pstop);
	outb(hdwbase+IDCFR, IDCFR_IRQ2 << (elii_irq[is->board_id] - 2));
	outb(hdwbase+GACFR, GACFR_TCM|GACFR_8K);
	/* BCFR & PCRFR ro */
	/* STREG ro & dma */
	outb(hdwbase+DQTR, 0);
	outb(hdwbase+DAMSB, 0);
	outb(hdwbase+DALSB, 0);
	outb(hdwbase+VPTR2, 0);
	outb(hdwbase+VPTR1, 0);
	outb(hdwbase+VPTR0, 0);
	outb(hdwbase+RFMSB, 0);
	outb(hdwbase+RFLSB, 0);
	return TRUE;
}

/*
 * ns8390intoff:
 *
 *	This function turns interrupts off for the ns8390 board indicated.
 *
 */

ns8390intoff(unit)
int unit;
{
	caddr_t nic = ns8390_softc[unit].nic;
	int	temp_cr = inb(nic+CR);                  /* get current CR value */

	outb(nic+CR,((temp_cr & 0x3F)|PS0|STP));
	outb(nic+IMR, 0);                       /* Interrupt Mask Register  */
	outb(nic+CR, temp_cr|STP);

}

/*
 *   wd80xxget_board_id:
 *
 *   determine which board is being used.
 *   Currently supports:
 *    wd8003E
 *    wd8003EBT
 *    wd8013EBT
 *
 */
wd80xxget_board_id(dev)
struct isa_dev	*dev;
{
	caddr_t        hdwbase = dev->dev_addr;
	long           unit = dev->dev_unit;
	long           board_id = 0;
	int            reg_temp;
	int            rev_num;			/* revision number */
	int            ram_flag;
	int            intr_temp;

	board_id |= ETHERNET_MEDIA;		/* assume Ethernet media */

	outb(hdwbase+MSR, MENB);
	if (inb(hdwbase+0x0e) == 0x05 ) {	/* check if board is a WD8013EBT */

		/* board is 16 bits */
		board_id |= BOARD_16BIT;
		reg_temp &= 0xFE;
		outb(hdwbase + REG_1, reg_temp);
		if (inb(hdwbase + REG_1) & BID_SIXTEEN_BIT_BIT)		/* check if in 16 bit slot */

			board_id |= SLOT_16BIT;
	}

	rev_num = (inb(hdwbase + BOARD_ID_BYTE) & BID_REV_MASK) >> 1;
	if (rev_num < 2) {
		if (board_id & BOARD_16BIT)
			board_id |= RAM_SIZE_16K;
		else
			if (board_id & INTERFACE_CHIP)
				if (inb(hdwbase + REG_1) & BID_MSZ_583)
					board_id |= RAM_SIZE_32K;
				else
					board_id |= RAM_SIZE_8K;
	} else {
		ram_flag = inb(hdwbase + BOARD_ID_BYTE) & BID_RAM_SIZE_BIT;
		switch ((int) (board_id & STATIC_ID_MASK)) {
		case WD8003E:
		case WD8003EB:
			if (ram_flag)
				board_id |= RAM_SIZE_32K;
			else
				board_id |= RAM_SIZE_8K;
			break;
		case WD8013EBT:
			if (ram_flag)
				board_id |= RAM_SIZE_32K;
			else
				board_id |= RAM_SIZE_16K;
			break;
		default :
			board_id |= RAM_SIZE_8K;
		}
	}
	if ((board_id & WD8003EB) == WD8003EB) {
		/* program the WD83C583 EEPROM registers */
		if (ram_flag)
			outb(hdwbase+ICR, inb(hdwbase+ICR) | DMAE | IOPE | MSZ);
		else
			outb(hdwbase+ICR, inb(hdwbase+ICR) | DMAE | IOPE);
		switch(ns8390info[unit]->dev_pic) {
			/* attempt to set interrupt according to assigned pic */
		case 2: 
			outb(hdwbase+IRR, IEN);
			break;
		case 3: 
			outb(hdwbase+IRR, IEN|IR0);
			break;
		case 4: 
			outb(hdwbase+IRR, IEN|IR1);
			break;
		case 7: 
			outb(hdwbase+IRR, IEN|IR0|IR1);
			break;
		default: 
			printf("%s%d wd80xx_get_board_id(): Could not set WD8003EB Interrupt Request Register according to pic(%d).\n",
				ns8390_softc[unit].card, unit,
				ns8390info[unit]->dev_pic);
		}
	}
	return (board_id);
}

wdpr(unit)
{
	caddr_t nic = ns8390_softc[unit].nic;
	int	temp_cr = inb(nic);		/* get current CR value */

	printf("CR %x, BNDRY %x, TSR %x, NCR %x, FIFO %x, ISR %x, RSR %x\n",
		inb(nic+0x0), inb(nic+0x3), inb(nic+0x4), inb(nic+0x5),
		inb(nic+0x6), inb(nic+0x7), inb(nic+0xc));
	printf("CLD %x:%x, CRD %x:%x, FR %x, CRC %x, Miss %x\n",
		inb(nic+0x1), inb(nic+0x2),
		inb(nic+0x8), inb(nic+0x9),
		inb(nic+0xd), inb(nic+0xe), inb(nic+0xf));

	
	outb(nic, (temp_cr&0x3f)|PS1);		/* page 1 CR value */
	printf("PHYS %x:%x:%x:%x:%x CUR %x\n",
		inb(nic+0x1), inb(nic+0x2), inb(nic+0x3),
		inb(nic+0x4), inb(nic+0x5), inb(nic+0x6),
		inb(nic+0x7));
	printf("MAR %x:%x:%x:%x:%x:%x:%x:%x\n",
		inb(nic+0x8), inb(nic+0x9), inb(nic+0xa), inb(nic+0xb),
		inb(nic+0xc), inb(nic+0xd), inb(nic+0xe), inb(nic+0xf));
	outb(nic, temp_cr);			/* restore current CR value */
}
