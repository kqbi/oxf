//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: AbstractLayer
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


#ifndef os_H
#define os_H

//## dependency BasicTypes
#include "rawtypes.h"
//## dependency IOxfEventGenerationParams
#include "IOxfEventGenerationParams.h"
//## dependency Manager
#include "OXFManager.h"
//## dependency addTypes
#include "OXFAddTypes.h"
//## auto_generated
class OMOS;

//## dependency OMOSConnectionPort
class OMOSConnectionPort;

//## dependency OMOSEventFlag
class OMOSEventFlag;

//## auto_generated
class OMOSFactory;

//## dependency OMOSMessageQueue
class OMOSMessageQueue;

//## dependency OMOSMutex
class OMOSMutex;

//## dependency OMOSSemaphore
class OMOSSemaphore;

//## auto_generated
class OMOSSocket;

//## dependency OMOSThread
class OMOSThread;

//## dependency OMOSTimer
class OMOSTimer;

//## dependency OMSData
class OMSData;

//## dependency OMUList
class OMUList;

//## package Design::oxf::Adapters::AbstractLayer


//#[ ignore
// A generic adapter package.
// This adapter doesn't contain any implementation, instead it 
// describes the API so one can copy the adapter and add 
// specific implementation.
//#]

// Used by the connection port implementation
//## attribute MAX_LEN_STR
const Rhp_int32_t MAX_LEN_STR = 6;

//## package Design::oxf::Adapters::AbstractLayer

//## class OMOSMutex
// Mutex (binary semaphore) abstraction.
// The mutex must allow recursive lock policy.
// This means that once a thread obtained the mutex 
// it can call lock() any number of times and pass.
// The mutex is released only when the number of unlock() calls 
// is equal to the number of lock() calls done by the owner thread.
class RP_FRAMEWORK_DLL OMOSMutex {
//#[ ignore
    // override new & delete operators
    OM_DECLARE_FRAMEWORK_MEMORY_ALLOCATION_OPERATORS
    
//#]

    ////    Constructors and destructors    ////
    
public :

    // Virtual destructor to enable polymorphic deletion
    //## operation ~OMOSMutex()
    inline virtual ~OMOSMutex(void) {
        //#[ operation ~OMOSMutex()
        //#]
    }
    
    ////    Operations    ////
    
    // get the OS implementation
    //## operation getOsHandle() const
    virtual void * getOsHandle(void) const = 0;
    
    // obtain the mutex
    //## operation lock()
    virtual void lock(void) = 0;
    
    // release the mutex
    //## operation unlock()
    virtual void unlock(void) = 0;
    
};

//## package Design::oxf::Adapters::AbstractLayer

//## class OMOSEventFlag
// Event flag abstraction.
// Used for execution synchronization between threads.
// Initially the event flag should have no tokens - if the first call is to wait(), the caller should block.
class RP_FRAMEWORK_DLL OMOSEventFlag {
//#[ ignore
    // override new & delete operators
    OM_DECLARE_FRAMEWORK_MEMORY_ALLOCATION_OPERATORS
    
//#]

    ////    Constructors and destructors    ////
    
public :

    // Virtual destructor to enable polymorphic deletion
    //## operation ~OMOSEventFlag()
    inline virtual ~OMOSEventFlag(void) {
        //#[ operation ~OMOSEventFlag()
        //#]
    }
    
    ////    Operations    ////
    
    // get the real OS element
    //## operation getOsHandle() const
    virtual void * getOsHandle(void) const = 0;
    
    // Reset the event flag.
    // All waiting threads should be signaled.
    // The next call to wait() should block
    //## operation reset()
    virtual void reset(void) = 0;
    
    // Signal the first waiting thread.
    // If there are no threads waiting, increase the token count (following call to wait() pass without blocking).
    //## operation signal()
    virtual void signal(void) = 0;
    
    // Wait for a token or a timeout.
    // Argument const Rhp_int32_t aTimeout = -1 :
    // Wait timeout. t == -1 is wait forever
    //## operation wait(Rhp_int32_t)
    virtual void wait(const Rhp_int32_t aTimeout = -1) = 0;
    
};

