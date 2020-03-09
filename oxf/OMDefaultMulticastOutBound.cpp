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



//## auto_generated
#include "OMDefaultMulticastOutBound.h"
//## dependency IOxfActive
#include "IOxfActive.h"
//## dependency IOxfEvent
#include "IOxfEvent.h"
//## dependency OMOSEventGenerationParams
#include "OMOSEventGenerationParams.h"
//## package Design::oxf::Services::Ports

//## class OMDefaultMulticastOutBound
RP_FRAMEWORK_DLL OMDefaultMulticastOutBound::OMDefaultMulticastOutBound(void) {
    //#[ operation OMDefaultMulticastOutBound()
    //#]
}

OMDefaultMulticastOutBound::~OMDefaultMulticastOutBound(void) {
    cleanUpRelations();
}

void OMDefaultMulticastOutBound::addItsDefaultRequiredInterface(IOxfReactive* p_IOxfReactive) {
    //#[ operation addItsDefaultRequiredInterface(IOxfReactive*)
    itsDefaultRequiredInterface.add(p_IOxfReactive);
    //#]
}

bool OMDefaultMulticastOutBound::cancelTimeout(const IOxfTimeout* /*timeout*/) {
    //#[ operation cancelTimeout(IOxfTimeout)
    return false;
    //#]
}

void OMDefaultMulticastOutBound::destroy(void) {
    //#[ operation destroy()
    //#]
}

void OMDefaultMulticastOutBound::endBehavior(const Rhp_const_char_pt /*theTerminator*/) {
    //#[ operation endBehavior(Rhp_const_char_pt)
    //#]
}

IOxfActive* OMDefaultMulticastOutBound::getActiveContext(void) const {
    //#[ operation getActiveContext() const
    return 0;
    //#]
}

IOxfEvent* OMDefaultMulticastOutBound::getCurrentEvent(void) const {
    //#[ operation getCurrentEvent() const
    return 0;
    //#]
}

OMCollection<IOxfReactive*>* OMDefaultMulticastOutBound::getItsDefaultRequiredInterface(void) {
    //#[ operation getItsDefaultRequiredInterface()
    return &itsDefaultRequiredInterface;
    //#]
}

IOxfReactive::TakeEventStatus OMDefaultMulticastOutBound::handleEvent(IOxfEvent* /*ev*/) {
    //#[ operation handleEvent(IOxfEvent)
    return IOxfReactive::eventNotConsumed;
    //#]
}

void OMDefaultMulticastOutBound::popNullTransition(void) {
    //#[ operation popNullTransition()
    //#]
}

void OMDefaultMulticastOutBound::pushNullTransition(void) {
    //#[ operation pushNullTransition()
    //#]
}

bool OMDefaultMulticastOutBound::send(IOxfEvent* ev, const IOxfEventGenerationParams& params) {
    //#[ operation send(IOxfEvent,IOxfEventGenerationParams)
    bool res = false;
    if (ev != NULL) {
    	if (itsDefaultRequiredInterface.getCount() > 0){
    		res = itsDefaultRequiredInterface[0]->send(ev, params);
    	}
    }
    return res;
    //#]
}

bool OMDefaultMulticastOutBound::send(IOxfEvent* ev) {
    //#[ operation send(IOxfEvent)
    OMOSEventGenerationParams p;
    return send(ev, p);
    //#]
}

void OMDefaultMulticastOutBound::setActiveContext(IOxfActive* /**/) {
    //#[ operation setActiveContext(IOxfActive)
    //#]
}

void OMDefaultMulticastOutBound::setItsDefaultRequiredInterface(IOxfReactive* p_IOxfReactive) {
    //#[ operation setItsDefaultRequiredInterface(IOxfReactive*)
    itsDefaultRequiredInterface.add(p_IOxfReactive);
    //#]
}

bool OMDefaultMulticastOutBound::startBehavior(void) {
    //#[ operation startBehavior()
    return true;
    //#]
}

void OMDefaultMulticastOutBound::handleNotConsumed(IOxfEvent* /*ev*/, IOxfReactive::EventNotConsumedReason /*reason*/) 
{
    //#[ operation handleNotConsumed(IOxfEvent,EventNotConsumedReason)
    //#]
}

void OMDefaultMulticastOutBound::handleTrigger(IOxfEvent* /*ev*/) {
    //#[ operation handleTrigger(IOxfEvent)
    //#]
}

IOxfTimeout* OMDefaultMulticastOutBound::scheduleTimeout(OxfTimeUnit /*delay*/, const Rhp_const_char_pt
 /*targetStateName*/) {
    //#[ operation scheduleTimeout(OxfTimeUnit,Rhp_const_char_pt)
    return NULL;
    //#]
}

void OMDefaultMulticastOutBound::removeItsDefaultRequiredInterface(IOxfReactive* p_IOxfReactive) {
    itsDefaultRequiredInterface.remove(p_IOxfReactive);
}

void OMDefaultMulticastOutBound::clearItsDefaultRequiredInterface(void) {
    itsDefaultRequiredInterface.removeAll();
}

void OMDefaultMulticastOutBound::cleanUpRelations(void) {
    {
        itsDefaultRequiredInterface.removeAll();
    }
}




