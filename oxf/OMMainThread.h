//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: OMMainThread
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


#ifndef OMMainThread_H
#define OMMainThread_H

//## class OMMainThread
#include "omthread.h"
//## dependency AnimServices
class AnimServices;

//## auto_generated
class IOxfTimeout;

//## auto_generated
class OMCore;

//## auto_generated
class OMEvent;

//## auto_generated
class OMOS;

//## auto_generated
class OMOSEventGenerationParams;

//## dependency OMOSThread
class OMOSThread;

//## auto_generated
class OMReactive;

//## auto_generated
class OMThreadManager;

//## auto_generated
class OMTimeout;

//## auto_generated
class OMTimerManager;

//## dependency OXF
class OXF;

//## package Design::oxf::Services::Initialization

//## class OMMainThread
// The default active class for running the application main event loop.
class RP_FRAMEWORK_DLL OMMainThread : public OMThread {
    ////    Constructors and destructors    ////
    
protected :

    // force singleton
    //## operation OMMainThread()
    OMMainThread(void);
    

private :

    // disable copy constructor
    // Argument const OMMainThread& other :
    // The main thread to copy
    //## operation OMMainThread(OMMainThread)
    explicit OMMainThread(const OMMainThread& other);
    

public :

    // Cleanup
    //## operation ~OMMainThread()
    ~OMMainThread(void);
    
    ////    Operations    ////
    
    // override destroyThread(), to disable deletion of statically allocated instance
    // call the cleanupThread() to perform cleanup
    //## operation destroyThread()
    inline virtual void destroyThread(void) {
        //#[ operation destroyThread()
        this->cleanupThread();
        //#]
    }
    
    // Get the 'default active class' singleton instance.
    // Argument bool create = true :
    // When true, attempt to initialize the singleton if it was not created.
    //## operation instance(bool)
    static OMThread* instance(bool create = true);
    
    // Start the thread & the event loop.
    // Argument bool doFork = false :
    // The fork flag
    // When false the framework is expected to use the thread that the framework was initialized on.
    // Otherwise a new RTOS thread is created.
    //## operation startDispatching(bool)
    virtual void startDispatching(bool doFork = false);
    

private :

    //## operation assureInit()
    void assureInit(void);
    
    // actually get the main thread instance
    //## operation getInstance()
    static OMMainThread* getInstance(void);
    
    // disable assignment operator
    // Argument const OMMainThread& other :
    // The main thread to copy
    //## operation operator=(OMMainThread)
    OMMainThread& operator=(const OMMainThread& other);
    
    ////    Additional operations    ////
    

public :

    //## auto_generated
    static void setCallStackSize(Rhp_int32_t p_callStck);
    
    ////    Attributes    ////
    

private :

    static Rhp_int32_t callStck;		//## attribute callStck
    
};

#endif



