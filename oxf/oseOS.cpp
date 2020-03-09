//
//	file name   :	$Source: R:/StmOO/Master/cg/LangCpp/oxf/rcs/oseOS.cpp $
//	file version:	$Revision: 1.28 $
//
//	purpose:	 	
//
//	author(s):		
//	date started:	
//	date changed:	$Date: 2007/03/11 08:43:00 $
//	last change by:	$Author: ilgiga $
//
//	Licensed Materials - Property of IBM
//	(c) Copyright IBM Corporation 1996, 2016. All Rights Reserved.
//	
//	Note to U.S. Government Users Restricted Rights:  
//	Use, duplication or disclosure restricted by GSA ADP Schedule 
//	Contract with IBM Corp.
//


#include <oxf/oxf.h>
#include <oxf/oseOS.h>
#include <oxf/omthread.h>
#include <oxf/timer.h>
#include <oxf/oseev.sig>

#ifdef _OMINSTRUMENT
#include <aom/AnimServices.h>
#endif // _OMINSTRUMENT
#ifdef _OMINSTRUMENT
#include <omcom/omsdata.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

#ifdef OM_STL
#include <cstdlib>
#include <cstdio>
#else // !OM_STL
#include <stdlib.h>
#include <stdio.h>
#endif
#endif // _OMINSTRUMENT


// the signal union
union SIGNAL
{
   SIGSELECT       sigNo;
   struct RHAPSODY_SIGNAL event;
};

///////////////////////
// forward declarations
int lockThreadParameter(void);
int unlockThreadParameter(void);
int setThreadParameter(PROCESS pid, void *param);
void* getThreadParameter(PROCESS pid);

//////////////////////////////////////////////
// initialize static OS layer attributes
const Rhp_int32_t OMOSThread::DefaultStackSize = DEFAULT_STACK;
const Rhp_int32_t OMOSThread::DefaultMessageQueueSize = MQ_DEFAULT_SIZE;
const Rhp_int32_t OMOSThread::DefaultThreadPriority = PRIORITY_NORMAL;

OMOSFactory* OMOSFactory::instance()
{
	static oseOSFactory theFactory;
	return &theFactory;
}

void OMOS::initEpilog()
{
}

void OMOS::endProlog()
{
}

void OMOS::endApplication(const Rhp_int32_t errorCode)
{
#ifdef _OMINSTRUMENT
	AnimServices::notifyEndApplication(false);
#endif // _OMINSTRUMENT

	OMThread::setEndOfProcess(true);
	OMThread* currentThread = OMThread::cleanupAllThreads();

#ifdef _OMINSTRUMENT
	AnimServices::cleanupOnEndApplication();
#endif // _OMINSTRUMENT

	OMTimerManager::clearInstance();

#ifndef WIN32
	// it is no need in WIN32:
	// main thread is destroyed while exit() call
	OMThread* maint = OMMainThread::instance(false);
	if (maint) {
		maint->destroyThread();
	}
#endif // WIN32
	exit(0);
}

////////////////////////////////////////////
////////////////////////////////////////////
void* oseOSFactory::getCurrentThreadHandle(void) const
{	
	return (void*)current_process();
}

void oseOSFactory::delayCurrentThread(const timeUnit ms) const
{
	delay(ms);	
}

// ------------------------------------------------------------------------------------
// this method can now return NULL, so it should be checked in OMThread::execute()
// or an event with cancelled event id should be returned
//
void *oseOSMessageQueue::get(void)
{  
	void *m = NULL;

	if (dataReady == m_State) {
		m = pmessage ;
		pmessage = NULL;
		m_State = noData;
	}
	else {
		if (!isEmpty()) {	    
			static SIGSELECT any_sig[] = {0}; // could be global
			m = receive_w_tmo(0, any_sig);
			if(m == NIL) return NULL;
		}
		else {
			return NULL;
		}
	}  

	union SIGNAL* sig = (union SIGNAL*)m;
	m = NULL;

	// local event -> signal data is a pointer to a Rhapsody event
	if(sig->sigNo == RHAPSODY_SIGNAL_ID) { 
		m = sig->event.ev_data;
	}

	free_buf(&sig);  
	return m;
}



void oseOSMessageQueue::pend(void)
{	
	if (isEmpty()) {	  
		static SIGSELECT any_sig[] = {0};	  // could be global
		pmessage = receive(any_sig);
		m_State = dataReady;
	}
}

