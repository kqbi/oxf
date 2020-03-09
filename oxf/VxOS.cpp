//
//	file name   :	$Source: R:/StmOO/Master/cg/LangCpp/oxf/rcs/VxOS.cpp $
//	file version:	$Revision: 1.71 $
//
//	purpose:	 	
//
//	author(s):		
//	date started:	
//	date changed:	$Date: 2007/05/28 07:43:50 $
//	last change by:	$Author: ilvler $
//
//	Licensed Materials - Property of IBM
//	(c) Copyright IBM Corporation 1996, 2016. All Rights Reserved.
//	
//	Note to U.S. Government Users Restricted Rights:  
//	Use, duplication or disclosure restricted by GSA ADP Schedule 
//	Contract with IBM Corp.
//

// Rhapsody Framework includes
#include "oxf.h"
#include "VxOS.h"
#include "omthread.h"
#include "timer.h"

#include <ctype.h>
#include <errno.h>

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

char VxTimer::TimerName[6] = {'t', 'i', 'm', 'e', 'r', 0};

OMOSFactory* OMOSFactory::instance(void) {
    static VxOSFactory theFactory;
    return &theFactory;
}

void OMOS::initEpilog(void) {
    taskDelay(2);
}

void OMOS::endProlog(void) {
    return;
}

void OMOS::endApplication(const Rhp_int32_t retCode) {
#ifdef _OMINSTRUMENT
	AnimServices::notifyEndApplication(false);
#endif // _OMINSTRUMENT

	OMThread::setEndOfProcess( true );		
	OMThread* currentThread = OMThread::cleanupAllThreads();
	OMTimerManager::clearInstance();

#ifdef _OMINSTRUMENT
	AnimServices::cleanupOnEndApplication();
#endif // _OMINSTRUMENT

	OMThread* maint = OMMainThread::instance(false);
	if (maint != NULL) {
		OMTaskHandle maintHandle = (OMTaskHandle)(reinterpret_cast<intptr_t>(maint->getOsHandle()));
		Rhp_char_pt maintName = taskName(maintHandle);
		Rhp_int32_t killmainthread = 1;
		if ( (maintName != NULL) ) {
			if (!strcmp(maintName,"tShell") != 0 ){
				taskRestart(maintHandle);
			} else {
				taskDeleteForce(maintHandle);
			}
			killmainthread = 0;
		}
		if (killmainthread != 0) {
			maint->destroyThread();
		}
	}

    if (currentThread != NULL) {
        OMOSThread::OMOSThreadEndCallBack theOSThreadEnderClb;
        OMOSHandle* arg1 = NULL;
        // get a callback to end the thread
        currentThread->getOSThreadEndClb(&theOSThreadEnderClb,(void**)&arg1);
		// save handle value before theThread will be destroyed
		OMOSHandle argValue = *arg1;
        currentThread->setEndOSThreadInDtor(FALSE); // do not really end the os thread because we 
                                                    // are executing on this thread and if do
                                                    // we are going to leak resources
        delete currentThread;	// delete the whole object through a virtual destructor
        if (theOSThreadEnderClb != NULL) {
            (*theOSThreadEnderClb)(argValue);	// now end the os thread
        }
    }

#if defined(__RTP__)
	exit(retCode);
#else
	// make sure that the execution thread is being endded
    VxThread::endMyThread((void*) taskIdSelf());
#endif
}

static timeUnit cvrtTmInMStoTicks(const timeUnit ms) { 
    timeUnit ticks = ( sysClkRateGet() * ms ) / 1000; // time is in milliseconds
    if (ticks == 0) {
        ticks = 1;
    }
    return ticks;
}


void* VxOSFactory::getCurrentThreadHandle(void) const {
    return reinterpret_cast<void*>(taskIdSelf());
}

void VxOSFactory::delayCurrentThread(const timeUnit ms) const {
    timeUnit ticks = cvrtTmInMStoTicks(ms);
    taskDelay(static_cast<_Vx_ticks_t>(ticks));
}

void *VxOSMessageQueue::get(void) {
    void *m;

    if (m_State == dataReady) {
        m = pmessage;
        m_State = noData;
    } else {
        // function returns NULL, if the queue is empty
        ssize_t ret;
        if ((ret = msgQReceive(hVxMQ, reinterpret_cast<Rhp_char_pt>(&m), sizeof(m), NO_WAIT)) <= 0) {
            // nonblocking semantics 
            // S_objLib_OBJ_UNAVAILABLE - The NO_WAIT timeout was specified but no message was available
            if ((ret == ERROR) && (errno != S_objLib_OBJ_UNAVAILABLE)) {
                OM_NOTIFY_ERROR("msgQReceive","VxOSMessageQueue::get")
            }
        m = NULL;
        }
    }
    return m;
}


