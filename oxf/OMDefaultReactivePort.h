//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: OMDefaultReactivePort
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


#ifndef OMDefaultReactivePort_H
#define OMDefaultReactivePort_H

//## classInstance InBound
#include "OMDefaultInBound.h"
//## classInstance OutBound
#include "OMDefaultOutBound.h"
//## auto_generated
#include "omreactive.h"
//## package Design::oxf::Services::Ports

//## class OMDefaultReactivePort
// default reactive in-out port
class RP_FRAMEWORK_DLL OMDefaultReactivePort {
    ////    Constructors and destructors    ////
    
public :

    // Initialize
    //## operation OMDefaultReactivePort()
    OMDefaultReactivePort(void);
    
    //## auto_generated
    ~OMDefaultReactivePort(void);
    
    ////    Operations    ////
    
    // Get the in bound port
    //## operation getInBound() const
    OMDefaultInBound* getInBound(void) const;
    
    // Get the provided interface
    //## operation getItsDefaultProvidedInterface() const
    IOxfReactive* getItsDefaultProvidedInterface(void) const;
    
    // Get the required interface
    //## operation getItsDefaultRequiredInterface() const
    IOxfReactive* getItsDefaultRequiredInterface(void) const;
    
    // Get the out bound port
    //## operation getOutBound() const
    OMDefaultOutBound* getOutBound(void) const;
    
    // Set the provided interface
    // Argument IOxfReactive* reactive :
    // The provided interface
    //## operation setItsDefaultProvidedInterface(IOxfReactive)
    void setItsDefaultProvidedInterface(IOxfReactive* reactive);
    
    // Set the Required interface
    // Argument IOxfReactive* reactive :
    // The required interface
    //## operation setItsDefaultRequiredInterface(IOxfReactive)
    void setItsDefaultRequiredInterface(IOxfReactive* reactive);
    
    ////    Relations and components    ////
    

protected :

    // in port
    OMDefaultInBound InBound;		//## classInstance InBound
    
    // out port
    OMDefaultOutBound OutBound;		//## classInstance OutBound
    
};

#endif



