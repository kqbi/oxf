//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: OMThread
//!	File name		: $Source$
//!	File version	: $Revision$
//
//!	Date changed	: $Date$
//!	Last change by	: $Author$
//
//	Licensed Materials - Property of IBM
//	(c) Copyright IBM Corporation 2004, 2017. All Rights Reserved.
//	
//	Note to U.S. Government Users Restricted Rights:  
//	Use, duplication or disclosure restricted by GSA ADP Schedule 
//	Contract with IBM Corp.



//## auto_generated
#include "omthread.h"
//## dependency AnimServices
//#[ ignore
#ifdef _OMINSTRUMENT
//#]
#include <aom/AnimServices.h>
//#[ ignore

#endif //_OMINSTRUMENT
//#]
//## dependency GuardMacros
#include "OXFGuardMacros.h"
//## dependency IOxfTimeout
#include "IOxfTimeout.h"
//## dependency OMCore
#include "OMCore.h"
//## dependency OMEvent
#include "OMEvent.h"
//## dependency OMMainThread
#include "OMMainThread.h"
//## dependency OMOS
#include "os.h"
//## dependency OMOSEventGenerationParams
#include "OMOSEventGenerationParams.h"
//## dependency OMReactive
#include "omreactive.h"
//## dependency OMThreadManager
#include "OMThreadManager.h"
//## dependency OMTimeout
#include "OMTimeout.h"
//## dependency OMTimerManager
#include "OMTimerManager.h"
// for the compatibility mode
//## dependency OXF
#include "oxf.h"
//## package Design::oxf::Core::CoreImplementation

//## class OMThread
bool OMThread::endOfProcess = false;

OMThread::OMThread(const Rhp_const_char_pt name, const Rhp_int32_t priority, const Rhp_int32_t stackSize
, const Rhp_int32_t messageQueueSize, bool dynamicMessageQueue) : deletionAllowed(true), toGuardThread(false), 
processing(true), dispatching(true), finalTermination(false) {
    //#[ operation OMThread(Rhp_const_char_pt,Rhp_int32_t,Rhp_int32_t,Rhp_int32_t,bool)
    _initializeOMThread(false, name, stackSize, messageQueueSize, dynamicMessageQueue);
    setPriority(priority);
    //#]
}

OMThread::OMThread(bool wrapThread) : deletionAllowed(true), toGuardThread(false), processing(true), 
dispatching(true), finalTermination(false) {
    //#[ operation OMThread(bool)
    _initializeOMThread(wrapThread);
    //#]
}

OMThread::OMThread(const OMAffinity_t coreid, const OMPowerMode_t pwrMode, const Rhp_const_char_pt name
, const Rhp_int32_t priority, const Rhp_int32_t stackSize, const Rhp_int32_t messageQueueSize, bool dynamicMessageQueue
) : deletionAllowed(true), toGuardThread(false), processing(true), dispatching(true), finalTermination(false) {
    //#[ operation OMThread(OMAffinity_t,OMPowerMode_t,Rhp_const_char_pt,Rhp_int32_t,Rhp_int32_t,Rhp_int32_t,bool)
    _initializeOMThread(false, name, stackSize, messageQueueSize, dynamicMessageQueue);
    assignCoreId(coreid);
    #ifdef _OMINSTRUMENT
    AnimServices::notifyCoreAllocation(this,static_cast<int>(coreid),pwrMode);
    #endif //_OMINSTRUMENT
    if (osThread)
    {
    	osThread->setPwrState(pwrMode);
    }
    setPriority(priority);
    //#]
}

OMThread::~OMThread(void) {
    //#[ operation ~OMThread()
    _cleanupThread();
    //#]
    cleanUpRelations();
}

bool OMThread::allowDeleteInThreadsCleanup(void) {
    //#[ operation allowDeleteInThreadsCleanup()
    return deletionAllowed;
    //#]
}

//#[ ignore
#ifndef OM_DISABLE_DIRECT_REACTIVE_DELETION

