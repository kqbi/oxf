//	Component		: oxfFiles 
//	Configuration 	: generic
//	Model Element	: OMUIterator
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


#ifndef OMUIterator_H
#define OMUIterator_H

//## link theLink
#include "OMUAbstractContainer.h"
//## package Design::oxf::Services::Containers::Typeless

//## class OMUIterator
// Iterator over type less containers that derived from OMUAbstractContainer
class RP_FRAMEWORK_DLL OMUIterator {
    ////    Constructors and destructors    ////
    
public :

    // copy constructor
    // Argument const OMUIterator& iter :
    // The other iterator
    //## operation OMUIterator(OMUIterator)
    inline OMUIterator(const OMUIterator& iter) : thePos(iter.thePos), theLink(iter.theLink) {
        //#[ operation OMUIterator(OMUIterator)
        //#]
    }
    
    // Initialize an iterator
    // Argument const OMUAbstractContainer& aContainer :
    // the context container
    //## operation OMUIterator(OMUAbstractContainer)
    explicit inline OMUIterator(const OMUAbstractContainer& aContainer) : thePos(NULL), theLink(&aContainer) {
        //#[ operation OMUIterator(OMUAbstractContainer)
        reset();
        //#]
    }
    
    // Initialize an iterator
    // Argument const OMUAbstractContainer::AbstractContainerPtr& aContainer :
    // the context container
    //## operation OMUIterator(AbstractContainerPtr)
    explicit inline OMUIterator(const OMUAbstractContainer::AbstractContainerPtr& aContainer) : thePos(NULL), 
theLink(aContainer) {
        //#[ operation OMUIterator(AbstractContainerPtr)
        reset();
        //#]
    }
    
    // default constructor
    //## operation OMUIterator()
    inline OMUIterator(void) : thePos(NULL) {
        //#[ operation OMUIterator()
        //#]
    }
    
    // cleanup
    //## operation ~OMUIterator()
    inline virtual ~OMUIterator(void) {
        //#[ operation ~OMUIterator()
        theLink = NULL;
        //#]
    }
    
    ////    Operations    ////
    
    // return the current value
    //## operation operator*()
    inline void * operator*(void) {
        //#[ operation operator*()
        return value();
        //#]
    }
    
    // operator ++ (prefix)
    //## operation operator++()
    inline OMUIterator& operator++(void) {
        //#[ operation operator++()
        return increment();
        //#]
    }
    
    // operator ++ (postfix)
    // Argument const Rhp_int32_t /**/ :
    // C++ standard for post fix ++
    //## operation operator++(Rhp_int32_t)
    inline OMUIterator operator++(const Rhp_int32_t /**/) {
        //#[ operation operator++(Rhp_int32_t)
        OMUIterator T = *this ;	// save status prior to increment
        (void) increment();
        return T; 
        //#]
    }
    
    // Assignment operator
    // Argument const OMUIterator& iter :
    // The other iterator
    //## operation operator=(OMUIterator)
    inline OMUIterator& operator=(const OMUIterator& iter) {
        //#[ operation operator=(OMUIterator)
        theLink = iter.theLink;
        thePos = iter.thePos;
        return (*this);
        //#]
    }
    
    // reset the iterator, to the container's first position
    //## operation reset()
    inline void reset(void) {
        //#[ operation reset()
        theLink->getFirst(thePos);
        //#]
    }
    
    // reset the iterator to a new container
    // Argument const OMUAbstractContainer& newLink :
    // The new context container
    //## operation reset(OMUAbstractContainer)
    inline void reset(const OMUAbstractContainer& newLink) {
        //#[ operation reset(OMUAbstractContainer)
        theLink = &newLink; 
        reset();
        //#]
    }
    
    // return the current value
    //## operation value()
    inline void * value(void) {
        //#[ operation value()
        return (theLink->getCurrent(thePos));
        //#]
    }
    

private :

    // move to the next position
    //## operation _advance()
    inline void _advance(void) {
        //#[ operation _advance()
        theLink->getNext(thePos);
        //#]
    }
    
    // move to the next position, and return it
    //## operation increment()
    inline OMUIterator& increment(void) {
        //#[ operation increment()
        _advance();
        return (*this);
        //#]
    }
    
    ////    Attributes    ////
    
    // the current position of the iterator
    void * thePos;		//## attribute thePos
    
    ////    Relations and components    ////
    
    const OMUAbstractContainer* theLink;		//## link theLink
    
};

#endif



