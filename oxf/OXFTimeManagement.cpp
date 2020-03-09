//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: TimeManagement
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
#include "OXFTimeManagement.h"
//## dependency Events
#include "OXFEvents.h"
//## dependency IOxfTimeout
#include "IOxfTimeout.h"
//## auto_generated
#include "OMDelay.h"
//## dependency OMTimeout
#include "OMTimeout.h"
//## auto_generated
#include "OMTimerManager.h"
//## auto_generated
#include "OMTimerManagerDefaults.h"
//## dependency OXF
#include "oxf.h"
//## package Design::oxf::Services::Time::TimeManagement


//## operation operator <(IOxfTimeout,IOxfTimeout)
bool operator <(const IOxfTimeout& t1, const IOxfTimeout& t2) {
    //#[ operation operator <(IOxfTimeout,IOxfTimeout)
    return (t1.getDueTime() < t2.getDueTime());
    //#]
}

//## operation operator ==(IOxfTimeout,IOxfTimeout)
bool operator ==(const IOxfTimeout& t1, const IOxfTimeout& t2) {
    //#[ operation operator ==(IOxfTimeout,IOxfTimeout)
    bool res = false;
    if ((t1.isCanceled()) && (t2.isCanceled()))
    {
    	res = true;
    }
    else
    {
    	res = (t1.getDueTime() == t2.getDueTime());
    }
    return res;
    //#]
}

//## operation operator >(IOxfTimeout,IOxfTimeout)
bool operator >(const IOxfTimeout& t1, const IOxfTimeout& t2) {
    //#[ operation operator >(IOxfTimeout,IOxfTimeout)
    return (t1.getDueTime() > t2.getDueTime());
    //#]
}




