//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: OXF
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


#ifndef oxf_H
#define oxf_H

//## dependency addTypes
#include "OXFAddTypes.h"
//## dependency BasicTypes
#include "rawtypes.h"
//## dependency IOxfActive
#include "IOxfActive.h"
//## dependency IOxfTickTimerFactory
#include "IOxfTickTimerFactory.h"
// The dependency on the memory manager is required for backward compatibility
//## dependency OMMemoryManager
#include "ommemorymanager.h"
//## dependency OMTimerManagerDefaults
#include "OMTimerManagerDefaults.h"
//## dependency OXFRefLock
#ifndef OM_NO_TEMPLATES_USAGE
#include "OXFRefLock.h"
#endif // OM_NO_TEMPLATES_USAGE
//## dependency PortMacros
#include "OXFPortMacros.h"
//## dependency AnimServices
class AnimServices;

//## dependency OMAnimHelper
class OMAnimHelper;

//## dependency OMDelay
class OMDelay;

//## dependency OMHandleCloser
class OMHandleCloser;

//## dependency OMMainThread
class OMMainThread;

//## dependency OMOS
class OMOS;

//## dependency OMReactive
class OMReactive;

//## dependency OMThread
class OMThread;

//## dependency OMTimerManager
class OMTimerManager;

//## dependency OXFURefManager
class OXFURefManager;

//## package Design::oxf::Services::Initialization

//## class OXF
// The framework entrypoint.
// Provides initialization, startup and termination services.
class RP_FRAMEWORK_DLL OXF {
public :

    //## type frmThreadAffinities_t
    struct frmThreadAffinities_t {
        OMAffinity_t MainThread;		//## attribute MainThread
        OMAffinity_t Timer;		//## attribute Timer
        OMAffinity_t HandleCloser;		//## attribute HandleCloser
        OMAffinity_t AnimMessageReader;		//## attribute AnimMessageReader
        OMAffinity_t AnimMessageSender;		//## attribute AnimMessageSender
        OMAffinity_t Webify;		//## attribute Webify
    };
    
    //#[ type OM_ALLOCATE_MAIN
    #define OM_ALLOCATE_MAIN(aff) OXF::frmThreadAffinities.MainThread=aff; 
    
    //#]
    
    //#[ type OM_ALLOCATE_TIMER
    #define OM_ALLOCATE_TIMER(aff) OXF::frmThreadAffinities.Timer=aff;
    //#]
    
    //#[ type OM_ALLOCATE_READER
    #define OM_ALLOCATE_READER(aff) OXF::frmThreadAffinities.AnimMessageReader=aff;
    //#]
    
    //#[ type OM_ALLOCATE_SENDER
    #define OM_ALLOCATE_SENDER(aff) OXF::frmThreadAffinities.AnimMessageSender=aff;
    //#]
    
    //#[ type OM_ALLOCATE_HANDLECLOSER
    #define OM_ALLOCATE_HANDLECLOSER(aff) OXF::frmThreadAffinities.HandleCloser=aff;
    //#]
    
    //#[ type OM_ALLOCATE_WEBIFY
    #define OM_ALLOCATE_WEBIFY(aff) OXF::frmThreadAffinities.Webify=aff;
    //#]
    
    //#[ type OM_ALLOCATE
    #define OM_ALLOCATE(aff) \
    { \
    	OMThread * task = dynamic_cast<OMThread*>(this); \
    	if (task == NULL) { \
    		task = OMMainThread::instance(); \
    	} \
    	if (task) \
    	{ \
    		assignCoreId(aff); \
    	} \
    }	
    //#]
    
    // This macro should be used in simulated time models instead of any lock call (mutex,semaphore,event), calling context goes to wait for its freeing.
    //#[ type OM_LOCK
    #define OM_LOCK(LOCK_CALL) \
    {\
        OMTimerManager* sysTimer = OMTimerManager::instance(); \
       	bool simulatedTime = false; \
       	if (sysTimer != NULL) { \
       	     simulatedTime = (sysTimer->getRealTimeModel() == false); \
       	} \
    	if (simulatedTime) { \
    		sysTimer->decNonIdleThreadCounter(); \
    	} \
    	LOCK_CALL; \
    	if (simulatedTime) { \
          sysTimer->incNonIdleThreadCounter(); \
        } \
    }
    //#]
    