//## package Design::oxf::Adapters::AbstractLayer

//## class OMOSSemaphore
// Semaphore abstraction.
// This class is not used by the framework.
// It is provided for the completeness of the OS abstraction.
class RP_FRAMEWORK_DLL OMOSSemaphore {
//#[ ignore
    // override new & delete operators
    OM_DECLARE_FRAMEWORK_MEMORY_ALLOCATION_OPERATORS
    
//#]

    ////    Constructors and destructors    ////
    
public :

    // Virtual destructor to enable polymorphic deletion
    //## operation ~OMOSSemaphore()
    inline virtual ~OMOSSemaphore(void) {
        //#[ operation ~OMOSSemaphore()
        //#]
    }
    
    ////    Operations    ////
    
    // get the real OS element
    //## operation getOsHandle() const
    virtual void * getOsHandle(void) const = 0;
    
    // signal the waiting threads
    //## operation signal()
    virtual void signal(void) = 0;
    
    // wait on the semaphore
    // Argument const Rhp_int64_t aTimeout = -1 :
    // wait timeout time in time units, -1 means forever
    //## operation wait(Rhp_int64_t)
    virtual bool wait(const Rhp_int64_t aTimeout = -1) = 0;
    
};

//## package Design::oxf::Adapters::AbstractLayer

//## class OMOSMessageQueue
// Message queue abstraction.
// The queue is expected to pass pointers to the messages rather than the data itself.
class RP_FRAMEWORK_DLL OMOSMessageQueue {
//#[ ignore
    // override new & delete operators
    OM_DECLARE_FRAMEWORK_MEMORY_ALLOCATION_OPERATORS
    
//#]

    ////    Constructors and destructors    ////
    
public :

    // Virtual destructor to enable polymorphic deletion
    //## operation ~OMOSMessageQueue()
    inline virtual ~OMOSMessageQueue(void) {
        //#[ operation ~OMOSMessageQueue()
        //#]
    }
    
    ////    Operations    ////
    
    // Get a message from the queue.
    // This is not a blocking call, it should return 0 if the queue is empty
    //## operation get()
    virtual void * get(void) = 0;
    
    // copy the messages in the queue into l
    // Argument OMListType& aList :
    // the list of messages in the queue
    //## operation getMessageList(OMListType& )
    virtual void getMessageList(OMListType& aList) = 0;
    
    // get the real OS element
    //## operation getOsHandle() const
    virtual void * getOsHandle(void) const = 0;
    
    // check if the queue is empty
    //## operation isEmpty() const
    virtual Rhp_int32_t isEmpty(void) const = 0;
    
    // check if the queue is full
    //## operation isFull() const
    virtual bool isFull(void) const = 0;
    
    // block until there are messages in the queue
    //## operation pend()
    virtual void pend(void) = 0;
    
    // Add a message to the queue
    // Argument void * /* msg */ :
    // The message
    // Argument const bool /* fromISR */ = false :
    // When true, the message is send in the context of an ISR
    //## operation put(void *,bool)
    inline virtual bool put(void * /* msg */, const bool /* fromISR */ = false) {
        //#[ operation put(void *,bool)
        return false;
        //#]
    }
    
    // put a message to the queue
    // Argument void * aMessage :
    // The message
    // Argument const IOxfEventGenerationParams& params :
    // Message sending parameters
    //## operation putMessage(void *,IOxfEventGenerationParams)
    inline virtual bool putMessage(void * aMessage, const IOxfEventGenerationParams& params) {
        //#[ operation putMessage(void *,IOxfEventGenerationParams)
        // Implementation added to support pre-5.1 adapters
        return put(aMessage, params.getFromISR());
        //#]
    }
    
    // set the thread that owns the queue (required in some adapters)
    // Argument void * /* process */ :
    // A handle to the process that own the message queue
    //## operation setOwnerProcess(void *)
    inline virtual void setOwnerProcess(void * /* process */) {
        //#[ operation setOwnerProcess(void *)
        //#]
    }
    
};

