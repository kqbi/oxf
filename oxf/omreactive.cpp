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
//## dependency AnimServices
//#[ ignore
#ifdef _OMINSTRUMENT
//#]
#include <aom/AnimServices.h>
//#[ ignore

#endif //_OMINSTRUMENT
//#]
//## auto_generated
#include "IOxfActive.h"
//## dependency NotifyMacros
#include "OXFNotifyMacros.h"
//## dependency OMAnimReactive
#include "OMAnimReactive.h"
//## link rootState
#include "state.h"
//## dependency OMMainThread
#include "OMMainThread.h"
//## dependency OMOS
#include "os.h"
//## link eventGuard
#include "omprotected.h"
//## dependency OMThread
#include "omthread.h"
//## dependency OMTimeout
#include "OMTimeout.h"
//## dependency OMTimerManager
#include "OMTimerManager.h"
// for backward compatibility mode
// 					
//## dependency OXF
#include "oxf.h"
//## package Design::oxf::Core::CoreImplementation

//## class OMReactive
const Rhp_uint32_t OMReactive::defaultStateMask = 0x00000000UL;

const Rhp_uint32_t OMReactive::nullTransitionStateMask = 0x00000001UL;

const Rhp_uint32_t OMReactive::nullTransitionMask = 0x0000FFFFUL;

const Rhp_uint32_t OMReactive::terminateConnectorReachedStateMask = 0x00010000UL;

const Rhp_uint32_t OMReactive::underDestructionStateMask = 0x00020000UL;

const Rhp_uint32_t OMReactive::deleteOnTerminateStateMask = 0x00040000UL;

const Rhp_uint32_t OMReactive::shouldCompleteStartBehaviorStateMask = 0x00080000UL;

const Rhp_uint32_t OMReactive::behaviorStartedStateMask = 0x00100000UL;

Rhp_int32_t OMReactive::maxNullSteps = DEFAULT_MAX_NULL_STEPS;

bool OMReactive::globalSupportDirectDeletion = false;

const Rhp_uint32_t OMReactive::destroyEventResentStateMask = 0x00200000UL;

bool OMReactive::globalSupportRestartBehavior = false;

const OMOSEventGenerationParams OMReactive::isrParams(true);

OMReactive::OMReactive(IOxfActive* context) : state(0U), active(false), busy(false), toGuardReactive(false), 
supportDirectDeletion(false), supportRestartBehavior(false), activeContext(0), currentEvent(0), eventGuard(0), 
rootState(0) {
    //#[ operation OMReactive(IOxfActive)
    OMReactive::setActiveContext(context, false);
    setShouldDelete(true);
    
    #ifdef _OMINSTRUMENT
    // register the reactive instance
    AnimServices::registerReactiveInstance(this, new OMAnimReactive(this));
    // register the start behavior event
    AnimServices::notifyFrameworkEventCreated(&theStartOrTerminationEvent);
    #endif
    //#]
}

OMReactive::~OMReactive(void) {
    //#[ operation ~OMReactive()
    // Mark that the object is under destruction. This is required
    setUnderDestruction();
    if (shouldSupportDirectDeletion()) {
    	// In case where the object is destructed from another thread.
    	if (!OMThread::isEndOfProcess()) {
    		// All events queued for this object need be "deleted".
    		if (!isActive()) {
    			cancelEvents();
    		}
    	}
    	if (toGuardReactive && (activeContext != NULL)) {
    		// toGuard should be set to true by the application class, if necessary
    		// unlock the thread guard taken in the beginning of the user class DTOR
    		getThread()->unlock();
    	}
    }
    #ifdef _OMINSTRUMENT
    AnimServices::notifyReactiveInstanceDeleted(this);
    #endif // _OMINSTRUMENT
    			
    
    //#]
    cleanUpRelations();
}

bool OMReactive::IsCurrentEvent(IOxfEvent::ID eventId) const {
    //#[ operation IsCurrentEvent(ID) const
    IOxfEvent* ev = currentEvent; 
    bool status;
    
    // ev might be null during destruction
    if (ev == NULL) {
    	status = false;
    } else {
        status = ev->isTypeOf(eventId);
    }
    return status;
    //#]
}

