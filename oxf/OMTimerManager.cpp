//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: OMTimerManager
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
#include "OMTimerManager.h"
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
//## dependency IOxfReactive
#include "IOxfReactive.h"
//## dependency IOxfTickTimerFactory
#include "IOxfTickTimerFactory.h"
//## dependency OMCore
#include "OMCore.h"
//## dependency OMDelay
#include "OMDelay.h"
//## link guard
#include "os.h"
//## dependency OMThread
#include "omthread.h"
//## dependency OMTimeout
#include "OMTimeout.h"
//## dependency OXF
#include "oxf.h"
//## package Design::oxf::Services::Time::TimeManagement

//## class OMTimerManager

//#[ ignore
#ifdef OM_USE_TIMEOUT_LATENCY_CORRECTION
OM_GET_CURRENT_TIME		// OMGetTimeOfDay() definition
#endif
//#]


const OxfTimeUnit OMTimerManager::overflowMark = 0x80000000;

bool OMTimerManager::timerManagerSingletonDestroyed = false;

bool OMTimerManager::allowDestroy = true;

bool OMTimerManager::instanceInitialized = false;

bool OMTimerManager::externalTimer(false);

OMTimerManager::OMTimerManager(OxfTimeUnit ticktime, const Rhp_uint32_t maxTM, bool isRealTimeModel) : time_(0U), 
tick(ticktime), realTimeModel(true), suspended(false), timeouts(static_cast<Rhp_int32_t>(maxTM)), 
nonIdleThreadCounter(0), tickStart(0U) {
    //#[ operation OMTimerManager(OxfTimeUnit,Rhp_uint32_t,bool)
    #ifndef OM_NO_TEMPLATES_USAGE
    	OMTimeout::OMMemoryPoolSetIncrement(static_cast<Rhp_int32_t>(maxTM));
    #endif // OM_NO_TEMPLATES_USAGE
    tickTimer = NULL;
    guard = NULL;
    guardNonIdle = NULL;
    realTimeModel = isRealTimeModel;
    suspended = false;
    #ifdef OM_USE_TIMEOUT_LATENCY_CORRECTION
    tickStart = OMGetTimeOfDay(); 
    #endif
    //#]
}

OMTimerManager::~OMTimerManager(void) {
    //#[ operation ~OMTimerManager()
    // mark the timer manager singleton is destroyed
    if (getStaticTimerManager() == this) {
    	timerManagerSingletonDestroyed = true;
    }
    
    cleanup();
    
    // reset tick
    tick = 0U;
    //#]
}

void OMTimerManager::advanceTime(void) {
    //#[ operation advanceTime()
    goNextAndPost();
    //#]
}

void OMTimerManager::cbkBridge(void * me) {
    //#[ operation cbkBridge(void *)
    #ifdef OM_USE_TIMEOUT_LATENCY_CORRECTION
    reinterpret_cast<OMTimerManager*>(me)->tickStart = OMGetTimeOfDay(); 
    #endif
    reinterpret_cast<OMTimerManager*>(me)->timeTickCbk();
    //#]
}

void OMTimerManager::cbkBridgeWithTime(void * me, OxfTimeUnit currTime) {
    //#[ operation cbkBridgeWithTime(void *,OxfTimeUnit)
    reinterpret_cast<OMTimerManager*>(me)->timeTickCbkWithTime(currTime);
    //#]
}

void OMTimerManager::cleanup(void) {
    //#[ operation cleanup()
    instanceInitialized = false;
    
    // Without grabbing the guard before deleting the tick timer, there is a
    // possible race condition. The tick timer could be cancelled after it
    // has destroyed a timeout but before it has removed it from the heap. 
    // Grabbing the lock insures that the tick timer can complete 
    // OMTimerManager::post before it is cancelled.
    lock ();
    // delete the timer - done first to stop timer work
    delete tickTimer;
    tickTimer = NULL;
        
    // delete the guard
    if (guard != NULL)
    {
       	OMOSMutex* tmp = guard;
       	guard = NULL;
       	tmp->unlock ();
       	delete tmp;
    }
    if (guardNonIdle != NULL)
    {		
       	delete guardNonIdle;
       	guardNonIdle = NULL;
    }
    // cleanup the timeouts & delete the timouts left in it
    // this should be done after the deletion of the mutex
    while (timeouts.isEmpty() == 0) {
       	IOxfTimeout* t = reinterpret_cast<IOxfTimeout*>(timeouts.top());
       	timeouts.trim();
       	delete t;
    }
    
    time_ = 0U;
    
    externalTimer = false;
    //#]
}

