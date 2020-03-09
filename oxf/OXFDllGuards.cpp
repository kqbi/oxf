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



//## auto_generated
#include "OXFDllGuards.h"
//## dependency MISRA_Cpp_Types
#include "OXFMISRA_Cpp_Types.h"
//## auto_generated
#include "OXFRefManager.h"
//## package Design::oxf::Services::Guards::DllGuards



//#[ ignore
#ifdef FRAMEWORK_DLL

//#]


//## attribute theRefManager
RefManagerType theRefManager;


//#[ ignore
#else
#ifndef lint // ignore the dummy op in lint
// define a dummy function to prevent link warnings due to an empty object
void dummyOXFDllGuardsFunc(Rhp_int32_t& x) {
	++x;
}
#endif //lint
#endif //FRAMEWORK_DLL
//#]




