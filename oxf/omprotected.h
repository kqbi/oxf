//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: OMProtected
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


#ifndef omprotected_H
#define omprotected_H

//## dependency BasicTypes
#include "rawtypes.h"
//## dependency GuardMacros
#include "OXFGuardMacros.h"
//## class OMGuard
#include "OMResourceGuard.h"
//## dependency AnimServices
#ifdef _OMINSTRUMENT
class AnimServices;

#endif //_OMINSTRUMENT
//## link theMutex
class OMOSMutex;

//## package Design::oxf::Services::Guards

//## class OMProtected
// A monitor class that uses OMOSMutex as the internal mutex object
class RP_FRAMEWORK_DLL OMProtected {
    ////    Constructors and destructors    ////
    
public :

    // Initialize the object with control over the initialization of the RTOS mutex
    // Argument bool createMutex :
    // When true - initialize the RTOS mutex
    //## operation OMProtected(bool)
    explicit inline OMProtected(bool createMutex) : theMutex(NULL) {
        //#[ operation OMProtected(bool)
        if (createMutex == true) {
        	initializeMutex();
        }
        //#]
    }
    
    // Initialize the object and the RTOS mutex
    //## operation OMProtected()
    OMProtected(void);
    
    //## operation OMProtected(const OMProtected& )
    explicit OMProtected(const OMProtected& omProtected);
    
    // Cleanup
    //## operation ~OMProtected()
    inline virtual ~OMProtected(void) {
        //#[ operation ~OMProtected()
        cleanupMutex();
        //#]
    }
    
    ////    Operations    ////
    
    // Destroy the RTOS mutex
    //## operation cleanupMutex()
    void cleanupMutex(void);
    
    // get the guard object - to allow embedding of OMProtected in OMThread
    //## operation getGuard() const
    virtual const OMProtected& getGuard(void) const;
    
    // Initialize the RTOS mutex
    //## operation initializeMutex()
    void initializeMutex(void);
    
    // Lock the protected object mutex.
    //## operation lock() const
    void lock(void) const;
    
    //## operation operator=(const OMProtected& )
    OMProtected& operator=(const OMProtected& omProtected);
    
    // Unlock the mutex
    //## operation unlock() const
    void unlock(void) const;
    
    ////    Relations and components    ////
    

private :

    // The RTOS mutex
    OMOSMutex* theMutex;		//## link theMutex
    
};


//#[ ignore

#ifdef OM_NO_TEMPLATES_USAGE
#include "OMUResourceGuard.h"
#endif  //OM_NO_TEMPLATES_USAGE

//#]

//## package Design::oxf::Services::Guards

//## class OMGuard

//#[ ignore
#ifndef OM_NO_TEMPLATES_USAGE

//#]


// Enter-exit guard on OMProtected classes
typedef OMResourceGuard<OMProtected> OMGuard;


//#[ ignore
#else
typedef OMUResourceGuard OMGuard;
#endif //  OM_NO_TEMPLATES_USAGE
//#]

//## package Design::oxf::Services::Guards

//## class OMGuard

#endif



