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


#ifndef omreactive_H
#define omreactive_H

//## dependency BasicTypes
#include "rawtypes.h"
//## dependency DllMacros
#include "rp_framework_dll_definition.h"
//## dependency Events
#include "OXFEvents.h"
//## dependency GenMacros
#include "OXFGenMacros.h"
//## dependency IOxfEvent
#include "IOxfEvent.h"
//## class OMReactive
#include "IOxfReactive.h"
//## dependency OMOSEventGenerationParams
#include "OMOSEventGenerationParams.h"
//## dependency StatechartMacros
#include "OXFStatechartMacros.h"
//## dependency AOMSState
class AOMSState;

//## dependency AnimServices
class AnimServices;

//## auto_generated
class IOxfActive;

//## dependency OMAnimReactive
class OMAnimReactive;

//## link rootState
class OMComponentState;

//## dependency OMMainThread
class OMMainThread;

//## dependency OMOS
class OMOS;

//## dependency OMOSThread
class OMOSThread;

//## link eventGuard
class OMProtected;

//## dependency OMThread
class OMThread;

//## dependency OMTimeout
class OMTimeout;

//## dependency OMTimerManager
class OMTimerManager;

//## dependency OXF
class OXF;

//## package Design::oxf::Core::CoreImplementation

//## class OMReactive
// The base IOxfReactive implementation
class RP_FRAMEWORK_DLL OMReactive : public IOxfReactive {
public :

    // Constant default values
    //## type Defaults
    enum Defaults {
        DEFAULT_MAX_NULL_STEPS = 100
    };
    

//#[ ignore
    // override new & delete operators
    OM_DECLARE_FRAMEWORK_MEMORY_ALLOCATION_OPERATORS
    
    
//#]

    ////    Constructors and destructors    ////
    
public :

    // Initialize the reactive instance
    // Argument IOxfActive* context = NULL :
    // the active context of the reactive class
    //## operation OMReactive(IOxfActive)
    explicit OMReactive(IOxfActive* context = NULL);
    
    // Virtual destructor to enable polymorphic deletion
    //## operation ~OMReactive()
    virtual ~OMReactive(void);
    
    ////    Operations    ////
    
    // Check if the provided event ID matches the current handled event.
    // Argument IOxfEvent::ID eventId :
    // The id to check
    //## operation IsCurrentEvent(ID) const
    bool IsCurrentEvent(IOxfEvent::ID eventId) const;
    
    // Cleanup specified timeout and nullifies its reference
    // Argument IOxfTimeout*& timeout :
    // the timeout to remove references to
    //## operation cancel(IOxfTimeout)
    void cancel(IOxfTimeout*& timeout);
    
    // cleanup the event queue in destruction, 
    // if the user modified the event queue - reactive relationship,
    // it must deal with the cleanup in its own code.
    //## operation cancelEvents() const
    void cancelEvents(void) const;
    
    // cleanup references to the specified timeout
    // Argument const IOxfTimeout* /*timeout*/ :
    // the timeout to remove references to
    //## operation cancelTimeout(IOxfTimeout)
    virtual bool cancelTimeout(const IOxfTimeout* /*timeout*/);
    
    // destroy the reactive instance (delete should never be called directly)
    //## operation destroy()
    virtual void destroy(void);
    
    // signal that the reactive instance reached a terminate connector
    //## operation endBehavior(const Rhp_const_char_pt aomArg())
    virtual void endBehavior(const Rhp_const_char_pt aomArg(theTerminator) = NULL);
    
    // Consume an event
    // Argument IOxfEvent* ev :
    // The event to handle
    //## operation handleEvent(IOxfEvent)
    virtual IOxfReactive::TakeEventStatus handleEvent(IOxfEvent* ev);
    
    // This function is called if event is not put into queue for some reason. 
    // It may be overridden in user reactive class to provide processing of this situation.
    // For example, user can destroy event, if event was created dynamically.
    //## operation handleEventNotQueued(IOxfEvent)
    virtual void handleEventNotQueued(IOxfEvent* const ev);
    
