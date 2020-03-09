//
//  purpose:        NT OS implementations
//
//  Licensed Materials - Property of IBM
//  (c) Copyright IBM Corporation 1995, 2018. All Rights Reserved.
//
//  Note to U.S. Government Users Restricted Rights:  
//  Use, duplication or disclosure restricted by GSA ADP Schedule 
//  Contract with IBM Corp.
//


// ---------------------------------------------------------------
// |                             ntos.h                          |
// -------------------------------------------------------------- 
#ifndef _ntos_H
#define _ntos_H

#include <windows.h>
// Rhapsody Framework includes
#include "omtypes.h"
#include "os.h"

#ifdef OM_USE_MULTIMEDIA_TIMER
  #include <Mmsystem.h>
#endif // OM_USE_MULTIMEDIA_TIMER

#define OM_DWORD_PARAM_TYPE DWORD
#define OM_THREAD_ID_TYPE DWORD
#ifdef _MSC_VER
	#if (_MSC_VER >= 1300)
		#undef OM_DWORD_PARAM_TYPE
		#define OM_DWORD_PARAM_TYPE DWORD_PTR
		#undef OM_THREAD_ID_TYPE
		#define OM_THREAD_ID_TYPE DWORD_PTR
	#endif
#else
	#if defined(__CYGWIN__)
		#undef OM_THREAD_ID_TYPE 
		#undef OM_DWORD_PARAM_TYPE
		#define OM_DWORD_PARAM_TYPE DWORD_PTR
		#define OM_THREAD_ID_TYPE DWORD_PTR
	#endif
#endif

#ifdef _WIN32_WCE
#if _WIN32_WCE < 300
#define NO_SEMAPHORE_IMPLEMENTATION
#else
#define WINCE_PRIORITY
#endif // _WIN32_WCE
#endif // _WIN32_WCE

#ifdef  WINCE_PRIORITY
// WinCE priorities
#ifdef OM_WINCE_DRIVER
// The OM_WINCE_DRIVER flag should be set when compiling a WinCE driver
#define PRIORITY_HIGH 100
#define PRIORITY_NORMAL 150
#define PRIORITY_LOW 200
#else
// WinCE application
#define PRIORITY_HIGH 201
#define PRIORITY_NORMAL 225
#define PRIORITY_LOW 247
#endif // OM_WINCE_DRIVER

#else	// Windows

#define PRIORITY_HIGH THREAD_PRIORITY_ABOVE_NORMAL
#define PRIORITY_NORMAL THREAD_PRIORITY_NORMAL
#define PRIORITY_LOW THREAD_PRIORITY_IDLE

#endif // WINCE_PRIORITY

class NTTimer : public OMOSTimer {
private:
    void (*cbkfunc)(void*);
    void waitThread(void);
    static void bridge(NTTimer* me) {
        me->waitThread();
    }
    HANDLE hThread;     // The timeTick thread 
    OM_THREAD_ID_TYPE ThreadId;     // this thread's ID
	timeUnit m_Time;
    void *param;
    OMBoolean toTerminate;

#ifdef OM_USE_MULTIMEDIA_TIMER
	MMRESULT TimerHdl; // multimedia timer ID
#endif // OM_USE_MULTIMEDIA_TIMER

public:
    NTTimer(const timeUnit ptime, void pcbkfunc(void*), void *pparam); 
    NTTimer(void pcbkfunc(void*), void *pparam);

    ~NTTimer(void);
    virtual void* getOsHandle(void) const {
        return reinterpret_cast<void*>(hThread);
    }
	virtual void setAffinity(const OMAffinity_t aff);

#ifdef OM_USE_MULTIMEDIA_TIMER
	static void CALLBACK timerFunction(UINT wTimerID, UINT msg,
        OM_DWORD_PARAM_TYPE dwUser, OM_DWORD_PARAM_TYPE dw1, OM_DWORD_PARAM_TYPE dw2);
#endif // OM_USE_MULTIMEDIA_TIMER
};

class NTThread : public OMOSThread {
private:
    HANDLE hThread ;
    OM_THREAD_ID_TYPE ThreadId;      // this thread's ID
    Rhp_int32_t isWrapperThread;
    OMBoolean endOSThreadInDtor; // TRUE means that the os thread is ended as part of this object's destruction

public:
    NTThread(void tfunc(void*), void *param, const Rhp_int32_t stackSize = OMOSThread::DefaultStackSize);
    NTThread(void *osThreadId); // for creation of wrapper thread
    virtual ~NTThread(void);

    virtual void setPriority( const Rhp_int32_t aPriority );
    virtual void suspend(void) {
        (void)SuspendThread(hThread);
    }
    virtual void resume(void) {
        (void)ResumeThread(hThread);
    }
    virtual void start(void) {
        resume();
    }

