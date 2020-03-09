//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: IOMPortConnector
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


#ifndef IOMPortConnector_H
#define IOMPortConnector_H

//## dependency FRAMEWORK_DLL
#include "rp_framework_dll_definition.h"
//## package Design::oxf::Services::Ports::PortsOptimization

//## class IOMPortConnector
template <class TPortInterface> class RP_FRAMEWORK_DLL IOMPortConnector {
    ////    Operations    ////
    
public :

    //## operation setItsTarget(TPortInterface* const)
    virtual void setItsTarget(TPortInterface* const t) = 0;
    
};

//## package Design::oxf::Services::Ports::PortsOptimization

//## class IOMPortConnector

#endif



