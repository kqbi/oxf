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
//	(c) Copyright IBM Corporation 2004, 2016. All Rights Reserved.
//	
//	Note to U.S. Government Users Restricted Rights:  
//	Use, duplication or disclosure restricted by GSA ADP Schedule 
//	Contract with IBM Corp.


#ifndef omthread_H
#define omthread_H

//## dependency Events
#include "OXFEvents.h"
//## class OMThread
#include "IOxfActive.h"
//## dependency IOxfEvent
#include "IOxfEvent.h"
//## dependency OMEventListType
#include "OXFAddTypes.h"
//## classInstance eventQueue
#include "OMEventQueue.h"
//## dependency OMOSThread
#include "os.h"
//## classInstance dispatchingGuard
#include "omprotected.h"
//## dependency AnimServices
class AnimServices;

//## dependency IOxfTimeout
class IOxfTimeout;

//## dependency OMCore
class OMCore;

//## dependency OMEvent
class OMEvent;

//## dependency OMMainThread
class OMMainThread;

//## dependency OMOS
class OMOS;

//## dependency OMOSEventGenerationParams
class OMOSEventGenerationParams;

//## dependency OMReactive
class OMReactive;

//## dependency OMThreadManager
class OMThreadManager;

//## dependency OMTimeout
class OMTimeout;

//## dependency OMTimerManager
class OMTimerManager;

//## dependency OXF
class OXF;

//## package Design::oxf::Core::CoreImplementation

//## class OMThread
// The base IOxfActive implementation 
class RP_FRAMEWORK_DLL OMThread : public IOxfActive {
public :

    // Initialize the  thread
    // Argument const Rhp_const_char_pt name = NULL :
    // The RTOS thread name
    // Argument const Rhp_int32_t priority = OMOSThread::DefaultThreadPriority :
    // The RTOS thread priority
    // Argument const Rhp_int32_t stackSize = OMOSThread::DefaultStackSize
    //   :
    // The RTOS thread stack size
    // Argument const Rhp_int32_t messageQueueSize = OMOSThread::DefaultMessageQueueSize :
    // The message queue size (number of messages)
    // Argument bool dynamicMessageQueue = true :
    // When true the message queue should grow when it is full
    //## operation OMThread(Rhp_const_char_pt,Rhp_int32_t,Rhp_int32_t,Rhp_int32_t,bool)
    OMThread(const Rhp_const_char_pt name = NULL, const Rhp_int32_t priority = OMOSThread::DefaultThreadPriority
, const Rhp_int32_t stackSize = OMOSThread::DefaultStackSize
     , const Rhp_int32_t messageQueueSize = OMOSThread::DefaultMessageQueueSize, bool dynamicMessageQueue = true);
    
    // Initialize the  thread
    // Argument bool wrapThread :
    // When true the thread should wrap the current RTOS thread instead of spawning a new one.
    //## operation OMThread(bool)
    explicit OMThread(bool wrapThread);
    
    //## operation OMThread(OMAffinity_t,OMPowerMode_t,Rhp_const_char_pt,Rhp_int32_t,Rhp_int32_t,Rhp_int32_t,bool)
    OMThread(const OMAffinity_t coreid, const OMPowerMode_t pwrMode = (OMPowerMode_t)0, const Rhp_const_char_pt name
 = NULL, const Rhp_int32_t priority = OMOSThread::DefaultThreadPriority, const Rhp_int32_t stackSize
 = OMOSThread::DefaultStackSize, const Rhp_int32_t messageQueueSize = OMOSThread::DefaultMessageQueueSize, bool
 dynamicMessageQueue = true);
    
    // Virtual destructor to enable polymorphic deletion
    //## operation ~OMThread()
    virtual ~OMThread(void);
    
    // Check if the thread can be deleted
    //## operation allowDeleteInThreadsCleanup()
    virtual bool allowDeleteInThreadsCleanup(void);
    
    // cancel event
    // Argument OMEvent* ev :
    // The event to cancel
    //## operation cancelEvent(OMEvent)
    //#[ ignore
    #ifndef OM_DISABLE_DIRECT_REACTIVE_DELETION
    