void OMReactive::cancel(IOxfTimeout*& timeout) {
    //#[ operation cancel(IOxfTimeout)
    if (timeout != NULL)
    {
      timeout->cancel();
      timeout = NULL;
    }
    //#]
}

void OMReactive::cancelEvents(void) const {
    //#[ operation cancelEvents() const
    #ifndef OM_DISABLE_DIRECT_REACTIVE_DELETION
    // ask my thread to cancel all the events that are targeted for me
    OMThread* itsOMThread = getThread();
    if (itsOMThread != NULL) {
    	itsOMThread->cancelPendingEvents(this);
    }
    #endif /* OM_DISABLE_DIRECT_REACTIVE_DELETION */
    //#]
}

bool OMReactive::cancelTimeout(const IOxfTimeout* /*timeout*/) {
    //#[ operation cancelTimeout(IOxfTimeout)
    return false;
    //#]
}

void OMReactive::destroy(void) {
    //#[ operation destroy()
    setUnderDestruction();
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
    //#]
}

void OMReactive::endBehavior(const Rhp_const_char_pt aomArg(theTerminator)) {
    //#[ operation endBehavior(const Rhp_const_char_pt aomArg())
    state |= terminateConnectorReachedStateMask;
    #ifdef _OMINSTRUMENT
    	AnimServices::notifyTerminateConnector(this, theTerminator);
    #endif // _OMINSTRUMENT
    //#]
}

IOxfReactive::TakeEventStatus OMReactive::handleEvent(IOxfEvent* ev) {
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
    		if (eventGuard != NULL) {
    			eventGuard->lock();
    		}
    #ifdef _OMINSTRUMENT
    		AnimServices::notifyHandleEventBegin(this, ev);
    #endif
    		// actually handle the event
    		status = processEvent(ev);
    
    		// unlock the event guard
    		if (eventGuard != NULL) {
    			eventGuard->unlock();
    		}
    
    		// result with a status which indicates that the item had reached a terminate connector
    		if (shouldTerminate()) {
    			status = instanceReachTerminate;
    		}
    #ifdef _OMINSTRUMENT
    		AnimServices::notifyHandleEventEnd(this, ev);
    #endif
          }
    	}
    return status;
    //#]
}

void OMReactive::handleEventNotQueued(IOxfEvent* const ev) {
    //#[ operation handleEventNotQueued(IOxfEvent)
    if (ev != NULL) 
    {
    	ev->destroy();	// shouldDeleteAfterConsume is tested inside of the destroy function
    }
    else 
    { 
    	// memory allocation failed for event-there is nothing to do here 
    }
    //#]
}

void OMReactive::popNullTransition(void) {
    //#[ operation popNullTransition()
    if ((state & nullTransitionMask)  == 0U) {
    	OM_NOTIFY_TO_ERROR("underflow in OMReactive less then 0 Null Configs\n");
    } else {
    	--state;
    }
    //#]
}

void OMReactive::pushNullTransition(void) {
    //#[ operation pushNullTransition()
    if ((state & nullTransitionMask) == nullTransitionMask) {
    	OM_NOTIFY_TO_ERROR("overflow in OMReactive too many active Null Configs\n");
    } else {
    	++state;
    }
    //#]
}

//#[ ignore
#ifdef _OMINSTRUMENT

//#]
void OMReactive::rootState_serializeStates(AOMSState* aomsState) const {
    //#[ operation rootState_serializeStates(AOMSState) const
    // serialize states from the class statechart 
    if (rootState != 0U) {
    	// call serialization for the root state
    	rootState->serializeStates(aomsState);
    }
    //#]
}
//#[ ignore


#endif // _OMINSTRUMENT
//#]

bool OMReactive::send(IOxfEvent* ev, const IOxfEventGenerationParams& params) {
    //#[ operation send(IOxfEvent,IOxfEventGenerationParams)
    bool retCode = false;
    if (ev != NULL)
    {
    	retCode = sendEvent(ev, params);
    	if (retCode == false)
    	{
    		handleEventNotQueued(ev);
    	}
    }
    return retCode; 
     
    //#]
}

