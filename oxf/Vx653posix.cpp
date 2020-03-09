//
//	file name   :	$Source: R:/StmOO/Master/cg/LangCpp/oxf/rcs/Vx653posix.cpp $
//	file version:	$Revision: 1.1 $
//
//	purpose:	 	
//
//	author(s):		
//	date started:	
//	date changed:	$Date: 2007/05/28 07:43:50 $
//	last change by:	$Author: ilvler $
//
//	Licensed Materials - Property of IBM
//	(c) Copyright IBM Corporation 2008, 2016. All Rights Reserved.
//	
//	Note to U.S. Government Users Restricted Rights:  
//	Use, duplication or disclosure restricted by GSA ADP Schedule 
//	Contract with IBM Corp.
//

// Rhapsody Framework includes
#include "oxf.h"
#include "Vx653posix.h"
#include "omthread.h"
#include "timer.h"

#include <ctype.h>
#include <errno.h>
#include <fcntl.h>

#ifdef _OMINSTRUMENT
#include <aom/AnimServices.h>
#endif // _OMINSTRUMENT
#ifdef _OMINSTRUMENT
#include <omcom/omsdata.h>

#ifdef _WRS_KERNEL
#include <socket.h>
#include <rpc/rpc.h>
#include <in.h>
#else
#include <sys/socket.h>
#endif /* _WRS_KERNEL */

#include <stdio.h>
#include <sys/types.h>
#include <sockLib.h>
#include <unistd.h>
#include <hostLib.h>
#include <arpa/inet.h>
#endif // _OMINSTRUMENT

const Rhp_int32_t OMOSThread::DefaultStackSize = DEFAULT_STACK;
const Rhp_int32_t OMOSThread::DefaultMessageQueueSize = MQ_DEFAULT_SIZE;
const Rhp_int32_t OMOSThread::DefaultThreadPriority = PRIORITY_NORMAL;
const Rhp_int64_t OMOS_MSec = 1000;
const Rhp_int64_t OMOS_MicroSec = 1000000;
const Rhp_int64_t OMOS_NSec = 1000000000;
// TODO
const Rhp_int32_t LowestPriority = 0; 

OMOSFactory* OMOSFactory::instance(void) {
    static Vx653OSFactory theFactory;
    return &theFactory;
}

void OMOS::initEpilog(void) {
}

void OMOS::endProlog(void) {
    return;
}

void OMOS::endApplication(const Rhp_int32_t errcode) {
#ifdef _OMINSTRUMENT
  AnimServices::notifyEndApplication(false);
#endif // _OMINSTRUMENT
  OMThread::setEndOfProcess(true);
	OXFTDelay(OMTimerManager::instance()->getTick() *2);
#ifdef _OMINSTRUMENT
  AnimServices::endApplication();
#else
  OMTimerManager::clearInstance();
#endif // _OMINSTRUMENT
  // make sure that the execution thread is being endded
  exit(errcode);
}

void* Vx653OSFactory::getCurrentThreadHandle(void) const {
    return reinterpret_cast<void*>(pthread_self());
}

void Vx653OSFactory::delayCurrentThread(const OxfTimeUnit ms) const {
	struct timespec tms;

	if (ms > 0) {
		Vx653Timer::evaluateSleepTime(tms, ms);
		nanosleep(&tms, NULL);
	} else {
		sched_yield(); // give up current time slice
	}
}

void Vx653OSMessageQueue::Exit_Handler( int sig_number )
{
	OMOS::endApplication(sig_number)	;
}


Vx653OSMessageQueue::Vx653OSMessageQueue(const OMBoolean /*shouldGrow*/, const Rhp_int32_t messageQueueSize): 
  pmessage(NULL),m_State(noData)	
{
  	struct mq_attr attr ;
    hVx653MQ = (mqd_t)-1;

    while(hVx653MQ == (mqd_t)-1) 
    {
		Mq_name();     
		attr.mq_maxmsg = messageQueueSize ;
		attr.mq_msgsize = sizeof(void *) ;
		hVx653MQ = mq_open(name,O_RDWR | O_CREAT | O_NONBLOCK , 0, &attr);
	 }
	signal(SIGINT,Vx653OSMessageQueue::Exit_Handler);
}

Vx653OSMessageQueue::~Vx653OSMessageQueue(void)
{
  if (hVx653MQ) {
		mq_unlink(name);
		hVx653MQ = 0;
	}
}