    // signal that a null transition was taken (called by the generated code)
    //## operation popNullTransition()
    virtual void popNullTransition(void);
    
    // signal that there is a null transition to be taken (called by the generated code)
    //## operation pushNullTransition()
    virtual void pushNullTransition(void);
    
    // states serialization (should be overridden in Flat code generation)
    // Argument AOMSState* aomsState :
    // The state vector
    //## operation rootState_serializeStates(AOMSState) const
    //#[ ignore
    #ifdef _OMINSTRUMENT
    
    //#]
    void rootState_serializeStates(AOMSState* aomsState) const;
    //#[ ignore
    
    #endif // _OMINSTRUMENT
    //#]
    
    // send an event to the active context queue
    // Argument IOxfEvent* ev :
    // The event to send
    // Argument const IOxfEventGenerationParams& params :
    // Sending parameters
    //## operation send(IOxfEvent,IOxfEventGenerationParams)
    virtual bool send(IOxfEvent* ev, const IOxfEventGenerationParams& params);
    
    // send the specified event to the instance active context queue
    // Argument IOxfEvent* ev :
    // The event to send
    //## operation send(IOxfEvent)
    virtual bool send(IOxfEvent* ev);
    
    // serialization of the active states vector
    // Argument AOMSState* aomsState :
    // The state vector
    //## operation serializeStates(AOMSState) const
    //#[ ignore
    #ifdef _OMINSTRUMENT
    
    //#]
    void serializeStates(AOMSState* aomsState) const;
    //#[ ignore
    
    #endif // _OMINSTRUMENT
    //#]
    
    // this operation is virtual and public in order to allow user to initialize 
    // nested embedded reactive components of active class manually
    // Rhapsody supports only one level of nesting for such cases.
    // The usage of the operation should be done with care.
    // Argument IOxfActive* context :
    // The active context (event dispatcher) of the reactive instance
    //## operation setActiveContext(IOxfActive)
    virtual void setActiveContext(IOxfActive* context);
    
    // Argument IOxfActive* context :
    // The active context (event dispatcher) of the reactive instance
    // Argument bool activeInstance :
    // should be true if the instance is active-reactive and false otherwise
    //## operation setActiveContext(IOxfActive,bool)
    void setActiveContext(IOxfActive* context, bool activeInstance);
    
    // set  the event guard by reference
    // Argument const OMProtected& guard :
    // The guard
    //## operation setEventGuard(OMProtected)
    void setEventGuard(const OMProtected& guard);
    
    // Mark the instance as dynamically or statically allocated
    // Argument bool flag :
    // The new value
    //## operation setShouldDelete(bool)
    void setShouldDelete(bool flag);
    
    // getter/setter for the shouldTerminate flag
    // Argument bool flag :
    // The new value
    //## operation setShouldTerminate(bool)
    inline void setShouldTerminate(bool flag) {
        //#[ operation setShouldTerminate(bool)
        if (flag) {
        	state |= terminateConnectorReachedStateMask;
        } else {
        	state &= ~terminateConnectorReachedStateMask;
        }
        //#]
    }
    
    // mark the reactive instance as guarded - to prevent mutual exclusion between the instance deletion and the event consumption
    // Argument bool flag :
    // The new value
    //## operation setToGuardReactive(bool)
    void setToGuardReactive(bool flag);
    
    // Check if the instance is dynamically allocated.
    //## operation shouldDelete() const
    inline bool shouldDelete(void) const {
        //#[ operation shouldDelete() const
        return ((state & deleteOnTerminateStateMask) != 0U);
        //#]
    }
    
    // Check if the instance should support direct deletion
    //## operation shouldSupportDirectDeletion() const
    bool shouldSupportDirectDeletion(void) const;
    
    // initialize the reactive instance state machine
    //## operation startBehavior()
    virtual bool startBehavior(void);
    

protected :

