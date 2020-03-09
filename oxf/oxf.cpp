//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: OXF
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
#include "oxf.h"
//## dependency AnimServices
//#[ ignore
#ifdef _OMINSTRUMENT
//#]
#include <aom/AnimServices.h>
//#[ ignore

#endif //_OMINSTRUMENT
//#]
//## dependency DllGuards
#include "OXFDllGuards.h"
//## dependency OMAnimHelper
#include "OMAnimHelper.h"
//## dependency OMDelay
#include "OMDelay.h"
//## dependency OMHandleCloser
#include "OMHandleCloser.h"
//## dependency OMMainThread
#include "OMMainThread.h"
//## dependency OMOS
#include "os.h"
//## dependency OMReactive
#include "omreactive.h"
//## dependency OMTimerManager
#include "OMTimerManager.h"
//## dependency OXFURefManager
#ifdef OM_NO_TEMPLATES_USAGE
#include "OXFURefManager.h"
#endif // OM_NO_TEMPLATES_USAGE
//## package Design::oxf::Services::Initialization

//## class OXF
OXF::frmThreadAffinities_t OXF::frmThreadAffinities = {0,0,0,0,0,0};

OXF::OXFNotifyEventMethod OXF::notifyEventCbkfunc = NULL;

OXF::OXFNotifyIdleMethod OXF::notifyIdleCbkfunc = NULL;

IOxfActive* OXF::theDefaultActiveClass = NULL;

IOxfMemoryAllocator* OXF::theMemoryManager = NULL;

IOxfTickTimerFactory* OXF::theTickTimerFactory = NULL;

bool OXF::theTickTimerFactoryWasSet = false;

void OXF::animDeregisterForeignThread(void * aomArg(theHandle)) {
    //#[ operation animDeregisterForeignThread(void *)
    #ifdef _OMINSTRUMENT
    AnimServices::deregisterForeignThread(theHandle);
    #endif
    //#]
}

void OXF::animRegisterForeignThread(const Rhp_const_char_pt aomArg(name), void * aomArg(theHandle)) {
    //#[ operation animRegisterForeignThread(Rhp_const_char_pt,void *)
    #ifdef _OMINSTRUMENT
    AnimServices::registerForeignThread(theHandle, name);
    #endif
    //#]
}

void OXF::cleanup(void) {
    //#[ operation cleanup()
    (void)OMThread::stopAllThreads(NULL);
    (void)OMThread::cleanupAllThreads();
    OXF::end();
    OMTimerManager::clearInstance();
    
    #ifdef _OMINSTRUMENT
    OMHandleCloser* tempHandle = OMHandleCloser::instance();
    if (tempHandle != NULL) {
    	AnimServices::deleteAomThread(tempHandle->getOmosThread());
    }
    AnimServices::cleanup();
    #endif
    //#]
}

void OXF::delay(OxfTimeUnit aTime) {
    //#[ operation delay(OxfTimeUnit)
    OMDelay d(aTime);
    //#]
}

void OXF::end(void) {
    //#[ operation end()
    #ifdef FRAMEWORK_DLL
    bool done=false;
    
    OXFRefLock aLock(theRefManager, false);
    if (theRefManager.Decrement() != 0) {
    	// Not the last reference so just return
    	done = true;
    } else {
    	// Last reference so do the necessary cleanup
    	theRefManager.setOxfStarted(false);
    }
    if ( !done ) 
    #endif 
    {
    	OMThread::setEndOfProcess(true);
    	
    	OxfTimeUnit tick = 0;
    	if(OMTimerManager::instance())
    	{
    		tick = OMTimerManager::instance()->getTick();
    	}
    	OXFTDelay(tick);
    	
    	OMOS::endProlog();
    	OMThread* currentThread = OMThread::cleanupAllThreads();
    	if (OMMainThread::instance(false) != NULL) {
    		static_cast<OMThread*>(OMMainThread::instance(false))->destroyThread();
    	}
    	if (currentThread != NULL) {
    		delete currentThread;
    	}
    }   
    theDefaultActiveClass = NULL;
    theMemoryManager = NULL;
    theTickTimerFactory = NULL;
    theTickTimerFactoryWasSet = false;
    notifyEventCbkfunc = NULL;
    notifyIdleCbkfunc = NULL;
    //#]
}

