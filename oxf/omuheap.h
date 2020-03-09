//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: OMUHeap
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


#ifndef omuheap_H
#define omuheap_H

//## dependency IOxfTimeout
#include "IOxfTimeout.h"
//## dependency MemoryManagerMacros
#include "OXFMemoryManagerMacros.h"
//## dependency NotifyMacros
#include "OXFNotifyMacros.h"
//## dependency OMMemoryManager
#include "ommemorymanager.h"
//## class OMUHeap
#include "OMUAbstractContainer.h"
//## dependency TimeManagement
#include "OXFTimeManagement.h"
//## dependency OMUIterator
class OMUIterator;

//## package Design::oxf::Services::Containers::Typeless

//## class OMUHeap
// //////////////////////////////////////////////////////////
// class OMUHeap
// 
// The Heap invariants:
// 1. theHeap[0] is empty - this is so we have "easy arithmetic"
// 2. theHeap[1] -- theHeap[count] hold the actual elements
// 3. theHeap[i]<theHeap[2*i] && theHeap[i]<theHeap[2*i+1]
// 			  for all i>0, 2*i<=count, 2*i+1<=count.
// 	  Hence Min = theHeap[1]
// 
// 
// OMUHeap is holding elements of type "void*"
// 
// //////////////////////////////////////////////////////////
class RP_FRAMEWORK_DLL OMUHeap : public OMUAbstractContainer {
    ////    Constructors and destructors    ////
    
public :

    // Initialize a heap with a given size
    // Argument const Rhp_int32_t size = 100 :
    // The heap size (number of elements)
    //## operation OMUHeap(Rhp_int32_t)
    explicit inline OMUHeap(const Rhp_int32_t size = 100) : OMUAbstractContainer(), count(0), heapSize(0), 
theheap(NULL) {
        //#[ operation OMUHeap(Rhp_int32_t)
        heapSize = size + 1; // theheap[0] is never used
        theheap = static_cast<void**>(OMNEW(void*, heapSize));
        //#]
    }
    
    // copy constructor and assignment operator
    // Argument const OMUHeap & aHeap :
    // The heap to copy
    //## operation OMUHeap(const OMUHeap & )
    explicit inline OMUHeap(const OMUHeap & aHeap) : OMUAbstractContainer(), count(0), heapSize(0), theheap(NULL) {
        //#[ operation OMUHeap(const OMUHeap & )
        copy(aHeap);
        //#]
    }
    
    // cleanup
    //## operation ~OMUHeap()
    inline ~OMUHeap(void) {
        //#[ operation ~OMUHeap()
        OMDELETE(theheap, sizeof(void*) * heapSize);
        theheap = NULL;
        //#]
    }
    
    ////    Operations    ////
    
    // Add e to heap
    // Argument void * anElement :
    // The element to add
    //## operation add(void *)
    inline bool add(void * anElement) {
        //#[ operation add(void *)
        bool res = true;
        if (count + 1 < heapSize) {
        	++count;
        	takeUp(anElement,count);
        } else {
        	OM_NOTIFY_TO_ERROR("\n\nHeap overflow\n\n");
        	res = false;
        }
        return res;
        //#]
    }
    
    // Return the position of the first e such that 
    // (*e) == (*clone) return 0 if not found
    // Argument void * clone :
    // The search prototype
    //## operation find(void *) const
    inline Rhp_int32_t find(void * clone) const {
        //#[ operation find(void *) const
        Rhp_int32_t position=0;
        // Return the position of the first e such that 
        // (*e) == (*clone) return 0 if not found
        for (Rhp_int32_t i=1; i<=count; i++) {
        	if ( ((*(IOxfTimeout*)theheap[i])) == (*(IOxfTimeout*)clone) ) {
        		position = i; 
        		break;
        	}
        }
        return position;
        //#]
    }
    
    // Check if the heap is empty
    //## operation isEmpty() const
    inline Rhp_int32_t isEmpty(void) const {
        //#[ operation isEmpty() const
        return (count == 0);
        //#]
    }
    
