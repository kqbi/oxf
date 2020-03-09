#ifndef _osesocket_H
#define _osesocket_H
//
//	file name   :	$Source: R:/StmOO/Master/cg/LangCpp/oxf/rcs/osesocket.h $
//	file version:	$Revision: 1.6 $
//
//	purpose:	
//
//	author(s):	Mikko Holappa
//	date started:	
//	date changed:	$Date: 2007/03/11 08:43:01 $
//	last change by:	$Author: ilgiga $
//
//	Licensed Materials - Property of IBM
//	(c) Copyright IBM Corporation 1999, 2016. All Rights Reserved.
//	
//	Note to U.S. Government Users Restricted Rights:  
//	Use, duplication or disclosure restricted by GSA ADP Schedule 
//	Contract with IBM Corp.
//
// ---------------------------------------------------------------
//|                                oseOS.h                        |
// --------------------------------------------------------------- 


#ifdef _OMINSTRUMENT

#ifndef USE_WIN32_SOCKET
#include <inet.h>
#endif // !USE_WIN32_SOCKET

#include <oxf/omtypes.h>
#include <oxf/os.h>

class oseSocket: public OMOSSocket {
private:
	int theSock;
public:
	oseSocket(void);
	virtual ~oseSocket(void);
	virtual Rhp_int32_t Create(	const Rhp_const_char_pt SocketAddress = NULL, const Rhp_uint32_t nSocketPort = 0);
	virtual Rhp_int32_t Send(const Rhp_const_char_pt lpBuf, const Rhp_int32_t nBufLen);
	virtual Rhp_int32_t Receive(Rhp_char_pt lpBuf, const Rhp_int32_t nBufLen);
	virtual Rhp_int32_t HasInputOnScoket(void);
};


#endif // _OMINSTRUMENT


//
// $Log: osesocket.h $
// Revision 1.6  2007/03/11 08:43:01  ilgiga
// Change copyright comment
// Revision 1.5  2007/03/01 14:32:41  ilgiga
// Telelogic instead of i-Logix
// Revision 1.4  2005/11/07 12:11:44  yshekel
// Upgrade_from_60_to_61
// Revision 1.3  2001/05/03 15:57:13  amos
// Changes framework API to support OSE 4.3.1
// - Modify the name of  OMOSMutex::free() to OMOSMutex::unlock
// - Modify the name of State::exit() & State::enter() to State::exitState() & State::enterState()
// Revision 1.2  2001/04/19 11:41:28  amos
// upgrade OSE files to support OSE 4.3.1
// - cleanup the OSE framework files
// - use OSE 4.3.1 API to fix the behavior of oseThread::setPriority() - so it can be called by other threads.
// Revision 1.1  1999/12/08 13:21:50  ofer
// Initial revision
// Revision 1.1  1999/11/08 10:58:38  ofer
// Initial revision
// 
#endif // _osesocket_H