    //#]
    virtual void cancelEvent(OMEvent* ev);
    //#[ ignore
    
    #endif //!OM_DISABLE_DIRECT_REACTIVE_DELETION
    //#]
    
    // cancel all events targeted for destination			
    // Argument OMReactive* destination :
    // The reactive instance that all its pending events should be canceled
    //## operation cancelEvents(OMReactive)
    //#[ ignore
    #ifndef OM_DISABLE_DIRECT_REACTIVE_DELETION
    
    //#]
    virtual void cancelEvents(OMReactive* destination);
    //#[ ignore
    
    #endif //!OM_DISABLE_DIRECT_REACTIVE_DELETION
    //#]
    
    // Cancel an invent event in the queue.
    // This operation requires an ability to iterate over the events waiting in the queue.
    // Argument IOxfEvent* ev :
    // An event to cancel
    //## operation cancelPendingEvent(IOxfEvent)
    //#[ ignore
    #ifndef OM_DISABLE_DIRECT_REACTIVE_DELETION
    
    //#]
    virtual void cancelPendingEvent(IOxfEvent* ev);
    //#[ ignore
    
    #endif //!OM_DISABLE_DIRECT_REACTIVE_DELETION
    //#]
    
    // Cancel all events targeted for destination.
    // This operation requires an ability to iterate over the events waiting in the queue.	
    // Argument const IOxfReactive* destination :
    // A reactive instance to cancel all its pending events
    //## operation cancelPendingEvents(IOxfReactive)
    //#[ ignore
    #ifndef OM_DISABLE_DIRECT_REACTIVE_DELETION
    
    //#]
    virtual void cancelPendingEvents(const IOxfReactive* destination);
    //#[ ignore
    
    #endif //!OM_DISABLE_DIRECT_REACTIVE_DELETION
    //#]
    
    // Destroy all the active threads
    //## operation cleanupAllThreads()
    static OMThread* cleanupAllThreads(void);
    
    // Destroy the active instance.
    //## operation destroyThread()
    virtual void destroyThread(void);
    
    // end the active instance event dispatching and destroy the instance.
    //## operation endDispatching()
    virtual void endDispatching(void);
    
    // Get the thread event queue
    //## operation getEventQueue() const
    const OMEventQueue* getEventQueue(void) const;
    
    // Get the thread guard
    //## operation getGuard() const
    virtual const OMProtected& getGuard(void) const;
    
    // asking for a callback to end my os thread
    // onExecuteThread = true: I will kill my own thread
    // onExecuteThread = false: someone else will kill my thread
    // Argument OMOSThread::EndCallBack* clb_p :
    // The termination callback function
    // Argument void ** arg1_p :
    // An argument to the termination function
    // Argument bool onExecuteThread = true :
    // The context (this thread vs. other thread)
    //## operation getOSThreadEndClb(EndCallBack,void *,bool) const
    void getOSThreadEndClb(OMOSThread::EndCallBack* clb_p, void ** arg1_p, bool onExecuteThread = true) const;
    
    // get the OS thread handle
    //## operation getOsHandle() const
    void * getOsHandle(void) const;
    
    // Get the RTOS thread handle
    // Argument void *& osHandle :
    // The RTOS thread handle
    //## operation getOsHandle(void *) const
    void * getOsHandle(void *& osHandle) const;
    
    // Check to see if thread is at the end of the process
    //## operation isEndOfProcess()
    static bool isEndOfProcess(void);
    
    // Guard API
    //## operation lock() const
    void lock(void) const;
    
    // Queue the event for later processing
    // Argument IOxfEvent* ev :
    // the event to queue
    // Argument const IOxfEventGenerationParams& params :
    // Queuing parameters
    //## operation queue(IOxfEvent,IOxfEventGenerationParams)
    virtual bool queue(IOxfEvent* ev, const IOxfEventGenerationParams& params);
    
    // resume the thread
    //## operation resume()
    void resume(void);
    
    // Mutator for endOfProcess
    //## operation setEndOfProcess(bool)
    static void setEndOfProcess(bool aState);
    
