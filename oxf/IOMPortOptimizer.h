//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: IOMPortOptimizer
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


#ifndef IOMPortOptimizer_H
#define IOMPortOptimizer_H

//## dependency FRAMEWORK_DLL
#include "rp_framework_dll_definition.h"
//## package Design::oxf::Services::Ports::PortsOptimization

//## class IOMPortOptimizer
class RP_FRAMEWORK_DLL IOMPortOptimizer {
    ////    Operations    ////
    
public :

    //## operation Cleanup()
    virtual void Cleanup(void) = 0;
    
    //## operation Optimize()
    virtual void Optimize(void) = 0;
    
};

#endif



