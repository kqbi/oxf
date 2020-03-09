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


#ifndef ommemorymanager_H
#define ommemorymanager_H

//## class OMMemoryManager
#include "IOxfMemoryAllocator.h"
//## dependency MemoryManagerMacros
#include "OXFMemoryManagerMacros.h"
//## dependency OMMemoryManagerSwitchHelper
//#[ ignore
#if (!defined(OM_NO_FRAMEWORK_MEMORY_MANAGER) && !defined(OMOMATE))
//#]
#include "OMMemoryManagerSwitchHelper.h"
//#[ ignore

#endif // (!defined(OM_NO_FRAMEWORK_MEMORY_MANAGER) && !defined(OMOMATE))
//#]
//## dependency OXF
class OXF;

//## package Design::oxf::Services::MemoryManagement::Manager

//## class OMMemoryManager

//#[ ignore
#if (!defined(OM_NO_FRAMEWORK_MEMORY_MANAGER) && !defined(OMOMATE))

//#]


// The framework default memory manager, uses the global new/delete operators to get and return memory.
class RP_FRAMEWORK_DLL OMMemoryManager : public IOxfMemoryAllocator {
    ////    Constructors and destructors    ////
    
public :

    // constructor
    // Argument bool theFrameworkSingleton = false :
    // Indicate that the _singletonDestroyed attribute should be reset.
    //## operation OMMemoryManager(bool)
    explicit OMMemoryManager(bool theFrameworkSingleton = false);
    
    // destructor
    //## operation ~OMMemoryManager()
    virtual ~OMMemoryManager(void);
    
    ////    Operations    ////
    
    // get the default (internal) memory manager
    //## operation getDefaultMemoryManager()
    static IOxfMemoryAllocator* getDefaultMemoryManager(void);
    
    // get memory for an instance
    // Argument size_t size :
    // The memory size (in bytes)
    //## operation getMemory(size_t)
    virtual void * getMemory(size_t size);
    
    // get the actual memory manager
    //## operation getMemoryManager()
    static IOxfMemoryAllocator* getMemoryManager(void);
    
    // Return the memory of the object
    // Argument void * object :
    // The memory to return
    // Argument size_t /* size */ :
    // The size of the returned object
    //## operation returnMemory(void *,size_t)
    virtual void returnMemory(void * object, size_t /* size */);
    
    ////    Attributes    ////
    

private :

    // Singleton state flag, used to identify that the memory manager singleton was destroyed (while exit())
    static bool _singletonDestroyed;		//## attribute _singletonDestroyed
    
};


//#[ ignore
#else
	//Dummy function to avoid warning
	void OMMemoryManager_dummy(void);
#endif // (!defined(OM_NO_FRAMEWORK_MEMORY_MANAGER) && !defined(OMOMATE))
//#]

#endif



