//
//  file name   :   $Source: R:/StmOO/Master/cg/LangCpp/oxf/rcs/NuOS.cpp $
//  file version:   $Revision: 1.1		07/08/2001
//							 : 1.2		30/11/2001
//							 : 1.3		18/12/2001	
//							 : 1.4		06/04/2002 	
//
//  purpose:        Nucleus PLUS PPC adaptor for Rhapsody

//
//  author(s):      
//                  
//  date started:   
//  date changed:   
//  last change by: 
//
//	Licensed Materials - Property of IBM
//	(c) Copyright IBM Corporation 2000, 2016. All Rights Reserved.
//
//  Note to U.S. Government Users Restricted Rights:  
//  Use, duplication or disclosure restricted by GSA ADP Schedule 
//  Contract with IBM Corp.
//

#if ((!defined lint) && (!defined OM_NO_RCS_ID))
static char *rcsid="$Id: NuOS.cpp 1.15 2007/03/11 08:42:41 ilgiga Exp $";
#endif // lint

#include <oxf/oxf.h>
#include <oxf/os.h>
#include <oxf/nuos.h>
#include <oxf/timer.h> 
#include <oxf/omthread.h>
#include <oxf/omreactive.h>
#include <oxf/omqueue.h>
#include <oxf/event.h>
#include <oxf/HdlCls.h>

#ifdef _OMINSTRUMENT
#include <aom/AnimServices.h>
#include <omcom/omsdata.h>
#endif // _OMINSTRUMENT

extern "C" {

#include <nucleus.h>
#include <qu_defs.h>
extern NU_MEMORY_POOL System_Memory;

}

//
// Define the 'new' operator for C++ to use the Nucleus PLUS memory management
// functions. THIS IS NOT OPTIONAL!
//
void *operator new(size_t size)
{
	void *new_mem = NULL;
  
	if(size == 0) {
		size = 1;
	}
	(void)NU_Allocate_Memory(&System_Memory, &new_mem, size, NU_NO_SUSPEND);
	memset( new_mem, 0, size );
	return new_mem;
}

//
// Define the 'delete' operator for C++ to use the Nucleus PLUS memory management
// functions. THIS IS NOT OPTIONAL!
//
void operator delete(void *p)
{
	if(p) {
		NU_Deallocate_Memory( p );
	}
}

////////////////////////////////////////////////////////////////////////////
//
////						NuOSFactory									////	
//
////////////////////////////////////////////////////////////////////////////

//
// theOSFactory:
//
// The NuOSFactory is implemented as a Singleton.  The first time theOSFactory()
// is called to get an instance of the factory, the single instance of the
// NuOSFactory is created along with returning a pointer to the factory.
//


const Rhp_int32_t OMOSThread::DefaultStackSize = DEFAULT_STACK;
const Rhp_int32_t OMOSThread::DefaultMessageQueueSize = MQ_DEFAULT_SIZE;
const Rhp_int32_t OMOSThread::DefaultThreadPriority = PRIORITY_NORMAL;

OMOSFactory* OMOSFactory::instance()
{

	static NuOSFactory theFactory;
	return &theFactory;
}

static void doCloseHandle(void* hThreadPtr)
{
	NU_TASK *hThread = (NU_TASK *)hThreadPtr;
    if (hThread == OMOSFactory::instance()->getCurrentThreadHandle())
		NU_Terminate_Task(hThread);			
	else
		NU_Delete_Task(hThread);
	delete hThread;

};


void OMOS::initEpilog()
{
	(void)OMHandleCloser::instance(doCloseHandle)->startBehavior();
}


void OMOS::endProlog()
{
	//nothing to do
}


//
// createOMOSThread:
//
// Create and return a pointer to an OMOSThread.
//
OMOSThread* NuOSFactory::createOMOSThread(void (*tfunc)(void *), void *param, 
					  const Rhp_const_char_pt threadName,
					  const Rhp_int32_t stackSize)	 const
{
	return (OMOSThread*)new NuThread(tfunc, param, threadName, stackSize);
}


//
// createOMOSMessageQueue:
//
// Create and return a pointer to an OMOSMessageQueue.
//
OMOSMessageQueue* NuOSFactory::createOMOSMessageQueue(const OMBoolean shouldGrow, const Rhp_int32_t messageQueueSize) const	
{
	return (OMOSMessageQueue*)new NuOSMessageQueue( shouldGrow, messageQueueSize);
}


