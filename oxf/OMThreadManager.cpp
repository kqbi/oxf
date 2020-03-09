//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: OMThreadManager
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
#include "OMThreadManager.h"
//## dependency AnimServices
//#[ ignore
#ifdef _OMINSTRUMENT   
/* Include only used for animation */ 
/*LDRA_INSPECTED 4 Q */
//#]
#include <aom/AnimServices.h>
//#[ ignore

#endif //_OMINSTRUMENT
//#]
//## auto_generated
#include "IOxfActive.h"
//## dependency OMCore
#include "OMCore.h"
//## dependency OMEvent
#include "OMEvent.h"
//## dependency OMThread
#include "omthread.h"
//## dependency OMUResourceGuard
#ifdef OM_NO_TEMPLATES_USAGE
#include "OMUResourceGuard.h"
#endif // OM_NO_TEMPLATES_USAGE

//## dependency TopLevel
#include "OXFEvents.h"
//## package Design::oxf::Services::ResourceManagement

//## class OMThreadManager
OMThreadManager::coreList_t OMThreadManager::coreList;

OMThreadManager::OMThreadManager(void) {
    //#[ operation OMThreadManager()
    #ifdef _OMINSTRUMENT
    AnimServices::registerAnimThreadManager(this);
    #endif // _OMINSTRUMENT
    //#]
}

OMThreadManager::~OMThreadManager(void) {
    //#[ operation ~OMThreadManager()
    for (OMAffinity_t coreId = 0; coreList.getCount() > 0; coreId++)
    {
    	#ifdef OM_NO_TEMPLATES_USAGE
    	const void* key =  reinterpret_cast<const void*>(coreId);
    	OMCore* core = reinterpret_cast<OMCore*>(coreList.getKey(key));
    	#else
    	OMCore* core = coreList.getKey(coreId);
    	#endif
    	if (core) {
    		delete core;
    		#ifdef OM_NO_TEMPLATES_USAGE
    		coreList.remove(key);
    		#else
    		coreList.remove(coreId);
    		#endif		
    	}            
    }
    coreList.removeAll();
    
    //#]
}

OMThreadManager& OMThreadManager::instance(void) {
    //#[ operation instance()
    static OMThreadManager theManager;
    return theManager;
    //#]
}

//#[ ignore
/*LDRA_INSPECTED 62 D : Can't make argument const */  

//#]
void OMThreadManager::deregisterThread(OMThread* aThread) {
    //#[ operation deregisterThread(OMThread)
    #ifndef OM_NO_APPLICATION_TERMINATION_SUPPORT
    GUARD_OPERATION
    removeThreads(aThread);
    #endif // !OM_NO_APPLICATION_TERMINATION_SUPPORT
    //#]
}

//#[ ignore
/*LDRA_INSPECTED 62 D : Can't make argument const */  

//#]
void OMThreadManager::registerThread(OMThread* aThread) {
    //#[ operation registerThread(OMThread)
    #ifndef OM_NO_APPLICATION_TERMINATION_SUPPORT
    GUARD_OPERATION
    if (findThreads(aThread) == 0) {
    	addThreads(aThread);
    }
    #endif // !OM_NO_APPLICATION_TERMINATION_SUPPORT
    //#]
}

OMThread* OMThreadManager::cleanupAllThreads(void) {
    //#[ operation cleanupAllThreads()
    OMThread::setEndOfProcess( true );
    OMThread* currentThread = NULL; 
    
    #ifdef _OMINSTRUMENT
    AnimServices::notifyEndApplication(false);
    #endif // _OMINSTRUMENT
    
    while ( !threads.isEmpty() ) {
    	// remove the first thread from the list
    
    #ifdef OM_NO_TEMPLATES_USAGE
    	OMThread* aThread = reinterpret_cast<OMThread*>(threads.getAt(0));
    #else
    	OMThread* aThread = threads.getAt(0);
    #endif // OM_NO_TEMPLATES_USAGE                              
    
    	threads.removeFirst();
    	// perform the cleanup
    	deregisterThread(aThread);
    	if ( (aThread->allowDeleteInThreadsCleanup() ) &&
    		 (aThread != OMMainThread::instance(false)) ) {
    		// not the main thread and not a thread that should not be deleted
    		/*LDRA_INSPECTED 560 S : OMOSFactory is a singleton of the framework*/
    		if (aThread->getOsHandle() != OMOSFactory::instance()->getCurrentThreadHandle() ) {
    			// destroy
    			aThread->destroyThread();
    		} else {
    			// the current thread - skip
    			currentThread = aThread;
    		}
    	}
    }
    /*LDRA_INSPECTED 71 S  :  This seems to be an LDRA bug */
    return currentThread;
    //#]
}

