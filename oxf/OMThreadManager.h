//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: OMThreadManager
//!	File name		: $Source$
//!	File version	: $Revision$
//
//!	Date changed	: $Date$
//!	Last change by	: $Author$
//
//	Licensed Materials - Property of IBM
//	(c) Copyright IBM Corporation 2004, 2016. All Rights Reserved.
//	
//	Note to U.S. Government Users Restricted Rights:  
//	Use, duplication or disclosure restricted by GSA ADP Schedule 
//	Contract with IBM Corp.


#ifndef OMThreadManager_H
#define OMThreadManager_H

//## dependency addTypes
#include "OXFAddTypes.h"
//## dependency DllMacros
#include "rp_framework_dll_definition.h"
// class OMThreadManager 
//## dependency IOxfAnimThreadManager
#include "IOxfAnimThreadManager.h"
//## dependency OMMap
#ifndef OM_NO_TEMPLATES_USAGE
#include "ommap.h"
#endif // OM_NO_TEMPLATES_USAGE
//## dependency OMProtected
#include "omprotected.h"
//## dependency OMUMap
#ifdef OM_NO_TEMPLATES_USAGE
#include "omumap.h"
#endif // OM_NO_TEMPLATES_USAGE

//## dependency AnimServices
class AnimServices;

//## auto_generated
class IOxfActive;

//## dependency OMCore
class OMCore;

//## dependency OMEvent
class OMEvent;

//## dependency OMThread
class OMThread;

//## dependency OMUResourceGuard
#ifdef OM_NO_TEMPLATES_USAGE
class OMUResourceGuard;


#endif // OM_NO_TEMPLATES_USAGE
//## package Design::oxf::Services::ResourceManagement

//## class OMThreadManager
// This class is responsible for managing the living threads list and for cleanup of these threads on close of the application.
// It is used by RTOS that do not have automatic process cleanup such as VxWorks.
// The cleanup is also used to cleanup the framework threads on unload of the framework DLL.
// Compile the oxf with the OM_NO_APPLICATION_TERMINATION_SUPPORT compilation flag to disable the management of the list.
class OMThreadManager : public IOxfAnimThreadManager {
public :

    // The manager guard declaration
    //#[ type Guard
    OMDECLARE_GUARDED // Guard 
    //#]
    
    //#[ type coreList_t
    #ifdef OM_NO_TEMPLATES_USAGE
        typedef OMUMap coreList_t;
    #else
        typedef OMMap<OMAffinity_t, OMCore*> coreList_t;
    #endif
    
    //#]
    

protected :

    // Initialization
    //## operation OMThreadManager()
    OMThreadManager(void);
    

public :

    //## operation ~OMThreadManager()
    virtual ~OMThreadManager(void);
    
    // Get the singleton instance
    //## operation instance()
    static OMThreadManager& instance(void);
    
    // Deregister an about to die thread
    // Argument OMThread* aThread :
    // The thread
    //## operation deregisterThread(OMThread)
    //#[ ignore
    /*LDRA_INSPECTED 62 D : Can't make argument const */  
    
    //#]
    void deregisterThread(OMThread* aThread);
    
    // register a new thread
    // Argument OMThread* aThread :
    // The thread
    //## operation registerThread(OMThread)
    //#[ ignore
    /*LDRA_INSPECTED 62 D : Can't make argument const */  
    
    //#]
    void registerThread(OMThread* aThread);
    
    // Cleanup all the live threads on close of the application.
    // Cleanup all the registered threads except for:
    // - OMMainThread::instance()
    // - threads that return false in allowDeleteInThreadsCleanup() call
    // - the thread context that this call is invoked on
    // 
    // Should be called only in OSAL cleanup when the RTOS exit() doesn't perform the cleanup
    // return the thread context
    //## operation cleanupAllThreads()
    OMThread* cleanupAllThreads(void);
    
    // Stop all the live threads before unload of the framework as a DLL.
    // stop all the registered threads
    // except the skipme thread and the context thread
    // return the context thread
    // Argument const OMThread* skipme :
    // The thread to skip
    //## operation stopAllThreads(OMThread) const
    OMThread* stopAllThreads(const OMThread* skipme) const;
    
    // Wakeup the specified thread (the thread is supposed to be waiting for events)
    // Argument IOxfActive* aThread :
    // The thread to wakeup
    //## operation wakeup(IOxfActive) const
    //#[ ignore
    /*LDRA_INSPECTED 62 D : Can't make argument const */  
    
    //#]
    virtual void wakeup(IOxfActive* aThread) const;
    
    //## operation getThreads() const
    OMThreadIter getThreads(void) const;
    
    // register a new thread
    // Argument OMThread* aThread :
    // The thread
    //## operation removeThreads(OMThread)
    //#[ ignore
    /*LDRA_INSPECTED 62 D : Can't make argument const */  
    
    //#]
    void removeThreads(OMThread* aThread);
    
    //## operation clearThreads()
    void clearThreads(void);
    
    // register a new thread
    // Argument OMThread* aThread :
    // The thread
    //## operation addThreads(OMThread)
    //#[ ignore
    /*LDRA_INSPECTED 62 D : Can't make argument const */  
    
    //#]
    void addThreads(OMThread* aThread);
    
    // register a new thread
    // Argument OMThread* aThread :
    // The thread
    //## operation findThreads(OMThread) const
    //#[ ignore
    /*LDRA_INSPECTED 62 D : Can't make argument const */  
    
    //#]
    Rhp_int32_t findThreads(OMThread* aThread) const;
    
    //## operation addToCoreList(OMAffinity_t,OMCore*)
    static void addToCoreList(const OMAffinity_t coreId, OMCore* newCore);
    
    //## operation getExistingCore(OMAffinity_t)
    static OMCore* getExistingCore(const OMAffinity_t coreId);
    
    //## operation getCoreList()
    coreList_t* getCoreList(void);
    
    ////    Attributes    ////
    

private :

    static coreList_t coreList;		//## attribute coreList
    
    OMThreadType threads;		//## attribute threads
    
};

#endif