void *Vx653OSMessageQueue::get(void) {
	struct mq_attr attr ;
	void *m ;

	if (m_State == dataReady) {
			m = pmessage;
			m_State = noData;
	}
	else {
		if (!isEmpty()) {
			mq_getattr(hVx653MQ, &attr);
			attr.mq_flags = O_NONBLOCK ;
			mq_setattr(hVx653MQ,&attr,NULL);
 			mq_receive(hVx653MQ,(char*)&m, sizeof(m) ,NULL);
		}
		else {
				return NULL;
		}
	}
	return m ;
}


void Vx653OSMessageQueue::pend(void) {
	struct mq_attr attr ;

	if (isEmpty()) {
	  void *m;
	  mq_getattr(hVx653MQ, &attr);
	  attr.mq_flags = 0 ;
	  mq_setattr(hVx653MQ, &attr, NULL) ;
	  mq_receive(hVx653MQ,(char*)&m, sizeof(m) ,NULL);
	  m_State = dataReady;
	  pmessage = m;
	}
}

OMBoolean Vx653OSMessageQueue::put(void* aMessage, const OMBoolean fromISR) {
	struct mq_attr attr ;
	int	retr = 1 ;
	int priority = 10 ;
	static void* NULL_VAL = NULL;
	if (NULL == aMessage) {
		aMessage = NULL_VAL;
	}
	
	mq_getattr(hVx653MQ, &attr);
	attr.mq_flags = 0 ;
	
	if (fromISR) {
		attr.mq_flags = O_NONBLOCK;
		priority = HighestPriority ;
	}
	mq_setattr(hVx653MQ,&attr,NULL);

	retr = mq_send(hVx653MQ,(char *)&aMessage, sizeof(aMessage), priority);
	
	if (retr != -1) 
		return TRUE;
	else 
		return FALSE;	
}


Rhp_int32_t Vx653OSMessageQueue::isEmpty(void) const {
	struct mq_attr attr ;
	mq_getattr(hVx653MQ, &attr );
	if (noData == m_State && 0 == attr.mq_curmsgs ) 
		return TRUE;
	else
		return FALSE;
}


void Vx653OSMessageQueue::getMessageList(OMListType& aList) {
    	aList.removeAll();
// TODO
}

OMBoolean Vx653OSMessageQueue::isFull(void) const {
    OMBoolean status = false;

	struct mq_attr attr ;
	if (!isEmpty())
  {
  	mq_getattr(hVx653MQ, &attr );
  	if (attr.mq_curmsgs >= attr.mq_maxmsg) {
  	 status = true;
  	}
  }
  return status;
}

// the formal pthread_create parameter
extern "C" {
    typedef void*(*FormalThrCreateFunc)(void*);
}

 // TickTimer
Vx653Timer::Vx653Timer( const OxfTimeUnit ptime, void pcbkfunc(void *), void *pparam ):
     cbkfunc(pcbkfunc),
     m_Time(ptime),
     param(pparam) {
    pthread_attr_t tthread_attr;
    pthread_attr_init( &tthread_attr );
    pthread_attr_setstacksize( &tthread_attr, PTHREAD_STACK_MIN);
    pthread_attr_setdetachstate( &tthread_attr, PTHREAD_CREATE_DETACHED );
    pthread_attr_setinheritsched( &tthread_attr, PTHREAD_INHERIT_SCHED );

    pthread_create ( &hThread, //Handle
                    &tthread_attr, // default attributes
                    reinterpret_cast<FormalThrCreateFunc>(bridge),
                    static_cast<void*>(this));

 // Create a thread that runs bridge, passing this as argument 
}

// IdleTimer (Simulated Time) 
Vx653Timer::Vx653Timer( void pcbkfunc(void *), void *pparam):
     cbkfunc(pcbkfunc),
     m_Time(5), // Just create context-switch until the system enters idle mode
     param(pparam),
     ticks(1) {
	// Just create context-switch until the system enters idle mode
    pthread_attr_t tthread_attr;

    pthread_attr_init( &tthread_attr );
    pthread_attr_setstacksize( &tthread_attr, PTHREAD_STACK_MIN);
    pthread_attr_setdetachstate( &tthread_attr, PTHREAD_CREATE_DETACHED );
    pthread_attr_setinheritsched( &tthread_attr, PTHREAD_INHERIT_SCHED );

    pthread_create ( &hThread, // Handle 
                     &tthread_attr, // default attributes
                     reinterpret_cast<FormalThrCreateFunc>(bridge),
                    static_cast<void*>(this));

 // Create a thread that runs bridge, passing this as argument
 // have to set the lowest priority for the simulated timer, in order to
 // make sure it get activate when all other threads are Idle

    Rhp_int32_t policy;
    sched_param param;

    pthread_getschedparam(hThread, &policy, &param );
    param.sched_priority = LowestPriority;
    (void)pthread_setschedparam( hThread, policy, &param );
}

