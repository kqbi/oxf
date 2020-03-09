//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: PortMacros
//!	File name		: $Source$
//!	File version	: $Revision$
//
//!	Date changed	: $Date$
//!	Last change by	: $Author$
//
//	Licensed Materials - Property of IBM
//	(c) Copyright IBM Corporation 2004, 2018. All Rights Reserved.
//	
//	Note to U.S. Government Users Restricted Rights:  
//	Use, duplication or disclosure restricted by GSA ADP Schedule 
//	Contract with IBM Corp.


#ifndef OXFPortMacros_H
#define OXFPortMacros_H

//## dependency GenMacros
#include "OXFGenMacros.h"
//## package Design::oxf::Services::Macros::PortMacros


//#[ ignore
// Ports access macros
//#]

// Get the out bound of the provided port
//#[ type _OPORT
#define _OPORT(p) ((p != NULL) ? p->getOutBound() : NULL)
//#]

// Check if the current event was sent via the specified port
//#[ type IS_PORT
#define IS_PORT(p) ((getCurrentEvent() != NULL) ? (getCurrentEvent()->getPort() == (void *)(get_##p())) : false)
//#]

// Check if the current event was sent via the specified port when using a port with multiplicity > 1
//#[ type IS_PORT_AT
#define IS_PORT_AT(p,i) ((getCurrentEvent() != NULL) ? (getCurrentEvent()->getPort() == (void *)(get_##p(i))) : false)
//#]

// Get the out bound of the provided port
//#[ type OPORT
#define OPORT(p) OUT_PORT(p)
//#]

// Get the out bound of the provided port when using a port with multiplicity > 1
//#[ type OPORT_AT
#define OPORT_AT(p, i) OUT_PORT_AT(p, i)
//#]

// Get the out bound of the provided port
//#[ type OUT_PORT
#define OUT_PORT(p) _OPORT(get_##p())
//#]

// Get the out bound of the provided port when using a port with multiplicity > 1
//#[ type OUT_PORT_AT
#define OUT_PORT_AT(p, i) _OPORT(get_##p(i))
//#]

//#[ type FLOW_DATA_SEND
#ifdef _OMINSTRUMENT
#define FLOW_DATA_SEND(flowPort, servicePortName, relayFunc, serializeFunc) \
{																\
	Rhp_char_pt fpValStr = serializeFunc(flowPort);					\
	NOTIFY_FLOW_DATA_SEND(#flowPort, fpValStr)					\
	OUT_PORT(servicePortName)->relayFunc(flowPort);				\
	NOTIFY_FLOW_DATA_SEND_END									\
	delete [] fpValStr;											\
}
#else
#define FLOW_DATA_SEND(flowPort, servicePortName, relayFunc, serializeFunc) \
	OUT_PORT(servicePortName)->relayFunc(flowPort);
#endif
//#]

//#[ type FLOW_DATA_RECEIVE
#ifdef _OMINSTRUMENT
#define FLOW_DATA_RECEIVE(argName, argValue, serializeFunc) \
{																		\
	Rhp_char_pt argValStr = serializeFunc(argValue);							\
	NOTIFY_FLOW_DATA_RECEIVE(argName, argValStr)						\
	delete [] argValStr;												\
}
#else
#define FLOW_DATA_RECEIVE(argName, argValue, serializeFunc) 
#endif		
	
//#]

// Get the out bound of the provided port
//#[ type FLOW_GEN
#define FLOW_GEN(PORT, EVENT) OUT_PORT(PORT##_SP)->GEN(EVENT)
//#]

//#[ type MULTICAST_GEN
#define MULTICAST_GEN(PORT, EVENT) \
{ \
	if (OUT_PORT(PORT)) \
	{ \
		OMCollection<IOxfReactive*>*  pLinksContainer = OUT_PORT(PORT)->getItsDefaultRequiredInterface(); \
		if (pLinksContainer) \
		{ \
			for (Rhp_int32_t i = 0; i < (*pLinksContainer).getCount(); i++) \
			{ \
				(*pLinksContainer)[i]->GEN(EVENT); \
			} \
		} \
	} \
}	
//#]

//#[ type MULTICAST_FLOW_GEN
#define MULTICAST_FLOW_GEN(PORT, EVENT) MULTICAST_GEN(PORT##_SP, EVENT)
//#]

//#[ type FLOW_DATA_POP
#ifdef _OMINSTRUMENT
#define FLOW_DATA_POP		\
{							\
	NOTIFY_FLOW_DATA_POP	\
}
#else
#define FLOW_DATA_POP
#endif		

//#]

#endif



