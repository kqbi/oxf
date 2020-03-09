//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: IOxfMemoryAllocator
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


#ifndef IOxfMemoryAllocator_H
#define IOxfMemoryAllocator_H

//## dependency BasicTypes
#include "rawtypes.h"
//## package Design::oxf::Services::MemoryManagement::MemoryAPI

//## class IOxfMemoryAllocator
// Memory manager interface
class RP_FRAMEWORK_DLL IOxfMemoryAllocator {
    ////    Constructors and destructors    ////
    
public :

    // Virtual destructor to enable polymorphic deletion
    //## operation ~IOxfMemoryAllocator()
    inline virtual ~IOxfMemoryAllocator(void) {
        //#[ operation ~IOxfMemoryAllocator()
        //#]
    }
    
    ////    Operations    ////
    
    // get a memory block of the specified size
    // Argument size_t size :
    // The memory size in bytes
    //## operation getMemory(size_t)
    virtual void * getMemory(size_t size) = 0;
    
    // Return the memory of the object.
    // The size argument is available for optimization of the memory manager implementation (for example when several pools are used based on the requested memory size).
    // Argument void * object :
    // The object to delete
    // Argument size_t size :
    // The object size (in bytes)
    //## operation returnMemory(void *,size_t)
    virtual void returnMemory(void * object, size_t size) = 0;
    
};

#endif



