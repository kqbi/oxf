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



//## auto_generated
#include "omprotected.h"
//## dependency AnimServices
#ifdef _OMINSTRUMENT
#include <aom/AnimServices.h>
#endif //_OMINSTRUMENT
//## link theMutex
#include "os.h"
//## package Design::oxf::Services::Guards

//## class OMProtected
OMProtected::OMProtected(void) : theMutex(NULL) {
    //#[ operation OMProtected()
    initializeMutex();
    //#]
}

OMProtected::OMProtected(const OMProtected& omProtected) {
    //#[ operation OMProtected(const OMProtected& )
    *this = omProtected;
    //#]
}

void OMProtected::cleanupMutex(void) {
    //#[ operation cleanupMutex()
    if (theMutex != NULL) { 
    /* This is a framework that can be configured so that dynamic */
    /* memory allocation is just done during the initialisation phase */
    /*LDRA_INSPECTED 44 S */
    	delete theMutex;
    	theMutex = NULL;
    }
    //#]
}

const OMProtected& OMProtected::getGuard(void) const {
    //#[ operation getGuard() const
    return (*this);
    //#]
}

void OMProtected::initializeMutex(void) {
    //#[ operation initializeMutex()
    if (theMutex == NULL) {
    	theMutex = OMOSFactory::instance()->createOMOSMutex();
    }
    //#]
}

void OMProtected::lock(void) const {
    //#[ operation lock() const
    if (theMutex != NULL) {
    	theMutex->lock();
    }
    //#]
}

OMProtected& OMProtected::operator=(const OMProtected& omProtected) {
    //#[ operation operator=(const OMProtected& )
    theMutex = NULL;
    if (omProtected.theMutex!= NULL) {
    	initializeMutex();
    }
    return *this;
    //#]
}

void OMProtected::unlock(void) const {
    //#[ operation unlock() const
    if (theMutex != NULL) {
    	theMutex->unlock();
    }
    //#]
}




