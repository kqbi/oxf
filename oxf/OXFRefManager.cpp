//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: OXFRefManager
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
#include "OXFRefManager.h"
//## link theMutex
#include "os.h"
//## package Design::oxf::Services::Guards::DllGuards

//## class OXFRefManager

//#[ ignore
#ifdef FRAMEWORK_DLL

//#]


OXFRefManager::OXFRefManager(void) : oxfStarted(false), totalReferences(0), theMutex(NULL) {
    //#[ operation OXFRefManager()
    theMutex = OMOSFactory::instance()->createOMOSMutex();
    //#]
}

OXFRefManager::~OXFRefManager(void) {
    //#[ operation ~OXFRefManager()
    delete theMutex;
    theMutex = NULL;
    //#]
    cleanUpRelations();
}

Rhp_int64_t OXFRefManager::Decrement(void) {
    //#[ operation Decrement()
    if (totalReferences > 0) {
    	--totalReferences;
    }
    return totalReferences;
    //#]
}

Rhp_int64_t OXFRefManager::Increment(void) {
    //#[ operation Increment()
    return ++totalReferences;
    //#]
}

void OXFRefManager::lock(void) const {
    //#[ operation lock() const
    if (theMutex != NULL) {
    	theMutex->lock();
    }
    //#]
}

void OXFRefManager::unlock(void) const {
    //#[ operation unlock() const
    if (theMutex != NULL) {
    	theMutex->unlock();
    }
    //#]
}

bool OXFRefManager::getOxfStarted(void) const {
    return oxfStarted;
}

void OXFRefManager::setOxfStarted(bool p_oxfStarted) {
    oxfStarted = p_oxfStarted;
}

Rhp_int64_t OXFRefManager::getCount(void) const {
    return totalReferences;
}

void OXFRefManager::cleanUpRelations(void) {
    if(theMutex != NULL)
        {
            theMutex = NULL;
        }
}


//#[ ignore
#else
#ifndef lint
void OXFRefManager_preventLinkWarnings(Rhp_int32_t& i) {
	++i;
}
#endif // !lint
#endif //FRAMEWORK_DLL
//#]




