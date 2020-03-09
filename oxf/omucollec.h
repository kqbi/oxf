//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: OMUCollection
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


#ifndef omucollec_H
#define omucollec_H

//## dependency Manager
#include "OXFManager.h"
//## class OMUCollection
#include "OMUAbstractContainer.h"
//## dependency OMUIterator
#include "OMUIterator.h"
//## package Design::oxf::Services::Containers::Typeless

//## class OMUCollection
// A type less dynamic array
class RP_FRAMEWORK_DLL OMUCollection : public OMUAbstractContainer {
public :

    // constants
    //## type defaultValues
    enum defaultValues {
        DefaultStartSize = 20,
        DefaultFactor = 2
    };
    
    ////    Constructors and destructors    ////
    
    // copy constructor and assignment operator
    // Argument const OMUCollection& aCollection :
    // The collection to copy
    //## operation OMUCollection(OMUCollection)
    explicit inline OMUCollection(const OMUCollection& aCollection) : OMUAbstractContainer(), count(0), size(0), 
theLink(NULL) {
        //#[ operation OMUCollection(OMUCollection)
        copy(aCollection);
        //#]
    }
    
    // Constructor
    // Argument const Rhp_int32_t theSize = DefaultStartSize :
    // The initial array size
    //## operation OMUCollection(Rhp_int32_t)
    explicit inline OMUCollection(const Rhp_int32_t theSize = DefaultStartSize) : OMUAbstractContainer(), count(0), 
size(0), theLink(NULL) {
        //#[ operation OMUCollection(Rhp_int32_t)
        size = theSize;
        if (size > 0) {
        	theLink = static_cast<void**>(OMNEW(void*, size));
        }
        //#]
    }
    
    // Destructor	
    //## operation ~OMUCollection()
    inline virtual ~OMUCollection(void) {
        //#[ operation ~OMUCollection()
        if (theLink != NULL) {
        	OMDELETE(theLink, sizeof(void*) * size);
        }
        theLink = NULL;
        size = 0;
        count = 0;
        //#]
    }
    
    ////    Operations    ////
    
    // add an element to the collection, grow if need to
    // Argument void * anElement :
    // The element to add
    //## operation add(void *)
    inline void add(void * anElement) {
        //#[ operation add(void *)
        if (count >= size) {
        	reorganize();
        }
        theLink[count++] = anElement;
        //#]
    }
    
    // Add new element if in range, without increasing the collection size.
    // Return 0 if fail, or 1 on success.
    // Argument const Rhp_int32_t index :
    // The position to add the element at
    // Argument void * anElement :
    // The element to add
    //## operation addAt(Rhp_int32_t,void *)
    inline void addAt(const Rhp_int32_t index, void * anElement) {
        //#[ operation addAt(Rhp_int32_t,void *)
        if (index >= 0) {
        	if (index < count) {
        		theLink[index] = anElement;
        	} 
        	else {
        		if (index == count && count < size) {
        			theLink[count++] = anElement;
        		}
        	}
        }
        
        //#]
    }
    
    // If p in the collection return 1 else return 0
    // Argument void * anElement :
    // The element to find
    //## operation find(void *) const
    inline Rhp_int32_t find(void * anElement) const {
        //#[ operation find(void *) const
        Rhp_int32_t pos = 0; 
        
        for (Rhp_int32_t i = 0; i < count; i++) {
        	if (theLink[i] == anElement) {
        		pos = 1;
        		break;
        	}
        }
        return pos;
        //#]
    }
    
    // return the element at index i, if i is out of range, return 0;
    // Argument const Rhp_int32_t anIndex :
    // The index to get the element from
    //## operation getAt(Rhp_int32_t) const
    inline void * getAt(const Rhp_int32_t anIndex) const {
        //#[ operation getAt(Rhp_int32_t) const
        void* element = NULL;
        
        if ( (anIndex >= 0) && (anIndex < count) ) {
        	element = theLink[anIndex];
        }
        return element;
        //#]
    }
    
    // return true if the collection is empty, else return false
    //## operation isEmpty() const
    inline bool isEmpty(void) const {
        //#[ operation isEmpty() const
        return (count == 0);
        //#]
    }
    
    // Assignment operator
    // Argument const OMUCollection& aCollection :
    // The collection to copy
    //## operation operator=(OMUCollection)
    inline OMUCollection& operator=(const OMUCollection& aCollection) {
        //#[ operation operator=(OMUCollection)
        copy(aCollection);
        return *this;
        //#]
    }
    
    // operator [] - return the element in index i, or NULL if out of range
    // Argument const Rhp_int32_t anIndex :
    // The index to get the element from
    //## operation operator[](Rhp_int32_t)
    inline void * operator[](const Rhp_int32_t anIndex) {
        //#[ operation operator[](Rhp_int32_t)
        void* element = NULL;
        
        if ( (anIndex >= 0) && (anIndex < count) ) {
        	element = theLink[anIndex];
        }
        return element;
        //#]
    }
    
