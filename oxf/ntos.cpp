//
//	purpose:	 	NT OS implementations 
//
//	Licensed Materials - Property of IBM
//	(c) Copyright IBM Corporation 1995, 2018. All Rights Reserved.
//
//  Note to U.S. Government Users Restricted Rights:  
//  Use, duplication or disclosure restricted by GSA ADP Schedule 
//  Contract with IBM Corp.
//
// ---------------------------------------------------------------
//|                            ntos.cpp                           |
// --------------------------------------------------------------- 

// Rhapsody Framework Includes
#include "ntos.h"
#include "event.h"
#include "timer.h"

#ifdef _OMINSTRUMENT
#include <aom/AnimServices.h>
#include <omcom/omsdata.h>
#include <oxf/oxf.h>

#ifndef _WIN32_WCE
#ifdef OM_STL
#include <cstdlib>
#include <cstdio>
#else
#include <stdlib.h>
#include <stdio.h>
#endif
#endif // _WIN32_WCE
#endif // _OMINSTRUMENT

#include "HdlCls.h"

#ifndef _WIN32_WCE
#ifndef __USE_CREATE_THREAD__
#include <process.h>
#endif // __USE_CREATE_THREAD__
#endif // _WIN32_WCE

#ifdef _WIN32_WCE
#include "omunicode.h"
#endif

#ifndef _OM_NO_IOSTREAM
#ifdef OM_STL
#include <fstream>
#else
#include <fstream.h>
#endif
#endif // _OM_NO_IOSTREAM

///////////////////////////////////////////
/// Init static 
///////////////////////////////////////////
const Rhp_int32_t OMOSThread::DefaultStackSize = 0;
const Rhp_int32_t OMOSThread::DefaultMessageQueueSize = 100;
const Rhp_int32_t OMOSThread::DefaultThreadPriority = PRIORITY_NORMAL;

#ifdef _WIN32_WCE
#ifdef _x86_ 
// in case of x86  we will always set the __USE_CREATE_THREAD__ macro
#define __USE_CREATE_THREAD__
#else
#if _WIN32_WCE > 200
#define __USE_CREATE_THREAD__
#endif
#endif
#endif

typedef unsigned ( __stdcall* start_addr_t)(void*);

OMOSFactory* OMOSFactory::instance(void){
	static NTOSFactory theFactory;
	return &theFactory;
}


void OMOS::endApplication(const Rhp_int32_t errorCode) {
	Rhp_uint32_t err = (static_cast<Rhp_uint32_t>(errorCode));
#ifdef _OMINSTRUMENT
	AnimServices::notifyEndApplication(false);
#endif // _OMINSTRUMENT
	OMThread::setEndOfProcess( true );
	if (TerminateProcess(GetCurrentProcess(), err) == 0)	{
		OM_NOTIFY_ERROR("TerminateProcess", "OMOS::endApplication")
	}
}

static void NTDoCloseHandle(void* param) {
	HANDLE hThread = param;
	if (WaitForSingleObject(hThread,INFINITE) == WAIT_FAILED)	{
		OM_NOTIFY_ERROR("WaitForSingleObject", "NTDoCloseHandle")
	}
	if (CloseHandle(hThread) == 0) {
		OM_NOTIFY_ERROR("CloseHandle", "NTDoCloseHandle")
	}
}

#ifdef _OMINSTRUMENT
#ifndef _WIN32_WCE
BOOL WINAPI NTOSExitHandlerRoutine(DWORD) {
	OMThread::setEndOfProcess( true );
	AnimServices::notifyEndApplication(true);
	return 0;
}

class NTOSExitRegister {
public:
	NTOSExitRegister(void) {
		if (SetConsoleCtrlHandler(NTOSExitHandlerRoutine, true) == 0) {
			OM_NOTIFY_ERROR("SetConsoleCtrlHandler", "NTOSExitRegister")
		}		
	}

} theNTOSExitRegister;

#endif // _WIN32_WCE
#endif // _OMINSTRUMENT

void OMOS::initEpilog(void) {
	(void)OMHandleCloser::instance(NTDoCloseHandle)->startBehavior();
}

void OMOS::endProlog(void) {
#ifdef _OMINSTRUMENT
	AnimServices::notifyEndApplication(true);
	AnimServices::cleanupOnEndApplication();
#endif // _OMINSTRUMENT

	OMHandleCloser* tempHandle = OMHandleCloser::instance();
	//delete all the threads in the system
	OMThread* currentThread = OMThread::stopAllThreads( tempHandle->getThread() );

	//now all the OMThreads except HandleCloser are destroyed
	//so time to stop HandleCloser
	//lint -save -e429 (aEvent should not be deleted)
	if ((tempHandle != NULL) && (tempHandle->getThread() != NULL)) {
		void *handle = NULL;
		(void) tempHandle->getThread()->getOsHandle(handle);
		tempHandle->sendCloseHandleCloserEvent();
		(void) OMOSFactory::instance()->waitOnThread(handle, 1000U);
	}
	//lint -restore

	// Timer thread has to be the last thread running as it is used
	// by reactive objects
	OMTimerManager::clearInstance();
	
	if (currentThread != NULL) {
		delete currentThread; // destructor will be calling exitthread
	}
}
#ifdef OM_WIN32_COMPILER_DISABLE_WARNING_4312
#pragma warning ( push )
#pragma warning ( disable : 4312 )
#endif // OM_WIN32_COMPILER_DISABLE_WARNING_4312

