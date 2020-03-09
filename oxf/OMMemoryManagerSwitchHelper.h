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


#ifndef OMMemoryManagerSwitchHelper_H
#define OMMemoryManagerSwitchHelper_H

//## dependency BasicTypes
#include "rawtypes.h"
//## dependency OMMemoryManagerSwitchHelperImpl
class OMMemoryManagerSwitchHelperImpl;

//## package Design::oxf::Services::MemoryManagement::Manager

//## class OMMemoryManagerSwitchHelper

//#[ ignore
#if (!defined(OM_NO_FRAMEWORK_MEMORY_MANAGER) && !defined(OMOMATE))

#ifdef OM_ENABLE_MEMORY_MANAGER_SWITCH
// use the argument name
#define ommmswArg(arg) arg
#else
// remove the argument name
#define ommmswArg(arg)
#endif //OM_ENABLE_MEMORY_MANAGER_SWITCH


//#]


// Support switch of the memory manager after memory was already requested.
// This support is required since the memory must return via the manager that allocated it.
// This class supply the interface, the actual implementation is provided by the OMMemoryManagerSwitchHelperImpl that should not be accessed directly.
class RP_FRAMEWORK_DLL OMMemoryManagerSwitchHelper {
    ////    Operations    ////
    
public :

    // cleanup the allocated memory list
    //## operation cleanup() const
    void cleanup(void) const;
    
    // search for a recorded memory allocation
    // return 'true' if the memory was found in the recorded memory
    //  or 'false' when the memory is not found
    // Argument const void * ommmswArg(memory) :
    // The memory to find
    //## operation findMemory(void *) const
    bool findMemory(const void * ommmswArg(memory)) const;
    
    // return the internally used singleton instance 
    // of the OMMemoryManagerSwitchHelper
    //## operation instance()
    static OMMemoryManagerSwitchHelper* instance(void);
    
    // check if the memory log is empty
    //## operation isLogEmpty() const
    bool isLogEmpty(void) const;
    
    // record a single memory allocation
    // return true on success
    // Argument const void * ommmswArg(memory) :
    // The memory to record
    //## operation recordMemoryAllocation(void *) const
    bool recordMemoryAllocation(const void * ommmswArg(memory)) const;
    
    // record a single memory deallocation
    // return true if memory record found & removed ok
    // Argument const void * ommmswArg(memory) :
    // The memory to deallocate
    //## operation recordMemoryDeallocation(void *) const
    bool recordMemoryDeallocation(const void * ommmswArg(memory)) const;
    
    // Set the switch helper updating state
    // Argument bool ommmswArg(val) :
    // When true enable the switch helper otherwise disable it
    //## operation setUpdateState(bool) const
    void setUpdateState(bool ommmswArg(val)) const;
    
    // Check if the switch helper should be updated
    //## operation shouldUpdate() const
    bool shouldUpdate(void) const;
    
};


//#[ ignore
#else
	//Dummy function to avoid warning
	void OMMemoryManagerSwitchHelper_dummy(void);
#endif //(!defined(OM_NO_FRAMEWORK_MEMORY_MANAGER) && !defined(OMOMATE))
//#]

#endif



