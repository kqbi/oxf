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



