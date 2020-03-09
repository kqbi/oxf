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



//## auto_generated
#include "OXFEvents.h"
//## package Design::oxf::Services::Events



//#[ ignore
//lint -save -e1506 -e1401 (safe within event generated code)

//#]



//## event OMStartBehaviorEvent()
OMStartBehaviorEvent::OMStartBehaviorEvent(void) : OMEvent() {
    setId(OMStartBehaviorEvent_Events_Services_oxf_Design_id);
    setDeleteAfterConsume(false);
}

bool OMStartBehaviorEvent::isTypeOf(const IOxfEvent::ID id) const {
    //#[ operation isTypeOf(ID) const
    return (lId==id);
    //#]
}

void OMStartBehaviorEvent::reincarnateAsTerminationEvent(void) {
    //#[ operation reincarnateAsTerminationEvent()
    setId(OMReactiveTerminationEventId);
    setFrameworkEvent(true);
    //#]
}

//#[ ignore
const IOxfEvent::ID OMStartBehaviorEvent_Events_Services_oxf_Design_id(OMStartBehaviorEventId);
//#]

//## event OMEndThreadEvent()
OMEndThreadEvent::OMEndThreadEvent(void) : OMEvent() {
    setId(OMEndThreadEvent_Events_Services_oxf_Design_id);
    setDeleteAfterConsume(false);
}

bool OMEndThreadEvent::isTypeOf(const IOxfEvent::ID id) const {
    return (OMEndThreadEvent_Events_Services_oxf_Design_id==id);
}

//#[ ignore
const IOxfEvent::ID OMEndThreadEvent_Events_Services_oxf_Design_id(OMEndThreadEventId);
//#]

//## event OMNullEvent()
OMNullEvent::OMNullEvent(void) : OMEvent() {
    setId(OMNullEvent_Events_Services_oxf_Design_id);
}

bool OMNullEvent::isTypeOf(const IOxfEvent::ID id) const {
    return (OMNullEvent_Events_Services_oxf_Design_id==id);
}

//#[ ignore
const IOxfEvent::ID OMNullEvent_Events_Services_oxf_Design_id(OMNullEventId);
//#]

//## event OMCloseHandleEvent(void *)
OMCloseHandleEvent::OMCloseHandleEvent(void * p_handle) : OMEvent() ,handle(p_handle) {
    setId(OMCloseHandleEvent_Events_Services_oxf_Design_id);
}

bool OMCloseHandleEvent::isTypeOf(const IOxfEvent::ID id) const {
    return (OMCloseHandleEvent_Events_Services_oxf_Design_id==id);
}

//#[ ignore
const IOxfEvent::ID OMCloseHandleEvent_Events_Services_oxf_Design_id(OMCloseHandleEventId);
//#]

//## event OMReactiveTerminationEvent()
OMReactiveTerminationEvent::OMReactiveTerminationEvent(void) : OMEvent() {
    setId(OMReactiveTerminationEvent_Events_Services_oxf_Design_id);
    setDeleteAfterConsume(false);
}

bool OMReactiveTerminationEvent::isTypeOf(const IOxfEvent::ID id) const {
    return (OMReactiveTerminationEvent_Events_Services_oxf_Design_id==id);
}

//#[ ignore
const IOxfEvent::ID OMReactiveTerminationEvent_Events_Services_oxf_Design_id(OMReactiveTerminationEventId);
//#]

//## event evGetBusy(unsigned long,OMOSEventFlag)
evGetBusy::evGetBusy(unsigned long p_t) : OMEvent() ,t(p_t) {
    setId(evGetBusy_Events_Services_oxf_Design_id);
}

bool evGetBusy::isTypeOf(const IOxfEvent::ID id) const {
    return (evGetBusy_Events_Services_oxf_Design_id==id);
}

//#[ ignore
const IOxfEvent::ID evGetBusy_Events_Services_oxf_Design_id(25801);
//#]

//#[ ignore
//lint -restore
//#]


//
//! Log: $Log$
//


