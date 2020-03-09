/*******************************************************************************
 * Licensed Materials - Property of IBM
 * (c) Copyright IBM Corporation 2008, 2014. All Rights Reserved.
 *
 * Note to U.S. Government Users Restricted Rights:  
 * Use, duplication or disclosure restricted by GSA ADP Schedule 
 * Contract with IBM Corp.
 *******************************************************************************/
#if ((!defined lint) && (!defined OM_NO_RCS_ID))
static const char *rcsid = "$Id: osesocket.cpp 1.9 2007/03/11 08:43:00 ilgiga Exp $";
#endif 
//
//	file name   :	$Source: R:/StmOO/Master/cg/LangCpp/oxf/rcs/osesocket.cpp $
//	file version:	$Revision: 1.9 $
//
//	purpose:	 	
//
//	author(s):		
//	date started:	
//	date changed:	$Date: 2007/03/11 08:43:00 $
//	last change by:	$Author: ilgiga $
//
//	Licensed Materials - Property of IBM
//	(c) Copyright IBM Corporation 1996, 2008. All Rights Reserved.
//


#ifdef _OMINSTRUMENT

#ifdef USE_WIN32_SOCKET
#include <winsock.h>
#include <oxf/osesocket.h>
#include <oxf/omoutput.h>

#include <sys/types.h>
#include <sys/stat.h>

#ifdef OM_STL
#include <cstdlib>
#include <cstdio>
#else
#include <stdlib.h>
#include <stdio.h>
#endif // OM_STL

// the following 2 routines should be global and should be
// place somewhere else



oseSocket::oseSocket(void)
{
	theSock = (SOCKET)0;
}

oseSocket::~oseSocket(void)
{
	if (theSock != 0) {
		(void)closesocket((SOCKET)theSock);
	}
}


Rhp_int32_t oseSocket::Create(	const Rhp_const_char_pt  SocketAddress /*= NULL*/,
						const Rhp_uint32_t nSocketPort /*= 0*/)
{
	static struct sockaddr_in	addr;
	int			proto;
	struct hostent	*host = NULL;
	char	hostName[128];
    Rhp_int32_t port = nSocketPort;
    Rhp_const_char_pt address = SocketAddress;

	if ( nSocketPort == 0 ) {
		port = 6423;
	}

	addr.sin_family = AF_INET;


	struct protoent	*protocol;
	char *proto_name = "tcp";
	if ((protocol = getprotobyname(proto_name)) == (struct protoent *) 0) {
    OM_NOTIFY_TO_ERROR("Could not get the AF_INET protocol\n");
		return 0;
	}
	proto = protocol->p_proto;


  (void)gethostname(hostName, sizeof(hostName)-1);
  if (NULL != address) {
	if (!strcmp(hostName,address)) {
		address = NULL;
	}
	else {
		(void)strcpy(hostName,address);
		if ((host = gethostbyname(hostName)) == (struct hostent *) 0) {
			 char msg[100];

			 (void)sprintf(msg,"Could not get the address of host '%s'\n",	hostName);

		   return 0;
		}
	 }
  }
  
#ifdef unix
  endprotoent();
#endif // unix
  
  addr.sin_port = htons((u_short)port);
    
  if (NULL == address) {
 	 addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
  }
  else {
	if(host)
		addr.sin_addr.s_addr = *((unsigned long *) host->h_addr);
  }
    
 
  if ((theSock = (SOCKET)socket(AF_INET, SOCK_STREAM, proto)) == INVALID_SOCKET) {
     OM_NOTIFY_TO_ERROR("Could not create socket\n");
	 theSock = (SOCKET)0;
     return 0;
  }
    
  int rvStat;
  while ((rvStat = connect((SOCKET)theSock, (struct sockaddr *) &addr, sizeof(addr))) == SOCKET_ERROR && /*lint !e740*/
		(WSAGetLastError() == WSAEINTR))
	;

  if (SOCKET_ERROR == rvStat) {
	  char msg[100];
#ifndef _OM_UNICODE_ONLY
	 (void)sprintf(msg,
		  "Could not connect to server at %s port %d\n Error No. : %d\n",
			hostName,
			(int)port,
			WSAGetLastError());
#else
	 wchar_t wmsg[100];
	 wchar_t whostName[128];
	 OMctow(whostName,hostName,128);
	 (void)swprintf(wmsg,
		  L"Could not connect to server at %s port %d\n Error No. : %d\n",
			whostName,
			(int)port,
			WSAGetLastError());
	 OMwtoc(msg,wmsg,100);
#endif // _OM_UNICODE_ONLY
	 OM_NOTIFY_TO_ERROR(msg);
	 return 0;
  }

  return 1;
}

