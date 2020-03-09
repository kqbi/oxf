//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: OMMemoryManagerWrapper
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
#include "OMMemoryManagerWrapper.h"
//## dependency MemoryManagerMacros
#include "OXFMemoryManagerMacros.h"
//## dependency OMMemoryManager
#include "ommemorymanager.h"
//## package Design::oxf::Services::MemoryManagement::Manager

//## class OMMemoryManagerWrapper
OMMemoryManagerWrapper::~OMMemoryManagerWrapper(void) {
}

void OMMemoryManagerWrapper::Delete(void * obj, const size_t size) {
    //#[ operation Delete(void *,size_t)
    Rhp_char_pt tmp = reinterpret_cast<Rhp_char_pt>(obj);
    OMDELETE(tmp, size);
    //#]
}

void * OMMemoryManagerWrapper::getMemory(const Rhp_uint64_t size) {
    //#[ operation getMemory(Rhp_uint64_t)
    return OMGET_MEMORY(size);
    //#]
}




