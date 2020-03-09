//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: OXFRefLock
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


#ifndef OMUResourceGuard_H
#define OMUResourceGuard_H

//## dependency AnimServices
//#[ ignore
#ifdef _OMINSTRUMENT
//#]
#include <aom/AnimServices.h>
//#[ ignore

#endif //_OMINSTRUMENT
//#]
//## dependency BasicTypes
#include "rawtypes.h"
//## package Design::oxf::Services::Guards

//## class OMUResourceGuard
// Enter-Exit object for definition of a critical section lock/unlock (the lock is done on the constructor and the unlock on the destructor)
class OMUResourceGuard {
    ////    Constructors and destructors    ////
    
public :

    // create a resource guard with the specified guard
    // Argument const OMProtected& theGuard :
    // the guard object
    // Argument bool aomArg(instrument) = true :
    // Instrumentation support - when true notify about status changes
    //## operation OMUResourceGuard(OMProtected,bool (instrument))
    inline OMUResourceGuard(const OMProtected& theGuard, bool aomArg(instrument) = true) : guard(theGuard) {
        //#[ operation OMUResourceGuard(OMProtected,bool (instrument))
        #ifdef _OMINSTRUMENT
        if (instrument == true) {
        	AnimServices::notifyMutexLock(false);
        }
        #endif
        
        // lock
        guard.lock();
        
        #ifdef _OMINSTRUMENT
        if (instrument == true) {
        	AnimServices::notifyMutexLock(true);
        }
        #endif
        //#]
    }
    

private :

    // explicitly disable copy CTOR
    // Argument const OMUResourceGuard& other :
    // The resource guard to copy
    //## operation OMUResourceGuard(const OMUResourceGuard&)
    explicit inline OMUResourceGuard(const OMUResourceGuard& other) : guard(other.guard)  {
        //#[ operation OMUResourceGuard(const OMUResourceGuard&)
        //#]
    }
    

public :

    // Cleanup
    //## operation ~OMUResourceGuard()
    inline virtual ~OMUResourceGuard(void) {
        //#[ operation ~OMUResourceGuard()
        guard.unlock();
        //#]
    }
    
    ////    Operations    ////
    

private :

    // disable assignment operator
    // Argument const OMUResourceGuard& /**/ :
    // The resource guard to copy
    //## operation operator=(const OMUResourceGuard&)
    inline OMUResourceGuard& operator=(const OMUResourceGuard& /**/) {
        //#[ operation operator=(const OMUResourceGuard&)
        return *this;
        //#]
    }
    
    ////    Attributes    ////
    
    // The guard object
    // Note that the guard lock() & unlock() must be const
    const OMProtected& guard;		//## attribute guard
    
};

//## type OMGuard
typedef OMUResourceGuard OMGuard;

//## type OXFRefLock
//#[ ignore
#ifdef FRAMEWORK_DLL
#ifdef OM_NO_TEMPLATES_USAGE

//#]
typedef OMUResourceGuard OXFRefLock;
//#[ ignore

#endif // OM_NO_TEMPLATES_USAGE
#endif // FRAMEWORK_DLL

//#]

#endif



