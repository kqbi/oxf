//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: OMUList
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


#ifndef omulist_H
#define omulist_H

//## class OMUList
#include "OMUAbstractContainer.h"
//## dependency OMUIterator
#include "OMUIterator.h"
//## dependency Manager
#include "OXFManager.h"
//## package Design::oxf::Services::Containers::Typeless

//## class OMUList
// type less list
class RP_FRAMEWORK_DLL OMUList : public OMUAbstractContainer {
public :

    // A list node
    //## class OMUList::Item
    class RP_FRAMEWORK_DLL Item {
    //#[ ignore
        // override new & delete operators
        OM_DECLARE_FRAMEWORK_MEMORY_ALLOCATION_OPERATORS
        
        
    //#]
    
        ////    Constructors and destructors    ////
        
    public :
    
        // copy constructor
        // Argument const Item& item :
        // The item to copy
        //## operation Item(const Item&)
        explicit inline Item(const Item& item) : element(item.element), next(item.next)  {
            //#[ operation Item(const Item&)
            //#]
        }
        
        // Constructor
        // Argument void * theElement :
        // The element to hold
        //## operation Item(void *)
        explicit inline Item(void * theElement) : element(theElement), next(NULL)  {
            //#[ operation Item(void *)
            //#]
        }
        
        // Cleanup
        //## operation ~Item()
        inline virtual ~Item(void) {
            //#[ operation ~Item()
            element = NULL;
            next = NULL;
            //#]
        }
        
        ////    Operations    ////
        
        // connect to another item
        // Argument Item* item :
        // The item to connect to
        //## operation connectTo(Item*)
        inline void connectTo(Item* item) {
            //#[ operation connectTo(Item*)
            setNext(item);
            //#]
        }
        
        // Assignment operator
        // Argument const Item& item :
        // The item to copy
        //## operation operator=(const Item&)
        inline Item& operator=(const Item& item) {
            //#[ operation operator=(const Item&)
            element = item.element;
            next = item.next;
            return (*this);
            //#]
        }
        
        ////    Additional operations    ////
        
        //## auto_generated
        inline void * getElement(void) const {
            //#[ auto_generated
            return element;
            //#]
        }
        
        //## auto_generated
        inline void setElement(void * const p_element) {
            //#[ auto_generated
            element = p_element;
            //#]
        }
        
        //## auto_generated
        inline Item* getNext(void) const {
            //#[ auto_generated
            return next;
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
    
        // The element (data)
        void * element;		//## attribute element
        
        // The next item
        Item* next;		//## attribute next
        
    };
    
    ////    Constructors and destructors    ////
    
    // copy constructor and assignment operator
    // Argument const OMUList& aList :
    // The list to copy
    //## operation OMUList(OMUList)
    explicit inline OMUList(const OMUList& aList) : OMUAbstractContainer(), first(NULL), last(NULL)
     	 {
        //#[ operation OMUList(OMUList)
        copy(aList);
        //#]
    }
    
    // Constructor - create an empty list
    //## operation OMUList()
    inline OMUList(void) : OMUAbstractContainer(), first(NULL), last(NULL)  {
        //#[ operation OMUList()
        //#]
    }
    
    // Destructor - empty the list 
    //## operation ~OMUList()
    inline virtual ~OMUList(void) {
        //#[ operation ~OMUList()
        removeAll();
        first = NULL;
        last = NULL;
        //#]
    }
    
    ////    Operations    ////
    
    // Add an object to the list (at its end)
    // Argument void * anElement :
    // The element to add
    //## operation add(void *)
    inline void add(void * anElement) {
        //#[ operation add(void *)
        // Create a new list item
        Item* item = new Item(anElement);
        // Insert it into the list at the end
        if (first == NULL) {
        	first = item;
        } else {
        	last->connectTo(item);
        }
        last = item;
        //#]
    }
    
    // if getCount() >= i - Add p after i'th element else Add p at end
    // Argument const Rhp_int32_t anIndex :
    // The index to add the element at
    // Argument void * anElement :
    // The element to add
    //## operation addAt(Rhp_int32_t,void *)
    inline void addAt(const Rhp_int32_t anIndex, void * anElement) {
        //#[ operation addAt(Rhp_int32_t,void *)
        Rhp_int32_t index = anIndex;
        
        if ((index == 0) || (first == NULL)) {
        	// Insert anElement in first position
        	addFirst(anElement);
        } else {
        	// Find the position of insertion
        	Item* item = NULL;
        	for (item = first; (item != last) && (index > 0); item = item->getNext()) {
        		index--;
        	}
        	// Insert enElement in last position
        	if (item == last) {
        		add(anElement);
        	} else {
        		Item* newGuy = new Item(anElement);
        		Item* nextGuy = item->getNext();
        		item->connectTo(newGuy);
        		newGuy->connectTo(nextGuy);
        	}
        }
        //#]
    }
    
    // Add an object to the list (at its beginning)
    // Argument void * anElement :
    // The element to add
    //## operation addFirst(void *)
    inline void addFirst(void * anElement) {
        //#[ operation addFirst(void *)
        // Create a new list item
        Item* item = new Item(anElement);
        // Insert it into the list at the begining
        item->connectTo(first);
        first = item;
        if (last == NULL) {
        	last = first;
        }
        //#]
    }
    
