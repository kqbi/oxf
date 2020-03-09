//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: OMAnimReactive
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
#include "OMAnimReactive.h"
//## dependency IOxfReactive
#include "IOxfReactive.h"
//## dependency OMEventQueue
#include "OMEventQueue.h"
//## link oxfReactive
#include "omreactive.h"
//## dependency OMThread
#include "omthread.h"
//## package Design::oxf::Anim::AnimImplementation

//## class OMAnimReactive
OMAnimReactive::OMAnimReactive(OMReactive* context) : oxfReactive(context) {
    //#[ operation OMAnimReactive(OMReactive)
    //#]
}

OMAnimReactive::~OMAnimReactive(void) {
    cleanUpRelations();
}

bool OMAnimReactive::canAcceptEvents(void) const {
    //#[ operation canAcceptEvents() const
    bool res = false;
    OMThread* aThread = getThread();
    if (aThread != NULL) {
    	const OMEventQueue* aQueue = aThread->getEventQueue();
    	if (aQueue != NULL) {
    		res = (!aQueue->isFull());
    	}
    }
    return res;
    //#]
}

void * OMAnimReactive::getContextThread(void) const {
    //#[ operation getContextThread() const
    void* osThread = NULL;
    OMThread* aThread = getThread();
    if (aThread != NULL) {
    	osThread = aThread->getOsHandle();
    }
    return osThread;
    //#]
}

IOxfReactive* OMAnimReactive::getOxfReactive(void) const {
    //#[ operation getOxfReactive() const
    return oxfReactive;
    //#]
}

bool OMAnimReactive::send(IOxfEvent* ev, void * sender) {
    //#[ operation send(IOxfEvent,void *)
    bool res = false;
    if (oxfReactive != NULL) {
    	OMOSEventGenerationParams params(sender);
    	res = oxfReactive->send(ev, params);
    }
    return res;
    //#]
}

void OMAnimReactive::serializeStates(AOMSState* aomArg(states)) const {
    //#[ operation serializeStates(AOMSState) const
    #ifdef _OMINSTRUMENT
    if (oxfReactive != NULL) {
    	oxfReactive->serializeStates(states);
    }
    #endif
    //#]
}

OMThread* OMAnimReactive::getThread(void) const {
    //#[ operation getThread() const
    OMThread* aThread = NULL;
    if (oxfReactive != NULL) {
    	// IMPORTANT: at this level we assume coupling between OMReactive and OMThread
    	aThread = static_cast<OMThread*>(oxfReactive->getActiveContext());
    }
    return aThread;
    //#]
}

void OMAnimReactive::cleanUpRelations(void) {
    if(oxfReactive != NULL)
        {
            oxfReactive = NULL;
        }
}




