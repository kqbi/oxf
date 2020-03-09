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


#ifndef OMTimerManager_H
#define OMTimerManager_H

//## auto_generated
#include "OXFTimeManagement.h"
//## class OMTimerManager
#include "IOxfAnimTimerManager.h"
//## dependency IOxfEvent
#include "IOxfEvent.h"
//## dependency IOxfTimeout
#include "IOxfTimeout.h"
//## dependency OMHeap
#ifndef OM_NO_TEMPLATES_USAGE
#include "omheap.h"
#endif // OM_NO_TEMPLATES_USAGE

//## dependency OMTimerManagerDefaults
#include "OMTimerManagerDefaults.h"
//## dependency OMUHeap
#ifdef OM_NO_TEMPLATES_USAGE
#include "omuheap.h"
#endif //OM_NO_TEMPLATES_USAGE
//## dependency AnimServices
class AnimServices;

//## dependency IOxfReactive
class IOxfReactive;

//## dependency IOxfTickTimerFactory
class IOxfTickTimerFactory;

//## dependency OMCore
class OMCore;

//## dependency OMDelay
class OMDelay;

//## link guard
class OMOSMutex;

//## link tickTimer
class OMOSTimer;

//## dependency OMThread
class OMThread;

//## dependency OMTimeout
class OMTimeout;

//## dependency OXF
class OXF;

//## package Design::oxf::Services::Time::TimeManagement

//## class OMTimerManager
// The timer manager is responsible for timeout bookkeeping and dispatching.
// In Extensive Timeout Management mode it is also responsible for timeouts canceling.
class OMTimerManager : public IOxfAnimTimerManager {
    ////    Constructors and destructors    ////
    
public :

    // Initialize
    // Argument OxfTimeUnit ticktime = OMTimerManagerDefaults::defaultTicktime :
    // The tick-timer resolution
    // Argument const Rhp_uint32_t maxTM = OMTimerManagerDefaults::defaultMaxTM :
    // The maximum number of timeouts that can be active in the system
    // Argument bool isRealTimeModel = true :
    // Real-time vs. simulated-time mode
    //## operation OMTimerManager(OxfTimeUnit,Rhp_uint32_t,bool)
    RP_FRAMEWORK_DLL OMTimerManager(OxfTimeUnit ticktime = OMTimerManagerDefaults::defaultTicktime, const Rhp_uint32_t
 maxTM = OMTimerManagerDefaults::defaultMaxTM, bool isRealTimeModel = true);
    

private :

    // disable copy CTOR and = operator
    // Argument const OMTimerManager& other :
    // The manager to copy
    //## operation OMTimerManager(OMTimerManager)
    RP_FRAMEWORK_DLL explicit OMTimerManager(const OMTimerManager& other);
    

public :

    // Cleanup
    //## operation ~OMTimerManager()
    RP_FRAMEWORK_DLL virtual ~OMTimerManager(void);
    
    ////    Operations    ////
    
    // advance the system time to the next waiting timeout
    //## operation advanceTime()
    RP_FRAMEWORK_DLL virtual void advanceTime(void);
    
    // the timer manager callback (activated by the tick-timer)
    // Argument void * me :
    // The timer manager
    //## operation cbkBridge(void *)
    RP_FRAMEWORK_DLL static void cbkBridge(void * me);
    
    // the timer manager callback with currTime(activated currently by OMSFunctionTimer)
    // Argument void * me :
    // The timer manager
    //## operation cbkBridgeWithTime(void *,OxfTimeUnit)
    RP_FRAMEWORK_DLL static void cbkBridgeWithTime(void * me, OxfTimeUnit currTime);
    
    //## operation cleanup()
    RP_FRAMEWORK_DLL void cleanup(void);
    
    // Remove canceled timeouts from the heap
    // Returns true is canceled timeouts were removed
    //## operation cleanupCanceledTimeouts(bool)
    RP_FRAMEWORK_DLL bool cleanupCanceledTimeouts(bool withLock = true);
    
    // Singleton cleanup
    //## operation clearInstance()
    RP_FRAMEWORK_DLL static void clearInstance(void);
    
    // Consume time  in simulated time model. It is needed for backward compatibility need.
    // Argument IOxfActive* const theContext = NULL :
    // active context,when thread is running on separate core 
    //## operation consumeTime(OxfTimeUnit,OxfTimeUnit,IOxfActive)
    RP_FRAMEWORK_DLL void consumeTime(OxfTimeUnit interval, OxfTimeUnit /*step*/, IOxfActive* const theContext = NULL);
    
    // Consume time  in simulated time model.
    // Argument IOxfActive* const theContext = NULL :
    // active context,when thread is running on separate core 
    //## operation consumeTime(OxfTimeUnit,IOxfActive)
    RP_FRAMEWORK_DLL void consumeTime(OxfTimeUnit interval, IOxfActive* const theContext = NULL);
    
