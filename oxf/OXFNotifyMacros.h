//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: NotifyMacros
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


#ifndef OXFNotifyMacros_H
#define OXFNotifyMacros_H

//## dependency OMNotifier
#include "OMNotifier.h"
//## package Design::oxf::Services::Macros::NotifyMacros


//#[ ignore
// Output macros
//#]

// Notify an error message
//#[ type OM_NOTIFY_TO_ERROR
#define OM_NOTIFY_TO_ERROR(msg) OMNotifier::notifyToError(msg)
//#]

// Notify a message
//#[ type OM_NOTIFY_TO_OUTPUT
#define OM_NOTIFY_TO_OUTPUT(msg)	OMNotifier::notifyToOutput(msg)
//#]

#endif



