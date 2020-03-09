//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: OMDefaultMulticastReactivePort
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


#ifndef OMDefaultMulticastReactivePort_H
#define OMDefaultMulticastReactivePort_H

//## classInstance InBound
#include "OMDefaultMulticastInBound.h"
//## classInstance OutBound
#include "OMDefaultMulticastOutBound.h"
//## package Design::oxf::Services::Ports

//## class OMDefaultMulticastReactivePort
// default reactive in-out port
class OMDefaultMulticastReactivePort {
    ////    Constructors and destructors    ////
    
public :

    // Initialize
    //## operation OMDefaultMulticastReactivePort()
    RP_FRAMEWORK_DLL OMDefaultMulticastReactivePort(void);
    
    //## auto_generated
    ~OMDefaultMulticastReactivePort(void);
    
    ////    Operations    ////
    
    // Set the Required interface
    // Argument IOxfReactive* reactive :
    // The required interface
    //## operation addItsDefaultProvidedInterface(IOxfReactive)
    RP_FRAMEWORK_DLL void addItsDefaultProvidedInterface(IOxfReactive* reactive);
    
    // Set the Required interface
    // Argument IOxfReactive* reactive :
    // The required interface
    //## operation addItsDefaultRequiredInterface(IOxfReactive)
    RP_FRAMEWORK_DLL void addItsDefaultRequiredInterface(IOxfReactive* reactive);
    
    // Get the in bound port
    //## operation getInBound() const
    RP_FRAMEWORK_DLL OMDefaultMulticastInBound* getInBound(void) const;
    
    // Get the provided interface
    //## operation getItsDefaultProvidedInterface() const
    RP_FRAMEWORK_DLL IOxfReactive* getItsDefaultProvidedInterface(void) const;
    
    // Get the required interface
    //## operation getItsDefaultRequiredInterface() const
    RP_FRAMEWORK_DLL IOxfReactive* getItsDefaultRequiredInterface(void) const;
    
    // Get the out bound port
    //## operation getOutBound() const
    RP_FRAMEWORK_DLL OMDefaultMulticastOutBound* getOutBound(void) const;
    
    // Set the provided interface
    // Argument IOxfReactive* reactive :
    // The provided interface
    //## operation setItsDefaultProvidedInterface(IOxfReactive)
    RP_FRAMEWORK_DLL void setItsDefaultProvidedInterface(IOxfReactive* reactive);
    
    // Set the Required interface
    // Argument IOxfReactive* reactive :
    // The required interface
    //## operation setItsDefaultRequiredInterface(IOxfReactive)
    RP_FRAMEWORK_DLL void setItsDefaultRequiredInterface(IOxfReactive* reactive);
    
    ////    Relations and components    ////
    

protected :

    // in port
    OMDefaultMulticastInBound InBound;		//## classInstance InBound
    
    // out port
    OMDefaultMulticastOutBound OutBound;		//## classInstance OutBound
    
};

#endif