void VxOSMessageQueue::pend(void) {
	if (m_State == noData) {
		void *m;
		if (msgQReceive(hVxMQ, reinterpret_cast<Rhp_char_pt>(&m), sizeof(m), NO_WAIT)<= 0) {
			// if the hVxMQ is empty,
			if (ERROR == msgQReceive(hVxMQ, reinterpret_cast<Rhp_char_pt>(&m), sizeof(m), WAIT_FOREVER)) {
				// to wait for message
				OM_NOTIFY_ERROR("msgQReceive","VxOSMessageQueue::pend")
			}
		} 
		m_State = dataReady;
		pmessage = m;
	}
}

OMBoolean VxOSMessageQueue::put(void* aMessage, const OMBoolean fromISR) {
    static void* NULL_VAL = NULL;
    if (NULL == aMessage) {
        aMessage = NULL_VAL;
    }

    Rhp_int32_t timeout = WAIT_FOREVER;
    Rhp_int32_t priority = MSG_PRI_NORMAL;
    STATUS res = OK;

    if (fromISR) {
        timeout = NO_WAIT;
#ifdef OM_VX_URGENT_PRIORITY_FOR_ISR
        priority = MSG_PRI_URGENT;
#endif // OM_VX_URGENT_PRIORITY_FOR_ISR
    }
    res = msgQSend(hVxMQ, reinterpret_cast<Rhp_char_pt>(&aMessage), sizeof(aMessage), timeout, priority);
    if (res == ERROR)	{
        OM_NOTIFY_ERROR("msgQSend","VxOSMessageQueue::put")
    }
    return (res == OK);
}


Rhp_int32_t VxOSMessageQueue::isEmpty(void) const {
    Rhp_int32_t status;
    if ((noData == m_State) && (0 == msgQNumMsgs(hVxMQ)) ) {
        status = 1;
    	} else {
        status = 0;
    }
    return status;
}


void VxOSMessageQueue::getMessageList(OMListType& aList) {
    	aList.removeAll();
#ifdef _WRS_KERNEL
    if (!isEmpty()) {
        if (noData != m_State) {
            aList.add(pmessage);
        }
        MSG_Q_INFO msgQInfo;
        msgQInfo.taskIdListMax = 0;
        msgQInfo.taskIdList = NULL; // do not care which tasks are waiting
        msgQInfo.msgListMax = 0;
        msgQInfo.msgPtrList = NULL;
        msgQInfo.msgLenList = NULL; // do not care about messages length
        // the first call will retrieve the numMsgs data member
        if (OK == msgQInfoGet(hVxMQ,&msgQInfo)) {
            if (msgQInfo.numMsgs > 0) {
                size_t numMsgs = msgQInfo.numMsgs;
                msgQInfo.msgListMax = static_cast<int>(numMsgs);
                msgQInfo.msgPtrList = OMNEW(Rhp_char_pt,numMsgs);
                if (OK == msgQInfoGet(hVxMQ,&msgQInfo)) {
                    void* m;
                    size_t i;
                    for (i = 0; i < numMsgs; i++) {
                        m = *(void **)msgQInfo.msgPtrList[i];
                        aList.add(m);
                    }
                }
                OMDELETE(msgQInfo.msgPtrList, sizeof(Rhp_char_pt) * numMsgs);
            }
        }
    }
#endif // _WRS_KERNEL
}

OMBoolean VxOSMessageQueue::isFull(void) const {
    OMBoolean status = false;

    if (!isEmpty()) {
        MSG_Q_INFO msgQInfo;
#ifdef _WRS_KERNEL
        msgQInfo.taskIdListMax = 0;
        msgQInfo.taskIdList = NULL; // do not care which tasks are waiting
        msgQInfo.msgListMax = 0;
        msgQInfo.msgPtrList = NULL;
        msgQInfo.msgLenList = NULL; // do not care about messages length
#endif // _WRS_KERNEL
        if (OK != msgQInfoGet(hVxMQ,&msgQInfo)) {
            OM_NOTIFY_ERROR("msgQInfoGet","VxOSMessageQueue::isFull")
            status = true;    // assume the worst case
        } else {
            if (msgQInfo.numMsgs >= msgQInfo.maxMsgs) {
                status = true;
            }
        }
    }
    return status;
}


 // TickTimer