//#]
void OMThread::cancelEvent(OMEvent* ev) {
    //#[ operation cancelEvent(OMEvent)
    IOxfEvent* e = ev;
    cancelPendingEvent(e);
    //#]
}
//#[ ignore


#endif //!OM_DISABLE_DIRECT_REACTIVE_DELETION
//#]

//#[ ignore
#ifndef OM_DISABLE_DIRECT_REACTIVE_DELETION

//#]
void OMThread::cancelEvents(OMReactive* destination) {
    //#[ operation cancelEvents(OMReactive)
    IOxfReactive* dest = destination;
    cancelPendingEvents(dest);
    //#]
}
//#[ ignore


#endif //!OM_DISABLE_DIRECT_REACTIVE_DELETION
//#]

//#[ ignore
#ifndef OM_DISABLE_DIRECT_REACTIVE_DELETION

//#]
void OMThread::cancelPendingEvent(IOxfEvent* ev) {
    //#[ operation cancelPendingEvent(IOxfEvent)
    #ifdef _OMINSTRUMENT
    // notify the user of this cancellation
    AnimServices::notifyEventCancelled(getOsHandle(), ev);
    #endif
    // cancel an event means marking it as cancelled
    ev->setId(OMCancelledEventId);
    //#]
}
//#[ ignore


#endif //!OM_DISABLE_DIRECT_REACTIVE_DELETION
//#]

//#[ ignore
#ifndef OM_DISABLE_DIRECT_REACTIVE_DELETION

//#]
void OMThread::cancelPendingEvents(const IOxfReactive* destination) {
    //#[ operation cancelPendingEvents(IOxfReactive)
    // cancel existing events that are targeted to destination
    // NOTE: There is not explicit care for making the following code guarded,
    // so based on the underlying implementation of eventQueue,
    // messageList may not reflect the most updated content of the eventQueue
    OMEventListType messageList;
    eventQueue.getMessageList(messageList); // not guarded
    
    OMEventQueueIter iter(messageList);
    for ( ; (*iter) != 0; ++iter) {
    	IOxfEvent* ev = static_cast<IOxfEvent*>(*iter);
    	if (ev->getDestination() == destination) {
    		cancelPendingEvent(ev);
    	}
    }
    //#]
}
//#[ ignore


#endif //!OM_DISABLE_DIRECT_REACTIVE_DELETION
//#]

OMThread* OMThread::cleanupAllThreads(void) {
    //#[ operation cleanupAllThreads()
    return OMThreadManager::instance().cleanupAllThreads();
    //#]
}

void OMThread::destroyThread(void) {
    //#[ operation destroyThread()
    if (deletionAllowed) {
    	delete this;
    } else {
    	_cleanupThread();
    }
    //#]
}

void OMThread::endDispatching(void) {
    //#[ operation endDispatching()
    // stop dispatching of events
    dispatching = false;
    // the dummy event will wakeup thread if it is waiting on the queue
    OMOSEventGenerationParams p;
    (void)queue(&endThreadEvent, p);
    if (getOsHandle() != OMOSFactory::instance()->getCurrentThreadHandle() )
    	OMOSFactory::instance()->delayCurrentThread(1); // switch context to another thread   
    
    //#]
}

const OMEventQueue* OMThread::getEventQueue(void) const {
    //#[ operation getEventQueue() const
    // return the queue
    return &eventQueue;
    //#]
}

const OMProtected& OMThread::getGuard(void) const {
    //#[ operation getGuard() const
    return dispatchingGuard;
    //#]
}

void OMThread::getOSThreadEndClb(OMOSThread::EndCallBack* clb_p, void ** arg1_p, bool onExecuteThread) const {
    //#[ operation getOSThreadEndClb(EndCallBack,void *,bool) const
    // propagate the request to the object representing the real os thread
    if (osThread != NULL) {
    	osThread->getThreadEndClbk(clb_p,arg1_p,onExecuteThread);
    }
    //#]
}

void * OMThread::getOsHandle(void) const {
    //#[ operation getOsHandle() const
    void* OsHandle;
    
    if (osThread != NULL) {
    	OsHandle = osThread->getOsHandle();
    } else {
    	OsHandle = NULL;
    }
    return OsHandle;
    //#]
}

