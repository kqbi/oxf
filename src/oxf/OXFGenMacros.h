//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: GenMacros
//!	File name		: $Source$
//!	File version	: $Revision$
//
//!	Date changed	: $Date$
//!	Last change by	: $Author$
//
//	Licensed Materials - Property of IBM
//	(c) Copyright IBM Corporation 2004, 2016. All Rights Reserved.
//	
//	Note to U.S. Government Users Restricted Rights:  
//	Use, duplication or disclosure restricted by GSA ADP Schedule 
//	Contract with IBM Corp.


#ifndef OXFGenMacros_H
#define OXFGenMacros_H

//## package Design::oxf::Services::Macros::GenMacros
#include <memory>

//#[ ignore
// Event sending macros
//#]

// Send an event.
//#[ type GEN
#ifdef OM_USE_NOTHROW_GEN
#define GEN(event) send(new (std::nothrow) event, OMOSEventGenerationParams(false))
#else
#define GEN(event, ...) send(std::make_shared<event>(__VA_ARGS__))
#endif
//#]

// Design level debugging - send an event via a UI that uses the framework.
//#[ type GEN_BY_GUI
#ifdef OM_USE_NOTHROW_GEN
#define GEN_BY_GUI(event) send(new (std::nothrow) event, OMOSEventGenerationParams((void*)OMGui))
#else
#define GEN_BY_GUI(event) send(new event, OMOSEventGenerationParams((void*)OMGui))
#endif
//#]

// Design level debugging - send an event from a specific context.
//#[ type GEN_BY_X
#ifdef OM_USE_NOTHROW_GEN
#define GEN_BY_X(event,sender) send(new (std::nothrow) event, OMOSEventGenerationParams(sender))
#else
#define GEN_BY_X(event,sender) send(new event, OMOSEventGenerationParams(sender))
#endif
//#]

// Send an event from the context of an ISR handler
//#[ type GEN_ISR
#define GEN_ISR(event) send(event, OMReactive::isrParams)
//#]

#endif