bool OMReactive::send(IOxfEvent* ev) {
    //#[ operation send(IOxfEvent)
    #ifndef _OMINSTRUMENT
    	static OMOSEventGenerationParams params;
    #else
    	OMOSEventGenerationParams params;
    #endif
    return send(ev, params);
    //#]
}

//#[ ignore
#ifdef _OMINSTRUMENT

//#]
void OMReactive::serializeStates(AOMSState* aomsState) const {
    //#[ operation serializeStates(AOMSState) const
    AnimServices::addTerminateState(aomsState, shouldTerminate());
    //#]
}
//#[ ignore


#endif // _OMINSTRUMENT
//#]

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
    if (getActiveContext() == NULL) {
    	// The fallback is that the object is dispatched by the system thread.
    	setActiveContext(OMMainThread::instance());
    }
    //#]
}

void OMReactive::setEventGuard(const OMProtected& guard) {
    //#[ operation setEventGuard(OMProtected)
    setEventGuard(&guard);
    //#]
}

void OMReactive::setShouldDelete(bool flag) {
    //#[ operation setShouldDelete(bool)
    if (flag) {
    	state |= deleteOnTerminateStateMask;
    } else {
    	state &= ~deleteOnTerminateStateMask;		
    	OMThread* itsOMThread = getThread();
    	if ((itsOMThread != NULL) && (isActive() == true)) {
    		itsOMThread->setDeletionAllowed(false);
    	}
    }
    //#]
}

void OMReactive::setToGuardReactive(bool flag) {
    //#[ operation setToGuardReactive(bool)
    toGuardReactive = toGuardReactive || flag;
    OMThread* itsOMThread = getThread();
    if (itsOMThread != NULL) {
    	itsOMThread->setToGuardThread(flag);
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
    			(void) send(&theStartOrTerminationEvent);
    		}
    	}
       
    	// and deleting the item if it reached a terminate connector
    	bool toTerminate = shouldTerminate();
    	if (toTerminate) {
    		destroy();
    	}
    
    #ifdef _OMINSTRUMENT
    	AnimServices::notifyStartBehaviorEnd(this);
    #endif
        status = !toTerminate;
    	} 
    return status;
    //#]
}

void OMReactive::handleNotConsumed(IOxfEvent* /*ev*/, IOxfReactive::EventNotConsumedReason /*reason*/) {
    //#[ operation handleNotConsumed(IOxfEvent,EventNotConsumedReason)
    //#]
}

void OMReactive::handleTimeoutSetFailure(IOxfTimeout* timeout) {
    //#[ operation handleTimeoutSetFailure(IOxfTimeout)
    delete timeout;
    OM_NOTIFY_TO_ERROR("Could not create timeout. It is lost\n");
    //#]
}

void OMReactive::handleTrigger(IOxfEvent* ev) {
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

IOxfReactive::TakeEventStatus OMReactive::processEvent(IOxfEvent* ev) {
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
    		setCurrentEvent(NULL);
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
    Rhp_int32_t nullStepCount = 0;
    bool breakCondition = false;
    
    // remember the real event, and relace it with a null event
    IOxfEvent* evReal = currentEvent;
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
    #ifdef _OMINSTRUMENT
    	AnimServices::notifyError(this, "Infinite Loop of Null Transitions");
    #else
    	// notify the infinite loop for debugging
    	OM_NOTIFY_TO_ERROR("Exception - Infinite Loop of null transitions found\n");
    #endif // _OMINSTRUMENT
    }
    //#]
}