//
// createOMOSEventFlag:
//
// Create and return a pointer to an OMOSEventFlag.
//
OMOSEventFlag* NuOSFactory::createOMOSEventFlag(void) const
{
	return (OMOSEventFlag *)new NuOSEventFlag();
}


//
// createOMOSWrapperThread:
//
// Create and return a pointer to an OMOSThread, wrapping an existing thread.
//
OMOSThread* NuOSFactory::createOMOSWrapperThread(void* osHandle) const
{
	if (NULL == osHandle)
		osHandle = getCurrentThreadHandle();
	return (OMOSThread*)new NuThread(osHandle);
}

	
//
// createOMOSConnectionPort:
//
// Create and return a pointer to an OMOSConnectionPort (Instrumented Code Only)
//
OMOSConnectionPort* NuOSFactory::createOMOSConnectionPort(void) const
{
#ifdef _OMINSTRUMENT
	return (OMOSConnectionPort*)new NuConnectionPort();
#else
	return NULL;
#endif // _OMINSTRUMENT
}


//
// createOMOSSemaphore:
//
// Create and return a pointer to an OMOSSemaphore
//
OMOSSemaphore* NuOSFactory::createOMOSSemaphore(const Rhp_uint64_t semFlags, const Rhp_uint64_t initialCount, const Rhp_uint64_t maxCount, const Rhp_const_char_pt name) const	
{
	return (OMOSSemaphore*)new NuOSSemaphore(semFlags, initialCount, maxCount, name);
}


//
// createOMOSMutex:
//
// Create and return a pointer to an OMOSMutex.
//
OMOSMutex* NuOSFactory::createOMOSMutex(void) const
{
	return (OMOSMutex*)new NuMutex();
}


//
// createOMOSTickTimer:
//
// Create and return a pointer to an OMOSTimer tied to a tick for real-time.
//
OMOSTimer* NuOSFactory::createOMOSTickTimer(const timeUnit tim, void (*cbkfunc)(void*), void *param) const
{
	return (OMOSTimer*)new NuTimer(tim, cbkfunc, param); // TickTimer for real time
}


//
// createOMOSIdleTimer:
//
// Create and return a pointer to an OMOSTimer tied to an idle task for
// simulated time.
//
OMOSTimer* NuOSFactory::createOMOSIdleTimer(void (*cbkfunc)(void*), void *param) const
{
	return (OMOSTimer*)new NuTimer(cbkfunc, param); // Idle timer for simulated time
}


//
// getCurrentThreadHandle:
//
// Return a pointer to the current thread.
//
void* NuOSFactory::getCurrentThreadHandle(void) const
{
	return (void *)NU_Current_Task_Pointer();
}


//
// delayCurrentThread:
//
// Delay the current thread for the specified number of milli-seconds.  Convert
// the ms value to a tick value using the clock rate.
//
void NuOSFactory::delayCurrentThread(const timeUnit ms) const
{
	if (ms > 0) {
		UNSIGNED ticks = NUOS_CLOCK_RATE * ms / 1000;
		// handle case where (NUOS_CLOCK_RATE * ms) < 1000
		if (ticks == 0) {
			ticks = 1;
		}
		NU_Sleep(ticks);
	}
}


//
// OSEndApplication:
//
// If the application is terminated, restore the system to its original state.
//



