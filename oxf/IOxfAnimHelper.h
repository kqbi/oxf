//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: IOxfAnimHelper
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


#ifndef IOxfAnimHelper_H
#define IOxfAnimHelper_H

//## dependency DllMacros
#include "rp_framework_dll_definition.h"
//## dependency IOxfEvent
class IOxfEvent;

//## dependency OMString
class OMString;

//## package Design::oxf::Anim::AnimAPI

//## class IOxfAnimHelper
// An animation helper interface a singleton helper class that provides animation with a set of services
class RP_FRAMEWORK_DLL IOxfAnimHelper {
    ////    Constructors and destructors    ////
    
public :

    // Cleanup
    //## operation ~IOxfAnimHelper()
    inline virtual ~IOxfAnimHelper(void) {
        //#[ operation ~IOxfAnimHelper()
        //#]
    }
    
    ////    Operations    ////
    
    // The operation will return false and an empty string for user events, and the event class name for animated internal framework events (e.g. start behavior, timeouts)
    // Returns true if the event was handled (invisible framework events should return true and with an empty signature)
    // Argument const IOxfEvent* event :
    // the event to get the signature for
    // Argument OMString& className :
    // The specified event animation signature
    // Argument bool signatureFormat = false :
    // Specify that the class name should be return in a signature format i.e. <class>()
    //## operation getFrameworkEventClassName(IOxfEvent,OMString,bool) const
    virtual bool getFrameworkEventClassName(const IOxfEvent* event, OMString& className, bool signatureFormat = false
) const = 0;
    
    // The operation will return false and empty string for user events, and the event signature for animated internal framework events (e.g. start behavior, timeouts)
    // Returns true if the event was handled (invisible framework events should return true and with an empty signature)
    // Argument const IOxfEvent* event :
    // the event to get the signature for
    // Argument OMString& signature :
    // The specified event animation signature
    //## operation getFrameworkEventSignature(IOxfEvent,OMString) const
    virtual bool getFrameworkEventSignature(const IOxfEvent* event, OMString& signature) const = 0;
    
    // Return true if the provided event is cancelled
    // Argument const IOxfEvent* ev :
    // the event
    //## operation isCancelledEvent(IOxfEvent) const
    virtual bool isCancelledEvent(const IOxfEvent* ev) const = 0;
    
    // Return true if the provided event is a timeout
    // Argument const IOxfEvent* ev :
    // the event
    //## operation isTimeoutEvent(IOxfEvent) const
    virtual bool isTimeoutEvent(const IOxfEvent* ev) const = 0;
    
};

#endif



