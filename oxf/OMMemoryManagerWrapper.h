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


#ifndef OMMemoryManagerWrapper_H
#define OMMemoryManagerWrapper_H

//## dependency BasicTypes
#include "rawtypes.h"
//## dependency OMMemoryManager
class OMMemoryManager;

//## package Design::oxf::Services::MemoryManagement::Manager

//## class OMMemoryManagerWrapper
// A wrapper for the memory manager used to avoid circular dependencies
class RP_FRAMEWORK_DLL OMMemoryManagerWrapper {
    ////    Constructors and destructors    ////
    
public :

    //## auto_generated
    ~OMMemoryManagerWrapper(void);
    
    ////    Operations    ////
    
    // Delete an object using OMDELETE
    // Argument void * obj :
    // The object to delete
    // Argument const size_t size :
    // The object size (in bytes)
    //## operation Delete(void *,size_t)
    static void Delete(void * obj, const size_t size);
    
    // Request memory using OMGET_MEMORY
    // Argument const Rhp_uint64_t size :
    // The requested memory size (in bytes)
    //## operation getMemory(Rhp_uint64_t)
    static void * getMemory(const Rhp_uint64_t size);
    
};

#endif