void * OMThread::getOsHandle(void *& osHandle) const {
    //#[ operation getOsHandle(void *) const
    void* OsHandle = NULL;
    if (osThread != NULL) {
    	OsHandle = osThread->getOsHandle(osHandle);
    }
    return OsHandle;
    //#]
}

bool OMThread::isEndOfProcess(void) {
    //#[ operation isEndOfProcess()
    return endOfProcess;
    //#]
}

void OMThread::lock(void) const {
    //#[ operation lock() const
    dispatchingGuard.lock();
    //#]
}

bool OMThread::queue(IOxfEvent* ev, const IOxfEventGenerationParams& params) {
    //#[ operation queue(IOxfEvent,IOxfEventGenerationParams)
    if(ev && !ev->isFrameworkEvent())
    	OXF::notifyEvent();
    
    #ifdef _OMINSTRUMENT
    bool shouldNotify = ((!OMThread::endOfProcess)&&(!params.getFromISR()));
    if (shouldNotify) {
    	AnimServices::notifyEventPutBegin(getOsHandle(), ev, eventQueue.isFull());
    }
    #endif // _OMINSTRUMENT
    
    // queue the event
    bool res = eventQueue.putMessage(ev, params);
    
    #ifdef _OMINSTRUMENT
    if (shouldNotify) {
    	AnimServices::notifyEventPutEnd(getOsHandle(), ev, res);
    }
    #endif // _OMINSTRUMENT
    
    return res;
    //#]
}

void OMThread::resume(void) {
    //#[ operation resume()
    osThread->resume();
    //#]
}

void OMThread::setEndOfProcess(bool aState) {
    //#[ operation setEndOfProcess(bool)
    OMThread::endOfProcess = aState;
    //#]
}

void OMThread::setPriority(const Rhp_int32_t pr) {
    //#[ operation setPriority(Rhp_int32_t)
    if (osThread != NULL) {
    	osThread->setPriority(pr);
    }
    //#]
}

void OMThread::start(const Rhp_int32_t doFork) {
    //#[ operation start(Rhp_int32_t)
    bool fork = (doFork != 0);
    startDispatching(fork);
    //#]
}

void OMThread::startDispatching(bool /**/) {
    //#[ operation startDispatching(bool)
    if (osThread != NULL) {
    	osThread->start();
    }
    //#]
}

OMThread* OMThread::stopAllThreads(const OMThread* skipme) {
    //#[ operation stopAllThreads(OMThread)
    return OMThreadManager::instance().stopAllThreads(skipme);
    //#]
}

void OMThread::suspend(void) {
    //#[ operation suspend()
    if (osThread != NULL) {
    	osThread->suspend();
    }
    //#]
}

void OMThread::unlock(void) const {
    //#[ operation unlock() const
    dispatchingGuard.unlock();
    //#]
}

void OMThread::cleanupThread(void) {
    //#[ operation cleanupThread()
    _cleanupThread();
    //#]
}

IOxfReactive::TakeEventStatus OMThread::dispatch(IOxfEvent* ev) {
    //#[ operation dispatch(IOxfEvent)
    IOxfReactive::TakeEventStatus result = IOxfReactive::eventNotConsumed;
    bool destroyEvent = true;
    if (shouldDispatch(ev)) {
    	// do not try to destroy the reactive termination event
    	// since it is part of the reactive object that performs 
    	// self destruction
    	destroyEvent = !isControlEvent(ev);
    	
    	IOxfReactive* dest = ev->getDestination();
    	if (dest != NULL) {
    		result = dest->handleEvent(ev);
    	}
    }
    if (destroyEvent) {
    	ev->destroy();
    }
    return result;
    //#]
}

