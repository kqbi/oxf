// $Id: QNXOS.h 1.13 2007/03/11 08:42:54 ilgiga Exp $
//
//	file name   :	$Source:      D:\Rhapsody\Share\LangCpp\oxf
//	file version:	$Revision: 1.13 $
//
//	purpose:	 	QNXOS implementations
//
//
//	author(s):
//	date started:
//	date changed:	$Date: 2007/03/11 08:42:54 $
//	last change by:	$Author:
//
//	Licensed Materials - Property of IBM
//	(c) Copyright IBM Corporation 1995, 2016. All Rights Reserved.
//	
//	Note to U.S. Government Users Restricted Rights:  
//	Use, duplication or disclosure restricted by GSA ADP Schedule 
//	Contract with IBM Corp.
//
// ---------------------------------------------------------------
//|                               QNXOS.h                        |
// ---------------------------------------------------------------
 
#ifndef _qnxos_H
#define _qnxos_H

#include <sys/neutrino.h>
#include <iostream.h>
#include <errno.h>
#include <signal.h>

#include <pthread.h>
#include <mqueue.h>
#include <semaphore.h>

// Rhapsody Includes
#include "omtypes.h"
#include "os.h"
#include "omoutput.h"

const Rhp_int32_t LowestPriority   = 0;
const Rhp_int32_t HighestPriority = 63;
const Rhp_int32_t PRIO_NORMAL      = 30;
const Rhp_int32_t DEFAULT_STACK    = 20000;
const Rhp_int32_t DEFAULT_MQ_SIZE = 100;

// fwd declaration of classes
class QNXTimer;
class QNXThread;
class QNXMutex;
class QNXMessageQueue;
class QNXEventFlag;
class QNXSemaphore;
class QNXSocket;
class QNXConnectionPort;


///////////////////////////////////////////////////////////////////////////////
///                           QNXOSFactory Class                            ///
///////////////////////////////////////////////////////////////////////////////

class QNXOSFactory : public OMOSFactory {
// OSFactory hides the RTOS mechnisms for tasking and synchronization
public:
    virtual OMOSMessageQueue* createOMOSMessageQueue( const OMBoolean /*shouldGrow*/ = TRUE,
                                                      const Rhp_int32_t messageQueueSize = OMOSThread::DefaultMessageQueueSize ) const;

    virtual OMOSConnectionPort* createOMOSConnectionPort(void) const;

    OMOSEventFlag* createOMOSEventFlag(void) const;

    virtual OMOSThread* createOMOSThread( void (*tfunc)(void*), 
                                          void* param,
                                          const Rhp_const_char_pt threadName = NULL,
                                          const Rhp_int32_t stackSize = OMOSThread::DefaultStackSize ) const;

    virtual OMOSThread* createOMOSWrapperThread(void* osHandle) const;

    virtual OMOSMutex* createOMOSMutex(void) const;

    virtual OMOSTimer* createOMOSTickTimer(const timeUnit tim, void (*cbkfunc)(void*), void* param ) const;

    virtual OMOSTimer* createOMOSIdleTimer(void (*cbkfunc)(void*), void* param ) const;

    virtual OMOSSemaphore* createOMOSSemaphore( const Rhp_uint64_t semFlags = 0U,
                                                const Rhp_uint64_t initialCount = 1U, 
                                                const Rhp_uint64_t maxCount = 1U, 
                                                const Rhp_const_char_pt name = NULL ) const;

    virtual void* getCurrentThreadHandle(void) const;

    virtual void delayCurrentThread(const timeUnit ms) const;

    virtual OMBoolean waitOnThread( void* osHandle, const timeUnit ms) const;
};



///////////////////////////////////////////////////////////////////////////////
//                             QNXTimer Class                               ///
///////////////////////////////////////////////////////////////////////////////

class QNXTimer : public OMOSTimer {
public:
    QNXTimer ( const timeUnit ptime, 
               void pcbkfunc(void*), 
               void* pparam ); // TickTimer

    QNXTimer ( void pcbkfunc(void*), 
               void* pparam ); // IdleTimer (Simulated Time)

    virtual ~QNXTimer(void);

    virtual void* getOsHandle(void) const	{
        return reinterpret_cast<void*>(hThread);
    }
    virtual void setAffinity(const OMAffinity_t /*aff*/) {}

    static OMBoolean active;
    static void terminate(void);

private:
    void (*cbkfunc)(void*);
    void waitThread(void);
    static void* bridge(void* me);
    void* timerThread(void);

    pthread_t hThread;    // The timeTick thread
    timeUnit m_Time;
    void *param;
};