void OMOS::endApplication(const Rhp_int32_t errorCode)
{
	//The following variables are added for OSEndApplication using NUcleus API's 
	//instead of cleanupAllThreads()
	   
	NU_TASK *Pointer_Array[50];
	NU_TASK *Current_Task = NULL;
	UNSIGNED number;
	VOID *stack;
	char *name;
    int count; 
	
	UNSIGNED total_tasks = NU_Established_Tasks();
    
#ifdef _OMINSTRUMENT
	AnimServices::notifyEndApplication(true);
#endif // _OMINSTRUMENT

	OMThread::setEndOfProcess(true);
  	total_tasks = total_tasks  + 1;
     
	Current_Task=NU_Current_Task_Pointer(); //We get the current task pointer
    
	number = NU_Task_Pointers(&Pointer_Array[0],50);//Get the Pointers of Established task 
	for(count=0;count < number; count++)
	{
		DATA_ELEMENT task_status ;
		UNSIGNED scheduled_count ;
		OPTION priority ;
		OPTION preempt ;
		UNSIGNED time_slice ;
		UNSIGNED stack_size ;
		UNSIGNED minimum_stack ;
		NU_Task_Information (Pointer_Array[count],
							name,
							&task_status,
							&scheduled_count,
							&priority,
							&preempt,
							&time_slice,
							&stack,
							&stack_size,
							&minimum_stack);//get the stack of the established task
		if( Current_Task == Pointer_Array[count] )
	    {
            
			continue;
		}
		else 
		{
			NU_Terminate_Task(Pointer_Array[count]); //terminate the task before deleting the Task
			NU_Delete_Task(Pointer_Array[count]); //delete the task
			delete stack;  //delete the stack maintained by the task
			               // this is done as NU_Delete_Task only removes the task from the table it maintains
                           //Hence we have to explicitly delete the stack allocated by eack task 
		}
	}
	
	
#ifdef _OMINSTRUMENT
	AnimServices::cleanupOnEndApplication();
#endif // _OMINSTRUMENT

	//CleanupAllThreads was removed from the code instead the 
	//Nucleus APIs were used to delete all the Threads
	exit( errorCode );
}



////////////////////////////////////////////////////////////////////////////
//
//								NuTimer									////
//
////////////////////////////////////////////////////////////////////////////

//
// Constructor:
//
// Create a tick timer with a period of "ptime" (ms).  This will create a thread
// that will call "pcbkfunc" every period.  "pparam" will be passed to "pcbkfunc"
// when "pcbkfunc" is called.  The timer thread runs with high priority to ensure
// the timing of reactive objects is accurate.  This timer is used for real-time.
//
NuTimer::NuTimer(long ptime, void pcbkfunc(void *), void *pparam)
: m_Time(ptime), cbkfunc(pcbkfunc), param(pparam)
{
	ticks = NUOS_CLOCK_RATE * m_Time / 1000;
	if (ticks == 0)
		ticks = 1;
	hThread = new (NU_TASK);
	threadStack = new (unsigned char[SMALL_STACK]);
	NU_Create_Task(hThread,                                // task record (must be supplied)
		"tcktimr",                              // task name
		(void (*)(unsigned long, void*))bridge, // actual task
		1,                                      // argc: 1 argument
		(void *)this,                           // argv: pass this pointer
		threadStack,                            // begining of the stack for this task
		SMALL_STACK,                            // task's stack size
		PRIORITY_HIGH,                          // self explanatory
		0,                                      // disable time slicing
		NU_PREEMPT,                             // preembtable by higher priority task
		NU_START);                              // start already
}

//
// Constructor:
//
// Create an idle timer.  This will create a thread that will call "pcbkfunc"
// constantly at a low priority.  "pparam" will be passed to "pcbkfunc" when
// "pcbkfunc" is called.  The timer thread will run in the background and has a
// low priority.  Higher priority tasks will preempt this thread.  This timer
// is used for simulated time.
//
NuTimer::NuTimer(void pcbkfunc(void *), void *pparam)
: m_Time(0), cbkfunc(pcbkfunc), param(pparam), ticks(0)
{
	hThread = new (NU_TASK);
	threadStack = new unsigned char[SMALL_STACK];
	NU_Create_Task(hThread,                                // task record (must be supplied)
		"idltimr",                              // task name
		(void (*)(unsigned long, void*))bridge, // actual task
		1,                                      // argc: 1 argument
		(void *)this,                           // argv: pass this pointer
		threadStack,                            // begining of the stack for this task
		SMALL_STACK,                            // task's stack size
		PRIORITY_LOW,                           // self explanatory
		0,                                      // disable time slicing
		NU_PREEMPT,                             // preembtable by higher priority task
		NU_START);                              // start already
}

//
// Destructor:
//
// Destroy the timer.  Release the memory used by the timer task and stack.
//
NuTimer::~NuTimer()
{
	if (hThread != NULL) {
		NU_Terminate_Task(hThread);
		NU_Delete_Task(hThread);
		delete hThread;
	}
	if (threadStack != NULL)
		delete[] threadStack;
}

//
// bridge:
//
// This is the actual timer task as Nucleus knows it.
//
void NuTimer::bridge(unsigned long dummy, NuTimer *me)
{
	me->waitThread();
}