    virtual void* getOsHandle(void) const {
        return (void*) ThreadId;
    }

    virtual void* getOsHandle(void*& osHandle) const { 
        osHandle = static_cast<void*>(hThread);
        return getOsHandle();
    }

    void setEndOSThreadInDtor(const OMBoolean val) { 
        endOSThreadInDtor = val;
    }

    // asking for a callback to end my os thread
    // onExecuteThread = TRUE: I will kill my own thread
    // onExecuteThread = FALSE: someone else will kill my thread
    virtual void getThreadEndClbk ( OMOSThreadEndCallBack* clb_p,   // a pointer to the callback function
                                    void** arg1_p,                  // the argument for this function
                                    const OMBoolean onExecuteThread );
	// end the thread I'm working on
	static void endMyThread(void*);
	// end a thread which is NOT my thread
	static void endOtherThread(void*);
	    //## operation getAffinity()
	virtual OMAffinity_t getAffinity(void) const;
		//## operation setAffinity(OMAffinity_t)
	virtual void setAffinity(const OMAffinity_t aff);

	virtual void setPwrState(const OMPowerMode_t /*val*/) {}

	virtual OMPowerMode_t getPwrState(void) const { return (OMPowerMode_t)0;}

	static void setThreadAffinity(HANDLE m_hThread, const OMAffinity_t coreId);

}; // NTThread


class NTMutex : public OMOSMutex {
private:
    CRITICAL_SECTION hMutex;
public:
    virtual void lock() {
        ::EnterCriticalSection(&hMutex);
    }
    virtual void unlock(void) {
        ::LeaveCriticalSection(&hMutex);
    }
    NTMutex(void) {
        ::InitializeCriticalSection(&hMutex);
    }
    ~NTMutex(void) {
        ::DeleteCriticalSection (&hMutex);
    }  
    CRITICAL_SECTION* getHandle(void) const {
        return const_cast<CRITICAL_SECTION*>(&hMutex);
    }
    virtual void* getOsHandle(void) const {
        return reinterpret_cast<void*>(const_cast<CRITICAL_SECTION*>(&hMutex));
    }
};


#ifndef NO_SEMAPHORE_IMPLEMENTATION
class NTSemaphore : public OMOSSemaphore {
public:
    NTSemaphore(const Rhp_uint64_t initialCount, const Rhp_uint64_t maxCount, const Rhp_const_char_pt name);
    ~NTSemaphore(void);
    virtual void signal(void);
    virtual OMBoolean wait(const Rhp_int64_t timeout = -1);
    virtual void* getOsHandle(void) const { 
        return static_cast<void*>(hSemaphore);
    }

private:
    HANDLE hSemaphore;
};
#endif // NO_SEMAPHORE_IMPLEMENTATION


class NTOSEventFlag : public OMOSEventFlag {
private:
    HANDLE 	hEventFlag;
public:
    virtual void signal(void);
    virtual void reset(void);
    virtual void wait(const Rhp_int32_t tminms = -1);  // tminms = -1 is wait forever
    NTOSEventFlag(void);
    ~NTOSEventFlag(void);
    virtual HANDLE getHandle(void) const {
        return hEventFlag;
    }
    virtual void* getOsHandle(void) const {
        return static_cast<void*>(hEventFlag);
    }
};


class NTOSMessageQueue : public OMOSMessageQueue {
private:
    OMQueueType m_theQueue;
    NTMutex	m_QueueMutex;
    NTOSEventFlag m_QueueEventFlag;
public:
    NTOSMessageQueue(const OMBoolean shouldGrow = TRUE, 
                     const Rhp_int32_t initSize = OMOSThread::DefaultMessageQueueSize ):
    m_theQueue(shouldGrow, initSize) {}
    virtual OMBoolean put(void*, const OMBoolean fromISR = FALSE);
    virtual void* get(void);
    virtual Rhp_int32_t isEmpty(void) const {
        return m_theQueue.isEmpty();
    }
    virtual void pend(void);
    virtual void getMessageList(OMListType& aList);
    virtual OMBoolean isFull(void) const {
        return m_theQueue.isFull();
    }
    virtual void* getOsHandle(void) const { 
        return static_cast<void*>(NULL);
    }
};

#ifdef _OMINSTRUMENT
#ifndef _WIN32_WCE
	#include <winsock.h>
#else
	#include <winsock2.h>
	#include <ws2tcpip.h>
#endif // _WIN32_WCE

