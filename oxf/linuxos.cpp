//#if ((!defined lint) && (!defined OM_NO_RCS_ID))
//static const char *rcsid = "$Id: linuxos.cpp 1.34 2007/03/11 08:42:54 ilgiga Exp $";
//#endif
//
//	file name   :	$Source: R:/StmOO/Master/cg/LangCpp/oxf/rcs/linuxos.cpp $
//	file version:	$Revision: 1.34 $
//
//	purpose:	 	
//
//	author(s):		
//	date started:	
//	date changed:	$Date: 2007/03/11 08:42:54 $
//	last change by:	$Author: ilgiga $
//
//	Licensed Materials - Property of IBM
//	(c) Copyright IBM Corporation 1997, 2016. All Rights Reserved.
//
//  Note to U.S. Government Users Restricted Rights:  
//  Use, duplication or disclosure restricted by GSA ADP Schedule 
//  Contract with IBM Corp.
//

// Rhapsody Framework includes
#include "linuxos.h" 
#include "omthread.h"
#include "timer.h"

#ifdef _OMINSTRUMENT
#include <aom/AnimServices.h>
#include <omcom/omsdata.h>
#include "oxf.h"

#ifdef OM_STL
#include <cstdio>
#else
#include <stdio.h>
#endif

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <sys/utsname.h> 
#endif // _OMINSTRUMENT

#ifdef OM_USE_SYSTEM_TIMER
#include <signal.h>
#include <time.h>
#endif

#include <unistd.h>
#include <bits/local_lim.h>

#ifndef OM_NO_MC_SUPPORT
#include <sched.h>
#include <sys/syscall.h>
#endif // OM_NO_MC_SUPPORT

const Rhp_int32_t OMOSThread::DefaultStackSize = DEFAULT_STACK;
const Rhp_int32_t OMOSThread::DefaultMessageQueueSize = 100;
const Rhp_int32_t OMOSThread::DefaultThreadPriority = 0;

const Rhp_int64_t OMOS_MSec = 1000;
const Rhp_int64_t OMOS_MicroSec = 1000000;
const Rhp_int64_t OMOS_NSec = 1000000000;
const Rhp_int64_t OMOS_DefaultTick = 100;

#ifdef _OMINSTRUMENT
static void notifySyscallFault( const Rhp_uint64_t errCode, 
                                const Rhp_char_t* syscallName,
                                const Rhp_char_t* funcName ) {
	if (0 != errCode ) {
		if ( !(OMThread::isEndOfProcess()) ) {
			Rhp_char_t buf[255];
			sprintf(buf, "Call to %s inside routine %s failed, Error=0x%lx\n",
				syscallName,funcName,errCode);
			OM_NOTIFY_TO_ERROR(buf);
		}
	}
}
#define LINUX_NOTIFY_ERROR(err,callName,func) notifySyscallFault(err,callName,func);
#else
#define LINUX_NOTIFY_ERROR(err,callName,func)
#endif // _OMINSTRUMENT 

bool LinuxOSFactory::destroyed = false;

#ifdef OM_USE_SYSTEM_TIMER

static void LinuxTimer_handler (union sigval si)
{
	LinuxTimer* me = reinterpret_cast<LinuxTimer*>(si.sival_ptr);
	if (OMThread::isEndOfProcess())
	{
		if (me->timerId != 0)
		{
			timer_delete(me->timerId);
			me->timerId = 0;
		}
	}
	else
	{
		(*me->cbkfunc)(me->param);
	}
}

static void LinuxTimer_init(struct timespec* tms, timeUnit mTime, LinuxTimer* me)
{
	Rhp_uint64_t rv;
	if (mTime > 0) { // real timer
		struct itimerspec t;
		struct sigevent se;

		se.sigev_notify = SIGEV_THREAD;
		se.sigev_value.sival_ptr = me;
		se.sigev_notify_function = LinuxTimer_handler;
		se.sigev_notify_attributes = NULL;

		rv = timer_create(CLOCK_REALTIME,&se,&me->timerId);
		LINUX_NOTIFY_ERROR(rv,"timer_create","LinuxTimer::waitThread");
		// since m_Time in ms    
		t.it_interval = *tms;
		t.it_value = *tms;
		rv = timer_settime(me->timerId,0,&t,NULL);
		LINUX_NOTIFY_ERROR(rv,"timer_settime","LinuxTimer::waitThread");
	}
}
#endif /* OM_USE_SYSTEM_TIMER */


OMOSFactory* OMOSFactory::instance() {
	static LinuxOSFactory theFactory;
	if ( LinuxOSFactory::isDestroyed() ) {
	  (void) new(&theFactory) LinuxOSFactory;
	}	  
	return &theFactory;
}

LinuxOSFactory::~LinuxOSFactory() {
	destroyed = true;
}

void OMOS::initEpilog() {
	// nothing to do
}                   

void OMOS::endProlog() {
    // nothing to do
}

