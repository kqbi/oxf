//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: OMReactive
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
#include "omreactive.h"
#include "OMMainDispatcher.h"
//## auto_generated
#include "IOxfActive.h"
//## dependency NotifyMacros
//#include "OXFNotifyMacros.h"
//## link rootState
#include "state.h"
//## dependency OMTimeout
#include "OMTimeout.h"
#include "OMTimerManager.h"
#include "OXFEventPoller.h"
//## dependency OMTimerManager
//#include "OMTimerManager.h"
// for backward compatibility mode
#include <boost/bind.hpp>
#include <memory>
//## dependency OXF
//#include "oxf.h"
//## package Design::oxf::Core::CoreImplementation

//## class OMReactive
const uint32_t OMReactive::defaultStateMask = 0x00000000UL;

const uint32_t OMReactive::nullTransitionStateMask = 0x00000001UL;

const uint32_t OMReactive::nullTransitionMask = 0x0000FFFFUL;

const uint32_t OMReactive::terminateConnectorReachedStateMask = 0x00010000UL;

const uint32_t OMReactive::underDestructionStateMask = 0x00020000UL;

const uint32_t OMReactive::deleteOnTerminateStateMask = 0x00040000UL;

const uint32_t OMReactive::shouldCompleteStartBehaviorStateMask = 0x00080000UL;

const uint32_t OMReactive::behaviorStartedStateMask = 0x00100000UL;

int32_t OMReactive::maxNullSteps = DEFAULT_MAX_NULL_STEPS;

bool OMReactive::globalSupportDirectDeletion = false;

const uint32_t OMReactive::destroyEventResentStateMask = 0x00200000UL;

bool OMReactive::globalSupportRestartBehavior = false;

OMReactive::OMReactive(IOxfActive* context) : state(0U), active(false), busy(false),
    supportDirectDeletion(false), supportRestartBehavior(false), activeContext(0),
    rootState(0),_strand(OXFEventPollerPool::Instance()._ioc) {
    //#[ operation OMReactive(IOxfActive)
    OMReactive::setActiveContext(context, false);
    setShouldDelete(true);
    theStartOrTerminationEvent = std::make_shared<OMStartBehaviorEvent>();
    //#]
}

OMReactive::~OMReactive(void) {
    //#[ operation ~OMReactive()
    // Mark that the object is under destruction. This is required
    setUnderDestruction();
    //#]
    cleanUpRelations();
}

void OMReactive::setShouldDelete(bool flag) {
    //#[ operation setShouldDelete(bool)
    if (flag) {
        state |= deleteOnTerminateStateMask;
    } else {
        state &= ~deleteOnTerminateStateMask;
    }
    //#]
}

bool OMReactive::IsCurrentEvent(IOxfEvent::ID eventId) const {
    //#[ operation IsCurrentEvent(ID) const
    auto ev = _currentEvent.lock();
    bool status;
    
    // ev might be null during destruction
    if (!ev) {
        status = false;
    } else {
        status = ev->isTypeOf(eventId);
    }
    return status;
    //#]
}

void OMReactive::cancel(IOxfTimeout::Ptr& timeout) {
    //#[ operation cancel(IOxfTimeout)
    if (timeout) {
        timeout->cancel();
        timeout = NULL;
    }
    //#]
}

void OMReactive::cancelEvents(void) const {
    //#[ operation cancelEvents() const
    //#ifndef OM_DISABLE_DIRECT_REACTIVE_DELETION
    //    // ask my thread to cancel all the events that are targeted for me
    //    OMThread* itsOMThread = getThread();
    //    if (itsOMThread != NULL) {
    //        itsOMThread->cancelPendingEvents(this);
    //    }
    //#endif /* OM_DISABLE_DIRECT_REACTIVE_DELETION */
    //#]
}

bool OMReactive::cancelTimeout(const IOxfTimeout::Ptr & /*timeout*/) {
    //#[ operation cancelTimeout(IOxfTimeout)
    return false;
    //#]
}

