//	file name   :	$Source    D:\Rhapsody\Share\Langcpp\oxf
//	file version:	$Revision: 1.24 $
//
//	purpose:	 	QNXOS implementations
//
//	author(s):
//	date started:
//	date changed:	$Date: 2007/03/11 08:42:53 $
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
//|                           QNXOS.cpp                           |
// ---------------------------------------------------------------

// Rhapsody framework includes
#include "QNXOS.h"
#include "oxf.h"
#include "timer.h"
#include "omthread.h"

#include <string.h>
#include <ctype.h>

#ifdef _OMINSTRUMENT
// Rhapsody animation framework includes
#include <aom/AnimServices.h>
#include <omcom/omsdata.h>

#include <stdio.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <sys/utsname.h>

#endif // _OMINSTRUMENT

#include <rpc/rpc.h>

// timer
#include <time.h>
#include <sys/netmgr.h>
#include <sys/neutrino.h>
#include <sys/syspage.h>

OMBoolean QNXTimer::active = true;

const Rhp_int32_t OMOSThread::DefaultStackSize        = DEFAULT_STACK;
const Rhp_int32_t OMOSThread::DefaultMessageQueueSize = DEFAULT_MQ_SIZE;
const Rhp_int32_t OMOSThread::DefaultThreadPriority   = PRIO_NORMAL;
const Rhp_int32_t SOCKET_PORT = 6423;

//Variable to store the Wrapper Thread ID
pthread_t MainThreadId;

OMOSFactory* OMOSFactory::instance() {
	static QNXOSFactory theFactory;
	return &theFactory;
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
#ifdef OM_POSIX_QUEUES
	// _exit() perform all the cleanup when internal queues are used

#ifdef _OMINSTRUMENT
	AnimServices::cleanupOnEndApplication();
#endif // _OMINSTRUMENT

	OMThread* currentThread = OMThread::cleanupAllThreads();
	pthread_t self_id;
	self_id = pthread_self();
	if (self_id != MainThreadId) {
		pthread_cancel(MainThreadId);
	}

	//clean up message queues - valid only for POSIX queues.
	QNXMessageQueue::cleanUpMessageQueues();

#endif //OM_POSIX_QUEUES

	_exit(errorCode);
}

///////////////////////////////////////////////////////////////////////////////
///                             QNXOSFactory Class                          ///
///////////////////////////////////////////////////////////////////////////////

OMOSMessageQueue* QNXOSFactory::createOMOSMessageQueue ( const OMBoolean shouldGrow , 
														const Rhp_int32_t messageQueueSize ) const {
#ifdef OM_POSIX_QUEUES
	return (OMOSMessageQueue*)new QNXMessageQueue(messageQueueSize);
#else
	return (OMOSMessageQueue*)new QNXMessageQueue(shouldGrow, messageQueueSize);
#endif
}


OMOSConnectionPort* QNXOSFactory::createOMOSConnectionPort(void) const {
#ifdef _OMINSTRUMENT
	  return (OMOSConnectionPort*)new QNXConnectionPort();
#else
	  return NULL;
#endif
}

OMOSEventFlag* QNXOSFactory::createOMOSEventFlag(void) const {
	return (OMOSEventFlag *)new QNXEventFlag();
}

OMOSThread* QNXOSFactory::createOMOSThread ( void (*tfunc)(void*),
                                             void *param,
                                             const Rhp_const_char_pt threadName,
                                             const Rhp_int32_t stackSize ) const {
    return (OMOSThread*)new QNXThread(tfunc, param, threadName, stackSize);
}

OMOSThread* QNXOSFactory::createOMOSWrapperThread(void* osHandle) const {
    if (NULL == osHandle) {
        osHandle = getCurrentThreadHandle();
    }
    return (OMOSThread*)new QNXThread(osHandle);
}

OMOSMutex* QNXOSFactory::createOMOSMutex(void) const {
	return (OMOSMutex*)new QNXMutex();
}

