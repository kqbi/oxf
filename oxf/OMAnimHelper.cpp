//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: OMAnimHelper
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
#include "OMAnimHelper.h"
//## dependency Events
#include "OXFEvents.h"
//## dependency OMString
#include "omstring.h"
//## dependency OMTimeout
#include "OMTimeout.h"
// Needed for unicode adapters
//## dependency OMUnicodeHelper
#include "OMUnicodeHelper.h"
//## package Design::oxf::Anim::AnimImplementation

//## class OMAnimHelper
OMAnimHelper::~OMAnimHelper(void) {
}

bool OMAnimHelper::getFrameworkEventClassName(const IOxfEvent* event, OMString& className, bool signatureFormat) const 
{
    //#[ operation getFrameworkEventClassName(IOxfEvent,OMString,bool) const
    bool res = false;
    bool applySignatureFormat = true;
    className.Empty();
    if (event != NULL) {
    	if (event->isTypeOf(OMStartBehaviorEventId) == 1) {
    		className = "OMStartBehaviorEvent";
    		res = true;
    	} else {
    		if (event->isTypeOf(OMTimeoutEventId) == 1)	{
    			className = "Timeout";
    			applySignatureFormat = false;
    			res = true;
    		} else {
    			if (event->isTypeOf(OMTimeoutDelayId) == 1)	{
    				className = "OMDelay";
    				res = true;
    			} else {
    				if ( (event->getId() == OMAnimWakeupEventId) ||
    				 	 (event->getId() == OMCloseHandleEventId) ||
    					 (event->getId() == OMEndThreadEventId) ||
    					 (event->getId() == OMReactiveTerminationEventId) ) {
    					// invisible framework event
    					res = true;
    				}
    			}
    		}
    	}
    }
    // Signature Format
    if ( (res) &&
    	 (applySignatureFormat) &&
    	 (signatureFormat) &&
    	 (!className.IsEmpty()) ) {
    	// if 
    	//		The event is a framework event AND
    	// 		A signature format should ve applied to this event class AND
    	//		A signature format was requested AND
    	//		The class is animated (has a name)
    	className += "()";
    }
    return res;
    //#]
}

bool OMAnimHelper::getFrameworkEventSignature(const IOxfEvent* event, OMString& signature) const {
    //#[ operation getFrameworkEventSignature(IOxfEvent,OMString) const
    bool res = false;
    signature.Empty();
    if (event != NULL) {
    	if (event->isTypeOf(OMStartBehaviorEventId) == 1) {
    		signature = "OMStartBehaviorEvent";
    		res = true;
    	} else {
    		if (event->isTypeOf(OMTimeoutEventId) == 1) {
    			fillTimeoutSignature(reinterpret_cast<const OMTimeout*>(event), signature);
    			res = true;
    		} else {
    			if (event->isTypeOf(OMTimeoutDelayId) == 1) {
    				fillDelaySignature(reinterpret_cast<const OMTimeout*>(event), signature);
    				res = true;
    			} else {
    				if ( (event->getId() == OMAnimWakeupEventId) ||
    					 (event->getId() == OMCloseHandleEventId) ||
    					 (event->getId() == OMEndThreadEventId) ||
    					 (event->getId() == OMReactiveTerminationEventId) ) {
    				// invisible framework event
    				res = true;
    				}
    			}
    		}
    	}
    }
    return res;
    //#]
}

OMAnimHelper* OMAnimHelper::instance(void) {
    //#[ operation instance()
    static OMAnimHelper theHelper;
    return &theHelper;
    //#]
}

bool OMAnimHelper::isCancelledEvent(const IOxfEvent* ev) const {
    //#[ operation isCancelledEvent(IOxfEvent) const
    bool res = false;
    if (ev != NULL) {
    	if (ev->isTypeOf(OMTimeoutEventId) == 1)	{
    		res = static_cast<const IOxfTimeout*>(ev)->isCanceled();
    	} else {
    		res = (ev->getId() == OMCancelledEventId);
    	}
    }
    return res;
    //#]
}

bool OMAnimHelper::isTimeoutEvent(const IOxfEvent* ev) const {
    //#[ operation isTimeoutEvent(IOxfEvent) const
    return ( (ev != NULL) &&
    		 (ev->isTypeOf(OMTimeoutEventId)) );
    //#]
}

void OMAnimHelper::fillDelaySignature(const OMTimeout* tm, OMString& signature) const {
    //#[ operation fillDelaySignature(OMTimeout,OMString) const
    if (tm != NULL) {
       	signature = "Thread Delay ";
    	fillTime(tm, signature);
    }
    //#]
}

void OMAnimHelper::fillTime(const OMTimeout* tm, OMString& str) const {
    //#[ operation fillTime(OMTimeout,OMString) const
    const Rhp_int32_t STRING30 = 30;
    
    OxfTimeUnit t = 0;
    if (tm != NULL) {
    	t = tm->getDelayTime();
    }
    Rhp_char_t c[STRING30];
    #ifndef _OM_UNICODE_ONLY
    // simple characters
    sprintf(&c[0], "tm(%ld)", t);
    #else
    // wide characters 
    wchar_t wC[STRING30];
    swprintf(wC, L"tm(%ld)", t);
    (void) OMUnicodeHelper::wtoc(c,wC,STRING30);
    #endif // _OM_UNICODE_ONLY
    str += c;
    //#]
}

void OMAnimHelper::fillTimeoutSignature(const OMTimeout* tm, OMString& signature) const {
    //#[ operation fillTimeoutSignature(OMTimeout,OMString) const
    if (tm != NULL) {
    	fillTime(tm, signature);
       	signature += " at ";
       	signature += tm->getState();
    }
    //#]
}




