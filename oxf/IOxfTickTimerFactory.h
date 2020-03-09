//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: IOxfTickTimerFactory
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


#ifndef IOxfTickTimerFactory_H
#define IOxfTickTimerFactory_H

//## dependency OMOSTimer
#include "os.h"
//## package Design::oxf::Services::Time::TimeAPI

//## class IOxfTickTimerFactory
// Low-level timer factory interface.
// Enable the user to plug-in its own tick-timers that are created by the implementation of the factory.
// The factory enables the user to replace the low-level timer without modifying the adapter timer implementation.
class RP_FRAMEWORK_DLL IOxfTickTimerFactory {
public :

    // A callback function signature that should be passed to the tick-timer to perform a tick action
    //#[ type TimerManagerCallBack
    typedef void (*TimerManagerCallBack)(void*);
    //#]
    
    ////    Constructors and destructors    ////
    
    // Virtual destructor to enable polymorphic deletion
    //## operation ~IOxfTickTimerFactory()
    inline virtual ~IOxfTickTimerFactory(void) {
        //#[ operation ~IOxfTickTimerFactory()
        //#]
    }
    
    ////    Operations    ////
    
    // create a real-time timer.
    // the timer should call the TimerManagerCallBack(callBackParams) every tickTime.
    // The method returns a handle to the timer, so it can be deleted when the timer manager is destroyed.
    // Argument OxfTimeUnit tickTime :
    // The timer resolution
    // Argument TimerManagerCallBack callBack :
    // The timer action callback
    // Argument void * callBackParams :
    // callback arguments
    //## operation createRealTimeTimer(OxfTimeUnit,TimerManagerCallBack,void *) const
    virtual OMOSTimer* createRealTimeTimer(OxfTimeUnit tickTime, TimerManagerCallBack callBack, void * callBackParams
) const = 0;
    
    // create a simulated-time timer.
    // the timer should call the TimerManagerCallBack(callBackParams) when the rest of the application is idle.
    // The method returns a handle to the timer, so it can be deleted when the timer manager is destroyed.
    // Argument TimerManagerCallBack callBack :
    // The timer action callback
    // Argument void * callBackParams :
    // callback arguments
    //## operation createSimulatedTimeTimer(TimerManagerCallBack,void *) const
    virtual OMOSTimer* createSimulatedTimeTimer(TimerManagerCallBack callBack, void * callBackParams) const = 0;
    
};

#endif



