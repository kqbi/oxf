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
//## dependency OMTimeout
#include "OMTimeout.h"
#include "OMMainDispatcher.h"
#include "OXFEventPoller.h"

//## package Design::oxf::Services::Time::TimeManagement

//## class OMTimerManager

bool OMTimerManager::timerManagerSingletonDestroyed = false;

bool OMTimerManager::allowDestroy = true;

bool OMTimerManager::externalTimer(false);

OMTimerManager::OMTimerManager(boost::asio::io_context &ioc) : _ioc(ioc), time_(0U),
                                                               suspended(false), nonIdleThreadCounter(0),
                                                               tickStart(0U) {
    //#[ operation OMTimerManager(unsigned long,uint32_t,bool)
    //#]
}

OMTimerManager::~OMTimerManager(void) {
    //#[ operation ~OMTimerManager()
    // mark the timer manager singleton is destroyed
    printf("~OMTimerManager\n");
    cleanup();
    //#]
}

void OMTimerManager::cleanup(void) {
    //#[ operation cleanup()
    //#]
}

bool OMTimerManager::cleanupCanceledTimeouts(bool withLock) {
    //#[ operation cleanupCanceledTimeouts(bool)
    bool res = false;

    return res;
    //#]
}

void OMTimerManager::clearInstance(void) {
    //#[ operation clearInstance()
    //    if (getStaticTimerManager() != NULL) {
    //        if(allowDestroy)
    //            getStaticTimerManager()->destroyTimer();
    //        else
    //            getStaticTimerManager()->cleanup();
    //    }
    //#]
}

void OMTimerManager::consumeTime(unsigned long interval, unsigned long /*step*/, IOxfActive *const theContext) {
    //#[ operation consumeTime(unsigned long,unsigned long,IOxfActive)
    consumeTime(interval, theContext);

    //#]
}

