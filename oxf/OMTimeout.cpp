//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: OMTimeout
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
#include "OMTimeout.h"
//## auto_generated
//#[ ignore
#ifdef _OMINSTRUMENT
//#]
#include <aom/AnimServices.h>
//#[ ignore

#endif //_OMINSTRUMENT
//#]
//## dependency Events
#include "OXFEvents.h"
//## auto_generated
#include "IOxfReactive.h"
// Used for instrumentation of the timeout canceling
//## dependency OMThread
#include "omthread.h"
//## dependency OMTimerManager
#include "OMTimerManager.h"
//## dependency OXF
#include "oxf.h"
//## package Design::oxf::Core::CoreImplementation

//## class OMTimeout
IMPLEMENT_MEMORY_ALLOCATOR(OMTimeout,OM_DYNAMIC_POOL_INITIALIZATION_SIZE, 0, true)

OMTimeout::OMTimeout(IOxfReactive* pdest, OxfTimeUnit delay, const OMHandle* aomArg(theState)
) : OMEvent(OMTimeoutEventId, pdest), canceled(false), delayTime(0) , dueTime(0) , state(0) {
    //#[ operation OMTimeout(IOxfReactive,OxfTimeUnit,OMHandle)
    delayTime = delay;
    
    #ifdef _OMINSTRUMENT
    state = theState;
    AnimServices::notifyFrameworkEventCreated(this);
    #endif
    
    RESET_MEMORY_ALLOCATOR(OMTimeout)
    //#]
}

OMTimeout::OMTimeout(void) : OMEvent(OMTimeoutEventId, 0), canceled(false) , delayTime(0) , dueTime(0) , state(0) {
    //#[ operation OMTimeout()
    #ifdef _OMINSTRUMENT
    AnimServices::notifyFrameworkEventCreated(this);
    #endif
    
    RESET_MEMORY_ALLOCATOR(OMTimeout)
    //#]
}

OMTimeout::OMTimeout(const OMTimeout& tm) : OMEvent(tm), canceled(tm.canceled), delayTime(tm.delayTime), dueTime(tm.dueTime), 
state(tm.state) {
    //#[ operation OMTimeout(OMTimeout)
    RESET_MEMORY_ALLOCATOR(OMTimeout)
    //#]
}

OMTimeout::~OMTimeout(void) {
    //#[ operation ~OMTimeout()
    // self managed timeouts - notify the destination
    // so it can cleanup references
    if (destination != 0) {
    	(void)destination->cancelTimeout(this);
    }
    state = 0;
    RESET_MEMORY_ALLOCATOR(OMTimeout);
    //#]
}

void OMTimeout::cancel(void) {
    //#[ operation cancel()
    #ifdef _OMINSTRUMENT
    AnimServices::notifyTimeoutCancelled(this);
    #endif // _OMINSTRUMENT
    
    // prevent access to the destination on destruction
    setDestination(NULL);
    canceled = true;
    //#]
}

OMTimeout& OMTimeout::operator =(const OMTimeout& tm) {
    //#[ operation operator =(OMTimeout)
    (void) OMEvent::operator=(tm);
    canceled = tm.canceled;
    delayTime = tm.delayTime;
    dueTime = tm.dueTime;
    state = tm.state;
    RESET_MEMORY_ALLOCATOR(OMTimeout)
    return *this;
    //#]
}

bool OMTimeout::operator<(const OMTimeout& tn) const {
    //#[ operation operator<(OMTimeout) const
    return (dueTime < tn.dueTime);
    //#]
}

bool OMTimeout::operator>(const OMTimeout& tn) const {
    //#[ operation operator>(OMTimeout) const
    return (dueTime > tn.dueTime);
    //#]
}

void OMTimeout::setDelayTimeout(void) {
    //#[ operation setDelayTimeout()
    setId(OMTimeoutDelayId);
    //#]
}

void OMTimeout::setRelativeDueTime(OxfTimeUnit now) {
    //#[ operation setRelativeDueTime(OxfTimeUnit)
    dueTime = now + delayTime;
    //#]
}

bool OMTimeout::isCanceled(void) const {
    return canceled;
}

OxfTimeUnit OMTimeout::getDelayTime(void) const {
    return delayTime;
}

void OMTimeout::setDelayTime(OxfTimeUnit p_delayTime) {
    delayTime = p_delayTime;
}

OxfTimeUnit OMTimeout::getDueTime(void) const {
    return dueTime;
}

void OMTimeout::setDueTime(OxfTimeUnit p_dueTime) {
    dueTime = p_dueTime;
}

const OMHandle* OMTimeout::getState(void) const {
    return state;
}

void OMTimeout::setState(const OMHandle* p_state) {
    state = p_state;
}




