//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: DllMacros
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


#ifndef rp_framework_dll_definition_H
#define rp_framework_dll_definition_H

//## auto_generated
#include <omosconfig.h>
//## package Design::oxf::Services::Macros::DllMacros


//#[ ignore
// OXF as a shared library macros
//#]

// The framework DLL export macros
//#[ type FRAMEWORK_DLL
#ifdef OM_ENABLE_DLL
#ifndef RP_FRAMEWORK_DLL
#ifndef FRAMEWORK_DLL

#define RP_FRAMEWORK_DLL
#define RP_FRAMEWORK_DLLV(type) type

#else // !FRAMEWORK_DLL

#define RP_FRAMEWORK_DLLV(type) type RP_FRAMEWORK_DLL

#ifdef RP_FRAMEWORK_EXPORTS
#define RP_FRAMEWORK_DLL __declspec(dllexport) 
#else // !RP_FRAMEWORK_EXPORTS
#define RP_FRAMEWORK_DLL __declspec(dllimport)

#endif // RP_FRAMEWORK_EXPORTS 
#endif // FRAMEWORK_DLL 
#endif // RP_FRAMEWORK_DLL 

#else // !OM_ENABLE_DLL 
#define RP_FRAMEWORK_DLL 
#define RP_FRAMEWORK_DLLV(type) type
#endif // OM_ENABLE_DLL 
//#]

#endif