void* NTOSFactory::getCurrentThreadHandle(void) const {
	return reinterpret_cast<void*>( GetCurrentThreadId() );
}

#ifdef OM_WIN32_COMPILER_DISABLE_WARNING_4312
#pragma warning ( pop )
#endif // OM_WIN32_COMPILER_DISABLE_WARNING_4312

void NTOSFactory::delayCurrentThread( const timeUnit ms ) const {
    Sleep(static_cast<DWORD>(ms));
}

OMBoolean NTOSFactory::waitOnThread( void* osHandle, const timeUnit ms ) const {
	OMBoolean retVal = false;  
    if (osHandle != NULL) 
	{
	    DWORD aStatus = ::WaitForSingleObject (osHandle, static_cast<DWORD>(ms));	
		if (aStatus == WAIT_OBJECT_0) {
			if (::GetExitCodeThread (osHandle, &aStatus) != 0) {
				if (::CloseHandle (osHandle) == 0) {
					OM_NOTIFY_ERROR("CloseHandle", "NTOSFactory::waitOnThread")
				}
				retVal = true;
			} 
			else {
				OM_NOTIFY_ERROR("GetExitCodeThread", "NTOSFactory::waitOnThread")
			}
		}
		else {
			if (aStatus == WAIT_FAILED) {
			    OM_NOTIFY_ERROR("WaitForSingleObject", "NTOSFactory::waitOnThread")
			}
		}
	}
    return retVal;
}

#ifndef NO_SEMAPHORE_IMPLEMENTATION
NTSemaphore::NTSemaphore( const Rhp_uint64_t initialCount, 
                          const Rhp_uint64_t maxCount, 
                          const Rhp_const_char_pt name ) {
#ifdef _OM_UNICODE_ONLY
    if (0 == name) {
        hSemaphore = CreateSemaphore( NULL, initialCount, maxCount, NULL);
    } else {
        wchar_t wname[MAX_PATH];
        OMctow(wname,name,MAX_PATH);
        hSemaphore = CreateSemaphore( NULL, static_cast<LONG>(initialCount), static_cast<LONG>(maxCount), wname);
    }
#else
    hSemaphore = CreateSemaphore( NULL, static_cast<LONG>(initialCount), static_cast<LONG>(maxCount), name);
#endif
    if (hSemaphore == NULL) {
        OM_NOTIFY_ERROR("CreateSemaphore", "NTSemaphore::NTSemaphore")
    }
}  //lint !e818 ( parameter could be declared as pointing to const)

NTSemaphore::~NTSemaphore(void) { 
    //lint -e1740
    if (CloseHandle(hSemaphore) == 0) {
    OM_NOTIFY_ERROR("CloseHandle", "NTSemaphore::~NTSemaphore")
    }
}  

void NTSemaphore::signal(void) {
    LONG prev = 0;
    if (ReleaseSemaphore(hSemaphore,1,&prev) == 0) {
    OM_NOTIFY_ERROR("ReleaseSemaphore", "NTSemaphore::signal")
    }
}

OMBoolean NTSemaphore::wait(const Rhp_int64_t timeout) {
    DWORD result;
    if ( timeout < 0 ) {
        result = WaitForSingleObject( hSemaphore, INFINITE );
    } else {
        result = WaitForSingleObject( hSemaphore, static_cast<Rhp_uint32_t>(timeout) );
    }
    if (result == WAIT_FAILED) {
        OM_NOTIFY_ERROR("WaitForSingleObject", "NTSemaphore::wait")	
    }
    return (result == WAIT_OBJECT_0);
}
#endif // NO_SEMAPHORE_IMPLEMENTATION

void* NTOSMessageQueue::get(void) {
    void *aMessage;
    m_QueueMutex.lock();
    if (isEmpty() == 0) {
        aMessage = m_theQueue.get();
		if (isEmpty() == 1) {
			  m_QueueEventFlag.reset();
		}
    } else {
        aMessage = NULL;
    }
    m_QueueMutex.unlock();
    return aMessage;
}


void NTOSMessageQueue::pend(void) {
  if (isEmpty() != 0)  {
	m_QueueEventFlag.wait();
  }
}

OMBoolean NTOSMessageQueue::put(void* aMessage, const OMBoolean /* fromISR */) {
    m_QueueMutex.lock();
    Rhp_int32_t wasEmpty = isEmpty();

    OMBoolean res = m_theQueue.put(aMessage);

    if (wasEmpty != 0) {
        m_QueueEventFlag.signal();
    }
    m_QueueMutex.unlock();
    return res;
}

void NTOSMessageQueue::getMessageList(OMListType& aList) {
    // Copy to it all the messages I have
    m_theQueue.getInverseQueue(aList);
}