OMOSTimer* QNXOSFactory::createOMOSTickTimer ( const timeUnit tim,
                                               void (*cbkfunc)(void*),
                                               void *param ) const {
   	return (OMOSTimer*)new QNXTimer(tim, cbkfunc, param);   // TickTimer for real time
}

OMOSTimer* QNXOSFactory::createOMOSIdleTimer ( void (*cbkfunc)(void*),
                                               void *param ) const {
   	return (OMOSTimer*)new QNXTimer(cbkfunc, param);   // Idle timer for simulated time
}

OMOSSemaphore* QNXOSFactory::createOMOSSemaphore ( const Rhp_uint64_t semFlags,
                                                   const Rhp_uint64_t initialCount,
                                                   const Rhp_uint64_t maxCount,
                                                   const Rhp_const_char_pt name ) const {
	return (OMOSSemaphore*) new QNXSemaphore(semFlags, initialCount);
}

OMBoolean QNXOSFactory::waitOnThread ( void* osHandle,
                                       const timeUnit ms ) const {
	return FALSE;
}

void* QNXOSFactory::getCurrentThreadHandle(void) const {
	return reinterpret_cast<void*>(pthread_self());
}

void QNXOSFactory::delayCurrentThread ( const timeUnit ms ) const {
	struct timespec tms;
	tms.tv_sec = ms/1000;
	tms.tv_nsec = (ms % 1000) * 1000000;
	if (ms > 0) {
		nanosleep(&tms,NULL);
	} else {
		sched_yield();
	}
}


///////////////////////////////////////////////////////////////////////////////
//                            QNXTimer Class                                ///
///////////////////////////////////////////////////////////////////////////////

extern "C" {
    typedef void*(*FormalThrCreateFunc)(void*);
}

// Tic timer

#define TIC_CODE _PULSE_CODE_MINAVAIL

QNXTimer::QNXTimer ( const timeUnit ptime, void pcbkfunc(void*), void *pparam ):
        m_Time(ptime), cbkfunc(pcbkfunc), param(pparam)
{
    pthread_attr_t tthread_attr;
    struct sched_param s_param;

    pthread_attr_init( &tthread_attr );
    pthread_attr_setstacksize( &tthread_attr, OMOSThread::DefaultStackSize );
    pthread_attr_setdetachstate( &tthread_attr, PTHREAD_CREATE_DETACHED );
    pthread_attr_setinheritsched( &tthread_attr, PTHREAD_EXPLICIT_SCHED );

    s_param.sched_priority = PRIO_NORMAL + 2;
    pthread_attr_setschedparam(&tthread_attr, &s_param);

    pthread_create ( &hThread, /* Handle */
                     &tthread_attr,
                     reinterpret_cast<FormalThrCreateFunc>(bridge),
                     this );
    // Create a thread that runs bridge, passing this as argument
}

// IdleTimer (Simulated Time)
QNXTimer::QNXTimer ( void pcbkfunc(void*), void* pparam ):
    m_Time(0), cbkfunc(pcbkfunc), param(pparam) 
{

    pthread_attr_t tthread_attr;
    struct sched_param s_param;

    pthread_attr_init( &tthread_attr );
    pthread_attr_setstacksize( &tthread_attr, OMOSThread::DefaultStackSize );
    pthread_attr_setdetachstate( &tthread_attr, PTHREAD_CREATE_DETACHED );
    pthread_attr_setinheritsched( &tthread_attr, PTHREAD_INHERIT_SCHED );
    s_param.sched_priority = LowestPriority;
    pthread_attr_setschedparam(&tthread_attr, &s_param);

    pthread_create (&hThread, /* Handle */
                    &tthread_attr,
                    (FormalThrCreateFunc) bridge,
                    this );
    pthread_setname_np(hThread,"TheSimTimer");
}

QNXTimer::~QNXTimer() {
    pthread_cancel(hThread);
}


