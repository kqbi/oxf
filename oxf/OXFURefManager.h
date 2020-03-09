//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: OXFURefManager
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


#ifndef OXFURefManager_H
#define OXFURefManager_H

//## class OXFURefManager
#include "omprotected.h"
//## dependency AnimServices
//#[ ignore
#ifdef _OMINSTRUMENT

//#]
class AnimServices;

//#[ ignore

#endif // _OMINSTRUMENT
//#]
//## link theMutex
class OMOSMutex;

//## package Design::oxf::Services::Guards::DllGuards

//## class OXFURefManager

//#[ ignore
#ifdef FRAMEWORK_DLL

//#]


// This class is used to maintain the references for OXF::init(..) call in DLL version of framework
class OXFURefManager : public OMProtected {
    ////    Constructors and destructors    ////
    
public :

    // Initialize
    //## operation OXFURefManager()
    OXFURefManager(void);
    
    //## operation OXFURefManager(OMProtected,bool)
    OXFURefManager(const OMProtected& theGuard, bool aomArg);
    
    // Cleanup
    //## operation ~OXFURefManager()
    ~OXFURefManager(void);
    
    ////    Operations    ////
    
    // Reduce the count of the framework users
    //## operation Decrement()
    Rhp_int64_t Decrement(void);
    
    // Increase  the count of the framework users
    //## operation Increment()
    Rhp_int64_t Increment(void);
    
    // Lock the mutex
    //## operation lock() const
    void lock(void) const;
    
    // Unlock the mutex
    //## operation unlock() const
    void unlock(void) const;
    
    ////    Additional operations    ////
    
    //## auto_generated
    bool getOxfStarted(void) const;
    
    //## auto_generated
    void setOxfStarted(bool p_oxfStarted);
    
    //## auto_generated
    Rhp_int32_t getCount(void) const;
    

protected :

    //## auto_generated
    void cleanUpRelations(void);
    
    ////    Attributes    ////
    

private :

    // indicate if the OXF default active class is running (OXF::start() was called)
    bool oxfStarted;		//## attribute oxfStarted
    
    // reference count to the number of calls
    Rhp_int32_t totalReferences;		//## attribute totalReferences
    
    ////    Relations and components    ////
    
    // The RTOS mutex
    OMOSMutex* theMutex;		//## link theMutex
    
};


//#[ ignore

#endif // FRAMEWORK_DLL
//#]

#endif



