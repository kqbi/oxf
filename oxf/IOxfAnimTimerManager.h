//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: IOxfAnimTimerManager
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


#ifndef IOxfAnimTimerManager_H
#define IOxfAnimTimerManager_H

//## dependency IOxfReactive
#include "IOxfReactive.h"
//## dependency Types
#include "OXFTypes.h"
//## package Design::oxf::Anim::AnimAPI

//## class IOxfAnimTimerManager
// An animation interface to the timer manager singleton class implementation
// Enables the animation layer to communicate with the timer manager implementation
class RP_FRAMEWORK_DLL IOxfAnimTimerManager {
    ////    Constructors and destructors    ////
    
public :

    // Cleanup
    //## operation ~IOxfAnimTimerManager()
    inline virtual ~IOxfAnimTimerManager(void) {
        //#[ operation ~IOxfAnimTimerManager()
        //#]
    }
    
    ////    Operations    ////
    
    // advance the system time to the next waiting timeout
    //## operation advanceTime()
    virtual void advanceTime(void) = 0;
    
    // Returns the elapsed time
    //## operation getElapsedTime() const
    virtual OxfTimeUnit getElapsedTime(void) const = 0;
    
    //## operation isExternalTimer() const
    virtual bool isExternalTimer(void) const = 0;
    
    // A service to be notified after deltaT time.
    // Argument IOxfReactive* reactive :
    // The reactive requesting the service
    // Argument const OxfTimeUnit deltaT :
    // The requested time to elapse
    // Argument OxfTimeUnit& baseTime :
    // An output parameter containing the current time
    //## operation requestTimeNotification(IOxfReactive*,const OxfTimeUnit,IOxfTimeout*&,OxfTimeUnit&)
    virtual void requestTimeNotification(IOxfReactive* reactive, const OxfTimeUnit deltaT, IOxfTimeout*& timeout
, OxfTimeUnit& baseTime) = 0;
    
    // Resumes the timer manager after it was suspended
    //## operation resume()
    virtual void resume(void) = 0;
    
    // Suspends the timer manager
    //## operation suspend()
    virtual void suspend(void) = 0;
    
};

#endif



