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


#ifndef OMAnimHelper_H
#define OMAnimHelper_H

//## class OMAnimHelper
#include "IOxfAnimHelper.h"
//## dependency OMString
class OMString;

//## dependency OMTimeout
class OMTimeout;

//## dependency OMUnicodeHelper
class OMUnicodeHelper;

//## package Design::oxf::Anim::AnimImplementation

//## class OMAnimHelper
// OMReactive animation wrapper
class RP_FRAMEWORK_DLL OMAnimHelper : public IOxfAnimHelper {
    ////    Constructors and destructors    ////
    
public :

    //## auto_generated
    virtual ~OMAnimHelper(void);
    
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
) const;
    
    // he operation will return false and empty string for user events, and the event signature for animated internal framework events (e.g. start behavior, timeouts)
    // Returns true if the event was handled (invisible framework events should return true and with an empty signature)
    // Argument const IOxfEvent* event :
    // the event to get the signature for
    // Argument OMString& signature :
    // The specified event animation signature
    //## operation getFrameworkEventSignature(IOxfEvent,OMString) const
    virtual bool getFrameworkEventSignature(const IOxfEvent* event, OMString& signature) const;
    
    // Get the singleton instance
    //## operation instance()
    static OMAnimHelper* instance(void);
    
    // Return true if the provided event is cancelled
    // Argument const IOxfEvent* ev :
    // the event
    //## operation isCancelledEvent(IOxfEvent) const
    virtual bool isCancelledEvent(const IOxfEvent* ev) const;
    
    // Return true if the provided event is a timeout
    // Argument const IOxfEvent* ev :
    // the event
    //## operation isTimeoutEvent(IOxfEvent) const
    virtual bool isTimeoutEvent(const IOxfEvent* ev) const;
    

private :

    // Fill the signature for the provided delay-timeout
    // Argument const OMTimeout* tm :
    // The delay-timeout
    // Argument OMString& signature :
    // The signature to fill
    //## operation fillDelaySignature(OMTimeout,OMString) const
    void fillDelaySignature(const OMTimeout* tm, OMString& signature) const;
    
    // Fill the string with the time for the provided timeout
    // Argument const OMTimeout* tm :
    // The timeout
    // Argument OMString& str :
    // The string to fill
    //## operation fillTime(OMTimeout,OMString) const
    void fillTime(const OMTimeout* tm, OMString& str) const;
    
    // Fill the signature for the provided timeout
    // Argument const OMTimeout* tm :
    // The timeout
    // Argument OMString& signature :
    // The signature to fill
    //## operation fillTimeoutSignature(OMTimeout,OMString) const
    void fillTimeoutSignature(const OMTimeout* tm, OMString& signature) const;
    
};

#endif



