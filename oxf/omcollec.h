//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: OMCollection
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


#ifndef omcollec_H
#define omcollec_H

//## class OMCollection
#include "OMStaticArray.h"
//## package Design::oxf::Services::Containers::TypeSafe

//## class OMCollection
// A dynamic array
template <class Concept> class OMCollection : public OMStaticArray<Concept> {
public :

    //#[ type DEFAULT_START_SIZE
    #define DEFAULT_START_SIZE 20
    //#]
    
    //#[ type DEFAULT_FACTOR
    #define DEFAULT_FACTOR 2
    //#]
    
    ////    Constructors and destructors    ////
    
    // copy constructor and assignment operator
    // Argument const OMCollection<Concept> & aCollection :
    // The collection to copy
    //## operation OMCollection(const OMCollection<Concept> & )
    explicit inline OMCollection(const OMCollection<Concept> & aCollection) : OMStaticArray<Concept>(0) {
        //#[ operation OMCollection(const OMCollection<Concept> & )
        copy(aCollection);
        //#]
    }
    
    // Constructor
    // Argument const Rhp_int32_t theSize = DEFAULT_START_SIZE :
    // The array initial size
    //## operation OMCollection(Rhp_int32_t)
    explicit inline OMCollection(const Rhp_int32_t theSize = DEFAULT_START_SIZE) : OMStaticArray<Concept>(theSize)  {
        //#[ operation OMCollection(Rhp_int32_t)
        //#]
    }
    
    ////    Operations    ////
    
    // Add an element to the end of the array
    // Argument Concept aConcept :
    // The element to add
    //## operation add(Concept)
    inline void add(Concept aConcept) {
        //#[ operation add(Concept)
        if (this->count >= this->size) {
        	reorganize();
        }
        this->theLink[this->count] = aConcept;
        this->count++;
        //#]
    }
    
    // add new element if in range, without increase of the container size.
    // Argument const Rhp_int32_t anIndex :
    // The index
    // Argument Concept aConcept :
    // The element to add
    //## operation addAt(Rhp_int32_t,Concept)
    inline void addAt(const Rhp_int32_t anIndex, Concept aConcept) {
        //#[ operation addAt(Rhp_int32_t,Concept)
        if (anIndex >= 0) {
        	if (this->count > anIndex) {
        		this->theLink[anIndex] = aConcept;
        	} else {
        		if ( (anIndex == this->count) && 
        	  		 (this->size > this->count) ) {
        			this->theLink[this->count] = aConcept;
        			this->count++; 
        		}
        	}
        }
        //#]
    }
    
    // Assignment operator
    // Argument const OMCollection<Concept> & aCollection :
    // The collection to copy
    //## operation operator=(const OMCollection<Concept> & )
    inline OMCollection<Concept> & operator=(const OMCollection<Concept> & aCollection) {
        //#[ operation operator=(const OMCollection<Concept> & )
        copy(aCollection);
        return *this;
        //#]
    }
    
    // Remove p from the array
    // Argument Concept aConcept :
    // The element to remove
    //## operation remove(Concept)
    inline void remove(Concept aConcept) {
        //#[ operation remove(Concept)
        // Delete aCount
        for (Rhp_int32_t i = 0; i < this->count; i++) {
        	if (this->theLink[i] == aConcept) { 
        		removeByIndex(i);
        		// assuming no duplicates
        		break;
        	}
        }
        //#]
    }
    
    // Cleanup the array
    //## operation removeAll()
    inline void removeAll(void) {
        //#[ operation removeAll()
        OMDELETE(this->theLink, sizeof(Concept) * this->size);
        this->count = 0;
        this->size = DEFAULT_START_SIZE;
        this->theLink = static_cast<Concept*>(OMNEW(Concept, this->size));
        //#]
    }
    
    // Remove the element at the specified index
    // Argument const Rhp_int32_t i :
    // The index
    //## operation removeByIndex(Rhp_int32_t)
    inline void removeByIndex(const Rhp_int32_t i) {
        //#[ operation removeByIndex(Rhp_int32_t)
        this->count--;
        this->theLink[i] = this->theLink[this->count];
        //#]
    }
    
    // Reset the collection size
    // Argument const Rhp_int32_t factor = DEFAULT_FACTOR :
    // resize factor
    //## operation reorganize(Rhp_int32_t)
    inline void reorganize(const Rhp_int32_t factor = DEFAULT_FACTOR) {
        //#[ operation reorganize(Rhp_int32_t)
        Rhp_int32_t f;
        if (factor < 1) {
        	f = 1;
        } else {
            f = factor;
        }
        Rhp_int32_t oldSize = this->size;
        this->size = (this->count * f) + 1;
        Concept* tmpLink = static_cast<Concept*>(OMNEW(Concept, this->size));
        for (Rhp_int32_t i = 0; i < this->count; i++) {
        	tmpLink[i] = this->theLink[i];
        }
        OMDELETE(this->theLink, sizeof(Concept) * oldSize);
        this->theLink = tmpLink;
        //#]
    }
    

private :

    // Copy a collection
    // Argument const OMCollection<Concept> & aCollection :
    // The collection to copy
    //## operation copy(const OMCollection<Concept> & )
    inline void copy(const OMCollection<Concept> & aCollection) {
        //#[ operation copy(const OMCollection<Concept> & )
        OMStaticArray<Concept>::copy(aCollection);
        //#]
    }
    
};

//## package Design::oxf::Services::Containers::TypeSafe

//## class OMCollection

#endif