//
// waitThread:
//
// This routine sets up an infinit loop of sleeping and calling cbkfunc.  If
// this is a tick timer (high priority) other tasks can run during the sleeping
// portion.  If this is an idle timer (low priority), the ticks member will be
// set to zero, resulting in a background task that never goes to sleep.
//
void NuTimer::waitThread()
{
	do {
		NU_Sleep(ticks);
		(*cbkfunc)(param);
	} while (1);
}


////////////////////////////////////////////////////////////////////////////
//
//							NuOSEventFlag								////
//
////////////////////////////////////////////////////////////////////////////

//
// Constructor:
//
// Create an event flag.  Note that this flag is implemented with a semaphore.
//
NuOSEventFlag::NuOSEventFlag()
{
	hEventFlag = new (NU_SEMAPHORE);
	(void)NU_Create_Semaphore(hEventFlag, "EVTFLAG", 0, NU_FIFO);
}

//
// Destructor:
//
// Destroy an event flag.  Release the memory used by the semaphore.
//
NuOSEventFlag::~NuOSEventFlag()
{
	NU_Delete_Semaphore(hEventFlag);
	if(hEventFlag != NULL) {
		delete hEventFlag;
	}
}

//
// signal:
//
// Release all tasks waiting for this event. This method is called by the source
// task of the event flag.
//
void NuOSEventFlag::signal()
{
	(void)NU_Release_Semaphore(hEventFlag);
}

//
// reset:
//
// Readies the event flag for use by using up the semaphore.  In this way, the
// the consumers of the event will be halted until the signal is sent.  This
// method is called by the source task of the event flag.
//
void NuOSEventFlag::reset()
{
	(void)NU_Obtain_Semaphore(hEventFlag, NU_NO_SUSPEND);
}

//
// wait:
//
// Wait for the event to occur, blocking the task either forever or for a
// specified timeout.  This method is called by the consumer of the event.  If
// no timeout is specified the task will wait forever.
//
void NuOSEventFlag::wait(const Rhp_int32_t tminms /*=-1*/)
{
	if (tminms == -1)
		(void)NU_Obtain_Semaphore(hEventFlag, NU_SUSPEND);
	else
		(void)NU_Obtain_Semaphore(hEventFlag, NUOS_CLOCK_RATE * tminms / 1000);
}



////////////////////////////////////////////////////////////////////////////
//
//							NuThread									////
//
////////////////////////////////////////////////////////////////////////////

//new start 

void NuThread::endMyThread(void * hThread)
{
	OMHandleCloser::instance()->genCloseEvent(hThread);

	NU_Terminate_Task((NU_TASK *)hThread);		

}

void NuThread::endOtherThread(void * hThread)
{
	NU_TASK *hThreadPtr = (NU_TASK *)hThread;
	NU_Terminate_Task(hThreadPtr);		
	NU_Delete_Task(hThreadPtr);
	delete hThreadPtr;
}

//new end 

//
// preExecFunc:
//
// This is the task function.  It merely calls the function passed to our
// object upon construction with the given parameters.  Note that this function
// is needed only because its arguments match what Nucleus expects.  It will
// not run until the task is started.
//
void NuThread::preExecFunc(unsigned long dummy, void* me)
{
	((NuThread *)me)->m_ExecFunc(((NuThread *)me)->m_ExecParam);
}

//
// Constructor:
//
// Create a thread and stack.  The thread is initially suspended and must be
// started to run.  Tie the thread function to the preExecFunc, which will call
// the actual thread function passed to this constructor.
//
NuThread::NuThread(void tfunc(void *), void *param, const char* const threadName, const long stackSize)
{
	isWrapperThread = 0;
	m_ExecFunc = tfunc;
	m_ExecParam = param;
	hThread = new (NU_TASK);
	threadStack = new unsigned char[stackSize];
	NU_Create_Task(hThread,                                     // task record (must be supplied)
		(char *) threadName,                         // task name
		(void (*)(unsigned long, void*))preExecFunc, // actual task
		1,                                           // argc: 1 argument
		(void *)this,                                // argv: pass this pointer
		threadStack,                                 // begining of the stack for this task
		stackSize,                                   // task's stack size
		PRIORITY_NORMAL,                             // Normal priority
		1,                                          // 10 ticks time slice
		NU_PREEMPT,                                  // preembtable by higher priority task
		NU_NO_START);				            // start suspended
}