    // Reduce the number of active threads
    //## operation decNonIdleThreadCounter()
    RP_FRAMEWORK_DLL void decNonIdleThreadCounter(void);
    
    // Cleanup
    //## operation destroyTimer()
    RP_FRAMEWORK_DLL inline void destroyTimer(void) {
        //#[ operation destroyTimer()
        this->~OMTimerManager();
        //#]
    }
    
    // Returns the elapsed time
    //## operation getElapsedTime() const
    RP_FRAMEWORK_DLL OxfTimeUnit getElapsedTime(void) const;
    
    //## operation getNextTime()
    RP_FRAMEWORK_DLL OxfTimeUnit getNextTime(void);
    
    // Advance the simulated/instrumentation time and send matured timeouts
    //## operation goNextAndPost()
    RP_FRAMEWORK_DLL void goNextAndPost(void);
    
    // Increase the number of active threads
    //## operation incNonIdleThreadCounter()
    RP_FRAMEWORK_DLL void incNonIdleThreadCounter(void);
    
    // Initialize the timer manager
    //## operation init()
    RP_FRAMEWORK_DLL virtual void init(void);
    
    // Lazy initialization of the timer manager singleton
    // Argument OxfTimeUnit ticktime = OMTimerManagerDefaults::defaultTicktime :
    // The tick-timer resolution
    // Argument const Rhp_uint32_t maxTM = OMTimerManagerDefaults::defaultMaxTM :
    // The maximum number of timeouts that can be active in the system
    // Argument bool isRealTimeModel = true :
    // Real-time vs. simulated-time mode
    //## operation initInstance(OxfTimeUnit,Rhp_uint32_t,bool)
    RP_FRAMEWORK_DLL static OMTimerManager* initInstance(OxfTimeUnit ticktime = OMTimerManagerDefaults::defaultTicktime
, const Rhp_uint32_t maxTM = OMTimerManagerDefaults::defaultMaxTM, bool isRealTimeModel = true);
    
    // Get the singleton
    //## operation instance()
    RP_FRAMEWORK_DLL static OMTimerManager* instance(void);
    
    //## operation isExternalTimer() const
    RP_FRAMEWORK_DLL bool isExternalTimer(void) const;
    
    //## operation isHeapFull() const
    RP_FRAMEWORK_DLL bool isHeapFull(void) const;
    
    // Start a guarded critical section
    //## operation lock() const
    RP_FRAMEWORK_DLL void lock(void) const;
    
    // A service to be notified after deltaT time.
    // Argument IOxfReactive* reactive :
    // The reactive requesting the service
    // Argument const OxfTimeUnit deltaT :
    // The requested time to elapse
    // Argument OxfTimeUnit& baseTime :
    // An output parameter containing the current time
    //## operation requestTimeNotification(IOxfReactive*,const OxfTimeUnit,IOxfTimeout*&,OxfTimeUnit&)
    RP_FRAMEWORK_DLL virtual void requestTimeNotification(IOxfReactive* reactive, const OxfTimeUnit deltaT
, IOxfTimeout*& timeout, OxfTimeUnit& baseTime);
    
    // Design level debugging support - resume time processing
    //## operation resume()
    RP_FRAMEWORK_DLL inline void resume(void) {
        //#[ operation resume()
        suspended = false; 
        //#]
    }
    
    // set - adding a timeout to be managed
    // Argument IOxfTimeout* timeout :
    // The new timeout
    //## operation set(IOxfTimeout)
    RP_FRAMEWORK_DLL bool set(IOxfTimeout* timeout);
    
    // Update the time
    // Argument OxfTimeUnit newTime :
    // The new time
    //## operation setElapsedTime(OxfTimeUnit)
    RP_FRAMEWORK_DLL void setElapsedTime(OxfTimeUnit newTime);
    
    // Design level debugging support - suspend time processing
    //## operation suspend()
    RP_FRAMEWORK_DLL void suspend(void);
    
    // End of the manager critical section
    //## operation unlock() const
    RP_FRAMEWORK_DLL void unlock(void) const;
    

protected :

    // Send a matured timeout to its destination.
    // Also wakeup  completed delays.
    // Argument IOxfTimeout* timeout :
    // The matured timeout
    //## operation action(IOxfTimeout) const
    RP_FRAMEWORK_DLL virtual void action(IOxfTimeout* timeout) const;
    

private :

    //## operation getNonIdleThreadCounter() const
    RP_FRAMEWORK_DLL inline Rhp_int64_t getNonIdleThreadCounter(void) const;
    
    // return a static instance of the timer manager
    //## operation getStaticTimerManager()
    RP_FRAMEWORK_DLL static OMTimerManager* getStaticTimerManager(void);
    
