//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: OMOSEventGenerationParams
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
#include "OMOSEventGenerationParams.h"
//## dependency BasicTypes
#include "rawtypes.h"
//## package Design::oxf::Services::RTOSWrappers

//## class OMOSEventGenerationParams

//#[ ignore
#ifndef OM_ADAPTER_OS_EVEMT_GENERATION_PARAMS

//#]


OMOSEventGenerationParams::OMOSEventGenerationParams(void) : fromISR(false), sender(NULL) {
    //#[ operation OMOSEventGenerationParams()
    //#]
}

OMOSEventGenerationParams::OMOSEventGenerationParams(const bool genFromISR) : fromISR(genFromISR), sender(NULL) {
    //#[ operation OMOSEventGenerationParams(bool)
    //#]
}

OMOSEventGenerationParams::OMOSEventGenerationParams(void * theSender) : fromISR(false), sender(theSender) {
    //#[ operation OMOSEventGenerationParams(void *)
    //#]
}

OMOSEventGenerationParams::~OMOSEventGenerationParams(void) {
    //#[ operation ~OMOSEventGenerationParams()
    sender = NULL;
    //#]
}

bool OMOSEventGenerationParams::getFromISR(void) const {
    return fromISR;
}

void OMOSEventGenerationParams::setFromISR(bool p_fromISR) {
    fromISR = p_fromISR;
}

void * OMOSEventGenerationParams::getSender(void) const {
    return sender;
}

void OMOSEventGenerationParams::setSender(void * const p_sender) {
    sender = p_sender;
}


//#[ ignore

#endif // !OM_ADAPTER_OS_EVEMT_GENERATION_PARAMS
//#]




