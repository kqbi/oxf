#ifndef _vx653posix_H
#define _vx653posix_H
//
//	file name   :	$Source: R:/StmOO/Master/cg/LangCpp/oxf/rcs/Vx653posix.h $
//	file version:	$Revision: 1.43 $
//
//	purpose:	
//
//	author(s):	Vladimir Erukhimovich
//	date started:	
//	date changed:	$Date: 2011/01/16 07:43:51 $
//	last change by:	$Author: ilvler $
//
//	Licensed Materials - Property of IBM
//	(c) Copyright IBM Corporation 2008, 2016. All Rights Reserved.
//	
//	Note to U.S. Government Users Restricted Rights:  
//	Use, duplication or disclosure restricted by GSA ADP Schedule 
//	Contract with IBM Corp.
//
// ---------------------------------------------------------------
//|                                vxos.h                        |
// --------------------------------------------------------------- 


#include <vxWorks.h>
#include <version.h>
#include <sysLib.h> 
#include <semaphore.h>
#include <sched.h>
#include <mqueue.h>

#include <stdarg.h>
#include <stdio.h>

#if ((_WRS_VXWORKS_MAJOR >5) && (_WRS_VXWORKS_MINOR >5))
#include <cpuset.h>
#ifdef _WRS_KERNEL
#include <cpuPwrLib.h>
#endif
#endif
// Rhapsody Framework Includes
#include "omtypes.h"
#include "os.h"

#define MQ_DEFAULT_SIZE     100     /* queue default size */
#define SMALL_STACK       10000
#define DEFAULT_STACK     20000

#define HighestPriority  63
#define PRIORITY_NORMAL  30            

static int OMOSMessageQueue_mqNo =0;

class Vx653Timer : public OMOSTimer {
private:
	void (*cbkfunc)(void*);
	void waitThread(void);
	static void bridge(Vx653Timer* me);
	OMOSHandle hThread;    // The timeTick thread 
	OxfTimeUnit m_Time;
	void *param;
	Rhp_int32_t ticks;      // how many OS ticks the timer wakes up  

public:
	Vx653Timer(const OxfTimeUnit ptime, void pcbkfunc(void*), void* pparam); // TickTimer
	Vx653Timer(void pcbkfunc(void*), void *pparam);    // IdleTimer (Simulated Time) 
	virtual ~Vx653Timer(void);
	virtual void* getOsHandle(void) const { 
		return reinterpret_cast<void*>(hThread);
	}
	virtual void setAffinity(const OMAffinity_t aff);
	static void evaluateSleepTime(struct timespec& tms, const OxfTimeUnit sleepTime);
};


class Vx653OSEventFlag : public OMOSEventFlag {
private:
    sem_t hEventFlag;
public:
	virtual void signal(void);
	virtual void reset(void);
	virtual void wait(const Rhp_int32_t tminms = -1);  // tminms = -1 is wait forever
	Vx653OSEventFlag(void);
	~Vx653OSEventFlag(void) { 
		(void)sem_destroy(&hEventFlag);
		hEventFlag = NULL;
	}
	virtual void* getHandle(void) const {
		return reinterpret_cast<void*>(const_cast<sem_t*>(&hEventFlag)); 
	}
	virtual void* getOsHandle(void) const {
		return reinterpret_cast<void*>(const_cast<sem_t*>(&hEventFlag)); 
	}
};

/////////////////
/////////////////

class Vx653Thread : public OMOSThread {
private:
	OMOSHandle hThread;
	Rhp_int32_t isWrapperThread;
	OMBoolean endOSThreadInDtor; // TRUE means that the os thread is ended as part of this object's destruction