#ifdef _OMINSTRUMENT
bool OXF::initialize(const Rhp_int32_t aomArg(numProgArgs), Rhp_char_pt* aomArg(progArgs), const Rhp_uint32_t
 aomArg(defaultPort), const Rhp_const_char_pt aomArg(defaultHost), OxfTimeUnit ticktime, Rhp_uint32_t maxTM, bool
 isRealTimeModel) {
    //#[ operation initialize(Rhp_int32_t,Rhp_char_pt,Rhp_uint32_t,const Rhp_const_char_pt ,OxfTimeUnit,Rhp_uint32_t,bool)

    bool status = false;
    
    #ifdef FRAMEWORK_DLL
    // If framework is a DLL keep track of total no. of 
    // times OXFInit(...) is called
    OXFRefLock aLock(theRefManager, false);
    if (theRefManager.Increment() > 1) {
    	// Framework is already initialized so return
    	status = true;
    } else {
    #endif  // FRAMEWORK_DLL
    
    	// Currently we initialize the timer, which depends on OSFactory
    	// The OSfactory is initialized by the singleton mechanism.
    	// set the timer default parameter values
    	if (maxTM == 0U) {
    		maxTM = OMTimerManagerDefaults::defaultMaxTM;
    	}
    	if (ticktime == 0U) {
    		ticktime = OMTimerManagerDefaults::defaultTicktime;
    	}
    	
    	// create the timer
    	(void) OMTimerManager::initInstance(ticktime, maxTM, isRealTimeModel);
    
    	// disable the set of the timer factory
    	(void) setTheTickTimerFactory(NULL);
    
    #ifdef OM_ENABLE_MEMORY_MANAGER_SWITCH
    	// stop logging memory allocation
    	// and cleanup the memory manager switch data, if the switch was not done
    	OMMemoryManagerSwitchHelper::instance()->setUpdateState(false);
    	if (OMMemoryManager::getMemoryManager() == OMMemoryManager::getDefaultMemoryManager()) {
    		OMMemoryManagerSwitchHelper::instance()->cleanup();
    	}
    #endif // OM_ENABLE_MEMORY_MANAGER_SWITCH
    
    	// Initialize the animation (aomDispatcher (and in trace mode the tomDispatcher))
       	bool animInitialized = AnimServices::init(numProgArgs, progArgs, defaultPort, defaultHost, frmThreadAffinities.AnimMessageSender);
    	if (!animInitialized) {
    		OMTimerManager::instance()->clearInstance();
    		status = false;
    	} else {
    		AnimServices::registerAnimHelper(OMAnimHelper::instance());
    		// Ensure that the default thread has the correct OS thread id
    		// Required in some RTOS where the initialization of pre-main objects is -
    		//   done in another (system) context
    		AnimServices::resetDefaultThread(0, OMOSFactory::instance()->getCurrentThreadHandle());
    
    		// Create the main thread (actually its OXF wrapper)
    		(void)OMMainThread::instance();
    
    		// Make sure that the main thread is set properly
    		// This is required if the main thread is created in pre-main and the OS (e.g. VxWorks)
    		// initialize pre-main objects in another context (not the application main thread)
    		// Since the main thread is initialized as a wrapper thread, without reset of its thread
    		// the main thread OS handle can be wrong
    		OMOSThread* mainOsThread = OMMainThread::instance()->getOsThread();
    		if (mainOsThread != 0) {
    			void* currentThread = OMOSFactory::instance()->getCurrentThreadHandle();
    			mainOsThread->resetWrapperThreadOsHandle(currentThread);
    		}
    		// Ensure no left over registration candidate in callstack from pre main
    		AnimServices::resetCallStack(0);
    		
    		// Ensure main thread stops on first step (could be none if proxy not yet arrived).
    		AnimServices::notifyFirstStep(0);
    		
    		// os specific actions to be taken after the environment is set
    		#ifndef OM_POSTPONE_INIT_EPILOG_CALL
    		OMOS::initEpilog();
    		#endif
     		status = true;
     		}
    #ifdef FRAMEWORK_DLL
     	}
    #endif  // FRAMEWORK_DLL
    return status;
    //#]
}

