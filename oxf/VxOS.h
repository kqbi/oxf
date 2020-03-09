#ifndef _vxos_H
#define _vxos_H
//
//	file name   :	$Source: R:/StmOO/Master/cg/LangCpp/oxf/rcs/VxOS.h $
//	file version:	$Revision: 1.43 $
//
//	purpose:	
//
//	author(s):	Eran Gery
//	date started:	
//	date changed:	$Date: 2007/05/28 07:43:51 $
//	last change by:	$Author: ilvler $
//
//	Licensed Materials - Property of IBM
//	(c) Copyright IBM Corporation 1996, 2016. All Rights Reserved.
//	
//	Note to U.S. Government Users Restricted Rights:  
//	Use, duplication or disclosure restricted by GSA ADP Schedule 
//	Contract with IBM Corp.
// ---------------------------------------------------------------
//|                                vxos.h                        |
// --------------------------------------------------------------- 


#include <vxWorks.h>
#include <version.h>
#include <sysLib.h>
#include <taskLib.h>
#include <msgQLib.h>
#include <semLib.h>
#include <stdarg.h>
#include <stdio.h>

#if ((_WRS_VXWORKS_MAJOR >5) && (_WRS_VXWORKS_MINOR >5))
#include <cpuset.h>
#ifdef _WRS_KERNEL
#if (_WRS_VXWORKS_MINOR >8)
#include <perfMgrLib.h>
#else
#include <cpuPwrLib.h>
#endif
#endif
#endif
// Rhapsody Framework Includes
#include "omtypes.h"
#include "os.h"


#define PRIORITY_HIGH         1
#define PRIORITY_NORMAL     100
#define PRIORITY_LOW        255     /* lowest priority is 255 */
#define MQ_DEFAULT_SIZE     100     /* queue default size */
#define SMALL_STACK       10000
#define DEFAULT_STACK     20000


class VxTimer : public OMOSTimer {
private:
    void (*cbkfunc)(void*);
    void waitThread();
    static void bridge(VxTimer* me);
    OMTaskHandle hThread;    // The timeTick thread 
    timeUnit m_Time;
    void *param;
	  timeUnit ticks;      // how many OS ticks the timer wakes up  
	static char TimerName[6]; //A string to store the name of the timer.

public:
    VxTimer(const timeUnit ptime, void pcbkfunc(void*), void* pparam); // TickTimer
    VxTimer(void pcbkfunc(void*), void *pparam);    // IdleTimer (Simulated Time) 
    virtual ~VxTimer();
    virtual void* getOsHandle() const { 
        return reinterpret_cast<void*>(hThread);
    }
    virtual void setAffinity(const OMAffinity_t aff);
};


class VxOSEventFlag : public OMOSEventFlag {
private:
    SEM_ID hEventFlag;
public:
    virtual void signal();
    virtual void reset();
    virtual void wait(const Rhp_int32_t tminms = -1);  // tminms = -1 is wait forever
    VxOSEventFlag();
    ~VxOSEventFlag();
    virtual void* getHandle() const { 
        return reinterpret_cast<void*>(hEventFlag);
    }
    virtual void* getOsHandle() const {
        return reinterpret_cast<void*>(hEventFlag);
    }
};

/////////////////
/////////////////

class VxThread : public OMOSThread {
private:
    OMTaskHandle hThread;
    Rhp_int32_t isWrapperThread;
    OMBoolean endOSThreadInDtor; // TRUE means that the os thread is ended as part of this object's destruction

    	// preExecFunc takes control upon contruction to suspend the task untill
    // it is activated by start
    static void preExecFunc(void* me);
    void (*m_ExecFunc)(void*);
    void* m_ExecParam;
    VxOSEventFlag* m_SuspEventFlag;

public:
    VxThread( void tfunc(void *),
              void *param,
              const Rhp_const_char_pt name = NULL,
              const Rhp_int32_t stackSize = OMOSThread::DefaultStackSize );
    VxThread(void* osThreadId); // for creation of wrapper thread
    virtual ~VxThread();

    virtual void setPriority(const Rhp_int32_t aPriority) {
        if (ERROR == taskPrioritySet(hThread, aPriority)) {
            OM_NOTIFY_ERROR("taskPrioritySet", "VxThread::setPriority")
        }
    }

    virtual void suspend() {
        if (ERROR == taskSuspend(hThread)) {
            OM_NOTIFY_ERROR("taskSuspend", "VxThread::suspend")
        }
    }

    virtual void resume() {
        if (ERROR == taskResume(hThread))	{
            OM_NOTIFY_ERROR("taskResume","VxThread::resume")
        }
    }