Vx653Timer::~Vx653Timer(void) {
#ifdef OM_USE_SYSTEM_TIMER
	if (timerId) 
	{
		Rhp_uint64_t rv = timer_delete(timerId);
		if (rv) {
		  OM_NOTIFY_ERROR("timer_delete","Vx653Timer::~Vx653Timer");
		}
	}
#endif
	pthread_cancel(hThread);
}

void Vx653Timer::evaluateSleepTime(struct timespec& tms, 
	                               const OxfTimeUnit sleepTime ) {

	tms.tv_sec = sleepTime/OMOS_MSec;
	tms.tv_nsec = (sleepTime % OMOS_MSec)* OMOS_MicroSec;
}

void Vx653Timer::setAffinity(const OMAffinity_t aff) {
	Vx653Thread::setThreadAffinity(hThread, aff);
}

void Vx653Timer::bridge(Vx653Timer *me) {
  pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
  me->waitThread();
}

void Vx653Timer::waitThread(void) {
	struct timespec tms;
	evaluateSleepTime(tms, m_Time);
	do {
		nanosleep(&tms, NULL);
		(*cbkfunc)(param);
		if (OMThread::isEndOfProcess())
		{
			break;
		}
	} while ( 1 ); 
}


void Vx653OSEventFlag::signal(void) {
	if (sem_post(&hEventFlag) == ERROR) {
  		OM_NOTIFY_ERROR("sem_post","Vx653OSEventFlag::signal")
	}
}

void Vx653OSEventFlag::reset(void) {
	if (sem_trywait(&hEventFlag) == ERROR) {
  		OM_NOTIFY_ERROR("semTake","Vx653OSEventFlag::reset")
	}
}

void Vx653OSEventFlag::wait(const Rhp_int32_t tminms /*= -1 */) {
	if ( -1 == tminms ) {
		int rc = ERROR;
		while (rc == ERROR) {       
			rc = sem_wait(&hEventFlag);
#ifdef OM_SEMAPHORE_CAN_BE_INTERRUPTED
			if((rc == ERROR) && (errno == EINTR)) {
				continue;
			}
			else
#endif // OM_SEMAPHORE_CAN_BE_INTERRUPTED
				break;
		}
	} 
	else {
		struct timespec tms;
		if ( 0 != sem_trywait(&hEventFlag)) {
		// POSIX semaphores do not have timeouts.
		// To implement timeouts we loop on a try without wait
		// then sleep 50 ms until either semaphore is open ( ret value is 0)
		// or time is up.
			OxfTimeUnit sleepTimeInterval = 50;
			Rhp_int32_t count = tminms / static_cast<Rhp_int32_t>(sleepTimeInterval);
			Rhp_int32_t i = 0;
			Vx653Timer::evaluateSleepTime(tms, sleepTimeInterval);
			for (i = 1; i < count ; i++) {
				nanosleep(&tms, NULL); 
				if ( sem_trywait(&hEventFlag) == OK) {
					break;
				}
			}
		}
	}
}

Vx653OSEventFlag::Vx653OSEventFlag(void) {
   if (sem_init (&hEventFlag, 0, 0) == ERROR)  
   {
		OM_NOTIFY_ERROR("semBCreate","Vx653OSEventFlag::Vx653OSEventFlag")
	}
}

Vx653Mutex::Vx653Mutex(void) 
{ 
	pthread_mutexattr_t attr;
	pthread_mutexattr_init( &attr );
	pthread_mutex_init( &hMutex, &attr );
} 

Vx653Mutex::~Vx653Mutex(void) {
  pthread_mutex_destroy(&hMutex);
}


void Vx653Mutex::lock(void) {
	pthread_mutex_lock(&hMutex);
}

void Vx653Mutex::unlock(void) {

	pthread_mutex_unlock(&hMutex);
}  