#endif //  _OMINSTRUMENT


#ifndef _OMINSTRUMENT
bool OXF::initialize(OxfTimeUnit ticktime, Rhp_uint32_t maxTM, bool isRealTimeModel) {
    //#[ operation initialize(OxfTimeUnit,Rhp_uint32_t,bool)
    bool status = false;
    
    #ifdef FRAMEWORK_DLL
    // If framework is a DLL keep track of total no. of 
    // times OXFInit(...) is called
    OXFRefLock aLock(theRefManager, false);
    if (theRefManager.Increment() > 1) {
    	// Framework is already initialized so return
    	status = true;
    } else {
    #endif  // FRAMEWORK_DLL
    	// Currently we initialize the timer, which depends on OSFactory
    	// The OSfactory is initialized by the singleton mechanism.
    	// set the timer default parameter values
    	if (maxTM == 0U) {                   
    		maxTM = OMTimerManagerDefaults::defaultMaxTM;
    	}
    	if (ticktime == 0U) {
    		ticktime = OMTimerManagerDefaults::defaultTicktime;
    	}
    	// create the timer
    	(void) OMTimerManager::initInstance(ticktime, maxTM, isRealTimeModel);
    
    	// disable the set of the timer factory
    	(void) setTheTickTimerFactory(NULL);
    
    #ifdef OM_ENABLE_MEMORY_MANAGER_SWITCH
    	// stop logging memory allocation
    	// and cleanup the memory manager switch data, if the switch was not done
    	OMMemoryManagerSwitchHelper::instance()->setUpdateState(false);
    	if (OMMemoryManager::getMemoryManager() == OMMemoryManager::getDefaultMemoryManager()) {
    		OMMemoryManagerSwitchHelper::instance()->cleanup();
    	}
    #endif // OM_ENABLE_MEMORY_MANAGER_SWITCH
    
    	// Create the main thread (actually its OXF wrapper)
    	(void)OMMainThread::instance();
    
    	// os specific actions to be taken after the environment is set
    	#ifndef OM_POSTPONE_INIT_EPILOG_CALL
    	OMOS::initEpilog(); 
    	#endif
        status = true;
    #ifdef FRAMEWORK_DLL
        }
    #endif  // FRAMEWORK_DLL
    return status;
    //#]
}

#endif // _OMINSTRUMENT


bool OXF::setMemoryManager(IOxfMemoryAllocator* memoryManager) {
    //#[ operation setMemoryManager(IOxfMemoryAllocator)
    #ifdef FRAMEWORK_DLL
    // prevent access from several DLLs at the same time
    OXFRefLock aLock(theRefManager, false);
    #endif
    
    bool result = false;
    bool allowManagerSwitch = false;
    
    #ifdef OM_ENABLE_MEMORY_MANAGER_SWITCH
    // allow switch of memory manager even if its already set
    allowManagerSwitch = true;
    #endif // OM_ENABLE_MEMORY_MANAGER_SWITCH
    
    if ( (theMemoryManager == NULL) || (allowManagerSwitch) ) {	//lint !e774 (Boolean within 'right side of || within if' always evaluates to False)
    	theMemoryManager = memoryManager;
    	result = true;
    #ifdef _OMINSTRUMENT
    } else {
    	OM_NOTIFY_TO_ERROR("ERROR: Attempt to set the memory manager failed,\n\t the memory manager is already set, and the framework was compiled without OM_ENABLE_MEMORY_MANAGER_SWITCH.\n");
    #endif
    }
    
    return result;
    //#]
}