//## package Design::oxf::Adapters::AbstractLayer

//## class OMOSThread
// Thread abstraction.
// Either creates a new thread or represents an existing thread.
// When creating a new thread it should be blocked until the call to start().
class RP_FRAMEWORK_DLL OMOSThread {
public :

    // The end thread callback type
    //#[ type EndCallBack
    typedef void (*EndCallBack)(OMOSHandle);
    //#]
    
    // alias of EndCallBack
    //## type OMOSThreadEndCallBack
    typedef EndCallBack OMOSThreadEndCallBack;
    

//#[ ignore
    // override new & delete operators
    OM_DECLARE_FRAMEWORK_MEMORY_ALLOCATION_OPERATORS
    
//#]

    ////    Constructors and destructors    ////
    
public :

    // Virtual destructor to enable polymorphic deletion
    //## operation ~OMOSThread()
    inline virtual ~OMOSThread(void) {
        //#[ operation ~OMOSThread()
        //#]
    }
    
    ////    Operations    ////
    
    // Cleanup IP resources allocated for the thread (required by some adapters).
    //## operation CleanupCommunicationLayer()
    inline virtual void CleanupCommunicationLayer(void) {
        //#[ operation CleanupCommunicationLayer()
        //#]
    }
    
    // Initialize IP resources allocated for the thread (required by some adapters).
    //## operation InitCommunicationLayer()
    inline virtual void InitCommunicationLayer(void) {
        //#[ operation InitCommunicationLayer()
        //#]
    }
    
    // the following service returns true if it is invoked from the same 
    // os thread  as the one the object represents
    //## operation exeOnMyThread()
    virtual bool exeOnMyThread(void);
    
    //## operation getAffinity() const
    virtual OMAffinity_t getAffinity(void) const = 0;
    
    // get the real OS element
    //## operation getOsHandle() const
    virtual void * getOsHandle(void) const = 0;
    
    // pass the real OS element to the osHandle
    // Argument void *& osHandle :
    // The RTOS thread handle
    //## operation getOsHandle(void *) const
    virtual void * getOsHandle(void *& osHandle) const = 0;
    
    //## operation getPwrState() const
    virtual OMPowerMode_t getPwrState(void) const = 0;
    
    // get the thread termination call
    // Argument EndCallBack* clb_p :
    // the callback pointer
    // Argument void ** arg1_p :
    // argument to pass to the callback
    // Argument const bool onExecuteThread :
    // true: self termination
    // false: termination by another thread
    //## operation getThreadEndClbk(EndCallBack,void *,bool)
    virtual void getThreadEndClbk(EndCallBack* clb_p, void ** arg1_p, const bool onExecuteThread) = 0;
    
    // Reset the thread OS handle
    // Should be used with care and only for wrapper threads
    // Argument void * /*newHandle*/ :
    // The new OS handle
    //## operation resetWrapperThreadOsHandle(void *)
    inline virtual void resetWrapperThreadOsHandle(void * /*newHandle*/) {
        //#[ operation resetWrapperThreadOsHandle(void *)
        //#]
    }
    
    // resume suspended thread
    //## operation resume()
    virtual void resume(void) = 0;
    
    //## operation setAffinity(OMAffinity_t)
    virtual void setAffinity(const OMAffinity_t aff) = 0;
    
    // Mark the thread as under destruction
    // Argument const bool val :
    // When true the RTOS thread should be destroyed as part of the OMOSThread destructor.
    //## operation setEndOSThreadInDtor(bool)
    virtual void setEndOSThreadInDtor(const bool val) = 0;
    
    // set the thread priority
    // Argument const Rhp_int32_t pr :
    // The new priority
    //## operation setPriority(Rhp_int32_t)
    virtual void setPriority(const Rhp_int32_t pr) = 0;
    
    //## operation setPwrState(OMPowerMode_t)
    virtual void setPwrState(const OMPowerMode_t coreId) = 0;
    
