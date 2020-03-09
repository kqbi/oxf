//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: OMEvent
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
#include "OMEvent.h"
//## dependency AnimServices
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
//## package Design::oxf::Core::CoreImplementation

//## class OMEvent
OMEvent::OMEvent(IOxfEvent::ID eventId, IOxfReactive* dest) : lId(eventId), deleteAfterConsume(true), 
frameworkEvent(false), port(NULL), synchronous(false), destination(dest) {
    //#[ operation OMEvent(ID,IOxfReactive)
    #ifdef ATG_MODIFICATIONS_TO_OXF
        ATG_showEventID();
    #endif
    //#]
}

OMEvent::OMEvent(const OMEvent& ev) : lId(ev.lId), deleteAfterConsume(ev.deleteAfterConsume), 
frameworkEvent(ev.frameworkEvent), port(ev.port), synchronous(ev.synchronous), destination(ev.destination) {
    //#[ operation OMEvent(OMEvent)
    #ifdef ATG_MODIFICATIONS_TO_OXF
        ATG_showEventID();
    #endif
    //#]
}

OMEvent::~OMEvent(void) {
    //#[ operation ~OMEvent()
    #ifdef _OMINSTRUMENT
    AnimServices::notifyEventDestroyed(this);
    #endif
    //#]
    cleanUpRelations();
}

//#[ ignore
#ifdef ATG_MODIFICATIONS_TO_OXF

//#]
OMEvent* OMEvent::ATG_showEventID(void) {
    //#[ operation ATG_showEventID()
    return(this);
    //#]
}
//#[ ignore

#endif // ATG_MODIFICATIONS_TO_OXF

//#]

void OMEvent::cancel(void) {
    //#[ operation cancel()
    //#]
}

void OMEvent::destroy(void) {
    //#[ operation destroy()
    if (shouldDeleteAfterConsume()) {
    	delete this;
    }
    //#]
}

OxfTimeUnit OMEvent::getDelayTime(void) const {
    //#[ operation getDelayTime() const
    return 0;
    //#]
}

OxfTimeUnit OMEvent::getDueTime(void) const {
    //#[ operation getDueTime() const
    return 0;
    //#]
}

bool OMEvent::isCanceled(void) const {
    //#[ operation isCanceled() const
    return false;
    //#]
}

bool OMEvent::isRealEvent(void) const {
    //#[ operation isRealEvent() const
    return (lId >= OMTimeoutEventId);
    //#]
}

OMEvent& OMEvent::operator =(const OMEvent& ev) {
    //#[ operation operator =(OMEvent)
    lId = ev.lId;
    deleteAfterConsume = ev.deleteAfterConsume;
    frameworkEvent = ev.frameworkEvent;
    port = ev.port;
    synchronous = ev.synchronous;
    destination = ev.destination;
    return *this;
    //#]
}

void OMEvent::setDelayTime(OxfTimeUnit /**/) {
    //#[ operation setDelayTime(OxfTimeUnit)
    //#]
}

void OMEvent::setDueTime(OxfTimeUnit /**/) {
    //#[ operation setDueTime(OxfTimeUnit)
    //#]
}

bool OMEvent::shouldDeleteAfterConsume(void) const {
    return deleteAfterConsume;
}

void OMEvent::setDeleteAfterConsume(bool p_deleteAfterConsume) {
    deleteAfterConsume = p_deleteAfterConsume;
}

bool OMEvent::isFrameworkEvent(void) const {
    return frameworkEvent;
}

void OMEvent::setFrameworkEvent(bool p_frameworkEvent) {
    frameworkEvent = p_frameworkEvent;
}

void * OMEvent::getPort(void) const {
    return port;
}

void OMEvent::setPort(void * const p_port) {
    port = p_port;
}

bool OMEvent::getSynchronous(void) const {
    return synchronous;
}

void OMEvent::setSynchronous(bool p_synchronous) {
    synchronous = p_synchronous;
}

IOxfReactive* OMEvent::getDestination(void) const {
    return destination;
}

void OMEvent::setDestination(IOxfReactive* p_IOxfReactive) {
    destination = p_IOxfReactive;
}

void OMEvent::cleanUpRelations(void) {
    if(destination != NULL)
        {
            destination = NULL;
        }
}




