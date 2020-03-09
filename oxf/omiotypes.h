//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: omiotypes
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


#ifndef omiotypes_H
#define omiotypes_H

//## dependency DllMacros
#include "rp_framework_dll_definition.h"
//## dependency STLMacros
#if ((defined OM_STL) || (defined OM_USE_STL))
#include "OXFSTLMacros.h"
#endif // ((defined OM_STL) || (defined OM_USE_STL))
//## package Design::oxf::Services::Types::omiotypes


//#[ ignore
// C++ iostream types and constants definitions.
// The definitions includes or avoid the std namespace based on the OM_STL definition.
//#]

// Forward declaration to STL io types
//#[ type iosfwd
#if ((defined OM_STL) || (defined OM_USE_STL))
#include <iosfwd>
#endif // ((defined OM_STL) || (defined OM_USE_STL))
//#]

// Definition of STD_NAMESPACE when it is not defined by the include to STLMacros
//#[ type STD_NAMESPACE
#ifndef STD_NAMESPACE
#define STD_NAMESPACE
#endif // STD_NAMESPACE
//#]

// cerr definition
//#[ type omcerr
#define omcerr STD_NAMESPACE cerr
//#]

// cin definition
//#[ type omcin
#define omcin STD_NAMESPACE cin
//#]

// cout definition
//#[ type omcout
#define omcout STD_NAMESPACE cout
//#]

// endl definition
//#[ type omendl
#define omendl STD_NAMESPACE endl
//#]

// ends definition
//#[ type omends
#define omends STD_NAMESPACE ends
//#]

// flush definition
//#[ type omflush
#define omflush STD_NAMESPACE flush
//#]

// hex definition
//#[ type omhex
#define omhex STD_NAMESPACE hex
//#]

// ifstream definition
//#[ type omifstream
#define omifstream STD_NAMESPACE ifstream
//#]

// istream definition
//#[ type omistream
#define omistream STD_NAMESPACE istream
//#]

// istrstream definition
//#[ type omistrstream
#define omistrstream STD_NAMESPACE istrstream
//#]

// ofstream definition
//#[ type omofstream
#define omofstream STD_NAMESPACE ofstream
//#]

// istream definition
//#[ type omostream
#define omostream STD_NAMESPACE ostream
//#]

// ostrstream definition
//#[ type omostrstream
#define omostrstream STD_NAMESPACE ostrstream
//#]

#endif