void Vx653Thread::preExecFunc(void* me) {
	if (((Vx653Thread *)me)->m_SuspEventFlag.getOsHandle()) {
		((Vx653Thread *)me)->m_SuspEventFlag.wait();
	}
	((Vx653Thread *)me)->m_ExecFunc(((Vx653Thread *)me)->m_ExecParam);
}

Vx653Thread::Vx653Thread( void tfunc(void *), void *param, Rhp_const_char_pt /*name*/, const Rhp_int32_t stackSize ) : 
						isWrapperThread(0),
						endOSThreadInDtor(TRUE),
						m_ExecFunc(tfunc),
						m_ExecParam(param) 
{
	// Create SUSPENDED thread !!!!!!
	pthread_attr_t tthread_attr;
	pthread_attr_init( &tthread_attr );
	pthread_attr_setstacksize( &tthread_attr, stackSize);
	pthread_attr_setdetachstate( &tthread_attr, PTHREAD_CREATE_DETACHED );
	pthread_attr_setinheritsched( &tthread_attr, PTHREAD_INHERIT_SCHED );

	Rhp_int32_t retVal = pthread_create ( &hThread,       // Handle
                                          &tthread_attr,  // default attributes
                                          reinterpret_cast<FormalThrCreateFunc>(preExecFunc),
                                          static_cast<void*>(this) );

    if (retVal) {
		OM_NOTIFY_ERROR("pthread_create", "Vx653Thread::Vx653Thread");
	} 
}


Vx653Thread::Vx653Thread(void* osThreadId) : 
			isWrapperThread(1),
			endOSThreadInDtor(TRUE) 
{
    // Create Wrapper Thread !!!!
    hThread = reinterpret_cast<OMOSHandle>(osThreadId);
}



Vx653Thread::~Vx653Thread(void) {
	if (!isWrapperThread) {
		if (endOSThreadInDtor) 
		{
			OMBoolean onMyThread = exeOnMyThread();
			if (!((OMThread::isEndOfProcess()) && onMyThread)) {
				OMOSThread::OMOSThreadEndCallBack theOSThreadEndClb = NULL;
				OMOSHandle* threadHandle = NULL;
				// get a callback function to end the os thread
				getThreadEndClbk( &theOSThreadEndClb, reinterpret_cast<void**>(&threadHandle),onMyThread );
				if (theOSThreadEndClb != NULL) {
					// ending the os thread
					(*theOSThreadEndClb)(*threadHandle);
				}
			}
		}
	}
}

static const Rhp_uint32_t endThreadResult = 0U;

void Vx653Thread::endMyThread(OMOSHandle hThread) {
	pthread_exit( reinterpret_cast<void*>(const_cast<Rhp_uint32_t*>(&endThreadResult)) );
}

void Vx653Thread::endOtherThread(OMOSHandle hThread) {
	pthread_cancel(hThread);
}

void Vx653Thread::getThreadEndClbk( Vx653Thread::OMOSThreadEndCallBack* clb_p, 
                                 void** arg1_p, 
                                 const OMBoolean onExecuteThread) {
    if (onExecuteThread) {
        // asking for a callback to end my own thread
        *clb_p = &endMyThread;
        *arg1_p = reinterpret_cast<void*>(&hThread);
    } else {
        // asking for a callback to end my thread by someone else
        *clb_p = &endOtherThread;
        // my thread handle
        *arg1_p = reinterpret_cast<void*>(&hThread);
    }
}

void Vx653Thread::setPriority(const Rhp_int32_t aPriority)
{  
  Rhp_int32_t policy;
  Rhp_int32_t rv;
  
  sched_param param;
 rv = pthread_getschedparam(hThread, &policy, &param );
  if (rv == 0) {
      param.sched_priority = aPriority;
      if (rv = pthread_setschedparam(hThread, policy, &param )) {
       OM_NOTIFY_ERROR("pthread_setschedparam", "LinuxThread::setPriority");
      }
  }
}

void Vx653Thread::start(void) 
{
    if (m_SuspEventFlag.getOsHandle()) 
	{
		m_SuspEventFlag.signal();
    } 
}

void Vx653Thread::setAffinity(const OMAffinity_t aff) {
	Vx653Thread::setThreadAffinity(hThread, aff);
}

#if ((_WRS_VXWORKS_MAJOR >5) && (_WRS_VXWORKS_MINOR >5))