NTTimer::NTTimer(const timeUnit ptime, void pcbkfunc(void*), void* pparam): // TickTimer
    cbkfunc(pcbkfunc),
    m_Time(ptime),
    param(pparam),
	toTerminate(FALSE) {

#ifdef OM_USE_MULTIMEDIA_TIMER
	hThread = static_cast<HANDLE>(NULL);
    // Set resolution to the minimum supported by the system
	TIMECAPS tc;
	if (timeGetDevCaps(&tc, sizeof(TIMECAPS)) != TIMERR_NOERROR) {
        OM_NOTIFY_ERROR("timeGetDevCaps","NTTimer::NTTimer")
	}
	else {
		DWORD period = min(max(tc.wPeriodMin, 0), tc.wPeriodMax);
		if (timeBeginPeriod(period) != TIMERR_NOERROR) {
			OM_NOTIFY_ERROR("timeBeginPeriod","NTTimer::NTTimer")
		}
		else {
			period = max (period, static_cast<DWORD>(m_Time));

			// create the timer
			TimerHdl = timeSetEvent(
				period, //period
				0, // max system resolution
				timerFunction,
				(OM_DWORD_PARAM_TYPE)this,
				TIME_PERIODIC);

			if (!TimerHdl) {
				OM_NOTIFY_ERROR("timeSetEvent","NTTimer::NTTimer")
			}
		}
	}

#else
	DWORD threadId = 0;
#ifdef __USE_CREATE_THREAD__
    hThread = CreateThread( NULL,
                            0,                                                /* default stack size */
                            reinterpret_cast<LPTHREAD_START_ROUTINE>(bridge), /* thread function */
                            this,                                             /* argument to thread */
                            0,                                                /* use default creation flags */
                            &threadId);                                      /* returns the thread identifier */
#else
    hThread = (HANDLE) _beginthreadex( NULL,
                                       0,                                      /* default stack size */
                                       reinterpret_cast<start_addr_t>(bridge), /* thread function */
                                       this,                                   /* argument to thread */
                                       0,                                      /* use default creation flags */
                                       reinterpret_cast<UINT*>(&threadId) );   /* returns the thread identifier */

#endif
	ThreadId = threadId;
	if ( hThread == static_cast<HANDLE>(NULL)) {
        OM_NOTIFY_ERROR("_beginthreadex/CreateThread","NTTimer::NTTimer")
    }
#endif // OM_USE_MULTIMEDIA_TIMER
}

NTTimer::NTTimer(void pcbkfunc(void*), void* pparam):   // IdleTimer (Simulated Time) 
     cbkfunc(pcbkfunc),
     m_Time(1U), // Just create context-switch until the system enters idle mode
     param(pparam),
	 toTerminate(FALSE) {
	DWORD threadId = 0;
#ifdef __USE_CREATE_THREAD__
    hThread = CreateThread ( NULL,
                             0,                                               /* default stack size */
                             reinterpret_cast<LPTHREAD_START_ROUTINE>(bridge), /* thread function */
                             this,                                             /* argument to thread */
                             0,                                                /* use default creation flags */
                             &threadId);                                      /* returns the thread identifier */
#else
    hThread = (HANDLE) _beginthreadex ( NULL,
                                        0,                                      /* default stack size */
                                        reinterpret_cast<start_addr_t>(bridge), /* thread function */
                                        this,                                   /* argument to thread */
                                        0,                                      /* use default creation flags */
                                       reinterpret_cast<UINT*>(&threadId) );   /* returns the thread identifier */

#endif
	ThreadId = threadId;
    if ( hThread == static_cast<HANDLE>(NULL) ) {
        OM_NOTIFY_ERROR("_beginthreadex/CreateThread","NTTimer::NTTimer")
    }


#ifdef  WINCE_PRIORITY
    if (CeSetThreadPriority(hThread, PRIORITY_LOW) == FALSE) {
        OM_NOTIFY_ERROR("CeSetThreadPriority","NTTimer::NTTimer")
    }
#else
    if (SetThreadPriority(hThread, PRIORITY_LOW) == 0) {
        OM_NOTIFY_ERROR("SetThreadPriority","NTTimer::NTTimer")
    }
#endif // WINCE_PRIORITY
}

NTTimer::~NTTimer(void) {
#ifdef OM_USE_MULTIMEDIA_TIMER
	if (TimerHdl != 0)
	{
		(void)timeKillEvent(TimerHdl);
		TimerHdl = 0;
	}
#endif // OM_USE_MULTIMEDIA_TIMER
	if (hThread != 0) {
        void* executedOsHandle = OMOSFactory::instance()->getCurrentThreadHandle();
        // a handle to this' 'thread'
        void* myOsHandle = reinterpret_cast<void*>(ThreadId);
        OMBoolean onMyThread = ((executedOsHandle == myOsHandle) ? TRUE : FALSE);

        if (onMyThread) {
            NTThread::endMyThread(hThread);
        } else {
			toTerminate = TRUE;
            (void) OMOSFactory::instance()->waitOnThread(hThread, m_Time);
        }
        hThread = 0;
    }
    cbkfunc = NULL;
    param = NULL;
}

void NTTimer::setAffinity(const OMAffinity_t aff)
{
	NTThread::setThreadAffinity(hThread, aff);
}


#ifdef OM_USE_MULTIMEDIA_TIMER
void CALLBACK NTTimer::timerFunction(UINT, UINT, OM_DWORD_PARAM_TYPE dwUser, OM_DWORD_PARAM_TYPE, OM_DWORD_PARAM_TYPE)
{
    // This is used only to call callback function
  // Can only be static
	NTTimer* obj = (NTTimer*)dwUser;
	if (!(obj->toTerminate)&& !OMThread::isEndOfProcess()) {
		obj->cbkfunc(obj->param);
	}
	else
	{
		(void)timeKillEvent(obj->TimerHdl);
		obj->TimerHdl = 0;
	}
}