void OMReactive::destroy(void) {
    //#[ operation destroy()
    setUnderDestruction();
#if 0
    OMThread* itsOMThread = getThread();
    if ((itsOMThread != NULL) && (isActive() == true))
    {
        // this is an active-reactive instance
        // terminate the dispatching (this will destroy the instance by destroyThread())
        itsOMThread->endDispatching();
    }
    else
    {
        if (!shouldSupportDirectDeletion())
        {
            // graceful self-termination
            theStartOrTerminationEvent.reincarnateAsTerminationEvent();
            (void) send(&theStartOrTerminationEvent);
        }
        else
        {
            if (shouldDelete())
            {
                // forced termination
                delete this;
            }
        }
    }
#endif
    if (shouldDelete())
    {
        // forced termination
        shared_from_this().reset();
    }
    //#]
}

void OMReactive::endBehavior() {
    //#[ operation endBehavior(const Rhp_const_char_pt aomArg())
    state |= terminateConnectorReachedStateMask;
    //#]
}

IOxfReactive::TakeEventStatus OMReactive::handleEvent(IOxfEvent::Ptr& ev) {
    //#[ operation handleEvent(IOxfEvent)
    IOxfReactive::TakeEventStatus status = eventNotConsumed;
    
    if (isUnderDestruction()) {
        // in termination process
        status = handleEventUnderDestruction(ev);
    } else {
        // check that the behavior should still run
        if ((shouldTerminate() == true) && (shouldDelete() == true)) {
            status = eventConsumed;
        } else {
            // the event guard is set -
            // use it to set mutual exclusion between Events and Triggered Operations
            // the m_eventGuard is set by the application when there is a guarded triggered operation
            //_mutex.lock();
            // actually handle the event

            status = processEvent(ev);
            // unlock the event guard
            //_mutex.unlock();

            // result with a status which indicates that the item had reached a terminate connector
            if (shouldTerminate()) {
                status = instanceReachTerminate;
            }
        }
    }
    return status;
    //#]
}

void OMReactive::handleEventNotQueued(IOxfEvent::Ptr &ev) {
    //#[ operation handleEventNotQueued(IOxfEvent)
    if (ev) {
        ev.reset();	// shouldDeleteAfterConsume is tested inside of the destroy function
    } else {
        // memory allocation failed for event-there is nothing to do here
    }
    //#]
}

void OMReactive::popNullTransition(void) {
    //#[ operation popNullTransition()

    //#]
}

void OMReactive::pushNullTransition(void) {
    //#[ operation pushNullTransition()

    //#]
}

bool OMReactive::send(const IOxfEvent::Ptr& ev) {
    //#[ operation send(IOxfEvent,IOxfEventGenerationParams)
    bool retCode = false;
    if (ev) {
        retCode = sendEvent(ev);
        if (retCode == false) {
            handleEventNotQueued(const_cast<IOxfEvent::Ptr&>(ev));
        }
    }
    return retCode;
    //#]
}

void OMReactive::setActiveContext(IOxfActive* context) {
    //#[ operation setActiveContext(IOxfActive)
    activeContext = context;
    //#]
}

void OMReactive::setActiveContext(IOxfActive* context, bool activeInstance) {
    //#[ operation setActiveContext(IOxfActive,bool)
    if (context != getActiveContext()) {
        setActive(activeInstance);
        setActiveContext(context);
    }
    // Make sure we have a context
    if (getActiveContext() == 0) {
        // The fallback is that the object is dispatched by the system thread.
        setActiveContext(&OMMainDispatcher::Instance());
    }
    //#]
}

bool OMReactive::shouldSupportDirectDeletion(void) const {
    //#[ operation shouldSupportDirectDeletion() const
    return (supportDirectDeletion || globalSupportDirectDeletion);
    //#]
}

bool OMReactive::startBehavior(void) {
    //#[ operation startBehavior()
    bool status;
    
    if (isUnderDestruction()) {
        status = false;
    } else {
#ifdef _OMINSTRUMENT
        AnimServices::notifyStartBehaviorBegin(this);
#endif

        if ((isBehaviorStarted() == false) ||
                (restartBehaviorEnabled() == true)) {
            setBehaviorStarted();
            // take the default transition
            rootState_entDef();
            // This takes care of transitions without triggering events
            if (shouldCompleteRun()) {
                // generate a dummy event in case the class doesn't receive any external events
                // this causes the runToCompletion() after the default transition to be taken -
                // in the class own thread (for active classes)
                setCompleteStartBehavior(true);

                //IOxfEvent::Ptr event = std::dynamic_pointer_cast<IOxfEvent>(theStartOrTerminationEvent);
                send(std::dynamic_pointer_cast<IOxfEvent>(theStartOrTerminationEvent));
            }
        }

        // and deleting the item if it reached a terminate connector
        bool toTerminate = shouldTerminate();
        if (toTerminate) {
            destroy();
        }


        status = !toTerminate;
    }
    return status;
    //#]
}

