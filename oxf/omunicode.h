//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: Unicode
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


#ifndef omunicode_H
#define omunicode_H

//## dependency OMUnicodeHelper
#include "OMUnicodeHelper.h"
//## package Design::oxf::Services::Unicode


//#[ ignore
// Unicode support
//#]


//#[ ignore
#ifdef _OM_UNICODE_ONLY

//#]


// OMUnicodeHelper::ctow()
//#[ type OMctow
#define OMctow OMUnicodeHelper::ctow
//
//#]

// OMUnicodeHelper::toupper()
//#[ type OMtoupper
#define OMtoupper OMUnicodeHelper::toupper
//
//#]

// OMUnicodeHelper::wtoc()
//#[ type OMwtoc
#define OMwtoc OMUnicodeHelper::wtoc
//
//#]


//#[ ignore

#endif // _OM_UNICODE_ONLY
//#]

#endif