    // Start the thread execution
    //## operation start()
    virtual void start(void) = 0;
    
    // Suspend the thread
    //## operation suspend()
    virtual void suspend(void) = 0;
    
    ////    Attributes    ////
    
    // The default message queue size
    static const Rhp_int32_t DefaultMessageQueueSize;		//## attribute DefaultMessageQueueSize
    
    // The default thread stack-size
    static const Rhp_int32_t DefaultStackSize;		//## attribute DefaultStackSize
    
    // The default thread priority
    static const Rhp_int32_t DefaultThreadPriority;		//## attribute DefaultThreadPriority
    
};

//## package Design::oxf::Adapters::AbstractLayer

//## class OMOSTimer
// A tick-timer abstraction.
// Represents a real-time timer that ticks for a specific duration, or an idle timer that ticks only when the system is idle.
// The idle timer is used for the time simulation feature.
class RP_FRAMEWORK_DLL OMOSTimer {
//#[ ignore
    // override new & delete operators
    OM_DECLARE_FRAMEWORK_MEMORY_ALLOCATION_OPERATORS
    
//#]

    ////    Constructors and destructors    ////
    
public :

    // Virtual destructor to enable polymorphic deletion
    //## operation ~OMOSTimer()
    inline virtual ~OMOSTimer(void) {
        //#[ operation ~OMOSTimer()
        //#]
    }
    
    ////    Operations    ////
    
    // get the real OS element
    //## operation getOsHandle() const
    virtual void * getOsHandle(void) const = 0;
    
    //## operation setAffinity(OMAffinity_t)
    virtual void setAffinity(const OMAffinity_t coreId) = 0;
    
};

//## package Design::oxf::Adapters::AbstractLayer

//## class OMOSSocket

//#[ ignore
#ifdef _OMINSTRUMENT

//#]


// Client socket abstraction
// Used for animation
class RP_FRAMEWORK_DLL OMOSSocket {
//#[ ignore
    // override new & delete operators
    OM_DECLARE_FRAMEWORK_MEMORY_ALLOCATION_OPERATORS
    
//#]

    ////    Constructors and destructors    ////
    
public :

    // Virtual destructor to enable polymorphic deletion
    //## operation ~OMOSSocket()
    inline virtual ~OMOSSocket(void) {
        //#[ operation ~OMOSSocket()
        //#]
    }
    
    ////    Operations    ////
    
    // close the socket
    //## operation Close()
    inline virtual void Close(void) {
        //#[ operation Close()
        //#]
    }
    
    // Create the socket.
    // Return the socket discriminator or 0 on error
    // Argument const Rhp_const_char_pt SocketAddress = 0 :
    // The IP address that the socket should connect to
    // Argument const Rhp_uint32_t nSocketPort = 0 :
    // The port that the socket should connect to
    //## operation Create(Rhp_const_char_pt,Rhp_uint32_t)
    virtual Rhp_int32_t Create(const Rhp_const_char_pt SocketAddress = 0, const Rhp_uint32_t nSocketPort = 0) = 0;
    
    // Receive a message from the socket (blocking)
    // Argument Rhp_char_pt lpBuf :
    // The message buffer
    // Argument const Rhp_int32_t nBufLen :
    // The message length
    //## operation Receive(Rhp_char_pt,Rhp_int32_t)
    virtual Rhp_int32_t Receive(Rhp_char_pt lpBuf, const Rhp_int32_t nBufLen) = 0;
    
    // Send a message via the socket (blocking)
    // Argument const Rhp_const_char_pt lpBuf :
    // The message buffer
    // Argument const Rhp_int32_t nBufLen :
    // The message length
    //## operation Send(Rhp_const_char_pt,Rhp_int32_t)
    virtual Rhp_int32_t Send(const Rhp_const_char_pt lpBuf, const Rhp_int32_t nBufLen) = 0;
    
};

#endif //_OMINSTRUMENT

//## package Design::oxf::Adapters::AbstractLayer

