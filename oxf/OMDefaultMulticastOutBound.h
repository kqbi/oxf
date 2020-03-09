//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: OMDefaultMulticastOutBound
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


#ifndef OMDefaultMulticastOutBound_H
#define OMDefaultMulticastOutBound_H

//## auto_generated
#include "omcollec.h"
//## dependency BasicTypes
#include "rawtypes.h"
//## class OMDefaultMulticastOutBound
#include "IOxfReactive.h"
//## dependency IOxfActive
class IOxfActive;

//## dependency IOxfEvent
class IOxfEvent;

//## dependency OMOSEventGenerationParams
class OMOSEventGenerationParams;

//## package Design::oxf::Services::Ports

//## class OMDefaultMulticastOutBound
// default out-bound port to a reactive instance.
// forward the events to the reactive target.
class OMDefaultMulticastOutBound : public IOxfReactive {
    ////    Constructors and destructors    ////
    
public :

    // Initialize
    //## operation OMDefaultMulticastOutBound()
    RP_FRAMEWORK_DLL OMDefaultMulticastOutBound(void);
    
    //## auto_generated
    virtual ~OMDefaultMulticastOutBound(void);
    
    ////    Operations    ////
    
    //## operation addItsDefaultRequiredInterface(IOxfReactive*)
    RP_FRAMEWORK_DLL void addItsDefaultRequiredInterface(IOxfReactive* p_IOxfReactive);
    
    // cleanup references to the specified timeout
    // return true if the reference was removed.
    // Argument const IOxfTimeout* /*timeout*/ :
    // the timeout to remove references to
    //## operation cancelTimeout(IOxfTimeout)
    bool cancelTimeout(const IOxfTimeout* /*timeout*/);
    
    // destroy the reactive instance (delete should never be called directly)
    //## operation destroy()
    void destroy(void);
    
    // signal that the reactive instance reached a terminate connector
    // Argument const Rhp_const_char_pt /*theTerminator*/ = NULL :
    // the termination connector name
    //## operation endBehavior(Rhp_const_char_pt)
    virtual void endBehavior(const Rhp_const_char_pt /*theTerminator*/ = NULL);
    
    // Unused, needed to realize the entire IOxfReactive interface
    //## operation getActiveContext() const
    IOxfActive* getActiveContext(void) const;
    
    // Unused, needed to realize the entire IOxfReactive interface
    //## operation getCurrentEvent() const
    IOxfEvent* getCurrentEvent(void) const;
    
    //## operation getItsDefaultRequiredInterface()
    RP_FRAMEWORK_DLL OMCollection<IOxfReactive*>* getItsDefaultRequiredInterface(void);
    
    // consume an event
    // Argument IOxfEvent* /*ev*/ :
    // The event
    //## operation handleEvent(IOxfEvent)
    IOxfReactive::TakeEventStatus handleEvent(IOxfEvent* /*ev*/);
    
    // signal that a null transition was taken (called by the generated code)
    //## operation popNullTransition()
    void popNullTransition(void);
    
    // signal that there is a null transition to be taken (called by the generated code)
    //## operation pushNullTransition()
    void pushNullTransition(void);
    
    // send an event to the active context queue
    // Argument IOxfEvent* ev :
    // The event
    // Argument const IOxfEventGenerationParams& params :
    // Sending parameters
    //## operation send(IOxfEvent,IOxfEventGenerationParams)
    RP_FRAMEWORK_DLL bool send(IOxfEvent* ev, const IOxfEventGenerationParams& params);
    
    // send the specified event to the instance active context queue
    // Argument IOxfEvent* ev :
    // The event
    //## operation send(IOxfEvent)
    RP_FRAMEWORK_DLL bool send(IOxfEvent* ev);
    
    // Unused, needed to realize the entire IOxfReactive interface
    // Argument IOxfActive* /**/ :
    // The active context
    //## operation setActiveContext(IOxfActive)
    RP_FRAMEWORK_DLL void setActiveContext(IOxfActive* /**/);
    
    //## operation setItsDefaultRequiredInterface(IOxfReactive*)
    RP_FRAMEWORK_DLL void setItsDefaultRequiredInterface(IOxfReactive* p_IOxfReactive);
    
    // initialize the reactive instance state machine
    //## operation startBehavior()
    bool startBehavior(void);
    

protected :

    // react to an event that was not consumed.
    // note that the event can be allocated on the stack.
    // Argument IOxfEvent* /*ev*/ :
    // The event
    // Argument IOxfReactive::EventNotConsumedReason /*reason*/ :
    // The reason
    //## operation handleNotConsumed(IOxfEvent,EventNotConsumedReason)
    void handleNotConsumed(IOxfEvent* /*ev*/, IOxfReactive::EventNotConsumedReason /*reason*/);
    
    // consume a triggered operation (synchronous event)
    // Argument IOxfEvent* /*ev*/ :
    // The call-event
    //## operation handleTrigger(IOxfEvent)
    void handleTrigger(IOxfEvent* /*ev*/);
    
    // schedule a timeout to be consumed by the reactive instance.
    // Argument OxfTimeUnit /*delay*/ :
    // The delay
    // Argument const Rhp_const_char_pt /*targetStateName*/ = NULL :
    // The state name
    //## operation scheduleTimeout(OxfTimeUnit,Rhp_const_char_pt)
    IOxfTimeout* scheduleTimeout(OxfTimeUnit /*delay*/, const Rhp_const_char_pt /*targetStateName*/ = NULL);
    
    ////    Additional operations    ////
    

public :

    //## auto_generated
    void removeItsDefaultRequiredInterface(IOxfReactive* p_IOxfReactive);
    
    //## auto_generated
    void clearItsDefaultRequiredInterface(void);
    

protected :

    //## auto_generated
    void cleanUpRelations(void);
    
    ////    Relations and components    ////
    

private :

    // The port required interface
    OMCollection<IOxfReactive*> itsDefaultRequiredInterface;		//## link itsDefaultRequiredInterface
    
};

#endif



