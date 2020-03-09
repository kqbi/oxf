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



//## auto_generated
#include "OMUnicodeHelper.h"
//## package Design::oxf::Services::Unicode

//## class OMUnicodeHelper

//#[ ignore
#ifdef _OM_UNICODE_ONLY

//#]


size_t OMUnicodeHelper::ctow(wchar_t* wcstr, const char* cstr, size_t count) {
    //#[ operation ctow(wchar_t,char*,size_t)
    for (size_t pos = 0; pos < count; pos++) {
    	wcstr[pos] = cstr[pos];
    }
    return count;
    //#]
}

Rhp_int32_t OMUnicodeHelper::toupper(const Rhp_int32_t aCharacter) {
    //#[ operation toupper(Rhp_int32_t)
    Rhp_int32_t res = aCharacter;
    if ((aCharacter >= 97) && (aCharacter <= 122)) {
    	res = (aCharacter - 32);
    }
    return res;
    //#]
}

size_t OMUnicodeHelper::wtoc(char* cstr, const wchar_t* wcstr, size_t count) {
    //#[ operation wtoc(char*,wchar_t,size_t)
    for (size_t pos = 0; pos < count; pos++) {
    	cstr[pos] = static_cast<Rhp_char_t>(wcstr[pos]);
    }
    return count;
    //#]
}


//#[ ignore

#endif // _OM_UNICODE_ONLY
//#]