    virtual void start();

    virtual void setEndOSThreadInDtor(const OMBoolean val) {
        endOSThreadInDtor = val;
    }

    virtual void* getOsHandle() const { 
        return reinterpret_cast<void*>(hThread);
    }

    virtual void* getOsHandle(void*& osHandle) const{
        osHandle = reinterpret_cast<void*>(hThread);
        return getOsHandle();
    }

  // Reset the thread OS handle
  // Should be used with care and only for wrapper threads
  // Argument void * newHandle : 
  // The new OS handle
  virtual void resetWrapperThreadOsHandle(void* newHandle);


    // asking for a callback to end my os thread
    // onExecuteThread = TRUE: I will kill my own thread
    // onExecuteThread = FALSE: someone else will kill my thread
    virtual void getThreadEndClbk( OMOSThreadEndCallBack* clb_p,    // a pointer to the callback function
                                   void ** arg1_p,                  // the argument for this function
                                   const OMBoolean onExecuteThread );
    // end the thread I'm working on
    static void endMyThread(void *);

    // end a thread which is NOT my thread
    static void endOtherThread(void *);

    //## operation getAffinity()
    virtual OMAffinity_t getAffinity(void) const; 
	    
    //## operation setAffinity(OMAffinity_t)
    virtual void setAffinity(const OMAffinity_t aff);

    virtual OMPowerMode_t getPwrState(void) const;

    virtual void setPwrState(const OMPowerMode_t val);

	static void setThreadAffinity(OMTaskHandle m_hThread, const OMAffinity_t coreId);


}; // VxThread

class VxMutex : public OMOSMutex {
private:
    SEM_ID  hMutex;

public:
    virtual void lock() {
        if (ERROR == semTake(hMutex, WAIT_FOREVER)) {
            OM_NOTIFY_ERROR("semTake", "VxMutex::lock")
        }
    }

    virtual void unlock() {
        if (ERROR == semGive(hMutex)) {
            OM_NOTIFY_ERROR("semGive", "VxMutex::unlock")
        }
    }

    VxMutex() { 
        hMutex = semMCreate(SEM_Q_PRIORITY | SEM_INVERSION_SAFE);
        if (NULL == hMutex) {
            OM_NOTIFY_ERROR("semMCreate", "VxMutex::VxMutex")
        }
    } 

    ~VxMutex() {
        if (ERROR == semDelete(hMutex))	{
            OM_NOTIFY_ERROR("semDelete", "VxMutex::~VxMutex")
        }
    }

    virtual void* getHandle() const {
        return reinterpret_cast<void*>(hMutex);
    }
    virtual void* getOsHandle() const {
        return reinterpret_cast<void*>(hMutex);
    }
};

/////////////
/////////////
class VxOSMessageQueue : public OMOSMessageQueue {
private:
    MSG_Q_ID hVxMQ;
    void *pmessage; // Buffer of a single lookahead message 
    enum { dataReady, noData } m_State;

public:
    VxOSMessageQueue(const Rhp_int32_t messageQueueSize = OMOSThread::DefaultMessageQueueSize): m_State(noData)	{
        hVxMQ = msgQCreate(static_cast<Rhp_int32_t>(messageQueueSize), sizeof(void*), MSG_Q_FIFO);
        if (hVxMQ == 0) {
            OM_NOTIFY_ERROR("msgQCreate","VxOSMessageQueue::VxOSMessageQueue")
        }
    }

    ~VxOSMessageQueue() {
        if (hVxMQ) {
            if (ERROR == msgQDelete(hVxMQ)) {
                OM_NOTIFY_ERROR("msgQDelete", "VxOSMessageQueue::~VxOSMessageQueue")
            }
            hVxMQ = 0;
        }
    }

    virtual OMBoolean put(void* aMessage, const OMBoolean fromISR = FALSE);
    virtual void* get();
    virtual Rhp_int32_t isEmpty() const ;
    virtual void pend();
    virtual void getMessageList(OMListType& aList);
    virtual OMBoolean isFull() const;
    virtual void* getOsHandle() const {
        return reinterpret_cast<void*>(hVxMQ);
    }
};

#ifdef _OMINSTRUMENT

class VxSocket: public OMOSSocket {
private:
    Rhp_int32_t theSock;
public:
    VxSocket();
    virtual ~VxSocket();
    virtual Rhp_int32_t Create  ( const Rhp_const_char_pt SocketAddress = NULL,
                                  const Rhp_uint32_t aSocketPort = 0U );
    virtual Rhp_int32_t Send    ( const Rhp_const_char_pt lpBuf, 
                                  const Rhp_int32_t nBufLen );
    virtual Rhp_int32_t Receive ( Rhp_char_pt lpBuf, 
                                  const Rhp_int32_t nBufLen );
    virtual void Close();
};