    // Assignment operator
    // Argument const OMUHeap & aHeap :
    // The heap to copy
    //## operation operator=(const OMUHeap & )
    inline OMUHeap & operator=(const OMUHeap & aHeap) {
        //#[ operation operator=(const OMUHeap & )
        copy(aHeap);
        return *this;
        //#]
    }
    
    // Remove the first e such that
    // (*e) == (*clone)	
    // return e if found NULL otherwise
    // Argument void* clone :
    // The element to remove
    //## operation remove(void*)
    inline void * remove(void* clone) {
        //#[ operation remove(void*)
        void* element = NULL;
        
        Rhp_int32_t position = find(clone);
        if (position != 0 ) {
        	element = theheap[position];
        	// Remove theheap[position] by:
        	// 1. Decrementing count, 2. Making position empty and
        	// 3. Trying to place in it the last heap element
        	void* last = theheap[count]; // 3.
        	count--;					 // 2.
        	// Reorder the heap             1.
        	if ( (position == 1) || 
        	     ((*(IOxfTimeout*)last) > *(IOxfTimeout*)theheap[position/2]) ) {
        		takeDown(last,position);
        	} else {
        		takeUp(last,position);
        	}
        }
        return element; 
        //#]
    }
    
    // Cleanup the heap
    //## operation removeAll()
    inline void removeAll(void) {
        //#[ operation removeAll()
        while (count > 0) {
        	trim();
        }
        //#]
    }
    
    // Get the top of the heap
    //## operation top() const
    inline void * top(void) const {
        //#[ operation top() const
        return theheap[1];
        //#]
    }
    
    // Remove top
    //## operation trim()
    inline void trim(void) {
        //#[ operation trim()
        count--;
        if (count > 0) {
        	takeDown(theheap[count+1], 1);  
        }
        //#]
    }
    

protected :

    // Get the element at the given position (called by the iterator)
    // Argument void * pos :
    // The iterator position
    //## operation getCurrent(void *) const
    inline virtual void* getCurrent(void * pos) const {
        //#[ operation getCurrent(void *) const
        void* element = NULL;
        
        if ( ((Rhp_int32_t)(Rhp_uintptr_t)pos >= 1 ) && 
             ((Rhp_int32_t)(Rhp_uintptr_t)pos <= count) ) {
        	element = theheap[(Rhp_int32_t)(Rhp_uintptr_t)pos];
        }
        return element;
        //#]
    }
    
    // Set the initial position for the iterator
    // Argument void * & pos :
    // The initial position (out)
    //## operation getFirst(void * & ) const
    inline virtual void getFirst(void * & pos) const {
        //#[ operation getFirst(void * & ) const
        pos = reinterpret_cast<void*>(1);
        //#]
    }
    
    // Update the provided position to the next position in the container
    // Argument void * & pos :
    // The position to advance
    //## operation getNext(void * & ) const
    inline virtual void getNext(void * & pos) const {
        //#[ operation getNext(void * & ) const
        Rhp_uintptr_t i = reinterpret_cast<Rhp_uintptr_t>(pos) + 1;       
        pos = reinterpret_cast<void*>(i);
        //#]
    }
    

private :

    // Copy a heap
    // Argument const OMUHeap & aHeap :
    // The heap to copy
    //## operation copy(const OMUHeap & )
    inline void copy(const OMUHeap & aHeap) {
        //#[ operation copy(const OMUHeap & )
        if (theheap != aHeap.theheap) {
        	// prevent self copy
        	if (theheap != NULL) {
        		// cleanup before copy
        		OMDELETE(theheap, sizeof(void*) * heapSize);
        	}
        	count = aHeap.count;
        	heapSize = aHeap.heapSize;
        	theheap = static_cast<void**>(OMNEW(void*, heapSize));
        	for (Rhp_int32_t i = 1; i <= count; ++i) {
        		// theheap[0] is unused
        		theheap[i] = aHeap.theheap[i];
        	}
        }
        //#]
    }
    