bool OMTimerManager::cleanupCanceledTimeouts(bool withLock) {
    //#[ operation cleanupCanceledTimeouts(bool)
    bool res = false;
    OMTimeout examplar;
    examplar.cancel();
    
    if (withLock) {
    	lock();
    }
    bool done = false;
    while (!done) {
    	IOxfTimeout* tm = reinterpret_cast<IOxfTimeout*>(timeouts.remove(&examplar));
    	if (tm != NULL) {
    		tm->destroy();
    		res = true;
    	} else {
    		done = true;
    	}
    }
    if (withLock) {
    	unlock();
    }
    return res;
    //#]
}

void OMTimerManager::clearInstance(void) {
    //#[ operation clearInstance()
    if (getStaticTimerManager() != NULL) {
    	if(allowDestroy)
        	getStaticTimerManager()->destroyTimer();
    	else
    		getStaticTimerManager()->cleanup();
    }
    //#]
}

void OMTimerManager::consumeTime(OxfTimeUnit interval, OxfTimeUnit /*step*/, IOxfActive* const theContext) {
    //#[ operation consumeTime(OxfTimeUnit,OxfTimeUnit,IOxfActive)
    consumeTime(interval , theContext);
    
    //#]
}

void OMTimerManager::consumeTime(OxfTimeUnit interval, IOxfActive* const theContext) {
    //#[ operation consumeTime(OxfTimeUnit,IOxfActive)
    if (!realTimeModel) {
    	OMCore* currCore = NULL;
    	IOxfActive* currContext = theContext;
    	if (currContext == NULL) 
    	{
    		currContext = OMMainThread::instance();
    	}
    	if (currContext != NULL) 
    	{
     		OMThread* theOMThread = reinterpret_cast<OMThread*>(currContext);  
    		if (theOMThread)
    			currCore = theOMThread->getTheCore();
    		if (currCore == NULL)
    		{
    		 	if (theOMThread)
       			{
    				theOMThread->assignCoreId(0);
    				currCore = theOMThread->getTheCore();
    			}
    		}
    		if(currCore)
    			currCore->consumeTime(interval);
    	}
    }
    //#]
}

void OMTimerManager::decNonIdleThreadCounter(void) {
    //#[ operation decNonIdleThreadCounter()
    if (!realTimeModel) 
    {
    	lockNonIdle();
    	if (nonIdleThreadCounter > 0) {
    		--nonIdleThreadCounter;
    	}
    	unlockNonIdle(); 
    }
    //#]
}

OxfTimeUnit OMTimerManager::getElapsedTime(void) const {
    //#[ operation getElapsedTime() const
    return time_;
    //#]
}

OxfTimeUnit OMTimerManager::getNextTime(void) {
    //#[ operation getNextTime()
    OxfTimeUnit nextTime = time_;
    lock(); // critical section for the timeouts structure
    Rhp_uint32_t count = timeouts.getCount();
    while (count >0) {
    	IOxfTimeout* timeout = reinterpret_cast<IOxfTimeout*>(timeouts.top());
    	if (timeout != NULL)
    	{	
    		if (timeout->isCanceled()) 
    		{
    			// destroy the canceled timeout
    			timeout->destroy();
    			timeouts.trim(); // trim the timeout
    		}
    		else
    		{
    			nextTime = timeout->getDueTime();
    			break;
    		}
    	}
    	count--;
    }
    unlock();
    return nextTime;
    //#]
}

void OMTimerManager::goNextAndPost(void) {
    //#[ operation goNextAndPost()
    // Advance to the next timeout and post it
    lock(); // critical section for the timeouts structure
    goNext();
    unlock();
    post();	// Handle that time event
    //#]
}

void OMTimerManager::incNonIdleThreadCounter(void) {
    //#[ operation incNonIdleThreadCounter()
    if (!realTimeModel) 
    {
    	lockNonIdle();
    	++nonIdleThreadCounter;
    	unlockNonIdle(); 
    }
    //#]
}