//
// Constructor:
//
// Create a wrapper thread by attaching to the task pointer passed to this
// constructor.
//
NuThread::NuThread(void *osThreadId)
{
	hThread = (NU_TASK *)osThreadId;
	threadStack = NULL;;
	isWrapperThread = 1;
	endOSThreadInDtor = TRUE ;
}

//
// Destructor:
//
// If this is not a wrapper thread or the currently executing thread, suspend
// and then delete the task.  Finally, release the memory used by the task and
// stack.
//

void NuThread::getThreadEndClbk(NuThread::OMOSThreadEndCallBack * clb_p, void ** arg1_p, const OMBoolean onExecuteThread)
{
	if (onExecuteThread) {
		// asking for a callback to end my own thread
		*clb_p = &endMyThread;
		*arg1_p = &hThread;
	}
	else {
		// asking for a callback to end my thread by someone else
		*clb_p  = &endOtherThread;
		// my thread handle
		*arg1_p = &hThread;
	}
}


NuThread::~NuThread()
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
				if (threadStack != NULL) {
					delete[] threadStack;
					threadStack = NULL;	
				}
				(*theOSThreadEndClb)(*threadHandle);
			}
		}
	}
	if (threadStack != NULL) {
		delete[] threadStack;
	}

}

//
// setPriority:
//
// Change the priority of the task.
//
void NuThread::setPriority(int pr)
{
	NU_Change_Priority(hThread, pr);
}

//
// suspend:
//
// Suspend the task execution.
//
void NuThread::suspend()
{
	NU_Suspend_Task(hThread);
}

//
// resume:
//
// Resume the task execution.
//
void NuThread::resume()
{
	NU_Resume_Task(hThread);
}



////////////////////////////////////////////////////////////////////////////
//
//							NuMutex										////
//
////////////////////////////////////////////////////////////////////////////

//
// Constructor:
//
// Create a mutex.  Implemented with a semaphore along with added support for
// recursive calls by the same thread.
//
NuMutex::NuMutex()
{
	owner = NULL;
	recursionCount = 0;
	hMutex = new (NU_SEMAPHORE);
	(void)NU_Create_Semaphore(hMutex, "Mutex", 1, NU_FIFO);
}

//
// Destructor:
//
// Destroy the mutex.  Release the memory used by the semaphore.
//
NuMutex::~NuMutex()
{
	(void)NU_Delete_Semaphore(hMutex);
	if (hMutex != NULL)
		delete hMutex;
}

//
// lock:
//
// Lock the semaphore.  The first time lock() is called by a thread, the
// semaphore will be obtained (suspending the task if necessary) and the owning
// thread tracked.  Recursive locking by the same thread is then tracked by
// keeping a count of the number of times the owning thread has locked the mutex.
//
void NuMutex::lock()
{
	NU_TASK* currentTask = NU_Current_Task_Pointer();
	if (owner == currentTask)
	{
		++recursionCount;
	}
	else 
	{
		(void)NU_Obtain_Semaphore(hMutex, NU_SUSPEND);
		owner = currentTask;
		recursionCount = 1;
	}
}

//
// free:
//
// Free the semaphore, taking into account recursive locking by same thread.
// When a thread has released all locks on the semaphore, reset the owner and
// recursion count and release the semaphore.
//
//void NuMutex::free()
void NuMutex::unlock()	
{
	NU_TASK* currentTask = NU_Current_Task_Pointer();
	if (owner == currentTask) {
		if (recursionCount > 1)
			--recursionCount;
		else {
			recursionCount = 0;
			owner = NULL;
			(void)NU_Release_Semaphore(hMutex);

		}
	}
}



////////////////////////////////////////////////////////////////////////////
//
//							NuOSMessageQueue							////
//
////////////////////////////////////////////////////////////////////////////


NuOSMessageQueue::NuOSMessageQueue(OMBoolean shouldGrow , int initSize )
{
	STATUS status;
	unsigned int mq_size;

	mq_size = (sizeof(void *)) * initSize ;

	m_State = noData;
	pmessage = NULL;
	Queue_p = new (NU_PIPE) ;
	QueueData_p = new unsigned char[mq_size] ;
	status = NU_Create_Pipe(Queue_p,
					"Queue",
					QueueData_p,
					mq_size,
					NU_FIXED_SIZE,
					sizeof(void *),
					NU_PRIORITY);

	if(status != NU_SUCCESS) {
		delete Queue_p;
	}
}