    // set the thread priority
    // Argument const Rhp_int32_t pr :
    // The new priority
    //## operation setPriority(Rhp_int32_t)
    void setPriority(const Rhp_int32_t pr);
    
    // backward compatibility
    // Argument const Rhp_int32_t doFork = 0 :
    // When the value is other than 0, activate the event loop on a new thread.
    //## operation start(Rhp_int32_t)
    virtual void start(const Rhp_int32_t doFork = 0);
    
    // start the thread & the event loop - 
    // 
    // IMPORTANT: OMThread ignore start parameter!! 
    // 	the parameter should be checked only in default application threads (OMMainThread)
    // 
    // when creating an alternative default thread - 
    // 	when doFork is set to false, the framework is expected to use the OS main thread.
    // 	when doFork is set to true is should create a new thread.
    // 					
    // Argument bool /**/ = false :
    // ignored
    //## operation startDispatching(bool)
    virtual void startDispatching(bool /**/ = false);
    
    // Stop the execution of all the framework threads to enable unload of framework related modules (used for COM applications support)
    // Argument const OMThread* skipme :
    // The thread that initiate the call (should not be stopped in this call)
    //## operation stopAllThreads(OMThread)
    static OMThread* stopAllThreads(const OMThread* skipme);
    
    // suspend the thread
    //## operation suspend()
    void suspend(void);
    
    // Unlock the thread guard
    //## operation unlock() const
    void unlock(void) const;
    

protected :

    // cleanup - hook to allow cleanup of a thread without calling the DTOR
    // this method is needed to allow cleanup without destruction of the v-table
    //## operation cleanupThread()
    virtual void cleanupThread(void);
    
    // dispatch the specified event to its destination
    // Argument IOxfEvent* ev :
    // The event to dispatch
    //## operation dispatch(IOxfEvent)
    virtual IOxfReactive::TakeEventStatus dispatch(IOxfEvent* ev);
    
    // task entry method - calls execute
    // Argument void * me :
    // This thread - passed via the RTOS thread entry point
    //## operation doExecute(void *)
    static void doExecute(void * me);
    
    // The thread event loop
    //## operation execute()
    virtual OMReactive* execute(void);
    
    // Set the OSAL thread
    // Argument OMOSThread* thread :
    // The OSAL thread
    //## operation setOsThread(OMOSThread*)
    void setOsThread(OMOSThread* thread);
    

private :

    // cleanup - called from the DTOR and from cleanupThread()
    //## operation _cleanupThread()
    void _cleanupThread(void);
    
    // initialization
    // Argument bool wrapThread :
    // When true the thread should wrap the current RTOS thread instead of spawning a new one.
    // Argument const Rhp_const_char_pt name = NULL :
    // The RTOS thread name
    // Argument const Rhp_int32_t stackSize = OMOSThread::DefaultStackSize :
    // The RTOS thread stack size
    // Argument const Rhp_int32_t messageQueueSize = OMOSThread::DefaultMessageQueueSize :
    // The RTOS thread message queue size (number of messages)
    // Argument bool dynamicMessageQueue = true :
    // When true the message queue should grow when it is full
    //## operation _initializeOMThread(bool,Rhp_const_char_pt,Rhp_int32_t,Rhp_int32_t,bool)
    void _initializeOMThread(bool wrapThread, const Rhp_const_char_pt name = NULL, const Rhp_int32_t stackSize
 = OMOSThread::DefaultStackSize, const Rhp_int32_t messageQueueSize = OMOSThread::DefaultMessageQueueSize, bool
 dynamicMessageQueue = true);
    
    // Check if the event is canceled
    // Argument const IOxfEvent* ev :
    // The context event
    //## operation isCanceled(IOxfEvent) const
    bool isCanceled(const IOxfEvent* ev) const;
    
    // Check if the event is a framework control event
    // Argument const IOxfEvent* ev :
    // The context event
    //## operation isControlEvent(IOxfEvent) const
    bool isControlEvent(const IOxfEvent* ev) const;
    