VxTimer::VxTimer( const timeUnit ptime, 
                  void pcbkfunc(void *),
                  void *pparam ):
     cbkfunc(pcbkfunc),
     m_Time(ptime),
     param(pparam) {
    // Create a thread that runs bridge, passing this as argument 
    ticks = cvrtTmInMStoTicks(m_Time);
    hThread = taskSpawn( TimerName, 
                         PRIORITY_HIGH,
                         VX_FP_TASK, 
                         SMALL_STACK,
                         reinterpret_cast<FUNCPTR>(bridge),
                         reinterpret_cast<_Vx_usr_arg_t>(this),
                         0,0,0,0,0,0,0,0,0 );
    if (TASK_ID_ERROR == hThread) {
        OM_NOTIFY_ERROR("taskSpawn","VxTimer::VxTimer")
    }
}

// IdleTimer (Simulated Time) 
VxTimer::VxTimer( void pcbkfunc(void *), 
                  void *pparam):
     cbkfunc(pcbkfunc),
     m_Time(0), // Just create context-switch until the system enters idle mode
     param(pparam),
     ticks(1) {
  	// Create a thread that runs bridge, passing this as argument	
    hThread = taskSpawn( TimerName,
                         PRIORITY_LOW,
                         VX_FP_TASK,
                         SMALL_STACK,
                         reinterpret_cast<FUNCPTR>(bridge),
                         reinterpret_cast<_Vx_usr_arg_t>(this),
                         0,0,0,0,0,0,0,0,0 );
    if (TASK_ID_ERROR == hThread) {
        OM_NOTIFY_ERROR("taskSpawn","VxTimer::VxTimer")
    }
    // Set the thread priority to idle
    // SetThreadPriority(@@@)
}

VxTimer::~VxTimer(void) {
	if (hThread != 0) {
		void* executedOsHandle = OMOSFactory::instance()->getCurrentThreadHandle();
		// a handle to this' 'thread'
		void* myOsHandle = reinterpret_cast<void *>(hThread);
		OMBoolean onMyThread = ((executedOsHandle == myOsHandle) ? TRUE : FALSE);

		if (onMyThread) {
			VxThread::endMyThread(myOsHandle);
		}	else {
			VxThread::endOtherThread(myOsHandle);
		}
		hThread = 0;
	}
}

void VxTimer::setAffinity(const OMAffinity_t aff) {
	VxThread::setThreadAffinity(hThread, aff);
}

void VxTimer::bridge(VxTimer *me) {
	me->waitThread();
}

void VxTimer::waitThread(void) {
  do {
     taskDelay(static_cast<_Vx_ticks_t>(ticks));
     (*cbkfunc)(param);
  } while (1);
}


void VxOSEventFlag::signal(void) {
	if (ERROR == semGive(hEventFlag)) {
		OM_NOTIFY_ERROR("semGive","VxOSEventFlag::signal")
	}
}

void VxOSEventFlag::reset(void) {
	// The semaphore is created as SEM_EMPTY, meaning that it is already locked by the current thread.
	if ((ERROR == semTake(hEventFlag, NO_WAIT)) && (errno != S_objLib_OBJ_UNAVAILABLE))	{
		OM_NOTIFY_ERROR("semTake","VxOSEventFlag::reset")
	}
}

void VxOSEventFlag::wait(const Rhp_int32_t tminms /*= -1 */) {
	if ( -1 == tminms) {
		if (ERROR == semTake(hEventFlag, WAIT_FOREVER)) {
			OM_NOTIFY_ERROR("semTake","VxOSEventFlag::wait")
		}
	}	else {
		timeUnit ticks = cvrtTmInMStoTicks(tminms);
		if (ERROR == semTake(hEventFlag, static_cast<_Vx_ticks_t>(ticks))) {
			OM_NOTIFY_ERROR("semTake","VxOSEventFlag::wait")
		}
	}
}

VxOSEventFlag::VxOSEventFlag(void) {
	hEventFlag = semBCreate(SEM_Q_FIFO, SEM_EMPTY );
	if (NULL == hEventFlag) {
		OM_NOTIFY_ERROR("semBCreate","VxOSEventFlag::VxOSEventFlag")
	}
}  

VxOSEventFlag::~VxOSEventFlag(void) {
	if (ERROR == semDelete(hEventFlag))	{
		OM_NOTIFY_ERROR("semDelete","VxOSEventFlag::~VxOSEventFlag")
	}
}  

void VxThread::preExecFunc(void* me) {
	if (((VxThread *)me)->m_SuspEventFlag) {
		((VxThread *)me)->m_SuspEventFlag->wait();
		/* delete the Eventflag here after receiving */
		VxOSEventFlag* tmp = ((VxThread *)me)->m_SuspEventFlag;
		((VxThread *)me)->m_SuspEventFlag= NULL;
		delete tmp;
	}
	((VxThread *)me)->m_ExecFunc(((VxThread *)me)->m_ExecParam);
}

