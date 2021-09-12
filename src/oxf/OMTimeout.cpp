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
//## dependency OMTimerManager
#include "OMTimerManager.h"
//## package Design::oxf::Core::CoreImplementation

OMTimeout::OMTimeout(std::shared_ptr<IOxfReactive> pdest, OMTimerManager& tm, oxf::EventPoller::Ptr &poller, unsigned long delay, const char* theState
) : OMEvent(OMTimeoutEventId, pdest), _tm(tm), _poller(poller), _timer(nullptr), canceled(false), delayTime(0) , dueTime(0) , state(0) {
    //#[ operation OMTimeout(IOxfReactive,unsigned long,OMHandle)
    delayTime = delay;
    state = theState;
    //#]
}

//OMTimeout::OMTimeout(void) : OMEvent(OMTimeoutEventId, 0), canceled(false) , delayTime(0) , dueTime(0) , state(0) {
//    //#[ operation OMTimeout()
//    //#]
//}

//OMTimeout::OMTimeout(const OMTimeout& tm) : OMEvent(tm), canceled(tm.canceled), delayTime(tm.delayTime), dueTime(tm.dueTime),
//state(tm.state) {
//    //#[ operation OMTimeout(OMTimeout)
//    //#]
//}

OMTimeout::~OMTimeout(void) {
    //#[ operation ~OMTimeout()
    // self managed timeouts - notify the destination
    // so it can cleanup references
//    if (destination != 0) {
//    	(void)destination->cancelTimeout(this);
//    }
//    state = 0;
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

void OMTimeout::action() {
    std::weak_ptr<IOxfTimeout> weakSelf = std::dynamic_pointer_cast<IOxfTimeout>(shared_from_this());
    _timer = std::make_shared<oxf::Timer>((float)delayTime/1000, [weakSelf](){
        auto timeout = weakSelf.lock();
        if (timeout) {
            if (timeout->isCanceled()) {
                (std::dynamic_pointer_cast<OMTimeout>(timeout))->_tm.remove(timeout);
            } else {
                (std::dynamic_pointer_cast<OMTimeout>(timeout))->_tm.action(timeout);
            }
        }
        return false;
    },_poller);
}

OMTimeout& OMTimeout::operator =(const OMTimeout& tm) {
    //#[ operation operator =(OMTimeout)
    (void) OMEvent::operator=(tm);
    canceled = tm.canceled;
    delayTime = tm.delayTime;
    dueTime = tm.dueTime;
    state = tm.state;
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

void OMTimeout::setRelativeDueTime(unsigned long now) {
    //#[ operation setRelativeDueTime(unsigned long)
    dueTime = now + delayTime;
    //#]
}

bool OMTimeout::isCanceled(void) const {
    return canceled;
}

unsigned long OMTimeout::getDelayTime(void) const {
    return delayTime;
}

void OMTimeout::setDelayTime(unsigned long p_delayTime) {
    delayTime = p_delayTime;
}

unsigned long OMTimeout::getDueTime(void) const {
    return dueTime;
}

void OMTimeout::setDueTime(unsigned long p_dueTime) {
    dueTime = p_dueTime;
}

const char* OMTimeout::getState(void) const {
    return state;
}

void OMTimeout::setState(const char* p_state) {
    state = p_state;
}




