//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: OMNotifier
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
#include "OMNotifier.h"
//## dependency BasicTypes
//#[ ignore
#ifdef OM_NOTIFY_USE_IOSTREAM
#ifndef OM_FORCE_IOSTREAM
#define OM_FORCE_IOSTREAM
#endif // !OM_FORCE_IOSTREAM
#elif (defined OM_NOTIFY_USE_STDIO)
#ifdef OM_FORCE_IOSTREAM
#undef OM_FORCE_IOSTREAM
#endif // OM_FORCE_IOSTREAM
#ifndef OM_FROCE_STDIO
#define OM_FROCE_STDIO
#endif // !OM_FROCE_STDIO
#endif // OM_NOTIFY_USE_IOSTREAM
//#]
#include "rawtypes.h"
//## package Design::oxf::Services::IO

//## class OMNotifier
OMNotifier::~OMNotifier(void) {
}

void OMNotifier::notifyToError(Rhp_const_char_pt msg) {
    //#[ operation notifyToError(Rhp_const_char_pt)
    #ifndef OM_NOTIFY_SILENT
    if (msg != NULL) {
    #ifdef USE_IOSTREAM
    #ifdef NO_STDERR
    	omcout << msg << omflush;
    #else
    	omcerr << msg << omflush;
    #endif
    #else
    #ifdef USE_STDIO
    	fprintf(stderr,"%s",msg);
    	fflush(stderr);
    #endif // USE_STDIO
    #endif // USE_IOSTREAM
    }
    #endif // OM_NOTIFY_SILENT
    //#]
}

void OMNotifier::notifyToOutput(Rhp_const_char_pt msg) {
    //#[ operation notifyToOutput(Rhp_const_char_pt)
    #ifndef OM_NOTIFY_SILENT
    if (msg != NULL) {
    #ifdef USE_IOSTREAM
    	omcout << msg << omflush;
    #else
    #ifdef USE_STDIO
    	fprintf(stdout,"%s",msg);
    	fflush(stdout);
    #endif // USE_STDIO
    #endif // USE_IOSTREAM
    }
    #endif // OM_NOTIFY_SILENT
    //#]
}




