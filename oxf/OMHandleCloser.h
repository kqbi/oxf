//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: OMHandleCloser
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


#ifndef OMHandleCloser_H
#define OMHandleCloser_H

//## class OMHandleCloser
#include "omreactive.h"
//## classInstance thread
#include "omthread.h"
//## dependency AnimServices
class AnimServices;

//## dependency IOxfActive
class IOxfActive;

//## dependency IOxfEvent
class IOxfEvent;

//## auto_generated
class OMAnimReactive;

//## auto_generated
class OMComponentState;

//## auto_generated
class OMMainThread;

//## auto_generated
class OMOS;

//## auto_generated
class OMOSThread;

//## dependency OMProtected
class OMProtected;

//## dependency OMThreadManager
class OMThreadManager;

//## auto_generated
class OMTimeout;

//## auto_generated
class OMTimerManager;

//## auto_generated
class OXF;

//## package Design::oxf::Services::ResourceManagement

//## class OMHandleCloser
// Provide mechanism for cleanup after thread deletion
class RP_FRAMEWORK_DLL OMHandleCloser : public OMReactive {
public :

    // The RTOS callback function that perform the RTOS thread cleanup
    //#[ type closeHandleFunc
    typedef void  (* closeHandleFunc)(void * ) ;
    //#]
    

//#[ ignore
    // override new & delete operators
    OM_DECLARE_FRAMEWORK_MEMORY_ALLOCATION_OPERATORS
    
    
//#]

    ////    Constructors and destructors    ////
    
public :

    // Initialize
    // Argument closeHandleFunc doCloseHandlePtr = 0 :
    // The callback
    //## operation OMHandleCloser(closeHandleFunc)
    explicit OMHandleCloser(closeHandleFunc doCloseHandlePtr = 0);
    

private :

    // disable copy constructor
    // Argument const OMHandleCloser& other :
    // unused
    //## operation OMHandleCloser(OMHandleCloser)
    explicit OMHandleCloser(const OMHandleCloser& other);
    

public :

    // Cleanup
    //## operation ~OMHandleCloser()
    virtual ~OMHandleCloser(void);
    
    ////    Operations    ////
    
    // sends event to the HandleCloser thread to delete hObject thread
    // Argument void * hObject :
    // The RTOS thread handle
    //## operation genCloseEvent(void *)
    void genCloseEvent(void * hObject);
    
    //## operation getOmosThread()
    //#[ ignore
    #ifdef _OMINSTRUMENT
    
    
    //#]
    inline void * getOmosThread(void) {
        //#[ operation getOmosThread()
        return omosThread;
        //#]
    }
    //#[ ignore
    #endif
    
    //#]
    
    // Get the internal thread
    //## operation getThread() const
    OMThread* getThread(void) const;
    
    // Get the singleton
    //## operation instance()
    static OMHandleCloser* instance(void);
    
    // returns handle closer instance and initializes its doCloseHandle function ptr
    // Argument closeHandleFunc doCloseHandlePtr :
    // The callback
    //## operation instance(closeHandleFunc)
    static OMHandleCloser* instance(closeHandleFunc doCloseHandlePtr);
    
    // Send the OMCloseHandleEvent to itself
    //## operation sendCloseHandleCloserEvent()
    void sendCloseHandleCloserEvent(void);
    
    // Start the statechart
    //## operation startBehavior()
    virtual bool startBehavior(void);
    

private :

    //## operation assureInit()
    void assureInit(void);
    
    // Initialize and get the singleton
    // Argument closeHandleFunc doCloseHandlePtr :
    // The callback
    //## operation getInstance(closeHandleFunc)
    static OMHandleCloser & getInstance(closeHandleFunc doCloseHandlePtr);
    
    // disable assignment operator
    // Argument const OMHandleCloser& other :
    // unused
    //## operation operator=(OMHandleCloser)
    OMHandleCloser& operator=(const OMHandleCloser& other);
    
    ////    Additional operations    ////
    

protected :

    //## auto_generated
    void initStatechart(void);
    
    ////    Attributes    ////
    

private :

    // Indicate that the singleton was destroyed (while exit())
    static bool _singletonDestroyed;		//## attribute _singletonDestroyed
    
    // The cleanup callback function
    closeHandleFunc doCloseHandle;		//## attribute doCloseHandle
    
    //#[ ignore
    #ifdef _OMINSTRUMENT
    
    //#]
    void * omosThread;
    //#[ ignore
    #endif
    
    //#]		//## attribute omosThread
    
    ////    Relations and components    ////
    
    // The handle closer context
    OMThread thread;		//## classInstance thread
    
    ////    Framework operations    ////
    

public :

    // rootState:
    //## statechart_method
    inline RhpBoolean rootState_IN(void) const;
    
    // ready:
    //## statechart_method
    inline RhpBoolean ready_IN(void) const;
    

protected :

    //## statechart_method
    virtual void rootState_entDef(void);
    
    //## statechart_method
    virtual IOxfReactive::TakeEventStatus rootState_processEvent(void);
    
    ////    Framework    ////
    
//#[ ignore
    enum OMHandleCloser_Enum {
        OMNonState = 0,
        ready = 1
    };
    
//#]

private :

//#[ ignore
    OMHandleCloser_Enum rootState_subState;
    
    OMHandleCloser_Enum rootState_active;
    
//#]
};

inline RhpBoolean OMHandleCloser::rootState_IN(void) const {
    return true;
}

inline RhpBoolean OMHandleCloser::ready_IN(void) const {
    return rootState_subState == ready;
}

#endif