	// preExecFunc takes control upon contruction to suspend the task until
	// it is activated by start
	static void preExecFunc(void* me);
	void (*m_ExecFunc)(void*);
	void* m_ExecParam;
	Vx653OSEventFlag m_SuspEventFlag;

public:
	Vx653Thread( void tfunc(void *),
			  void *param,
			  Rhp_const_char_pt name = NULL,
			  const Rhp_int32_t stackSize = OMOSThread::DefaultStackSize );
	Vx653Thread(void* osThreadId); // for creation of wrapper thread
	virtual ~Vx653Thread();
	virtual void setPriority(const Rhp_int32_t aPriority); 
	virtual void suspend(void) {} 
	virtual void resume(void) {}
	virtual void start(void);
	virtual void setEndOSThreadInDtor(const OMBoolean val) {
		endOSThreadInDtor = val;
	}
	virtual void* getOsHandle(void) const { 
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
	static void endMyThread(OMOSHandle);

	// end a thread which is NOT my thread
	static void endOtherThread(OMOSHandle);

	virtual OMAffinity_t getAffinity(void) const; 
	virtual void setAffinity(const OMAffinity_t aff);
	virtual OMPowerMode_t getPwrState(void) const;
	virtual void setPwrState(const OMPowerMode_t val);
	static void setThreadAffinity(Rhp_int32_t m_hThread, const OMAffinity_t coreId);


}; // Vx653Thread

class Vx653Mutex : public OMOSMutex {
private:
    pthread_mutex_t hMutex;
public:
    virtual void lock(void);
    virtual void unlock(void);
    Vx653Mutex(void);
    ~Vx653Mutex(void) ;

    virtual void* getHandle(void) const {
        return reinterpret_cast<void*>(const_cast<pthread_mutex_t*>(&hMutex));
    }
    virtual void* getOsHandle(void) const {
        return reinterpret_cast<void*>(const_cast<pthread_mutex_t*>(&hMutex));
    }
};

/////////////
/////////////
class Vx653OSMessageQueue : public OMOSMessageQueue {
private:
    mqd_t hVx653MQ;
    void *pmessage; // Buffer of a single lookahead message 
    enum { dataReady, noData } m_State;
    char name[20] ;
    void Mq_name(void) {
	   sprintf(name,"/MQ%d",OMOSMessageQueue_mqNo);
	   ++OMOSMessageQueue_mqNo ;
    }
    static void Vx653OSMessageQueue::Exit_Handler( int sig_number );
public:
    Vx653OSMessageQueue(const OMBoolean shouldGrow = TRUE,const Rhp_int32_t messageQueueSize = OMOSThread::DefaultMessageQueueSize);
    ~Vx653OSMessageQueue(void);
 
    virtual OMBoolean put(void* aMessage, const OMBoolean fromISR = FALSE);
    virtual void* get(void);
    virtual Rhp_int32_t isEmpty(void) const ;
    virtual void pend(void);
    virtual void getMessageList(OMListType& aList);
    virtual OMBoolean isFull(void) const;
    virtual void* getOsHandle(void) const {
        return reinterpret_cast<void*>(hVx653MQ);
    }
};

/////////////////////////////////
// Semaphore class
/////////////////////////////////

class Vx653Semaphore : public OMOSSemaphore {
public:
    Vx653Semaphore( const Rhp_uint64_t semFlags,
                 const Rhp_uint64_t initialCount);
    ~Vx653Semaphore(void);

    // override of pure virtual
    virtual void signal(void);
    virtual OMBoolean wait(const Rhp_int64_t aTimeout = -1);
    virtual void* getOsHandle(void) const {
      return reinterpret_cast<void*>(const_cast<sem_t*>(&m_sem));
    }
private:
     sem_t m_sem;
    OMBoolean m_ok;
};

#ifdef _OMINSTRUMENT

class Vx653Socket: public OMOSSocket {
private:
    Rhp_int32_t theSock;
public:
    Vx653Socket(void);
    virtual ~Vx653Socket(void);
    virtual Rhp_int32_t Create  ( const Rhp_const_char_pt SocketAddress = NULL,
                                  const Rhp_uint32_t aSocketPort = 0U );
    virtual Rhp_int32_t Send    ( const Rhp_const_char_pt lpBuf, 
                                  const Rhp_int32_t nBufLen );
    virtual Rhp_int32_t Receive ( Rhp_char_pt lpBuf, 
                                  const Rhp_int32_t nBufLen );
    virtual void Close(void);
};


class Vx653ConnectionPort: public OMOSConnectionPort {
private:
    static void readFromSockLoop(Vx653ConnectionPort *me);
    static Rhp_char_pt m_Buf;
    static Rhp_int32_t m_BufSize;
    Vx653Mutex m_SendMutex ;
    Rhp_int32_t m_Connected;
    void (*m_dispatchfunc)(OMSData *);
    Vx653Thread* m_ConnectionThread;
    Vx653Socket m_Socket;
public:
    Rhp_int32_t m_ShouldWaitForAck;