class VxConnectionPort: public OMOSConnectionPort {
private:
    static void readFromSockLoop(VxConnectionPort *me);
    static Rhp_char_pt m_Buf;
    static Rhp_int32_t m_BufSize;
    VxMutex m_SendMutex ;
    Rhp_int32_t m_Connected;
    void (*m_dispatchfunc)(OMSData *);
    VxThread* m_ConnectionThread;
    VxSocket m_Socket;
public:
    Rhp_int32_t m_ShouldWaitForAck;

    VxOSEventFlag m_AckEventFlag;
    Rhp_int32_t m_NumberOfMessagesBetweenAck;

    VxConnectionPort();
    virtual ~VxConnectionPort();
    virtual Rhp_int32_t Connect ( const Rhp_const_char_pt SocketAddress = NULL,
                                  const Rhp_uint32_t aSocketPort = 0U );
    virtual Rhp_int32_t Send ( OMSData *aMessage);
    virtual void SetDispatcher (void (*dispatchfunc)(OMSData*)) {
        m_dispatchfunc = dispatchfunc;
    }

};
#endif

/////////////////////////////////
// Semaphore class
class VxSemaphore : public OMOSSemaphore {
public:
    VxSemaphore( const Rhp_uint64_t semFlags,
                 const Rhp_uint64_t initialCount);
    ~VxSemaphore();

    // override of pure virtual
    virtual void signal();
    virtual OMBoolean wait(const Rhp_int64_t aTimeout = -1);
    virtual void* getOsHandle() const {
        return reinterpret_cast<void*>(m_semId);
    }
private:
    SEM_ID m_semId;
};


/////////////////////////////////////////
/////////////////////////////////////////
class VxOSFactory : public OMOSFactory {
	// OSFactory hides the RTOS mechnisms for tasking and synchronization
public:
    virtual OMOSMessageQueue* createOMOSMessageQueue( const OMBoolean shouldGrow = TRUE, 
                                                      const Rhp_int32_t messageQueueSize = OMOSThread::DefaultMessageQueueSize ) const {
        return (OMOSMessageQueue*)new VxOSMessageQueue(messageQueueSize);
    }
    virtual OMOSConnectionPort *createOMOSConnectionPort(void) const {
#ifdef _OMINSTRUMENT
        return (OMOSConnectionPort*)new VxConnectionPort();
#else
        return NULL;
#endif
    }
    virtual OMOSEventFlag* createOMOSEventFlag(void) const {
        return (OMOSEventFlag *)new VxOSEventFlag();
    }
    
    virtual OMOSThread *createOMOSThread( void (*tfunc)(void *),
                                          void *param,
                                          const Rhp_const_char_pt threadName = NULL,
                                          const Rhp_int32_t stackSize = OMOSThread::DefaultStackSize ) const {
    return (OMOSThread*)new VxThread(tfunc, param, threadName, stackSize);
    }
    
    virtual OMOSThread* createOMOSWrapperThread(void* osHandle) const {
        if (NULL == osHandle) {
            osHandle = getCurrentThreadHandle();
        }
        return (OMOSThread*)new VxThread(osHandle);
    }
    
    virtual OMOSMutex* createOMOSMutex(void) const {
        return (OMOSMutex*)new VxMutex();
    }
    
    virtual OMOSTimer *createOMOSTickTimer( const timeUnit tim, 
                                            void (*cbkfunc)(void*),
                                            void *param ) const {
        return (OMOSTimer*)new VxTimer(tim, cbkfunc, param);   // TickTimer for real time
    }
    
    virtual OMOSTimer *createOMOSIdleTimer(void (*cbkfunc)(void*), void *param) const {
        return (OMOSTimer*)new VxTimer(cbkfunc, param);   // Idle timer for simulated time
    }
    
    virtual OMOSSemaphore* createOMOSSemaphore( const Rhp_uint64_t semFlags = 0U,
                                                const Rhp_uint64_t initialCount = 1U,
                                                const Rhp_uint64_t maxCount = 1U,
                                                const Rhp_const_char_pt name = NULL)  const {
        return (OMOSSemaphore*) new VxSemaphore(semFlags, initialCount);
    }

    virtual void* getCurrentThreadHandle(void) const;
    virtual void delayCurrentThread(const timeUnit ms) const;