#endif // OM_USE_MULTIMEDIA_TIMER

void NTTimer::waitThread(void) {
	for (;;) {
		Sleep(static_cast<DWORD>(m_Time));
		if ((!toTerminate) && (!OMThread::isEndOfProcess())) {
			(*cbkfunc)(param);
		}
		else
		{
			// If This Flag is set then exit.
			break;   
		}
	}

}



void NTOSEventFlag::signal(void) {
    if (SetEvent(hEventFlag) == 0) {
        OM_NOTIFY_ERROR("SetEvent", "NTOSEventFlag::signal")
    }
}

void NTOSEventFlag::reset(void) {
    if (ResetEvent(hEventFlag) == 0) {
        OM_NOTIFY_ERROR("ResetEvent", "NTOSEventFlag::reset")
    }
}

void NTOSEventFlag::wait(const Rhp_int32_t tminms /* = -1 */) {
    DWORD res = 1;
    if ( -1 == tminms ) {
        res = WaitForSingleObject( hEventFlag, INFINITE );
    } else {
        res = WaitForSingleObject( hEventFlag, static_cast<Rhp_uint64_t>(tminms) );
    }
    if (res == WAIT_FAILED)	{
        OM_NOTIFY_ERROR("WaitForSingleObject", "NTOSEventFlag::wait")
    }
}

NTOSEventFlag::NTOSEventFlag(void) {
    hEventFlag = CreateEvent( NULL, 
                              FALSE /* autoreset */, 
                              FALSE /* initially not signaled */,
                              NULL );
    if (hEventFlag == NULL) {
        OM_NOTIFY_ERROR("CreateEvent", "NTOSEventFlag::NTOSEventFlag")
    }
}

NTOSEventFlag::~NTOSEventFlag(void) {
    if (CloseHandle(hEventFlag) == 0) {
        OM_NOTIFY_ERROR("CloseHandle", "NTOSEventFlag::~NTOSEventFlag")
    }
    hEventFlag = static_cast<HANDLE>(NULL);
}

NTThread::NTThread ( void tfunc(void*), 
                     void* param, 
                     const Rhp_int32_t stackSize )
                : ThreadId(0),isWrapperThread(0),endOSThreadInDtor(TRUE) {

    // Create SUSPENDED thread !!!!!!
	DWORD threadId = 0;					
#ifdef __USE_CREATE_THREAD__
    hThread = CreateThread( NULL,
                            static_cast<DWORD>(stackSize),                   /* stack size */
                            reinterpret_cast<LPTHREAD_START_ROUTINE>(tfunc), /* thread function */
                            param,                                           /* argument to thread */
                            CREATE_SUSPENDED,                                /* use default creation flags */
							&threadId);                                      /* returns the thread identifier */
#else
    hThread = (HANDLE) _beginthreadex( NULL,
                                       static_cast<Rhp_uint32_t>(stackSize),	/* stack size */
                                       reinterpret_cast<start_addr_t>(tfunc),	/* thread function */
                                       param,                                   /* argument to thread */
                                       CREATE_SUSPENDED,                        /* use default creation flags */
                                       reinterpret_cast<UINT*>(&threadId));   	/* returns the thread identifier */

#endif
	ThreadId = threadId;
    if ( hThread == static_cast<HANDLE>(NULL) ) {
        OM_NOTIFY_ERROR("_beginthreadex/CreateThread","NTThread::NTThread")
    }
}

NTThread::NTThread(void *osThreadId)
: hThread(NULL),ThreadId((OM_THREAD_ID_TYPE)osThreadId),isWrapperThread(1),endOSThreadInDtor(TRUE) {
// Create wrapper thread for threads that exist outside of the framework
#ifdef _WIN32_WCE
    // WCE does not support the DuplicateHandle system call
    hThread = GetCurrentThread();
#else
    HANDLE pseudoHandle = GetCurrentThread();
    if ( DuplicateHandle( GetCurrentProcess(),      // handle to process with handle to duplicate
                          pseudoHandle,             // handle to duplicate
                          GetCurrentProcess(),      // handle to process to duplicate to
                          &hThread,                 // pointer to duplicate handle 
                          THREAD_ALL_ACCESS,        // access for duplicate handle
                          FALSE,                    // handle inheritance flag
                          0 ) == 0) {               // optional actions
        OM_NOTIFY_ERROR("DuplicateHandle", "NTThread::NTThread")
    }

#endif // _WIN32_WCE
}

void NTThread::endMyThread(void* p_hThread) {
    //lint -save -e429 (closeHandle should not be deleted)
    OMHandleCloser::instance()->genCloseEvent(p_hThread);

    //lint -restore
    // real ending my thread
#ifdef __USE_CREATE_THREAD__
	ExitThread(0);
#else
	_endthreadex(0);
#endif
	// there is a memory leakage of the handle
}

void NTThread::endOtherThread(void* handle) {
    // terminate a thread which its handle is given

    // NOTE: TerminateThread is known to have memory leaks
    if (TerminateThread(handle,0) == 0) {
        OM_NOTIFY_ERROR("TerminateThread", "NTThread::endOtherThread")
    }
}