    // remove p from the collection
    // Argument void * anElement :
    // The element to remove
    //## operation remove(void *)
    inline void remove(void * anElement) {
        //#[ operation remove(void *)
        for (Rhp_int32_t i = 0; i < count; i++) {
        	if (theLink[i] == anElement) { 
        		removeByIndex(i);
        		break;
        	}
        }
        //#]
    }
    
    // clean up, and reset
    //## operation removeAll()
    inline void removeAll(void) {
        //#[ operation removeAll()
        OMDELETE(theLink, sizeof(void*) * size);
        count = 0;
        size = DefaultStartSize;
        theLink = static_cast<void**>(OMNEW(void*, size));
        //#]
    }
    
    // remove the element in index i
    // Argument const Rhp_int32_t anIndex :
    // The index of the element to remove
    //## operation removeByIndex(Rhp_int32_t)
    inline void removeByIndex(const Rhp_int32_t anIndex) {
        //#[ operation removeByIndex(Rhp_int32_t)
        if ( (anIndex < count) && (anIndex > -1) ) {
        	theLink[anIndex] = theLink[--count];
        }
        //#]
    }
    
    // reorganize the collection, and grow if need to
    // Argument const Rhp_int32_t aFactor = DefaultFactor :
    // Size growth factor
    //## operation reorganize(Rhp_int32_t)
    inline void reorganize(const Rhp_int32_t aFactor = DefaultFactor) {
        //#[ operation reorganize(Rhp_int32_t)
        Rhp_int32_t factor = aFactor;
        if (factor < 1) {
        	factor = 1;
        }
        Rhp_int32_t oldSize = size;
        size = (count * factor) + 1;
        // create a temporary array in the new size
        void** tmpLink = reinterpret_cast<void**>(OMNEW(void*, size));
        memset((void*) tmpLink, 0, size);
        // copy the data to the temp array
        for (Rhp_int32_t i = 0; i < count; i++) {
        	tmpLink[i] = theLink[i];
        }
        // replace arrays
        OMDELETE(theLink, sizeof(void*) * oldSize);
        theLink = tmpLink;
        //#]
    }
    
    // set an p in i
    // return 0 if fail, or 1 on success
    // Argument const Rhp_int32_t anIndex :
    // The index
    // Argument const void * anElement :
    // The element
    //## operation setAt(Rhp_int32_t,void *)
    inline Rhp_int32_t setAt(const Rhp_int32_t anIndex, const void * anElement) {
        //#[ operation setAt(Rhp_int32_t,void *)
        Rhp_int32_t status;
        if ((anIndex< 0) || (anIndex >= count)) {
        	status = 0;
        } else {
        	theLink[anIndex] = (void*)anElement;
        	status = 1;
        }
        return status;
        //#]
    }
    

protected :

    // Copy a collection
    // Argument const OMUCollection& aCollection :
    // The collection to copy
    //## operation copy(OMUCollection)
    inline void copy(const OMUCollection& aCollection) {
        //#[ operation copy(OMUCollection)
        if (theLink != aCollection.theLink) {
        	// avoid self copy
        	if (theLink != NULL) {
        		// cleanup before copy
        		OMDELETE(theLink, sizeof(void*) * size);
        	}
        
        	count = aCollection.count;
        	size = aCollection.size;
        	theLink = static_cast<void**>(OMNEW(void*, size));
        
        	for (Rhp_int32_t i = 0; i < count; ++i) {
        		theLink[i] = aCollection.theLink[i];
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
        Rhp_int32_t index = (Rhp_int32_t)(Rhp_uintptr_t)(pos);
        return getAt(index);
        //#]
    }
    
    // iteration interface
    // Argument void *& pos :
    // The position to set
    //## operation getFirst(void *) const
    inline void getFirst(void *& pos) const {
        //#[ operation getFirst(void *) const
        pos = NULL;
        //#]
    }
    
    // Get the next position for the iterator
    // Argument void *& pos :
    // The current position
    //## operation getNext(void *) const
    inline void getNext(void *& pos) const {
        //#[ operation getNext(void *) const
        pos = (void*)((Rhp_uintptr_t)pos + 1);
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
    inline Rhp_int32_t getSize(void) const {
        //#[ auto_generated
        return size;
        //#]
    }
    
    ////    Attributes    ////
    

private :

    // The number of elements stored in the array
    Rhp_int32_t count;		//## attribute count
    
    // The array allocated size
    Rhp_int32_t size;		//## attribute size
    
    // The raw array
    void ** theLink;		//## attribute theLink
    
};

#endif