//## class OMOSConnectionPort
// This class provides the animation messaging acknowledge protocol with Rhapsody and a wrapper on the socket class.
class RP_FRAMEWORK_DLL OMOSConnectionPort {
//#[ ignore
    // override new & delete operators
    OM_DECLARE_FRAMEWORK_MEMORY_ALLOCATION_OPERATORS
    
//#]

    ////    Constructors and destructors    ////
    
public :

    // Virtual destructor to enable polymorphic deletion
    //## operation ~OMOSConnectionPort()
    inline virtual ~OMOSConnectionPort(void) {
        //#[ operation ~OMOSConnectionPort()
        //#]
    }
    
    ////    Operations    ////
    
    // Connect to the specified address and port
    // Argument const Rhp_const_char_pt SocketAddress = NULL :
    // the socket IP address
    // Argument const Rhp_uint32_t nSocketPort = 0U :
    // The port the socket should connect to
    //## operation Connect(Rhp_const_char_pt,Rhp_uint32_t)
    virtual Rhp_int32_t Connect(const Rhp_const_char_pt SocketAddress = NULL, const Rhp_uint32_t nSocketPort = 0U) = 0;
    
    // Send the data
    // Argument OMSData* aMessage :
    // The data to send
    //## operation Send(OMSData)
    virtual Rhp_int32_t Send(OMSData* aMessage) = 0;
    
    // Set the message handler for incoming messages.
    // Argument void (*dispfunc)(OMSData*) :
    // The dispatching function
    //## operation SetDispatcher(void (*)(OMSData*))
    virtual void SetDispatcher(void (*dispfunc)(OMSData*)) = 0;
    
};

//## package Design::oxf::Adapters::AbstractLayer

//## class OMOSFactory
// OS elements creation factory
class RP_FRAMEWORK_DLL OMOSFactory {
    ////    Constructors and destructors    ////
    
public :

    // Virtual destructor to enable polymorphic deletion
    //## operation ~OMOSFactory()
    inline virtual ~OMOSFactory(void) {
        //#[ operation ~OMOSFactory()
        //#]
    }
    
    ////    Operations    ////
    
    // Create the adapter implementation of the connection port
    //## operation createOMOSConnectionPort() const
    virtual OMOSConnectionPort* createOMOSConnectionPort(void) const = 0;
    
    // Create the adapter implementation of the event flag
    //## operation createOMOSEventFlag() const
    virtual OMOSEventFlag* createOMOSEventFlag(void) const = 0;
    
    // Create the adapter implementation of the idle timer (an idle timer send ticks only when the system is idle)
    // Argument void (*callback)(void*) :
    // The timer calls this function when a tick occurs
    // Argument void * param :
    // Argument for the callback function
    //## operation createOMOSIdleTimer(void (*)(void*),void *) const
    virtual OMOSTimer* createOMOSIdleTimer(void (*callback)(void*), void * param) const = 0;
    
    // Create the adapter implementation of the message queue
    // Argument const bool shouldGrow = true :
    // When true, the message queue should resize itself when full
    // Argument const Rhp_int32_t messageQueueSize = OMOSThread::DefaultMessageQueueSize :
    // The initial size of the message queue (number of messages)
    //## operation createOMOSMessageQueue(bool,Rhp_int32_t) const
    virtual OMOSMessageQueue* createOMOSMessageQueue(const bool shouldGrow = true, const Rhp_int32_t messageQueueSize
 = OMOSThread::DefaultMessageQueueSize) const = 0;
    
    // Create the adapter implementation of the mutex
    //## operation createOMOSMutex() const
    virtual OMOSMutex* createOMOSMutex(void) const = 0;
    