VxThread::VxThread( void tfunc(void *), 
                    void *param,
                    const Rhp_const_char_pt name,
                    const Rhp_int32_t stackSize ) : endOSThreadInDtor(TRUE) {
	isWrapperThread = 0;

	// copy the thread name
	size_t len = 0;
	Rhp_char_pt myName = NULL;

	if (name != NULL) {
		len = strlen(name);
	}
	// check for legal name
	for (size_t i = 0; i < len; i++) {
		if ((!isalnum(name[i])) && (name[i] != '_')) {
			len = 0;
			break;
		}
	}
	if (len > 0) {
		myName = const_cast<Rhp_char_pt>(name);
	}
	m_SuspEventFlag = new VxOSEventFlag();
	m_SuspEventFlag->reset();
	// Create SUSPENDED thread !!!!!!
	m_ExecFunc = tfunc;
	m_ExecParam = param;
	hThread = 0;
	hThread = taskSpawn( myName,                                /* name of new task (stored at pStackBase) */
                         PRIORITY_NORMAL,                       /* priority of new task */
                         VX_FP_TASK,                            /* task option word */ 
                         static_cast<Rhp_int32_t>(stackSize),   /* size (bytes) of stack needed */
                         reinterpret_cast<FUNCPTR>(preExecFunc),     /* thread function */
                         reinterpret_cast<_Vx_usr_arg_t>(this),             /* argument to thread */
                         0,0,0,0,0,0,0,0,0); 
    if (TASK_ID_ERROR == hThread) {
        OM_NOTIFY_ERROR("taskSpawn","VxThread::VxThread")
    }
}

VxThread::VxThread(void* osThreadId) : endOSThreadInDtor(TRUE) {
    	m_SuspEventFlag = NULL;
    // Create Wrapper Thread !!!!
    hThread = (OMTaskHandle)reinterpret_cast<intptr_t>(osThreadId);
    isWrapperThread = 1;
}


