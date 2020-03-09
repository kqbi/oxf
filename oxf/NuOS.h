#ifndef _nuos_H
#define _nuos_H

//
//  file name   :   $Source: R:/StmOO/Master/cg/LangCpp/oxf/rcs/NuOS.h $
//  file version:   $Revision: 1.0		23/07/2001
//								1.1		30/11/2001
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
//  $Id: NuOS.h 1.7 2007/03/11 08:42:41 ilgiga Exp $

extern "C" {
#include <nucleus.h>
/* #include <hardware.h>*/
}

#ifdef _OMINSTRUMENT
extern "C" {
#include <externs.h>
#include <socketd.h> 
}
#include <oxf/omtypes.h>
#endif // _OMINSTRUMENT
#include <oxf/os.h>
#include <oxf/omoutput.h>

#include <iostream.h>

#define PRIORITY_HIGH 1
#define PRIORITY_NORMAL 10
#define PRIORITY_LOW 255       // lowest priority is 255
#define MQ_DEFAULT_SIZE 100     // 32  events seem reasonable, but 100 better
#define SMALL_STACK		10000 
#define DEFAULT_STACK	20000 

#define NUOS_CLOCK_RATE (100)  // ticks per second

//
// NuTimer
//
class NuTimer : public OMOSTimer {
private:
	void (*cbkfunc)(void *);
	void waitThread();
	static void bridge(unsigned long dummy, NuTimer *me);
	NU_TASK* hThread;
	long m_Time ;
	void *param;
	long ticks ;
	void* threadStack;
public:
	NuTimer(long ptime, void pcbkfunc(void *), void *pparam); // TickTimer (Real Time)
	NuTimer(void pcbkfunc(void *), void *pparam);             // IdleTimer (Simulated Time)
	virtual ~NuTimer();
	virtual void* getOsHandle() const { return (void*) hThread; }	
	virtual void setAffinity(const OMAffinity_t /*aff*/) {}
};

//
// NuOsEventFlag
//
class NuOSEventFlag : public OMOSEventFlag {
private:
	NU_SEMAPHORE* hEventFlag;
public:
	NuOSEventFlag();
	virtual ~NuOSEventFlag();
	void signal();
	void reset();
	void wait(const Rhp_int32_t tminms = -1); // tminms = -1 means wait forever
	virtual void* getOsHandle() const { return (void*) hEventFlag; } 

};

//
// NuThread
//
class NuThread : public OMOSThread {
private:
	NU_TASK* hThread ;
	void* threadStack;
	int isWrapperThread;
	static void preExecFunc(unsigned long dummy, void* me);
	void (*m_ExecFunc)(void *);
	void* m_ExecParam;
	OMBoolean endOSThreadInDtor; // TRUE means that the os thread is ended as part of this object's destruction 
public:
	NuThread(void tfunc(void *), void *param, const char* const threadName, const long stackSize);
	NuThread(void *osThreadId); // for creation of wrapper thread
	virtual ~NuThread(void);
	void setPriority(const Rhp_int32_t pr);
	void suspend(void);
	void resume(void);
	void start(void) { resume(); }
	virtual void* getOsHandle(void) const { return (void *) hThread ; }

	// no function implementation for these finctions
	virtual void* getOsHandle(void*& osHandle) const {  //const is removed 
		osHandle = (void*) hThread ; 
		return getOsHandle() ;
	}

	// no function implementation for these finctions
	static void endMyThread(void *);
	static void endOtherThread(void *);
	
	// added to remove abstract class problem
	void setEndOSThreadInDtor(const  OMBoolean val) { endOSThreadInDtor = val; };
	void getThreadEndClbk(OMOSThreadEndCallBack * clb_p,           // a pointer to the callback function
								void ** arg1_p,					 // the argument for this function
								const OMBoolean onExecuteThread);
  //## operation getAffinity()
	virtual OMAffinity_t getAffinity(void) const {
		return (OMAffinity_t)0U;
	}
	//## operation setAffinity(OMAffinity_t)
	virtual void setAffinity(const OMAffinity_t /*aff*/) {}

	virtual void setPwrState(const OMPowerMode_t /*val*/) {}

	virtual OMPowerMode_t getPwrState(void) const { return (OMPowerMode_t)0;}

};

//
// NuMutex
//
class NuMutex : public OMOSMutex {
private:
	NU_SEMAPHORE* hMutex;
	NU_TASK* owner;
	int recursionCount;
public:
	NuMutex();
	virtual ~NuMutex();
	void lock();
	void unlock();
	//void free();
	//void* getHandle() { return (void *)hMutex; }
	virtual void* getOsHandle() const { return (void*) hMutex; } 
};