IOxfTimeout* OMReactive::scheduleTimeout(OxfTimeUnit delay, const Rhp_const_char_pt targetStateName) {
    //#[ operation scheduleTimeout(OxfTimeUnit,Rhp_const_char_pt)
    IOxfTimeout* timeout = NULL;
    
    OMTimerManager* sysTimer = OMTimerManager::instance();
    if (sysTimer != NULL) { 
    	// schedule timeout
    	timeout = new OMTimeout(this, delay, targetStateName);
    	if (timeout != NULL) {
    		// Delegating the request to timer
    		bool isSet = sysTimer->set(timeout);
    		if (!isSet) {
    			handleTimeoutSetFailure(timeout);
    			timeout = NULL;
    		}
    	    #ifdef _OMINSTRUMENT
    		else {
    			// notify the event queue of this
    			AnimServices::notifyTimeoutSet(timeout);
    		}
    		#endif
    	}
    }
    return timeout;
    //#]
}

void OMReactive::setBehaviorStarted(void) {
    //#[ operation setBehaviorStarted()
    state |= behaviorStartedStateMask;
    //#]
}

void OMReactive::setCurrentEvent(IOxfEvent* ev) {
    //#[ operation setCurrentEvent(IOxfEvent)
    currentEvent = ev;
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

OMThread* OMReactive::getThread(void) const {
    //#[ operation getThread() const
    return static_cast<OMThread*>(activeContext);
    //#]
}

IOxfReactive::TakeEventStatus OMReactive::handleEventUnderDestruction(const IOxfEvent* ev) {
    //#[ operation handleEventUnderDestruction(IOxfEvent)
    if ((ev != NULL) &&
    	ev->isTypeOf(OMReactiveTerminationEventId)) {
    	if (shouldDelete()) {
    		if (isDestroyEventResent()) {
    			// second consumption
    			// self termination event - do self destruction
    			delete this;
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
     			(void) send(&theStartOrTerminationEvent);
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

bool OMReactive::sendEvent(IOxfEvent* ev, const IOxfEventGenerationParams& params) {
    //#[ operation sendEvent(IOxfEvent,IOxfEventGenerationParams)
    bool result = false;
    
    if ((isUnderDestruction() == true) &&
    	(ev->isTypeOf(OMReactiveTerminationEventId) == false)) {
    	// Destruction had begun,
    	// ignore events
    
    #ifdef _OMINSTRUMENT
    	// Inside an interrupt request this code is not allowed
    	if (!params.getFromISR()) {
    		AnimServices::notifyError("Event sent to an under-destruction item is ignored.");
    	}
    #endif // _OMINSTRUMENT
    } else {
    #ifdef _OMINSTRUMENT
    	AnimServices::notifySendingEvent(ev, params);
    #endif // _OMINSTRUMENT
    	// Set the Receiver of the event
    	IOxfActive* context = getActiveContext();
    	if ((ev != NULL) && (context != NULL)) {
    		ev->setDestination(this);
    		result = context->queue(ev, params);    
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

Rhp_int32_t OMReactive::getMaxNullSteps(void) {
    return maxNullSteps;
}

void OMReactive::setMaxNullSteps(Rhp_int32_t p_maxNullSteps) {
    maxNullSteps = p_maxNullSteps;
}

bool OMReactive::isActive(void) const {
    return active;
}

bool OMReactive::getToGuardReactive(void) const {
    return toGuardReactive;
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

IOxfEvent* OMReactive::getCurrentEvent(void) const {
    return currentEvent;
}

const OMProtected* OMReactive::getEventGuard(void) const {
    return eventGuard;
}

void OMReactive::setEventGuard(const OMProtected* p_OMProtected) {
    eventGuard = p_OMProtected;
}

Rhp_uint32_t OMReactive::getReactiveInternalState(void) const {
    return state;
}

void OMReactive::setReactiveInternalState(Rhp_uint32_t p_state) {
    state = p_state;
}

bool OMReactive::isBusy(void) const {
    return busy;
}

void OMReactive::setBusy(bool p_busy) {
    busy = p_busy;
}

void OMReactive::cleanUpRelations(void) {
    if(activeContext != NULL)
        {
            activeContext = NULL;
        }
    if(currentEvent != NULL)
        {
            currentEvent = NULL;
        }
    if(eventGuard != NULL)
        {
            eventGuard = NULL;
        }
    if(rootState != NULL)
        {
            rootState = NULL;
        }
}

void OMReactive::setActive(bool p_active) {
    active = p_active;
}




