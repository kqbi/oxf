#ifndef _sol2os_H
#define _sol2os_H

//	file name   :	$Source: R:/StmOO/Master/cg/LangCpp/oxf/rcs/sol2os.h $
//	file version:	$Revision: 1.34 $
//
//	purpose:	
//
//	author(s):	Eran Gery
//	date started:	
//	date changed:	$Date: 2007/03/11 08:43:02 $
//	last change by:	$Author: ilgiga $
//
//	Licensed Materials - Property of IBM
//	(c) Copyright IBM Corporation 1996, 2016. All Rights Reserved.
//	
//	Note to U.S. Government Users Restricted Rights:  
//	Use, duplication or disclosure restricted by GSA ADP Schedule 
//	Contract with IBM Corp.

// ---------------------------------------------------------------
// |                              sol2os.h                        |
// --------------------------------------------------------------- 

#include <synch.h>
#include "oxf/omiotypes.h"
#ifdef OM_STL
#include <iostream>
#include <cerrno>
#include <csignal>
#else
#include <iostream.h>
#include <errno.h>
#include <signal.h>
#endif //OM_STL

#include <thread.h>
//#include <stdarg.h>
#include <semaphore.h>

#include <oxf/omtypes.h>
#include <oxf/os.h>
#include <oxf/ommemorymanager.h>

const int LowestPriority = 0; 

class Sol2Timer : public OMOSTimer {
private:
	void (*cbkfunc)(void *);
	void waitThread();
	static void* bridge(void* me);
	thread_t hThread;			/* The timeTick thread  */
	void *param;
	timeUnit m_Time ;
	timer_t timerId;
public:
	Sol2Timer(timeUnit ptime, void pcbkfunc(void *), void *pparam); /* TickTimer */
	Sol2Timer(void pcbkfunc(void *), void *pparam); /* IdleTimer (Simulated Time)  */
	~Sol2Timer();
	
	virtual void* getOsHandle() const { return (void*) hThread; }
	virtual void setAffinity(const OMAffinity_t /*aff*/) {}
};


class Sol2OSEventFlag : public OMOSEventFlag {
private:
	sema_t 	hEventFlag;
public:
	void signal();
	void reset();
	virtual void wait(const Rhp_int32_t tminms = -1);  // tminms = -1 is wait forever
	Sol2OSEventFlag();
	~Sol2OSEventFlag();
	void* getHandle() { return (void *)&hEventFlag; }
	virtual void* getOsHandle() const { return (void*) &hEventFlag; }
};


class Sol2Thread : public OMOSThread {
private:
	thread_t hThread ;
	int isWrapperThread;
	OMBoolean endOSThreadInDtor; // TRUE means that the os thread is ended as part of this object's destruction
public:
	Sol2Thread(void tfunc(void *), void *param, const long stackSize = OMOSThread::DefaultStackSize);
	Sol2Thread(void *osThreadId); /* for creation of wrapper thread */
	
	virtual ~Sol2Thread();
	
	
	void setPriority(const Rhp_int32_t pr) { thr_setprio(hThread, pr); }
	void* getOsHandle(void) { return (void *)hThread; } 
	void suspend(void) { (void)thr_suspend(hThread); }
	void resume(void) { (void)thr_continue(hThread); }
	void start(void) { resume(); }
	
	void setEndOSThreadInDtor(const OMBoolean val) { endOSThreadInDtor = val; }
	virtual void* getOsHandle(void) const { return (void*) hThread; }
	virtual void* getOsHandle(void*& osHandle) const
	{ osHandle = (void*) hThread ; return getOsHandle() ; }
	
	// asking for a callback to end my os thread
	// onExecuteThread = TRUE: I will kill my own thread
	// onExecuteThread = FALSE: someone else will kill my thread
	virtual void getThreadEndClbk(OMOSThreadEndCallBack * clb_p, // a pointer to the callback function
		void ** arg1_p,					// the argument for this function
		const OMBoolean onExecuteThread);
	// end the thread I'm working on
	static void endMyThread(void *);
	// end a thread which is NOT my thread
	static void endOtherThread(void *);
  //## operation getAffinity()
  virtual OMAffinity_t getAffinity(void) const {
      return (OMAffinity_t)0U;
  }
  //## operation setAffinity(OMAffinity_t)
  virtual void setAffinity(const OMAffinity_t /*aff*/) {}
  
  virtual void setPwrState(const OMPowerMode_t /*val*/) {}

  virtual OMPowerMode_t getPwrState(void) const { return (OMPowerMode_t)0;}

}; /* Sol2Thread */