    // react to an event that was not consumed.
    // note that the event can be allocated on the stack.
    // Argument IOxfEvent* /*ev*/ :
    // The context event
    // Argument IOxfReactive::EventNotConsumedReason /*reason*/ :
    // The reason for the consumption failure
    //## operation handleNotConsumed(IOxfEvent,EventNotConsumedReason)
    virtual void handleNotConsumed(IOxfEvent* /*ev*/, IOxfReactive::EventNotConsumedReason /*reason*/);
    
    // This operation is called when the setting of a timeout failed.
    // This happens when the timer manager cannot add the timeout to the waiting timeouts heap
    // The user should override it in derived classes to handle the error.
    // For example the user may call OMTimerManager::instance()->cleanupCanceledTimeouts() and then retry setting the timeout
    //## operation handleTimeoutSetFailure(IOxfTimeout)
    virtual void handleTimeoutSetFailure(IOxfTimeout* timeout);
    
    // the entry-point for triggered operation consumption
    // Argument IOxfEvent* ev :
    // The call-event to handle
    //## operation handleTrigger(IOxfEvent)
    virtual void handleTrigger(IOxfEvent* ev);
    
    // check if there are null transitions to take
    //## operation hasWaitingNullTransitions() const
    bool hasWaitingNullTransitions(void) const;
    
    // getter/setter for the behavior started flag
    //## operation isBehaviorStarted() const
    bool isBehaviorStarted(void) const;
    
    // return true when the instance is under destruction
    //## operation isUnderDestruction() const
    bool isUnderDestruction(void) const;
    
    // events/triggered operations event consumption shared code
    // Argument IOxfEvent* ev :
    // The event to process
    //## operation processEvent(IOxfEvent)
    virtual IOxfReactive::TakeEventStatus processEvent(IOxfEvent* ev);
    
    // Checks if second call to startBehavior() should cause restart - i.e. restart of the statechart
    //## operation restartBehaviorEnabled() const
    bool restartBehaviorEnabled(void) const;
    
    // Take the statechart initial default transition(s).
    // In FLAT statechart code, expected to be overridden by the user class.
    //## operation rootState_entDef()
    virtual void rootState_entDef(void);
    
    // Dispatch the received event to the statechart.
    // In FLAT statechart code, expected to be overridden by the user class.
    //## operation rootState_processEvent()
    virtual IOxfReactive::TakeEventStatus rootState_processEvent(void);
    
    // take null transitions - called at the end of the event consumption
    //## operation runToCompletion()
    void runToCompletion(void);
    
    // schedule a timeout to be consumed by the reactive instance.
    // Argument OxfTimeUnit delay :
    // The time until the timeout will expire
    // Argument const Rhp_const_char_pt targetStateName = NULL :
    // The target state name (for design level debugging)
    //## operation scheduleTimeout(OxfTimeUnit,Rhp_const_char_pt)
    virtual IOxfTimeout* scheduleTimeout(OxfTimeUnit delay, const Rhp_const_char_pt targetStateName = NULL);
    
    // Mark that startBehavior() was called
    //## operation setBehaviorStarted()
    void setBehaviorStarted(void);
    
    // set the ShouldCompleteStartBehavior flag
    // Argument bool flag :
    // The flag value
    //## operation setCompleteStartBehavior(bool)
    inline void setCompleteStartBehavior(bool flag) {
        //#[ operation setCompleteStartBehavior(bool)
        if (flag) {
        	state |= shouldCompleteStartBehaviorStateMask;
        } else {
        	state &= ~shouldCompleteStartBehaviorStateMask;
        }
        //#]
    }
    
    // set the current event
    // Argument IOxfEvent* ev :
    // The event currently handled
    //## operation setCurrentEvent(IOxfEvent)
    void setCurrentEvent(IOxfEvent* ev);
    
    // Mark that the instance is being destroyed
    //## operation setUnderDestruction()
    void setUnderDestruction(void);
    
    // check if there are null transitions to take
    //## operation shouldCompleteRun() const
    bool shouldCompleteRun(void) const;
    
    // check if there are null transitions to take as part of startBehavior()
    //## operation shouldCompleteStartBehavior() const
    bool shouldCompleteStartBehavior(void) const;
    