// -----------------------------------------------------------------------------------
// OMReactive::_gen() and OMThreadTimer::action(Timeout* timeout) call this method via
// OMThread::queueEvent(OMEvent* ev)
//
OMBoolean oseOSMessageQueue::put(void* m,const OMBoolean fromISR /*= FALSE*/)
{
	// allocate space for the Rhapsody event pointer and send it:	
	union SIGNAL *sig = alloc(sizeof(struct RHAPSODY_SIGNAL), RHAPSODY_SIGNAL_ID);
	sig->event.ev_data = m;
	send(&sig, ownerProcess);	// message queue has an owner process, MHo !!!	
	return TRUE;	// no return value from the OSE call
}

Rhp_int32_t oseOSMessageQueue::isEmpty(void) const
{
	if(noData == m_State) 
	{	
		struct OS_pcb *pcbbuf = get_pcb(ownerProcess);

		if(pcbbuf)
		{
			if (0 == pcbbuf->sigqueue)
			{
				free_buf((union SIGNAL**)&pcbbuf);
				return TRUE;			
			}

			free_buf((union SIGNAL**)&pcbbuf);
			return FALSE;
		}
		else		// pcbbuf could not be allocated -> return "empty" -> caller goes pending					
		{
			return TRUE;
		}
	}

	return FALSE;
}

void oseOSMessageQueue::getMessageList(OMListType & l) {
	// Make sure list is empty
	l.removeAll();

	// iterate over the signal queue
	struct OS_pcb* pcbbuf = get_pcb(ownerProcess);	// get the event queue address
	OSADDRESS sigAddr = pcbbuf->sigqueue;
	union SIGNAL* sig = NULL;
	while (!get_signal(ownerProcess, sigAddr, &sig, &sigAddr)) { // iterate over the event queue
		if (sig != NULL) {
			if((sig->sigNo == RHAPSODY_SIGNAL_ID) && (sig->event.ev_data)) 
				l.add(sig->event.ev_data);	// event found, add it to the list
			free_buf(&sig);	// free the signal copy
		}
		if (sigAddr == NULL) break;	// end of queue
	}
	free_buf((union SIGNAL**)&pcbbuf);	// free the OS_pcb
}

OMBoolean oseOSMessageQueue::isFull() const
{
	struct OS_pcb* pcbbuf = get_pcb(ownerProcess);	// get the event queue address
	if (pcbbuf == NULL) return FALSE;
	if (pcbbuf->max_sigsize < sizeof(struct RHAPSODY_SIGNAL)) return TRUE;
	return FALSE;
}

// void oseTimer::bridge(oseTimer *me)
OS_PROCESS(bridge) // changed to public to compile, MHo
{		
	// pointer to thread object (given as parameter for other operating systems) must be obtained
	lockThreadParameter();
	oseTimer *me = (oseTimer*)getThreadParameter(current_process()); 
	unlockThreadParameter();
	me->waitThread();
}

// TickTimer
oseTimer::oseTimer(timeUnit ptime, void pcbkfunc(void *), void *pparam):
     m_Time(ptime),
     cbkfunc(pcbkfunc),
     param(pparam)
{
	// Create a thread that runs bridge, passing this as argument 
    // ticks = cvrtTmInMStoTicks(m_Time);

	// ---------------------------------------------------------------------------------
	// Notice: "callers block" and "user number" parameters control the protection of 
	// memory of the processes (among other things) - these features of OSE can not
	// be used, if Rhapsody does not provide some support for it. One possibility could be
	// to get them from "somewhere", but it would require extra work. Now the process being
	// created inherts both the block number (7th parameter) and the user number (last 
	// parameter) from the caller (the creator of the oseTimer-object)
	//
	hThread = create_process(OS_PRI_PROC, "timer", bridge, SMALL_STACK, PRIORITY_HIGH, 0 /* timeslice */, 
							 0 /* callers block */, NULL /* no redirection */, 0 /* vector */, 
							 0 /* inherit user number */);
	lockThreadParameter();
	setThreadParameter(hThread, this);
	unlockThreadParameter();

	start(hThread);
}

