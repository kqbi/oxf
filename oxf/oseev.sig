#ifndef _oseev_SIG
#define _oseev_SIG

/*
//
//	file name   :	$Source: R:/StmOO/Master/cg/LangCpp/oxf/rcs/oseev.sig $
//	file version:	$Revision: 1.5 $
//
//	purpose:	Rhapsody event - OSE signal structure
//
//	author(s):	Mikko Holappa
//
//	date started:	
//	date changed:	$Date: 2005/11/07 12:11:43 $
//	last change by:	$Author: yshekel $
//
//	Licensed Materials - Property of IBM
//	© Copyright IBM Corporation 1999, 2008. All Rights Reserved.
//
*/

#include "ose.h"

/* Rhapsody event signal number */
 /* !-SIGNO(struct RHAPSODY_SIGNAL)-! */
#define RHAPSODY_SIG (222)

/* the Rhapsody event signal */
struct RHAPSODY_SIGNAL
{
   SIGSELECT sigNo;
   void*     ev_data;    /* !-FORMAT("%x")-! */
};

#endif /* _oseev_SIG */

