//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: IOxfActive
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


#ifndef IOxfActive_H
#define IOxfActive_H

//## dependency IOxfReactive
#include "IOxfReactive.h"
//## dependency Types
#include "OXFTypes.h"
//## dependency IOxfEvent
class IOxfEvent;

//## dependency IOxfEventGenerationParams
class IOxfEventGenerationParams;

//## package Design::oxf::Core::CoreAPI

//## class IOxfActive
// Active class interface.
// An active class is an event dispatcher executing an event loop (message pump), potentially on its own thread of execution.
class RP_FRAMEWORK_DLL IOxfActive {
    ////    Constructors and destructors    ////
    
public :

    // Virtual destructor to enable polymorphic deletion
    //## operation ~IOxfActive()
    inline virtual ~IOxfActive(void) {
        //#[ operation ~IOxfActive()
        //#]
    }
    
    ////    Operations    ////
    
    // end the active instance event dispatching and destroy the instance.
    //## operation endDispatching()
    virtual void endDispatching(void) = 0;
    
    // Queue the specified event to be handled by the event loop asynchronously.
    // Argument IOxfEvent* ev :
    // the event to queue
    // Argument const IOxfEventGenerationParams& params :
    // Event sending parameters
    //## operation queue(IOxfEvent,IOxfEventGenerationParams)
    virtual bool queue(IOxfEvent* ev, const IOxfEventGenerationParams& params) = 0;
    
    // start the event loop
    // Argument bool fork = false :
    // when true, a new execution thread is created as part of the call and the event loop run on the thread context.
    //## operation startDispatching(bool)
    virtual void startDispatching(bool fork = false) = 0;
    

protected :

    // dispatch the specified event to its destination
    // Argument IOxfEvent* ev :
    // The event to dispatch
    //## operation dispatch(IOxfEvent)
    virtual IOxfReactive::TakeEventStatus dispatch(IOxfEvent* ev) = 0;
    
};

#endif



