//
//	file name   :	$Source: R:/StmOO/Master/cg/LangCpp/oxf/rcs/sol2os.cpp $
//	file version:	$Revision: 1.47 $
//
//	purpose:	 	
//
//	author(s):		
//	date started:	
//	date changed:	$Date: 2007/05/17 09:17:13 $
//	last change by:	$Author: ilvler $
//
//	Licensed Materials - Property of IBM
//	(c) Copyright IBM Corporation 1997, 2016. All Rights Reserved.
//	
//	Note to U.S. Government Users Restricted Rights:  
//	Use, duplication or disclosure restricted by GSA ADP Schedule 
//	Contract with IBM Corp.
//

#include <oxf/sol2os.h> 
#include <oxf/omthread.h>
#include <oxf/timer.h>

#ifdef _OMINSTRUMENT
#include <aom/AnimServices.h>
#endif // _OMINSTRUMENT
#ifdef _OMINSTRUMENT
#include <omcom/omsdata.h>

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

#include <sys/systeminfo.h>
#include <unistd.h>

#endif 

const Rhp_int32_t OMOSThread::DefaultStackSize = 0;
const Rhp_int32_t OMOSThread::DefaultMessageQueueSize = 100;
const Rhp_int32_t OMOSThread::DefaultThreadPriority = THR_SUSPENDED;

static void notifySyscallFault(int errCode, const char* syscallName,const char* funcName)
{
	if (0 != errCode ) {
		if (!OMThread::isEndOfProcess()) {
			char buf[255];
			sprintf(buf,"Call to %s inside routine %s failed, Error=0x%x\n",
				syscallName,funcName,errCode);
			OM_NOTIFY_TO_ERROR(buf);
		}
	}
}
bool Sol2OSFactory::destroyed = false;

OMOSFactory* OMOSFactory::instance()
{
	static Sol2OSFactory theFactory; 
	if ( Sol2OSFactory::destroyed) 
	{
	  (void) new(&theFactory) Sol2OSFactory;
	   Sol2OSFactory::destroyed = false;
	}	  
	return &theFactory;
}

Sol2OSFactory::~Sol2OSFactory()
{
  destroyed = true;
}

void OMOS::initEpilog()
{
	// nothing to do
}                   

void OMOS::endProlog()
{
	// nothing to do
}

void OMOS::endApplication(const Rhp_int32_t errorCode)
{
#ifdef _OMINSTRUMENT
	AnimServices::notifyEndApplication(false);
#endif // _OMINSTRUMENT
	OMThread::setEndOfProcess(true);
	exit(errorCode);
}

void* Sol2OSFactory::getCurrentThreadHandle(void) const
{
	return (void *)thr_self();
}

void Sol2OSFactory::delayCurrentThread(const timeUnit ms) const
{
	struct timespec tms;
	tms.tv_sec = ms/1000;
	tms.tv_nsec = (ms % 1000) * 1000000;
	if (ms > 0)
	{
		nanosleep(&tms,NULL);
	}
	else
	{
		thr_yield();
	}
}


void *Sol2OSMessageQueue::get()
{
	void *m;
	m_QueueMutex.lock();
	if (!isEmpty()) {
		m = m_theQueue.get();
	} else {
		m =  NULL ;
		m_QueueEventFlag.reset();
	}
	m_QueueMutex.unlock();
	return m ;
}


void Sol2OSMessageQueue::pend()
{
	if (isEmpty())  {
		m_QueueEventFlag.wait();
	}
}

OMBoolean Sol2OSMessageQueue::put(void* m, OMBoolean fromISR)
{
	m_QueueMutex.lock();
	int wasEmpty = isEmpty();
	
	OMBoolean res = m_theQueue.put(m);
	
	if (wasEmpty) m_QueueEventFlag.signal();
	m_QueueMutex.unlock();
	
	return res;
}

void Sol2OSMessageQueue::getMessageList(OMListType & c) {
	// Copy to it all the messages I have
	m_theQueue.getInverseQueue(c);
}

Sol2OSEventFlag::Sol2OSEventFlag()
{
    int rv = sema_init(&hEventFlag,0,USYNC_THREAD,NULL);
	notifySyscallFault(rv,"sema_init","Sol2OSEventFlag ctor");
}  