class Sol2Mutex : public OMOSMutex {
private:
	mutex_t hMutex;
	int count;
	void * owner;
public:
	Sol2Mutex();
	~Sol2Mutex();
	void lock();
	void unlock();
	void* getHandle() { return (void *)&hMutex; }
	virtual void* getOsHandle() const { return (void*) &hMutex; }
};

/////////////////////////
/////////////////////////
#include <oxf/omoutput.h> /* for notify_to_error*/
class Sol2OSMessageQueue : public OMOSMessageQueue { 
private:
	OMQueueType m_theQueue;
	Sol2Mutex	m_QueueMutex;
	Sol2OSEventFlag m_QueueEventFlag;
public:
	Sol2OSMessageQueue(OMBoolean shouldGrow = TRUE, int initSize = OMOSThread::DefaultMessageQueueSize):
	  m_theQueue(shouldGrow, initSize) {}
	  OMBoolean put(void *, OMBoolean fromISR = FALSE);
	  void *get(void);
	  virtual	Rhp_int32_t isEmpty(void) const { return m_theQueue.isEmpty(); }
	  void pend(void);
	  void getMessageList(OMListType & c);
	  virtual OMBoolean isFull() const {return m_theQueue.isFull();}
	  virtual void* getOsHandle() const { return (void*) NULL; }
};

#ifdef _OMINSTRUMENT

class Sol2Socket: public OMOSSocket {
private:
	int theSock;
public:
	Sol2Socket();
	virtual ~Sol2Socket();
	virtual Rhp_int32_t Create(const Rhp_const_char_pt SocketAddress = NULL,
		const Rhp_uint32_t nSocketPort = 0);
	virtual Rhp_int32_t Send(const Rhp_const_char_pt lpBuf, const Rhp_int32_t nBufLen);
    virtual Rhp_int32_t Receive(Rhp_char_pt lpBuf, const Rhp_int32_t nBufLen);
};


class Sol2ConnectionPort: public OMOSConnectionPort {
private:
	static void readFromSockLoop(Sol2ConnectionPort *me);
	static char* m_Buf;
	static int m_BufSize;
	Sol2Mutex m_SendMutex ;
protected:
	int m_Connected; /* maybe should be private */
	void (*m_dispatchfunc)(OMSData *);
	Sol2Thread* m_ConnectionThread;
	Sol2Socket m_Socket;
public:
	int m_ShouldWaitForAck;
	
	Sol2OSEventFlag m_AckEventFlag;
	int m_NumberOfMessagesBetweenAck;
	
	
	Sol2ConnectionPort();
	virtual ~Sol2ConnectionPort();
    virtual Rhp_int32_t Connect ( const Rhp_const_char_pt SocketAddress = NULL,
                                  const Rhp_uint32_t nSocketPort = 0U );
	virtual Rhp_int32_t Send(OMSData *m);
	virtual void SetDispatcher(void (*dispatchfunc)(OMSData*)) {
		m_dispatchfunc = dispatchfunc;
	}
	
};
#endif

/////////////////////////////////
// Semaphore class
class Sol2Semaphore : public OMOSSemaphore {
public:
	Sol2Semaphore(unsigned long semFlags, unsigned long initialCount);
	~Sol2Semaphore();
	
	// override of pure virtual
	virtual void signal();
	virtual OMBoolean wait(const Rhp_int64_t timeout = -1);
	virtual void* getOsHandle() const { return (void*) &m_sem; }
	
protected:
	sem_t m_sem;
	OMBoolean m_ok;
};


/////////////////////////////////////////
/////////////////////////////////////////

