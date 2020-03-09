//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: DllGuards
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


#ifndef OXFDllGuards_H
#define OXFDllGuards_H

//## dependency OXFURefManager
#ifdef  FRAMEWORK_DLL
#include "OXFURefManager.h"
#endif // FRAMEWORK_DLL

//## auto_generated
class OXFRefManager;

//## package Design::oxf::Services::Guards::DllGuards


//#[ ignore
// OXF shared library initialization guards.
// Used to prevent repeated initialization and premature cleanup of the framework singletons by various users.
//#]


//#[ ignore
#ifdef FRAMEWORK_DLL

//#]


//#[ type RefManagerType
#ifdef OM_NO_TEMPLATES_USAGE
typedef OXFURefManager  RefManagerType;
#else
typedef OXFRefManager  RefManagerType;
#endif
//#]

//## attribute theRefManager
extern RefManagerType theRefManager;


//#[ ignore

#endif // FRAMEWORK_DLL
//#]

#endif