Sol2OSEventFlag::~Sol2OSEventFlag()
{
    int rv = sema_destroy(&hEventFlag);
	notifySyscallFault(rv,"sema_destroy","Sol2OSEventFlag dtor");
}  


void Sol2OSEventFlag::signal()
{
	(void)sema_trywait(&hEventFlag);
	(void)sema_post(&hEventFlag);
}

void Sol2OSEventFlag::reset()
{
	(void)sema_trywait(&hEventFlag);
}

void Sol2OSEventFlag::wait(const Rhp_int32_t tminms /*= -1 */)
{
	if ( -1 == tminms ) {
		(void)sema_wait(&hEventFlag);
	}
	else {
		// Solaris semaphores do not have timeouts.
		// To implement timeouts we loop on a try without wait
		// then sleep 50 ms until either semaphore is open ( ret value is 0)
		// or time is up.
		struct timespec tms;
		if ( 0 != sema_trywait(&hEventFlag)) {
			timeUnit sleepTimeInterval = 50;
			int count = tminms / (int)sleepTimeInterval;
			int i = 0;
			for (i = 1; i < count ; i++) {
				tms.tv_sec = sleepTimeInterval/1000 ;
				tms.tv_nsec = (sleepTimeInterval % 1000)* 1000000;
				nanosleep(&tms, NULL);
				if (0 == sema_trywait(&hEventFlag))
					break;
			}
		}
	}
}

Sol2Mutex::Sol2Mutex()
{
	count = 0;
	owner = NULL;
	int rv = mutex_init(&hMutex,USYNC_THREAD, NULL);
	notifySyscallFault(rv,"mutex_init","Sol2Mutex ctor");
}  

Sol2Mutex::~Sol2Mutex()
{
	int rv = mutex_destroy(&hMutex);
	notifySyscallFault(rv,"mutex_destroy","Sol2Mutex dtor");
	owner = NULL;
}  

// Allow recursive locking of the mutex by one thread

void Sol2Mutex::lock()
{
	void * current = (void *)thr_self();
	if ( owner == current) { // only one thread will pass this
		count++; 
	}
	else {
		mutex_lock(&hMutex);
		owner = current;
	}
}

void Sol2Mutex::unlock()
{
	void * current = (void *)thr_self();
	if ( owner == current) { // only the owner can unlock the mutex
		if (count == 0) {
			owner = NULL;
			mutex_unlock(&hMutex);
		}
		else {
			count--;
		}
	}
}

// the formal thr_create parameter
extern "C" {
	typedef void*(*FormalThrCreateFunc)(void*);
}

// TickTimer
Sol2Timer::Sol2Timer(timeUnit ptime, void pcbkfunc(void *), void *pparam):
cbkfunc(pcbkfunc),
param(pparam),
m_Time(ptime),
timerId(0)
{
	int rv = thr_create(NULL, /* stack base */
		0, /* stack size */
		(FormalThrCreateFunc)bridge,
		this,
		0,
		&hThread);
	notifySyscallFault(rv,"thr_create","Sol2Timer ctor");
	// Create a thread that runs bridge, passing this as argument 
}

// IdleTimer (Simulated Time) 
Sol2Timer::Sol2Timer(void pcbkfunc(void *), void *pparam):
cbkfunc(pcbkfunc),
param(pparam),
m_Time(0), // Just create context-switch until the system enters idle mode
timerId(0)
{
	int rv;
	rv = thr_create(NULL, /* stack base */
		0, /* stack size */
		(FormalThrCreateFunc)bridge,
		this,
		0,
		&hThread);
	notifySyscallFault(rv,"thr_create","Sol2Timer ctor (sim)");
	// Create a thread that runs bridge, passing this as argument
	// have to set the lowest priority for the simulated timer, in order to
	// make sure it get activate when all other threads are Idle
	
	rv = thr_setprio( hThread,LowestPriority);
	notifySyscallFault(rv,"thr_setprio","Sol2Timer ctor (sim)");
}

Sol2Timer::~Sol2Timer()
{
	if (timerId) {
		int rv = timer_delete(timerId);
		notifySyscallFault(rv,"timer_delete","Sol2Timer dtor");
	}
	if (hThread) {
		void * executedOsHandle = OMOSFactory::instance()->getCurrentThreadHandle();
		// a handle to this' 'thread'
		void * myOsHandle = (void *)hThread;
		OMBoolean onMyThread = ((executedOsHandle == myOsHandle) ? TRUE : FALSE);
		
		if (onMyThread) {
			Sol2Thread::endMyThread(myOsHandle);
		}
		else {
			Sol2Thread::endOtherThread(myOsHandle);
		}
		hThread = 0;
	}
}