void OMOS::endApplication(const Rhp_int32_t errorCode) {
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
    exit(errorCode);
}


void* LinuxOSFactory::getCurrentThreadHandle() const {
    return reinterpret_cast<void*>(pthread_self());
}

void LinuxOSFactory::delayCurrentThread(const OxfTimeUnit ms) const {
	struct timespec tms;

	if (ms > 0) {
		LinuxTimer::evaluateSleepTime(tms, ms);
		nanosleep(&tms, NULL);
	} else {
		sched_yield(); // give up current time slice
	}

}

// LinuxOSMessageQueue
void* LinuxOSMessageQueue::get() {
	void *m;
	m_QueueMutex.lock();
	if (!isEmpty()) {
		m = m_theQueue.get();
	} else {
		m = NULL;
		m_QueueEventFlag.reset();
	}
	m_QueueMutex.unlock();
	return m;
}


void LinuxOSMessageQueue::pend() {
  if ( isEmpty() ) {
		m_QueueEventFlag.wait();
  }
}

OMBoolean LinuxOSMessageQueue::put( void* aMessage, 
                                    const OMBoolean fromISR ) {
  m_QueueMutex.lock();
  Rhp_int32_t wasEmpty = isEmpty();

  OMBoolean res = m_theQueue.put(aMessage);
  
  if (wasEmpty) {
  	m_QueueEventFlag.signal();
  }
  m_QueueMutex.unlock();

  return res;
}

void LinuxOSMessageQueue::getMessageList(OMListType& aList) {
	// Copy to it all the messages I have
	m_theQueue.getInverseQueue(aList);
}
/// LinuxOSEventFlag
LinuxOSEventFlag::LinuxOSEventFlag() {
   sem_init (&hEventFlag, 0, 0);  
}  

void LinuxOSEventFlag::signal() {
	(void)sem_trywait(&hEventFlag);
	(void)sem_post(&hEventFlag);
}

void LinuxOSEventFlag::reset() {
	(void)sem_trywait(&hEventFlag);
}

