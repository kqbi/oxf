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



//## auto_generated
#include "OXFURefManager.h"
//## dependency AnimServices
//#[ ignore
#ifdef _OMINSTRUMENT

//#]
#include <aom/AnimServices.h>
//#[ ignore

#endif // _OMINSTRUMENT
//#]
//## link theMutex
#include "os.h"
//## package Design::oxf::Services::Guards::DllGuards

//## class OXFURefManager

//#[ ignore
#ifdef FRAMEWORK_DLL


//#]


OXFURefManager::OXFURefManager(void) : OMProtected(), oxfStarted(false), totalReferences(0), theMutex(NULL) {
    //#[ operation OXFURefManager()
    theMutex = OMOSFactory::instance()->createOMOSMutex();
    //#]
}

OXFURefManager::OXFURefManager(const OMProtected& theGuard, bool aomArg) : OMProtected(), oxfStarted(false), 
totalReferences(0) {
    //#[ operation OXFURefManager(OMProtected,bool)
    //#]
}

OXFURefManager::~OXFURefManager(void) {
    //#[ operation ~OXFURefManager()
    delete theMutex;
    theMutex = NULL;
    //#]
    cleanUpRelations();
}

Rhp_int64_t OXFURefManager::Decrement(void) {
    //#[ operation Decrement()
    if (totalReferences > 0) {
    	--totalReferences;
    }
    return totalReferences;
    //#]
}

Rhp_int64_t OXFURefManager::Increment(void) {
    //#[ operation Increment()
    return ++totalReferences;
    //#]
}

void OXFURefManager::lock(void) const {
    //#[ operation lock() const
    if (theMutex != NULL) {
    	theMutex->lock();
    }
    //#]
}

void OXFURefManager::unlock(void) const {
    //#[ operation unlock() const
    if (theMutex != NULL) {
    	theMutex->unlock();
    }
    //#]
}

bool OXFURefManager::getOxfStarted(void) const {
    return oxfStarted;
}

void OXFURefManager::setOxfStarted(bool p_oxfStarted) {
    oxfStarted = p_oxfStarted;
}

Rhp_int32_t OXFURefManager::getCount(void) const {
    return totalReferences;
}

void OXFURefManager::cleanUpRelations(void) {
    if(theMutex != NULL)
        {
            theMutex = NULL;
        }
}


//#[ ignore

#else
#ifndef lint
void OXFURefManager_preventLinkWarnings(Rhp_int32_t& i) {
	++i;
}
#endif // !lint
#endif //FRAMEWORK_DLL
//#]