    //#[ type OXFNotifyEventMethod
    typedef void( *OXFNotifyEventMethod)(void); 
    //#]
    
    //#[ type OXFNotifyIdleMethod
    typedef void( *OXFNotifyIdleMethod)(void); 
    //#]
    
    ////    Operations    ////
    
    // Design level debugging support - de register a RTOS thread that is not associated with an IOxfActive object.
    // Argument void * aomArg(theHandle) :
    // The RTOS thread handle
    //## operation animDeregisterForeignThread(void *)
    static void animDeregisterForeignThread(void * aomArg(theHandle));
    
    // Design level debugging support - register a RTOS thread that is not associated with an IOxfActive object
    // Argument const Rhp_const_char_pt aomArg(name) :
    // The RTOS thread name
    // Argument void * aomArg(theHandle) :
    // The RTOS thread handle
    //## operation animRegisterForeignThread(Rhp_const_char_pt,void *)
    static void animRegisterForeignThread(const Rhp_const_char_pt aomArg(name), void * aomArg(theHandle));
    
    //## operation cleanup()
    static void cleanup(void);
    
    // Delay the calling thread for "t" units (currently milliseconds)
    // Argument OxfTimeUnit aTime :
    // The delay time
    //## operation delay(OxfTimeUnit)
    static void delay(OxfTimeUnit aTime);
    
    // Cleanup the framework objects
    //## operation end()
    static void end(void);
    
    // initialize the framework (timer, main thread, animation and etc.)
    // Argument const Rhp_int32_t aomArg(numProgArgs) = 0 :
    // The number of argument passed in progArgs
    // Argument Rhp_char_pt* aomArg(progArgs) = NULL :
    // An argument list (similar to argv of the main)
    // Argument const Rhp_uint32_t aomArg(defaultPort) = 0U :
    // The animation port
    // Argument const Rhp_const_char_pt aomArg(defaultHost) = NULL :
    // Rhapsody host IP
    // Argument OxfTimeUnit ticktime = OMTimerManagerDefaults::defaultTicktime :
    // The framework tick-timer resolution
    // Argument Rhp_uint32_t maxTM = OMTimerManagerDefaults::defaultMaxTM :
    // The max number of timeouts that can be waiting simultaneously
    // Argument bool isRealTimeModel = true :
    // The framework tick-timer mode (real time when true or simulated otherwise)
    //## operation initialize(Rhp_int32_t,Rhp_char_pt,Rhp_uint32_t,const Rhp_const_char_pt ,OxfTimeUnit,Rhp_uint32_t,bool)

    #ifdef _OMINSTRUMENT
    static bool initialize(const Rhp_int32_t aomArg(numProgArgs) = 0, Rhp_char_pt* aomArg(progArgs) = NULL
, const Rhp_uint32_t aomArg(defaultPort) = 0U, const Rhp_const_char_pt aomArg(defaultHost) = NULL, OxfTimeUnit ticktime
 = OMTimerManagerDefaults::defaultTicktime, Rhp_uint32_t maxTM = OMTimerManagerDefaults::defaultMaxTM, bool
 isRealTimeModel = true);
    #endif // _OMINSTRUMENT
    
    
    // initialize the non-animated framework (timer, main thread, and etc.)
    // Argument OxfTimeUnit ticktime = OMTimerManagerDefaults::defaultTicktime :
    // The framework tick-timer resolution
    // Argument Rhp_uint32_t maxTM = OMTimerManagerDefaults::defaultMaxTM :
    // The max number of timeouts that can be waiting simultaneously
    // Argument bool isRealTimeModel = true :
    // The framework tick-timer mode (real time when true or simulated otherwise)
    //## operation initialize(OxfTimeUnit,Rhp_uint32_t,bool)
    #ifndef _OMINSTRUMENT
    static bool initialize(OxfTimeUnit ticktime = OMTimerManagerDefaults::defaultTicktime, Rhp_uint32_t maxTM
 = OMTimerManagerDefaults::defaultMaxTM, bool isRealTimeModel = true);
    #endif // _OMINSTRUMENT
    
    
    //## operation notifyEvent()
    inline static void notifyEvent(void) {
        //#[ operation notifyEvent()
        if(notifyEventCbkfunc != NULL)
        	(*(notifyEventCbkfunc))();
        //#]
    }
    
