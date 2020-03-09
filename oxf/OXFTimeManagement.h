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


#ifndef OXFTimeManagement_H
#define OXFTimeManagement_H

//## dependency addTypes
#include "OXFAddTypes.h"
//## dependency IOxfTickTimerFactory
#ifndef OM_NO_TEMPLATES_USAGE
#include "IOxfTickTimerFactory.h"
#endif // OM_NO_TEMPLATES_USAGE

//## dependency IOxfTimeout
class IOxfTimeout;

//## auto_generated
class OMDelay;

//## dependency OMTimeout
class OMTimeout;

//## auto_generated
class OMTimerManager;

//## auto_generated
class OMTimerManagerDefaults;

//## dependency OXF
class OXF;

//## package Design::oxf::Services::Time::TimeManagement


//#[ ignore
// The time services implementation.
// This package does not contain tick-timers which are part of the adapters.
//#]

// typedef of IOxfTickTimerFactory for backward compatibility
//## type OMAbstractTickTimerFactory
//#[ ignore
#ifndef OM_NO_TEMPLATES_USAGE

//#]
typedef IOxfTickTimerFactory OMAbstractTickTimerFactory;
//#[ ignore

#endif // OM_NO_TEMPLATES_USAGE
//#]

// Less than timeouts compare that compares two timeouts based on the due time.
// Used to sort & find the timeouts collection of the timer manager.
// Argument const IOxfTimeout& t1 :
// The source timeout
// Argument const IOxfTimeout& t2 :
// The other timeout
//## operation operator <(IOxfTimeout,IOxfTimeout)
bool operator <(const IOxfTimeout& t1, const IOxfTimeout& t2);

// Equal to timeouts compare that compares two timeouts based on the due time.
// Used to sort & find the timeouts collection of the timer manager.
// Argument const IOxfTimeout& t1 :
// The source timeout
// Argument const IOxfTimeout& t2 :
// The other timeout
//## operation operator ==(IOxfTimeout,IOxfTimeout)
bool operator ==(const IOxfTimeout& t1, const IOxfTimeout& t2);

// Greater than timeouts compare that compares two timeouts based on the due time.
// Used to sort & find the timeouts collection of the timer manager.
// Argument const IOxfTimeout& t1 :
// The source timeout
// Argument const IOxfTimeout& t2 :
// The other timeout
//## operation operator >(IOxfTimeout,IOxfTimeout)
bool operator >(const IOxfTimeout& t1, const IOxfTimeout& t2);

#endif