class Sol2OSFactory : public OMOSFactory {
/* OSFactory hides the RTOS mechnisms for tasking and synchronization
	*/
public:
	virtual OMOSMessageQueue *createOMOSMessageQueue(const OMBoolean shouldGrow = TRUE, const Rhp_int32_t messageQueueSize = OMOSThread::DefaultMessageQueueSize) const
	{ 
		return (OMOSMessageQueue*)new Sol2OSMessageQueue(shouldGrow, messageQueueSize);
	}
	virtual OMOSConnectionPort *createOMOSConnectionPort(void)  const
	{
#ifdef _OMINSTRUMENT
		return (OMOSConnectionPort*)new Sol2ConnectionPort();
#else
		return NULL;
#endif
	}
	virtual OMOSEventFlag* createOMOSEventFlag(void)  const
	{ 
		return (OMOSEventFlag *)new Sol2OSEventFlag(); 
	}
	virtual OMOSThread *createOMOSThread(void (*tfunc)(void *), void *param,
		const Rhp_const_char_pt threadName = NULL,
		const Rhp_int32_t stackSize = OMOSThread::DefaultStackSize)  const
	{
		return (OMOSThread*)new Sol2Thread(tfunc, param, stackSize);
	}
	virtual OMOSThread* createOMOSWrapperThread(void* osHandle) const
	{
		if (NULL == osHandle)
			osHandle = getCurrentThreadHandle();
		return (OMOSThread*)new Sol2Thread(osHandle);
	}
	virtual OMOSMutex  *createOMOSMutex(void) const
	{
		return (OMOSMutex*)new Sol2Mutex();
	}
	virtual OMOSTimer *createOMOSTickTimer(const timeUnit tim, void (*cbkfunc)(void*), void *param) const
	{ 
		return (OMOSTimer*)new Sol2Timer(tim, cbkfunc, param);   /* TickTimer for real time */
	}
	virtual OMOSTimer *createOMOSIdleTimer(void (*cbkfunc)(void*), void *param) const
	{ 
		return (OMOSTimer*)new Sol2Timer(cbkfunc, param);   /* Idle timer for simulated time */
	}
	
	virtual OMOSSemaphore* createOMOSSemaphore(const Rhp_uint64_t semFlags = 0U, const Rhp_uint64_t initialCount = 1U, const Rhp_uint64_t maxCount = 1U, const Rhp_const_char_pt name = NULL) const
	{
		return (OMOSSemaphore*) new Sol2Semaphore(semFlags , initialCount);
	}
	
	virtual void* getCurrentThreadHandle(void) const;
	virtual void delayCurrentThread(const timeUnit ms) const;
	
	virtual OMBoolean waitOnThread( void* osHandle, const timeUnit ms) const
	{
		return FALSE ;
	}
	
	virtual ~Sol2OSFactory(void);

 private:
	friend class OMOSFactory;
	static bool destroyed;
};