void NTThread::getThreadEndClbk ( NTThread::OMOSThreadEndCallBack* clb_p,
                                  void** arg1_p, 
                                  const OMBoolean onExecuteThread ) {
    if (onExecuteThread) {
        // asking for a callback to end my own thread
        *clb_p = &endMyThread;
        *arg1_p = &hThread;
    } else {
        // asking for a callback to end my thread by someone else
        *clb_p = &endOtherThread;
        // my thread handle
        *arg1_p = &hThread;
    }
}

NTThread::~NTThread(void) {
    if (isWrapperThread == 0) {
        if (endOSThreadInDtor) {
            OMOSThread::OMOSThreadEndCallBack theOSThreadEndClb = NULL;
            OMOSHandle* threadHandle = NULL;
            OMBoolean onMyThread = exeOnMyThread(); //lint !e1506 (Call to virtual function within a ctor/dtor)
            // get a callback function to end the os thread
            getThreadEndClbk(&theOSThreadEndClb,reinterpret_cast<void**>(&threadHandle),onMyThread); //lint !e1506 (Call to virtual function within a ctor/dtor)
            if (theOSThreadEndClb != NULL) {
                // ending the os thread
                (*theOSThreadEndClb)(*threadHandle);
            }
        }
    }
    hThread = (HANDLE)NULL;
}

#ifdef WINCE_PRIORITY
// WinCE
void NTThread::setPriority(const Rhp_int32_t aPriority) {
    if (CeSetThreadPriority(hThread, aPriority) == FALSE) {
        OM_NOTIFY_ERROR("CeSetThreadPriority","NTThread::setPriority")
    }
}
#else
// Win32
void NTThread::setPriority(const Rhp_int32_t aPriority) {
    if (SetThreadPriority(hThread, aPriority) == 0) {
        OM_NOTIFY_ERROR("SetThreadPriority","NTThread::setPriority")
    }
}
#endif // WINCE_PRIORITY

OMAffinity_t NTThread::getAffinity(void) const
{
	OM_DWORD_PARAM_TYPE aff = (OMAffinity_t)0;
#ifndef OM_NO_MC_SUPPORT
	// there is no getThreadAffinityMask API so we use repeated setThreadAffinityMask 
	// call to take thread affinity mask and then restore it
	aff =  SetThreadAffinityMask(hThread,(OM_DWORD_PARAM_TYPE)1);
	(void)SetThreadAffinityMask(hThread,aff); 
#endif // OM_NO_MC_SUPPORT
	return (OMAffinity_t)aff;
}

void NTThread::setAffinity(const OMAffinity_t aff)
{
	setThreadAffinity(hThread, aff);
}

void NTThread::setThreadAffinity(HANDLE m_hThread, const OMAffinity_t coreId)
{
#ifndef OM_NO_MC_SUPPORT
	OM_DWORD_PARAM_TYPE new_aff = (OM_DWORD_PARAM_TYPE)coreId;
	OM_DWORD_PARAM_TYPE aff = SetThreadAffinityMask(m_hThread,new_aff);
	if (aff == 0U) {
		OM_NOTIFY_ERROR("SetThreadAffinityMask","NTThread::setThreadAffinity")
	}
#endif // OM_NO_MC_SUPPORT
}

#ifdef _OMINSTRUMENT

NTSocket::NTSocket(void) {
    theSock = 0;
}

NTSocket::~NTSocket(void) {
    if (theSock != 0) {
        if (closesocket(theSock) == SOCKET_ERROR) {
            OM_NOTIFY_ERROR("closesocket","NTSocket::~NTSocket")
        }
    }
}

void NTSocket::Close(void) {
    if (theSock != 0) {
        if( closesocket(theSock) == 0 ) {
            theSock = 0;
        } else {
            OM_NOTIFY_ERROR("closesocket","NTSocket::Close")
        }
    }
}


