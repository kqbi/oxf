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


#ifndef OXFRefLock_H
#define OXFRefLock_H

//## class OXFRefLock
#include "OMResourceGuard.h"
//## dependency OXFRefManager
#include "OXFRefManager.h"
//## package Design::oxf::Services::Guards::DllGuards

//## class OXFRefLock

//#[ ignore
#ifdef FRAMEWORK_DLL
#ifndef OM_NO_TEMPLATES_USAGE
//#]


// enter-exit guard for OXFRefManager
typedef OMResourceGuard<OXFRefManager> OXFRefLock;


//#[ ignore

#endif // OM_NO_TEMPLATES_USAGE
#endif // FRAMEWORK_DLL
//#]

//## package Design::oxf::Services::Guards::DllGuards

//## class OXFRefLock

#endif



