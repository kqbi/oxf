#ifndef _linuxos_H
#define _linuxos_H
/*
*	file name   :	$Source: R:/StmOO/Master/cg/LangCpp/oxf/rcs/linuxos.h $
*	file version:	$Revision: 1.21 $
*
*	purpose:	
*
*	author(s):	Eran Gery
*	date started:	
*	date changed:	$Date: 2007/03/11 08:42:55 $
*	last change by:	$Author: ilgiga $
*
*	Licensed Materials - Property of IBM
*	(c) Copyright IBM Corporation 1996, 2008. All Rights Reserved.
*
* ---------------------------------------------------------------
*|                             linuxos.h                        |
* --------------------------------------------------------------- 
*/

// Rhapsody Framework includes
#include "semaphore.h" 
#include "omiotypes.h"
#include "omoutput.h" /* for notify_to_error */

#ifdef OM_STL
#include <iostream>
#include <cerrno>
#include <csignal>
#else
#include <iostream.h>
#include <errno.h>
#include <signal.h>
#endif //OM_STL

#include <pthread.h>

// Additional Rhapsody Framework includes
#include "omtypes.h"
#include "os.h"

const Rhp_int32_t LowestPriority = 0; 
const Rhp_int32_t DEFAULT_STACK = 20000;

class LinuxTimer : public OMOSTimer {
public:
    void (*cbkfunc)(void*);
    void *param;
	timer_t timerId;
private:
   timeUnit m_Time;
   void waitThread();
    static void* bridge(void* me);
    OMOSHandle hThread;     /* The timeTick thread  */
	OMBoolean SetAffinityInCtor;
#ifndef OM_NO_MC_SUPPORT
	cpu_set_t m_aff;
#endif

public:
    LinuxTimer( timeUnit ptime, 
                void pcbkfunc(void*), 
                void* pparam ); /* TickTimer */
    LinuxTimer( void pcbkfunc(void*), 
                void* pparam ); /* IdleTimer (Simulated Time) */
    virtual ~LinuxTimer();

    virtual void* getOsHandle() const {
        return reinterpret_cast<void*>(hThread);
    }
    virtual void setAffinity(const OMAffinity_t /*aff*/);
    static void evaluateSleepTime(struct timespec& tms, const timeUnit sleepTime);
};


class LinuxOSEventFlag : public OMOSEventFlag {
private:
    sem_t hEventFlag;

public:
    virtual void signal();
    virtual void reset();
    virtual void wait(Rhp_int32_t tminms = -1);  // tminms = -1 is wait forever
    LinuxOSEventFlag();
    virtual ~LinuxOSEventFlag() { 
        (void)sem_destroy(&hEventFlag); 
    }
    virtual void* getHandle() {
        return reinterpret_cast<void*>(const_cast<sem_t*>(&hEventFlag)); 
    }
    virtual void* getOsHandle() const {
        return reinterpret_cast<void*>(const_cast<sem_t*>(&hEventFlag)); 
    }
};


class LinuxThread : public OMOSThread {
private:
    OMOSHandle hThread;
    Rhp_int32_t isWrapperThread;
	
    // it is activated by start
    static void preExecFunc(void* me);
    void (*m_ExecFunc)(void*); // Method used to suspend the thread
    void* m_ExecParam;
    LinuxOSEventFlag* m_SuspEventFlag;
#ifndef OM_NO_MC_SUPPORT
	cpu_set_t m_aff;
#endif
	OMBoolean SetAffinityInCtor;
    OMBoolean endOSThreadInDtor; // TRUE means that the os thread is ended as part of this object's destruction
public:
    LinuxThread(void tfunc(void*), void* param, const Rhp_int32_t stackSize = OMOSThread::DefaultStackSize);
    explicit LinuxThread(void* osThreadId); /* for creation of wrapper thread */