void* QNXTimer::timerThread(void)
{
    struct sigevent         event;
    struct itimerspec       itime;
    timer_t                 timer_id;
    int                     chid;
    int                     rcvid;
    struct _pulse   		pulse;


    // create a communications channel
    chid = ChannelCreate(0);

    // create an periodic timer
    event.sigev_notify = SIGEV_PULSE;
    event.sigev_coid = ConnectAttach(ND_LOCAL_NODE, 0,
                                    chid,
                                    _NTO_SIDE_CHANNEL, 0);
    event.sigev_priority = getprio(0);
    event.sigev_code = TIC_CODE;
    if (timer_create(CLOCK_REALTIME, &event, &timer_id)){
		OM_NOTIFY_TO_ERROR("ERROR: couldn'd create tic timer ... ending in 5 sec\n");
		sleep(5);
		exit(-1);
    }

    itime.it_value.tv_sec = 0;
    itime.it_value.tv_nsec = 1000000 * m_Time;
    itime.it_interval.tv_sec = 0;
    itime.it_interval.tv_nsec = 1000000 * m_Time;;

    // start
    if (timer_settime(timer_id, 0, &itime, NULL)){
		OM_NOTIFY_TO_ERROR("ERROR: couldn'd start tic timer ... ending in 5 sec\n");
		sleep(5);
		exit(-1);
    }

    pthread_setname_np(hThread,"TheTickTimer");

    do
    {
		if (OMThread::isEndOfProcess()) {
			break;
		}
        rcvid = MsgReceive(chid, &pulse, sizeof(pulse), NULL);
        if (rcvid == 0) { /* we got a pulse */
            if (pulse.code == TIC_CODE) {
                (*cbkfunc)(param);
            }
        }
    }
    while ( active );
}


void* QNXTimer::bridge(void* me) {
    QNXTimer* theTimer = static_cast<QNXTimer*>(me);
    if ( theTimer->m_Time <= 0 ) {
    	theTimer->waitThread();
    }
    else {
    	theTimer->timerThread();
    }
    pthread_exit(0);
    return NULL;
}

void QNXTimer::waitThread(void) {
    struct timespec tms;

    tms.tv_sec = 0 ;
    tms.tv_nsec = 5000; // 5 ms in simulated time to give other thread running
    do {
		if (OMThread::isEndOfProcess())
			break;
		nanosleep(&tms, NULL);
        (*cbkfunc)(param);
    }
	while ( active );
}

void QNXTimer::terminate(void) {
    active = false;
}


// adding functions for implementing suspend and resume

void User1handler(const Rhp_int32_t signumber) {
    sigpause( static_cast<Rhp_int32_t>(SIGUSR2) );
}

void User2handler(const Rhp_int32_t signumber) {
    /*DO NOTHING */
}


///////////////////////////////////////////////////////////////////////////////
//                             QNXThread Class                              ///
///////////////////////////////////////////////////////////////////////////////

void QNXThread::preExecFunc(void* me) {
    if ( (static_cast<QNXThread*>(me))->m_SuspEventFlag) {
        (static_cast<QNXThread*>(me))->m_SuspEventFlag->wait();
        /* delete the Eventflag here after receiving */
        QNXEventFlag* tmp = (static_cast<QNXThread*>(me))->m_SuspEventFlag;
        (static_cast<QNXThread*>(me))->m_SuspEventFlag= NULL;
        		delete tmp;
    }
    (static_cast<QNXThread*>(me))->m_ExecFunc( (static_cast<QNXThread*>(me))->m_ExecParam );
}


QNXThread::QNXThread ( void tfunc(void*),
                       void* param,
                       const Rhp_const_char_pt name,
                       const Rhp_int32_t stackSize ) : endOSThreadInDtor(TRUE) {
    isWrapperThread = 0;
    m_SuspEventFlag = new QNXEventFlag();

    m_SuspEventFlag->reset();
    // Create SUSPENDED thread !!!!!!
    m_ExecFunc = tfunc;
    m_ExecParam = param;

    signal(SIGUSR1,User1handler);
    signal(SIGUSR2,User2handler);

    // Set thread attributes prior to thread creation.
    pthread_attr_t tthread_attr;
    pthread_attr_init( &tthread_attr );
    pthread_attr_setstacksize( &tthread_attr, (size_t)stackSize );
    pthread_attr_setdetachstate( &tthread_attr, PTHREAD_CREATE_DETACHED);
    pthread_attr_setinheritsched( &tthread_attr, PTHREAD_INHERIT_SCHED );

    pthread_create ( &hThread, /* Handle */
                     &tthread_attr ,
                     reinterpret_cast<FormalThrCreateFunc>(preExecFunc),
                     static_cast<void*>(this) );
	if (name && strlen(name) > 0)
			pthread_setname_np(hThread,name);

}