OMThread* OMThreadManager::stopAllThreads(const OMThread* skipme) const {
    //#[ operation stopAllThreads(OMThread) const
    OMThread::setEndOfProcess( true );
    OMThread* currentThread = NULL;
    OMThread* mainT = OMMainThread::instance(false);
    
    #ifdef _OMINSTRUMENT
    AnimServices::notifyEndApplication(false);
    #endif // _OMINSTRUMENT
    
    // First we need to stop all the registered OMThreads 
    // and then stop the OMMainThread
    OMThreadType threadListCopy(threads);
    /*LDRA_INSPECTED 70 D : Variable iter.thePos is ok */
    OMThreadIter threadIter(threadListCopy);
    OMListType osthreadList;
    
    // build OS handle list
    while (*threadIter != NULL) {
    #ifdef OM_NO_TEMPLATES_USAGE
    	OMThread* aThread = reinterpret_cast<OMThread*>(*threadIter);
    #else	
    	OMThread* aThread = *threadIter;
    #endif // OM_NO_TEMPLATES_USAGE                              
    
    	if ( (aThread->allowDeleteInThreadsCleanup()) &&
    		 (aThread != mainT) &&
    		 (aThread != skipme) ) {
    		// add the os thread to the list
    		void* osHandle = NULL;
    		(void) aThread->getOsHandle(osHandle);
    		osthreadList.add(osHandle);
    	
    		if ( aThread->getOsHandle() != OMOSFactory::instance()->getCurrentThreadHandle() ) {
    			// send termination event to stop the thread gracefully
    			aThread->endDispatching();
    		} else {
    			// this is the context thread
    			currentThread = aThread;
    		}
    	}
    	++threadIter;
    }
    
    /*LDRA_INSPECTED 70 D : Variable iter.thePos is ok */
    OMThreadVoidIter osThreadIter(osthreadList);
    while (*osThreadIter != NULL) {
    	// wait for the os threads to terminate
    	const Rhp_int32_t THREAD_DEFAULT_TIMEOUT = 1000;
    	(void) OMOSFactory::instance()->waitOnThread(*osThreadIter, THREAD_DEFAULT_TIMEOUT);
    	++osThreadIter;
    }
    // Stop the main thread
    if ( (mainT != NULL) &&
    	 (mainT != currentThread) &&
    	 (mainT != skipme) ) {
    	void* osHandle = NULL;
    	(void) mainT->getOsHandle(osHandle);
    	mainT->endDispatching();
    	const Rhp_int32_t THREAD_DEFAULT_TIMEOUT = 1000;
    	(void) OMOSFactory::instance()->waitOnThread(osHandle, THREAD_DEFAULT_TIMEOUT);
    }
    return currentThread;
    //#]
}

//#[ ignore
/*LDRA_INSPECTED 62 D : Can't make argument const */  

//#]
void OMThreadManager::wakeup(IOxfActive* aThread) const {
    //#[ operation wakeup(IOxfActive) const
    // create & initialize a static wakeup token
    static OMEvent animWakeupEv(OMAnimWakeupEventId, 0);
    static bool initialized = false;
    
    if (!initialized) {
    	initialized = true;
    /*LDRA_INSPECTED 69 D : event is static and is initialized */
    	animWakeupEv.setFrameworkEvent(true);
    /*LDRA_INSPECTED 69 D : event is static and is initialized */
    	animWakeupEv.setDeleteAfterConsume(false);
    }
    
    if (aThread != NULL) {
    	OMOSEventGenerationParams params(false);
    	(void) aThread->queue(&animWakeupEv, params);
    }
    //#]
}

OMThreadIter OMThreadManager::getThreads(void) const {
    //#[ operation getThreads() const
    OMThreadIter iter(threads);
    return iter;
    //#]
}

//#[ ignore
/*LDRA_INSPECTED 62 D : Can't make argument const */  

//#]
void OMThreadManager::removeThreads(OMThread* aThread) {
    //#[ operation removeThreads(OMThread)
    threads.remove(aThread);
    //#]
}

void OMThreadManager::clearThreads(void) {
    //#[ operation clearThreads()
    threads.removeAll();
    //#]
}

//#[ ignore
/*LDRA_INSPECTED 62 D : Can't make argument const */  

//#]
void OMThreadManager::addThreads(OMThread* aThread) {
    //#[ operation addThreads(OMThread)
    threads.add(aThread);
    //#]
}

//#[ ignore
/*LDRA_INSPECTED 62 D : Can't make argument const */  

//#]
Rhp_int32_t OMThreadManager::findThreads(OMThread* aThread) const {
    //#[ operation findThreads(OMThread) const
    return threads.find(aThread);
    //#]
}

void OMThreadManager::addToCoreList(const OMAffinity_t coreId, OMCore* newCore) {
    //#[ operation addToCoreList(OMAffinity_t,OMCore*)
    #ifdef OM_NO_TEMPLATES_USAGE
    void* key =  reinterpret_cast<void*>(coreId);
    coreList.add(key,newCore);
    #else
    coreList.add(coreId,newCore);
    #endif
    //#]
}

OMCore* OMThreadManager::getExistingCore(const OMAffinity_t coreId) {
    //#[ operation getExistingCore(OMAffinity_t)
    #ifdef OM_NO_TEMPLATES_USAGE
    void* key =  reinterpret_cast<void*>(coreId);
    return reinterpret_cast<OMCore*>(coreList.getKey(key));
    #else
    return coreList.getKey(coreId);
    #endif
    //#]
}

OMThreadManager::coreList_t* OMThreadManager::getCoreList(void) {
    //#[ operation getCoreList()
    return &coreList;
    //#]
}