VxThread::~VxThread(void) {
    if (!isWrapperThread) {
        if (m_SuspEventFlag) {
            delete m_SuspEventFlag;
        }
        // Remove the thread
        if (endOSThreadInDtor) {
            OMBoolean onMyThread = exeOnMyThread();
            if (!((OMThread::isEndOfProcess()) && (exeOnMyThread()))) {
                // Don't kill os thread if this is end of process and the
                // running thread is 'this' - we need the OS thread to do some
                // cleanups and then we kill it explicitely
                OMOSThread::OMOSThreadEndCallBack theOSThreadEndClb = NULL;
                OMOSHandle* threadHandle = NULL;
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

void VxThread::endMyThread(void* hThread) {
    endOtherThread(hThread); // in VxWorks it is the same action
}

void VxThread::endOtherThread(void* hThread) {
    if (OMThread::isEndOfProcess()) {
        if (ERROR == taskDeleteForce((OMTaskHandle)reinterpret_cast<intptr_t>(hThread))) {
            // Force in animation mode while end application - since this is probably waiting on something
            OM_NOTIFY_ERROR("taskDeleteForce","VxThread::endOtherThread")
        }
    } else {
        if (ERROR == taskDelete((OMTaskHandle)reinterpret_cast<intptr_t>(hThread))) {
            OM_NOTIFY_ERROR("taskDelete","VxThread::endOtherThread")
        }
    }
}

void VxThread::getThreadEndClbk( VxThread::OMOSThreadEndCallBack* clb_p, 
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

void VxThread::start(void) {
    if (m_SuspEventFlag) {
        m_SuspEventFlag->signal();
    } else {
        resume();
    }
}

void VxThread::setAffinity(const OMAffinity_t aff) {
	VxThread::setThreadAffinity(hThread, aff);
}

#if ((_WRS_VXWORKS_MAJOR >5) && (_WRS_VXWORKS_MINOR >5))

OMAffinity_t VxThread::getAffinity(void) const {
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

void VxThread::setThreadAffinity(OMTaskHandle m_hThread, const OMAffinity_t coreId) {
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



void VxThread::setPwrState(const OMPowerMode_t val)
{
#ifdef _WRS_KERNEL
#ifdef OM_SUPPORT_POWER_MGMT
	if (cpuPwrTaskPStateSet(hThread,val) == ERROR) {
		OM_NOTIFY_ERROR("cpuPwrTaskPStateSet","VxThread::setPwrState")
	}
#endif //OM_SUPPORT_POWER_MGMT
#endif
}

OMPowerMode_t VxThread::getPwrState(void) const
{
#ifdef _WRS_KERNEL
#ifdef OM_SUPPORT_POWER_MGMT
	return cpuPwrTaskPStateGet(hThread);
#else
	return OMPwrModeNone;
#endif //OM_SUPPORT_POWER_MGMT
#else
	return OMPwrModeNone;
#endif
}

#else
OMAffinity_t VxThread::getAffinity(void) const {
	return 0U; 
}

void VxThread::setThreadAffinity(Rhp_int32_t /*m_hThread*/, const OMAffinity_t /*aff*/) {
}

void VxThread::setPwrState(const OMPowerMode_t val)
{
}
OMPowerMode_t VxThread::getPwrState(void) const
{
	return OMPwrModeNone;
}
#endif // _WRS_VXWORKS_MAJOR


// Reset the thread OS handle
// Should be used with care and only for wrapper threads
// Argument void * newHandle : 
// The new OS handle
void VxThread::resetWrapperThreadOsHandle(void* newHandle) {
	if (isWrapperThread) {
		hThread = (OMTaskHandle)reinterpret_cast<intptr_t>(newHandle);
	}
}

#ifdef _OMINSTRUMENT

#define	WIND_STOP 0x10	/* stopped by the debugger */
extern "C" {

    // this function is called from host while IDE running
    Rhp_int32_t OMTaskIsSuspended(OMTaskHandle handle) {
        Rhp_int32_t status = 0;
        if (taskIsSuspended(handle)) {
            status = 1;
        } else{
            TASK_DESC pTaskDesc;
            STATUS ret = taskInfoGet(handle, &pTaskDesc);
            if ((ret == OK) && (pTaskDesc.td_status == WIND_STOP)) {
                // task is stopped at break point
                status = 1;
           }
        }
        return status;
    }
} // end extern C

void VxSocket::Close(void) {
    if (theSock != 0) { 
        (void)shutdown(theSock,2);
        (void)close(theSock);
        theSock = 0;
    }
}


VxSocket::VxSocket(void) {
    theSock = 0;
}

VxSocket::~VxSocket(void) {
    Close();
}

#ifndef SOCKET_ERROR
#define SOCKET_ERROR -1
#endif // SOCKET_ERROR

Rhp_int32_t VxSocket::Create( const Rhp_const_char_pt SocketAddress /*= NULL*/,
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
            if (((Rhp_uintptr_t)ERROR) == addr.sin_addr.s_addr) {
                addr.sin_addr.s_addr = hostGetByName(hostName);
            }
            if (((Rhp_uintptr_t)ERROR) == addr.sin_addr.s_addr) {
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

    addr.sin_port = static_cast<u_short>(htons(aSocketPort));

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

Rhp_int32_t VxSocket::Send( const Rhp_const_char_pt lpBuf,
                            const Rhp_int32_t nBufLen ) {
    ssize_t bytes_writ = 0;
    ssize_t n;

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
    return static_cast<Rhp_int32_t>(bytes_writ);
}

Rhp_int32_t VxSocket::Receive( Rhp_char_pt lpBuf, 
                               const Rhp_int32_t nBufLen ) {
    ssize_t bytes_read = 0;
    ssize_t n;

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
    return static_cast<Rhp_int32_t>(bytes_read);
}

Rhp_char_pt VxConnectionPort::m_Buf = NULL;
Rhp_int32_t VxConnectionPort::m_BufSize = 0;


VxConnectionPort::VxConnectionPort(void) {
      m_Connected = 0;
    m_dispatchfunc = NULL;
      m_ConnectionThread = NULL;
    m_ShouldWaitForAck = 1;
    m_NumberOfMessagesBetweenAck = 0;
    m_AckEventFlag.reset();
}

VxConnectionPort::~VxConnectionPort(void) {
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


void VxConnectionPort::readFromSockLoop(VxConnectionPort *me) {
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
        // ( since the thraed is self locked)
        me->m_ShouldWaitForAck = 0;
        me->m_AckEventFlag.signal();
        me->m_dispatchfunc(OMSData::string2OMSData(m_Buf));
        me->m_ShouldWaitForAck = 1;
        }
    }
}

Rhp_int32_t VxConnectionPort::Connect( const Rhp_const_char_pt SocketAddress /*= NULL*/,
                                       const Rhp_uint32_t aSocketPort /*= 0*/) {
    if (NULL == m_dispatchfunc) {
        fprintf(stderr,"VxConnectionPort::SetDispatcher should be called before NTConnectionPort::Connect()\n");
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
    new VxThread((void (*)(void *))readFromSockLoop,(void *)this,"tRhpSock");

	if (OXF::frmThreadAffinities.AnimMessageReader != 0U)
	{	// multi core support
		m_ConnectionThread->setAffinity(OXF::frmThreadAffinities.AnimMessageReader);
	}

    m_ConnectionThread->start();
    return m_Connected;
}


Rhp_int32_t VxConnectionPort::Send(OMSData* aMessage) {
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
///                        VxSemaphore                      
////////////////////////////////////////////////////////////

VxSemaphore::VxSemaphore( const Rhp_uint64_t semFlags, 
                          const Rhp_uint64_t initialCount ) : m_semId(NULL) {
    m_semId = semCCreate(static_cast<Rhp_int32_t>(semFlags),
                         static_cast<Rhp_int32_t>(initialCount) );
    if (NULL == m_semId) {
        OM_NOTIFY_ERROR("semCCreate", "VxSemaphore::VxSemaphore")
    }
}

///////
VxSemaphore::~VxSemaphore() {
    if (m_semId) {
        if (ERROR == semFlush(m_semId))	{
            OM_NOTIFY_ERROR("semFlush", "VxSemaphore::~VxSemaphore")
        }
        if (ERROR == semDelete(m_semId)) {
            OM_NOTIFY_ERROR("semDelete", "VxSemaphore::~VxSemaphore")
        }
    }
}

////////
void VxSemaphore::signal() {
    if (m_semId) {
        if (ERROR == semGive(m_semId)) {
            OM_NOTIFY_ERROR("semGive", "VxSemaphore::signal")
        }
    }
}

OMBoolean VxSemaphore::wait( const Rhp_int64_t aTimeout ) {
    OMBoolean status;
    if (!m_semId) {
        status = FALSE;
    } else {
        Rhp_int64_t timeout = aTimeout;
        if (timeout < 0) {
            timeout = WAIT_FOREVER;
        }
        status = (semTake(m_semId, static_cast<_Vx_ticks_t>(timeout)) == OK);
    }
    return status;
}


//
// $Log: VxOS.cpp $
// Revision 1.71  2007/05/28 07:43:50  ilvler
// Macro OM_NOTIFY_ERROR call added after every VxWorks system unsuccessful calls
// Revision 1.70  2007/03/11 08:42:54  ilgiga
// Change copyright comment
// Revision 1.69  2007/03/01 14:32:34  ilgiga
// Telelogic instead of i-Logix
// Revision 1.68  2006/10/16 13:35:19  vova
// RTP support
// Revision 1.67  2005/11/07 12:11:52  yshekel
// Upgrade_from_60_to_61
// Revision 1.66  2005/09/25 16:36:04  vova
// 
// --- Added comments ---  vova [2005/09/25 17:13:07 GMT]
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
// Revision 1.65  2005/08/23 14:53:36  amos
// bugfix 85444 to main branch
// Revision 1.64.1.2  2005/08/22 10:08:19  amos
// provide a compilation switch (OM_NO_RCS_ID) to remove the definitions of the rcsid and hrcsid variables
// this is done to prevent compiler warnings for defined but not used global variables
// Revision 1.64.1.1  2005/08/04 07:10:03  amos
// Duplicate revision
// Revision 1.63  2005/08/03 14:47:29  vova
// 85446: OMTaskIsSuspended has been changed to process the STOP status of task
// Revision 1.62  2005/08/03 12:39:29  amos
// Fix AnimServices support for end application to support the various RTOS needs
// - Add a boolean argument to notifyEndApplication() that controls the closing of the connection to Rhapsody
// - Add new public static operation cleanupOnEndApplication() that destroys the anim dispatcher
// - Modify the adapters usage of these operations besed on the 6.0 version of the adapters
// Revision 1.61  2005/07/10 09:36:09  vova
// 63382: ISR event is put as urgent only if OM_VX_URGENT_PRIORITY_FOR_ISR is defined
// Revision 1.61  2005/07/10 09:25:45  vova
// 63382: ISR event is put as urgent only if OM_VX_URGENT_PRIORITY_FOR_ISR is defined
// Revision 1.60  2005/07/03 09:05:05  vova
// VxWorks 6.0 warnings eliminated
// Revision 1.59  2005/04/21 10:08:33  amos
// Revision 1.58.2.2  2005/03/17 13:00:43  amos
// Use the AnimServices by the adapters
// Revision 1.58  2005/01/05 12:10:23  vova
// Memory leaks in tasks removed
// Revision 1.58  2005/01/04 16:31:48  vova
// Memory leaks in tasks removed
// Revision 1.57  2004/10/13 10:54:52  vova
// 71760: very old problem, when SuspEventFlag is deleted too early while task starting.
// Revision 1.56  2004/01/19 09:39:12  vova
// VX_FP_TASK option added for task creation
// Revision 1.55  2003/10/29 09:21:23  eldad
// Fixed message queue isFull()
// Revision 1.54.1.2  2003/10/29 08:13:32  vova
// Revision 1.54  2002/11/05 07:51:12  vova
// 54208: Support for MULTI 2000 v3.5
// Revision 1.53  2002/09/17 13:07:01  vova
// 56422: Breakpoint doesn't work under IDE
// Revision 1.52  2002/08/21 09:23:16  vova
// 53870: timer resolution problem fixed (if evaluated tick is equal 0, it should be 1)
// Revision 1.51  2002/01/07 09:57:59  vova
// Style changes
// Revision 1.50  2002/01/06 09:03:31  vova
// Message queue iteration has been made more efficient.
// Revision 1.48  2001/11/25 14:46:15  vova
// 47212: main task should be killed before quitting from application
// Revision 1.47  2001/11/21 16:46:32  amos
// VxConnectionPort::Connect() - comment the default parameters value.
// Revision 1.46  2001/08/07 10:18:59  amos
// back to main branch
// Revision 1.45.1.4  2001/08/07 10:18:59  amos
// use OMTimerManager instead of the OMThreadTimer typedef
// Revision 1.45.1.3  2001/08/05 09:35:27  amos
// modify the memory manager to support passing of the object size in deletion
// Revision 1.45.1.2  2001/08/02 11:34:23  amos
// Revision 1.45.1.1  2001/07/03 08:11:23  amos
// Duplicate revision
// Revision 1.44  2001/05/16 12:32:34  amos
// merge OSE 4.3.1 support into r40
// Revision 1.43  2001/03/01 14:57:40  amos
// back to main branch
// Revision 1.42.1.2  2001/03/01 14:57:40  amos
// add abuility for the user to set an alternative default active class and low-level timers
// Revision 1.42.1.1  2001/01/30 09:09:51  amos
// Duplicate revision
// Revision 1.41  2001/01/25 13:59:12  avrahams
// OXF globals encapsulation
// Revision 1.40  2000/11/14 11:14:59  vova
// Bug 38164: OXFTdelay(0) isn't supported
// Revision 1.39  2000/11/13 12:14:09  amos
// merge 1.38.1.2 and 1.38.2.2
// Revision 1.38.2.2  2000/11/08 15:44:27  amos
// modify the OS layer message queue put() method to return a success status
// Revision 1.38.2.1  2000/07/11 07:52:02  amos
// Duplicate revision
// Revision 1.38.1.2  2000/11/06 16:50:27  npadmawar
// Added OXFEndProlog
// Revision 1.38  2000/07/11 07:52:02  amos
// the main change related to modify char* to const char*.
// there are some other changes related to assignment of static member function as extern "C" functions.
// Also modify NTOSMessageQueue/Sol2OSMessageQueue to have OMQueue<void*> as a private member (aggregation) instead of rivate inheritace from OMQueue<void*>
// Revision 1.37  2000/03/28 12:23:44  amos
// back to main branch
// Revision 1.36.1.2  2000/03/22 08:49:08  amos
// fix VxWorks warnnings (-Wall)
// Revision 1.36.1.1  2000/01/25 16:35:43  amos
// Duplicate revision
// Revision 1.35.1.1  2000/01/18 15:51:55  amos
// Revision 1.35  1999/10/17 11:26:10  ofer
// bugfix 32053 OSOXFInitEpilog call taskDelay(2)
// so main will context switch and allow the Target Server to return
// its status
// Revision 1.34  1999/10/05 14:05:31  ofer
// VxOs.cpp hold a GLOBAl variable that calcalute during
// compilation time the offset of "status" field under WIND_TCB
// ( in other words it allows theTornadoIDE.dll to read the task status)
// Revision 1.33  1999/07/29 10:36:52  amos
// support generation of events from interupt handler (VxWorks)
// Revision 1.32  1999/07/28 16:24:15  amos
// add GEN_ISR for generate of interapts in VxWorks
// Revision 1.31  1999/03/11 15:54:09  amos
// Revision 1.30.1.2  1999/03/11 15:25:59  amos
// add semaphores to the OXF
// Revision 1.30.1.1  1999/02/16 12:53:09  amos
// Duplicate revision
// Revision 1.29  1999/02/16 12:06:15  beery
// adjust to endMyThread vs. endOtherThread
// Revision 1.28  1999/02/16 11:11:13  beery
// unify the call to end thread to go through endMyThread and endOtherThread
// Revision 1.27  1999/02/10 15:09:38  amos
// vxThread constructor, fix of task name
// Revision 1.26  1999/02/09 16:37:47  amos
// change the getMessageList back to OMList
// add new operation on OMQueue - getInverseQueue()
// Revision 1.25  1999/02/03 12:38:34  amos
// back to main branch
// Revision 1.24.1.2  1999/02/03 12:33:09  amos
// convert OMOSMessageQueue from sizeless (OMList) to size controled (OMQueue)
// Revision 1.24.1.1  1999/02/01 16:19:46  amos
// Duplicate revision
// Revision 1.23.1.2  1999/02/01 11:24:06  amos
// chage time from long to unsigned long
// Revision 1.23  1999/01/26 08:44:49  amos
// back to main branch
// Revision 1.22.1.2  1999/01/25 16:59:21  amos
// merge
// Revision 1.22  1999/01/25 07:25:49  beery
// reference an handle instead of the hThread itself
// Revision 1.21  1999/01/24 16:04:24  beery
// resolve compile error due to inappropiate casts
// Revision 1.20.1.2  1999/01/24 14:52:51  amos
// merge
// Revision 1.20  1999/01/21 10:32:44  beery
// Revision 1.19.1.3  1999/01/05 14:58:17  beery
// Revision 1.19.1.2  1999/01/03 12:56:05  beery
// Revision 1.19.1.1  1998/09/09 13:12:40  beery
// Revision 1.19.2.3  1999/01/19 12:24:22  amos
// setting the message queue size from OMThread constructor
// Revision 1.19.2.2  1999/01/19 09:05:26  amos
// user control over thread name, priority and stack size 
// via parameters in OMThread constructor
// Revision 1.19.2.1  1998/09/09 13:12:40  amos
// Duplicate revision
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
// os.h ntos.cpp/h VxOs.cpp/h sol2os.cpp/h
// Revision 1.14  1997/06/09 07:50:12  ofer
// Full support for trace and animation
// added OSEndApplication (vxos.cpp/h)
// Revision 1.13  1997/04/30 11:03:30  ofer
// If local host name is equal to the current host name 
// we use the INADDR_LOOPBACK adderss
// sol2os.cpp ntos.cpp VxOS.cpp
// Revision 1.12  1997/04/29 09:08:56  ofer
// eventFlag for suspended thread is deleted after signal;
// vxos.cpp
// Revision 1.11  1997/04/17 05:24:56  ofer
// Support for trace/animation under VxWorks
// the low level WAS NOT debugged yet !!!!
// VxOS.cpp/h
// Revision 1.10  1997/04/09 10:19:54  ofer
// update VxOS.cpp/h interfaces so INSTRUMENTED
// version can be compiled
// I have to implement the Socket/ConnectionPort and
// MessageQueue info in order to work with Tracer/Animator
// VxOS.cpp/h
// Revision 1.9  1997/03/05 13:59:18  ofer
// Implemet creation of suspended VxThread by using Event Flag
// We should use the TaskInit/taskActivate system calls but
// somhow it does not work so for the time beeing it is implemented
// with EventFlag
// VxOs.cpp/h
// Revision 1.8  1997/02/17 14:16:44  ofer
// 1) Move some of the inline functions to the VxOs.cpp file
// 2) correct VxOsMessageQueue::isEmpty and now simple
// programs are working
// VxOs.cpp/h
// 
// Revision 1.7  1997/02/17 09:25:26  ofer
// return 0 on not implemented methods
// Revision 1.6  1997/01/29 09:01:34  ofer
// using native os call to determine if MessageQ is empty
// state --> m_State
// Revision 1.5  1997/01/28 12:00:40  ofer
// member variables "time" changed to "m_Time"
// remove signal method from vxOsMessageQueue
// VxOsMessageQueue::getNext/First?Current print "Not Implemented"
// timer.cpp/h ntos.cpp/h VxOs.cpp/h
// Revision 1.4  1997/01/27 13:55:16  ofer
// No need for OMRegisterThread and OMGetCurrentThread global
// functions in VxOs.cpp
// Revision 1.3  1997/01/27 11:44:16  ofer
// Trying to support vxWorks
// for the time beeing we support compilation of NON instumented
// version (for vxWorks.
// we assume the WE DO NOT use iostream for vxWorks
// Revision 1.2  1996/11/25 08:10:04  erang
//
