//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: IOxfAnimReactive
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


#ifndef IOxfAnimReactive_H
#define IOxfAnimReactive_H

//## dependency DllMacros
#include "rp_framework_dll_definition.h"
//## dependency AOMSState
class AOMSState;

//## dependency IOxfEvent
class IOxfEvent;

//## link oxfReactive
class IOxfReactive;

//## dependency OMString
class OMString;

//## package Design::oxf::Anim::AnimAPI

//## class IOxfAnimReactive
// An animation interface to the reactive class implementation
// Enables the animation layer to communicate with the reactive class implementation
class RP_FRAMEWORK_DLL IOxfAnimReactive {
    ////    Constructors and destructors    ////
    
public :

    // Cleanup
    //## operation ~IOxfAnimReactive()
    inline virtual ~IOxfAnimReactive(void) {
        //#[ operation ~IOxfAnimReactive()
        //#]
    }
    
    ////    Operations    ////
    
    // Checks if the queue can accept a new event (if it is not full)
    //## operation canAcceptEvents() const
    virtual bool canAcceptEvents(void) const = 0;
    
    // get the identifier of the OS thread that is associated with the active context of the reactive instance
    //## operation getContextThread() const
    virtual void * getContextThread(void) const = 0;
    
    // Returns the "real" reactive part. 
    // Used (for example) to send events
    //## operation getOxfReactive() const
    virtual IOxfReactive* getOxfReactive(void) const = 0;
    
    // Send an animated event to the reactive context
    // Argument IOxfEvent* ev :
    // The event
    // Argument void * sender :
    // The event sender
    //## operation send(IOxfEvent,void *)
    virtual bool send(IOxfEvent* ev, void * sender) = 0;
    
    // Serializes the states.
    // Argument AOMSState* states :
    // The animation states vector to fill.
    // AnimServices provides operations to fill the vector so all you need to do is to pass this pointer to these operations.
    //## operation serializeStates(AOMSState) const
    virtual void serializeStates(AOMSState* states) const = 0;
    
};

#endif



