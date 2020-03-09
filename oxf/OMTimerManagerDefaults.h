//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: OMTimerManagerDefaults
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


#ifndef OMTimerManagerDefaults_H
#define OMTimerManagerDefaults_H

//## dependency BasicTypes
#include "rawtypes.h"
//## package Design::oxf::Services::Time::TimeManagement

//## class OMTimerManagerDefaults
// Default values for the timer manager initialization
class RP_FRAMEWORK_DLL OMTimerManagerDefaults {
    ////    Constructors and destructors    ////
    
public :

    //## auto_generated
    ~OMTimerManagerDefaults(void);
    
    ////    Attributes    ////
    
    // default value of the number of tm-s that can co-exist simultaneously (either on the heap or in the matured list)
    static const Rhp_uint32_t defaultMaxTM;		//## attribute defaultMaxTM
    
    // default value of the timer's tick length
    static const Rhp_uint32_t defaultTicktime;		//## attribute defaultTicktime
    
};

#endif



