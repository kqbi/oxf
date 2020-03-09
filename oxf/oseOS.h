#ifndef _oseos_H
#define _oseos_H
//
//	file name   :	$Source: R:/StmOO/Master/cg/LangCpp/oxf/rcs/oseOS.h $
//	file version:	$Revision: 1.15 $
//
//	purpose:	
//
//	author(s):	Mikko Holappa
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
// ---------------------------------------------------------------
//|                                oseOS.h                        |
// --------------------------------------------------------------- 


// ------------------------------------------------------------------------------
// Additional functions to deliver a void* parameter to the process being created
// and for storing Rhapsody object pointers that are interested in Software Bus
// 

#include <ose.h>
#include <stdarg.h>
#include <stdio.h>

#include <oxf/os.h>
#include <oxf/omtypes.h>

#ifdef _OMINSTRUMENT
#include <oxf/osesocket.h>
#endif // _OMINSTRUMENT

// 
// ------------------------------------------------------------------------------

// singal number for Rhapsody events (used in oseOSMessageQueue::put())
#define RHAPSODY_SIGNAL_ID 222


#define PRIORITY_HIGH 1
#define PRIORITY_NORMAL 5
#define PRIORITY_LOW 31   /* lowest priority is 31 */
#define MQ_DEFAULT_SIZE 32 /* 32  events seem reasonable */
#define SMALL_STACK 1000
#define DEFAULT_STACK 2000


class oseTimer : public OMOSTimer {
public:
	
	void waitThread(void);
	oseTimer(timeUnit ptime, void pcbkfunc(void *), void *pparam); // TickTimer
	oseTimer(void pcbkfunc(void *), void *pparam); 	   // IdleTimer (Simulated Time) 
	virtual ~oseTimer(void);
	virtual void* getOsHandle(void) const { return (void*) hThread; }
	virtual void setAffinity(const OMAffinity_t /*aff*/) {}
	
private:
	void (*cbkfunc)(void *);
	PROCESS hThread;
	timeUnit m_Time ;
	void *param;
	int ticks ; // how many OS ticks the timer wakes up  
};


class oseOSEventFlag : public OMOSEventFlag {
public:
	void signal(void);
	void reset(void);
	virtual void wait(const Rhp_int32_t tminms = -1);  // tminms = -1 is wait forever
	oseOSEventFlag(void);
	~oseOSEventFlag(void);
	void* getHandle(void) { return (void *)hEventFlag; }
	virtual void* getOsHandle(void) const { return (void*) hEventFlag; }
private:
	SEMAPHORE *hEventFlag;
};


class oseThread : public OMOSThread {
public:
	oseThread(void tfunc(void *), void *param,const char* const name = NULL, const long stackSize = OMOSThread::DefaultStackSize);
	oseThread(void *osThreadId); // for creation of wrapper thread
	
	virtual ~oseThread(void);
	
	void setPriority(const Rhp_int32_t pr) {		
		(void) set_pri_for(hThread, (OSPRIORITY)pr);
	}
	
	void* getOsHandle(void) { return (void *)hThread; } 
	void suspend(void) { stop(hThread); }
	void resume(void) { ::start(hThread); }	
	void start(void) { resume(); }
	
	void setEndOSThreadInDtor(const OMBoolean val) {  endOSThreadInDtor = val; }
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
	
private:	
	PROCESS hThread;
	int isWrapperThread;
	OMBoolean endOSThreadInDtor; // TRUE means that the os thread is ended as part of this object's destruction
	// preExecfunc activate the exec func passing param to exec func
	static void preExecFunc();
	void (*m_ExecFunc)(void *);
	void* m_ExecParam;
}; 

class oseMutex : public OMOSMutex {
public:
	void lock(void);
	void unlock(void);
	oseMutex(void);
	~oseMutex(void);
	void* getHandle(void) { return (void *)hMutex; }
	virtual void* getOsHandle(void) const { return (void*) hMutex; }
private:
	int count;
	void * owner;
	SEMAPHORE *hMutex;
};