    // Create the adapter implementation of the semaphore
    // Argument const Rhp_uint64_t semFlags = 0U :
    // Implementation-specific initialization flags
    // Argument const Rhp_uint64_t initialCount = 1U :
    // The initial number of available tokens
    // Argument const Rhp_uint64_t maxCount = 1U :
    // The maximum number of available tokens
    // Argument const Rhp_const_char_pt name = NULL :
    // The semaphore name
    //## operation createOMOSSemaphore(Rhp_uint64_t,Rhp_uint64_t,Rhp_uint64_t,const Rhp_const_char_pt ) const
    virtual OMOSSemaphore* createOMOSSemaphore(const Rhp_uint64_t semFlags = 0U, const Rhp_uint64_t initialCount = 1U
, const Rhp_uint64_t maxCount = 1U, const Rhp_const_char_pt name = NULL) const = 0;
    
    // Create the adapter implementation of the thread
    // Argument void (*entryFunction)(void*) :
    // The thread entry function
    // Argument void * param :
    // Argument to the entry function
    // Argument const Rhp_const_char_pt threadName = NULL :
    // The thread name
    // Argument const Rhp_int32_t stackSize = OMOSThread::DefaultStackSize :
    // The thread stack size
    //## operation createOMOSThread(void (*)(void*),void *,const Rhp_const_char_pt ,Rhp_int32_t) const
    virtual OMOSThread* createOMOSThread(void (*entryFunction)(void*), void * param, const Rhp_const_char_pt threadName
 = NULL, const Rhp_int32_t stackSize = OMOSThread::DefaultStackSize) const = 0;
    
    // Create the adapter implementation of the real-time timer
    // Argument const OxfTimeUnit time :
    // The time between timer ticks
    // Argument void (*callback)(void*) :
    // The timer calls this function when a tick occurs
    // Argument void * param :
    // Argument for the callback function
    //## operation createOMOSTickTimer(OxfTimeUnit,void (*)(void*),void *) const
    virtual OMOSTimer* createOMOSTickTimer(const OxfTimeUnit time, void (*callback)(void*), void * param) const = 0;
    
    // Create the adapter implementation of the wrapper thread (an OMOSThread representation of a thread that already exist in the system).
    // Argument void * osHandle :
    // The RTOS thread handle that the OMOSThread should be associated with.
    //## operation createOMOSWrapperThread(void *) const
    virtual OMOSThread* createOMOSWrapperThread(void * osHandle) const = 0;
    
    // Make the current thread delay (blocking) for the specified time.
    // Argument const OxfTimeUnit ms :
    // the delay time in the adapter time resolution
    //## operation delayCurrentThread(OxfTimeUnit) const
    virtual void delayCurrentThread(const OxfTimeUnit ms) const = 0;
    
    // return the current thread OS handle (id)
    //## operation getCurrentThreadHandle() const
    virtual void * getCurrentThreadHandle(void) const = 0;
    
    // Create the OSFactory (replaces V3.0 global function theOSFactory())
    //## operation instance()
    static OMOSFactory* instance(void);
    
    // wait for a thread to terminate
    // Argument void * osHandle :
    // the thread to wait for
    // Argument const OxfTimeUnit ms :
    // timeout time
    //## operation waitOnThread(void *,OxfTimeUnit) const
    virtual bool waitOnThread(void * osHandle, const OxfTimeUnit ms) const = 0;
    
};


//#[ ignore

#define OXFTDelay(timInMs) OMOSFactory::instance()->delayCurrentThread((timInMs))
//#]

//## package Design::oxf::Adapters::AbstractLayer

//## class OMOS
// Utility class for general RTOS services
// The implementation of these services is done at the adapter level by writing the operation bodies.
class RP_FRAMEWORK_DLL OMOS {
    ////    Operations    ////
    
public :

    // os-specific actions to take at the end of OXFInit 
    // after the environment is set (i.e. main thread, timer etc) 
    // and before return from the function
    // Argument const Rhp_int32_t errorCode :
    // The exit code
    //## operation endApplication(Rhp_int32_t)
    static void endApplication(const Rhp_int32_t errorCode);
    
    // Called just before terminating the application.
    // Allow adapter to specific tasks that should be done before termination.
    //## operation endProlog()
    static void endProlog(void);
    
    // Called at the end of OXF::init() to allow adapter specific initializations.
    //## operation initEpilog()
    static void initEpilog(void);
    
};

#endif



