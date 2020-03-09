//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: OMDefaultMulticastInBound
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


#ifndef OMDefaultMulticastInBound_H
#define OMDefaultMulticastInBound_H

//## auto_generated
#include "omcollec.h"
//## dependency BasicTypes
#include "rawtypes.h"
//## class OMDefaultMulticastInBound
#include "IOxfReactive.h"
//## dependency IOxfActive
class IOxfActive;

//## dependency IOxfEvent
class IOxfEvent;

//## dependency OMOSEventGenerationParams
class OMOSEventGenerationParams;

//## package Design::oxf::Services::Ports

//## class OMDefaultMulticastInBound
// Default behavioral in-bound port of a reactive class implementation.
// Forward the messages to the reactive state machine.
class OMDefaultMulticastInBound : public IOxfReactive {
    ////    Constructors and destructors    ////
    
public :

    // Initialize
    //## operation OMDefaultMulticastInBound()
    RP_FRAMEWORK_DLL OMDefaultMulticastInBound(void);
    
    //## auto_generated
    virtual ~OMDefaultMulticastInBound(void);
    
    ////    Operations    ////
    
    //## operation addItsDefaultProvidedInterface(IOxfReactive*)
    RP_FRAMEWORK_DLL void addItsDefaultProvidedInterface(IOxfReactive* p_IOxfReactive);
    
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
    // dummy - to comply with the interface signature
    //## operation endBehavior(Rhp_const_char_pt)
    virtual void endBehavior(const Rhp_const_char_pt /*theTerminator*/ = NULL);
    
    // Get the provided interface active context
    //## operation getActiveContext() const
    RP_FRAMEWORK_DLL IOxfActive* getActiveContext(void) const;
    
    // Get the provided interface current event
    //## operation getCurrentEvent() const
    RP_FRAMEWORK_DLL IOxfEvent* getCurrentEvent(void) const;
    
    //## operation getItsDefaultProvidedInterface()
    RP_FRAMEWORK_DLL OMCollection<IOxfReactive*>* getItsDefaultProvidedInterface(void);
    
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
    // dummy
    //## operation setActiveContext(IOxfActive)
    void setActiveContext(IOxfActive* /**/);
    
    //## operation setItsDefaultProvidedInterface(IOxfReactive*)
    RP_FRAMEWORK_DLL void setItsDefaultProvidedInterface(IOxfReactive* p_IOxfReactive);
    
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
    // The delay time
    // Argument const Rhp_const_char_pt /*targetStateName*/ = NULL :
    // The target state
    //## operation scheduleTimeout(OxfTimeUnit,Rhp_const_char_pt)
    IOxfTimeout* scheduleTimeout(OxfTimeUnit /*delay*/, const Rhp_const_char_pt /*targetStateName*/ = NULL);
    
    ////    Additional operations    ////
    

public :

    //## auto_generated
    void * getPort(void) const;
    
    //## auto_generated
    void setPort(void * const p_port);
    
    //## auto_generated
    void removeItsDefaultProvidedInterface(IOxfReactive* p_IOxfReactive);
    
    //## auto_generated
    void clearItsDefaultProvidedInterface(void);
    

protected :

    //## auto_generated
    void cleanUpRelations(void);
    
    ////    Attributes    ////
    

private :

    // just for stamping incoming events
    void * port;		//## attribute port
    
    ////    Relations and components    ////
    
    // The port provided interface
    OMCollection<IOxfReactive*> itsDefaultProvidedInterface;		//## link itsDefaultProvidedInterface
    
};

#endif