    virtual ~LinuxThread();
#ifdef OM_POSIX_THREAD_SUSPEND_RESUME_SUPPORT
    static void User1handler(Rhp_int32_t signumber);
    static void User2handler(Rhp_int32_t signumber);
#endif	
    virtual void setPriority(const Rhp_int32_t aPriority); 
    void* getOsHandle() {
        return reinterpret_cast<void*>(hThread);
    }
	virtual void* getOsHandle(void*& osHandle) const { 
        osHandle = reinterpret_cast<void*>(hThread);
        return getOsHandle();
    }

    virtual void suspend();
    virtual void resume();
    virtual void start();

    void setEndOSThreadInDtor(const OMBoolean val) {
        endOSThreadInDtor = val;
    }
    virtual void* getOsHandle() const {
        return reinterpret_cast<void*>(hThread);
    }

    // asking for a callback to end my os thread
    // onExecuteThread = TRUE: I will kill my own thread
    // onExecuteThread = FALSE: someone else will kill my thread
    virtual void getThreadEndClbk( OMOSThreadEndCallBack * clb_p, // a pointer to the callback function
                                   void** arg1_p,                 // the argument for this function
                                   const OMBoolean onExecuteThread);

    // end the thread I'm working on
    static void endMyThread(OMOSHandle);

    // end a thread which is NOT my thread
    static void endOtherThread(OMOSHandle hThread);
    //## operation getAffinity()
    virtual OMAffinity_t getAffinity(void) const;
    //## operation setAffinity(OMAffinity_t)
    virtual void setAffinity(const OMAffinity_t aff);

    virtual void setPwrState(const OMPowerMode_t /*val*/) {}
    virtual OMPowerMode_t getPwrState(void) const { return (OMPowerMode_t)0;}
#ifndef OM_NO_MC_SUPPORT
    static void evaluateAffinity(const OMAffinity_t coreId, cpu_set_t & aff);
#endif 
	
}; /* LinuxThread */

class LinuxMutex : public OMOSMutex {
private:
    pthread_mutex_t hMutex;
    Rhp_int32_t count;
    void* owner;
public:
    LinuxMutex();
    virtual ~LinuxMutex();
    virtual void lock();
    virtual void unlock();
    virtual void* getHandle() const {
        return reinterpret_cast<void*>(const_cast<pthread_mutex_t*>(&hMutex));
    }
    virtual void* getOsHandle() const {
        return reinterpret_cast<void*>(const_cast<pthread_mutex_t*>(&hMutex));
    }
};

/////////////////////////
/////////////////////////
class LinuxOSMessageQueue : public OMOSMessageQueue { 
private:
    OMQueueType m_theQueue;
    LinuxMutex m_QueueMutex;
    LinuxOSEventFlag m_QueueEventFlag;

public:
    LinuxOSMessageQueue( const OMBoolean shouldGrow = TRUE, 
                         const Rhp_int32_t initSize = OMOSThread::DefaultMessageQueueSize ):
      m_theQueue(shouldGrow, initSize) {}
    virtual OMBoolean put( void* aMessage,
                           const OMBoolean fromISR = FALSE);
    virtual void* get();
    virtual Rhp_int32_t isEmpty() const { 
        return m_theQueue.isEmpty(); 
    }
    virtual void pend();
    virtual void getMessageList(OMListType& aList);
    virtual OMBoolean isFull() const {
        return m_theQueue.isFull();
    }
    virtual void* getOsHandle() const { 
        return static_cast<void*>(NULL); 
    }
};

#ifdef _OMINSTRUMENT

class LinuxSocket: public OMOSSocket {
private:
    Rhp_int32_t theSock;

public:
    LinuxSocket();
    virtual ~LinuxSocket();
    virtual Rhp_int32_t Create  ( const Rhp_const_char_pt SocketAddress = NULL,
                                  const Rhp_uint32_t aSocketPort = 0U );
    virtual Rhp_int32_t Send    ( const Rhp_const_char_pt lpBuf, 
                                  const Rhp_int32_t nBufLen );
    virtual Rhp_int32_t Receive ( Rhp_char_pt lpBuf,
                                  const Rhp_int32_t nBufLen );
};