    // Create/get the timer manager singleton
    // Argument OxfTimeUnit tickTime :
    // The tick-timer resolution
    // Argument const Rhp_uint32_t maxTM :
    // The maximum number of timeouts that can be active in the system
    // Argument bool isRealTimeModel :
    // Real-time vs. simulated-time mode
    // Argument bool forceInitialization = false :
    // When true, reinitialize the singleton even if it was already initialized
    //## operation getStaticTimerManager(OxfTimeUnit,Rhp_uint32_t,bool,bool)
    RP_FRAMEWORK_DLL static OMTimerManager* getStaticTimerManager(OxfTimeUnit tickTime, const Rhp_uint32_t maxTM, bool
 isRealTimeModel, bool forceInitialization = false);
    
    // simulated time/instrumentation tick
    //## operation goNext()
    RP_FRAMEWORK_DLL void goNext(void);
    
    // initialize the timeouts static memory pool
    //## operation initTimeoutsMemoryPool()
    RP_FRAMEWORK_DLL static void initTimeoutsMemoryPool(void);
    
    // Start a guarded critical section
    //## operation lockNonIdle() const
    RP_FRAMEWORK_DLL void lockNonIdle(void) const;
    
    // Disabled assignment operator
    // Argument const OMTimerManager& other :
    // The manager to copy
    //## operation operator=(OMTimerManager)
    RP_FRAMEWORK_DLL OMTimerManager& operator=(const OMTimerManager& other);
    
    // handle the matured timeouts, and handle timer overflow
    //## operation post()
    RP_FRAMEWORK_DLL void post(void);
    
    // Correct the timeouts due time and the time itself when the time_ field overflows.
    //## operation resetTimeoutsDueTime()
    RP_FRAMEWORK_DLL void resetTimeoutsDueTime(void);
    
    //## operation setNonIdleThreadCounter(Rhp_int64_t)
    RP_FRAMEWORK_DLL inline void setNonIdleThreadCounter(Rhp_int64_t newCounter);
    
    // Set the timeout due time.
    // Done when the timeout is added to the manager based on the timeout delay and the current system time.
    // Argument IOxfTimeout* timeout :
    // The timeout
    //## operation setTimeoutDueTime(IOxfTimeout) const
    RP_FRAMEWORK_DLL void setTimeoutDueTime(IOxfTimeout* timeout) const;
    
    // respond to a tick
    //## operation timeTickCbk()
    RP_FRAMEWORK_DLL void timeTickCbk(void);
    
    // Advances the time with the given 'currTime' time, and then post to see if any timeouts occured.
    // The main use for this function is for S_Function integration where Simulink supplies the time. 
    //## operation timeTickCbkWithTime(OxfTimeUnit)
    RP_FRAMEWORK_DLL void timeTickCbkWithTime(OxfTimeUnit currTime);
    
    // End of the manager critical section
    //## operation unlockNonIdle() const
    RP_FRAMEWORK_DLL void unlockNonIdle(void) const;
    
    ////    Additional operations    ////
    

public :

    //## auto_generated
    OxfTimeUnit getTick(void) const;
    
    //## auto_generated
    bool getRealTimeModel(void) const;
    
    //## auto_generated
    bool getSuspended(void) const;
    
    //## auto_generated
    static bool getAllowDestroy(void);
    
    //## auto_generated
    static void setAllowDestroy(bool p_allowDestroy);
    
    //## auto_generated
    static void setExternalTimer(bool p_externalTimer);
    
    ////    Attributes    ////
    

private :

    // The current system time
    OxfTimeUnit time_;		//## attribute time_
    
    // timer resolution, updated every tick ms and counts time
    OxfTimeUnit tick;		//## attribute tick
    
    // time model can be real or simulated
    bool realTimeModel;		//## attribute realTimeModel
    
    // Used by AOM to suspend/resume
    bool suspended;		//## attribute suspended
    
    // overflow watermark;
    static const OxfTimeUnit overflowMark;		//## attribute overflowMark
    
    // Singleton state flag, used to identify that the singleton is destroyed (due to exit())
    static bool timerManagerSingletonDestroyed;		//## attribute timerManagerSingletonDestroyed
    
    OMHeapType timeouts;		//## attribute timeouts
    
    // The number of active threads. 
    // Used for simulated time support (a tick occur only when all the threads are idle).
    Rhp_int64_t nonIdleThreadCounter;		//## attribute nonIdleThreadCounter
    
    static bool allowDestroy;		//## attribute allowDestroy
    
    static bool instanceInitialized;		//## attribute instanceInitialized
    
    static bool externalTimer;		//## attribute externalTimer
    
    // Real time value of timer step beginning.
    OxfTimeUnit tickStart;		//## attribute tickStart
    
    ////    Relations and components    ////
    
    OMOSMutex* guard;		//## link guard
    
    OMOSMutex* guardNonIdle;		//## link guardNonIdle
    
    OMOSTimer* tickTimer;		//## link tickTimer
    
};

#endif



