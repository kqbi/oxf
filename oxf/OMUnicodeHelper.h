//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: OMUnicodeHelper
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


#ifndef OMUnicodeHelper_H
#define OMUnicodeHelper_H

//## dependency DllMacros
#include "rp_framework_dll_definition.h"
//## dependency MISRA_Cpp_Types
#include "OXFMISRA_Cpp_Types.h"
//## package Design::oxf::Services::Unicode

//## class OMUnicodeHelper

//#[ ignore
#ifdef _OM_UNICODE_ONLY

//#]


// A utility class for unicode resolution
class RP_FRAMEWORK_DLL OMUnicodeHelper {
    ////    Operations    ////
    
public :

    // converts the char* string to the wide character string
    // returns size of the wide character string
    // Argument wchar_t* wcstr :
    // the output wide character string
    // Argument const char* cstr :
    // the input string
    // Argument size_t count :
    // length of cstr
    //## operation ctow(wchar_t,char*,size_t)
    static size_t ctow(wchar_t* wcstr, const char* cstr, size_t count);
    
    // Returns the c character, converted to upper case
    // If the c is already uppercased, it returns the same value
    // Argument const Rhp_int32_t aCharacter :
    // A character
    //## operation toupper(Rhp_int32_t)
    static Rhp_int32_t toupper(const Rhp_int32_t aCharacter);
    
    // converts the wcstr wide character string to char* string
    // returns size of cstr
    // Argument char* cstr :
    // the output string
    // Argument const wchar_t* wcstr :
    // wide character string
    // Argument size_t count :
    // length of wcstr
    //## operation wtoc(char*,wchar_t,size_t)
    static size_t wtoc(char* cstr, const wchar_t* wcstr, size_t count);
    
};


//#[ ignore

#endif // _OM_UNICODE_ONLY
//#]

#endif