void OMReactive::handleNotConsumed(IOxfEvent::Ptr& /*ev*/, IOxfReactive::EventNotConsumedReason /*reason*/) {
    //#[ operation handleNotConsumed(IOxfEvent,EventNotConsumedReason)
    //#]
}

void OMReactive::handleTimeoutSetFailure(IOxfTimeout* timeout) {
    //#[ operation handleTimeoutSetFailure(IOxfTimeout)
    delete timeout;
    //#]
}

void OMReactive::handleTrigger(IOxfEvent::Ptr& ev) {
    //#[ operation handleTrigger(IOxfEvent)
    // mark as triggered operation
    ev->setSynchronous(true);
    (void)processEvent(ev);
    // deleting the item if it reached a terminate connector
    if ((shouldTerminate() == true) && (shouldDelete() == true)) {
        delete this;
    }
    //#]
}

bool OMReactive::hasWaitingNullTransitions(void) const {
    //#[ operation hasWaitingNullTransitions() const
    return ((state & nullTransitionMask) != 0U);
    //#]
}

bool OMReactive::isBehaviorStarted(void) const {
    //#[ operation isBehaviorStarted() const
    return ((state & behaviorStartedStateMask) != 0U);
    //#]
}

bool OMReactive::isUnderDestruction(void) const {
    //#[ operation isUnderDestruction() const
    return ((state & underDestructionStateMask) != 0U);
    //#]
}

IOxfReactive::TakeEventStatus OMReactive::processEvent(IOxfEvent::Ptr& ev) {
    //#[ operation processEvent(IOxfEvent)
    // the first received event, needs to perform runToCompletion(),
    // if in startBehavior() shouldCompleteStartBehavior() returned true.
    // for any other event shouldCompleteStartBehavior(), should return false.
    if (shouldCompleteStartBehavior()) {
        setCompleteStartBehavior(false);
        // protect from recursive Triggered Operation calls
        setBusy(true);
        runToCompletion();
        // end protection from recursive Triggered Operation calls
        setBusy(false);
    }
    
    // check that this is not the dummy OMStartBehaviorEvent event
    IOxfReactive::TakeEventStatus res = eventNotConsumed;
    if (ev->getId() != OMStartBehaviorEventId) {
        if (!isBusy()) {
            // protect from recursive Triggered Operation calls
            setBusy(true);
            // Store the event in the OMReactive instance
            setCurrentEvent(ev);
            // consume the event

            res = rootState_processEvent();

            // take null transitions (transitions without triggeres)
            if (shouldCompleteRun()) {
                runToCompletion();
            }
            // notify unconsumed event
            if (res == eventNotConsumed) {
                handleNotConsumed(ev, IOxfReactive::EventNotHandledByStatechart);
            }
            // done with this event
            //  setCurrentEvent(NULL);
            // end protection from recursive Triggered Operation calls
            setBusy(false);
        } else {
            handleNotConsumed(ev, IOxfReactive::StateMachineBusy);
        }
    } else {
        // the start behavior event is consumed by taking the 0 transitions
        // therefore it is always consumed
        res = eventConsumed;
    }

    return res;
    //#]
}

bool OMReactive::restartBehaviorEnabled(void) const {
    //#[ operation restartBehaviorEnabled() const
    return (supportRestartBehavior || globalSupportRestartBehavior);
    //#]
}

void OMReactive::rootState_entDef(void) {
    //#[ operation rootState_entDef()
    if (rootState != NULL) {
        if (rootState->active == 0) {
            rootState->entDef();
        }
    }
    //#]
}

