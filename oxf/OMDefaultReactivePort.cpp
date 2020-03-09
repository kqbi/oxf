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



//## auto_generated
#include "OMDefaultReactivePort.h"
//## package Design::oxf::Services::Ports

//## class OMDefaultReactivePort
OMDefaultReactivePort::OMDefaultReactivePort(void) {
    //#[ operation OMDefaultReactivePort()
    InBound.setPort(this);
    //#]
}

OMDefaultReactivePort::~OMDefaultReactivePort(void) {
}

OMDefaultInBound* OMDefaultReactivePort::getInBound(void) const {
    //#[ operation getInBound() const
    return const_cast<OMDefaultInBound*>(&InBound);
    //#]
}

IOxfReactive* OMDefaultReactivePort::getItsDefaultProvidedInterface(void) const {
    //#[ operation getItsDefaultProvidedInterface() const
    return getInBound();
    //#]
}

IOxfReactive* OMDefaultReactivePort::getItsDefaultRequiredInterface(void) const {
    //#[ operation getItsDefaultRequiredInterface() const
    return getOutBound();
    //#]
}

OMDefaultOutBound* OMDefaultReactivePort::getOutBound(void) const {
    //#[ operation getOutBound() const
    return const_cast<OMDefaultOutBound*>(&OutBound);
    //#]
}

void OMDefaultReactivePort::setItsDefaultProvidedInterface(IOxfReactive* reactive) {
    //#[ operation setItsDefaultProvidedInterface(IOxfReactive)
    InBound.setItsDefaultProvidedInterface(reactive);
    //#]
}

void OMDefaultReactivePort::setItsDefaultRequiredInterface(IOxfReactive* reactive) {
    //#[ operation setItsDefaultRequiredInterface(IOxfReactive)
    OutBound.setItsDefaultRequiredInterface(reactive);
    //#]
}




