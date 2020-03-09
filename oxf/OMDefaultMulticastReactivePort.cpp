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



//## auto_generated
#include "OMDefaultMulticastReactivePort.h"
//## package Design::oxf::Services::Ports

//## class OMDefaultMulticastReactivePort
OMDefaultMulticastReactivePort::OMDefaultMulticastReactivePort(void) {
    //#[ operation OMDefaultMulticastReactivePort()
    InBound.setPort(this);
    //#]
}

OMDefaultMulticastReactivePort::~OMDefaultMulticastReactivePort(void) {
}

void OMDefaultMulticastReactivePort::addItsDefaultProvidedInterface(IOxfReactive* reactive) {
    //#[ operation addItsDefaultProvidedInterface(IOxfReactive)
    InBound.addItsDefaultProvidedInterface(reactive);
    //#]
}

void OMDefaultMulticastReactivePort::addItsDefaultRequiredInterface(IOxfReactive* reactive) {
    //#[ operation addItsDefaultRequiredInterface(IOxfReactive)
    OutBound.addItsDefaultRequiredInterface(reactive);
    //#]
}

OMDefaultMulticastInBound* OMDefaultMulticastReactivePort::getInBound(void) const {
    //#[ operation getInBound() const
    return const_cast<OMDefaultMulticastInBound*>(&InBound);
    //#]
}

IOxfReactive* OMDefaultMulticastReactivePort::getItsDefaultProvidedInterface(void) const {
    //#[ operation getItsDefaultProvidedInterface() const
    return getInBound();
    //#]
}

IOxfReactive* OMDefaultMulticastReactivePort::getItsDefaultRequiredInterface(void) const {
    //#[ operation getItsDefaultRequiredInterface() const
    return getOutBound();
    //#]
}

OMDefaultMulticastOutBound* OMDefaultMulticastReactivePort::getOutBound(void) const {
    //#[ operation getOutBound() const
    return const_cast<OMDefaultMulticastOutBound*>(&OutBound);
    //#]
}

void OMDefaultMulticastReactivePort::setItsDefaultProvidedInterface(IOxfReactive* reactive) {
    //#[ operation setItsDefaultProvidedInterface(IOxfReactive)
    InBound.setItsDefaultProvidedInterface(reactive);
    //#]
}

void OMDefaultMulticastReactivePort::setItsDefaultRequiredInterface(IOxfReactive* reactive) {
    //#[ operation setItsDefaultRequiredInterface(IOxfReactive)
    OutBound.setItsDefaultRequiredInterface(reactive);
    //#]
}




