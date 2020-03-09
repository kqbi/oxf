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


#ifndef OMNotifier_H
#define OMNotifier_H

//## dependency DllMacros
#include "rp_framework_dll_definition.h"
//## dependency MISRA_Cpp_Types
#include "OXFMISRA_Cpp_Types.h"
//## package Design::oxf::Services::IO

//## class OMNotifier
// This class is responsible for sending of notifications to the user
class RP_FRAMEWORK_DLL OMNotifier {
    ////    Constructors and destructors    ////
    
public :

    //## auto_generated
    ~OMNotifier(void);
    
    ////    Operations    ////
    
    // Sent a message to the error output
    // Argument Rhp_const_char_pt msg :
    // The message
    //## operation notifyToError(Rhp_const_char_pt)
    static void notifyToError(Rhp_const_char_pt msg);
    
    // Sent a message to the standard output
    // Argument Rhp_const_char_pt msg :
    // The message
    //## operation notifyToOutput(Rhp_const_char_pt)
    static void notifyToOutput(Rhp_const_char_pt msg);
    
};

#endif