// IdleTimer (Simulated Time) 
oseTimer::oseTimer(void pcbkfunc(void *), void *pparam):
     m_Time(0), // Just create context-switch until the system enters idle mode
     cbkfunc(pcbkfunc),
     param(pparam)
{
	// ---------------------------------------------------------------------------------
	// Notice: "callers block" and "user number" parameters control the protection of 
	// memory of the processes (among other things) - these features of OSE can not
	// be used, if Rhapsody does not provide some support for it. One possibility could be
	// to get them from "somewhere", but it would require extra work. Now the process being
	// created inherts both the block number (7th parameter) and the user number (last 
	// parameter) from the caller (the creator of the oseTimer-object)
	//

  	// Create a thread that runs bridge, passing this as argument     
	hThread = create_process(OS_PRI_PROC, "timer", bridge, SMALL_STACK, PRIORITY_LOW, 0 /* timeslice */, 
							 0 /* callers block */, NULL /* no redirection */, 0 /* vector */, 
							 0 /* inherit user number */);
	lockThreadParameter();
	setThreadParameter(hThread, this);
	unlockThreadParameter();

	start(hThread);

    // Set the thread priority to idle
	// SetThreadPriority(@@@)
}

oseTimer::~oseTimer(void)
{
	if (hThread) {	
		kill_proc(hThread);
		hThread = 0;
	}
}

void oseTimer::waitThread(void)
{
  do {
	  delay(m_Time);
     (*cbkfunc)(param);
  } while (1);
}


void oseOSEventFlag::signal(void)
{		
	signal_sem(hEventFlag);
}

void oseOSEventFlag::reset(void)
{		
	// this code assume that reset() is called without interfrence of another thread
	// otherwise the number of wait_sem() calls may be more than needed, 
	// and potentialy cause a dead-lock
	OSSEMVAL value = get_sem(hEventFlag);
	while (value > 0) {	
		wait_sem(hEventFlag);
		value = get_sem(hEventFlag);
	}
}

void oseOSEventFlag::wait(const Rhp_int32_t tminms /*= -1 */)
{	
	if ( -1 == tminms ) {
		wait_sem(hEventFlag); // always forever	
	}
	else {
	// OSE semaphores do not have timeouts.
	// To implement timeouts we loop on a try without wait
	// then sleep 50 ms until either semaphore is open ( ret value is 0)
	// or time is up.
		OSSEMVAL semval;
		semval = get_sem(hEventFlag);
		if ( semval > 0 ) {
			// we have to decrement the semaphore value
			wait_sem(hEventFlag);
		}
		else {
			timeUnit sleepTimeInterval = 50;
			int count = tminms / (int)sleepTimeInterval;
			int i = 0;
			for (i = 1; i < count ; i++) {
				delay(sleepTimeInterval);
				semval = get_sem(hEventFlag);
				if ( semval > 0 ) {
					wait_sem(hEventFlag);
					break;
				}
			}
		}
	}
}

oseOSEventFlag::oseOSEventFlag(void)
{
	hEventFlag = create_sem(0); // initially not signalled 
}  

oseOSEventFlag::~oseOSEventFlag(void)
{
	signal();
	kill_sem(hEventFlag);
}  


// Allow recursive locking of the mutex by one thread

void oseMutex::lock(void)
{
	void * current = OMOSFactory::instance()->getCurrentThreadHandle();

	if ( owner == current) { // only one thread will pass this
		count++; 
	}
	else {
		wait_sem(hMutex);
		owner = current;
	}
}

void oseMutex::unlock(void)
{
	void * current = OMOSFactory::instance()->getCurrentThreadHandle();
	if ( owner == current) { // only the owner can unlock the mutex
		if (count == 0) {
			owner = NULL;
			signal_sem(hMutex);
		}
	    else {
			count--;
	    }
	}
}
				 
oseMutex::oseMutex(void)
{ 	  
	count = 0;
	owner = NULL;
	hMutex = create_sem(1); // initially signalled !!!
}
  
oseMutex::~oseMutex(void)
{
	kill_sem(hMutex);
	owner = NULL;
}  

/* get name for a process */
static void getNewProcessName(char *newName)
{	
	static SEMAPHORE nameLock = {1, 0, 0};
	static int nameCounter = 5555;

	wait_sem(&nameLock);
	
	OMitoa(nameCounter, newName, 10);
    nameCounter++;

	signal_sem(&nameLock);
}