class LinuxConnectionPort: public OMOSConnectionPort {
private:
    static void readFromSockLoop(LinuxConnectionPort* me);
    static Rhp_char_pt m_Buf;
    static Rhp_int32_t m_BufSize;
    LinuxMutex m_SendMutex;
    Rhp_int32_t m_Connected;
    void (*m_dispatchfunc)(OMSData*);
    LinuxThread* m_ConnectionThread;
    LinuxSocket m_Socket;

public:
    Rhp_int32_t m_ShouldWaitForAck;

    LinuxOSEventFlag m_AckEventFlag;
    Rhp_int32_t m_NumberOfMessagesBetweenAck;

    LinuxConnectionPort();
    virtual ~LinuxConnectionPort();
    virtual Rhp_int32_t Connect ( const Rhp_const_char_pt SocketAddress = NULL,
                                  const Rhp_uint32_t aSocketPort = 0U );
    virtual Rhp_int32_t Send ( OMSData* aMessage );
    virtual void SetDispatcher ( void (*dispatchfunc)(OMSData*) ) {
        m_dispatchfunc = dispatchfunc;
    }
};
#endif

/////////////////////////////////
// Semaphore class
class LinuxSemaphore : public OMOSSemaphore {
public:
    LinuxSemaphore( const Rhp_uint64_t semFlags, 
                    const Rhp_uint64_t initialCount );
    ~LinuxSemaphore();

    // override of pure virtual
    virtual void signal();
    virtual OMBoolean wait(const Rhp_int64_t timeout = -1);
    virtual void* getOsHandle() const {
        return reinterpret_cast<void*>(const_cast<sem_t*>(&m_sem));
    }

private:
    sem_t m_sem;
    OMBoolean m_ok;
};


/////////////////////////////////////////
/////////////////////////////////////////
class LinuxOSFactory : public OMOSFactory {
/* OSFactory hides the RTOS mechnisms for tasking and synchronization */
public:
    LinuxOSFactory() {
        destroyed = false;
    }

    virtual ~LinuxOSFactory();

    static bool isDestroyed() {
        return destroyed;
    }

    virtual void* getCurrentThreadHandle() const;

    virtual OMOSMessageQueue* createOMOSMessageQueue( const bool shouldGrow = true,
                                                      const Rhp_int32_t messageQueueSize = OMOSThread::DefaultMessageQueueSize ) const {
        return (OMOSMessageQueue*) new LinuxOSMessageQueue(shouldGrow, messageQueueSize);
    }

    virtual OMOSConnectionPort* createOMOSConnectionPort() const {
#ifdef _OMINSTRUMENT
        return (OMOSConnectionPort*) new LinuxConnectionPort();
#else
        return NULL;
#endif
    }

    virtual OMOSEventFlag* createOMOSEventFlag() const {
        return (OMOSEventFlag*) new LinuxOSEventFlag();
    }

    virtual OMOSThread* createOMOSThread( void (*tfunc)(void*),
                                          void* param, 
                                          const Rhp_const_char_pt threadName = NULL, 
                                          const Rhp_int32_t stackSize = OMOSThread::DefaultStackSize) const {
        return (OMOSThread*) new LinuxThread(tfunc, param, stackSize);
    }

    virtual OMOSThread* createOMOSWrapperThread(void* osHandle) const {
        if (NULL == osHandle) {
            osHandle = getCurrentThreadHandle();
        }
        return (OMOSThread*) new LinuxThread(osHandle);
    }

    virtual OMOSMutex* createOMOSMutex() const { 
        return (OMOSMutex*) new LinuxMutex();
    }

    virtual OMOSTimer* createOMOSTickTimer( const OxfTimeUnit tim,
                                           void (*cbkfunc)(void*),
                                           void* param) const { 
        return (OMOSTimer*) new LinuxTimer(tim, cbkfunc, param);   /* TickTimer for real time */
    }

    virtual OMOSTimer* createOMOSIdleTimer( void (*cbkfunc)(void*), 
                                            void* param) const { 
        return (OMOSTimer*) new LinuxTimer(cbkfunc, param);   /* Idle timer for simulated time */
    }