/*
* $Log: sol2os.h $
* Revision 1.34  2007/03/11 08:43:02  ilgiga
* Change copyright comment
* Revision 1.33  2007/03/01 14:32:42  ilgiga
* Telelogic instead of i-Logix
* Revision 1.32  2005/11/07 12:11:51  yshekel
* Upgrade_from_60_to_61
* Revision 1.31  2005/08/25 07:52:51  vova
* Signature fixed in all arguments, defined as pointer to function
* Revision 1.30  2005/01/27 15:38:38  vova
* 79959: crash while endApplication eliminated. It was caused by early destruction of OMOSFactory instance.
* Revision 1.29  2002/07/15 12:27:49  avrahams
* Back to main
* Revision 1.28.1.2  2002/07/04 10:49:42  avrahams
* Cleanup std namespace usage
* Revision 1.28.1.1  2001/08/05 09:30:40  avrahams
* Duplicate revision
* Revision 1.28  2001/08/05 09:30:40  amos
* back to main branch
* Revision 1.27.1.3  2001/08/05 09:30:40  amos
* modify the memory manager to support passing of the object size in deletion
* Revision 1.27.1.2  2001/08/02 12:20:42  amos
* Revision 1.27.1.1  2001/05/16 12:32:36  amos
* Duplicate revision
* Revision 1.26  2001/01/30 09:10:05  avrahams
* Add OM prefix to globals
* Convert OMOS methods to static methods
* Revision 1.25  2001/01/25 13:59:28  avrahams
* OXF globals encapsulation
* Revision 1.24  2001/01/04 10:30:54  ofer
* check return value of several system calls and notify error
* if retval is not zero ( when in shutdown mode does not inform messages)
* Revision 1.23  2000/11/14 08:58:40  amos
* COM submission fix: replace true/false with TRUE/FALSE
* Revision 1.22  2000/11/13 12:15:57  amos
* merge 1.21.1.2 and 1.21.2.2
* Revision 1.21.2.2  2000/11/09 19:33:45  npadmawar
* Changes for OXFEnd
* Revision 1.21.2.1  2000/09/17 13:43:34  npadmawar
* Revision 1.21.1.2  2000/11/08 15:59:17  amos
* modify the OS layer message queue put() method to return a success status
* Revision 1.21.1.1  2000/09/17 13:43:34  amos
* Duplicate revision
* Revision 1.20  2000/08/07 08:36:32  amos
* fix getOSHandle() for Solaris
* Revision 1.19  2000/08/06 09:24:21  amos
* merge 1.17.1.2 into 1.18
* Revision 1.18  2000/07/12 06:29:57  amos
* the main change related to modify char* to const char*.
* there are some other changes related to assignment of static member function as extern "C" functions.
* Also modify NTOSMessageQueue/Sol2OSMessageQueue to have OMQueue<void*> as a private member (aggregation) instead of rivate inheritace from OMQueue<void*>
* Revision 1.17  1999/07/29 10:34:10  amos
* support generation of events from interupt handler (VxWorks)
* Revision 1.17.1.2  2000/07/26 12:11:44  amos
* add getOSHandle() to all OS classes (but Socket & connection port)
* Revision 1.17.1.1  1999/07/29 10:34:10  amos
* Duplicate revision
* Revision 1.16  1999/03/14 13:12:06  amos
* Revision 1.15.1.3  1999/03/14 11:09:45  amos
* move os includes before framework includes, and by priority
* Revision 1.15.1.2  1999/03/11 11:57:14  amos
* add semaphores to the OXF
* Revision 1.15.1.1  1999/02/09 14:55:29  amos
* Duplicate revision
* Revision 1.14  1999/02/03 12:38:33  amos
* back to main branch
* Revision 1.13.1.2  1999/02/03 12:12:18  amos
* convert OMOSMessageQueue from sizeless (OMList) to size controled (OMQueue)
* Revision 1.13.1.1  1999/02/01 16:19:44  amos
* Duplicate revision
* Revision 1.12.1.2  1999/02/01 11:24:35  amos
* chage time from long to unsigned long
* Revision 1.12  1999/01/26 08:49:41  amos
* back to main branch
* Revision 1.11.1.2  1999/01/24 14:52:50  amos
* merge
* Revision 1.11  1999/01/21 10:34:47  beery
* separate termination of threads when on my thread vs. on other thread
* Revision 1.10.1.4  1999/01/03 12:55:43  beery
* Revision 1.10.1.3  1999/01/03 11:51:32  beery
* adjust to new thread policy
* Revision 1.10.1.2  1999/01/03 11:25:06  beery
* new approach to kill threads
* Revision 1.10.1.1  1998/09/09 13:12:42  beery
* Revision 1.10.2.3  1999/01/19 12:24:22  amos
* setting the message queue size from OMThread constructor
* Revision 1.10.2.2  1999/01/19 09:05:25  amos
* user control over thread name, priority and stack size 
* via parameters in OMThread constructor
* Revision 1.10.2.1  1998/09/09 13:12:42  amos
* Duplicate revision
* Revision 1.9  1998/07/28 13:24:09  ofer
* 1) file oxf/types.h chnaged top oxf/omtypes.h so we needed
* to update include as wel as update dependencies
* 2) psos cadul compiler force as to use inline directive in
*   template method implementation ( otherwise it complain about
*   multiple definitions)
* 3) psos compiler does not allow to use inline for virtual methods
*  ( the method implementation is defined in the .h file) so we have 
*  to move the implementation to the corresponding .cpp files
* 4) update makefiles to use omtypes.h (instead of types.h)
* Revision 1.8  1998/04/13 07:59:56  ofer
* keep "using namespace std;"
* only after include to <XXXstream>
* Revision 1.7  1998/04/13 07:40:27  ofer
* added "using namespace std;" after each include to stl files
* Revision 1.6  1998/04/12 12:16:41  ofer
* Change includes to Stl format ifdefed by OM_USE_STL
* Revision 1.5  1998/04/09 06:49:48  ofer
* change implementation of Sol2EventFlag
* No need for m_StateEventFlag anymore ( sol2os.cpp/h)
* 
* Revision 1.4  1997/12/14 14:30:54  ofer
* added  delayCurrentThread(long ms) to abstract factory 
* and define and implement the method in the XXXOS.cpp/h
* Also added convienent macro OXFTDelay(timInMs)
* os.h ntos.cpp/h VxOs.cpp/h sol2os.cpp/h
* Revision 1.3  1997/10/30 13:08:58  ofer
* change implementation of Sol2EventFlag
* since we are using counting semaphore we have to check
* the "state" of the event flag
* sol2os.cpp/h
* Revision 1.2  1997/04/15 10:27:42  ofer
* New interface for OMOSMessageQueue forced changes
* in the Sol2OSMessageQueue
* the interface now is cleaner !!!!
* sol2os.cpp/h
* Revision 1.1  1997/04/03 23:52:02  ofer
* Initial revision
*/
#endif // _sol2os_H