Rhp_int32_t oseSocket::Send(const Rhp_const_char_pt lpBuf, const Rhp_int32_t nBufLen)
{
  int bytes_writ = 0;
  int n;
  
  while (bytes_writ < nBufLen) {
    n = send((SOCKET)theSock, lpBuf + bytes_writ, nBufLen - bytes_writ,0);
	if (SOCKET_ERROR == n) {
		if (WSAGetLastError() == WSAEINTR) {
			continue;
		}
		else {
			return -1;
		}
	}
    bytes_writ += n;
  }

  return bytes_writ;
}

Rhp_int32_t oseSocket::Receive(char* lpBuf, int nBufLen)
{
  int bytes_read = 0;
  int n;
  
  while (bytes_read < nBufLen) {
    n = recv((SOCKET)theSock, lpBuf + bytes_read, nBufLen - bytes_read,0);
	if (SOCKET_ERROR == n) {
		if (WSAGetLastError() == WSAEINTR) {
			continue;
		}
		else {
			return -1;
		}
	}
    bytes_read += n;
  }
  return bytes_read;
}


Rhp_int32_t oseSocket::HasInputOnScoket()
{
	u_long sizeOfData = 0;
	if (0 == ioctlsocket ((SOCKET)theSock,FIONREAD,&sizeOfData)) {
		if (sizeOfData > 0)
			return 1;
	}
	
	return 0;
}



#endif // USE_WIN32_SOCKET
#endif // _OMINSTRUMENT

// 
// $Log: osesocket.cpp $
// Revision 1.9  2007/03/11 08:43:00  ilgiga
// Change copyright comment
// Revision 1.8  2007/03/01 14:32:41  ilgiga
// Telelogic instead of i-Logix
// Revision 1.7  2005/11/07 12:11:44  yshekel
// Upgrade_from_60_to_61
// Revision 1.6  2005/08/23 14:53:40  amos
// bugfix 85444 to main branch
// Revision 1.5.1.2  2005/08/22 10:08:27  amos
// provide a compilation switch (OM_NO_RCS_ID) to remove the definitions of the rcsid and hrcsid variables
// this is done to prevent compiler warnings for defined but not used global variables
// Revision 1.5.1.1  2002/07/15 12:27:47  amos
// Duplicate revision
// Revision 1.4.1.2  2002/07/04 10:40:28  avrahams
// Cleanup std namespace usage
// Revision 1.4  2001/05/16 13:31:29  amos
// merge OSE 4.3.1 support into r40
// Revision 1.3  2001/01/25 13:59:25  avrahams
// OXF globals encapsulation
// Revision 1.2.1.3  2001/05/06 07:32:04  amos
// fix syntax errors
// Revision 1.2.1.2  2001/05/03 15:57:13  amos
// Changes framework API to support OSE 4.3.1
// - Modify the name of  OMOSMutex::free() to OMOSMutex::unlock
// - Modify the name of State::exit() & State::enter() to State::exitState() & State::enterState()
// Revision 1.2.1.1  2001/04/19 14:50:29  amos
// upgrade OSE files to support OSE 4.3.1
// - cleanup the OSE framework files
// - use OSE 4.3.1 API to fix the behavior of oseThread::setPriority() - so it can be called by other threads.
// Revision 1.2  2000/07/11 07:52:03  amos
// the main change related to modify char* to const char*.
// there are some other changes related to assignment of static member function as extern "C" functions.
// Also modify NTOSMessageQueue/Sol2OSMessageQueue to have OMQueue<void*> as a private member (aggregation) instead of rivate inheritace from OMQueue<void*>
// Revision 1.1  1999/12/08 13:21:51  ofer
// Initial revision
//