void OMTimerManager::init(void) {
    //#[ operation init()
    // initialize the guard
    guard = OMOSFactory::instance()->createOMOSMutex();
    guardNonIdle = OMOSFactory::instance()->createOMOSMutex();
    // reset the idle thread counter
    setNonIdleThreadCounter(0);
    // get the user timer factory
    const IOxfTickTimerFactory* timerFactory = OXF::getTheTickTimerFactory();
    // create the timer
    if (realTimeModel) {
    	if (timerFactory != NULL) {
    		// user timer
    		tickTimer = timerFactory->createRealTimeTimer(tick,cbkBridge,this);
    	} else {
    		// the system timer
    		tickTimer = OMOSFactory::instance()->createOMOSTickTimer(tick,cbkBridge,this);
    	}
    } else {
    	// In case of simulated time this task is an idle task called when all other tasks are Blocked
    	if (timerFactory != NULL) {
    		// user timer
    		tickTimer = timerFactory->createSimulatedTimeTimer(cbkBridge,this);
    	} else {
    		tickTimer = OMOSFactory::instance()->createOMOSIdleTimer(cbkBridge,this);
    	}
    }
    if (OXF::frmThreadAffinities.Timer != 0U) 
    {
    	tickTimer->setAffinity(OXF::frmThreadAffinities.Timer);
    }
    //#]
}

OMTimerManager* OMTimerManager::initInstance(OxfTimeUnit ticktime, const Rhp_uint32_t maxTM, bool isRealTimeModel) {
    //#[ operation initInstance(OxfTimeUnit,Rhp_uint32_t,bool)
    OMTimerManager* manager = NULL;
    
    if (!instanceInitialized) {
    	instanceInitialized = true;
    	manager = getStaticTimerManager(ticktime,maxTM,isRealTimeModel, true);
    	if (manager != NULL) {
    		manager->init();
    	}
    }
    return manager;
    //#]
}

OMTimerManager* OMTimerManager::instance(void) {
    //#[ operation instance()
    return getStaticTimerManager();
    //#]
}

bool OMTimerManager::isExternalTimer(void) const {
    //#[ operation isExternalTimer() const
    return externalTimer;
    //#]
}

bool OMTimerManager::isHeapFull(void) const {
    //#[ operation isHeapFull() const
    bool status;
    if ((timeouts.getCount()+1) >= timeouts.getHeapSize()) {
    	status = true;
    } else {
    	status = false;
    }        
    return status;
    //#]
}

void OMTimerManager::lock(void) const {
    //#[ operation lock() const
    if (guard != NULL) {
    	guard->lock();
    }
    //#]
}

void OMTimerManager::requestTimeNotification(IOxfReactive* reactive, const OxfTimeUnit deltaT, IOxfTimeout*& timeout
, OxfTimeUnit& baseTime) {
    //#[ operation requestTimeNotification(IOxfReactive*,const OxfTimeUnit,IOxfTimeout*&,OxfTimeUnit&)
    timeout = reinterpret_cast<IOxfTimeout*>(new OMTimeout(reactive, deltaT, NULL));
    (void)set(timeout);
    baseTime = getElapsedTime();
    //#]
}

bool OMTimerManager::set(IOxfTimeout* timeout) {
    //#[ operation set(IOxfTimeout)
    // critical section for the timeouts structure
    lock();
    bool cleanupDone = true; // it is true if no need to cleanup or timeouts deleted from heap
    setTimeoutDueTime(timeout);
    if (isHeapFull()) {
    	cleanupDone = cleanupCanceledTimeouts(false);
    }
    bool res = false;
    if (cleanupDone) {
    	res = timeouts.add(timeout);
    }
    unlock();
    return res;
    //#]
}

void OMTimerManager::setElapsedTime(OxfTimeUnit newTime) {
    //#[ operation setElapsedTime(OxfTimeUnit)
    lock(); 
    time_ = (newTime) & (~overflowMark);
    unlock();
    //#]
}

void OMTimerManager::suspend(void) {
    //#[ operation suspend()
    suspended = true; 
    //#]
}

void OMTimerManager::unlock(void) const {
    //#[ operation unlock() const
    if (guard != NULL) {
    	guard->unlock();
    }
    //#]
}

void OMTimerManager::action(IOxfTimeout* timeout) const {
    //#[ operation action(IOxfTimeout) const
    IOxfReactive* reactive = timeout->getDestination();
    if (timeout->getId() != OMTimeoutDelayId) {
    	// only "real" timeouts
    	// send the timeout
    	if (reactive != NULL) {
    		OMOSEventGenerationParams params((void*)this);
    		(void) reactive->send(timeout, params);
    	} else {
    		// cleanup
    		if (timeout->isCanceled())
    		{
    			timeout->destroy();
    		}
    	}
    } else {
    	// A delay request - The thread is the receiver	
    	OMDelay* d = reinterpret_cast<OMDelay*>(reactive);
    	d->wakeup();
    	///////////////////////
    	// destroy the timeout
    	///////////////////////
    	// first cancel the timeout
    	// so that the timeout will not call -
    	// the destination cancelTimeout()
    	// set the destiation to 0 to avoid query of the destination
    	timeout->setDestination(NULL);
    	timeout->cancel();
    	timeout->destroy();
    }
    
    //#]
}