Rhp_int32_t NTSocket::Create( const Rhp_const_char_pt SocketAddress /*= NULL*/,
                              const Rhp_uint32_t nSocketPort /*= 0*/) {
#ifndef _WIN32_WCE
    static struct sockaddr_in addr;
    Rhp_int32_t proto;
    struct hostent* host = NULL;
    Rhp_char_t hostName[128];
    Rhp_int32_t port;
    Rhp_const_char_pt address = SocketAddress;

    if ( nSocketPort == 0U ) {
        port = 6423U;
    } else {
        port = nSocketPort;
    }

    addr.sin_family = AF_INET;

    struct protoent	*protocol;
    Rhp_char_pt proto_name = const_cast<Rhp_char_pt>("tcp");
    if ((protocol = getprotobyname(proto_name)) == (struct protoent *) 0) {
        OM_NOTIFY_ERROR("getprotobyname","NTSocket::Create")
        OM_NOTIFY_TO_ERROR("Could not get the AF_INET protocol\n");
        return 0;
    }
    proto = protocol->p_proto;

    (void)gethostname(hostName, sizeof(hostName)-1);
    if (NULL != address) {
        if (!strcmp(hostName,address)) {
        address = NULL;
    } else {
        (void)strcpy(hostName,address);
        host = gethostbyname(hostName);
        if (host == (struct hostent*) NULL) {
            Rhp_char_t msg[100];
#ifndef _OM_UNICODE_ONLY
            (void)sprintf(msg,"Could not get the address of host '%s'\n",hostName);
#else
            wchar_t wmsg[100];
            wchar_t whostName[128];
            OMctow (whostName,hostName,128);
            (void)swprintf(wmsg,L"Could not get the address of host '%s'\n",whostName);
            OMwtoc (msg,wmsg,100);
#endif // _OM_UNICODE_ONLY
            OM_NOTIFY_ERROR("gethostbyname", "NTSocket::Create")
            OM_NOTIFY_TO_ERROR(msg);
            return 0;
            }
        }
    }

#ifdef unix
#ifndef CYGWIN
  endprotoent();
#endif // CYGWIN
#endif // unix

    addr.sin_port = htons( static_cast<u_short>(port) );

    if (NULL == address) {
        addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    } else {
        if (host) {
            addr.sin_addr.s_addr = *(reinterpret_cast<ULONG*>(host->h_addr));
        }
    }

    if ((theSock = socket(AF_INET, SOCK_STREAM, proto)) == INVALID_SOCKET) {
        OM_NOTIFY_ERROR("socket","NTSocket::Create")
        OM_NOTIFY_TO_ERROR("Could not create socket\n");
        theSock = 0;
        return 0;
    }

    // If the rate of messages send between Rhapsody and the application is very high,
    // for example, in a recursive creation of over a 1000 instances (when each instance create some more instances in it constructor)
    // The socket internal buffer will get to be full, this will can a very slow communication between Rhapsody and the application.
    // To increase the size of the socket buffers (default is 8k) remove the remarks form the next 3 lines.
    // Rhp_int32_t socketBufSize = 64 * 1024;	// 64k
    // setsockopt(theSock, SOL_SOCKET , SO_RCVBUF, (char*) &socketBufSize, sizeof(int));
    // setsockopt(theSock, SOL_SOCKET , SO_SNDBUF, (char*) &socketBufSize, sizeof(int));

    Rhp_int32_t rvStat;
    while ((rvStat = connect(theSock, (struct sockaddr *) &addr, sizeof(addr))) == SOCKET_ERROR && /*lint !e740*/
        (WSAGetLastError() == WSAEINTR)) {}
        ;

    if (SOCKET_ERROR == rvStat) {
    Rhp_char_t msg[100];
#ifndef _OM_UNICODE_ONLY
    (void)sprintf(msg, "Could not connect to server at %s port %d\n Error No. : %d\n",
                        hostName,
                        static_cast<Rhp_int32_t>(port),
                        WSAGetLastError() );
#else
    wchar_t wmsg[100];
    wchar_t whostName[128];
    OMctow(whostName,hostName,128);
    (void)swprintf(wmsg,
            L"Could not connect to server at %s port %d\n Error No. : %d\n",
            whostName,
            static_cast<Rhp_int32_t>(port),
            WSAGetLastError() );
    OMwtoc(msg,wmsg,100);
#endif // _OM_UNICODE_ONLY
    OM_NOTIFY_ERROR("connect", "NTSocket::Create")
    OM_NOTIFY_TO_ERROR(msg);
    return 0;
    }

#else // _WIN32_WCE  
  
    Rhp_char_t hostName[128];
    Rhp_int32_t port;
    Rhp_const_char_pt address = SocketAddress;
	Rhp_char_t portName[10];
	struct addrinfo aiHints;
	struct addrinfo *aiList = NULL;
	Rhp_int32_t retVal;

    if ( nSocketPort == 0U ) {
        port = 6423U;
    } else {
        port = nSocketPort;
    }

	(void)gethostname(hostName, sizeof(hostName)-1);
	if (NULL != address) {
		if (!strcmp(hostName,address)) {
			address = NULL;
		}
		else {
			(void)strcpy(hostName,address);

			sprintf(portName,"%d",port);

			//--------------------------------
			// Setup the hints address info structure
			// which is passed to the getaddrinfo() function
			memset(&aiHints, 0, sizeof(aiHints));
			aiHints.ai_family = AF_INET;
			aiHints.ai_socktype = SOCK_STREAM;
			aiHints.ai_protocol = IPPROTO_TCP;

			//--------------------------------
			// Call getaddrinfo(). If the call succeeds,
			// the aiList variable will hold a linked list
			// of addrinfo structures containing response
			// information about the host
			if((retVal = getaddrinfo(hostName, portName, &aiHints, &aiList)) != 0) {
				Rhp_char_t msg[100];
#ifndef _OM_UNICODE_ONLY
				(void)sprintf(msg,"Could not get the address of host '%s'\n",	hostName);
#else
				wchar_t wmsg[100];
				wchar_t whostName[128];
				OMctow(whostName,hostName,128);
				(void)swprintf(wmsg,L"Could not get the address of host '%s'\n",whostName);
				OMwtoc(msg,wmsg,100);
#endif // _OM_UNICODE_ONLY
				OM_NOTIFY_ERROR("gethostbyname","NTSocket::Create")
				OM_NOTIFY_TO_ERROR(msg);
				return 0;
			}
		}
	}
        
	if ((theSock = socket(aiList->ai_family, aiList->ai_socktype, aiList->ai_protocol)) == INVALID_SOCKET) {

		OM_NOTIFY_ERROR("socket","NTSocket::Create")
		OM_NOTIFY_TO_ERROR("Could not create socket\n");
		theSock = 0;
		return 0;
	}

	Rhp_int32_t rvStat;
	while ((rvStat = connect(theSock, aiList->ai_addr, aiList->ai_addrlen)) == SOCKET_ERROR && /*lint !e740*/
		(WSAGetLastError() == WSAEINTR)) {}
	;

  if (SOCKET_ERROR == rvStat) {
	  Rhp_char_t msg[100];
#ifndef _OM_UNICODE_ONLY
	 (void)sprintf(msg,
			"Could not connect to server at %s port %d\n Error No. : %d\n",hostName,static_cast<Rhp_int32_t>(port),WSAGetLastError());
#else
	 wchar_t wmsg[100];
	 wchar_t whostName[128];
	 OMctow(whostName,hostName,128);
	 (void)swprintf(wmsg,
			L"Could not connect to server at %s port %d\n Error No. : %d\n",whostName,static_cast<Rhp_int32_t>(port),WSAGetLastError());
	 OMwtoc(msg,wmsg,100);
#endif // _OM_UNICODE_ONLY
	 OM_NOTIFY_ERROR("connect","NTSocket::Create")
	 OM_NOTIFY_TO_ERROR(msg);
	 return 0;
  }
  if (aiList != NULL)
  {
	freeaddrinfo(aiList);
  }
#endif // _WIN32_WCE
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  return 1;
}