class NuOSMessageQueue : public OMOSMessageQueue { 
private:
	NU_PIPE *Queue_p ;
	void * QueueData_p ;
	void *pmessage;
	enum { dataReady, noData } m_State; 
	
public:
	NuOSMessageQueue(OMBoolean shouldGrow = TRUE, int initSize = OMOSThread::DefaultMessageQueueSize);
	OMBoolean put(void *, OMBoolean fromISR = FALSE);//OMBoolean 
	void *get(void);
	virtual Rhp_int32_t isEmpty(void) const;
	void pend(void);
	void getMessageList(OMListType & c);
	virtual OMBoolean isFull(void) const;
	// no implementation of this function
	virtual void* getOsHandle() const { return (void*) Queue_p;} //
};
//
// NuOsSemaphore
//
class NuOSSemaphore : public OMOSSemaphore {
private:
	NU_SEMAPHORE* hSem;
public:
	NuOSSemaphore(unsigned long semFlags, unsigned long initialCount, unsigned long maxCount, const char * const name);
	virtual ~NuOSSemaphore();
	void signal();
	//virtual void reset() = 0;
	OMBoolean wait(const Rhp_int64_t timeout = -1); 
	virtual void* getOsHandle() const { return (void*) hSem; } 

} ;


//
// NuOSFactory
//
class NuOSFactory : public OMOSFactory {
public:
	virtual   OMOSMessageQueue* createOMOSMessageQueue(const OMBoolean shouldGrow, const Rhp_int32_t messageQueueSize = OMOSThread::DefaultMessageQueueSize) const; 
	virtual   OMOSConnectionPort* createOMOSConnectionPort(void) const;
	virtual   OMOSEventFlag* createOMOSEventFlag(void) const;
	virtual   OMOSThread* createOMOSThread(void (*tfunc)(void *), void *param, 
									 const Rhp_const_char_pt threadName=NULL,	
									 const Rhp_int32_t stackSize = OMOSThread::DefaultStackSize ) const;
	virtual	  OMOSThread* createOMOSWrapperThread(void* osHandle) const;
	virtual   OMOSMutex*  createOMOSMutex(void) const;
	virtual   OMOSSemaphore* createOMOSSemaphore(const Rhp_uint64_t semFlags=0U, const Rhp_uint64_t initialCount=1U, const Rhp_uint64_t maxCount=1U, const Rhp_const_char_pt name=NULL) const; 
	virtual   OMOSTimer* createOMOSTickTimer(const timeUnit time, void (*cbkfunc)(void *), void *param) const;
	virtual   OMOSTimer* createOMOSIdleTimer(void (*cbkfunc)(void *), void *param) const;
	virtual   void* getCurrentThreadHandle(void) const;
	virtual   void delayCurrentThread(const timeUnit ms) const;
	virtual   OMBoolean waitOnThread( void* osHandle, const timeUnit ms) const
	{   
		return FALSE;
	}
};


#ifdef _OMINSTRUMENT

//
// NuSocket - Instrumented Code Only
//
class NuSocket: public OMOSSocket {
private:
	int theSock;
	int lsbFirst; // 0- MsbFisrt 1-LsbFisrt
public:
	NuSocket(void);
	virtual ~NuSocket(void);
	virtual Rhp_int32_t Create(const Rhp_const_char_pt SocketAddress = NULL, const Rhp_uint32_t nSocketPort = 0);
	virtual Rhp_int32_t Send(const Rhp_const_char_pt lpBuf, const Rhp_int32_t nBufLen);
	virtual Rhp_int32_t Receive(Rhp_char_pt lpBuf, const Rhp_int32_t nBufLen);
	virtual void Close(void);
};

//
// NuConnectionPort - Instrumented Code Only
//
class NuConnectionPort: public OMOSConnectionPort {
private:
	static void readFromSockLoop(NuConnectionPort *me);
	static char* m_Buf;
	static int m_BufSize;
	NuMutex m_SendMutex ;
	int m_Connected;		
	NuOSEventFlag m_AckEventFlag;	
protected:
	//int m_Connected;	
	void (*m_dispatchfunc)(OMSData *);
	NuThread* m_ConnectionThread;
	NuSocket m_Socket;
public:
	int m_ShouldWaitForAck;
	//NuOSEventFlag m_AckEventFlag;
	int m_NumberOfMessagesBetweenAck;
	NuConnectionPort();
	virtual ~NuConnectionPort(void);
	virtual Rhp_int32_t Connect(const Rhp_const_char_pt SocketAddress = NULL, const Rhp_uint32_t nSocketPort = 0U);
	virtual Rhp_int32_t Send(OMSData *m);
	virtual void SetDispatcher(void (*dispatchfunc)(OMSData*)) { m_dispatchfunc = dispatchfunc; }
};

#endif // _OMINSTRUMENT

#endif // _nuos_H
