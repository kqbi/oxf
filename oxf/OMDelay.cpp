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



//## auto_generated
#include "OMDelay.h"
//## dependency AnimServices
//#[ ignore
#ifdef _OMINSTRUMENT
//#]
#include <aom/AnimServices.h>
//#[ ignore

#endif //_OMINSTRUMENT
//#]
//## link stopSignal
#include "os.h"
//## dependency OMTimeout
#include "OMTimeout.h"
//## dependency OMTimerManager
#include "OMTimerManager.h"
//## package Design::oxf::Services::Time::TimeManagement

//## class OMDelay
OMDelay::OMDelay(OxfTimeUnit aTime) {
    //#[ operation OMDelay(OxfTimeUnit)
    // Create the stop signal 
    stopSignal = OMOSFactory::instance()->createOMOSEventFlag();
    if (stopSignal != NULL) {
    	stopSignal->reset();
    }
    // Create the timeout event
    
    //lint -save -e826  (the pdest parameter is used to save OMDelay instance pointer)
    OMTimeout* timeout = new OMTimeout(reinterpret_cast<IOxfReactive*>(this), aTime, NULL);
    //lint -restore
    timeout->setDelayTimeout();
    // Delegating the request to timer
    OMTimerManager* sysTimer = OMTimerManager::instance();
    if (sysTimer != NULL) {	
    	(void) sysTimer->set(timeout); 
    	// while waiting - we should consider the thread as idle.
    	sysTimer->decNonIdleThreadCounter();
    }
    // stop and wait for this timeout
    
    #ifdef _OMINSTRUMENT
    // notify my stepper that I'm stopping
    AnimServices::notifyMutexLock(false);
    #endif
    
    // Actually stop
    if (stopSignal != NULL) {
    	stopSignal->wait();
    	if (sysTimer != NULL) {
    		sysTimer->incNonIdleThreadCounter();
    	}
    }
    
    #ifdef _OMINSTRUMENT
    // notify my stepper that I'm continuing
    AnimServices::notifyMutexLock(true);
    #endif
    //#]
}

//#[ ignore
/*

//#]
OMDelay::OMDelay(const OMDelay& delay) {
    //#[ operation OMDelay(OMDelay)
    //#]
}
//#[ ignore


*/
//#]

OMDelay::~OMDelay(void) {
    //#[ operation ~OMDelay()
    delete stopSignal;
    stopSignal = NULL;
    //#]
    cleanUpRelations();
}

void OMDelay::wakeup(void) {
    //#[ operation wakeup()
    if (stopSignal != NULL) {
    	stopSignal->signal();
    }
    //#]
}

//#[ ignore
/*

//#]
OMDelay& OMDelay::operator=(const OMDelay& delay) {
    //#[ operation operator=(OMDelay)
    //#]
}
//#[ ignore


*/
//#]

void OMDelay::cleanUpRelations(void) {
    if(stopSignal != NULL)
        {
            stopSignal = NULL;
        }
}