void OMThread::doExecute(void * me) {
    //#[ operation doExecute(void *)
    // Now do some real work
    OMThread* theThread = static_cast<OMThread*>(me);
    // start the event loop
    (void) theThread->execute();
    // the event loop ends
    OMOSThread::EndCallBack theOSThreadEnderClb;
    OMOSHandle* arg1 = NULL;
    // get a callback to end the thread
    theThread->getOSThreadEndClb(&theOSThreadEnderClb,(void**)&arg1);
    // save handle value before theThread will be destroyed
    OMOSHandle argValue = *arg1;
    theThread->setEndOSThreadInDtor(false);
    
    // do not really end the os thread because we 
    // are executing on this thread and if do
    // we are going to leak resources
    theThread->destroyThread();
    
    if (theOSThreadEnderClb != NULL) {
    	// now end the os thread
    	(*theOSThreadEnderClb)(argValue);
    }
    //#]
}

OMReactive* OMThread::execute(void) {
    //#[ operation execute()
    OMTimerManager* sysTimer = OMTimerManager::instance();
    
    #ifdef _OMINSTRUMENT
    AnimServices::resetCallStack(getOsHandle());
    #endif
    
    while (processing) {
    	if (sysTimer != NULL) {
    		sysTimer->incNonIdleThreadCounter();
    	}
    #ifdef _OMINSTRUMENT
    	bool shouldNotify = true; // Ensure we do not report again
    	// after "dummy" or cancelled events
    #endif
    	
    	bool bShouldNotifyIdle = false;
    	bool thereAreEventsToConsume = true;
    	while (thereAreEventsToConsume) {
    		// process all the events in the queue
    		
    #ifdef _OMINSTRUMENT
    		// store the shouldNotify in order to reset it in case of anim wakeup event
    		bool lastShouldNotify = shouldNotify;
    		if ( (!eventQueue.isEmpty()) && 
    		     (shouldNotify) && 
    		     (!OMThread::isEndOfProcess()) ) {
    			// notifyEventStep() supports the "go event" command
    			// The semantics of go event is to stop before extracting the first event from the queue -
    			// and then continue until the queue is empty before stopping again
    			AnimServices::notifyEventStep(getOsHandle());
    			shouldNotify = false;
    		}
    #endif // _OMINSTRUMENT
    
    		if (toGuardThread) {
    			// toGuard should be set to true by the application class, if necessary
    			START_THREAD_GUARDED_SECTION 
    		}
    
    #ifdef _OMINSTRUMENT
    		AnimServices::notifyEventGetBegin(getOsHandle());
    #endif // _OMINSTRUMENT
    
    		// Actually dispatch the event
    		IOxfEvent* ev = eventQueue.get();
            
            if(ev && !ev->isFrameworkEvent())
    			bShouldNotifyIdle = true;
    				
    #ifdef _OMINSTRUMENT
    		IOxfEvent* animEv = ev;
    		if ( (animEv != NULL ) &&
    			 (animEv->getId() == OMAnimWakeupEventId) ) {
    			// animation should ignore the wakeup token
    			animEv = NULL;
    			// reset the shouldNotify state
    			shouldNotify = lastShouldNotify;
    		}
    		AnimServices::notifyEventGetEnd(getOsHandle(), animEv);
    #endif // _OMINSTRUMENT
    
    		if (ev == NULL) {
    			thereAreEventsToConsume = false;
    		} else {
    			if (ev->getId() == OMEndThreadEventId) {
    				if (finalTermination) {
    					// stop the event loop
    					processing = false;
    					break;
    				} else {
    					// resend the termination event
    					finalTermination = true;
    					endDispatching();
    				}
    			}
    		
    			IOxfReactive::TakeEventStatus result = IOxfReactive::eventConsumed;
    			IOxfReactive* dest = ev->getDestination();
    #ifdef _OMINSTRUMENT
    			if ( (!isCanceled(ev) ) &&
    				 (ev->getId() != OMAnimWakeupEventId) ) {
    				// destination still exists
    				shouldNotify = true;
    			}
    #endif
    			result = dispatch(ev);
    			ev = NULL;
    
    			if (result == IOxfReactive::instanceReachTerminate) {
    				if (dest!=NULL)	{
    					dest->destroy();
    				}
    			}
    		}
    		
    		if ( eventQueue.isEmpty() )
    		{
    			thereAreEventsToConsume = false;
    		}
    
    		if (toGuardThread) {
    			// toGuard should be set to true by the application class, if necessary
    			END_THREAD_GUARDED_SECTION
    		}
    	}
    	if (processing) {
    		if (sysTimer != NULL) {
    			sysTimer->decNonIdleThreadCounter();
    		}
            
            if(bShouldNotifyIdle)
            	OXF::notifyIdle();
            
    #ifdef _OMINSTRUMENT
    		// Entering idle state 
    		// If should stop on idle -- then stop
    		// else become idle 
    		// Note: if should stop on idle you never really go idle
    		if ( AnimServices::shouldNotifyIdle(getOsHandle()) ) {
    			AnimServices::notifyIdle(getOsHandle());
    		} else {
    			eventQueue.pend();
    			AnimServices::notifyReady(getOsHandle());
    		}
    #else
    		eventQueue.pend();
    #endif
    	}
    }
    // the return type is maintained for backwards compatibility
    return 0;
    //#]
}

