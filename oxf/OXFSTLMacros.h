//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: STLMacros
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


#ifndef OXFSTLMacros_H
#define OXFSTLMacros_H

//## package Design::oxf::Services::Macros::STLMacros


//#[ ignore
// STL support macros
//#]

// Use the std namespace
//#[ type OM_USE_STL
#ifdef OM_USE_STL
namespace std {}
using namespace std;
#define OM_STL
#endif // OM_USE_STL
//#]

// Some compilers don't support the std:: namespace
// You may omit it from the signature by compiling your application with NO_STD_NAMESPACE compiler switch
//#[ type STD_NAMESPACE
#define STD_NAMESPACE std::
#ifdef NO_STD_NAMESPACE
#undef STD_NAMESPACE
#define STD_NAMESPACE
#endif // NO_STD_NAMESPACE
//#]

#endif



