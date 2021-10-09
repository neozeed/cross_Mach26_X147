#include "mach_interface.h"
#include <mach/message.h>
#include <mach/mach_types.h>
#include <mach/mig_errors.h>
#include <mach/msg_type.h>
#if	!defined(KERNEL) && !defined(MIG_NO_STRINGS)
#include <strings.h>
#endif
/* LINTLIBRARY */

extern port_t mig_get_reply_port();
extern void mig_dealloc_reply_port();

#ifndef	mig_internal
#define	mig_internal	static
#endif

#ifndef	TypeCheck
#define	TypeCheck 1
#endif

#ifndef	UseExternRCSId
#ifdef	__HC__
#define	UseExternRCSId		1
#endif
#endif

#ifndef	UseStaticMsgType
#if	!defined(__HC__) || defined(__STDC__)
#define	UseStaticMsgType	1
#endif
#endif

#define msg_request_port	msg_remote_port
#define msg_reply_port		msg_local_port


/* Routine port_set_status */
mig_external kern_return_t port_set_status
#if	(defined(__STDC__) || defined(c_plusplus))
(
	task_t task,
	port_set_name_t set_name,
	port_name_array_t *members,
	unsigned int *membersCnt
)
#else
	(task, set_name, members, membersCnt)
	task_t task;
	port_set_name_t set_name;
	port_name_array_t *members;
	unsigned int *membersCnt;
#endif
{
	typedef struct {
		msg_header_t Head;
		msg_type_t set_nameType;
		port_set_name_t set_name;
	} Request;

	typedef struct {
		msg_header_t Head;
		msg_type_t RetCodeType;
		kern_return_t RetCode;
		msg_type_long_t membersType;
		port_name_array_t members;
	} Reply;

	union {
		Request In;
		Reply Out;
	} Mess;

	register Request *InP = &Mess.In;
	register Reply *OutP = &Mess.Out;

	msg_return_t msg_result;

#if	TypeCheck
	boolean_t msg_simple;
#endif	TypeCheck

	unsigned int msg_size = 32;

#if	UseStaticMsgType
	static msg_type_t set_nameType = {
		/* msg_type_name = */		MSG_TYPE_INTEGER_32,
		/* msg_type_size = */		32,
		/* msg_type_number = */		1,
		/* msg_type_inline = */		TRUE,
		/* msg_type_longform = */	FALSE,
		/* msg_type_deallocate = */	FALSE,
		/* msg_type_unused = */		0
	};
#endif	UseStaticMsgType

#if	UseStaticMsgType
	static msg_type_t RetCodeCheck = {
		/* msg_type_name = */		MSG_TYPE_INTEGER_32,
		/* msg_type_size = */		32,
		/* msg_type_number = */		1,
		/* msg_type_inline = */		TRUE,
		/* msg_type_longform = */	FALSE,
		/* msg_type_deallocate = */	FALSE,
		/* msg_type_unused = */		0
	};
#endif	UseStaticMsgType

#if	UseStaticMsgType
	InP->set_nameType = set_nameType;
#else	UseStaticMsgType
	InP->set_nameType.msg_type_name = MSG_TYPE_INTEGER_32;
	InP->set_nameType.msg_type_size = 32;
	InP->set_nameType.msg_type_number = 1;
	InP->set_nameType.msg_type_inline = TRUE;
	InP->set_nameType.msg_type_longform = FALSE;
	InP->set_nameType.msg_type_deallocate = FALSE;
	InP->set_nameType.msg_type_unused = 0;
#endif	UseStaticMsgType

	InP->set_name /* set_name */ = /* set_name */ set_name;

	InP->Head.msg_simple = TRUE;
	InP->Head.msg_size = msg_size;
	InP->Head.msg_type = MSG_TYPE_NORMAL | MSG_TYPE_RPC;
	InP->Head.msg_request_port = task;
	InP->Head.msg_reply_port = mig_get_reply_port();
	InP->Head.msg_id = 2084;

	msg_result = msg_rpc(&InP->Head, MSG_OPTION_NONE, sizeof(Reply), 0, 0);
	if (msg_result != RPC_SUCCESS) {
		if (msg_result == RCV_INVALID_PORT)
			mig_dealloc_reply_port();
		return msg_result;
	}

#if	TypeCheck
	msg_size = OutP->Head.msg_size;
	msg_simple = OutP->Head.msg_simple;
#endif	TypeCheck

	if (OutP->Head.msg_id != 2184)
		return MIG_REPLY_MISMATCH;

#if	TypeCheck
	if (((msg_size != 48) || (msg_simple != FALSE)) &&
	    ((msg_size != sizeof(death_pill_t)) ||
	     (msg_simple != TRUE) ||
	     (OutP->RetCode == KERN_SUCCESS)))
		return MIG_TYPE_ERROR;
#endif	TypeCheck

#if	TypeCheck
#if	UseStaticMsgType
	if (* (int *) &OutP->RetCodeType != * (int *) &RetCodeCheck)
#else	UseStaticMsgType
	if ((OutP->RetCodeType.msg_type_inline != TRUE) ||
	    (OutP->RetCodeType.msg_type_longform != FALSE) ||
	    (OutP->RetCodeType.msg_type_name != MSG_TYPE_INTEGER_32) ||
	    (OutP->RetCodeType.msg_type_number != 1) ||
	    (OutP->RetCodeType.msg_type_size != 32))
#endif	UseStaticMsgType
		return MIG_TYPE_ERROR;
#endif	TypeCheck

	if (OutP->RetCode != KERN_SUCCESS)
		return OutP->RetCode;

#if	TypeCheck
	if ((OutP->membersType.msg_type_header.msg_type_inline != FALSE) ||
	    (OutP->membersType.msg_type_header.msg_type_longform != TRUE) ||
	    (OutP->membersType.msg_type_long_name != MSG_TYPE_INTEGER_32) ||
	    (OutP->membersType.msg_type_long_size != 32))
		return MIG_TYPE_ERROR;
#endif	TypeCheck

	*members /* members */ = /* *members */ OutP->members;

	*membersCnt /* membersType.msg_type_long_number */ = /* *membersCnt */ OutP->membersType.msg_type_long_number;

	return OutP->RetCode;
}