    // Test if the reactive instance should terminate
    //## operation shouldTerminate() const
    inline bool shouldTerminate(void) const;
    

private :

    // Get the thread
    //## operation getThread() const
    OMThread* getThread(void) const;
    
    // Consume an event when the reaction instance is under destruction
    // Argument const IOxfEvent* ev :
    // The event to handle
    //## operation handleEventUnderDestruction(IOxfEvent)
    IOxfReactive::TakeEventStatus handleEventUnderDestruction(const IOxfEvent* ev);
    
    // Check if the theTerminateEvent was resent
    //## operation isDestroyEventResent() const
    bool isDestroyEventResent(void) const;
    
    // actually send an event to the active context queue
    // Argument IOxfEvent* ev :
    // The event to send
    // Argument const IOxfEventGenerationParams& params :
    // Sending parameters
    //## operation sendEvent(IOxfEvent,IOxfEventGenerationParams)
    bool sendEvent(IOxfEvent* ev, const IOxfEventGenerationParams& params);
    
    // Mark that the theTerminateEvent was resent
    //## operation setDestroyEventResent()
    void setDestroyEventResent(void);
    
    ////    Additional operations    ////
    

public :

    //## auto_generated
    static Rhp_int32_t getMaxNullSteps(void);
    
    //## auto_generated
    static void setMaxNullSteps(Rhp_int32_t p_maxNullSteps);
    
    //## auto_generated
    bool isActive(void) const;
    
    //## auto_generated
    bool getToGuardReactive(void) const;
    
    //## auto_generated
    bool getSupportDirectDeletion(void) const;
    
    //## auto_generated
    void setSupportDirectDeletion(bool p_supportDirectDeletion);
    
    //## auto_generated
    static bool getGlobalSupportDirectDeletion(void);
    
    //## auto_generated
    static void setGlobalSupportDirectDeletion(bool p_globalSupportDirectDeletion);
    
    //## auto_generated
    bool getSupportRestartBehavior(void) const;
    
    //## auto_generated
    void setSupportRestartBehavior(bool p_supportRestartBehavior);
    
    //## auto_generated
    static bool getGlobalSupportRestartBehavior(void);
    
    //## auto_generated
    static void setGlobalSupportRestartBehavior(bool p_globalSupportRestartBehavior);
    
    //## auto_generated
    virtual IOxfActive* getActiveContext(void) const;
    
    //## auto_generated
    virtual IOxfEvent* getCurrentEvent(void) const;
    
    //## auto_generated
    const OMProtected* getEventGuard(void) const;
    
    //## auto_generated
    void setEventGuard(const OMProtected* p_OMProtected);
    

protected :

    //## auto_generated
    Rhp_uint32_t getReactiveInternalState(void) const;
    
    //## auto_generated
    void setReactiveInternalState(Rhp_uint32_t p_state);
    
    //## auto_generated
    bool isBusy(void) const;
    
    //## auto_generated
    void setBusy(bool p_busy);
    
    //## auto_generated
    void cleanUpRelations(void);
    

private :

    //## auto_generated
    void setActive(bool p_active);
    
    ////    Attributes    ////
    
    // OMReactive state mask - the initial state
    static const Rhp_uint32_t defaultStateMask;		//## attribute defaultStateMask
    
    // OMReactive state mask - a null transition was found/taken
    static const Rhp_uint32_t nullTransitionStateMask;		//## attribute nullTransitionStateMask
    
    // OMReactive state mask - the max number of waiting null transitions that OMReactive can handle
    static const Rhp_uint32_t nullTransitionMask;		//## attribute nullTransitionMask
    
    // OMReactive state mask - the instance statechart reached a terminate connector
    static const Rhp_uint32_t terminateConnectorReachedStateMask;		//## attribute terminateConnectorReachedStateMask
    
    // OMReactive state mask - the instance is under destruction
    static const Rhp_uint32_t underDestructionStateMask;		//## attribute underDestructionStateMask
    