OMAffinity_t Vx653Thread::getAffinity(void) const {
	cpuset_t aff;
	OMAffinity_t coreId = (OMAffinity_t)0;
	CPUSET_ZERO(aff);
	taskCpuAffinityGet(hThread,&aff);

	unsigned int cpu;
	OMAffinity_t mask = (OMAffinity_t)1;
	for (cpu = 0 ; cpu < sizeof(OMAffinity_t) * 8; cpu++,mask = mask<<1) 
	{
		if (CPUSET_ISSET(cpu, aff))
		{
			coreId = coreId | mask;
		}
	}
	return coreId; 
}

void Vx653Thread::setThreadAffinity(Rhp_int32_t m_hThread, const OMAffinity_t coreId) {
	cpuset_t aff;
	CPUSET_ZERO(aff);
	OMAffinity_t locId = coreId;
	unsigned int cpu;
	for (cpu = 0 ; cpu < sizeof(OMAffinity_t) * 8; cpu++) 
	{
		if (locId%2)
		{
			CPUSET_SET(aff, cpu);
		}
		locId = locId>>1;
	}
	taskCpuAffinitySet(m_hThread, aff);
	taskActivate(m_hThread);
}

void Vx653Thread::setPwrState(const OMPowerMode_t val)
{
#ifdef _WRS_KERNEL
	if (cpuPwrTaskPStateSet(hThread,val) == ERROR) {
		OM_NOTIFY_ERROR("cpuPwrTaskPStateSet","Vx653Thread::setPwrState")
	}
#endif
}

OMPowerMode_t Vx653Thread::getPwrState(void) const
{
#ifdef _WRS_KERNEL
	return cpuPwrTaskPStateGet(hThread);
#else
	return OMPwrModeNone;
#endif
}
#else
OMAffinity_t Vx653Thread::getAffinity(void) const {
	return 0U; 
}

void Vx653Thread::setThreadAffinity(Rhp_int32_t /*m_hThread*/, const OMAffinity_t /*aff*/) {
}

void Vx653Thread::setPwrState(const OMPowerMode_t val)
{
}
OMPowerMode_t Vx653Thread::getPwrState(void) const
{
	return OMPwrModeNone;
}
#endif // _WRS_VXWORKS_MAJOR


// Reset the thread OS handle
// Should be used with care and only for wrapper threads
// Argument void * newHandle : 
// The new OS handle
void Vx653Thread::resetWrapperThreadOsHandle(void* newHandle) {
	if (isWrapperThread) {
		hThread = static_cast<Rhp_int32_t>(reinterpret_cast<Rhp_uint64_t>(newHandle));
	}
}

#ifdef _OMINSTRUMENT

extern "C" {
///// TODO
    // this function is called from host while IDE running
    Rhp_int32_t OMTaskIsSuspended(Rhp_int32_t handle) {
        Rhp_int32_t status = 0;
        return status;
    }
} // end extern C

void Vx653Socket::Close(void) {
    if (theSock != 0) { 
        (void)shutdown(theSock,2);
        (void)close(theSock);
        theSock = 0;
    }
}


Vx653Socket::Vx653Socket(void) {
    theSock = 0;
}

Vx653Socket::~Vx653Socket(void) {
    Close();
}

#ifndef SOCKET_ERROR
#define SOCKET_ERROR -1
#endif // SOCKET_ERROR

Rhp_int32_t Vx653Socket::Create( const Rhp_const_char_pt SocketAddress /*= NULL*/,
                              const Rhp_uint32_t aSocketPort /*= 0*/) {
    static struct sockaddr_in	addr;
    Rhp_int32_t   proto;
    Rhp_char_t    hostName[128];
    Rhp_const_char_pt   address = SocketAddress;
    Rhp_int32_t   port = aSocketPort;

    if ( port == 0U ) {
    port = 6423U;
    }

    addr.sin_family = AF_INET;
    proto = IPPROTO_TCP;

    (void)gethostname(hostName, sizeof(hostName)-1);
    if (NULL != address) {
        if (!strcmp(hostName,address)) {
            address = NULL;
        } else {
            (void)strcpy(hostName,address);
            addr.sin_addr.s_addr = inet_addr(hostName);
            if (((Rhp_uint32_t)ERROR) == addr.sin_addr.s_addr) {
                addr.sin_addr.s_addr = hostGetByName(hostName);
            }
            if (((Rhp_uint32_t)ERROR) == addr.sin_addr.s_addr) {
                fprintf(stderr,"Could not get the address of host '%s'\n", hostName);
                return 0;
            }
        }
    }

    if (NULL == address) {
        addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    }

#ifdef unix
	endprotoent();
#endif // unix

    addr.sin_port = htons((u_short)port);

    if ((theSock = socket(AF_INET, SOCK_STREAM, proto)) == -1) {
        fprintf(stderr,"Could not create socket\n");
        theSock = 0;
        return 0;
    }

    Rhp_int32_t rvStat;
    while (( rvStat = connect(theSock, (struct sockaddr*) &addr, sizeof(addr))) == SOCKET_ERROR &&
        (errno == EINTR) ) {
    };

    if (SOCKET_ERROR == rvStat) {
        fprintf( stderr,
                "Could not connect to server at %s port %d\n Error No. : %d\n",
               hostName,
               static_cast<Rhp_int32_t>(aSocketPort),
               errno );
		return 0;
    }

	return 1;
}