void* Sol2Timer::bridge(void* me)
{
	Sol2Timer* theTimer = (Sol2Timer*) me;
	theTimer->waitThread();
	return NULL;
}
extern "C" {

#ifdef OM_USE_SIGALRM_BASED_TIMER
static void VoidSigAlrmHandler(int)
{
	(void)signal(SIGALRM,VoidSigAlrmHandler); 
}

static void Sol2Timer_timerInit(struct timespec* tms, struct itimerspec* t, timeUnit mTime, timer_t timerId)
{
	int rv;
	if (mTime > 0) { // real timer
		rv = timer_create(CLOCK_REALTIME,NULL,&timerId);
		notifySyscallFault(rv,"timer_create","Sol2Timer::waitThread");
		// since m_Time in ms    
		t->it_interval = *tms;
		t->it_value = *tms;
		rv = timer_settime(timerId,TIMER_RELTIME,&t,NULL);
		notifySyscallFault(rv,"timer_create","Sol2Timer::waitThread");
		(void)signal(SIGALRM,VoidSigAlrmHandler); 
	}
} 
#endif /* OM_USE_SIGALRM_BASED_TIMER */

}
void Sol2Timer::waitThread()
{
	struct timespec tms;
	tms.tv_sec = m_Time/1000 ;
	tms.tv_nsec = (m_Time % 1000)* 1000000;
	
#ifdef OM_USE_SIGALRM_BASED_TIMER
	struct itimerspec t;
	Sol2Timer_timerInit(&tms, &t, m_Time, timerId);
#endif /* OM_USE_SIGALRM_BASED_TIMER */
	
	
	do {
		if (m_Time > 0) { //Real timer
#ifdef OM_USE_SIGALRM_BASED_TIMER
			sigpause(SIGALRM);
#else
			nanosleep(&tms, NULL);
#endif /* OM_USE_SIGALRM_BASED_TIMER */		
		}
		else
		{
			// simulated timer simply yields until the next time the system idles
			thr_yield();
		}
		(*cbkfunc)(param);		
	} while (1);
	
}

Sol2Thread::Sol2Thread(void tfunc(void *), void *param, const long stackSize) 
: endOSThreadInDtor(TRUE)
{
	isWrapperThread = 0;
	
	// Create SUSPENDED thread !!!!!!
	int rv;
	rv = thr_create(NULL, /* stack base */
		(int)stackSize, /* stack size */
		(FormalThrCreateFunc)tfunc,
		param,
		THR_SUSPENDED | THR_DETACHED,
		&hThread);
	notifySyscallFault(rv,"thr_create","Sol2Thread ctor");
}

Sol2Thread::Sol2Thread(void *osThreadId)
: endOSThreadInDtor(TRUE)
{
	// Create Wrapper Thread !!!!
	hThread = (thread_t)osThreadId;
	isWrapperThread = 1;
}

Sol2Thread::~Sol2Thread()	
{
	if (!isWrapperThread) {
		if (endOSThreadInDtor) {
			OMOSThread::OMOSThreadEndCallBack theOSThreadEndClb = NULL;
			OMOSHandle * threadHandle = NULL;
			OMBoolean onMyThread = exeOnMyThread();
			// get a callback function to end the os thread
			getThreadEndClbk(&theOSThreadEndClb,reinterpret_cast<void**>(&threadHandle),onMyThread);
			if (theOSThreadEndClb != NULL) {
				// ending the os thread
				(*theOSThreadEndClb)(*threadHandle);
			}
		}
	}
}

static const unsigned endThreadResult = 0;

void Sol2Thread::endMyThread(void * hThread)
{
	thr_exit( (void *)endThreadResult);
}

void Sol2Thread::endOtherThread(void * hThread)
{
	thr_kill((unsigned)hThread,SIGHUP );
}

