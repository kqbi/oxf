//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: OMHeap
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


#ifndef omheap_H
#define omheap_H

//## dependency MemoryManagerMacros
#include "OXFMemoryManagerMacros.h"
//## dependency NotifyMacros
#include "OXFNotifyMacros.h"
//## class OMHeap
#include "OMAbstractContainer.h"
//## dependency OMMemoryManager
#include "ommemorymanager.h"
//## package Design::oxf::Services::Containers::TypeSafe

//## class OMHeap
// //////////////////////////////////////////////////////////
// template class OMHeap
// 
// The Heap invariants:
// 1. theHeap[0] is empty - this is so we have "easy arithmetic"
// 2. theHeap[1] -- theHeap[count] hold the actual elements
// 3. theHeap[i]<theHeap[2*i] && theHeap[i]<theHeap[2*i+1]
// 			  for all i>0, 2*i<=count, 2*i+1<=count.
// 	  Hence Min = theHeap[1]
// 
// 
// OMHeap<Node> is a heap holding elements of type "Node*"
// 
// //////////////////////////////////////////////////////////
template <class Node> class OMHeap : public OMAbstractContainer<Node> {
    ////    Constructors and destructors    ////
    
public :

    // Initialize a heap with a given size
    // Argument const Rhp_int32_t size = 100 :
    // The heap size (number of elements)
    //## operation OMHeap(Rhp_int32_t)
    inline OMHeap(const Rhp_int32_t size = 100) : count(0), heapSize(0), theheap(NULL) {
        //#[ operation OMHeap(Rhp_int32_t)
        heapSize = size + 1; // theheap[0] is never used
        theheap = static_cast<Node**>(OMNEW(Node*, heapSize));
        //#]
    }
    
    // copy constructor and assignment operator
    // Argument const OMHeap<Node> & aHeap :
    // The heap to copy
    //## operation OMHeap(const OMHeap<Node> & )
    inline OMHeap(const OMHeap<Node> & aHeap) : count(0), heapSize(0), theheap(NULL) {
        //#[ operation OMHeap(const OMHeap<Node> & )
        copy(aHeap);
        //#]
    }
    
    // cleanup
    //## operation ~OMHeap()
    inline ~OMHeap(void) {
        //#[ operation ~OMHeap()
        OMDELETE(theheap, sizeof(Node*) * heapSize);
        theheap = NULL;
        //#]
    }
    
    ////    Operations    ////
    
    // Add node to heap
    // Argument Node* aNode :
    // The element to add
    //## operation add(Node*)
    inline bool add(Node* aNode) {
        //#[ operation add(Node*)
        bool res = true;
        if ((count + 1) < heapSize) {
        	++count;
        	takeUp(aNode,count);
        } else {
        	OM_NOTIFY_TO_ERROR("\n\nHeap overflow\n\n");
        	res = false;
        }
        return res;
        //#]
    }
    
    // Return the position of the first node such that 
    // (*node) == (*clone) return 0 if not found
    // Argument Node* clone :
    // The search prototype
    //## operation find(Node*) const
    inline Rhp_int32_t find(Node* clone) const {
        //#[ operation find(Node*) const
        Rhp_int32_t position=0;
        
        // Return the position of the first Node such that 
        // (*node) == (*clone) return 0 if not found
        for (Rhp_int32_t i=1; i<=count; i++ ) {
        	if (*(theheap[i]) == *clone) {
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
    // Argument const OMHeap<Node> & aHeap :
    // The heap to copy
    //## operation operator=(const OMHeap<Node> & )
    inline OMHeap<Node> & operator=(const OMHeap<Node> & aHeap) {
        //#[ operation operator=(const OMHeap<Node> & )
        copy(aHeap);
        return (*this);
        //#]
    }
    
    // Remove the first e such that
    // (*e) == (*clone)	
    // return e if found NULL otherwise
    // Argument Node* clone :
    // The element to remove
    //## operation remove(Node*)
    inline Node * remove(Node* clone) {
        //#[ operation remove(Node*)
        Node* aNode;
        
        Rhp_int32_t position = find(clone);
        if (position == 0) {
        	aNode = NULL;
        } else {
        	aNode = theheap[position];
        	// Remove theheap[position] by:
        	// 1. Decrementing count, 2. Making position empty and
        	// 3. Trying to place in it the last heap element
        	Node* last = theheap[count]; // 3.
        	count--;					 // 2.
        	// Reorder the heap             1.
        	if ( (position == 1) || (*last > *theheap[position/2]) ) {
        		takeDown(last,position);
        	} else {
        		takeUp(last,position); 
        	}
        }
        return aNode; 
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
    inline Node * top(void) const {
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
    inline virtual Node& getCurrent(void * pos) const {
        //#[ operation getCurrent(void *) const
        Rhp_int32_t position = (Rhp_int32_t)(Rhp_uintptr_t)(pos);
        
        if ( (position >= 1) && (position <= count) ) {
           	return *(theheap[position]);
        } else {
          	return OMNullValue<Node>::get();
        }
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
        pos = reinterpret_cast<void*>(reinterpret_cast<Rhp_uintptr_t>(pos) + 1);
        //#]
    }
    

private :

    // Copy a heap
    // Argument const OMHeap<Node> & aHeap :
    // The heap to copy
    //## operation copy(const OMHeap<Node> & )
    inline void copy(const OMHeap<Node> & aHeap) {
        //#[ operation copy(const OMHeap<Node> & )
        if (theheap != aHeap.theheap) {
        	// prevent self copy
        	if (theheap != NULL) {
        		// cleanup before copy
        		OMDELETE(theheap, sizeof(Node*) * heapSize);
        	}
        	count = aHeap.count;
        	heapSize = aHeap.heapSize;
        	theheap = static_cast<Node**>(OMNEW(Node*, heapSize));
        	for (Rhp_int32_t i = 1; i <= count; ++i) {
        		// theheap[0] is unused
        		theheap[i] = aHeap.theheap[i];
        	}
        }
        //#]
    }
    
    // a Node is a node which needs to be placed in the heap.
    // Its position can be either 'emptyPos' which is currently empty or some position lower than emptyPos (if elements currently there are smaller than aNode(
    // Argument Node* aNode :
    // The element to move
    // Argument const Rhp_int32_t emptyPos :
    // The next empty position
    //## operation takeDown(Node*,Rhp_int32_t)
    inline void takeDown(Node* aNode, const Rhp_int32_t emptyPos) {
        //#[ operation takeDown(Node*,Rhp_int32_t)
        Rhp_int32_t oneLower = emptyPos*2;  
        
        // Case 1 - Currently there are no lower positions
        if (oneLower > count) { 
        	// Place aNode in empty position and quit
        	theheap[emptyPos] = aNode;
        } else {
        	// Case 2 - There is one lower position
        	if (oneLower == count) {
        		if (*theheap[oneLower] < *aNode) {
        			// The element there is smaller
        			// Put the smaller element in the empty position
        			theheap[emptyPos] = theheap[oneLower];
        			// Put aNode in the lower position (which we know does not
        			// have occupied positions below it)
        			theheap[oneLower] = aNode;
        		} else {
        			// The element there is bigger
        			// Put aNode in the empty position
        			theheap[emptyPos]= aNode;
        		}
        	} else {
                // The general Case There are two lower positions
        		// (oneLower and oneLower+1)
        		// Make oneLower the position holding the smaller of the items
        		// Since theHeap[i]<theHeap[2*i] && theHeap[i]<theHeap[2*i+1]
        		// is our invariant
        		if (*theheap[oneLower] > *theheap[oneLower+1]) {
        			oneLower++;                                  
        		}
        		if (*theheap[oneLower] < *aNode) {
        			// The "lower" element is smaller
        			// Put the smaller element in the empty position
        			theheap[emptyPos]=theheap[oneLower];
        			takeDown(aNode,oneLower);
        		} else {
        			// Put aNode in the empty position
        			theheap[emptyPos] = aNode;
        		}
        	}
        }
        //#]
    }
    
    // aNode is a node which needs to be placed in the heap.
    // Its position can be either 'emptyPos' which is currently empty or some position higher than emptyPos (if elements currently there are bigger than aNode)
    // Argument Node* aNode :
    // The element to move
    // Argument const Rhp_int32_t emptyPos :
    // The next empty position
    //## operation takeUp(Node*,Rhp_int32_t)
    inline void takeUp(Node* aNode, const Rhp_int32_t emptyPos) {
        //#[ operation takeUp(Node*,Rhp_int32_t)
        Rhp_int32_t pos = emptyPos;
        Rhp_int32_t oneHigher; 
        
        for (;;) {
        	oneHigher = pos/2;
        	if ( (oneHigher > 0) && (*theheap[oneHigher] > *aNode) ) {
        		// There is a higher position and 
        		// the element there is bigger than aNode
        		// 1. Put the bigger element in the empty position
        		theheap[pos]= theheap[oneHigher];
        		// 2. Make its old position the empty one
        		pos = oneHigher;
        	} else {
        		// Put aNode in the empty position
        		theheap[pos] = aNode;
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
    Node** theheap;		//## attribute theheap
    
};

//## package Design::oxf::Services::Containers::TypeSafe

//## class OMHeap

#endif