void LinuxOSEventFlag::wait(const Rhp_int32_t tminms /*= -1 */) {
	if ( -1 == tminms ) {
		int rc = -1;
		while (rc == -1) {       
			rc = sem_wait(&hEventFlag);
#ifdef OM_SEMAPHORE_CAN_BE_INTERRUPTED
			if((rc == -1) && (errno == EINTR)) {
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
#ifdef OM_NO_SEM_TIMEDWAIT_SUPPORT
		// POSIX semaphores do not have timeouts.
		// To implement timeouts we loop on a try without wait
		// then sleep 50 ms until either semaphore is open ( ret value is 0)
		// or time is up.
			timeUnit sleepTimeInterval = 50;
			Rhp_int32_t count = tminms / static_cast<Rhp_int32_t>(sleepTimeInterval);
			Rhp_int32_t i = 0;
			LinuxTimer::evaluateSleepTime(tms, sleepTimeInterval);
			for (i = 1; i < count ; i++) {
				nanosleep(&tms, NULL); 
				if ( 0 == sem_trywait(&hEventFlag) ) {
					break;
				}
			}
#else
			LinuxTimer::evaluateSleepTime(tms, tminms);
			int rv = sem_timedwait(&hEventFlag, &tms);
			LINUX_NOTIFY_ERROR(static_cast<Rhp_uint64_t>(rv), "sem_timedwait", "LinuxOSEventFlag::wait");
#endif // OM_NO_SEM_TIMEDWAIT_SUPPORT
		}
	}
}

LinuxMutex::LinuxMutex() {
	pthread_mutexattr_t attr;
	pthread_mutexattr_init( &attr );
#ifndef OM_NO_RECURSIVE_MUTEX_SUPPORT
	pthread_mutexattr_settype (&attr, PTHREAD_MUTEX_RECURSIVE_NP);
#endif // OM_NO_RECURSIVE_MUTEX_SUPPORT
	count = 0;
	owner = NULL;
	pthread_mutex_init( &hMutex, &attr ); 
}  

LinuxMutex::~LinuxMutex() {
  pthread_mutex_destroy(&hMutex);
  owner = NULL;
}  

// Allow recursive locking of the mutex by one thread

void LinuxMutex::lock() {
#ifdef OM_NO_RECURSIVE_MUTEX_SUPPORT
	void* current = OMOSFactory::instance()->getCurrentThreadHandle();

	if ( owner == current) {
		count++; 
	} else {
		pthread_mutex_lock(&hMutex);
		owner = current;
	}
#else // OM_NO_RECURSIVE_MUTEX_SUPPORT
    pthread_mutex_lock(&hMutex);
#endif
}

void LinuxMutex::unlock() {
#ifdef OM_NO_RECURSIVE_MUTEX_SUPPORT
	void* current = OMOSFactory::instance()->getCurrentThreadHandle();
	if (owner == current) {
		if (count == 0) {
			owner = NULL;
			pthread_mutex_unlock(&hMutex); 
		} else {
			count--;
		}
	}
#else 
    pthread_mutex_unlock(&hMutex);
#endif // OM_NO_RECURSIVE_MUTEX_SUPPORT
}

// the formal pthread_create parameter
extern "C" {
    typedef void*(*FormalThrCreateFunc)(void*);
}

// TickTimer
LinuxTimer::LinuxTimer(const timeUnit ptime, void pcbkfunc(void*), void *pparam):
     cbkfunc(pcbkfunc),
     param(pparam),
	 timerId(0),
     m_Time(ptime),
	 SetAffinityInCtor(FALSE)
{

    pthread_attr_t tthread_attr;
    pthread_attr_init( &tthread_attr );
    pthread_attr_setstacksize( &tthread_attr, PTHREAD_STACK_MIN);
    pthread_attr_setdetachstate( &tthread_attr, PTHREAD_CREATE_DETACHED );
    pthread_attr_setinheritsched( &tthread_attr, PTHREAD_INHERIT_SCHED );

    pthread_create ( &hThread, //Handle
                     &tthread_attr, // default attributes
                     reinterpret_cast<FormalThrCreateFunc>(bridge),
                     this );

 // Create a thread that runs bridge, passing this as argument 
}

// IdleTimer (Simulated Time) 
LinuxTimer::LinuxTimer(void pcbkfunc(void*), void *pparam):
     cbkfunc(pcbkfunc),
     param(pparam),
	 timerId(0),
     m_Time(5),
	 SetAffinityInCtor(FALSE)
{ 
     	
	// Just create context-switch until the system enters idle mode
    pthread_attr_t tthread_attr;

    pthread_attr_init( &tthread_attr );
    pthread_attr_setstacksize( &tthread_attr, PTHREAD_STACK_MIN);
    pthread_attr_setdetachstate( &tthread_attr, PTHREAD_CREATE_DETACHED );
    pthread_attr_setinheritsched( &tthread_attr, PTHREAD_INHERIT_SCHED );

    pthread_create ( &hThread, // Handle 
                     &tthread_attr, // default attributes
                     reinterpret_cast<FormalThrCreateFunc>(bridge),
                     this );

 // Create a thread that runs bridge, passing this as argument
 // have to set the lowest priority for the simulated timer, in order to
 // make sure it get activate when all other threads are Idle

    Rhp_int32_t policy;
    sched_param param;

    pthread_getschedparam(hThread, &policy, &param );
    param.sched_priority = LowestPriority;
    (void)pthread_setschedparam( hThread, policy, &param );
}

LinuxTimer::~LinuxTimer() {
#ifdef OM_USE_SYSTEM_TIMER
	if (timerId) 
	{
		Rhp_uint64_t rv = timer_delete(timerId);
		LINUX_NOTIFY_ERROR(rv,"timer_delete","LinuxTimer::~LinuxTimer");
	}
#endif
	pthread_cancel(hThread);
}

void LinuxTimer::setAffinity(const OMAffinity_t aff)
{
#ifndef OM_NO_MC_SUPPORT
	SetAffinityInCtor = TRUE;
	cpu_set_t osAffinity;
	LinuxThread::evaluateAffinity(aff, osAffinity);
	m_aff = osAffinity;
#endif
}

void* LinuxTimer::bridge(void* me) {
    LinuxTimer* theTimer = reinterpret_cast<LinuxTimer*>(me);
#ifndef OM_NO_MC_SUPPORT
	if (theTimer->SetAffinityInCtor == TRUE)
	{
		pid_t tid;
		tid = syscall(SYS_gettid);
		(void)sched_setaffinity(tid ,sizeof(theTimer->m_aff),&theTimer->m_aff);
	}
	theTimer->SetAffinityInCtor = TRUE;
#endif
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
    theTimer->waitThread();
    return NULL;
}

void LinuxTimer::evaluateSleepTime(struct timespec& tms, 
	                               const timeUnit sleepTime ) {

	tms.tv_sec = sleepTime/OMOS_MSec;
	tms.tv_nsec = (sleepTime % OMOS_MSec)* OMOS_MicroSec;

#ifdef OM_TIMER_CORRECTION_NEEDED
	static Rhp_int64_t clk_tck = 0; // clock tick of system
	static Rhp_int64_t tv_corr = 0; // will be 1.5 ticks in nsec

	if (clk_tck <= 0) {
		// get the real value once at runtime
		clk_tck = sysconf(_SC_CLK_TCK);
		if (clk_tck <= 0) {
			// call failed
			clk_tck = OMOS_DefaultTick; // use default
		}
		tv_corr = 1500000000 / clk_tck;
	}

	// compensate nanosleep adding additional tick
	tms.tv_nsec = tms.tv_nsec - tv_corr;

	if (tms.tv_nsec < 0) { // inhibit negative
		if (tms.tv_sec > 0) {
			tms.tv_sec--;
			tms.tv_nsec += OMOS_NSec;
		} else {  // still one tick
			tms.tv_nsec = 0;
		}
	}
#endif
}

void LinuxTimer::waitThread() {
	struct timespec tms;
	evaluateSleepTime(tms, m_Time);
#ifdef OM_USE_SYSTEM_TIMER
	LinuxTimer_init(&tms, m_Time, this);
#else
	do {
		nanosleep(&tms, NULL);
		(*cbkfunc)(param);
		if (OMThread::isEndOfProcess())
		{
			break;
		}
	} while ( 1 ); 
#endif
}

#ifdef	OM_POSIX_THREAD_SUSPEND_RESUME_SUPPORT
void LinuxThread::User1handler(Rhp_int32_t signumber) {
    sigpause((Rhp_int32_t) SIGUSR2);
}

void LinuxThread::User2handler(Rhp_int32_t signumber) {
    // DO NOTHING
}
#endif

void LinuxThread::preExecFunc(void* me) {
	LinuxThread* thr = (reinterpret_cast<LinuxThread*>(me));
    if (thr->m_SuspEventFlag != NULL) {
        thr->m_SuspEventFlag->wait();
        LinuxOSEventFlag* tmp = thr->m_SuspEventFlag;
        thr->m_SuspEventFlag = NULL;
        delete tmp;
    }
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
#ifndef OM_NO_MC_SUPPORT
	if (thr->SetAffinityInCtor == TRUE)
	{
		pid_t tid;
		tid = syscall(SYS_gettid);
		(void)sched_setaffinity(tid ,sizeof(thr->m_aff),&thr->m_aff);
	}
	else
	{
		thr->SetAffinityInCtor = TRUE;
	}		
#endif
	(reinterpret_cast<LinuxThread*>(me))->m_ExecFunc((reinterpret_cast<LinuxThread*>(me))->m_ExecParam);
}


void LinuxThread::suspend() {
#ifdef	OM_POSIX_THREAD_SUSPEND_RESUME_SUPPORT
    pthread_kill(hThread,(Rhp_int32_t)SIGUSR1);
#endif
}

void LinuxThread::resume() {
#ifdef	OM_POSIX_THREAD_SUSPEND_RESUME_SUPPORT
    pthread_kill(hThread,(Rhp_int32_t)SIGUSR2);
#endif
}

LinuxThread::LinuxThread( void tfunc(void*), 
                          void* param, 
                          const Rhp_int32_t stackSize ) : SetAffinityInCtor(FALSE), endOSThreadInDtor(TRUE) {
    isWrapperThread = 0;
    m_SuspEventFlag = new LinuxOSEventFlag();
    m_SuspEventFlag->reset();
    // Create SUSPENDED thread !!!!!!
    m_ExecFunc = tfunc;
    m_ExecParam = param;

#ifdef OM_POSIX_THREAD_SUSPEND_RESUME_SUPPORT
    signal(SIGUSR1,LinuxThread::User1handler);
    signal(SIGUSR2,LinuxThread::User2handler);  
#endif
    pthread_attr_t tthread_attr;

	pthread_attr_init( &tthread_attr );
	pthread_attr_setstacksize( &tthread_attr, stackSize);
	pthread_attr_setdetachstate( &tthread_attr, PTHREAD_CREATE_DETACHED );
	pthread_attr_setinheritsched( &tthread_attr, PTHREAD_INHERIT_SCHED );
	
    Rhp_int32_t retVal = pthread_create ( &hThread,       // Handle
                                          &tthread_attr,  // default attributes
                                          reinterpret_cast<FormalThrCreateFunc>(preExecFunc),
                                          static_cast<void*>(this) );

    LINUX_NOTIFY_ERROR(static_cast<Rhp_uint64_t>(retVal), "pthread_create", "LinuxThread::LinuxThread");
}

LinuxThread::LinuxThread(void* osThreadId) : SetAffinityInCtor(FALSE), endOSThreadInDtor(TRUE) {
    m_SuspEventFlag = NULL;
    // Create Wrapper Thread !!!!
    hThread = reinterpret_cast<pthread_t>(osThreadId);
    isWrapperThread = 1;
}

LinuxThread::~LinuxThread()	{
	if (!isWrapperThread) {
		if (m_SuspEventFlag) {
			delete m_SuspEventFlag;
		}
		if (endOSThreadInDtor) {
			OMOSThread::OMOSThreadEndCallBack theOSThreadEndClb = NULL;
			OMOSHandle* threadHandle = NULL;
			OMBoolean onMyThread = exeOnMyThread();
			// get a callback function to end the os thread
			getThreadEndClbk( &theOSThreadEndClb, reinterpret_cast<void**>(&threadHandle),onMyThread );
			if (theOSThreadEndClb != NULL) {
				// ending the os thread
				(*theOSThreadEndClb)(*threadHandle);
			}
		}
	}
}

void LinuxThread::setPriority(const Rhp_int32_t aPriority) { 
  Rhp_int32_t policy;
  Rhp_int32_t rv;
  
  sched_param param;
  rv = pthread_getschedparam(hThread, &policy, &param );
  if (rv == 0) {
      param.sched_priority = aPriority;
      rv = pthread_setschedparam(hThread, policy, &param );
      LINUX_NOTIFY_ERROR(static_cast<Rhp_uint64_t>(rv), "pthread_setschedparam", "LinuxThread::setPriority");
    }
}

static const Rhp_uint32_t endThreadResult = 0U;

void LinuxThread::endMyThread(OMOSHandle hThread) {
	pthread_exit( reinterpret_cast<void*>(const_cast<Rhp_uint32_t*>(&endThreadResult)) );
}

void LinuxThread::endOtherThread(OMOSHandle hThread) {
	pthread_cancel(hThread);
}

void LinuxThread::getThreadEndClbk( LinuxThread::OMOSThreadEndCallBack* clb_p, 
	                                  void** arg1_p, 
	                                  OMBoolean onExecuteThread ) {
	if (onExecuteThread) {
		// asking for a callback to end my own thread
		*clb_p = (LinuxThread::OMOSThreadEndCallBack)&endMyThread;
		*arg1_p = reinterpret_cast<void*>(&hThread);
	} else {
		// asking for a callback to end my thread by someone else
		*clb_p = &endOtherThread;
		// my thread handle
		*arg1_p = reinterpret_cast<void*>(&hThread);
	}
}

void LinuxThread::start() {
	if (m_SuspEventFlag) {
		m_SuspEventFlag->signal();
	} else {
		resume();
	}
}

OMAffinity_t LinuxThread::getAffinity(void) const
{
	OMAffinity_t coreId = (OMAffinity_t)0;
#ifndef OM_NO_MC_SUPPORT
	cpu_set_t aff;
	CPU_ZERO(&aff);
	pid_t tid;
	tid = syscall(SYS_gettid);
	int retVal = sched_getaffinity(tid,sizeof(coreId),&aff);
	if (retVal == -1)
	{
		LINUX_NOTIFY_ERROR(static_cast<Rhp_uint64_t>(retVal), "sched_getaffinity", "LinuxThread::getAffinity");
	}
	else
	{
		int cpu;
		OMAffinity_t mask = (OMAffinity_t)1;
		for (cpu = 0 ; cpu < sizeof(OMAffinity_t) * 8; cpu++,mask= mask<<1) 
		{
			if (CPU_ISSET(cpu, &aff))
			{
				coreId = coreId | mask;
			}
		}
	}
#endif
	return coreId;
}

void LinuxThread::setAffinity(const OMAffinity_t aff)
{
#ifndef OM_NO_MC_SUPPORT
	cpu_set_t osAffinity;
	evaluateAffinity(aff, osAffinity);
	if (SetAffinityInCtor == FALSE) {
		m_aff = osAffinity;
		SetAffinityInCtor = TRUE;
	}
	else {
		pid_t tid;
		tid = syscall(SYS_gettid);
		int retVal = sched_setaffinity(tid,sizeof(osAffinity),&osAffinity);
		if (retVal == -1)
			LINUX_NOTIFY_ERROR(static_cast<Rhp_uint64_t>(retVal), "sched_setaffinity", "LinuxThread::setAffinity");
	}
#endif
}

#ifndef OM_NO_MC_SUPPORT
void LinuxThread::evaluateAffinity(const OMAffinity_t coreId, cpu_set_t &aff)
{
	CPU_ZERO(&aff);
	OMAffinity_t locId = coreId;
	int cpu;
	for (cpu = 0 ; cpu < sizeof(OMAffinity_t) * 8; cpu++) 
	{
		if (locId%2)
		{
			CPU_SET(cpu, &aff);
		}
		locId = locId>>1;
	}
}
#endif


#ifdef _OMINSTRUMENT

LinuxSocket::LinuxSocket() {
  theSock = 0;
}

LinuxSocket::~LinuxSocket() {
  if (theSock != 0) {
    (void)close(theSock);
  }
}

#ifndef SOCKET_ERROR
#define SOCKET_ERROR -1
#endif // SOCKET_ERROR

Rhp_int32_t LinuxSocket::Create( const Rhp_const_char_pt SocketAddress /*= NULL */,
                                 const Rhp_uint32_t aSocketPort /* = 0*/) {
  static struct sockaddr_in	addr;
  struct protoent* protocol;
  Rhp_int32_t	proto;
  struct hostent* host = NULL;
  Rhp_const_char_pt proto_name = (Rhp_const_char_pt)"tcp";
  Rhp_char_t hostName[128];
  Rhp_const_char_pt address = SocketAddress;
  Rhp_uint32_t port = aSocketPort;
  
  if ( port == 0u ) {
    port = 6423;
  }

  addr.sin_family = AF_INET;
  if ((protocol = getprotobyname(proto_name)) == (struct protoent*) 0) {
    fprintf(stderr,"Could not get the AF_INET protocol\n");
    return 0;
  }
  proto = protocol->p_proto;

    // use uname in order to get the local host name (nodename )
 struct utsname buf;  
 uname(&buf);
 strcpy (hostName, buf.nodename); 
 if (NULL != address && (strlen(address) !=0)) {
	if (!strcmp(hostName, address)) {
		address = NULL;
	}	else {
      (void)strcpy(hostName, address);
      if ((host = gethostbyname(hostName)) == (struct hostent *) 0) {
        fprintf(stderr,"Could not get the address of host '%s'\n",
	        hostName);
        return 0;
      }
		}
  }
  
  
#ifdef unix
  endprotoent();
#endif // unix
  
  addr.sin_port = htons((u_short)port);
  
  if (NULL == address || strlen(address) ==0) {
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
  } else {
    addr.sin_addr.s_addr = *(reinterpret_cast<Rhp_uint32_t*>(host->h_addr) );
  }
  
  
  if ((theSock = socket(AF_INET, SOCK_STREAM, proto)) == -1) {
    fprintf(stderr,"Could not create socket\n");
    theSock = 0;
    return 0;
  }
  
  Rhp_int32_t rvStat;
  while ((rvStat = connect(theSock, (struct sockaddr *) &addr, sizeof(addr))) == SOCKET_ERROR &&
	 (errno == EINTR))
    ;

  if (SOCKET_ERROR == rvStat) {
    fprintf( stderr,
	           "Could not connect to server at %s port %d\n Error No. : %d\n",
	           hostName,
	           static_cast<Rhp_int32_t>(port),
	           errno);
    return 0;
  }
  return 1;
}

Rhp_int32_t LinuxSocket::Send( const Rhp_const_char_pt lpBuf, 
                               const Rhp_int32_t nBufLen ) {
  Rhp_int32_t bytes_writ = 0;
  Rhp_int32_t n;
  
  while (bytes_writ < nBufLen) {
    n = send(theSock, lpBuf + bytes_writ, nBufLen - bytes_writ,0);
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

Rhp_int32_t LinuxSocket::Receive( Rhp_char_pt lpBuf, 
                                  const Rhp_int32_t nBufLen ) {
  Rhp_int32_t bytes_read = 0;
  Rhp_int32_t n;
  
  while (bytes_read < nBufLen) {
    n = recv(theSock, lpBuf + bytes_read, nBufLen - bytes_read,0);
    if (SOCKET_ERROR == n) {
      if (errno == EINTR) {
				continue;
      }
      else {
				return -1;
      }
    } else {
		if ( 0 == n ) { //connection closed
			return -1;
		}
	}
    bytes_read += n;
  }
  return bytes_read;
}


Rhp_char_pt LinuxConnectionPort::m_Buf = NULL;
Rhp_int32_t LinuxConnectionPort::m_BufSize = 0;

LinuxConnectionPort::LinuxConnectionPort() {
  m_Connected = 0;
  m_dispatchfunc = NULL;
  m_ConnectionThread = NULL;
  m_ShouldWaitForAck = 1;
  m_NumberOfMessagesBetweenAck = 0;
  m_AckEventFlag.reset();
}

LinuxConnectionPort::~LinuxConnectionPort() {
  if (m_ConnectionThread) {
    delete m_ConnectionThread;
    m_ConnectionThread = NULL;
  }
  // I assume that we will have only one connection port
  // so I can free the data for m_Buf but if it is not the case
  // it does not matter ( the readFromSockLoop will allocate it )
  if (m_Buf == NULL) {
    OMDELETE(m_Buf, m_BufSize);
  }
  m_BufSize = 0;
}

void LinuxConnectionPort::readFromSockLoop(LinuxConnectionPort* me) {
  Rhp_char_t lenStr[MAX_LEN_STR+1];
  Rhp_int32_t len;
  Rhp_int32_t rv;
  for (;;) {			
    rv = me->m_Socket.Receive(lenStr,MAX_LEN_STR);
    if (rv == -1) {
      OM_NOTIFY_TO_ERROR("Terminating application\n");
      exit(0);
    }
    lenStr[MAX_LEN_STR] = '\0';
		Rhp_int32_t oldBufSize = m_BufSize;
    if (sscanf(lenStr,"%d",&len) == 1) {
      if (len > m_BufSize ) {
				m_BufSize = 1000+len;
				if (m_Buf != NULL) {
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
				exit(0);
			}
		
      // len is not used by OMSData, but we need to change
      // the interface so we will use the length of the data
      // and not assume that the string is null terminated

      // if the socket thread is doing some work that may send
      // messages, we do not want to Block the Send by waiting for
      // acknowldegment since the thread cannot handle the acknowledgment
      // (since the thread is self locked)
      me->m_ShouldWaitForAck = 0;
      me->m_AckEventFlag.signal();
      me->m_dispatchfunc(OMSData::string2OMSData(m_Buf));
      me->m_ShouldWaitForAck = 1;
    }
  }
}

Rhp_int32_t LinuxConnectionPort::Connect( const Rhp_const_char_pt SocketAddress /*= NULL*/,
			                                    Rhp_uint32_t nSocketPort /*= 0*/ ) {
	if (NULL == m_dispatchfunc) 
	{
		fprintf(stderr,"LinuxConnectionPort::SetDispatcher should be called before NTConnectionPort::Connect()\n");
		return 0;
	}
	if ( 0  == m_Connected )
	{
		m_Connected = m_Socket.Create(SocketAddress,nSocketPort);
	}
	if (0 != m_Connected)
	{
		
		// Connection established
		// invoking thread to recieve messages from the socket

		m_ConnectionThread = new LinuxThread((void (*)(void*))readFromSockLoop,(void*)this);

		if (OXF::frmThreadAffinities.AnimMessageReader != 0U)
		{	// multi core support
			m_ConnectionThread->setAffinity(OXF::frmThreadAffinities.AnimMessageReader);
		}

		m_ConnectionThread->start();
	}

	return m_Connected;
}

Rhp_int32_t LinuxConnectionPort::Send(OMSData* aMessage) {
  Rhp_int32_t rv = 0;
  m_SendMutex.lock();
  if (m_Connected) {
    Rhp_char_t lenStr[MAX_LEN_STR+1];
    (void)sprintf(lenStr, "%d", aMessage->getLength());

    rv = m_Socket.Send(lenStr, MAX_LEN_STR);
    if (rv > 0) {
      rv = m_Socket.Send(aMessage->getRawData(), aMessage->getLength());
    }
    if (m_ShouldWaitForAck) {
      const Rhp_int32_t maxNumOfMessagesBetweenAck = 127; //MUST match the number in rhapsody
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

////////////////////////////////////////////////
/// LinuxSemaphore class
////////////////////////////////////////////////
LinuxSemaphore::LinuxSemaphore( const Rhp_uint64_t semFlags, 
                                const Rhp_uint64_t initialCount ) : m_ok(FALSE) {
    m_ok = (sem_init(&m_sem, static_cast<Rhp_int32_t>(semFlags), initialCount) == 0);
}

//////////
LinuxSemaphore::~LinuxSemaphore() {
	sem_destroy(&m_sem);
}

/////////
void LinuxSemaphore::signal() {
	sem_post(&m_sem);
}

////////
OMBoolean LinuxSemaphore::wait( const Rhp_int64_t timeout ) {
	OMBoolean status = false;
	if (m_ok) 
	{
		int rc = -1;
		if (timeout == 0) 
		{
			rc = sem_trywait(&m_sem);
		} 
#ifndef OM_NO_SEM_TIMEDWAIT_SUPPORT
		else
		if (timeout > 0)
		{ // timeout
			static Rhp_int64_t clk_tck = sysconf(_SC_CLK_TCK);
			struct timespec timer; 
			if (clk_tck <= 0) {
				// call failed
				clk_tck = OMOS_DefaultTick; // use default
			}
			timer.tv_sec  = timeout / clk_tck; 
			timer.tv_nsec = (timeout % clk_tck) * (OMOS_NSec / clk_tck); 
			struct timespec now;
			if (clock_gettime(CLOCK_REALTIME, &now) != -1) 
			{
				timer.tv_nsec += now.tv_nsec;
				timer.tv_sec  += now.tv_sec;
				if (timer.tv_nsec >= OMOS_NSec) 
				{
					timer.tv_nsec = timer.tv_nsec - OMOS_NSec;
					timer.tv_sec += 1; 
				}
				rc = sem_timedwait(&m_sem, &timer);
			}
		} 
#endif // OM_NO_SEM_TIMEDWAIT_SUPPORT
		else 
		{  // wait forever 
			while (rc == -1) 
			{
				rc = sem_wait(&m_sem);
#ifdef OM_SEMAPHORE_CAN_BE_INTERRUPTED
				if((rc == -1) && (errno == EINTR)) 
				{
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
// $Log: linuxos.cpp $
// Revision 1.34  2007/03/11 08:42:54  ilgiga
// Change copyright comment
// Revision 1.33  2007/03/01 14:32:34  ilgiga
// Telelogic instead of i-Logix
// Revision 1.32  2006/09/25 15:05:22  vova
// Include line moved out of #ifdef.
// Revision 1.31  2006/09/07 09:09:49  vova
// OM_NO_RECURSIVE_MUTEX_SUPPORT processing added (Multi Linux specific)
// Revision 1.30  2006/03/19 13:59:30  vova
// Structure initialization added
// Revision 1.29  2005/11/21 11:11:15  vova
// PTHREAD_CREATE_DETACHED parameter is used instead of PTHREAD_CREATE_JOINABLE
// Revision 1.28  2005/11/20 15:52:44  vova
// pthread_mutexattr_settype is used instead of inner private field.
// Revision 1.27  2005/11/07 12:11:26  yshekel
// Upgrade_from_60_to_61
// Revision 1.26  2005/08/23 14:53:36  amos
// bugfix 85444 to main branch
// Revision 1.25.1.2  2005/08/22 10:08:19  amos
// provide a compilation switch (OM_NO_RCS_ID) to remove the definitions of the rcsid and hrcsid variables
// this is done to prevent compiler warnings for defined but not used global variables
// Revision 1.25.1.1  2005/08/17 14:01:07  amos
// Duplicate revision
// Revision 1.24  2005/08/03 12:39:29  amos
// Fix AnimServices support for end application to support the various RTOS needs
// - Add a boolean argument to notifyEndApplication() that controls the closing of the connection to Rhapsody
// - Add new public static operation cleanupOnEndApplication() that destroys the anim dispatcher
// - Modify the adapters usage of these operations besed on the 6.0 version of the adapters
// Revision 1.23  2005/04/21 10:08:35  amos
// Revision 1.22.1.2  2005/04/05 08:55:46  amos
// Revision 1.22  2005/03/28 15:21:28  vova
// Thread suspend/resume is ifdefed 
// Revision 1.21.1.1  2005/03/28 08:01:11  vova
// Revision 1.21  2005/03/22 14:17:11  vova
// Thread suspend/resume function implemented like in C adapter
// Revision 1.21  2005/03/22 13:59:34  vova
// Thread suspend/resume function implementation added (C-like implementation)
// Revision 1.20  2005/03/22 08:45:39  vova
// pthread_setcanceltype call added
// Revision 1.19  2005/03/21 14:14:20  vova
// pthread_kill has been replaced with pthread_cancel
// Revision 1.18  2005/03/21 10:45:37  vova
// 81235:SIGHUP signal usage was eliminated
// Revision 1.17.1.2  2005/03/17 13:00:44  amos
// Use the AnimServices by the adapters
// Revision 1.17.1.1  2005/02/16 14:20:01  amos
// Duplicate revision
// Revision 1.17  2005/02/16 14:20:01  vova
// Crash eliminated because of too "early" OMOSFactory instance destruction while application exiting.
// Revision 1.16  2005/01/03 08:08:19  vova
// Scheduling policy Inheritance added into the task creating.
// Revision 1.16  2005/01/02 15:33:08  vova
// Scheduling policy Inheritance added into the task creating.
// Revision 1.16  2005/01/02 15:17:25  vova
// SCHED_OTHER policy is replaced with SCHED_FIFO in setPriority function.
// It is needed for static objects.
// Revision 1.15  2004/10/21 14:55:07  vova
// 75497: timer inaccuracy fixed.
// Revision 1.16  2004/10/19 10:28:29  vova
// Revision 1.15  2004/10/14 16:16:25  vova
// 75497:Timer inaccuracy corrected
// Revision 1.14  2004/05/11 07:56:57  vova
// Linux warnings: order of initializers changed
// Revision 1.13  2004/01/08 08:10:29  eldad
// Missed me prefix
// Revision 1.12  2003/12/30 13:28:23  eldad
// Fixed b#68182 - the m_SuspEventFlag is deleted after the wait() and 
// not after the signal()
// Revision 1.11  2002/07/15 12:27:43  avrahams
// Back to main
// Revision 1.10.1.2  2002/07/04 10:17:48  avrahams
// Cleanup std namespace usage
// Revision 1.10  2002/01/15 10:33:49  vova
// 52678: SIGUSR1 signal handler has been added for the timer thread
// Revision 1.9  2002/01/08 16:57:11  vova
// 50808 : static  function has been added and defined as the SIGUSR1 signal handler in LinuxThread::LinuxThread constructor
// Revision 1.8  2001/08/12 14:22:07  vova
// 47788: Linux: quit animation does not work !
// Revision 1.7  2001/08/05 09:37:08  amos
// back to main branch
// Revision 1.6.1.3  2001/08/05 09:37:08  amos
// modify the memory manager to support passing of the object size in deletion
// Revision 1.6.1.2  2001/08/02 11:34:23  amos
// Revision 1.6.1.1  2001/05/16 12:32:34  amos
// Duplicate revision
// Revision 1.5  2001/01/30 09:09:54  avrahams
// Add OM prefix to globals
// Convert OMOS methods to static methods
// Revision 1.4  2001/01/25 13:59:15  avrahams
// OXF globals encapsulation
// Revision 1.3  2000/11/13 13:00:59  amos
// add implementation of OSOXFEndProlog()
// Revision 1.2  2000/11/08 15:57:59  amos
// back to main branch
// Revision 1.1.1.2  2000/11/08 15:57:59  amos
// modify the OS layer message queue put() method to return a success status
// Revision 1.1.1.1  2000/10/04 10:53:51  amos
// Duplicate revision
//


