    //## operation notifyIdle()
    inline static void notifyIdle(void) {
        //#[ operation notifyIdle()
        if(notifyIdleCbkfunc != NULL)
        	(*(notifyIdleCbkfunc))();
        //#]
    }
    
    // getter & setter for the framework memory manager
    // set the framework memory manager, allowed only before any memory allocation request was made
    // Argument IOxfMemoryAllocator* memoryManager :
    // The plug-in memory manager
    //## operation setMemoryManager(IOxfMemoryAllocator)
    static bool setMemoryManager(IOxfMemoryAllocator* memoryManager);
    
    //## operation setNotifyEventCbk(OXFNotifyEventMethod)
    static void setNotifyEventCbk(OXFNotifyEventMethod func);
    
    //## operation setNotifyIdleCbk(OXFNotifyIdleMethod)
    static void setNotifyIdleCbk(OXFNotifyIdleMethod func);
    
    // setting of the  default active class is allowed only before OXF::init() is called.
    // Argument IOxfActive* anActive :
    // The alternative default active class
    //## operation setTheDefaultActiveClass(IOxfActive)
    static bool setTheDefaultActiveClass(IOxfActive* anActive);
    
    // setting the low level timers factory is allowed only before OXF::init() is called.
    // it is allowed to be set only once of the entire life-time of the application
    // Argument IOxfTickTimerFactory* theFactory :
    // The tick-timer factory
    //## operation setTheTickTimerFactory(IOxfTickTimerFactory)
    static bool setTheTickTimerFactory(IOxfTickTimerFactory* theFactory);
    
    // Start the framework default event loop
    // Argument bool doFork = false :
    // The fork flag
    // When false the framework is expected to use the thread that the framework was initialized on.
    // Otherwise a new RTOS thread is created.
    //## operation start(bool,Rhp_int32_t)
    static void start(bool doFork = false, const Rhp_int32_t callStck = OMOSThread::DefaultStackSize);
    
    // Activate the global system support in explicit reactive instances deletion (delete <instance> instead of <instance>->terminate())
    //## operation supportExplicitReactiveDeletion()
    static void supportExplicitReactiveDeletion(void);
    
    ////    Additional operations    ////
    
    //## auto_generated
    static IOxfActive* getTheDefaultActiveClass(void);
    
    //## auto_generated
    static IOxfMemoryAllocator* getMemoryManager(void);
    
    //## auto_generated
    static IOxfTickTimerFactory* getTheTickTimerFactory(void);
    
    ////    Attributes    ////
    
    static frmThreadAffinities_t frmThreadAffinities;		//## attribute frmThreadAffinities
    

private :

    static OXFNotifyEventMethod notifyEventCbkfunc;		//## attribute notifyEventCbkfunc
    
    static OXFNotifyIdleMethod notifyIdleCbkfunc;		//## attribute notifyIdleCbkfunc
    
    // The framework default active class (the default event loop)
    static IOxfActive* theDefaultActiveClass;		//## attribute theDefaultActiveClass
    
    // The framework memory manager
    static IOxfMemoryAllocator* theMemoryManager;		//## attribute theMemoryManager
    
    // A low-level timer factory -
    // if the user sets the factory, these timers will be used instead of the OSAL timers
    static IOxfTickTimerFactory* theTickTimerFactory;		//## attribute theTickTimerFactory
    
    static bool theTickTimerFactoryWasSet;		//## attribute theTickTimerFactoryWasSet
    
};

#endif



