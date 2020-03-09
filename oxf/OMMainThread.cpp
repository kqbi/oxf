//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: OMMainThread
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
#include "OMMainThread.h"
//## dependency AnimServices
//#[ ignore
#ifdef _OMINSTRUMENT
//#]
#include <aom/AnimServices.h>
//#[ ignore

#endif //_OMINSTRUMENT
//#]
//## auto_generated
#include "OXFGuardMacros.h"
//## auto_generated
#include "IOxfTimeout.h"
//## auto_generated
#include "OMCore.h"
//## auto_generated
#include "OMEvent.h"
//## auto_generated
#include "os.h"
//## auto_generated
#include "OMOSEventGenerationParams.h"
//## auto_generated
#include "omreactive.h"
//## auto_generated
#include "OMThreadManager.h"
//## auto_generated
#include "OMTimeout.h"
//## auto_generated
#include "OMTimerManager.h"
//## dependency OXF
#include "oxf.h"
//## package Design::oxf::Services::Initialization

//## class OMMainThread
Rhp_int32_t OMMainThread::callStck(OMOSThread::DefaultStackSize);

OMMainThread::OMMainThread(void) : OMThread(true) /* create a wrapper thread */ {
    //#[ operation OMMainThread()
    #ifdef _OMINSTRUMENT
    AnimServices::setThreadName(getOsHandle(), "mainThread");
    #endif
    
    //#]
}

OMMainThread::~OMMainThread(void) {
    //#[ operation ~OMMainThread()
    /* assuming the thread will not be re-created, nothing to do */
    //#]
}

OMThread* OMMainThread::instance(bool create) {
    //#[ operation instance(bool)
    IOxfActive* defaultActive = OXF::getTheDefaultActiveClass();
    if ( (defaultActive == NULL) && create ) {
    	defaultActive = getInstance();
    	(void) OXF::setTheDefaultActiveClass(defaultActive);
    	OMMainThread* main = static_cast<OMMainThread*>(defaultActive);
        if (main != NULL)
        {   
    		// assure main thread is initialized
    		main->assureInit();
    
    	    // multicore support
    		if (OXF::frmThreadAffinities.MainThread != 0U) 
    		{
        		main->assignCoreId(OXF::frmThreadAffinities.MainThread);
        	}
    	}
    }
    return static_cast<OMThread*>(defaultActive);
    //#]
}

void OMMainThread::startDispatching(bool doFork) {
    //#[ operation startDispatching(bool)
    if (!doFork) {
    	// The main thread simply grabs the control from the system
    	(void)OMMainThread::execute();
    } 
    else 
    {
    	// the default active class is running on its own thread
    	OMOSThread* oldWrapperThread = OMThread::getOsThread();
    	// Creating a thread of control
    	OMOSThread* newThread = OMOSFactory::instance()->createOMOSThread(OMThread::doExecute, this, "mainThread",callStck);
    	OMThread::setOsThread(newThread);
    
    	if (OXF::frmThreadAffinities.MainThread != 0U) 
    	{   // multicore support
    		newThread->setAffinity(OXF::frmThreadAffinities.MainThread);
    	}
    
    #ifdef _OMINSTRUMENT
    	AnimServices::switchOSThread(oldWrapperThread->getOsHandle(), getOsHandle());
    #endif
    	// delete the OSAL wrapper on the system main thread.
    	delete oldWrapperThread;
    	// start the event loop on the new thread
    	if (OMThread::getOsThread() != NULL) {
    		OMThread::getOsThread()->start();
    	}
    }
    //#]
}

void OMMainThread::assureInit(void) {
    //#[ operation assureInit()
    //since the MainThread is a static instance, if the user wants to restart the framework
    //we need to reinitialize the MainThread
    if(getOsThread() == NULL && OMThreadManager::instance().findThreads(this) == 0 && getDispatching() == false)
    {
    	reInitializeOMThread(true);
    
    #ifdef _OMINSTRUMENT
        AnimServices::setThreadName(getOsHandle(), "mainThread");
    #endif
    }
    //#]
}

OMMainThread* OMMainThread::getInstance(void) {
    //#[ operation getInstance()
    static OMMainThread theMainThread;
    return &theMainThread;
    //#]
}

void OMMainThread::setCallStackSize(Rhp_int32_t p_callStck) {
    callStck = p_callStck;
}