void oseThread::endMyThread(void * hThread)
{
	kill_proc((PROCESS)hThread);
}

void oseThread::endOtherThread(void * hThread)
{
	kill_proc((PROCESS)hThread);
}

void oseThread::getThreadEndClbk(oseThread::OMOSThreadEndCallBack * clb_p, void ** arg1_p, const OMBoolean onExecuteThread)
{
	if (onExecuteThread) {
		// asking for a callback to end my own thread
		*clb_p = &endMyThread;
		*arg1_p = (void*)&hThread;
	}
	else {
		// asking for a callback to end my thread by someone else
		*clb_p  = &endOtherThread;
		// my thread handle
		*arg1_p = (void*)&hThread;
	}
}

void oseThread::preExecFunc()
{
	oseThread* me = static_cast<oseThread*>(getThreadParameter(current_process())); 
	if (me != 0)
	{
		me->m_ExecFunc(me->m_ExecParam);
	}
}

oseThread::oseThread(void tfunc(void *), void *param,
					 const char* const name /*= NULL*/,
					 const long stackSize /*= OMOSThread::DefaultStackSize*/)
					 : endOSThreadInDtor(TRUE)
{

	isWrapperThread = 0;	

	// ---------------------------------------------------------------------------------
	// OSE requires a name for the process being created - now it is being got from a 
	// static variable, that is incremented for each new process and converted to 
	// equivalent string
	//
	char pname[80];

	if (NULL == name) {
		getNewProcessName(pname);
	}
	else {
		strcpy(pname,name);
	}

	lockThreadParameter();
	
	// ---------------------------------------------------------------------------------
	// Notice: "callers block" and "user number" parameters control the protection of 
	// memory of the processes (among other things) - these features of OSE can not
	// be used, if Rhapsody does not provide some support for it. One possibility could be
	// to get them from "somewhere", but it would require extra work. Now the process being
	// created inherts both the block number (7th parameter) and the user number (last 
	// parameter) from the caller (the creator of the oseTimer-object)
	//

    m_ExecFunc = tfunc;
    m_ExecParam = param; 

	hThread = create_process(OS_PRI_PROC, pname, preExecFunc, stackSize , OMOSThread::DefaultThreadPriority , 0 /* timeslice */, 
							 0 /* callers block */, NULL /* no redirection */, 0 /* vector */, 
							 0 /* inherit user number */);
	setThreadParameter(hThread, this);
	unlockThreadParameter();
}

oseThread::oseThread(void *osThreadId)
					 : endOSThreadInDtor(TRUE)
{
	// Create Wrapper Thread !!!!
	hThread = (int)osThreadId;
	isWrapperThread = 1;
    m_ExecFunc = 0;
    m_ExecParam = 0;
}


oseThread::~oseThread()
{
	if (!isWrapperThread) {
		// Remove the thread
		if (endOSThreadInDtor) {
			OMBoolean onMyThread = exeOnMyThread();
			if (!((OMThread::isEndOfProcess()) && (exeOnMyThread()))) {
				// Don't kill os thread if this is end of process and the
				// running thread is 'this' - we need the OS thread to do some
				// cleanups and then we kill it explicitely
				OMOSThread::OMOSThreadEndCallBack theOSThreadEndClb = NULL;
				OMOSHandle * threadHandle = NULL;
				// get a callback function to end the os thread
				getThreadEndClbk(&theOSThreadEndClb,reinterpret_cast<void**>(&threadHandle),onMyThread);
				if (theOSThreadEndClb != NULL) {
					// ending the os thread
					(*theOSThreadEndClb)(*threadHandle);
				}
			}
		}
	}
}


oseSemaphore::oseSemaphore(unsigned long semFlags, unsigned long initialCount) 
{
	 m_semId = create_sem(initialCount);
}
oseSemaphore::~oseSemaphore()
{
	kill_sem(m_semId);

}

void oseSemaphore::signal()
{
	signal_sem(m_semId);
}

OMBoolean oseSemaphore::wait(const Rhp_int64_t timeout /*= -1*/)
{
	if (!m_semId) return FALSE;
	// wil alway wait no matter
	if (timeout == 0 || timeout == -1 ) {
		wait_sem(m_semId);
		return TRUE;
	}
	return FALSE;
}


#ifdef _OMINSTRUMENT
#ifndef USE_WIN32_SOCKET

  
oseSocket::oseSocket(void)
{
	theSock = 0;
}

