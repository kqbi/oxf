//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: OMAnimReactive
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


#ifndef OMAnimReactive_H
#define OMAnimReactive_H

//## class OMAnimReactive
#include "IOxfAnimReactive.h"
//## dependency Manager
#include "OXFManager.h"
//## dependency IOxfReactive
class IOxfReactive;

//## dependency OMEventQueue
class OMEventQueue;

//## link oxfReactive
class OMReactive;

//## dependency OMThread
class OMThread;

//## package Design::oxf::Anim::AnimImplementation

//## class OMAnimReactive
// OMReactive animation wrapper
class RP_FRAMEWORK_DLL OMAnimReactive : public IOxfAnimReactive {
//#[ ignore
    // override new & delete operators
    OM_DECLARE_FRAMEWORK_MEMORY_ALLOCATION_OPERATORS
    
    
//#]

    ////    Constructors and destructors    ////
    
public :

    // initialization
    // Argument OMReactive* context :
    // The reactive instance to wrap
    //## operation OMAnimReactive(OMReactive)
    explicit OMAnimReactive(OMReactive* context);
    
    //## auto_generated
    ~OMAnimReactive(void);
    
    ////    Operations    ////
    
    // Checks if the queue can accept a new event (if it is not full)
    //## operation canAcceptEvents() const
    bool canAcceptEvents(void) const;
    
    // get the identifier of the OS thread that is associated with the active context of the reactive instance
    //## operation getContextThread() const
    void * getContextThread(void) const;
    
    // Returns the "real" reactive part. 
    // Used (for example) to send events
    //## operation getOxfReactive() const
    IOxfReactive* getOxfReactive(void) const;
    
    // Send an animated event to the reactive context
    // Argument IOxfEvent* ev :
    // The event
    // Argument void * sender :
    // The event sender
    //## operation send(IOxfEvent,void *)
    bool send(IOxfEvent* ev, void * sender);
    
    // Serializes the states.
    // Argument AOMSState* aomArg(states) :
    // The animation states vector to fill.
    // AnimServices provides operations to fill the vector so all you need to do is to pass this pointer to these operations.
    //## operation serializeStates(AOMSState) const
    void serializeStates(AOMSState* aomArg(states)) const;
    

private :

    // Get the thread
    //## operation getThread() const
    OMThread* getThread(void) const;
    
    ////    Additional operations    ////
    

protected :

    //## auto_generated
    void cleanUpRelations(void);
    
    ////    Relations and components    ////
    

private :

    // The reactive instance
    OMReactive* oxfReactive;		//## link oxfReactive
    
};

#endif



