//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: IOxfEventGenerationParams
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


#ifndef IOxfEventGenerationParams_H
#define IOxfEventGenerationParams_H

//## dependency Types
#include "OXFTypes.h"
//## package Design::oxf::Core::CoreAPI

//## class IOxfEventGenerationParams
// Abstract event generation parameters (allows the implementer to add generation parameters, such as generation timeout, priority etc.)
class RP_FRAMEWORK_DLL IOxfEventGenerationParams {
    ////    Constructors and destructors    ////
    
public :

    // Virtual destructor to enable polymorphic deletion
    //## operation ~IOxfEventGenerationParams()
    inline virtual ~IOxfEventGenerationParams(void) {
        //#[ operation ~IOxfEventGenerationParams()
        //#]
    }
    
    ////    Additional operations    ////
    
    //## auto_generated
    virtual bool getFromISR(void) const = 0;
    
    //## auto_generated
    virtual void setFromISR(bool p_fromISR) = 0;
    
    //## auto_generated
    virtual void * getSender(void) const = 0;
    
    //## auto_generated
    virtual void setSender(void * const p_sender) = 0;
    
};

#endif