Rhp_int32_t Vx653Socket::Send( const Rhp_const_char_pt lpBuf,
                            const Rhp_int32_t nBufLen ) {
    Rhp_int32_t bytes_writ = 0;
    Rhp_int32_t n;

    while (bytes_writ < nBufLen) {
        n = send(theSock, reinterpret_cast<Rhp_const_char_pt>(lpBuf + bytes_writ), nBufLen - bytes_writ,0);
        if (SOCKET_ERROR == n) {
            if (errno == EINTR) {
                continue;
            } else {
                return -1;
            }
        }
        bytes_writ += n;
    }
    return bytes_writ;
}

Rhp_int32_t Vx653Socket::Receive( Rhp_char_pt lpBuf, 
                               const Rhp_int32_t nBufLen ) {
    Rhp_int32_t bytes_read = 0;
    Rhp_int32_t n;

    while (bytes_read < nBufLen) {
    n = recv(theSock, lpBuf + bytes_read, nBufLen - bytes_read,0);
    if (SOCKET_ERROR == n) {
        if (errno == EINTR) {
            continue;
        } else {
            return -1;
        }
    } else {
        if ( 0 == n ) {
            // connection closed
            return -1;
            }
        }
        bytes_read += n;
    }
    return bytes_read;
}

Rhp_char_pt Vx653ConnectionPort::m_Buf = NULL;
Rhp_int32_t Vx653ConnectionPort::m_BufSize = 0;


Vx653ConnectionPort::Vx653ConnectionPort(void) {
    m_Connected = 0;
    m_dispatchfunc = NULL;
    m_ConnectionThread = NULL;
    m_ShouldWaitForAck = 1;
    m_NumberOfMessagesBetweenAck = 0;
    m_AckEventFlag.reset();
}

Vx653ConnectionPort::~Vx653ConnectionPort(void) {
     m_Socket.Close();
    if (m_ConnectionThread) {
        void* threadOsHandle = OMOSFactory::instance()->getCurrentThreadHandle();
        if (threadOsHandle != m_ConnectionThread->getOsHandle()) {
            // do not delete myself
            delete m_ConnectionThread;
        }
        m_ConnectionThread = NULL;
    }
    // I assume that we will have only one connection port
    // so I can free the data for m_Buf but if it is not the case
    // it does not matter ( the readFromSockLoop will allocate it )
    if (m_Buf) {
        OMDELETE(m_Buf, m_BufSize);
    }
    m_BufSize = 0;
}


void Vx653ConnectionPort::readFromSockLoop(Vx653ConnectionPort *me) {
    Rhp_char_t lenStr[MAX_LEN_STR+1];
    Rhp_int32_t len;
    Rhp_int32_t rv;
    for (;;) {
        rv = me->m_Socket.Receive(lenStr,MAX_LEN_STR);
        if (rv == -1) {
            OM_NOTIFY_TO_ERROR("Terminating application\n");
            me->m_Socket.Close();
            return;
        }
        lenStr[MAX_LEN_STR] = '\0';
        Rhp_int32_t oldBufSize = m_BufSize;
        if (sscanf(lenStr,"%d",&len) == 1) {
            if (len > m_BufSize ) {
                m_BufSize = 1000+len;
                if (m_Buf) {
                    OMDELETE(m_Buf, oldBufSize);
                }
                m_Buf = OMNEW(Rhp_char_t, m_BufSize);
            }
        if (len == -2) { 
            // Acknowledge message
            me->m_AckEventFlag.signal();
            continue;
        }
        m_Buf[len] = '\0';
        rv = me->m_Socket.Receive(m_Buf,len);
        if (rv == -1) {
            OM_NOTIFY_TO_ERROR("Terminating application\n");
            me->m_Socket.Close();
            return;
        }

        // len is not used by OMSData but we need to change
        // the interface so we will use the length of the data
        // and not assume that the string is null terminated

        // if socket thread is doing some work that may send
        // messages we do not want to Block the Send by waiting for
        // acknowldegment since the thread cannot handle the acknowledgment
        // ( since the thread is self locked)
        me->m_ShouldWaitForAck = 0;
        me->m_AckEventFlag.signal();
        me->m_dispatchfunc(OMSData::string2OMSData(m_Buf));
        me->m_ShouldWaitForAck = 1;
        }
    }
}

