//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: OMHandleCloser
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
#include "OMHandleCloser.h"
//## dependency AnimServices
//#[ ignore
#ifdef _OMINSTRUMENT
//#]
#include <aom/AnimServices.h>
//#[ ignore

#endif //_OMINSTRUMENT
//#]
//## dependency Events
#include "OXFEvents.h"
//## dependency IOxfActive
#include "IOxfActive.h"
//## dependency IOxfEvent
#include "IOxfEvent.h"
//## auto_generated
#include "OXFNotifyMacros.h"
//## auto_generated
#include "OMAnimReactive.h"
//## auto_generated
#include "state.h"
//## auto_generated
#include "OMMainThread.h"
//## auto_generated
#include "os.h"
//## dependency OMProtected
#include "omprotected.h"
//## dependency OMThreadManager
#include "OMThreadManager.h"
//## auto_generated
#include "OMTimeout.h"
//## auto_generated
#include "OMTimerManager.h"
//## auto_generated
#include "oxf.h"
//## package Design::oxf::Services::ResourceManagement

//## class OMHandleCloser

//#[ ignore
#ifdef OM_REUSABLE_STATECHART_IMPLEMENTATION
#undef OM_REUSABLE_STATECHART_IMPLEMENTATION
#endif // OM_REUSABLE_STATECHART_IMPLEMENTATION
//#]


bool OMHandleCloser::_singletonDestroyed = false;

OMHandleCloser::OMHandleCloser(OMHandleCloser::closeHandleFunc doCloseHandlePtr) : OMReactive(), 
doCloseHandle(doCloseHandlePtr), thread("_omCloseHandle", OMOSThread::DefaultThreadPriority, 
OMOSThread::DefaultStackSize, OMOSThread::DefaultMessageQueueSize, true) {
    initStatechart();
    //#[ operation OMHandleCloser(closeHandleFunc)
    OMReactive::setActiveContext(&thread, true);
    thread.setDeletionAllowed(false);
    if (OXF::frmThreadAffinities.HandleCloser != 0U)
    {
    	 thread.assignCoreId(OXF::frmThreadAffinities.HandleCloser);
    }
    #ifdef _OMINSTRUMENT
    omosThread = thread.getOsHandle();
    AnimServices::setThreadName(omosThread, "_omCloseHandle");
    #endif
    //#]
}

OMHandleCloser::~OMHandleCloser(void) {
    //#[ operation ~OMHandleCloser()
    // this class dies only at the end of the process since it is a singleton
    #ifdef _OMINSTRUMENT
    AnimServices::notifyEndApplication(false);
    #endif // _OMINSTRUMENT
    
    OMThread::setEndOfProcess( true );
    _singletonDestroyed = true;
    //#]
}

void OMHandleCloser::genCloseEvent(void * hObject) {
    //#[ operation genCloseEvent(void *)
    if (!_singletonDestroyed) {
    	OMEvent * closeHandle = new OMCloseHandleEvent(hObject);
    	closeHandle->setFrameworkEvent(true);
    	(void) send(closeHandle);
    }
    //#]
}

OMThread* OMHandleCloser::getThread(void) const {
    //#[ operation getThread() const
    return const_cast<OMThread*>(&thread);
    //#]
}

OMHandleCloser* OMHandleCloser::instance(void) {
    //#[ operation instance()
    OMHandleCloser* theHandleCloser = &getInstance(NULL); 
    if (theHandleCloser->doCloseHandle == NULL) {
    	theHandleCloser = NULL;
    }
    return theHandleCloser;
    //#]
}

OMHandleCloser* OMHandleCloser::instance(OMHandleCloser::closeHandleFunc doCloseHandlePtr) {
    //#[ operation instance(closeHandleFunc)
    OMHandleCloser* theHandleCloser = &getInstance(doCloseHandlePtr);
    if(theHandleCloser)
    	theHandleCloser->assureInit();
    return theHandleCloser;
    //#]
}

void OMHandleCloser::sendCloseHandleCloserEvent(void) {
    //#[ operation sendCloseHandleCloserEvent()
    if (!_singletonDestroyed) {
    	thread.endDispatching();
    }
    //#]
}

bool OMHandleCloser::startBehavior(void) {
    //#[ operation startBehavior()
    bool done = OMReactive::startBehavior();
    if (done) {
        thread.startDispatching();
    }
    return done;
    //#]
}

void OMHandleCloser::assureInit(void) {
    //#[ operation assureInit()
    if(thread.getOsThread() == NULL && OMThreadManager::instance().findThreads(&thread) == 0 && thread.getDispatching() == false)
    {
    	thread.reInitializeOMThread(false,"_omCloseHandle");
    
    	thread.setDeletionAllowed(false);
    	if (OXF::frmThreadAffinities.HandleCloser != 0U)
    	{
        	thread.assignCoreId(OXF::frmThreadAffinities.HandleCloser);
    	}
    #ifdef _OMINSTRUMENT
    	AnimServices::setThreadName(thread.getOsHandle(), "_omCloseHandle");
    #endif
    }
    //#]
}

OMHandleCloser & OMHandleCloser::getInstance(OMHandleCloser::closeHandleFunc doCloseHandlePtr) {
    //#[ operation getInstance(closeHandleFunc)
    static OMHandleCloser theHandleCloser(doCloseHandlePtr);
    return theHandleCloser;
    //#]
}

//#[ ignore
/*

//#]
OMHandleCloser& OMHandleCloser::operator=(const OMHandleCloser& other) {
    //#[ operation operator=(OMHandleCloser)
    return (*this);
    //#]
}
//#[ ignore


*/
//#]

void OMHandleCloser::initStatechart(void) {
    rootState_subState = OMNonState;
    rootState_active = OMNonState;
}

void OMHandleCloser::rootState_entDef(void) {
    {
        rootState_subState = ready;
        rootState_active = ready;
    }
}

IOxfReactive::TakeEventStatus OMHandleCloser::rootState_processEvent(void) {
    IOxfReactive::TakeEventStatus res = eventNotConsumed;
    // State ready
    if(rootState_active == ready)
        {
            if(IS_EVENT_TYPE_OF(OMCloseHandleEvent_Events_Services_oxf_Design_id) == 1)
                {
                    OMSETPARAMS(OMCloseHandleEvent);
                    //## transition 1 
                    if(doCloseHandle)
                        {
                            //#[ transition 1 
                            
                            (*doCloseHandle)(params->handle);
                            //#]
                            rootState_subState = ready;
                            rootState_active = ready;
                            res = eventConsumed;
                        }
                }
            
        }
    return res;
}