class oseOSMessageQueue : public OMOSMessageQueue {
public:
	oseOSMessageQueue(const long messageQueueSize = OMOSThread::DefaultMessageQueueSize): m_State(noData) {}
	~oseOSMessageQueue(void) {}
	
	OMBoolean put(void *,const OMBoolean fromISR = FALSE);
	void *get(void);
	virtual	Rhp_int32_t isEmpty(void) const;
	void pend(void);
	void getMessageList(OMListType & l);
	virtual OMBoolean isFull(void) const;
	void setOwnerProcess(void* process) {ownerProcess = (PROCESS)process;}
	virtual void* getOsHandle(void) const { return (void*) ownerProcess; }
	
private:  
	void *pmessage ; // Buffer of a single lookahead message 
	enum { dataReady, noData } m_State ;
	PROCESS ownerProcess;
};

#ifdef _OMINSTRUMENT
class oseConnectionPort: public OMOSConnectionPort {
public:
	int m_ShouldWaitForAck;
	
	oseOSEventFlag m_AckEventFlag;
	int m_NumberOfMessagesBetweenAck;
	
	oseConnectionPort();
	virtual ~oseConnectionPort();
	virtual Rhp_int32_t Connect(const Rhp_const_char_pt SocketAddress = NULL,
		const Rhp_uint32_t nSocketPort = 0U);
	virtual Rhp_int32_t Send(OMSData *m);
	virtual void SetDispatcher(void (*dispatchfunc)(OMSData*)) {
		m_dispatchfunc = dispatchfunc;
	}
	
protected:
	int m_Connected; // maybe should be private
	void (*m_dispatchfunc)(OMSData *);
	oseThread* m_ConnectionThread;
	oseSocket m_ntSocket;
	
private:
	static void readFromSockLoop(oseConnectionPort *me);
	static char* m_Buf;
	static int m_BufSize;
	
	oseMutex m_SendMutex ;
};
#endif 


/////////////////////////////////
// Semaphore class
class oseSemaphore : public OMOSSemaphore {
public:
	oseSemaphore(unsigned long semFlags, unsigned long initialCount);
	~oseSemaphore();
	
	// override of pure virtual
	virtual void signal();
	virtual OMBoolean wait(const Rhp_int64_t timeout = -1);
	virtual void* getOsHandle() const { return (void*) m_semId; }
protected:
	SEMAPHORE *m_semId;
};



class oseOSFactory : public OMOSFactory {
	// OSFactory hides the RTOS mechnisms for tasking and synchronization
public:
	virtual OMOSMessageQueue *createOMOSMessageQueue(const OMBoolean shouldGrow = TRUE, const Rhp_int32_t messageQueueSize = OMOSThread::DefaultMessageQueueSize) const
	{
		return (OMOSMessageQueue*)new oseOSMessageQueue(messageQueueSize);
	}
	
	virtual OMOSConnectionPort *createOMOSConnectionPort(void) const 
	{
#ifdef _OMINSTRUMENT
		return (OMOSConnectionPort*)new oseConnectionPort();
#else
		return NULL;
#endif 
	}
	
	virtual OMOSEventFlag* createOMOSEventFlag(void) const { return (OMOSEventFlag *)new oseOSEventFlag(); }
	
	virtual OMOSThread *createOMOSThread(void (*tfunc)(void *), void *param,
		const Rhp_const_char_pt threadName = NULL,
		const Rhp_int32_t stackSize = OMOSThread::DefaultStackSize) const 
	{
		return (OMOSThread*)new oseThread(tfunc, param, threadName, stackSize);
	}
	
	virtual OMOSThread* createOMOSWrapperThread(void* osHandle) const {
		if (NULL == osHandle)
			osHandle = getCurrentThreadHandle();
		return (OMOSThread*)new oseThread(osHandle);
	}
	virtual OMOSMutex  *createOMOSMutex(void) const 
	{
		return (OMOSMutex*)new oseMutex();
	}
	