void OMThread::setOsThread(OMOSThread* thread) {
    //#[ operation setOsThread(OMOSThread*)
    osThread = thread;
    //#]
}

void OMThread::_cleanupThread(void) {
    //#[ operation _cleanupThread()
    OMThreadManager::instance().deregisterThread(this);
    
    #ifdef _OMINSTRUMENT
    AnimServices::notifyThreadDestroyed(getOsHandle());
    #endif
    
    if ( (osThread != NULL) && (!osThread->exeOnMyThread()) ) {
    	// The thread running the destructor is not my 'thread'
    	// so we can safely end it, thereby avoiding interference in the deletion agenda
    	setEndOSThreadInDtor(true);
    	delete osThread;	// deletes the object representing the OS thread (i.e. release resources)
    	osThread = NULL;
    }
    
    eventQueue.cleanup();
    
    if (toGuardThread) {
    	// toGuard should be set to true by the application class, if necessary
    	END_THREAD_GUARDED_SECTION
    }
    // For self terminated thread we should cleanup it here
    dispatchingGuard.cleanupMutex();
    
    if ((osThread != 0) && (osThread->exeOnMyThread())) {
    	// here we should delete the mutex of this OMProtected
    	// otherwise, the code for unlock the mutex will not be executed 
    	// since the thread is just to be deleted
    	 unlock();
    
    	// Deletes the object representing the OS thread (i.e. release resources),
    	// really ending it depends on the thread itself.
    	// Depends what is the cause of destruction:
    	// is it an event that reaches a terminate connector, which is the recommended approach (see doExecute())
    	// or different path like a trigger operation reaching a terminate connector or even a 'delete this'....
    	delete osThread;
    	osThread = NULL;
    }
    //#]
}

void OMThread::_initializeOMThread(bool wrapThread, const Rhp_const_char_pt name, const Rhp_int32_t stackSize
, const Rhp_int32_t messageQueueSize, bool dynamicMessageQueue) {
    //#[ operation _initializeOMThread(bool,Rhp_const_char_pt,Rhp_int32_t,Rhp_int32_t,bool)
    theCore = NULL;
    OMThreadManager::instance().registerThread(this);
    toGuardThread = false; // the application class should set it to true, if necessary
    if (!wrapThread) {
    	// Creating a thread of control
    	osThread = OMOSFactory::instance()->createOMOSThread(doExecute, this, name, stackSize); 
    } else {
    	// When we wrap the thread WE ARE SURE that we are wrapping the
    	// current thread so we can ask about its identifier and then
    	// create the OSwrapper thread.
    	void* threadOsHandle = OMOSFactory::instance()->getCurrentThreadHandle();
    	osThread = OMOSFactory::instance()->createOMOSWrapperThread(threadOsHandle);
    }
    
    // Create the event queue
    eventQueue.init(messageQueueSize, dynamicMessageQueue) ;
    eventQueue.getOsQueue()->setOwnerProcess(osThread->getOsHandle());
    
    #ifdef _OMINSTRUMENT
    AnimServices::notifyThreadCreated(this, osThread->getOsHandle());
    #endif
    //#]
}