void OMTimerManager::consumeTime(unsigned long interval, IOxfActive *const theContext) {
    //#[ operation consumeTime(unsigned long,IOxfActive)
#if 0
    if (!realTimeModel) {
        OMCore* currCore = NULL;
        IOxfActive* currContext = theContext;
        if (currContext == NULL)
        {
            currContext = OMMainDispatcher::getInstance();
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
#endif
    //#]
}

unsigned long OMTimerManager::getElapsedTime(void) const {
    //#[ operation getElapsedTime() const
    return time_;
    //#]
}

unsigned long OMTimerManager::getNextTime(void) {
    //#[ operation getNextTime()
    unsigned long nextTime = time_;
#if 0
    lock(); // critical section for the timeouts structure
    uint32_t count = timeouts.getCount();
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
#endif
    return nextTime;
    //#]
}

void OMTimerManager::goNextAndPost(void) {
    //#[ operation goNextAndPost()
    // Advance to the next timeout and post it

    goNext();

    post();    // Handle that time event
    //#]
}

OMTimerManager *OMTimerManager::Instance() {
    //#[ operation instance()
    static OMTimerManager manager(OXFEventPollerPool::Instance()->_ioc);
    return &manager;
    //#]
}

bool OMTimerManager::isExternalTimer(void) const {
    //#[ operation isExternalTimer() const
    return externalTimer;
    //#]
}

bool OMTimerManager::set(IOxfTimeout::Ptr &timeout) {
    //#[ operation set(IOxfTimeout)
    // critical section for the timeouts structure
    bool res = true; // it is true if no need to cleanup or timeouts deleted from heap
    setTimeoutDueTime(timeout);
    _timeouts.add(timeout);
    (std::dynamic_pointer_cast<OMTimeout>(timeout))->action();
    return res;
    //#]
}

void OMTimerManager::remove(IOxfTimeout::Ptr &timeout) {
    _timeouts.remove(timeout);
}

void OMTimerManager::setElapsedTime(unsigned long newTime) {
    //#[ operation setElapsedTime(unsigned long)
    //time_ = (newTime) & (~overflowMark);
    //#]
}

void OMTimerManager::suspend(void) {
    //#[ operation suspend()
    suspended = true;
    //#]
}

void OMTimerManager::action(IOxfTimeout::Ptr &timeout) {
    //#[ operation action(IOxfTimeout) const
    std::weak_ptr<IOxfReactive> reactive = timeout->getDestination();
    auto ev = reactive.lock();
    _timeouts.remove(timeout);
    if (ev) {
        (void) ev->send(timeout);
    } else {
        if (timeout->isCanceled()) {
            timeout.reset();
        }
    }
    //#]
}

OMTimerManager *OMTimerManager::getStaticTimerManager(boost::asio::io_context &ioc) {
    //#[ operation getStaticTimerManager(unsigned long,uint32_t,bool,bool)
    static OMTimerManager theTimerManager(ioc);
    return &theTimerManager;
    //#]
}

void OMTimerManager::goNext(void) {
    //#[ operation goNext()
    // Check for expired timeouts
    //    while (timeouts.isEmpty() == 0) {
    //        IOxfTimeout* timeout = reinterpret_cast<IOxfTimeout*>(timeouts.top());
    //        if (timeout->isCanceled()) {
    //            // destroy the canceled timeout
    //            timeout->destroy();
    //            timeouts.trim(); // trim the timeout
    //        } else {
    //            time_ = timeout->getDueTime();
    //            break;
    //        }
    //    }
    // Advance to next relevant time

    //#]
}

void OMTimerManager::post(void) {
    //#[ operation post()
    //    while (_timeouts.isEmpty()) {
    //        IOxfTimeout* timeout = reinterpret_cast<IOxfTimeout*>(timeouts.top());
    //        if (time_ < timeout->getDueTime()) {
    //            // no ready timeouts
    //            break;
    //        }

    //        if (timeout->isCanceled()) {
    //            // destroy the canceled timeout
    //            timeout->destroy();
    //        } else {
    //            action(timeout);
    //        }
    //        timeouts.trim(); // trim the timeout
    //    }
    //    // checking if the time counter overflowed
    //    if (time_ >= overflowMark) {
    //        resetTimeoutsDueTime();
    //    }
    //#]
}

void OMTimerManager::resetTimeoutsDueTime(void) {
    //#[ operation resetTimeoutsDueTime()
    // iterate over the timeouts and update the triggered timeouts
    //    OMTimeoutValueIter iter(timeouts);
    //#ifdef OM_NO_TEMPLATES_USAGE
    //    while (iter.value() != NULL) {
    //        IOxfTimeout& curr = *((IOxfTimeout*)*iter);
    //#else
    //    while (&iter.value() != &OMNullValue<IOxfTimeout>::get()) {
    //        IOxfTimeout& curr = *iter;
    //#endif // OM_NO_TEMPLATES_USAGE
    //        unsigned long currDueTime = curr.getDueTime();
    //        curr.setDueTime((currDueTime) & (~overflowMark));
    //        ++iter;
    //    }

    //    // update the timer counter
    //    time_ &= ~overflowMark;
    //#]
}

void OMTimerManager::setTimeoutDueTime(IOxfTimeout::Ptr &timeout) const {
    //#[ operation setTimeoutDueTime(IOxfTimeout) const
    if (timeout != NULL) {
        unsigned long tmLatency = 0U;
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


    //        lock(); // critical section for the timeouts structure
    //        if (realTimeModel) {
    //            time_ += tick ;
    //        } else {
    //            // simulated time
    //            // The purpose of the following condition is to ensure that
    //            // all threads are idle and not just rely on the priority
    //            // of the threads (NT scheduling policy may cause scheduling
    //            // of low priority threads).
    //            // In some cases, when using guarded operations with simulated
    //            // time, one may consider to remove this condition.

    //            goNext();

    //        }
    //        unlock();
    //        post();	// Handle that time event


    //#]
}

void OMTimerManager::timeTickCbkWithTime(unsigned long currTime) {
    //#[ operation timeTickCbkWithTime(unsigned long)
#ifdef _OMINSTRUMENT
    // This code ensures the timer will not advance during
    // the "user's turn" in animation/trace
    // This is done by not advancing the time_ so the timer
    // keeps ticking but never advances (until resume)
    // For simulated time, in effect, this is a "busy wait".
    if (!suspended) {
#endif // _OMINSTRUMENT

    time_ = currTime;
    post();    // Handle that time event

#ifdef _OMINSTRUMENT
    }
#endif // _OMINSTRUMENT
    //#]
}

unsigned long OMTimerManager::getTick(void) const {
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




