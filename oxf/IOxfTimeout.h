//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: IOxfTimeout
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


#ifndef IOxfTimeout_H
#define IOxfTimeout_H

//## class IOxfTimeout
#include "IOxfEvent.h"
//## dependency IOxfReactive
class IOxfReactive;

//## package Design::oxf::Core::CoreAPI

//## class IOxfTimeout
// A timeout interface.
// A timeout is a unique type of event.
class RP_FRAMEWORK_DLL IOxfTimeout : public IOxfEvent {
    ////    Constructors and destructors    ////
    
public :

    // Virtual destructor to enable polymorphic deletion
    //## operation ~IOxfTimeout()
    inline virtual ~IOxfTimeout(void) {
        //#[ operation ~IOxfTimeout()
        //#]
    }
    
    ////    Operations    ////
    
    // cancel the timeout
    //## operation cancel()
    virtual void cancel(void) = 0;
    
    ////    Additional operations    ////
    
    //## auto_generated
    virtual bool isCanceled(void) const = 0;
    
    //## auto_generated
    virtual OxfTimeUnit getDelayTime(void) const = 0;
    
    //## auto_generated
    virtual void setDelayTime(OxfTimeUnit p_delayTime) = 0;
    
    //## auto_generated
    virtual OxfTimeUnit getDueTime(void) const = 0;
    
    //## auto_generated
    virtual void setDueTime(OxfTimeUnit p_dueTime) = 0;
    
};

#endif