bool OMThread::isCanceled(const IOxfEvent* ev) const {
    //#[ operation isCanceled(IOxfEvent) const
    bool canceled = false;
    
    if (ev != NULL) {
    	if ((ev->getId() == OMTimeoutEventId) && 
    		static_cast<const IOxfTimeout*>(ev)->isCanceled() )	{
    		canceled = true;
    	} else {
    		// support direct reactive deletion
    		if (ev->getId() == OMCancelledEventId) {
    			canceled = true; 
    		}
    	}
    }
    return canceled;
    //#]
}

bool OMThread::isControlEvent(const IOxfEvent* ev) const {
    //#[ operation isControlEvent(IOxfEvent) const
    bool res;
    
    if (ev != NULL) {
    	res = ( (ev->isTypeOf(OMEndThreadEventId) == 1) ||
    		    (ev->isTypeOf(OMReactiveTerminationEventId) == 1) );
    } else {
    	res = false;
    }
    return res;
    //#]
}

bool OMThread::shouldDispatch(const IOxfEvent* ev) const {
    //#[ operation shouldDispatch(IOxfEvent) const
    bool res = false; 
    
    if (ev != NULL) {
    	if (!isCanceled(ev)) {
    		res = (dispatching || isControlEvent(ev));
    	}
    }
    return res;
    //#]
}

void OMThread::setTheCore(OMCore* p_OMCore) {
    //#[ operation setTheCore(OMCore)
    if (p_OMCore)
    	theCore = p_OMCore;
    
    // if it doesnot exist in list
    // then add it
    //#]
}

void OMThread::assignCoreId(const OMAffinity_t myCoreId) {
    //#[ operation assignCoreId(OMAffinity_t)
    OMTimerManager* sysTimer = OMTimerManager::instance();
    OMAffinity_t curCoreId =  myCoreId;
    if ((sysTimer == NULL) || (sysTimer->getRealTimeModel() == true)) {
    	osThread->setAffinity(myCoreId);
    }
    else
    {
    	OMCore* myCore = getTheCore(); 
    	// user can define it in class constructor 
    	// In this  case we only add it to the list
    	if (myCore == NULL)
    	{
    		myCore = OMThreadManager::getExistingCore(curCoreId);
    		if (myCore == NULL) {
    			myCore = new OMCore(curCoreId);
    			(void)myCore->startBehavior();
    		}
    		setTheCore(myCore);
    	}
    }
    
    
    
    //#]
}

void OMThread::reInitializeOMThread(bool wrapThread, const Rhp_const_char_pt name, const Rhp_int32_t stackSize
, const Rhp_int32_t messageQueueSize, bool dynamicMessageQueue) {
    //#[ operation reInitializeOMThread(bool,Rhp_const_char_pt,Rhp_int32_t,Rhp_int32_t,bool)
    deletionAllowed = true;
    toGuardThread = false;
    processing = true;
    dispatching = true;
    finalTermination = false;
    
    _initializeOMThread(wrapThread,name,stackSize,messageQueueSize,dynamicMessageQueue);
    //#]
}

bool OMThread::getDeletionAllowed(void) const {
    return deletionAllowed;
}

void OMThread::setDeletionAllowed(bool p_deletionAllowed) {
    deletionAllowed = p_deletionAllowed;
}

bool OMThread::shouldGuardThread(void) const {
    return toGuardThread;
}

void OMThread::setToGuardThread(bool p_toGuardThread) {
    toGuardThread = p_toGuardThread;
}

bool OMThread::getDispatching(void) const {
    return dispatching;
}

OMOSThread* OMThread::getOsThread(void) const {
    return osThread;
}

OMCore* OMThread::getTheCore(void) const {
    return theCore;
}

void OMThread::cleanUpRelations(void) {
    if(osThread != NULL)
        {
            osThread = NULL;
        }
    if(theCore != NULL)
        {
            theCore = NULL;
        }
}