Rhp_int32_t NTSocket::Send ( const Rhp_const_char_pt lpBuf, 
                             const Rhp_int32_t nBufLen ) {
    Rhp_int32_t bytes_written = 0;
    Rhp_int32_t n;

    while (bytes_written < nBufLen) {
    n = send(theSock, &lpBuf[bytes_written], nBufLen - bytes_written, 0);
        if (SOCKET_ERROR == n) {
            if (WSAGetLastError() == WSAEINTR) {
                continue;
            } else {
                OM_NOTIFY_ERROR("send", "NTSocket::Create")
                return -1;
            }
        }
    bytes_written += n;
  }
  return bytes_written;
}

Rhp_int32_t NTSocket::Receive ( Rhp_char_pt lpBuf, 
                                const Rhp_int32_t nBufLen ) {
    Rhp_int32_t bytes_read = 0;
    Rhp_int32_t n;

    while (bytes_read < nBufLen) {
        n = recv(theSock, lpBuf + bytes_read, nBufLen - bytes_read,0);
        if (SOCKET_ERROR == n) {
            if (WSAGetLastError() == WSAEINTR) {
                continue;
            } else {
                OM_NOTIFY_ERROR("recv","NTSocket::Create")
                return -1;
            }
        }
        bytes_read += n;
    }
    return bytes_read;
}

Rhp_char_pt NTConnectionPort::m_Buf = NULL;
Rhp_int32_t NTConnectionPort::m_BufSize = 0;

//// Communication check
//static ofstream* csendFile = NULL;

NTConnectionPort::NTConnectionPort(void) {
    m_Connected = 0;
    m_dispatchfunc = NULL;
    hSocketHandleThread = NULL;

    m_ShouldWaitForAck = 1;
    m_NumberOfMessagesBetweenAck = 0;
    m_AckEventFlag.reset();

    toTerminate = FALSE;
    ThreadId = 0;
}

NTConnectionPort::~NTConnectionPort(void) {
    if (hSocketHandleThread) {
        toTerminate = TRUE;
        m_ntSocket.Close();

        if ( OMOSFactory::instance()->getCurrentThreadHandle() != (void*)ThreadId )
            (void) OMOSFactory::instance()->waitOnThread( hSocketHandleThread, 1000 ) ;
        }
    // I assume that we will have only one connection port
    // so I can free the data for m_Buf but if it is not the case
    // it does not matter ( the readFromSockLoop will allocate it )
    if (m_Buf) {
        OMDELETE(m_Buf, m_BufSize);
        m_Buf = NULL;
    }
    m_BufSize = 0;
    m_dispatchfunc = NULL;
    hSocketHandleThread = (HANDLE)NULL;
}

void NTConnectionPort::readFromSockLoop(NTConnectionPort* me) {
    Rhp_char_t lenStr[MAX_LEN_STR+1];
#ifdef _OM_UNICODE_ONLY
    wchar_t wlenStr[MAX_LEN_STR+1];
#endif // _OM_UNICODE_ONLY
    Rhp_int32_t len;
    Rhp_int32_t rv;
    for (;;) {
    rv = me->m_ntSocket.Receive(lenStr,MAX_LEN_STR);

    if (me->toTerminate) {
        return;
    }

    if (rv == -1) {
        OM_NOTIFY_TO_ERROR("Terminating application\n");
        OMOS::endApplication(0);
    }
    lenStr[MAX_LEN_STR] = '\0';
    Rhp_int32_t res;
#ifndef _OM_UNICODE_ONLY
    res = sscanf(lenStr,"%d",&len);
#else
    OMctow(wlenStr,lenStr,MAX_LEN_STR);
    res = swscanf(wlenStr,L"%d",&len);
#endif // _OM_UNICODE_ONLY
    if (res == 1) {
        Rhp_int32_t oldBufSize = m_BufSize;
        if (len > m_BufSize ) {
            m_BufSize = 1000 + len;
            if (m_Buf) {
                OMDELETE(m_Buf, oldBufSize);
            }
            m_Buf = OMNEW(char, m_BufSize); //lint !e119 (lint fail to find the replacement new operator)
        }
        if (len == -2) { // Acknowledge message
            me->m_AckEventFlag.signal();
            continue;
        }
        m_Buf[len] = '\0';
        rv = me->m_ntSocket.Receive(m_Buf,len);

        if(me->toTerminate) {
            return;
        }

        if (rv == -1) {
            OM_NOTIFY_TO_ERROR("Terminating application\n");
            OMOS::endApplication(0);
        }
        // len is not used by OMSData but we need to change
        // the interface so we will use the length of the data
        // and not assume that the string is null terminated

        // if socket thread is doing some work that may send
        // messages we do not want to Block the Send by waiting for
        // acknowledgement since the thread cannot handle the acknowledgement
        // ( since the thread is self locked)
        me->m_ShouldWaitForAck = 0;
        me->m_AckEventFlag.signal();
        me->m_dispatchfunc(OMSData::string2OMSData(m_Buf));
        me->m_ShouldWaitForAck = 1;
        }
    }
}

