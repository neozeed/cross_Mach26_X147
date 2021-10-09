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


/* Routine vm_region */
mig_external kern_return_t vm_region
#if	(defined(__STDC__) || defined(c_plusplus))
(
	vm_task_t target_task,
	vm_address_t *address,
	vm_size_t *size,
	vm_prot_t *protection,
	vm_prot_t *max_protection,
	vm_inherit_t *inheritance,
	boolean_t *is_shared,
	memory_object_name_t *object_name,
	vm_offset_t *offset
)
#else
	(target_task, address, size, protection, max_protection, inheritance, is_shared, object_name, offset)
	vm_task_t target_task;
	vm_address_t *address;
	vm_size_t *size;
	vm_prot_t *protection;
	vm_prot_t *max_protection;
	vm_inherit_t *inheritance;
	boolean_t *is_shared;
	memory_object_name_t *object_name;
	vm_offset_t *offset;
#endif
{
	typedef struct {
		msg_header_t Head;
		msg_type_t addressType;
		vm_address_t address;
	} Request;

	typedef struct {
		msg_header_t Head;
		msg_type_t RetCodeType;
		kern_return_t RetCode;
		msg_type_t addressType;
		vm_address_t address;
		msg_type_t sizeType;
		vm_size_t size;
		msg_type_t protectionType;
		vm_prot_t protection;
		msg_type_t max_protectionType;
		vm_prot_t max_protection;
		msg_type_t inheritanceType;
		vm_inherit_t inheritance;
		msg_type_t is_sharedType;
		boolean_t is_shared;
		msg_type_t object_nameType;
		memory_object_name_t object_name;
		msg_type_t offsetType;
		vm_offset_t offset;
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
	static msg_type_t addressType = {
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
	static msg_type_t addressCheck = {
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
	static msg_type_t sizeCheck = {
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
	static msg_type_t protectionCheck = {
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
	static msg_type_t max_protectionCheck = {
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
	static msg_type_t inheritanceCheck = {
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
	static msg_type_t is_sharedCheck = {
		/* msg_type_name = */		MSG_TYPE_BOOLEAN,
		/* msg_type_size = */		32,
		/* msg_type_number = */		1,
		/* msg_type_inline = */		TRUE,
		/* msg_type_longform = */	FALSE,
		/* msg_type_deallocate = */	FALSE,
		/* msg_type_unused = */		0
	};
#endif	UseStaticMsgType

#if	UseStaticMsgType
	static msg_type_t object_nameCheck = {
		/* msg_type_name = */		MSG_TYPE_PORT,
		/* msg_type_size = */		32,
		/* msg_type_number = */		1,
		/* msg_type_inline = */		TRUE,
		/* msg_type_longform = */	FALSE,
		/* msg_type_deallocate = */	FALSE,
		/* msg_type_unused = */		0
	};
#endif	UseStaticMsgType

#if	UseStaticMsgType
	static msg_type_t offsetCheck = {
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
	InP->addressType = addressType;
#else	UseStaticMsgType
	InP->addressType.msg_type_name = MSG_TYPE_INTEGER_32;
	InP->addressType.msg_type_size = 32;
	InP->addressType.msg_type_number = 1;
	InP->addressType.msg_type_inline = TRUE;
	InP->addressType.msg_type_longform = FALSE;
	InP->addressType.msg_type_deallocate = FALSE;
	InP->addressType.msg_type_unused = 0;
#endif	UseStaticMsgType

	InP->address /* *address */ = /* address */ *address;

	InP->Head.msg_simple = TRUE;
	InP->Head.msg_size = msg_size;
	InP->Head.msg_type = MSG_TYPE_NORMAL | MSG_TYPE_RPC;
	InP->Head.msg_request_port = target_task;
	InP->Head.msg_reply_port = mig_get_reply_port();
	InP->Head.msg_id = 2029;

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

	if (OutP->Head.msg_id != 2129)
		return MIG_REPLY_MISMATCH;

#if	TypeCheck
	if (((msg_size != 96) || (msg_simple != FALSE)) &&
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
#if	UseStaticMsgType
	if (* (int *) &OutP->addressType != * (int *) &addressCheck)
#else	UseStaticMsgType
	if ((OutP->addressType.msg_type_inline != TRUE) ||
	    (OutP->addressType.msg_type_longform != FALSE) ||
	    (OutP->addressType.msg_type_name != MSG_TYPE_INTEGER_32) ||
	    (OutP->addressType.msg_type_number != 1) ||
	    (OutP->addressType.msg_type_size != 32))
#endif	UseStaticMsgType
		return MIG_TYPE_ERROR;
#endif	TypeCheck

	*address /* address */ = /* *address */ OutP->address;

#if	TypeCheck
#if	UseStaticMsgType
	if (* (int *) &OutP->sizeType != * (int *) &sizeCheck)
#else	UseStaticMsgType
	if ((OutP->sizeType.msg_type_inline != TRUE) ||
	    (OutP->sizeType.msg_type_longform != FALSE) ||
	    (OutP->sizeType.msg_type_name != MSG_TYPE_INTEGER_32) ||
	    (OutP->sizeType.msg_type_number != 1) ||
	    (OutP->sizeType.msg_type_size != 32))
#endif	UseStaticMsgType
		return MIG_TYPE_ERROR;
#endif	TypeCheck

	*size /* size */ = /* *size */ OutP->size;

#if	TypeCheck
#if	UseStaticMsgType
	if (* (int *) &OutP->protectionType != * (int *) &protectionCheck)
#else	UseStaticMsgType
	if ((OutP->protectionType.msg_type_inline != TRUE) ||
	    (OutP->protectionType.msg_type_longform != FALSE) ||
	    (OutP->protectionType.msg_type_name != MSG_TYPE_INTEGER_32) ||
	    (OutP->protectionType.msg_type_number != 1) ||
	    (OutP->protectionType.msg_type_size != 32))
#endif	UseStaticMsgType
		return MIG_TYPE_ERROR;
#endif	TypeCheck

	*protection /* protection */ = /* *protection */ OutP->protection;

#if	TypeCheck
#if	UseStaticMsgType
	if (* (int *) &OutP->max_protectionType != * (int *) &max_protectionCheck)
#else	UseStaticMsgType
	if ((OutP->max_protectionType.msg_type_inline != TRUE) ||
	    (OutP->max_protectionType.msg_type_longform != FALSE) ||
	    (OutP->max_protectionType.msg_type_name != MSG_TYPE_INTEGER_32) ||
	    (OutP->max_protectionType.msg_type_number != 1) ||
	    (OutP->max_protectionType.msg_type_size != 32))
#endif	UseStaticMsgType
		return MIG_TYPE_ERROR;
#endif	TypeCheck

	*max_protection /* max_protection */ = /* *max_protection */ OutP->max_protection;

#if	TypeCheck
#if	UseStaticMsgType
	if (* (int *) &OutP->inheritanceType != * (int *) &inheritanceCheck)
#else	UseStaticMsgType
	if ((OutP->inheritanceType.msg_type_inline != TRUE) ||
	    (OutP->inheritanceType.msg_type_longform != FALSE) ||
	    (OutP->inheritanceType.msg_type_name != MSG_TYPE_INTEGER_32) ||
	    (OutP->inheritanceType.msg_type_number != 1) ||
	    (OutP->inheritanceType.msg_type_size != 32))
#endif	UseStaticMsgType
		return MIG_TYPE_ERROR;
#endif	TypeCheck

	*inheritance /* inheritance */ = /* *inheritance */ OutP->inheritance;

#if	TypeCheck
#if	UseStaticMsgType
	if (* (int *) &OutP->is_sharedType != * (int *) &is_sharedCheck)
#else	UseStaticMsgType
	if ((OutP->is_sharedType.msg_type_inline != TRUE) ||
	    (OutP->is_sharedType.msg_type_longform != FALSE) ||
	    (OutP->is_sharedType.msg_type_name != MSG_TYPE_BOOLEAN) ||
	    (OutP->is_sharedType.msg_type_number != 1) ||
	    (OutP->is_sharedType.msg_type_size != 32))
#endif	UseStaticMsgType
		return MIG_TYPE_ERROR;
#endif	TypeCheck

	*is_shared /* is_shared */ = /* *is_shared */ OutP->is_shared;

#if	TypeCheck
#if	UseStaticMsgType
	if (* (int *) &OutP->object_nameType != * (int *) &object_nameCheck)
#else	UseStaticMsgType
	if ((OutP->object_nameType.msg_type_inline != TRUE) ||
	    (OutP->object_nameType.msg_type_longform != FALSE) ||
	    (OutP->object_nameType.msg_type_name != MSG_TYPE_PORT) ||
	    (OutP->object_nameType.msg_type_number != 1) ||
	    (OutP->object_nameType.msg_type_size != 32))
#endif	UseStaticMsgType
		return MIG_TYPE_ERROR;
#endif	TypeCheck

	*object_name /* object_name */ = /* *object_name */ OutP->object_name;

#if	TypeCheck
#if	UseStaticMsgType
	if (* (int *) &OutP->offsetType != * (int *) &offsetCheck)
#else	UseStaticMsgType
	if ((OutP->offsetType.msg_type_inline != TRUE) ||
	    (OutP->offsetType.msg_type_longform != FALSE) ||
	    (OutP->offsetType.msg_type_name != MSG_TYPE_INTEGER_32) ||
	    (OutP->offsetType.msg_type_number != 1) ||
	    (OutP->offsetType.msg_type_size != 32))
#endif	UseStaticMsgType
		return MIG_TYPE_ERROR;
#endif	TypeCheck

	*offset /* offset */ = /* *offset */ OutP->offset;

	return OutP->RetCode;
}