    virtual OMBoolean waitOnThread( void* osHandle, const timeUnit ms) const {
        return FALSE;
    }
};

//
// $Log: VxOS.h $
// Revision 1.43  2007/05/28 07:43:51  ilvler
// Macro OM_NOTIFY_ERROR call added after every VxWorks system unsuccessful calls
// Revision 1.42  2007/03/11 08:42:54  ilgiga
// Change copyright comment
// Revision 1.41  2007/03/01 14:32:34  ilgiga
// Telelogic instead of i-Logix
// Revision 1.40  2005/11/07 12:11:52  yshekel
// Upgrade_from_60_to_61
// Revision 1.39  2005/09/25 16:36:04  vova
// 
// --- Added comments ---  vova [2005/09/25 17:12:52 GMT]
// AnimServices:
// - add public static operation 
//   void resetDefaultThread(IOxfActive* oxfContext, void* osThread)
//   The operation reset the default AOMThread OS thread id
//   Used to overcome an issue in VxWorks where the globals initialization thread is not an application thread
// 
// OMOSThread:
// - Add public virtual operation void resetWrapperThreadOsHandle(void*)
//   The operation reset the thread OS handle
//   it Should be used with care and only for wrapper threads
//   The operation has an empty implementation by default and is implemented in the VxWorks adapter
// 
// OMMainThread:
// - Add public virtual operation void resetWrapperThreadOsHandle(void*)
//   The operation calls the OS thread resetWrapperThreadOsHandle()
// 
// OXF::initialize() - call AnimServices::resetDefaultThread() and 
//   OMMainThread::instance()->resetWrapperThreadOsHandle() with the current thread to make sure the correct thread is used
// Revision 1.38  2005/08/25 07:52:50  vova
// Signature fixed in all arguments, defined as pointer to function
// Revision 1.37  2004/11/04 07:33:22  vova
// 71871,64236:Priority inversion avoidance is used in mutex
// Revision 1.36  2001/08/05 09:13:54  amos
// back to main branch
// Revision 1.35.1.3  2001/08/05 09:13:54  amos
// modify the memory manager to support passing of the object size in deletion
// Revision 1.35.1.2  2001/08/02 12:20:42  amos
// Revision 1.35.1.1  2001/05/16 12:32:34  amos
// Duplicate revision
// Revision 1.34  2001/05/01 12:48:27  vova
// Message queue default size has been increased
// Revision 1.33  2001/01/30 09:09:53  avrahams
// Add OM prefix to globals
// Convert OMOS methods to static methods
// Revision 1.32  2001/01/25 13:59:13  avrahams
// OXF globals encapsulation
// Revision 1.31  2000/11/14 08:57:54  amos
// COM submission fix: replace true/false with TRUE/FALSE
// Revision 1.30  2000/11/13 12:12:55  amos
// merge 1.29.1.2 and 1.29.2.2
// Revision 1.29.2.2  2000/11/08 16:00:51  amos
// modify the OS layer message queue put() method to return a success status
// Revision 1.29.2.1  2000/07/26 12:52:36  amos
// Duplicate revision
// Revision 1.29.1.2  2000/11/06 16:31:32  npadmawar
// Changes for OXFEnd
// Revision 1.29  2000/07/26 12:52:36  amos
// back to main branch
// Revision 1.28.1.2  2000/07/26 12:52:36  amos
// add getOSHandle() to all OS classes (but Socket & connection port)
// Revision 1.28.1.1  2000/03/28 12:23:44  amos
// Duplicate revision
// Revision 1.27.1.2  2000/03/22 08:49:08  amos
// fix VxWorks warnnings (-Wall)
// Revision 1.27.1.1  1999/07/29 10:34:10  amos
// Duplicate revision
// Revision 1.26  1999/07/28 15:19:47  amos
// add GEN_ISR for generate of interapts in VxWorks
// Revision 1.25  1999/03/14 13:12:07  amos
// Revision 1.24.1.3  1999/03/14 11:09:45  amos
// move os includes before framework includes, and by priority
// Revision 1.24.1.2  1999/03/11 15:25:59  amos
// add semaphores to the OXF
// Revision 1.24.1.1  1999/03/08 12:29:27  amos
// Duplicate revision
// Revision 1.23  1999/02/09 14:55:29  amos
// change the getMessageList back to OMList
// add new operation on OMQueue - getInverseQueue()
// Revision 1.22  1999/02/03 12:38:34  amos
// back to main branch
// Revision 1.21.1.2  1999/02/03 12:24:20  amos
// convert OMOSMessageQueue from sizeless (OMList) to size controled (OMQueue)
// Revision 1.21.1.1  1999/02/01 16:19:46  amos
// Duplicate revision
// Revision 1.20.1.2  1999/02/01 11:24:06  amos
// chage time from long to unsigned long
// Revision 1.20  1999/01/26 08:44:19  amos
// back to main branch
// Revision 1.19.1.2  1999/01/24 14:52:51  amos
// merge
// Revision 1.19  1999/01/21 10:31:53  beery
// Revision 1.18.1.2  1999/01/03 12:56:00  beery
// Revision 1.18.1.1  1998/09/09 13:12:40  beery
// Revision 1.18.2.3  1999/01/19 12:24:23  amos
// setting the message queue size from OMThread constructor
// Revision 1.18.2.2  1999/01/19 09:05:26  amos
// user control over thread name, priority and stack size 
// via parameters in OMThread constructor
// Revision 1.18.2.1  1998/09/09 13:12:40  amos
// Duplicate revision
// Revision 1.17  1998/07/28 13:23:58  ofer
// 1) file oxf/types.h chnaged top oxf/omtypes.h so we needed
// to update include as wel as update dependencies
// 2) psos cadul compiler force as to use inline directive in
//   template method implementation ( otherwise it complain about
//   multiple definitions)
// 3) psos compiler does not allow to use inline for virtual methods
//  ( the method implementation is defined in the .h file) so we have 
//  to move the implementation to the corresponding .cpp files
// 4) update makefiles to use omtypes.h (instead of types.h)
// Revision 1.16  1998/06/23 12:30:18  yachin
// fix VX virtual table problem bug
// Revision 1.15  1997/12/14 14:31:12  ofer
// added  delayCurrentThread(long ms) to abstract factory 
// and define and implement the method in the XXXOS.cpp/h
// Also added convienent macro OXFTDelay(timInMs)
// os.h ntos.cpp/h VxOs.cpp/h sol2os.cpp/h
// Revision 1.14  1997/06/08 05:09:32  ofer
// Full support for trace and animation
// added OSEndApplication (vxos.cpp/h)
// Revision 1.13  1997/06/02 11:42:48  ofer
// Change implementetion of VxOsEventFlag (using semGive
// instead of semFlush since semFlush does not ffect the value)
// Revision 1.12  1997/04/29 08:37:08  ofer
//  Using semMcreate for implementation of Mutex since
//     it must support recursion (vxos.h)
// Revision 1.11  1997/04/16 10:18:58  ofer
// Support for trace/animation under VxWorks
// the low level WAS NOT debugged yet !!!!
// VxOS.cpp/h
// Revision 1.10  1997/04/09 10:12:22  ofer
//  update VxOS.cpp/h interfaces so INSTRUMENTED
// version can be compiled
// I have to implement the Socket/ConnectionPort and
// MessageQueue info in order to work with Tracer/Animator
// VxOS.cpp/h
// Revision 1.9  1997/03/09 11:01:12  ofer
// Lowest priority under VxWorks is 255( and not 256)
// Revision 1.8  1997/03/05 14:01:20  ofer
// Implemet creation of suspended VxThread by using Event Flag
// We should use the TaskInit/taskActivate system calls but
// somhow it does not work so for the time beeing it is implemented
// with EventFlag
// VxOs.cpp/h
// Revision 1.7  1997/02/24 09:49:21  yachin
// OMOSFactory - the virtual function table no longer depends on
//  _INSTRUMENT (createOMOSConnectionPort now exists in 
// non-instrumented version  too but returns null)
// Revision 1.6  1997/02/17 13:42:04  ofer
// 1) Move some of the inline functions to the VxOs.cpp file
// 2) correct VxOsMessageQueue::isEmpty and now simple
// programs are working
// VxOs.cpp/h
// 
// Revision 1.5  1997/01/29 09:01:52  ofer
// state --> m_State
// Revision 1.4  1997/01/28 13:12:18  ofer
// member variables "time" changed to "m_Time"
// remove signal method from vxOsMessageQueue
// VxOsMessageQueue::getNext/First?Current print "Not Implemented"
// timer.cpp/h ntos.cpp/h VxOs.cpp/h
// Revision 1.3  1997/01/27 11:47:56  ofer
// Trying to support vxWorks
// for the time beeing we support compilation of NON instumented
// version (for vxWorks.
// we assume the WE DO NOT use iostream for vxWorks
// Revision 1.2  1996/11/25 08:08:18  erang
//
#endif // _vxos_H

 