///////////////////////////////////////////////////////////////////////////////
//                             QNXThread Class                              ///
///////////////////////////////////////////////////////////////////////////////

class QNXThread : public OMOSThread {
public:
    QNXThread ( void tfunc(void*), 
                void* param, 
                const Rhp_const_char_pt name = NULL, 
                const Rhp_int32_t stackSize = OMOSThread::DefaultStackSize );

    QNXThread ( void *osThreadId ); // for creation of wrapper thread

    virtual ~QNXThread(void);

    virtual void setPriority(const Rhp_int32_t aPriority);

    virtual void suspend(void);

    virtual void resume(void);

    virtual void start(void);

    virtual void setEndOSThreadInDtor(const OMBoolean val) {
        endOSThreadInDtor = val;
    }

    virtual void* getOsHandle(void) const {
        return reinterpret_cast<void*>(hThread);
    }

    virtual void* getOsHandle(void*& osHandle) const {
        osHandle = reinterpret_cast<void*>(hThread); 
        return getOsHandle();
    }

    virtual void getThreadEndClbk ( OMOSThreadEndCallBack* clb_p,   // a pointer to the callback function
                                    void** arg1_p,                  // the argument for this function
                                    const OMBoolean onExecuteThread );

    static void endMyThread(void*);

    static void endOtherThread(void*);

    //## operation getAffinity()
    virtual OMAffinity_t getAffinity(void) const {
      unsigned my_runmask = 0U;
      OMAffinity_t prevMask = 1U;
      RMSK_SET(prevMask, &my_runmask);

      ThreadCtl(_NTO_TCTL_RUNMASK_GET_AND_SET, (void *)&my_runmask);
      prevMask = my_runmask;  // save returned value 
      ThreadCtl(_NTO_TCTL_RUNMASK_GET_AND_SET, (void *)&my_runmask); //restore original mask
      return prevMask;
    }
    //## operation setAffinity(OMAffinity_t)
    virtual void setAffinity(const OMAffinity_t aff) 
    {
      unsigned my_runmask = 0U;
      RMSK_SET(aff, &my_runmask); 

      ThreadCtl(_NTO_TCTL_RUNMASK, (void *)&my_runmask);
    }

    virtual void setPwrState(const OMPowerMode_t /*val*/) {}

    virtual OMPowerMode_t getPwrState(void) const { return (OMPowerMode_t)0;}

private:
    pthread_t hThread;
    Rhp_int32_t isWrapperThread;

    OMBoolean endOSThreadInDtor; // TRUE means that the os thread is ended as part of this object's destruction

    // preExecFunc takes control upon contruction to suspend the task untill
    // it is activated by start
    static void preExecFunc(void* me);
    	void (*m_ExecFunc)(void*);
    void* m_ExecParam;
    QNXEventFlag* m_SuspEventFlag;
};


///////////////////////////////////////////////////////////////////////////////
//                               QNXMutex Class                             ///
///////////////////////////////////////////////////////////////////////////////

class QNXMutex : public OMOSMutex {
public:
    QNXMutex(void);
    ~QNXMutex(void);

    virtual void lock(void);
    virtual void unlock(void);

    virtual void* getHandle(void) {
        return reinterpret_cast<void*>(const_cast<pthread_mutex_t*>(&hMutex));
    }

    virtual void* getOsHandle(void) const {
        return reinterpret_cast<void*>(const_cast<pthread_mutex_t*>(&hMutex));
    }

private:
    pthread_mutex_t hMutex;
};

///////////////////////////////////////////////////////////////////////////////
//                           QNXEventFlag Class                             ///
///////////////////////////////////////////////////////////////////////////////

class QNXEventFlag : public OMOSEventFlag {
public:
    virtual void signal(void);
    virtual void reset(void);
    virtual void wait(const Rhp_int32_t tminms = -1);  // tminms = -1 is wait forever

    QNXEventFlag(void);

    ~QNXEventFlag(void)	{
        (void) sem_destroy(&hEventFlag);
    }

    virtual void* getHandle(void) const {
        return reinterpret_cast<void*>(const_cast<sem_t*>(&hEventFlag));
    }

    virtual void* getOsHandle(void) const {
        return reinterpret_cast<void*>(const_cast<sem_t*>(&hEventFlag));
    }

private:
    sem_t hEventFlag;
};





///////////////////////////////////////////////////////////////////////////////
//                            QNXMessageQueue Class                         ///
///////////////////////////////////////////////////////////////////////////////