    // e is a node which needs to be placed in the heap.
    // Its position can be either 'emptyPos' which is currently empty or some position lower than emptyPos (if elements currently there are smaller than e(
    // Argument void * aNode :
    // The element to move
    // Argument const Rhp_int32_t emptyPos :
    // The next empty position
    //## operation takeDown(void *,Rhp_int32_t)
    inline void takeDown(void * aNode, const Rhp_int32_t emptyPos) {
        //#[ operation takeDown(void *,Rhp_int32_t)
        Rhp_int32_t oneLower = emptyPos*2;
        
        // Case 1 - Currently there are no lower positions
        if (oneLower > count) { // Place aNode in empty position and quit
        	theheap[emptyPos] = aNode;
        } else {
        	// Case 2 - There is one lower position
        	if (oneLower == count) {
        		if ((*(IOxfTimeout*)theheap[oneLower]) < (*(IOxfTimeout*)aNode)) { 
        			// The element there is smaller
        			// Put the smaller element in the empty position
        			theheap[emptyPos] = theheap[oneLower];
        			// Put e in the lower position (which we know does not
        			// have occupied positions below it)
        			theheap[oneLower] = aNode;
         	   } else {
         	   	 	// The element there is bigger
        			// Put e in the empty position
        			theheap[emptyPos]= aNode;
        		}
        	} else {
        		// The general Case There are two lower positions
        		// (oneLower and oneLower+1)
        
        		// Make oneLower the position holding the smaller of the items
        		// Since theHeap[i]<theHeap[2*i] && theHeap[i]<theHeap[2*i+1]
        		// is our invariant
        		if ((*(IOxfTimeout*)theheap[oneLower]) > (*(IOxfTimeout*)theheap[oneLower+1])) {
        			oneLower++;
        		}
        
        		if ((*(IOxfTimeout*)theheap[oneLower]) < (*(IOxfTimeout*)aNode)) { 
        			// The "lower" element is smaller
        			// Put the smaller element in the empty position
        			theheap[emptyPos]=theheap[oneLower];
        			takeDown(aNode,oneLower);
        		} else {
        			// Put e in the empty position
        			theheap[emptyPos] = aNode;
        		}
        	}
        }		
        //#]
    }
    
    // e is a node which needs to be placed in the heap.
    // Its position can be either 'emptyPos' which is currently empty or some position higher than emptyPos (if elements currently there are bigger than e)
    // Argument void * aNode :
    // The element to move
    // Argument const Rhp_int32_t aPosition :
    // The next empty position
    //## operation takeUp(void *,Rhp_int32_t)
    inline void takeUp(void * aNode, const Rhp_int32_t aPosition) {
        //#[ operation takeUp(void *,Rhp_int32_t)
        Rhp_int32_t emptyPos = aPosition;
        
        for (;;) {
        	Rhp_int32_t oneHigher = emptyPos/2;
        	if ( (oneHigher > 0) && 
        	    ( (*(reinterpret_cast<IOxfTimeout*>(theheap[oneHigher]))) >
        	      (*(reinterpret_cast<IOxfTimeout*>(aNode))) ) ) {
        		// There is a higher position and 
        		// the element there is bigger than aNode
        		// 1. Put the bigger element in the empty position
        		theheap[emptyPos] = theheap[oneHigher];
        		// 2. Make its old position the empty one
        		emptyPos = oneHigher;
        	} else {
        		// Put element in the empty position
        		theheap[emptyPos] = aNode;
        		break;
        	}
        }
        //#]
    }
    
    ////    Additional operations    ////
    

public :

    //## auto_generated
    inline Rhp_int32_t getCount(void) const {
        //#[ auto_generated
        return count;
        //#]
    }
    
    //## auto_generated
    inline Rhp_int32_t getHeapSize(void) const {
        //#[ auto_generated
        return heapSize;
        //#]
    }
    
    ////    Attributes    ////
    

private :

    // The number of items currently in the Heap
    Rhp_int32_t count;		//## attribute count
    
    // The memory allocated for theHeap
    Rhp_int32_t heapSize;		//## attribute heapSize
    
    // An array of Node*'s - the data of the Heap
    void** theheap;		//## attribute theheap
    
};

//## package Design::oxf::Services::Containers::Typeless

//## class OMUHeap

#endif