IOxfReactive::TakeEventStatus OMReactive::rootState_processEvent(void) {
    //#[ operation rootState_processEvent()
    IOxfReactive::TakeEventStatus status = eventNotConsumed;
    
    if (isUnderDestruction()) {
        // Destruction had begun, so no more dispatching.
#ifdef _OMINSTRUMENT
        AnimServices::notifyError("Event ignored - Instance is under destruction\n\n");
#endif
    } else {
        if (rootState == NULL) {
#ifdef _OMINSTRUMENT
            AnimServices::notifyError("\nEvent ignored - Instance has no root state\n\n");
#endif
        } else {
            if (rootState->active != 0){
                status = rootState->active->handleEvent();
            } else {
#ifdef _OMINSTRUMENT
                AnimServices::notifyError("\nEvent ignored - Instance did not execute startBehavior()\n\n");
#endif
            }
        }
    }
    return status;
    //#]
}

void OMReactive::runToCompletion(void) {
    //#[ operation runToCompletion()
#if 0
    unsigned int nullStepCount = 0;
    bool breakCondition = false;
    
    // remember the real event, and relace it with a null event
    evReal = _currentEvent;
    OMNullEvent evNull;
    setCurrentEvent(&evNull);
    
    // If untriggered transitions are "hot" take them
    while ((breakCondition == false) && (hasWaitingNullTransitions() == true)) {
        ++nullStepCount;
        if ((maxNullSteps > 0) &&
                (nullStepCount > maxNullSteps)) {
            // Found infinite loop
            breakCondition = true;
        }
        else {
#ifdef _OMINSTRUMENT
            // notify a single step is about to be taken
            AnimServices::notifyNullTransition(this);
#endif 	// _OMINSTRUMENT
            // avoid event consumtion
            if ((isUnderDestruction() == true) ||
                    // No more null transitions to take
                    (rootState_processEvent() == eventNotConsumed)) {
                breakCondition = true;
            }
        }
    }
    
    // restore the real event
    setCurrentEvent(evReal);
    
    // Treat the infinite loop case
    if ((maxNullSteps > 0) &&
            (nullStepCount > maxNullSteps)) {
        state = state & (~nullTransitionMask);
    }
#endif
    //#]
}

std::shared_ptr<IOxfTimeout> OMReactive::scheduleTimeout(unsigned long delay, const char* targetStateName) {
    //#[ operation scheduleTimeout(unsigned long,Rhp_const_char_pt)
    // schedule timeout
    IOxfTimeout::Ptr timeout = std::dynamic_pointer_cast<IOxfTimeout>(std::make_shared<OMTimeout>(std::dynamic_pointer_cast<IOxfReactive>(shared_from_this()),
                                                                                 OMTimerManager::Instance(), OMTimerManager::Instance()._ioc, delay, targetStateName));
    if (timeout != NULL) {
        // Delegating the request to timer
            bool isSet = OMTimerManager::Instance().set(timeout);
    }
    return timeout;
    //#]
}

void OMReactive::setBehaviorStarted(void) {
    //#[ operation setBehaviorStarted()
    state |= behaviorStartedStateMask;
    //#]
}

void OMReactive::setCurrentEvent(IOxfEvent::Ptr& ev) {
    //#[ operation setCurrentEvent(IOxfEvent)
    _currentEvent = ev;
    //#]
}

void OMReactive::setUnderDestruction(void) {
    //#[ operation setUnderDestruction()
    state |= underDestructionStateMask;
    //#]
}

bool OMReactive::shouldCompleteRun(void) const {
    //#[ operation shouldCompleteRun() const
    return ((state & nullTransitionMask) != 0U);
    //#]
}

bool OMReactive::shouldCompleteStartBehavior(void) const {
    //#[ operation shouldCompleteStartBehavior() const
    return ((state & shouldCompleteStartBehaviorStateMask) != 0U);
    //#]
}

inline bool OMReactive::shouldTerminate(void) const {
    //#[ operation shouldTerminate() const
    return ((state & terminateConnectorReachedStateMask) != 0U);
    //#]
}

