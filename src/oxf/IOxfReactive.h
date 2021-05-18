//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: IOxfReactive
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


#ifndef IOxfReactive_H
#define IOxfReactive_H

//## class IOxfReactive
#include "IOxfEventSender.h"
#include "IOxfTimeout.h"
//## link activeContext
class IOxfActive;

//## link currentEvent
class IOxfEvent;

//## dependency IOxfEventGenerationParams
class IOxfEventGenerationParams;

//## dependency IOxfTimeout
class IOxfTimeout;

//## package Design::oxf::Core::CoreAPI

//## class IOxfReactive
// UML reactive class interface.
// Responsible for event consumption.
// A reactive instance is consuming events in a context of a single active instance.
class IOxfReactive : public IOxfEventSender, public std::enable_shared_from_this<IOxfReactive> {
public :

    // Event dispatching result
    //## type TakeEventStatus
    enum TakeEventStatus {
        eventNotConsumed = 0,
        eventConsumed = 1,
        instanceUnderDestruction = 2,
        instanceReachTerminate = 3
    };
    
    // The reason handleNotConsumed() is called.
    // ---------------------------------------------------------------------
    // StateMachineBusy - the state machine is handling another event (for example when a triggered operation is called while an event is being consumed).
    // EventNotHandledByStatechart - the event was processed by the state machine but the statechart was not in a state that consumed it.
    //## type EventNotConsumedReason
    enum EventNotConsumedReason {
        StateMachineBusy,
        EventNotHandledByStatechart
    };
    
    ////    Constructors and destructors    ////
    
    // Virtual destructor to enable polymorphic deletion
    //## operation ~IOxfReactive()
    inline virtual ~IOxfReactive(void) {
        //#[ operation ~IOxfReactive()
        //#]
    }
    
    ////    Operations    ////
    
    // Cleanup references to the specified timeout.
    // Return true if the reference was removed.
    // Argument const IOxfTimeout* timeout :
    // the timeout to remove references to
    //## operation cancelTimeout(IOxfTimeout)
    virtual bool cancelTimeout(const IOxfTimeout::Ptr& timeout) = 0;
    
    // destroy the reactive instance (delete should never be called directly)
    //## operation destroy()
    virtual void destroy(void) = 0;
    
    // signal that the reactive instance reached a terminate connector
    // Argument const Rhp_const_char_pt /*theTerminator*/ = 0 :
    // The terminate connector model name (used for instrumentation)
    //## operation endBehavior(Rhp_const_char_pt)
    virtual void endBehavior() = 0;
    
    // consume an event
    // Argument IOxfEvent* ev :
    // The event to handle
    //## operation handleEvent(IOxfEvent)
    virtual TakeEventStatus handleEvent(IOxfEvent::Ptr ev) = 0;
    
    // signal that a null transition was taken (called by the generated code)
    //## operation popNullTransition()
    virtual void popNullTransition(void) = 0;
    
    // signal that there is a null transition to be taken (called by the generated code)
    //## operation pushNullTransition()
    virtual void pushNullTransition(void) = 0;
    
    // initialize the reactive instance state machine
    //## operation startBehavior()
    virtual bool startBehavior(void) = 0;
    

protected :

    // react to an event that was not consumed.
    // note that the event can be allocated on the stack.
    // Argument IOxfEvent* ev :
    // The context event
    // Argument EventNotConsumedReason reason :
    // The reason that the event wasn't consumed
    //## operation handleNotConsumed(IOxfEvent,EventNotConsumedReason)
    virtual void handleNotConsumed(IOxfEvent::Ptr& ev, EventNotConsumedReason reason) = 0;
    
    // consume a triggered operation (synchronous event)
    // Argument IOxfEvent* ev :
    // The call-event
    //## operation handleTrigger(IOxfEvent)
    virtual void handleTrigger(IOxfEvent::Ptr& ev) = 0;
    
    // schedule a timeout to be consumed by the reactive instance.
    // Argument OxfTimeUnit delay :
    // The delay until the timeout will expire
    // Argument const Rhp_const_char_pt targetStateName :
    // The name of the destination state (used for instrumentation)
    //## operation scheduleTimeout(OxfTimeUnit,Rhp_const_char_pt)
    virtual std::shared_ptr<IOxfTimeout> scheduleTimeout(unsigned long delay, const char* targetStateName) = 0;
    
    ////    Additional operations    ////
    

public :

    //## auto_generated
    virtual IOxfActive* getActiveContext(void) const = 0;
    
    //## auto_generated
    virtual void setActiveContext(IOxfActive* p_IOxfActive) = 0;
    
    //## auto_generated
    virtual std::shared_ptr<IOxfEvent> getCurrentEvent(void) = 0;
    
};

#endif



