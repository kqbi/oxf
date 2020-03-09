//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: OMMemoryManagerSwitchHelper
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
#include "OMMemoryManagerSwitchHelper.h"
//## dependency OMMemoryManagerSwitchHelperImpl
//#[ ignore
#ifdef OM_ENABLE_MEMORY_MANAGER_SWITCH
//#]
#include "OMMemoryManagerSwitchHelperImpl.h"
//#[ ignore

#endif // OM_ENABLE_MEMORY_MANAGER_SWITCH
//#]
//## package Design::oxf::Services::MemoryManagement::Manager

//## class OMMemoryManagerSwitchHelper

//#[ ignore
#if (!defined(OM_NO_FRAMEWORK_MEMORY_MANAGER) && !defined(OMOMATE))

//#]


void OMMemoryManagerSwitchHelper::cleanup(void) const {
    //#[ operation cleanup() const
    #ifdef OM_ENABLE_MEMORY_MANAGER_SWITCH
    OMMemoryManagerSwitchHelperImpl::instance()->cleanup();
    #endif // OM_ENABLE_MEMORY_MANAGER_SWITCH
    //#]
}

bool OMMemoryManagerSwitchHelper::findMemory(const void * ommmswArg(memory)) const {
    //#[ operation findMemory(void *) const
    bool status;
    #ifdef OM_ENABLE_MEMORY_MANAGER_SWITCH
    status = OMMemoryManagerSwitchHelperImpl::instance()->findMemory(memory);
    #else
    status = false;
    #endif // OM_ENABLE_MEMORY_MANAGER_SWITCH
    return status;
    //#]
}

OMMemoryManagerSwitchHelper* OMMemoryManagerSwitchHelper::instance(void) {
    //#[ operation instance()
    static OMMemoryManagerSwitchHelper theMemoryManagerSwitchHelper;
    return &theMemoryManagerSwitchHelper;
    //#]
}

bool OMMemoryManagerSwitchHelper::isLogEmpty(void) const {
    //#[ operation isLogEmpty() const
    bool status;
    #ifdef OM_ENABLE_MEMORY_MANAGER_SWITCH
    status = OMMemoryManagerSwitchHelperImpl::instance()->isLogEmpty();
    #else
    status = true;
    #endif // OM_ENABLE_MEMORY_MANAGER_SWITCH
    return status;
    //#]
}

bool OMMemoryManagerSwitchHelper::recordMemoryAllocation(const void * ommmswArg(memory)) const {
    //#[ operation recordMemoryAllocation(void *) const
    bool status;
    #ifdef OM_ENABLE_MEMORY_MANAGER_SWITCH
    status = OMMemoryManagerSwitchHelperImpl::instance()->recordMemoryAllocation(memory);
    #else
    status = false;
    #endif // OM_ENABLE_MEMORY_MANAGER_SWITCH
    return status;
    //#]
}

bool OMMemoryManagerSwitchHelper::recordMemoryDeallocation(const void * ommmswArg(memory)) const {
    //#[ operation recordMemoryDeallocation(void *) const
    bool status;
    #ifdef OM_ENABLE_MEMORY_MANAGER_SWITCH
    status = OMMemoryManagerSwitchHelperImpl::instance()->recordMemoryDeallocation(memory);
    #else
    status = false;
    #endif // OM_ENABLE_MEMORY_MANAGER_SWITCH   
    return status;
    //#]
}

void OMMemoryManagerSwitchHelper::setUpdateState(bool ommmswArg(val)) const {
    //#[ operation setUpdateState(bool) const
    #ifdef OM_ENABLE_MEMORY_MANAGER_SWITCH
    OMMemoryManagerSwitchHelperImpl::instance()->setUpdateState(val);
    #endif // OM_ENABLE_MEMORY_MANAGER_SWITCH
    //#]
}

bool OMMemoryManagerSwitchHelper::shouldUpdate(void) const {
    //#[ operation shouldUpdate() const
    bool status;
    #ifdef OM_ENABLE_MEMORY_MANAGER_SWITCH
    status = OMMemoryManagerSwitchHelperImpl::instance()->shouldUpdate();
    #else
    status = false;
    #endif // OM_ENABLE_MEMORY_MANAGER_SWITCH          
    return status;
    //#]
}


//#[ ignore
#else
	//Dummy function to avoid warning
	void OMMemoryManagerSwitchHelper_dummy(void) {}
#endif // (!defined(OM_NO_FRAMEWORK_MEMORY_MANAGER) && !defined(OMOMATE))
//#]




