//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: IOxfEventSender
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


#ifndef IOxfEventSender_H
#define IOxfEventSender_H

//## dependency IOxfEventGenerationParams
#include "IOxfEventGenerationParams.h"
//## dependency OMOSEventGenerationParams
#include "OMOSEventGenerationParams.h"
//## dependency Types
#include "OXFTypes.h"
//## dependency IOxfEvent
class IOxfEvent;

//## package Design::oxf::Core::CoreAPI

//## class IOxfEventSender
// A thin interface specifying the service to send events.
// This can be used for reactive interfaces (interfaces with event receptions) since all they do is accept the event.
class RP_FRAMEWORK_DLL IOxfEventSender {
    ////    Constructors and destructors    ////
    
public :

    //## operation ~IOxfEventSender()
    inline virtual ~IOxfEventSender(void) {
        //#[ operation ~IOxfEventSender()
        //#]
    }
    
    ////    Operations    ////
    
    // send the specified event to the instance active context queue
    // Argument IOxfEvent* ev :
    // The event to send
    // Argument const IOxfEventGenerationParams& params :
    // Event sending parameters
    //## operation send(IOxfEvent,IOxfEventGenerationParams)
    virtual bool send(IOxfEvent* ev, const IOxfEventGenerationParams& params) = 0;
    
    // send the specified event to the instance active context queue
    // Argument IOxfEvent* ev :
    // The event to send
    //## operation send(IOxfEvent)
    virtual bool send(IOxfEvent* ev) = 0;
    
};

#endif



