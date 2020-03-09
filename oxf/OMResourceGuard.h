//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: OMResourceGuard
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


#ifndef OMResourceGuard_H
#define OMResourceGuard_H

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

//## class OMResourceGuard
// Enter-Exit object for definition of a critical section lock/unlock (the lock is done on the constructor and the unlock on the destructor)
//#[ ignore
#ifndef OM_NO_TEMPLATES_USAGE


//#]
template <class GUARD_TYPE> class OMResourceGuard {
    ////    Constructors and destructors    ////
    
public :

    // create a resource guard with the specified guard
    // Argument const GUARD_TYPE& theGuard :
    // the guard object
    // Argument bool aomArg(instrument) = true :
    // Instrumentation support - when true notify about status changes
    //## operation OMResourceGuard(const GUARD_TYPE&,bool (instrument))
    inline OMResourceGuard(const GUARD_TYPE& theGuard, bool aomArg(instrument) = true) : guard(theGuard) {
        //#[ operation OMResourceGuard(const GUARD_TYPE&,bool (instrument))
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
    // Argument const OMResourceGuard<GUARD_TYPE>& other :
    // The resource guard to copy
    //## operation OMResourceGuard(const OMResourceGuard<GUARD_TYPE>&)
    explicit inline OMResourceGuard(const OMResourceGuard<GUARD_TYPE>& other) : guard(other.guard)  {
        //#[ operation OMResourceGuard(const OMResourceGuard<GUARD_TYPE>&)
        //#]
    }
    

public :

    // Cleanup
    //## operation ~OMResourceGuard()
    inline virtual ~OMResourceGuard(void) {
        //#[ operation ~OMResourceGuard()
        guard.unlock();
        //#]
    }
    
    ////    Operations    ////
    

private :

    // disable assignment operator
    // Argument const OMResourceGuard<GUARD_TYPE>& /**/ :
    // The resource guard to copy
    //## operation operator=(const OMResourceGuard<GUARD_TYPE>&)
    inline OMResourceGuard<GUARD_TYPE>& operator=(const OMResourceGuard<GUARD_TYPE>& /**/) {
        //#[ operation operator=(const OMResourceGuard<GUARD_TYPE>&)
        return *this;
        //#]
    }
    
    ////    Attributes    ////
    
    // The guard object
    // Note that the guard lock() & unlock() must be const
    const GUARD_TYPE& guard;		//## attribute guard
    
};
//#[ ignore

#endif // OM_NO_TEMPLATES_USAGE
//#]

//## package Design::oxf::Services::Guards

//## class OMResourceGuard

#endif