IOxfReactive::TakeEventStatus OMReactive::handleEventUnderDestruction(IOxfEvent::Ptr& ev) {
    //#[ operation handleEventUnderDestruction(IOxfEvent)
    if ((ev != NULL) &&
            ev->isTypeOf(OMReactiveTerminationEventId)) {
        if (shouldDelete()) {
            if (isDestroyEventResent()) {
                // second consumption
                // self termination event - do self destruction
                shared_from_this().reset();
            } else {
                // first consumption - resend
                // When destroy is called the reactive instance is set in under destruction mode
                //	that prevents sending of additional events and the terminate event is sent by the instance to itself.
                // The terminate event must be the last event sent to this instance and since the setting in under destruction mode is done without guarding
                //	(for performance considerations), the terminate event is reset after consumed on the first time to avoid a scenario where,
                //	due to task scheduling, another event is sent after the destroy event.
                // Sending the terminate event a second time prevents most scheduling races
                //	however it does not prevent all possible scenarios.
                // In case that your scheduler may stop a task in the middle of a regular code (without a blocking call)
                //	for indefinite time (that will let the reactive instance thread dispatch the terminate event twice),
                //	you should consider using the direct deletion policy.
                (void) send(std::dynamic_pointer_cast<IOxfEvent>(theStartOrTerminationEvent));
                setDestroyEventResent();
            }
        }
    }
    return instanceUnderDestruction;
    //#]
}

bool OMReactive::isDestroyEventResent(void) const {
    //#[ operation isDestroyEventResent() const
    return ((state & destroyEventResentStateMask) != 0U);
    //#]
}

bool OMReactive::sendEvent(const IOxfEvent::Ptr& ev) {
    //#[ operation sendEvent(IOxfEvent,IOxfEventGenerationParams)
    bool result = false;

    if ((isUnderDestruction() == true) &&
        (ev->isTypeOf(OMReactiveTerminationEventId) == false)) {
        // Destruction had begun,
        // ignore events

    } else {
        // Set the Receiver of the event
        IOxfActive* context = getActiveContext();
        if ((ev != NULL) && (context != NULL)) {
            ev->setDestination(shared_from_this());

            _strand.post(boost::bind(&OMMainDispatcher::execute,
                                          (OMMainDispatcher*)context,
                                          ev));
            result = true;
        }
    }
    return result;
    //#]
}

void OMReactive::setDestroyEventResent(void) {
    //#[ operation setDestroyEventResent()
    state |= destroyEventResentStateMask;
    //#]
}

int32_t OMReactive::getMaxNullSteps(void) {
    return maxNullSteps;
}

void OMReactive::setMaxNullSteps(int32_t p_maxNullSteps) {
    maxNullSteps = p_maxNullSteps;
}

bool OMReactive::isActive(void) const {
    return active;
}

bool OMReactive::getSupportDirectDeletion(void) const {
    return supportDirectDeletion;
}

void OMReactive::setSupportDirectDeletion(bool p_supportDirectDeletion) {
    supportDirectDeletion = p_supportDirectDeletion;
}

bool OMReactive::getGlobalSupportDirectDeletion(void) {
    return globalSupportDirectDeletion;
}

void OMReactive::setGlobalSupportDirectDeletion(bool p_globalSupportDirectDeletion) {
    globalSupportDirectDeletion = p_globalSupportDirectDeletion;
}

bool OMReactive::getSupportRestartBehavior(void) const {
    return supportRestartBehavior;
}

void OMReactive::setSupportRestartBehavior(bool p_supportRestartBehavior) {
    supportRestartBehavior = p_supportRestartBehavior;
}

bool OMReactive::getGlobalSupportRestartBehavior(void) {
    return globalSupportRestartBehavior;
}

void OMReactive::setGlobalSupportRestartBehavior(bool p_globalSupportRestartBehavior) {
    globalSupportRestartBehavior = p_globalSupportRestartBehavior;
}

IOxfActive* OMReactive::getActiveContext(void) const {
    return activeContext;
}

std::shared_ptr<IOxfEvent> OMReactive::getCurrentEvent(void) {
    auto ev = _currentEvent.lock();
    return ev;
}

uint32_t OMReactive::getReactiveInternalState(void) const {
    return state;
}

void OMReactive::setReactiveInternalState(uint32_t p_state) {
    state = p_state;
}

bool OMReactive::isBusy(void) const {
    return busy;
}

void OMReactive::setBusy(bool p_busy) {
    busy = p_busy;
}

void OMReactive::cleanUpRelations(void) {
    if(activeContext != NULL) {
        activeContext = NULL;
    }
    if(rootState != NULL) {
        rootState = NULL;
    }
}

void OMReactive::setActive(bool p_active) {
    active = p_active;
}