inline Rhp_int64_t OMTimerManager::getNonIdleThreadCounter(void) const {
    //#[ operation getNonIdleThreadCounter() const
    lockNonIdle();
    Rhp_int64_t res = nonIdleThreadCounter;
    unlockNonIdle();
    return res;
    //#]
}

OMTimerManager* OMTimerManager::getStaticTimerManager(void) {
    //#[ operation getStaticTimerManager()
    return getStaticTimerManager(1, 0U, true);
    //#]
}

OMTimerManager* OMTimerManager::getStaticTimerManager(OxfTimeUnit tickTime, const Rhp_uint32_t maxTM, bool
 isRealTimeModel, bool forceInitialization) {
    //#[ operation getStaticTimerManager(OxfTimeUnit,Rhp_uint32_t,bool,bool)
    OMTimerManager* manager = NULL;
    static bool initialized = false; 
    
    if ( (!timerManagerSingletonDestroyed) && 
    	 (initialized || forceInitialization) ) {
    	// the timer manager static instance is already initialized (and was not destroyed) or -
    	// the parameter for the timer manager initialization are valid
    	initialized = true;
    	// the memory manager static instance
    	static OMTimerManager theTimerManager(tickTime, maxTM, isRealTimeModel);
    	initTimeoutsMemoryPool();
    
    #ifdef _OMINSTRUMENT
    	AnimServices::registerAnimTimerManager(&theTimerManager);
    #endif
    
    	manager = &theTimerManager;
    } else {
    	// the timer manager static instance was not initialized yet, and -
    	// the initialization parameters are not valid
     	manager = NULL;
    }
    return manager;
    //#]
}

void OMTimerManager::goNext(void) {
    //#[ operation goNext()
    // Check for expired timeouts 
    while (timeouts.isEmpty() == 0) {
    	IOxfTimeout* timeout = reinterpret_cast<IOxfTimeout*>(timeouts.top());
    	if (timeout->isCanceled()) {
    		// destroy the canceled timeout
    		timeout->destroy();
    		timeouts.trim(); // trim the timeout
    	} else {
    		time_ = timeout->getDueTime();
    		break;
    	}
    }
    // Advance to next relevant time
    
    //#]
}

void OMTimerManager::initTimeoutsMemoryPool(void) {
    //#[ operation initTimeoutsMemoryPool()
    static bool timeoutsMemoryInitialized = false;
    if (!timeoutsMemoryInitialized) {
    	// do once
    	timeoutsMemoryInitialized = true;
    	// create a dummy timeout in order to force the allocation of timeouts memory pool
    	#ifndef OM_NO_TEMPLATES_USAGE
    		OMTimeout::OMCallMemoryPoolIsEmpty(false); // avoid Message to the user 
    	#endif // OM_NO_TEMPLATES_USAGE
    	OMTimeout* dummy = new OMTimeout;
    	delete dummy;
    	#ifndef OM_NO_TEMPLATES_USAGE
    		OMTimeout::OMCallMemoryPoolIsEmpty(true);
    	#endif // OM_NO_TEMPLATES_USAGE
    }
    //#]
}

void OMTimerManager::lockNonIdle(void) const {
    //#[ operation lockNonIdle() const
    if (guardNonIdle != NULL) {
    	guardNonIdle->lock();
    }
    //#]
}

//#[ ignore
/*

//#]
OMTimerManager& OMTimerManager::operator=(const OMTimerManager& other) {
    //#[ operation operator=(OMTimerManager)
    //#]
}
//#[ ignore


*/
//#]

void OMTimerManager::post(void) {
    //#[ operation post()
    // Note post() must always be within the "lock" of OMTimerManager
    ///////////////////////////
    // begin critical section
    ///////////////////////////
    lock();
    ///////////////////////////
    while (timeouts.isEmpty() == 0) {
    	IOxfTimeout* timeout = reinterpret_cast<IOxfTimeout*>(timeouts.top());
    	if (time_ < timeout->getDueTime()) {
    		// no ready timeouts
    		break;
    	}
    	
    	if (timeout->isCanceled()) {
    		// destroy the canceled timeout
    		timeout->destroy();
    	} else {
    		action(timeout);
    	}
    	timeouts.trim(); // trim the timeout
    }
    // checking if the time counter overflowed
    if (time_ >= overflowMark) {
    	resetTimeoutsDueTime();
    }
    ///////////////////////////
    // end critical section
    ///////////////////////////
    unlock();
    ///////////////////////////
    //#]
}

