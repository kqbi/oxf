//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: OMList
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


#ifndef omlist_H
#define omlist_H

//## class OMList
#include "OMAbstractContainer.h"
//## dependency OMIterator
#include "OMIterator.h"
//## dependency Manager
#include "OXFManager.h"
//## package Design::oxf::Services::Containers::TypeSafe

//## class OMList
// Linked list container class
template <class Concept> class RP_FRAMEWORK_DLL OMList : public OMAbstractContainer<Concept> {
public :

    // List node
    //## class OMList::Item
    class Item {
    public :
    
        ////    Friend List    ////
        
        friend  class OMList<Concept>;
        
        
    
    //#[ ignore
        // override new & delete operators
        OM_DECLARE_FRAMEWORK_MEMORY_ALLOCATION_OPERATORS
        
        
    //#]
    
        ////    Constructors and destructors    ////
        
    public :
    
        // Initialize an item with a given data
        // Argument const Concept& theConcept :
        // The item data
        //## operation Item(const Concept&)
        inline Item(const Concept& theConcept) : concept(theConcept), next(NULL) {
            //#[ operation Item(const Concept&)
            //#]
        }
        
        // Copy constructor
        // Argument const Item& other :
        // The item to copy
        //## operation Item(const Item&)
        inline Item(const Item& other) : concept(other.concept), next(other.next) {
            //#[ operation Item(const Item&)
            //#]
        }
        
        // Cleanup
        //## operation ~Item()
        inline ~Item(void) {
            //#[ operation ~Item()
            next = NULL;
            //#]
        }
        
        ////    Operations    ////
        
        // Connect to the specified item
        // Argument Item* item :
        // The item to connect to
        //## operation connectTo(Item*)
        inline void connectTo(Item* item) {
            //#[ operation connectTo(Item*)
            next = item;
            //#]
        }
        
        // Get the next item in the linked list
        //## operation getNext() const
        inline Item* getNext(void) const {
            //#[ operation getNext() const
            return next;
            //#]
        }
        
        // Assignment operator
        // Argument const Item& other :
        // The item to copy
        //## operation operator=(const Item&)
        inline Item& operator=(const Item& other) {
            //#[ operation operator=(const Item&)
            next = other.next;
            concept = other.concept;	// assuming operator = for Concept
            return (*this);
            //#]
        }
        
        ////    Additional operations    ////
        
        //## auto_generated
        inline Concept getConcept(void) const {
            //#[ auto_generated
            return concept;
            //#]
        }
        
        //## auto_generated
        inline void setConcept(Concept p_concept) {
            //#[ auto_generated
            concept = p_concept;
            //#]
        }
        
        //## auto_generated
        inline void setNext(Item* const p_next) {
            //#[ auto_generated
            next = p_next;
            //#]
        }
        
        ////    Attributes    ////
        
    
    private :
    
        // the data of the node
        Concept concept;		//## attribute concept
        
        // the next item in the list
        Item* next;		//## attribute next
        
    };
    
    ////    Constructors and destructors    ////
    
    // Constructor - create an empty list
    //## operation OMList()
    inline OMList(void) : count_(0U), first(NULL), last(NULL) {
        //#[ operation OMList()
        //#]
    }
    
    // copy constructor
    // Argument const OMList<Concept> & aList :
    // The list to copy
    //## operation OMList(const OMList<Concept> & )
    inline OMList(const OMList<Concept> & aList) : OMAbstractContainer<Concept>(), count_(0U), first(NULL), last(NULL) 
{
        //#[ operation OMList(const OMList<Concept> & )
        copy(aList);
        //#]
    }
    
    // Destructor - empty the list 
    //## operation ~OMList()
    inline virtual ~OMList(void) {
        //#[ operation ~OMList()
        removeAll();
        //#]
    }
    
    ////    Operations    ////
    
    // Add an object to the list (at its end)
    // Argument Concept aConcept :
    // The element to add
    //## operation add(Concept )
    inline void add(Concept aConcept) {
        //#[ operation add(Concept )
        // Create a new list item
        Item* item = new Item(aConcept); 
        
        // Insert it into the list at the end
        if (first == NULL) {
        	first = item;
        } else {
        	last->connectTo(item);
        }
        last = item;
        count_ = count_ +1;
        //#]
    }
    
    // if getCount>=i - Add c after i'th element else Add c at end
    // Argument const Rhp_int32_t anIndex :
    // The index
    // Argument Concept aConcept :
    // The element to add
    //## operation addAt(Rhp_int32_t,Concept )
    inline void addAt(const Rhp_int32_t anIndex, Concept aConcept) {
        //#[ operation addAt(Rhp_int32_t,Concept )
        if ( (anIndex == 0) || (first == NULL) ) {
        	// Insert aConcept in first position
        	addFirst(aConcept);
        } else {
        	// Find the position of insertion
        	Item* item = first;
        	for (Rhp_int32_t j = 1; (j < anIndex); j++) {
        		if ( item == last ) {
        			break;
        		}
        		item = item->next;                                       
        	}
        
        	if (item == last) {
        		// Insert aConcept in last position
        		add(aConcept);
        	} else {
        		Item* newGuy = new Item(aConcept);
        		Item* nextGuy = item->next;
        		item->connectTo(newGuy);
        		newGuy->connectTo(nextGuy);
        		count_ = count_ +1;
        	}
        }
        //#]
    }
    
    // Add an object to the list (at its beginning)
    // Argument Concept aConcept :
    // The element to add
    //## operation addFirst(Concept )
    inline void addFirst(Concept aConcept) {
        //#[ operation addFirst(Concept )
        // Create a new list item
        Item* item = new Item(aConcept);
        
        // Insert it into the list at the begining
        item->connectTo(first);
        first = item;
        if (last == NULL) {
        	last = first;
        }
        count_ = count_ +1;
        //#]
    }
    
    // Find an object in the list
    // Argument Concept aConcept :
    // The element to find
    //## operation find(Concept ) const
    inline bool find(Concept aConcept) const {
        //#[ operation find(Concept ) const
        bool status = false;
        for (Item* i = first; i != NULL; i = i->next) {
        	if (i->concept == aConcept) {
        		status = true;
        		break;
        	}
        }
        return status;
        //#]
    }
    
    // Get the element in the given index
    // Argument const Rhp_int32_t anIndex :
    // The index
    //## operation getAt(Rhp_int32_t) const
    inline Concept & getAt(const Rhp_int32_t anIndex) const {
        //#[ operation getAt(Rhp_int32_t) const
        void* item;
        getFirst(item);
        for (Rhp_int32_t j = 0; j < anIndex; j++) {
        	if (item != NULL) {
        		getNext(item);
        	} else {
        		break;
        	}
        }
        return getCurrent(item);
        //#]
    }
    
    // Get the element in the head of the list
    //## operation getFirstConcept() const
    inline Concept & getFirstConcept(void) const {
        //#[ operation getFirstConcept() const
        return getCurrent(first);
        //#]
    }
    
    // Get the element in the tail of the list
    //## operation getLastConcept() const
    inline Concept & getLastConcept(void) const {
        //#[ operation getLastConcept() const
        return getCurrent(last);
        //#]
    }
    
    // Check if the list is empty
    //## operation isEmpty() const
    inline bool isEmpty(void) const {
        //#[ operation isEmpty() const
        return (first == NULL);
        //#]
    }
    
    // Assignment operator
    // Argument const OMList<Concept> & aList :
    // The list to copy
    //## operation operator=(const OMList<Concept> & )
    inline OMList<Concept> & operator=(const OMList<Concept> & aList) {
        //#[ operation operator=(const OMList<Concept> & )
        copy(aList);
        return (*this);
        //#]
    }
    
    // Get the element at the provided index
    // Argument const Rhp_int32_t anIndex :
    // The index
    //## operation operator[](Rhp_int32_t) const
    inline Concept & operator[](const Rhp_int32_t anIndex) const {
        //#[ operation operator[](Rhp_int32_t) const
        return getAt(anIndex);
        //#]
    }
    
    // Remove the first occurrence of a specific Object (Concept)
    // from list
    // Argument Concept aConcept :
    // The element to remove
    //## operation remove(Concept )
    inline void remove(Concept aConcept) {
        //#[ operation remove(Concept )
        // Check that we have something to remove
        if (first != NULL) {
        	if (first->concept == aConcept) { 
        		// Special case if the object is first
        		_removeFirst();
        	} else {
        		// Search for the object
        		Item* prev = first;
        		Item* cur = first->next;
        		while (cur!=NULL) {
        			if (cur->concept == aConcept) {
        				prev->connectTo(cur->next);
        				if (cur->next == NULL) {
        					last = prev;
        				}
        				delete cur;
        				count_ = count_ -1;
        				break;
        			} 
        			prev = cur;
        			cur = cur->next;
        		}
        	}
        }
        //#]
    }
    
    // Remove all items from list
    //## operation removeAll()
    inline void removeAll(void) {
        //#[ operation removeAll()
        while (first != NULL) {
        	_removeFirst();
        }
        //#]
    }
    
    // Remove first item from list
    //## operation removeFirst()
    inline void removeFirst(void) {
        //#[ operation removeFirst()
        if (first != NULL) {
        	_removeFirst();
        }
        //#]
    }
    
    // Remove a specific Item from list
    // Argument Item* anItem :
    // The list node to remove
    //## operation removeItem(Item*)
    inline void removeItem(Item* anItem) {
        //#[ operation removeItem(Item*)
        // Check that we have something to remove
        if (first != NULL) {
        	if (first == anItem) {
        		// Special case if the required item is first
        		_removeFirst();     
        	} else {
        		// Search for the item
        		Item* prev = first;
        		Item* cur = first->next;
        		while (cur != NULL) {
        			if (cur == anItem) {
        				// item found
        				prev->connectTo(cur->next);
        				if (cur->next == NULL) {
        					last = prev;
        				}
        				delete cur;
        				count_ = count_ -1;
        				break;
        			} 
        			// Advance to next item
        			prev = cur;
        			cur = cur->next;
        		}
        	}       
        }
        //#]
    }
    
    // Remove last item from list - inefficient as we keep no
    // backward pointers
    //## operation removeLast()
    inline void removeLast(void) {
        //#[ operation removeLast()
        removeItem(last);
        //#]
    }
    

protected :

    // unsafe Remove first item from list
    //## operation _removeFirst()
    inline void _removeFirst(void) {
        //#[ operation _removeFirst()
        if (first != NULL)
        {
        	Item* tmp = first;
        	first = first->next;
        	if (first == NULL) {
        		last = NULL;
        	}
        	delete tmp;
        	count_ = count_ -1;
        }
        //#]
    }
    
    // Copy the specified list
    // Argument const OMList<Concept> & aList :
    // The list to copy
    //## operation copy(const OMList<Concept> & )
    inline void copy(const OMList<Concept> & aList) {
        //#[ operation copy(const OMList<Concept> & )
        if (first != aList.first) {
        	// avoid self copy
        	removeAll();
        	OMIterator<Concept> iter(aList);
        	Rhp_int32_t length = aList.getCount();
        	while (length--) {
        		add(*iter);
        		++iter;
        	}
        }
        //#]
    }
    
    // Get the element at the given position (called by the iterator)
    // Argument void * pos :
    // The iterator position
    //## operation getCurrent(void *) const
    inline virtual Concept & getCurrent(void * pos) const {
        //#[ operation getCurrent(void *) const
        /*LDRA_INSPECTED 7 C  : Can't find a way to have a single return */
        if (pos != NULL) {
        	return reinterpret_cast<Item*>(pos)->concept;
        } else {
        	return OMNullValue<Concept>::get();
        }    
        //#]
    }
    
    // Set the initial position for the iterator
    // Argument void*& pos :
    // The list head (out)
    //## operation getFirst(void*& ) const
    inline virtual void getFirst(void*& pos) const {
        //#[ operation getFirst(void*& ) const
        pos = first;
        //#]
    }
    
    // Get the position of the list tail
    // Argument void*& pos :
    // The list tail (out)
    //## operation getLast(void*& ) const
    inline virtual void getLast(void*& pos) const {
        //#[ operation getLast(void*& ) const
        pos = last;
        //#]
    }
    
    // Update the provided position to the next position in the container
    // Argument void*& pos :
    // The iterator position to advance
    //## operation getNext(void*& ) const
    inline virtual void getNext(void*& pos) const {
        //#[ operation getNext(void*& ) const
        pos = reinterpret_cast<Item*>(pos)->next;
        //#]
    }
    
    ////    Additional operations    ////
    

public :

    //## auto_generated
    inline Rhp_int32_t getCount(void) const {
        //#[ auto_generated
        return count_;
        //#]
    }
    
    ////    Attributes    ////
    

protected :

    // the number of elements in the list
    Rhp_int32_t count_;		//## attribute count_
    

private :

    // the list head
    Item* first;		//## attribute first
    
    // the tail head
    Item* last;		//## attribute last
    
};

//## package Design::oxf::Services::Containers::TypeSafe

//## class OMList

#endif



