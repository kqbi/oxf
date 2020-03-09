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



//## auto_generated
#include "OMDefaultMulticastInBound.h"
//## dependency IOxfActive
#include "IOxfActive.h"
//## dependency IOxfEvent
#include "IOxfEvent.h"
//## dependency OMOSEventGenerationParams
#include "OMOSEventGenerationParams.h"
//## package Design::oxf::Services::Ports

//## class OMDefaultMulticastInBound
OMDefaultMulticastInBound::OMDefaultMulticastInBound(void) : port(NULL) {
    //#[ operation OMDefaultMulticastInBound()
    //#]
}

OMDefaultMulticastInBound::~OMDefaultMulticastInBound(void) {
    cleanUpRelations();
}

void OMDefaultMulticastInBound::addItsDefaultProvidedInterface(IOxfReactive* p_IOxfReactive) {
    //#[ operation addItsDefaultProvidedInterface(IOxfReactive*)
    itsDefaultProvidedInterface.add(p_IOxfReactive);
    //#]
}

bool OMDefaultMulticastInBound::cancelTimeout(const IOxfTimeout* /*timeout*/) {
    //#[ operation cancelTimeout(IOxfTimeout)
    return false;
    //#]
}

void OMDefaultMulticastInBound::destroy(void) {
    //#[ operation destroy()
    //#]
}

void OMDefaultMulticastInBound::endBehavior(const Rhp_const_char_pt /*theTerminator*/) {
    //#[ operation endBehavior(Rhp_const_char_pt)
    //#]
}

IOxfActive* OMDefaultMulticastInBound::getActiveContext(void) const {
    //#[ operation getActiveContext() const
    IOxfActive* context = NULL;
    if (itsDefaultProvidedInterface.getCount() > 0) {
        context = itsDefaultProvidedInterface.getAt(0)->getActiveContext();
    }
    return context;
    //#]
}

IOxfEvent* OMDefaultMulticastInBound::getCurrentEvent(void) const {
    //#[ operation getCurrentEvent() const
    IOxfEvent* ev = NULL;
    if (itsDefaultProvidedInterface.getCount() > 0) {
        ev = itsDefaultProvidedInterface.getAt(0)->getCurrentEvent();
    }
    return ev;
    //#]
}

OMCollection<IOxfReactive*>* OMDefaultMulticastInBound::getItsDefaultProvidedInterface(void) {
    //#[ operation getItsDefaultProvidedInterface()
    return &itsDefaultProvidedInterface;
    //#]
}

IOxfReactive::TakeEventStatus OMDefaultMulticastInBound::handleEvent(IOxfEvent* /*ev*/) {
    //#[ operation handleEvent(IOxfEvent)
    return IOxfReactive::eventNotConsumed;
    //#]
}

void OMDefaultMulticastInBound::popNullTransition(void) {
    //#[ operation popNullTransition()
    //#]
}

void OMDefaultMulticastInBound::pushNullTransition(void) {
    //#[ operation pushNullTransition()
    //#]
}

bool OMDefaultMulticastInBound::send(IOxfEvent* ev, const IOxfEventGenerationParams& params) {
    //#[ operation send(IOxfEvent,IOxfEventGenerationParams)
    bool res = false;
    if (ev != NULL) {
    	ev->setPort(getPort());
    	if (itsDefaultProvidedInterface.getCount() > 0){
    		res = itsDefaultProvidedInterface[0]->send(ev, params);
    	}
    }
    return res;
    //#]
}

bool OMDefaultMulticastInBound::send(IOxfEvent* ev) {
    //#[ operation send(IOxfEvent)
    OMOSEventGenerationParams p;
    return send(ev, p);
    //#]
}

void OMDefaultMulticastInBound::setActiveContext(IOxfActive* /**/) {
    //#[ operation setActiveContext(IOxfActive)
    //#]
}

void OMDefaultMulticastInBound::setItsDefaultProvidedInterface(IOxfReactive* p_IOxfReactive) {
    //#[ operation setItsDefaultProvidedInterface(IOxfReactive*)
    itsDefaultProvidedInterface.add(p_IOxfReactive);
    //#]
}

bool OMDefaultMulticastInBound::startBehavior(void) {
    //#[ operation startBehavior()
    return true;
    //#]
}

void OMDefaultMulticastInBound::handleNotConsumed(IOxfEvent* /*ev*/, IOxfReactive::EventNotConsumedReason /*reason*/) {
    //#[ operation handleNotConsumed(IOxfEvent,EventNotConsumedReason)
    //#]
}

void OMDefaultMulticastInBound::handleTrigger(IOxfEvent* /*ev*/) {
    //#[ operation handleTrigger(IOxfEvent)
    //#]
}

IOxfTimeout* OMDefaultMulticastInBound::scheduleTimeout(OxfTimeUnit /*delay*/, const Rhp_const_char_pt /*targetStateName*/) {
    //#[ operation scheduleTimeout(OxfTimeUnit,Rhp_const_char_pt)
    return NULL;
    //#]
}

void * OMDefaultMulticastInBound::getPort(void) const {
    return port;
}

void OMDefaultMulticastInBound::setPort(void * const p_port) {
    port = p_port;
}

void OMDefaultMulticastInBound::removeItsDefaultProvidedInterface(IOxfReactive* p_IOxfReactive) {
    itsDefaultProvidedInterface.remove(p_IOxfReactive);
}

void OMDefaultMulticastInBound::clearItsDefaultProvidedInterface(void) {
    itsDefaultProvidedInterface.removeAll();
}

void OMDefaultMulticastInBound::cleanUpRelations(void) {
    {
        itsDefaultProvidedInterface.removeAll();
    }
}




