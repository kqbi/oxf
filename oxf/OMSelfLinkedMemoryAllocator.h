//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: OMSelfLinkedMemoryAllocator
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


#ifndef OMSelfLinkedMemoryAllocator_H
#define OMSelfLinkedMemoryAllocator_H

//## class OMSelfLinkedMemoryAllocator
#include "IOxfMemoryAllocator.h"
//## dependency OMMemoryManagerWrapper
#include "OMMemoryManagerWrapper.h"
//## classInstance myGuard_
#include "omprotected.h"
//## package Design::oxf::Services::MemoryManagement::Pools

//## class OMSelfLinkedMemoryAllocator
// Memory pool implementation
//#[ ignore
#ifndef OM_NO_TEMPLATES_USAGE 

//#]
template <class T, int INITNUM> class RP_FRAMEWORK_DLL OMSelfLinkedMemoryAllocator : public IOxfMemoryAllocator {
public :

    // Additional memory allocation callback
    //#[ type AllocationCallback
    typedef omtypename T* (*AllocationCallback)(Rhp_int32_t);
    //#]
    
    //## type PoolBlock
    typedef struct PoolBlock {
        PoolBlock* nextBlock;		//## attribute nextBlock
        Rhp_uint8_t* blockP;		//## attribute blockP
    } PoolBlock;
    
    ////    Constructors and destructors    ////
    
    // construct the allocator, specify whether it is protected
    // and how much additional memory should be allocated if the initial pool is exhausted
    // Argument const Rhp_int32_t incrementNum :
    // The number of additional instances to allocate when the initial pool is empty.
    // Argument bool isProtected :
    // Enable/disable memory pool protection from race between threads
    //## operation OMSelfLinkedMemoryAllocator(Rhp_int32_t,bool)
    inline OMSelfLinkedMemoryAllocator(const Rhp_int32_t incrementNum, bool isProtected) : allocator_(NULL), 
headOfFreeList_(NULL), incrementNum_(incrementNum), isProtected_(isProtected), memoryPoolIsEmptyFlag_(true), 
pool(NULL), myGuard_(false) {
        //#[ operation OMSelfLinkedMemoryAllocator(Rhp_int32_t,bool)
        if (isProtected_) {
        	myGuard_.initializeMutex();
        }
        
        lock();
        {
        	T* newBlock = reinterpret_cast<T*>(initialBlock_);
        	(void)initiatePool(newBlock,INITNUM);
        }
        unlock();
        //#]
    }
    
    // Cleanup
    //## operation ~OMSelfLinkedMemoryAllocator()
    inline ~OMSelfLinkedMemoryAllocator(void) {
        //#[ operation ~OMSelfLinkedMemoryAllocator()
        allocator_ = NULL;
        
        #ifdef USE_DYNAMIC_MEMORY_ALLOCATION
        
        // only additional instances pool is allocated dynamically
        // and stored in the pool link list
        PoolBlock* element = pool;
        while (element) {
        	PoolBlock* next = element->nextBlock;
        	delete[] element->blockP;
        	delete element;
        	element = next;
        }
        #endif // USE_DYNAMIC_MEMORY_ALLOCATION
        
        headOfFreeList_ = NULL;
        pool = NULL;
        //#]
    }
    
    ////    Operations    ////
    
    // allocate memory pool big enough to hold numOfInstances instances of type T
    // Argument const Rhp_int32_t numOfInstances :
    // The number of instances to allocate memory for
    //## operation allocPool(Rhp_int32_t)
    inline T* allocPool(const Rhp_int32_t numOfInstances) {
        //#[ operation allocPool(Rhp_int32_t)
        // allocate a big block of memory
        T* newBlock = NULL;
        
        // notice, that according to the ANSI standard allocating 0 bytes 
        // return a valid pointer and NOT 0
        if (numOfInstances > 0) {
        #ifdef USE_DYNAMIC_MEMORY_ALLOCATION		
        	// the initial pool was used so we will have to allocate another chunk using ::new
        	// (still, we benefit by minimizing fragmentation and  lowering the overhead of many new-s)
        	newBlock = reinterpret_cast<T*>(OMMemoryManagerWrapper::getMemory((Rhp_uint64_t)(sizeof(T) * numOfInstances)));
        #endif // USE_DYNAMIC_MEMORY_ALLOCATION
        }
        return newBlock;
        //#]
    }
    
    // Get the memory allocation callback function
    //## operation getAllocator_() const
    inline AllocationCallback getAllocator_(void) const {
        //#[ operation getAllocator_() const
        return allocator_;
        //#]
    }
    
    // get a memory block of the specified size
    // Argument size_t size :
    // The memory to allocate (in bytes)
    //## operation getMemory(size_t)
    inline virtual void * getMemory(size_t size) {
        //#[ operation getMemory(size_t)
        T* element = NULL;
        
        if ((size != 0) && (size != sizeof(T))) {
        #ifdef USE_DYNAMIC_MEMORY_ALLOCATION		
        	element = reinterpret_cast<T*>(OMMemoryManagerWrapper::getMemory((Rhp_uint64_t)size));
        #endif // USE_DYNAMIC_MEMORY_ALLOCATION
        } else {
        	lock();
        	{
        	element = headOfFreeList_;
        
        	// if element is not valid, allocate more space
        	if (element == NULL) {
        		// hook for the user to catch pool exhaustion allocation of more memory
        		// by setting a breakpoint in T::OMMemoryPoolIsEmpty()
        		if (memoryPoolIsEmptyFlag_) {
        			T::OMMemoryPoolIsEmpty();	// notification
        		}
        		T* newBlock = NULL;
        		if (allocator_ != NULL) {
        			newBlock = allocator_(incrementNum_);
        		} else {
        			newBlock = allocPool(incrementNum_);
        		}            
        		
        		#ifdef USE_DYNAMIC_MEMORY_ALLOCATION
        		PoolBlock* newpB = new PoolBlock;
        		newpB->blockP = reinterpret_cast<Rhp_uint8_t*>(newBlock);
        		if (pool) {
        			newpB->nextBlock = pool;
        		}
        		else
        			newpB->nextBlock = NULL;
        		pool = newpB;
        		#endif // USE_DYNAMIC_MEMORY_ALLOCATION
        				
        		// connect the pool
        		if (initiatePool(newBlock,incrementNum_) >0)
        		{
        			element = headOfFreeList_;
        		}
        	}
        	// if element is valid, just move the list head to the
        	// next element in the free list
        	if (element != NULL) { 
        		headOfFreeList_ = element->OMMemoryPoolNextChunk;
        	}
        	}
        	unlock();
        }
        return element;
        //#]
    }
    
    // initiate the bookkeeping for the allocated pool
    // Argument T* const newBlock :
    // The new memory block
    // Argument const Rhp_int32_t numOfInstances :
    // The number of instances in the memory block
    //## operation initiatePool(T* const,Rhp_int32_t)
    inline Rhp_int32_t initiatePool(T* const newBlock, const Rhp_int32_t numOfInstances) {
        //#[ operation initiatePool(T* const,Rhp_int32_t)
        Rhp_int32_t status;
        
        // make sure we got one
        if ((newBlock == NULL) || (numOfInstances == 0)) {
        	headOfFreeList_ = NULL;
        	status = 0;
        } else {
        	// link the objects together
        	for (Rhp_int32_t i = 0; i < numOfInstances - 1; i++) {
        		newBlock[i].OMMemoryPoolNextChunk = &newBlock[i+1];
        	}
        
        	// terminate the linked list with a null pointer
        	newBlock[numOfInstances-1].OMMemoryPoolNextChunk = NULL;
        
        	// set headOfFreeList_ to the first element
        	headOfFreeList_ = &newBlock[0];          
        	status = 1; 
        }
        return status;
        //#]
    }
    
    // Return the number of elements that can be still allocated
    //## operation numberOfEmptyElements()
    inline Rhp_int32_t numberOfEmptyElements(void) {
        //#[ operation numberOfEmptyElements()
        int res = 0;
        lock();
        T* element = headOfFreeList_;
        while (element != NULL)
        {
         	element = element->OMMemoryPoolNextChunk;
         	res++;
        }
        unlock();
        return res; 
        //#]
    }
    
    // return a memory of object of the specified size
    // Argument void * object :
    // The object to delete
    // Argument size_t size :
    // The size of the object (in bytes)
    //## operation returnMemory(void *,size_t)
    inline virtual void returnMemory(void * object, size_t size) {
        //#[ operation returnMemory(void *,size_t)
        if (object != NULL) {
        	// send objects of "wrong" size to ::op delete
        	if ((size != 0) && (size != sizeof(T))) {
        	  OMMemoryManagerWrapper::Delete(object, size);
        	} else {
        		lock();
        		{
        		T* carcass = reinterpret_cast<T*>(object);
        		carcass->OMMemoryPoolNextChunk = headOfFreeList_;
        		headOfFreeList_ = carcass;
        		}
        		unlock();
        	}
        }
        //#]
    }
    
    // Set the memory pool additional memory allocation callback
    // Argument AllocationCallback p_allocator_ :
    // The callback
    //## operation setAllocator(AllocationCallback)
    inline void setAllocator(AllocationCallback p_allocator_) {
        //#[ operation setAllocator(AllocationCallback)
        allocator_ = p_allocator_;
        //#]
    }
    

private :

    // lock critical section
    //## operation lock() const
    inline void lock(void) const {
        //#[ operation lock() const
        if (isProtected_) {
        	myGuard_.lock();
        }
        //#]
    }
    
    // unlock critical section
    //## operation unlock() const
    inline void unlock(void) const {
        //#[ operation unlock() const
        if (isProtected_) {
        	myGuard_.unlock();
        }
        //#]
    }
    
    ////    Additional operations    ////
    

public :

    //## auto_generated
    inline Rhp_int32_t getIncrementNum(void) const {
        //#[ auto_generated
        return incrementNum_;
        //#]
    }
    
    //## auto_generated
    inline void setIncrementNum(Rhp_int32_t p_incrementNum_) {
        //#[ auto_generated
        incrementNum_ = p_incrementNum_;
        //#]
    }
    
    //## auto_generated
    inline bool getIsProtected(void) const {
        //#[ auto_generated
        return isProtected_;
        //#]
    }
    
    //## auto_generated
    inline void setIsProtected(bool p_isProtected_) {
        //#[ auto_generated
        isProtected_ = p_isProtected_;
        //#]
    }
    
    //## auto_generated
    inline void callMemoryPoolIsEmpty(bool p_memoryPoolIsEmptyFlag_) {
        //#[ auto_generated
        memoryPoolIsEmptyFlag_ = p_memoryPoolIsEmptyFlag_;
        //#]
    }
    
    ////    Attributes    ////
    

private :

    // callback function to override the memory allocation scheme
    AllocationCallback allocator_;		//## attribute allocator_
    
    // head of the free list
    T* headOfFreeList_;		//## attribute headOfFreeList_
    
    // how much (in instance number) to increment if initial pool is exhausted
    Rhp_int32_t incrementNum_;		//## attribute incrementNum_
    
    // initial pool
    Rhp_uint8_t initialBlock_[(OMRAW_MEMORY_ALIGNMENT-1)+(INITNUM*sizeof(T))];		//## attribute initialBlock_
    
    // activate the mutex
    bool isProtected_;		//## attribute isProtected_
    
    // when the flag is false, memoryPoolIsEmpty() will not be called
    bool memoryPoolIsEmptyFlag_;		//## attribute memoryPoolIsEmptyFlag_
    
    PoolBlock* pool;		//## attribute pool
    
    ////    Relations and components    ////
    
    // The pool guard
    OMProtected myGuard_;		//## classInstance myGuard_
    
};
//#[ ignore

#endif // !OM_NO_TEMPLATES_USAGE
//#]

//## package Design::oxf::Services::MemoryManagement::Pools

//## class OMSelfLinkedMemoryAllocator

#endif



