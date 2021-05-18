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
//## dependency IOxfEvent
#include "IOxfEvent.h"
//## dependency IOxfTimeout
#include "IOxfTimeout.h"
#include "OMEventQueue.h"

//## dependency IOxfReactive
class IOxfReactive;

//## dependency IOxfTickTimerFactory
class IOxfTickTimerFactory;

//## dependency OMCore
class OMCore;

class IOxfActive;

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
class OMTimerManager {
    ////    Constructors and destructors    ////

public :

    // Initialize
    // Argument unsigned long ticktime = OMTimerManagerDefaults::defaultTicktime :
    // The tick-timer resolution
    // Argument const Rhp_uint32_t maxTM = OMTimerManagerDefaults::defaultMaxTM :
    // The maximum number of timeouts that can be active in the system
    // Argument bool isRealTimeModel = true :
    // Real-time vs. simulated-time mode
    //## operation OMTimerManager(unsigned long,Rhp_uint32_t,bool)
    OMTimerManager();


private :

    // disable copy CTOR and = operator
    // Argument const OMTimerManager& other :
    // The manager to copy
    //## operation OMTimerManager(OMTimerManager)
    explicit OMTimerManager(const OMTimerManager &other);

public :

    // Cleanup
    //## operation ~OMTimerManager()
    virtual ~OMTimerManager(void);

    ////    Operations    ////

    //## operation cleanup()
    void cleanup(void);

    // Remove canceled timeouts from the heap
    // Returns true is canceled timeouts were removed
    //## operation cleanupCanceledTimeouts(bool)
    bool cleanupCanceledTimeouts(bool withLock = true);

    // Singleton cleanup
    //## operation clearInstance()
    static void clearInstance(void);

    // Consume time  in simulated time model. It is needed for backward compatibility need.
    // Argument IOxfActive* const theContext = NULL :
    // active context,when thread is running on separate core
    //## operation consumeTime(unsigned long,unsigned long,IOxfActive)
    void consumeTime(unsigned long interval, unsigned long /*step*/, IOxfActive *const theContext = NULL);

    // Consume time  in simulated time model.
    // Argument IOxfActive* const theContext = NULL :
    // active context,when thread is running on separate core
    //## operation consumeTime(unsigned long,IOxfActive)
    void consumeTime(unsigned long interval, IOxfActive *const theContext = NULL);

    // Reduce the number of active threads
    //## operation decNonIdleThreadCounter()
    void decNonIdleThreadCounter(void);

    // Cleanup
    //## operation destroyTimer()
    inline void destroyTimer(void) {
        //#[ operation destroyTimer()
        this->~OMTimerManager();
        //#]
    }

    // Returns the elapsed time
    //## operation getElapsedTime() const
    unsigned long getElapsedTime(void) const;

    //## operation getNextTime()
    unsigned long getNextTime(void);

    // Advance the simulated/instrumentation time and send matured timeouts
    //## operation goNextAndPost()
    void goNextAndPost(void);

    // Initialize the timer manager
    //## operation init()
    // Get the singleton
    //## operation instance()
    static OMTimerManager &Instance();

    //## operation isExternalTimer() const
    bool isExternalTimer(void) const;


    //## operation resume()
    inline void resume(void) {
        //#[ operation resume()
        suspended = false;
        //#]
    }

    // set - adding a timeout to be managed
    // Argument IOxfTimeout* timeout :
    // The new timeout
    //## operation set(IOxfTimeout)
    bool set(IOxfTimeout::Ptr &timeout);

    void remove(IOxfTimeout::Ptr &timeout);

    // Update the time
    // Argument unsigned long newTime :
    // The new time
    //## operation setElapsedTime(unsigned long)
    void setElapsedTime(unsigned long newTime);

    // Design level debugging support - suspend time processing
    //## operation suspend()
    void suspend(void);

    // Send a matured timeout to its destination.
    // Also wakeup  completed delays.
    // Argument IOxfTimeout* timeout :
    // The matured timeout
    //## operation action(IOxfTimeout) const
    virtual void action(IOxfTimeout::Ptr &timeout);


private :

    // simulated time/instrumentation tick
    //## operation goNext()
    void goNext(void);

    // initialize the timeouts static memory pool
    //## operation initTimeoutsMemoryPool()
    static void initTimeoutsMemoryPool(void);

    // Disabled assignment operator
    // Argument const OMTimerManager& other :
    // The manager to copy
    //## operation operator=(OMTimerManager)
    OMTimerManager &operator=(const OMTimerManager &other);

    // handle the matured timeouts, and handle timer overflow
    //## operation post()
    void post(void);

    // Correct the timeouts due time and the time itself when the time_ field overflows.
    //## operation resetTimeoutsDueTime()
    void resetTimeoutsDueTime(void);

    // Set the timeout due time.
    // Done when the timeout is added to the manager based on the timeout delay and the current system time.
    // Argument IOxfTimeout* timeout :
    // The timeout
    //## operation setTimeoutDueTime(IOxfTimeout) const
    void setTimeoutDueTime(IOxfTimeout::Ptr &timeout) const;

    // respond to a tick
    //## operation timeTickCbk()
    void timeTickCbk(void);

    // Advances the time with the given 'currTime' time, and then post to see if any timeouts occured.
    // The main use for this function is for S_Function integration where Simulink supplies the time.
    //## operation timeTickCbkWithTime(unsigned long)
    void timeTickCbkWithTime(unsigned long currTime);

    ////    Additional operations    ////


public :

    //## auto_generated
    unsigned long getTick(void) const;

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

private :

    std::size_t _pollSize;

    OMEventQueue _timeouts;

    // The current system time
    unsigned long time_;        //## attribute time_

    // timer resolution, updated every tick ms and counts time
    unsigned long tick;        //## attribute tick

    // time model can be real or simulated
    bool realTimeModel;        //## attribute realTimeModel

    // Used by AOM to suspend/resume
    bool suspended;        //## attribute suspended

    // overflow watermark;
    //static const unsigned long overflowMark;		//## attribute overflowMark

    // Singleton state flag, used to identify that the singleton is destroyed (due to exit())
    static bool timerManagerSingletonDestroyed;        //## attribute timerManagerSingletonDestroyed

    //OMHeapType timeouts;		//## attribute timeouts

    // The number of active threads.
    // Used for simulated time support (a tick occur only when all the threads are idle).
    int64_t nonIdleThreadCounter;        //## attribute nonIdleThreadCounter

    static bool allowDestroy;        //## attribute allowDestroy

    static bool externalTimer;        //## attribute externalTimer

    // Real time value of timer step beginning.
    unsigned long tickStart;        //## attribute tickStart

    ////    Relations and components    ////

    OMOSMutex *guard;        //## link guard

    OMOSMutex *guardNonIdle;        //## link guardNonIdle

    OMOSTimer *tickTimer;        //## link tickTimer

};

#endif