    // Check if the event should be dispatched
    // Argument const IOxfEvent* ev :
    // The context event
    //## operation shouldDispatch(IOxfEvent) const
    bool shouldDispatch(const IOxfEvent* ev) const;
    

public :

    // set the os thread in DTOR flag
    // Argument const bool doIt :
    // The new value
    //## operation setEndOSThreadInDtor(bool) const
    inline void setEndOSThreadInDtor(const bool doIt) const {
        //#[ operation setEndOSThreadInDtor(bool) const
        if (osThread != NULL) {
        	osThread->setEndOSThreadInDtor(doIt);
        }
        //#]
    }
    
    //## operation setTheCore(OMCore)
    void setTheCore(OMCore* p_OMCore = NULL);
    
    //  assign this thread to existing or newly created OMCore instance.
    //## operation assignCoreId(OMAffinity_t)
    void assignCoreId(const OMAffinity_t myCoreId = (OMAffinity_t)0);
    
    // Argument bool wrapThread :
    // When true the thread should wrap the current RTOS thread instead of spawning a new one.
    // Argument const Rhp_const_char_pt name = NULL :
    // The RTOS thread name
    // Argument const Rhp_int32_t stackSize = OMOSThread::DefaultStackSize :
    // The RTOS thread stack size
    // Argument const Rhp_int32_t messageQueueSize = OMOSThread::DefaultMessageQueueSize :
    // The RTOS thread message queue size (number of messages)
    // Argument bool dynamicMessageQueue = true :
    // When true the message queue should grow when it is full
    //## operation reInitializeOMThread(bool,Rhp_const_char_pt,Rhp_int32_t,Rhp_int32_t,bool)
    void reInitializeOMThread(bool wrapThread, const Rhp_const_char_pt name = NULL, const Rhp_int32_t stackSize
 = OMOSThread::DefaultStackSize, const Rhp_int32_t messageQueueSize = OMOSThread::DefaultMessageQueueSize, bool
 dynamicMessageQueue = true);
    
    //## auto_generated
    bool getDeletionAllowed(void) const;
    
    //## auto_generated
    void setDeletionAllowed(bool p_deletionAllowed);
    
    //## auto_generated
    bool shouldGuardThread(void) const;
    
    //## auto_generated
    void setToGuardThread(bool p_toGuardThread);
    
    //## auto_generated
    bool getDispatching(void) const;
    
    //## auto_generated
    OMOSThread* getOsThread(void) const;
    
    //## auto_generated
    OMCore* getTheCore(void) const;
    

protected :

    //## auto_generated
    void cleanUpRelations(void);
    
    ////    Attributes    ////
    

private :

    // Indicator that prevents deletion of statically allocated objects.
    bool deletionAllowed;		//## attribute deletionAllowed
    
    // activate guard flag
    bool toGuardThread;		//## attribute toGuardThread
    
    // The event loop state, when the value becomes false the event loop is terminated and the thread is destroyed.
    bool processing;		//## attribute processing
    
    // This flag indicate that the application is terminating.
    static bool endOfProcess;		//## attribute endOfProcess
    
    // The event loop state, when the value becomes false the event loop will ignore all the events in the queue until the OMEndThreadEvent is received.
    bool dispatching;		//## attribute dispatching
    
    // The thread termination self event
    OMEndThreadEvent endThreadEvent;		//## attribute endThreadEvent
    
    // Since reactive instances are performing second dispatching of the termination event the active object must follow the same policy to enable reactive parts to finalize their self-destruction.
    // This attribute is used for this aim.
    bool finalTermination;		//## attribute finalTermination
    
    ////    Relations and components    ////
    

protected :

    // The event dispatching guard - prevents mutual exclusion between the event dispatching and instance deletion.
    OMProtected dispatchingGuard;		//## classInstance dispatchingGuard
    
    // The thread event queue
    OMEventQueue eventQueue;		//## classInstance eventQueue
    
    OMOSThread* osThread;		//## link osThread
    
    OMCore* theCore;		//## link theCore
    
};


//#[ ignore

// Include the declaration of OMMainThread
// for backward compatibility
#include "OMMainThread.h"

//#]

#endif