Rhp_int32_t Vx653ConnectionPort::Connect( const Rhp_const_char_pt SocketAddress /*= NULL*/,
                                       const Rhp_uint32_t aSocketPort /*= 0*/) {
    if (NULL == m_dispatchfunc) {
        fprintf(stderr,"Vx653ConnectionPort::SetDispatcher should be called before NTConnectionPort::Connect()\n");
        return 0;
    }
    if ( 0  == m_Connected ) {
        m_Connected = m_Socket.Create(SocketAddress,aSocketPort);
    }
    if (0 == m_Connected) {
        return 0;
    }

    // Connection established
    // invoking thread to receive messages from the socket

    m_ConnectionThread =
    new Vx653Thread((void (*)(void *))readFromSockLoop,(void *)this,"tRhpSock");

	if (OXF::frmThreadAffinities.AnimMessageReader != 0U)
	{	// multi core support
		m_ConnectionThread->setAffinity(OXF::frmThreadAffinities.AnimMessageReader);
	}

    m_ConnectionThread->start();
    return m_Connected;
}


Rhp_int32_t Vx653ConnectionPort::Send(OMSData* aMessage) {
    Rhp_int32_t rv = 0;
    m_SendMutex.lock();
    if (m_Connected) {
        Rhp_char_t lenStr[MAX_LEN_STR+1];
        (void)sprintf(lenStr,"%d", aMessage->getLength());

        rv = m_Socket.Send(lenStr, MAX_LEN_STR);
        if (rv > 0) {
            rv = m_Socket.Send(aMessage->getRawData(),
                               aMessage->getLength() );
        }
        if (m_ShouldWaitForAck) {
            const Rhp_int32_t maxNumOfMessagesBetweenAck = 127; // MUST match the number in rhapsody
            if (maxNumOfMessagesBetweenAck > 0) {
                m_NumberOfMessagesBetweenAck++;
                if (m_NumberOfMessagesBetweenAck >= maxNumOfMessagesBetweenAck) {
                    m_NumberOfMessagesBetweenAck = 0;
                    m_AckEventFlag.wait();
                    m_AckEventFlag.reset();
                }
            }
        }

    }
    m_SendMutex.unlock();
    return rv;
}
#endif 

////////////////////////////////////////////////////////////
///                        Vx653Semaphore                      
////////////////////////////////////////////////////////////

Vx653Semaphore::Vx653Semaphore( const Rhp_uint64_t semFlags, 
                          const Rhp_uint64_t initialCount ) : m_ok(FALSE) {
    m_ok = (sem_init(&m_sem, static_cast<Rhp_int32_t>(semFlags), initialCount) == 0);
}

///////
Vx653Semaphore::~Vx653Semaphore(void) {
	sem_destroy(&m_sem);
}

////////
void Vx653Semaphore::signal(void) {
	sem_post(&m_sem);
}

OMBoolean Vx653Semaphore::wait( const Rhp_int64_t aTimeout ) {
	OMBoolean status = false;
	if (m_ok) {
		int rc = -1;
		if (aTimeout == 0) {
			rc = sem_trywait(&m_sem);
		} 
		else {
			while (rc == -1) {
				rc = sem_wait(&m_sem);
#ifdef OM_SEMAPHORE_CAN_BE_INTERRUPTED
				if((rc == -1) && (errno == EINTR)) {
					continue;
				}
				else
#endif // OM_SEMAPHORE_CAN_BE_INTERRUPTED
				{
					break;
				}
			}
		}
		status = (rc == 0);
	}
	return status;
}


//
// $Log: Vx653posix.cpp $
// Revision 1.1  2007/05/28 07:43:50  ilvler
//