void Sol2Thread::getThreadEndClbk(Sol2Thread::OMOSThreadEndCallBack * clb_p, void ** arg1_p, const OMBoolean onExecuteThread)
{
	if (onExecuteThread) {
		// asking for a callback to end my own thread
		*clb_p = &endMyThread;
		*arg1_p = (void *)&hThread;
	}
	else {
		// asking for a callback to end my thread by someone else
		*clb_p  = &endOtherThread;
		// my thread handle
		*arg1_p = (void *)&hThread;
	}
}


#ifdef _OMINSTRUMENT

Sol2Socket::Sol2Socket()
{
	theSock = 0;
}

Sol2Socket::~Sol2Socket()
{
	if (theSock != 0) {
		(void)close(theSock);
	}
	
}

#ifndef SOCKET_ERROR
#define SOCKET_ERROR -1
#endif // SOCKET_ERROR

Rhp_int32_t Sol2Socket::Create( const Rhp_const_char_pt SocketAddress /*= NULL */,
					   const Rhp_uint32_t nSocketPort /* = 0*/)
{
	static struct sockaddr_in	addr;
	struct protoent	*protocol;
	int			proto;
	struct hostent	*host = NULL;
	const char *proto_name = "tcp";
	char	hostName[128];
    Rhp_int32_t port = nSocketPort;
    Rhp_const_char_pt address = SocketAddress;
	
	if ( port == 0 ) {
		port = 6423;
	}
	
	addr.sin_family = AF_INET;
	if ((protocol = getprotobyname(proto_name)) == (struct protoent *) 0) {
		fprintf(stderr,"Could not get the AF_INET protocol\n");
		return 0;
	}
	proto = protocol->p_proto;
	
	(void)sysinfo(SI_HOSTNAME,hostName, sizeof(hostName)-1);
	if (NULL != address) {
		if (!strcmp(hostName,address)) {
			address = NULL;
		}
		else {
			(void)strcpy(hostName,address);
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
	
	if (NULL == address) {
		addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	}
	else {
		addr.sin_addr.s_addr = *((unsigned long *) host->h_addr);
	}
	
	
	if ((theSock = socket(AF_INET, SOCK_STREAM, proto)) == -1) {
		fprintf(stderr,"Could not create socket\n");
		theSock = 0;
		return 0;
	}
	
	int rvStat;
	while ((rvStat = connect(theSock, (struct sockaddr *) &addr, sizeof(addr))) == SOCKET_ERROR &&
		(errno == EINTR))
		;
	
	if (SOCKET_ERROR == rvStat) {
		fprintf(stderr,
			"Could not connect to server at %s port %d\n Error No. : %d\n",
			hostName,
			(int)port,
			errno);
		return 0;
	}
	
	return 1;
}

Rhp_int32_t Sol2Socket::Send(const Rhp_const_char_pt lpBuf, const Rhp_int32_t nBufLen)
{
	int bytes_writ = 0;
	int n;
	
	while (bytes_writ < nBufLen) {
		n = send(theSock, lpBuf + bytes_writ, nBufLen - bytes_writ,0);
		if (SOCKET_ERROR == n) {
			if (errno == EINTR) {
				continue;
			}
			else {
				return -1;
			}
		}
		bytes_writ += n;
	}
	
	return bytes_writ;
}

Rhp_int32_t Sol2Socket::Receive(Rhp_char_pt lpBuf, const Rhp_int32_t nBufLen)
{
	int bytes_read = 0;
	int n;
	
	while (bytes_read < nBufLen) {
		n = recv(theSock, lpBuf + bytes_read, nBufLen - bytes_read,0);
		if (SOCKET_ERROR == n) {
			if (errno == EINTR) {
				continue;
			}
			else {
				return -1;
			}
		}
		else {
			if ( 0 == n ) { //connection closed
				return -1;
			}
		}
		bytes_read += n;
	}
	return bytes_read;
}


char* Sol2ConnectionPort::m_Buf = NULL;
int Sol2ConnectionPort::m_BufSize = 0;

Sol2ConnectionPort::Sol2ConnectionPort() 
{
	m_Connected = 0;
	m_dispatchfunc = NULL;
	m_ConnectionThread = NULL;
	m_ShouldWaitForAck = 1;
	m_NumberOfMessagesBetweenAck = 0;
	m_AckEventFlag.reset();
	
}

Sol2ConnectionPort::~Sol2ConnectionPort()
{
	if (m_ConnectionThread) {
		delete m_ConnectionThread;
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

void Sol2ConnectionPort::readFromSockLoop(Sol2ConnectionPort *me)
{
	char lenStr[MAX_LEN_STR+1];
	int len;
	int rv;
	for (;;) {			
		rv = me->m_Socket.Receive(lenStr,MAX_LEN_STR);
		if (rv == -1) {
			OM_NOTIFY_TO_ERROR("Terminating application\n");
			exit(0);
		}
		lenStr[MAX_LEN_STR] = '\0';
		if (sscanf(lenStr,"%d",&len) == 1) {
			if (len > m_BufSize ) {
				int oldBufSize = m_BufSize;
				m_BufSize = 1000+len;
				if (m_Buf) {
					OMDELETE(m_Buf, oldBufSize);
				}
				m_Buf = OMNEW(char, m_BufSize);
			}
			if (len == -2) { // Acknoledge message
				me->m_AckEventFlag.signal();
				continue;
			}
			m_Buf[len] = '\0';
			rv = me->m_Socket.Receive(m_Buf,len);
			if (rv == -1) {
				OM_NOTIFY_TO_ERROR("Terminating application\n");
				exit(0);
			}
			// len is not used by OMSData but we need to change
			// the interface so we will use the length of the data
			// and not assume that the string is null terminated
			
			// if socket thread is doing some work that may send
			// messages we do not want to Block the Send by wainting for
			// acknoldegment since the thread cannot handle the acknoledgment
			// ( since the thraed is self locked)
			me->m_ShouldWaitForAck = 0;
			me->m_AckEventFlag.signal();
			me->m_dispatchfunc(OMSData::string2OMSData(m_Buf));
			me->m_ShouldWaitForAck = 1;
		}
	}
}


Rhp_int32_t Sol2ConnectionPort::Connect(const Rhp_const_char_pt SocketAddress /*= NULL*/,
								const Rhp_uint32_t nSocketPort /*= 0U*/)
{
	if (NULL == m_dispatchfunc) {
		fprintf(stderr,"Sol2ConnectionPort::SetDispatcher should be called before NTConnectionPort::Connect()\n");
		return 0;
	}
	if ( 0  == m_Connected ) {
		m_Connected = m_Socket.Create(SocketAddress,nSocketPort);
	}
	if (0 == m_Connected)
		return 0;
	
	// Connection established
	// invoking thread to recieve messages from the socket
	
	m_ConnectionThread =
		new Sol2Thread((void (*)(void *))readFromSockLoop,(void *)this);
	m_ConnectionThread->start();
	return m_Connected;
}

Rhp_int32_t Sol2ConnectionPort::Send(OMSData *m)
{
	int rv = 0;
	m_SendMutex.lock();
	if (m_Connected) {
		char lenStr[MAX_LEN_STR+1];
		(void)sprintf(lenStr,"%d",m->getLength());
		
		rv = m_Socket.Send(lenStr,MAX_LEN_STR);
		if (rv > 0) {
			rv = m_Socket.Send(m->getRawData(),m->getLength());
		}
		if (m_ShouldWaitForAck) {
			const int maxNumOfMessagesBetweenAck = 127; //MUST match the number in rhapsody
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
/// Sol2Semaphore class
////////////////////////////////////////////////
Sol2Semaphore::Sol2Semaphore(unsigned long semFlags, unsigned long initialCount) : m_ok(FALSE)
{
	m_ok = (sem_init(&m_sem, (int)semFlags, initialCount) == 0);
}

//////////
Sol2Semaphore::~Sol2Semaphore() 
{
	sem_destroy(&m_sem);
}

/////////
void Sol2Semaphore::signal()
{
	sem_post(&m_sem);
}

////////
OMBoolean Sol2Semaphore::wait(const Rhp_int64_t timeout)
{
	if (!m_ok) return FALSE;
	if (timeout == 0) return (sem_trywait(&m_sem) == 0);
	else return (sem_wait(&m_sem) == 0);
}



//
// $Log: sol2os.cpp $
// Revision 1.47  2007/05/17 09:17:13  ilvler
// 68417:warnings removed (ANSI C standard)
// Revision 1.46  2007/03/29 13:36:31  ilvler
// Warnings eliminated
// Revision 1.45  2007/03/11 08:43:02  ilgiga
// Change copyright comment
// Revision 1.44  2007/03/01 14:32:42  ilgiga
// Telelogic instead of i-Logix
// Revision 1.43  2007/02/28 15:56:03  ilgiga
// bug fix 97779
// Revision 1.42.1.3  2007/02/28 15:25:39  ilgiga
// bug fix 97779
// Revision 1.42.1.2  2007/02/28 13:56:33  ilgiga
// bug fix 97779
// Revision 1.42  2005/11/07 12:11:51  yshekel
// Upgrade_from_60_to_61
// Revision 1.41  2005/11/06 15:32:46  vova
// 80890: usleep replaced with nanosleep
// SIGALRM lsot handling problem fixed
// Revision 1.40  2005/08/23 14:53:41  amos
// bugfix 85444 to main branch
// Revision 1.39.1.2  2005/08/22 10:08:28  amos
// provide a compilation switch (OM_NO_RCS_ID) to remove the definitions of the rcsid and hrcsid variables
// this is done to prevent compiler warnings for defined but not used global variables
// Revision 1.39.1.1  2005/08/03 12:39:31  amos
// Duplicate revision
// Revision 1.38  2005/04/21 10:08:46  amos
// Revision 1.37.2.2  2005/03/17 13:00:46  amos
// Use the AnimServices by the adapters
// Revision 1.37  2005/01/27 15:40:42  vova
// 79959: crash while endApplication eliminated. It was caused by early destruction of OMOSFactory instance.
// Revision 1.35.1.1  2005/01/27 15:38:35  vova
// 79959: crash while endApplication eliminated. It was caused by early destruction of OMOSFactory instance.
// Revision 1.36  2005/01/25 12:24:47  vova
// Timeout problem on Solaris with newest patches fixed
// Revision 1.35  2002/07/15 12:27:49  avrahams
// Back to main
// Revision 1.34.1.2  2002/07/04 10:48:23  avrahams
// Cleanup std namespace usage
// Revision 1.34  2001/08/05 11:21:24  amos
// back to main branch
// Revision 1.33.1.3  2001/08/05 11:21:24  amos
// modify the memory manager to support passing of the object size in deletion
// Revision 1.33.1.2  2001/08/02 11:34:23  amos
// Revision 1.33.1.1  2001/07/23 14:11:44  amos
// Duplicate revision
// Revision 1.32  2001/05/16 12:32:36  amos
// merge OSE 4.3.1 support into r40
// Revision 1.31  2001/01/30 09:10:04  avrahams
// Add OM prefix to globals
// Convert OMOS methods to static methods
// Revision 1.30  2001/01/25 13:59:27  avrahams
// OXF globals encapsulation
// Revision 1.29  2001/01/07 12:26:35  amos
// resolve compilation warnings
// Revision 1.28  2001/01/04 10:30:53  ofer
// check return value of several system calls and notify error
// if retval is not zero ( when in shutdown mode does not inform messages)
// Revision 1.27  2000/11/13 12:17:07  amos
// merge 1.26.1.2 and 1.26.2.2
// Revision 1.26.2.2  2000/11/09 19:56:14  npadmawar
// Changes for OXFEnd
// Revision 1.26.2.1  2000/07/12 06:30:33  npadmawar
// Revision 1.26.1.2  2000/11/08 15:57:59  amos
// modify the OS layer message queue put() method to return a success status
// Revision 1.26.1.1  2000/07/12 06:30:33  amos
// Duplicate revision
// Revision 1.25  2000/01/25 16:37:33  amos
// back to main branch
// Revision 1.24.1.1  2000/01/18 15:51:40  amos
// Revision 1.24  1999/07/29 10:36:52  amos
// support generation of events from interupt handler (VxWorks)
// Revision 1.23  1999/03/21 14:02:36  ofer
// fix zobieBug on Solaris
//  Solaris semaphores do not have timeouts.
//  To implement timeouts we loop on a try without wait
//  then sleep 50 ms until either semaphore is open ( ret value is 0)
//  or time is up.
// Revision 1.22  1999/03/11 15:54:08  amos
// Revision 1.21.1.2  1999/03/11 10:39:29  amos
// add semaphores to the OXF
// Revision 1.21.1.1  1999/02/28 14:06:40  amos
// Duplicate revision
// Revision 1.20.1.1  1999/02/25 15:39:36  sasha
// Added missing function OSOXFInitEpilog()
// Revision 1.20  1999/02/09 16:05:03  amos
// change the getMessageList back to OMList
// add new operation on OMQueue - getInverseQueue()
// Revision 1.19  1999/02/03 12:38:33  amos
// back to main branch
// Revision 1.18.1.2  1999/02/03 12:14:19  amos
// convert OMOSMessageQueue from sizeless (OMList) to size controled (OMQueue)
// Revision 1.18.1.1  1999/02/01 16:19:44  amos
// Duplicate revision
// Revision 1.17.1.2  1999/02/01 11:24:35  amos
// chage time from long to unsigned long
// Revision 1.17  1999/01/26 08:50:06  amos
// back to main branch
// Revision 1.16.1.2  1999/01/24 14:52:50  amos
// merge
// Revision 1.16  1999/01/21 10:35:08  beery
// separate termination of threads when on my thread vs. on other thread
// Revision 1.15.1.7  1999/01/05 14:58:06  beery
// Revision 1.15.1.6  1999/01/04 14:14:52  beery
// Revision 1.15.1.5  1999/01/04 09:58:14  beery
// Revision 1.15.1.4  1999/01/04 09:16:17  beery
// Revision 1.15.1.3  1999/01/03 11:51:51  beery
// adjsut to new thread policy
// Revision 1.15.1.2  1999/01/03 11:25:13  beery
// new approach to kill threads
// Revision 1.15.1.1  1998/09/09 13:12:42  beery
// Revision 1.15.2.2  1999/01/19 09:05:25  amos
// user control over thread name, priority and stack size 
// via parameters in OMThread constructor
// Revision 1.15.2.1  1998/09/09 13:12:42  amos
// Duplicate revision
// Revision 1.14  1998/04/13 07:59:56  ofer
// keep "using namespace std;"
// only after include to <XXXstream>
// Revision 1.13  1998/04/13 07:40:26  ofer
// added "using namespace std;" after each include to stl files
// Revision 1.12  1998/04/12 12:16:41  ofer
// Change includes to Stl format ifdefed by OM_USE_STL
// Revision 1.11  1998/04/09 06:49:48  ofer
// change implementation of Sol2EventFlag
// No need for m_StateEventFlag anymore ( sol2os.cpp/h)
// 
// Revision 1.10  1998/04/08 06:02:17  ofer
// fix implementation of Sol2EventFlag::wait()
// Revision 1.9  1997/12/31 11:09:54  ofer
// declare usleep ( since it is not defined in unstd.h )
// Revision 1.8  1997/12/14 14:33:02  ofer
// added  delayCurrentThread(long ms) to abstract factory 
// and define and implement the method in the XXXOS.cpp/h
// Also added convienent macro OXFTDelay(timInMs)
// os.h ntos.cpp/h VxOs.cpp/h sol2os.cpp/h
// Revision 1.7  1997/10/30 13:01:16  ofer
// change implementation of Sol2EventFlag
// since we are using counting semaphore we have to check
// the "state" of the event flag
// sol2os.cpp/h
// Revision 1.6  1997/07/02 05:43:18  ofer
// fix Sol2Mutex::unlock() to set owner to null before releasing the
// mutex. 
// ( michael find the following bug:
//  1) task2 has higher pripority than task1
//  2) task1.lock() 
//  3) task2.lock()
//  4) task1.unlock() cause the mutex to be freed BUT since task2 has
//      higher priority it will grab the lock and set OWNER to current
//      then task1 continue and set OWNER to NULL
// )
// 
// Revision 1.5  1997/06/05 08:02:18  ofer
//  Added OXFEnd and OSEndApplication(platform specific)
// oxf.h os.h VxOs.cpp ntos.cpp sol2os.cpp
//  
// Revision 1.4  1997/06/03 05:05:06  ofer
// When recv read 0 bytes it means that the socket is closed
// so we return -1
// Revision 1.3  1997/04/30 11:05:40  ofer
// If local host name is equal to the current host name 
// we use the INADDR_LOOPBACK adderss
// sol2os.cpp ntos.cpp VxOS.cpp
// Revision 1.2  1997/04/15 10:29:24  ofer
// New interface for OMOSMessageQueue forced changes
// in the Sol2OSMessageQueue
// the interface now is cleaner !!!!
// sol2os.cpp/h
// Revision 1.1  1997/04/03 23:52:00  ofer
// Initial revision
//