QNXThread::QNXThread(void *osThreadId) : endOSThreadInDtor(TRUE) {
    m_SuspEventFlag = NULL;
    hThread = reinterpret_cast<pthread_t>(osThreadId);
    isWrapperThread = 1;
    MainThreadId = hThread;
    pthread_setname_np(hThread,"TheMainThread");

}


QNXThread::~QNXThread(void)	{	//RTOS Independent Method
    if (!isWrapperThread) {
        if (m_SuspEventFlag) {
            delete m_SuspEventFlag;
        }

        if (endOSThreadInDtor) {
            OMOSThread::OMOSThreadEndCallBack theOSThreadEndClb = NULL;
            OMOSHandle* threadHandle = NULL;
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

void QNXThread::setPriority(const Rhp_int32_t aPriority) {
    Rhp_int32_t s_policy;
    struct sched_param s_param;

    pthread_getschedparam( hThread, &s_policy, &s_param );
    s_param.sched_priority = aPriority;
    pthread_setschedparam( hThread, s_policy, &s_param );
}

static const Rhp_uint32_t endThreadResult = 0U;

void QNXThread::endMyThread(void* hThread) {
	pthread_exit( static_cast<void*>(endThreadResult) );
}

void QNXThread::endOtherThread(void* hThread) {
	pthread_cancel( reinterpret_cast<Rhp_uint32_t>(hThread) );
}

void QNXThread::getThreadEndClbk(
	QNXThread::OMOSThreadEndCallBack* clb_p,
	void** arg1_p, OMBoolean onExecuteThread){
	//RTOS Independent Method
    if (onExecuteThread) {
        // asking for a callback to end my own thread
        *clb_p = &endMyThread;
        *arg1_p = (void*)&hThread;
    } else {
        // asking for a callback to end my thread by someone else
        *clb_p  = &endOtherThread;
        // my thread handle
        *arg1_p = (void*)&hThread;
    }
}

void QNXThread::start(void) {
    if(m_SuspEventFlag) {
        m_SuspEventFlag->signal();
    } else {
        resume();
    }
}

void QNXThread::suspend(void) {
    pthread_kill( hThread, static_cast<Rhp_int32_t>(SIGUSR1) );
}

void QNXThread::resume(void)
{
    pthread_kill( hThread, static_cast<Rhp_int32_t>(SIGUSR2) );
}


///////////////////////////////////////////////////////////////////////////////
//                            QNXMutex Class                                ///
///////////////////////////////////////////////////////////////////////////////


QNXMutex::QNXMutex(void) {
    pthread_mutexattr_t attr;
    hMutex = (pthread_mutex_t)PTHREAD_RMUTEX_INITIALIZER;
    (void)pthread_mutex_init( &hMutex, NULL );
}

QNXMutex::~QNXMutex(void) {
    pthread_mutex_destroy(&hMutex); // will destroy the mutex
}

// Allow recursive locking of the mutex by one thread

void QNXMutex::lock(void) {
    pthread_mutex_lock(&hMutex);
}

void QNXMutex::unlock(void) {
    pthread_mutex_unlock(&hMutex);
}


///////////////////////////////////////////////////////////////////////////////
//                           QNXMessageQueue Class                          ///
///////////////////////////////////////////////////////////////////////////////

#ifdef OM_POSIX_QUEUES

Rhp_int32_t QNXMessageQueue::mq_no = 0; //Queue number


QNXMessageQueue::QNXMessageQueue(const Rhp_int32_t messageQueueSize = OMOSThread::DefaultMessageQueueSize): hQNXMQ(-1), pmessage(NULL), m_State(noData) 
{
    struct mq_attr attr;
    while (hQNXMQ == -1) {
        Mq_name();
        attr.mq_maxmsg = messageQueueSize;
        attr.mq_msgsize = sizeof(void*);
        hQNXMQ = mq_open(name, O_RDWR | O_CREAT | O_NONBLOCK, 0, &attr);
    }
}

QNXMessageQueue::~QNXMessageQueue(void) {
    if (hQNXMQ) {
        mq_unlink(name);
        hQNXMQ = 0;
    }
}


void QNXMessageQueue::cleanUpMessageQueues(void) {
    Rhp_char_t msg_name[50];
    for (Rhp_int32_t i=0; i<QNXMessageQueue::mq_no; i++) {
        sprintf(msg_name,"MQ%d",i);
        mq_unlink(msg_name);
    }
}

void* QNXMessageQueue::get(void) {
    struct mq_attr attr;
    void* m;

    if (m_State == dataReady) {
        m = pmessage;
        m_State = noData;
    } else {
        if (!isEmpty()) {
            mq_getattr(hQNXMQ, &attr);
            attr.mq_flags = O_NONBLOCK;
            mq_setattr(hQNXMQ, &attr, NULL);
            mq_receive(hQNXMQ, reinterpret_cast<Rhp_char_pt>(&m), sizeof(m), NULL);
        } else {
            return NULL;
        }
    }
    return m;
}


OMBoolean QNXMessageQueue::put(void* aMessage, const OMBoolean fromISR) {
	struct mq_attr attr;
	OMBoolean status;

	static void* NULL_VAL = NULL;
	if (NULL == aMessage) {
		 aMessage = NULL_VAL;
	}

	mq_getattr(hQNXMQ, &attr);
	attr.mq_flags = 0;
	Rhp_int32_t priority = 10;

	if (fromISR) {
		attr.mq_flags = O_NONBLOCK;
		priority = MQ_PRIO_MAX;
	}

	mq_setattr(hQNXMQ, &attr, NULL);

	Rhp_int32_t	retr=1;
	retr = mq_send(hQNXMQ, static_cast<Rhp_char_t>(&aMessage), sizeof(aMessage), priority );

	if (retr != -1) {
		status = TRUE;
	} else {
		status = FALSE;
	}
	return status;
}

void QNXMessageQueue::pend(void) {
	struct mq_attr attr;
	mq_attr oldattr;

	if (isEmpty()) {
		void* m;

		mq_getattr(hQNXMQ, &attr);
		attr.mq_flags = 0;
		mq_setattr(hQNXMQ, &attr, NULL);
		mq_receive(hQNXMQ, reinterpret_cast<Rhp_char_pt>(&m), sizeof(m), NULL);
		m_State = dataReady;
		pmessage = m;
	}
}

void QNXMessageQueue::Mq_name(void) {
	sprintf(name, "MQ%d", QNXMessageQueue::mq_no);
	++QNXMessageQueue::mq_no;
}

Rhp_int32_t QNXMessageQueue::isEmpty(void) const {
	struct mq_attr attr;
	Rhp_int32_t status;

	mq_getattr(hQNXMQ, &attr );
	if ( (noData == m_State) && (0 == attr.mq_curmsgs) ) {
		status = 1;
	} else {
		status = 0;
	}
	return status;
}

void QNXMessageQueue::getMessageList( OMListType& aList ) {
    aList.removeAll();
    struct mq_attr attr;
    Rhp_int32_t num_msgs;
    void* m;
    OMListType lst;

    mq_getattr(hQNXMQ, &attr );
    	num_msgs = attr.mq_curmsgs;

    for (Rhp_int32_t i=0; i<num_msgs; i++ ) {
        m = get();
        lst.add(m);
    }

    for (Rhp_int32_t i=0,j=1; i<num_msgs; i++, j++ )	{
        m = lst.getAt(num_msgs-j);
        aList.add(m);			// Since the list has to be filled in reverse order
        m = lst.getAt(i);
        put(m,FALSE);
    }
}

OMBoolean QNXMessageQueue::isFull(void) const {

    struct mq_attr attr;
    if (isEmpty()) {
        return FALSE;
    }

    	mq_getattr(hQNXMQ, &attr );
    if (attr.mq_curmsgs < attr.mq_maxmsg) {
        return FALSE;
    } else {
        return TRUE;
    }
}
#else // not POSIX message queues implementation.



void* QNXMessageQueue::get(void) {
    void* m;
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


void QNXMessageQueue::pend(void) {
    if (isEmpty())  {
        m_QueueEventFlag.wait();
    }
}

void QNXMessageQueue::cleanUpMessageQueues(void) {
}

OMBoolean QNXMessageQueue::put ( void* aMessage, const OMBoolean /* fromISR */ ) {
    m_QueueMutex.lock();
    Rhp_int32_t wasEmpty = isEmpty();

    OMBoolean res = m_theQueue.put(aMessage);

    if (wasEmpty) {
        m_QueueEventFlag.signal();
    }
    m_QueueMutex.unlock();

    return res;
}

void QNXMessageQueue::getMessageList(OMListType& aList) {
    // Copy to it all the messages that I have
    m_theQueue.getInverseQueue(aList);
}
#endif

///////////////////////////////////////////////////////////////////////////////
//                            QNXEventFlag Class                            ///
///////////////////////////////////////////////////////////////////////////////


QNXEventFlag::QNXEventFlag(void) {
    sem_init (&hEventFlag, 0, 0);
}

void QNXEventFlag::signal(void) {
    (void)sem_post(&hEventFlag);
}

void QNXEventFlag::reset(void) {
    while (sem_trywait(&hEventFlag) == 0)
        ;
}

void QNXEventFlag::wait(const Rhp_int32_t tminms ) {
	if ( -1 == tminms ) {
  		(void)sem_wait(&hEventFlag);
	} else {
		// POSIX semaphores do not have timeouts.
		// To implement timeouts we loop on a try without wait
		// then sleep 50 ms until either semaphore is open ( ret value is 0)
		// or time is up.
        struct timespec tms;
		if ( 0 != sem_trywait(&hEventFlag)) {
			timeUnit sleepTimeInterval = 10;					//50		//05-03-2001

			Rhp_int32_t count = tminms / (Rhp_int32_t)sleepTimeInterval;
			Rhp_int32_t i = 0;
			for (i = 1; i < count ; i++) {
				tms.tv_sec = sleepTimeInterval/1000 ;
				tms.tv_nsec = (sleepTimeInterval % 1000)* 1000000;
				nanosleep(&tms, NULL);

				if (0 == sem_trywait(&hEventFlag)) {
					break;
				}
			}
		}
	}
}


///////////////////////////////////////////////////////////////////////////////
//                          QNXSemaphore Class                              ///
///////////////////////////////////////////////////////////////////////////////
QNXSemaphore::QNXSemaphore( const Rhp_uint64_t semFlags,
                            const Rhp_uint64_t initialCount ) : m_ok(FALSE) {
	m_ok = (sem_init(&m_sem, static_cast<Rhp_int32_t>(semFlags), initialCount) == 0);
}

//////////
QNXSemaphore::~QNXSemaphore(void) {
	sem_destroy(&m_sem);
}

/////////
void QNXSemaphore::signal(void) {
	sem_post(&m_sem);
}

////////
OMBoolean QNXSemaphore::wait ( const Rhp_int64_t timeout ) {
    OMBoolean status = false;
    if (m_ok) {
        if (timeout == 0) {
            status = (sem_trywait(&m_sem) == 0);
        } else {
            status = (sem_wait(&m_sem) == 0);
        }
    }
    return status;
}



#ifdef _OMINSTRUMENT
///////////////////////////////////////////////////////////////////////////////
//                             QNXSocket Class                              ///
///////////////////////////////////////////////////////////////////////////////

QNXSocket::QNXSocket(void) {
	theSock = 0;
}

QNXSocket::~QNXSocket(void) {
	if (theSock != 0) {
		(void)close(theSock);
	}
}

#ifndef SOCKET_ERROR
#define SOCKET_ERROR -1
#endif // SOCKET_ERROR

Rhp_int32_t QNXSocket::Create( const Rhp_const_char_pt SocketAddress /*= NULL */,
                               const Rhp_uint32_t nSocketPort /* = 0*/) {
	static struct sockaddr_in	addr;
	struct protoent	*protocol;
	Rhp_int32_t	proto;
	struct hostent* host = NULL;
	Rhp_const_char_pt proto_name = "tcp";
	Rhp_char_t hostName[128];
	Rhp_const_char_pt address = SocketAddress;
	Rhp_uint32_t port = nSocketPort;
	Rhp_int32_t status = 0;

	if ( port == 0U ) {
		port = SOCKET_PORT;
	}

	addr.sin_family = AF_INET;
	if ((protocol = getprotobyname(proto_name)) == (struct protoent*) 0) {
		// supported by test Prog
		fprintf(stderr,"Could not get the AF_INET protocol\n");
	} else {
		proto = protocol->p_proto;

    // use uname in order to get the local host name (nodename)
		struct utsname buf;
		uname(&buf);
		strcpy (hostName, buf.nodename);

		if (NULL != address) {
			if (!strcmp(hostName, address)) {
				address = NULL;
			} else {
				(void)strcpy(hostName, address);
				if ((host = gethostbyname(hostName)) == (struct hostent *) 0) {
					fprintf(stderr,"Could not get the address of host '%s'\n", hostName);
					return 0;
				}
			}
		}

#ifdef unix
		endprotoent();
#endif // unix

		addr.sin_port = htons(port);

		if (NULL == SocketAddress) {
			addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
		} else {
			addr.sin_addr.s_addr = *((Rhp_uint32_t *) host->h_addr);
		}

		if ((theSock = socket(AF_INET, SOCK_STREAM, proto)) == -1) {
			fprintf(stderr,"Could not create socket\n");
			theSock = 0;
		} else {
			Rhp_int32_t rvStat;
			while ((rvStat = connect(theSock, (struct sockaddr *) &addr, sizeof(addr))) == SOCKET_ERROR
				&& (errno == EINTR));

			if (SOCKET_ERROR == rvStat) {
				fprintf(stderr,"Could not connect to server at %s port %d\n Error No. : %d\n",
				    hostName,(Rhp_int32_t)nSocketPort,errno);
				(void)close(theSock);
			} else {
				status = 1;
			}
		}
	}
	return status;
}

Rhp_int32_t QNXSocket::Send ( const Rhp_const_char_pt lpBuf,
                              const Rhp_int32_t nBufLen ) {
	Rhp_int32_t bytes_writ = 0;
	Rhp_int32_t n;

	while (bytes_writ < nBufLen) {
		n = send(theSock, lpBuf + bytes_writ, nBufLen - bytes_writ, 0);
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

Rhp_int32_t QNXSocket::Receive ( Rhp_char_pt lpBuf,
                                 const Rhp_int32_t nBufLen ) {
	Rhp_int32_t bytes_read = 0;
	Rhp_int32_t n;

	while (bytes_read < nBufLen) {
		n = recv(theSock, lpBuf + bytes_read, nBufLen - bytes_read, 0);
		if (SOCKET_ERROR == n) {
			if (errno == EINTR) {
				continue;
			} else {
				return -1;
			}
		} else {
			if ( 0 == n )	{
				//connection closed
				return -1;
			}
		}

		bytes_read += n;
	}
	return bytes_read;
}

///////////////////////////////////////////////////////////////////////////////
//                          QNXConnectionPort Class                         ///
///////////////////////////////////////////////////////////////////////////////


Rhp_char_pt QNXConnectionPort::m_Buf = NULL;
Rhp_int32_t QNXConnectionPort::m_BufSize = 0;

QNXConnectionPort::QNXConnectionPort(void) {
	m_Connected = 0;
	m_dispatchfunc = NULL;
	m_ConnectionThread = NULL;
	m_ShouldWaitForAck = 1;
	m_NumberOfMessagesBetweenAck = 0;
	m_AckEventFlag.reset();
}

QNXConnectionPort::~QNXConnectionPort(void) {
	m_Socket.Close();
	if (m_ConnectionThread) {
		void* threadOSHandle = OMOSFactory::instance()->getCurrentThreadHandle();
		if (threadOSHandle != m_ConnectionThread->getOsHandle()) {
			delete m_ConnectionThread;
			m_ConnectionThread = NULL;
		}
	}
	// I assume that we will have only one connection port
	// so I can free the data for m_Buf but if it is not the case
	// it does not matter ( the readFromSockLoop will allocate it )
	if (m_Buf != NULL) {
		delete[] m_Buf;
	}

	m_BufSize = 0;
}

void QNXConnectionPort::readFromSockLoop(QNXConnectionPort* me) {
	char lenStr[MAX_LEN_STR+1];
	Rhp_int32_t len;
	Rhp_int32_t rv;
	for (;;) {
		rv = me->m_Socket.Receive(lenStr,MAX_LEN_STR);
		if (rv == -1) {
			OM_NOTIFY_TO_ERROR("Terminating application\n");
			exit(0);
		}
		lenStr[MAX_LEN_STR] = '\0';

		if (sscanf(lenStr,"%d",&len) == 1) {
			if (len > m_BufSize ) {
				m_BufSize = 1000 + len;
				if (m_Buf != NULL) {
					delete[] m_Buf;
				}
				m_Buf = new char[m_BufSize];
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
			// len is not used by OMSData but we need to change
			// the interface so we will use the length of the data
			// and not assume that the string is null terminated

			// if socket thread is doing some work that may send
			// messages we do not want to Block the Send by waiting for
			// acknowledgement since the thread cannot handle the acknowledegment
			// ( since the thread is self locked)
			me->m_ShouldWaitForAck = 0;
			me->m_AckEventFlag.signal();
			me->m_dispatchfunc(OMSData::string2OMSData(m_Buf));
			me->m_ShouldWaitForAck = 1;
		}
	} //for(;;)
}

Rhp_int32_t QNXConnectionPort::Connect ( const Rhp_const_char_pt SocketAddress /*= NULL*/,
                                         const Rhp_uint32_t aSocketPort /*= 0*/) {
	if (NULL == m_dispatchfunc) {
		fprintf(stderr,"QNXConnectionPort::SetDispatcher should be called before QNXConnectionPort::Connect()\n");
		return 0;
	}

	if ( 0 == m_Connected ) {
		m_Connected = m_Socket.Create(SocketAddress,aSocketPort);
	}

	if (0 == m_Connected) {
		return 0;
	}

	// Connection established
	// invoking thread to recieve messages from the socket

	m_ConnectionThread = new QNXThread((void (*)(void*))readFromSockLoop,(void*)this,"RhpSock");
	m_ConnectionThread->start();
	return m_Connected;
}

Rhp_int32_t QNXConnectionPort::Send(OMSData* aMessage) {
	Rhp_int32_t rv = 0;
	m_SendMutex.lock();
	if (m_Connected) {
		Rhp_char_t lenStr[MAX_LEN_STR+1];
		(void)sprintf(lenStr, "%d", aMessage->getLength());
		//		// communcation check
		//		if (NULL == csendFile) {
		//			csendFile = new ofstream("send.dat");
		//		}
		//		*csendFile << "buflen=" << m->getLength() << "data="<< m->getRawData()<< "\n" << flush;

		rv = m_Socket.Send(lenStr, MAX_LEN_STR);
		if (rv > 0) {
			rv = m_Socket.Send( aMessage->getRawData(),
			                    aMessage->getLength() );
		}

		if (m_ShouldWaitForAck) {
			const Rhp_int32_t maxNumOfMessagesBetweenAck = 127; // MUST match the number in rhapsody
			if (maxNumOfMessagesBetweenAck > 0)	{
				m_NumberOfMessagesBetweenAck++;

				if (m_NumberOfMessagesBetweenAck >= maxNumOfMessagesBetweenAck)	{
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
