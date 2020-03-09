//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: OMDefaultInBound
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
#include "OMDefaultInBound.h"
//## dependency IOxfActive
#include "IOxfActive.h"
//## dependency IOxfEvent
#include "IOxfEvent.h"
//## dependency OMOSEventGenerationParams
#include "OMOSEventGenerationParams.h"
//## package Design::oxf::Services::Ports

//## class OMDefaultInBound
OMDefaultInBound::OMDefaultInBound(void) : port(NULL), itsDefaultProvidedInterface(NULL)  {
    //#[ operation OMDefaultInBound()
    //#]
}

OMDefaultInBound::~OMDefaultInBound(void) {
    cleanUpRelations();
}

bool OMDefaultInBound::cancelTimeout(const IOxfTimeout* /*timeout*/) {
    //#[ operation cancelTimeout(IOxfTimeout)
    return false;
    //#]
}

void OMDefaultInBound::destroy(void) {
    //#[ operation destroy()
    //#]
}

void OMDefaultInBound::endBehavior(const Rhp_const_char_pt /*theTerminator*/) {
    //#[ operation endBehavior(Rhp_const_char_pt)
    //#]
}

IOxfActive* OMDefaultInBound::getActiveContext(void) const {
    //#[ operation getActiveContext() const
    IOxfActive* context = NULL;
    if (itsDefaultProvidedInterface != NULL) {
    	context = itsDefaultProvidedInterface->getActiveContext();
    }
    return context;
    //#]
}

IOxfEvent* OMDefaultInBound::getCurrentEvent(void) const {
    //#[ operation getCurrentEvent() const
    IOxfEvent* ev = NULL;
    if (itsDefaultProvidedInterface != NULL) {
    	ev = itsDefaultProvidedInterface->getCurrentEvent();
    }
    return ev;
    //#]
}

IOxfReactive::TakeEventStatus OMDefaultInBound::handleEvent(IOxfEvent* /*ev*/) {
    //#[ operation handleEvent(IOxfEvent)
    return IOxfReactive::eventNotConsumed;
    //#]
}

void OMDefaultInBound::popNullTransition(void) {
    //#[ operation popNullTransition()
    //#]
}

void OMDefaultInBound::pushNullTransition(void) {
    //#[ operation pushNullTransition()
    //#]
}

bool OMDefaultInBound::send(IOxfEvent* ev, const IOxfEventGenerationParams& params) {
    //#[ operation send(IOxfEvent,IOxfEventGenerationParams)
    bool res = false;
    if (ev != NULL) {
    	ev->setPort(getPort());
    	if (itsDefaultProvidedInterface != NULL){
    		res = itsDefaultProvidedInterface->send(ev, params);
    	}
    }
    return res;
    //#]
}

bool OMDefaultInBound::send(IOxfEvent* ev) {
    //#[ operation send(IOxfEvent)
    OMOSEventGenerationParams p;
    return send(ev, p);
    //#]
}

void OMDefaultInBound::setActiveContext(IOxfActive* /**/) {
    //#[ operation setActiveContext(IOxfActive)
    //#]
}

bool OMDefaultInBound::startBehavior(void) {
    //#[ operation startBehavior()
    return true;
    //#]
}

void OMDefaultInBound::handleNotConsumed(IOxfEvent* /*ev*/, IOxfReactive::EventNotConsumedReason /*reason*/) {
    //#[ operation handleNotConsumed(IOxfEvent,EventNotConsumedReason)
    //#]
}

void OMDefaultInBound::handleTrigger(IOxfEvent* /*ev*/) {
    //#[ operation handleTrigger(IOxfEvent)
    //#]
}

IOxfTimeout* OMDefaultInBound::scheduleTimeout(OxfTimeUnit /*delay*/, const Rhp_const_char_pt /*targetStateName*/) {
    //#[ operation scheduleTimeout(OxfTimeUnit,Rhp_const_char_pt)
    return NULL;
    //#]
}

void * OMDefaultInBound::getPort(void) const {
    return port;
}

void OMDefaultInBound::setPort(void * const p_port) {
    port = p_port;
}

IOxfReactive* OMDefaultInBound::getItsDefaultProvidedInterface(void) const {
    return itsDefaultProvidedInterface;
}

void OMDefaultInBound::setItsDefaultProvidedInterface(IOxfReactive* p_IOxfReactive) {
    itsDefaultProvidedInterface = p_IOxfReactive;
}

void OMDefaultInBound::cleanUpRelations(void) {
    if(itsDefaultProvidedInterface != NULL)
        {
            itsDefaultProvidedInterface = NULL;
        }
}