oseSocket::~oseSocket(void)
{
	if (theSock != 0) {
		(void)close(theSock);
	}
}



#ifndef SOCKET_ERROR
#define SOCKET_ERROR -1
#endif /* SOCKET_ERROR */

Rhp_int32_t oseSocket::Create(	const Rhp_const_char_pt  SocketAddress /*= NULL*/, const Rhp_uint32_t nSocketPort /*= 0*/)
{
	struct sockaddr_in	addr;
	char	hostName[128];
    Rhp_int32_t port = nSocketPort;

	// reset the address struct
	memset(&addr, 0, sizeof(addr));

	//
	// set the address
	//
	addr.sin_family = AF_INET;
	if (NULL == SocketAddress) {
		addr.sin_addr.s_addr = INADDR_LOOPBACK;
		strcpy(hostName,"127.0.0.1");
	}
	else {
		if ((addr.sin_addr.s_addr = inet_addr(SocketAddress)) == INADDR_NONE) {
			fprintf(stderr,"Illegal address\n");
			theSock = 0;
			return 0;
		}
		strcpy(hostName,SocketAddress);
	}

	if (nSocketPort == 0) port = 6423;
	addr.sin_port = htons(port);
    
	//
	// create the socket
	//
	if ((theSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == SOCKET_ERROR) {
		fprintf(stderr,"Could not create socket\n");
		theSock = 0;
		return 0;
	}
    

	//
	// connect
	//
	int count = 0;
	int rvStat = 0;
	while ((rvStat = connect(theSock, (struct sockaddr *) &addr, sizeof(addr))) == SOCKET_ERROR && 
		(++count < 10) &&
		(errno == EINTR))
	;

	if (SOCKET_ERROR == rvStat) {
		fprintf(stderr,
			"Could not connect to server at %s port %d\n Error No. : %d\n",
			hostName,
			(int)nSocketPort,
			errno);
		return 0;
	}

	return 1;
}

Rhp_int32_t oseSocket::Send(const Rhp_const_char_pt lpBuf, const Rhp_int32_t nBufLen)
{
  int bytes_writ = 0;
  int n;
  
  while (bytes_writ < nBufLen) {
    n = inet_send(theSock, (char *)(lpBuf + bytes_writ), nBufLen - bytes_writ,0);
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

Rhp_int32_t oseSocket::Receive(Rhp_char_pt lpBuf, const Rhp_int32_t nBufLen)
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
    bytes_read += n;
  }
  return bytes_read;
}

Rhp_int32_t oseSocket::HasInputOnScoket(void)
{
	unsigned long sizeOfData = 0;
	if (0 == ioctl (theSock,FIONREAD, (char*) &sizeOfData)) {
		return (sizeOfData > 0);
	}
	
	return 0;
}

#endif // USE_WIN32_SOCKET

char* oseConnectionPort::m_Buf = NULL;
int oseConnectionPort::m_BufSize = 0;

oseConnectionPort::oseConnectionPort() 
{
	m_Connected = 0;
	m_dispatchfunc = NULL;
	m_ConnectionThread = NULL;

	m_ShouldWaitForAck = 1;
	m_NumberOfMessagesBetweenAck = 0;
	m_AckEventFlag.reset();
}

oseConnectionPort::~oseConnectionPort() {
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

void oseConnectionPort::readFromSockLoop(oseConnectionPort *me)
{
	 char lenStr[MAX_LEN_STR+1];
	 int len;
	 int rv;
	 for (;;) {			
		 if (!me->m_ntSocket.HasInputOnScoket()) {
			delay(100);
			continue;
		 }
		 delay(1);
		 rv = me->m_ntSocket.Receive(lenStr,MAX_LEN_STR);
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
			 rv = me->m_ntSocket.Receive(m_Buf,len);
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


Rhp_int32_t oseConnectionPort::Connect(	const Rhp_const_char_pt SocketAddress /*= NULL*/,
								const Rhp_uint32_t nSocketPort /*= 0*/)
{
	if (NULL == m_dispatchfunc) {
		fprintf(stderr," oseConnectionPort::SetDispatcher should be called before oseConnectionPort::Connect()\n");
		return 0;
	}
	if ( 0  == m_Connected ) {
		m_Connected = m_ntSocket.Create(SocketAddress,nSocketPort);
	}
	if (0 == m_Connected)
		return 0;

	m_ConnectionThread =
				new oseThread((void (*)(void *))readFromSockLoop,(void *)this);

	m_ConnectionThread->start();

	return m_Connected;
}

Rhp_int32_t oseConnectionPort::Send(OMSData *m)
{
	int rv = 0;
	m_SendMutex.lock();
	if (m_Connected) {
		char lenStr[MAX_LEN_STR+1];
		(void)sprintf(lenStr,"%d",m->getLength());
		rv = m_ntSocket.Send(lenStr,MAX_LEN_STR);
		if (rv > 0) {
			rv = m_ntSocket.Send(m->getRawData(),m->getLength());
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

// ------------------------------------------------------------------------------
// Additional functions to deliver a void* parameter to the process being created
// and for storing Rhapsody object pointers that are interested in Software Bus
//		- naive implementation, just to get things to work in some level
//
// NOTICE: removal of information is not implemented yet
// 
#define THREAD_TABLE_SIZE   100
#define NAME_MAX_LENGTH     100

/* struct type for process identifier <-> process parameter -linking */
typedef struct
{
    PROCESS pid;   
    void *param;

} PID_VS_PARAM_STR;

/* arrays for Software Bus applicaiton and thread parameter info */
static PID_VS_PARAM_STR threadParameters[THREAD_TABLE_SIZE];

/* semaphore for locking the information */
static SEMAPHORE *lock = 0;

/* reset array items */
static void initThreadParameters(void)
{
    int i = 0;

    for(i=0; i<THREAD_TABLE_SIZE; i++)
    {
        threadParameters[i].pid = 0;        
        threadParameters[i].param = NULL;
    }
	
	lock = create_sem(1);
}

/* set thread's parameter */
int setThreadParameter(PROCESS pid, void *param)
{
    int i = 0;
    
	for(i=0; i<THREAD_TABLE_SIZE; i++)
    {
        if(threadParameters[i].param == NULL)
        {
            threadParameters[i].pid = pid;    
            threadParameters[i].param = param;
            return 1;
        }
    }

    return 0;
}

/* get thread's parameter */
void *getThreadParameter(PROCESS pid)
{
    int i = 0;

	for(i=0; i<THREAD_TABLE_SIZE; i++)
    {
        if(threadParameters[i].pid == pid)    
        {            
            return threadParameters[i].param;            
        }
    }

    return NULL;
}

int lockThreadParameter(void)
{
	static int initialized = 0;
    if(initialized == 0)
    {
		initialized = 1;
        initThreadParameters();
    }

	wait_sem(lock);
	return 1;
}

int unlockThreadParameter(void)
{
	signal_sem(lock);
	return 1;
}

//
// $Log: oseOS.cpp $
// Revision 1.28  2007/03/11 08:43:00  ilgiga
// Change copyright comment
// Revision 1.27  2007/03/01 14:32:40  ilgiga
// Telelogic instead of i-Logix
// Revision 1.26  2005/11/07 12:11:43  yshekel
// Upgrade_from_60_to_61
// Revision 1.25  2005/09/21 06:49:59  vova
// 87053: redundant main thread dstruction has been avoided on osesfk target: it is destroyed while exit() function execution
// Revision 1.24  2005/08/23 14:53:39  amos
// bugfix 85444 to main branch
// Revision 1.23.1.2  2005/08/22 10:08:22  amos
// provide a compilation switch (OM_NO_RCS_ID) to remove the definitions of the rcsid and hrcsid variables
// this is done to prevent compiler warnings for defined but not used global variables
// Revision 1.23.1.1  2005/08/03 12:39:31  amos
// Duplicate revision
// Revision 1.22  2005/04/21 10:08:43  amos
// Revision 1.21.1.2  2005/03/17 13:00:45  amos
// Use the AnimServices by the adapters
// Revision 1.21  2005/01/30 11:27:11  amos
// oseThread::preExecFunc() - add testing that getThreadParameter(current_process()) returned value is not NULL
// Revision 1.20  2002/07/15 12:27:46  avrahams
// Back to main
// Revision 1.19.1.2  2002/07/04 10:39:08  avrahams
// Cleanup stdnamespace usage
// Revision 1.19  2001/08/07 10:19:00  amos
// back to main branch
// Revision 1.18.1.4  2001/08/07 10:19:00  amos
// use OMTimerManager instead of the OMThreadTimer typedef
// Revision 1.18.1.3  2001/08/05 11:21:24  amos
// modify the memory manager to support passing of the object size in deletion
// Revision 1.18.1.2  2001/08/02 11:28:13  amos
// Revision 1.18.1.1  2001/08/01 15:36:57  amos
// merge bugfix from 3.0.1
// fix oseSocket::HasInputOnScoket() sizeOfData automatic parameter type
// Revision 1.18  2001/07/03 08:11:23  amos
// modify OMMainThread::instance() to register itself as the default active class. if the user didn't register its own.
// use OMMainThread::instance() instead of OXF::getTheDefaultActiveClass() through out the framework.
// Revision 1.17  2001/05/16 14:08:15  amos
// merge OSE 4.3.1 support into r40
// Revision 1.16  2001/04/24 14:49:17  ofer
// changes  for OSE since it works for both win32 ( sfk)
// and for target board
// Revision 1.15  2001/03/01 14:57:41  amos
// back to main branch
// Revision 1.14.1.2  2001/03/01 14:57:41  amos
// add abuility for the user to set an alternative default active class and low-level timers
// Revision 1.14.1.1  2001/01/30 09:10:01  amos
// Duplicate revision
// Revision 1.13  2001/01/25 13:59:24  avrahams
// OXF globals encapsulation
// Revision 1.12.1.2  2001/05/03 16:01:40  amos
// Changes framework API to support OSE 4.3.1
// - Modify the name of  OMOSMutex::free() to OMOSMutex::unlock
// - Modify the name of State::exit() & State::enter() to State::exitState() & State::enterState()
// Revision 1.12.1.1  2001/04/19 11:40:17  amos
// upgrade OSE files to support OSE 4.3.1
// - cleanup the OSE framework files
// - use OSE 4.3.1 API to fix the behavior of oseThread::setPriority() - so it can be called by other threads.
// Revision 1.12  2000/11/28 14:00:26  ofer
// bugfix 37952 using stackSize ( instead of DEFAULT_STACK ) 
// when creating thread
// and using OMOSThread::DefaultThreadPriority instead of PRIORITY_NORMAL
// somhow checkpoint of revision 1.10 is wrong ( it is the same as 1.9)
// Revision 1.11  2000/11/13 12:23:37  amos
// merge 1.10.1.2 and 1.10.2.2
// Revision 1.10.2.2  2000/11/09 19:52:39  npadmawar
// Changes for OXFEnd
// Revision 1.10.2.1  2000/10/12 06:55:47  npadmawar
// Revision 1.10.1.2  2000/11/08 15:57:11  amos
// modify the OS layer message queue put() method to return a success status
// Revision 1.10.1.1  2000/10/12 06:55:47  amos
// Duplicate revision
// Revision 1.9  2000/07/11 07:52:02  amos
// the main change related to modify char* to const char*.
// there are some other changes related to assignment of static member function as extern "C" functions.
// Also modify NTOSMessageQueue/Sol2OSMessageQueue to have OMQueue<void*> as a private member (aggregation) instead of rivate inheritace from OMQueue<void*>
// Revision 1.8  2000/01/25 16:42:27  amos
// back to main branch
// Revision 1.7.1.1  2000/01/18 15:50:54  amos
// Revision 1.7  1999/12/12 16:01:59  amos
// fix OSEndApplication() - disable the deletion of the current process, let exit(0) do the job.
// Revision 1.6  1999/12/09 14:00:21  amos
// fix oseMessageQueue::get(), basicly roll-back to 1.4, but I made some changes,
// particulary remove the section which prevent other processes to access the message queue.
// this was done since the preventions  caused lost of events.
// Revision 1.5  1999/12/08 13:21:14  ofer
// using win32 socket in ose soft kernel
// win32 socket does not block on recieve but check if we have input on the 
// socket and only then reads it.
// Revision 1.4  1999/12/07 09:52:27  amos
// fix the distruction of oseThread.
// Revision 1.3  1999/12/02 13:15:31  amos
// fix oseOSMessageQueue::getMessageList(),
// back to main branch
// Revision 1.2.1.2  1999/12/01 13:17:57  amos
// support getMessageList() for OSE
// fix OSEndApplication(), use exit() instead of kill_process() at the end of the method.
// --- Added comments ---  amos [1999/12/01 13:20:57 GMT]
// replace cout messages with NOTIFY_TO_ERROR(), and wraped in animation ifdef
// Revision 1.2  1999/11/21 12:31:13  amos
// back to main branch
// Revision 1.1.1.2  1999/11/15 06:20:41  amos
// fix oseSocket::Create(), remove the htonl() after call to inet_addr()
// Revision 1.1.1.1  1999/11/10 07:35:56  amos
// fix in oseSocket::Create()
// Revision 1.1  1999/11/08 10:58:37  ofer
// Initial revision
// Revision 1.19  1998/09/09 13:12:40  ofer
// interface of eventFlag::wait changed ( passing time in ms)
// Revision 1.18  1998/06/24 08:18:30  ofer
// bugfix 3748 and 5456
// Attention the OXFEnd rutine was deleted and we decided that every rtos 
// will implement the OSEndApplication by itself
// the omthread dtor and aomdispatcher dtor use the endOfProcess
// the aomdispatcher does not inform delete of instance deletion
// vxos.cpp oxf.cpp/h omthread.cpp aomstep.cpp aomthrd.cpp
// Revision 1.17  1998/06/23 12:30:17  yachin
// fix VX virtual table problem bug
// Revision 1.16  1998/05/03 08:15:45  ofer
// getMessageList will function properly in all cases
// (not just in INSTRUMENTED mode) vxoxf.cpp
// Revision 1.15  1997/12/14 14:37:46  ofer
// added  delayCurrentThread(long ms) to abstract factory 
// and define and implement the method in the XXXOS.cpp/h
// Also added convienent macro OXFTDelay(timInMs)
// os.h ntos.cpp/h oseOs.cpp/h sol2os.cpp/h
// Revision 1.14  1997/06/09 07:50:12  ofer
// Full support for trace and animation
// added OSEndApplication (vxos.cpp/h)
// Revision 1.13  1997/04/30 11:03:30  ofer
// If local host name is equal to the current host name 
// we use the INADDR_LOOPBACK adderss
// sol2os.cpp ntos.cpp oseOS.cpp
// Revision 1.12  1997/04/29 09:08:56  ofer
// eventFlag for suspended thread is deleted after signal;
// vxos.cpp
// Revision 1.11  1997/04/17 05:24:56  ofer
// Support for trace/animation under oseWorks
// the low level WAS NOT debugged yet !!!!
// oseOS.cpp/h
// Revision 1.10  1997/04/09 10:19:54  ofer
// update oseOS.cpp/h interfaces so INSTRUMENTED
// version can be compiled
// I have to implement the Socket/ConnectionPort and
// MessageQueue info in order to work with Tracer/Animator
// oseOS.cpp/h
// Revision 1.9  1997/03/05 13:59:18  ofer
// Implemet creation of suspended oseThread by using Event Flag
// We should use the TaskInit/taskActivate system calls but
// somhow it does not work so for the time beeing it is implemented
// with EventFlag
// oseOs.cpp/h
// Revision 1.8  1997/02/17 14:16:44  ofer
// 1) Move some of the inline functions to the oseOs.cpp file
// 2) correct oseOsMessageQueue::isEmpty and now simple
// programs are working
// oseOs.cpp/h
// 
// Revision 1.7  1997/02/17 09:25:26  ofer
// return 0 on not implemented methods
// Revision 1.6  1997/01/29 09:01:34  ofer
// using native os call to determine if MessageQ is empty
// state --> m_State
// Revision 1.5  1997/01/28 12:00:40  ofer
// member variables "time" changed to "m_Time"
// remove signal method from vxOsMessageQueue
// oseOsMessageQueue::getNext/First?Current print "Not Implemented"
// timer.cpp/h ntos.cpp/h oseOs.cpp/h
// Revision 1.4  1997/01/27 13:55:16  ofer
// No need for OMRegisterThread and OMGetCurrentThread global
// functions in oseOs.cpp
// Revision 1.3  1997/01/27 11:44:16  ofer
// Trying to support vxWorks
// for the time beeing we support compilation of NON instumented
// version (for vxWorks.
// we assume the WE DO NOT use iostream for vxWorks
// Revision 1.2  1996/11/25 08:10:04  erang
//