class NTSocket: public OMOSSocket {
private:
    SOCKET theSock;
public:
    NTSocket(void);
    virtual ~NTSocket(void);
    virtual Rhp_int32_t Create  (const Rhp_const_char_pt SocketAddress = NULL,
                                 const Rhp_uint32_t nSocketPort = 0U );
    virtual Rhp_int32_t Send    (const Rhp_const_char_pt lpBuf,
                                 const Rhp_int32_t nBufLen );
    virtual Rhp_int32_t Receive (Rhp_char_pt lpBuf,
                                 const Rhp_int32_t nBufLen );
    virtual void Close(void);
};


class NTConnectionPort: public OMOSConnectionPort {
private:
    static void readFromSockLoop(NTConnectionPort* me);
    static Rhp_char_t* m_Buf;
    static Rhp_int32_t m_BufSize;

    NTMutex m_SendMutex;
    static Rhp_int32_t initializeWinSock(void);
    OMBoolean toTerminate;

    Rhp_int32_t m_Connected;
    void (*m_dispatchfunc)(OMSData*);
    HANDLE hSocketHandleThread;
    OM_THREAD_ID_TYPE ThreadId;      // this thread's ID
    NTSocket m_ntSocket;

public:
    Rhp_int32_t m_ShouldWaitForAck;

    NTOSEventFlag m_AckEventFlag;
    Rhp_int32_t m_NumberOfMessagesBetweenAck;

    NTConnectionPort(void);
    virtual ~NTConnectionPort(void);
    virtual Rhp_int32_t Connect( const Rhp_const_char_pt SocketAddress = NULL,
                                 const Rhp_uint32_t aSocketPort = 0);
    virtual Rhp_int32_t Send ( OMSData* aMessage );
    virtual void SetDispatcher( void (*dispatchfunc)(OMSData*)) {
        m_dispatchfunc = dispatchfunc;
    }

};
#endif


class NTOSFactory : public OMOSFactory {
    // OSFactory hides the RTOS mechanisms for tasking and synchronization
public:
    virtual OMOSMessageQueue* createOMOSMessageQueue ( const OMBoolean shouldGrow = TRUE, 
                                                       const Rhp_int32_t messageQueueSize = OMOSThread::DefaultMessageQueueSize) const { 
        return (OMOSMessageQueue*)new NTOSMessageQueue(shouldGrow, messageQueueSize);
    }

    virtual OMOSConnectionPort* createOMOSConnectionPort(void) const {
#ifdef _OMINSTRUMENT
        return (OMOSConnectionPort*)new NTConnectionPort();
#else
        return NULL;
#endif
    }

    virtual OMOSEventFlag* createOMOSEventFlag(void) const { 
        return (OMOSEventFlag *)new NTOSEventFlag();
    }

    virtual OMOSThread* createOMOSThread ( void (*tfunc)(void*),
                                           void *param,
                                           const Rhp_const_char_pt /* threadName */ = NULL,
                                           const Rhp_int32_t stackSize = OMOSThread::DefaultStackSize ) const {
        return (OMOSThread*)new NTThread(tfunc, param, stackSize);
    }

    virtual OMOSThread* createOMOSWrapperThread(void* osHandle) const {
        if (NULL == osHandle) {
            osHandle = getCurrentThreadHandle();
        }
        return (OMOSThread*)new NTThread(osHandle);
    }

    virtual OMOSMutex* createOMOSMutex(void) const { 
        return (OMOSMutex*)new NTMutex();
    }

    virtual OMOSSemaphore* createOMOSSemaphore ( const Rhp_uint64_t /* semFlags */ = 0U,
                                                 const Rhp_uint64_t initialCount = 1U, 
                                                 const Rhp_uint64_t maxCount = 1U, 
                                                 const Rhp_const_char_pt name = NULL ) const {
#ifdef NO_SEMAPHORE_IMPLEMENTATION
    return (OMOSSemaphore*) NULL;
#else
    return (OMOSSemaphore*) new NTSemaphore(initialCount,maxCount, name);
#endif // NO_SEMAPHORE_IMPLEMENTATION
    }

    virtual OMOSTimer* createOMOSTickTimer ( const timeUnit tim, 
                                             void (*cbkfunc)(void*),
                                             void* param ) const { 
		return (OMOSTimer*)new NTTimer(tim, cbkfunc, param);   // TickTimer for real time
	}

    virtual OMOSTimer *createOMOSIdleTimer( void (*cbkfunc)(void*),
                                            void *param ) const { 
        return (OMOSTimer*)new NTTimer(cbkfunc, param);   // Idle timer for simulated time
    }

    virtual void* getCurrentThreadHandle(void) const;
    virtual void delayCurrentThread(const timeUnit ms) const;

    virtual OMBoolean waitOnThread(void* osHandle, const timeUnit ms) const;
};

#endif // _ntos_H
