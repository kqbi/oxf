//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: OMMemoryManager
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
#include "ommemorymanager.h"
//## dependency OXF
#include "oxf.h"
//## package Design::oxf::Services::MemoryManagement::Manager

//## class OMMemoryManager

//#[ ignore
#if (!defined(OM_NO_FRAMEWORK_MEMORY_MANAGER) && !defined(OMOMATE))

//#]


bool OMMemoryManager::_singletonDestroyed = false;

OMMemoryManager::OMMemoryManager(bool theFrameworkSingleton) {
    //#[ operation OMMemoryManager(bool)
    if (theFrameworkSingleton) {
    	_singletonDestroyed = false;
    }
    //#]
}

OMMemoryManager::~OMMemoryManager(void) {
    //#[ operation ~OMMemoryManager()
    if (this == getDefaultMemoryManager()) {
    	_singletonDestroyed = true;            
    }
    //#]
}

IOxfMemoryAllocator* OMMemoryManager::getDefaultMemoryManager(void) {
    //#[ operation getDefaultMemoryManager()
    static OMMemoryManager theOMMemoryManager(true);
    if (_singletonDestroyed) {
    	// recreate deleted singleton
    	(void) new(&theOMMemoryManager) OMMemoryManager(true);
    }
    return &theOMMemoryManager;
    //#]
}

void * OMMemoryManager::getMemory(size_t size) {
    //#[ operation getMemory(size_t)
    void* mem = ::new Rhp_uint8_t[size];
    
    #ifdef OM_ENABLE_MEMORY_MANAGER_SWITCH
    // record the memory allocated by the default manager
    // to allow a switch to a user memory manager after memory was allocated
    // it is the responsibility of the user memory manager 
    //  to check if the memory was allocated by the framework default memory manager
    // the check is made by calling:
    //  OMMemoryManagerSwitchHelper::instance()->findMemory(<memory>)
    // when a memory found in the list it should be deleted by calling:
    //  OMMemoryManager::getDefaultMemoryManager()->returnMemory(<memory>,<size>)
    // the user is also responsible to cleanup the deleted memory from the table by calling:
    //  OMMemoryManagerSwitchHelper::instance()->recordMemoryDeallocation(<memory>)
    // if the user doesn't replace the default memory manager the log of allocated memory
    //  will be cleaned and disabled by OXFInit()
    if (OMMemoryManagerSwitchHelper::instance()->shouldUpdate()) {
    	bool status = OMMemoryManagerSwitchHelper::instance()->recordMemoryAllocation(mem);
    	// if the record operation failed 
    	// the user must icrease OM_MEMORY_MANAGER_SWITCH_HELPER_POOL_SIZE
    	assert(status == true); 
    }
    #endif // OM_ENABLE_MEMORY_MANAGER_SWITCH
    
    return mem;
    //#]
}

IOxfMemoryAllocator* OMMemoryManager::getMemoryManager(void) {
    //#[ operation getMemoryManager()
    // handle destroyed internal memory manager
    if (_singletonDestroyed) {
    	(void) getDefaultMemoryManager();
    }
    // get the user memory manager
    IOxfMemoryAllocator* theManager = OXF::getMemoryManager();
    if (theManager == NULL) {
    	// no user manager - use the framework default manager
    	theManager = getDefaultMemoryManager();
    	// register the internal memory manager as the current memory manager
    	(void) OXF::setMemoryManager(theManager);
    }
    return theManager;
    //#]
}

void OMMemoryManager::returnMemory(void * object, size_t /* size */) {
    //#[ operation returnMemory(void *,size_t)
    Rhp_uint8_t* pObject = static_cast<Rhp_uint8_t*>(object);
    
    #ifdef OM_ENABLE_MEMORY_MANAGER_SWITCH
    // remove entry from the log
    if (!OMMemoryManagerSwitchHelper::instance()->isLogEmpty()) {
    	(void) OMMemoryManagerSwitchHelper::instance()->
    		recordMemoryDeallocation(object);
    }
    #endif // OM_ENABLE_MEMORY_MANAGER_SWITCH
    
    ::delete[] pObject;
    //#]
}


//#[ ignore
#else
	//Dummy function to avoid warning
	void OMMemoryManager_dummy(void) {}
#endif // (!defined(OM_NO_FRAMEWORK_MEMORY_MANAGER) && !defined(OMOMATE))
//#]