    // Find an object in the list, return 1 if found or 0 otherwise
    // Argument const void * anElement :
    // The element to find
    //## operation find(const void * ) const
    inline bool find(const void * anElement) const {
        //#[ operation find(const void * ) const
        bool status = false;
        
        for (Item* index = first; index != NULL; index = index->getNext()) {
        	if (index->getElement() == anElement) {
        		status = true;   
        		break;
        	}
        }
        return status;
        //#]
    }
    
    // return the element in a given index
    // Argument const Rhp_int32_t anIndex :
    // the index
    //## operation getAt(Rhp_int32_t) const
    inline void * getAt(const Rhp_int32_t anIndex) const {
        //#[ operation getAt(Rhp_int32_t) const
        Rhp_int32_t index = anIndex;
        Item* item = first;      
        
        while ( (item != NULL) && (index > 0) ) {
        	item = item->getNext();
        	index--;
        }
        
        if (item != NULL) {
        	item = static_cast<Item*>(item->getElement());
        }
        
        return static_cast<void*>(item);
        //#]
    }
    
    // return the number of elements in the list
    //## operation getCount() const
    inline Rhp_int32_t getCount(void) const {
        //#[ operation getCount() const
        Rhp_int32_t count = 0;
        for (Item* iter = first; iter != NULL; iter = iter->getNext()) {
        	++count;
        }
        return count;
        //#]
    }
    
    // return true if the list is empty and false otherwise
    //## operation isEmpty() const
    inline bool isEmpty(void) const {
        //#[ operation isEmpty() const
        return (first == NULL);
        //#]
    }
    
    // Assignment operator
    // Argument const OMUList& aList :
    // The list to copy
    //## operation operator=(OMUList)
    inline OMUList& operator=(const OMUList& aList) {
        //#[ operation operator=(OMUList)
        copy(aList);
        return (*this);
        //#]
    }
    
    // return the element at the given index
    // Argument const Rhp_int32_t anIndex :
    // The index
    //## operation operator[](Rhp_int32_t) const
    inline void * operator[](const Rhp_int32_t anIndex) const {
        //#[ operation operator[](Rhp_int32_t) const
        return getAt(anIndex);
        //#]
    }
    
    // Remove the first occurrence of a specific Object from list
    // Argument const void * anElement :
    // The element to remove
    //## operation remove(void *)
    inline void remove(const void * anElement) {
        //#[ operation remove(void *)
        if (first != NULL) {
        	if (first->getElement() == anElement) {
        		// Special case when the object is first
        		_removeFirst();
        	} else {
        		// Search for the object
        		Item* prev = first;
        		Item* cur = first->getNext();
        		while (cur != NULL) {
        			if (cur->getElement() == anElement) {
        				prev->connectTo(cur->getNext());
        				if (cur->getNext() == NULL) {
        					last = prev;
        				}
        				delete cur;
        				break;
        			}
        			prev = cur;
        			cur = cur->getNext();
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
    // Argument const Item* item :
    // The item to remove
    //## operation removeItem(Item)
    inline void removeItem(const Item* item) {
        //#[ operation removeItem(Item)
        if (first != NULL) {
        	if (first == item) {
        		// Special case when the required item is first
        		_removeFirst();
        	} else {
        		// Search for the item
        		Item* prev = first;
        		Item* cur = first->getNext();
        		while (cur != NULL) {
        			if (cur == item) { 
        				// item found
        				prev->connectTo(cur->getNext());
        				if (cur->getNext() == NULL) {
        					last = prev;
        				}
        				delete cur;
        				break;
        			}
        			// Advance to next item
        			prev = cur;
        			cur = cur->getNext();
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

    // Remove first item from list
    //## operation _removeFirst()
    inline void _removeFirst(void) {
        //#[ operation _removeFirst()
        if (first != NULL) {
        	Item* tmp = first;
        	first = first->getNext();
        	if (first == NULL) {
        		last = NULL;
        	}
        	delete tmp;
        }
        //#]
    }
    
    // Copy a list
    // Argument const OMUList& aList :
    // The list to copy
    //## operation copy(OMUList)
    inline void copy(const OMUList& aList) {
        //#[ operation copy(OMUList)
        if (first != aList.first) {
        	// avoid self copy
        	removeAll();
        	OMUIterator iter(aList);
        	Rhp_int32_t length = aList.getCount();
        	while (length--) {
        		add(*iter);
        		++iter;
        	}
        }
        //#]
    }
    
    // Get the item in the provided position (supplied by the iterator)
    // Argument void * pos :
    // The position
    //## operation getCurrent(void *) const
    inline void * getCurrent(void * pos) const {
        //#[ operation getCurrent(void *) const
        void* element;
        
        if (pos == NULL) {
        	element = NULL;
        } else {
        	element = (reinterpret_cast<Item*>(pos))->getElement();
        }
        return element;
        //#]
    }
    
    // iteration interface - get the initial position
    // Argument void *& pos :
    // The position to set
    //## operation getFirst(void *) const
    inline void getFirst(void *& pos) const {
        //#[ operation getFirst(void *) const
        pos = first;
        //#]
    }
    
    // Get the next position for the iterator
    // Argument void *& pos :
    // The current position
    //## operation getNext(void *) const
    inline void getNext(void *& pos) const {
        //#[ operation getNext(void *) const
        if (pos != NULL) {
        	pos = (reinterpret_cast<Item*>(pos))->getNext();
        }
        //#]
    }
    
    ////    Relations and components    ////
    

private :

    Item* first;		//## link first
    
    Item* last;		//## link last
    
};

#endif



