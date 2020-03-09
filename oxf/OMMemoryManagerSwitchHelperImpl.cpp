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



//## auto_generated
#include "OMMemoryManagerSwitchHelperImpl.h"
//## dependency NotifyMacros
#ifdef _OMINSTRUMENT
#include "OXFNotifyMacros.h"

#endif // _OMINSTRUMENT
//## package Design::oxf::Services::MemoryManagement::Manager

//## class OMMemoryManagerSwitchHelperImpl

//#[ ignore
#if (!defined(OM_NO_FRAMEWORK_MEMORY_MANAGER) && !defined(OMOMATE))

//#]


//## class OMMemoryManagerSwitchHelperImpl::Node
IMPLEMENT_MEMORY_ALLOCATOR(OMMemoryManagerSwitchHelperImpl::Node,OM_MEMORY_MANAGER_SWITCH_HELPER_POOL_SIZE, 0, false)

OMMemoryManagerSwitchHelperImpl::Node::Node(const void * mem, Node* nextNode) : allocatedMemory(mem), next(nextNode) {
    //#[ operation Node(void *,Node*)
    #ifndef OM_NO_TEMPLATES_USAGE
    OMMemoryPoolNextChunk = NULL;
    #endif // OM_NO_TEMPLATES_USAGE
    //#]
}

OMMemoryManagerSwitchHelperImpl::Node::Node(void) : allocatedMemory(NULL), next(NULL) {
    //#[ operation Node()
    #ifndef OM_NO_TEMPLATES_USAGE
    OMMemoryPoolNextChunk = NULL;
    #endif // OM_NO_TEMPLATES_USAGE
    
    static bool wasCalled = false;
    if (!wasCalled) {
    	wasCalled = true;
    #ifndef OM_NO_TEMPLATES_USAGE
    	OMCallMemoryPoolIsEmpty(FALSE);
    	OMSetMemoryAllocator(outOfMemoryAssert);
    #endif // OM_NO_TEMPLATES_USAGE
    }
    //#]
}

OMMemoryManagerSwitchHelperImpl::Node::~Node(void) {
    cleanUpRelations();
}

const void * OMMemoryManagerSwitchHelperImpl::Node::getAllocatedMemory(void) const {
    return allocatedMemory;
}

OMMemoryManagerSwitchHelperImpl::Node* OMMemoryManagerSwitchHelperImpl::Node::getNext(void) const {
    return next;
}

void OMMemoryManagerSwitchHelperImpl::Node::setNext(OMMemoryManagerSwitchHelperImpl::Node* p_Node) {
    next = p_Node;
}

void OMMemoryManagerSwitchHelperImpl::Node::cleanUpRelations(void) {
    if(next != NULL)
        {
            next = NULL;
        }
}

void OMMemoryManagerSwitchHelperImpl::cleanup(void) {
    //#[ operation cleanup()
    Node* current = _recordedMemory;
    while (current != NULL) {
    	Node* next = current->next;
    	delete current;
    	current = next;
    }
    _recordedMemory = NULL;
    //#]
}

bool OMMemoryManagerSwitchHelperImpl::findMemory(const void * memory) const {
    //#[ operation findMemory(void *) const
    bool status=false;
    Node* current = _recordedMemory;  
    
    // find the node
    while (current != NULL) {
    	if (current->allocatedMemory == memory) {
    		status = true;
    		break;
    	}
    	current = current->next;
    }
    return status;
    //#]
}

OMMemoryManagerSwitchHelperImpl* OMMemoryManagerSwitchHelperImpl::instance(void) {
    //#[ operation instance()
    static OMMemoryManagerSwitchHelperImpl impl;
    return &impl;
    //#]
}

bool OMMemoryManagerSwitchHelperImpl::recordMemoryAllocation(const void * memory) {
    //#[ operation recordMemoryAllocation(void *)
    Node* node = new Node(memory, _recordedMemory);
    assert (node != NULL);
    if (node != NULL) {		//lint !e774 (Boolean within 'if' always evaluates to True)
    	_recordedMemory = node;
    }
    return (node != NULL);
    //#]
}

bool OMMemoryManagerSwitchHelperImpl::recordMemoryDeallocation(const void * memory) {
    //#[ operation recordMemoryDeallocation(void *)
    bool found = false;
    Node* prev = NULL;
    Node* current = _recordedMemory;
    
    // find the node
    while ((current != NULL) && (!found)) {
    	if (current->allocatedMemory == memory) {
    		found = true;
    	} else {
    		prev = current;
    		current = current->next;
    	}
    }
    // remove the node
    // lint fail to see that the while condition potect from an option where 'current' is NULL
    //lint -save -e613 (Possible use of null pointer 'current' in left argument to operator '->')
    if (found) {
    	// first element
    	if (prev == NULL) {
    		_recordedMemory = current->next;
    	} else {
    		// not the first element
    		prev->next = current->next;
    	}
    	delete current;
    }
    //lint -restore
    return found;
    //#]
}

bool OMMemoryManagerSwitchHelperImpl::shouldUpdate(void) const {
    return shouldUpdateLog;
}

void OMMemoryManagerSwitchHelperImpl::setUpdateState(bool p_shouldUpdateLog) {
    shouldUpdateLog = p_shouldUpdateLog;
}

void OMMemoryManagerSwitchHelperImpl::cleanUpRelations(void) {
    if(_recordedMemory != NULL)
        {
            _recordedMemory = NULL;
        }
}


//#[ ignore
#else
	//Dummy function to avoid warning
	void OMMemoryManagerSwitchHelperImpl_dummy(void) {}
#endif //(!defined(OM_NO_FRAMEWORK_MEMORY_MANAGER) && !defined(OMOMATE))

//#]