    virtual OMOSSemaphore* createOMOSSemaphore( const Rhp_uint64_t semFlags = 0U,
                                                const Rhp_uint64_t initialCount = 1U, 
                                                const Rhp_uint64_t maxCount = 1U, 
                                                const Rhp_const_char_pt name = NULL ) const {
        return (OMOSSemaphore*) new LinuxSemaphore(semFlags, initialCount);
    }

    virtual void delayCurrentThread(const OxfTimeUnit ms) const;

    virtual bool waitOnThread(void* osHandle, const OxfTimeUnit ms) const {
        return FALSE;
    }

private:
    static bool destroyed;
};


/*
* $Log: linuxos.h $
* Revision 1.21  2007/03/11 08:42:55  ilgiga
* Change copyright comment
* Revision 1.20  2007/03/01 14:32:35  ilgiga
* Telelogic instead of i-Logix
* Revision 1.19  2005/11/07 12:11:27  yshekel
* Upgrade_from_60_to_61
* Revision 1.18  2005/08/25 07:52:50  vova
* Signature fixed in all arguments, defined as pointer to function
* Revision 1.17  2005/08/17 14:01:07  amos
* OMOSFactory::instance() - Fix the creation of the LinuxOSFactory
* LinuxOSFactory: use the new types instead of the compatibility types.
* Revision 1.16  2005/03/28 15:22:18  vova
* Thread suspend/resume function implementation is ifdefed
* Revision 1.15.1.1  2005/03/28 08:14:22  vova
* Revision 1.15  2005/03/22 13:59:34  vova
* Thread suspend/resume function implementation added (C-like implementation)
* Revision 1.14  2005/03/21 14:14:21  vova
* pthread_kill has been replaced with pthread_cancel
* Revision 1.13  2005/02/16 14:20:01  vova
* Crash eliminated because of too "early" OMOSFactory instance destruction while application exiting.
* Revision 1.12  2004/10/19 10:28:29  vova
* Revision 1.11  2004/10/14 16:16:26  vova
* 75497:Timer inaccuracy corrected
* Revision 1.10  2002/07/15 12:27:44  avrahams
* Back to main
* Revision 1.9.1.2  2002/07/04 10:19:34  avrahams
* Clean up std namespace usage
* Revision 1.9.1.1  2002/01/15 10:33:50  avrahams
* Duplicate revision
* Revision 1.9  2002/01/15 10:33:50  vova
* 52678: SIGHUP signal handler has been added for the timer thread
* Revision 1.8  2002/01/08 16:57:11  vova
* 50808 : static  function has been added and defined as the SIGHUP signal handler in LinuxThread::LinuxThread constructor
* Revision 1.7  2001/08/05 09:15:37  amos
* back to main branch
* Revision 1.6.1.3  2001/08/05 09:15:37  amos
* modify the memory manager to support passing of the object size in deletion
* Revision 1.6.1.2  2001/08/02 12:01:57  amos
* Revision 1.6.1.1  2001/05/16 12:32:34  amos
* Duplicate revision
* Revision 1.5  2001/01/30 09:09:55  avrahams
* Add OM prefix to globals
* Convert OMOS methods to static methods
* Revision 1.4  2001/01/25 13:59:15  avrahams
* OXF globals encapsulation
* Revision 1.3  2000/11/14 08:58:01  amos
* COM submission fix: replace true/false with TRUE/FALSE
* Revision 1.2  2000/11/13 12:46:03  amos
* merge 1.1.1.2 and 1.1.2.2
* Revision 1.1.1.2  2000/11/08 15:59:03  amos
* modify the OS layer message queue put() method to return a success status
* Revision 1.1.1.1  2000/10/04 10:53:48  amos
* Revision 1.1.2.2  2000/11/09 19:37:07  npadmawar
* Changes for OXFEnd
* Revision 1.1.2.1  2000/10/04 10:53:48  npadmawar
* Duplicate revision
*/
#endif // _linuxos_H
