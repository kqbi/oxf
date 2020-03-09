//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: Events
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


#ifndef OXFEvents_H
#define OXFEvents_H

//## dependency OMEvent
#include "OMEvent.h"
//## dependency OMOSEventFlag
#include "os.h"
//## package Design::oxf::Services::Events


//#[ ignore
// Predefined events used by the framework implementation
//#]

// Animation wakeup event id
// Used by the thread manager to implement the wakeup API
//## attribute OMAnimWakeupEventId
const IOxfEvent::ID OMAnimWakeupEventId(-10);

// Any event id is used by the timer manager in extensive timeout management mode to locate timeouts that needs to be canceled.
//## attribute OMAnyEventId
const IOxfEvent::ID OMAnyEventId(-4);

// Canceled event special id
// Required for event canceling
//## attribute OMCancelledEventId
const IOxfEvent::ID OMCancelledEventId(-3);

// OMCloseHandleEvent event id
//## attribute OMCloseHandleEventId
const IOxfEvent::ID OMCloseHandleEventId(-7);

// OMEndThreadEvent event id
//## attribute OMEndThreadEventId
const IOxfEvent::ID OMEndThreadEventId(-6);

// OMNullEvent event id
//## attribute OMNullEventId
const IOxfEvent::ID OMNullEventId(-1);

// The id of the reactive termination event
//## attribute OMReactiveTerminationEventId
const IOxfEvent::ID OMReactiveTerminationEventId(-9);

// OMStartBehaviorEvent event id
//## attribute OMStartBehaviorEventId
const IOxfEvent::ID OMStartBehaviorEventId(-5);

// OMDelay timeout id
//## attribute OMTimeoutDelayId
const IOxfEvent::ID OMTimeoutDelayId(-8);

// Timeout event id
//## attribute OMTimeoutEventId
const IOxfEvent::ID OMTimeoutEventId(-2);

// Support consumption of NULL transitions that follows the default transition on the appropriate active context
//## event OMStartBehaviorEvent()
class RP_FRAMEWORK_DLL OMStartBehaviorEvent : public OMEvent {
    ////    Constructors and destructors    ////
    
public :

    //## auto_generated
    OMStartBehaviorEvent(void);
    
    ////    Operations    ////
    
    //## operation isTypeOf(ID) const
    bool isTypeOf(const IOxfEvent::ID id) const;
    
    //## operation reincarnateAsTerminationEvent()
    void reincarnateAsTerminationEvent(void);
    
};

//#[ ignore
extern const IOxfEvent::ID OMStartBehaviorEvent_Events_Services_oxf_Design_id;
//#]

// Active classes event loop termination
//## event OMEndThreadEvent()
class RP_FRAMEWORK_DLL OMEndThreadEvent : public OMEvent {
//#[ ignore
    // override new & delete operators
    OM_DECLARE_FRAMEWORK_MEMORY_ALLOCATION_OPERATORS
    
    
//#]

    ////    Constructors and destructors    ////
    
public :

    //## auto_generated
    OMEndThreadEvent(void);
    
    ////    Framework operations    ////
    
    //## statechart_method
    virtual bool isTypeOf(const IOxfEvent::ID id) const;
    
};

//#[ ignore
extern const IOxfEvent::ID OMEndThreadEvent_Events_Services_oxf_Design_id;
//#]

// Null event is used for consumption of null transitions
//## event OMNullEvent()
class OMNullEvent : public OMEvent {
    ////    Constructors and destructors    ////
    
public :

    //## auto_generated
    OMNullEvent(void);
    
    ////    Framework operations    ////
    
    //## statechart_method
    virtual bool isTypeOf(const IOxfEvent::ID id) const;
    
};

//#[ ignore
extern const IOxfEvent::ID OMNullEvent_Events_Services_oxf_Design_id;
//#]

// An event used for RTOS threads cleanup in adapters that uses the OMHandleCloser
//## event OMCloseHandleEvent(void *)
class OMCloseHandleEvent : public OMEvent {
//#[ ignore
    // override new & delete operators
    OM_DECLARE_FRAMEWORK_MEMORY_ALLOCATION_OPERATORS
    
    
//#]

    ////    Constructors and destructors    ////
    
public :

    //## auto_generated
    explicit OMCloseHandleEvent(void * p_handle);
    
    ////    Framework operations    ////
    
    //## statechart_method
    virtual bool isTypeOf(const IOxfEvent::ID id) const;
    
    ////    Framework    ////
    
    void * handle;		//## auto_generated
    
};

//#[ ignore
extern const IOxfEvent::ID OMCloseHandleEvent_Events_Services_oxf_Design_id;
//#]

// OMReactive graceful termination event
//## event OMReactiveTerminationEvent()
class RP_FRAMEWORK_DLL OMReactiveTerminationEvent : public OMEvent {
    ////    Constructors and destructors    ////
    
public :

    //## auto_generated
    OMReactiveTerminationEvent(void);
    
    ////    Framework operations    ////
    
    //## statechart_method
    virtual bool isTypeOf(const IOxfEvent::ID id) const;
    
};

//#[ ignore
extern const IOxfEvent::ID OMReactiveTerminationEvent_Events_Services_oxf_Design_id;
//#]

//## event evGetBusy(OxfTimeUnit,OMOSEventFlag)
class evGetBusy : public OMEvent {
    ////    Constructors and destructors    ////
    
public :

    //## auto_generated
    evGetBusy(OxfTimeUnit p_t, OMOSEventFlag* p_myLocker);
    
    ////    Framework operations    ////
    
    //## statechart_method
    virtual bool isTypeOf(const IOxfEvent::ID id) const;
    
    ////    Framework    ////
    
    OxfTimeUnit t;		//## auto_generated
    
    OMOSEventFlag* myLocker;		//## auto_generated
    
};

//#[ ignore
extern const IOxfEvent::ID evGetBusy_Events_Services_oxf_Design_id;
//#]

#endif