    Vx653OSEventFlag m_AckEventFlag;
    Rhp_int32_t m_NumberOfMessagesBetweenAck;

    Vx653ConnectionPort(void);
    virtual ~Vx653ConnectionPort(void);
    virtual Rhp_int32_t Connect ( const Rhp_const_char_pt SocketAddress = NULL,
                                  const Rhp_uint32_t aSocketPort = 0U );
    virtual Rhp_int32_t Send ( OMSData *aMessage);
    virtual void SetDispatcher (void (*dispatchfunc)(OMSData*)) {
        m_dispatchfunc = dispatchfunc;
    }

};
#endif

/////////////////////////////////////////
/////////////////////////////////////////
class Vx653OSFactory : public OMOSFactory {
	// OSFactory hides the RTOS mechnisms for tasking and synchronization
public:
    virtual OMOSMessageQueue* createOMOSMessageQueue( const OMBoolean shouldGrow = TRUE, 
                                                      const Rhp_int32_t messageQueueSize = OMOSThread::DefaultMessageQueueSize ) const {
        return (OMOSMessageQueue*)new Vx653OSMessageQueue(messageQueueSize);
    }
    virtual OMOSConnectionPort *createOMOSConnectionPort(void) const {
#ifdef _OMINSTRUMENT
        return (OMOSConnectionPort*)new Vx653ConnectionPort();
#else
        return NULL;
#endif
    }
    virtual OMOSEventFlag* createOMOSEventFlag(void) const {
        return (OMOSEventFlag *)new Vx653OSEventFlag();
    }
    
    virtual OMOSThread *createOMOSThread( void (*tfunc)(void *),
                                          void *param,
                                          const Rhp_const_char_pt threadName = NULL,
                                          const Rhp_int32_t stackSize = OMOSThread::DefaultStackSize ) const {
    return (OMOSThread*)new Vx653Thread(tfunc, param, threadName, stackSize);
    }
    
    virtual OMOSThread* createOMOSWrapperThread(void* osHandle) const {
        if (NULL == osHandle) {
            osHandle = getCurrentThreadHandle();
        }
        return (OMOSThread*)new Vx653Thread(osHandle);
    }
    
    virtual OMOSMutex* createOMOSMutex(void) const {
        return (OMOSMutex*)new Vx653Mutex();
    }
    
    virtual OMOSTimer *createOMOSTickTimer( const OxfTimeUnit tim, 
                                            void (*cbkfunc)(void*),
                                            void *param ) const {
        return (OMOSTimer*)new Vx653Timer(tim, cbkfunc, param);   // TickTimer for real time
    }
    
    virtual OMOSTimer *createOMOSIdleTimer(void (*cbkfunc)(void*), void *param) const {
        return (OMOSTimer*)new Vx653Timer(cbkfunc, param);   // Idle timer for simulated time
    }
    
    virtual OMOSSemaphore* createOMOSSemaphore( const Rhp_uint64_t semFlags = 0U,
                                                const Rhp_uint64_t initialCount = 1U,
                                                const Rhp_uint64_t maxCount = 1U,
                                                const Rhp_const_char_pt name = NULL)  const {
        return (OMOSSemaphore*) new Vx653Semaphore(semFlags, initialCount);
    }

    virtual void* getCurrentThreadHandle(void) const;
    virtual void delayCurrentThread(const OxfTimeUnit ms) const;

    virtual OMBoolean waitOnThread( void* osHandle, const OxfTimeUnit ms) const {
        return FALSE;
    }
};

//
// $Log: Vx653OS.h $
// Revision 1.1  2007/05/28 07:43:51  ilvler
//
#endif // _vx653posix_H

 
