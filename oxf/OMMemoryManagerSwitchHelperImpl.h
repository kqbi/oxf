//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: OMMemoryManagerSwitchHelperImpl
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


#ifndef OMMemoryManagerSwitchHelperImpl_H
#define OMMemoryManagerSwitchHelperImpl_H

//## dependency MemoryManagerMacros
#include "OXFMemoryManagerMacros.h"
//## dependency MemoryPoolsMacros
#include "OXFMemoryPoolsMacros.h"
//## dependency Pools
#include "OXFPools.h"
//## package Design::oxf::Services::MemoryManagement::Manager

//## class OMMemoryManagerSwitchHelperImpl

//#[ ignore
#if (!defined(OM_NO_FRAMEWORK_MEMORY_MANAGER) && !defined(OMOMATE))

//#]


// Support switch of the memory manager after memory was already requested.
// This support is required since the memory must return via the manager that allocated it.
// This class perform the actual recording of the memory it should no be accessed or included directly.
class OMMemoryManagerSwitchHelperImpl {
public :

    // A node in the memory managers list
    // Used by OMMemoryManagerSwitchHelper
    //## class OMMemoryManagerSwitchHelperImpl::Node
    class Node {
        ////    Constructors and destructors    ////
        
    public :
    
        // Initialize a node
        // Argument const void * mem :
        // The memory to record by the node
        // Argument Node* nextNode :
        // The next node on the list (to connect to)
        //## operation Node(void *,Node*)
        Node(const void * mem, Node* nextNode);
        
        // Initialize an empty node
        //## operation Node()
        Node(void);
        
        //## auto_generated
        ~Node(void);
        
        ////    Operations    ////
        
        // assert when run out of memory
        // Argument Rhp_int32_t /**/ :
        // dummy - in order to comply with the pool signature.
        //## operation outOfMemoryAssert(Rhp_int32_t)
        inline static Node* outOfMemoryAssert(Rhp_int32_t /**/) {
            //#[ operation outOfMemoryAssert(Rhp_int32_t)
            assert(false);
            return NULL;
            //#]
        }
        
        ////    Additional operations    ////
        
        //## auto_generated
        const void * getAllocatedMemory(void) const;
        
        //## auto_generated
        Node* getNext(void) const;
        
        //## auto_generated
        void setNext(Node* p_Node);
        
    
    protected :
    
        //## auto_generated
        void cleanUpRelations(void);
        
        ////    Attributes    ////
        
    
    public :
    
        // The allocated memory address
        const void * allocatedMemory;		//## attribute allocatedMemory
        
        ////    Relations and components    ////
        
        // The next node in the memory list
        Node* next;		//## link next
        
    
        DECLARE_MEMORY_ALLOCATOR(Node,OM_MEMORY_MANAGER_SWITCH_HELPER_POOL_SIZE)
        
    };
    
    ////    Constructors and destructors    ////
    
    // CTOR
    //## operation OMMemoryManagerSwitchHelperImpl()
    inline OMMemoryManagerSwitchHelperImpl(void) : shouldUpdateLog(true), _recordedMemory(NULL)
     	 {
        //#[ operation OMMemoryManagerSwitchHelperImpl()
        //#]
    }
    
    // DTOR
    //## operation ~OMMemoryManagerSwitchHelperImpl()
    inline ~OMMemoryManagerSwitchHelperImpl(void) {
        //#[ operation ~OMMemoryManagerSwitchHelperImpl()
        cleanup();
        //#]
        cleanUpRelations();
    }
    
    ////    Operations    ////
    
    // cleanup the allocated memory list
    //## operation cleanup()
    void cleanup(void);
    
    // search for a recorded memory allocation
    // return 'true' if the memory was found in the recorded memory
    //  or 'false' when the memory is not found
    // Argument const void * memory :
    // The memory to find
    //## operation findMemory(void *) const
    bool findMemory(const void * memory) const;
    
    // return the internally used singleton instance 
    // of the OMMemoryManagerSwitchHelper
    //## operation instance()
    static OMMemoryManagerSwitchHelperImpl* instance(void);
    
    // check if the memory log is empty
    //## operation isLogEmpty() const
    inline bool isLogEmpty(void) const {
        //#[ operation isLogEmpty() const
        return (_recordedMemory == NULL);
        //#]
    }
    
    // record a single memory allocation
    // return true on success
    // Argument const void * memory :
    // The memory to log
    //## operation recordMemoryAllocation(void *)
    bool recordMemoryAllocation(const void * memory);
    
    // record a single memory deallocation
    // return true if memory record found & removed ok
    // Argument const void * memory :
    // The memory to remove from the log
    //## operation recordMemoryDeallocation(void *)
    bool recordMemoryDeallocation(const void * memory);
    
    ////    Additional operations    ////
    
    //## auto_generated
    bool shouldUpdate(void) const;
    
    //## auto_generated
    void setUpdateState(bool p_shouldUpdateLog);
    

protected :

    //## auto_generated
    void cleanUpRelations(void);
    
    ////    Attributes    ////
    

private :

    // should update the log state flag
    bool shouldUpdateLog;		//## attribute shouldUpdateLog
    
    ////    Relations and components    ////
    
    // The head of the recorded memory list
    Node* _recordedMemory;		//## link _recordedMemory
    
};


//#[ ignore
#else
	//Dummy function to avoid warning
	void OMMemoryManagerSwitchHelperImpl_dummy(void);
#endif //(!defined(OM_NO_FRAMEWORK_MEMORY_MANAGER) && !defined(OMOMATE))
//#]

#endif



