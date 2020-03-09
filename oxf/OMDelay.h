//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: OMDelay
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


#ifndef OMDelay_H
#define OMDelay_H

//## dependency BasicTypes
#include "rawtypes.h"
//## dependency AnimServices
class AnimServices;

//## link stopSignal
class OMOSEventFlag;

//## dependency OMTimeout
class OMTimeout;

//## dependency OMTimerManager
class OMTimerManager;

//## package Design::oxf::Services::Time::TimeManagement

//## class OMDelay
// Delay the calling thread
class RP_FRAMEWORK_DLL OMDelay {
    ////    Constructors and destructors    ////
    
public :

    // Initialize a delay class
    // Argument OxfTimeUnit aTime :
    // The delay time
    //## operation OMDelay(OxfTimeUnit)
    explicit OMDelay(OxfTimeUnit aTime);
    

private :

    // the copy ctor and the assignment operator should not be used
    // Argument const OMDelay& delay :
    // The delay to copy
    //## operation OMDelay(OMDelay)
    explicit OMDelay(const OMDelay& delay);    //lint !e1704 !e1526 (disable copy constructor)
    

public :

    // Cleanup
    //## operation ~OMDelay()
    ~OMDelay(void);
    
    ////    Operations    ////
    
    // Wakeup  the delayed thread
    //## operation wakeup()
    void wakeup(void);
    

private :

    // Disabled assignment operator
    // Argument const OMDelay& delay :
    // The delay to copy
    //## operation operator=(OMDelay)
    OMDelay& operator=(const OMDelay& delay);   //lint !e1526 (disable copy constructor)
    
    ////    Additional operations    ////
    

protected :

    //## auto_generated
    void cleanUpRelations(void);
    
    ////    Relations and components    ////
    

private :

    OMOSEventFlag* stopSignal;		//## link stopSignal
    
};

#endif



