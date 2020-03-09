//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: OMDefaultOutBound
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
#include "OMDefaultOutBound.h"
//## dependency IOxfActive
#include "IOxfActive.h"
//## dependency IOxfEvent
#include "IOxfEvent.h"
//## dependency OMOSEventGenerationParams
#include "OMOSEventGenerationParams.h"
//## package Design::oxf::Services::Ports

//## class OMDefaultOutBound
OMDefaultOutBound::OMDefaultOutBound(void) : itsDefaultRequiredInterface(NULL)  {
    //#[ operation OMDefaultOutBound()
    //#]
}

OMDefaultOutBound::~OMDefaultOutBound(void) {
    cleanUpRelations();
}

bool OMDefaultOutBound::cancelTimeout(const IOxfTimeout* /*timeout*/) {
    //#[ operation cancelTimeout(IOxfTimeout)
    return false;
    //#]
}

void OMDefaultOutBound::destroy(void) {
    //#[ operation destroy()
    //#]
}

void OMDefaultOutBound::endBehavior(const Rhp_const_char_pt /*theTerminator*/) {
    //#[ operation endBehavior(Rhp_const_char_pt)
    //#]
}

IOxfActive* OMDefaultOutBound::getActiveContext(void) const {
    //#[ operation getActiveContext() const
    return 0;
    //#]
}

IOxfEvent* OMDefaultOutBound::getCurrentEvent(void) const {
    //#[ operation getCurrentEvent() const
    return 0;
    //#]
}

IOxfReactive::TakeEventStatus OMDefaultOutBound::handleEvent(IOxfEvent* /*ev*/) {
    //#[ operation handleEvent(IOxfEvent)
    return IOxfReactive::eventNotConsumed;
    //#]
}

void OMDefaultOutBound::popNullTransition(void) {
    //#[ operation popNullTransition()
    //#]
}

void OMDefaultOutBound::pushNullTransition(void) {
    //#[ operation pushNullTransition()
    //#]
}

bool OMDefaultOutBound::send(IOxfEvent* ev, const IOxfEventGenerationParams& params) {
    //#[ operation send(IOxfEvent,IOxfEventGenerationParams)
    bool res = false;
    if (ev != NULL) {
    	if (itsDefaultRequiredInterface != NULL){
    		res = itsDefaultRequiredInterface->send(ev, params);
    	} 
    	else
    	{
    		//avoid memory leak of the created event (via the GEN macro) when ports aren't linked
    		if(ev)
    			ev->destroy();
    	}
    }
    return res;
    //#]
}

bool OMDefaultOutBound::send(IOxfEvent* ev) {
    //#[ operation send(IOxfEvent)
    OMOSEventGenerationParams p;
    return send(ev, p);
    //#]
}

void OMDefaultOutBound::setActiveContext(IOxfActive* /**/) {
    //#[ operation setActiveContext(IOxfActive)
    //#]
}

bool OMDefaultOutBound::startBehavior(void) {
    //#[ operation startBehavior()
    return true;
    //#]
}

void OMDefaultOutBound::handleNotConsumed(IOxfEvent* /*ev*/, IOxfReactive::EventNotConsumedReason /*reason*/) {
    //#[ operation handleNotConsumed(IOxfEvent,EventNotConsumedReason)
    //#]
}

void OMDefaultOutBound::handleTrigger(IOxfEvent* /*ev*/) {
    //#[ operation handleTrigger(IOxfEvent)
    //#]
}

IOxfTimeout* OMDefaultOutBound::scheduleTimeout(OxfTimeUnit /*delay*/, const Rhp_const_char_pt /*targetStateName*/) {
    //#[ operation scheduleTimeout(OxfTimeUnit,Rhp_const_char_pt)
    return NULL;
    //#]
}

IOxfReactive* OMDefaultOutBound::getItsDefaultRequiredInterface(void) const {
    return itsDefaultRequiredInterface;
}

void OMDefaultOutBound::setItsDefaultRequiredInterface(IOxfReactive* p_IOxfReactive) {
    itsDefaultRequiredInterface = p_IOxfReactive;
}

void OMDefaultOutBound::cleanUpRelations(void) {
    if(itsDefaultRequiredInterface != NULL)
        {
            itsDefaultRequiredInterface = NULL;
        }
}