    // OMReactive state mask - the reactive instance should be deleted when a terminate connector is reached
    static const Rhp_uint32_t deleteOnTerminateStateMask;		//## attribute deleteOnTerminateStateMask
    
    // OMReactive state mask - need to complete the startBehavior() by a start behavior event
    static const Rhp_uint32_t shouldCompleteStartBehaviorStateMask;		//## attribute shouldCompleteStartBehaviorStateMask
    
    // OMReactive state mask - startBehavior() was called	
    static const Rhp_uint32_t behaviorStartedStateMask;		//## attribute behaviorStartedStateMask
    
    // Maximum number of null transitions allowed in a single take
    // infinite loop checker.
    static Rhp_int32_t maxNullSteps;		//## attribute maxNullSteps
    
    // The reactive internal state (bit field)
    Rhp_uint32_t state;		//## attribute state
    
    // The instance start behavior event.
    // This event is sent from the instance to itself when the default transition is followed by null transitions.
    OMStartBehaviorEvent theStartOrTerminationEvent;		//## attribute theStartOrTerminationEvent
    
    // This flag mark an active-reactive class
    bool active;		//## attribute active
    
    // This flag indicate that the reactive instance is currently handling an event.
    bool busy;		//## attribute busy
    
    // This flag indicate that the destruction of the reactive instance should be guarded against mutual exclusion - prevents deletion of the instance while processing an event.
    bool toGuardReactive;		//## attribute toGuardReactive
    
    // When set to true, the reactive class should support direct deletion.
    // The user can also set the globalSupportDirectDeletion attribute to affect all the reactive classes in the system.
    // The reactive instance will support direct deletion if either of the attributes is set to true.
    bool supportDirectDeletion;		//## attribute supportDirectDeletion
    
    // When set to true, all the reactive classes in the system should support direct deletion.
    // The user can also set the supportDirectDeletion attribute to affect a single reactive instance.
    // The reactive instance will support direct deletion if either of the attributes is set to true.
    static bool globalSupportDirectDeletion;		//## attribute globalSupportDirectDeletion
    
    // OMReactive state mask - indicate that theTerminateEvent was resent.
    // The terminate event is send twice to reduce the probability of a race between event sending on call to destroy().
    // When destroy is called the reactive instance is set in under destruction mode that prevents sending of additional events and the terminate event is sent by the instance to itself.
    // The terminate event must be the last event sent to this instance and since the setting in under destruction mode is done without guarding (for performance considerations), the terminate event is reset after consumed on the first time to avoid a scenario where, due to task scheduling, another event is sent after the destroy event.
    // Sending the terminate event a second time prevents most scheduling races however it does not prevent all possible scenarios.
    // In case that your scheduler may stop a task in the middle of a regular code (without a blocking call) for indefinite time (that will let the reactive instance thread dispatch the terminate event twice), you should consider using the direct deletion policy.
    static const Rhp_uint32_t destroyEventResentStateMask;		//## attribute destroyEventResentStateMask
    
    // When set to true the instance reacts to sequential calls of startBehavior() by reset of the statechart.
    // The user can also set the globalSupportRestartBehavior static attribute to apply this behavior to all the instances of OMReactive.
    bool supportRestartBehavior;		//## attribute supportRestartBehavior
    
    // When set to true all the instances of OMReactive reacts to sequential calls of startBehavior() by reset of the statechart.
    // The user can also set the instance supportRestartBehavior attribute to apply this behavior to specific instance.
    static bool globalSupportRestartBehavior;		//## attribute globalSupportRestartBehavior
    

public :

    // Static instance of OMOSEventGenerationParams for ISR generation
    static const OMOSEventGenerationParams isrParams;		//## attribute isrParams
    
    ////    Relations and components    ////
    

private :

    IOxfActive* activeContext;		//## link activeContext
    
    IOxfEvent* currentEvent;		//## link currentEvent
    
    const OMProtected* eventGuard;		//## link eventGuard
    

protected :

    OMComponentState* rootState;		//## link rootState
    
};

#endif