	virtual OMOSTimer *createOMOSTickTimer(const timeUnit tim, void (*cbkfunc)(void*), void *param) const 
	{ 
		return (OMOSTimer*)new oseTimer(tim, cbkfunc, param);   // TickTimer for real time
	}
	
	virtual OMOSTimer *createOMOSIdleTimer(void (*cbkfunc)(void*), void *param) const 
	{ 
		return (OMOSTimer*)new oseTimer(cbkfunc, param);   // Idle timer for simulated time
	}
	
	virtual OMOSSemaphore* createOMOSSemaphore(const Rhp_uint64_t semFlags = 0U, const Rhp_uint64_t  initialCount = 1U, 
		const Rhp_uint64_t  maxCount = 1U, const Rhp_const_char_pt name = NULL) const
	{
		return (OMOSSemaphore*) new oseSemaphore(semFlags, initialCount);
	}
	
	virtual void* getCurrentThreadHandle(void) const;
	virtual void delayCurrentThread(const timeUnit ms) const;
	
	virtual OMBoolean waitOnThread(void* osHandle, const timeUnit ms) const 
	{
		return FALSE ;
	}
	
};

//
// $Log: oseOS.h $
// Revision 1.15  2007/03/11 08:43:00  ilgiga
// Change copyright comment
// Revision 1.14  2007/03/01 14:32:40  ilgiga
// Telelogic instead of i-Logix
// Revision 1.13  2005/11/07 12:11:43  yshekel
// Upgrade_from_60_to_61
// Revision 1.12  2005/08/25 07:52:51  vova
// Signature fixed in all arguments, defined as pointer to function
// Revision 1.10.1.1  2003/06/02 06:39:37  gio
// Fix bug 60572:
// PRIORITY_LOW value is changed to 31.
// Revision 1.10  2001/08/05 09:29:58  amos
// back to main branch
// Revision 1.9.1.3  2001/08/05 09:29:58  amos
// modify the memory manager to support passing of the object size in deletion
// Revision 1.9.1.2  2001/08/02 12:20:42  amos
// Revision 1.9.1.1  2001/05/16 13:37:02  amos
// Duplicate revision
// Revision 1.8  2001/01/30 09:10:03  avrahams
// Add OM prefix to globals
// Convert OMOS methods to static methods
// Revision 1.7  2001/01/25 13:59:24  avrahams
// OXF globals encapsulation
// Revision 1.6.1.2  2001/05/03 15:57:13  amos
// Changes framework API to support OSE 4.3.1
// - Modify the name of  OMOSMutex::free() to OMOSMutex::unlock
// - Modify the name of State::exit() & State::enter() to State::exitState() & State::enterState()
// Revision 1.6.1.1  2001/04/19 10:54:54  amos
// upgrade OSE files to support OSE 4.3.1
// - cleanup the OSE framework files
// - use OSE 4.3.1 API to fix the behavior of oseThread::setPriority() - so it can be called by other threads.
// Revision 1.6  2000/11/14 08:58:40  amos
// COM submission fix: replace true/false with TRUE/FALSE
// Revision 1.5  2000/11/13 12:22:35  amos
// merge 1.4.1.2 and 1.4.2.2
// Revision 1.4.2.2  2000/11/09 19:35:38  npadmawar
// Changes for OXFEnd
// Revision 1.4.2.1  2000/07/26 11:57:38  npadmawar
// Revision 1.4.1.2  2000/11/08 16:00:14  amos
// modify the OS layer message queue put() method to return a success status
// Revision 1.4.1.1  2000/07/26 11:57:38  amos
// Duplicate revision
// Revision 1.3.1.2  2000/07/26 11:57:38  amos
// add getOSHandle() to all OS classes (but Socket & connection port)
// Revision 1.3.1.1  2000/01/25 16:42:02  amos
// Duplicate revision
// Revision 1.2.1.1  2000/01/18 15:51:00  amos
// Revision 1.2  1999/12/08 13:20:08  ofer
// using win32 socket in ose soft kernel
// Revision 1.1  1999/11/08 10:58:38  ofer
// Initial revision
// 
#endif // _oseos_H