Rhp_int32_t NTConnectionPort::initializeWinSock(void) {
    static Rhp_int32_t initialized = 0;
    if ( 0 == initialized ) {
        WORD wVersionRequested;
        WSADATA wsaData;
        int err;
        wVersionRequested = MAKEWORD(1, 1);

        err = WSAStartup(wVersionRequested, &wsaData);

        if (err != 0) {
            /* Tell the user that we couldn't find a useable */
            /* winsock.dll.     */
            OM_NOTIFY_ERROR("WSAStartup","NTConnectionPort::initializeWinSock")		
            OM_NOTIFY_TO_ERROR("Unable to locate winsock library");
            return 0;
        }
        /* Confirm that the Windows Sockets DLL supports 1.1.*/
        /* Note that if the DLL supports versions greater */
    }
    return 1;
}

Rhp_int32_t NTConnectionPort::Connect( const Rhp_const_char_pt SocketAddress /*= NULL*/,
                                       const Rhp_uint32_t aSocketPort /*= 0*/) {
    if ( 0  == initializeWinSock() ) {
        return 0;
    }

    if (NULL == m_dispatchfunc) {
        OM_NOTIFY_TO_ERROR(" NTConnectionPort::SetDispatcher should be called before NTConnectionPort::Connect()\n");
        return 0;
    }
    if ( 0  == m_Connected ) {
        m_Connected = m_ntSocket.Create(SocketAddress, aSocketPort);
    }
    if (0 == m_Connected) {
        return 0;
    }

    // Connection established
    // invoking thread to recieve messages from the socket
	DWORD threadId = 0;
#ifdef __USE_CREATE_THREAD__
    hSocketHandleThread = CreateThread( 
                    NULL,
                    0 ,                                                             /* default stack size */
                    reinterpret_cast<LPTHREAD_START_ROUTINE>(readFromSockLoop),     /* thread function */
                    this,                                                           /* argument to thread */
                    0,                                                              /* use default creation flags */
					&threadId);                                      /* returns the thread identifier */
#else
    hSocketHandleThread = (HANDLE) _beginthreadex( 
                    NULL,
                    0,                                                              /* default stack size */
                    reinterpret_cast<start_addr_t>(readFromSockLoop),               /* thread function */
                    this,                                                           /* argument to thread */
                    0,                                                              /* use default creation flags */
                    reinterpret_cast<UINT*>(&threadId) );   /* returns the thread identifier */

#endif
	ThreadId = threadId;
	if ( hSocketHandleThread == static_cast<HANDLE>(NULL)) {
        OM_NOTIFY_ERROR("_beginthreadex/CreateThread","NTConnectionPort::Connect")
    }

	if (OXF::frmThreadAffinities.AnimMessageReader != 0U)
	{	// multi core support
		NTThread::setThreadAffinity(hSocketHandleThread, OXF::frmThreadAffinities.AnimMessageReader);
	}

    return m_Connected;
}

Rhp_int32_t NTConnectionPort::Send(OMSData* msg) {
    Rhp_int32_t rv = 0;

    m_SendMutex.lock();
    if (m_Connected) {
        Rhp_char_t lenStr[MAX_LEN_STR+1];
        for (Rhp_int32_t i=0; i<MAX_LEN_STR; ++i) {
            lenStr[i] = '\0';
        }
#ifdef _OM_UNICODE_ONLY
        wchar_t wLenStr[MAX_LEN_STR+1];
        (void)swprintf(wLenStr,L"%d",msg->getLength());
        OMwtoc(lenStr, wLenStr, MAX_LEN_STR+1);
#else
        (void)sprintf(lenStr,"%d",msg->getLength());
#endif // _OM_UNICODE_ONLY

        rv = m_ntSocket.Send(lenStr,MAX_LEN_STR);
        if (rv > 0) {
            rv = m_ntSocket.Send(msg->getRawData(),msg->getLength());
        }
        if (m_ShouldWaitForAck) {
            const Rhp_int32_t maxNumOfMessagesBetweenAck = 127; //MUST match the number in rhapsody
            m_NumberOfMessagesBetweenAck++;
            if (m_NumberOfMessagesBetweenAck >= maxNumOfMessagesBetweenAck) {
                m_NumberOfMessagesBetweenAck = 0;
                m_AckEventFlag.wait();
                m_AckEventFlag.reset();
            }
        }
    }
    m_SendMutex.unlock();
    return rv;
}
#endif 
// end of NTSocket and NTConnectionPort ifdef _OMINSTRUMENT

 
 
 
 
 
 
 
 
 
 
 
 
 
