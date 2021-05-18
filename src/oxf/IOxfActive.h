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
#include "IOxfEvent.h"

//## package Design::oxf::Core::CoreAPI

//## class IOxfActive
// Active class interface.
// An active class is an event dispatcher executing an event loop (message pump), potentially on its own thread of execution.
class IOxfActive {
    ////    Constructors and destructors    ////
    
public :

    // Virtual destructor to enable polymorphic deletion
    //## operation ~IOxfActive()
    inline virtual ~IOxfActive(void) {
        //#[ operation ~IOxfActive()
        //#]
    }
    
    ////    Operations    ////

protected :

    // dispatch the specified event to its destination
    // Argument IOxfEvent* ev :
    // The event to dispatch
    //## operation dispatch(IOxfEvent)
    virtual IOxfReactive::TakeEventStatus dispatch(IOxfEvent::Ptr& ev) = 0;
    
};

#endif