void OMTimerManager::resetTimeoutsDueTime(void) {
    //#[ operation resetTimeoutsDueTime()
    // iterate over the timeouts and update the triggered timeouts
    OMTimeoutValueIter iter(timeouts);
    #ifdef OM_NO_TEMPLATES_USAGE
    while (iter.value() != NULL) {
    	IOxfTimeout& curr = *((IOxfTimeout*)*iter);
    #else
    while (&iter.value() != &OMNullValue<IOxfTimeout>::get()) {
    	IOxfTimeout& curr = *iter;
    #endif // OM_NO_TEMPLATES_USAGE
    	OxfTimeUnit currDueTime = curr.getDueTime();
       	curr.setDueTime((currDueTime) & (~overflowMark));
       	++iter;
    }
    
    // update the timer counter
    time_ &= ~overflowMark;
    //#]
}

inline void OMTimerManager::setNonIdleThreadCounter(Rhp_int64_t newCounter) {
    //#[ operation setNonIdleThreadCounter(Rhp_int64_t)
    if (!realTimeModel) 
    {
    	lockNonIdle();
    	nonIdleThreadCounter = newCounter;
    	unlockNonIdle();
    }
    //#]
}

void OMTimerManager::setTimeoutDueTime(IOxfTimeout* timeout) const {
    //#[ operation setTimeoutDueTime(IOxfTimeout) const
    if (timeout != NULL) {
    	OxfTimeUnit tmLatency = 0U;
    #ifdef OM_USE_TIMEOUT_LATENCY_CORRECTION
    	tmLatency = OMGetTimeOfDay();
    	if (tmLatency > tickStart) 
    	{
    		tmLatency = tmLatency - tickStart;
    	}
    	else
    		tmLatency = 0U;
    #endif
    	timeout->setDueTime(timeout->getDelayTime() + time_ + tmLatency);
    }
    //#]
}

void OMTimerManager::timeTickCbk(void) {
    //#[ operation timeTickCbk()
    #ifdef _OMINSTRUMENT 
    // This code ensures the timer will not advance during
    // the "user's turn" in animation/trace
    // This is done by not advancing the time_ so the timer
    // keeps ticking but never advances (until resume)
    // For simulated time, in effect, this is a "busy wait".
    if (!suspended) {
    #endif // _OMINSTRUMENT
    
    	lock(); // critical section for the timeouts structure
    	if (realTimeModel) {
    		time_ += tick ;
    	} else {
    		// simulated time
    		// The purpose of the following condition is to ensure that
    		// all threads are idle and not just rely on the priority
    		// of the threads (NT scheduling policy may cause scheduling 
    		// of low priority threads).
    		// In some cases, when using guarded operations with simulated 
    		// time, one may consider to remove this condition.
    		if (getNonIdleThreadCounter() == 0) {
    			goNext();
    		}
    	}
    	unlock();
    	post();	// Handle that time event 
    
    #ifdef _OMINSTRUMENT 
    }
    #endif // _OMINSTRUMENT
    //#]
}

void OMTimerManager::timeTickCbkWithTime(OxfTimeUnit currTime) {
    //#[ operation timeTickCbkWithTime(OxfTimeUnit)
    #ifdef _OMINSTRUMENT 
    // This code ensures the timer will not advance during
    // the "user's turn" in animation/trace
    // This is done by not advancing the time_ so the timer
    // keeps ticking but never advances (until resume)
    // For simulated time, in effect, this is a "busy wait".
    if (!suspended) {
    #endif // _OMINSTRUMENT
        
        time_ = currTime;
    	post();	// Handle that time event 
    
    #ifdef _OMINSTRUMENT 
    }
    #endif // _OMINSTRUMENT
    //#]
}

void OMTimerManager::unlockNonIdle(void) const {
    //#[ operation unlockNonIdle() const
    if (guardNonIdle != NULL) {
    	guardNonIdle->unlock();
    }
    //#]
}

OxfTimeUnit OMTimerManager::getTick(void) const {
    return tick;
}

bool OMTimerManager::getRealTimeModel(void) const {
    return realTimeModel;
}

bool OMTimerManager::getSuspended(void) const {
    return suspended;
}

bool OMTimerManager::getAllowDestroy(void) {
    return allowDestroy;
}

void OMTimerManager::setAllowDestroy(bool p_allowDestroy) {
    allowDestroy = p_allowDestroy;
}

void OMTimerManager::setExternalTimer(bool p_externalTimer) {
    externalTimer = p_externalTimer;
}