#ifdef OM_POSIX_QUEUES
class QNXMessageQueue : public OMOSMessageQueue {
public:
    static Rhp_int32_t mq_no;
    QNXMessageQueue(const Rhp_int32_t messageQueueSize = OMOSThread::DefaultMessageQueueSize);
    ~QNXMessageQueue(void);
    virtual OMBoolean put(void*, const OMBoolean fromISR = FALSE);
    virtual void* get(void);
    virtual Rhp_int32_t isEmpty(void) const;
    virtual void pend(void);

    virtual void getMessageList(OMListType& aList);
    virtual OMBoolean isFull(void) const;
    virtual void* getOsHandle(void) const {
        return reinterpret_cast<void*>(hQNXMQ);
    }
    void Mq_name(void);
    static void cleanUpMessageQueues(void);

private:
    mqd_t hQNXMQ;
    void* pmessage; // Buffer of a single lookahead message
    enum { dataReady, noData } m_State;
    Rhp_char_t name[20];
};
#else

class QNXMessageQueue : public OMOSMessageQueue {
public:
    QNXMessageQueue ( const OMBoolean shouldGrow = TRUE, 
                      const Rhp_int32_t initSize = OMOSThread::DefaultMessageQueueSize ):
        m_theQueue(shouldGrow, initSize) {
    }

    virtual OMBoolean put(void*, const OMBoolean fromISR = FALSE);
    virtual void* get(void);
    virtual void pend(void);
    virtual void getMessageList(OMListType& aList);
    static void cleanUpMessageQueues(void);

    virtual Rhp_int32_t isEmpty(void) const {
        return m_theQueue.isEmpty();
    }

    virtual OMBoolean isFull(void) const {
        return m_theQueue.isFull();
    }

    virtual void* getOsHandle(void) const {
        return static_cast<void*>(NULL);
    }

private:
    OMQueueType m_theQueue;
    QNXMutex m_QueueMutex;
    QNXEventFlag m_QueueEventFlag; 
};
#endif



///////////////////////////////////////////////////////////////////////////////
//                            QNXSemaphore Class                            ///
///////////////////////////////////////////////////////////////////////////////

class QNXSemaphore : public OMOSSemaphore {
public:
    QNXSemaphore ( const Rhp_uint64_t semFlags, const Rhp_uint64_t initialCount );
    ~QNXSemaphore(void);

    // override of pure virtual
    virtual void signal(void);

    virtual OMBoolean wait(const Rhp_int64_t timeout = -1);
    virtual void* getOsHandle(void) const { 
    return reinterpret_cast<void*>(const_cast<sem_t*>(&m_sem));
    }

private:
    sem_t m_sem;
    OMBoolean m_ok;
};


#ifdef _OMINSTRUMENT

///////////////////////////////////////////////////////////////////////////////
//                             QNXSocket Class                              ///
///////////////////////////////////////////////////////////////////////////////

class QNXSocket: public OMOSSocket {
public:
    QNXSocket(void);
    virtual ~QNXSocket(void);

    virtual Rhp_int32_t Create  ( const Rhp_const_char_pt SocketAddress = NULL,
                                  const Rhp_uint32_t nSocketPort = 0U );

    virtual Rhp_int32_t Send    ( const Rhp_const_char_pt lpBuf, 
                                  const Rhp_int32_t nBufLen );

    virtual Rhp_int32_t Receive ( Rhp_char_pt lpBuf, 
                                  const Rhp_int32_t nBufLen );

private:
    Rhp_int32_t theSock;

};

///////////////////////////////////////////////////////////////////////////////
//                         QNXConnectionPort Class                          ///
///////////////////////////////////////////////////////////////////////////////

class QNXConnectionPort: public OMOSConnectionPort {
public:

    QNXConnectionPort(void);

    virtual ~QNXConnectionPort(void);

    virtual Rhp_int32_t Connect ( const Rhp_const_char_pt SocketAddress = NULL,
                                  const Rhp_uint32_t aSocketPort = 0U );

    virtual Rhp_int32_t Send    ( OMSData* aMessage );

    virtual void SetDispatcher ( void (*dispatchfunc)(OMSData*) ) {
        m_dispatchfunc = dispatchfunc;
    }

private:
    void (*m_dispatchfunc)(OMSData*);
    QNXThread* m_ConnectionThread;
    QNXSocket m_Socket;

    static void readFromSockLoop(QNXConnectionPort* me);
    static Rhp_char_pt m_Buf;
    static Rhp_int32_t m_BufSize;
    QNXMutex m_SendMutex ;
    OMBoolean m_Connected;
    Rhp_int32_t m_ShouldWaitForAck;
    QNXEventFlag m_AckEventFlag;
    Rhp_int32_t m_NumberOfMessagesBetweenAck;

};
#endif // _OMINSTRUMENT

#endif // _qnxos_H