OMBoolean NuOSMessageQueue::put(void *m, OMBoolean fromISR)
{
	STATUS status;

	static void * NULL_VAL = NULL ;
	if (NULL == m)
		m = NULL_VAL ;

	if (fromISR == TRUE) {
		status = NU_Send_To_Pipe(Queue_p,
							(void *)&m,
							sizeof(void *),
							NU_NO_SUSPEND );
	}
	else {
			status = NU_Send_To_Pipe(Queue_p,
								(void *)&m,
								sizeof(void *),
								NU_SUSPEND );
	}

	if (status == NU_SUCCESS)
		return TRUE;
	else
		return FALSE;
}

void * NuOSMessageQueue::get()
{
	void *m;
	
	if (m_State == dataReady) {
		m = pmessage ;
		m_State = noData ;
	}
	else {
		if (!isEmpty()) {
			STATUS st;
			UNSIGNED act_size = 0;
			st = NU_Receive_From_Pipe(Queue_p,
							(void *)&m,
							sizeof(void *),
							&act_size,
							NU_NO_SUSPEND );
			if ((st != NU_SUCCESS) || (act_size == 0))
			{
				m = NULL;
			}
		}
		else
			m = NULL;
	}
	return m;
}

void NuOSMessageQueue::pend()
{
	void *m;

	if (isEmpty()) {
		STATUS st;
		UNSIGNED act_size;
		st = NU_Receive_From_Pipe(Queue_p,
							(void *)&m,
							sizeof(void *),
							&act_size,
							NU_SUSPEND );	
	
			if ((st == NU_SUCCESS) && (act_size > 0))
			{
				m_State = dataReady;
				pmessage = m;
			}
	}
}

Rhp_int32_t NuOSMessageQueue::isEmpty() const
{
	    UNSIGNED available_bytes;
        CHAR queue_name[8];
        VOID *start_address;
        UNSIGNED size;
        UNSIGNED message;
        OPTION message_type;
        UNSIGNED message_size;
        OPTION suspend_type;
        UNSIGNED tasks_suspended;
        NU_TASK *first_task;


	NU_Pipe_Information(Queue_p,
						queue_name,
						&start_address,
						&size,
                        &available_bytes,
						&message,
                        &message_type,
						&message_size,
                        &suspend_type,
                        &tasks_suspended,
                        &first_task);


	if (message == 0 && noData == m_State) 
		return TRUE;
	return FALSE;
}

OMBoolean NuOSMessageQueue::isFull(void) const
{

	    if (isEmpty()) return FALSE;

		UNSIGNED available_bytes;
        CHAR queue_name[8];
        VOID *start_address;
        UNSIGNED size;
        UNSIGNED messages;
        OPTION message_type;
        UNSIGNED message_size;
        OPTION suspend_type;
        UNSIGNED tasks_suspended;
        NU_TASK *first_task;

        NU_Pipe_Information(Queue_p,
							queue_name,
							&start_address,
							&size,
                            &available_bytes,
							&messages,
                            &message_type,
							&message_size,
                            &suspend_type,
                            &tasks_suspended,
                            &first_task);
	    if (available_bytes == 0)
			return TRUE;
		else
			return FALSE;

}


void NuOSMessageQueue::getMessageList(OMListType & l)
{

	l.removeAll() ;

	UNSIGNED num_msgs ;
	void *m ;
	OMListType lst ;

		UNSIGNED available_bytes;
        CHAR queue_name[8];
        VOID *start_address;
        UNSIGNED size;
        OPTION message_type;
        UNSIGNED message_size;
        OPTION suspend_type;
        UNSIGNED tasks_suspended;
        NU_TASK *first_task;

        NU_Pipe_Information(Queue_p,
							queue_name,
							&start_address,
							&size,
                            &available_bytes,
							&num_msgs,
                            &message_type,
							&message_size,
                            &suspend_type,
                            &tasks_suspended,
                            &first_task);


	for(int i=0; i<num_msgs; i++ ){
		m = get() ;
		lst.add(m) ;
	}
	
	for(int i=0,j=1; i<num_msgs; i++, j++ ){
		m = lst.getAt(num_msgs-j) ;
		l.add(m);									//Since the list has to be filled in reverse order
		m = lst.getAt(i);	
		put(m,FALSE) ;
	}
}


//
//
// The remainder of the code in this file supports Sockets and Connection Ports.
// This code is only included when Instrumentation is active.
//
//

