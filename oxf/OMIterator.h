//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: OMIterator
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


#ifndef OMIterator_H
#define OMIterator_H

//## dependency OMAbstractContainer
#include "OMAbstractContainer.h"
//## package Design::oxf::Services::Containers::TypeSafe

//## class OMIterator
// Iterator on containers derived from OMAbstractContainer
template <class Concept> class OMIterator {
public :

    // Abstract container instantiation used by the iterator
    //## class OMIterator::Container
    typedef OMAbstractContainer<Concept> Container;
    
    // Initialize an empty iterator
    //## operation OMIterator()
    inline OMIterator(void) : thePos(NULL), theLink(NULL) {
        //#[ operation OMIterator()
        //#]
    }
    
    // Initialize an iterator associated with the provided container
    // Argument const Container& aContainer :
    // The iterator context
    //## operation OMIterator(const Container&)
    inline OMIterator(const Container& aContainer) : thePos(NULL), theLink(&aContainer)  {
        //#[ operation OMIterator(const Container&)
        reset();
        //#]
    }
    
    // Initialize an iterator associated with the provided container
    // Argument const Container* aContainer :
    // The iterator context
    //## operation OMIterator(const Container*)
    inline OMIterator(const Container* aContainer) : thePos(NULL), theLink(aContainer) {
        //#[ operation OMIterator(const Container*)
        reset();
        //#]
    }
    
    // Copy constructor
    // Argument const OMIterator<Concept> & iter :
    // The iterator to copy
    //## operation OMIterator(const OMIterator<Concept> & )
    inline OMIterator(const OMIterator<Concept> & iter) : thePos(iter.thePos), theLink(iter.theLink) {
        //#[ operation OMIterator(const OMIterator<Concept> & )
        //#]
    }
    
    // Copy Constructor
    //## operation OMIterator(const OMIterator<Concept>*)
    inline OMIterator(const OMIterator<Concept>* iter) : thePos(iter->thePos), theLink(iter->theLink) {
        //#[ operation OMIterator(const OMIterator<Concept>*)
        //#]
    }
    
    // Assignment operator
    // Argument const OMIterator<Concept> & iter :
    // The iterator to copy
    //## operation operator=(const OMIterator<Concept> & )
    inline OMIterator<Concept> & operator=(const OMIterator<Concept> & iter) {
        //#[ operation operator=(const OMIterator<Concept> & )
        theLink = iter.theLink;
        thePos = iter.thePos;
        return (*this);
        //#]
    }
    
    // Move to the next item in the collection
    //## operation increment()
    inline OMIterator<Concept> & increment(void) {
        //#[ operation increment()
        _advance();
        return (*this);
        //#]
    }
    
    // Get the current item
    //## operation value() const
    inline Concept & value(void) const {
        //#[ operation value() const
        /*LDRA_INSPECTED 7 C  : Can't find a way to have a single return */
        if (theLink != NULL) {
           	return theLink->getCurrent(thePos);
        } else {
           	return OMNullValue<Concept>::get();
        }
        //#]
    }
    
    // Get the current item
    //## operation operator*() const
    inline Concept & operator*(void) const {
        //#[ operation operator*() const
        return value();
        //#]
    }
    
    // Reset the iterator (to the first element in the container)
    //## operation reset()
    inline void reset(void) {
        //#[ operation reset()
        if (theLink != NULL) {
        	theLink->getFirst(thePos); 
        }
        //#]
    }
    
    // Reset the iterator to the specified container
    // Argument const Container& newLink :
    // The new context of the iterator
    //## operation reset(const Container&)
    inline void reset(const Container& newLink) {
        //#[ operation reset(const Container&)
        theLink = &newLink; 
        reset();
        //#]
    }
    
    // Advance to the next item in the collection
    //## operation operator++()
    inline OMIterator<Concept> & operator++(void) {
        //#[ operation operator++()
        return increment(); 
        //#]
    }
    
    // Advance to the next item in the collection (postfix operator)
    // Argument const Rhp_int32_t /**/ :
    // C++ postfix ++ operator dummy argument
    //## operation operator++(Rhp_int32_t)
    inline OMIterator<Concept> operator++(const Rhp_int32_t /**/) {
        //#[ operation operator++(Rhp_int32_t)
        OMIterator<Concept> T(*this) ;	// save status prior to increment
        (void) increment();
        return T; 
        //#]
    }
    

private :

    // advance to the next item in the context collection
    //## operation _advance()
    inline void _advance(void) {
        //#[ operation _advance()
        if (theLink != NULL) {
        	theLink->getNext(thePos);
        }
        //#]
    }
    

public :

    // Cleanup
    //## operation ~OMIterator()
    inline ~OMIterator(void) {
        //#[ operation ~OMIterator()
        theLink = NULL;
        //#]
    }
    
    ////    Attributes    ////
    

private :

    // The current position of the iterator (in the collection)
    void * thePos;		//## attribute thePos
    
    ////    Relations and components    ////
    
    const Container* theLink;		//## link theLink
    
};

//## package Design::oxf::Services::Containers::TypeSafe

//## class OMIterator

#endif