void OXF::setNotifyEventCbk(OXFNotifyEventMethod func) {
    //#[ operation setNotifyEventCbk(OXFNotifyEventMethod)
    notifyEventCbkfunc = func;
    //#]
}

void OXF::setNotifyIdleCbk(OXFNotifyIdleMethod func) {
    //#[ operation setNotifyIdleCbk(OXFNotifyIdleMethod)
    notifyIdleCbkfunc = func;
    //#]
}

bool OXF::setTheDefaultActiveClass(IOxfActive* anActive) {
    //#[ operation setTheDefaultActiveClass(IOxfActive)
    bool result = false; 
    
    #ifdef FRAMEWORK_DLL
    // prevent access from several DLLs at the same time
    OXFRefLock aLock(theRefManager, false);
    #endif
    
    if (theDefaultActiveClass == NULL) {
    	theDefaultActiveClass = anActive;
    	result = true;
    #ifdef _OMINSTRUMENT
    } else {
    	OM_NOTIFY_TO_ERROR("ERROR: Attempt to set the default active class failed\n\tthe efault active class already set.\n");
    #endif
    }
    return result;
    //#]
}

bool OXF::setTheTickTimerFactory(IOxfTickTimerFactory* theFactory) {
    //#[ operation setTheTickTimerFactory(IOxfTickTimerFactory)
    #ifdef FRAMEWORK_DLL
    // prevent access from several DLLs at the same time
    OXFRefLock aLock(theRefManager, false);
    #endif
    bool result = false;
    if (!theTickTimerFactoryWasSet) {
    	theTickTimerFactory = theFactory;
    	theTickTimerFactoryWasSet = true;
    	result = true;
    #ifdef _OMINSTRUMENT
    } else {
    	if (theFactory != NULL) {
    		OM_NOTIFY_TO_ERROR("ERROR: Attempt to set the timer factory failed.\n");
    	}
    #endif
    }
    return result;
    //#]
}

void OXF::start(bool doFork, const Rhp_int32_t callStck) {
    //#[ operation start(bool,Rhp_int32_t)
    
    #ifdef _OMINSTRUMENT
    AnimServices::notifyFrameworkStarted();
    #endif
    
    OMMainThread::setCallStackSize(callStck);
    #ifdef FRAMEWORK_DLL
    bool doStart=true;  
    //Note: No special handling in case of OXF::start(false) 
    //as this will block the main thread
    if (doFork) {
    	if (!theRefManager.getOxfStarted()) {
    		OXFRefLock aLock(theRefManager, false);
    		if (!theRefManager.getOxfStarted()) {
    			theRefManager.setOxfStarted(true);
    			OMMainThread::instance()->startDispatching(true);
    		}
    		doStart = false;
    	}
    }
    if ( doStart) 
    #endif // FRAMEWORK_DLL
                     
    {                 
    	// Calling the main event dispatching loop
    	OMMainThread::instance()->startDispatching(doFork);
    	// Note the Instrumentation threads have already been started
    	// in OXF::init() or earlier (see AOMDispatcher::instance()
    }
    #ifdef OM_POSTPONE_INIT_EPILOG_CALL
    OMOS::initEpilog();
    #endif
    //#]
}

void OXF::supportExplicitReactiveDeletion(void) {
    //#[ operation supportExplicitReactiveDeletion()
    OMReactive::setGlobalSupportDirectDeletion(true);
    //#]
}

IOxfActive* OXF::getTheDefaultActiveClass(void) {
    return theDefaultActiveClass;
}

IOxfMemoryAllocator* OXF::getMemoryManager(void) {
    return theMemoryManager;
}

IOxfTickTimerFactory* OXF::getTheTickTimerFactory(void) {
    return theTickTimerFactory;
}