#ifdef _OMINSTRUMENT

//
// Convert an IP address in the format "1.2.3.4" to the structure addr_struct
//
static void IPStringToStruct( char *IPSrc, struct addr_struct *st )
{
	char *ptr1, *base_ptr = IPSrc;
	char ip[4];
  
	for( int i = 0; i < 3; i++ ) {
		ptr1 = strchr( base_ptr, '.' );
		strncpy( ip, base_ptr, ( ptr1 - base_ptr ) );
		ip[ptr1 - base_ptr] = 0;
		st->id.is_ip_addrs[i] = atoi( ip );
		base_ptr = ptr1 + 1;
	}
	strcpy( ip, base_ptr );
	st->id.is_ip_addrs[3] = atoi( ip );
}


////////////////////////////////////////////////////////////////////////////
//
//							NuSocket									////
//
////////////////////////////////////////////////////////////////////////////

//
// Constructor:
//
//
//
NuSocket::NuSocket()
{
	theSock = -1;

}

//
// Destructor:
//
//
//
NuSocket::~NuSocket()
{
	Close();
}

//
// Create:
//
// Open and connect to the socket.
//

Rhp_int32_t NuSocket::Create(const Rhp_const_char_pt SocketAddress /*= NULL*/, const Rhp_uint32_t nSocketPort /*= 0*/)
{
	struct addr_struct server_addr_struct;
	NU_HOSTENT host_entry;
    Rhp_int32_t port = nSocketPort;
  
	// Set to Rhapsody default port if not specified
	if ( nSocketPort == 0 )
		port = 6423;

	// Set to loopback address if SocketAddress is not specified
	if ( SocketAddress == NULL ) {
		server_addr_struct.id.is_ip_addrs[0] = 127;
		server_addr_struct.id.is_ip_addrs[1] = 0;
		server_addr_struct.id.is_ip_addrs[2] = 0;
		server_addr_struct.id.is_ip_addrs[3] = 1;
	}
	else {
		// Check to see if SocketAddress has a host name in it
		if ( NU_Get_Host_By_Name(const_cast<char*>(SocketAddress), &host_entry ) == NU_SUCCESS )
			IPStringToStruct( host_entry.h_addr, &server_addr_struct );
		else // Assume it's a valid IP address
			IPStringToStruct( const_cast<char*>(SocketAddress), &server_addr_struct );
    }

	server_addr_struct.port = INTSWAP(port);
	server_addr_struct.family = NU_FAMILY_IP;
	server_addr_struct.name = "RhapsodyLink";

	// Open the socket
	if ( ( theSock = NU_Socket( NU_FAMILY_IP, NU_TYPE_STREAM, NU_NONE ) ) < 0 )
		return 0;
  
	// Make sure the socket is set to blocking.
	NU_Fcntl( theSock, NU_SETFLAG, NU_BLOCK );

	// Attempt to connect to the server
	if ( NU_Connect( theSock, &server_addr_struct, 0 ) < 0 )
		return 0;
 
	return 1;
}

//
// Close:
//
// Close the socket.
//
void NuSocket::Close(void)
{
	if (theSock >= 0) {
		NU_Close_Socket( theSock );
		theSock = -1;
	}
}

//
// Send:
//
// Send data out the socket.
//
Rhp_int32_t NuSocket::Send(const Rhp_const_char_pt lpBuf, const Rhp_int32_t nBufLen)
{
	int bytes_written = 0;

	bytes_written = NU_Send( theSock, (char *)lpBuf, nBufLen, 0 );  
	return bytes_written;
}

//
// Receive:
//
// Receive data from the socket
//

Rhp_int32_t NuSocket::Receive(Rhp_char_pt lpBuf, const Rhp_int32_t nBufLen)
{
	int bytes_read = 0;

	bytes_read = NU_Recv( theSock, lpBuf, nBufLen, 0 );  
	return bytes_read;
}



////////////////////////////////////////////////////////////////////////////
//
//						NuConnectionPort								////
//
////////////////////////////////////////////////////////////////////////////
//

char* NuConnectionPort::m_Buf = NULL;
int NuConnectionPort::m_BufSize = 0;

//
// Constructor:
//
//
//
NuConnectionPort::NuConnectionPort()
{
	m_Connected = 0;
	m_dispatchfunc = NULL;
	m_ConnectionThread = NULL;
	m_ShouldWaitForAck = 1;
	m_NumberOfMessagesBetweenAck = 0;
	m_AckEventFlag.reset();
}

//
// Destructor:
//
// Close and destroy socket
//
NuConnectionPort::~NuConnectionPort()
{
	m_Socket.Close();
	if (m_ConnectionThread) {
		
		void* threadOsHandle = OMOSFactory::instance()->getCurrentThreadHandle();
		if (threadOsHandle != m_ConnectionThread->getOsHandle())
			// do not delete myself
			delete m_ConnectionThread;
        m_ConnectionThread = NULL;
	}
	// I assume that we will have only one connection port
	// so I can free the data for m_Buf but if it is not the case
	// it does not matter ( the readFromSockLoop will allocate it )
	if (m_Buf) 
		delete[] m_Buf;

    m_BufSize = 0;
}

//
// Connect:
//
// Connect to Rhapsody and start the thread that reads data from the socket.
//
Rhp_int32_t NuConnectionPort::Connect(const Rhp_const_char_pt SocketAddress, const Rhp_uint32_t nSocketPort)
{
	if ( m_dispatchfunc == NULL )
		return 0;
  
	// Are we already connected?
	if ( m_Connected == 0 ) {
		m_Connected = m_Socket.Create(SocketAddress,nSocketPort);
		// Did we connect ok?
		if ( m_Connected == 0 )
			return 0;
    }
  
	// Connection established
	// invoking thread to recieve messages from the socket
	m_ConnectionThread = new NuThread((void (*)(void *))readFromSockLoop,(void *)this, "ConnectionPort", DEFAULT_STACK);
	m_ConnectionThread->start();
	return m_Connected;
}

//
// readFromSockLoop:
//
// Thread that reads all data sent to the application from Rhapsody.
//
void NuConnectionPort::readFromSockLoop(NuConnectionPort *me)
{
	char lenStr[MAX_LEN_STR+1];
	int len;
	int rv;
	for (;;) {
		(void)NU_Check_Stack();
		rv = me->m_Socket.Receive(lenStr,MAX_LEN_STR);
		if ( rv < 0 ) {
			me->m_Socket.Close();
			return;
		}
		lenStr[MAX_LEN_STR] = '\0';
		if (sscanf(lenStr,"%d",&len) == 1) {
			if (len > m_BufSize ) {
				m_BufSize = 1000+len;
				if (m_Buf) {
					delete[] m_Buf;
				}
				m_Buf = new char[m_BufSize];
			}
			if (len == -2)  {// Acknoledge message
				me->m_AckEventFlag.signal();
				continue;
			}
			m_Buf[len] = '\0';
			rv = me->m_Socket.Receive(m_Buf,len);
			if ( rv < 0 ) {
				me->m_Socket.Close();
				return;
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

//
// Send:
//
//
//
Rhp_int32_t NuConnectionPort::Send(OMSData *m)
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

#endif // _OMINSTRUMENT



////////////////////////////////////////////////////////////////////////////
//
//						NuOSSemaphore									////
//
////////////////////////////////////////////////////////////////////////////

//
// Constructor:
//
// Create a semaphore.  Implemented with a semaphore.
//
NuOSSemaphore::NuOSSemaphore(unsigned long semFlags, unsigned long initialCount, unsigned long maxCount, const char * const name)
{
	hSem = new (NU_SEMAPHORE);
	(void)NU_Create_Semaphore(hSem, (char *)name, initialCount, semFlags);
}

//
// Destructor:
//
// Destroy the Semaphore.  Release the memory used by the semaphore.
//
NuOSSemaphore::~NuOSSemaphore()
{
	NU_Delete_Semaphore(hSem);
	if (hSem != NULL)
		delete hSem;
}

//
// signal:
//
//
void NuOSSemaphore::signal()
{
	(void)NU_Release_Semaphore(hSem);
}

//
// wait:
//
//
OMBoolean NuOSSemaphore::wait(const Rhp_int64_t timeout)
{
	STATUS status;
  
	if (timeout == -1)
		status = NU_Obtain_Semaphore(hSem, NU_SUSPEND);
	else
		status = NU_Obtain_Semaphore(hSem, NUOS_CLOCK_RATE * timeout / 1000);
  
	return (OMBoolean)(status == NU_SUCCESS);
}


//Revision 1.0
//Added Message Queueu Implememtation
